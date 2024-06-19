#include <libpic30.h>

#include "uInvLys_main.h"
// Configuration bits
// Start-up with FRC and switch to FRC w/ Pll
// Configure Watch Dog Timeout (Software Enable/Disable)
// Select ICSP Pair 2 for debugging/programming
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & IOL1WAY_OFF)
_FWDT(FWDTEN_OFF & WDTPOST_PS16 & WDTPRE_PR32 & WINDIS_OFF)
_FPOR(FPWRT_PWR128)
_FICD(ICS_PGD2 & JTAGEN_OFF)
int x=0;
int main() {
    
    initClock();                            // Initialize Device Oscillator and Auxiliary Oscillator (PWM/ADC)
    initIOPorts();                          // Initialize all I/O Ports
    initADC();                              // Initialize ADC Module:
  
    ADCONbits.ADON = 1;                     // Enable the ADC Module early for ADC Settling Time
    
    initCMP();                              // Initialize Comparator Module
    initPWM();                              // Initialize PWM Module 
    
    //T2CONbits.TON = 1;                      // Enable State Machine Timer
    PTCONbits.PTEN = 1;                     // Enable PWM Module

    //RCONbits.SWDTEN = 1;                    // Enable WDT (cleared at every zero cross)
   // LED_DRV1=ON;
    
    //PDC1=FLYBACKPERIOD/10;
    //PDC2=FLYBACKPERIOD/10;
    
    IOCON1bits.OVRENH = 0;
    IOCON1bits.OVRENL = 0;
    IOCON2bits.OVRENH = 0;
    IOCON2bits.OVRENL = 0;
    //IOCON3bits.OVRENH = 0;
    //IOCON3bits.OVRENL = 0;
    //Kopru pasif
    OPTO_DRV2 = 1;
    OPTO_DRV1 = 1;

    while(1)
    {
        Nop();
        Nop();
        Nop();
        
    }

    return (0);
}

//        Nop();
//        Nop();
//        Nop();
//        x+=10;
//        PDC1=x;
//        PDC2=x;
//        __delay32(40000*5);
//        if(x>FLYBACKPERIOD-10)x=0;
////****
 //FULLBRIDGE_Q2Q5_ACTIVE  N+   L-
//        OPTO_DRV1 = 0; //Mosfet on
//        OPTO_DRV2 = 1; //Mosfet off
//        IOCON3bits.OVRENH = 0;
//        IOCON2bits.OVRENL = 1;
//        
//         __delay32(40000*4000);
//        
//        //Kopru Mosfetleri OFF
//        OPTO_DRV1 = 1;
//        OPTO_DRV2 = 1;
//        IOCON3bits.OVRENH = 1;
//        IOCON2bits.OVRENL = 1;
//        
//        __delay32(40000*1000);
//        
//        // FULLBRIDGE_Q3Q4_ACTIVE  L+  N-
//        OPTO_DRV1 = 1;
//        OPTO_DRV2 = 0;
//        IOCON3bits.OVRENH = 1;
//        IOCON3bits.OVRENL = 0; 
//                
//         __delay32(40000*4000);
//         
//          //Kopru Mosfetleri OFF
//        OPTO_DRV1 = 1;
//        OPTO_DRV2 = 1;
//        IOCON3bits.OVRENH = 1;
//        IOCON2bits.OVRENL = 1;
//        
//        __delay32(40000*1000);

