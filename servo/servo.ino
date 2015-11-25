#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int pos = 0;
int ir =0;

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
int apininp1 = A0;
int dpinout1 = 7;
int dpinout2 = 8;
int dpinout3 = 9;
int waterlevelstatus = 0;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(apininp1, INPUT);
  pinMode(dpinout1, OUTPUT);
  pinMode(dpinout2, OUTPUT);
  pinMode(dpinout3, OUTPUT);
  digitalWrite(dpinout1, LOW);
  digitalWrite(dpinout2, LOW);
  digitalWrite(dpinout3, LOW);
  myservo.attach(8);
  pinMode(A1, INPUT);
}

void loop(void) {
  
    float waterlevel = analogRead(apininp1); 
    float waterlevelvolt = waterlevel*4.7/1023;
    
    if(waterlevelvolt <= 5 && waterlevelvolt >= 3){
          waterlevelstatus=0;
          pos = 0;
    } else if(waterlevelvolt < 3 && waterlevelvolt >= 2.25){
          waterlevelstatus=30;
          pos = 60;
    } else if(waterlevelvolt < 2.25 && waterlevelvolt >= 2.20) {
          waterlevelstatus=60;
          pos = 120;
    } else {
        waterlevelstatus=90;
        pos = 180;
    }
    
    //if (Serial.available() > 0) 
    //{
               // pos = Serial.read() - '0';
   // }
    //pos = (pos, DEC);
    myservo.write(180);
    delay(100);
    myservo.write(90);
    delay(100);
    myservo.write(0);

    ir = analogRead(A1);
    Serial.println(ir);
    
    //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      //myservo.write(pos);              // tell servo to go to position in variable 'pos'
     // delay(5);                       // waits 15ms for the servo to reach the position
    //}
    //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     // myservo.write(pos);              // tell servo to go to position in variable 'pos'
      //delay(5);                       // waits 15ms for the servo to reach the position
    //}
  
    //Serial.println(waterlevel);
    Serial.println(waterlevelvolt);
    Serial.print("Water Level: ");
    Serial.print(waterlevelstatus);
    Serial.println(" %");
    
    
    
    
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Level: ");
    lcd.setCursor(7,0);
    lcd.print(waterlevelstatus);
    lcd.setCursor(9,0);
    lcd.print(" %");
    delay(1000);
}
