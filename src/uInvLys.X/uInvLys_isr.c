
#include "uInvLys_isr.h"
// System Faults
unsigned char criticalFaultFlag = 0, inverterFrequencyErrorFlag = 0, frequencyFaultCounter = 0;
int maxInverterOutputVoltage = 0, rectifiedInverterOutputVoltage = 0;

// Compensator Variables
int rectifiedInverterOutputCurrent = 0, peakInverterOutputVoltage = 0;
long int Ioutput = 0;
unsigned char fullBridgeState = FULLBRIDGE_INACTIVE_4TH_QUADRANT;

// Inverter Current Reference Variables
unsigned char ninetyDegreeDetectFlag = 0;
unsigned int globalAngle = 0, sineAngle = 0, deltaAngle = 0;
unsigned int currentReferenceDynamic = 0;

// ADC Variables
unsigned int pvPanelVoltage = 0, flybackCurrent1 = 0, flybackCurrent2 = 0;
int inverterOutputVoltage = 0, inverterOutputCurrent = 0, prevInverterOutputVoltage = 0;
unsigned int driveSupplyVoltage = 0, measuredTemperature = 0, referenceVoltage = 0;

// Flyback Current Moving Average Variables/Arrays
unsigned char currentArrayCnt = 0;
unsigned int averageFlybackCurrent1 = 0, averageFlybackCurrent2 = 0;
unsigned int flybackCurrent1Array[8] = {0,0,0,0,0,0,0,0};
unsigned int flybackCurrent2Array[8] = {0,0,0,0,0,0,0,0};
long unsigned int flybackCurrent1Sum = 0, flybackCurrent2Sum = 0;

// AC Current Variables and Moving Avg Variables/Array
unsigned int averageRectifiedCurrent = 0, maxInverterOutputCurrent = 0; 
unsigned int rectifiedInverterOutputCurrentArray[8] = {0,0,0,0,0,0,0,0};
long unsigned int rectifiedInverterOutputCurrentSum = 0;

// Peak Power and Burst Mode Variables
unsigned int averagePeakOutputPower = 0, peakInverterOutputCurrent = 0, peakOutputPower = 0;
unsigned char peakOutputPowerArrayCnt = 0;
unsigned int peakOutputPowerArray[8] = {0,0,0,0,0,0,0,0};
long unsigned int peakOutputPowerSum = 0;
unsigned char burstModeActiveFlag = 0;
unsigned int burstModeActiveCounter = 0;

// Zero Cross Variables
unsigned char zeroCrossDetectFlag = 0, zeroCrossCount = 0, firstQuadrantFlag = 0;
unsigned char thirdQuadrantFlag = 0, avgInputDataReadyFlag = 0;
unsigned char zcCounter = 0, startupZeroCrossCounter = 0;
unsigned char hardwareZeroCrossCounter = 0, prevFullBridgeState = 0;
unsigned int inverterPeriod = 0, inverterPeriodCounter = 0, prevInverterPeriod = 0, numberofSamples = 0;

// MPPT Variables
unsigned int mpptFactorMaximum = 0, mpptDeratingFactor = 0;
long unsigned int inputCurrentSum = 0, inputVoltageSum = 0;

// Externally Defined Variables
extern unsigned char switchState, systemState, faultState, zeroCrossDelay;
extern unsigned char inverterFrequencyState, criticalFaultRestartFlag, startFullBridgeFlag;
extern unsigned char zeroCrossDelayNom, zeroCrossDelayMin, zeroCrossDelayMax;
extern unsigned int mpptFactor, inputVoltageAverage, inputCurrentAverage;
extern unsigned int inverterPeriodMin, inverterPeriodMax, inverterOutputOverCurrent;
//extern int deltaDutyCycle, acCurrentOffset;
/////LYS DEĞİŞkenler
int acCurrentOffset=0;

///

// Variable Declaration for DMCI Debugging Tool
#ifdef DMCI_ISR
int array1[100];
int array2[100];
int array3[100];
unsigned char dmciArrayIndex = 0;
unsigned int dmciCount = 0;
#endif


