#include "LiquidCrystal.h"

LiquidCrystal::LiquidCrystal(uint8_t rsPin, uint8_t rwPin, uint8_t enablePin, 
                              uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _rs_pin = rsPin;
  _rw_pin = rwPin;
  _enable_pin = enablePin;

   _num_pins = 4;
  _data_pins = new uint8_t[_num_pins];
  _data_pins[0] = d4;
  _data_pins[1] = d5;
  _data_pins[2] = d6;
  _data_pins[3] = d7;

  _function_set = LCD_FUNCTIONSET | LCD_4BITMODE;
}

LiquidCrystal::LiquidCrystal(uint8_t rsPin, uint8_t rwPin, uint8_t enablePin, 
                              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                              uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _rs_pin = rsPin;
  _rw_pin = rwPin;
  _enable_pin = enablePin;

   _num_pins = 8;
  _data_pins = new uint8_t[_num_pins];
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3;
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7;

  _function_set = LCD_FUNCTIONSET | LCD_8BITMODE;
}

LiquidCrystal::LiquidCrystal(const LiquidCrystal &lcd)
{
  _rs_pin = lcd._rs_pin;
  _rw_pin = lcd._rw_pin;
  _enable_pin = lcd._enable_pin;

  _num_pins = lcd._num_pins;
  _data_pins = new char[_num_pins];
  for (int i=0; i < _num_pins; i++) {
    _data_pins[i] = lcd._data_pins[i];
  } 

  _function_set = lcd._function_set;
}

void LiquidCrystal::init(uint8_t mode, uint8_t font)
{
  // Set modes for Register Select, Read/Write, and Enable pins
  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);

  for (int i=0; i < _num_pins; i++) {
    pinMode(_data_pins[i], OUTPUT);
  }

  digitalWrite(_rs_pin, LOW);
  digitalWrite(_rw_pin, LOW); 

  delay(20);  // Wait for default initialization to complete

  if (_num_pins == 4) write_enable(_function_set >> 4);

  _function_set |= mode | font;

  write(_function_set, INSTRUCTION);
  displayPower(LCD_DISPLAYOFF, LCD_CURSOROFF, LCD_BLINKOFF);
  clearDisplay();
  setEntryMode(LCD_ENTRYINCREMENT, LCD_DISPLAYSTATIC);
}

unsigned int LiquidCrystal::print(char *str)
{
  unsigned int index = 0;

  while (str[index] != '\0') {
    uint8_t id = int(str[index]);
    write(id, DATA);
    index++;
  }

  return index;
}

/****************************
>> Protected member functions
****************************/
void LiquidCrystal::write(uint8_t val, uint8_t reg_sel) const
{
  // Ensure data pins are set to OUTPUT
  for (int i=0; i < _num_pins; i++) {
    pinMode(_data_pins[i], OUTPUT);
  }

  digitalWrite(_rw_pin, LOW);
  if (reg_sel == INSTRUCTION) digitalWrite(_rs_pin, LOW);
  else digitalWrite(_rs_pin, HIGH); 

  if (_num_pins == 8) {
    write_enable(val);
  } else {
    write_enable(val >> 4);
    write_enable(val);
  }

  // Execution time delay + cycle time 
  if ((val == LCD_CLEARDISPLAY) || (val == LCD_RETURNHOME)) delayMicroseconds(1520);
  else delayMicroseconds(37);
}

void LiquidCrystal::write_enable(uint8_t val) const
{
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);           // Fall time delay > 25ns
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);           // Pulse width + rise time delay > 165ns

  for (int i=0; i < _num_pins; i++) {
    digitalWrite(_data_pins[i], ((val >> i) & 0x01));
  }

  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(2);   // Cycle-time delay
}

uint8_t LiquidCrystal::read(uint8_t reg_sel) const
{
  uint8_t result = 0x00; 

  // Ensure data pins are set to INPUT
  for (int i=0; i < _num_pins; i++) {
    pinMode(_data_pins[i], INPUT);
  }

  digitalWrite(_rw_pin, HIGH);
  if (reg_sel == INSTRUCTION) digitalWrite(_rs_pin, LOW);
  else digitalWrite(_rs_pin, HIGH);

  if (_num_pins == 8) {
    result = read_enable();
  } else {
    result = (read_enable() << 4) & 0xF0;
    result ^= read_enable();
  }

  // Execution time delay
  if (reg_sel == DATA) delayMicroseconds(37);
  return result;
}

uint8_t LiquidCrystal::read_enable(void) const 
{
  uint8_t result = 0x00;

  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);           // Fall time delay > 25ns
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);           // Pulse width + rise time delay > 165ns

  for (int i=0; i < _num_pins; i++) {
    result ^= (digitalRead(_data_pins[i]) << i);
  }

  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(2);     // Cycle-time delay

  return result;
}