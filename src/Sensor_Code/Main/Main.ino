#include <WiFi.h>
#include <Servo.h>
#include "DHT.h"
#include "GoogleAssistant.h"
#include "IFTTT_Motion.h"
#include "IFTTT_Smoke.h"
#include "IOT_AWS.h"
#include "ServoMotorControl.h"
#include "WIFI_details.h"
#include "fingerprint_with_servo.h"
#include "globalVars.h"
#include "handle_buzzer.h"
#include "pir_sensor.h"
#include "smokeSensor.h"


// make wificlient object
WiFiClient client;

// create servo object to control a servo 
Servo myservo1; 
Servo myservo2; 

//temp sensor 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  
  Serial.begin(115200);
  
  dht.begin();
  
  MQTT_connect();
  
  //attach servo motors
  myservo1.attach(servoPin1); // door 
  myservo2.attach(servoPin2); //window
  

  //Set input and outputs
  pinMode(motion1, INPUT);
  pinMode(smokeA0, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  //lights in the house
  pinMode(2,OUTPUT);//bedroom1
  pinMode(5,OUTPUT);//bedroom2
  pinMode(16,OUTPUT);//bathroom
  pinMode(17,OUTPUT);//livingroom1
  pinMode(18,OUTPUT);//livingroom2
  pinMode(19,OUTPUT);//livingroom3
  pinMode(21,OUTPUT);//kitchen
  pinMode(22,OUTPUT);//frontOfHouse1
  pinMode(23,OUTPUT);//frontOfHouse2
  pinMode(25,OUTPUT);//frontOfHouse3
  pinMode(26,OUTPUT);//frontOfHouse4
 
  
  //wifi connection 
  delay(2000);
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to wifi");
    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
      Serial.println("Connected to AWS");
      delay(1000);
      if(0==hornbill.subscribe(TOPIC_NAME, mySubCallBackHandler))
      {
        Serial.println("Subscribe Successfull");
      }
      else
      {
        Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
        while(1);
      }
    }
    else
    {
      Serial.println("AWS connection failed, Check the HOST Address");
      while(1);
    }
    delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
    
//Fucntions that will constantly loop 

 ControlGoogleAssistant();
 
 getFingerprintIDez();
 
 smokeSensor();
 
 MsgRcvdAWS();
 
 if(digitalRead(motion1)== HIGH) 
  {
     digitalWrite(redLed, HIGH);
     digitalWrite(buzzer, HIGH);
     motion = digitalRead(motion1); //PIR sensor pin
     Serial.println("Alarm detected!"); //Send things to serial for handy dandy info
     Serial.print("motion ");
     Serial.println(motion);
     Serial.print("smoke ");
     Serial.println(smoke);
     ifttt(); //Tell IFTTT that intruder detected
     
     //Pulbish message to IOT Core
     sprintf(payload,"1");
     if(aws.publish("smoke",payload) == 0)
     {        
      Serial.print("Publish Message:");
      Serial.println("Success\n");
      Serial.println(payload);
     }
     else
     {
      Serial.println("Publish failed");
     }
     
  } 
  else 
  {
    Serial.println("no trigger"); //enable for debugging of no event being triggered
  }
}
