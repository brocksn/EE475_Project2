/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>  

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/**
 * Wait for a given number of milli-seconds using busy waiting scheme.
 * @param time - time in ms to wait.
 */
void wait_ms(uint16_t time)
{
    static long timel = 0;
    timel = time * 100000l;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    //ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    // LED config
    TRISAbits.TRISA6 = 0;
    LATAbits.LATA6 = 0; // set pin LOW
    
    // Timer setup
    T1CONbits.T1RD16 = 1;   // 2 8 bit operations for writing to memory
    T1CONbits.T1CKPS0 = 0;  // setting prescale to 1:1 
    T1CONbits.T1CKPS1 = 0;  
    T1CONbits.T1OSCEN = 0;  // Timer 1 Osc. off
    T1CONbits.NOT_T1SYNC = 1;   // Don't sync external clock input
    T1CONbits.TMR1CS = 1;   // Using external clock
    T1CONbits.TMR1ON = 1;   // Enable timer 1
    
    LATAbits.LATA6 = 0; // set pin LOW
    //LATAbits.LATA6 = 1;
    while(1)
    {
        uint16_t data = TMR1L;
        data += TMR1H << 8;
        if(data > 0) {
            LATAbits.LATA6 ^= 1; // set pin LOW
            wait_ms(1);
        }

    }

}


