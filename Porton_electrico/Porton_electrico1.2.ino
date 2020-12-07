#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
static unsigned int sw1 = 9;
static unsigned int sw2 = 10;
static unsigned int externa = 11;
static unsigned int giro1 = 2 ;
static unsigned int giro2 = 4 ;
static unsigned int proteccion =  3;
int serial = 0;
int Sw1 = 0;
int Sw2 = 0;
int Externa = 0;
int Giro1 = 0;
int Giro2 = 0;
int Proteccion = 0;
void setup() {
  BTSerial.begin(9600);//Inicializar comunicacion
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(externa, INPUT);
  pinMode(giro1, OUTPUT);
  pinMode(proteccion, OUTPUT);
  pinMode(giro2, OUTPUT);
}
void loop() {
  digitalWrite (giro2, Giro2);
  digitalWrite(giro1, Giro1);
  Sw1 = digitalRead(sw1);
  Sw2 = digitalRead(sw2);
  Externa = digitalRead(externa);
  while (BTSerial.available()) {    //pregunto sobre el dato del serial
    char data = (char)BTSerial.read();
    if ( data == 'H')
    { digitalWrite(serial, !digitalRead(serial));
    }
  }
  if
  ((!serial and !Sw1) or (!Externa and !Sw1))
  {
    Giro1 = 1;
  }
  else {
    Giro1 = 0;
  }
  if
  ((serial and !Sw2) or (!Externa and !Sw2))
  {
    Giro2 = 1;
  }
  else {
    Giro2 = 0;
  }
}
