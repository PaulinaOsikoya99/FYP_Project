<img align="left" width="250" height="200" src="./ml.png">

<h1 align="right"><b>FYP Project</h1>
<h2 align="right">Machine Learning(ML)</h2>
<h2 align="right">Date:11 Feburary 2020</h2>
  
From Machine learning, I used the raspberry pi 4 to this. On the pi 4, I had a  pi camera which ran a facial recognition script and had a live steam streaming to localhost.this feature acted as camera surveillance for my house. 
<br>
<br>
Unfortunately during Cov-19 in quarantine, my pi 4  fried and was kaput and I wasn't able to progress further with the development of the feature that I wanted to add because during that time there was no Available pi 4 to order from Irish Vendor and the next delivery date would have been way past my demo date so, I made the decision to leave out this feature but am happy to answer on it if I am asked. 
<br>
<br>
The feature was real-time facial recognition using AWS Kinesis on AWS and utilizing a lambda function to kick off an AWS SNS action which would use the SMS protocol to send an SMS to my phone if someone was near the door. <br>
<br>
The proximity of the person near the door would be tracked by a PIR proximity sensor which is visible in the code that I wrote in the src section of my GitHub. here when the person was in a certain proximity to my house an integer value would be published to the tope door. <br>
<br>The pi which had the pi camera would have been also subscribed to the topic and would also have publishing writes. So when this integer value is received in a JSON string from the ESP32 the pi 4 would then invoke AWS Kinesis and send the messages. <br>
<br>However, I still researched this area and am fully confident on how to execute this feature if I had the pi 4 to test on
