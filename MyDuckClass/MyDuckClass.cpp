#include "Arduino.h"
#include "MyDuckClass.h"
MyDuckClass::MyDuckClass(int pinPropellor, int pinHeadingMotor, int pinHeadBobbing) {
    _pinProp = pinPropellor;
    _pinHM = pinHeadingMotor;
    _pinHB = pinHeadBobbing;
    //Remaining Private Variables 
    //_angleOfHeading
    //wayPoints[10]
    //_spotLockLocation
}

void MyDuckClass::calibrationOfMagnotometer(){
//Used to calibrate heading (IMPORTANT)
}

void MyDuckClass::turnOnProppellor(int propellorSpeed){
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
