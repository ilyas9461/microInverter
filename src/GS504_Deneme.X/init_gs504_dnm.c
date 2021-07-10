
#include "p33FJ16GS504.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include <pps.h>
#include <adc.h>

#define FOSC 80000000UL
//#define FCY 40000000UL
#define FCY FOSC/2
#define BAUD 9600
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void initClock(void)
{
    // Configure Oscillator to operate the device at 40 MIPS
    //   Fosc = Fin*M/(N1*N2), Fcy = Fosc/2
    //   Fosc = 7.37*(43)/(2*2) = 80MHz for Fosc, Fcy = 40MHz

    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 41; 			    // M = PLLFBD + 2
    CLKDIVbits.PLLPOST = 0;     // N1 = 2
    CLKDIVbits.PLLPRE = 0;      // N2 = 2

    // Change oscillator to FRC + PLL 
    __builtin_write_OSCCONH(0x01);		// New Oscillator FRC w/ PLL
    __builtin_write_OSCCONL(0x01);  		// Enable Clock Switch
    
    while(OSCCONbits.COSC != 0b001);		// Wait for new Oscillator to become FRC w/ PLL    
    while(OSCCONbits.LOCK != 1);		// Wait for Pll to Lock

    // Now setup the ADC and PWM clock for 120MHz
    //   ((FRC * 16) / APSTSCLR ) = (7.37 * 16) / 1 = ~ 120MHz

    ACLKCONbits.FRCSEL = 1;            // FRC provides input for Auxiliary PLL (x16)
    ACLKCONbits.SELACLK = 1;		   // Auxiliary Ocillator provides clock source for PWM & ADC
    ACLKCONbits.APSTSCLR = 7;		   // Divide Auxiliary clock by 1
    ACLKCONbits.ENAPLL = 1;			   // Enable Auxiliary PLL

    while(ACLKCONbits.APLLCK != 1);			// Wait for Aux. PLL to Lock
    
}
void init_PWM(void)    
{
 	PTCON2bits.PCLKDIV=0;//0b110;		//PWM input clk devider =64
    
    PTPER =16864;//24040;               // Flyback inverter period value
    //PHASE2 = 12020;             // 180Deg phase-shift for second converter
    ALTDTR1 = 1500;//150		// Setup Deadtime for PWM1 and PWM2
    DTR1 = 1500;//50                                                                                 
    PDC1 =PTPER/4;				// Initialize Flyback duty cycle 
    
    PWMCON1bits.ITB = 0;//1;				// Select Independent Timebase mode
    PWMCON1bits.IUE = 1;		// Enable immediate updates
    PWMCON1bits.DTC = 0;	        // Positive dead-time enabled
    
    IOCON1bits.POLL =0;// 1;                // PWM1L and PWM2L have inverted polarity (active-low)
    IOCON1bits.PMOD=0;				       // PWM pair works in complemantry Mode
    
	IOCON1bits.PENH = 1;                  	// PWM1H is controlled by PWM module
	IOCON1bits.PENL = 1;                  	// PWM1H is controlled by PWM module	
    
    //IOCON1bits.POLH = 0;                  	// Drive signals are active-high 
	IOCON1bits.POLL = 1;                // PWM1L and PWM2L have inverted polarity (active-low)
    
    IOCON1bits.OVRDAT = 0;              // Flyback override data (Safe-State)
    IOCON1bits.OVRENH = 0;//1;          // Enable override (Disable MOSFETs)
    IOCON1bits.OVRENL = 0;//1;          //PWM sinyalin kesilmesini yada aktif hale gelmesi için        
       
    // Leading Edge Blanking for Current Protection

    // PWM1H rising and falling edges trigger LEB counter (240ns)
    // LEB is applied to current limit input
    //Leading-Edge Blanking Control-PWM sinyal için sinyalin ön k?sm?ndaki 
    //silme(blanking) kontrolü
    LEBCON1 = 0xC4F0;  //0xB 110001 0011110 000
                       // 0011110=30*8,32nS= 249,6nS
    
    // PWM Fault/Current limit Setup
    FCLCON1bits.FLTMOD = 0;		// Latched Fault Mode
                                //00 = The selected Fault source forces the 
                                //PWMxH and PWMxL pins to the FLTDATx values 
                                //(latched condition)
    FCLCON1bits.CLMOD = 1;		// Current Limit Enabled 1 = Current-Limit mode is enabled
    FCLCON1bits.CLSRC = 1;		// Current Limit Source is Fault 2
    
    FCLCON1bits.CLPOL = 0;		// Current Limit Source is Active High
    
    // Triggers for ADC Module
    TRGCON1bits.TRGDIV = 0;             // Trigger ADC every PWM Period
    TRGCON1bits.TRGSTRT = 0;            // Wait 0 PWM cycles before generating first PWM trigger
     // Triggers for ADC Module
    TRGCON1bits.DTM=1;//1;		//dual trigger mode
	//TRIG1bits.TRGCMP=5000;			//Primary trig compare value 
	//STRIG1bits.STRGCMP=5000;	//secondary trig compare value

 	TRGCON1bits.TRGDIV = 0;		// Trigger generated every PWM cycle
	TRGCON1bits.TRGSTRT = 0;		// enable Trigger generated after 0 PWM cycles 
	TRIG1 =8;//1000;						// Trigger compare value
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void init_ADC(void)  
{	 
    ADCONbits.SLOWCLK = 1;          // Requirement from ADC Errata
    ADCONbits.FORM = 0;             // Output in Integer Format
    ADCONbits.EIE = 0;              // Disable Early Interrupt
    ADCONbits.ORDER = 0;            // Even channel first
    ADCONbits.SEQSAMP = 0;          // Simultaneus Sampling Enabled
    ADCONbits.ASYNCSAMP = 1;        // Asynchronous Sampling Enableed
    ADCONbits.ADCS = 4;             // Clock Divider is set up for Fadc/5, TAD = 41.6ns
                                    // For simultaneus sampling total conversion time for one pair is 0.58us

    ADSTAT = 0;                     // Clear the ADSTAT register
    
    ADPCFGbits.PCFG0 = 0;           // AN0 PV Panel Voltage Sense
    ADPCFGbits.PCFG1 = 0;           // AN1 PV current sense of Interleaved Flyback 1 converter 
    	
    ADCPC0bits.TRGSRC0 = 4;         // AN0 and AN1 triggered by PWM1
    
    IFS6bits.ADCP0IF = 0;			//Clear ADC Pair 0 interrupt flag 
    IPC27bits.ADCP0IP = 6;			//Set ADC Pair 0 interrupt priority
    IEC6bits.ADCP0IE = 1;			//Enable the ADC Pair 0 interrupt
}

/*
        ADPCFGbits.PCFG0 = 0; 		 //select CH0 as analog pin 
    	ADPCFGbits.PCFG1 = 0; 		 //select CH1 as analog pin

    	IFS6bits.ADCP0IF = 0;			//Clear ADC Pair 0 interrupt flag 
    	IPC27bits.ADCP0IP = 4;			//Set ADC Pair 0 interrupt priority
    	IEC6bits.ADCP0IE = 1;			//Enable the ADC Pair 0 interrupt

     	ADSTATbits.P0RDY = 0; 			//Clear Pair 0 data ready bit
    	ADCPC0bits.IRQEN0 = 1;		    //Enable ADC Interrupt pair 0 
    	ADCPC0bits.TRGSRC0 = 4; 		//ADC Pair 0 triggered by PWM1 Trigger
      */

void init_timer2(void){
    
    T2CON = 0;              // Timer reset
 	TMR2 = 0x0000;		
	PR2 = 65535;//0x8000;           // Timer2 period register = 32768
	T2CONbits.TCS = 0;      // Timer2 Clock= internal
    
//Interrupt Stuff
	IPC1bits.T2IP = 6;		// Set Timer2 interrupt priority to 6 
	IFS0bits.T2IF = 0;		// Reset Timer2 interrupt flag 
	IEC0bits.T2IE = 1;		// Enable Timer2 interrupt
  
	T2CONbits.TON = 1;      // Enable Timer2 and start the counter
}
void initCMP(void)
{
    //CMP2C (Flyback Current Phase 1)
    CMPCON2bits.EXTREF = 0;		// Internal Voltage Selected
    CMPCON2bits.RANGE = 1;		// Select Avdd/2 (high-range)
    CMPCON2bits.INSEL = 2;		// Select Comparator 2C

    CMPDAC2bits.CMREF =700;		// CMREF * (Avdd/2) / 1024 - Volts : 1.12V
    CMPCON2bits.CMPON = 1;		// Enable CMP2

    IPC25bits.AC2IP = 7;		// Highest Priority Interrupt
    IFS6bits.AC2IF = 0;			// Clear Interrupt Flag
    IEC6bits.AC2IE = 1;			// Enable Interrupt to declare fault
}
void init_uart(void)
{
    TRISBbits.TRISB6=0; //TX
    TRISBbits.TRISB5=1; //RX
    
    PPSInput(IN_FN_PPS_U1RX,IN_PIN_PPS_RP5);
    PPSOutput(OUT_FN_PPS_U1TX,OUT_PIN_PPS_RP6);

    U1MODE = 0x0000;
    U1STA = 0x0000;

    U1BRG = ((FCY/16)/BAUD) - 1; // set baudrate to BAUD rate

    IEC0bits.U1RXIE = 1;  //Set Rx interrupt enable: veri geldi?inde kesme aktifle?tirildi

    U1MODEbits.UARTEN=1; // UART1 is enabled
    U1STAbits.UTXEN = 1; // Initiate transmission
}