#include <AWS_IOT.h>
#include "ArduinoJson.h"
AWS_IOT aws;

char HOST_ADDRESS[]="a3v4cms691n0e7-ats.iot.us-east-1.amazonaws.com";
char CLIENT_ID[]= "add your client id here";
char TOPIC_NAME[]= "Add your topics here";

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

void MsgRcvdAWS() {

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
                if (value == 600){ // light on / off
                   Serial.print("inside if statement light is on .");
                    digitalWrite(LED, HIGH);
                } else if (value == 500){
                   Serial.print("inside if statement light is off .");
                    digitalWrite(LED, LOW); 
                    handleDoor();  
                } else if (value == 400){
                   Serial.print("inside if statement door is open ."); 
                    handleDoor();          
                } else if (value == 300){
                   Serial.print("inside if statement door is closed .");
                    handleDoor(); 
                } else if (value == 200){
                   Serial.print("inside if statement window is open  .");
                     handleWindow();         
                } else if (value == 100){
                   Serial.print("inside if statement window is closed ."); 
                    handleWindow();     
                }else{
                  Serial.print("nothing recieved .");
                }
                
//      //  Serial.print("Received Message:");
//       // Serial.println(rcvdPayload);
//         if( rcvdPayload ==  "{\"test_data\":\"500\"}")
//         {
//          Serial.println("got message");
//          Serial.println(rcvdPayload);
//          Serial.println("led onnnnnnnnn");
//         }
//         else
//         {
//          Serial.print("Received Message111:");
//          Serial.print("string not deliver ");
//         // Serial.println(rcvdPayload);
//           Serial.println(payload);
         }
    }
    if(tick >= 5)   // publish to topic every 5seconds
    {
        
       float temp = dht.readTemperature(); // return temperature in °C
       float humidity = dht.readHumidity();// return humidity in %
       tick=0;
        // check whether reading was successful or not
        if(temp == NAN || humidity == NAN){ // NAN means no available data
          Serial.println("Reading failed.");
        }
        else{
          //create string payload for publishing
          String temp_humidity = "Temperature: ";
          temp_humidity += String(temp);
          temp_humidity += "°C Humidity: ";
          temp_humidity += String(humidity);
          temp_humidity += " %";
          char payload[40];
          temp_humidity.toCharArray(payload, 40);
          Serial.println("Publishing:- ");
          Serial.println(payload);
           if(aws.publish(MQTT_TOPIC, payload) == 0){// publishes payload and returns 0 upon success
            Serial.println("Success\n");
          }
          else{
            Serial.println(" Publish Failed!\n");
          }
        } 

    vTaskDelay(1000 / portTICK_RATE_MS); 
    tick++;   
  }  
}
