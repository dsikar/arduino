#include <Buttons.h>
// For Due boards; use due-no-eeprom here and on arduino-libraries/Buttons branch 
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ArduinoJson.h>

// Serial debug. Set to 1 to debug.
#define SERIAL_DEBUG 0

// timer contants
#define WIRE_SERVICE 3

// Wire slave PID jsoknit read functions.
// See slave's libdef.h
// TODO remove magic numbers 4, 5 and 6.

// checkNodes() timer variables
int iCount;
int iTime1;
int iTime2;
// Values received from nodes; we will not use
// indexes 0 and 1, only 2, 3 and 4 to match
// Wire slave nodes' numbering
int iNode[6] = {0, 0, 0, 0, 0, 0};
// Ignoring 0 and 1, use offset;

// Buttons (temporary switches).
// Analog pin.
int iPin = 0; 
// Expected digital noise level.
int iNoise = 25;
// AD conversion value for switching nodes.
int iSwitchSelect = 160;
// AD conversion value for decrementing node value.
int iSwitchDec = 260;
// AD conversion value for incrementing node value.
int iSwitchInc = 440;
// Number of PID nodes managed by Wire slave node.
int iPIDNodes = 3;
// The Wire slave node we will be talking to.
int iWireSlaveNode = 2;
// The maximum number of bytes expected in any I2C data exchange.
int iMaxExpectedBytes = 21;
/*
Initialize Buttons (temporary switches) object.
NOTE:
Arrays in Buttons.h need dimensioning e.g. 
	int iMax[3];
	int iMin[3];
	int iStep[3];
	int iNode[3];
where 3 is a hardcoded value, each of the nodes
having a min value, max value, etc.
If other than 3 nodes are required, 
Button.h int arrays will need adjusting.
*/
Buttons buttons(iPin, iNoise, iSwitchSelect, iSwitchInc, iSwitchDec, iPIDNodes);

// LCD
int iLCDLine1 = 1;
int iLCDLine2 = 2;
// Initialize the library with the numbers of the interface pins.
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

/*
Left pad with 0's if need be to format number with 3 digits.
@param iVal The integer that will be padded with leading 0's
if required.
*/
String pad(int iVal) {
  String strVal = String(iVal);
  strVal = "00" + strVal; 
  return strVal.substring(strVal.length() - 3);
}

/*
Make remote function call by sending
Json string to node.
@param iVal The value to be sent as function argument.
@param iFunctionID the function to be called on slave node.
*/
void makeRemoteCall(int iVal, int iFunctionId)
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  char c;
  root["id"] = iFunctionId;
  if(iVal != NULL){
    root["arg"] = iVal;
  }
  char cJson[200];
  root.printTo(cJson, sizeof(cJson)); 
  String strSend = cJson; 
  // Begin transmission to slave device.
  Wire.beginTransmission(iWireSlaveNode); 
  for(int i = 0; i < strSend.length(); i++) {
      c = strSend[i];
      Wire.write(c);
  } 
  // End transmission to slave device.
  Wire.endTransmission(); 
  if(SERIAL_DEBUG) {  
    Serial.print("\n*** Sending request ");
    Serial.print(strSend);
    Serial.println(" ***");
  }
}

/*
Listen to the node's reply made with makeRemoteCall
@param iNodeNumber The node number we want the value from.
@param iBytes The number of expected bytes.
*/
void listenRemoteCallReply(int iNodeNumber, int iMaxExpectedBytes)
{
  String strRetVal;
  Wire.requestFrom(iNodeNumber, iMaxExpectedBytes); 
  while(Wire.available())   
  {
    char c = Wire.read();
    strRetVal += c;
  }
  Parse(strRetVal);
}

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
  // Requested oven temperature
  if(id == 4) {
    int iTemp = root["retval"];
    iNode[2] = iTemp;
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Requested oven temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iTemp);  
      Serial.println(" ***");
    }   
  } 
  // Requested injector temperature
  if(id == 5) {
    int iTemp = root["retval"];
    iNode[3] = iTemp;
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Requested injector temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iTemp);  
      Serial.println(" ***");  
    }
  }
  // Requested column temperature
  if(id == 6) {
    int iTemp = root["retval"];
    iNode[4] = iTemp;
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Requested column temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iTemp);  
      Serial.println(" ***");   
    }
  }  
}

