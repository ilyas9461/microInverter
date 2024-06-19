/*
 * SolarMicroinverterModelDigitalControl_230V.c
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

/* Block signals (auto storage) */
B_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_B;

/* Continuous states */
X_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_X;

/* Block states (auto storage) */
DW_SolarMicroinverterModelDig_T SolarMicroinverterModelDigit_DW;

/* Real-time model */
RT_MODEL_SolarMicroinverterMo_T SolarMicroinverterModelDigit_M_;
RT_MODEL_SolarMicroinverterMo_T *const SolarMicroinverterModelDigit_M =
  &SolarMicroinverterModelDigit_M_;
static void rate_monotonic_scheduler(void);

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
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
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(SolarMicroinverterModelDigit_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(SolarMicroinverterModelDigit_M, 2);
  rtmSampleHitPtr[3] = rtmStepTask(SolarMicroinverterModelDigit_M, 3);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rates: 2, 3 */
  SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_2 =
    (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[2] == 0);

  /* update PerTaskSampleHits matrix for non-inline sfcn */
  SolarMicroinverterModelDigit_M->Timing.perTaskSampleHits[2] =
    SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_2;
  SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_3 =
    (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[3] == 0);

  /* update PerTaskSampleHits matrix for non-inline sfcn */
  SolarMicroinverterModelDigit_M->Timing.perTaskSampleHits[3] =
    SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_3;

  /* tid 1 shares data with slower tid rates: 2, 3 */
  if (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[1] == 0) {
    SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_2 =
      (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    SolarMicroinverterModelDigit_M->Timing.perTaskSampleHits[6] =
      SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_2;
    SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_3 =
      (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[3] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    SolarMicroinverterModelDigit_M->Timing.perTaskSampleHits[7] =
      SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_3;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[2])++;
  if ((SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[2]) > 169) {/* Sample time: [1.7E-5s, 0.0s] */
    SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[2] = 0;
  }

  (SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[3])++;
  if ((SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[3]) > 1999) {/* Sample time: [0.0002s, 0.0s] */
    SolarMicroinverterModelDigit_M->Timing.TaskCounters.TID[3] = 0;
  }
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 11;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  SolarMicroinverterModelDigitalControl_230V_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  SolarMicroinverterModelDigitalControl_230V_output0();
  SolarMicroinverterModelDigitalControl_230V_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  SolarMicroinverterModelDigitalControl_230V_output0();
  SolarMicroinverterModelDigitalControl_230V_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  SolarMicroinverterModelDigitalControl_230V_output0();
  SolarMicroinverterModelDigitalControl_230V_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T u1_0;
  if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf(u1)))))
  {
    y = (rtNaN);
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = u0 / u1;
      if (fabs(u1_0 - rt_roundd_snf(u1_0)) <= DBL_EPSILON * fabs(u1_0)) {
        y = 0.0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* Model output function for TID0 */
void SolarMicroinverterModelDigitalControl_230V_output0(void) /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_Product1_g;
  real_T rtb_DataTypeConversion1;
  real_T rtb_DataTypeConversion2;
  real_T rtb_Abs;
  real_T rtb_VOLTAGELIMIT;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_RelationalOperator1;
  int32_T rtb_DataTypeConversion3;
  real_T rtb_Sum2_b;
  real_T rtb_Product1;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* set solver stop time */
    if (!(SolarMicroinverterModelDigit_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&SolarMicroinverterModelDigit_M->solverInfo,
                            ((SolarMicroinverterModelDigit_M->Timing.clockTickH0
        + 1) * SolarMicroinverterModelDigit_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&SolarMicroinverterModelDigit_M->solverInfo,
                            ((SolarMicroinverterModelDigit_M->Timing.clockTick0
        + 1) * SolarMicroinverterModelDigit_M->Timing.stepSize0 +
        SolarMicroinverterModelDigit_M->Timing.clockTickH0 *
        SolarMicroinverterModelDigit_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(SolarMicroinverterModelDigit_M)) {
    SolarMicroinverterModelDigit_M->Timing.t[0] = rtsiGetT
      (&SolarMicroinverterModelDigit_M->solverInfo);
  }

  /* Sin: '<S3>/UNIT SINE' */
  SolarMicroinverterModelDigita_B.UNITSINE = sin
    (SolarMicroinverterModelDigita_P.UNITSINE_Freq *
     SolarMicroinverterModelDigit_M->Timing.t[0] +
     SolarMicroinverterModelDigita_P.UNITSINE_Phase) *
    SolarMicroinverterModelDigita_P.UNITSINE_Amp +
    SolarMicroinverterModelDigita_P.UNITSINE_Bias;

  /* Abs: '<S15>/Abs' */
  rtb_Abs = fabs(SolarMicroinverterModelDigita_B.UNITSINE);
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Gain: '<S15>/Gain1' incorporates:
     *  Constant: '<S15>/POWER'
     *  Constant: '<S15>/RMS GridVoltage'
     *  Product: '<S15>/Divide'
     */
    SolarMicroinverterModelDigita_B.Gain1 =
      SolarMicroinverterModelDigita_P.POWER_Value /
      SolarMicroinverterModelDigita_P.RMSGridVoltage_Value *
      SolarMicroinverterModelDigita_P.Gain1_Gain;
  }

  /* Product: '<S15>/Product1' */
  SolarMicroinverterModelDigita_B.Product1 = rtb_Abs *
    SolarMicroinverterModelDigita_B.Gain1;

  /* TransferFcn: '<S1>/Filter1' */
  SolarMicroinverterModelDigita_B.Filter1 = 0.0;
  SolarMicroinverterModelDigita_B.Filter1 +=
    SolarMicroinverterModelDigita_P.Filter1_C *
    SolarMicroinverterModelDigita_X.Filter1_CSTATE;

  /* Sum: '<S1>/Sum1' */
  SolarMicroinverterModelDigita_B.Sum1 =
    SolarMicroinverterModelDigita_B.Product1 -
    SolarMicroinverterModelDigita_B.Filter1;

  /* RateTransition: '<S1>/Rate Transition1' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M) &&
      SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_2) {
    SolarMicroinverterModelDigita_B.RateTransition1 =
      SolarMicroinverterModelDigita_B.Sum1;
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* Clock: '<S13>/Clock' */
  rtb_DataTypeConversion1 = SolarMicroinverterModelDigit_M->Timing.t[0];

  /* Sum: '<S13>/Sum' incorporates:
   *  S-Function (sfun_tstart): '<S13>/startTime'
   */
  rtb_DataTypeConversion1 -= (0.0);
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S13>/Constant' */
    SolarMicroinverterModelDigita_B.Constant =
      SolarMicroinverterModelDigita_P.Constant_Value;
  }

  /* Math: '<S13>/Math Function' */
  rtb_DataTypeConversion1 = rt_remd_snf(rtb_DataTypeConversion1,
    SolarMicroinverterModelDigita_B.Constant);

  /* Lookup_n-D: '<S13>/Look-Up Table1' */
  SolarMicroinverterModelDigita_B.LookUpTable1 = look1_binlxpw
    (rtb_DataTypeConversion1,
     SolarMicroinverterModelDigita_P.LookUpTable1_bp01Data,
     SolarMicroinverterModelDigita_P.CARRIER_rep_seq_y, 1U);

  /* RateTransition: '<S1>/Rate Transition3' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    if (SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_3) {
      SolarMicroinverterModelDigita_B.RateTransition3 =
        SolarMicroinverterModelDigit_DW.RateTransition3_Buffer0;
    }

    /* RateTransition: '<S1>/Rate Transition2' */
    if (SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_2) {
      SolarMicroinverterModelDigita_B.RateTransition2 =
        SolarMicroinverterModelDigit_DW.RateTransition2_Buffer0;
    }

    /* End of RateTransition: '<S1>/Rate Transition2' */

    /* Saturate: '<S12>/Duty Limit2' */
    if (SolarMicroinverterModelDigita_B.RateTransition3 >
        SolarMicroinverterModelDigita_P.DutyLimit2_UpperSat) {
      rtb_Sum2_b = SolarMicroinverterModelDigita_P.DutyLimit2_UpperSat;
    } else if (SolarMicroinverterModelDigita_B.RateTransition3 <
               SolarMicroinverterModelDigita_P.DutyLimit2_LowerSat) {
      rtb_Sum2_b = SolarMicroinverterModelDigita_P.DutyLimit2_LowerSat;
    } else {
      rtb_Sum2_b = SolarMicroinverterModelDigita_B.RateTransition3;
    }

    /* Sum: '<S12>/Sum1' incorporates:
     *  Saturate: '<S12>/Duty Limit2'
     */
    rtb_Sum2_b += SolarMicroinverterModelDigita_B.RateTransition2;

    /* Saturate: '<S12>/Duty Limit' */
    if (rtb_Sum2_b > SolarMicroinverterModelDigita_P.DutyLimit_UpperSat) {
      SolarMicroinverterModelDigita_B.DutyLimit =
        SolarMicroinverterModelDigita_P.DutyLimit_UpperSat;
    } else if (rtb_Sum2_b < SolarMicroinverterModelDigita_P.DutyLimit_LowerSat)
    {
      SolarMicroinverterModelDigita_B.DutyLimit =
        SolarMicroinverterModelDigita_P.DutyLimit_LowerSat;
    } else {
      SolarMicroinverterModelDigita_B.DutyLimit = rtb_Sum2_b;
    }

    /* End of Saturate: '<S12>/Duty Limit' */
  }

  /* End of RateTransition: '<S1>/Rate Transition3' */

  /* RelationalOperator: '<S12>/Relational Operator' */
  rtb_RelationalOperator = (SolarMicroinverterModelDigita_B.LookUpTable1 <=
    SolarMicroinverterModelDigita_B.DutyLimit);

  /* DataTypeConversion: '<S12>/Data Type Conversion1' incorporates:
   *  Logic: '<S12>/Logical Operator'
   */
  rtb_DataTypeConversion1 = !rtb_RelationalOperator;

  /* Saturate: '<S5>/CURRENT LIMIT' incorporates:
   *  Integrator: '<S5>/Integrator'
   */
  if (SolarMicroinverterModelDigita_X.Integrator_CSTATE >
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_UpperSat) {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT =
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_UpperSat;
  } else if (SolarMicroinverterModelDigita_X.Integrator_CSTATE <
             SolarMicroinverterModelDigita_P.CURRENTLIMIT_LowerSat) {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT =
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_LowerSat;
  } else {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT =
      SolarMicroinverterModelDigita_X.Integrator_CSTATE;
  }

  /* End of Saturate: '<S5>/CURRENT LIMIT' */

  /* Gain: '<S5>/Gain3' incorporates:
   *  Product: '<S5>/Product4'
   */
  SolarMicroinverterModelDigita_B.Gain3 = rtb_DataTypeConversion1 *
    SolarMicroinverterModelDigita_B.CURRENTLIMIT *
    SolarMicroinverterModelDigita_P.Gain3_Gain;

  /* TransportDelay: '<S12>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
    real_T simTime = SolarMicroinverterModelDigit_M->Timing.t[0];
    real_T tMinusDelay = simTime -
      SolarMicroinverterModelDigita_P.TransportDelay1_Delay;
    SolarMicroinverterModelDigita_B.TransportDelay1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.CircularBufSize,
      &SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Last,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head,
      SolarMicroinverterModelDigita_P.TransportDelay1_InitOutput,
      0,
      0);
  }

  /* RateTransition: '<S1>/Rate Transition4' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    if (SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID1_3) {
      SolarMicroinverterModelDigita_B.RateTransition4 =
        SolarMicroinverterModelDigit_DW.RateTransition4_Buffer0;
    }

    /* Saturate: '<S12>/Duty Limit3' */
    if (SolarMicroinverterModelDigita_B.RateTransition4 >
        SolarMicroinverterModelDigita_P.DutyLimit3_UpperSat) {
      rtb_Sum2_b = SolarMicroinverterModelDigita_P.DutyLimit3_UpperSat;
    } else if (SolarMicroinverterModelDigita_B.RateTransition4 <
               SolarMicroinverterModelDigita_P.DutyLimit3_LowerSat) {
      rtb_Sum2_b = SolarMicroinverterModelDigita_P.DutyLimit3_LowerSat;
    } else {
      rtb_Sum2_b = SolarMicroinverterModelDigita_B.RateTransition4;
    }

    /* Sum: '<S12>/Sum2' incorporates:
     *  Saturate: '<S12>/Duty Limit3'
     */
    rtb_Sum2_b += SolarMicroinverterModelDigita_B.RateTransition2;

    /* Saturate: '<S12>/Duty Limit1' */
    if (rtb_Sum2_b > SolarMicroinverterModelDigita_P.DutyLimit1_UpperSat) {
      SolarMicroinverterModelDigita_B.DutyLimit1 =
        SolarMicroinverterModelDigita_P.DutyLimit1_UpperSat;
    } else if (rtb_Sum2_b < SolarMicroinverterModelDigita_P.DutyLimit1_LowerSat)
    {
      SolarMicroinverterModelDigita_B.DutyLimit1 =
        SolarMicroinverterModelDigita_P.DutyLimit1_LowerSat;
    } else {
      SolarMicroinverterModelDigita_B.DutyLimit1 = rtb_Sum2_b;
    }

    /* End of Saturate: '<S12>/Duty Limit1' */
  }

  /* End of RateTransition: '<S1>/Rate Transition4' */

  /* RelationalOperator: '<S12>/Relational Operator1' */
  rtb_RelationalOperator1 = (SolarMicroinverterModelDigita_B.TransportDelay1 <=
    SolarMicroinverterModelDigita_B.DutyLimit1);

  /* DataTypeConversion: '<S12>/Data Type Conversion3' incorporates:
   *  Logic: '<S12>/Logical Operator1'
   */
  rtb_DataTypeConversion3 = !rtb_RelationalOperator1;

  /* Saturate: '<S6>/CURRENT LIMIT' incorporates:
   *  Integrator: '<S6>/Integrator'
   */
  if (SolarMicroinverterModelDigita_X.Integrator_CSTATE_m >
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_UpperSat_a) {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l =
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_UpperSat_a;
  } else if (SolarMicroinverterModelDigita_X.Integrator_CSTATE_m <
             SolarMicroinverterModelDigita_P.CURRENTLIMIT_LowerSat_a) {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l =
      SolarMicroinverterModelDigita_P.CURRENTLIMIT_LowerSat_a;
  } else {
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l =
      SolarMicroinverterModelDigita_X.Integrator_CSTATE_m;
  }

  /* End of Saturate: '<S6>/CURRENT LIMIT' */

  /* Gain: '<S6>/Gain3' incorporates:
   *  Product: '<S6>/Product4'
   */
  SolarMicroinverterModelDigita_B.Gain3_i = (real_T)rtb_DataTypeConversion3 *
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l *
    SolarMicroinverterModelDigita_P.Gain3_Gain_g;

  /* Saturate: '<S7>/ LIMIT' incorporates:
   *  Integrator: '<S7>/Integrator'
   */
  if (SolarMicroinverterModelDigita_X.Integrator_CSTATE_e >
      SolarMicroinverterModelDigita_P.LIMIT_UpperSat) {
    SolarMicroinverterModelDigita_B.LIMIT =
      SolarMicroinverterModelDigita_P.LIMIT_UpperSat;
  } else if (SolarMicroinverterModelDigita_X.Integrator_CSTATE_e <
             SolarMicroinverterModelDigita_P.LIMIT_LowerSat) {
    SolarMicroinverterModelDigita_B.LIMIT =
      SolarMicroinverterModelDigita_P.LIMIT_LowerSat;
  } else {
    SolarMicroinverterModelDigita_B.LIMIT =
      SolarMicroinverterModelDigita_X.Integrator_CSTATE_e;
  }

  /* End of Saturate: '<S7>/ LIMIT' */

  /* Sum: '<S2>/Sum2' */
  rtb_Sum2_b = (SolarMicroinverterModelDigita_B.Gain3 +
                SolarMicroinverterModelDigita_B.Gain3_i) -
    SolarMicroinverterModelDigita_B.LIMIT;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/ESR'
   *  Integrator: '<S2>/Integrator1'
   */
  SolarMicroinverterModelDigita_B.Sum1_i =
    SolarMicroinverterModelDigita_P.ESR_Gain * rtb_Sum2_b +
    SolarMicroinverterModelDigita_X.Integrator1_CSTATE;

  /* Integrator: '<S4>/Integrator3' */
  SolarMicroinverterModelDigita_B.Integrator3 =
    SolarMicroinverterModelDigita_X.Integrator3_CSTATE;

  /* DataTypeConversion: '<S12>/Data Type Conversion' */
  SolarMicroinverterModelDigita_B.DataTypeConversion = rtb_RelationalOperator;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S5>/Ron+Rp' */
    SolarMicroinverterModelDigita_B.RonRp =
      SolarMicroinverterModelDigita_P.RonRp_Value;
  }

  /* Product: '<S5>/Product1' */
  rtb_Product1 = SolarMicroinverterModelDigita_B.DataTypeConversion *
    SolarMicroinverterModelDigita_B.RonRp *
    SolarMicroinverterModelDigita_B.CURRENTLIMIT;

  /* Gain: '<S5>/1//(Ron+Rp)' */
  SolarMicroinverterModelDigita_B.RonRp_a =
    SolarMicroinverterModelDigita_P.RonRp_Gain * rtb_Product1;

  /* Sum: '<S4>/Sum2' */
  rtb_Product1_g = SolarMicroinverterModelDigita_B.Integrator3 -
    SolarMicroinverterModelDigita_B.RonRp_a;

  /* Sum: '<S4>/Sum3' incorporates:
   *  Gain: '<S4>/Resr'
   *  Integrator: '<S4>/Integrator1'
   */
  rtb_VOLTAGELIMIT = SolarMicroinverterModelDigita_P.Resr_Gain * rtb_Product1_g
    + SolarMicroinverterModelDigita_X.Integrator1_CSTATE_k;

  /* Saturate: '<S4>/VOLTAGE LIMIT' */
  if (rtb_VOLTAGELIMIT > SolarMicroinverterModelDigita_P.VOLTAGELIMIT_UpperSat)
  {
    rtb_VOLTAGELIMIT = SolarMicroinverterModelDigita_P.VOLTAGELIMIT_UpperSat;
  } else {
    if (rtb_VOLTAGELIMIT < SolarMicroinverterModelDigita_P.VOLTAGELIMIT_LowerSat)
    {
      rtb_VOLTAGELIMIT = SolarMicroinverterModelDigita_P.VOLTAGELIMIT_LowerSat;
    }
  }

  /* End of Saturate: '<S4>/VOLTAGE LIMIT' */

  /* Product: '<S10>/Divide' incorporates:
   *  Gain: '<S10>/TURNS'
   *  Sum: '<S10>/Sum4'
   */
  SolarMicroinverterModelDigita_B.Divide =
    SolarMicroinverterModelDigita_B.Sum1_i /
    (SolarMicroinverterModelDigita_P.TURNS_Gain * rtb_VOLTAGELIMIT +
     SolarMicroinverterModelDigita_B.Sum1_i);

  /* ZeroOrderHold: '<S1>/ZOH1' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M) &&
      SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_2) {
    SolarMicroinverterModelDigita_B.ZOH1 =
      SolarMicroinverterModelDigita_B.Divide;
  }

  /* End of ZeroOrderHold: '<S1>/ZOH1' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
  }

  /* TransferFcn: '<S11>/S//W Filter' */
  SolarMicroinverterModelDigita_B.SWFilter = 0.0;
  SolarMicroinverterModelDigita_B.SWFilter +=
    SolarMicroinverterModelDigita_P.SWFilter_C *
    SolarMicroinverterModelDigita_X.SWFilter_CSTATE;

  /* TransferFcn: '<S11>/S//W Filter1' */
  SolarMicroinverterModelDigita_B.SWFilter1 = 0.0;
  SolarMicroinverterModelDigita_B.SWFilter1 +=
    SolarMicroinverterModelDigita_P.SWFilter1_C *
    SolarMicroinverterModelDigita_X.SWFilter1_CSTATE;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S11>/CURRENT REF ERROR' */
    SolarMicroinverterModelDigita_B.CURRENTREFERROR =
      SolarMicroinverterModelDigita_P.CURRENTREFERROR_Value;
  }

  /* Sum: '<S11>/Sum4' incorporates:
   *  Sum: '<S11>/Sum3'
   */
  rtb_DataTypeConversion2 = SolarMicroinverterModelDigita_B.CURRENTREFERROR -
    (SolarMicroinverterModelDigita_B.SWFilter -
     SolarMicroinverterModelDigita_B.SWFilter1);

  /* RateTransition: '<S11>/Rate Transition1' */
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M) &&
      SolarMicroinverterModelDigit_M->Timing.RateInteraction.TID0_3) {
    SolarMicroinverterModelDigita_B.RateTransition1_f = rtb_DataTypeConversion2;
  }

  /* End of RateTransition: '<S11>/Rate Transition1' */

  /* TransferFcn: '<S11>/H//W Filter' */
  SolarMicroinverterModelDigita_B.HWFilter = 0.0;
  SolarMicroinverterModelDigita_B.HWFilter +=
    SolarMicroinverterModelDigita_P.HWFilter_C *
    SolarMicroinverterModelDigita_X.HWFilter_CSTATE;

  /* TransferFcn: '<S11>/H//W Filter1' */
  SolarMicroinverterModelDigita_B.HWFilter1 = 0.0;
  SolarMicroinverterModelDigita_B.HWFilter1 +=
    SolarMicroinverterModelDigita_P.HWFilter1_C *
    SolarMicroinverterModelDigita_X.HWFilter1_CSTATE;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
  }

  /* Clock: '<S14>/Clock' */
  rtb_DataTypeConversion2 = SolarMicroinverterModelDigit_M->Timing.t[0];
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S14>/Constant' */
    SolarMicroinverterModelDigita_B.Constant_l =
      SolarMicroinverterModelDigita_P.Constant_Value_f;
  }

  /* Sum: '<S14>/Sum' incorporates:
   *  S-Function (sfun_tstart): '<S14>/startTime'
   */
  rtb_DataTypeConversion2 -= (0.0);

  /* Math: '<S14>/Math Function' */
  rtb_DataTypeConversion2 = rt_remd_snf(rtb_DataTypeConversion2,
    SolarMicroinverterModelDigita_B.Constant_l);

  /* Lookup_n-D: '<S14>/Look-Up Table1' */
  SolarMicroinverterModelDigita_B.LookUpTable1_j = look1_binlxpw
    (rtb_DataTypeConversion2,
     SolarMicroinverterModelDigita_P.LookUpTable1_bp01Data_b,
     SolarMicroinverterModelDigita_P.CARRIER1_rep_seq_y, 1U);

  /* DataTypeConversion: '<S12>/Data Type Conversion2' */
  rtb_DataTypeConversion2 = rtb_RelationalOperator1;

  /* Gain: '<S2>/1//Co' */
  SolarMicroinverterModelDigita_B.Co = SolarMicroinverterModelDigita_P.Co_Gain *
    rtb_Sum2_b;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Gain: '<S15>/Gain2' incorporates:
     *  Constant: '<S15>/RMS GridVoltage'
     */
    SolarMicroinverterModelDigita_B.Gain2 =
      SolarMicroinverterModelDigita_P.Gain2_Gain *
      SolarMicroinverterModelDigita_P.RMSGridVoltage_Value;
  }

  /* Product: '<S15>/Product' */
  SolarMicroinverterModelDigita_B.Product = rtb_Abs *
    SolarMicroinverterModelDigita_B.Gain2;

  /* Gain: '<S4>/1//Cin' */
  SolarMicroinverterModelDigita_B.Cin = SolarMicroinverterModelDigita_P.Cin_Gain
    * rtb_Product1_g;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S9>/Vmpp' */
    SolarMicroinverterModelDigita_B.Vmpp =
      SolarMicroinverterModelDigita_P.Vmpp_Value;
  }

  /* TransportDelay: '<S4>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[1];
    real_T simTime = SolarMicroinverterModelDigit_M->Timing.t[0];
    real_T tMinusDelay = simTime -
      SolarMicroinverterModelDigita_P.TransportDelay1_Delay_l;
    rtb_Product1_g = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.CircularBufSize,
      &SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Last,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail,
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head,
      SolarMicroinverterModelDigita_P.TransportDelay1_InitOutput_l,
      0,
      0);
  }

  /* Gain: '<S4>/1//Lin' incorporates:
   *  Gain: '<S4>/Rin'
   *  Sum: '<S4>/Sum1'
   */
  SolarMicroinverterModelDigita_B.Lin = ((SolarMicroinverterModelDigita_B.Vmpp -
    rtb_VOLTAGELIMIT) - SolarMicroinverterModelDigita_P.Rin_Gain *
    rtb_Product1_g) * SolarMicroinverterModelDigita_P.Lin_Gain;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S5>/Diode Drop' */
    SolarMicroinverterModelDigita_B.DiodeDrop =
      SolarMicroinverterModelDigita_P.DiodeDrop_Value;
  }

  /* Gain: '<S5>/1//L' incorporates:
   *  Gain: '<S5>/1//N'
   *  Gain: '<S5>/Rs'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product2'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  SolarMicroinverterModelDigita_B.L = ((rtb_VOLTAGELIMIT *
    SolarMicroinverterModelDigita_B.DataTypeConversion - rtb_Product1) -
    ((SolarMicroinverterModelDigita_P.Rs_Gain *
      SolarMicroinverterModelDigita_B.CURRENTLIMIT +
      SolarMicroinverterModelDigita_B.Sum1_i) +
     SolarMicroinverterModelDigita_B.DiodeDrop) * rtb_DataTypeConversion1 *
    SolarMicroinverterModelDigita_P.N_Gain) *
    SolarMicroinverterModelDigita_P.L_Gain;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S6>/Ron+Rp' */
    SolarMicroinverterModelDigita_B.RonRp_g =
      SolarMicroinverterModelDigita_P.RonRp_Value_n;
  }

  /* Product: '<S6>/Product1' */
  rtb_Product1_g = rtb_DataTypeConversion2 *
    SolarMicroinverterModelDigita_B.RonRp_g *
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l;

  /* Gain: '<S6>/1//(Ron+Rp)' */
  SolarMicroinverterModelDigita_B.RonRp_k =
    SolarMicroinverterModelDigita_P.RonRp_Gain_d * rtb_Product1_g;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    /* Constant: '<S6>/Diode Drop' */
    SolarMicroinverterModelDigita_B.DiodeDrop_o =
      SolarMicroinverterModelDigita_P.DiodeDrop_Value_g;
  }

  /* Gain: '<S6>/1//L' incorporates:
   *  Gain: '<S6>/1//N'
   *  Gain: '<S6>/Rs'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product2'
   *  Sum: '<S6>/Sum'
   *  Sum: '<S6>/Sum1'
   */
  SolarMicroinverterModelDigita_B.L_e = ((rtb_VOLTAGELIMIT *
    rtb_DataTypeConversion2 - rtb_Product1_g) -
    ((SolarMicroinverterModelDigita_P.Rs_Gain_c *
      SolarMicroinverterModelDigita_B.CURRENTLIMIT_l +
      SolarMicroinverterModelDigita_B.Sum1_i) +
     SolarMicroinverterModelDigita_B.DiodeDrop_o) * (real_T)
    rtb_DataTypeConversion3 * SolarMicroinverterModelDigita_P.N_Gain_p) *
    SolarMicroinverterModelDigita_P.L_Gain_h;

  /* Gain: '<S7>/1//Lf' incorporates:
   *  Gain: '<S7>/Rf'
   *  Sum: '<S7>/Sum'
   */
  SolarMicroinverterModelDigita_B.Lf = ((SolarMicroinverterModelDigita_B.Sum1_i
    - SolarMicroinverterModelDigita_B.Product) -
    SolarMicroinverterModelDigita_P.Rf_Gain *
    SolarMicroinverterModelDigita_B.LIMIT) *
    SolarMicroinverterModelDigita_P.Lf_Gain;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
  }

  /* Gain: '<S8>/ScaleDown' */
  SolarMicroinverterModelDigita_B.ScaleDown =
    SolarMicroinverterModelDigita_P.ScaleDown_Gain *
    SolarMicroinverterModelDigita_B.Product;
  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
  }
}

