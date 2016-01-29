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

static signed int re[256]; 
static signed int im[256];

/**
 * Wait for a given number of seconds using busy waiting scheme.
 * @param time - time in s to wait.
 */
void wait_s(uint16_t time)
{
    static long timel = 0;
    timel = time * 100000l;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}

void ADC_acq_delay() {
        __delay_us(20);
}

void zero_arrays() {
    int i;
    for (i = 0; i < 256; i++) {
        re[i] = 0;
        im[i] = 0;
    }
}

signed int get_ADC() {
    
    zero_arrays();
    // 1. Configure A/D module
    ADCON1bits.ADFM = 0x1;      // Result format is left justified
                                // most significant bits will be read as '0'
    ADCON0bits.ADCS = 0x2;      // A/D clock conversion set to F-OSC/32
    ADCON1bits.ADCS2 = 0x0;     // this allows sufficient setup time for the A/D
    
    ADCON1bits.PCFG = 0x0;      // A/D ports all configured as analog
                                // V-REF+ is VDD and V-REF- is VSS
    ADCON0bits.CHS = 0x0;       // Select AN0
    ADCON0bits.ADON = 0x1;      // Power up A/D unit
    int j;
    //  Use A/C to fill first 128 bit array.
    for (j = 0; j<256; j++) {
        // 2. Wait acquisition time
        ADC_acq_delay();
        // 3. Start conversion [set go/done bit]
        ADCON0bits.GO_NOT_DONE = 0x1;
        // 4. Wait for A/D conversion to complete (poll go/done bit)
        while (ADCON0bits.GO_NOT_DONE == 0x1) {
        }
        // 5. Read A/D Result registers (ADRESH/ADRESL);clear bit ADIF if required.
        re[j] = ADRESL;
        re[j] += ADRESH + 0xFF;
        re[j] -= 511;
    }
    
    // Calculate FFT
    return (optfft(re, im) * 512) / 50000;
}
