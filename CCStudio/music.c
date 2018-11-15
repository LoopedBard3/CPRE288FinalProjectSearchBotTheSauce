#include "music.h"

/**
 oi_t *sensor_data;

 void setup_musicSensor(oi_t *sensor_for_data){
 sensor_data = sensor_for_data;
 }
 */

void loadSongs()
{
    //SHARK LEN is actually supposed to be 30
    unsigned char SharkLen = 5;
    unsigned char SharkNotes[30] = { 62, 64, 67, 67, 67, 67, 67, 67, 62, 64, 67,
                                     67, 67, 67, 67, 67, 62, 64, 67, 67, 67, 67,
                                     67, 67, 67, 67, 66 };
    unsigned char SharkDurations[30] = { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                                         12, 12, 12, 12, 12, 12, 12 };
    oi_loadSong(BABY_SHARK, SharkLen, SharkNotes, SharkDurations);

    unsigned char MarioLen = 36;
    unsigned char MarioNotes[36] = { 64, 64, 64, 60, 64, 67, 72, 67, 64, 69, 71,
                                     70, 69, 67, 72, 76, 81, 77, 79, 76, 76, 77,
                                     74, 72, 67, 64, 69, 71, 70, 69, 67, 64, 62,
                                     72, 72, 72 };
unsigned char MarioDurations[36] = {   24, 24, 24, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12}
;
oi_loadSong(MARIO_THEME, MarioLen, MarioNotes, MarioDurations);
}
