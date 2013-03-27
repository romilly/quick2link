#include "Arduino.h"
#include "Microcontroller.h"

unsigned int ArduinoController::digitalRead(int pin) {
  return ::digitalRead(pin);
}

void ArduinoController::pinMode(int pin, int mode) {
  ::pinMode(pin, mode);
}

void ArduinoController::digitalWrite(int pin, int value) {
  ::digitalWrite(pin, value);
}

void ArduinoController::delayMilliseconds(unsigned long millis) {
  ::delay(millis);
}

void ArduinoController::delayMicroseconds(unsigned long micros) {
  ::delayMicroseconds(micros);
}

