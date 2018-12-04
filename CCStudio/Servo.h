/*
 * Servo.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */

#include "timer.h"

/**
 * Move the servo to the specified degrees. Try also setting TBILR in this method
 */
int move_servo(double degree);
/**
 * Set up for the Servo Motor
 */
void setup_servo();
