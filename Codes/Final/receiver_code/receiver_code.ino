#include <SoftwareSerial.h>
SoftwareSerial HC12(6,7); // HC-12 TX Pin, HC-12 RX Pin
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
}
void loop() {
  while (HC12.available()) {        // If HC-12 has data
    //Serial.println();
    Serial.write(HC12.read());      // Send the data to Serial monitor
    //Serial.println();
  }
  while (Serial.available()) {      // If Serial monitor has data
    //Serial.println();
    HC12.write(Serial.read());      // Send that data to HC-12
    //Serial.println();
  }
}
