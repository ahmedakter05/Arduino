#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

float humidity;
float temperature;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(void) {
  
    float humValue = analogRead(A1); 
    float humVoltage = ((humValue*5.0)/1023.0); 
    humidity = (3.71*pow(humVoltage,3))-(20.65*pow(humVoltage,2))+(64.81*humVoltage)-27.44;
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %"); 
    //Serial.println(voltage);
    
    
    float tempValue = analogRead(A0); 
    float tempVoltage = ((tempValue*5.0)/1023.0); // convert analog value to voltage
    //equation for temperature
    temperature = (5.26*pow(tempVoltage,3))-(27.34*pow(tempVoltage,2))+(68.87*tempVoltage)-17.81;
    
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");
    //Serial.println(tempVoltage);
    
    
    // Print a message to the LCD.
    lcd.setCursor(2,0);
    lcd.print("Tonni + Ahmed");
    //lcd.setCursor(10,0);
    //lcd.print(humidity);
    //lcd.setCursor(15,0);
    //lcd.print("%");
    
    lcd.setCursor(0,1);
    lcd.print("Hum:");
    lcd.print(humidity);
    lcd.setCursor(6,1);
    lcd.print("% ");
    lcd.setCursor(8,1);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.setCursor(15,1);
    lcd.print("C");
    delay(1000);
}
