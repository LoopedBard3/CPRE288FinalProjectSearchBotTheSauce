/*
 *
 *   uart.c
 *
 *
 *
 *
 *
 *   @author Parker Bibus, Brandon Bui
 *   @date 9/25/18
 */

#include "uart.h"

void uart_init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; //ENABLE CLOCK PORT B
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; //ENABLE UART1 CLOCK
    timer_waitMillis(1); // Small delay before accessing device after turning on clock
    GPIO_PORTB_AFSEL_R |= 0x00000003;
    GPIO_PORTB_PCTL_R &= 0x00000000;     // Force 0's in the disired locations
    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations
    GPIO_PORTB_DEN_R |= 0x00000003;
    GPIO_PORTB_DIR_R &= 0x00000000;      // Force 0's in the disired locations
    GPIO_PORTB_DIR_R |= 0x00000001;      // Force 1's in the disired locataions

    //BAUD DATA
    uint16_t iBRD = 8;
    uint16_t fBRD = 44;
    //Turn off uart1 while we setup
    UART1_CTL_R &= ~(UART_CTL_UARTEN);
    //set baud rate
    UART1_IBRD_R = iBRD;
    UART1_FBRD_R = fBRD;
    //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
    UART1_LCRH_R = UART_LCRH_WLEN_8;
    //use system clock as source
    UART1_CC_R = UART_CC_CS_SYSCLK;
    //re-enable enable RX, TX, and uart1
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
}   //END of uart_init

void uart_sendChar(char data)
{
    while(UART1_FR_R & 0x20)
    {
    }
     //send data
     UART1_DR_R = data;
}

void uart_sendBits(char data)
{
    while(UART1_FR_R & 0x20)
    {
    }
     //send data
     UART1_DR_R = data;
}

char uart_receive(void)
{
    char data = 0;
     //wait to receive
     while(UART1_FR_R & UART_FR_RXFE)
    {
    }
    //mask the 4 error bits and grab only 8 data bits
    data = (char)(UART1_DR_R & 0xFF);

    return data;
}

void uart_sendStr(const char *data)
{
    while(*data != '\0')//Until the end of the string
        {
            uart_sendChar(*data);
            data++;
        }
}
