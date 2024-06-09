#include "Clock.h"

namespace UserInterface
{
  uint8_t Date::getNumDays(void) 
  {
    uint8_t result;

    if ((_month % 2) == 1) {            // January, March, May, July, September, November
      result = 31;
    } else if (_month == 2) {                             // Feburary
      if ((((_year % 4) == 0) && ((_year % 100) != 0))    // Leap year - centenials 
          || ((_year % 400) == 0))                        // Centenial leap year
        result = 29;
      else 
        result = 28;                          
    } else {                            // April, June, August, October, December 
      result = 30;
    }

    return result;
  }

  void Time::toString(char output[9])
  {
    uint8_t length;
    
    output[2] = ':';
    output[5] = ':';
    output[8] = '\0';

    length = itos(_hour, 2, output); 
    if (length < 2) {
      output[1] = output[0];
      output[0] = '0';
    }

    length = itos(_minute, 2, output+3);
    if (length < 2) {
      output[4] = output[3];
      output[3] = '0';
    }

    length = itos(_second, 2, output+6);
    if (length < 2) {
      output[7] = output[6];
      output[6] = '0'; 
    }
  }

  void Clock::display(void)
  {
    char *dspString = new char[9];

    // Print date format first
    Context::print("XXX XX XXXX\0", LCD_LINE1); 

    printMonth();
    printDay();
    printYear();

    _time.toString(dspString);
    Context::print(dspString, LCD_LINE2);
    delete [] dspString;

  }
  
  void Clock::refresh(void) 
  {
    if (Context::getMode() == CNTX_DISPLAY) {
      switch (updateDateTime()) {
        case CLK_YEAR:
          printYear();
        case CLK_MONTH:
          printMonth();
        case CLK_DAY:
          printDay();
        case CLK_HOUR:
          printTimeSegment(CLK_HOUR);
        case CLK_MINUTE:
          printTimeSegment(CLK_MINUTE);
        default:
          printTimeSegment(CLK_SECOND);
      }
    }
  }
  
  // Returns highest Date/Time segment that needs to be updated
  uint8_t Clock::updateDateTime(void)
  {
    unsigned long seconds;
    uint8_t result = CLK_SECOND;
  
    // Update Time object - assumes refresh() is called at least every minute
    seconds = (millis() / 1000) % 60;
    if (_offset == 60) _offset -= seconds;        // _offset is set to 60 by buttonHold()
  
    seconds = (seconds + _offset) % 60;          
    if (seconds < _time.getSecond()) {
      _time.incrementMinute();
      result = CLK_MINUTE;

      if (_time.getMinute() == 0) {
        _time.incrementHour();
        result = CLK_HOUR;
      }
    }
    _time.setSecond(seconds);
  
    // Update Date object; if necessary
    if ((result == CLK_HOUR) && (_time.getHour() == 0)) {
      _date.incrementDay();
      result = CLK_DAY;

      if (_date.getDay() == 1) {
        _date.incrementMonth();
        result = CLK_MONTH;

        if (_date.getMonth() == 1) {
          _date.incrementYear();
          result = CLK_YEAR;
        }
      }
    }
  
    return result;
  }
  
  void Clock::shiftRight(void) 
  {
    if (Context::getMode() == CNTX_EDIT) {
      switch (Context::getCursor()) {
        case CLK_MONTH:
          Context::setCursor(CLK_DAY);
          break;
        case CLK_DAY:
          Context::setCursor(CLK_YEAR);
          break;
        case CLK_YEAR:
          Context::setCursor(CLK_HOUR);
          break;
        case CLK_HOUR:
          Context::setCursor(CLK_MINUTE);
          break;
        case CLK_MINUTE:
          Context::setCursor(CLK_SECOND);
          break;
        case CLK_SECOND:
          Context::setCursor(CLK_MONTH);        // Loop back around to the beginning
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
        case CLK_MONTH:                     // Loop around to the end
          Context::setCursor(CLK_SECOND);    
          break;
        case CLK_DAY:
          Context::setCursor(CLK_MONTH);
          break;
        case CLK_YEAR:
          Context::setCursor(CLK_DAY);
          break;
        case CLK_HOUR:
          Context::setCursor(CLK_YEAR);
          break;
        case CLK_MINUTE:
          Context::setCursor(CLK_HOUR);
          break;
        case CLK_SECOND:
          Context::setCursor(CLK_MINUTE);        
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
        case CLK_MONTH:
          _date.incrementMonth();
          printMonth();
          Context::setCursor(CLK_MONTH);
          break;
        case CLK_DAY:
          _date.incrementDay();
          printDay();
          Context::setCursor(CLK_DAY);
          break;
        case CLK_YEAR:
          _date.incrementYear();
          printYear();
          Context::setCursor(CLK_YEAR);
          break;
        case CLK_HOUR:
          _time.incrementHour();
          printTimeSegment(CLK_HOUR);
          Context::setCursor(CLK_HOUR);
          break;
        case CLK_MINUTE:
          _time.incrementMinute();
          printTimeSegment(CLK_MINUTE);
          Context::setCursor(CLK_MINUTE);
          break;
      }
    }
  }
  
