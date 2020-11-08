#include <SoftwareSerial.h>   //Se puede emular mas de un puerto serial
SoftwareSerial BTSerial(10, 11);   // RX | TX 
static unsigned int  Led = 12;


void setup() {
   pinMode(Led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  while (BTSerial.available()) 
  {
    char data = (char)BTSerial.read();
    if ( data == 'H')
    { digitalWrite(Led, !digitalRead(Led));
    }
}}
