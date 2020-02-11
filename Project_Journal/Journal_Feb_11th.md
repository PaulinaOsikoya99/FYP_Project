<img align="left" width="250" height="200" src="/gmit.png">

<h1 align="right"><b>FYP Project</h1>
<h2 align="right">Engineering Journal</h2>
<h2 align="right">Date:10 Feburary 2020</h2>

<p>&nbsp;</p>

### Tasks
 *For this week, I set out to accomplish the following tasks and so far I hope to accomplish the following tasks:*
 
- [x] Testing the sensors for my project 
- [x] investigating why the fingerprint is not working 
- [ ] Setting up MQTT between the Raspberry pi and the esp32

### Reflection
<p></p>
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
- [ ] Solving the fingerprint sensor problem


