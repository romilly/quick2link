#include "Arduino.h"
#include "Microcontroller.h"
#include <Servo.h> 


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

void ArduinoController::attach(int pin) {
  servo.attach(pin);
}

void ArduinoController::servoPosition(int pos) {
  servo.write(pos);
}

void ArduinoController::delayMilliseconds(unsigned long millis) {
  ::delay(millis);
}

void ArduinoController::delayMicroseconds(unsigned long micros) {
  ::delayMicroseconds(micros);
}

