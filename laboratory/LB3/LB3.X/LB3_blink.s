PROCESSOR   18F57Q43
#include    <xc.inc>
#include    "configuration_bits.inc"
#include    "delays.inc"
    
PSECT	resetVec, class=CODE, reloc=2

PSECT	absdata, abs, ovrld
absdata:
    org	    0x1000

resetVec:
    goto    MAIN

PSECT code
MAIN:
    ; OSCILLATOR CONFIGURATION
    BANKSEL OSCCON1	
    MOVLW   0X62H
    MOVWF   OSCCON1,1
    MOVLW   0X02H
    MOVWF   OSCFRQ,1

    ; GPIO CONFIGURATION
    BCF	    TRISF,3,0   ;CONFIGURE PIN F.3 AS OUTPUT (ON-BOARD LED)
    BSF	    LATF,3,0    ;TURN OFF ON-BOARD LED 

LOOP:
    BSF	    LATF,3,0
    CALL    DELAY500MS; 2
    BCF	    LATF,3,0
    CALL    DELAY500MS
    GOTO    LOOP

END resetVec
