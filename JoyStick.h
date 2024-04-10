#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

// Resting pin states
#define SW_REST HIGH
#define XY_REST 512

class JoyStick 
{
public:
  JoyStick(uint8_t xPin, uint8_t yPin, uint8_t swPin);
  void listen(void);

private:
  uint8_t _x_pin;
  uint8_t _y_pin;
  uint8_t _sw_pin; 
};

#endif