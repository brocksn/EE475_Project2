/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        10000000L  // 10 MHz
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/**
 * Wait for a given number of seconds using busy waiting scheme.
 * @param time - time in s to wait.
 */
void wait_s(uint16_t time);

void zero_array(signed int *array, int length);

void ADC_acq_delay();

signed int get_ADC();
