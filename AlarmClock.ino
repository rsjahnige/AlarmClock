/*********************************************************************
>>  File: AlarmClock.ino
>>  Author: Ryan Jahnige
>>
>>  Description: Main file
**********************************************************************/

#include <Arduino.h>

#include "LiquidCrystal.h"
#include "JoyStick.h"
#include "PassiveBuzzer.h"

#include "List.h"
#include "Melodies.h"

#include "Context.h"
#include "Menu.h"
#include "Clock.h"
#include "Alarm.h"
#include "TempHumid.h"

#define STOP_BUTTON    12        // Pin for the button used to stop the buzzer

using LCD1602A::LiquidCrystal;
using LinkedList::Node;
using Database::Melody;

using namespace UserInterface;

// Initialize hardware classes
LiquidCrystal lcd(3,4,5,6,7,8,9);
PassiveBuzzer bzr(11);
JoyStick ctrl(A0,A1,2);

// Initialize user interface classes
Menu menu(&lcd);
Menu alarmMenu(&lcd);
Clock clk(&lcd);
TempHumid env(&lcd, 10);

Context *view = &clk;     // Currently visible context; default is to start up with clock visible

// Pointer to the begining of each linked list
Node<Menu::Item> *mainHead;
Node<Menu::Item> *alarmHead;

// Function used to switch between LCD display screens
void changeView(Context* newView) {
  view = newView;
  view -> changeContext();
}

void newAlarm(Context* alarm) {
  alarm = new Alarm(&lcd);
  Menu::Item temp = {nullptr, alarm, changeView};
  LinkedList::insertAfter(alarmHead, temp);
  alarmMenu.setNode(alarmHead -> getNextLink());
  changeView(alarm);
}

void alarmString(Alarm* alrm, char output[9]) {
    char *temp = new char[9];
    (alrm -> getTime()).toString(temp);

    output[0] = '>';
    output[1] = ((alrm -> getMelody()) -> name)[0];   // First character of Melody.name
    output[2] = '-';
   
    for (int i=0; i < 5; i++)
      output[3+i] = temp[i];

    output[8] = '\0';
    delete [] temp;
}

// Initialize main menu
Menu::Item clock = {"1.Calendar\0", &clk, changeView};
Menu::Item envir = {"2.Temp&Humidity\0", &env, changeView};
Menu::Item alarm = {"3.Set Alarm\0", &alarmMenu, changeView};

// Intialize alarm list 
Menu::Item back = {"<Back\0", &menu, changeView};
Menu::Item addAlarm = {"+Alarm\0", nullptr, newAlarm};

void setup() {
  Serial.begin(250000);

  // Initialize LCD 
  lcd.init(LCD_2LINEMODE, LCD_5x8FONT);
  delay(500);
  view -> setContext();
  delay(500);
  view -> display();          

  // Build Main Menu
  mainHead = new Node<Menu::Item>(clock);
  LinkedList::insertAfter(mainHead, envir);
  LinkedList::insertAfter(mainHead->getNextLink(), alarm);
  menu.setNode(mainHead);

  // Build Alarm Menu
  alarmHead = new Node<Menu::Item>(back);
  LinkedList::insertAfter(alarmHead, addAlarm);
  alarmMenu.setNode(alarmHead);

  pinMode(STOP_BUTTON, INPUT_PULLUP);
}

void loop() {
  uint8_t usr_action = 0;
  int8_t usr_option = 0;  

  usr_action = ctrl.listen();
  switch (usr_action) {
    case JS_HOLD:
      view -> buttonHold();
      break;
    case JS_PRESS:
      if ((view -> getMode()) == CNTX_DISPLAY) 
        changeView(&menu);
      else
        usr_option = view -> buttonPress();
      break;
    case JS_LEFT:
      view -> shiftLeft();
      break;
    case JS_RIGHT:
      view -> shiftRight();
      break;
    case JS_DOWN:
      view -> shiftDown();
      break;
    case JS_UP:
      view -> shiftUp();
      break;
    default:
      view -> refresh();                 
  }

  if (((view -> type()) == ALARM) && 
      ((view -> getMode()) == CNTX_INPUT)) {
    if (usr_option == ALRM_SAVE) {
      Menu::Item alarm = alarmMenu.getNode() -> getData();
      if (alarm.string == nullptr) alarm.string = new char[9];     
      alarmString(alarm.cntx, alarm.string);
      alarmMenu.getNode() -> setData(alarm);
      alarmMenu.setNode(alarmHead);
      changeView(&alarmMenu);
    } else if (usr_option == ALRM_DELETE) {
      LinkedList::deleteNode(alarmMenu.getNode()); 
      alarmMenu.setNode(alarmHead);
      changeView(&alarmMenu);
    }
  }

  if (view -> type() != ALARM) {    // Prevents the alarm from playing when the user is setting it 
    Node<Menu::Item> *currNode = (alarmHead->getNextLink());        // Skip 'Back' node
    while (((currNode->getData()).cntx != nullptr)) {               // while Menu::Item != addAlarm
      Alarm *currAlarm = (currNode->getData()).cntx;                // Cast Context to Alarm object
      if ((currAlarm->getTime()) == clk.getTime()) {
        clk.changeContext();                    // Clock becomes visible when the alarm sounds
        Melody *currMelody = currAlarm -> getMelody();

        // TODO - how can we mitigate the user having to hold the button to stop the alarm
        while (digitalRead(STOP_BUTTON) != LOW) {                   
          bzr.playMelody(currMelody->length, currMelody->pitch, 
                          currMelody->rhythm, currMelody->tempo); 
          clk.updateDateTime();     // Clock will update but UI will not until alarm is stopped
        }
        
        view -> changeContext();                  // Re-display visible view before alarm sounded
        break;
      } else {
        currNode = currNode -> getNextLink();
      }
    }
  }

  // Make sure the clock stays up to date even when not visible
  if ((view -> type()) != CLOCK)
    clk.updateDateTime();
}