/* Model update function for TID0 */
void SolarMicroinverterModelDigitalControl_230V_update0(void) /* Sample time: [0.0s, 0.0s] */
{
  /* Update for TransportDelay: '<S12>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[1];
    real_T simTime = SolarMicroinverterModelDigit_M->Timing.t[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head =
      ((SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head <
        (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.CircularBufSize-1))
       ? (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head+1) : 0);
    if (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head ==
        SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail) {
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail =
        ((SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail <
          (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.CircularBufSize
           -1)) ? (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail+1)
         : 0);
    }

    (*tBuffer)[SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head] =
      simTime;
    (*uBuffer)[SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head] =
      SolarMicroinverterModelDigita_B.LookUpTable1_j;
  }

  /* Update for TransportDelay: '<S4>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[1];
    real_T simTime = SolarMicroinverterModelDigit_M->Timing.t[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head =
      ((SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head <
        (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.CircularBufSize
         -1)) ? (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head+1)
       : 0);
    if (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head ==
        SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail) {
      SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail =
        ((SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail <
          (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.CircularBufSize
           -1)) ? (SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail+
                   1) : 0);
    }

    (*tBuffer)[SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head] =
      simTime;
    (*uBuffer)[SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head] =
      SolarMicroinverterModelDigita_B.Integrator3;
  }

  if (rtmIsMajorTimeStep(SolarMicroinverterModelDigit_M)) {
    rt_ertODEUpdateContinuousStates(&SolarMicroinverterModelDigit_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++SolarMicroinverterModelDigit_M->Timing.clockTick0)) {
    ++SolarMicroinverterModelDigit_M->Timing.clockTickH0;
  }

  SolarMicroinverterModelDigit_M->Timing.t[0] = rtsiGetSolverStopTime
    (&SolarMicroinverterModelDigit_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++SolarMicroinverterModelDigit_M->Timing.clockTick1)) {
    ++SolarMicroinverterModelDigit_M->Timing.clockTickH1;
  }

  SolarMicroinverterModelDigit_M->Timing.t[1] =
    SolarMicroinverterModelDigit_M->Timing.clockTick1 *
    SolarMicroinverterModelDigit_M->Timing.stepSize1 +
    SolarMicroinverterModelDigit_M->Timing.clockTickH1 *
    SolarMicroinverterModelDigit_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void SolarMicroinverterModelDigitalControl_230V_derivatives(void)
{
  XDot_SolarMicroinverterModelD_T *_rtXdot;
  _rtXdot = ((XDot_SolarMicroinverterModelD_T *)
             SolarMicroinverterModelDigit_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S1>/Filter1' */
  _rtXdot->Filter1_CSTATE = 0.0;
  _rtXdot->Filter1_CSTATE += SolarMicroinverterModelDigita_P.Filter1_A *
    SolarMicroinverterModelDigita_X.Filter1_CSTATE;
  _rtXdot->Filter1_CSTATE += SolarMicroinverterModelDigita_B.LIMIT;

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = SolarMicroinverterModelDigita_B.Co;

  /* Derivatives for Integrator: '<S5>/Integrator' */
  _rtXdot->Integrator_CSTATE = SolarMicroinverterModelDigita_B.L;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE_m = SolarMicroinverterModelDigita_B.L_e;

  /* Derivatives for Integrator: '<S7>/Integrator' */
  _rtXdot->Integrator_CSTATE_e = SolarMicroinverterModelDigita_B.Lf;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_k = SolarMicroinverterModelDigita_B.Cin;

  /* Derivatives for Integrator: '<S4>/Integrator3' */
  _rtXdot->Integrator3_CSTATE = SolarMicroinverterModelDigita_B.Lin;

  /* Derivatives for TransferFcn: '<S11>/S//W Filter' */
  _rtXdot->SWFilter_CSTATE = 0.0;
  _rtXdot->SWFilter_CSTATE += SolarMicroinverterModelDigita_P.SWFilter_A *
    SolarMicroinverterModelDigita_X.SWFilter_CSTATE;
  _rtXdot->SWFilter_CSTATE += SolarMicroinverterModelDigita_B.HWFilter;

  /* Derivatives for TransferFcn: '<S11>/S//W Filter1' */
  _rtXdot->SWFilter1_CSTATE = 0.0;
  _rtXdot->SWFilter1_CSTATE += SolarMicroinverterModelDigita_P.SWFilter1_A *
    SolarMicroinverterModelDigita_X.SWFilter1_CSTATE;
  _rtXdot->SWFilter1_CSTATE += SolarMicroinverterModelDigita_B.HWFilter1;

  /* Derivatives for TransferFcn: '<S11>/H//W Filter' */
  _rtXdot->HWFilter_CSTATE = 0.0;
  _rtXdot->HWFilter_CSTATE += SolarMicroinverterModelDigita_P.HWFilter_A *
    SolarMicroinverterModelDigita_X.HWFilter_CSTATE;
  _rtXdot->HWFilter_CSTATE += SolarMicroinverterModelDigita_B.RonRp_a;

  /* Derivatives for TransferFcn: '<S11>/H//W Filter1' */
  _rtXdot->HWFilter1_CSTATE = 0.0;
  _rtXdot->HWFilter1_CSTATE += SolarMicroinverterModelDigita_P.HWFilter1_A *
    SolarMicroinverterModelDigita_X.HWFilter1_CSTATE;
  _rtXdot->HWFilter1_CSTATE += SolarMicroinverterModelDigita_B.RonRp_k;
}

