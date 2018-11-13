#include "music.h"

oi_t *sensor_data;

void setup_musicSensor(oi_t *sensor_for_data){
    sensor_data = sensor_for_data;
}

void loadSongs(){
       unsigned char MarioLen = 30;
       unsigned char MarioNotes[30]     = {55, 55, 55, 51, 58, 55, 51, 58, 55, 0,  62, 62, 62, 63, 58, 54, 51, 58, 55};
       unsigned char MarioDurations[30] = {32, 32, 32, 20, 12, 32, 20, 12, 32, 32, 32, 32, 32, 20, 12, 32, 20, 12, 32};
       oi_loadSong(MARIO_VICTORY, MarioLen, MarioNotes, MarioDurations);
}
