// Temp sensor
int val;
int tempPin = A1;


// Heartbeat sensor
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;

void setup() 
{
  // For serial monitor
  Serial.begin(9600);  
  
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
  // Temp sensor
  val = analogRead(tempPin);
  float temp = ((val/1024.0)*5000);
  float cel = (temp/10)- 20;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("C   ");
  Serial.print(farh);
  Serial.print("F");
  Serial.println();
  
  //Heartbeat Sensor

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int" .. "myBPM" hold this BPM value now. 
  if (pulseSensor.sawStartOfBeat()) 
  {                                              // Constantly test to see if "a beat happened". 
    Serial.print("BPM: ");                        // Print phrase "BPM: " 
    Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }

  delay(1000); 
}
