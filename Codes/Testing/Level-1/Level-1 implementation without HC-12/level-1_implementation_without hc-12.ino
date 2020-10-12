//LIBRARIES

#define USE_ARDUINO_INTERRUPTS false              //pulse sensor playground library use this intrerupts and we need it to make it fals in order to be sure that we will not use intrerupts
#include <PulseSensorPlayground.h>                //Pulse Sensor library
#include <TinyGPS++.h>                            //GPS library
#include <SoftwareSerial.h>                       //this library allow to use not dedicated pins for serial comunication,create a sw serial communication

//VARIABLES
//LM35_Temp sensor

const int LM35_sensor_output = A0;                //assigning analog pin A1 to variable 'LM35_sensor_output'
float temp;                                       //variable for temperature in Celsius
float vout;                                       //temporary variable to hold sensor digital reading
int contor_apelare = 0;

//Pulse_sensor_Variables

int Beat_per_minutes = 0;                         //variable for pulse
const int OUTPUT_TYPE = SERIAL_PLOTTER;           //the format of our pulse sensor output, choseed by us to being a serial monitor output0 (not mandatory in our program)

const int Pulse_sensor_output = A1;               //analog Input. Connected to the pulse sensor output
const int treshhold = 550;                        //the trashhold used to helping us reading the pulse waves (heart beat moments)

byte samplesUntilReport;                          //the number of samples remaining to read until we want to report a sample over the serial connection.
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;        //after 10 samples measurment we will calculate the Pulse

//GPS_Variables

double latidude = 0;                              //variable for latitude
double longitude = 0;                             //variable for longitude
int years, mounth,days;                           //variables for date
int hours,minutes,seconds;                        //variables for time
static const uint32_t GPSBaud = 9600;             //define the GPS baudrate for serial communication
static const int RXPin = 4, TXPin = 3;            //asign of the rx and tx pins to the variables RXPin,TXPin for our sw serial communication with GPS
SoftwareSerial gps_bus(RXPin, TXPin);             //the serial connection to the GPS sw serial comm

///FUNCTION OBJECT FOR DEDICATED LIBRARY

PulseSensorPlayground pulseSensor;                //the object created for pulse library
TinyGPSPlus GPS;                                  //the object created for GPS library

//COMMUNICATION SETUP AND OTHERS SETUP

void setup()
{
 pinMode(LM35_sensor_output,INPUT);              // configuring pin A1 as input
 Serial.begin(9600);                             //sets the data rate in bits per second (baud) for serial monitor communication        
 gps_bus.begin(GPSBaud);                         //sets the data rate in bits per second (baud) for sw serial communication with GPS  
 
 // Configure the PulseSensor manager.
 pulseSensor.analogInput(Pulse_sensor_output);   //assignation of the variable to the analog pin(A0) of arduino
 pulseSensor.setSerial(Serial);                  //set the serial monitor to output data
 pulseSensor.setOutputType(OUTPUT_TYPE);         //set the output type (not mandatory for us)
 pulseSensor.setThreshold(treshhold);            //set the trashhold


 samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE; // Skip the first SAMPLES_PER_SERIAL_SAMPLE in the loop().

 
 if (!pulseSensor.begin())                       // Now that everything is ready, start reading the PulseSensor signal.
 {
   Serial.print("Pulse sensor start reading the pulse");
 }
}

//MAIN FUNCTION
void loop()
{
 
 if(contor_apelare == 25)
 {
   vout = analogRead(LM35_sensor_output);
   vout = analogRead(LM35_sensor_output);
   vout = vout * 5 / 1023;
   temp = vout / 0.01;
   contor_apelare = 0;
 }
 
 if (pulseSensor.sawNewSample())
 {
   contor_apelare++;
   if (--samplesUntilReport == (byte) 0)
   {
     
     samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

     if (pulseSensor.sawStartOfBeat())
     {
       
       Beat_per_minutes = pulseSensor.getBeatsPerMinute();
       Beat_per_minutes = pulseSensor.getBeatsPerMinute();
     }
     
   }

    if (gps_bus.available() > 0)               // check for gps data on the serial comm
     {
       GPS.encode(gps_bus.read());                 // encode gps data
       if (GPS.location.isUpdated())
       {
   //LOCATION
         // Latitude in degrees (double)
         latidude = GPS.location.lat();
         Serial.print("Latitude = ");
         Serial.print(latidude, 6);
             
         // Longitude in degrees (double)
         longitude = GPS.location.lng();
         Serial.print(" Longitude = ");
         Serial.println(longitude, 6);
         
  //DATE
         // Year (2000+) (u16)
         years = GPS.date.year();
         Serial.print("Year = ");
         Serial.print(years);
         
         // Month (1-12) (u8)
         mounth = GPS.date.month();
         Serial.print("  Month = ");
         Serial.print(mounth);
         
         // Day (1-31) (u8)
         days = GPS.date.day();
         Serial.print("  Day = ");
         Serial.println(days);
         
  //TIME
         // Hour (0-23) (u8)
         hours = GPS.time.hour();
         hours = hours + 2;
         Serial.print("Hour = ");
         Serial.print(hours);
         
         // Minute (0-59) (u8)
         minutes = GPS.time.minute();
         Serial.print("  Minute = ");
         Serial.print(minutes);
         
         // Second (0-59) (u8)
         seconds = GPS.time.second();
         Serial.print("  Second = ");
         Serial.println(seconds);

         //Puls
         Serial.print("BPM: ");
         Serial.println(Beat_per_minutes);

         //Temperature
         Serial.print("Temperature = ");
         Serial.print(temp);
         Serial.println(" °C");
         Serial.println(" ");
         
     }
     
    }

 }    
 
}
