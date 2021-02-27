#include <Servo.h> 
Servo servoObject; 
int position = 0;
int posEin = 90;
int posAus = 90; 
const int waitTime = 5; 
 
void setup() 
{ 
  pinMode(D8, OUTPUT);
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  // Servo an digiteln Port D0
  servoObject.attach(D0);
  digitalWrite(D8, HIGH);  
} 
 
void loop() 
{ 
  // Servo um 180 Grad drehen 
  for (position = 75; position < 95; position++) 
  { 
    servoObject.write(position); 
    delay(waitTime); 
  } 
  delay(1000);
 
  // Servo wieder zurückdrehen 
  for (position = 95; position >= 75; position--) 
  { 
    servoObject.write(position); 
    delay(waitTime); 
  } 
  delay(1000);
  //digitalWrite(D8, 0);
  //Serial.println(digitalRead(D8));
  //delay(3000);
  //digitalWrite(D8, 1);
  //delay(1000);
  //Serial.println(digitalRead(D8));
}
