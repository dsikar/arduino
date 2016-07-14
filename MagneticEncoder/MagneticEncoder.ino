// Read in 10-bits Magnetic Encoder AEAT-6010-A06  into Arduino Uno
// Original code by RobinL
// http://forum.arduino.cc/index.php?topic=164353.0
// with added delay and verbose serial output

// Declarate

const int CSn = 4; // Chip select
const int CLK = 7; // Clock signal
const int DO = 8; // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle..

unsigned int sensorWaarde = 0;

void setup(){

        Serial.begin(115200);
        
	//Fix de tris

	pinMode(CSn, OUTPUT);
	pinMode(CLK, OUTPUT);
	pinMode(DO, INPUT);

	//Let's start here
	digitalWrite(CLK, HIGH);
	digitalWrite(CSn, HIGH);
}



void loop() {

	sensorWaarde = readSensor();
	delayMicroseconds(1); //Tcs waiting for another read in
        // Longer delay to stop serial line from choking
        delay(500);
}

unsigned int readSensor(){
	unsigned int dataOut = 0;

	digitalWrite(CSn, LOW);
	delayMicroseconds(1); //Waiting for Tclkfe

	//Passing 10 times, from 0 to 9
	for(int x=0; x<10; x++){
		digitalWrite(CLK, LOW); 
		delayMicroseconds(1); //Tclk/2
		digitalWrite(CLK, HIGH);
		delayMicroseconds(1); //Tdo valid, like Tclk/2
		dataOut = (dataOut << 1) | digitalRead(DO); //shift all the entering data to the left and past the pin state to it. 1e bit is MSB
	}

	digitalWrite(CSn, HIGH);
       Serial.print("10 bit value: ");
       Serial.print(dataOut);
       Serial.print(" - Angle: ");
       Serial.println(dataOut * 0.3515625);
       return dataOut;

}
