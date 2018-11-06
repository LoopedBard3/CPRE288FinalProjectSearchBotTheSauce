/*
*	movementCommands.h
*	Created on: September 11th, 2018
*	Created by Parker Bibus.
*/

#include "open_interface.h"

double yawCalibrationLeft;
double yawCalibrationRight;
double speedCalibrationValue;
int movementSpeed;
int turnSpeed;

//Initializes the calibrationValues with calibrationValue being set to the left wheel and the speeds
//void movement_init(int movementSpd = 250, int turnSpd = 250, double yawCalValue = 1.0, double distanceCalValue = 1.0, double angleCalValue = 1.0);

//moves forward the specified distance in mm, returns the actual distance moved forwards
int moveForwards(oi_t *sensor, int dist);

//Moves backwards the specified distance in mm, returns the actual distance moved backwards
int moveBackwards(oi_t *sensor, int dist);

//Turns clockwise the specified angle in degrees, returns the actual degrees turned
int turnClockwise(oi_t *sensor, int deg);

//Turns counter-clockwise the specified angle in degrees, returns the actual degrees turned
int turnCounterClockwise(oi_t *sensor, int deg);
