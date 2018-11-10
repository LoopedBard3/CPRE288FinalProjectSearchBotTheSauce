#include "ContactSensors.h"

oi_t *sensor_data;

void setup_ContactSensors(oi_t *sensor_for_data){
    sensor_data = sensor_for_data;
}

void updateContactSensors(){
    oi_update(sensor_data);
}

bool bumperHitLeft(){return sensor_data->bumpLeft;}
bool bumperHitRight(){return sensor_data->bumpRight;}
bool cliffMiddleLeft(){return sensor_data->cliffLeft;}
bool cliffFrontLeft(){return sensor_data->cliffFrontLeft;}
bool cliffFrontRight(){return sensor_data->cliffFrontRight;}
bool cliffMiddleRight(){return sensor_data->cliffRight;}
