#include <Wire.h>
#include <LiquidCrystal.h>
#include <PID_v1.h>
#include <MAX31855.h>
#include <ArduinoJson.h>

// Serial debug, set to 1 for serial debugging.
#define SERIAL_DEBUG 0

// Slave node number.
#define SLAVE_NODE 2

// Json reply buffer.
char cJson[200];

// SPI interface IO digital pins for the MAX31855.
// Note: On UNO cannot use 0 and 1 (RX, TX).

// UNO pinout.
/*
#define MISO 2 // A.K.A. DO pin.
#define SCK  3
#define CSoven  4
#define CSinjector  5
#define CScolumn  6
*/
// DUE pinout.
#define MISO 22 // A.K.A. DO pin.
#define SCK  24
#define CSoven  26
#define CSinjector  28
#define CScolumn  30

// Human readable MAX31855 array indexes.
#define IDX_OVEN 0
#define IDX_INJECTOR 1
#define IDX_COLUMN 2

// MAX31855 object array.
MAX31855 *temp[3] = {new MAX31855(MISO, CSoven, SCK), new MAX31855(MISO, CSinjector, SCK), new MAX31855(MISO, CScolumn, SCK)};

// Thermocouple error constants.
// If the average PID output is greater than
#define MAX_ERROR_PID_AVG 130
// but the temperature rises less than
#define MIN_ERROR_TEMP_DELTA 20
// an error will be raised.

// PID variables
// PWM pins to drive opto-couplers
const int ovenMosfetPin = 9;
const int injectorMosfetPin = 10;
const int columnMosfetPin = 11;

double ovenTemperature, setOvenTemperature, ovenPIDOutput;
double injectorTemperature, setInjectorTemperature, injectorPIDOutput;
double columnTemperature, setColumnTemperature, columnPIDOutput;

// libdef.h function indexes.
int iFnIdxSetOvenTemp = 1;
int iFnIdxSetInjectorTemp = 2;
int iFnIdxSetColumnTemp = 3;
int iFnIdxReadOvenTemp = 4;
int iFnIdxReadInjectorTemp = 5;
int iFnIdxReadColumnTemp = 6;

// timer contants
#define PID_SERVICE_INTERVAL 2 // check PID every 2 seconds
#define ERROR_CHECK_INTERVAL 5 // check for error conditions when count reaches 5 (ten seconds)

// PID service counters.
int iTime1;
int iTime2;

// temperature variables
double dTemp[3];
int iAvgPID;
double dTempDelta;

// Error flag
int iFlagError;

// Initialise PID objects.
PID ovenPID(&ovenTemperature, &ovenPIDOutput, &setOvenTemperature, 2.5, 0.2 , 0, DIRECT);    // Kp,Ki,Kd values generated from autotune sketch run previously 
PID injectorPID(&injectorTemperature, &injectorPIDOutput, &setInjectorTemperature, 2.5, 0.2 , 0, DIRECT);
PID columnPID(&columnTemperature, &columnPIDOutput, &setColumnTemperature, 2.5, 0.2 , 0, DIRECT);

