#include <Wire.h>
#include <ArduinoJson.h>

// MASTER
  
// The Slave node we will be talking to
int iWireNode = 2;

/*
Parse json content.
@param content Json content.
*/
void Parse(String content) {  
  int str_len = content.length() + 1;
  char char_array[str_len];
  content.toCharArray(char_array, str_len);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(char_array);
  int id = root["id"];  
  // Requesting oven temperature
  if(id == 4) {
    int iTemp = root["retval"];
    Serial.print("\n*** Requested oven temperature, received string: ");
    Serial.print(content);
    Serial.print(" extracted temperature: ");
    Serial.print(iTemp);  
    Serial.println(" ***");   
  } 
  // Requesting injector temperature
  if(id == 5) {
    int iTemp = root["retval"];
    Serial.print("\n*** Requested injector temperature, received string: ");
    Serial.print(content);
    Serial.print(" extracted temperature: ");
    Serial.print(iTemp);  
    Serial.println(" ***");   
  }
  // Requesting column temperature
  if(id == 6) {
    int iTemp = root["retval"];
    Serial.print("\n*** Requested column temperature, received string: ");
    Serial.print(content);
    Serial.print(" extracted temperature: ");
    Serial.print(iTemp);  
    Serial.println(" ***");   
  }  
}

/*
Receives a value from node.
@param iNodeNumber The node number we want the value from.
@param iBytes The number of expected bytes.
*/
void receiveNodeVal(int iNodeNumber, int iBytes)
{
  String strRetVal;
  Wire.requestFrom(iNodeNumber, iBytes); 
  while(Wire.available())   
  {
    char c = Wire.read();
    strRetVal += c;
  }
  Parse(strRetVal);
}

/*
void sendNodeVal(int iVal)
Send Jsoknit string to node.
TODO - Change iVal to char cJson
*/
void sendNodeVal(int iVal, int iNodeNumber)
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  char c;
  root["id"] = iNodeNumber;
  if(iVal != NULL){
    root["arg"] = iVal;
  }
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
  Serial.print("\n*** Sending request ");
  Serial.print(strSend);
  Serial.println(" ***");
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(3000);
  // call function id 1 passing argument value of 150;
  sendNodeVal(150, 1);
  
  //delay(45); 
  sendNodeVal(250, 2);
  
  //delay(45); 
  sendNodeVal(350, 3);  

  //delay(75); 
  sendNodeVal(NULL, 4);
  delay(100);  
  receiveNodeVal(2, 21);
 
  //delay(75); 
  sendNodeVal(NULL, 5);    
  delay(100);
  receiveNodeVal(2, 21);
  
  //delay(75);   
  sendNodeVal(NULL, 6);
  delay(100);  
  receiveNodeVal(2, 21);  
}
