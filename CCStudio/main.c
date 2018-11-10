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


int main(void)  //Wifi Settings: Raw, port 288, ip 192.168.1.1,
{
    uart_init();    //uart_sendStr()
    uart_sendStr("\nDegrees  IR Distance (cm)  Sonar Distance (cm)\n");
    setup_PING();        //set up the roomba
    setup_IR();         //Set up the IR sensor
    setup_servo();      //Set up the Servo
    lcd_init();     //initialize the lcd screen
    double degrees = 0;    //Initial degrees to go er
    int IR_dist = 0;        //IR Distance
    int sonar_dist = 0;     //The sonar distance
    int sonar_cycles = 0;   //The number of cycles between the sonar interrupts
    char string[50];    //String to be printed to the uA0;
    move_servo(degrees);    //Move the servo to the initial system
    char character = 0;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //Update the sensor data
    oi_update(sensor_data);
    oi_setLeds(1, 1, 255, 200);
    while (1){
        for (degrees = 0; degrees <= 180; degrees += 2) //Go through all degrees
        {
            if (!(UART1_FR_R & UART_FR_RXFE))
            {
                character = uart_receive();
                switch (character)
                {
                case 'w':
                    oi_setWheels(250, 250);
                    break;
                case 's':
                    oi_setWheels(-250, -250);
                    break;
                case 'a':
                    oi_setWheels(100, -100);
                    break;
                case 'd':
                    oi_setWheels(-100, 100);
                    break;
                case 'x':
                    oi_setWheels(0, 0);
                    break;
                }
            }
            move_servo(degrees);
            sonar_cycles = ping_read();
            sonar_dist = cycles2dist(sonar_cycles);
            IR_dist = get_IR_dist();
            sprintf(string, "%-8.0f %-17d %-10d\n", degrees, IR_dist,
                    sonar_dist);

            uart_sendStr(string);
            timer_waitMillis(40);
        }
    }
}
