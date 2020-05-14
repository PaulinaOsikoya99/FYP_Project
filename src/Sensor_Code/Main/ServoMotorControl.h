// Include the Servo library 
#include <Servo.h> 

Servo Servo1;
Servo Servo2;

void handleDoor(){ 
 // Make servo go to 0 degrees 
  Servo1.write(0);
  delay(1000); 
  Servo1.write(90); 
  delay(1000); 
  Servo1.write(180); 
  delay(10000);  
  // Make servo go to 180 degrees 
  Servo1.write(90); 
  delay(20);
  Servo1.write(60);
  delay(20); 
  Servo1.write(0); 
  Serial.println(F("door opened "));
  }

void handleWindow(){ 
 // Make servo go to 0 degrees 
  Servo2.write(0);
  delay(1000); 
  Servo2.write(90); 
  delay(1000); 
  Servo2.write(180); 
  delay(10000);  
  // Make servo go to 180 degrees 
  Servo2.write(90); 
  delay(20);
  Servo2.write(60);
  delay(20); 
  Servo2.write(0); 
  Serial.println(F("door opened "));
  }
