#include <Adafruit_Fingerprint.h>   //https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
#include <HardwareSerial.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
Servo myservo;


int buzzerPin = 15;

void setup()
{

 myservo.attach(13);  // attaches the servo on pin 13 to the servo 

 pinMode(buzzerPin, OUTPUT);
 digitalWrite(buzzerPin, LOW);
 
 Serial.begin(57600);
 Serial2.begin(115200);
 
 while (!Serial); 
 delay(100);

 Serial.println("Fingerprint Door Lock");
 delay(3000);

 // set the data rate for the sensor serial port
 finger.begin(57600);

 if (finger.verifyPassword()) 
 {
   Serial.println("Fingerprint Sensor Connected");
   delay(3000); 
 }

 else  
 {
   Serial.println("Unable to find Sensor");
   delay(3000);
   Serial.println("Check Connections");

   while (1) {
     delay(1);
   }
 }
}

void loop()                     // run over and over again
{
 getFingerprintIDez();
 delay(50);            //don't need to run this at full speed.
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() 
{
 uint8_t p = finger.getImage();
 if (p != FINGERPRINT_OK)  
 {
   Serial.println("Waiting For Valid Finger");
   return -1;
 }

 p = finger.image2Tz();
 if (p != FINGERPRINT_OK)  
 {
   Serial.println("Messy Image Try Again");
   delay(3000);
   return -1;
 }

 p = finger.fingerFastSearch();
 if (p != FINGERPRINT_OK)  {
   display.println("Try Again");
   Serial.println("Not Valid Finger");
 }

 // found a match!

   myservo.write(90);     
   digitalWrite(buzzerPin, HIGH);
   delay(3000);
   myservo.write(0);   
   digitalWrite(buzzerPin, LOW);
   delay(3000);
   
   Serial.println("Door Unlocked Welcome");
   
   return finger.fingerID;
}
