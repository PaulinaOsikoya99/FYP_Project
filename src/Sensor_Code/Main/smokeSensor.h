#include <AWS_IOT.h>

AWS_IOT aws;

void smokeSensor() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    Serial.print("buzzer and led high ");
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    ifttt();
    String smoke_sensor= "Smoke_level: ";
    smoke_sensor += String(analogSensor);
    char payload[40];
    smoke_sensor.toCharArray(payload, 40);
    Serial.println("Publishing:- ");
    Serial.println(payload);
    if(aws.publish("smoke",payload) == 0)
    {        
      Serial.print("Publish Message:");
      Serial.println(payload); 
      Serial.println("Success\n");    
    }
    else{
      Serial.println("Failed!\n");
    }
      
  }
  else
  {
     digitalWrite(redLed, LOW);
     digitalWrite(buzzer, LOW);
  }
  delay(100);
}
