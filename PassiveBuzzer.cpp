#include "PassiveBuzzer.h"

namespace Buzzer
{
  PassiveBuzzer::PassiveBuzzer(uint8_t pin) 
  {
    _pin = pin;
  }

  void PassiveBuzzer::playTone(unsigned int frequency, unsigned int duration)
  {
    tone(_pin, frequency, duration);
    delay(duration);            // tone() in non-blocking so we need to wait for the note to finish
    noTone(_pin);
  }

  void PassiveBuzzer::playMelody(struct Melody tune)
  {
    double time = 1000 + (1-((tune.tempo*1000)/60000))*1000;
    unsigned int duration;

    for (int i=0; i < tune.length; i++) {
      duration = time / tune.rhythm[i];
      playTone(tune.pitch[i], duration);
    }
  }
}