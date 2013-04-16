/*

This class represents an Arduino or clone.

We will eventually define an interface so we can use a mock for testing,
and this class for deployment.

Romilly Cocking 19 march 2013
*/

#include <Servo.h>

#ifndef Microcontroller_h
#define Microcontroller_h

class Microcontroller {
 public:
  virtual ~Microcontroller() {};
  virtual void pinMode(int pin, int value) = 0;
  virtual unsigned int digitalRead(int pin) = 0;
  virtual void digitalWrite(int pin, int value) = 0;
  virtual unsigned int analogRead(int pin) = 0;
  virtual void attach(int pin) = 0;
  virtual void servoPosition(int pos) = 0;

  virtual void delayMilliseconds(unsigned long millis) = 0;
  virtual void delayMicroseconds(unsigned long micros) = 0;
};

class ArduinoController : public Microcontroller {
 public:
  virtual ~ArduinoController() {};
  void pinMode(int pin, int value);
  unsigned int digitalRead(int pin);
  void digitalWrite(int pin, int value);
  unsigned int analogRead(int pin);
  void attach(int pin);
  void servoPosition(int pos);
  
  void delayMilliseconds(unsigned long millis);
  void delayMicroseconds(unsigned long micros);
 private:
  Servo servo;
};


#endif
