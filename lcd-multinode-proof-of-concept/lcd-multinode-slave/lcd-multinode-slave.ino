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
  uint16_t iVar = readTemp();
  // bit shifting
  byte bHigh = (iVar >> 8);
  byte bLow = iVar & 0xfff;
  Wire.write(bHigh); 
  Wire.write(bLow);
}

uint16_t readTemp() 
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  uint16_t iTemp = cel;
  return iTemp;
}

void setTemp()
{
  // read temp every 1 second  
}

void loop()
{
  // delay(100);

  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);

}