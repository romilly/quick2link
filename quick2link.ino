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
unsigned long x = 0;
int y = 0;
int digitalPin = 13;
Microcontroller arduino;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(-1);
  arduino = Microcontroller();
  Serial.println(Welcome);
}

void loop() {
  char buf[64];
  if (txtRead(buf, 64)) {
    txtEval(buf);
  }
  delay(100);
}

boolean txtRead (char *p, byte n) {
  const int count = Serial.readBytesUntil('\n', p, 60);
  Serial.println(">>>>");
  p[count] = 0;
  return count > 0;
}

void txtEval (char *buf) {
  unsigned int k = 0; 
  char *loop;
  char ch;
  while ((ch = *buf++)) {
    switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      x = ch - '0';
      while (*buf >= '0' && *buf <= '9') {
        x = x*10 + (*buf++ - '0');
      }
      break;
    case 'p':
      Serial.print(x);
      break;
    case 'd':
      digitalPin = x;
      break;
    case 'i':
      pinMode(digitalPin, INPUT);
      x = arduino.digitalRead(digitalPin);
      break;
    case 'o':
      arduino.pinMode(digitalPin, OUTPUT);   
      arduino.digitalWrite(digitalPin, x%2);
      break;
    case 'm':
      delay(x);
      break;
    case 'u':
      delayMicroseconds(x);
      break;
    case '{':
      k = x;
      loop = buf;
      while ((ch = *buf++) && ch != '}') {
      }
    case '}':
      if (k) {
        k--;
        buf = loop;
      }
      break;
    case 'k':
      x = k;
      break;
    case '_':
      while ((ch = *buf++) && ch != '_') {
        Serial.print(ch);
      }
      Serial.print(ch);
      break;
    case ENQ:
    case '?':
      Serial.print(Name);
      break;
    case 's':
      x = arduino.analogRead(x);
      break;
    case 'A':
      arduino.servoAttach(x);
      break;
    case 'D':
      arduino.servoDetach();
      break;
    case 'W':
      arduino.servoWrite(y);
      break;
    case '-':
      y = -x;
      break; 
    case '+':
      y = x;  
    }
  }
  Serial.println();
}








