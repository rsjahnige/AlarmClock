#ifndef TEMPHUMID_H
#define TEMPHUMID_H

#include "Arduino.h"

class TempHumid 
{
public:
  TempHumid(uint8_t dataPin);
  void readData(void);

private:
  uint8_t _data_pin; 
  uint8_t _data[5];    
};

#endif