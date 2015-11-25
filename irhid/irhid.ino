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


uint8_t buf[8] = { 
  0 };  /* Keyboard report buffer */

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
   //Serial.println(results.value);
   switch (results.value){
      case 948321242: //mute [m]
        buf[2] = 16;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321266: //P+ [Up Arrow]
        buf[2] = 82;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321274: //P- [Down Arrow]
        buf[2] = 81;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321226: //V- [Left Arrow]
        buf[2] = 80;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321218: //V+ [Right Arrow]
        buf[2] = 79;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321244: //Menu [Enter/Return]
        buf[2] = 40;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321230: //PIC [Spacebar]
        buf[2] = 44;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321278: //SYS [Backspace]
        buf[2] = 42;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321254: //P.P [Page Down] *
        buf[2] = 78;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321222: //Zoom [Page Up] *
        buf[2] = 75;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321234: //Power [cntrl s] *
        buf[2] = 0;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321236: //-/-- [Close Window] *
        buf[0] = 226;
        buf[2] = 61;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321238: //(recycle) [Tab Window] *
        buf[0] = 226;
        buf[2] = 43;   
        Serial.write(buf, 8); 
        releaseKey();
        results.value = 12345;  
        delay(10); 
        break;

      case 948321270: //Disp [Led Switch] 
        if(led1States==0)
        {
          digitalWrite(LED1, HIGH);
          led1States=1;
        } else if(led1States==1) {
            digitalWrite(LED1, LOW);
            led1States=0;
        }
        results.value = 12345;  
        delay(10); 
        break;
       
       default:
        results.value = 12345;
        //Serial.println();
   }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
  
}

