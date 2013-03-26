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
#define BUFFER_LENGTH 64

const String Name = "arduino";
const String Welcome = "up";
const unsigned long Forever = 4294967295;
Microcontroller arduino;

char bufferIn[BUFFER_LENGTH];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(Forever);
  arduino = Microcontroller();
  Serial.println(Welcome);
}

void loop() {
  if (txtRead()) {
    txtEval();
    delay(100);
  }
}

boolean txtRead () {
  const int readCount =  Serial.readBytesUntil('\n', bufferIn, BUFFER_LENGTH - 1);
  bufferIn[readCount] = 0;
  return readCount > 0;
}

void txtEval () {
  char *in = bufferIn;
  String result;  
  result += '0';
  
  char ch;
  while ((ch = *in++)) {
    switch (ch) {
    case '?':
      result += Name;
      break;
    default: 
      Serial.println("1");
      return;
    }
  }
  Serial.println(result);
}








