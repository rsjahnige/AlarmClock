#ifndef CALENDAR_H
#define CALENDAR_H

#include "LiquidCrystal.h"
#include "Arduino.h"

class Calendar
{
public:
  Calendar(const LiquidCrystal *lcd);
  void display(void);

protected:
  void update(void);
  void printTime(void);
  void printDate(void);

private:
  unsigned int _year;
  uint8_t _month, _day; 
  uint8_t _hour, _minute, _second;

  char *_date_str = "XXX 00 0000\0";
  char *_time_str = "00:00:00\0";

  LiquidCrystal *_lcd;
};

#endif