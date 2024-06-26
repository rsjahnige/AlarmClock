/*********************************************************************
>>  File:   TempHumid.h
>>  Author: Ryan Jahnige
>>
>>  Description:  Header file for the TempHumid class which is derived 
>>                from the Context class. Uses the DHT11 senor to 
>>                measure temperature and humidity of the surrounding
>>                environment which is then displayed to the LCD screen.
**********************************************************************/
#ifndef TEMPHUMID_H
#define TEMPHUMID_H

#include <Arduino.h>
#include "Context.h"
#include "ThermoHygro.h"

using namespace DHT11;
using namespace UserInterface;

#define TEMPHUMID 0x32      // Type identifier - needs to match Menu list index 

// LCD Address locations for start of sensor values
#define TEMP      0x06
#define HUMIDITY  0x4a

class TempHumid : public Context
{
public:
  TempHumid(const LiquidCrystal *lcd, uint8_t dataPin);
  ~TempHumid();

  void display(void) override;
  void refresh(void) override;
  uint8_t type(void) override { return TEMPHUMID; }

  void buttonHold(void) override { return; }      // Context mode switching is prohibited

protected:
  void printData(uint8_t addr);

private:
  ThermoHygro *_sensor;

  // Currently displayed temperature and humidity values
  RealNum _dsp_temp;
  RealNum _dsp_humid;
};

#endif
