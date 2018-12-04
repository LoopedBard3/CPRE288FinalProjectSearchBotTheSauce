/*
 * IRSensor.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */

#include <math.h>
#include "open_interface.h"

/**
 * Gets the IR reading distance
 */
int get_IR_dist();
/**
 * Calculate the distance from the IR sensor.
 */
int IR_distance_calc(int data);
/**
 * Setup for IR sensor
 */
void setup_IR();
