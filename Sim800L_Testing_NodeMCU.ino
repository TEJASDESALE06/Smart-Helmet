#include <SoftwareSerial.h>
SoftwareSerial Sim800L(D4, D3);  //Sim800L Rx -> D3 Sim800L Tx -> D4

void setup()
{
  Serial.begin(115200);
  Sim800L.begin(9600);
  Serial.println("Initializing...");
  delay(5000);
  Sim800L.println("AT"); //Once the handshake test is successful, it will back to OK
  delay(1000);
  updateSerial();
  Sim800L.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  delay(1000);
  updateSerial();
  Sim800L.println("AT+CBC"); //Signal quality test, value range is 0-31 , 31 is the best
  delay(1000);
  updateSerial();
  delay(1000);
  Sim800L.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(1200);
  Sim800L.print ("AT+CSMP=17,167,0,0\r");// Configuring TEXT mode
  delay(1200);
  Sim800L.println("AT+CMGS=\"+919790906809\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(1500); 
  Sim800L.print("Tesing SMS"); //text content
  Sim800L.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1200);
  updateSerial();
  delay(2000);
}

void loop()
{ updateSerial();}


void updateSerial()
{
  while (Serial.available())   {  Sim800L.write(Serial.read());  }
  while(Sim800L.available())   {  Serial.write(Sim800L.read());  }
}
