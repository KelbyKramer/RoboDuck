#include "Arduino.h"
#include "MyDuckClass.h"
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>
#include <TinyGPSPlus.h>
TinyGPSPlus gps;
#include <QMC5883LCompass.h>
QMC5883LCompass compass;
MyDuckClass::MyDuckClass(int pinPropellorSpeed, int pinPropellorDirection, int pinHeadingMotor, int pinHeadBobbing) {
    _pinPropSpeed = pinPropellorSpeed;
    _pinPropDirection = pinPropellorDirection;
    _pinHM = pinHeadingMotor;
    _pinHB = pinHeadBobbing;
    //Remaining Private Variables 
    //_angleOfHeading
    //wayPoints[10]
    //_spotLockLocation
    Servo headBobbingServo;
    Servo PropellorServo;
    headBobbingServo.Attach(_pinHM);
    PropellorServo.Attach(_pin);


}   

void MyDuckClass::calibrationOfMagnotometer(){
//Used to calibrate heading (IMPORTANT)
}

void MyDuckClass::turnOnProppellor(int propellorSpeed, int propellorDirection){
// Turning on DC motor to have Propellor run


}

void MyDuckClass::movePropHeading(int angleOfHeading){
//Set direction of Propellor
}

void MyDuckClass::spotLock(String spotLockLocation){
// Spot lock for duck
}

String MyDuckClass::currentLocation(){
//Get the current location of the duck
}

int MyDuckClass::angleToWaypoint(String waypointLatLon){
// Returns angle needed to get to waypoint
}