/* Model output function for TID2 */
void SolarMicroinverterModelDigitalControl_230V_output2(void) /* Sample time: [1.7E-5s, 0.0s] */
{
  /* DiscreteTransferFcn: '<S1>/PI Controller' incorporates:
   *  Gain: '<S1>/PerUnitizingGain'
   */
  SolarMicroinverterModelDigit_DW.PIController_tmp =
    (SolarMicroinverterModelDigita_P.PerUnitizingGain_Gain *
     SolarMicroinverterModelDigita_B.RateTransition1 -
     SolarMicroinverterModelDigita_P.PIController_DenCoef[1] *
     SolarMicroinverterModelDigit_DW.PIController_states) /
    SolarMicroinverterModelDigita_P.PIController_DenCoef[0];

  /* Sum: '<S1>/Sum2' incorporates:
   *  DiscreteTransferFcn: '<S1>/PI Controller'
   */
  SolarMicroinverterModelDigita_B.Sum2 =
    (SolarMicroinverterModelDigita_P.PIController_NumCoef[0] *
     SolarMicroinverterModelDigit_DW.PIController_tmp +
     SolarMicroinverterModelDigita_P.PIController_NumCoef[1] *
     SolarMicroinverterModelDigit_DW.PIController_states) +
    SolarMicroinverterModelDigita_B.ZOH1;
}

