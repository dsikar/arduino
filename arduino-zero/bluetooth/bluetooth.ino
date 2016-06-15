#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "libdef.h"

/***************************************
The Manual

1. Build and hookup RDNO 0 then upload sketch.
2. Open Android Bluetooth monitoring app of your choice.
3. Send string "libdef" without quotes to get library definition.
4. Send strings
4.1 Turn led on
  {"function":"LedOn"}
4.2 Turn led off
  {"function":"LedOff"}
4.3 Determine state
  {"function":"IsLedOn"}
4.4 Vary intensity
  {"function":"PWMLed","intensity":255}
  where intensity is in the rang 0-255
***************************************/

boolean boolIsLedOn = false;
int ledpin = 11;
#define RX   12
#define TX   13

SoftwareSerial mySerial(RX, TX);

void LedOn() {
  digitalWrite(ledpin, HIGH);
  boolIsLedOn = true;
}

void LedOff() {
  digitalWrite(ledpin, LOW);
  boolIsLedOn = false;
}

boolean IsLedOn() {
    return boolIsLedOn;
}

void PWMLed(int intensity) {
  analogWrite(ledpin, intensity); 
}

void setup() {
  pinMode(ledpin, OUTPUT);
  mySerial.begin(57600);
  Serial.begin(9600);
  Serial.println(libdef);
}

void CheckSerial() {
  String content = "";
  char character;
  while(mySerial.available()) {
      character = mySerial.read();
      content.concat(character);
      delay(10);
  }
  if (content != "") {
    if (content.substring(0,6) == "libdef") {
      mySerial.println(libdef); 
    } else {
      Parse(content);
    }
  }
}

void Parse(String content) {  
  int str_len = content.length() + 1;
  char char_array[str_len];
  content.toCharArray(char_array, str_len);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(char_array);
  const char* function = root["function"];
  if(strcmp(function, "LedOn") == 0) {
    LedOn();
  }  
  if(strcmp(function, "LedOff") == 0) {
    LedOff();
  }
  if(strcmp(function, "IsLedOn") == 0) {
    mySerial.println(IsLedOn());
  }
  if(strcmp(function, "PWMLed") == 0) {
    int intensity = root["intensity"];
    PWMLed(intensity);
  }
  
}

void loop() {
  CheckSerial();
}
