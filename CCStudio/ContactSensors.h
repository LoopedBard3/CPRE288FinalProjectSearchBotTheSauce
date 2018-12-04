/*
 * ContactSensors.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */
#include <stdbool.h>
#include "open_interface.h"

/**
 * Setup command that a previously setup oi_t to the local one.
 */
void setup_ContactSensors(oi_t *sensor_for_data);
/**
 * Updates the data from the sensors
 */
void updateContactSensors();
/**
 *Returns true if the left side bumper is being pressed
 */
bool bumperHitLeft();
/**
 * Returns true if the right side bumper is being pressed
 */
bool bumperHitRight();
/**
 * Returns true if there is a cliff on the left side of the Roomba
 */
bool cliffMiddleLeft();
/**
 * Returns true if there is a cliff on the front left side of the Roomba
 */
bool cliffFrontLeft();
/**
 * Returns true if there is a cliff on the front right side of the Roomba
 */
bool cliffFrontRight();
/**
 * Returns true if there is a cliff on the right side of the Roomba
 */
bool cliffMiddleRight();
/**
 * Returns true if any of the sensors are currently being triggered
 */
bool sensorTrip();
/**
 * Returns true if the Roomba is over a white boundary compared to the blue floors
 */
bool boundaryHit();
