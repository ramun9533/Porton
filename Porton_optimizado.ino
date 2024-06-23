#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

// Definición de los pines de entrada
const int numInputs = 6;
static const unsigned short int inputPins[numInputs] = {2, 3, 4, 5, 6, 12}; 
// 2: sw1, 3: paro, 4: sw2, 5: externa, 6: selec, 12: selec1

// Definición de los pines de salida
const int numOutputs = 3;
static const unsigned short int outputPins[numOutputs] = {7, 8, 9}; 
// 7: giro1, 8: giro2, 9: proteccion

int Selec1, Selec, Paro, Sw1, Sw2, Externa;
int Giro1 = 0;
int Giro2 = 0;
int serial = 0;

void setup() {
  BTSerial.begin(9600); // Inicializar comunicación serial

  // Configurar pines de entrada
  for (int i = 0; i < numInputs; i++) {
    pinMode(inputPins[i], INPUT);
  }

  // Configurar pines de salida
  for (int i = 0; i < numOutputs; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }
}

void loop() {
  // Leer entradas
  Sw1 = digitalRead(inputPins[0]);
  Paro = digitalRead(inputPins[1]);
  Sw2 = digitalRead(inputPins[2]);
  Externa = digitalRead(inputPins[3]);
  Selec = digitalRead(inputPins[4]);
  Selec1 = digitalRead(inputPins[5]);

  // Paro de emergencia
  if (Paro) {
    digitalWrite(outputPins[2], HIGH); // Activar protección
  } else {
    digitalWrite(outputPins[2], LOW); // Desactivar protección
  }

  delay(10);
  
  // Leer datos seriales
  while (BTSerial.available()) {
    char data = (char)BTSerial.read();
    if (data == 'H') {
      serial = !serial; // Invertir estado de serial
    }
  }

  // Lógica de giro1
  if (Selec1 && Sw1) {
    Giro1 = 0;
  } else if (!Selec1 && ((Selec && !serial && !Sw1) || (!Selec && !Externa && !Sw1))) {
    Giro1 = 0;
  } else {
    Giro1 = 1;
  }

  // Lógica de giro2
  if (Selec1 && Sw2) {
    Giro2 = 0;
  } else if (!Selec1 && ((Selec && serial && !Sw2) || (!Selec && Externa && !Sw2))) {
    Giro2 = 0;
  } else {
    Giro2 = 1;
  }

  // Escribir salidas
  digitalWrite(outputPins[0], Giro1);
  digitalWrite(outputPins[1], Giro2);
}
 
