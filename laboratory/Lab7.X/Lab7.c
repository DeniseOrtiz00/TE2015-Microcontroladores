
// CONFIG1L

// ejercicio 2
/*#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>                //Incluimos los registros del Microcontrolador 18F4550
#include <stdio.h>             //Incluimos stdio para escribir cadenas  con formato en una variable
#include "lcd.h"               //Incluimos la libreria LCD
#define _XTAL_FREQ 8000000     //Cristal Externo de Alta Velocidad 8000000

float decimal= 4.47;
int entero=20;
char buffer_lcd[20];
void main(void)
{
    unsigned char contador;   //Variable entera de 8 digitos tipo char
    TRISD=0x00;               //Configuramos el Puerto D como salida digital.
    lcd_init();               //Inicializamos la pantalla LCD.
    while(1)                  //Bucle Infinito 
    {
        lcd_clear();          //Limpiamos pantalla LCD
        lcd_gotoxy(1,1);      //Ubicamos el cursor en fila 1, columna 1
        lcd_putc("TE2015 - Lab de");  //mostramos una cadena de caracteres en la pantalla LCD
        lcd_gotoxy(2,1);      //Ubicamos el cursor en fila2, columna 1
        lcd_putc("Micros, AD2022");  //mostramos una cadena de caracteres en la pantalla LCD
        __delay_ms(1000);     //Retardo de 200 ms
        lcd_clear();          //Limpiamos pantalla LCD
        lcd_gotoxy(1,1);      //Ubicamos el cursor en fila 1, columna 1
        lcd_putc("Denise Ortiz");   //mostramos una cadena de caracteres en la pantalla LCD
        lcd_gotoxy(2,1);      //Ubicamos el cursor en fila 2, columna 1
        lcd_putc("A01177158"); //mostramos una cadena de caracteres en la pantalla LCD
        __delay_ms(1000);     //Retardo de 200 ms
    }
    return;
}*/

//ejercicio 3
#define LCD_ENABLE_PIN PIN_d0 // ASIGNAMOS EL PIN "d0" COMO SALIDA PARA E
#define LCD_RS_PIN PIN_d1 // ASIGNAMOS EL PIN "d1" COMO SALIDA PARA RS
#define LCD_RW_PIN PIN_d2 // ASIGNAMOS EL PIN "d2" COMO SALIDA PARA RW
#define LCD_DATA4 PIN_d3 // ASIGNAMOS EL PIN "d3" COMO SALIDA PARA D4
#define LCD_DATA5 PIN_d4 // ASIGNAMOS EL PIN "d4" COMO SALIDA PARA D5
#define LCD_DATA6 PIN_d5 // ASIGNAMOS EL PIN "d5" COMO SALIDA PARA D6
#define LCD_DATA7 PIN_d6 // ASIGNAMOS EL PIN "d6" COMO SALIDA PARA D7
#include <lcd.c>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz)
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOMCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD

void main()
{
lcd_init ();
     set_tris_b(0x0f);/* se declara el pueto como entrada los promeros 4 pines y como salida los siguientes 4 pines */
     int x[4]={0,0,0,1};/* Pines de salida del puerto B*/
     int y[4];
     char const display[16]= {'7','8','9','/','4','5','6','X','1','2','3','-','C','0','=','+'};
     int z[16]={7,8,9,0,4,5,6,0,1,2,3,0,0,0,0,0};
     float32 h[17];
     int k,i,j,e=1,n=0;
     float resultado=0,suma=0,mul=0,resta=0,div=0;
     while(TRUE)
     {
     inicio:
      k=0;
      rotate_left(x,4);
      output_bit(pin_b4,x[0]);
      output_bit(pin_b5,x[1]);
      output_bit(pin_b6,x[2]);
      output_bit(pin_b7,x[3]);
      y[0]=input(pin_b0);
      y[1]=input(pin_b1);
      y[2]=input(pin_b2);
      y[3]=input(pin_b3);

      for(i=0; i<=3; ++i)
      {
         for(j=0; j<=3; ++j)
         {
            if (y[i]==1 && x[j]==1)
            {
               if (y[3]==1 && x[0]==1)
               {
                    lcd_gotoxy (1,1);printf(LCD_PUTC,"                    ");
                    lcd_gotoxy (1,2);printf(LCD_PUTC,"                     ");
                    e=0;resultado=0;suma=0;mul=0;resta=0;div=0;n=0;k=0;
                    goto inicio;
               }
               if (y[3]==1 && x[2]==1)
               {
                    lcd_gotoxy (1,2);printf(LCD_PUTC, "%c",display[k]);
                    resultado=h[e-1];
                    lcd_gotoxy (2,2);printf(LCD_PUTC, "%f    ",resultado);
                    goto inicio;
               }
               n=n+1;
               lcd_gotoxy (n,1);printf(LCD_PUTC, "%c",display[k]);
               __delay_ms(100);
               h[e]=z[k];
               if (y[3]==1 && x[3]==1)
               {
                    suma=1;
                    goto inicio;
               }
               if (suma==1)
               {
                    h[e]=h[e]+h[e-1];
                    suma=0;
               }
               if (y[1]==1 && x[3]==1)
               {
                    mul=1;
                    goto inicio;
               }
               if (mul==1)
               {
                    h[e]=h[e]*h[e-1];
                    mul=0;
               }
               if (y[2]==1 && x[3]==1)
               {
                    resta=1;
                    goto inicio;
               }
               if (resta==1)
               {
                    h[e]=-h[e]+h[e-1];
                    resta=0;
               }
               if (y[0]==1 && x[3]==1)
               {
                    div=1;
                    goto inicio;
               }
               if (div==1)
               {
                    h[e]=h[e-1]/h[e];
                    div=0;
               }
               e=e+1;

            }
             k=k+1;
         }

      }
      goto inicio;
   }
}

