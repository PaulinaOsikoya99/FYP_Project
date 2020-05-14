#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "your user name"
#define AIO_KEY         "yor key "

uint32_t x=0;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);        // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Subscribe LED_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LED_Control");
Adafruit_MQTT_Subscribe LED2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led2");

void ControlGoogleAssistant() {
 MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &LED_Control) {
      Serial.print(F("Got: "));
      Serial.println((char *)LED_Control.lastread);
       if (!strcmp((char*) LED_Control.lastread, "ON"))
      {
        digitalWrite(2, HIGH);
      }
      else
      {
        digitalWrite(2, LOW);
      }
    }

     if (subscription == &LED2) {
      Serial.print(F("Got from led 2: "));
      Serial.println((char *)LED_Control.lastread);
       if (!strcmp((char*) LED_Control.lastread, "ON"))
      {
        digitalWrite(4, HIGH);
      }
      else
      {
        digitalWrite(4, LOW);
      }
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
  mqtt.subscribe(&LED_Control);
  mqtt.subscribe(&LED2);
  ControlGoogleAssistant(); 
}
