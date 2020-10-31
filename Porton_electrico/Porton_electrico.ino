#include <SoftwareSerial.h>   //Se puede emular mas de un puerto serial
SoftwareSerial BTSerial(10, 11);	 // RX | TX Poner los pines que uses
char data = 0;
int arranque = 0;
int enclavamiento = 0;
int paro = 0;
int estado = 0;
int reversible = 0;
int areversible = 0;
int restado = 0;
int renclavamiento = 0;
int w = 0;
int Led = 12; //modificar para incluir en la variable

void setup () {

  BTSerial.begin(9600);//Inicializar comunicacion

 int PinArranque = 2;
  pinMode(PinArranque, INPUT);
  arranque = digitalRead(PinArranque);

  int PinParo = 3;
  pinMode(PinParo, INPUT);
  paro = digitalRead(PinParo);
  
 int Pinreversible = 4;
  pinMode(Pinreversible, INPUT);
  paro = digitalRead(Pinreversible);
  
 int Pinw = 5;
  pinMode(Pinw, INPUT);
  paro = digitalRead(Pinw);

 
 
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite (9, LOW);


  pinMode(Led, OUTPUT);

  delay (10);
}
void loop () {



  while (BTSerial.available()) {
    char data = (char)BTSerial.read();
    if ( data == 'H')
    { digitalWrite(Led, !digitalRead(Led));
    }
  }

  paro = digitalRead(3);


  if (paro == HIGH) {
    digitalWrite (8, HIGH);
    digitalWrite (7, HIGH);
    restado = 0;
    estado = 0;
  } delay (8);
  reversible = digitalRead(4);
  arranque = digitalRead(2);
  paro = digitalRead(3);
  w = digitalRead(5);

  enclavamiento = estado;
  if (arranque == HIGH and w == HIGH) {
    estado = 1;
    restado = 0;
  }

  if (arranque == HIGH and Led == HIGH) { //Led

    estado = 1;
    restado = 0;
  }

  if (estado == HIGH) {
    digitalWrite (7, LOW);
    digitalWrite (8, HIGH);

  }

  else {

    digitalWrite (7, HIGH);

  }
  if (paro == HIGH) {
    estado = 0;
    restado = 0;
    digitalWrite (8, HIGH);
    digitalWrite (7, HIGH);
  }
  renclavamiento = restado;
  if (reversible == HIGH and w == LOW ) {
    restado = 1;
    estado = 0;
  }

  if (restado == HIGH) {
    digitalWrite (8, LOW);
    digitalWrite (7, HIGH);
  }

  else {

    digitalWrite (8, HIGH);

  }
  if (paro == HIGH) {
    digitalWrite (8, HIGH);
    digitalWrite (7, HIGH);
    restado = 0;
    estado = 0;

  }
  if (reversible == HIGH and w == HIGH) {
    estado = 0;
    restado = 0;
  }

  if (arranque == HIGH and w == LOW) {
    estado = 0;
    restado = 0;
  }
}
