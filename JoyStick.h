/*********************************************************************
>>  File:   JoyStick.h
>>  Author: Ryan Jahnige
>>
>>  Description:  Header file for the JoyStick class which is used to 
>>                listen for user actions from an external joy stick 
>>                module.
>>
>>  Note: To my knowledge, Arduino's do not support parallel computing; 
>>        therefore, the listen() method use a do-while loop take control 
>>        of the program for a maximum of 1 second - see JoyStick::listen()
>>        for further details.
**********************************************************************/
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

// Resting pin states
#define SW_REST HIGH
#define XY_REST 512

// User actions
#define JS_PRESS  0x01
#define JS_HOLD   0x02
#define JS_LEFT   0x03
#define JS_RIGHT  0x04
#define JS_DOWN   0x05
#define JS_UP     0x06    

class JoyStick 
{
public:
  JoyStick(uint8_t xPin, uint8_t yPin, uint8_t swPin);
  uint8_t listen(void);

private:
  uint8_t _x_pin;
  uint8_t _y_pin;
  uint8_t _sw_pin; 
};

#endif
