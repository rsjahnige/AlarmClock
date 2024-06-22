/*********************************************************************
>>  File:   PassiveBuzzer.h
>>  Author: Ryan Jahnige
>>
>>  Description:  Header file for the PassiveBuzzer class which is used
>>                to play individual tones and full melodies.
**********************************************************************/
#ifndef PASSIVEBUZZER_H
#define PASSIVEBUZZER_H

#include <Arduino.h>

class PassiveBuzzer 
{
public:
  PassiveBuzzer(uint8_t pin);

  // converts Arduino::tone() to a blocking function
  void playTone(unsigned int frequency, unsigned int duration);

  void playMelody(uint8_t length, unsigned int* pitch, 
                  unsigned int* rhythm, double tempo);   

private:
  uint8_t _pin;
};

#endif
