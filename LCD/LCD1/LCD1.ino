#include "U8glib.h"
 
U8GLIB_ST7920_128X64_1X u8g(18, 16, 17); // SPI Com: en=18,rw=16,di=17
 
void draw(void) {
  u8g.setFont(u8g_font_fub49n);
  u8g.drawStr( 0, 56, "123");
}
 
void setup(void) {
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}
 
void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
   
  delay(50);
}
