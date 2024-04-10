#include "Calendar.h"

Calendar::Calendar(const LiquidCrystal *lcd)
{
  _lcd = lcd;

  _year = 0;
  _month = 0;
  _day = 0;
  _hour = 0;
  _minute = 0;
  _second = 0;
}

void Calendar::displayTime(void) 
{
  _lcd -> clearDisplay();
  _lcd -> print("Hello, Calendar\0");
  /*
  long seconds = (millis() / 1000) % 60;

  _second += (seconds - _second);

  Serial.print("Hour: ");
  Serial.println(_hour);
  Serial.print("Minute: ");
  Serial.println(_minute);
  Serial.print("Second: ");
  Serial.println(_second);

  if (_second >= 59) {
    _minute += 1;
  }
  */
}