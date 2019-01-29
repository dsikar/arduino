#include "U8glib.h"
 
 
#define encoderPin1 2
#define encoderPin2 3
#define pinEncButt 4
  
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
  
long lastencoderValue = 0;
  
int lastMSB = 0;
int lastLSB = 0;
 
U8GLIB_ST7920_128X64_1X u8g(15, 17, 16);
 
void draw(void) {
  u8g.setFont(u8g_font_fub11);
  u8g.drawStr( 0, 12, "Test Encoder");
 
  u8g.setFont(u8g_font_fub20);
   
  char buf[8];
  sprintf(buf, "%d %d",digitalRead(pinEncButt), encoderValue); 
  u8g.drawStr( 10, 40, buf);
 
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr( 0, 63, "www.mauroalfieri.it");
}
 
void updateEncoder(){
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);
  
  int encoded = (MSB << 1) |LSB;
  int sum  = (lastEncoded << 2) | encoded;
  
  if(sum==0b1101 || sum==0b0100 || sum==0b0010 || sum==0b1011) encoderValue++;
  if(sum==0b1110 || sum==0b0111 || sum==0b0001 || sum==0b1000) encoderValue--;
  
  lastEncoded = encoded; //store this value for next time
}
 
void setup(void) {
  Serial.begin(9600);
  if (u8g.getMode()==U8G_MODE_R3G3B2)        { u8g.setColorIndex(255); }
  else if (u8g.getMode()==U8G_MODE_GRAY2BIT) { u8g.setColorIndex(3); }
  else if (u8g.getMode()==U8G_MODE_BW)       { u8g.setColorIndex(1); }
  else if (u8g.getMode()==U8G_MODE_HICOLOR)  { u8g.setHiColorByRGB(255,255,255);}
   
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  pinMode(pinEncButt,  INPUT);
 
  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);
  digitalWrite(pinEncButt,  HIGH);
 
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}
  
void loop(void) {
  // Serial.println( digitalRead(pinEncButt) );
  u8g.firstPage();  
  do { draw(); } while( u8g.nextPage() );
    
  delay(50);
}
