#include "Arduino.h"
#include <math.h> /* atan2 */
#include "MyDuckClass.h"
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>
#include <TinyGPSPlus.h>
#include <QMC5883LCompass.h>


MyDuckClass::MyDuckClass(int pinPropellorSpeed, int pinPropellorDirection, int pinHeadingMotor, int pinHeadBobbing, TinyGPSPlus LocationGps, QMC5883LCompass HeadingCompass)
  : _pinPropSpeed(pinPropellorSpeed),
    _pinPropDirection(pinPropellorDirection),
    _pinHM(pinHeadingMotor),
    _pinHB(pinHeadBobbing),
    _GPS(LocationGps),
    _HeadingCompass(HeadingCompass),
    headBobbingServo(),
    PropellorServo() {
  headBobbingServo.attach(_pinHB);
  PropellorServo.attach(_pinHM);
}

String MyDuckClass::calibrationOfMagnotometer() {
  //Used to calibrate heading (IMPORTANT)
  Servo PropellorServo;
  //Turn heading to face perpendicular to duck decoy
  PropellorServo.write(270);
  digitalWrite(_pinPropDirection, HIGH);  // direction = forward
  analogWrite(_pinPropSpeed, -255);       // PWM speed = fast max is 255
  delay(3000);                            // Delay for 3 seconds to allow propper heading of propellor

  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;

  while (done != true) {

    int x, y, z;
    // Read compass values
    _HeadingCompass.read();
    // Return XYZ readings
    x = _HeadingCompass.getX();
    y = _HeadingCompass.getY();
    z = _HeadingCompass.getZ();
    changed = false;

    if (x < calibrationData[0][0]) {
      calibrationData[0][0] = x;
      changed = true;
    }
    if (x > calibrationData[0][1]) {
      calibrationData[0][1] = x;
      changed = true;
    }

    if (y < calibrationData[1][0]) {
      calibrationData[1][0] = y;
      changed = true;
    }
    if (y > calibrationData[1][1]) {
      calibrationData[1][1] = y;
      changed = true;
    }

    if (z < calibrationData[2][0]) {
      calibrationData[2][0] = z;
      changed = true;
    }
    if (z > calibrationData[2][1]) {
      calibrationData[2][1] = z;
      changed = true;
    }

    if (changed && !done) {

      c = millis();
    }
    t = millis();


    if ((t - c > 5000) && !done) {
      done = true;

      String result = "_HeadingCompass.setCalibration(";

      result = result + calibrationData[0][0] + "," + calibrationData[0][1] + "," + calibrationData[1][0] + "," + calibrationData[1][1] + "," + calibrationData[2][0] + "," + calibrationData[2][1] + ");";
      return result;
    }
  }
}


void MyDuckClass::togglePropellor(bool isOn) {

  if (isOn) {
    // Motor is turned on
    digitalWrite(_pinPropDirection, HIGH);
    analogWrite(_pinPropSpeed, 50);
  } else {
    // Motor is turned off
    digitalWrite(_pinPropDirection, LOW);
    digitalWrite(_pinPropSpeed, LOW);
  }
}


//Change heading of the propellor motor using the servo motor
void MyDuckClass::movePropHeading(int angleOfHeading) {
  //Set direction of Propellor
  headBobbingServo.write(angleOfHeading);
}


float MyDuckClass::GetDuckHeading() {
  int x, y, z, dy, dx, d, azimuth;  //Read QMC5883LCompass values

  _HeadingCompass.read();

  //Return XYZ readings
  x = _HeadingCompass.getX();
  y = _HeadingCompass.getY();
  z = _HeadingCompass.getZ();
  azimuth = _HeadingCompass.getAzimuth();
  char myArray[3];
  _HeadingCompass.getDirection(myArray, azimuth);
  Serial.print(myArray[0]);
  Serial.print(myArray[1]);
  Serial.print(myArray[2]);
  Serial.println();
  Serial.print(x);
  Serial.print(y);
  Serial.print(z);

  dx = (x * .48828125);
  dy = (y * .48828125);

  d = atan(dy / dx) * (180 / 3.14);
  float result = d;

  return result;
}

void MyDuckClass::navigateToLocation(double targetLat, double targetLng) {
  // Get current location and heading
  double currentLat = _GPS.location.lat();
  double currentLng = _GPS.location.lng();
  double currentHeading = GetDuckHeading();

  // Calculate distance and bearing to target location
  double distance = TinyGPSPlus::distanceBetween(currentLat, currentLng, targetLat, targetLng);
  double bearing = TinyGPSPlus::courseTo(currentLat, currentLng, targetLat, targetLng);

  // Turn towards target location
  double headingError = bearing - currentHeading;
  if (headingError > 180) {
    headingError -= 360;
  } else if (headingError < -180) {
    headingError += 360;
  }
  int servoPosition = map(headingError, -180, 180, 0, 180);
  PropellorServo.write(servoPosition);

  // Go towards target location
  togglePropellor(true);
  //digitalWrite(_motorPin, HIGH);
  while (distance > 3.0) {
    currentLat = _GPS.location.lat();
    currentLng = _GPS.location.lng();
    distance = TinyGPSPlus::distanceBetween(currentLat, currentLng, targetLat, targetLng);
  }
  //digitalWrite(_motorPin, LOW);
  togglePropellor(false);
}
