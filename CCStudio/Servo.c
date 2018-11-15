#include "Servo.h"

/*Initialization for the Servo variables*/
unsigned period_width = 320000; // Period width of the PWM modulation
unsigned lowCalibrate = 8000;  //may need to be changed depending on roomba
unsigned highCalibrate = 27000; //may need to be changed depending on roomba
unsigned timeBuffer = 20; //Buffer time before return ready in the move function

//Move the servo to the specified degrees. Try also setting TBILR in this method
int move_servo(double degree)
{
    unsigned pulse_width;    // pulse width in cycles
    pulse_width = lowCalibrate + (double) degree / 180 * highCalibrate; // calculate pulse width in cycles
    TIMER1_TBMATCHR_R = period_width - pulse_width; // set pulse width
    timer_waitMillis(timeBuffer); // enforce a delay for the servo to correctly set
    return 1;
}

//Set up for the Servo Motor
void setup_servo()
{
    SYSCTL_RCGCGPIO_R |= 0x2;    //enable GPIO clock
    GPIO_PORTB_DEN_R |= 0x20;    //Digitally enable GPIO Port B
    GPIO_PORTB_PCTL_R |= 0x700000;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20; // set PB5 as output

    SYSCTL_RCGCTIMER_R |= 0x02;
    TIMER1_CTL_R &= ~0x0100;
    TIMER1_TBMR_R |= 0x0A;
    TIMER1_CFG_R |= 0x4;
    TIMER1_TBILR_R = period_width;
    TIMER1_TBMATCHR_R = period_width - 24000;
    TIMER1_CTL_R |= 0x100;
}
