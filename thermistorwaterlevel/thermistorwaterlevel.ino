#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
int led0p = 7;
int led50p = 8;
int led100p = 9;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(void) {
  
    float level0p = analogRead(A1); 
    float level0pVolt = level0p*5/1023;
    float level50p = analogRead(A2); 
    float level50pVolt = level50p*5/1023;
    float level100p = analogRead(A3); 
    float level100pVolt = level100p*5/1023;
    
    
    Serial.println(level0p);
    Serial.println(level50p);
    Serial.println(level100p);
    
    //Serial.print("Light: ");
    //Serial.print(light);
    //Serial.println(" F"); 
    //Serial.println(lightVoltage);
    
    
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Level: ");
    lcd.setCursor(7,0);
    lcd.print("50");
    lcd.setCursor(9,0);
    lcd.print(" %");
    delay(1000);
}
