#include "PassiveBuzzer.h"

PassiveBuzzer::PassiveBuzzer(uint8_t pin, melody tune) 
{
  _pin = pin;

  switch (tune) {
    case TUNE_ALLEGRO: 
      _melody.pitch = allegro_pitch;
      _melody.rhythm = allegro_rhythm;
      _melody.length = 23;
      _melody.tempo = 80;
      break;
    default:
      _melody.pitch = default_pitch;
      _melody.rhythm = default_rhythm;
      _melody.length = 8;
      _melody.tempo = 60;
  }
}

void PassiveBuzzer::playMelody(void)
{
  double time = 1000 + (1-((_melody.tempo*1000)/60000))*1000;
  unsigned int duration;

  for (int i=0; i < _melody.length; i++) {
    duration = time / _melody.rhythm[i];
    tone(_pin, _melody.pitch[i], duration);
    delay(duration);            // tone() in non-blocking so we need to wait for the note to finish
    noTone(_pin);
  }
}