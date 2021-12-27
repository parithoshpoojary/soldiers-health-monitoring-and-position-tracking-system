# Soldiers Health Monitoring and Position Tracking System

The Soldier Health Monitoring and Position Tracking System allows the military personnel to track the current GPS position of a soldier and also checks the health status including body temperature and heartbeat of a soldier.

### Introduction

  In this modern era, enemy warfare is one of the most significant factors in any nation’s security. Nation’s security mainly depends on these three specialized uniformed services: The Army, the Air Force, and the Navy. Soldiers are a very essential part of these security systems. During any special operation or mission that’s been carried out by these services, soldiers involved tends to get injured or get lost on the battlefield. As the soldier plays a significant role in national security, we cannot afford to let them get lost, or have any delayed medics reach the injured ones. So, to protect these soldiers we should have some technology that monitors and tracks the soldiers in real-time and help minimize the time of search operation, and rescue operation efforts of the control unit. 

So, to support this idea, the project presents an effectual system that is capable of monitoring the health vitals of soldiers and at the same time able to record their current position using necessary sensors. The data collected from the sensors are then transmitted to the next level of the hierarchy using wireless RF modules. This system enables the control room unit to track the location and monitor the health vitals of the soldiers constantly using the wireless body sensor network, and the GPS receiver at frequent intervals. Arduino associated with the control room constantly monitors the data received from the different subsystems of the proposed design and triggers a warning if any values cross the set threshold values. Live health monitoring and position tracking of the soldiers will ensure that they are safe on the battlefield and if any abnormalities are found in the values received to the control unit node, they make sure that relief is sent from the control unit node or the squadron leader’s node within a minimum amount of time.

##### This system in particular will be useful for individuals, who involve in missions or in special operations.

### Extra libraries
The extranal librarires used in the project.

  - TinyGPS++ : https://github.com/mikalhart/TinyGPSPlus
  - PulseSensorPlayground : https://github.com/WorldFamousElectronics/PulseSensorPlayground
  - LoRa: https://www.arduino.cc/reference/en/libraries/lora/

  ###### Clone the repos and add the folder to the *libraries* folder in Arduino IDE.

### METHODOLOGY

#### Components Required
  * Arduino UNO (x3)
  * Temperature Sensor - LM35 (x2)
  * Pulse Sensor - RC-A-4015 (x2)
  * GPS Receiver - Neo-6M (x2)
  * HC-12 RF module
  * SX-1278 RF LoRa module
  * 9V 3A Battery
  * Breadboard and jumper wires

#### Components Descriptions

* #### HC-12 Sensor
HC-12 wireless serial port communication module is a new-generation multichannel embedded wireless data transmission module. The HC-12 is a half-duplex 20 dBm (100 mW) transmitter paired with a receiver that has -117 dBm (2×10-15 W) sensitivity at 5000 bps. Paired with an external antenna, these transceivers are capable of communicating up to and possibly slightly beyond 1 km in the open and are more than adequate for providing coverage throughout a typical house. Its wireless working frequency band is 433.4-473.0MHz, multiple channels can be set, with the stepping of 400 KHz, and there are totally 100 channels.

* #### SX-1278
The SX1278 transceiver feature the LoRa long range modem that provides ultra-long range spread spectrum communication and high interference immunity whilst minimizing current consumption. Using Semtech’s patented LoRa modulation technique SX1278 can achieve a sensitivity of over -148dBm using a low cost crystal and bill of materials. The high sensitivity combined with the integrated +20dBm power amplifier yields industry leading link budget making it optimal for any application requiring range or robustness. LoRa also provides significant advantages in both blocking and selectivity over conventional modulation techniques, solving the traditional design compromise between range, interference immunity and energy consumption.

#### WORKING
   The system has two sections, hardware and software. The system consists of 3 nodes i.e Soldier’s node, Squadron leader’s node, and Control unit node. At all the nodes Arduino constantly monitors and records data from the several sensors connected to the system, and communicates with other nodes using wireless RF modules present in the system. 

###### The hierarchy of obtaining data from the soldier is divided into three segments:
   1. Soldier's Node - Level 1
   2. Squadron's Node - Level 2
   3. Control unit Node - Level 3

  <p align="center">
    <img width="400" height="300" src="https://user-images.githubusercontent.com/43223792/128725212-935d9508-f457-4ec8-bec7-f8699636639c.png">
  </p>
  
  The block diagram below explains how the nodes and all the internal sensors are connected.
  
  <p align="center">
    <img width="500" height="600" src="https://user-images.githubusercontent.com/43223792/128724870-6c4c61db-dd4f-469c-a0f7-886dcfbaf592.png">
  </p>
 
 Circuit Diagram for the project.
 <p align="center">
    <img src="https://user-images.githubusercontent.com/43223792/147447506-192172a8-2695-4708-8c3d-b32fb00e8968.png">
  </p>
 

