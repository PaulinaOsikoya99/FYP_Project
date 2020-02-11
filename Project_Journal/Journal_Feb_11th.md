<img align="left" width="250" height="200" src="/gmit.png">

<h1 align="right"><b>FYP Project</h1>
<h2 align="right">Engineering Journal</h2>
<h2 align="right">Date:11 Feburary 2020</h2>

<p>&nbsp;</p>

### Tasks
 *For this week, I set out to accomplish the following tasks and so far I hope to accomplish the following tasks:*
 
- [x] Testing the sensors for my project 
- [x] investigating why the fingerprint is not working 
- [x] Setting up MQTT between the Raspberry pi and the esp32

### Reflection
<p>I believe this week i was able o get a few thingsaccomplished. I was able to check all of my sensors and test to see if they were in working order. I was able to spot on time that there was an issue with the fingerprint sensor for my home automation system and I am actively working on solving the issue. I was able to set MQTT communication on the raspberry pi and I am now working on getting it set up with the ESP 32 and also working towards setting up the fingerprint sensor on the raspberry pi </p>
<p></p>

### Issues and Solutions
 *For this week, this was the following issues I encountered:*

#### Hardware:
| Name  | Issue  | Solution |
| :------------ |:---------------| :-----|
| Fingerprint Sensor    | During testing the fingerprint sensor I encountered serval issues regarding wiring. When I try to connect the fingerprint sensor to the 3.3v rail the sensor flash intermittently and then opowers off. But, according to too the datasheet, the sensor should stay lit when connected to power  | I tried to connect the sensor to  an external power source such as 5v -9v as it stated in the datasheet that the sensor can handle such voltages but still the same issue persists. I will consult with my supervisor to find a solution to this issue. |

#### Software:
| Name  | Issue  | Solution |
| :------------ |:---------------|:-----|
|Fingerprint Sensor      | while trying to connect the fingerprint sensor to my esp 32 the following error display which stated that the ESP32 does not recognize the object type Software Serial | To provide a solution to the issue I tried to import in the libraries again for the fingerprint sensor and the same issue occurred. Afterwards, I tried to import in the header files and .cpp files separately and tried to compile it again. The library belongs and is best suited to the Arduino because it uses an object type called Software serial which is initialized and is utilized by the Arduino. Another solution that I tried was importing the FPM.h header file to use the hardware serial to connect the fingerprint sensor to the esp32 but the same issue still persists. I will consult with my supervisor to find a solution to this issue. |

#### Next Steps for this week :

- [ ] Setting up MQTT between the Raspberry pi and the esp32

<p>During the lab class for project, I managed to set up the MQTT broker on the raspberry pi and I will now work on getting it integrated with the ESP 32.</p>
- [ ] Solving the fingerprint sensor problem

<p>I think the next steps that I will take with the fingerprint sensor will be to try set it up on the raspberry pi and then test its functionality on that platform and finally have the fingerprint sensor on the pi communicate with the ESP 32 via MQTT</p>


