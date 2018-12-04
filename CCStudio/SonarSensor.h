/*
 * SonarSensor.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */
#include <stdbool.h>
#include "timer.h"
#include "driverlib/interrupt.h"

/**
 * Gets distance based on time
 */
unsigned cycles2dist(unsigned cycles);
/**
 * changes seconds to milliseconds
 */
unsigned cycles2ms(unsigned cycles);
/**
 * sends the pulse
 */
void send_pulse();
/**
 * Pings the sensor
 */
unsigned ping_read();
/**
 * Setup for Sonar Sensor
 */
void setup_PING();
