#define BLYNK_PRINT SwSerial
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

char auth[] = "tJ5y3HY03zV4vi31dGaL2HVsBOdm-VkC";

WidgetLCD lcd(V1);
WidgetMap myMap(V0);
String GPSLabel = "BLYNK";

BlynkTimer timer;

int Signal;
int S;
WidgetLCD lcd1(V4);

static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS)
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps;                             // The TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin);     // Serial connection to the GPS module

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  int analogValue = analogRead(A0); //reading the sensor on A0
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;
  Blynk.virtualWrite(V5, celsius);
}
void setup()
{
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  ss.begin(GPSBaud);
  Blynk.begin(Serial, auth);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, pulseSen);
  timer.setInterval(1000L, periodicUpdate);
  timer.setInterval(60*1000, reconnectBlynk);
}

void periodicUpdate() {
  String line1, line2;
  //LCD
  lcd.clear();
  if (gps.location.isValid() && (gps.location.age() < 3000)) {
    //position current
    line1 = String("lat: ") + String(gps.location.lat(), 6);
    line2 = String("lng: ") + String(gps.location.lng(), 6);
    lcd.print(0, 0, line1);
    lcd.print(0, 1, line2);
    //update location on map
    myMap.location(2, gps.location.lat(), gps.location.lng(), GPSLabel);
  } else {
    //position is lost
    lcd.print(0, 0, "GPS lost");
  }
}

void updateGPS() {
  //read data from GPS module
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
}

void reconnectBlynk() {
  if (!Blynk.connected()) {
    Serial.println("Lost connection");
    if(Blynk.connect()) Serial.println("Reconnected");
    else Serial.println("Not reconnected");
  }
}

void pulseSen()
{
  lcd1.clear();
  Signal = analogRead(A1);
  S = (Signal/8);
  lcd1.print(0,0,S);
  
}

void loop()
{
  Blynk.run();
  timer.run();
  if(Blynk.connected()) 
  { 
    Blynk.run(); 
  }
  updateGPS();
}
