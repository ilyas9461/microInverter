#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include <pps.h>
#include <adc.h>

#include <p33FJ16GS504.h>

void init_PWM(void);
void init_ADC(void);
void initClock(void);
void init_uart(void);
void init_timer2(void);
void initCMP(void);
void __attribute__((__interrupt__,no_auto_psv)) _ADCP0Interrupt ();
void __attribute__((__interrupt__, __auto_psv__)) _U1TXInterrupt(void);
void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt(void);