//Este proyecto pretende sustituir la tarjeta electronica de un porton electrico, poderlo abrir por via bluetooth o manual a traves de botonera o por medio de radio control e incluso Wifi.


#include <SoftwareSerial.h>                                //Se puede emular mas de un puerto serial
SoftwareSerial BTSerial(10, 11);                          // RX | TX los pines que a usar
char data = 0;                                           // para guardar dato recibido del bluetooth
int arranque = 0;                                       // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "A"
int enclavamiento = 0;                                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "A"
int paro = 0;                                         // boton de paro el cual solo se uso al inicio del proyecto, pero se deja para ver la posibilidad de usarlo de nuevo en alguna  mejora
int estado = 0;                                      // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "A"
int reversible = 0;                                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int areversible = 0;                 // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int restado = 0;                    // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int renclavamiento = 0;            // esta variable la uso para guardar un dato de las entradas y poder hacer la logica del programa giro "B"
int w = 0;                        //entrada retro de serial y otra
static unsigned int  serial = 12; //modificar para incluir en la variable
static unsigned int PinArranque = 2; //configurar entradas digitales
static unsigned int PinParo = 3;  //configurar entradas digitales
static unsigned int Pinreversible = 4;  //configurar entradas digitales
static unsigned int Pinw = 5;  //configurar entradas digitales
static unsigned int Pinestado = 7; //configurar entradas digitales
static unsigned int Pinrestado = 8; //configurar entradas digitales
static unsigned int Pinprot = 9; //configurar entradas digitales
void setup () {

  BTSerial.begin(9600);//Inicializar comunicacion
  digitalWrite (Pinprot, HIGH); // configuracion de pines
  pinMode(PinArranque, INPUT);
  pinMode(PinParo, INPUT);
  pinMode(Pinreversible, INPUT);
  pinMode(Pinw, INPUT); //variable que se usaria para arrenques externos
  pinMode(Pinprot, OUTPUT); //pin que se pretende usar ciomo proteccion al medir ameraje alto
  pinMode(serial, OUTPUT); // se usa para para la salida digital del serial, pero tambien se usara para bloquear nivel hardware, se puede mejorar
  delay (1000);
  digitalWrite (Pinprot, LOW);
  pinMode(Pinestado, OUTPUT); // pin de salida giro "A"
  pinMode(Pinrestado, OUTPUT);// pin de salida giro "B"
}
void loop () {
  arranque = digitalRead(PinArranque); //veo los pines de entrada
  paro = digitalRead(PinParo);
  reversible = digitalRead(Pinreversible);
  w = digitalRead(Pinw);

  while (BTSerial.available()) {    //pregunto sobre el dato del serial
    char data = (char)BTSerial.read();
    if ( data == 'H')
    { digitalWrite(serial, !digitalRead(serial));
    }
  }

  if (paro == HIGH) { //funcion de paro
    digitalWrite (Pinrestado, HIGH);
    digitalWrite (Pinestado, HIGH);
    restado = 0;
    estado = 0;
  } delay (8);

  enclavamiento = estado; //funcion de activar giro "A"
  if (arranque == HIGH and w == HIGH) {
    estado = 1;
    restado = 0;
  }

  if (arranque == HIGH and serial == HIGH) { // salida usando con la logica de datos serial

    estado = 1;
    restado = 0;
  }

  if (estado == HIGH) { // giro "A" con proteccion de timer por si hay atoramiento en porton
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

  if (paro == HIGH) { // activando el paro general
    estado = 0;
    restado = 0;
    digitalWrite (Pinrestado, HIGH);
    digitalWrite (Pinestado, HIGH);
  }
  renclavamiento = restado;
  if (reversible == HIGH and w == LOW ) { //activando el giro "B"
    restado = 1;
    estado = 0;
  }

  if (restado == HIGH) {        // gito "B" con proteccion de timer por si hay atoramiento en porton
    digitalWrite (Pinrestado, LOW);
    digitalWrite (Pinestado, HIGH);
    delay (10000);
    restado = 0;
  }

  else {

    digitalWrite (Pinrestado, HIGH); // regreso a desactivar la salida, latarjete del proyecto se activa con niveles bajos

  }

  digitalWrite (Pinestado, HIGH);
  digitalWrite (Pinrestado, HIGH);

  if (paro == HIGH) {                   //funcion de paro 2
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
