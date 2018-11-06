#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "driverlib/interrupt.h"
#include <math.h>

unsigned pulse_period;
unsigned mid_width = 24000;
unsigned period_width = 320000;
unsigned lowCalibrate = 8000;  //may need to be changed depending on roomba
unsigned highCalibrate = 27000; //may need to be changed depending on roomba
unsigned timeBuffer = 20; //Buffer time before return ready in the move function

/*initialization for PING*/
volatile unsigned last_time = 0;
volatile unsigned current_time = 0;
volatile int waiting_fall_flag = 0;
volatile unsigned int overflow = 0;
volatile unsigned int time_diff;
volatile unsigned char ready = 0;

/*setup methods so order doesn't matter*/
unsigned cycles2dist(unsigned cycles);
unsigned cycles2ms(unsigned cycles);
void send_pulse();
unsigned ping_read();
int get_IR_dist();
int get_array_avg(int arr[], int size);
int IR_distance_calc(int data);
int move_servo(double degree);
void setup_IR();
void setup_PING();
void setup_servo();

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

int get_IR_dist()
{
    int fifoResult = 0;
    int dist = 0;
    ADC0_PSSI_R |= ADC_PSSI_SS0;
    while ((ADC0_RIS_R & ADC_RIS_INR0) == 0)
    {
        //wait
    }
    fifoResult = ADC0_SSFIFO0_R; //Get result
    dist = IR_distance_calc(fifoResult);
    ADC0_ISC_R |= ADC_ISC_IN0;
    return dist;
}

/* ping sensor related to ISR */
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
    TIMER1_TBMATCHR_R = period_width - mid_width;
    TIMER1_CTL_R |= 0x100;

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

//Setup for IR sensor
void setup_IR()
{
    SYSCTL_RCGCADC_R |= 0x3;
    SYSCTL_RCGCGPIO_R |= 0x2;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DIR_R |= 0x00;
    GPIO_PORTB_DEN_R |= 0x00;
    GPIO_PORTB_AMSEL_R |= 0x10;
    GPIO_PORTB_ADCCTL_R |= 0x00;

    //set up the analog for IR
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
    ADC0_EMUX_R |= ADC_EMUX_EM0_PROCESSOR;
    ADC0_SSMUX0_R |= 0x000A;
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
    ADC0_SAC_R |= ADC_SAC_AVG_16X;
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //Initialize the conversation
    ADC0_PSSI_R |= ADC_PSSI_SS0;
}

//Move the servo to the specified degrees.
int move_servo(double degree)
{
    unsigned pulse_width;    // pulse width in cycles
    pulse_width = lowCalibrate + (double) degree / 180 * highCalibrate; // calculate pulse width in cycles
    TIMER1_TBMATCHR_R = period_width - pulse_width; // set pulse width
    timer_waitMillis(timeBuffer); // enforce a delay for the servo to correctly set
    return 1;
}

//Calculate the distance from the IR sensor.
int IR_distance_calc(int data)
{
    int distance = 0;
    if (data < 1600)
    {    //Far calibration
        distance = -36.51 * log(data) + 288;
    }
    else
    { //Close Calibration
        distance = -15.67 * log(data) + 135;
    }
    return distance;
}

// Struct containing data for detected objects
struct detected_obj
{
    int distance;
    int measured_width;
    int calculated_width;
    int final_deg;
};

int main(void)  //Wifi Settings: Raw, port 288, ip 192.168.1.1,
{
    uart_init();    //uart_sendStr()
    uart_sendStr("\nDegrees  IR Distance (cm)  Sonar Distance (cm)\n");
    setup_PING();        //set up the roomba
    setup_IR();         //Set up the IR sensor
    setup_servo();      //Set up the Servo
    lcd_init();     //initialize the lcd screen
    double degrees = 0;    //Initial degrees to go to
    int IR_change = 15;    //Change in IR distance needed to count as an edge of an object
    int measuring = 0;  //Whether or not we are measuring an object
    int obj_count = 0;  //Number of objects
    int obj_width = 0;  //Width of the object
    int smallest_ind = 0;   //The index of the smallest object
    int prev_IR_dist = 0;   //Previous IR distance holder
    int IR_dist = 0;        //IR Distance
    int sonar_dist = 0;     //The sonar distance
    int sonar_cycles = 0;   //The number of cycles between the sonar interrupts
    char string[50];    //String to be printed to the uART
    struct detected_obj objects[5]; //Objects that we detected
    objects[smallest_ind].measured_width = 0;   //Initialize the first object
    objects[smallest_ind].distance = 0;
    move_servo(degrees);    //Move the servo to the initial system
    for (degrees = 0; degrees <= 180; degrees += 2) //Go through all degrees
    {
        move_servo(degrees);
        sonar_cycles = ping_read();
        sonar_dist = cycles2dist(sonar_cycles);
        prev_IR_dist = IR_dist;
        IR_dist = get_IR_dist();
        sprintf(string, "%-8.0f %-17d %-10d\n", degrees, IR_dist, sonar_dist);
        if (prev_IR_dist - IR_dist > IR_change)
        {
            obj_width = 0;
            measuring = 1;
        }
        else if (measuring)
        {
            obj_width += 2;
        }
        if (IR_dist - prev_IR_dist > IR_change && measuring == 1)
        {
            measuring = 0;

            if (obj_width > 10)
            {
                // Carry out size calculation here
                objects[obj_count].distance = prev_IR_dist;
                objects[obj_count].measured_width = obj_width;
                objects[obj_count].calculated_width = (int) (sin(obj_width)
                        * prev_IR_dist);
                objects[obj_count].final_deg = degrees;
                if (obj_count > 0
                        && objects[smallest_ind].measured_width
                                > objects[obj_count].measured_width)
                {
                    smallest_ind = obj_count;
                }
                obj_count++;
            }

        }
        lcd_printf("number of objects: %dsmallest index: %d\nwidth: %d\ndistance: %d", obj_count,
                   smallest_ind, objects[smallest_ind].measured_width, objects[smallest_ind].distance);

        uart_sendStr(string);
        timer_waitMillis(80);
    }
    move_servo(objects[smallest_ind].final_deg - (objects[smallest_ind].measured_width)); //Move servo to the middle of the smallest object
}
