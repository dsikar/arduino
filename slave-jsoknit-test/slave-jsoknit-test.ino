#include <Wire.h>
#include <ArduinoJson.h>

char cJson[200];

#define SERIAL_DEBUG 0

void Parse(String content) {  
  int str_len = content.length() + 1;
  char char_array[str_len];
  content.toCharArray(char_array, str_len);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(char_array);
  int id = root["id"];
  if(id == 1) {
    int iTemp = root["arg"];
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Received function call ");
      Serial.print(content);
      Serial.print(" setOvenTemperature");
      Serial.print(", setting temperature to ");
      Serial.print(iTemp);
      Serial.print(" ***\n");
    }
  }
  if(id == 2) {
    int iTemp = root["arg"];
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");
      Serial.print(content);
      Serial.print(" setInjectorTemperature");
      Serial.print(", setting temperature to ");
      Serial.print(iTemp);
      Serial.print(" ***\n");    
    }
  }
  if(id == 3) {
    int iTemp = root["arg"];
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");
      Serial.print(content);
      Serial.print(" setColumnTemperature");
      Serial.print(", setting temperature to ");
      Serial.print(iTemp);
      Serial.print(" ***\n"); 
    }   
  }  
  // Master requested oven temperature
  if(id == 4) {
    setTemperatureReading(id);
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Received function call ");
      Serial.print(content);    
      Serial.print (" - Master requested oven temperature, sending JSON string: ");   
    }
  } 
  // Master requested injector temperature
  if(id == 5) {
    setTemperatureReading(id);
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");
      Serial.print(content);    
      Serial.print (" - Master requested injector temperature, sending JSON string: ");
    }
  } 
    // Master requested column temperature
  if(id == 6) {
    setTemperatureReading(id);
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");;
      Serial.print(content);    
      Serial.print (" - Master requested column temperature, sending JSON string: ");
    }
  } 
}

/*
Set return json string.
@param id Temperature PID controller id.
*/
void setTemperatureReading(int id)
{
  StaticJsonBuffer<200> jsonBufferReply;
  JsonObject& rootReply = jsonBufferReply.createObject();
  rootReply["id"] = id; // id = 4, 5 or 6.
  rootReply["retval"] = id * 78; // Mock 3-digit temperature.
  rootReply.printTo(cJson, sizeof(cJson));
}
void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); 
  if(SERIAL_DEBUG) {
    Serial.begin(9600);
  }
}

void receiveEvent(int howMany)
{
  String strRecVal;
  while(Wire.available())    // slave may send less than requested
  {
    char c = Wire.read(); // receive byte as character
    strRecVal += c;
  }
  Parse(strRecVal);
}

/*
void requestEvent()
Master requests event.
Send stored sJson back.
*/
void requestEvent()
{
  Wire.write(cJson);
  if(SERIAL_DEBUG) {
    Serial.println(sJson);
  }
}


void loop()
{
  delay(100);
}
