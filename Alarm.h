#ifndef ALARM_H
#define ALARM_H

#include "Menu.h"
#include "Clock.h"
#include "Context.h"
#include "Melodies.h"
#include "PassiveBuzzer.h"

#define ALARM 0x03    // TODO - revist these global definitions

#define ALRM_HOUR     0x06
#define ALRM_MINUTE   0x09
#define ALRM_MELODY   0x46

#define ALRM_SAVE     0x01
#define ALRM_DELETE   0x02

using Buzzer::Melody;

namespace UserInterface 
{
  class Alarm : public Context
  {
  public:
    Alarm(const LiquidCrystal* lcd);

    const Time* getTime() const     { return _time; }
    const Melody* getMelody() const { return _melody; }

    void display(void) override;
    void refresh(void) override { return; }
    uint8_t type(void) override { return ALARM; }

    void shiftLeft(void) override;
    void shiftRight(void) override;
    void shiftDown(void) override;
    void shiftUp(void) override;

    int8_t buttonPress(void) override;
    void buttonHold(void) override;

  private:
    Time *_time;
    Melody *_melody;
  };
};

#endif
