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


//    unsigned char ImperialMarchNumNotes = 19;
//    unsigned char ImperialMarchNotes[19]     = {55, 55, 55, 51, 58, 55, 51, 58, 55, 0,  62, 62, 62, 63, 58, 54, 51, 58, 55};
//    unsigned char ImperialMarchDurations[19] = {32, 32, 32, 20, 12, 32, 20, 12, 32, 32, 32, 32, 32, 20, 12, 32, 20, 12, 32};
//    oi_loadSong(IMERPIAL_MARCH, ImperialMarchNumNotes, ImperialMarchNotes, ImperialMarchDurations);
}
