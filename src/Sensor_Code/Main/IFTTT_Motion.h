#include "Adafruit_MQTT.h"

String result;

void ifttt1()
{
  const char host[ ]        = "maker.ifttt.com";          // maker channel of IFTTT
  const char trigger[ ]     = "add your trigger/s";             
  const char APIKey[ ]      = "add your api key here";      //Your maker key for Webhooks on IFTTT
  Serial.print("Connect to: ");
  Serial.println(host);
  // WiFiClient to make HTTP connection
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
  }
 
// Build URL
  String url = String("/trigger/") + trigger + String("/with/key/") + APIKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);

// Send request to IFTTT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 
  //FYI rn rn is just two new lines to comply with http format
   delay(20);

// Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    }
  Serial.println();
  Serial.println("closing connection");
  Serial.println();
  Serial.println();
  client.stop();  //disconnect
  delay (20000); //This delay here just to stop spamming of emails
 }
  
