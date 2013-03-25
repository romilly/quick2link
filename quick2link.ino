#include <Microcontroller.h>

/*
Experimental code for distributed embedded architectures.

This Arduino code is inspired by and based on Ward Cunningham's
Txtzyme https://github.com/WardCunningham/Txtzyme

See LICENSE.md in this directory for licensing information
*/
#include "Microcontroller.h"
#include <Servo.h>
#define ENQ 0x05

const String Name = "arduino";
const String Welcome = "up";
const unsigned long Forever = 4294967295;
unsigned long x = 0;
int y = 0;
int digitalPin = 13;
Microcontroller arduino;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(Forever);
  arduino = Microcontroller();
  Serial.println(Welcome);
}

void loop() {
  char buf[64];
  if (txtRead(buf, 64)) {
    txtEval(buf);
    delay(100);
  }
}

boolean txtRead (char *p, byte n) {
  return Serial.readBytesUntil('\n', p, 60) > 0;
}

void txtEval (char *buf) {
  char ch;
  while ((ch = *buf++)) {
    switch (ch) {
    case '?':
      Serial.print(Name);
      break;
    }
  }
  Serial.println();
}








