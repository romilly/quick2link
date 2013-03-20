#include "Arduino.h"
#include "Microcontroller.h"
#include "Servo.h"

Microcontroller::Microcontroller() {
	servo = Servo();
}

unsigned int Microcontroller::digitalRead(int pin) {
	return digitalRead(pin);
}

void Microcontroller::pinMode(int pin, int mode) {
	pinMode(pin, mode);
}

void Microcontroller::digitalWrite(int pin, int value) {
	digitalWrite(pin, value);
}

unsigned int Microcontroller::analogRead(int pin) {
	return analogRead(pin);
}

void Microcontroller::servoAttach(int pin) {
        servo.attach(pin);
}

void Microcontroller::servoDetach() {
        servo.detach();
}

void Microcontroller::servoWrite(int angle) {
        servo.write(angle);
}

void Microcontroller::delay(int millis) {
        delay(millis);
}



