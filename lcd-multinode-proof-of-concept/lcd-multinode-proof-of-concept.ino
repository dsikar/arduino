#include <Buttons.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

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
void lcdUpdate()
Update a hypothetical display.
*/
void lcdUpdate()
{
  String strLine1 = "TMP  XXX XXX XXX";
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
  //Serial.println(strRes); 
  lcd.setCursor(0, 0);
  lcd.print(strLine1); 
  lcd.setCursor(0, 1);
  lcd.print(strLine2);  
}

/*
void lcdInit() {
  int iThermTemp = thermocouple.readCelsius();
  int iProgTemp = buttons.getTemp();
  // set up the LCD's number of columns and rows: 
  lcd.setCursor(0, 0);
  // temperature is a global variable
  String strTemp;
  formatTemp(iThermTemp, strTemp);
  lcd.print("TEMPERATURA: " + strTemp);
  formatTemp(iProgTemp, strTemp);
  strTemp = "TEMP. PROG.: " + strTemp;
  lcd.setCursor(0, 1);
  lcd.print(strTemp);
} 

void lcdUpdate2() {
  // same as lcdInit() except only update the values
  int iThermTemp = thermocouple.readCelsius();
  int iProgTemp = buttons.getTemp();
  // set up the LCD's number of columns and rows: 
  lcd.setCursor(13, 0);
  // temperature is a global variable
  String strTemp;
  formatTemp(iThermTemp, strTemp);
  lcd.print(strTemp);
  formatTemp(iProgTemp, strTemp);
  strTemp = strTemp;
  lcd.setCursor(13, 1);
  lcd.print(strTemp);
}
*/
void setup()
{
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
  lcdUpdate();
}

void loop()
{
    // checkNodes();
    buttons.checkButtons();
    if(buttons.changed()) {
      int iVal = buttons.setNodeVal();fs
      // pass node data on to where it is dealt with
      // dealWithNodeData(iVal, buttons.getNodePos());
      // settemperature = iVal;
      // etc
      // for the time being, update what is shown in the Serial Monitor
      lcdUpdate();
    } 
}
