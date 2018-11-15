#include "music.h"

// oi_t *sensor_data;  //Holder for the sensor data

// void setup_musicSensor(oi_t *sensor_for_data){
//     sensor_data = sensor_for_data;
// }

//Load our songs onto the roomba
void loadSongs(){
       unsigned char MarioLen = 30; //Length of the Mario song
       unsigned char MarioNotes[30]     = {55, 55, 55, 51, 58, 55, 51, 58, 55, 0,  62, 62, 62, 63, 58, 54, 51, 58, 55}; //Notes for the Mario song, 60 is middle C
       unsigned char MarioDurations[30] = {32, 32, 32, 20, 12, 32, 20, 12, 32, 32, 32, 32, 32, 20, 12, 32, 20, 12, 32}; //Duration for each note in the Mario song
       oi_loadSong(MARIO_VICTORY, MarioLen, MarioNotes, MarioDurations); //Loads the arrays onto the Roomba
}
