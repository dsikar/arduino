#include <Buttons.h>
// For Due boards; use due-no-eeprom branch on arduino-libraries/Buttons
// and comment out line below.
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ArduinoJson.h>

// TODO add interrupt on top of A0.

// Serial debug. Set to 1 to debug.
#define SERIAL_DEBUG 0

// Timer contants - seconds between data exchange.
#define WIRE_SERVICE 3

// checkNode() timer variables
int iCount = 0;
int iTime1;
int iTime2;
// Temperature global variables.
int iOvenTemp, iInjectorTemp, iColumnTemp;
// libdef.h function indexes.
int iFnIdxSetOvenTemp = 1;
int iFnIdxSetInjectorTemp = 2;
int iFnIdxSetColumnTemp = 3;
int iFnIdxReadOvenTemp = 4;
int iFnIdxReadInjectorTemp = 5;
int iFnIdxReadColumnTemp = 6;

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
int iWireSlavePIDx3Node = 2;
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
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

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
@param iFunctionID the function to be called on slave node.
@param iVal The value to be sent as function argument.
*/
void makeRemoteCall(int iFunctionId, int iVal)
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
  Wire.beginTransmission(iWireSlavePIDx3Node); 
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
Listen to the node's reply made with makeRemoteCall.
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
  if(id == iFnIdxReadOvenTemp) {
    // Need isNan error check.
    iOvenTemp = root["retval"];
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Requested oven temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iOvenTemp);  
      Serial.println(" ***");
    }   
  } 
  // Requested injector temperature
  if(id == iFnIdxReadInjectorTemp) {
    iInjectorTemp = root["retval"];
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Requested injector temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iInjectorTemp);  
      Serial.println(" ***");  
    }
  }
  // Requested column temperature
  if(id == iFnIdxReadColumnTemp) {
    iColumnTemp = root["retval"];    
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Requested column temperature, received string: ");
      Serial.print(content);
      Serial.print(" extracted temperature: ");
      Serial.print(iColumnTemp);  
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
    String strLine1 = "TMP  " + pad(iOvenTemp) + " " + pad(iInjectorTemp) + " " + pad(iColumnTemp);
      // iLine - 1 because of 0 indexed LCD lines.
      lcd.setCursor(0, (iLine - 1));
      lcd.print(strLine1);
  } else {
    // Note getNodePos and getNodeVal are not related to Wire nodes.
    // They're related to the PID controller temperatures displayed on LCD.
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
    // iLine - 1 because of 0 indexed LCD lines.
    lcd.setCursor(0, (iLine - 1));
    lcd.print(strLine2);    
  }  
}

/*
Check data from slave node.
*/
void checkNode()
{ 
  // In practice, split the checks to make temporary
  // switches more responsive.
  switch (iCount) {
    case 0:
      // Make function call id == 4 on slave node 2.
      //  {"id":4}
      makeRemoteCall(iFnIdxReadOvenTemp, NULL);
      delay(50);
      listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes);
      break;
    case 1:
      makeRemoteCall(iFnIdxReadInjectorTemp, NULL);
      delay(50);  
      listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes); 
      break;
    case 2:
      makeRemoteCall(iFnIdxReadColumnTemp, NULL);
      delay(50);  
      listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes);
      break;
  }
  // Update LCD line temperatures read from node PIDs.
  lcdUpdate(iLCDLine1); 
  iCount++;
  if(iCount > 2) {iCount = 0;}
}

/*
Set up routine.
*/
void setup()
{
  // Join i2c bus (address optional for master).
  Wire.begin(); 
  if(SERIAL_DEBUG) {
    Serial.begin(9600);
  }
  // add nodes
  // Buttons::addNode(int iMn, int iMx, int iSt, int iDx)
  // Node attributes, minimum and maximum values, step and index (base 1).
  int iMn = 0; int iMx = 220; int iSt = 1; int iDx = 1;
  // furness thermocouple
  buttons.addNode(iMn, iMx, iSt, iDx);
  // injector thermocouple
  iMn = 1; iMx = 300; iSt = 1; iDx = 2;
  buttons.addNode(iMn, iMx, iSt, iDx); 
  // column thermocouple
  iMn = 1; iMx = 400; iSt = 1; iDx = 3;
  buttons.addNode(iMn, iMx, iSt, iDx);
  
  tempStartUp();
  
  lcd.begin(16, 2);
  lcdUpdate(iLCDLine1); 
  lcdUpdate(iLCDLine2);
}

/* 
PID temperature controllers' start up routine.
*/
void tempStartUp() 
{ 
  // Give slave node time to wake up.
  delay(2000);

  // Read PID controllers' temperatures.
  // Each checkNode() call retrieve one PID from the three.
  checkNode();
  checkNode();
  checkNode();
  /*
  makeRemoteCall(iFnIdxReadOvenTemp, NULL);
  delay(50);
  listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes);
  makeRemoteCall(iFnIdxReadInjectorTemp, NULL);
  delay(50);
  listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes);
  makeRemoteCall(iFnIdxReadColumnTemp, NULL);
  delay(50);
  listenRemoteCallReply(iWireSlavePIDx3Node, iMaxExpectedBytes);
  */
  
  // Set PID controllers, Temperatures.
  int iTemp = buttons.getNodeVal(iFnIdxSetOvenTemp);
  makeRemoteCall(iFnIdxSetOvenTemp, iTemp);
  
  iTemp = buttons.getNodeVal(iFnIdxSetInjectorTemp);
  makeRemoteCall(iFnIdxSetInjectorTemp, iTemp);
  
  iTemp = buttons.getNodeVal(iFnIdxSetColumnTemp);
  makeRemoteCall(iFnIdxSetColumnTemp, iTemp);  
}

/*
Main loop.
*/
void loop()
{ 
  checkNode();   
  buttons.checkButtons();
  if(buttons.changed()) {
    int iVal = buttons.setNodeVal();
    int iPIDPos = buttons.getNodePos(); 
    // Note iPIDPos matches the function ids to set temperatures on each of 
    // the Wire slave's PID nodes.
    // See libdef.h on slave node.
    makeRemoteCall(iPIDPos, iVal);
    lcdUpdate(iLCDLine2);
  } 
}
