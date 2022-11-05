#ifndef MyDuckClass_h
#define MyDuckClass_h
#include "Arduino.h"

class MyDuckClass {
    public:
        MyDuckClass(int pinPropellor,int pinPropDirection int pinHeadingMotor, int pinHeadBobbing);
            //Used to calibrate heading (IMPORTANT)
            void calibrationOfMagnotometer();
            // Turning on DC motor to have Propellor run
            void turnOnProppellor(int propellorSpeed, int propellorDirection);
            //Set direction of Propellor
            void movePropHeading(int angleOfHeading);
            // Spot lock for duck
            void spotLock(String spotLockLocation);
            //Get the current location of the duck
            String currentLocation();
            // Returns angle needed to get to waypoint
            int angleToWaypoint(String waypointLatLon);
      
    private:
        //Pins for Different motors being used
        int _pinProp,_pinPropDir, _pinHM, _pinHB;
        //Angle needed for heading
        int _angleOfHeading;
        // Array of Waypoints
        String _wayPoints[10];
        // Spot lock position
        String _spotLockLocation;
        

};

#endif