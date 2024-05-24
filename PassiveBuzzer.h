#ifndef PASSIVEBUZZER_H
#define PASSIVEBUZZER_H

#include "Arduino.h"

namespace Buzzer
{
  struct Melody 
  { 
    unsigned int *pitch;
    unsigned int *rhythm;
    double tempo;     
    uint8_t length;         // length of pitch & rhythm arrays; must be equal
  };

  class PassiveBuzzer 
  {
  public:
    PassiveBuzzer(uint8_t pin);

    void playTone(unsigned int frequency, unsigned int duration);     // converts Arduino::tone() to a blocking function 
    void playMelody(struct Melody tune);   

  private:
    uint8_t _pin;
  };
};

#endif