#include "config_bits.h"

void __interrupt(irq(default)) ISR(){
    LATFbits.LATF3 = ~LATFbits.LATF3;
    PIR1bits.INT0IF = 0;
}

void main(void) {
    // I/O CONFIGURATION
    TRISBbits.TRISB0 = 1;
    TRISFbits.TRISF3 = 0;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    //ANSELFbits.ANSELF3 = 0;
    LATFbits.LATF3 = 1;
    
    // INT0 INTERRUPT CONFIGURATION
    PIE1bits.INT0IE = 1;        // INT0 enabled
    IPR1bits.INT0IP = 1;        // INT0 is high priority
    INTCON0bits.INT0EDG = 0;    // INT0 on falling edge
    PIR1bits.INT0IF = 0;        // INT0 flag cleared
      
    // GLOBAL INTERRUPTS CONFIGURATION
    INTCON0bits.GIE = 1;
    INTCON0bits.GIEL = 1;
    INTCON0bits.IPEN = 1;
    
    while(1);
}
