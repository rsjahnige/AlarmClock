/***************************************************
>> File: AlarmClock.ino
>> Author: Ryan Jahnige
>> Description: Master file
***************************************************/

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "JoyStick.h"

#include "Context.h"
#include "Calendar.h"
#include "TempHumid.h"

#define BUTTON    11        // Pin to read fo button click

LiquidCrystal lcd(3,4,5,6,7,8,9);
JoyStick ctrl(A0,A1,2);

Calendar clk(&lcd);
TempHumid env(&lcd, 10);

Context *view = &env;

void setup() {
  Serial.begin(250000);
  lcd.init(LCD_2LINEMODE, LCD_5x8FONT);
  delay(500);
  view -> setContext();
  delay(500);
  view -> display();          // Default behavior is to startup with clock visible

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  uint8_t usr_action = 0;

  unsigned long timer = millis() + 250;
  while (timer > millis()) {
    if (digitalRead(BUTTON) == LOW) {
      view = &clk;
      view -> changeContext();
    }
  }

  usr_action = ctrl.listen();
  switch (usr_action) {
    case JS_HOLD:
      view -> buttonHold();
      break;
    case JS_PRESS:
      view -> buttonPress();
      break;
    case JS_BACK:                      // Added additional button for this functionality
      Serial.println("Go Back");
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
