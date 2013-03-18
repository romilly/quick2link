
#include <Servo.h> 
#define ENQ 0x05

unsigned int x = 0;
int y = 0;
int d = 13;
Servo servo;

void setup() {
  Serial.begin(38400);
  servo = Servo();
  
}

void loop() {
  char buf[64];
  txtRead(buf, 64);
  txtEval(buf);
  delay(10);
}

void txtRead (char *p, byte n) {
  byte i = 0;
  while (i < (n-1)) {
    while (!Serial.available());
    char ch = Serial.read();
    if (ch == '\r' || ch == '\n') break;
    if (ch >= ' ' && ch <= '~') {
      *p++ = ch;
      i++;
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
      x = digitalRead(d);
      break;
    case 'o':
      pinMode(d, OUTPUT);   
      digitalWrite(d, x%2);
      break;
    case 'm':
      delay(x);
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
      Serial.println();
      break;
    case ENQ:
    case '?':
      Serial.println("arduino");
      break;
    case 's':
      x = analogRead(x);
      break;
    case 'A':
      servo.attach(x);
      break;
    case 'D':
      servo.detach();
      break;
    case 'W':
      servo.write(x);
      break;
    case '-':
      y = -x;
      break; 
    case '+':
      y = x;  
    }
  }
}








