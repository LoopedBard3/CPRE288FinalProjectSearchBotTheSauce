/*
 *	movementCommands.c
 *	Created on: September 11th, 2018
 *	Created by Parker Bibus.
 */

#include "movementCommands.h"

double yawCalibrationLeft;
double yawCalibrationRight;
double angleCalibrationValue;
double distanceCalibrationValue;
int movementSpeed;
int turnSpeed;

//Initializes the calibrationValues with calibrationValue being set to the left wheel and the speeds
//yawCalValue gives a calibration parameter for when the wheels don't change at the same speed with values <1 causing the left wheel to spin faster.
//void movement_init(int movementSpd = 250, int turnSpd = 250, double yawCalValue = 1.0, double distanceCalValue = 1.0, double angleCalValue = 1.0)
//{
//    yawCalibrationRight = yawCalValue;
//    yawCalibrationLeft = 2.0 - yawCalValue;
//    angleCalibrationValue = angleCalValue;
//    distanceCalibrationValue = distanceCalValue;
//    movementSpeed = movementSpd;
//    turnSpeed = turnSpd;
//}


//moves forward the specified distance in mm, returns the actual distance moved forwards
int moveForwards(oi_t *sensor, int dist)
{
    int sum = 0;    //Initialize aggregator variable to zero

    oi_setWheels(movementSpeed, yawCalibrationLeft*movementSpeed);//Start moving forward
    while (sum < dist)//Loop until we have gone the distance
    {
        oi_update(sensor);  //Update sensor data
        if (sensor->bumpLeft)//If the left bumper is hit
        {
            moveBackwards(sensor, 150); //Move backward 150 cm
            sum -= 150;//Decrease sum by the distance moved backward
            turnClockwise(sensor, 90);//Turn clockwise 90 degrees
            moveForwards(sensor, 250);//Move forward 250 cm
            turnCounterClockwise(sensor, 90);//Turn back to forward
            oi_setWheels(yawCalibrationRight*movementSpeed, yawCalibrationLeft*movementSpeed);//Continue moving forward
        }
        if (sensor->bumpRight) //If the right bumper is hit
        {
            moveBackwards(sensor, 150); //Move backward 150 cm
            sum -= 150;//Decrease sum by the distance moved backward
            turnCounterClockwise(sensor, 90);//Turn counter-clockwise 90 degrees
            moveForwards(sensor, 250);//Move forward 250 cm
            turnClockwise(sensor, 90);//Turn back to forward
            oi_setWheels(yawCalibrationRight*movementSpeed, yawCalibrationLeft*movementSpeed);//Continue moving forward
        }
        sum += distanceCalibrationValue*(sensor->distance); //Add the distance since last grab to the sum distance traveled
    }
    oi_setWheels(0, 0); //When complete, stop
    return sum;//Return the distance traveled.
}


//Moves backwards the specified distance in mm, returns the actual distance moved backwards
int moveBackwards(oi_t *sensor, int dist)
{
    int sum = 0;   //Initialize aggregator to 0
    oi_setWheels(-yawCalibrationRight*movementSpeed, -yawCalibrationLeft*movementSpeed);//Start moving backwards
    while (sum < dist)//Keep going backwards until the distance has been covered
    {
        oi_update(sensor);  //Keep refreshing the distance traveled
        sum -= distanceCalibrationValue*(sensor->distance);
    }
    return sum; //Return the distance covered
}



//Turns clockwise the specified angle in degrees, returns the actual degrees turned
int turnClockwise(oi_t *sensor, int deg)
{
    int sum = 0;    //Initialize aggregator to 0
    oi_setWheels(-yawCalibrationRight*turnSpeed, yawCalibrationLeft*turnSpeed);//Start turning clockwise
    while (sum < deg)//Keep turning clockwise until the angle has be met
    {
        oi_update(sensor);  //Keep refreshing the angle turned
        sum -= angleCalibrationValue*(sensor->angle);
    }
    oi_setWheels(0, 0); //Stop turning
    return sum; //Return the angle turned
}


//Turns counter-clockwise the specified angle in degrees, returns the actual degrees turned
int turnCounterClockwise(oi_t *sensor, int deg)
{
    int sum = 0;    //Initialize aggregator to 0
    oi_setWheels(yawCalibrationRight*turnSpeed, -yawCalibrationLeft*turnSpeed);//Start turning counter-clockwise
    while (sum < deg)//Keep turning counter-clockwise until the angle has been met
    {
        oi_update(sensor);  //Keep refreshing the angle turned
        sum += angleCalibrationValue*(sensor->angle);
    }
    oi_setWheels(0, 0); //Stop turning
    return sum; //Return the angle turned
}
