/***
    Faux CRC - Enough space in EEPROM to backup data
    Duplicate data in EEPROM, if copy does not match
    original, data is corrupted, reset.
***/

#include <Arduino.h>
#include <EEPROM.h>


// DEFINES
// SELECTED ASTERISK OFFSET INDEXES
#define MENU_TRACKER_IDX 0
#define START_STOP_INDEX 1
#define UP_DOWN_INDEX 2
#define MAN_PROG_INDEX 3
#define CYCLES_INDEX 4
#define UP_SPEED_INDEX 5
#define DOWN_SPEED_INDEX 6
#define END_POS_INDEX 7
#define START_POS_INDEX 8
#define POS_INDEX 9

// CRC ADDRESSES
#define DATA_EEPROM_OFFSET 0
#define COPY_EEPROM_OFFSET 18 // 7 integers (14 bytes) 1 unsigned long (4 bytes)

// EEPROM stored struct
struct LCDState {
  int menuUpDown_EncoderValue;
  int menuManProg_EncoderValue;                                                                                                           
  int menuCycles_EncoderValue;
  int menuUpSpeed_EncoderValue;                                                       
  int menuDownSpeed_EncoderValue;                                                    
  int menuEndPos_EncoderValue;
  int menuStartPos_EncoderValue;
  unsigned long AbsoluteStepCount;    
};

LCDState lcd_state;

unsigned int uiAbsoluteStepCount = 0;

void init_struct(void)
{
  Serial.println("Initialising menu struct object");
  lcd_state.menuUpDown_EncoderValue = 1;
  lcd_state.menuManProg_EncoderValue = 2;
  lcd_state.menuCycles_EncoderValue = 3;
  lcd_state.menuUpSpeed_EncoderValue = 4;
  lcd_state.menuDownSpeed_EncoderValue = 5;
  lcd_state.menuEndPos_EncoderValue = 6;
  lcd_state.menuStartPos_EncoderValue = 7;
  lcd_state.AbsoluteStepCount = 0;
  uiAbsoluteStepCount = 0; 
}


/****************************
 * 
 * readConfigFromEEPROM
 * 
 * Read LCD State from EEPROM
 * 
 ****************************/
void readConfigFromEEPROM()
{
  // We use the global lcd_state struct and compare it with the local copy
  // Copy
  LCDState lcd_state_copy;

  // get state - EEPROM library manages variable addresses
  EEPROM.get(DATA_EEPROM_OFFSET, lcd_state); 
  // get state - EEPROM library manages variable addresses
  EEPROM.get(COPY_EEPROM_OFFSET, lcd_state_copy); 

  // Validate, if data is the same as copy
  if( (lcd_state.menuUpDown_EncoderValue == lcd_state_copy.menuUpDown_EncoderValue) &&
      (lcd_state.menuManProg_EncoderValue == lcd_state_copy.menuManProg_EncoderValue) &&
      (lcd_state.menuCycles_EncoderValue == lcd_state_copy.menuCycles_EncoderValue) &&
      (lcd_state.menuUpSpeed_EncoderValue == lcd_state_copy.menuUpSpeed_EncoderValue) &&
      (lcd_state.menuDownSpeed_EncoderValue == lcd_state_copy.menuDownSpeed_EncoderValue) &&
      (lcd_state.menuEndPos_EncoderValue == lcd_state_copy.menuEndPos_EncoderValue) &&
      (lcd_state.menuStartPos_EncoderValue == lcd_state_copy.menuStartPos_EncoderValue) &&
      (lcd_state.AbsoluteStepCount == lcd_state_copy.AbsoluteStepCount) )
  {
    Serial.println("No data corruption");
    // no corrupted bits, retrieve absolute position and populate menu struct objects
    uiAbsoluteStepCount == lcd_state.AbsoluteStepCount;
  } else
  { // else memory has been corrupted, keep blank values from initialisation
    Serial.print("Corrupted lcd_state.menuUpDown_EncoderValue: ");
    Serial.println(lcd_state.menuUpDown_EncoderValue);
    Serial.println("Data corrupted, resetting");
    delay(2000);
    init_struct();
  }

  Serial.print("lcd_state.menuUpDown_EncoderValue: ");
  Serial.println(lcd_state.menuUpDown_EncoderValue);
  Serial.print("lcd_state.uiAbsoluteStepCount: ");
  Serial.println(lcd_state.AbsoluteStepCount);
  delay(2000); 
}

/**************************
 * 
 * saveConfigToEEPROM
 * 
 * Save LCD State to EEPROM
 * 
 *************************/
 void saveConfigToEEPROM()
 {

  lcd_state.menuUpDown_EncoderValue = 20;
  //lcd_state.menuManProg_EncoderValue += 1;
  //lcd_state.menuCycles_EncoderValue+;
  //lcd_state.menuUpSpeed_EncoderValue;
  //lcd_state.menuDownSpeed_EncoderValue++;
  //lcd_state.menuEndPos_EncoderValue++;
  //lcd_state.menuStartPos_EncoderValue += 2;
  lcd_state.AbsoluteStepCount = uiAbsoluteStepCount;

  // Store state - EEPROM library manages variable addresses
  EEPROM.put(DATA_EEPROM_OFFSET, lcd_state);  

  // Store backup copy
  EEPROM.put(COPY_EEPROM_OFFSET, lcd_state); 

  Serial.print("lcd_state.menuUpDown_EncoderValue: ");
  Serial.println(lcd_state.menuUpDown_EncoderValue);
  Serial.print("lcd_state.uiAbsoluteStepCount: ");
  Serial.println(lcd_state.AbsoluteStepCount);   
}

// setup
void setup() {
  Serial.begin(9600);
  init_struct();
}
void loop() {  
  /* Empty loop */
  uiAbsoluteStepCount++;
  saveConfigToEEPROM();
  if(lcd_state.AbsoluteStepCount == 5) { 
    readConfigFromEEPROM();
  }  
  if(lcd_state.AbsoluteStepCount == 10) {
    // corrupt menu state saved to EEPROM
    EEPROM.put(DATA_EEPROM_OFFSET, 0x00);
    // CRC_info(); 
    readConfigFromEEPROM();
  }
  delay(2000);
}
