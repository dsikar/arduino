#include <Wire.h>
#include <ArduinoJson.h>

// MASTER

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
// The Slave node we will be talking to
int iWireNode = 2;

void receiveNodeVal(int iNodeNumber)
{
  String strRetVal;
  Wire.requestFrom(iNodeNumber, 5);    // request 20 bytes from slave device iNode
  while(Wire.available())    // slave may send less than requested
  {
    //  int iVal = (bHigh << 8) | bLow ; 
    char c = Wire.read(); // receive a byte as character
    strRetVal += c;
  }
  Serial.println(strRetVal);
}

/*
void sendNodeVal(int iVal)
Send Jsoknit string to node.
TODO - Change iVal to char cJson
*/
void sendNodeVal(int iVal, int iNodeNumber)
{
  // monitoring string
  //String strSend;
  char c;
  // create an ArduinoJson object
  root["id"] = iNodeNumber;
  root["arg"] = iVal;
  char cJson[200];
  root.printTo(cJson, sizeof(cJson)); 
  String strSend = cJson; 
  Wire.beginTransmission(iWireNode); // transmit to device #2
  for(int i = 0; i < strSend.length(); i++) {
      c = strSend[i];
      Wire.write(c);
      //strSend += c;
  }  
  Wire.endTransmission();    // stop transmitting
  Serial.println(strSend);
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);
  // call function id 1 passing argument value of 150;
  sendNodeVal(150, 1);
  delay(2000);
  // call function id 1 passing argument value of 150;
  sendNodeVal(250, 2);
  delay(2000);
  // call function id 1 passing argument value of 150;
  sendNodeVal(350, 3);  
  receiveNodeVal(2);
}
