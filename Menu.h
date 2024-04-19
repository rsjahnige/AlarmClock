#ifndef MENU_H
#define MENU_H

#include "Arduino.h"
#include "Context.h"

#define MENU    0x01

class Menu : public Context 
{
public:
  Menu(const LiquidCrystal *lcd, uint8_t num_options=3, char **options=nullptr);
  ~Menu();

  void display(void) override;

  void shiftLeft(void) override { return; }
  void shiftRight(void) override { return; }
  void shiftDown(void) override;
  void shiftUp(void) override;

private:
  char **_options;
  uint8_t _size;
  uint8_t _index;       // Array index of first visible line
};

#endif