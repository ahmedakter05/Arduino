#include <IRremote.h>

#include <LiquidCrystal.h>
#include <IRremote.h>

// use this option for OSX:
// char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux:
// char ctrlKey = KEY_LEFT_CTRL;  


LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

float humidity;
float temperature;

int IRpin = 7;
IRrecv irrecv(IRpin);
decode_results results;

int pirPin = 6;
int led1Pin = 8;
int led2Pin = 9;

int pirState = 0;
int tubeState = 1;
int tubeClock = 0;
int delay1s = 100;
int maxDelay = 120*delay1s;

int switch1States = 0;
int switch2States = 0;
int switch3States = 0;
int switch4States = 0;
int switch5States = 0;


void setup(void) {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin(16, 2);
  //Keyboard.begin();
  pinMode(pirPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(pirPin, LOW);
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, LOW);
  delay(1000);
}

void loop(void) {
 
   if (irrecv.decode(&results)) 
    {
      
      irrecv.resume();   // Receive the next value
    }

    int motionState = digitalRead(pirPin);
    
    Serial.println(results.value);
    //results.value = 0;

    switch (results.value){
      case 948321248: //when you press the Forward button
       //statement
       digitalWrite(led1Pin, HIGH);
       if(switch1States==0){
          pirState = 1;
          switch1States=1;
       } else if(switch1States==1) {
          pirState = 0;
          switch1States=0;
       }
       results.value = 12345;  
       delay(10); 
       break;
       
       case 948321232: //when you press the Forward button
       if(switch2States==0){
          tubeState = 0;
          switch2States=1;
       } else if(switch2States==1) {
          tubeState = 1;
          switch2States=0;
       }
       results.value = 12345;  
       delay(10); 
       break;

       case 948321264: //when you press the Forward button
       if(switch2States==0){
          digitalWrite(led2Pin, LOW);
          switch2States=1;
       } else if(switch2States==1) {
         digitalWrite(led2Pin, HIGH);
          switch2States=0;
       }
       results.value = 12345;  
       delay(10); 
       break;
       
       default:
        results.value = 12345;
        Serial.println();
   }

     //Serial.print("PIR State: ");
     //Serial.println(pirState);
  
     if (pirState == 1) {
      if (motionState == HIGH) {
        digitalWrite(led1Pin, LOW);
      }
     }
  
     Serial.print("Motion State: ");
     Serial.println(motionState);
      if (tubeState == 1) {
       if (motionState == HIGH) {
        tubeClock = 0;
       }
    
      tubeClock = tubeClock + (delay1s/10);
      Serial.println(tubeClock);
  
      if (tubeClock >= maxDelay){
        digitalWrite(led2Pin, HIGH);
      } else {
        digitalWrite(led2Pin, LOW);
      }
     }
     
  
    float humValue = analogRead(A0); 
    float humVoltage = ((humValue*5.0)/1023.0); 
    humidity = (3.71*pow(humVoltage,3))-(20.65*pow(humVoltage,2))+(64.81*humVoltage)-27.44;
    
    ///Serial.print("Humidity: ");
    ///Serial.print(humidity);
    ///Serial.println(" %"); 
    //Serial.println(voltage);
    
    
    float tempValue = analogRead(A1); 
    float tempVoltage = ((tempValue*5.0)/1023.0); // convert analog value to voltage
    //equation for temperature
    temperature = (5.26*pow(tempVoltage,3))-(27.34*pow(tempVoltage,2))+(68.87*tempVoltage)-17.81;
    
    ///Serial.print("Temperature: ");
    ///Serial.print(temperature);
    ///Serial.println("C");
    //Serial.println(tempVoltage);
    
    
    // Print a message to the LCD.
    lcd.setCursor(1,0);
    lcd.print("Tonni + Ahmed");
    //lcd.setCursor(9,0);
    //lcd.print(humidity);
    //lcd.setCursor(15,0);
    //lcd.print("%");
    
    lcd.setCursor(0,1);
    lcd.print("Hum:");
    lcd.print(humidity);
    lcd.setCursor(6,1);
    lcd.print("% ");
    lcd.setCursor(8,1);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.setCursor(15,1);
    lcd.print("C");
    delay(delay1s);
}
