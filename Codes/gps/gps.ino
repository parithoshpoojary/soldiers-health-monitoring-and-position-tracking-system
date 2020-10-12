#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 4, TXPin = 3;// Here we make pin 4 as RX of arduino & pin 3 as TX of arduino 
static const uint32_t GPSBaud = 9600;

double latitude;
double longitude;

//HC-12 sensor
SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin

SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;

char buf[500]; 

void setup()
{
  Serial.begin(9600);
  HC12.begin(9600); // Serial port to HC12
  ss.begin(GPSBaud);
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      displayInfo();
    }

  /*if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }*/
}

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
