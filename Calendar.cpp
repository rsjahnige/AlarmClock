#include "Calendar.h"

Calendar::Calendar(const LiquidCrystal *lcd)
{
  _lcd = lcd;

  _year = 2024;
  _month = 4;
  _day = 11;
  _hour = 3;
  _minute = 59;
  _second = 0;
}

void Calendar::display(void) 
{
  update();
  if ((millis() / 1000) < 10) printDate();
  printTime();
}

void Calendar::update(void)
{
  long seconds;

  // Assumes display() is called at least every minute
  seconds = (millis() / 1000) % 60;
  if (seconds < _second) {
    if ((_minute += 1) == 60) {
      _minute = 0; 
      if ((_hour += 1) == 24) {
        _hour = 0;
      }
    }
  }
  _second = seconds;
}

void Calendar::printTime(void)
{
  uint8_t high, low;                  // High and low base 10 integer digits

  high = _hour / 10;
  low = _hour % 10;
  _time_str[0] = (char)(high | 0x30);
  _time_str[1] = (char)(low | 0x30);

  high = _minute / 10;
  low = _minute % 10;
  _time_str[3] = (char)(high | 0x30);
  _time_str[4] = (char)(low | 0x30);

  high = _second / 10;
  low = _second % 10;
  _time_str[6] = (char)(high | 0x30);
  _time_str[7] = (char)(low | 0x30);

  while(_lcd -> isBusy());
  _lcd -> setDDRAMAddr(0x40);         // Set DDRAM Address to second line
  while(_lcd -> isBusy());
  _lcd -> print(_time_str);
}

void Calendar::printDate(void) 
{
  uint8_t high, low;

  switch (_month) {
    case 1:
      _date_str[0] = 'J';
      _date_str[1] = 'a';
      _date_str[2] = 'n';
      break;
    case 2:
      _date_str[0] = 'F';
      _date_str[1] = 'e';
      _date_str[2] = 'b';
      break;
    case 3:
      _date_str[0] = 'M';
      _date_str[1] = 'a';
      _date_str[2] = 'r';
      break;
    case 4:
      _date_str[0] = 'A';
      _date_str[1] = 'p';
      _date_str[2] = 'r';
      break;
    case 5:
      _date_str[0] = 'M';
      _date_str[1] = 'a';
      _date_str[2] = 'y';
      break;
    case 6:
      _date_str[0] = 'J';
      _date_str[1] = 'u';
      _date_str[2] = 'n';
      break;
    case 7:
      _date_str[0] = 'J';
      _date_str[1] = 'u';
      _date_str[2] = 'l';
      break;
    case 8:
      _date_str[0] = 'A';
      _date_str[1] = 'u';
      _date_str[2] = 'g';
      break;
    case 9:
      _date_str[0] = 'S';
      _date_str[1] = 'e';
      _date_str[2] = 'p';
      break;
    case 10:
      _date_str[0] = 'O';
      _date_str[1] = 'c';
      _date_str[2] = 't';
      break;
    case 11:
      _date_str[0] = 'N';
      _date_str[1] = 'o';
      _date_str[2] = 'v';
      break;
    case 12:
      _date_str[0] = 'D';
      _date_str[1] = 'e';
      _date_str[2] = 'c';
      break;
    default:
      _date_str[0] = 'E';
      _date_str[1] = 'R';
      _date_str[2] = 'R';
  }

  high = _day / 10;
  low = _day % 10;
  _date_str[4] = (char)(high | 0x30); 
  _date_str[5] = (char)(low | 0x30);

  high = _year / 1000;
  low = _year % 1000;
  _date_str[7] = (char)(high | 0x30);
  high = low / 100;
  low = low % 100;
  _date_str[8] = (char)(high | 0x30);
  high = low / 10;
  low = low % 10;
  _date_str[9] = (char)(high | 0x30);
  _date_str[10] = (char)(low | 0x30);

  while(_lcd -> isBusy());
  _lcd -> setDDRAMAddr(0x00);         // Set DDRAM Address to first line
  while(_lcd -> isBusy());
  _lcd -> print(_date_str);
}