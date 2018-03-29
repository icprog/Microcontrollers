/*  Programa para testar ponte H
 *  Autor: Will Douglas
 *  
 *  Como usar: 
 *  
 *  Usar pinos 2, 4 e GND do arduino como sentido 1, 2 e terra, reespectivamente.
 *  Abrir monitor serial a 9600 de velocidade (ctrl shift M)
 *  enviar o caractere 'a' como sentido 1
 *  enviar o caractere 'b' como sentido 2
 *  enviar o caractere 's' para parar
 */

//GPIO do arduino
const unsigned int pin1 = 2;
const unsigned int pin2 = 4;


void setup() {
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}


void loop() {
  while(Serial.available()) {
    char a = (char)Serial.read();
    switch(a) {
      case 'a':
        Serial.println("Sentido 1");
        digitalWrite(pin1, LOW);
        delay(50);
        digitalWrite(pin2, HIGH);
        break;
      case 'd':
        Serial.println("Sentido pin1");
        digitalWrite(pin2, LOW);
        delay(50);
        digitalWrite(pin1, HIGH);
        break;
      case 's':
        Serial.println("Parado");
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        break;
      default:
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        break;
    }
  }
}
