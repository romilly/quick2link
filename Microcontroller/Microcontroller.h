/*

This class represents an Arduino or clone.

We will eventually define an interface so we can use a mock for testing,
and this class for deployment.

Romilly Cocking 19 march 2013
*/

#ifndef Microcontroller_h
#define Microcontroller_h

#include "Arduino.h"
#include "Servo.h"

class Microcontroller {
 public:
  Microcontroller();
  void pinMode(int pin, int value);
  unsigned int digitalRead(int pin);
  void digitalWrite(int pin, int value);
  
  void delayMilliseconds(unsigned long millis);
  void delayMicroseconds(unsigned long micros);
};

#endif
