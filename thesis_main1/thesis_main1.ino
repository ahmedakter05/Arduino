#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <String.h>
#include "Wire.h"
#include <OneWire.h>
#include <Temperature.h>
#include <LiquidCrystal.h>


#define DS3231_I2C_ADDRESS 0x68
#define onewiretempIPin 10


Servo servo1;
Servo servo2;
SoftwareSerial gsmSerial(7, 8);
OneWire oneWire(onewiretempIPin);
Temperature ds18b20(&oneWire);
//33o35y36r37g38a39b
//LiquidCrystal lcd(36, 38, 39, 37, 35, 33);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int temptopIPin = A0; 
int lightIPin = A6; 
int soilMoistIPin = A2; 
int humIPin = A1; 
int phIPin = A7;
//int tempds18bIPin = 10; 
int wl1IPin = A13; 
int wl2IPin = A14; 
int wl3PIin = A15; 
int servo1OPin = 53; 
int servo2OPin = 52;
int fanOPin = 22; 
int motorOPin = 23; 
int uvOPin = 24; 
int lightnorOPin = 25;

char link[128];
float humidity;
float light;
float temperature;
float waterlevel;
float soilmoist;
float phlevel;
int relayPin;
int lightcount = 0;
int lightreq = 8*3600;

int daystart = 1;
int day;

void setup(void) {
  gsmSerial.begin(19200); 
  Wire.begin();      
  Serial.begin(19200); 
  //lcd.begin(16, 2);
  servo1.attach(servo1OPin);
  servo1.write(0);
  servo2.attach(servo2OPin);
  servo2.write(0);
  ds18b20.begin();
  pinMode(fanOPin, OUTPUT);
  pinMode(motorOPin, OUTPUT);
  pinMode(uvOPin, OUTPUT);
  pinMode(lightnorOPin, OUTPUT);
  setDS3231time(30,13,15,4,2,12,15);

   lcd.begin(20, 4);
  delay(1000);
}

void loop(void) {
   
    if (Serial.available())
    switch(Serial.read())
    {
    case 'o':
    servoOpen();
    break;
    case 'c':
    servoClose();
    break;
    case 'f':
    relayControlOn(uvOPin);
    break;
    case 'm':
    relayControlOn(motorOPin);
    break;
    case 'n':
    relayControlOff(motorOPin);
    break;
    case 'p':
    postData();
    break;
    } 
    
    displayTime();

    lcd.setCursor(0,0);
    lcd.print("Light: ");
    lcd.setCursor(7,0);
    lcd.print("73");
    lcd.setCursor(8,1);
    lcd.print(" Flux");
    
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

    
    ds18b20.requestTemperatures();
    Serial.print("Temp-Soil: ");
    Serial.print(ds18b20.getTempCByIndex(0));
    Serial.println(" Celcius");
    
    soilMoist(soilmoist);
    
    waterLev(waterlevel);
    Serial.print("Water Level: ");
    Serial.print(waterlevel);
    Serial.println(" %");

    phLevel(phlevel);
    Serial.print("Ph Level: ");
    Serial.print(phlevel);
    Serial.println(" %");
    
    //relayControlOn(uvOPin);
    
    
    delay(3000);

    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

    
    int daynow = dayOfMonth;
    if (daynow < daystart){
      day = daynow + 30 - daystart;
    } else {
      day = daynow - daystart;
    }
    Serial.print("Day: ");
    Serial.println(day);

    //light
    if (hour < 19 && hour > 5){
      if (light > 50){
        lightcount = lightcount+1;
        
      }
      
    } else {
      
      if (lightcount < lightreq && lightcount!=0){
        lightcount = lightcount+1;
        relayControlOn(uvOPin);
      } else {
        lightcount = 0;
        relayControlOff(uvOPin);
      }
    }

    Serial.print("light: ");
    Serial.println(lightcount);



    
    if (0 < day < 6){

      //check temp & control fan + servo + normal light
      if (temperature < 15 ){
        relayControlOn(lightnorOPin);
      } else if (temperature > 35 ) {
        relayControlOn(fanOPin);
        servoOpen();
      } else if ( temperature > 20 && temperature < 30) {
        relayControlOff(lightnorOPin);
        relayControlOff(fanOPin);
        servoClose();
      }
      

      //humidity control
      if (humidity < 50 ){
        relayControlOn(fanOPin);
        servoOpen();
      } else if (humidity > 50 ) {
        relayControlOff(fanOPin);
        servoClose();
      }
      
      
      //check waterlevel & control motor
      if (soilmoist > 180 ){
        //relayControlOn(motorOPin);
      } else {
        relayControlOff(motorOPin);
      }
      
      //check ph and notify user
      
    } else if (5 < day < 12) {

      //check temp & control fan + servo + normal light
      if (temperature < 15 ){
        relayControlOn(lightnorOPin);
      } else if (temperature > 35 ) {
        relayControlOn(fanOPin);
        servoOpen();
      } else if ( temperature > 20 && temperature < 30) {
        relayControlOff(lightnorOPin);
        relayControlOff(fanOPin);
        servoClose();
      }
      

      //humidity control
      if (humidity < 50 ){
        relayControlOn(fanOPin);
        servoOpen();
      } else if (humidity > 50 ) {
        relayControlOff(fanOPin);
        servoClose();
      }
      
      
      //check waterlevel & control motor
      if (waterlevel < 30 ){
        relayControlOn(motorOPin);
      } else {
        relayControlOff(motorOPin);
      }
      
      //check ph and notify user
      
    } else if (11 < day < 28) {

      //check temp & control fan + servo + normal light
      if (temperature < 15 ){
        relayControlOn(lightnorOPin);
      } else if (temperature > 35 ) {
        relayControlOn(fanOPin);
        servoOpen();
      } else if ( temperature > 20 && temperature < 30) {
        relayControlOff(lightnorOPin);
        relayControlOff(fanOPin);
        servoClose();
      }
      

      //humidity control
      if (humidity < 50 ){
        relayControlOn(fanOPin);
        servoOpen();
      } else if (humidity > 50 ) {
        relayControlOff(fanOPin);
        servoClose();
      }
      
      
      //check waterlevel & control motor
      if (waterlevel < 60 ){
        relayControlOn(motorOPin);
      } else {
        relayControlOff(motorOPin);
      }
      
      //check ph and notify user
      
    } else {
      //stop the system & ring the Alarm
    }
}

