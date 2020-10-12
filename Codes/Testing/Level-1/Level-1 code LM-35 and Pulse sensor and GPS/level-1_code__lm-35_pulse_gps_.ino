#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/*gps sensor*/
static const int RXPin = 4, TXPin = 3;// Here we make pin 4 as RX of arduino & pin 3 as TX of arduino 
static const uint32_t GPSBaud = 9600;


/*pulse sensor*/
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.  
   
double latitude;
double longitude;

/*HC-12 sensor*/
SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin

/*gps sensor*/
SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;

/*temp sensor*/
int sensorPin = A0;

/*pulse sensor*/
const int PulseWire = 1;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 



char buf[500];  
                          
PulseSensorPlayground pulseSensor;


void setup() 
{
  /*Serial port to computer*/
  Serial.begin(9600); 
  
  /*Serial port to HC12*/
  HC12.begin(9600); 

  /*gps sensor*/
  ss.begin(GPSBaud);
  
  /*pulse sensor*/
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
   /*gps sensor*/
 while (ss.available() > 0)
  {
    Serial.print((gps.encode(ss.read())));
    if (gps.encode(ss.read()))
    {
      displayInfo();
    }
  }
  
  /*temp sensor*/
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0 / 1024.0; // converter
  int temp = (voltage * 100)- 20; // conver float to int
  sprintf(buf, "Temp sensor: %d °C\r\n", temp); // send string;
  HC12.write(buf); // Send that data to HC-12

  /*pulse senosr*/
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int" .. "myBPM" hold this BPM value now. 
  if (pulseSensor.sawStartOfBeat()) 
  {                                             
     sprintf(buf, "BPM: %d \r\n", myBPM); // send string; 
  }
  HC12.write(buf); // Send that data to HC-12

 
  delay(3000);
}

/*gps sensor display function*/
void displayInfo()
{
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  { 
    latitude = gps.location.lat();
    char str_lat[10];
    dtostrf(latitude,4,6,str_lat);
    longitude = gps.location.lng();
    char str_lon[10];
    dtostrf(longitude,4,6,str_lon);
    sprintf(buf, "Location: %s ; %s\r\n", str_lat, str_lon); // send string;
    HC12.write(buf);     
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
  Serial.println();
}
