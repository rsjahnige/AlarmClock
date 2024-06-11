#ifndef MELODIES_H
#define MELODIES_H

#include <inttypes.h>       // uint8_t

namespace Database 
{
  typedef struct Melody 
  { 
    char* name;
    uint8_t length;         // length of pitch & rhythm arrays; must be equal
    unsigned int* pitch;
    uint8_t* rhythm;
    uint8_t tempo;                
  };

  // Pre-defined melodies
  extern const Melody Default;
  extern const Melody Allegro;

  // Used to loop through all pre-defined melodies
  const Melody* getNextMelody(const Melody* current);
};

#endif
