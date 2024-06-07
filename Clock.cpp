#include "Clock.h"

namespace UserInterface
{
  Clock::Clock(const LiquidCrystal *lcd) : Context(lcd, CNTX_DISPLAY)
  {
    _year = 2024;
    _month = 0;
    _day = 1;
    _hour = 0;
    _minute = 0;
    _second = 0;
    _offset = 0;
  }
  
  void Clock::display(void)
  {
    Context::print("XXX XX XXXX\0", LCD_LINE1);
    Context::print("XX:XX:XX\0", LCD_LINE2);
  
    printMonth();
    printDay();
    printYear();
    printTimeSegment(HOUR);
    printTimeSegment(MINUTE);
    printTimeSegment(SECOND);
  }
  
  void Clock::refresh(void) 
  {
    if (Context::getMode() == CNTX_DISPLAY) {
      switch (updateDateTime()) {
        case YEAR:
          printYear();
        case MONTH:
          printMonth();
        case DAY:
          printDay();
        case HOUR:
          printTimeSegment(HOUR);
        case MINUTE:
          printTimeSegment(MINUTE);
        default:
          printTimeSegment(SECOND);
      }
    }
  }
  
  // Returns highest Date/Time segment that needs to be updated
  uint8_t Clock::updateDateTime(void)
  {
    long seconds;
    uint8_t result = SECOND;
  
    // Assumes refresh() is called at least every minute
    // TODO - I need to revisit this logic and consider what happens 
    //        when the user sets the time
    seconds = (millis() / 1000) % 60;
    if (_offset == 60) _offset -= seconds;       // Set to 60 by buttonHold()
  
    seconds = (seconds + _offset) % 60;
    if (seconds < _second) {
      result = MINUTE;
      if ((_minute += 1) == 60) {
        _minute = 0; 
        result = HOUR;
        if ((_hour += 1) == 24) {
          _hour = 0;
        }
      }
    }
    _second = seconds;
  
    // !!! TODO - make sure this logic works !!! 
    // !!! greater than has been used for days to mitigate adverse effects of possible user error !!!
    if ((result == HOUR) && (_hour == 0)) {
      if (((_month % 2) == 1) && (_day >= 31)) {              // January, March, May, July, September, November
        _day = 1; 
        _month += 1;
        result = MONTH;
      } else if (((_month % 2) == 0) && (_day >= 30)) {       // April, June, August, October, December
        _day = 1;
        _month += 1;
        result = MONTH;
      } else if ((_month == 2) && (_day >= 28)) {              // Feburary
        if ((_year % 4) != 0) {                               // Not a leap year
          _day = 1;
          _month += 1;
        } else if (((_year % 4) == 0) && (_day >= 29)) {      // Leap year
          _day = 1;
          _month += 1;
        }
        result = MONTH;
      } else {
        _day += 1;
        result = DAY;
      } 
    }
  
    if (_month == 12) {
      _month = 0;
      _year += 1;
      result = YEAR;
    }
  
    return result;
  }
  
  void Clock::shiftRight(void) 
  {
    if (Context::getMode() == CNTX_EDIT) {
      switch (Context::getCursor()) {
        case MONTH:
          Context::setCursor(DAY);
          break;
        case DAY:
          Context::setCursor(YEAR);
          break;
        case YEAR:
          Context::setCursor(HOUR);
          break;
        case HOUR:
          Context::setCursor(MINUTE);
          break;
        case MINUTE:
          Context::setCursor(SECOND);
          break;
        case SECOND:
          Context::setCursor(MONTH);        // Loop back around to the beginning
          break;
        default:
          Serial.println("Clock::shiftRight() : ERROR");
      }
    }
  }
  
  void Clock::shiftLeft(void) 
  {
    if (Context::getMode() == CNTX_EDIT) {
      switch (Context::getCursor()) {
        case MONTH:                     // Loop around to the end
          Context::setCursor(SECOND);    
          break;
        case DAY:
          Context::setCursor(MONTH);
          break;
        case YEAR:
          Context::setCursor(DAY);
          break;
        case HOUR:
          Context::setCursor(YEAR);
          break;
        case MINUTE:
          Context::setCursor(HOUR);
          break;
        case SECOND:
          Context::setCursor(MINUTE);        
          break;
        default:
          Serial.println("Clock::shiftLeft() : ERROR");
      }
    }
  }
  
