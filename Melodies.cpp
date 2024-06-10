#include "Melodies.h"

namespace Melodies 
{
  const Melody Default = {
    0, 
    "Default\0",
    //{NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4},
    nullptr,
    //{4, 8, 8, 4, 4, 4, 4, 4},
    nullptr,
    60,
    8
  };
  
  const Melody Allegro = {
    1,
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
    switch (current->id) {
    case 0: 
      return &Allegro;
    default:
      return &Default;
    }
  }
}
