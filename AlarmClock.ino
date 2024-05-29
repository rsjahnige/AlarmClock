/*********************************************************************
>>  File: AlarmClock.ino
>>  Author: Ryan Jahnige
>>
>>  Description: Main file
**********************************************************************/

#include <Arduino.h>

#include "LiquidCrystal.h"
#include "JoyStick.h"

#include "Context.h"
#include "Menu.h"
#include "Calendar.h"
#include "TempHumid.h"

#define BUTTON    11        // Pin to read for button click

LiquidCrystal lcd(3,4,5,6,7,8,9);
JoyStick ctrl(A0,A1,2);

Menu menu(&lcd);
Calendar clk(&lcd);
TempHumid env(&lcd, 10);

Context *view = &clk;     // Default behavior is to startup with clock visible

void setup() {
  Serial.begin(250000);
  lcd.init(LCD_2LINEMODE, LCD_5x8FONT);
  delay(500);
  view -> setContext();
  delay(500);
  view -> display();          

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  uint8_t usr_action = 0;
  uint8_t usr_option;

  unsigned long timer = millis() + 250;
  while (timer > millis()) {
    if (digitalRead(BUTTON) == LOW) {
      // Return to main menu
      view = &menu;
      view -> changeContext();
    }
  }

  usr_action = ctrl.listen();
  switch (usr_action) {
    case JS_HOLD:
      view -> buttonHold();
      break;
    case JS_PRESS:
      usr_option = view -> buttonPress();
      switch (usr_option) {
        case CALENDAR:
          view = &clk;
          break;
        case TEMPHUMID:
          view = &env;
          break;
      }
      if (usr_option != '\0') view -> changeContext();
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
  if ((view -> type()) != CALENDAR)
    clk.updateDateTime();
}
