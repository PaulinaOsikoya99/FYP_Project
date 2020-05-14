void motion() 
{
   motion = digitalRead(motion1); //PIR sensor pin
 
   Serial.println("Alarm detected!"); //Send things to serial for handy dandy info
   Serial.print("motion ");
   Serial.println(motion);
   Serial.print("smoke ");
   Serial.println(smoke);
   ifttt1(); //Tell IFTTT that intruder detected

}


  
