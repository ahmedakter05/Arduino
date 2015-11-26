
#include <Servo.h>

  Servo myservo;  // create servo object to control a servo

  // variable to read the value from the analog pin

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{ 
  myservo.write(0);                  // sets the servo position according to the scaled value 
  delay(100);
  myservo.write(180);
  delay(100);  // waits for the servo to get there 
} 

