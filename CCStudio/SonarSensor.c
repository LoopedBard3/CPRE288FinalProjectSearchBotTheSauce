#include "SonarSensor.h"

/*initialization for PING variabless*/
volatile unsigned last_time = 0;
volatile unsigned current_time = 0;
volatile int waiting_fall_flag = 0;
volatile unsigned int overflow = 0;
volatile unsigned int time_diff;
volatile unsigned char ready = 0;

/*Gets distance based on time*/
unsigned cycles2dist(unsigned cycles)
{
    return 2125 * cycles / 2000000;
}

/*changes seconds to milliseconds*/
unsigned cycles2ms(unsigned cycles)
{
    return cycles / 16000;
}

/*sends the pulse*/
void send_pulse()
{
    TIMER3_CTL_R &= ~0x100; //Turn off Timer3
    GPIO_PORTB_AFSEL_R &= ~0x8; //Reset PB3 AFSEL
    GPIO_PORTB_DIR_R |= 0x08; // set PB3 as output
    GPIO_PORTB_DATA_R |= 0x08; // set PB3 to high
    timer_waitMicros(6); // wait at least 5 microseconds based on data sheet
    GPIO_PORTB_DATA_R &= ~0x08; // set PB3 to low
    GPIO_PORTB_DIR_R &= ~0x08; // set PB3 as input
    GPIO_PORTB_AFSEL_R |= 0x8; //Set PB3 AFSEL
    TIMER3_CTL_R |= 0x100; //Turn Timer back on
}

/* Pings the sensor*/
unsigned ping_read()
{
    ready = 0;
    send_pulse();
    while (!ready)
    {
    }
    if (current_time < last_time)
    {
        overflow += 1;
        time_diff = ((unsigned long) 0b1 << 24) + current_time - last_time;
    }
    else
    {
        time_diff = current_time - last_time;
    }
    return time_diff; //Get distance
}

/* ping sensor handler for the ISR */
void TIMER3B_Handler(void)
{
    if (!waiting_fall_flag)
    {
        last_time = TIMER3_TBR_R;
        waiting_fall_flag = 1;
        TIMER3_ICR_R = 0x0400;  //Clear Interrupt
    }
    else
    {
        current_time = TIMER3_TBR_R;
        waiting_fall_flag = 0;
        ready = 1;
        TIMER3_ICR_R = 0x0400;  //Clear Interrupt
    }
}

//Setup for Sonar Sensor
void setup_PING()
{
    SYSCTL_RCGCTIMER_R |= 0x8;
    SYSCTL_RCGCGPIO_R |= 0x2;    //enable GPIO clock
    GPIO_PORTB_DEN_R |= 0x08;    //Digitally enable GPIO Port B port 3
    GPIO_PORTB_PCTL_R |= 0x7000;

    TIMER3_CTL_R = 0x00000000;  //Disable timer 3B
    TIMER3_CFG_R |= 0x4;  //Set number of bits for 3B to use
    TIMER3_TBMR_R = 0x17; //Sets timer mode+
    TIMER3_TBILR_R = 0xFFFF;
    TIMER3_CTL_R = 0x00000C00;
    TIMER3_ICR_R = 0x0400;
    TIMER3_IMR_R = 0x00000400;  //Interrupt mask

    NVIC_EN1_R |= 0x00000010;
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable(); //Initialize global interrupts
    TIMER3_CTL_R |= 0x00000D00;  //Enable timer 3B
}

