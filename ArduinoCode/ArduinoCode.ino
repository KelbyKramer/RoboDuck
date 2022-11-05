#include "MyDuckClass.h"
//#include "Arduino.h”
MyDuckClass roboDuck(27,14,25,26);

void setup() {
  roboDuck.movePropHeading(90);
  Serial.begin(9600);
  Serial2.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
