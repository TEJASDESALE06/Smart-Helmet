#include <Wire.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define rxGPS 34
#define txGPS 35
SoftwareSerial neogps(rxGPS,txGPS);
TinyGPSPlus gps;

#define rxGSM 26
#define txGSM 27
SoftwareSerial sim800(rxGSM,txGSM);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object

void setup()
 {
  Serial.begin(9600);
  neogps.begin(9600);
  Serial.begin(9600);
  sim800.begin(9600);
  if(!accel.begin())   // if ASXL345 sensor not found
  {
    Serial.println("ADXL345 not detected");
    while(1);
  }

}

void loop() 
{
  while (neogps.available() > 0)
  {
    gps.encode(neogps.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      }
       
    }

 sensors_event_t event;
 accel.getEvent(&event);
 Serial.print("X: ");
 Serial.print(event.acceleration.x);
 Serial.print("  ");
  Serial.print("Y: ");
 Serial.print(event.acceleration.y);
 Serial.print("  ");
  Serial.print("Z: ");
 Serial.print(event.acceleration.z);
 Serial.print("  ");
 Serial.println("m/s^2 ");
 delay(500);
 if(event.acceleration.z<3)
 {
  sim800.print("AT+CMGF=1\r");
  delay(1000);
  sim800.println("AT+CMGS=\"+919049261854\"");
  delay(1000);
  sim800.print("http://maps.google.com/maps?q=loc:");
  sim800.print(gps.location.lat(), 6);
  sim800.print(",");
  sim800.print(gps.location.lng(), 6);
  delay(100);
  sim800.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1000);
  Serial.println("GPS Location SMS Sent Successfully.");
  
 }
 

}