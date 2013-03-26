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

const unsigned int DefaultDigitalPin = 13;
const String Ok = "0";
const String Fail = "1";
const String Name = "arduino";
const String Welcome = "up";
const unsigned long Forever = 4294967295;

Microcontroller arduino;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(Forever);
  arduino = Microcontroller();
  Serial.println(Welcome);
}

void loop() {
  char bufferIn[BUFFER_LENGTH];
  if (txtRead(bufferIn)) {
    txtEval(bufferIn);
    delay(100);
  }
}

boolean txtRead (char *bufferIn) {
  const int readCount =  Serial.readBytesUntil('\n', bufferIn, BUFFER_LENGTH - 1);
  bufferIn[readCount] = 0;
  return readCount > 0;
}


void txtEval (char *bufferIn) {
  Serial.println(interpretBuffer(bufferIn));
}

boolean is_a_digit(char c) { return '0' <= c && c <= '9'; }
unsigned int as_digit(char c) { return c - '0'; }
String echo(boolean echoed, String echoString) { return echoed ? ">" + echoString : "";  }

String interpretBuffer(char *in) {
  unsigned int digitalPin = DefaultDigitalPin;
  unsigned int x = 0;
  boolean echoed = false;
  String result = Ok;
  String echoString;
  
  char ch;
  while ((ch = *in++)) {
    echoString += ch;
    switch (ch) {
    case '?':
      result += Name;
      break;
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
      x = as_digit(ch);
      while (is_a_digit(*in)) {
        echoString += *in;
        x = x*10 + as_digit(*in++);
      }
      break;
    case 'd':
      digitalPin = x;
      break;
    case 'e':
      echoed = ! echoed;
      break;
    case 'i':
      pinMode(digitalPin, INPUT); 
      x = arduino.digitalRead(digitalPin);
      break;
    case 'o':
      arduino.pinMode(digitalPin, OUTPUT);   
      arduino.digitalWrite(digitalPin, x%2);
      break;
    case 'p':
      result += x;
      break;    
    default: 
      return Fail  + ch + echo(echoed, echoString);
    }
  }
  return result + echo(echoed, echoString);
}









