#ifndef TEMPHUMID_H
#define TEMPHUMID_H

#include "Arduino.h"
#include "Context.h"

// LCD Address locations
#define TEMP      0x06
#define HUMIDITY  0x4a

class TempHumid : public Context
{
public:
  TempHumid(const LiquidCrystal *lcd, uint8_t dataPin);

  void display(void) override;
  void refresh(void) override;

  void buttonHold(void) override { return; }      // Context mode switching is prohibited

protected:
  bool readData(void);
  void printData(uint8_t addr, uint8_t integer, uint8_t decimal);

private:
  uint8_t _data_pin; 

  uint8_t _humid_int, _humid_dec;
  uint8_t _temp_int, _temp_dec;    
};

#endif