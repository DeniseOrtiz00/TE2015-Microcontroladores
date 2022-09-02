PROCESSOR   18F57Q43
#include    <xc.inc>
#include    "config_bits.inc"

; PAGE SECTION FOR VARIABLES 
PSECT UDATA_ACS
    VAR:  DS 1
    AUX:  DS 1

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
    BCF	    TRISF,3,0   ;Configure Pin F3 as output (on-board LED)
    BSF	    LATF,3,0    ;Turn off on-board LED
    BSF	    TRISB,4,0	;Configure Pin B4 as input (on-board switch)
    CLRF    TRISA,0
    BANKSEL ANSELB
    CLRF    ANSELB,1
    SETF    WPUB,1

; 1) Assign literal 01101101B to Port A through WREG
    MOVLW   01101101B	;Move 0X6D to WREG
    MOVWF   LATA,1	;Move WREG to LATA (BSR)

; 2) Invert the value on WREG and assign in to a variable called VAR.
    COMF    WREG,0,0	    ;Complement WREG and save in WREG (Access Bank)
    MOVWF   BANKMASK(VAR),0 ;Move WREG to masked VAR address (Access Bank)

; 3) Use the current value on WREG and add literal 0x02. Keep the result on WREG.
    ADDLW   0x02	;Add 0x02 to WREG

LOOP:
    GOTO    LOOP
END resetVec


