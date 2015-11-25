#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
float humidity;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(void) {
  
    float humValue = analogRead(A0); 
    float voltage = ((humValue*5.0)/1023.0); 
    humidity = (3.71*pow(voltage,3))-(20.65*pow(voltage,2))+(64.81*voltage)-27.44;
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %"); 
    Serial.println(voltage);
    
    
    // Print a message to the LCD.
    lcd.setCursor(0,0);
    lcd.print("Humidity: ");
    lcd.setCursor(4,1);
    lcd.print(humidity);
    lcd.setCursor(8,1);
    lcd.print(" %");
    delay(1000);
}
