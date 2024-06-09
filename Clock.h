#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

#include "Context.h"
#include "ThermoHygro.h"      // itos()
#include "LiquidCrystal.h"

#define CLOCK 0x31      // Type identifier - needs to match Menu.h character index

// LCD Address locations
#define CLK_MONTH     0x00 
#define CLK_DAY       0x04 
#define CLK_YEAR      0x07 
#define CLK_HOUR      0x40 
#define CLK_MINUTE    0x43 
#define CLK_SECOND    0x46

using LCD1602A::LiquidCrystal;
using DHT11::itos;

namespace UserInterface 
{
  class Date 
  {
  public:
    Date(unsigned int year=2024, uint8_t month=1, uint8_t day=1) :
          _year(year), _month(month), _day(day) {}

    unsigned int getYear(void) const    { return _year; }
    uint8_t getMonth(void) const        { return _month; }
    uint8_t getDay(void) const          { return _day; }

    void setYear(unsigned int year)     { _year = year; }
    void setMonth(uint8_t month)        { _month = month; }
    void setDay(uint8_t day)            { _day = day; }

    uint8_t getNumDays(void);   // Returns number of days in current month - Gregorian Calendar

    void incrementYear(void)            { _year = (_year + 1) % 10000; }    // max year is 9999
    void incrementMonth(void)           { _month = (_month % 12) + 1; }
    void incrementDay(void)             { _day = (_day % getNumDays()) + 1; }

    void decrementYear(void)            { _year = (_year + 9999) % 10000; }
    void decrementMonth(void)           { _month = (_month == 1) ? 12 : (_month + 11) % 12; }
    void decrementDay(void)             { _day = (_day == 1) ? getNumDays() : (_day+getNumDays()-1) %getNumDays(); }
      
  private:
    unsigned int _year;
    uint8_t _month, _day;
  };

  class Time
  {
  public:
    Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0) :
          _hour(hour), _minute(minute), _second(second) {}

    uint8_t getHour(void) const     { return _hour; }
    uint8_t getMinute(void) const   { return _minute; }
    uint8_t getSecond(void) const   { return _second; }

    void setHour(uint8_t hour)      { _hour = hour; }
    void setMinute(uint8_t minute)  { _minute = minute; }
    void setSecond(uint8_t second)  { _second = second; }

    void incrementHour(void)        { _hour = (_hour + 1) % 24; }
    void incrementMinute(void)      { _minute = (_minute + 1) % 60; }

    void decrementHour(void)        { _hour = (_hour + 23) % 24; }
    void decrementMinute(void)      { _minute = (_minute + 59) % 60; }

    // !!! WARNING - compiler does not catch calls to this  !!! 
    // !!! function with invaid input array sizes           !!!
    void toString(char output[9]);

  private:
    uint8_t _hour, _minute, _second;
  };

  class Clock : public Context
  {
  public:
    Clock(const LiquidCrystal *lcd) : Context(lcd, CNTX_DISPLAY) {}
  
    void display(void) override;
    void refresh(void) override;
    uint8_t type(void) override { return CLOCK; }
  
    void shiftRight(void) override;
    void shiftLeft(void) override;
    void shiftUp(void) override;
    void shiftDown(void) override;
    void buttonPress(void) override;
    void buttonHold(void) override;
  
    uint8_t updateDateTime(void);
  
  protected:
    void printMonth(void);
    void printDay(void);
    void printYear(void);
  
    void printTimeSegment(uint8_t segment);
  
  private:
    Date _date;
    Time _time;
    uint8_t _offset;                 // Seconds offset from system clock when user sets the time                   
  };
};

#endif
