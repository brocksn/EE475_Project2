/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void initialize() {
    TRISC = 0x00;
    TRISCbits.TRISC3 = 0x1;
    TRISCbits.TRISC4 = 0x1;
    SSPCON1bits.SSPEN = 0x0;
    SSPSTATbits.SMP = 0x0;
    SSPSTATbits.CKE = 0x1;
    SSPCON1bits.CKP = 0x0;
    SSPCON1bits.SSPM = 0x5;
    SSPCON1bits.SSPEN = 0x1;
    
    TRISD = 0x00;
}
