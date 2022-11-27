#define rs LATC.RC0;
#define rv LATC.RC1;
#define en LATC.RC2;

#define c1 PORTB.RB4;
#define c2 PORTB.RB5;
#define c3 PORTB.RB6;
#define c4 PORTB.RB7;

#define r1 PORTB.RB0;
#define r2 PORTB.RB1;
#define r3 PORTB.RB2;
#define r4 PORTB.RB3;

void lcdcmd(unsigned char);
void lcddata(unsigned char);
void col1();
void col2();
void col3();
void col4();

void main(void) {
    ADCON1 = 0x0F;      //disable ADC
    TRISD = 0x00;       //portd as output
    TRISC = 0x00;       //portc as output
    TRISB = 0xF0;       //upper pins as input and lower pins as output
    LATC = 0x00;
    LATD = 0x00;
    INTCON.RBPU = 0;     //pull-up resistors disable
    
    lcdcmd(0x38);       //2 lines and 5x7 matrix
    lcdcmd(0x0E);       //display on and cursor blinking
    lcdcmd(0x01);       // clear display
    lcdcmd(0x80);       //force cursor to be on the first line
    
    c1=c2=c3=c4=1;
    
    while(1)  
    { 
        r1=r2=r3=r4=0;
        while (c1==1 && c2== 1 && c3== 1 && c4==1);
        if(c1==0)
        {
            col1();
        }
        if(c2==0)
        {
            col2();
        }
        if(c3==0)
        {
            col3();
        }if(c4==0)
        {
            col4();
        }
    }
}

void col1(){
    r1=r2=r3=r4=1;
    r1=0;
    if(c1==0){
        while(c1==0);   //loop until the key is pressed
        lcddata('7');
    }
    r1=1;
    r2=0;
    if(c1==0){
        while(c1==0);
        lcddata('4');
    }
    r2=1;
    r3=0;
    if(c1==0){
        while(c1==0);
        lcddata('1');
    }
    r3=1;
    r4=0;
    if(c1==0){
        while(c1==0);
        lcddata('o');
    }
    r4=1;
}
void col2(){
    r1=r2=r3=r4=1;
    r1=0;
    if(c2==0){
        while(c2==0);   //loop until the key is pressed
        lcddata('8');
    }
    r1=1;
    r2=0;
    if(c2==0){
        while(c2==0);
        lcddata('5');
    }
    r2=1;
    r3=0;
    if(c2==0){
        while(c2==0);
        lcddata('2');
    }
    r3=1;
    r4=0;
    if(c2==0){
        while(c2==0);
        lcddata('0');
    }
    r4=1;
}
void col3(){
    r1=r2=r3=r4=1;
    r1=0;
    if(c3==0){
        while(c3==0);   //loop until the key is pressed
        lcddata('9');
    }
    r1=1;
    r2=0;
    if(c3==0){
        while(c3==0);
        lcddata('6');
    }
    r2=1;
    r3=0;
    if(c3==0){
        while(c3==0);
        lcddata('3');
    }
    r3=1;
    r4=0;
    if(c3==0){
        while(c3==0);
        lcddata('=');
    }
    r4=1;
}
void col4(){
    r1=r2=r3=r4=1;
    r1=0;
    if(c4==0){
        while(c4==0);   //loop until the key is pressed
        lcddata('/');
    }
    r1=1;
    r2=0;
    if(c4==0){
        while(c4==0);
        lcddata('X');
    }
    r2=1;
    r3=0;
    if(c4==0){
        while(c4==0);
        lcddata('-');
    }
    r3=1;
    r4=0;
    if(c4==0){
        while(c4==0);
        lcddata('+');
    }
    r4=1;
}

void lcdcmd(unsigned char a1)
{
    LATD=a1;
    rs = 0;
    en = 0;
    __delay_ms(25);
    en = 1;
}

void lcddata(unsigned char a2)
{
    LATD=a2;
    rs = 1;
    en = 0;
    __delay_ms(25);
    en = 1;
}