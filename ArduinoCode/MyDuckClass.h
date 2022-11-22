#ifndef MyDuckClass_h
#define MyDuckClass_h
#include "Arduino.h"


class MyDuckClass {
    public:
        MyDuckClass(int pinPropellor,int pinPropDirection, int pinHeadingMotor, int pinHeadBobbing);
            //Used to calibrate heading (IMPORTANT)
            String calibrationOfMagnotometer();
            // Turning on DC motor to have Propellor run
            void turnOnProppellor(int propellorSpeed, int propellorDirection);

            void turnOffProppellor(int propellorSpeed, int propellorDirection);
            //Set direction of Propellor
            void movePropHeading(int angleOfHeading);
            // Spot lock for duck
            void spotLock(float spotLockLocation[2]);
            //Get the current location of the duck
            float * currentLocation();
            // Returns angle needed to get to waypoint
            float angleToWaypoint (float waypointLatLonCur[2], float waypointLatLon[2]);
            //Get distance to specified waypoint
            float distanceToWaypoint(float waypointLatLonCur[2], float desiredpointLatLon[2]);
            //get heading from magnotometer
            float GetDuckHeading() ;

      
    private:
        //Pins for Different motors being used
        int _pinPropSpeed,_pinPropDirection, _pinHM, _pinHB;
        //Angle needed for heading
        int _angleOfHeading;
        // Array of Waypoints
        String _wayPoints[10];
        // Spot lock position
        String _spotLockLocation;
        

};
#endif
