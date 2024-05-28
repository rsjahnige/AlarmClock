/*  
  This could be implemented as a Linked List so that user can add and remove 
  options without reinitializing the array each time (e.g., when dealing with alarms).
  Would the effort to restructure this class outweigh the benifits of such 
  an implementation?
    - Using a templated class could be benificial for when an Alarm class is defined
      - How will a character sting vs an Alarm object be printed to the LCD ??
*/

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

  virtual void display(void) override;

  virtual void shiftLeft(void) override { return; }
  virtual void shiftRight(void) override { return; }
  virtual void shiftDown(void) override;
  virtual void shiftUp(void) override;

protected:
  /*** !!! Untested functions !!! ***/
  virtual void addOption(char *option) final;
  virtual void rmOption(uint8_t index) final;

private:
  char **_options;
  uint8_t _size;
  uint8_t _index;       // Array index of first visible line
};

#endif
