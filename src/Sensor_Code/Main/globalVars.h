/**************Temperature Sensor**************************/
#define DHT_PIN 33 // pin connected to data pin of DHT11
#define DHT_TYPE DHT11  // Type of the DHT Sensor, DHT11/DHT22

/**************MOTORS, Door, Window**************************/
int servoPin1= 21; //servo motor for door
int servoPin2 = 22; //servo motor for window

/**************Buzzer - events in the House**************************/
int buzzerPin = 15;

/**************red - to acts as a visual to signal events in the House**************************/
int redLed = 13;
int LED = 32;

/**************Smoke Sensor**************************/
int smokeA0 = 4;
int sensorThres = 4094;

/**************Motion PIR Sensor**************************/
int  motion1 = 23;


/**************Lights in the house **************************/
int bedroom1=2;
int bedroom2=5;
int bathroom=16;
int livingroom1=17;
int livingroom2=18;
int livingroom3=19;
int kitchen=21;
int frontOfHouse1=22;
int frontOfHouse2=23;
int frontOfHouse3=25;
int frontOfHouse4=26;
