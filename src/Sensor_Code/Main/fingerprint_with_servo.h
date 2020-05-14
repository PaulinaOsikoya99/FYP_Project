#include <Adafruit_Fingerprint.h>   
#include <HardwareSerial.h>
#include <Wire.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

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
   if (p != FINGERPRINT_OK){
     display.println("Try Again");
     Serial.println("Not Valid Finger");
   }

   // found a match!

   handleDoor();
   Buzzer();
   delay(3000);
   Serial.println("Door Unlocked Welcome");
   return finger.fingerID;
}
