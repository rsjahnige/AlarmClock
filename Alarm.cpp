#include "Alarm.h"

namespace UserInterface
{
  Alarm::Alarm(const LiquidCrystal* lcd) : Context(lcd, CNTX_EDIT)
  {
    _time = new Time(12);
    _melody = &Database::Default;
  }

  void Alarm::display(void) 
  {
    char *timeStr = new char[9];
    
    if (Context::getMode() != CNTX_EDIT) 
      Context::setMode(CNTX_EDIT);

    _time -> toString(timeStr);
    Context::print("Time: \0", LCD_LINE1);
    Context::print(timeStr, LCD_LINE1+6);

    Context::print("Tone: \0", LCD_LINE2);
    Context::print(_melody -> name, LCD_LINE2+6);

    Context::setCursor(ALRM_HOUR);

    delete [] timeStr;
  }

  void Alarm::shiftLeft(void) 
  {
    if (Context::getMode() == CNTX_INPUT) return;

    switch (Context::getCursor()) {
    case ALRM_MINUTE:
      Context::setCursor(ALRM_HOUR);
      break;
    case ALRM_MELODY:
      Context::setCursor(ALRM_MINUTE);
      break;
    default:
      Context::setCursor(ALRM_MELODY);
    }
  }

  void Alarm::shiftRight(void) 
  {
    if (Context::getMode() == CNTX_INPUT) return;

    switch (Context::getCursor()) {
    case ALRM_HOUR:
      Context::setCursor(ALRM_MINUTE);
      break;
    case ALRM_MINUTE:
      Context::setCursor(ALRM_MELODY);
      break;
    default:
      Context::setCursor(ALRM_HOUR);
    }
  }

  void Alarm::shiftDown(void) 
  {
    if (Context::getMode() == CNTX_INPUT) {
      if (Context::getCursor() < LCD_LINE2) Context::shiftDown();
      return;
    }

    char *str = new char[9];        // Max size of both Time and Melody strings
    uint8_t cursorPos = Context::getCursor(); 
    
    for (int i=0; i < 8; i++) str[i] = 0x20;
    str[8] = '\0';

    if (Context::getCursor() < LCD_LINE2) Context::print(str, ALRM_HOUR);
    else Context::print(str, ALRM_MELODY);
      
    switch (cursorPos) {
    case ALRM_HOUR:
      _time -> decrementHour();
      break;
    case ALRM_MINUTE:
      _time -> decrementMinute();
      break;
    default:
      _melody = Database::getNextMelody(_melody);
    }

    if (Context::getCursor() < LCD_LINE2) {
      _time -> toString(str);
      Context::print(str, ALRM_HOUR);
    } else 
      Context::print(_melody->name, ALRM_MELODY);

    Context::setCursor(cursorPos);    // Set cursor back to original position

    delete [] str;
  }

  void Alarm::shiftUp(void)
  {
    if (Context::getMode() == CNTX_INPUT) {
      if (Context::getCursor() >= LCD_LINE2) Context::shiftUp();
      return;
    }

    char *str = new char[9];        // Max size of both Time and Melody strings
    uint8_t cursorPos = Context::getCursor(); 
    
    for (int i=0; i < 8; i++) str[i] = 0x20;
    str[8] = '\0';

    if (Context::getCursor() < LCD_LINE2) Context::print(str, ALRM_HOUR);
    else Context::print(str, ALRM_MELODY);
      
    switch (cursorPos) {
    case ALRM_HOUR:
      _time -> incrementHour();
      break;
    case ALRM_MINUTE:
      _time -> incrementMinute();
      break;
    default:
      _melody = Database::getNextMelody(_melody);
    }

    if (Context::getCursor() < LCD_LINE2) {
      _time -> toString(str);
      Context::print(str, ALRM_HOUR);
    } else 
      Context::print(_melody->name, ALRM_MELODY);

    Context::setCursor(cursorPos);    // Set cursor back to original position

    delete [] str;
  }

  // Allows user to return from Save/Delete context
  void Alarm::buttonHold(void)
  {
    this -> display();
  }

  int8_t Alarm::buttonPress(void) 
  {
    uint8_t result = -1;

    if (Context::getMode() == CNTX_INPUT) {
      if (Context::getCursor() < LCD_LINE2) result = ALRM_SAVE;
      else result = ALRM_DELETE;
    } else { 
      Context::clearDisplay();
      Context::print(">Save\0", LCD_LINE1);
      Context::print(">Delete\0", LCD_LINE2);

      Context::setMode(CNTX_INPUT);
      Context::setCursor(LCD_LINE1);
    }

    return result;
  }
};