/* Model update function for TID2 */
void SolarMicroinverterModelDigitalControl_230V_update2(void) /* Sample time: [1.7E-5s, 0.0s] */
{
  /* Update for DiscreteTransferFcn: '<S1>/PI Controller' */
  SolarMicroinverterModelDigit_DW.PIController_states =
    SolarMicroinverterModelDigit_DW.PIController_tmp;

  /* Update for RateTransition: '<S1>/Rate Transition2' */
  SolarMicroinverterModelDigit_DW.RateTransition2_Buffer0 =
    SolarMicroinverterModelDigita_B.Sum2;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++SolarMicroinverterModelDigit_M->Timing.clockTick2)) {
    ++SolarMicroinverterModelDigit_M->Timing.clockTickH2;
  }

  SolarMicroinverterModelDigit_M->Timing.t[2] =
    SolarMicroinverterModelDigit_M->Timing.clockTick2 *
    SolarMicroinverterModelDigit_M->Timing.stepSize2 +
    SolarMicroinverterModelDigit_M->Timing.clockTickH2 *
    SolarMicroinverterModelDigit_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output function for TID3 */
void SolarMicroinverterModelDigitalControl_230V_output3(void) /* Sample time: [0.0002s, 0.0s] */
{
  /* DiscreteTransferFcn: '<S11>/PI Controller' incorporates:
   *  Gain: '<S11>/Per Unitizing Gain + Base Conversion'
   */
  SolarMicroinverterModelDigit_DW.PIController_tmp_i =
    (SolarMicroinverterModelDigita_P.PerUnitizingGainBaseConversion_ *
     SolarMicroinverterModelDigita_B.RateTransition1_f -
     SolarMicroinverterModelDigita_P.PIController_DenCoef_f[1] *
     SolarMicroinverterModelDigit_DW.PIController_states_l) /
    SolarMicroinverterModelDigita_P.PIController_DenCoef_f[0];

  /* Gain: '<S11>/deltaD//2' incorporates:
   *  DiscreteTransferFcn: '<S11>/PI Controller'
   */
  SolarMicroinverterModelDigita_B.deltaD2 =
    (SolarMicroinverterModelDigita_P.PIController_NumCoef_m[0] *
     SolarMicroinverterModelDigit_DW.PIController_tmp_i +
     SolarMicroinverterModelDigita_P.PIController_NumCoef_m[1] *
     SolarMicroinverterModelDigit_DW.PIController_states_l) *
    SolarMicroinverterModelDigita_P.deltaD2_Gain;

  /* Gain: '<S11>/Invert' */
  SolarMicroinverterModelDigita_B.Invert =
    SolarMicroinverterModelDigita_P.Invert_Gain *
    SolarMicroinverterModelDigita_B.deltaD2;
}

