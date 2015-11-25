/*
 Some Sample code of how to use your IR remote
 
 * Lets get started:
 
 The IR sensor's pins are attached to Arduino as so:
 Pin 1 to Vout (pin 11 on Arduino)
 Pin 2 to GND
 Pin 3 to Vcc (+5v from Arduino)

*/

#include <IRremote.h>

int IRpin = 7;  // pin for the IR sensor
int LED1 = 8;// LED pin  
int LED2 = 9;
IRrecv irrecv(IRpin);
decode_results results;
int led1States = 0;
int led2States = 0;

boolean LEDon = true; // initializing LEDon as true

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() 
{
   
  if (irrecv.decode(&results)) 
    {
      
      irrecv.resume();   // Receive the next value
    }
    
  Serial.println(results.value);
  
   //if (results.value == 948321234)  // this is where you put in your IR remote button #
   switch (results.value){
      case 948321248: //when you press the Forward button
       //this if/else statement makes sure that LED is ON or OFF before move to the next LED
       if(led1States==0){
          digitalWrite(LED1, HIGH);
          led1States=1;
       } else if(led1States==1) {
          digitalWrite(LED1, LOW);
          led1States=0;
       }
       results.value = 12345;  
       delay(10); 
       break;
       
       case 948321232: //when you press the Forward button
       //this if/else statement makes sure that LED is ON or OFF before move to the next LED
       if(led2States==0){
          digitalWrite(LED2, HIGH);
          led2States=1;
       } else if(led2States==1) {
          digitalWrite(LED2, LOW);
          led2States=0;
       }
       results.value = 12345;  
       delay(10); 
       break;
       
       default:
        Serial.println();
   }
       
  
    delay(1000); 
    
}

