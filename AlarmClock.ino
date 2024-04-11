/***************************************************
>> File: AlarmClock.ino
>> Author: Ryan Jahnige
>> Description: Master file
***************************************************/

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Calendar.h"

LiquidCrystal lcd(2,3,4,5,6,7,8);
Calendar *clk;

void setup() {
  Serial.begin(250000);
  lcd.init(LCD_2LINEMODE, LCD_5x8FONT);

  clk = new Calendar(&lcd);

  while(lcd.isBusy());
  lcd.displayPower(LCD_DISPLAYON, LCD_CURSOROFF, LCD_BLINKOFF);
}

void loop() {
  clk -> display();
  delay(1000);
}
