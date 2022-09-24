#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>

#include <TinyGPSPlus.h>
TinyGPSPlus gps;
#include <QMC5883LCompass.h>
QMC5883LCompass compass;

Servo microServo; //Create Servo object
Servo Servo1; // Create Servo object

int pos = 0; // Position of Servo

void setup(){

  Serial.begin(9600);
  Serial2.begin(9600);
  compass.init();   //initialize QMC5883LCompass
  delay(3000);

////
//Below is where the pins are attached to the specic servo motor this allows us
//to control via a PWM


  //Atach servos to pins
  microServo.attach(25);
  Servo1.attach(26);
}


void loop() {
  int x, y , z, dy, dx, d; //Read QMC5883LCompass values
  compass.read();

  //Return XYZ readings
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

  dx = (x*.48828125);
  dy = (y*.48828125);

  d = atan(dy/dx)*(180/3.14);
  Serial.print("GPS heading: ");
  Serial.print(d);
  Serial.println();

//part below is not working
  if ((Serial2.available() > 0) ) {
    Serial.print(F("Location: "));
    if((gps.encode(Serial2.read()))){
      if (gps.location.isValid()) {
        
        Serial.print("Lat: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print("Lng: ");
        Serial.print(gps.location.lng(), 6);
        Serial.println();

      } else {

        Serial.print(F("INVALID"));

      }
    }

  }

  if (millis() > 5000 && gps.charsProcessed() < 10) {

    Serial.println(F("No GPS detected: check wiring."));

    while (true);

  }

    //Movement of servo motors
  for (pos = 0; pos <= 180; pos += 1){
    microServo.write(pos);
    Servo1.write(pos);
    delay(15);
  }

  for (pos = 180; pos >=0; pos -= 1){
   microServo.write(pos);
   Servo1.write(pos);
   delay(15);
 }

 /*runDCMotor();
  */
}
/*

void runDCMotor(){

  Serial.println( "Forward..." );
  // always stop motors briefly before abrupt changes
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  delay( DIR_DELAY );
  // set the motor speed and direction
  digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
  analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
  isValidInput = true;

  delay(10000);

  // 3) Soft stop (preferred)
  Serial.println( "Soft stop (coast)..." );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  isValidInput = true;

}*/
