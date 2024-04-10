#ifndef LIQUIDCRYSTAL_H
#define LIQUIDCRYSTAL_H

#include <inttypes.h>
#include "Arduino.h"

// Instruction Patterns
#define LCD_CLEARDISPLAY 	0x01
#define LCD_RETURNHOME 		0x02
#define LCD_ENTRYMODESET 	0x04
#define LCD_DISPLAYPOWER	0x08 
#define LCD_DISPLAYSET	  0x10
#define LCD_FUNCTIONSET		0x20
#define LCD_SETCGRAMADDR	0x40
#define LCD_SETDDRAMADDR	0x80

// Modes of operation
#define LCD_4BITMODE		0x00
#define LCD_8BITMODE		0x10
#define LCD_1LINEMODE		0x00		
#define LCD_2LINEMODE		0x08
#define LCD_5x8FONT			0x00
#define LCD_5x10FONT		0x04		// Can only be used in 1-line mode

// LCD instruction parameters
#define LCD_ENTRYINCREMENT    0x02
#define LCD_ENTRYDECREMENT    0x00
#define LCD_DISPLAYDYNAMIC    0x01
#define LCD_DISPLAYSTATIC     0x00
#define LCD_DISPLAYON         0x04
#define LCD_DISPLAYOFF        0x00
#define LCD_CURSORON          0x02
#define LCD_CURSOROFF         0x00
#define LCD_BLINKON           0x01
#define LCD_BLINKOFF          0x00
#define LCD_DISPLAYSHIFT      0x08
#define LCD_SHIFTRIGHT        0x04
#define LCD_SHIFTLEFT         0x00

// Register selection (_rs_pin) states
#define INSTRUCTION   0x00
#define DATA          0x01

class LiquidCrystal 
{
public:
	LiquidCrystal(uint8_t rsPin, uint8_t rwPin, uint8_t enablePin, 
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  LiquidCrystal(uint8_t rsPin, uint8_t rwPin, uint8_t enablePin, 
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  virtual ~LiquidCrystal() { delete [] _data_pins; }

  LiquidCrystal(const LiquidCrystal &lcd); 
  // overload the '=' operator in this class and all derived classes (?)

  void init(uint8_t mode, uint8_t font=LCD_5x8FONT);
  void clearDisplay(void) const { write(LCD_CLEARDISPLAY, INSTRUCTION); }
  void returnHome(void) const { write(LCD_RETURNHOME, INSTRUCTION); }

  /*********************************************************************************************************
  *         shift_dir        |        dsp_shift       | Description
  * --------------------------------------------------------------------------------------------------------
  *   LCD_ENTRYINCREMENT     |   LCD_DISPLAYSTATIC    | shift address right following read/write operations 
  *   LCD_ENTRYDECREMENT     |   LCD_DISPLAYSTATIC    | shift address left following read/write operations
  *   LCD_ENTRYINCREMENT     |   LCD_DISPLAYDYNAMIC   | shift entire display right following read/write operations 
  *   LCD_ENTRYDECREMENT     |   LCD_DISPLAYDYNAMIC   | shift entire display left following read/write operations
  *********************************************************************************************************/
  void setEntryMode(uint8_t shift_dir, uint8_t dsp_shift) const
  { write((LCD_ENTRYMODESET | shift_dir | dsp_shift), INSTRUCTION); }

  /*********************************************
  * dsp_pwr   : LCD_DISPLAYON | LCD_DISPLAYOFF
  * csr_pwr   : LCD_CURSORON  | LCD_CURSOROFF
  * csr_blink : LCD_BLINKON   | LCD_BLINKOFF 
  **********************************************/
  void displayPower(uint8_t dsp_pwr, uint8_t csr_pwr, uint8_t csr_blink) const
  { write((LCD_DISPLAYPOWER | dsp_pwr | csr_pwr | csr_blink), INSTRUCTION); }
  
  /************************************************************************************
  *       dsp_shift       |     shift_dir      |              Description
  *------------------------------------------------------------------------------------
  *   LCD_DISPLAYSTATIC   |   LCD_SHIFTLEFT    | shift cursor left
  *   LCD_DISPLAYSTATIC   |   LCD_SHIFTRIGHT   | shift cursor right
  *   LCD_DISPLAYSHIFT    |   LCD_SHIFTLEFT    | shift display left (cursor follows) 
  *   LCD_DISPLAYSHIFT    |   LCD_SHIFTRIGHT   | shift display right (cursor follows)
  ************************************************************************************/
  void displayShift(uint8_t dsp_shift, uint8_t shift_dir) const
  { write((LCD_DISPLAYSET | dsp_shift | shift_dir), INSTRUCTION); }

  bool isBusy(void) const { return ((read(INSTRUCTION) >> 7) & 0x01); }
  uint8_t getAddrCntr(void) const { return (read(INSTRUCTION) & 0x7F); }

  // !!! Input strings should explicitly be NULL terminated ('\0') !!!
  unsigned int print(char *str);

protected:
  void write(uint8_t val, uint8_t reg_sel) const;
  void write_enable(uint8_t val) const;

  uint8_t read(uint8_t reg_sel) const;
  uint8_t read_enable(void) const;

  // Address range in 1-line mode:  0x00 - 0x4F
  // Address range in 2-line mode:  0x00 - 0x27 (line one)
  //                                0x40 - 0x67 (line two)
  void setDDRAMAddr(uint8_t addr) const { write((LCD_SETDDRAMADDR | addr), INSTRUCTION); }
  void setCGRAMAddr(uint8_t addr) const { write((LCD_SETCGRAMADDR | addr), INSTRUCTION); }

private:
  uint8_t _rs_pin;
  uint8_t _rw_pin;
  uint8_t _enable_pin;

  uint8_t _num_pins;
  uint8_t *_data_pins; 

  uint8_t _function_set;
};

#endif
