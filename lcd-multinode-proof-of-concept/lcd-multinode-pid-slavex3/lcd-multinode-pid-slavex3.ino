#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <PID_v1.h>
#include "Adafruit_MAX31855.h"

/*
  After hearing from the creatir himself that it is possible
  to work with three PID instances in a single sketch
  https://groups.google.com/forum/#!topic/diy-pid-control/IrdhZUh6tcM
  I'll give it a go.
*/
// Serial debug, set to 1 for serial debugging
#define SERIAL_DEBUG 1

// Slave node number
#define SLAVE_NODE 2

// SPI interface IO digital pins for the MAX31855
#define DO1    0
#define CS1    1
#define CLK1   2

#define DO2    3
#define CS2    4
#define CLK2   5

#define DO3    6
#define CS3    7
#define CLK3   8

// Thermocouple error constants
// If the average PID output is greater than
#define MAX_ERROR_PID_AVG 130
// but the temperature rises less than
#define MIN_ERROR_TEMP_DELTA 20
// an error will be raise

// PID variables
// PWM pins to drive opto-couplers
const int mosfetDrive1 = 9;
const int mosfetDrive2 = 10;
const int mosfetDrive3 = 11;

double temperature1, settemperature1, output1;
double temperature2, settemperature2, output2;
double temperature3, settemperature3, output3;

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
double dTemp[3];
int iAvgPID;
double dTempDelta;

// Error flag
int iFlagError;

// initialise thermocouple object
Adafruit_MAX31855 thermocouple1(CLK1, CS1, DO1);
Adafruit_MAX31855 thermocouple2(CLK2, CS2, DO2);
Adafruit_MAX31855 thermocouple3(CLK3, CS3, DO3);

// initialise PID object
PID myPID1(&temperature1, &output1, &settemperature1, 2.5, 0.2 , 0, DIRECT);    // Kp,Ki,Kd values generated from autotune sketch run previously 
PID myPID2(&temperature2, &output2, &settemperature2, 2.5, 0.2 , 0, DIRECT);
PID myPID3(&temperature3, &output3, &settemperature3, 2.5, 0.2 , 0, DIRECT);

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
  
  // need jsoknit parser here e.g. { set heater 2 temp etc }
  
}

/*
double getTemp()
Return temperature to be set.
*/
double getTemp(int i)
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
  uint16_t iVar = thermocouple1.readCelsius(); // add thermocouple2 and thermocouple3
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
  pinMode(mosfetDrive1,OUTPUT);
  pinMode(mosfetDrive2,OUTPUT);
  pinMode(mosfetDrive3,OUTPUT);

  // get last stored temperature from EEPROM
  // might be better to let master node deal with 
  // initial values
  settemperature1 = getTemp(1);
  settemperature2 = getTemp(2);
  settemperature3 = getTemp(3);
  myPID1.SetMode(AUTOMATIC); 
  myPID2.SetMode(AUTOMATIC); 
  myPID3.SetMode(AUTOMATIC); 
  
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
    iAvgPID += output1;  
    // Service the PID
    servicePID1();
    servicePID2();
    servicePID3();
    // increment counter
    iCount++;
    
    if(SERIAL_DEBUG){
      Serial.print("iCount = ");
      Serial.println(iCount);  
      Serial.println("");  
    }
    
    // store reference time and temperature for deltas
    if(iCount == 1){dTemp[0] = thermocouple1.readCelsius();} 
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
void servicePID1()
Service PID.
*/
void servicePID1() {
  temperature1=thermocouple1.readCelsius();
  myPID1.Compute();
  if(isnan(output1)) {
    if(SERIAL_DEBUG){
      Serial.println("Output1 == nan");
    }
    raiseError();
  }
  analogWrite(mosfetDrive1, output1);
  if(SERIAL_DEBUG){
    Serial.print("TEMP1: ");
    Serial.println(temperature1);
    Serial.print("TEMP. PROG: ");
    Serial.println(settemperature1);  
    Serial.print("PID output: ");
    Serial.println(output1); 
    Serial.print("dTempVar: ");
    Serial.println(dTempVar); 
  }
}

/*
void servicePID2()
Service PID.
*/
void servicePID2() {
  temperature2=thermocouple2.readCelsius();
  myPID2.Compute();
  if(isnan(output2)) {
    if(SERIAL_DEBUG){
      Serial.println("Output2 == nan");
    }
    raiseError();
  }
  analogWrite(mosfetDrive2, output2);
  if(SERIAL_DEBUG){
    Serial.print("TEMP2: ");
    Serial.println(temperature2);
    Serial.print("TEMP2. PROG: ");
    Serial.println(settemperature2);  
    Serial.print("PID output2: ");
    Serial.println(output2); 
    Serial.print("dTempVar2: ");
    Serial.println(dTempVar); 
  }
}

/*
void servicePID3()
Service PID3.
*/
void servicePID3() {
  temperature3=thermocouple3.readCelsius();
  myPID3.Compute();
  if(isnan(output3)) {
    if(SERIAL_DEBUG){
      Serial.println("Output3 == nan");
    }
    raiseError();
  }
  analogWrite(mosfetDrive3, output3);
  if(SERIAL_DEBUG){
    Serial.print("TEMP3: ");
    Serial.println(temperature3);
    Serial.print("TEMP3. PROG: ");
    Serial.println(settemperature3);  
    Serial.print("PID output3: ");
    Serial.println(output3); 
    Serial.print("dTempVar3: ");
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
