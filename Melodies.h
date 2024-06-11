#ifndef MELODIES_H
#define MELODIES_H

#include "PassiveBuzzer.h"
using Buzzer::Melody; 

namespace Database 
{
  extern const Melody Default;
  extern const Melody Allegro;

  // Used to loop through all pre-defined melodies
  const Melody* getNextMelody(const Melody* current);
};

#endif
