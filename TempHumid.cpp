#include "TempHumid.h"

TempHumid::TempHumid(const LiquidCrystal *lcd, uint8_t dataPin) : Context(lcd, CNTX_DISPLAY) 
{
  _sensor = new ThermoHygro(dataPin);            
}

TempHumid::~TempHumid() 
{
  delete _sensor;
}

void TempHumid::display(void)
{
  Context::print("Temp: \0", LCD_LINE1);
  printData(TEMP);
  Context::print("Humidity: \0", LCD_LINE2);
  printData(HUMIDITY);
}

void TempHumid::refresh(void)
{
  RealNum sensor_val;

  sensor_val = _sensor -> getTemperature();
  if (sensor_val != _dsp_temp) {
    _dsp_temp = sensor_val;
    printData(TEMP);
  }

  sensor_val = _sensor -> getHumidity();
  if (sensor_val != _dsp_humid) { 
    _dsp_humid = sensor_val;
    printData(HUMIDITY);
  }
}

/*
  Weird things happen when you try to overwrite an array index that has 
  previously been set to NULL within the same instance of a function call. 
  What is causing this to happen? Is it Arduino specific?
*/
void TempHumid::printData(uint8_t addr) 
{
  uint8_t index = 0;
  char str[10] = {0x20};              // 10 is max length of a temperature reading string (including units); 0x20 is bit pattern for empty space

  str[9] = '\0';                      // Add NULL terminator for compliance with Context::print() function             
  Context::print(str, addr);          // Clear currently displayed values

  if (addr == TEMP) {
    index = _dsp_temp.toString(10, str);
    str[index] = 0xDF;                      // bit pattern for ASCII 'degree' character
    str[index+1] = 'C';
    index += 2;
  } else if (addr == HUMIDITY) {
    index = _dsp_humid.toString(10, str);
    str[index] = '%';
    index += 1;
  }

  str[index] = '\0';
  Context::print(str, addr);
}
