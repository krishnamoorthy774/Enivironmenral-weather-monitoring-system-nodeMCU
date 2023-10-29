# Enivironmenral-weather-monitoring-system-nodeMCU
Reads the Temperature and the Humidity of the environment and can be monitored through our phone using IOT

Install [VScode](https://code.visualstudio.com/) and [PlatfromIO](https://platformio.org/platformio-ide).

The **platformio.ini** file will install the required library for this project.

Download and import the folder into the VScode workspace.

Open" src> **main.cpp** "file. 

Enter your **wifi SSID** and **password**.

connect the sensors and LEDs with the appropirate pins as given in the code.

In this code we are using "**broker.hivemq.com**" as MQTT server 

And publishing the data in the topics "**topic/environment/temperature**" and "**topic/environment/humidity**"

Here,

If ---- temp<24°C ======> Blue LED glows.

If ---- temp>27°C ======> Red LED glows.

If ---- 24°C<temp<27°C ==> Green LED glows.

![39e6fb11-f108-4570-9bc4-613fc4650642](https://github.com/krishnamoorthy774/Enivironmenral-weather-monitoring-system-nodeMCU/assets/133330566/6fe992e0-5310-4a51-941b-c88f1642a8ca)

Download MyMQTT app in your phone and connect with the MQTT server and subscribe to the topics
![2f044b08-ec5e-451d-8214-beb13e54fea5](https://github.com/krishnamoorthy774/Enivironmenral-weather-monitoring-system-nodeMCU/assets/133330566/50d50cc9-4666-4e6e-940c-f9e688253abd) ![67b93829-9fe1-488a-8878-bfa51a36e27c](https://github.com/krishnamoorthy774/Enivironmenral-weather-monitoring-system-nodeMCU/assets/133330566/6a4f5d4a-c533-45e5-b7f6-c403052cda2f)

And you can monitor the temperature and the humidity from your phone.
