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
#include "optfft.h"        /* Optimized Fast Fourier Transform funct/params */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */
      // low current, high last 16
            // bit3 controls historical SRAM data, active high
            // bit4 controls window: low 10ms, high 1s
            // bit0:2 controls mode

            // 0x00 = frequency mode, 10ms, current data
            // 0x05 = frequency mode, last 16 measurements
            // 0x0A = frequency mode, 1s, current data
            // 0x01 = period, 10ms, current data
            // 0x06 = period, last 16
            // 0x0B = period, 1s, current data
            // 0x02 = events, 10ms, current data
            // 0x07 = events, last 16
            // ox0C = events, 1s, current data
            // 0x03= interval, 10ms, current data
            // 0x08 = interval, last 16
            // 0x0D = interval, 1s, current data
            // 0x04 = spectrum, 10ms, current data
            // 0x09 = spectrum, last 16
            // 0x0E = spectrum, 10ms, current data



/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    initialize();
    
    while(1) {
        //if (1) {
          //  read();
        //}
        if (SSPSTATbits.BF) {
            read();
            transmit_data();
        }

    }
}


