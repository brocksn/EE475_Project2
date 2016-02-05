/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        10000000L  // 10 MHz
#define FCY             SYS_FREQ/4


char slave_address;
char mode;
bit window;    // low 10ms, high 1s
bit hist;
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void read_slave_address();
void read();
void read_mode();
void read_duration();
void read_historical();
void transmit_data();

