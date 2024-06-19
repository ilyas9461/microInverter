#include "main_gs504_dnm.h"
int rx_f;
char c=0;
void __attribute__((__interrupt__, __auto_psv__)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // clear interrupt flag
}

void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void)
{
    //Herbir karakter geldi?inde kesme olu?uyor....
    IFS0bits.U1RXIF = 0; // clear interrupt flag
    rx_f=1;
    c=U1RXREG;//'a';
    U1TXREG =c;

    if(c=='#'){
        U1TXREG='\n';
        U1TXREG='\r';
        rx_f=0;
    }
}