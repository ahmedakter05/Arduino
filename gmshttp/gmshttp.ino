#include <SoftwareSerial.h>
#include <String.h>
#define BUFFSIZ 90
char buffer[BUFFSIZ];
char buffidx;
char aa='ahmed';
int retry = 5;
int value;
int dLine[30];
int sendCommand(char* command, char* resp, int delayTime=500, int reps=5, int numData=2);
boolean config = false;
boolean power = false;
SoftwareSerial mySerial(7, 8);
void setup()
{
 mySerial.begin(19200); // the GPRS baud rate 
 Serial.begin(19200); // the GPRS baud rate 
 delay(500);
}

void loop()
{
 //after start up the program, you can using terminal to connect 
 //the serial of gprs shield,
 //if you input 't' in the terminal, the program will execute SendTextMessage(), 
 //it will show how to send a sms message,
 //if input 'd' in the terminal, it will execute DialVoiceCall(), etc.

 if (Serial.available())
 switch(Serial.read())
 {
 case 't':
 SendTextMessage();
 break;
 case 'd':
 DialVoiceCall();
 break;
 case 's':
 SubmitHttpRequestwv();
 break;
 case 'h':
 SubmitHttpRequest();
 break;
 } 
 if (mySerial.available())
 Serial.write(mySerial.read());
}

///SendTextMessage()
///this function is to send a sms message
void SendTextMessage()
{
 mySerial.print("AT+CMGF=1\r"); //Because we want to send the SMS in text mode
 delay(100);
 mySerial.println("AT + CMGS = \"+8801715009721\"");//send sms message, 
 //be careful need to add a country code before the cellphone number
 delay(100);
 mySerial.println("A test message from AA!");//the content of the message
 delay(100);
 mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
 delay(100);
 mySerial.println();
}

///DialVoiceCall
///this function is to dial a voice call
void DialVoiceCall()
{
 mySerial.println("ATD + +8801712203145;");//dial the number
 delay(100);
 mySerial.println();
}

///SubmitHttpRequest()
///this function is submit a http request
///attention:the time of delay is very important, it must be set enough 
void SubmitHttpRequest()
{
 powerOn();
 mySerial.println("AT+CSQ");
 delay(100);
 ShowSerialData();// this code is to show the data from gprs shield, 
 //in order to easily see the process of
 //how the gprs shield submit a http request, and the following is for this purpose too.
 mySerial.println("AT+CGATT?");
 delay(100);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection 
 //type is using gprs
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"APN\",\"blweb\"");//setting the APN, 
 //the second need you fill in your local apn server
 delay(4000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to 
 //the AT command mamual
 delay(2000);
 ShowSerialData();
 mySerial.println("AT+HTTPINIT"); //init the HTTP request
 delay(2000); 
 ShowSerialData();
 mySerial.println("AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?query=aawtv\"");// setting the httppara,
 Serial.print("id=" + aa);
 //the second parameter is the website you want to access
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+HTTPACTION=0");//submit the request 
 delay(4000);//the delay is very important, the delay time is base on the return from the website, 
 //if the return datas are very large, the time required longer.
 //while(!mySerial.available());
 ShowSerialData();
 //mySerial.println("AT+HTTPREAD");// read the data from the website you access
 delay(300);
// ShowSerialData();
 checkForResponse();
 mySerial.println("");
 delay(100);
 mySerial.println("AT+HTTPTERM");// read the data from the website you access
 delay(300);
 ShowSerialData();
 //powerOff();
}

