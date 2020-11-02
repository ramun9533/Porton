#include <SoftwareSerial.h>   //Se puede emular mas de un puerto serial
SoftwareSerial BTSerial(10, 11);   // RX | TX Poner los pines que uses
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
static unsigned int  Led = 12; //modificar para incluir en la variable
static unsigned int PinArranque = 2;
static unsigned int PinParo = 3;
static unsigned int Pinreversible = 4;
static unsigned int Pinw = 5;
static unsigned int Pinestado = 7;
static unsigned int Pinrestado = 8;
static unsigned int Pinprot = 9;
void setup () {

  BTSerial.begin(9600);//Inicializar comunicacion
  digitalWrite (Pinprot, HIGH);
  pinMode(PinArranque, INPUT);
  pinMode(PinParo, INPUT);
  pinMode(Pinreversible, INPUT);
  pinMode(Pinw, INPUT);
  pinMode(Pinprot, OUTPUT);
  pinMode(Led, OUTPUT);
  delay (1000);
  digitalWrite (Pinprot, LOW);
  pinMode(Pinestado, OUTPUT);
  pinMode(Pinrestado, OUTPUT);
}
void loop () {
  arranque = digitalRead(PinArranque);
  paro = digitalRead(PinParo);
  reversible = digitalRead(Pinreversible);
  w = digitalRead(Pinw);

  while (BTSerial.available()) {
    char data = (char)BTSerial.read();
    if ( data == 'H')
    { digitalWrite(Led, !digitalRead(Led));
    }
  }

  if (paro == HIGH) {
    digitalWrite (Pinrestado, HIGH);
    digitalWrite (Pinestado, HIGH);
    restado = 0;
    estado = 0;
  } delay (8);

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
    digitalWrite (Pinestado, LOW);
    digitalWrite (Pinrestado, HIGH);
    delay (10000);
    estado = 0;
  }

  else {

    digitalWrite (Pinestado, HIGH);

  }
  digitalWrite (Pinestado, HIGH);
  digitalWrite (Pinrestado, HIGH);

  if (paro == HIGH) {
    estado = 0;
    restado = 0;
    digitalWrite (Pinrestado, HIGH);
    digitalWrite (Pinestado, HIGH);
  }
  renclavamiento = restado;
  if (reversible == HIGH and w == LOW ) {
    restado = 1;
    estado = 0;
  }

  if (restado == HIGH) {
    digitalWrite (Pinrestado, LOW);
    digitalWrite (Pinestado, HIGH);
    delay (10000);
    restado = 0;
  }

  else {

    digitalWrite (Pinrestado, HIGH);

  }

  digitalWrite (Pinestado, HIGH);
  digitalWrite (Pinrestado, HIGH);

  if (paro == HIGH) {
    digitalWrite (Pinrestado, HIGH);
    digitalWrite (Pinestado, HIGH);
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
