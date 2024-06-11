#include "Melodies.h"

namespace Database 
{
  const Melody Default = {
    "Default\0",
    //{NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4},
    nullptr,
    //{4, 8, 8, 4, 4, 4, 4, 4},
    nullptr,
    60,
    8
  };
  
  const Melody Allegro = {
    "Allegro\0",
    //{NOTE_C4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3, REST, NOTE_GS3, NOTE_GS3, NOTE_GS3, REST,
    //  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_DS4, 
    //  NOTE_D4, NOTE_G4, NOTE_G4, NOTE_DS4},
    nullptr,
    // {1,4,3,3,3,4,3,3,3,4,3,3,3,1,4,4,4,3,1,4,4,4,1},
    nullptr,
    50,
    23
  };

  const Melody* getNextMelody(const Melody* current) 
  {
    if ((current->name) == Default.name) return &Allegro;
    else return &Default;
  }
}
