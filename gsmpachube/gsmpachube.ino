#include <SoftwareSerial.h>
#include <String.h>

char link[128];
 
SoftwareSerial mySerial(7, 8);
 
void setup()
{
  mySerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);    // the GPRS baud rate 
  delay(500);

}
 
void loop()
{
  //after start up the program, you can using terminal to connect the serial of gprs shield,
  //if you input 't' in the terminal, the program will execute SendTextMessage(), it will show how to send a sms message,
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
  mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT + CMGS = \"+8801980936038\"");//send sms message, be careful need to add a country code before the cellphone number
  delay(100);
  mySerial.println("A test message!");//the content of the message
  delay(100);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial.println();
}
 
///DialVoiceCall
///this function is to dial a voice call
void DialVoiceCall()
{
  mySerial.println("ATD + +8801980936038;");//dial the number
  delay(100);
  mySerial.println();
}
 
///SubmitHttpRequest()
///this function is submit a http request
///attention:the time of delay is very important, it must be set enough 
void SubmitHttpRequest()
{
  mySerial.println("AT+CSQ");
  delay(1000);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 
  mySerial.println("AT+CGATT?");
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(4000);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"blweb\"");//setting the APN, the second need you fill in your local apn server
  delay(4000);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
  delay(4000);
 
  ShowSerialData();
 
  mySerial.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(8000); 
  ShowSerialData();
  char *aa = "ahmed12ass";
  char aa_val[160]; 
   sprintf(aa_val,"%s", aa);
   //Serial.println(sl_val);
   String url = "AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?";
   url.concat("query=");
   url.concat(String(aa_val));
   url.concat("\"");
  //mySerial.println("AT+HTTPPARA=\"URL\",\"www.aapf.tk/yapps/apps/siteinfo/arduino?query=aa\"");// setting the httppara, the second parameter is the website you want to access
  mySerial.println(url);
  delay(4000);
 
  ShowSerialData();
 
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available());
 
  ShowSerialData();

  mySerial.println("AT+HTTPTERM");
 
  //mySerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
 
  ShowSerialData();
 
  mySerial.println("");
  delay(100);
}
 
///send2Pachube()///
///this function is to send the sensor data to the pachube, you can see the new value in the pachube after execute this function///


 
void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}
