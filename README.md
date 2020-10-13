# Soldiers Health Monitoring and Position Tracking System

    The Soldier Health Monitoring and Position Tracking System allows the military personnel 
    to track the current GPS position of a soldier and also checks the health status including 
    body temperature and heartbeat of a soldier.

### Introduction

In today’s era, enemy warfare is an important factor in any nation’s security. The national security mainly depends on Army, Navy and Air Force. The most important and vital role is played by the soldiers. So, in order to protect soldiers there should be some technology too. So, to support this idea, in this project I have come up with a system which will track soldiers position as well as give their health status during a operation/mission.

##### This system in particular will be useful for individuals, who involve in missions or in special operations.

### METHODOLOGY

#### Components Required
  * [Arduino UNO](#arduino-uno)
  * [Temperature Sensor](#Temperature-sensor)
  * [Pulse Sensor](#pulse-sensor)
  * [GPS Senor](#gps-sensor)
  * [HC-12](#hc-12_sensor)
  * 9V 3A Battery
  * Breadboard and jumper wires

#### Components Descriptions

* #### Arduino UNO
The Arduino UNO is an open-source microcontroller board based on the Microchip ATmega328P microcontroller and developed by Arduino.cc. The board is equipped with sets of digital and analog input/output (I/O) pins that may be interfaced to various expansion boards (shields) and other circuits. The board has 14 Digital pins, 6 Analog pins, and programmable with the Arduino IDE (Integrated Development Environment) via a type B USB cable. It can be powered by a USB cable or by an external 9 volt battery, though it accepts voltages between 7 and 20 volts.

* #### Temperature Sensor
LM35 is a precession Integrated circuit Temperature sensor, whose output voltage varies, based on the temperature around it. It is a small and cheap IC which can be used to measure temperature anywhere between -55°C to 150°C.

* #### Pulse Senor
Pulse Sensor is a well-designed plug-and-play heart-rate sensor for Arduino. It can be used by students, artists, athletes, makers, and game & mobile developers who want to easily incorporate live heart rate data into their projects. The sensor clips onto a fingertip or earlobe and plugs right into Arduino. It also includes an open-source monitoring app that graphs your pulse in real time. It operating voltage is 3.3V – 5V.
      The Pulse Sensor can be connected to Arduino, or plugged into a breadboard. The front of the sensor is the pretty side with the Heart logo. This is the side that makes contact with the skin. On the front you see a small round hole, which is where the LED shines through from the back, and there is also a little square just under the LED. The square is an ambient light sensor, exactly like the one used in cellphones, tablets, and laptops, to adjust the screen brightness in different light conditions. The LED shines light into the fingertip or earlobe, or other capillary tissue, and sensor reads the light that bounces back. The back of the sensor is where the rest of the parts are mounted.

* #### GPS Sensor
GPS sensors are receivers with antennas that use a satellite-based navigation system with a network of 24 satellites in orbit around the earth to provide position, velocity, and timing information. The NEO-6MV2 is a GPS module used for navigation. The module simply checks its location on earth and provides output data which is longitude and latitude of its position. It is from a family of stand-alone GPS receivers featuring the high performance u-blox 6 positioning engine. These flexible and cost effective receivers offer numerous connectivity options in a miniature (16 x 12.2 x 2.4 mm) package. The compact architecture, power and memory options make NEO-6 modules ideal for battery operated mobile devices with very strict cost and space constraints. Its Innovative design gives NEO-6MV2 excellent navigation performance even in the most challenging environments.

* #### HC-12 Sensor
HC-12 wireless serial port communication module is a new-generation multichannel embedded wireless data transmission module. The HC-12 is a half-duplex 20 dBm (100 mW) transmitter paired with a receiver that has -117 dBm (2×10-15 W) sensitivity at 5000 bps. Paired with an external antenna, these transceivers are capable of communicating up to and possibly slightly beyond 1 km in the open and are more than adequate for providing coverage throughout a typical house. Its wireless working frequency band is 433.4-473.0MHz, multiple channels can be set, with the stepping of 400 KHz, and there are totally 100 channels.

#### WORKING
   This system enables GPS tracking of these soldiers. It is possible by *S-Health*. The S-Health can be defined as mobile computing, medical sensors and communication technologies for health care. In this system, smart sensors such as (Temperature sensor, Pulse sensor, Wireless comm. sensor) are attached to the body of the soldiers in order to have their health status and their position in the war field.

###### The hierarchy of obtaining data from the soldier is divided into three segments:
   1. First Unit (Soldiers S-Health System)
   2. Second Unit (Squadron leader)
   3. Third unit (Control room)

All the data collected from the S-Health system (of each individual soldier) is sent to the Squadron leader of the second unit via a wireless sensor module (HC-12 transmitter). The same procedure is repeated and the data from the second unit (including the data of the each soldiers and the squadron leader) is sent to the third unit...i.e. Control Room, where it is all about collecting all the data at one place so if any soldier is in trouble then he/she can be tracked down and help can be sent for the individual.

#### APPLICATIONS
   * #### Defence Forces
     ###### The project can be implemented in battle field or high altitude areas where health and location of soldiers is the most basic information which should be   known to the control room.

   * #### Civilians
     ###### This project can also be utilized by individuals who work in remote areas or high altitudes wherein the most basic information should be known to someone dear to them or their guardian’s.

#### FUTURE SCOPE
   * #### Algorithms and Models
   ###### These can be implemented in the future so as to have more precision in the data collected.

   * #### Data Management 
   ###### This can be implemented in the future so as to handle to the huge data that is incoming from the soldiers.

   * #### Cyber security
   ###### This can be implemented in the future so as to secure the RF channel from where the all the data has to transmitted and received.

   * #### Power Management
   ###### This can be implemented in the near future so as we have reduced the power consumption and the total efficiency of the whole system.
