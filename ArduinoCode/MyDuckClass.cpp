#include "Arduino.h"
#include "MyDuckClass.h"
#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>
//#include <TinyGPSPlus.h>
//TinyGPSPlus gps;
//#include <QMC5883LCompass.h>
//QMC5883LCompass compass;
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
    headBobbingServo.attach(_pinHM);
    PropellorServo.attach(_pinHB);


}   

void MyDuckClass::calibrationOfMagnotometer(){
//Used to calibrate heading (IMPORTANT)
int x = 1;
}

void MyDuckClass::turnOnProppellor(int propellorSpeed, int propellorDirection){
// Turning on DC motor to have Propellor run
int x = 1;

}

void MyDuckClass::movePropHeading(int angleOfHeading){
//Set direction of Propellor
    Servo headBobbingServo;
    headBobbingServo.attach(_pinHM);

  headBobbingServo.write(angleOfHeading);
}

void MyDuckClass::spotLock(String spotLockLocation){
// Spot lock for duck
int x = 1;
}

String MyDuckClass::currentLocation(){
//Get the current location of the duck
int x = 1;
}

int MyDuckClass::angleToWaypoint(String waypointLatLon){ 
// Returns angle needed to get to waypoint
int x = 1;
}
