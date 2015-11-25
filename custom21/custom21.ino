#include <IRremote.h>
//#include <IRremoteInt.h>



#include <OneWire.h>

// include the library code:
#include <LiquidCrystal.h>



int IRpin = 6;  // pin for the IR sensor
int LED1 = 8;// LED pin  
int LED2 = 13;
IRrecv irrecv(IRpin);
decode_results results;
int led1States = 0;
int led2States = 0;

boolean LEDon = true; // initializing LEDon as true


// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(9);  // on pin 10 (a 4.7K resistor is necessary)

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop(void) {

   byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {
    
    ds.reset_search();
    delay(250);
    return;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      //Serial.println("CRC is not valid!");
      return;
  }
  

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    //Serial.print(data[i], HEX);
    //Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.println(" Celcius");
  
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
   
   
  
   float humidity;
   humIdity(humidity);
  
   Serial.print("Humidity: ");
   Serial.print(humidity);
   Serial.println(" %");
   
   
  float light;
  lightInt(light);
  
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println(" Lumens");
  
  float temperature;
  tempVal(temperature);
  
  Serial.print("Temp-2: ");
  Serial.print(temperature);
  Serial.println(" Celcius");
    
  
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print(celsius);
  lcd.setCursor(5,0);
  lcd.print("^C");
  
  lcd.setCursor(8,0);
  lcd.print(humidity);
  lcd.setCursor(12,0);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("Light:");
  lcd.setCursor(7,1);
  lcd.print(light);
  lcd.setCursor(12,1);
  lcd.print("Lux");
  
}

void humIdity(float &humidity){
    int humValue = analogRead(A1); 
    int voltage = ((humValue*5.0)/1023.0); 
    humidity= (3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void lightInt(float &light){
    int lightValue = analogRead(A0); 
    //int voltage = ((humValue*5.0)/1023.0); 
    light = lightValue; //(3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void tempVal(float &temperature){
    int tempValue = analogRead(A2); 
    int voltage_temp = ((tempValue*5.0)/1023.0); // convert analog value to voltage
    //equation for temperature
    temperature=(5.26*pow(voltage_temp,3))-(27.34*pow(voltage_temp,2))+(68.87*voltage_temp)-17.81;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}
