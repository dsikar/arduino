/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 12.12.2017 - Wired in to NodeMCU @dsikar
 */

#include <Wtv020sd16p.h>

/*
int resetPin = 4;  // The pin number of the reset pin.
int clockPin = 5;  // The pin number of the clock pin.
int dataPin = 6;  // The pin number of the data pin.
int busyPin = 7;  // The pin number of the busy pin.
*/

/*
 * Wiring
      
                  NodeMCU
                +------------+
                |            |
                |            | +------+  D1 (5)
                |            |
                |            | +------+  D2 (4)
                |            |
                |            |
                |            | +------+  D5 (14)
                |            |
                |            | +------+  D6 (12)
                |            |
                |            | +------+  GND
                |            |
                |            | +------+  3V3
                |            |
                +------------+

                    WTV020
                +-----------+
                |           |
  5   +-------+ | 1      16 | +------+ 3V3
                |        15 | +------+ 12
                |           |
  +   +-------+ | 4         |
  -   +-------+ | 5         |
                |           |
                |           |
  4   +-------+ | 7      10 | +------+ 14
  GND +-------+ | 8         |
                |           |
                +-----------+    
  
 */
int resetPin = 5;  // The pin number of the reset pin.
int clockPin = 4;  // The pin number of the clock pin.
int dataPin = 14;  // The pin number of the data pin.
int busyPin = 12;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup() {
  //Initializes the module.
  wtv020sd16p.reset();
}

void loop() {
  //Plays synchronously an audio file. Busy pin is used for this method.
  wtv020sd16p.playVoice(0);
  //Plays asynchronously an audio file.
  wtv020sd16p.asyncPlayVoice(1);
  //Plays audio file number 1 during 2 seconds.
  delay(5000);
  //Pauses audio file number 1 during 2 seconds.  
  wtv020sd16p.pauseVoice();
  delay(5000);
  //Resumes audio file number 1 during 2 seconds.
  wtv020sd16p.pauseVoice();
  delay(5000);  
  //Stops current audio file playing.
  wtv020sd16p.stopVoice();
  //Plays synchronously an audio file. Busy pin is used for this method.  
  wtv020sd16p.asyncPlayVoice(2);
  delay(2000);   
  //Mutes audio file number 2 during 2 seconds.
  wtv020sd16p.mute();
  delay(2000);
  //Unmutes audio file number 2 during 2 seconds.
  wtv020sd16p.unmute();
  delay(2000);    
  //Stops current audio file playing.
  wtv020sd16p.stopVoice();
}
