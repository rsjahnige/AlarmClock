/*********************************************************************
>>  File: AlarmClock.ino
>>  Author: Ryan Jahnige
>>
>>  Description: Main file
**********************************************************************/

#include <Arduino.h>

#include "LiquidCrystal.h"
#include "JoyStick.h"

#include "List.h"

#include "Context.h"
#include "Menu.h"
#include "Clock.h"
#include "TempHumid.h"

//#define BUTTON    11        // Pin to read for button click

using LCD1602A::LiquidCrystal;
using LinkedList::Node;
using namespace UserInterface;

// Initialize hardware classes
LiquidCrystal lcd(3,4,5,6,7,8,9);
JoyStick ctrl(A0,A1,2);

// Initialize user interface classes
Menu menu(&lcd);
Clock clk(&lcd);
TempHumid env(&lcd, 10);
Context *view = &clk;     // Default behavior is to startup with clock visible

// Function used to switch between LCD display screens
void changeView(Context* newView) {
  view = newView;
  view -> changeContext();
}

// Initialize main menu
Menu::Item clock = {"1.Calendar\0", &clk, changeView};
Menu::Item envir = {"2.Temp&Humidity\0", &env, changeView};
Menu::Item alarm = {"3.Set Alarm\0", nullptr, nullptr};
Node<Menu::Item> *head;

void setup() {
  Serial.begin(250000);

  // Initialize LCD 
  lcd.init(LCD_2LINEMODE, LCD_5x8FONT);
  delay(500);
  view -> setContext();
  delay(500);
  view -> display();          

  // Build Main Menu
  head = new Node<Menu::Item>(clock);
  LinkedList::insertNode(head, envir);
  LinkedList::insertNode(head->getNextLink(), alarm);
  menu.setNode(head);

  //pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  uint8_t usr_action = 0;

  /*
  unsigned long timer = millis() + 250;
  while (timer > millis()) {
    if (digitalRead(BUTTON) == LOW) {     // Return to main menu
      view = &menu;
      view -> changeContext();
    }
  }
  */

  usr_action = ctrl.listen();
  switch (usr_action) {
    case JS_HOLD:
      view -> buttonHold();
      break;
    case JS_PRESS:
      if ((view -> type()) != MENU)
        changeView(&menu);
      else
        view -> buttonPress();
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

  // Make sure the clock stays up to date even when not visible
  if ((view -> type()) != CLOCK)
    clk.updateDateTime();
}