A breif explaination of all the nodes are given below:
### Soldier's Node
  This node comprises of body sensor networks (BSN) i.e a temperature sensor and a pulse sensor. These sensors are used to monitor the health vitals of soldiers. Temperature sensor (LM35) is used for monitoring the temperature of the soldier and his surrounding environment, and the pulse sensor (RC-A-4015) monitors the pulse rate of the soldiers as beats per minute (BPM). If there is any variance among the sensed values and the defined threshold values, then it is considered as an exigency. Along with the BSN, a GPS receiver is also added to the node, so as to locate/monitor the soldier’s position. All the data incoming from the sensors are processed and recorded by the micro controller and sent via the wireless RF transceiver module present in the system to the next node i.e Squadron leader’s node. The RF module used in the soldier’s node is HC12, as the communication range between soldier’s node and the squadron leader’s node is short as they are hardly few kms apart.   
Additionally, to connect this node to the internet, we use the Blynk application. With the help of a USB and the laptop, we are able to connect this node to the internet. While this node is connected to the internet, the data from the sensors are uploaded to the Blynk cloud, and concurrently sent to the dashboard created to interface with the project via the cloud.


### Squadron's Node
  This node also comprises of body sensor networks (BSN) i.e a temperature sensor and a pulse sensor. These sensors are used to monitor the health vitals of the Squadron leader. Temperature sensor (LM35) is used for monitoring the temperature of the squadron leader and his surrounding environment, and the pulse sensor (RC-A-4015) monitors the pulse rate of the squadron leader as BPM. If there is any variance among the sensed values and the defined threshold values, then it is considered as an exigency. All the data coming from the sensors are processed and recorded by the micro controller and sent via the wireless RF transceiver module present in the system to the final node i.e Control unit node. Before sending the recorded data, foremost thing done by this node is receiving the data sent from the soldier’s node through the HC12 module present in the system. Subsequently after receiving the soldier’s data, both the data combined together i.e soldier’s data and the squadron leader’s data are sent through the RF module present in the system. Now, for sending the data to the control unit node, which is very far away from the squadron leader’s node, we use wireless RF Long Range (LoRa) module i.e SX1278, using this RF module we are easily able to send the data of both the soldier’s and the squadron leader to the control unit node which is up to ~ (25kms - 30kms) apart from each other.

### Control Unit Node
  This node includes the wireless RF LoRa module i.e SX1278, where it receives the data of both nodes i.e soldier’s and squadron leaders, from the squadron leader’s node. This node is just about monitoring, storing, and analyzing the received data from the other two node i.e Soldier’s node and the squadron leader’s node.
Additionally, the control unit node is provided with an extra feature, where they can monitor soldier’s directly through the internet using a graphical interface/dashboard. This is possible using the blynk application on the mobile phone available at control unit node, provided the soldier’s module is also connected to the internet.


### APPLICATIONS
   * #### Defence Forces
     ###### The project can be implemented in battle field or high altitude areas where health and location of soldiers is the most basic information which should be   known to the control room.

   * #### Civilians
     ###### This project can also be utilized by individuals who work in remote areas or high altitudes wherein the most basic information should be known to someone dear to them or their guardian’s.

### Conclusion and Future Scope
  Soldier’s being an important part of our nation’s security, their health vitals and their location needs to be regularly monitored for their safety and their efficient working. Wireless communication with IoT makes the whole experience of monitoring soldiers health vitals and their location, smart efficient and fast. Technologies like IoT has fundamentally reformed the way we live and work, it has made our life easier. Above proposed system not only monitors real-time health and location data of the soldiers but also provides necessary data to help us determine the last position and the health data of the soldiers if he gets lost, so as to track him down and send help. This system increases the efficiency of the soldiers working in the field and also reduces the effort of search and rescue operation led by control room unit at the same time. All in all, the system being compact and less in weight makes it more ideal for the soldier’s and the squadron leaders to carry the system with them, which in turns helps the control unit node to monitor their data of in real-time, even if they are kilometers apart. 

There is an enormous horizon of possibilities which could be offered - new designs, advanced system could be introduced to improve the conditions and efficiency of the system, and by introducing AI/ML algorithms we can predict out in near future if any soldier might require medical attention beforehand, other than this it can also predict whether a component or sensor might need attention or replacement. Other improvements that can be included is implementing advanced security protocols/techniques on the wireless RF modules so as to make the whole process of transmission and receiving sensors data more secure and reliable.

## Contributing

To contribute to the repository, open an issue or a pull request.