  void Clock::shiftUp(void) 
  {
    if (Context::getMode() == CNTX_EDIT) {
      switch(Context::getCursor()) {
        case MONTH:
          _month = (_month + 1) % 12;
          printMonth();
          Context::setCursor(MONTH);
          break;
        case DAY:
          _day = (_day == 31) ? 1 : (_day + 1);         // TODO - addd modulo depending on Month ??
          printDay();
          Context::setCursor(DAY);
          break;
        case YEAR:
          _year += 1;
          printYear();
          Context::setCursor(YEAR);
          break;
        case HOUR:
          _hour = (_hour + 1) % 24;
          printTimeSegment(HOUR);
          Context::setCursor(HOUR);
          break;
        case MINUTE:
          _minute = (_minute + 1) % 60;
          printTimeSegment(MINUTE);
          Context::setCursor(MINUTE);
          break;
      }
    }
  }
  
  void Clock::shiftDown(void)
  {
      if (Context::getMode() == CNTX_EDIT) {
      switch(Context::getCursor()) {
        case MONTH:
          _month = ((_month + 12) - 1) % 12;      // Workaround - Arduino doesn't like negative modulo arithmatic
          printMonth();
          Context::setCursor(MONTH);
          break;
        case DAY:
          _day = (_day == 1) ? 31 : (_day - 1);         // TODO - addd modulo depending on Month ??
          printDay();
          Context::setCursor(DAY);
          break;
        case YEAR:
          _year -= 1;
          printYear();
          Context::setCursor(YEAR);
          break;
        case HOUR:
          _hour = ((_hour + 24) - 1) % 24;
          printTimeSegment(HOUR);
          Context::setCursor(HOUR);
          break;
        case MINUTE:
          _minute = ((_minute + 60) - 1) % 60;
          printTimeSegment(MINUTE);
          Context::setCursor(MINUTE);
          break;
      }
    }
  }
  
  void Clock::buttonHold(void) 
  {
    if (Context::getMode() == CNTX_DISPLAY) {
      _second = 0;
      printTimeSegment(SECOND);
    } else {
      _offset = 60;         // Signals to updateDateTime() that an offset should be applied
    }
  
    Context::buttonHold();
  }
  
  void Clock::printMonth(void) 
  {
    switch (_month) {
      case JANUARY:
        Context::print("Jan\0", MONTH);
        break;
      case FEBURARY:
        Context::print("Feb\0", MONTH);
        break;
      case MARCH:
        Context::print("Mar\0", MONTH);
        break;
      case APRIL:
        Context::print("Apr\0", MONTH);
        break;
      case MAY:
        Context::print("May\0", MONTH);
        break;
      case JUNE:
        Context::print("Jun\0", MONTH);
        break;
      case JULY:
        Context::print("Jul\0", MONTH);
        break;
      case AUGUST:
        Context::print("Aug\0", MONTH);
        break;
      case SEPTEMBER:
        Context::print("Sep\0", MONTH);
        break;
      case OCTOBER:
        Context::print("Oct\0", MONTH);
        break;
      case NOVEMBER:
        Context::print("Nov\0", MONTH);
        break;
      case DECEMBER:
        Context::print("Dec\0", MONTH);
        break;
      default:
        Context::print("ERR\0", MONTH);
    }
  }
  
  void Clock::printDay(void)
  {
    unsigned int high, low;
    char output[3] = "XX\0";
  
    high = _day / 10;
    low = _day % 10;
    output[0] = (char)(high | 0x30); 
    output[1] = (char)(low | 0x30);
  
    Context::print(output, DAY);
  }
  
  void Clock::printYear(void)
  {
    unsigned int high, low;
    char output[5] = "XXXX\0";
  
    high = _year / 1000;
    low = _year % 1000;
    output[0] = (char)(high | 0x30);
    high = low / 100;
    low = low % 100;
    output[1] = (char)(high | 0x30);
    high = low / 10;
    low = low % 10;
    output[2] = (char)(high | 0x30);
    output[3] = (char)(low | 0x30);
  
    Context::print(output, YEAR);
  }
  
  void Clock::printTimeSegment(uint8_t segment)
  {
    uint8_t high, low;                  // High and low base 10 integer digits
    char output[3] = "XX\0";
  
    switch (segment) {
      case HOUR:
        high = _hour / 10;
        low = _hour % 10;
        break;
      case MINUTE:
        high = _minute / 10;
        low = _minute % 10;
        break;
      default:
        high = _second / 10;
        low = _second % 10;
    }
    
    output[0] = (char)(high | 0x30);
    output[1] = (char)(low | 0x30);
  
    Context::print(output, segment);
  }
};
