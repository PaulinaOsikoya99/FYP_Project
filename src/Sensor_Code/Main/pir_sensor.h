void motion() 
{
   digitalWrite(redLed, HIGH);
   digitalWrite(buzzer, HIGH);
   Serial.println("Alarm detected!"); //Send things to serial 
   Serial.print("motion ");
   Serial.println(motion);
   Serial.print("smoke ");
   Serial.println(smoke);
   ifttt1(); //Tell IFTTT that intruder detected

}


  
