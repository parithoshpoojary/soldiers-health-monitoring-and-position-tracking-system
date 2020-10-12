//HC-12 messenger receive
// This module RX the GPS coordinates connected to the TX HC12 unit

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);      //RX, TX with HC12 433MHz tranciver

int FUNCLED=13;
int i;                      // count the length of the input string
const int chipSelect = 4;   // CS of SD card

void setup() 
{
  pinMode(FUNCLED, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(1200);
  
  Serial.println("Starting RX mode");  
//======================================================
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    return;   // don't do anything more:
  }
  Serial.println("card initialized.");
//======================================================

}

void loop() 
{  
  if(mySerial.available() > 1)  //Read from HC12 + print on serial monitor / SD card
  {
    digitalWrite(FUNCLED, HIGH);
   
    String inFromAir = mySerial.readString();
    i=i+inFromAir.length();
    
    File dataFile = SD.open("GPSlog.txt", FILE_WRITE);
      if (dataFile)         // if the file is available, write to it
      {
        dataFile.print(inFromAir);
        dataFile.close();
        Serial.print(inFromAir);   // print to the serial port too
      }
      else  {                         // if the file isn't open, pop up an error
          Serial.println("error opening GPSlog.txt");
            }
    delay(200);        
    digitalWrite(FUNCLED, LOW);
  }
  if (i==24) 
  {
    i=0;
    Serial.println(" ");            // set new line at serial monitor
      File dataFile = SD.open("GPSlog.txt", FILE_WRITE);
        if (dataFile)               // if the file is available, write to it
        {
          dataFile.println(" ");    // set new line at TXT file
          dataFile.close();
        }
  }
  delay(20);
}