/*
Update 16x2 LCD display.
@param iLine LCD line to update.
*/
void lcdUpdate(int iLine)
{
  if(iLine == iLCDLine1) // update line 1 
  {
    String strLine1 = "TMP  " + pad(iNode[2]) + " " + pad(iNode[3]) + " " + pad(iNode[4]);
      lcd.setCursor(0, (iLine - 1));
      lcd.print(strLine1);
  } else {
    int iNodePos = buttons.getNodePos();
    String sel = (iNodePos == 1 ? "*" : " ");
    int iVal1 = buttons.getNodeVal(1);
    String strLine2 = "PRG " + sel + pad(iVal1);
    sel = (iNodePos == 2 ? "*" : " ");
    int iVal2 = buttons.getNodeVal(2);
    strLine2 += sel + pad(iVal2);
    int iVal3 = buttons.getNodeVal(3);  
    sel = (iNodePos == 3 ? "*" : " ");
    strLine2 += sel + pad(iVal3); 
    lcd.setCursor(0, (iLine - 1));
    lcd.print(strLine2);    
  }  
}

/*
Check values read by node.
*/
void checkNodes()
{
  iTime2 = millis() / 1000;
  if(iTime2 - iTime1 >= WIRE_SERVICE) {
    // Make function call id == 4 on slave node 2.
    //  {"id":4}
    makeRemoteCall(NULL, 4);
    if(SERIAL_DEBUG) {   
      // Delays needed to stop Serial Monitor from freezing. 
      delay(50);
    } 
    // receive 21 bytes of data from slave node 2.
    // {"id":4,"retval":312} 
    listenRemoteCallReply(iWireSlaveNode, iMaxExpectedBytes);
    if(SERIAL_DEBUG) { 
      delay(50);
    }
    // Make function call id == 5 on slave node 2.
    makeRemoteCall(NULL, 5);
    if(SERIAL_DEBUG) { 
      delay(50);    
    }
    listenRemoteCallReply(iWireSlaveNode, iMaxExpectedBytes);
    if(SERIAL_DEBUG) { 
      delay(50);
    } 
    // Make function call id == 6 on slave node 2.
    makeRemoteCall(NULL, 6);
    if(SERIAL_DEBUG) { 
      delay(50);    
    }
    listenRemoteCallReply(iWireSlaveNode, iMaxExpectedBytes);
    if(SERIAL_DEBUG) { 
      delay(50);  
    }
    lcdUpdate(iLCDLine1); // update LCD line with temperatures read from node PIDs   
    iTime1 = millis() / 1000; 
  }   
}

void setup()
{
  // Join i2c bus (address optional for master).
  Wire.begin(); 
  Serial.begin(9600);
  // add nodes
  // Buttons::addNode(int iMn, int iMx, int iSt, int iDx)
  // Node attributes, minimum and maximum values, step and index (base 1).
  int iMn = 0; int iMx = 220; int iSt = 5; int iDx = 1;
  // furness thermocouple
  buttons.addNode(iMn, iMx, iSt, iDx);
  // injector thermocouple
  iMn = 20; iMx = 300; iSt = 5; iDx = 2;
  buttons.addNode(iMn, iMx, iSt, iDx); 
  // column thermocouple
  iMn = 10; iMx = 400; iSt = 5; iDx = 3;
  buttons.addNode(iMn, iMx, iSt, iDx);
  
  lcd.begin(16, 2);
  lcdUpdate(iLCDLine1); 
  lcdUpdate(iLCDLine2);
  
  // Start checkButtons() timer.
  iTime1 = millis() / 1000;
  
  // Need start up routine here:
  // 1. Get values stored in eeprom
  int iTemp = buttons.getNodeVal(1);
  
  // 2. Set temperatures based on 1.
}

void loop()
{
    
    checkNodes();
    buttons.checkButtons();
    if(buttons.changed()) {
      int iVal = buttons.setNodeVal();
      // Magic number 1, iNodePos is base 1, add one
      // to match PID  position in slave node
      int iPIDPos = buttons.getNodePos() + 1; 
      // Note iPIDPos matches the function ids to set temperatures.
      // See libdef.h on slave node.
      makeRemoteCall(iVal, iPIDPos);
      lcdUpdate(iLCDLine2);
    } 
}
