/******************************************************************************/
/*Files to Include                                                            */
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

#include "system.h"
#include "optfft.h"

#define _XTAL_FREQ 20000000



void read() {
    while (!SSPSTATbits.BF);
    read_slave_address();
    read_mode();
    read_duration();
    read_historical();
}

void read_slave_address() {
    slave_address = (SSPBUF >> 5) & 0x7;
}

void read_mode() {
    mode = SSPBUF & 0x7;
}

void read_duration() {
    window = (SSPBUF >> 4) & 0x1;
}

void read_historical() {
    hist = (SSPBUF >> 3) & 0x1;
}

void transmit_data() {
    unsigned long data = (unsigned long) slave_address;
    data += ((unsigned long) window) * 10 ;
    data += ((unsigned long) mode) * 100;  
    char dump;
    if (SSPSTATbits.BF) {
        dump = SSPBUF;
    }
    SSPBUF = 0xFF & data;
    SSPCON1bits.WCOL = 0x1;
    while (SSPCON1bits.WCOL);
    SSPBUF = (data << 8) & 0xFF;
    SSPCON1bits.WCOL = 0x1;
    while (SSPCON1bits.WCOL);
    SSPBUF = (data << 16) & 0xFF;
    SSPCON1bits.WCOL = 0x1;
    while (SSPCON1bits.WCOL);
    SSPBUF = (data << 24) & 0xFF;
    SSPCON1bits.WCOL = 0x1;
    while (SSPCON1bits.WCOL);
}
