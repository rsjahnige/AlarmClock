#ifndef CONTEXT_H
#define CONTEXT_H

#include "LiquidCrystal.h"

#define CNTX_DISPLAY 0x00       // Cursor and Blink off
#define CNTX_EDIT 0x01          // Cursor and Blink on - user can modify display values
#define CNTX_INPUT 0x02         // Cursor and Blink on - user can select display values

#define CONTEXT 0x00            // Type identifier - derived classes need to define their own

class Context
{
public:
  Context(const LiquidCrystal *lcd, uint8_t mode);

  virtual void setCursor(uint8_t position) final;
  virtual void setMode(uint8_t mode) final { _mode = mode; }
  virtual uint8_t getMode(void) final { return _mode; }
  virtual uint8_t getCursor(void) final { return _csr_position; }

  virtual void setContext(void) final;
  virtual void changeContext(void) final;

  virtual void shiftRight(void);
  virtual void shiftLeft(void);
  virtual void shiftDown(void);
  virtual void shiftUp(void);
  virtual char buttonPress(void);
  virtual void buttonHold(void);

  // These functions should be overridden in each derived class     
  virtual void display(void) { print("Context::ERROR"); }
  virtual void refresh(void);  
  virtual uint8_t type(void) { return CONTEXT; } 

  // !!! Input strings should explicitly be NULL terminated ('\0')        !!!
  // !!! If pos=0xFF, then str will be printed starting at _csr_position  !!!
  virtual unsigned int print(char *str, uint8_t pos=0xFF) final;

private:
  const LiquidCrystal *_lcd;
  uint8_t _csr_position;
  uint8_t _mode;
};

#endif