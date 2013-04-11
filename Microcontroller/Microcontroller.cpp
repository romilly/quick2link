#include "Arduino.h"
#include "Microcontroller.h"

void ArduinoController::pinMode(int pin, int mode) {
  ::pinMode(pin, mode);
}

unsigned int ArduinoController::digitalRead(int pin) {
  return ::digitalRead(pin);
}

void ArduinoController::digitalWrite(int pin, int value) {
  ::digitalWrite(pin, value);
}

unsigned int ArduinoController::analogRead(int pin) {
  return ::analogRead(pin);
}

void ArduinoController::delayMilliseconds(unsigned long millis) {
  ::delay(millis);
}

void ArduinoController::delayMicroseconds(unsigned long micros) {
  ::delayMicroseconds(micros);
}

