#include "config_bits.h"

void main(void) {
    // I/O CONFIGURATION
    TRISFbits.TRISF3 = 0;       // On-board LED astive as output
    // TIMER 0 CONFIGURATION
    T0CON0bits.EN = 1;          // Timer 0 enabled
    T0CON0bits.MD16 = 1;        // Timer 0 as 16-bit mode
    T0CON0bits.OUTPS = 0x1;     // Timer 0 post-scaler 1:2
    
    T0CON1bits.CS = 0x2;        // Timer 0 clock source is FOSC/4
    T0CON1bits.ASYNC = 0;       // Timer 0 is synchronous
    T0CON1bits.CKPS = 0x0;      // Timer 0 pre-scaler 1:1
     
    RF3PPS = 0x39;              // Timer 0 out mapped to on-board LED

    while(1);
}
