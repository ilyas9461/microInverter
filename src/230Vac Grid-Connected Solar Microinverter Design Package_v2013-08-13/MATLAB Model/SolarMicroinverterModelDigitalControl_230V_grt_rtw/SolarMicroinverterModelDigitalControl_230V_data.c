/*
 * SolarMicroinverterModelDigitalControl_230V_data.c
 *
 * Code generation for model "SolarMicroinverterModelDigitalControl_230V".
 *
 * Model version              : 1.935
 * Simulink Coder version : 8.7 (R2014b) 08-Sep-2014
 * C source code generated on : Tue Jun 28 16:26:06 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "SolarMicroinverterModelDigitalControl_230V.h"
#include "SolarMicroinverterModelDigitalControl_230V_private.h"

/* Block parameters (auto storage) */
P_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_P = {
  /*  Mask Parameter: CARRIER_rep_seq_y
   * Referenced by: '<S13>/Look-Up Table1'
   */
  { 0.0, 1.0 },

  /*  Mask Parameter: CARRIER1_rep_seq_y
   * Referenced by: '<S14>/Look-Up Table1'
   */
  { 0.0, 1.0 },
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  314.15926535897933,                  /* Expression: 2*pi*50
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  215.0,                               /* Expression: 215
                                        * Referenced by: '<S15>/POWER'
                                        */
  230.0,                               /* Expression: 230
                                        * Referenced by: '<S15>/RMS GridVoltage'
                                        */
  1.4142135623730951,                  /* Expression: sqrt(2)
                                        * Referenced by: '<S15>/Gain1'
                                        */
  -721604.84918458655,                 /* Computed Parameter: Filter1_A
                                        * Referenced by: '<S1>/Filter1'
                                        */
  721604.84918458655,                  /* Computed Parameter: Filter1_C
                                        * Referenced by: '<S1>/Filter1'
                                        */
  0.46728971962616822,                 /* Expression: 1/2.14
                                        * Referenced by: '<S1>/PerUnitizingGain'
                                        */

  /*  Expression: [0.1805 -0.1595]
   * Referenced by: '<S1>/PI Controller'
   */
  { 0.1805, -0.1595 },

  /*  Expression: [1 -1]
   * Referenced by: '<S1>/PI Controller'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/PI Controller'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Integrator1'
                                        */
  1.7E-5,                              /* Expression: period
                                        * Referenced by: '<S13>/Constant'
                                        */

  /*  Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S13>/Look-Up Table1'
   */
  { 0.0, 1.7E-5 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition3'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S12>/Duty Limit2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition2'
                                        */
  0.75,                                /* Expression: 0.75
                                        * Referenced by: '<S12>/Duty Limit'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  200.0,                               /* Expression: 200
                                        * Referenced by: '<S5>/CURRENT LIMIT'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S5>/CURRENT LIMIT'
                                        */
  0.14285714285714285,                 /* Expression: 1/7
                                        * Referenced by: '<S5>/Gain3'
                                        */
  8.5E-6,                              /* Expression: 8.5e-6
                                        * Referenced by: '<S12>/Transport Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Transport Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition4'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S12>/Duty Limit3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit3'
                                        */
  0.75,                                /* Expression: 0.75
                                        * Referenced by: '<S12>/Duty Limit1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Integrator'
                                        */
  200.0,                               /* Expression: 200
                                        * Referenced by: '<S6>/CURRENT LIMIT'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S6>/CURRENT LIMIT'
                                        */
  0.14285714285714285,                 /* Expression: 1/7
                                        * Referenced by: '<S6>/Gain3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S7>/Integrator'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<S7>/ LIMIT'
                                        */
  -0.5,                                /* Expression: -0.5
                                        * Referenced by: '<S7>/ LIMIT'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S2>/ESR'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator3'
                                        */
  0.04,                                /* Expression: 0.04
                                        * Referenced by: '<S5>/Ron+Rp'
                                        */
  25.0,                                /* Expression: 1/0.04
                                        * Referenced by: '<S5>/1//(Ron+Rp)'
                                        */
  0.05,                                /* Expression: 0.05
                                        * Referenced by: '<S4>/Resr'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S4>/VOLTAGE LIMIT'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/VOLTAGE LIMIT'
                                        */
  7.0,                                 /* Expression: 7
                                        * Referenced by: '<S10>/TURNS'
                                        */
  -7352.9411764705883,                 /* Computed Parameter: SWFilter_A
                                        * Referenced by: '<S11>/S//W Filter'
                                        */
  7352.9411764705883,                  /* Computed Parameter: SWFilter_C
                                        * Referenced by: '<S11>/S//W Filter'
                                        */
  -7352.9411764705883,                 /* Computed Parameter: SWFilter1_A
                                        * Referenced by: '<S11>/S//W Filter1'
                                        */
  7352.9411764705883,                  /* Computed Parameter: SWFilter1_C
                                        * Referenced by: '<S11>/S//W Filter1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/CURRENT REF ERROR'
                                        */
  0.12363636363636364,                 /* Expression: 1.36/11
                                        * Referenced by: '<S11>/Per Unitizing Gain + Base Conversion'
                                        */

  /*  Expression: [0.07 -0.06]
   * Referenced by: '<S11>/PI Controller'
   */
  { 0.07, -0.06 },

  /*  Expression: [1 -1]
   * Referenced by: '<S11>/PI Controller'
   */
  { 1.0, -1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S11>/PI Controller'
                                        */
  0.5,                                 /* Expression: 1/2
                                        * Referenced by: '<S11>/deltaD//2'
                                        */
  -1.016260162601626E+6,               /* Computed Parameter: HWFilter_A
                                        * Referenced by: '<S11>/H//W Filter'
                                        */
  1.016260162601626E+6,                /* Computed Parameter: HWFilter_C
                                        * Referenced by: '<S11>/H//W Filter'
                                        */
  -1.016260162601626E+6,               /* Computed Parameter: HWFilter1_A
                                        * Referenced by: '<S11>/H//W Filter1'
                                        */
  1.016260162601626E+6,                /* Computed Parameter: HWFilter1_C
                                        * Referenced by: '<S11>/H//W Filter1'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S11>/Invert'
                                        */
  1.7E-5,                              /* Expression: period
                                        * Referenced by: '<S14>/Constant'
                                        */

  /*  Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S14>/Look-Up Table1'
   */
  { 0.0, 1.7E-5 },
  2.8985507246376812E+6,               /* Expression: 1/(0.1e-6*3+0.015e-6 * 3)
                                        * Referenced by: '<S2>/1//Co'
                                        */
  1.4142135623730951,                  /* Expression: sqrt(2)
                                        * Referenced by: '<S15>/Gain2'
                                        */
  138.88888888888889,                  /* Expression: 1/(4*1800E-6)
                                        * Referenced by: '<S4>/1//Cin'
                                        */
  36.0,                                /* Expression: 36
                                        * Referenced by: '<S9>/Vmpp'
                                        */
  1.0E-7,                              /* Expression: 1e-7
                                        * Referenced by: '<S4>/Transport Delay1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Transport Delay1'
                                        */
  0.02,                                /* Expression: 0.02
                                        * Referenced by: '<S4>/Rin'
                                        */
  4.5454545454545449E+6,               /* Expression: 1/0.22e-6
                                        * Referenced by: '<S4>/1//Lin'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S5>/Rs'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S5>/Diode Drop'
                                        */
  0.14285714285714285,                 /* Expression: 1/7
                                        * Referenced by: '<S5>/1//N'
                                        */
  18181.81818181818,                   /* Expression: 1/55e-6
                                        * Referenced by: '<S5>/1//L'
                                        */
  0.04,                                /* Expression: 0.04
                                        * Referenced by: '<S6>/Ron+Rp'
                                        */
  25.0,                                /* Expression: 1/0.04
                                        * Referenced by: '<S6>/1//(Ron+Rp)'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S6>/Rs'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S6>/Diode Drop'
                                        */
  0.14285714285714285,                 /* Expression: 1/7
                                        * Referenced by: '<S6>/1//N'
                                        */
  20000.0,                             /* Expression: 1/50e-6
                                        * Referenced by: '<S6>/1//L'
                                        */
  0.6,                                 /* Expression: 2*0.2+2*60e-3 + 2*40e-3
                                        * Referenced by: '<S7>/Rf'
                                        */
  3333.3333333333335,                  /* Expression: 1/300e-6
                                        * Referenced by: '<S7>/1//Lf'
                                        */
  0.0033333333333333335                /* Expression: 1/300
                                        * Referenced by: '<S8>/ScaleDown'
                                        */
};
