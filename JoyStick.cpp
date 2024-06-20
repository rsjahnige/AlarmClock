#include "JoyStick.h"

JoyStick::JoyStick(uint8_t xPin, uint8_t yPin, uint8_t swPin)
{
  _x_pin = xPin;
  _y_pin = yPin;
  _sw_pin = swPin;

  pinMode(_sw_pin, INPUT);
  digitalWrite(_sw_pin, HIGH);
}

uint8_t JoyStick::listen(void) 
{
  uint8_t swState; 
  int xState, yState;
  unsigned long counter;
  unsigned long timer = millis();
  uint8_t result = 0;

  // !!! delay() calls are required to prevent the same action  !!!
  // !!! from being executed twice in rapid succession          !!!
  do {
    swState = digitalRead(_sw_pin);
    if (swState != SW_REST) {
      counter = millis();
      while (swState != SW_REST) swState = digitalRead(_sw_pin);
      counter = millis() - counter;
      if (counter > 750) {              // Switch hold
        result = JS_HOLD;
      } else {                          // Switch pressed
        result = JS_PRESS;
      }
      delay(250);
      break;
    }

    xState = analogRead(_x_pin);
    if (xState < (XY_REST - 100)) {       // Negative x-move
      result = JS_LEFT;
      delay(250);
      break;
    } else if (xState > (XY_REST + 100)) {    // Positive x-move
      result = JS_RIGHT;
      delay(250);
      break;
    }

    yState = analogRead(_y_pin);
    if (yState < (XY_REST - 100)) {           // Positive y-move
      result = JS_UP;
      delay(250);
      break;
    } else if (yState > (XY_REST + 100)) {    // Negative y-move
      result = JS_DOWN;
      delay(250);
      break;
    }

    timer = millis() - timer;
  } while (timer < 1000);

  return result;
}
