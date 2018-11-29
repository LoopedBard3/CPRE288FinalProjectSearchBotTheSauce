#include "music.h"

/**
 oi_t *sensor_data;

 void setup_musicSensor(oi_t *sensor_for_data){
 sensor_data = sensor_for_data;
 }
 */

void loadSongs()
{
    //SHARK LEN is actually supposed to be 27
    unsigned char SharkLen = 4;
    unsigned char SharkNotes[27] = { 62, 64, 67, 67, 67, 67, 67, 67, 62, 64, 67,
                                     67, 67, 67, 67, 67, 62, 64, 67, 67, 67, 67,
                                     67, 67, 67, 67, 66 };
    unsigned char SharkDurations[27] = { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                                         12, 12, 12, 12, 12, 12, 12 };
    oi_loadSong(BABY_SHARK, SharkLen, SharkNotes, SharkDurations);

    //Up to 220 notes
    unsigned char EPICLength = 4;
    unsigned char EPICNotes[64] = { 79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84, 79, 84, 79, 84, 79, 84,
                                    79, 84, 79, 84 };
    unsigned char EPICDurations[64] = { 25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25,
                                        25, 25, 25, 25, 25, 25, 25, 25 };
    oi_loadSong(EPIC_MUSIC, EPICLength, EPICNotes, EPICDurations);
}
