#include <SoftwareSerial.h>

//HC-12 sensor
SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin

// temp sensor:
int sensorPin = A0;
char buf[15];

void setup() 
{
  Serial.begin(9600); // Serial port to computer
  HC12.begin(9600); // Serial port to HC12
}

void loop() 
{
  //temp sensor:
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0 / 1024.0; // converter
  int temp = voltage * 100; // conver float to int
  sprintf(buf, "Temp sensor: %d °C\r\n", temp); // send string;

  //sending data to HC-12:
  HC12.write(buf); // Send that data to HC-12
  delay(3000);
}
