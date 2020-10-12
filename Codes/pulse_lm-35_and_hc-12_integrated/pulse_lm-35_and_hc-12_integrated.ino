#include <SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.  

//HC-12 sensor
SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin

// temp sensor:
int sensorPin = A0;

// pulse sensor:
const int PulseWire = 1;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
char buf[15];                              
PulseSensorPlayground pulseSensor;

void setup() 
{
  Serial.begin(9600); // Serial port to computer
  HC12.begin(9600); // Serial port to HC12
  // heartbeat sensor
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) 
   {
    Serial.println();  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

void loop() 
{
  //temp sensor:
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0 / 1024.0; // converter
  int temp = voltage * 100; // conver float to int
  sprintf(buf, "Temp sensor: %d °C\r\n", temp); // send string;
  HC12.write(buf); // Send that data to HC-12
  
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int" .. "myBPM" hold this BPM value now. 
  if (pulseSensor.sawStartOfBeat()) 
  {                                             
     sprintf(buf, "BPM: %d \r\n", myBPM); // send string; 
  }

  //sending data to HC-12:
  HC12.write(buf); // Send that data to HC-12
  delay(3000);
}
