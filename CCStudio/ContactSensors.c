#include "ContactSensors.h"

oi_t *sensor_data;  //Holder that allows us to get the data from the Roomba

//Setup command that a previously setup oi_t to the local one.
void setup_ContactSensors(oi_t *sensor_for_data){
    sensor_data = sensor_for_data;
}

//Updates the data from the sensors
void updateContactSensors(){
    oi_update(sensor_data);
}

bool bumperHitLeft(){return sensor_data->bumpLeft;} //Returns true if the left side bumper is being pressed
bool bumperHitRight(){return sensor_data->bumpRight;} //Returns true if the right side bumper is being pressed
bool cliffMiddleLeft(){return sensor_data->cliffLeft;} //Returns true if there is a cliff on the left side of the Roomba
bool cliffFrontLeft(){return sensor_data->cliffFrontLeft;} //Returns true if there is a cliff on the front left side of the Roomba
bool cliffFrontRight(){return sensor_data->cliffFrontRight;}  //Returns true if there is a cliff on the front right side of the Roomba
bool cliffMiddleRight(){return sensor_data->cliffRight;} //Returns true if there is a cliff on the right side of the Roomba

//Returns true if any of the sensors are currently being triggered
bool sensorTrip(){
    return (bumperHitLeft()||bumperHitRight()||cliffMiddleLeft()||cliffMiddleRight()||cliffFrontLeft()||cliffFrontRight()||boundaryHit() );
}

//Returns true if the Roomba is over a white boundary compared to the blue floors
bool boundaryHit(){
    return (sensor_data->cliffLeftSignal) > 2600 || (sensor_data->cliffRightSignal) > 2600 || (sensor_data->cliffFrontLeftSignal) > 2600
            || (sensor_data->cliffFrontRightSignal) > 2600;
}
