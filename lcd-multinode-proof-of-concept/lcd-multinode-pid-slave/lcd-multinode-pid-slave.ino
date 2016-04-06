#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <PID_v1.h>
#include "Adafruit_MAX31855.h"

// Serial debug, set to 1 for serial debugging
#define SERIAL_DEBUG 1

// Slave node number
#define SLAVE_NODE 2

// SPI interface IO digital pins for the MAX31855
#define DO   10
#define CS   11
#define CLK  12

// Thermocouple error constants
// If the average PID output is greater than
#define MAX_ERROR_PID_AVG 130
// but the temperature rises less than
#define MIN_ERROR_TEMP_DELTA 20
// an error will be raise

// PID variables
const int mosfetDrive = 13;  // drive pin for heater
double temperature;
double settemperature;  
double output;  // needed for pid for column heater

// Prog. temp sent from master
double dTempVar;

// timer contants
#define PID_SERVICE_INTERVAL 2 // check PID every 2 seconds
#define ERROR_CHECK_INTERVAL 5 // check for error conditions when count reaches 5 (ten seconds)

// PID service counter
int iCount;
int iTime1;
int iTime2;

// temperature variables
double dTemp1;
int iAvgPID;
double dTempDelta;

// Error flag
int iFlagError;

// initialise thermocouple object
Adafruit_MAX31855 thermocouple(CLK, CS, DO);

// initialise PID object
PID myPID(&temperature, &output, &settemperature,2.5,0.2,0, DIRECT);    // Kp,Ki,Kd values generated from autotune sketch run previously 

/*
void receiveEvent(int howMany)
Receive message from master, howMany specifying number of bytes transmitted.
*/
void receiveEvent(int howMany)
{
  /*
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  */
  // uint16_t ~ expecting to receive 2 bytes
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
  // Store PID temperature
  dTempVar = iVal;
  
  Serial.print("Received val from master = ");
  Serial.println(iVal);
  Serial.print("Expected var howMany = ");
  Serial.println(howMany);  
}

/*
double getTemp()
Return temperature to be set.
*/
double getTemp()
{
 return dTempVar; 
}

/*
void requestEvent()
Send thermocouple reading to master.
*/
void requestEvent()
{
  // TODO add jsoknit function definitions
  // with request send via receiveEvent
  uint16_t iVar = thermocouple.readCelsius();
  // bit shifting
  byte bHigh = (iVar >> 8);
  byte bLow = iVar & 0xfff;
  Wire.write(bHigh); 
  Wire.write(bLow);
}

void setup() {
  
  if(SERIAL_DEBUG){
    Serial.begin(9600);
  }
  
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register events
  Wire.onRequest(requestEvent); 
  // Serial.begin(9600);
  
  // to control the heating element
  pinMode(mosfetDrive,OUTPUT);

  // get last stored temperature from EEPROM
  
  settemperature = getTemp();
  myPID.SetMode(AUTOMATIC); 
  
  // PID avg, count and timer;
  iTime1 = millis() / 1000;
  iAvgPID = 0;
  iCount = 1;
  
  // reset error flag
  iFlagError = 0;
}

void loop() {
  // redundant as master requests events
  // TODO add serial.print to debug
  while(iFlagError == 0) {
    // settemperature = iTemp;
    // temperature set by master
    temperatureMonitor();     
  }  
}

/*
void temperatureMonitor()
Service PID at a given interval
*/
void temperatureMonitor() {

  iTime2 = millis() / 1000;
  if(iTime2 - iTime1 >= PID_SERVICE_INTERVAL) {

    // keep track of PID output
    iAvgPID += output;  
    // Service the PID
    servicePID();
   
    // increment counter
    iCount++;
    
    if(SERIAL_DEBUG){
      Serial.print("iCount = ");
      Serial.println(iCount);  
      Serial.println("");  
    }
    
    // store reference time and temperature for deltas
    if(iCount == 1){dTemp1 = thermocouple.readCelsius();} 
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

// int iThermTemp = thermocouple.readCelsius();
// int iProgTemp = buttons.getTemp();

/*
void lcdThermocoupleError(){
Set thermocouple error state.
*/
void lcdThermocoupleError(){
  ;
  // set error state
}

/*
void servicePID()
Service PID.
*/
void servicePID() {
  temperature=thermocouple.readCelsius();
  myPID.Compute();
  if(isnan(output)) {
    if(SERIAL_DEBUG){
      Serial.println("Output == nan");
    }
    raiseError();
  }
  analogWrite(mosfetDrive, output);
  if(SERIAL_DEBUG){
    Serial.print("TEMP: ");
    Serial.println(temperature);
    Serial.print("TEMP. PROG: ");
    Serial.println(settemperature);  
    Serial.print("PID output: ");
    Serial.println(output); 
    Serial.print("dTempVar: ");
    Serial.println(dTempVar); 
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
