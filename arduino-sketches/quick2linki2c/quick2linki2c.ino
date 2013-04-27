#include <Wire.h>   

const unsigned int BufferLength = 64;
const int OnboardLED = 13;
const int EventLED = 8;
const int SlaveAddress = 0x04;
const String Ok = "0";
const String Fail = "1";
const String Name = "arduino";

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

void receiveEvent(int howMany)
{
  for (int i = 0; i < howMany; i++) {
    do_command(Wire.read());      
  }
}

String response;

void respond() {
  char response_buffer[BUFFER_LENGTH];
  response_buffer[0] = response.length();
  response.toCharArray((response_buffer + 1), BufferLength);
  Wire.write(response_buffer);
  response = "";
}

void do_command(char c) {
  switch(c) {
    case '1': digitalWrite(EventLED, HIGH); break;
    case '0': digitalWrite(EventLED, LOW); break;
    case 'h': response = Name; break;
  }
}

void setup() {
  pinMode(OnboardLED, OUTPUT);
  pinMode(EventLED, OUTPUT);
  Wire.begin(SlaveAddress);  // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
  Wire.onRequest(respond);
  flashForStartup();  
}

void loop() {
}
