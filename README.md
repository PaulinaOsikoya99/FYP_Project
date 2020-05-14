<p align="center">
  <img width="200" height="200" src="/gmit.png/">
</p>
 [I'm an inline-style link](https://www.google.com)

<h1 align="left" ><b>FYP Project</b><br><br>Final Year Project<br></h1>

<br>
<br>
<p align="center">
  <img width="200" height="200" src="/house.PNG/">
</p>

<h4 align="left">BEng in Software and Electronic Engineering<br><br>
Student Name: Paulina Osikoya<br>
Student Number: G00348898<br>
Supervisor: Brian O’ Shea<br>
Project Engineering<br>
Year: 4<br>
</h4>

<p>&nbsp;</p>

<h2 align="left"><b>Introduction</b></h2>
<p align="left">Automation is becoming an increasingly massive section and hot topic in today’s IOT sector. From the automation of arduous long complex installations using basic scripts to automating our day today tasks by simply implementing a mechanism that notifies you of your daily tasks to be executed during your set out schedule.</p>
<p align="left">During my Internship my role was centralized around automation and design of software to achieve and reach levels of performance that the world has never witnessed before.For  Final Year Project (FYP) i implemented similar.</p>

<h2 align="left"><b>Project Description</b></h2>
<p align="left">My Final year project is an internet of things (IOT) home automation system. The name of my home automation system is called Hestia. The name is derived from Ancient Greek religion, she was the goddess of ordering of domesticity, the family, and the home hence why I thought the name was befitting for my FYP.</p>
<p align="left">My FYP was developed and deployed on two microcontrollers which were then implemented into a house model designed and created by me and finally integrated with a website using the MEAN stack framework encapsulated inside a AWS EC2 instance.Finally, an experimental aspect of my project was hosting the application on Docker Container Framework using Docker Compose.</p>

<h2 align="left"><b>Project Functionality </b></h2>
<p align="left">My FYP possesses both a creative and technical aspect. </p>
<p align="left">For my project, the development platforms that i was working with were the Esp32 and Raspberry pi 4, I also created an interactive website that displayed the functionality and simulations of my FYP. The website was created by using the following languages HTML, CSS, JavaScript, JQuery, Bcrypt and the MEAN stack.Both the website and the app connected to the Wi-Fi module already integrated on the esp32.</p>
<p align="left">My Home automation system was written in following languages: C, Nodejs, Javascript ,YAML and Python. I used technologies such as GitHub and Trello to commit my code to and online repository that I  have created for the purpose of my FYP. With my IOT Home automation system, the user was able to successfully use voice commands that were picked up by the google assistant to execute specific functions inside the house. The benefits and use cases of my FYP are the following:</p>

- [x] Eliminates the possibility of a burglary happening 
- [x] Delivery Service such as DHL, FedEx no longer have to wait for the owner to be at the house as the user will be able to connect to the delivery man via the video stream mechanism implemented in the house.
- [x] Ease for the Customer -  customer can lock their door or check the status of their door while not being present at the house.
- [x] The user can control the usage of appliances within their home via the app or website
- [x] Fire aware and proof Smoke sensor will alert the Solenoid values to release water to stop a fire from happening 
- [x] Integrated system for the user ( aware of the day ahead of them)

<p align="left">All my hardware elements, digital inputs and outputs and analog inputs (i.e. the green led, the on / off switches and the various sensors ) were connected to both the esp32 and the Raspberry pi 4, which executed the preprogrammed algorithms Iwrote for the functionality of my project. The following Headings bellow explain the Mechanism and the functionality it brings to the IOT Home:
</p>

<h4><b>Sensors:</b></h4>
<p align="left">In my FYP , many sensors were implemented such as proximity , servo motors, humidity , temperature sensor (temp regulation),Speaker: 0.25W, 8 ohms, buzzer  and potentiometer sensors. The function of these sensors were to track temperature, open and close doors, windows, gate and garage door. the buzzer served as alarm system.</p>
<h4><b>Google Assitant:</b></h4>   
<p align="left">Serves a central component that listen for voice commands and executed function by sensors on the esp32 within the house</p>
<h4><b>MQTT:</b></h4>
<p align="left">Is the technology that was used to communicate between the development platforms and the AWS IOT Core.</p>
<h4><b>AWS IOT Core :</b></h4>
<p align="left">Is the technology that was used  as the MQTT Broker that communciates with the ESP32 and the Pi4 in the cloud.</p>
<h4><b>IFTTT:</b></h4>
<p align="left">Is the protocol that was used  to invoke a webhook to communicate with the esp32 to control google assistant and the smoke and motion sensor.</p>
<h4><b>AWS EC2:</b></h4>
<p align="left">Is the technology that was used to host the nodejs website that i created.</p>
<h4><b>NodeJS:</b></h4>
<p align="left">Is the technology that was used to create the nodejs</p>
<h4><b>IP Camera:</b></h4>
<p align="left">Serves a central component that streams video to the website and both app if the user/ home owner is not presently at the house and also integrates machine learning to scan for faces and number plates that are familiar to the house. 
</p>
<h4><b>Open CV:</b></h4>
<p align="left">Is the software that will be for the machine learning and facial recognition </p>
<h4><b>Docker:</b></h4>
<p align="left">The Container Technology Is the technology that was used to create create the container for the different elements in my FYP and Docker compose will be used to help the container communicate with one another
</p>

