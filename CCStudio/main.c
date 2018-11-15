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

//Variable declarations
char left_wheel_speed = 50;  //Holder for the left wheels speed
char right_wheel_speed = 50; //Holder for the right wheel speed
char sensorTripDistance = 20; //If an object is detected closer than this number (centimeters) by the Sonar or IR sensor, causes the robot to stop 

int IR_dist = 50;        //IR Distance
int sonar_dist = 50;     //The sonar distance
int sonar_cycles = 0;   //The number of cycles between the sonar interrupts
char string[50];    //String to be printed to the UART;

//Method declarations
void scan();

//Method for scanning the surroundings and then resuming movement
void scan()
{
    double degrees = 0;    //Initial degrees for the servo to go to
    oi_setWheels(0, 0);     //Stops the robot for scanning
    uart_sendStr("Scan:\n"); //Sends out that the folloing code will be scanning
    for (degrees = 0; degrees <= 180; degrees += 2) //Scan through 0 to 180 degrees at 2 degree increments
    {
        move_servo(degrees);    //Moves the servo to the specified degree
        sonar_cycles = ping_read(); //Gets the number of cycles between the sonar signal being sent and recieved
        sonar_dist = cycles2dist(sonar_cycles); //Turns the cycles to a sonar distance 
        IR_dist = get_IR_dist();    //Gets the IR distance being read
        sprintf(string, "%-8.0f %-17d %-10d\n", degrees, IR_dist, sonar_dist); //Sends the degrees and two distances to the UART string holder

        uart_sendStr(string);   //Sends the string over UART
        timer_waitMillis(40);   //Waits some time
    }
    move_servo(90); //Moves the servo back to the middle
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
    char character = 0; //Last read character holder
    oi_t *sensor_data = oi_alloc(); //Gets the main sensor data input for the Roomba
    oi_init(sensor_data);   //Setup the open interface
    setup_ContactSensors(sensor_data);  //Setup the Contact sensors
    oi_update(sensor_data); //Update the OI input
    oi_setLeds(1, 1, 160, 200); //Set the Roomba's LED
    bool active = 0; //Boolean that holds whether or not the roomba's movement should be active
    loadSongs();    //Load our songs onto the Roomba
    oi_setWheels(0, 0);
    int counter = 0;
    while (1)   //While forever, or until shutoff
    {
        if (active)
        { //If we are active
            if (!(UART1_FR_R & UART_FR_RXFE)) //If there is UART data to recieve, get it and do the command
            {
                character = uart_receive(); //Read in the UART character
                switch (character)
                //Do something depending the character
                {
                case 'W':   //If W is recieved, set the wheel speeds
                    //left_wheel_speed = uart_receive();  //Get the left wheel speed from UART
                    //right_wheel_speed = uart_receive(); //Get the right wheel speed from UART
                    oi_setWheels((int) right_wheel_speed * 4,
                                 (int) left_wheel_speed * 4); //Set the wheel speeds
                    break;
                case 'S':
                    oi_setWheels((int) right_wheel_speed * -4,
                                 (int) left_wheel_speed * -4);
                    break;
                case 'D':
                    oi_setWheels((int) right_wheel_speed * -1,
                                 (int) left_wheel_speed * 1);
                    break;
                case 'A':
                    oi_setWheels((int) right_wheel_speed * 1,
                                 (int) left_wheel_speed * -1);
                    break;
                case 'X':   //Stop the Robot
                    oi_setWheels(0, 0);
                    break;

                case 'L':   //Scan command
                    scan();
                    break;

                case 'Q':   //Stop the robot and make it inactive
                    oi_setWheels(0, 0);
                    active = 0;
                    break;

                case 'P':   //Play the Mario_Victory song
                    oi_play_song(BABY_SHARK);
                    break;

                default:
                    break;

                }

            }
            updateContactSensors(); //Update the contact sensors
            if (sensorTrip())
            {   //If one of the sensors are tripped, backup and stop
                sprintf(string, "T\n");   //Store that the sensors have tripped
                oi_setWheels(-400, -400);   //Go backwards
                uart_sendStr(string);   //Send that the sensors have tripped
                timer_waitMillis(500);  //Wait until we have backed up enough
                oi_setWheels(0, 0); //Stop the robot until told how to move again
            }
            if (counter % 1000 == 0)
            { //If we are too close to an object
              //Make an if statement so we can move backwards, just not forwards
                sonar_cycles = ping_read(); //Gets the number of cycles between the sonar signal being sent and recieved
                sonar_dist = cycles2dist(sonar_cycles); //Turns the cycles to a sonar distance
                if (sonar_dist < sensorTripDistance)
                {
                    oi_setWheels(0, 0); //Stop, don't move forward
                    sprintf(string, "C\n"); //Store that we have stopped
                    uart_sendStr(string); //Send that we have stopped
                }
            }
            //sprintf(string, "%d %d\n", IR_dist, sonar_dist);  //Save the distances to a string
            counter++;
            /**
             uart_sendStr(string);   //Send the distances
             timer_waitMillis(50); //Wait a second
             */
        }
        else
        {  //If the robot is not active
            character = uart_receive(); //Wait until we recieve a character
            if (character == 'G')
            {   //Activate the robot movement
                active = 1;
            }
            if (character == 'P')
            {   //Still allow the robot to play songs
                oi_play_song(BABY_SHARK);
            }
        }

    }
}
