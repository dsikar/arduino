#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "LCDData.h"
#include "StepperPins.h"
#include <TimerOne.h>
#include <EEPROM.h>

/*******************
 * DP Control v0.02
 * ROADMAP
 * 1. Added Absolute Position 
 * 2. Saving current configuration to memory

 * Known bugs
 * 1. Unit needs to be started and stopped (play/pause cycle) and
 * restarted before absolute position can be taken. This seems
 * to be related to a bug in the EEPROM library.
 * 
 ******************/
 
// NB ADD U8g2lib and TimerOne via Tools > Include libraries > Manage libraries

// BOARDS - HERE WE DEFINE THE BOARDS (with respect to pins) 
// U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
// ATMEGA2560
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 23 /* A4 */ , /* data=*/ 17 /* A2 */, /* CS=*/ 16 /* A3 */, /* reset=*/ U8X8_PIN_NONE);
// UNO
// U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18 /* A4 */ , /* data=*/ 16 /* A2 */, /* CS=*/ 17 /* A3 */, /* reset=*/ U8X8_PIN_NONE);
// CONSTRU PCB
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 15 /* A4 */ , /* data=*/ 17 /* A2 */, /* CS=*/ 16 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

// Menu item struct to keep track of rotary 
// encoder and selected indexes
struct MenuItem
{
  // keep track of selection pot selected options
  volatile char lastEncoded;  
  volatile int encoderValue;
  volatile int lastEncoderValue;      
};

MenuItem menuItem[TOTAL_MENU_ITEMS] = {{4,4,4},  // LCD_MENU_X_POS 10 LCD_MENU_Y_POS 10 // OUR ASTERISK SELECTED TRACKER 
                       {0,0,0}, // on off LCD_START_STOP_X_POS 9 LCD_START_STOP_Y_POS 19
                       {0,0,0}, // up down  LCD_UP_DOWN_X_POS 30 LCD_UP_DOWN_Y_POS 19
                       {0,0,0}, // up speed LCD_SPEED_X_POS 30 LCD_SPEED_Y_POS 19 // (odd cycle) 
                       {0,0,0}, // DOWN_SPEED_INDEX                                                                     
                       {0,0,0}, // END_POS_INDEX
                       {0,0,0}, // START_POS_INDEX
                       {0,0,0}, // MAN_PROG_INDEX
                       {0,0,0}}; // CYCLES_INDEX               

// state machine variables
// 1. Track if speed update is required
bool bUpdateSpeed;
// 2. Track if rotary encoder button 
//    has been pushed
bool bOn = false;
// 3. Track current menu index 
int iMenuIdx = 0;
// 4. Absolute step count
unsigned int uiAbsoluteStepCount = 0;

