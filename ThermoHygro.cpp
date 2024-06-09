#include "ThermoHygro.h"

namespace DHT11
{
  // Note that range(int8_t) = [-128,127]. Thus, the max size of the 
  // resulting string is 4 characters (including negative sign)
  uint8_t itos(int8_t num, uint8_t size, char* output) 
  {
    uint8_t index = 0;
    char converse_str[4] = {'\0'}; 
    uint8_t u_num;

    if (num < 0) u_num = (uint8_t)(num ^ 0xFF) + 1;     // +1 accounts for the offset bw +/- numbers in binary
    else u_num = (uint8_t)num; 

    // bitwise-OR of 0x30 is used to convert integer bits to ASCII equivalent 
    do {
      converse_str[index] = (char)((u_num % 10) | 0x30);
      u_num /= 10;
      index += 1;
    } while (u_num != 0);

    // Add negative sign (if applicable)
    if (num < 0) {
      converse_str[index] = '-';
      index += 1;
    }

    for (int i=0; i < index; i++) {
      if (i < size) output[i] = converse_str[index - (i+1)];
      else break;
    }

    return index;
  }

  /************************
  >> RealNum Class Methods
  ************************/
  RealNum::RealNum(int8_t integer, uint8_t decimal)
  {
    _integer = integer;
    _decimal = decimal;
  }

  bool RealNum::operator ==(const RealNum& right)
  {
    return ((_integer == right._integer) 
            && (_decimal == right._decimal));
  }

  bool RealNum::operator !=(const RealNum& right)
  {
    return ((_integer != right._integer)
            || (_decimal != right._decimal));
  }


  /*
    Note that range(int8_t) = [-128, 127] and _decimal represents a percentage,
    so range(_decimal) = [0, 100). Thus, the max_len(result string) = 
    1 (integer sign) + 3 (int) + 1 (decimal point) + 2 (dec) = 7
  */ 
  uint8_t RealNum::toString(uint8_t size, char *result) const
  { 
    // Iterator variables
    uint8_t index = 0;        
    uint8_t it;

    char num_str[4];              // see comment for itos() function about the size 
    char local_result[7];         // see comment above about size specification

    // Append integer portion of real number
    it = DHT11::itos(_integer, 4, num_str);
    for (int i=0; i < it; i++) {
      local_result[index] = num_str[i];
      index += 1;
    }

    // Add decimal point to string
    local_result[index] = '.';
    index += 1;

    // Append decimal portion of real number
    it = DHT11::itos(_decimal, 4, num_str);
    for (int i=0; i < it; i++) {
      local_result[index] = num_str[i];
      index += 1;
    }

    it = 0;
    while ((it < index) && (it < size)) {     // copy local string to input char array
      result[it] = local_result[it];
      it += 1;
    }

    return it;
  }

  /************************
  >> ThermoHygro Class Methods
  ************************/
  ThermoHygro::ThermoHygro(uint8_t dataPin, unsigned long timeDelay)
  {
    _data_pin = dataPin;
    _time_delay = timeDelay;
    _timer = millis(); 
  }

  const RealNum ThermoHygro::getTemperature()
  {
    unsigned long time = millis();
    if (abs(time - _timer) > _time_delay) readData();

    return _temp;
  }

  const RealNum ThermoHygro::getHumidity()
  {
    unsigned long time = millis();
    if (abs(time - _timer) > _time_delay) readData();

    return _humid;
  }

  void ThermoHygro::readData(void)
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
      _humid._integer = data[0];
      _humid._decimal = data[1];
      _temp._integer = data[2];
      _temp._decimal = data[3];
    }

    _timer = millis();      // update class timer
  }
}
