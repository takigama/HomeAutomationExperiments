#include <IRremoteESP8266.h>

int IR_RECV_PIN = 2; //an IR detector/demodulator is connected to GPIO pin 2

IRrecv irrecv(RECV_PIN);




void  setup ( )
{
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud
  irrecv.enableIRIn();  // Start the receiver
}



void loop()
{
  
}

