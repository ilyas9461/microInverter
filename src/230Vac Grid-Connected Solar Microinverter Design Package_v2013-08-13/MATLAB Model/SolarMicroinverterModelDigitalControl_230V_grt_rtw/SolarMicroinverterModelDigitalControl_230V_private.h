/*
 * SolarMicroinverterModelDigitalControl_230V_private.h
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
#ifndef RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_private_h_
#define RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"

extern real_T rt_roundd_snf(real_T u);
extern real_T rt_remd_snf(real_T u0, real_T u1);
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;
extern real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
void SolarMicroinverterModelDigitalControl_230V_output0(void);
void SolarMicroinverterModelDigitalControl_230V_update0(void);
void SolarMicroinverterModelDigitalControl_230V_output2(void);
void SolarMicroinverterModelDigitalControl_230V_update2(void);
void SolarMicroinverterModelDigitalControl_230V_output3(void);
void SolarMicroinverterModelDigitalControl_230V_update3(void);/* private model entry point functions */
extern void SolarMicroinverterModelDigitalControl_230V_derivatives(void);

#endif                                 /* RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_private_h_ */