/* Model update function for TID3 */
void SolarMicroinverterModelDigitalControl_230V_update3(void) /* Sample time: [0.0002s, 0.0s] */
{
  /* Update for RateTransition: '<S1>/Rate Transition3' */
  SolarMicroinverterModelDigit_DW.RateTransition3_Buffer0 =
    SolarMicroinverterModelDigita_B.deltaD2;

  /* Update for RateTransition: '<S1>/Rate Transition4' */
  SolarMicroinverterModelDigit_DW.RateTransition4_Buffer0 =
    SolarMicroinverterModelDigita_B.Invert;

  /* Update for DiscreteTransferFcn: '<S11>/PI Controller' */
  SolarMicroinverterModelDigit_DW.PIController_states_l =
    SolarMicroinverterModelDigit_DW.PIController_tmp_i;

  /* Update absolute time */
  /* The "clockTick3" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick3"
   * and "Timing.stepSize3". Size of "clockTick3" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick3 and the high bits
   * Timing.clockTickH3. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++SolarMicroinverterModelDigit_M->Timing.clockTick3)) {
    ++SolarMicroinverterModelDigit_M->Timing.clockTickH3;
  }

  SolarMicroinverterModelDigit_M->Timing.t[3] =
    SolarMicroinverterModelDigit_M->Timing.clockTick3 *
    SolarMicroinverterModelDigit_M->Timing.stepSize3 +
    SolarMicroinverterModelDigit_M->Timing.clockTickH3 *
    SolarMicroinverterModelDigit_M->Timing.stepSize3 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void SolarMicroinverterModelDigitalControl_230V_output(int_T tid)
{
  switch (tid) {
   case 0 :
    SolarMicroinverterModelDigitalControl_230V_output0();
    break;

   case 2 :
    SolarMicroinverterModelDigitalControl_230V_output2();
    break;

   case 3 :
    SolarMicroinverterModelDigitalControl_230V_output3();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void SolarMicroinverterModelDigitalControl_230V_update(int_T tid)
{
  switch (tid) {
   case 0 :
    SolarMicroinverterModelDigitalControl_230V_update0();
    break;

   case 2 :
    SolarMicroinverterModelDigitalControl_230V_update2();
    break;

   case 3 :
    SolarMicroinverterModelDigitalControl_230V_update3();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void SolarMicroinverterModelDigitalControl_230V_initialize(void)
{
  /* Start for RateTransition: '<S1>/Rate Transition3' */
  SolarMicroinverterModelDigita_B.RateTransition3 =
    SolarMicroinverterModelDigita_P.RateTransition3_X0;

  /* Start for RateTransition: '<S1>/Rate Transition2' */
  SolarMicroinverterModelDigita_B.RateTransition2 =
    SolarMicroinverterModelDigita_P.RateTransition2_X0;

  /* Start for TransportDelay: '<S12>/Transport Delay1' */
  {
    real_T *pBuffer =
      &SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK.TUbufferArea[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Tail = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Head = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.Last = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = SolarMicroinverterModelDigita_P.TransportDelay1_InitOutput;
    pBuffer[1024] = SolarMicroinverterModelDigit_M->Timing.t[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[0] =
      (void *) &pBuffer[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK.TUbufferPtrs[1] =
      (void *) &pBuffer[1024];
  }

  /* Start for RateTransition: '<S1>/Rate Transition4' */
  SolarMicroinverterModelDigita_B.RateTransition4 =
    SolarMicroinverterModelDigita_P.RateTransition4_X0;

  /* Start for TransportDelay: '<S4>/Transport Delay1' */
  {
    real_T *pBuffer =
      &SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK_e.TUbufferArea[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Tail = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Head = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.Last = 0;
    SolarMicroinverterModelDigit_DW.TransportDelay1_IWORK_o.CircularBufSize =
      1024;
    pBuffer[0] = SolarMicroinverterModelDigita_P.TransportDelay1_InitOutput_l;
    pBuffer[1024] = SolarMicroinverterModelDigit_M->Timing.t[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[0] =
      (void *) &pBuffer[0];
    SolarMicroinverterModelDigit_DW.TransportDelay1_PWORK_g.TUbufferPtrs[1] =
      (void *) &pBuffer[1024];
  }

  /* InitializeConditions for TransferFcn: '<S1>/Filter1' */
  SolarMicroinverterModelDigita_X.Filter1_CSTATE = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S1>/PI Controller' */
  SolarMicroinverterModelDigit_DW.PIController_states =
    SolarMicroinverterModelDigita_P.PIController_InitialStates;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  SolarMicroinverterModelDigita_X.Integrator1_CSTATE =
    SolarMicroinverterModelDigita_P.Integrator1_IC;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition3' */
  SolarMicroinverterModelDigit_DW.RateTransition3_Buffer0 =
    SolarMicroinverterModelDigita_P.RateTransition3_X0;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition2' */
  SolarMicroinverterModelDigit_DW.RateTransition2_Buffer0 =
    SolarMicroinverterModelDigita_P.RateTransition2_X0;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  SolarMicroinverterModelDigita_X.Integrator_CSTATE =
    SolarMicroinverterModelDigita_P.Integrator_IC;

  /* InitializeConditions for RateTransition: '<S1>/Rate Transition4' */
  SolarMicroinverterModelDigit_DW.RateTransition4_Buffer0 =
    SolarMicroinverterModelDigita_P.RateTransition4_X0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  SolarMicroinverterModelDigita_X.Integrator_CSTATE_m =
    SolarMicroinverterModelDigita_P.Integrator_IC_p;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  SolarMicroinverterModelDigita_X.Integrator_CSTATE_e =
    SolarMicroinverterModelDigita_P.Integrator_IC_b;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' */
  SolarMicroinverterModelDigita_X.Integrator1_CSTATE_k =
    SolarMicroinverterModelDigita_P.Integrator1_IC_h;

  /* InitializeConditions for Integrator: '<S4>/Integrator3' */
  SolarMicroinverterModelDigita_X.Integrator3_CSTATE =
    SolarMicroinverterModelDigita_P.Integrator3_IC;

  /* InitializeConditions for TransferFcn: '<S11>/S//W Filter' */
  SolarMicroinverterModelDigita_X.SWFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S11>/S//W Filter1' */
  SolarMicroinverterModelDigita_X.SWFilter1_CSTATE = 0.0;

  /* InitializeConditions for DiscreteTransferFcn: '<S11>/PI Controller' */
  SolarMicroinverterModelDigit_DW.PIController_states_l =
    SolarMicroinverterModelDigita_P.PIController_InitialStates_p;

  /* InitializeConditions for TransferFcn: '<S11>/H//W Filter' */
  SolarMicroinverterModelDigita_X.HWFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S11>/H//W Filter1' */
  SolarMicroinverterModelDigita_X.HWFilter1_CSTATE = 0.0;
}

/* Model terminate function */
void SolarMicroinverterModelDigitalControl_230V_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  SolarMicroinverterModelDigitalControl_230V_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  SolarMicroinverterModelDigitalControl_230V_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  SolarMicroinverterModelDigitalControl_230V_initialize();
}

void MdlTerminate(void)
{
  SolarMicroinverterModelDigitalControl_230V_terminate();
}

/* Registration function */
RT_MODEL_SolarMicroinverterMo_T *SolarMicroinverterModelDigitalControl_230V(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)SolarMicroinverterModelDigit_M, 0,
                sizeof(RT_MODEL_SolarMicroinverterMo_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&SolarMicroinverterModelDigit_M->solverInfo,
                          &SolarMicroinverterModelDigit_M->Timing.simTimeStep);
    rtsiSetTPtr(&SolarMicroinverterModelDigit_M->solverInfo, &rtmGetTPtr
                (SolarMicroinverterModelDigit_M));
    rtsiSetStepSizePtr(&SolarMicroinverterModelDigit_M->solverInfo,
                       &SolarMicroinverterModelDigit_M->Timing.stepSize0);
    rtsiSetdXPtr(&SolarMicroinverterModelDigit_M->solverInfo,
                 &SolarMicroinverterModelDigit_M->ModelData.derivs);
    rtsiSetContStatesPtr(&SolarMicroinverterModelDigit_M->solverInfo, (real_T **)
                         &SolarMicroinverterModelDigit_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&SolarMicroinverterModelDigit_M->solverInfo,
      &SolarMicroinverterModelDigit_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&SolarMicroinverterModelDigit_M->solverInfo,
                          (&rtmGetErrorStatus(SolarMicroinverterModelDigit_M)));
    rtsiSetRTModelPtr(&SolarMicroinverterModelDigit_M->solverInfo,
                      SolarMicroinverterModelDigit_M);
  }

  rtsiSetSimTimeStep(&SolarMicroinverterModelDigit_M->solverInfo,
                     MAJOR_TIME_STEP);
  SolarMicroinverterModelDigit_M->ModelData.intgData.y =
    SolarMicroinverterModelDigit_M->ModelData.odeY;
  SolarMicroinverterModelDigit_M->ModelData.intgData.f[0] =
    SolarMicroinverterModelDigit_M->ModelData.odeF[0];
  SolarMicroinverterModelDigit_M->ModelData.intgData.f[1] =
    SolarMicroinverterModelDigit_M->ModelData.odeF[1];
  SolarMicroinverterModelDigit_M->ModelData.intgData.f[2] =
    SolarMicroinverterModelDigit_M->ModelData.odeF[2];
  SolarMicroinverterModelDigit_M->ModelData.intgData.f[3] =
    SolarMicroinverterModelDigit_M->ModelData.odeF[3];
  SolarMicroinverterModelDigit_M->ModelData.contStates = ((real_T *)
    &SolarMicroinverterModelDigita_X);
  rtsiSetSolverData(&SolarMicroinverterModelDigit_M->solverInfo, (void *)
                    &SolarMicroinverterModelDigit_M->ModelData.intgData);
  rtsiSetSolverName(&SolarMicroinverterModelDigit_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      SolarMicroinverterModelDigit_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    mdlTsMap[3] = 3;
    SolarMicroinverterModelDigit_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    SolarMicroinverterModelDigit_M->Timing.sampleTimes =
      (&SolarMicroinverterModelDigit_M->Timing.sampleTimesArray[0]);
    SolarMicroinverterModelDigit_M->Timing.offsetTimes =
      (&SolarMicroinverterModelDigit_M->Timing.offsetTimesArray[0]);

    /* task periods */
    SolarMicroinverterModelDigit_M->Timing.sampleTimes[0] = (0.0);
    SolarMicroinverterModelDigit_M->Timing.sampleTimes[1] = (1.0E-7);
    SolarMicroinverterModelDigit_M->Timing.sampleTimes[2] = (1.7E-5);
    SolarMicroinverterModelDigit_M->Timing.sampleTimes[3] = (0.0002);

    /* task offsets */
    SolarMicroinverterModelDigit_M->Timing.offsetTimes[0] = (0.0);
    SolarMicroinverterModelDigit_M->Timing.offsetTimes[1] = (0.0);
    SolarMicroinverterModelDigit_M->Timing.offsetTimes[2] = (0.0);
    SolarMicroinverterModelDigit_M->Timing.offsetTimes[3] = (0.0);
  }

  rtmSetTPtr(SolarMicroinverterModelDigit_M,
             &SolarMicroinverterModelDigit_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = SolarMicroinverterModelDigit_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      SolarMicroinverterModelDigit_M->Timing.perTaskSampleHitsArray;
    SolarMicroinverterModelDigit_M->Timing.perTaskSampleHits =
      (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    SolarMicroinverterModelDigit_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(SolarMicroinverterModelDigit_M, 0.041999999999999996);
  SolarMicroinverterModelDigit_M->Timing.stepSize0 = 1.0E-7;
  SolarMicroinverterModelDigit_M->Timing.stepSize1 = 1.0E-7;
  SolarMicroinverterModelDigit_M->Timing.stepSize2 = 1.7E-5;
  SolarMicroinverterModelDigit_M->Timing.stepSize3 = 0.0002;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    SolarMicroinverterModelDigit_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(SolarMicroinverterModelDigit_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(SolarMicroinverterModelDigit_M->rtwLogInfo, (NULL));
    rtliSetLogT(SolarMicroinverterModelDigit_M->rtwLogInfo, "tout");
    rtliSetLogX(SolarMicroinverterModelDigit_M->rtwLogInfo, "");
    rtliSetLogXFinal(SolarMicroinverterModelDigit_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(SolarMicroinverterModelDigit_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(SolarMicroinverterModelDigit_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(SolarMicroinverterModelDigit_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(SolarMicroinverterModelDigit_M->rtwLogInfo, 1);
    rtliSetLogY(SolarMicroinverterModelDigit_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(SolarMicroinverterModelDigit_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(SolarMicroinverterModelDigit_M->rtwLogInfo, (NULL));
  }

  SolarMicroinverterModelDigit_M->solverInfoPtr =
    (&SolarMicroinverterModelDigit_M->solverInfo);
  SolarMicroinverterModelDigit_M->Timing.stepSize = (1.0E-7);
  rtsiSetFixedStepSize(&SolarMicroinverterModelDigit_M->solverInfo, 1.0E-7);
  rtsiSetSolverMode(&SolarMicroinverterModelDigit_M->solverInfo,
                    SOLVER_MODE_MULTITASKING);

  /* block I/O */
  SolarMicroinverterModelDigit_M->ModelData.blockIO = ((void *)
    &SolarMicroinverterModelDigita_B);

  {
    SolarMicroinverterModelDigita_B.UNITSINE = 0.0;
    SolarMicroinverterModelDigita_B.Gain1 = 0.0;
    SolarMicroinverterModelDigita_B.Product1 = 0.0;
    SolarMicroinverterModelDigita_B.Filter1 = 0.0;
    SolarMicroinverterModelDigita_B.Sum1 = 0.0;
    SolarMicroinverterModelDigita_B.RateTransition1 = 0.0;
    SolarMicroinverterModelDigita_B.Constant = 0.0;
    SolarMicroinverterModelDigita_B.LookUpTable1 = 0.0;
    SolarMicroinverterModelDigita_B.RateTransition3 = 0.0;
    SolarMicroinverterModelDigita_B.RateTransition2 = 0.0;
    SolarMicroinverterModelDigita_B.DutyLimit = 0.0;
    SolarMicroinverterModelDigita_B.CURRENTLIMIT = 0.0;
    SolarMicroinverterModelDigita_B.Gain3 = 0.0;
    SolarMicroinverterModelDigita_B.TransportDelay1 = 0.0;
    SolarMicroinverterModelDigita_B.RateTransition4 = 0.0;
    SolarMicroinverterModelDigita_B.DutyLimit1 = 0.0;
    SolarMicroinverterModelDigita_B.CURRENTLIMIT_l = 0.0;
    SolarMicroinverterModelDigita_B.Gain3_i = 0.0;
    SolarMicroinverterModelDigita_B.LIMIT = 0.0;
    SolarMicroinverterModelDigita_B.Sum1_i = 0.0;
    SolarMicroinverterModelDigita_B.Integrator3 = 0.0;
    SolarMicroinverterModelDigita_B.DataTypeConversion = 0.0;
    SolarMicroinverterModelDigita_B.RonRp = 0.0;
    SolarMicroinverterModelDigita_B.RonRp_a = 0.0;
    SolarMicroinverterModelDigita_B.Divide = 0.0;
    SolarMicroinverterModelDigita_B.ZOH1 = 0.0;
    SolarMicroinverterModelDigita_B.Sum2 = 0.0;
    SolarMicroinverterModelDigita_B.SWFilter = 0.0;
    SolarMicroinverterModelDigita_B.SWFilter1 = 0.0;
    SolarMicroinverterModelDigita_B.CURRENTREFERROR = 0.0;
    SolarMicroinverterModelDigita_B.RateTransition1_f = 0.0;
    SolarMicroinverterModelDigita_B.deltaD2 = 0.0;
    SolarMicroinverterModelDigita_B.HWFilter = 0.0;
    SolarMicroinverterModelDigita_B.HWFilter1 = 0.0;
    SolarMicroinverterModelDigita_B.Invert = 0.0;
    SolarMicroinverterModelDigita_B.Constant_l = 0.0;
    SolarMicroinverterModelDigita_B.LookUpTable1_j = 0.0;
    SolarMicroinverterModelDigita_B.Co = 0.0;
    SolarMicroinverterModelDigita_B.Gain2 = 0.0;
    SolarMicroinverterModelDigita_B.Product = 0.0;
    SolarMicroinverterModelDigita_B.Cin = 0.0;
    SolarMicroinverterModelDigita_B.Vmpp = 0.0;
    SolarMicroinverterModelDigita_B.Lin = 0.0;
    SolarMicroinverterModelDigita_B.DiodeDrop = 0.0;
    SolarMicroinverterModelDigita_B.L = 0.0;
    SolarMicroinverterModelDigita_B.RonRp_g = 0.0;
    SolarMicroinverterModelDigita_B.RonRp_k = 0.0;
    SolarMicroinverterModelDigita_B.DiodeDrop_o = 0.0;
    SolarMicroinverterModelDigita_B.L_e = 0.0;
    SolarMicroinverterModelDigita_B.Lf = 0.0;
    SolarMicroinverterModelDigita_B.ScaleDown = 0.0;
  }

  /* parameters */
  SolarMicroinverterModelDigit_M->ModelData.defaultParam = ((real_T *)
    &SolarMicroinverterModelDigita_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &SolarMicroinverterModelDigita_X;
    SolarMicroinverterModelDigit_M->ModelData.contStates = (x);
    (void) memset((void *)&SolarMicroinverterModelDigita_X, 0,
                  sizeof(X_SolarMicroinverterModelDigi_T));
  }

  /* states (dwork) */
  SolarMicroinverterModelDigit_M->ModelData.dwork = ((void *)
    &SolarMicroinverterModelDigit_DW);
  (void) memset((void *)&SolarMicroinverterModelDigit_DW, 0,
                sizeof(DW_SolarMicroinverterModelDig_T));
  SolarMicroinverterModelDigit_DW.PIController_states = 0.0;
  SolarMicroinverterModelDigit_DW.PIController_states_l = 0.0;
  SolarMicroinverterModelDigit_DW.PIController_tmp = 0.0;
  SolarMicroinverterModelDigit_DW.RateTransition3_Buffer0 = 0.0;
  SolarMicroinverterModelDigit_DW.RateTransition2_Buffer0 = 0.0;
  SolarMicroinverterModelDigit_DW.RateTransition4_Buffer0 = 0.0;
  SolarMicroinverterModelDigit_DW.PIController_tmp_i = 0.0;
  SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK.modelTStart = 0.0;

  {
    int_T i;
    for (i = 0; i < 2048; i++) {
      SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK.TUbufferArea[i] =
        0.0;
    }
  }

  SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK_e.modelTStart = 0.0;

  {
    int_T i;
    for (i = 0; i < 2048; i++) {
      SolarMicroinverterModelDigit_DW.TransportDelay1_RWORK_e.TUbufferArea[i] =
        0.0;
    }
  }

  /* Initialize Sizes */
  SolarMicroinverterModelDigit_M->Sizes.numContStates = (11);/* Number of continuous states */
  SolarMicroinverterModelDigit_M->Sizes.numY = (0);/* Number of model outputs */
  SolarMicroinverterModelDigit_M->Sizes.numU = (0);/* Number of model inputs */
  SolarMicroinverterModelDigit_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  SolarMicroinverterModelDigit_M->Sizes.numSampTimes = (4);/* Number of sample times */
  SolarMicroinverterModelDigit_M->Sizes.numBlocks = (132);/* Number of blocks */
  SolarMicroinverterModelDigit_M->Sizes.numBlockIO = (53);/* Number of block outputs */
  SolarMicroinverterModelDigit_M->Sizes.numBlockPrms = (97);/* Sum of parameter "widths" */
  return SolarMicroinverterModelDigit_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
