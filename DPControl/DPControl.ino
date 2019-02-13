#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "LCDData.h"
#include "StepperPins.h"
#include <TimerOne.h>
#include "MemoryFree.h"

// NB ADD U8g2lib and TimerOne via Tools > Include libraries > Manage libraries

// U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
// ATMEGA2560
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 23 /* A4 */ , /* data=*/ 17 /* A2 */, /* CS=*/ 16 /* A3 */, /* reset=*/ U8X8_PIN_NONE);
/*
  CONNECTIONS
  5V  %V
  GND GND   
 */
// UNO
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18 /* A4 */ , /* data=*/ 16 /* A2 */, /* CS=*/ 17 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

// PCB
// U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 15 /* A4 */ , /* data=*/ 17 /* A2 */, /* CS=*/ 16 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

// OUR GENERIC STRUCT
struct MenuItem
{
  int arrMax; // used to calculate iAbsMax, note for menu tracker this number matches the number of active items, i.e. values we need to keep track off such as programmed speed, etc
              // exception would be current location
  volatile char lastEncoded; // used for the selection pot wet to 
  volatile int encoderValue;
  int lastEncoderValue; 
  byte xPos;
  byte yPos;        
};

MenuItem menuItem[4] = {{3,3,4,4,10,10}, // magic numbers, start at array position 1 IMPORTANT: NEED TO +1 to array size menuItem[4] for every item added
                                             // LCD_MENU_X_POS 10 LCD_MENU_Y_POS 10 // OUR ASTERISK SELECTED TRACKER
                       {1,0,0,0,9,19}, // on off LCD_START_STOP_X_POS 9 LCD_START_STOP_Y_POS 19
                       {1,0,0,0,30,19}, // up down  LCD_UP_DOWN_X_POS 30 LCD_UP_DOWN_Y_POS 19
                       {108,0,0,0,55,19}}; // speeds LCD_SPEED_X_POS 30 LCD_SPEED_Y_POS 19 // (odd cycle)  
                       // {0,301,0,0,0,0,10,55}}; // speed anti-cycle (even cycle)                                             
                       // {0,301,0,0,0,0,10,55}}; // distance covered // add cycles later 
                       // {0,301,0,0,0,0,10,55}};    // start UP
                       // {0,301,0,0,0,0,10,55}};    // start down                       
                       //{0,1,0,0,0,0,10,55}};  // end                      // manual/prog

// Encoder limits - outside these do not increment or decrement encoder value
//int iAbsMin = 0;
// Do not go above 14 NB this is in case there is a slight offset in read values, e.g. initial absolute value jumps from 0 to 2. TODO investigate jumps of 3.
//int iAbsMax = (ENCODER_STEP * arrMax) + (ENCODER_STEP / 2);

bool bUpdateSpeed;

// state machine
bool bOn = false;
bool bButtonReleased = true;
bool bButtonPushed = false;

// state machine keep track of current menu index 
int iMenuIdx = 0;

