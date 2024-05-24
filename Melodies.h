#ifndef MELODIES_H
#define MELODIES_H

#include "PassiveBuzzer.h"
using Buzzer::Melody;

Melody DEFAULT = {
  {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4},
  {4, 8, 8, 4, 4, 4, 4, 4},
  60,
  8
};

Melody ALLEGRO = {
  {NOTE_C4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3, REST, NOTE_GS3, NOTE_GS3, NOTE_GS3, REST,
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_DS4, 
    NOTE_D4, NOTE_G4, NOTE_G4, NOTE_DS4},
  {1,4,3,3,3,4,3,3,3,4,3,3,3,1,4,4,4,3,1,4,4,4,1},
  50,
  23
};

#endif