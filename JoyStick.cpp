#include "JoyStick.h"

JoyStick::JoyStick(uint8_t xPin, uint8_t yPin, uint8_t swPin)
{
  _x_pin = xPin;
  _y_pin = yPin;
  _sw_pin = swPin;

  pinMode(_sw_pin, INPUT);
}

void JoyStick::listen(void) 
{
  uint8_t swState = LOW; 
  int xState, yState;

  while (true) {
    swState = digitalRead(_sw_pin);
    if (swState != SW_REST) {
      Serial.println("Button pressed");
      delay(250);
    }

    xState = analogRead(_x_pin);
    if (xState < (XY_REST - 100)) {
      Serial.println("Negative X-move");
      delay(500);
    } else if (xState > (XY_REST + 100)) {
      Serial.println("Positive X-move");
      delay(500);
    }

    yState = analogRead(_y_pin);
    if (yState < (XY_REST - 100)) {
      Serial.println("Negative Y-move");
      delay(500);
    } else if (yState > (XY_REST + 100)) {
      Serial.println("Positive Y-move");
      delay(500);
    }
  }
}