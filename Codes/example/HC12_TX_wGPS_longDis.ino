/*HC-12 messenger send/receive

Need to set HC12 tranciver for long range up to 1.8Km
1. Use file : HC-12_ATcmd1.ino
2. File Location : C:\Users\albertor\Desktop\arduino-1.8.2\sketch\HC-12_ATcmd1
3. configure both HC12 Receiver and Transmitter

AT+FU4
AT+B1200
AT+C005 - not must
AT+P8

*/

#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon;   // create variable for latitude and longitude object

SoftwareSerial mySerial(2, 3);      //RX, TX with HC12 433MHz tranciver
SoftwareSerial gpsSerial(10, 11);   // RX, TX with gps sensor connection
TinyGPS gps;    // create gps object

int FUNCLED=13;

void setup() 
{
  pinMode(FUNCLED, OUTPUT);
  
  Serial.begin(9600);     // com with serial monitor
  mySerial.begin(1200);   // com with HC12
  gpsSerial.begin(9600);  // com with gps sensor
  
  Serial.println("setup done");
  Serial.println("Starting GPS TX when lock");  
}

void loop() 
{  
      //  // For testing with serial monitor only
      //  //========================================================================
      //  if(Serial.available() > 0){//Read from serial monitor and send over HC-12
      //    String input = Serial.readString();
      //    mySerial.println(input);   
      //    Serial.println(input); //
      //  }
      // 
      //  if(mySerial.available() > 1){//Read from HC-12 and send to serial monitor
      //    String inFromAir = mySerial.readString();
      //    Serial.println(inFromAir);    
      //  }
      //  delay(20);
      //  //========================================================================

  while(gpsSerial.available())
  { // check for gps data
   if(gps.encode(gpsSerial.read()))
   { // encode gps data
    digitalWrite(FUNCLED, HIGH);
    gps.get_position(&lat,&lon); // get latitude and longitude
    
      //// display position on serial monitor for debug only
      //    Serial.print("Position: ");
      //    Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
      //    Serial.print("lon: ");Serial.println(lon); // print longitude
    
    // send position to HC12 RX unit over the air
    mySerial.print("lat: "); mySerial.println(lat); 
    mySerial.print("lon: "); mySerial.println(lon);
    delay(5000);    // sent position evry t/1000 sec interval >2sec
    digitalWrite(FUNCLED, LOW);
   }
  }
  //-------------------------------------------------------------------------------
  delay(20);
}
