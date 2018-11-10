/*
 * SonarSensor.h
 *
 *  Created on: November 9th, 2018
 *      Author: Parker Bibus
 */

#include <stdbool.h>
#include "timer.h"
#include "driverlib/interrupt.h"

unsigned cycles2dist(unsigned cycles);
unsigned cycles2ms(unsigned cycles);
void send_pulse();
unsigned ping_read();
void setup_PING();
