#include <AWS_IOT.h>
#include <WiFi.h>
#include "ArduinoJson.h"
AWS_IOT hornbill;

char WIFI_SSID[]="iPhone";
char WIFI_PASSWORD[]="your password ";
char HOST_ADDRESS[]="your host address";
char CLIENT_ID[]= "abcdefg";
char TOPIC_NAME[]= "humid";

int LED = 33;
int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



void setup() {
    Serial.begin(115200);
    delay(2000);
      pinMode(LED, OUTPUT);
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // wait 5 seconds for connection:
        delay(5000);
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

    if(msgReceived == 1)
    {
        msgReceived = 0;
        Serial.println("Parsing start: ");
        //  char JSONMessage[512] = ;

         StaticJsonBuffer<300> JSONBuffer;                         //Memory pool
         JsonObject& parsed = JSONBuffer.parseObject(rcvdPayload); //Parse message

         if (!parsed.success()) {   //Check for errors in parsing
 
            Serial.println("Parsing failed");
            delay(5000);
             return;
 
            }

            int value = parsed["test_data"];  
             Serial.print("Sensor value: ");
             Serial.println(value);
        if (value == 500){
           Serial.print("inside if statement led is on .");
            digitalWrite(LED, HIGH);
        } else if (value == 409){
           Serial.print("inside if statement led is off .");
            digitalWrite(LED, LOW);   
        }else{
          
        }
      //  Serial.print("Received Message:");
       // Serial.println(rcvdPayload);
         if( rcvdPayload ==  "{\"test_data\":\"500\"}")
         {
          Serial.println("got message");
          Serial.println(rcvdPayload);
          Serial.println("led onnnnnnnnn");
         }
         else
         {
          Serial.print("Received Message111:");
          Serial.print("string not deliver ");
         // Serial.println(rcvdPayload);
           Serial.println(payload);
         }
    }
    if(tick >= 5)   // publish to topic every 5seconds
    {
        tick=0;
        sprintf(payload,"Temperature: 1%d", msgCount++);
        if(hornbill.publish(TOPIC_NAME,payload) == 0)
        {        
            Serial.print("Publish Message:");
          //  Serial.println(payload);
        }
        else
        {
            Serial.println("Publish failed");
        }
    }  
    vTaskDelay(1000 / portTICK_RATE_MS); 
    tick++;
}
