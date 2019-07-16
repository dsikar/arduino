/*
  Low Cost Flame Detector 


            NodeMCU x MH Sensor Series Wiring Diagram
                                                 +------------+
  +----------------------+                       |   NodeMCU  |
  |                  A0  | +---+ A0              |            |
  | MH Sensor Series GND | |---| GND    A0 +---+ | A0         |
  |                  VCC | +---+ 3.3V            |        GND | +---+ GND
  +----------------------+                       |       3.3V | +---+ VCC
                                                 +------------+

 */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned int AnalogValue;
  AnalogValue = analogRead(A0);
  Serial.println(AnalogValue);
  delay(1000);
}
