#include <AWS_IOT.h>

AWS_IOT hornbill;

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
    
    sprintf(payload,"Smoke Sensor: ON");
    if(hornbill.publish(TOPIC_NAME,payload) == 0)
    {        
      Serial.print("Publish Message:");
      Serial.println(payload);     
    }
      
  }
  else
  {
     digitalWrite(redLed, LOW);
     digitalWrite(buzzer, LOW);
  }
  delay(100);
}
