#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
static unsigned int sw1 = 2;
static unsigned int paro = 3;
static unsigned int sw2 = 4;
static unsigned int externa = 5;
static unsigned int giro1 = 7 ;
static unsigned int giro2 = 8 ;
static unsigned int proteccion =  9;
static unsigned int selec = 6 ;
static unsigned int selec1 = 12 ;
int Selec1 = 0;
int Selec = 0;
int serial = 0;
int Paro = 0;
int Sw1 = 0;
int Sw2 = 0;
int Externa = 0;
int Giro1 = 0;
int Giro2 = 0;
int Proteccion = 0;
void setup() {
  BTSerial.begin(9600);//Inicializar comunicacion
 pinMode(selec1, INPUT); 
  pinMode(selec, INPUT);
  pinMode(paro, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(externa, INPUT);
  pinMode(giro1, OUTPUT);
  pinMode(proteccion, OUTPUT);
  pinMode(giro2, OUTPUT);
  digitalWrite (proteccion, LOW);
}
void loop() {
  Selec1 = digitalRead(selec1);
  Selec = digitalRead(selec);
  Paro = digitalRead(paro);
  Sw1 = digitalRead(sw1);
  Sw2 = digitalRead(sw2);
  Externa = digitalRead(externa);
  if (Paro == 1)
  {
    digitalWrite (proteccion, HIGH);
  } delay (10);
  
 while (BTSerial.available()) {    //pregunto sobre serial
    char data = (char)BTSerial.read();
   if ( data == 'H')
   { digitalWrite(serial, !digitalRead(serial));
   }
  }
  if
  (!Selec1 and ((Selec and !serial and !Sw1) or ( !Selec and !Externa and !Sw1)))
  //(!Externa and !Sw1) 
  {
    Giro1 = 0;
  }
  else {
    Giro1 = 1;
  }
  if (!Selec1 and ((Selec and serial and !Sw2) or (!Selec and Externa and !Sw2)))
  //( Externa and !Sw2 )  
  {
    Giro2 = 0;
  } 
  else {
    Giro2 = 1;
  }
 
if (Selec1 and Sw1)

{
  Giro1 =0;
  }
if (Selec1 and Sw2)

{
  Giro2 =0;
  }

  digitalWrite (giro2, Giro2);
  digitalWrite(giro1, Giro1);

   
}
