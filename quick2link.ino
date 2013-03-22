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

unsigned int x = 0;
int y = 0;
int d = 13;
Servo servo;
Microcontroller arduino;

void setup() {
  Serial.begin(38400);
  servo = Servo();
  arduino = Microcontroller();
  
}

void loop() {
  char buf[64];
  txtRead(buf, 64);
  txtEval(buf);
  delay(10);
}

void txtRead (char *p, byte n) {
  byte readCount = 0;
  while (readCount < (n-1)) {
    while (!Serial.available());
    char ch = Serial.read();
    if (ch == '\r' || ch == '\n') break;
    if (ch >= ' ' && ch <= '~') {
      *p++ = ch;
      readCount++;
    }
  }
  *p = 0;
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
      Serial.println(x);
      break;
    case 'd':
      d = x;
      break;
    case 'i':
      pinMode(d, INPUT);
      x = arduino.digitalRead(d);
      break;
    case 'o':
      arduino.pinMode(d, OUTPUT);   
      arduino.digitalWrite(d, x%2);
      break;
    case 'm':
      arduino.delay(x);
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
      Serial.println(ch);
      break;
    case ENQ:
    case '?':
      Serial.println("arduino");
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
}








