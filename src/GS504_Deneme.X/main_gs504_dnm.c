#include "main_gs504_dnm.h"

#define FOSC 80000000UL
//#define FCY 40000000UL
#define FCY FOSC/2
#include <libpic30.h> 


#define LED_DRV1 LATCbits.LATC12
#define LED_DRV2 LATCbits.LATC3
#define LED_DRV3 LATCbits.LATC8
#define LED_HIZ 150

_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(FWDTEN_OFF)
_FPOR(FPWRT_PWR128 )
_FICD(ICS_PGD2& JTAGEN_OFF) 

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int x=0;
extern int rx_f;
int main(int argc, char** argv) {
     
    initClock();
    
    TRISCbits.TRISC12=0;
    TRISCbits.TRISC3=0;
    TRISCbits.TRISC8=0;
    
        
    init_uart();
    //init_timer2();
	init_PWM();								// PWM Setup		
	//init_ADC();								// ADC Setup
   // initCMP();
    printf("Sistem Basladi...\n\r");
    
    PTCONbits.PTEN = 1;					// Enable the PWM  
	//ADCONbits.ADON = 1;					// Enable the ADC  
    rx_f=0;
    while(1){
        if(rx_f==0)printf("x=%u \r",x++);
        LED_DRV1=1;__delay_ms(LED_HIZ);
        LED_DRV2=1;__delay_ms(LED_HIZ);
        LED_DRV3=1; __delay_ms(LED_HIZ);
        LED_DRV3=0;__delay_ms(LED_HIZ); 
        LED_DRV2=0;__delay_ms(LED_HIZ);
        LED_DRV1=0;__delay_ms(LED_HIZ);
    }

    return (EXIT_SUCCESS);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
