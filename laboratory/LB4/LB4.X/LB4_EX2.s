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
    ; CLOCK CONFIGURATION
    BANKSEL OSCCON	;ACCESS TO OSCCON REGISTER 
    MOVLW   0x5E	;4MHZ FREQUENCY OF INTERNAL OSCILLATOR
    MOVWF   OSCCON,1	;LOAD DATA THROUGH BSR

    ; GPIO CONFIGURATION
    CLRF    TRISA,0   ;CONFIGURE PIN F.3 AS OUTPUT (ON-BOARD LED)
    SETF    LATA,0    ;TURN OFF ON-BOARD LED 

LOOP:
    SETF    LATA,0
    CALL    delay_200ms
    CLRF    LATA,0
    CALL    delay_200ms
    GOTO    LOOP

END resetVec