/**
 * @author Ben Carland, Brandon Bui, Jose Lopez, Parker Bibus
 */
#include "IRSensor.h"

/**
 * Gets the IR reading distance
 */
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

/**
 * Calculate the distance from the IR sensor.
 */
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

/**
 * Setup for IR sensor
 */
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
