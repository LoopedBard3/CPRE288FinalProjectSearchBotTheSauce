/*
 * ContactSensors.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */
#include <stdbool.h>
#include "open_interface.h"


void setup_ContactSensors(oi_t *sensor_for_data);
void updateContactSensors();
bool bumperHitLeft();
bool bumperHitRight();
bool cliffMiddleLeft();
bool cliffFrontLeft();
bool cliffFrontRight();
bool cliffMiddleRight();
bool sensorTrip();
bool boundaryHit();