/******************************

 Screw renderer

******************************/
void render(void) {
  // read state of digital pin
  char buf[15];

  u8g2.setFont(u8g2_font_unifont_t_symbols);
  // u8g2.drawGlyph(50, 20, 0x23f6);  /* dec 9731/hex 2603 Snowman */
  
  // u8g2.setFont(u8g2_font_pcsenior_8f);  
  // Get asterisk position, stored as encoder value in first MenuItem struct
  // int iMit = GetMenuIndexTrack(); 
  int menuArraySize = sizeof(menuItem) / sizeof(menuItem[0]);
  int x_pos;
  int y_pos;
  for(int i = 0; i < menuArraySize; i++)
  {
    switch(i)
    {
      case START_STOP_INDEX: 
            x_pos = getMenuItemProgMemVal(START_STOP_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(START_STOP_INDEX, Y_POS_INDEX);
            if((menuItem[i].encoderValue / ENCODER_STEP) == 0)
            {
              // we are paused
              u8g2.drawGlyph(x_pos, y_pos, PAUSE_SYMBOL); 
              // UPDATE STATE MACHINE
            }
            else
            {
              // we are moving
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
              u8g2.drawGlyph(x_pos, y_pos, UP_SYMBOL);  /* dec 9731/hex 2603 Snowman */
              digitalWrite(DIRECTION_PIN, HIGH);
            }
            else
            {
              // we are going down
              u8g2.drawGlyph(x_pos, y_pos, DOWN_SYMBOL);
              digitalWrite(DIRECTION_PIN, LOW);
            }
            break;            
      case SPEED_INDEX:
            x_pos = getMenuItemProgMemVal(SPEED_INDEX, X_POS_INDEX);
            y_pos = getMenuItemProgMemVal(SPEED_INDEX, Y_POS_INDEX);      
            int idx = (menuItem[3].encoderValue / ENCODER_STEP);
           
            // if speed changed, adjust timer interrupt
            if(bUpdateSpeed == true)
            {
              // NB adjustSpeed will convert argument to unsigned int
              unsigned int displayInt = pgm_read_word_near(frequencies + idx);
              adjustSpeed(displayInt); 
              bUpdateSpeed = false;             
            }

            // strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i])));

            strcpy_P(buf, (char*)pgm_read_word(&speed_table[idx]));
            // this line is breaking our code 
            // -sprintf(buf, "[%s]", speeds[(menuItem[i].encoderValue / iEncStep)]); 
            // speeds[(menuItem[i].encoderValue / iEncStep)]
            // TODO DEBUG COMMENT IN  
            u8g2.setFont(u8g2_font_pcsenior_8f);            
            u8g2.drawStr(x_pos, y_pos, buf); 
            u8g2.drawStr(x_pos + SPEED_RATE_OFFSET, y_pos, SPEED_RATE); 

            // debug speed
             // sprintf(buf, "[%d]", frequencies[(menuItem[3].encoderValue / ENCODER_STEP)]);
             // int idx = (menuItem[3].encoderValue / ENCODER_STEP);
             // unsigned int displayInt = pgm_read_word_near(frequencies + idx);
             int displayInt = pgm_read_word_near(&frequencies[idx]);
             // int displayInt = freeMemory();
             sprintf(buf, "[%u]", displayInt);
             u8g2.drawStr( 10, 55, buf);
             sprintf(buf, "[%u]", idx);
             
             // TODO DEBUG COMMENT IN
             u8g2.drawStr( 10, 40, buf);            
            break;  
      // distances
      case 4: 
            //strcpy_P(buf, (char*)pgm_read_word(&(distance_table[menuItem[i].encoderValue / ENCODER_STEP])));
            // sprintf(buf, "[%d]", (menuItem[i].encoderValue / iEncStep));   
            //u8g2.drawStr( menuItem[i].xPos, menuItem[i].yPos, buf);
            break;
      case 0:
        break;
      // TODO CASES
      // Cycles x/y x = programmed, y = completed
      // Speed up
      // speed down SPEED_DOWN_INDEX
      // start pos  START_POS_INDEX
      // end pos    END_POS_INDEX
      // current pos  CURRENT_POS_INDEX
      // direction up/down 
      // ??? Mode Manual/Auto // MANUAL_PROG_INDEX
      // ??? Calibrate CALIBRATE_INDEX
      // Save SAVE_INDEX  
    }
    // if this is the current active item, print an asterisk to denote state 
    if(i == (menuItem[0].encoderValue / ENCODER_STEP))
    {
      // TODO make offsets variables      
      u8g2.drawStr( menuItem[i].xPos - 5, menuItem[i].yPos, "*"); 
    }
  } 
}

// retrieve values from menuItemProgMem array

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

void adjustSpeed(unsigned int displayInt)
{
  Timer1.initialize(displayInt);
}
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
/**************************************
 * Keep track of what index is being updated
 * Possible options
 * 1. Position of active control is being updated
 * update relevant index
 * 2. Control has been selected and is being updated
 * update relevantindex
 * TODO each control will have unique min and max pairs
 */

void SetMenuIndexTrack(bool bOn)
{
  if(bOn == true)
  { 
    // Change value of highlighted menu option
    iMenuIdx = menuItem[0].encoderValue / ENCODER_STEP;  
  } else
  {
    // change between menus
    iMenuIdx = 0; // menuItem[0].encoderValue / iEncStep;
  }
}

int GetMenuIndexTrack()
{
  return iMenuIdx; // menuItem[0].encoderValue / iEncStep;
}

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
  int iAbsMax = (ENCODER_STEP * arrMax) + (ENCODER_STEP / 2);
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
  // used for bitwise operations
  menuItem[iMit].lastEncoded = encoded;
  // update index only if boolean flag (cheaper) has changed
  // we are going to update this in the menu renderer
  if(menuItem[iMit].lastEncoderValue != menuItem[iMit].encoderValue) 
  {
    menuItem[iMit].lastEncoderValue = menuItem[iMit].encoderValue;
    // special case, speed changes, as this calls a timer interrupt
    // and we don't want it happening inside a function that is called
    // several times by pins 2 and 3 interrupts
    if(iMit == SPEED_INDEX)
    {
      bUpdateSpeed = true;
    }
  }
  // Todo, keep track of changes
  
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
}

void checkPins(void) {
  // Top pin
  // Bottom pin
}
void loop(void) {
  u8g2.firstPage();
  do {
    pushedButton();
    render(); 
    //checkPins();  
  } while ( u8g2.nextPage() );
  // delay(50);
}

/// --------------------------
/// Custom ISR Timer Routine
/// --------------------------
void timerIsr()
{
    // if(bOn == true) { // TODO USE A BETTER SCHEME
    if((menuItem[1].encoderValue / ENCODER_STEP) == 1)
    {
      // Toggle LED at ISR Timer interval
      digitalWrite( PWM_PIN, digitalRead( PWM_PIN ) ^ 1 );      
    }
}
