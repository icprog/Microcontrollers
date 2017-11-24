#include <SoftwareSerial.h>

char c, d;
//definindo pinos
const int ponteH01DIR = 10, ponteH01ESQ = 9,
          ponteH02DIR = 5,  ponteH02ESQ = 6,
          ponteH03DIR = 4,  ponteH03ESQ = 3,
          pwm = 100;

bool a = 0, b = 0;

SoftwareSerial mySerial(7, 8);

void zero()
{
  digitalWrite(ponteH01DIR, LOW);
  digitalWrite(ponteH02DIR, LOW);
  digitalWrite(ponteH01ESQ, LOW);
  digitalWrite(ponteH02ESQ, LOW);
}

void up()
{
  zero();
  digitalWrite(ponteH01DIR, HIGH);
  digitalWrite(ponteH02DIR, HIGH);
}
void down()
{
  zero();
  digitalWrite(ponteH01ESQ, HIGH);
  digitalWrite(ponteH02ESQ, HIGH);
}
void left()
{
  zero();
  analogWrite(ponteH01ESQ, pwm);
  analogWrite(ponteH02DIR, pwm);
}
void righ()
{
  zero();
  analogWrite(ponteH01DIR, pwm);
  analogWrite(ponteH02ESQ, pwm);
}
void weaponX()
{ 
    if(a == 0 && b == 0)
    {
      digitalWrite(ponteH03ESQ,LOW);
      digitalWrite(ponteH03DIR,HIGH);
      a = 1;
    }
}
void weaponXoff()
{ 
    digitalWrite(ponteH03ESQ,LOW);
    digitalWrite(ponteH03DIR,LOW);
    a = 0;
    delay(30);
}
void weaponSquare()
{
    if(a == 0 && b == 0)
    {
      digitalWrite(ponteH03DIR,LOW);
      digitalWrite(ponteH03ESQ,HIGH);
      b = 1;
    }
}
void weaponSquareoff()
{
    digitalWrite(ponteH03DIR,LOW);
    digitalWrite(ponteH03ESQ,LOW);
    b = 0;
    delay(30);
}

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ponteH01DIR, OUTPUT);
  pinMode(ponteH01ESQ, OUTPUT);
  pinMode(ponteH02DIR, OUTPUT);
  pinMode(ponteH02ESQ, OUTPUT);
  pinMode(ponteH03DIR, OUTPUT);
  pinMode(ponteH03ESQ, OUTPUT);
  d = 'S';
  c = 'S';
  
}


void loop()
{
  while (mySerial.available())
  {
    d = c;
    c = mySerial.read();
    if (c != d)
    {
      zero();
      Serial.println("................TROCOU!...................");
      delay(30);
    }
//    Serial.print(a);
//    Serial.print(" , ");
    Serial.println(c);
    
      switch(c)
      {
        case 'F':
          up();
          break;
        case 'B':
          down();
          break;
        case 'L':
          left();
          break;
        case 'R':
          righ();
          break;
        case 'S':
          zero();
          break;
        case 'W':
          weaponX();
          break; 
        case 'w':
          weaponXoff();
          break;
        case 'U':
          weaponSquare();
          break;
        case 'u':
          weaponSquareoff();
          break;
        default:
          zero();
          break;
      }
  }
}

