#include <Wire.h>   

const int OnboardLED = 13;
const int EventLED = 8;

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
  char x = Wire.read();    // receive byte as a character
  flashOnboardLED();
  do_command(x);      
}

void do_command(char x) {
  switch(x) {
    case '1': digitalWrite(EventLED, HIGH); break;
    case '0': digitalWrite(EventLED, LOW); break;
  }
}

void setup() {
  pinMode(OnboardLED, OUTPUT);
  pinMode(EventLED, OUTPUT);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
  flashForStartup();  
}

void loop() {
}
