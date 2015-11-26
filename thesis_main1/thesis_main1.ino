#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

//LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
int temptopIPin = A0; 
int lightIPin = A6; 
int humIPin = A1; 
int tempds18bIPin = 10; 
int wl1IPin = A13; 
int wl2IPin = A14; 
int wl3PIin = A15; 
int servo1OPin = 53; 
int servo2OPin = 52; 

float humidity;
float light;
float temperature;
float waterlevel;

void setup(void) {
  Serial.begin(9600);
  //lcd.begin(16, 2);
  servo1.attach(servo1OPin);
  servo1.write(0);
  servo2.attach(servo2OPin);
  servo2.write(0);
}

void loop(void) {
   
   float soilMoistVal = analogRead(A7); 
   float soilMoistVolt = ((soilMoistVal*5.0)/1023.0); 
   Serial.println(soilMoistVal);
   Serial.println(soilMoistVolt);

   if (Serial.available())
   switch(Serial.read())
   {
   case 'o':
   servoOpen();
   break;
   case 'c':
   servoClose();
   break;
   } 
   

  
   humIdity(humidity);
   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.println(" %");
   
   
  lightInt(light);
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println(" Lumens");
  
  
  tempVal(temperature);
  Serial.print("Temp-Top: ");
  Serial.print(temperature);
  Serial.println(" Celcius");

  waterLev(waterlevel);
  
  Serial.print("Water Level: ");
  Serial.print(waterlevel);
  Serial.println(" %");


  delay(3000);
}

void humIdity(float &humidity){
    float humValue = analogRead(humIPin); 
    float voltage = ((humValue*5.0)/1023.0); 
    humidity = (3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void lightInt(float &light){
    float lightValue = analogRead(lightIPin); 
    //int voltage = ((humValue*5.0)/1023.0); 
    light = lightValue; //(3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void tempVal(float &temperature){
    float tempValue = analogRead(temptopIPin); 
    float tempVoltage = ((tempValue*5.0)/1023.0); // convert analog value to voltage
    //equation for temperature
    temperature = (5.26*pow(tempVoltage,3))-(27.34*pow(tempVoltage,2))+(68.87*tempVoltage)-17.81;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void waterLev(float &waterlevel){

    waterlevel = 0;
    
    float level30p = analogRead(wl1IPin); 
    float level30pVolt = level30p*5/1023;
    
    float level60p = analogRead(wl2IPin); 
    float level60pVolt = level60p*5/1023;
    
    float level90p = analogRead(wl3PIin); 
    float level90pVolt = level90p*5/1023;

    if (level30pVolt < 4){
          waterlevel = 30;
    }
    if (level60pVolt < 4){
          waterlevel = 60;
    }

    if (level90pVolt < 4){
          waterlevel = 90;
    }
    
    Serial.println(level30pVolt);
    Serial.println(level60pVolt);
    Serial.println(level90pVolt);
    //float waterlevel = 50;
}

void servoOpen(){
    servo1.write(2);
    servo2.write(148);
   
}

void servoClose(){
    servo1.write(32);
    servo2.write(178);
    
}