  void Clock::shiftDown(void)
  {
      if (Context::getMode() == CNTX_EDIT) {
      switch(Context::getCursor()) {
        case CLK_MONTH:
          _date.decrementMonth();
          printMonth();
          Context::setCursor(CLK_MONTH);
          break;
        case CLK_DAY:
          _date.decrementDay();
          printDay();
          Context::setCursor(CLK_DAY);
          break;
        case CLK_YEAR:
          _date.decrementYear();
          printYear();
          Context::setCursor(CLK_YEAR);
          break;
        case CLK_HOUR:
          _time.decrementHour();
          printTimeSegment(CLK_HOUR);
          Context::setCursor(CLK_HOUR);
          break;
        case CLK_MINUTE:
          _time.decrementMinute();
          printTimeSegment(CLK_MINUTE);
          Context::setCursor(CLK_MINUTE);
          break;
      }
    }
  }

  void Clock::buttonPress(void)
  {
    if (Context::getMode() == CNTX_EDIT)      // TODO - this logic is redundent; how can we improve?
      Clock::buttonHold();
  }

  void Clock::buttonHold(void) 
  {
    if (Context::getMode() == CNTX_DISPLAY) {
      _time.setSecond(0);
      printTimeSegment(CLK_SECOND);
    } else {
      _offset = 60;         // Signals to updateDateTime() that an offset should be applied
    }
  
    Context::buttonHold();
  }
  
  void Clock::printMonth(void) 
  {
    char *output;

    switch (_date.getMonth()) {
      case 1:
        output = "Jan\0";
        break;
      case 2:
        output = "Feb\0";
        break;
      case 3:
        output = "Mar\0";
        break;
      case 4:
        output = "Apr\0";
        break;
      case 5:
        output = "May\0";
        break;
      case 6:
        output = "Jun\0";
        break;
      case 7:
        output = "Jul\0";
        break;
      case 8:
        output = "Aug\0";
        break;
      case 9:
        output = "Sep\0";
        break;
      case 10:
        output = "Oct\0";
        break;
      case 11:
        output = "Nov\0";
        break;
      case 12:
        output = "Dec\0"; 
        break;
      default:
        output = "ERR\0";
    }

    Context::print(output, CLK_MONTH);
  }
  
  void Clock::printDay(void)
  {
    uint8_t length;
    char *output = new char[3];
  
    length = itos(_date.getDay(), 2, output);
    if (length < 2) { 
      output[1] = output[0]; 
      output[0] = '0';
    }
    output[2] = '\0';

    Context::print(output, CLK_DAY);
    delete [] output;
  }
  
  // Note that DHT11::itos() cannot be used here since _year is
  // an 'unsigned int'
  void Clock::printYear(void)
  {
    uint8_t high, low;
    char *output = new char[5];
  
    high = _date.getYear() / 1000;
    low = _date.getYear() % 1000;
    output[0] = (char)(high | 0x30);

    high = low / 100;
    low = low % 100;
    output[1] = (char)(high | 0x30);

    high = low / 10;
    low = low % 10;
    output[2] = (char)(high | 0x30);
    output[3] = (char)(low | 0x30);

    output[4] = '\0';  
    Context::print(output, CLK_YEAR);
    delete [] output;
  }
  
  void Clock::printTimeSegment(uint8_t segment)
  {
    uint8_t length;
    char *output = new char[3];
  
    switch (segment) {
      case CLK_HOUR:
        length = itos(_time.getHour(), 2, output);
        break;
      case CLK_MINUTE:
        length = itos(_time.getMinute(), 2, output);
        break;
      default:
        length = itos(_time.getSecond(), 2, output);
    }
    
    if (length < 2) {
      output[1] = output[0];
      output[0] = '0';
    }
    output[2] = '\0';

    Context::print(output, segment);
    delete [] output;
  }
};