void Parse(String content) {  
  int str_len = content.length() + 1;
  char char_array[str_len];
  content.toCharArray(char_array, str_len);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(char_array);
  int id = root["id"];
  if(id == iFnIdxSetOvenTemp) {
    int iTemp = root["arg"];
    // Set PID oven temperature
    setOvenTemperature = iTemp;
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Received function call ");
      Serial.print(content);
      Serial.print(" setOvenTemperature");
      Serial.print(", setting temperature to ");
      Serial.print(iTemp);
      Serial.print(" ***\n");
    }
  }
  if(id == iFnIdxSetInjectorTemp) {
    int iTemp = root["arg"];
    setInjectorTemperature = iTemp;
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");
      Serial.print(content);
      Serial.print(" setInjectorTemperature");
      Serial.print(", setting temperature to ");
      Serial.print(iTemp);
      Serial.print(" ***\n");  
    }  
  }
  if(id == iFnIdxSetColumnTemp) {
    int iTemp = root["arg"];
    setColumnTemperature = iTemp;
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
  if(id == iFnIdxReadOvenTemp) {
    // Convert float to int.
    int iTemp = ovenTemperature;
    readPIDTemperature(id, iTemp);
    if(SERIAL_DEBUG) {    
      Serial.print("\n*** Received function call ");
      Serial.print(content);    
      Serial.print (" - Master requested oven temperature, sending JSON string: "); 
    }  
  } 
  // Master requested injector temperature
  if(id == iFnIdxReadInjectorTemp) {
    int iTemp = injectorTemperature;
    readPIDTemperature(id, iTemp);
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Received function call ");
      Serial.print(content);    
      Serial.print (" - Master requested injector temperature, sending JSON string: ");
    }
  } 
  // Master requested column temperature
  if(id == iFnIdxReadColumnTemp) {
    // Convert float to int.
    int iTemp = columnTemperature; // for now, later change to columnTemperature;
    readPIDTemperature(id, iTemp);
    iTemp = 250;
    if(SERIAL_DEBUG) {
      Serial.print("\n*** Received function call ");;
      Serial.print(content);    
      Serial.print (" - Master requested column temperature, sending JSON string: ");
    }
  } 
}

/*
Set json string reply as requested by master node.
@param id Temperature PID controller id.
@param iTemp Thermocouple temperature as read by MAX31855
*/
void readPIDTemperature(int id, int iTemp)
{
    StaticJsonBuffer<200> jsonBufferReply;
    JsonObject& rootReply = jsonBufferReply.createObject();
    rootReply["id"] = id;
    rootReply["retval"] = iTemp;
    rootReply.printTo(cJson, sizeof(cJson));   
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
Master requests event.
Send stored sJson back.
*/
void requestEvent()
{
  String sJson = cJson; // convert char array to string
  for(int i = 0; i < sJson.length(); i++) {
    char inChar = sJson[i];
    Wire.write(inChar);
  } 
  if(SERIAL_DEBUG){
    Serial.print(sJson);
    Serial.print(" ***\n");  
  } 
}

void setup() {
  if(SERIAL_DEBUG){
    Serial.begin(9600);
  }
  // This Wire slave node.
  int iWireSlaveNode = 2;
  Wire.begin(iWireSlaveNode); 
  // Register events.
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent); 
  
  // Output to control heating elements.
  pinMode(ovenMosfetPin,OUTPUT);
  pinMode(injectorMosfetPin,OUTPUT);
  pinMode(columnMosfetPin,OUTPUT);

  ovenPID.SetMode(AUTOMATIC); 
  injectorPID.SetMode(AUTOMATIC); 
  columnPID.SetMode(AUTOMATIC); 
  
  // PID avg, count and timer;
  iTime1 = millis() / 1000;
  iAvgPID = 0;
  
  // reset error flag
  iFlagError = 0;
}

/*
Main loop.
*/
void loop() {
  while(iFlagError == 0) {
    temperatureMonitor();     
  } 
}

// Print the temperature, or the type of fault
void printTemperature(double temperature) {
  switch ((int) temperature) {
    case FAULT_OPEN:
      Serial.print("FAULT_OPEN");
      break;
    case FAULT_SHORT_GND:
      Serial.print("FAULT_SHORT_GND");
      break;
    case FAULT_SHORT_VCC:
      Serial.print("FAULT_SHORT_VCC");
      break;
    case NO_MAX31855:
      Serial.print("NO_MAX31855");
      break;
    default:
      Serial.print(temperature);
      break;
  }
  Serial.print(" ");
}

