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

char buf;



void read() {
    buf = SSPBUF;
    SSPBUF = 0x00;
    
    
    LATD = buf;
    read_slave_address(buf);
    read_mode(buf);
    read_duration(buf);
    read_historical(buf);
    /*
    if (buf == 0x61) {
        SSPBUF = 0xFF;
    } else {
        SSPBUF = 0xAA;
    }
    */
}

void read_slave_address(char buf) {
    slave_address = (buf >> 5) & 0x7;
}

void read_mode(char buf) {
    mode = buf & 0x7;
}

void read_duration(char buf) {
    window = (buf >> 4) & 0x1;
}

void read_historical(char buf) {
    hist = (buf >> 3) & 0x1;
}

void transmit_data() {
    
    unsigned long data = (unsigned long) mode;
    data += ((unsigned long) slave_address) * 10 ;
    data += ((unsigned long) window) * 100;
    //char dump;
    //if (SSPSTATbits.BF) {
    //    dump = SSPBUF;
    //}
    if (buf > 0xD5) {
        SSPBUF = 0xFF;
    } else {
        SSPBUF = 0xFF & data;
        SSPCON1bits.WCOL = 1;
        if (hist) {
            int i;
            for (i=0; i < 15; i++) {
                data += 1;
                while (SSPCON1bits.WCOL);
                SSPBUF = 0xFF & data;
                SSPCON1bits.WCOL = 1;
            }
        }
    }
}
