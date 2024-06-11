#include "Melodies.h"

namespace Database 
{
  const Melody Default = {
    "Default\0",
    8,
    60,
    new unsigned int[8]{NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4},
    new unsigned int[8]{4, 8, 8, 4, 4, 4, 4, 4}
  };
  
  const Melody Allegro = {
    "Allegro\0",
    23,
    50,
    new unsigned int[23]{NOTE_C4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3, REST, NOTE_GS3, NOTE_GS3, 
                          NOTE_GS3, REST, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_G4, 
                          NOTE_G4, NOTE_F4, NOTE_DS4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_DS4},
    new unsigned int[23]{1,4,3,3,3,4,3,3,3,4,3,3,3,1,4,4,4,3,1,4,4,4,1}
  };

  const Melody* getNextMelody(const Melody* current) 
  {
    if ((current->name) == Default.name) return &Allegro;
    else return &Default;
  }
}
