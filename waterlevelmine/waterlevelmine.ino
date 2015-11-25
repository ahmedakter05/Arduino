#include <LiquidCrystal.h>

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
}

void loop(void) {
  
    float waterlevel = analogRead(apininp1); 
    float waterlevelvolt = waterlevel*4.7/1023;
    
    if(waterlevelvolt <= 5 && waterlevelvolt >= 3){
          waterlevelstatus=0;
    } else if(waterlevelvolt < 3 && waterlevelvolt >= 2.25){
          waterlevelstatus=30;
    } else if(waterlevelvolt < 2.25 && waterlevelvolt >= 2.05) {
          waterlevelstatus=60;
    } else {
        waterlevelstatus=90;
    }
    
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
