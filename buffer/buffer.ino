#include <stdio.h>
int i = 0;
void setup() {
   Serial.begin(9600);
}

void loop() {
      int a=5, b=3;
      char buffer [50];
       i=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
       Serial.println(i);
      for(int l= 0; l<=i; l++)
      Serial.print(buffer[l]);
      Serial.println();
      delay(1000);
 }
