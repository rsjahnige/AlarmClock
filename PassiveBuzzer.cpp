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

  void PassiveBuzzer::playMelody(uint8_t length, unsigned int* pitch,
                                  uint8_t* rhythm, double tempo)
  {
    unsigned int duration;
    double time = 1000 + (1-((tempo*1000)/60000))*1000;

    for (int i=0; i < length; i++) {
      duration = time / rhythm[i];
      playTone(pitch[i], duration);
    }
  }
}
