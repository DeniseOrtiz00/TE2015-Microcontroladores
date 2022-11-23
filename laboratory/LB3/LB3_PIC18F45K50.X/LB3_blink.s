PROCESSOR   18F45K50
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
    ; GPIO CONFIGURATION
    BCF	    TRISA,4,0   ;CONFIGURE PIN F.3 AS OUTPUT (ON-BOARD LED)
    BSF	    LATA,4,0    ;TURN OFF ON-BOARD LED 

LOOP:
    BSF	    LATA,4,0
    CALL    DELAY500MS; 2
    BCF	    LATA,4,0
    CALL    DELAY500MS
    GOTO    LOOP

END resetVec