/*
void temperatureMonitor()
Service PID at a given interval
*/
void temperatureMonitor() {

  iTime2 = millis() / 1000;
  if(iTime2 - iTime1 >= PID_SERVICE_INTERVAL) {
    // keep track of PID output
    iAvgPID += ovenPIDOutput;  
    // Service the PID
    // Starting with PID1.
    serviceOvenPID();
    serviceInjectorPID();
    serviceColumnPID();
    
    // Store reference time and temperature for deltas. Leaving it out for now.
    // if(iCount == 1){dTemp[0] = ovenThermocouple.readCelsius();} 
    iTime1 = millis() / 1000; 
  }
  
  // ERROR CHECKING SWITCHED OFF
  /*
  if(iCount == ERROR_CHECK_INTERVAL) {
       // get average output over last 5 PID services
       iAvgPID /= ERROR_CHECK_INTERVAL;
       dTempDelta = thermocouple.readCelsius() - dTemp1;

       if(SERIAL_DEBUG){
         Serial.println("Count == 5, Checking deltas");
         Serial.print("iAvgPID = ");
         Serial.println(iAvgPID);
         Serial.print("dTempDelta = ");
         Serial.println(dTempDelta);
       }
       
       if(iAvgPID > MAX_ERROR_PID_AVG && dTempDelta < MIN_ERROR_TEMP_DELTA) {
         // ERROR - sending current but element not responding
         // switch off the element and raise error
         settemperature = 0; 
         servicePID(); 
         raiseError();
       }
       
       iCount = 0;
       iAvgPID = 0;
  }
  */
}

/*
void lcdThermocoupleError(){
Set thermocouple error state.
*/
void lcdThermocoupleError(){
  ;
  // set error state
}

/*
Service Oven PID.
*/
void serviceOvenPID() {
  // TODO - Add error handling.
  ovenTemperature = (*temp[IDX_OVEN]).readThermocouple(CELSIUS);
  ovenPID.Compute();
  // Leave out for now.
  /*
  if(isnan(ovenPIDOutput)) {
    if(SERIAL_DEBUG){
      Serial.println("ovenTemperature == nan");
    }
    // TODO Report error to LCD.
    raiseError();
  }
  */
  analogWrite(ovenMosfetPin, ovenPIDOutput);
  if(SERIAL_DEBUG){
    Serial.print("ovenTemperature: ");
    Serial.println(ovenTemperature);
    Serial.print("setOvenTemperature: ");
    Serial.println(setOvenTemperature);  
    Serial.print("ovenPIDOutput: ");
    Serial.println(ovenPIDOutput); 
  }
}

/*
Service Injector PID.
*/
void serviceInjectorPID() {
  // TODO - Add error handling.
  injectorTemperature = (*temp[IDX_INJECTOR]).readThermocouple(CELSIUS);
  injectorPID.Compute();
  // Leave out for now.
  /*
  if(isnan(injectorPIDOutput)) {
    if(SERIAL_DEBUG){
      Serial.println("Output2 == nan");
    }
    raiseError();
  }
  */
  analogWrite(injectorMosfetPin, injectorPIDOutput);
  if(SERIAL_DEBUG){
    Serial.print("injectorTemperature: ");
    Serial.println(injectorTemperature);
    Serial.print("setInjectorTemperature: ");
    Serial.println(setInjectorTemperature);  
    Serial.print("injectorPIDOutput: ");
    Serial.println(injectorPIDOutput); 
  }
}

/*
Service Column PID.
*/
void serviceColumnPID() {
  // TODO - Add error handling.
  columnTemperature = (*temp[IDX_COLUMN]).readThermocouple(CELSIUS);
  columnPID.Compute();
  // Leave out for now.
  /*
  if(isnan(injectorPIDOutput)) {
    if(SERIAL_DEBUG){
      Serial.println("Output2 == nan");
    }
    raiseError();
  }
  */
  analogWrite(columnMosfetPin, columnPIDOutput);
  if(SERIAL_DEBUG){
    Serial.print("columnTemperature: ");
    Serial.println(columnTemperature);
    Serial.print("setColumnTemperature: ");
    Serial.println(setColumnTemperature);  
    Serial.print("columnPIDOutput: ");
    Serial.println(columnPIDOutput); 
  }
}
/*
void raiseError()
Flag thermocouple error.
*/
void raiseError(){
 iFlagError = 1;
 lcdThermocoupleError();
} 
