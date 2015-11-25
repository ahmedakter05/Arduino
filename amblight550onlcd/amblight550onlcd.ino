#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
float light;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(void) {
  
    float lightValue = analogRead(A0); 
    float lightVoltage = ((lightValue*5.0)/1023.0); 
    light = (3.71*pow(lightVoltage,3))-(20.65*pow(lightVoltage,2))+(64.81*lightVoltage)-27.44;
    
    Serial.print("Light: ");
    Serial.print(light);
    Serial.println(" F"); 
    //Serial.println(lightVoltage);
    
    
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Light: ");
    lcd.setCursor(7,0);
    lcd.print("73");
    lcd.setCursor(8,1);
    lcd.print(" Flux");
    delay(1000);
}
