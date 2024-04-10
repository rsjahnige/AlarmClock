#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>
#include "LiquidCrystal.h"
#include "Arduino.h"

class Calendar
{
public:
  Calendar(const LiquidCrystal *lcd);

  void displayTime(void);

private:
  uint8_t _year, _month, _day; 
  uint8_t _hour, _minute, _second;

  LiquidCrystal *_lcd;
};

#endif