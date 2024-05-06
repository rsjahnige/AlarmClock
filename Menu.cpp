#include "Menu.h"

Menu::Menu(const LiquidCrystal *lcd, uint8_t num_options, char **options) : Context(lcd, CNTX_INPUT)
{
  _index = 0;
  _size = num_options;
  _options = new char*[_size];

  if (options == nullptr) { 
    _options[0] = "1.Calendar\0";
    _options[1] = "2.Temp&Humidity\0"; 
    _options[2] = "3.Set Alarm\0";
  } else {
    for (int i=0; i < _size; i++)
      _options[i] = options[i];
  }
}

Menu::~Menu()
{
  for (int i=0; i < _size; i++) 
    delete _options[i];

  delete [] _options;
}

void Menu::display(void)
{
  if (_size > 0) Context::print(_options[_index], LCD_LINE1);
  if (_size > 1) Context::print(_options[_index+1], LCD_LINE2);

  Context::setCursor(LCD_LINE1);
}

void Menu::shiftDown(void) 
{
  if (Context::getCursor() >= LCD_LINE2) {
    _index = (_index + 1) % (_size - 1);
    Context::changeContext();
  } else {
    Context::shiftDown(); 
  }
}

void Menu::shiftUp(void)
{
  if (Context::getCursor() < LCD_LINE2) {
    _index = ((_index + (_size-1)) - 1) % (_size - 1);    // Another workaround for unsupported negative modulo arithmatic
    Context::changeContext();
  } else {
    Context::shiftUp();
  }
}

void Menu::addOption(char *new_option)
{
  char **temp = new char*[_size+1];

  for (int i=0; i < _size; i++) {
    temp[i] = _options[i];
    delete _options[i];
  }
  temp[_size] = new_option;

  delete [] _options;

  _options = temp;
  _size += 1;
}

void Menu::rmOption(uint8_t index) 
{
  char **temp = new char*[_size-1];

  for (int i=0; i < _size; i++) {
    if (i != index) temp[i] = _options[i];
    delete _options[i];
  }

  delete [] _options;
  
  _options = temp;
  _size -= 1;
}