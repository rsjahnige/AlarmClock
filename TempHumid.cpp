#include "TempHumid.h"

TempHumid::TempHumid(const LiquidCrystal *lcd, uint8_t dataPin) : Context(lcd, CNTX_DISPLAY) 
{
  _data_pin = dataPin;

  _humid_int = 0;
  _humid_dec = 0;

  _temp_int = 0;
  _temp_dec = 0;                
}

void TempHumid::display(void)
{
  Context::print("Temp: ", LCD_LINE1);
  Context::print("Humidity: ", LCD_LINE2);
}

void TempHumid::refresh(void)
{
  if (readData()) {
    printData(TEMP, _temp_int, _temp_dec);
    printData(HUMIDITY, _humid_int, _humid_dec);
  }
}

// Return's true if data received is valid
bool TempHumid::readData(void)
{
  unsigned long timer;
  unsigned int parity = 0;
  uint8_t data[5] = {0};

  // Send start signal
  pinMode(_data_pin, OUTPUT);
  digitalWrite(_data_pin, LOW);
  delay(18);
  digitalWrite(_data_pin, HIGH);

  // Receive response signal
  pinMode(_data_pin, INPUT);
  while (digitalRead(_data_pin) != LOW);
  delayMicroseconds(80);
  while (digitalRead(_data_pin) != HIGH);
  delayMicroseconds(80);

  // Read data from sensor
  while(digitalRead(_data_pin) == HIGH);
  for (int i=0; i < 40; i++) {
    while(digitalRead(_data_pin) == LOW);
    timer = micros();
    while(digitalRead(_data_pin) == HIGH);
    timer = micros() - timer;
    if (timer > 30) data[int(i/8)] |= (0x80 >> (i%8));
  }

  for (int i=0; i < 4; i++) parity += data[i];

  if (parity == data[4]) {
    _humid_int = data[0];
    _humid_dec = data[1];
    _temp_int = data[2];
    _temp_dec = data[3];
    return true;
  }

  return false;
}

void TempHumid::printData(uint8_t addr, uint8_t integer, uint8_t decimal) 
{
  uint8_t index = 0;
  char str[8];        // Supports maximum of 2 decimal places for integer and fractional elements

  if (integer > 9) {
    str[index] = (char)((integer / 10) | 0x30);
    str[index+1] = (char)((integer % 10) | 0x30);
    index += 2;
  } else {
    str[index] = (char)(integer | 0x30);
    index += 1;
  }

  str[index] = '.';
  index += 1;

  if (decimal > 9) {
    str[index] = (char)((decimal / 10) | 0x30);
    str[index+1] = (char)((decimal % 10) | 0x30);
    index += 2;
  } else {
    str[index] = (char)(decimal | 0x30);
    index += 1;
  }

  if (addr == TEMP) {
    str[index] = 0xDF;
    str[index+1] = 'C';
    index += 2;
  } else if (addr == HUMIDITY) {
    str[index] = '%';
    index += 1;
  }

  str[index] = '\0';

  Context::print(str, addr);
}