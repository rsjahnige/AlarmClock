#ifndef CALENDAR_H
#define CALENDAR_H

#include <Arduino.h>

#include "Context.h"
#include "LiquidCrystal.h"

#define CALENDAR 0x31      // Type identifier - needs to match Menu.h character index

// Months of the year -- KEEP 0 INDEX ??
#define JANUARY   0x00
#define FEBURARY  0x01
#define MARCH     0x02
#define APRIL     0x03
#define MAY       0x04
#define JUNE      0x05
#define JULY      0x06
#define AUGUST    0x07
#define SEPTEMBER 0x08 
#define OCTOBER   0x09
#define NOVEMBER  0x0a
#define DECEMBER  0x0b

// LCD Address locations
#define MONTH     0x00 
#define DAY       0x04 
#define YEAR      0x07 
#define HOUR      0x40 
#define MINUTE    0x43 
#define SECOND    0x46

using LCD1602A::LiquidCrystal;
using namespace UserInterface;

class Calendar : public Context
{
public:
  Calendar(const LiquidCrystal *lcd);

  void display(void) override;
  void refresh(void) override;
  uint8_t type(void) override { return CALENDAR; }

  void shiftRight(void) override;
  void shiftLeft(void) override;
  void shiftUp(void) override;
  void shiftDown(void) override;
  void buttonHold(void) override;

  uint8_t updateDateTime(void);

protected:
  void printMonth(void);
  void printDay(void);
  void printYear(void);

  void printTimeSegment(uint8_t segment);

private:
  unsigned int _year;
  uint8_t _month, _day;     
  uint8_t _hour, _minute, _second;
  uint8_t _offset;                 // Seconds offset from system clock when user sets the time                   
};

#endif