/**************************
 * 
 * saveConfigToEEPROM
 * 
 * Save LCD State to EEPROM
 * 
 *************************/

 void saveConfigToEEPROM()
 {
  // Note we are saving and retrieving the lastEncoderValue for every menu item
  // except index 0 (Menu Controller) and index 1 (start/stop) as we will always
  // power up in pause mode
  
  // what we need to save  Data type  Note
  // 1. Absolute position  unsigned long 
  // 2. Up down state      byte
  // 3. Prog/Man state     byte
  // 4. Number of cycles   byte
  // 5. Up speed           uint 16
  // 6. Down speed         uint 16
  // 7. Up pos             uint 16
  // 8. Down pos           uint 16
   struct LCDState {
    int menuUpDown_EncoderValue;
    int menuManProg_EncoderValue;                                                                                                           
    int menuCycles_EncoderValue;
    int menuUpSpeed_EncoderValue;                                                       
    int menuDownSpeed_EncoderValue;                                                    
    int menuEndPos_EncoderValue;
    int menuStartPos_EncoderValue;
    int AbsoluteStepCount;    
  };
  
  // Populate struct objects
  LCDState lcd_state;
  lcd_state.menuUpDown_EncoderValue = menuItem[UP_DOWN_INDEX].encoderValue;
  lcd_state.menuManProg_EncoderValue = menuItem[MAN_PROG_INDEX].encoderValue;
  lcd_state.menuCycles_EncoderValue = menuItem[CYCLES_INDEX].encoderValue;
  lcd_state.menuUpSpeed_EncoderValue = menuItem[UP_SPEED_INDEX].encoderValue;
  lcd_state.menuDownSpeed_EncoderValue = menuItem[DOWN_SPEED_INDEX].encoderValue;
  lcd_state.menuEndPos_EncoderValue = menuItem[END_POS_INDEX].encoderValue;
  lcd_state.menuStartPos_EncoderValue = menuItem[START_POS_INDEX].encoderValue;
  lcd_state.AbsoluteStepCount = uiAbsoluteStepCount;

  // storage address
  int eeAddress = 0;
  // Store state - EEPROM library manages variable addresses
  EEPROM.put(eeAddress, lcd_state);  
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
  struct LCDState {
    int menuUpDown_EncoderValue;
    int menuManProg_EncoderValue;                                                                                                           
    int menuCycles_EncoderValue;
    int menuUpSpeed_EncoderValue;                                                       
    int menuDownSpeed_EncoderValue;                                                    
    int menuEndPos_EncoderValue;
    int menuStartPos_EncoderValue;
    int AbsoluteStepCount;    
  };

  // LCD struct
  LCDState lcd_state;

  // storage address
  int eeAddress = 0;
  // get state - EEPROM library manages variable addresses
  EEPROM.get(eeAddress, lcd_state);  

  // retrieve absolute position and populate menu struct objects
  menuItem[UP_DOWN_INDEX].encoderValue = lcd_state.menuUpDown_EncoderValue;
  menuItem[MAN_PROG_INDEX].encoderValue = lcd_state.menuManProg_EncoderValue;
  menuItem[CYCLES_INDEX].encoderValue = lcd_state.menuCycles_EncoderValue;
  menuItem[UP_SPEED_INDEX].encoderValue = lcd_state.menuUpSpeed_EncoderValue;
  menuItem[DOWN_SPEED_INDEX].encoderValue = lcd_state.menuDownSpeed_EncoderValue;
  menuItem[END_POS_INDEX].encoderValue = lcd_state.menuEndPos_EncoderValue;
  menuItem[START_POS_INDEX].encoderValue = lcd_state.menuStartPos_EncoderValue; 
  uiAbsoluteStepCount = lcd_state.AbsoluteStepCount; 
  // EEPROM library initialisation bug.
  // uiAbsoluteStepCount is 65535 when we expect 0
  if(uiAbsoluteStepCount == 65535)
  {
    uiAbsoluteStepCount = 0;
  }
}
 
 
/******************************
 * 
 * render()
 * LCD rendering engine
 * 
******************************/
void render(void) {

  char buf[5];
  int menuArraySize = sizeof(menuItem) / sizeof(menuItem[0]);
  int x_pos;
  int y_pos;
  int idx;
  
  for(int i = 0; i < menuArraySize; i++)
  { 
    switch(i)
    {
      case START_STOP_INDEX: 
            x_pos = getMenuItemProgMemVal(START_STOP_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(START_STOP_INDEX, Y_POS_INDEX);
            // Add one in case encoder value is 3 i.e. encoder was turned but only 3 was registered
            // instead of the expected 4
            if((menuItem[i].encoderValue / ENCODER_STEP) == 0)
            {
              // we are paused
              u8g2.setFont(u8g2_font_unifont_t_symbols);
              u8g2.drawGlyph(x_pos, y_pos, PAUSE_SYMBOL); 
              // UPDATE STATE MACHINE
            }
            else
            {
              // we are moving
              u8g2.setFont(u8g2_font_unifont_t_symbols);
              u8g2.drawGlyph(x_pos, y_pos, PLAY_SYMBOL);
              // UPDATE STATE MACHINE
            }
            //sprintf(buf, "[%d]", (menuItem[i].encoderValue / ENCODER_STEP));   
            //u8g2.drawStr( menuItem[i].xPos, menuItem[i].yPos, buf); 
            break;
      case UP_DOWN_INDEX: 
            x_pos = getMenuItemProgMemVal(UP_DOWN_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(UP_DOWN_INDEX, Y_POS_INDEX);
            if((menuItem[i].encoderValue / ENCODER_STEP) == 0)
            {
              // we are going up
              u8g2.setFont(u8g2_font_unifont_t_symbols);
              u8g2.drawGlyph(x_pos, y_pos, UP_SYMBOL);  /* dec 9731/hex 2603 Snowman */
              digitalWrite(DIRECTION_PIN, HIGH);
            }
            else
            {
              // we are going down
              u8g2.setFont(u8g2_font_unifont_t_symbols);
              u8g2.drawGlyph(x_pos, y_pos, DOWN_SYMBOL);
              digitalWrite(DIRECTION_PIN, LOW);
            }
            break;            
      case MAN_PROG_INDEX:
            // 1. Get x y coordinations
            x_pos = getMenuItemProgMemVal(MAN_PROG_INDEX, X_POS_INDEX);
            // Serial.println(START_POS_INDEX);
            y_pos = getMenuItemProgMemVal(MAN_PROG_INDEX, Y_POS_INDEX);
            //Serial.println(Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[MAN_PROG_INDEX].encoderValue / ENCODER_STEP);
            // 4. copy to buffer - different sytax
            strcpy_P(buf, (char*)pgm_read_word(&man_prog_table[idx])); 
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. print            
            u8g2.drawStr(x_pos, y_pos, buf); 
            break;

      case CYCLES_INDEX:
            // 1. Get x y coordinates
            x_pos = getMenuItemProgMemVal(CYCLES_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(CYCLES_INDEX, Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[CYCLES_INDEX].encoderValue / ENCODER_STEP);
            // 4. copy character array from cycles_table to buffer
            strcpy_P(buf, (char*)pgm_read_word(&cycles_table[idx])); 
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. print            
            u8g2.drawStr(x_pos, y_pos, buf); 
            break;
             
      case UP_SPEED_INDEX:
            // 1. Get x y coordinates        
            x_pos = getMenuItemProgMemVal(UP_SPEED_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(UP_SPEED_INDEX, Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[UP_SPEED_INDEX].encoderValue / ENCODER_STEP);

           // NOTE, this is where we deal with all speed change cases
            // and adjust timer interrupt
            if(bUpdateSpeed == true) // state machine: AND we are going up
            {
              adjustSpeed(); 
              bUpdateSpeed = false;             
            }
            // 4. Copy character array from speed_table to buffer
            strcpy_P(buf, (char*)pgm_read_word(&speed_table[idx])); 
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. Print nominal upward speed            
            u8g2.drawStr(x_pos, y_pos, buf);
            // 7. Print nominal speed rate unit
            u8g2.drawStr(x_pos + SPEED_RATE_OFFSET, y_pos, SPEED_RATE);      
            // 8. Print icon acronym
            //u8g2.drawStr(ICON_X_POS - ACRONYM_OFFSET, y_pos, "vs");  
            // 9. Set icon font
            u8g2.setFont(u8g2_font_unifont_t_symbols);
            // 10. Print icond
            u8g2.drawGlyph(ICON_X_POS, y_pos + ICON_Y_OFFSET, UP_SYMBOL);                           
            break;   
             
      case DOWN_SPEED_INDEX:
            // 1. Get x y coordinates
            x_pos = getMenuItemProgMemVal(DOWN_SPEED_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(DOWN_SPEED_INDEX, Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[DOWN_SPEED_INDEX].encoderValue / ENCODER_STEP);
            // 4. Copy character array from speed_table to buffer
            strcpy_P(buf, (char*)pgm_read_word(&speed_table[idx]));
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. Print nominal downward speed             
            u8g2.drawStr(x_pos, y_pos, buf); 
            // 7. Print nominal speed rate unit
            u8g2.drawStr(x_pos + SPEED_RATE_OFFSET, y_pos, SPEED_RATE); 
            // 8. Print icon acronym
            //u8g2.drawStr(ICON_X_POS - ACRONYM_OFFSET, y_pos, "vd");  
            // 9. Set icon font
            u8g2.setFont(u8g2_font_unifont_t_symbols);
            // 10. Print icond
            u8g2.drawGlyph(ICON_X_POS, y_pos + ICON_Y_OFFSET, DOWN_SYMBOL);              
            break;  

      case END_POS_INDEX:
            // 1. Get x y coordinations
            x_pos = getMenuItemProgMemVal(END_POS_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(END_POS_INDEX, Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[END_POS_INDEX].encoderValue / ENCODER_STEP);
            // 4. copy to buffer - different sytax
            // strcpy_P(buf, (char*)pgm_read_word(&speed_table[idx]));
            strcpy_P(buf, (char*)pgm_read_word(&distance_table[idx]));
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. print            
            u8g2.drawStr(x_pos, y_pos, buf); 
            // 7. print unit
            u8g2.drawStr(x_pos + SPEED_RATE_OFFSET, y_pos, DISTANCE_UNIT);
            // 8. Print icon acronym
            // u8g2.drawStr(ICON_X_POS - ACRONYM_OFFSET, y_pos, "vs");  
            // 9. Set icon font
            u8g2.setFont(u8g2_font_unifont_t_symbols);
            // 10. Print icond
            u8g2.drawGlyph(ICON_X_POS, y_pos + ICON_Y_OFFSET, DOWN_SYMBOL);             
            break; 
            
      case START_POS_INDEX:
            // 1. Get x y coordinations
            x_pos = getMenuItemProgMemVal(START_POS_INDEX, X_POS_INDEX);
            // Serial.println(START_POS_INDEX);
            y_pos = getMenuItemProgMemVal(START_POS_INDEX, Y_POS_INDEX);
            //Serial.println(Y_POS_INDEX);
            // 3. Get index      
            idx = (menuItem[START_POS_INDEX].encoderValue / ENCODER_STEP);
            // 4. copy to buffer - different sytax
            // strcpy_P(buf, (char*)pgm_read_word(&speed_table[idx]));
            strcpy_P(buf, (char*)pgm_read_word(&distance_table[idx]));
            // 5. Set font
            u8g2.setFont(u8g2_font_pcsenior_8f);
            // 6. print            
            u8g2.drawStr(x_pos, y_pos, buf);
            // 7. print unit
            u8g2.drawStr(x_pos + SPEED_RATE_OFFSET, y_pos, DISTANCE_UNIT);
            // 8. Print icon acronym
            //u8g2.drawStr(ICON_X_POS - ACRONYM_OFFSET, y_pos, "vs");  
            // 9. Set icon font
            u8g2.setFont(u8g2_font_unifont_t_symbols);
            // 10. Print icond
            u8g2.drawGlyph(ICON_X_POS, y_pos + ICON_Y_OFFSET, UP_SYMBOL);                      
            break;  
                     
      default:
        // do nothing
        break;  

/*
      // CASES TO ADD
      case WRITE_TO_EEPROM:
        break;

      case READ_FROM_EEPROM:
        break;

      case SAVED_ADDRESS:
        break;

      case ACTION_OK:
        break;
*/          
    }

    // EXTRAS
    // if this is the current active item, print an asterisk to denote state 
    if(i == (menuItem[0].encoderValue / ENCODER_STEP))
    { 
      x_pos = getMenuItemProgMemVal(i, X_POS_INDEX);
      y_pos = getMenuItemProgMemVal(i, Y_POS_INDEX);
      //Serial.println(x_pos);
      char asterisk_offset_x = getMenuItemProgMemVal(i, ASTERISK_X_OFFSET_INDEX);
      char asterisk_offset_y = getMenuItemProgMemVal(i, ASTERISK_Y_OFFSET_INDEX);         
      u8g2.setFont(u8g2_font_pcsenior_8f);
      u8g2.drawStr(x_pos - asterisk_offset_x, y_pos - asterisk_offset_y , "*"); 
    }

    // Print absolute location
    // 200 steps - 1.8mm
    // 111.111 steps = 1mm
    int iCurrentPos = uiAbsoluteStepCount / 112; // TODO FIX CALCULATION
    u8g2.setFont(u8g2_font_pcsenior_8f);    
    if(uiAbsoluteStepCount == 0) // we don't know where we are, print question marks
    {
      //strcpy_P(buf, (char*)pgm_read_word(&cycles_table[idx]));
      // sprintf(buf, "%07u", uiAbsoluteStepCount);
      // hash defines
      u8g2.drawStr(12, 59, NOT_CALIBRATED);
      //u8g2.drawStr(44, 59, buf);        
    }
    else
    {
      strcpy_P(buf, (char*)pgm_read_word(&distance_table[iCurrentPos]));      
      u8g2.drawStr(12, 59, buf);           
    }
    // print unit
    u8g2.drawStr(12 + SPEED_RATE_OFFSET, 59, DISTANCE_UNIT);   
  } 
}

/**********************************************
 * 
 * getMenuItemProgMemVal
 * retrieve values from menuItemProgMem array
 * 
 * @params i, k
 * multidimensional array indexes
 * 
 *********************************************/
unsigned int getMenuItemProgMemVal(int i, int k)
{
  /*
    We have an array of arrays that looks like this:
    const unsigned int menuController[3] PROGMEM = {3,10,10};
    const unsigned int menuStartPause[3] PROGMEM = {1,9,19};
    const unsigned int menuUpDown[3] PROGMEM = {1,30,19};   

    const uint16_t * const menuItem[] PROGMEM = { menuController, menuStartPause, menuUpDown, menuSpeed};

    we use pointer indexedMenuItem to access the address (reference) of menuItem 
    then access pgm_read_word(&indexedMenuItem[k]); value
   
   */
  unsigned int * indexedMenuItem = pgm_read_word(&menuItemProgMem[i]);
  return pgm_read_word(&indexedMenuItem[k]);  
}

/****************************************
 * updateStateMachine
 */
/************************
 * 
 * adjustSpeed()
 * Adjust up or down
 * speed
 * 
************************/
void adjustSpeed()
{
  unsigned int idx;
  // Which way are we going?
  if((menuItem[UP_DOWN_INDEX].encoderValue / ENCODER_STEP) == 0)
  {
    // we are going up, read speed from  up speed register
    idx = (menuItem[UP_SPEED_INDEX].encoderValue / ENCODER_STEP); 
  }
  else
  {
    // we are going down, read speed from  down speed register
    idx = (menuItem[DOWN_SPEED_INDEX].encoderValue / ENCODER_STEP);     
  }
  unsigned int half_frequency = pgm_read_word_near(frequencies + idx);;  
  Timer1.initialize(half_frequency);
}

/****************************
 * 
 * pushedButton()
 * Check if rotary encoder
 * has been pushed i.e.
 * a menu item has been
 * selected
 *
****************************/
void pushedButton(void)
{
  static int buttonPushCounter = 1;   // counter for the number of button presses
  static int buttonState = 1;         // current state of the button - active low
  static int lastButtonState = 1;     // previous state of the button - active low
  // read the pushbutton input pin:
  buttonState = digitalRead(ENCODER_SWITCH_PIN); 
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) 
  {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      buttonPushCounter++;   
    }
    if (buttonPushCounter == 3)
    {
      // reset, maybe less computation than taking remainder of large integer
      buttonPushCounter = 1;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  if (buttonPushCounter % 2 == 0) {
    bOn = true;
    SetMenuIndexTrack(bOn);
  } else {
    bOn = false;
    SetMenuIndexTrack(bOn);
  }  
}

// updateEncoder
/**********************************************************
 * Keep track of what index is being updated
 * Possible options
 * 1. Position of active control is being updated
 * update relevant index
 * 2. Control has been selected and is being updated
 * update relevantindex
***********************************************************/
void SetMenuIndexTrack(bool bOn)
{
  if(bOn == true)
  { 
    // Change value of highlighted menu option
    iMenuIdx = menuItem[0].encoderValue / ENCODER_STEP;  
  } 
  else
  {
    // change between menus
    iMenuIdx = 0; // menuItem[0].encoderValue / iEncStep;
  }
}

/****************************
 * 
 * GetMenuIndexTrack()
 * Which menu item is being
 * tracked
 *
****************************/
int GetMenuIndexTrack()
{
  return iMenuIdx; // menuItem[0].encoderValue / iEncStep;
}

/****************************
 * 
 * updateEncoder()
 * Keep track of state values e.g.
 * speed, direction, etc
 *
****************************/
void updateEncoder()
{
  // Called everytime Analog pins 2 or 3 are interrupted.
  // How it works
  // A turn to the right or left will generate several interrupts on both pins,
  // due probably to bouncing - see http://bildr.org/2012/08/rotary-encoder-arduino/
  // for more details.
  // A sum of expected clockwise and anticlockwise high/low states in general will tally to 4.
  // Occasionally we observe a total of less than 4, such as 2 and in rarer cases, 3,
  // generating a different offset, which we must account for - see iAbsMax.
    
  // get array we are tracking - this is to decided if we are switching between menu items or
  // changing the value of a specific menu item
  int iMit = GetMenuIndexTrack(); // if iMit equals 0, we are switching, otherwise, changing
  // iAbsMax - We add (ENCODER_STEP / 2) in case count is offset e.g. by 2 resulting in 2, 6, 10, 12, ...
  // get value from menuItemProgMem
  int arrMax = getMenuItemProgMemVal(iMit, ARR_MAX_INDEX);
  // int iAbsMax = (ENCODER_STEP * arrMax) + (ENCODER_STEP / 2);
  int iAbsMax = (ENCODER_STEP * arrMax);
  int iAbsMin = (iMit == 0 ? ENCODER_STEP : 0); // start at 4 for menu tracker, 0 otherwise
  int MSB = digitalRead(ENCODER_PIN_1); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_PIN_2); //LSB = least significant bit
  
  int encoded = (MSB << 1) |LSB; 
  //converting the 2 pin value to single number 
  int sum = (menuItem[iMit].lastEncoded << 2) | encoded;  
  //adding it to the previous encoded value 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011){
    if(menuItem[iMit].encoderValue < iAbsMax) {
      menuItem[iMit].encoderValue++;
    }
  }
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000){
    if(menuItem[iMit].encoderValue > iAbsMin) {
      menuItem[iMit].encoderValue--;    
    } 
  }
  // Correct if negative. Does not work. TODO
  // menuItem[iMit].encoderValue = (menuItem[iMit].encoderValue < 0 ? 0 : menuItem[iMit].encoderValue);
  
  // used for bitwise operations
  menuItem[iMit].lastEncoded = encoded;
  // update index only if boolean flag (cheaper) has changed
  // we are going to update this in the menu renderer

  // TODO IMPLEMENT STATE MACHINE AT THIS POINT E.G.
  // updateStateMachine();
  // 1. if we transitioned from running to stopped, save current location
  
  if(menuItem[iMit].lastEncoderValue != menuItem[iMit].encoderValue) 
  {
    // TODO implement in state machine later, for now, let's get it working
    if(iMit == START_STOP_INDEX)
    {
      // Check if we transitioned from play to pause
      if((menuItem[START_STOP_INDEX].encoderValue / ENCODER_STEP) == 0) // we have i.e. it was 1 (play) now it's 0 (pause)
      {
        saveConfigToEEPROM();
      }   
    }
//    if(iMit == UP_DOWN_INDEX)
//    {
      // Check if we transitioned from down to up, if yes, we have an absolute position, initialise counter
      // TODO change 0 for something sensible such as UP_INDEX 0
      // TODO we need to change this when we check the pins, not here, this would cause a reset if we changed the menu from down to up
//      if((menuItem[UP_DOWN_INDEX].encoderValue / ENCODER_STEP) == 0) // we have i.e. it was 1 (down) now it's 0 (up)
//      {
//        // 
//        uiAbsoluteStepCount = STEP_COUNTER_RESET; // initialise at STEP_COUNTER_RESET (5) as a safeguard for extra interrupt driven steps decrementing counter
//      }     
//    }
    // Update State Machine
    menuItem[iMit].lastEncoderValue = menuItem[iMit].encoderValue;
    // special case, speed changes, as this calls a timer interrupt
    // and we don't want it happening inside a function that is called
    // several times by pins 2 and 3 interrupts
    
    // State machine, if any transition between up/down, stop/pause, up speed/down speed, flag speed change required
    if(iMit == UP_SPEED_INDEX || iMit == DOWN_SPEED_INDEX || iMit == START_STOP_INDEX || iMit == UP_DOWN_INDEX  ) 
    {
      bUpdateSpeed = true;
    }
    
  }
}

/**************************************************
 * 
 * GetPositionIndex()
 * Turn absolute count into a value we can compare
 * with top and bottom possition indexes.
 * 
 *************************************************/
int GetPositionIndex(unsigned int iAbsStepCount)
{
  return 1;
}
/*************************************
 * 
 * updateStateMachine()
 * 
 * For lack of a better name
 * 
 * Keep track of what has changed
 * 
 *************************************/
 void updateStateMachine()
 {
    // Things we need to check
    // 1. Are more moving?
    if(menuItem[START_STOP_INDEX].encoderValue == PAUSED_INDEX)
    { // we are not, no action required
      return; 
    }
    // 2. Are we in programmed mode?
    if(menuItem[MAN_PROG_INDEX].encoderValue == MANUAL_INDEX)
    { // we are not, no action required
      return; 
    }
    // 3. We go this far, so we are moving and we are in programmed mode, get the indexes
    int endIdx = (menuItem[END_POS_INDEX].encoderValue / ENCODER_STEP);
    int startIdx = (menuItem[START_POS_INDEX].encoderValue / ENCODER_STEP);
    int currIdx = GetPositionIndex(uiAbsoluteStepCount);
    if(endIdx == startIdx)
    {
      // TODO decide what to do
    }
    if(currIdx == endIdx)
    {
      // TODO decide what to do
      // 1. What direction are we travelling?
      // If we are travelling up, reverse direction, decrease counter, if we are on 1, stop and return to manual mode
      // if we are travelling down, no action required
    }
    if(currIdx == startIdx)
    {
      // 1. What direction are we travelling?
      // If we are travelling down, reverse direction, decrease counter, if we are on 1, stop and return to manual mode
      // If we are travelling up, no action required.
    }    
    /*
          TODO implement limits logic
          Maximum for lower pos is top pos
          Minimum for top pos is lower pos

     
     */
  
 }
 
/**************************************
 * 
 * checkTopBottomLimits()
 * Check if we reached top or bottom
 * and update state machine accordingly
 * 
 **************************************/
void checkTopBottomLimits(void) {
  // Reached top
  if(digitalRead(TOP_PIN) == HIGH)
  {
    // Check if we are going up
    if((menuItem[UP_DOWN_INDEX].encoderValue / ENCODER_STEP) == 0)
    {
      // 1. We ARE going up - STOP!!!
      menuItem[START_STOP_INDEX].encoderValue = 0;
      // 2. Invert Up/Down Arrow
      menuItem[UP_DOWN_INDEX].encoderValue = ENCODER_STEP; // 4 e.g. second index of up down array (increments in counts of 4 most times.
      // 3. We stopped, save state
      saveConfigToEEPROM();
    }
  }
  if(digitalRead(BOTTOM_PIN) == HIGH)
  {
    // Check if we are going down
    if((menuItem[UP_DOWN_INDEX].encoderValue / ENCODER_STEP) == 1)
    {
      // 1. We ARE going down - STOP!!!
      menuItem[START_STOP_INDEX].encoderValue = 0;
      // reset counter
      uiAbsoluteStepCount = STEP_COUNTER_RESET;
      // 2. Invert Up/Down Arrow
      menuItem[UP_DOWN_INDEX].encoderValue = 0; // 0 e.g. up down index of up down array (increments in counts of 4 most times.
      // 3. We stopped, save state
      saveConfigToEEPROM();
    }   
  }
}

void setup(void) {
  u8g2.begin();

  // Encoder pins
  pinMode(ENCODER_PIN_1, INPUT); 
  pinMode(ENCODER_PIN_2, INPUT);
  pinMode(ENCODER_SWITCH_PIN,  INPUT);
 
  digitalWrite(ENCODER_PIN_1, HIGH); //turn pullup resistor on
  digitalWrite(ENCODER_PIN_2, HIGH); //turn pullup resistor on
  digitalWrite(ENCODER_SWITCH_PIN,  HIGH); //turn pullup resistor on

  pinMode(BOTTOM_PIN, INPUT);
  pinMode(TOP_PIN, INPUT);
  pinMode(DIRECTION_PIN, OUTPUT); 
  pinMode(PWM_PIN, OUTPUT);  

  // Set direction - TODO read initial state from EEPROM
  digitalWrite(PWM_PIN, HIGH); // we are pointing upwards
    
  // Encoder interrupts
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE); 

  Timer1.initialize(37500); // 37500 0,50 cm/min
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here  

  // Load values from last session
  readConfigFromEEPROM();
  
  // TODOS 
  // 1. SPLASH SCREEN
  
}

void loop(void) {
  u8g2.firstPage();
  do {
    pushedButton();
    render(); 
    // There is a 50ms debounce delay in pushedButton() 
    // so we are checking about twenty times per second
    checkTopBottomLimits();  
  } while ( u8g2.nextPage() );
  // delay(50);
}

/****************************************
 * updateCounter()
 * keep track of the absolute step count
 * 
 ****************************************/
 void updateCounter()
 {
    // What is the current state of counter?
    // 1. If we are not moving, it does not matter
    if((menuItem[START_STOP_INDEX].encoderValue / ENCODER_STEP) == PAUSED_INDEX)
    {
      return;
    }
    // 2. If counter == 0, we don't know where we are, don't do anything    
    if(uiAbsoluteStepCount == 0)
    {
      return; 
    }
    // 3. We have a position, track if we are going up or down and update counter
    if(uiAbsoluteStepCount > 0)
    {
      if((menuItem[UP_DOWN_INDEX].encoderValue / ENCODER_STEP) == UP_INDEX)
      { // we are going up, increase count
        uiAbsoluteStepCount++;
      }
      else
      { // we are going down, decrease count
        uiAbsoluteStepCount--;
      }  
    }
 }
 
/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
    // if(bOn == true) { // TODO USE A BETTER SCHEME
    if((menuItem[START_STOP_INDEX].encoderValue / ENCODER_STEP) == 1)
    {
      // Toggle LED at ISR Timer interval
      byte pinState = digitalRead( PWM_PIN );
      // digitalWrite( PWM_PIN, digitalRead( PWM_PIN ) ^ 1 );    
      digitalWrite( PWM_PIN, pinState ^ 1 );  
      if(pinState == HIGH)
      {
        // rising edge, add to position counter
        updateCounter();        
      }
    }
}