void SubmitHttpRequestwv()
{
 powerOn();
 mySerial.println("AT+CSQ");
 delay(100);
 ShowSerialData();// this code is to show the data from gprs shield, 
 //in order to easily see the process of
 //how the gprs shield submit a http request, and the following is for this purpose too.
 mySerial.println("AT+CGATT?");
 delay(100);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection 
 //type is using gprs
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"APN\",\"blweb\"");//setting the APN, 
 //the second need you fill in your local apn server
 delay(4000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to 
 //the AT command mamual
 delay(2000);
 ShowSerialData();
 mySerial.println("AT+HTTPINIT"); //init the HTTP request
 delay(2000); 
 ShowSerialData();
 mySerial.println("AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?query=aawv\"");// setting the httppara,
 //the second parameter is the website you want to access
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+HTTPACTION=0");//submit the request 
 delay(8000);//the delay is very important, the delay time is base on the return from the website, 
 //if the return datas are very large, the time required longer.
 while(!mySerial.available());
 ShowSerialData();
 mySerial.println("AT+HTTPREAD");// read the data from the website you access
 delay(300);
 ShowSerialData();
 checkForResponse();
 mySerial.println("");
 delay(100);
 mySerial.println("AT+HTTPTERM");// read the data from the website you access
 delay(300);
 ShowSerialData();
 //powerOff();
}
void ShowSerialData()
{
 while(mySerial.available()!=0)
 Serial.write(mySerial.read());
}
void checkForResponse(){ //this part for text parsing and processing. get 10101010 from
// the website and parse it.
 while(mySerial.available()!=0){
 for (int i = 0; i < 22; i++){
 dLine[i] = mySerial.read();
 }
 }
 Serial.print(dLine[6]);
 Serial.print(dLine[7]);
 Serial.print(dLine[8]);
 Serial.print(dLine[9]);
 Serial.print(dLine[10]);
 Serial.print(dLine[11]);
 Serial.print(dLine[12]);
 Serial.print(dLine[13]);
 value= (dLine[6]-48)*128+(dLine[7]-48)*64+(dLine[8]-48)*32+(dLine[9]-48)*16+(dLine[10]-48)*8+(dLine[11]-48)*4+(dLine[12]-48)*2+(dLine[13]-48);
 // this formula used to get decimal value for arduino shift register.
 Serial.print(value);
}
void powerOn(){
 if(sendCommand("AT","OK",500,1) !=1){
 Serial.println("Powering On...");
 pinMode(9, OUTPUT); 
 digitalWrite(9,LOW);
 delay(1000);
 digitalWrite(9,HIGH);
 delay(2000);
 digitalWrite(9,LOW);
 delay(10000);
 //delay(15500);
 if(sendCommand("AT+CREG?","+CREG: 0,1",500,10,10)==1){
 Serial.println("REGISTERED");
 Serial.print(".");
 }
 power = true;
// setupCommands();
 }
 else{
 Serial.println("ALREADY ON");
 power = true;
 }
}
void powerOff(){
 delay(1000);
 pinMode(9, OUTPUT); 
 digitalWrite(9,LOW);
 delay(1000);
 digitalWrite(9,HIGH);
 delay(2500);
 digitalWrite(9,LOW);
 power = false;
 //delay(10500);
}
int sendCommand(char* command, char* resp, int delayTime, int reps, int numData){
 int returnVal;
 //delay(100);
 for(int i=0;i<reps;i++){
 if (i > 0) delay(500);
 mySerial.flush();
 delay(100);
 mySerial.println(command);
 delay(100);
 Serial.print(command);
 Serial.print(": ");
 //delay(10);
 delay(delayTime);
 // while(mySerial.available() < numData+1){
 // unsigned long currentMillis = millis();
 // 
 // if(currentMillis - previousMillis > delayTime) {
 // Serial.println("TIMEOUT");
 // break;
 // }
 // }
 long previousMillis = millis();
 //unsigned long currentMillis;
 while(mySerial.available()) {
// unsigned long currentMillis = millis();
// if(currentMillis - previousMillis > delayTime) {
// Serial.println("TIMEOUT");
// break;
// }
 readline();
 //Serial.println("AFTER READLINE");
 if (strncmp(buffer, resp,numData) == 0) {
 Serial.println(buffer);
 return 1;
 }
 }
 Serial.print("FAILED");
 Serial.println(buffer);
 }
 return 0;
}
void readline() {
 memset(buffer,0,sizeof(buffer));
 char c;
 int i =0;
 buffidx = 0; // start at begninning
 //Serial.println("BEFORE READLINE");
 long previousMillis = millis();
 while (1) {
 unsigned long currentMillis = millis();
 if(currentMillis - previousMillis > 20000) {
 Serial.println("TIMEOUT");
 return;
 }
 delay(2);
 c=mySerial.read();
 //Serial.print(buffidx);
 if (c == -1)
 continue;
 if (c == '\n')
 continue;
 if ((buffidx == BUFFSIZ-1) || (c == '\r')) {
 buffer[buffidx] = 0;
 return;
 }
 buffer[buffidx++]= c;
 delay(2);
 }
}
void setupCommands(){
 sendCommand("AT&F","OK");
 sendCommand("ATE0","OK");
 sendCommand("AT+CLIP=1","OK");
 sendCommand("AT+CMEE=0","OK");
 sendCommand("AT+CIPSHUT","SHUT");
}
