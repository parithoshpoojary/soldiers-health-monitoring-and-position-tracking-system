#include <SPI.h>
#include <LoRa.h>
 
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop() {
  char line[200];
  char* LoRaData = line;
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    // received a paket
    Serial.println("");
    Serial.println("...................................");
    Serial.println("Received packet: ");
    
    // read packet
    while (LoRa.available()) 
    {
      // LoRaData = LoRa.readString();
      LoRaData = (char)LoRa.read();
      for(int i = 0, j; LoRaData[i]!= '\0' ;++i)
      {
        while(!(LoRaData[i] >= 'a' && LoRaData[i] <= 'z') && !(LoRaData[i] >= 'A' && LoRaData[i] <= 'Z') && !(LoRaData[i]=='\0'))
        {
           for(j = 1; LoRaData[j]!='\0'; ++j)
           {
             LoRaData[j] = LoRaData[j+1];
           }
           LoRaData[j] = '\0';
        }
      }
      Serial.print(LoRaData);
    }
  }
}
