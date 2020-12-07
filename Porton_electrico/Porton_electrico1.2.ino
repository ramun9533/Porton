<<<<<<< HEAD
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
static unsigned int paro = 3;
static unsigned int sw1 = 2;
static unsigned int sw2 = 4;
static unsigned int externa = 5;
static unsigned int giro1 = 7 ;
static unsigned int giro2 = 8 ;
static unsigned int proteccion =  9;
int serial = 0;
int Sw1 = 0;
int Sw2 = 0;
int Externa = 0;
int Paro = 0;
int Giro1 = 0;
int Giro2 = 0;
int Proteccion = 0;
void setup() {
=======
//Este proyecto pretende sustituir la tarjeta electronica de un porton electrico, poderlo abrir por via bluetooth o manual a traves de botonera o por medio de radio control e incluso Wifi.


#include <SoftwareSerial.h>                                //Se puede emular mas de un puerto serial
SoftwareSerial BTSerial(10, 11);                          // RX | TX los pines que a usar
//char data = 0;                                           // para guardar dato recibido del bluetooth
int arranque = 0;                                       // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "A"
int enclavamiento = 0;                                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "A"
int paro = 0;
int pasoAnterior = 0;
int estado = 0;
int reversible = 0;                                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int areversible = 0;                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int restado = 0;
int restadoAnterior = 1;
// esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int renclavamiento = 0;            // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int EstadoExterno = 1;                        //entrada retro de serial y otra
boolean EstadoSalida = false;

//static unsigned int  serial = 12; //modificar para incluir en la variable
static unsigned int PinArranque = 2; //configurar entradas digitales
static unsigned int PinParo = 3;  //configurar entradas digitales
static unsigned int Pinreversible = 4;  //configurar entradas digitales
static unsigned int PinExterna = 5;  //configurar entradas digitales
static unsigned int Pinestado = 7; //configurar entradas digitales
static unsigned int Pinrestado = 8; //configurar entradas digitales
static unsigned int Pinprot = 9; //configurar entradas digitales
>>>>>>> bd70cdc5782383e0311dc1a65d84998635a0d4b8

void setup () {
  BTSerial.begin(9600);//Inicializar comunicacion
<<<<<<< HEAD
  pinMode(paro, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(externa, INPUT);
  pinMode(giro1, OUTPUT);
  pinMode(proteccion, OUTPUT);
  pinMode(giro2, OUTPUT);
}

void loop() {
  Paro = digitalRead(paro);
  Sw1 = digitalRead(sw1);
  Sw2 = digitalRead(sw2);
  Externa = digitalRead(externa);

  if (Paro == 1)
  {
    Giro1 = 1;
    Giro1 = 1;
  }

=======
  pinMode(PinArranque, INPUT);
  pinMode(PinParo, INPUT);
  pinMode(Pinreversible, INPUT);
  pinMode(PinExterna, INPUT); //variable que se usaria para arrenques externos
  pinMode(Pinprot, OUTPUT); //pin que se pretende usar ciomo proteccion al medir ameraje alto
  //  pinMode(serial, OUTPUT); // se usa para para la salida digital del serial, pero tambien se usara para bloquear nivel hardware, se puede mejorar
  pinMode(Pinestado, OUTPUT); // pin de salida giro "A"
  pinMode(Pinrestado, OUTPUT);// pin de salida giro "B"
  digitalWrite (Pinprot, HIGH); // configuracion de pines
  delay (1000);
  digitalWrite (Pinprot, LOW);
}
void loop () {
  arranque = digitalRead(PinArranque); //veo los pines de entrada
  paro = digitalRead(PinParo);
  reversible = digitalRead(Pinreversible);
  EstadoExterno = digitalRead(PinExterna);
>>>>>>> bd70cdc5782383e0311dc1a65d84998635a0d4b8

  while (BTSerial.available()) {    //pregunto sobre el dato del serial
    char data = (char)BTSerial.read();
    if ( data == 'H') {
      EstadoSalida = !EstadoSalida;
    }
  }
<<<<<<< HEAD
  if
  ((!serial and !Sw1) or (!Externa and !Sw1))
  {
    Giro1 = 0;
  }
  else {
    Giro1 = 1;
  }
  if
  ((serial and !Sw2) or (!Externa and !Sw2))
  {
    Giro2 = 0;
  }
  else {
    Giro2 = 1;

=======

  if (EstadoExterno) {
    EstadoSalida = !EstadoSalida
                   //delay(100);
  }

  if (paro) {
    estado = 0;
    restado = 0;
  }
  else if (EstadoSalida && arranque) {
    estado = 1;
    restado = 0;
  } else if (EstadoSalida && paro) {
    estado = 0;
    restado = 1;
  } else {
    estado = 0;
    restado = 0;
  }

  if (estado != estadoAnterior) {
    estadoAnterior = estado;
    digitalWrite(PinEstado, estado);
  }
  if (restado != estadoAnterior) {
    restadoAnterior = restado;
    digitalWrite(PinRestado, restado);
>>>>>>> bd70cdc5782383e0311dc1a65d84998635a0d4b8
  }
  digitalWrite (giro2, Giro2);
  digitalWrite(giro1, Giro1);
}
