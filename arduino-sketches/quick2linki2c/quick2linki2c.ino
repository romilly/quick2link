#include <Servo.h>
#include <Microcontroller.h>
#include <Wire.h>   

const unsigned int BufferLength = 64;
const unsigned int OnboardLED = 13;
const int SlaveAddress = 0x04;
const String Ok = "0";
const String Fail = "1";
const unsigned long Forever = 4294967295;
const String Name = "arduino";

ArduinoController anArduino;

void flashOnboardLED() {
  digitalWrite(OnboardLED, HIGH);
  delay(800);
  digitalWrite(OnboardLED, LOW);
}

void flashForStartup() {
  flashOnboardLED();
  delay(200);
  flashOnboardLED();
}

void setup() {
  pinMode(OnboardLED, OUTPUT);
  Wire.begin(SlaveAddress);
  Wire.setTimeout(Forever);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(respond);
  flashForStartup();  
}

unsigned int as_digit(char c) { return c - '0'; }
boolean is_a_digit(char c) { return '0' <= c && c <= '9'; }

void receiveEvent(int howMany) {
  char buffer[howMany + 1];
  const unsigned int readCount = Wire.readBytes(buffer, howMany);
  buffer[readCount] = 0;
  interpret(buffer);
}

String response = "";

void respond() {
  char response_buffer[BUFFER_LENGTH];
  response_buffer[0] = response.length();
  response.toCharArray((response_buffer + 1), BufferLength);
  Wire.write(response_buffer);
  response = "";
}

void interpret(const char *request) {
  unsigned int x = 0;
  
  char ch;
  while ((ch = *request++)) {
    switch(ch) {
      case ' ': /* ignore */ break;
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
        while (is_a_digit(*request)) {
          x = x*10 + as_digit(*request++);
        }
        break;
      case 'h': response = Name; break;
      case '?': 
        response = "x= "; 
        response += x; 
        break;
    }
  }
}


void loop() {
}
