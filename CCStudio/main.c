#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "driverlib/interrupt.h"
#include "open_interface.h"
#include "ContactSensors.h"
#include "IRSensor.h"
#include "Servo.h"
#include "SonarSensor.h"
#include "music.h"

char left_wheel_speed = 0;
char right_wheel_speed = 0;
char sensorTripDistance = 20;


int IR_dist = 0;        //IR Distance
int sonar_dist = 0;     //The sonar distance
int sonar_cycles = 0;   //The number of cycles between the sonar interrupts
char string[50];    //String to be printed to the uA0;

void scan();

void scan()
{
    double degrees = 0;    //Initial degrees to go to
    oi_setWheels(0, 0);
    uart_sendStr("Scan:\n");
    for (degrees = 0; degrees <= 180; degrees += 2) //Go through all degrees
    {
        move_servo(degrees);
        sonar_cycles = ping_read();
        sonar_dist = cycles2dist(sonar_cycles);
        IR_dist = get_IR_dist();
        sprintf(string, "%-8.0f %-17d %-10d\n", degrees, IR_dist, sonar_dist);

        uart_sendStr(string);
        timer_waitMillis(40);
    }
    oi_setWheels((int) right_wheel_speed * 4, (int) left_wheel_speed * 4);
    move_servo(90);
}

int main(void)  //Wifi Settings: Raw, port 288, ip 192.168.1.1,
{
    uart_init();    //uart_sendStr()
    uart_sendStr("\nDegrees  IR Distance (cm)  Sonar Distance (cm)\n");
    setup_PING();        //set up the roomba
    setup_IR();         //Set up the IR sensor
    setup_servo();      //Set up the Servo
    lcd_init();     //initialize the lcd screen

    move_servo(90);    //Move the servo to the initial system
    char character = 0;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    setup_ContactSensors(sensor_data);
    //Update the sensor data
    oi_update(sensor_data);
    oi_setLeds(1, 1, 160, 200);
    bool active = 0;
    loadSongs();
    while (1)
    {
        if(active){
            if (!(UART1_FR_R & UART_FR_RXFE))
                    {
                        character = uart_receive();
                        switch (character)
                        {
                        case 'W':
                            left_wheel_speed = uart_receive();
                            right_wheel_speed = uart_receive();
                            oi_setWheels((int) right_wheel_speed * 4,
                                         (int) left_wheel_speed * 4);
                            break;

                        case 'X':
                            oi_setWheels(0, 0);
                            break;

                        case 'L':
                            scan();
                            break;

                        case 'Q':
                            oi_setWheels(0, 0);
                            active = 0;
                            break;

                        case 'P':
                            oi_play_song(MARIO_VICTORY);
                            break;

                        default:
                            break;

                        }

                    }
                    if(sensorTrip()){
                        sprintf(string, "tripped\n");
                        oi_setWheels(-400, -400);
                        uart_sendStr(string);
                        timer_waitMillis(500);
                        oi_setWheels(0, 0);
                    }
                    sonar_cycles = ping_read();
                    sonar_dist = cycles2dist(sonar_cycles);
                    IR_dist = get_IR_dist();
                    updateContactSensors();
                    if(IR_dist < sensorTripDistance || sonar_dist < sensorTripDistance){
                        oi_setWheels(0, 0);
                        sprintf(string, "CLOSE\n");
                        uart_sendStr(string);
                    }
                    sprintf(string, "%-10d %-10d\n", IR_dist, sonar_dist);
                    uart_sendStr(string);
                    timer_waitMillis(20);
        }else{
            character = uart_receive();
            if(character == 'G'){
                active = 1;
            }
            if(character == 'P'){
                oi_play_song(MARIO_VICTORY);
            }
        }

    }
}
