#include "TempHumid.h"

TempHumid::TempHumid(uint8_t dataPin) 
{
  _data_pin = dataPin;
  for (int i=0; i < 5; i++) _data[i] = 0x00;

  // Wait 1s to power on if initialized during setup() 
  if (millis() < 1000) delay(1000);                  
}

void TempHumid::readData(void)
{
  unsigned long timer;
  for (int i=0; i < 5; i++) _data[i] = 0x00;

  // Send start signal
  pinMode(_data_pin, OUTPUT);
  digitalWrite(_data_pin, LOW);
  delay(18);
  digitalWrite(_data_pin, HIGH);

  // Receive response signal
  pinMode(_data_pin, INPUT);
  while (digitalRead(_data_pin) != LOW);
  delayMicroseconds(80);
  while (digitalRead(_data_pin) != HIGH);
  delayMicroseconds(80);

  while(digitalRead(_data_pin) == HIGH);
  for (int i=0; i < 40; i++) {
    while(digitalRead(_data_pin) == LOW);
    timer = micros();
    while(digitalRead(_data_pin) == HIGH);
    timer = micros() - timer;
    if (timer > 30) _data[int(i/8)] |= (0x80 >> (i%8));
  }

  Serial.print("Received Data: ");
  for (int i=0; i < 5; i++) {
    Serial.print(_data[i]);
    Serial.print(" ");
  }
  Serial.println();
}