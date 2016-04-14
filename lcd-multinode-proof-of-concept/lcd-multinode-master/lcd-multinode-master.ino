#include <Buttons.h>
// For Due boards; use due-no-eeprom here and on arduino-libraries/Buttons branch 
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>

/****************************
  
  TODO
  1. Cleanup master node code e.g. remove ambiguous variable names for Buttons and Wire slaves nodes
  
****************************/  
// timer contants
#define WIRE_SERVICE 3

// checkNodes() timer variables
int iCount;
int iTime1;
int iTime2;
// Values received from nodes; we will not use
// indexes 0 and 1, only 2, 3 and 4 to match
// Wire slave nodes' numbering
int iNode[6] = {0, 0, 0, 0, 0, 0};
// Ignoring 0 and 1, use offset;

// buttons 
// analogue pin
int iPin = 0; 
// digital noise level
int iNoise = 25;
// AD conversion value for switching nodes
int iSwitchSelect = 160;
// AD conversion value for decrementing node value
int iSwitchDec = 260;
// AD conversion value for incrementing node value
int iSwitchInc = 440;
// Number of nodes
int iNodes = 3;

/*
NOTE
Arrays in Buttons.h need dimensioning e.g. 
	int iMax[3];
	int iMin[3];
	int iStep[3];
	int iNode[3];
if other than 3 nodes are required, 
Button.h int arrays will need adjusting.
*/

Buttons buttons(iPin, iNoise, iSwitchSelect, iSwitchInc, iSwitchDec, iNodes);

// LCD
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

/*
String pad(int iVal)
Left pad with 0's if need be to format number with 3 digits.
*/
String pad(int iVal) {
  String strVal = String(iVal);
  strVal = "00" + strVal; 
  return strVal.substring(strVal.length() - 3);
}

/*
String receiveNodeVal()
Get val from slave node.
*/
void receiveNodeVal(int iNodeNumber)
{
  Wire.requestFrom(iNodeNumber, 2);    // request 2 bytes from slave device iNode
  uint16_t iVal = 0xffff;
  byte bHigh;
  byte bLow;
  while(Wire.available())    // slave may send less than requested
  {
    //  int iVal = (bHigh << 8) | bLow ; 
    uint8_t c = Wire.read(); // receive a byte as character
    if(iVal == 0xffff)
    {
        iVal = 0;
        bHigh = c;
    } else {
        bLow = c;
       iVal = (bHigh << 8) | bLow;  
    }
  }
  iNode[iNodeNumber] = iVal; 
}

/*
void lcdUpdate()
Update a hypothetical display.
*/
void lcdUpdate(int iLine)
{
  if(iLine == 1) // update line 1 
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
void receive()
Receive wire request.
*/
void receive()
{
  Serial.println("Receiving readTemp() reply...");
  Wire.requestFrom(2, 5);    // request 3 bytes from slave device #2
  while (Wire.available())   // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  delay(500);
}

/*
void sendNodeVal(int iVal)
Send value to node.
*/
void sendNodeVal(int iVal, int iNodeNumber)
{
  uint16_t iVar = iVal;
  // bit shifting
  byte bHigh = (iVar >> 8);
  byte bLow = iVar & 0xfff;
  Wire.beginTransmission(iNodeNumber); // transmit to device #2
  Wire.write(bHigh); 
  Wire.write(bLow);
  Wire.endTransmission();    // stop transmitting
}

/*
void checkNodes()
Get the values (e.g. temperature) stored in nodes
*/
void checkNodes()
{
  iTime2 = millis() / 1000;
  // TODO add bit shifting to read reply
  if(iTime2 - iTime1 >= WIRE_SERVICE) {
    //receive(); // receive one request
    //delay(100);
    //send(); // send another one
    // get val from I2C slave node 2
    receiveNodeVal(2);
    // commment in when nodes are hooked up and ready
    // receiveNodeVal(3);
    // receiveNodeVal(4);
    lcdUpdate(1); // update LCD line 1   
    iTime1 = millis() / 1000; 
  }   
}

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  // TODO
  // Initial values (stored in eeprom must be sent to nodes
  // at start up.
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
  lcdUpdate(1); // update line 1
  lcdUpdate(2); // update line 2
  
  // checkButtons() init timer
  iTime1 = millis() / 1000;
}

void loop()
{
    checkNodes();
    buttons.checkButtons();
    if(buttons.changed()) {
      int iVal = buttons.setNodeVal();
      // Magic number 1, iNodePos is base 1, add one
      // to match slave node numbering
      int iNodePos = buttons.getNodePos() + 1; 
      sendNodeVal(iVal, iNodePos);
      lcdUpdate(2);
    } 
}
