Arduino Zero, the $1 Arduino.
==============

Welcome to yesterday. Introducing the new generation of has-beens, the Arduino Zero. This fingerprint size (depending on the size of your thumb) device provides the following features:  

* Ability to burn a bootloader to an Atmega328p SMD.  
* Ability to upload code to an Atmega328p SMD.
* 5 output pins: PD0, PD1, D8, D9 and D10.  

To burn the bootloader and upload code, [follow these steps] (https://github.com/dsikar/arduino/tree/master/lcd-multinode-master-pidx3#notes-on-configuring-the-arduino-on-a-breadboard).   

Notice that when burning the bootloader, SCK, MOSI, MISO and RESET pins need to be wired. When uploading code, the required pins are RX, TX and RESET. In both cases, Ground and +5V need to be wired.  

The connectors on the board, from left to right, match the SL1 connector in the schematic from top to bottom.
![Arduino Zero board](images/board.png)

![Arduino Zero schematic](images/schematic.png)
