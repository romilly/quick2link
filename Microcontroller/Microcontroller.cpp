#include "Arduino.h"
#include "Microcontroller.h"

Microcontroller::Microcontroller() {
}

unsigned int Microcontroller::digitalRead(int pin) {
  return ::digitalRead(pin);
}

void Microcontroller::pinMode(int pin, int mode) {
  ::pinMode(pin, mode);
}

void Microcontroller::digitalWrite(int pin, int value) {
  ::digitalWrite(pin, value);
}

void Microcontroller::delayMilliseconds(unsigned long millis) {
  ::delay(millis);
}

void Microcontroller::delayMicroseconds(unsigned long micros) {
  ::delayMicroseconds(micros);
}

