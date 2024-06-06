#include "Context.h"

Context::Context(const LiquidCrystal *lcd, uint8_t mode)
{
  _lcd = lcd;
  _mode = mode;
  _csr_position = _lcd -> getAddrCntr();
}

void Context::setCursor(uint8_t position)
{
  while(_lcd -> isBusy());
  _lcd -> setDDRAMAddr(position);
  while(_lcd -> isBusy());
  _csr_position = _lcd -> getAddrCntr();
}

void Context::setContext(void)
{
  while(_lcd -> isBusy());
  switch (_mode) {
    case (CNTX_DISPLAY):
      _lcd -> displayPower(LCD_DISPLAYON, LCD_CURSOROFF, LCD_BLINKOFF);
      break;
    default:
      _lcd -> displayPower(LCD_DISPLAYON, LCD_CURSORON, LCD_BLINKON);
  }
}

void Context::changeContext(void)
{
  while(_lcd -> isBusy());
  _lcd -> clearDisplay();
  while(_lcd -> isBusy());
  _csr_position = _lcd -> getAddrCntr();

  setContext();
  this -> display();
}

// TODO - add a check for when the display needs to shift
//      - needs to be added to shiftLeft() as well
void Context::shiftRight(void)  // UN-TESTED
{ 
  if (_mode != CNTX_DISPLAY) {
    if ((_csr_position != 0x4F) && (_csr_position != 0x67))     // Assumes 2-line mode of operation
      setCursor(_csr_position+1);
  }
}

void Context::shiftLeft(void)
{
  if (_mode != CNTX_DISPLAY) {
    if ((_csr_position != 0x00) && (_csr_position != 0x40))     // Assumes 2-line mode of operation
      setCursor(_csr_position-1);
  }
}

void Context::shiftDown(void)
{
  if (_mode != CNTX_DISPLAY) {
    if (_csr_position < 0x40)
      setCursor(_csr_position + 0x40);
  }
}

void Context::shiftUp(void)
{
  if (_mode != CNTX_DISPLAY) {
    if (_csr_position >= 0x40)
      setCursor(_csr_position - 0x40);
  }
}

void Context::buttonPress(void)
{
  /*
  char result = '\0';						// Returns null character when not in INPUT mode

  if (_mode == CNTX_INPUT) {
    while(_lcd -> isBusy());
    _lcd -> setDDRAMAddr(_csr_position);     // Ensure DDRAM is being read
    while(_lcd -> isBusy());
    result = (char)(_lcd -> read(DATA));
    while(_lcd -> isBusy());
    _lcd -> setDDRAMAddr(_csr_position);     // Set cursor position back to read location
  }
  return result;
  */
}

void Context::buttonHold(void)
{
  if (_mode == CNTX_DISPLAY) 
    _mode = CNTX_EDIT;
  else if  (_mode == CNTX_EDIT) 
    _mode = CNTX_DISPLAY;

  if (_mode != CNTX_INPUT) {
    setContext();
    while(_lcd -> isBusy());
    _lcd -> returnHome();
    _csr_position = _lcd -> getAddrCntr();
  }
}

void Context::refresh(void) 
{
  while(_lcd -> isBusy());
  _csr_position = _lcd -> getAddrCntr();
}

/*  
  TODO - I don't like that derived classes need to deal with NULL termination. 
  Would a size parameter be a better option? - Calendar an Menu classes would need
  to be updated if we choose to take this path
*/
unsigned int Context::print(char *str, uint8_t pos)
{
  unsigned int index = 0;

  while(_lcd -> isBusy());
  if (pos != 0xFF) _lcd -> setDDRAMAddr(pos);
  else _lcd -> setDDRAMAddr(_csr_position);       // Done to ensure that the DDRAM is being written to

  while (str[index] != '\0') {
    uint8_t id = int(str[index]);                 // Need to revisit this logic; why am I using int() to cast to a uint8_t?
    while (_lcd -> isBusy());
    _lcd -> write(id, DATA);
    index++;
  }

  while (_lcd -> isBusy());
  _csr_position = _lcd -> getAddrCntr();

  return index;
}
