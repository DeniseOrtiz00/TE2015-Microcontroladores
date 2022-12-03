#include "mcc_generated_files/mcc.h"

void main(void)
{
    SYSTEM_Initialize();

    uint16_t resultado; //variable de 16 bits
    while (1)
    {
        resultado = ADC_GetConversion(AN0_); //adquiere el valor del potenciometro (ADC)
        printf("ADC = %i\n\r", resultado); //UART
        __delay_ms(1000);
        
        if (EUSART1_is_tx_ready())
        {
                Led_D2_Toggle();
    }
}
}
