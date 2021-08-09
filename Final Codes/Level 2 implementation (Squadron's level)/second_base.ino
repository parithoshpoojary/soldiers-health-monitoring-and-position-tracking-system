#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>

#define USE_ARDUINO_INTERRUPTS false    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

SoftwareSerial HC12(6,7); // HC-12 TX Pin, HC-12 RX Pin

String inc;


int val;
int tempPin = A0;                //TempSensor connected to ANALOG PIN 0.

const int PulseWire = A1;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 1.
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                             
PulseSensorPlayground pulseSensor;
 
void setup() 
{    
  Serial.begin(9600);
  HC12.begin(9600);                              // Serial port to HC12
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);              //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
  while (!Serial);
  Serial.println("LoRa Sender");
 
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  if (pulseSensor.begin()) 
   {
    Serial.println();                           //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}
 
void loop() 
{
  val = analogRead(tempPin);                   //Reads the Temperature value from the sensor.
  float temp = ((val/1024.0)*5000);
  float cel = temp/10;                       //Converts the temo to Celsius.
  float farh = (cel*9)/5 + 32;                 //Converts the temp value to Fahrenheit.

  //int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
  int myBPM = 70.0;
  if (pulseSensor.sawStartOfBeat()) 
  {                                   // Constantly test to see if "a beat happened". 
  }

  Serial.println("Sending packet: ");
 
  // send packet
  LoRa.beginPacket();                         //Starts the sequence of sending a packet.
  LoRa.print("Soldier's Data:");
  while(HC12.available())                     //Checks if there's data in HC-12.
  {
    inc = (String)LoRa.write(HC12.read());                
  }
  LoRa.print(inc);
  LoRa.print("\n");
  LoRa.print("Squadron's Data:");
  LoRa.print(" Temperature:");
  LoRa.print(cel);                      //Sending the Temperature data of the Squadron.
  LoRa.print("C");
  LoRa.print("    BPM:");
  LoRa.print(myBPM);                    //Sending the BPM data of the Squadron.
  
  Serial.print("Sent the Soldier's data and the Squadron's data.");     //Prints the statement on the Serial monitor.
  Serial.println(""); 
  
  LoRa.endPacket();       //End's the sequence of sending a packet.
  
  delay(1000);
}
