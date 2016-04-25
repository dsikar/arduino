#include <Wire.h>
#include <ArduinoJson.h>

int val;
int tempPin = 0;
char cJson[200];

void Parse(String content) {  
  int str_len = content.length() + 1;
  char char_array[str_len];
  content.toCharArray(char_array, str_len);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(char_array);
  int id = root["id"];
  if(id == 1) {
    int iTemp = root["arg"];
    Serial.print("\nReceived function call setOvenTemperature, setting temperature to ");
    Serial.println(iTemp);
  }
  if(id == 2) {
    int iTemp = root["arg"];
    Serial.print("\nReceived function call setColumnTemperature, setting temperature to ");
    Serial.println(iTemp);
  }
  if(id == 3) {
    int iTemp = root["arg"];
    Serial.print("\nReceived function call setInjectorTemperature, setting temperature to ");
    Serial.println(iTemp);
  }  
  // requesting oven temperature
  if(id == 4) {
    StaticJsonBuffer<200> jsonBufferReply;
    JsonObject& rootReply = jsonBufferReply.createObject();
    rootReply["id"] = id; // 4
    rootReply["retval"] = 158; // readTemp(relatedTo4);
    //Serial.println(sizeof(cJson));
    rootReply.printTo(cJson, sizeof(cJson));
  } 
}

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);
}

void receiveEvent(int howMany)
{
  String strRecVal;
  while(Wire.available())    // slave may send less than requested
  {
    char c = Wire.read(); // receive byte as character
    strRecVal += c;
  }
  Serial.println(strRecVal);
  Parse(strRecVal);
}

void requestEvent()
{
  String sJson = cJson; // convert char array to string
  for(int i = 0; i < sJson.length(); i++) {
    char inChar = sJson[i];
    Wire.write(inChar);
  } 
  Serial.println(sJson); 
}


void loop()
{
  ;
}