void humIdity(float &humidity){
    float humValue = analogRead(humIPin); 
    float voltage = ((humValue*5.0)/1023.0); 
    humidity = (3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    //Serial.print("Humidity: ");
    //Serial.print(humidity);
    //Serial.println(" %");
}

void soilMoist(float &soilmoist){
     float soilMoistVal = analogRead(soilMoistIPin); 
     float soilMoistVolt = ((soilMoistVal*5.0)/1023.0); 
     //Serial.println(soilMoistVal);
     //Serial.println(soilMoistVolt);
     Serial.print("Soil Moist: ");
     Serial.print(soilMoistVal);
     Serial.print(" & ");
     Serial.print(soilMoistVolt);
     Serial.println(" %");
     soilmoist = soilMoistVal;
    
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

void phLevel(float &phlevel){
    float phValue = analogRead(phIPin); 
    float phVoltage = ((phValue*5.0)/1023.0); // convert analog value to voltage
    //equation for temperature
    phlevel = phValue; //(5.26*pow(phlevelVoltage,3))-(27.34*pow(tempVoltage,2))+(68.87*tempVoltage)-17.81;
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
    
    //Serial.println(level30pVolt);
    //Serial.println(level60pVolt);
    //Serial.println(level90pVolt);
    //float waterlevel = 50;
}

void servoOpen(){
    servo1.write(2);
    servo2.write(148);
   
}

void servoClose(){
    servo1.write(34);
    servo2.write(178);
    
}

void relayControlOn(int &relayPin)
{
  digitalWrite(relayPin, HIGH);
  
}

void relayControlOff(int &relayPin)
{
  digitalWrite(relayPin, LOW);
}

void SendMessage()
{
    gsmSerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
    delay(100);
    gsmSerial.println("AT + CMGS = \"+8801712203145\""); //send sms message, be careful need to add a country code before the cellphone number
    delay(100);
    gsmSerial.println("data");//the content of the message
    delay(100);
    gsmSerial.println((char)26);//the ASCII code of the ctrl+z is 26
    delay(100);
    gsmSerial.println();

    ShowSerialData();
}

void postData()
{
  gsmSerial.println("AT+CSQ");
  delay(1000);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 
  gsmSerial.println("AT+CGATT?");
  delay(1000);
 
  ShowSerialData();
 
  gsmSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(4000);
 
  ShowSerialData();
 
  gsmSerial.println("AT+SAPBR=3,1,\"APN\",\"blweb\"");//setting the APN, the second need you fill in your local apn server
  delay(4000);
 
  ShowSerialData();
 
  gsmSerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
  delay(4000);
 
  ShowSerialData();
 
  gsmSerial.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(8000); 
  ShowSerialData();
  char *aa = "ahmed12abs";
  char aa_val[160]; 
   sprintf(aa_val,"%s", aa);
   //Serial.println(sl_val);
   String url = "AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?";
   url.concat("query=");
   url.concat(String(aa_val));
   url.concat("\"");
  //gsmSerial.println("AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?query=aa\"");// setting the httppara, the second parameter is the website you want to access
  gsmSerial.println(url);
  delay(4000);
 
  ShowSerialData();
 
  gsmSerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!gsmSerial.available());
 
  ShowSerialData();

  gsmSerial.println("AT+HTTPTERM");
 
  //gsmSerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
 
  ShowSerialData();
 
  gsmSerial.println("");
  delay(100);
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}
 
void ShowSerialData()
{
  while(gsmSerial.available()!=0)
    Serial.write(gsmSerial.read());
}

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

