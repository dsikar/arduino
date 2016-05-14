#include <Wire.h>
#include <LiquidCrystal.h>
#include <PID_v1.h>
#include <MAX31855.h>
#include <ArduinoJson.h>
// not enough memory, excluding libdef.h
// #include libdef.h

// Serial debug, set to 1 for serial debugging.
#define SERIAL_DEBUG 0

// Slave node number.
#define SLAVE_NODE 2

// Json reply buffer.
char cJson[200];

// SPI interface IO digital pins for the MAX31855.
// Note: On UNO cannot use 0 and 1 (RX, TX).

// UNO pinout.
#define MISO 4 // A.K.A. DO pin.
#define SCK  2
#define CSoven  3
#define CSinjector  5
#define CScolumn  7

// DUE pinout.
/*
#define MISO 22 // A.K.A. DO pin.
#define SCK  24
#define CSoven  26
#define CSinjector  28
#define CScolumn  30
*/

// TODO fix sensor order: COL, VAP, DET

// Human readable MAX31855 array indexes.
#define IDX_OVEN 0
#define IDX_INJECTOR 1
#define IDX_COLUMN 2

// MAX31855 object array.
MAX31855 *temp[3] = {new MAX31855(MISO, CSoven, SCK), new MAX31855(MISO, CSinjector, SCK), new MAX31855(MISO, CScolumn, SCK)};

// PID variables
// PWM pins to drive opto-couplers
const int ovenMosfetPin = 9;
const int injectorMosfetPin = 10;
const int columnMosfetPin = 6;

// LED pins.
#define OVEN_DELTA_PIN 13
#define INJECTOR_DELTA_PIN 12
#define COLUMN_DELTA_PIN 11
// Minimum temperature delta % that lights up "Temp. reached" LED.
const double fDeltaPc = 5.0;

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

// PID service counters.
int iTime1;
int iTime2;

// Initialise PID objects.
PID ovenPID(&ovenTemperature, &ovenPIDOutput, &setOvenTemperature, 2.5, 0.2 , 0, DIRECT);    // Kp,Ki,Kd values generated from autotune sketch run previously 
PID injectorPID(&injectorTemperature, &injectorPIDOutput, &setInjectorTemperature, 2.5, 0.2 , 0, DIRECT);
PID columnPID(&columnTemperature, &columnPIDOutput, &setColumnTemperature, 2.5, 0.2 , 0, DIRECT);

/*
Return temperature delta percentage as a positive number.
@param dTemp1 Base temperature.
@oaram dTemp2 Temperature to be compared with.
*/
double tempDeltaPc(double dTemp1, double dTemp2)
{
  // Example; dTemp1 = 19.75, dTemp2 = 20.00, return value = 1.25(%).
  // TODO handle division by 0.
  if(dTemp2 == 0 && dTemp1 == 0) {
      return 0;
  }
  double dPcDiff = ((dTemp1 / dTemp2) - 1) * 100;
  if (dPcDiff < 0) {
    dPcDiff *= -1;
  }
  return dPcDiff;
}

/*
Light LED if temperature current is running through heater.
@param dRealTemp What is being read by thermocouple.
@param dSetTemp The temperature required.
@param iPin The pin number to be set to high or low.
*/
void setTemperatureDeltas(double dRealTemp, double dSetTemp, int iPin)
{
  if(tempDeltaPc(dRealTemp, dSetTemp) <= fDeltaPc)
  {
     digitalWrite(iPin, LOW);
  } else {
      digitalWrite(iPin, HIGH);
  }
}

/*
Check temperature deltas for all three PIDs.
*/
void checkTempDeltas()
{
  setTemperatureDeltas(ovenTemperature, setOvenTemperature, OVEN_DELTA_PIN);
  setTemperatureDeltas(injectorTemperature, setInjectorTemperature, INJECTOR_DELTA_PIN);
  setTemperatureDeltas(columnTemperature, setColumnTemperature, COLUMN_DELTA_PIN);
}

/*
Parse JSON content.
@param content The JSON content to be parsed.
*/
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
  Wire.write(cJson);
  if(SERIAL_DEBUG){
    Serial.println(cJson);
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
  
  // Temperature delta LEDs
  pinMode(OVEN_DELTA_PIN,OUTPUT);
  pinMode(INJECTOR_DELTA_PIN,OUTPUT);
  pinMode(COLUMN_DELTA_PIN,OUTPUT);

  ovenPID.SetMode(AUTOMATIC); 
  injectorPID.SetMode(AUTOMATIC); 
  columnPID.SetMode(AUTOMATIC); 
  
  // PID avg, count and timer;
  iTime1 = millis() / 1000;
}

/*
Main loop.
*/
void loop() {
  delay(100);
  temperatureMonitor();     
}

/*
void temperatureMonitor()
Service PID at a given interval
*/
void temperatureMonitor() {

  iTime2 = millis() / 1000;
  if(iTime2 - iTime1 >= PID_SERVICE_INTERVAL) {
    // Service PIDs
    serviceOvenPID();
    serviceInjectorPID();
    serviceColumnPID();
    
    // Turn temp. monitor LEDs on and off as called for.
    checkTempDeltas();
    // Store reference time and temperature for deltas. Leaving it out for now.
    // if(iCount == 1){dTemp[0] = ovenThermocouple.readCelsius();} 
    iTime1 = millis() / 1000; 
  }
}

/*
Service Oven PID.
*/
void serviceOvenPID() {
  // TODO - Add error handling.
  ovenTemperature = (*temp[IDX_OVEN]).readThermocouple(CELSIUS); 
  ovenPID.Compute();
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
