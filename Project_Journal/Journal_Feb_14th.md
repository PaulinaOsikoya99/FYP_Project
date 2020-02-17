<img align="left" width="250" height="200" src="/gmit.png">

<h1 align="right"><b>FYP Project</h1>
<h2 align="right">Engineering Journal</h2>
<h2 align="right">Date:14 Feburary 2020</h2>

<p>&nbsp;</p>

### Tasks
 *For this week, I set out to accomplish the following tasks and so far I hope to accomplish the following tasks:*
 
- [x] Testing the sensors for my project 
- [x] investigating why the fingerprint is not working 
- [x] Setting up MQTT between the Raspberry pi and the esp32

### Reflection
<p>I believe this week i was able o get a few things accomplished. I was able to check all of my sensors and test to see if they were in working order. I was able to spot on time that there was an issue with the fingerprint sensor for my home automation system and I am actively working on solving the issue. I was able to set MQTT communication on the raspberry pi and I am now working on getting it set up with the ESP 32 and also working towards setting up the fingerprint sensor on the raspberry pi </p>
<p></p>

### Issues and Solutions
 *For this week, this was the following issues I encountered:*

The fingerprint sensor from Grove ltd. needs 5v to power the sensor and the esp32 has both the 5v and 3.3v power rails and when I tried to connect the fingerprint sensor to the 5v power source it didn't power and I could find much documentation concerning fixing the power issue.
However, in my project, I am using the development board Raspberry Pi 4 and I saw on the web that there is much more documentation for integrating the fingerprint sensor with the pi 
So, in conclusion, I decided to begin the3 integration of the fingerprint sensor on the pi 4 and still have it communicate with the other sensor on the ESP32 via MQTT.

#### Next Steps for this week :

- [ ] Setting up MQTT between the Raspberry pi and the esp32

<p>During the lab class for project, I managed to set up the MQTT broker on the raspberry pi and I will now work on getting it integrated with the ESP 32.</p>

- [x] Solving the fingerprint sensor problem

<p>I think the next steps that I will take with the fingerprint sensor will be to try set it up on the raspberry pi and then test its functionality on that platform and finally have the fingerprint sensor on the pi communicate with the ESP 32 via MQTT</p>