void __attribute__((interrupt, no_auto_psv)) _CMP2Interrupt()
{
     LED_DRV1=ON;
    //LYS:System error
        IOCON1bits.OVRENH = 1;
        IOCON1bits.OVRENL = 1;
        IOCON2bits.OVRENH = 1;
        IOCON2bits.OVRENL = 1;
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 1;
     //LYS:System error,
        
    // FlyCurrent1    
//    if((criticalFaultFlag == 1) && (criticalFaultRestartFlag == 1))
//    {
//        PTCONbits.PTEN = 0;   //PWM module disable
//        RCONbits.SWDTEN = 0;  // Need to disable WDT
//    }

    // As PWM is latched we need to set the faultState to Flyback overcurrent no matter what
    // so that the latched fault can be removed
    criticalFaultFlag = 1;
//    faultState = FLYBACK_OVERCURRENT;
    
    IFS6bits.AC2IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _CMP3Interrupt()
{
    //LYS:System error
        IOCON1bits.OVRENH = 1;
        IOCON1bits.OVRENL = 1;
        IOCON2bits.OVRENH = 1;
        IOCON2bits.OVRENL = 1;
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 1;
     //LYS:System error
       LED_DRV2=ON; 
    // FlyCurrent2
//    if((criticalFaultFlag == 1) && (criticalFaultRestartFlag == 1))
//    {
//        PTCONbits.PTEN = 0;         //PWM module disable
//        RCONbits.SWDTEN = 0;		// Need to disable WDT
//    }

    // As PWM is latched we need to set the faultState to Flyback overcurrent no matter what
    // so that the latched fault can be removed
    criticalFaultFlag = 1;
    //faultState = FLYBACK_OVERCURRENT;
     
    IFS6bits.AC3IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _CMP4Interrupt()
{
    //LYS:System error
        IOCON1bits.OVRENH = 1;
        IOCON1bits.OVRENL = 1;
        IOCON2bits.OVRENH = 1;
        IOCON2bits.OVRENL = 1;
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 1;
     //LYS:System error
      LED_DRV3=ON; 
    // Flyback Output Over Voltage Condition used only for protection against
    // Full-Bridge failure (in normal operating conditions this event should never occur)

    // Over-ride the flyback MOSFETs immediately
    IOCON1bits.OVRENH = 1;
    IOCON1bits.OVRENL = 1;
    IOCON2bits.OVRENH = 1;
    IOCON2bits.OVRENL = 1;

//    if((criticalFaultFlag == 1) && (criticalFaultRestartFlag == 1))
//    {
//        PTCONbits.PTEN = 0;         //PWM module disable
//        RCONbits.SWDTEN = 0;		// Need to disable WDT
//    }

//    if(faultState == NO_FAULT)
//    {
//        criticalFaultFlag = 1;
//        faultState = FLYBACK_OUTPUT_VOLTAGE;
//    }

    IFS6bits.AC4IF = 0;
}


void __attribute__((interrupt, no_auto_psv)) _ADCP3Interrupt()
{		
    // Read Flyback Current, PV Voltage, and 2.5V Reference in Q15 Format
    pvPanelVoltage  = (ADCBUF0 << 5); 		// Read PV Panel Voltage
    flybackCurrent1 = (ADCBUF1 << 5); 		// Read PV cell Current at Flyback leg1
    flybackCurrent2 = (ADCBUF2 << 5); 		// Read PV cell Current at Flyback leg2 
    referenceVoltage = (ADCBUF6 << 5);		// Read 2.5V Reference Voltage (used for AC offset)

    // Read inverter output voltage and inverter output current (Q14)
    inverterOutputCurrent = (ADCBUF3 << 5) - acCurrentOffset;  //AC Current 
    inverterOutputVoltage = (ADCBUF7 << 5) - referenceVoltage; //AC Voltage
    //2,5 V referans de?erinden küçük de?er okunuyorsa negatif alternans okunmu?tur
    //sonuçta negatif deger ç?kar....

    // Rectified Inverter Output Voltage
    if(inverterOutputVoltage >= 0)
    {
        rectifiedInverterOutputVoltage = inverterOutputVoltage;
    }
    else
    {
        rectifiedInverterOutputVoltage = (-inverterOutputVoltage);
    }

    // Find Peak Inverter Output Voltage
    if(rectifiedInverterOutputVoltage > maxInverterOutputVoltage)
    {
        maxInverterOutputVoltage = rectifiedInverterOutputVoltage;
    }

    // Rectify AC current and check for over current condition on the ouput
    if(inverterOutputCurrent >= 0)
    {
        rectifiedInverterOutputCurrent = inverterOutputCurrent;
    }
    else
    {
        rectifiedInverterOutputCurrent = (-inverterOutputCurrent);
    }

    // Find Peak Inverter Output Current
    if(rectifiedInverterOutputCurrent > maxInverterOutputCurrent)
    {
        maxInverterOutputCurrent = rectifiedInverterOutputCurrent;
    }


    // Moving Average of Flyback Currents for load sharing
    //toplam değerin hep 8 tane değerin toplamı olmasını sağlamak için her toplamda dizi deki 
    //değerin en sonundaki değer toplamdan çıkartılıyor...
    flybackCurrent1Sum = flybackCurrent1Sum + flybackCurrent1 - flybackCurrent1Array[currentArrayCnt];
    averageFlybackCurrent1 = flybackCurrent1Sum >> 3;// 8'e bölmek demek 8 değerin ortalaması

    flybackCurrent2Sum = flybackCurrent2Sum + flybackCurrent2 - flybackCurrent2Array[currentArrayCnt];
    averageFlybackCurrent2 = flybackCurrent2Sum >> 3;

    flybackCurrent1Array[currentArrayCnt] = flybackCurrent1;
    flybackCurrent2Array[currentArrayCnt] = flybackCurrent2;

    // Moving Average of AC Current for AC Current Fault
    rectifiedInverterOutputCurrentSum = rectifiedInverterOutputCurrentSum + rectifiedInverterOutputCurrent - rectifiedInverterOutputCurrentArray[currentArrayCnt];
    averageRectifiedCurrent = rectifiedInverterOutputCurrentSum >> 3;

    rectifiedInverterOutputCurrentArray[currentArrayCnt++] = rectifiedInverterOutputCurrent;

    if(currentArrayCnt >= 8)
    {
        currentArrayCnt = 0;
    }

    // Check for Over Current Condition
    if((averageFlybackCurrent1 > MAXFLYBACKCURRENT)||(averageFlybackCurrent2 > MAXFLYBACKCURRENT))
    {

    }

    // Call zero cross detection function to look for both +ve and -ve zero cross events
    // Routine also keeps track of the number of ADC interrupts over three AC cycles
    // to calculate the average flyback current and PV panel voltage for MPPT

    // To eliminate glitches at the ZC detection only look for a zero cross
    // when inverterPeriodCounter is greater then 200

    if((zeroCrossDetectFlag == 0) && (inverterPeriodCounter > 200))
    {
        //zeroCrossDetection();
    }

    // Store current grid voltage to compare with next sample for ZCD
    prevInverterOutputVoltage = inverterOutputVoltage;


    // Counter for verifying the Grid Frequency (number of ADC interrupts per grid half cycle)
    // variable gets reset when finding the zero crossing event
    inverterPeriodCounter++;
    
    //sinOlustur();
    
    // Accumulate samples for the Average Calculation
    inputCurrentSum = inputCurrentSum + flybackCurrent1 + flybackCurrent2;
    inputVoltageSum = inputVoltageSum + pvPanelVoltage;


    // ZeroCrossDetectFlag is set inside the zeroCrossDetection Routine
    if(zeroCrossDetectFlag == 1)
    {
       
    }else   /////********LYS yazdı... ******//////
        if(zeroCrossDetectFlag == 0)
        {              
            deltaAngle=(int)(58);
            globalAngle=globalAngle+deltaAngle;

             if (globalAngle < ONEHUNDREDSEVENTYFIVEDEGREE)//180 derece
             {
                fullBridgeState=FULLBRIDGE_Q3Q4_ACTIVE;
                 
                if(ninetyDegreeDetectFlag == 0){

                     // if sineAngle is less than 90 degrees, then add deltaAngle to point to next sample
                    if (sineAngle < NINETYDEGREE)
                    {
                        currentReferenceDynamic = sineTable512[((sineAngle) >> 5)];
                        sineAngle = sineAngle + deltaAngle;                        
                    }
                else
                {
                    sineAngle = NINETYDEGREE;
                    ninetyDegreeDetectFlag = 1;
                }

                }else
                    {
                        // if sineAngle is greater than 90 degrees, then subtract deltaAngle from it
                        currentReferenceDynamic = sineTable512[((sineAngle) >> 5)];
                        sineAngle = sineAngle - deltaAngle;
                    
                    }
             }else if((globalAngle>ONEHUNDREDSEVENTYFIVEDEGREE)&&(globalAngle<32767))
             {
                 fullBridgeState = FULLBRIDGE_INACTIVE_2ND_QUADRANT;  
                 sineAngle = 0;
                 ninetyDegreeDetectFlag = 0;
                                  
             }else if(globalAngle>=32767){
                fullBridgeState=FULLBRIDGE_Q2Q5_ACTIVE;
                 
                if(ninetyDegreeDetectFlag == 0){

                     // if sineAngle is less than 90 degrees, then add deltaAngle to point to next sample
                    if (sineAngle < NINETYDEGREE)
                    {
                        currentReferenceDynamic = sineTable512[((sineAngle) >> 5)];
                        sineAngle = sineAngle + deltaAngle;                        
                    }
                else
                {
                    sineAngle = NINETYDEGREE;
                    ninetyDegreeDetectFlag = 1;
                }

                }else
                    {
                        // if sineAngle is greater than 90 degrees, then subtract deltaAngle from it
                        currentReferenceDynamic = sineTable512[((sineAngle) >> 5)];
                        sineAngle = sineAngle - deltaAngle;
                    
                    }
                 if(globalAngle>(65018)){
                    fullBridgeState = FULLBRIDGE_INACTIVE_2ND_QUADRANT;  
                    sineAngle = 0;
                    ninetyDegreeDetectFlag = 0;
                    globalAngle=0;
                 }
             }
            fullBridgeDrive_lys();
            flybackControlLoop_lys();
    }////LYS 


    //Can read AN10 and AN11 here data should be available at this time
    driveSupplyVoltage = (ADCBUF11 << 5);
    measuredTemperature = (ADCBUF10 << 5);

    IFS7bits.ADCP3IF = 0;                   // Clear ADC Interrupt Flag
}

int sinPwm=150;
void sinOlustur(void){
    
    if(inverterPeriodCounter<=256){
     // FULLBRIDGE_Q3Q4_ACTIVE  L+  N-
        OPTO_DRV1 = 1;
        OPTO_DRV2 = 0;
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 0; 
        
        sinPwm=((sineTable512[inverterPeriodCounter*2-1])>>3);//32767/8=4095 max değer 4095/16864=0,24 %24 duty demek oluyor....
               
    }else if((inverterPeriodCounter>256)&&inverterPeriodCounter<=512){
        
        sinPwm=((sineTable512[((512-inverterPeriodCounter)*2)])>>3);
        
    }else if((inverterPeriodCounter>512)&&inverterPeriodCounter<=768){//0 da
        
        //FULLBRIDGE_Q2Q5_ACTIVE   L-   N+  
        OPTO_DRV1 = 0; //Mosfet on
        OPTO_DRV2 = 1; //Mosfet off
        IOCON3bits.OVRENH = 0;
        IOCON2bits.OVRENL = 1;

        sinPwm=((sineTable512[((inverterPeriodCounter-512)*2)-1])>>3);          
    }
    else if((inverterPeriodCounter>768)&&inverterPeriodCounter<=1024){
        
         sinPwm=((sineTable512[((1024-inverterPeriodCounter)*2)])>>3); 
         
    }else inverterPeriodCounter=0;
    
    if(sinPwm<150)sinPwm=150;
    else if(sinPwm>4095)sinPwm=4216;//0,25Duty
    
    PDC1=sinPwm;
    PDC2=sinPwm;
    
}

void zeroCrossDetection_lys(void)
{
    // Detect the zero crossing at the 1st Quadrant
    if((prevInverterOutputVoltage < 0) && (inverterOutputVoltage >= 0))
    {
        // As a precaution change state of Full-Bridge if it hasn't already chaged
        fullBridgeState = FULLBRIDGE_INACTIVE_4TH_QUADRANT;

        ClrWdt();

        zeroCrossDetectFlag = 1;
        firstQuadrantFlag = 1;				// Allows Full-Bridge to change State

        // Load counter to Grid Period to check grid frequency
        inverterPeriod = inverterPeriodCounter;
        inverterPeriodCounter = 0;

        // Store accumulated voltage/current sum and counter for avg (avg calculated in T2ISR)
        // The average is calculated every 3rd +ve zero cross event
        zeroCrossCount++;

        if (zeroCrossCount == 1)
        {
            numberofSamples = 0;
        }

        // inverterPeriod is only half cycle so add prevInverterPeriod
        numberofSamples = numberofSamples + inverterPeriod + prevInverterPeriod;

        if(zeroCrossCount >= 3)
        {
            zeroCrossCount = 0;

         //   inputVoltageAverage = __builtin_divsd((long)inputVoltageSum ,(int)(numberofSamples));
         //   inputCurrentAverage = __builtin_divsd((long)inputCurrentSum ,(int)(numberofSamples));
            numberofSamples = 0;
            inputVoltageSum = 0;
            inputCurrentSum = 0;

            avgInputDataReadyFlag = 1;
        }
    }

    // Detect the zero crossing at the 3rd Quadrant
    else if ((prevInverterOutputVoltage >= 0) && (inverterOutputVoltage < 0))
    {
        // As a precaution change state of Full-Bridge if it hasn't already chaged
        fullBridgeState = FULLBRIDGE_INACTIVE_2ND_QUADRANT;

        ClrWdt();

        zeroCrossDetectFlag = 1;
        thirdQuadrantFlag = 1;			// Allows Full-Bridge to change State

        // Load counter to Grid Period to check grid frequency
        inverterPeriod = inverterPeriodCounter;
        inverterPeriodCounter = 0;
    }
}

void inverterFrequencyCheck(void)
{
   

    prevInverterPeriod = inverterPeriod;	// Store Inverter Period for average calculation
}

void fullBridgeDrive_lys(void)
{
    // Now that we know the state we can modify the PWM outputs

    if(fullBridgeState == FULLBRIDGE_Q3Q4_ACTIVE)
    {
        OPTO_DRV1 = 1;
        OPTO_DRV2 = 0;
        IOCON3bits.OVRENL = 0;
    }
    else if (fullBridgeState == FULLBRIDGE_INACTIVE_2ND_QUADRANT)
    {
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 1;
        OPTO_DRV2 = 1;
        OPTO_DRV1 = 1;
    }
    else if (fullBridgeState == FULLBRIDGE_Q2Q5_ACTIVE)
    {
        OPTO_DRV2 = 1;
        OPTO_DRV1 = 0;
        IOCON3bits.OVRENH = 0;
    }
    else
    {
        IOCON3bits.OVRENH = 1;
        IOCON3bits.OVRENL = 1;
        OPTO_DRV2 = 1;
        OPTO_DRV1 = 1;
    }
}


void flybackControlLoop_lys(void)
{
    unsigned int flybackDutyCycle = 0;
    unsigned int rectifiedVac = 0, decoupleTerm = 0;
    int IoRef = 0, currentError = 0, Poutput = 0;
    long int totalOutput = 0;

//    peakInverterOutputVoltage=10512;//Q14 olarak Vp=100V Adcbuf değeri
//    // Input/Output Voltage Decoupling Software (Vo/(Vin + Vo))
//    //lys:  D=(Vo/(Vin*N + Vo))
//    // rectifiedVac is in Q13 format          Q15				Q14
//    rectifiedVac = (__builtin_mulss((int)currentReferenceDynamic,(int)peakInverterOutputVoltage) >> 16);
//    //                                        Q14                  Q15                                                     
//    decoupleTerm = rectifiedVac + (__builtin_mulss(27573,(int)pvPanelVoltage) >> 16);
//    
//     // Divide Q26/Q13, result is in Q13
//    decoupleTerm = __builtin_divsd(((long)rectifiedVac << 13) ,decoupleTerm);
//
//    // Total Compensator Output, decoupleTerm is scaled back to Q15 as totalOutput is clamped to Q15
//    totalOutput = totalOutput + (long)(decoupleTerm << 2);//2 bit sa?a kayd?rarak Q15 yap?yor...
//
//    // Clamp total output to the maximum Duty Cycle
//    if(totalOutput > MAXDUTYCLAMPED)
//    {
//        totalOutput = MAXDUTYCLAMPED;
//    }
//    else if(totalOutput < 0)
//    {
//        totalOutput = 0;
//    }
//
//    // Multiply flyback period by total output to get the flyback duty cycle
//    flybackDutyCycle = (__builtin_mulss((int)totalOutput,(int)FLYBACKPERIOD) >> 15);
    
    flybackDutyCycle=(currentReferenceDynamic>>3);
    // If duty cycle is less than dead-time make duty cycle equal to dead-time
    if(flybackDutyCycle < FLYBACKALTDTR)
    {
        FLYBACKDUTY1 = FLYBACKALTDTR;
        FLYBACKDUTY2 = FLYBACKALTDTR;
    }
    else
    {
        FLYBACKDUTY1 = flybackDutyCycle;//+ deltaDutyCycle ;
        FLYBACKDUTY2 = flybackDutyCycle;//- deltaDutyCycle ;
    }

    // Update ADC Triggers (trigger near end of PWM On-time)
    TRIG1 = FLYBACKDUTY1 - (FLYBACKDUTY1 >> 2);
    TRIG2 = FLYBACKDUTY2 - (FLYBACKDUTY2 >> 2);
}