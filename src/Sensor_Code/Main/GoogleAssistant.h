#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "add username here"
#define AIO_KEY         "add your key here"

uint32_t x=0;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TOPICS TO SUBSCRIBE TO:
// feeds/Lights
// feeds/bedroom1
// feeds/bathroom
// feeds/livingroom
// feeds/frontOfHouse
// feeds/door
// feeds/happy
// feeds/kitchen
// feeds/window
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

Adafruit_MQTT_Subscribe Lights = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Lights");
Adafruit_MQTT_Subscribe bedroom1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/bedroom1");
Adafruit_MQTT_Subscribe bathroom = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/bathroom");
Adafruit_MQTT_Subscribe livingroom = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/livingroom");
Adafruit_MQTT_Subscribe frontOfHouse = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/frontOfHouse");
Adafruit_MQTT_Subscribe door = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/door");
Adafruit_MQTT_Subscribe happy = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/happy");
Adafruit_MQTT_Subscribe kitchen = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/kitchen");
Adafruit_MQTT_Subscribe window = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/window");

void ControlGoogleAssistant() {
 MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    
        if (subscription == &bedroom1) {
          Serial.print(F("Got from bedroom feed: "));
          Serial.println((char *)bedroom1.lastread);
           if (!strcmp((char*) bedroom1.lastread, "ON"))
          {
            digitalWrite(2, HIGH);
            digitalWrite(5, HIGH);
          }
          else
          {
            digitalWrite(2, LOW);
            digitalWrite(5, LOW);
          }
        }
    
         if (subscription == &door) {
          Serial.print(F("Got from door feed: "));
          handleDoor();
        }
    
    
       if (subscription == &happy) {
        Serial.print(F("Got from happy mode feed: "));
        Serial.println((char *)happy.lastread);
         if (!strcmp((char*) happy.lastread, "ON"))
        {
           digitalWrite(redLed, HIGH);
        }
        else
        {
           digitalWrite(redLed, LOW);
        }
      }
    
       if (subscription == &kitchen) {
        Serial.print(F("Got from kitchen feed: "));
        Serial.println((char *)kitchen.lastread);
         if (!strcmp((char*) kitchen.lastread, "ON"))
        {
          digitalWrite(21, HIGH);
        }
        else
        {
          digitalWrite(21, LOW);
        }
      }

       if (subscription == &bathroom) {
        Serial.print(F("Got from bathroom feed: "));
        Serial.println((char *)bathroom.lastread);
         if (!strcmp((char*) bathroom.lastread, "ON"))
        {
          digitalWrite(16, HIGH);
        }
        else
        {
          digitalWrite(16, LOW);
        }
      }

       if (subscription == &livingroom) {
        Serial.print(F("Got from livingroom feed: "));
        Serial.println((char *)livingroom.lastread);
         if (!strcmp((char*) livingroom.lastread, "ON"))
        {
          digitalWrite(17, HIGH);
          digitalWrite(18, HIGH);
          digitalWrite(19, HIGH);
        }
        else
        {
          digitalWrite(17, LOW);
          digitalWrite(18, LOW);
          digitalWrite(19, LOW);
        }
      }

       if (subscription == &frontOfHouse) {
        Serial.print(F("Got from frontOfHouse feed: "));
        Serial.println((char *)frontOfHouse.lastread);
         if (!strcmp((char*) frontOfHouse.lastread, "ON"))
        {
          digitalWrite(22, HIGH);
          digitalWrite(23, HIGH);
          digitalWrite(25, HIGH);
          digitalWrite(26, HIGH);
        }
        else
        {
          digitalWrite(22, LOW);
          digitalWrite(23, LOW);
          digitalWrite(25, LOW);
          digitalWrite(26, LOW);
        }
      }
    
     if (subscription == &Lights) {
        Serial.print(F("Got from Lights feed: "));
        Serial.println((char *)Lights.lastread);
         if (!strcmp((char*) Lights.lastread, "ON"))
        {
          digitalWrite(2, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(16, HIGH);
          digitalWrite(17, HIGH);
          digitalWrite(18, HIGH);
          digitalWrite(19, HIGH);
          digitalWrite(21, HIGH);
          digitalWrite(22, HIGH);
          digitalWrite(23, HIGH);
          digitalWrite(25, HIGH);
          digitalWrite(26, HIGH);  
        }
        else
        {
          digitalWrite(2, LOW);
          digitalWrite(5, LOW);
          digitalWrite(16, LOW);
          digitalWrite(17, LOW);
          digitalWrite(18, LOW);
          digitalWrite(19, LOW);
          digitalWrite(21, LOW);
          digitalWrite(22, LOW);
          digitalWrite(23, LOW);
          digitalWrite(25, LOW);
          digitalWrite(26, LOW);   
        }
      }
    
       if (subscription == &window) {
        Serial.print(F("Got from window feed : "));
        handleWindow();
      }
  }
}

void MQTT_connect() {
  
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

 Serial.print("Connecting to MQTT... ");
 uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0){ // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0){
         // try 3 times before giving up 
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
  mqtt.subscribe(&bedroom1);
  mqtt.subscribe(&door);
  mqtt.subscribe(&happy);
  mqtt.subscribe(&kitchen);
  mqtt.subscribe(&Lights);
  mqtt.subscribe(&window);
  mqtt.subscribe(&bathroom);
  mqtt.subscribe(&livingroon);
  mqtt.subscribe(&frontOfHouse);
}
