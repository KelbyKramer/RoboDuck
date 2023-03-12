#ifndef MyDuckClass_h
#define MyDuckClass_h
#include "Arduino.h"
#include <TinyGPSPlus.h>
#include <QMC5883LCompass.h>
#include <ESP32Servo.h>

class MyDuckClass {
public:
  MyDuckClass(int pinPropellor, int pinPropDirection, int pinHeadingMotor, int pinHeadBobbing, TinyGPSPlus LocationGps, QMC5883LCompass HeadingCompass);
  //Used to calibrate heading (IMPORTANT)
  String calibrationOfMagnotometer();
  // Turning on/off DC motor to have Propellor run isOn == true -> ON
  void togglePropellor(bool isOn);
  //Set direction of Propellor
  void movePropHeading(int angleOfHeading);
  //get heading from magnotometer
  float GetDuckHeading();
  void navigateToLocation(double targetLat, double targetLng);


private:
  int _pinPropSpeed;
  int _pinPropDirection;
  int _pinHM;
  int _pinHB;
  int _angleOfHeading;
  TinyGPSPlus _GPS;
  QMC5883LCompass _HeadingCompass;
  Servo headBobbingServo;
  Servo PropellorServo;
  String _spotLockLocation;
    String _wayPoints[10];
};
#endif