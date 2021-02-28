#include <Servo.h> 
Servo servoObject; 
int position = 0;
const int waitTime = 5; 
 
void setup() 
{ 
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  // Servo an digiteln Port D0
  servoObject.attach(D0);  
} 
 
void loop() 
{  
  for (position = 75; position < 95; position++) 
  { 
    servoObject.write(position); 
    delay(waitTime); 
  } 
  delay(1000);
 
  for (position = 95; position >= 75; position--) 
  { 
    servoObject.write(position); 
    delay(waitTime); 
  } 
  delay(1000);
}
