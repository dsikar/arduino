#include <Wire.h>
   
int val;
int tempPin = 0;

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
}

void requestEvent()
{
  Serial.print("Received requestEvent, sending readTemp()"); 
  int iTemp = readTemp();
  Serial.println(iTemp);
  String strTemp = String(iTemp);
  Wire.write("Hello."); // respond with message of 3 bytes 
}

int readTemp() 
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  int iTemp = cel;
  return iTemp;
}

void setTemp()
{
  // read temp every 1 second  
}

void loop()
{
  delay(100);
  /*
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);


*/
}