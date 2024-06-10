#ifndef MELODIES_H
#define MELODIES_H

#include "PassiveBuzzer.h"
using Buzzer::Melody; 

namespace Melodies 
{
  extern const Melody Default;
  extern const Melody Allegro;

  const Melody* getNextMelody(const Melody* current);
};

#endif
