/*
 * SolarMicroinverterModelDigitalControl_230V.h
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
#ifndef RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_h_
#define RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef SolarMicroinverterModelDigitalControl_230V_COMMON_INCLUDES_
# define SolarMicroinverterModelDigitalControl_230V_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* SolarMicroinverterModelDigitalControl_230V_COMMON_INCLUDES_ */

#include "SolarMicroinverterModelDigitalControl_230V_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ((rtm)->Timing.RateInteraction)
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ((rtm)->Timing.RateInteraction = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->ModelData.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->ModelData.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ((rtm)->Timing.TaskCounters)
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ((rtm)->Timing.TaskCounters = (val))
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->ModelData.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->ModelData.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) ((tid) <= 1)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) (((rtm)->Timing.sampleTimeTaskIDPtr[sti] == (tid)))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define SolarMicroinverterModelDigitalControl_230V_rtModel RT_MODEL_SolarMicroinverterMo_T

/* Block signals (auto storage) */
typedef struct {
  real_T UNITSINE;                     /* '<S3>/UNIT SINE' */
  real_T Gain1;                        /* '<S15>/Gain1' */
  real_T Product1;                     /* '<S15>/Product1' */
  real_T Filter1;                      /* '<S1>/Filter1' */
  real_T Sum1;                         /* '<S1>/Sum1' */
  real_T RateTransition1;              /* '<S1>/Rate Transition1' */
  real_T Constant;                     /* '<S13>/Constant' */
  real_T LookUpTable1;                 /* '<S13>/Look-Up Table1' */
  real_T RateTransition3;              /* '<S1>/Rate Transition3' */
  real_T RateTransition2;              /* '<S1>/Rate Transition2' */
  real_T DutyLimit;                    /* '<S12>/Duty Limit' */
  real_T CURRENTLIMIT;                 /* '<S5>/CURRENT LIMIT' */
  real_T Gain3;                        /* '<S5>/Gain3' */
  real_T TransportDelay1;              /* '<S12>/Transport Delay1' */
  real_T RateTransition4;              /* '<S1>/Rate Transition4' */
  real_T DutyLimit1;                   /* '<S12>/Duty Limit1' */
  real_T CURRENTLIMIT_l;               /* '<S6>/CURRENT LIMIT' */
  real_T Gain3_i;                      /* '<S6>/Gain3' */
  real_T LIMIT;                        /* '<S7>/ LIMIT' */
  real_T Sum1_i;                       /* '<S2>/Sum1' */
  real_T Integrator3;                  /* '<S4>/Integrator3' */
  real_T DataTypeConversion;           /* '<S12>/Data Type Conversion' */
  real_T RonRp;                        /* '<S5>/Ron+Rp' */
  real_T RonRp_a;                      /* '<S5>/1//(Ron+Rp)' */
  real_T Divide;                       /* '<S10>/Divide' */
  real_T ZOH1;                         /* '<S1>/ZOH1' */
  real_T Sum2;                         /* '<S1>/Sum2' */
  real_T SWFilter;                     /* '<S11>/S//W Filter' */
  real_T SWFilter1;                    /* '<S11>/S//W Filter1' */
  real_T CURRENTREFERROR;              /* '<S11>/CURRENT REF ERROR' */
  real_T RateTransition1_f;            /* '<S11>/Rate Transition1' */
  real_T deltaD2;                      /* '<S11>/deltaD//2' */
  real_T HWFilter;                     /* '<S11>/H//W Filter' */
  real_T HWFilter1;                    /* '<S11>/H//W Filter1' */
  real_T Invert;                       /* '<S11>/Invert' */
  real_T Constant_l;                   /* '<S14>/Constant' */
  real_T LookUpTable1_j;               /* '<S14>/Look-Up Table1' */
  real_T Co;                           /* '<S2>/1//Co' */
  real_T Gain2;                        /* '<S15>/Gain2' */
  real_T Product;                      /* '<S15>/Product' */
  real_T Cin;                          /* '<S4>/1//Cin' */
  real_T Vmpp;                         /* '<S9>/Vmpp' */
  real_T Lin;                          /* '<S4>/1//Lin' */
  real_T DiodeDrop;                    /* '<S5>/Diode Drop' */
  real_T L;                            /* '<S5>/1//L' */
  real_T RonRp_g;                      /* '<S6>/Ron+Rp' */
  real_T RonRp_k;                      /* '<S6>/1//(Ron+Rp)' */
  real_T DiodeDrop_o;                  /* '<S6>/Diode Drop' */
  real_T L_e;                          /* '<S6>/1//L' */
  real_T Lf;                           /* '<S7>/1//Lf' */
  real_T ScaleDown;                    /* '<S8>/ScaleDown' */
} B_SolarMicroinverterModelDigi_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T PIController_states;          /* '<S1>/PI Controller' */
  real_T PIController_states_l;        /* '<S11>/PI Controller' */
  real_T PIController_tmp;             /* '<S1>/PI Controller' */
  real_T RateTransition3_Buffer0;      /* '<S1>/Rate Transition3' */
  real_T RateTransition2_Buffer0;      /* '<S1>/Rate Transition2' */
  real_T RateTransition4_Buffer0;      /* '<S1>/Rate Transition4' */
  real_T PIController_tmp_i;           /* '<S11>/PI Controller' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay1_RWORK;             /* '<S12>/Transport Delay1' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay1_RWORK_e;           /* '<S4>/Transport Delay1' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay1_PWORK;             /* '<S12>/Transport Delay1' */

  struct {
    void *LoggedData;
  } Controlleroutput_PWORK;            /* '<S1>/Controller output' */

  struct {
    void *LoggedData;
  } CurrentError_PWORK;                /* '<S1>/CurrentError' */

  struct {
    void *LoggedData;
  } Iac1_PWORK;                        /* '<S1>/Iac1' */

  struct {
    void *LoggedData;
  } AverageFlybackInputCurrents_PWO;   /* '<S11>/Average Flyback Input Currents' */

  struct {
    void *LoggedData;
  } Iac2_PWORK;                        /* '<S11>/Iac2' */

  struct {
    void *LoggedData;
  } CARRIERDUTYPULSE_PWORK;            /* '<S12>/CARRIER-DUTY-PULSE' */

  struct {
    void *LoggedData;
  } CARRIERDUTYPULSE1_PWORK;           /* '<S12>/CARRIER-DUTY-PULSE1' */

  struct {
    void *LoggedData;
  } Sin_PWORK;                         /* '<S3>/Sin ' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay1_PWORK_g;           /* '<S4>/Transport Delay1' */

  struct {
    void *LoggedData;
  } Controlleroutput_PWORK_p;          /* '<S5>/Controller output' */

  struct {
    void *LoggedData;
  } Controlleroutput1_PWORK;           /* '<S5>/Controller output1' */

  struct {
    void *LoggedData;
  } FlybackInductorCurrents_PWORK;     /* '<S8>/Flyback Inductor Currents' */

  struct {
    void *LoggedData;
  } FlybackInputCurrents_PWORK;        /* '<S8>/Flyback Input Currents' */

  struct {
    void *LoggedData;
  } FlybackSecondaryDiodeCurrents_P;   /* '<S8>/Flyback Secondary Diode Currents' */

  struct {
    void *LoggedData;
  } MIXED_PWORK;                       /* '<S8>/MIXED' */

  struct {
    void *LoggedData;
  } GridCurrentandCurrentReference_;   /* '<S8>/Grid Current  and  Current Reference' */

  struct {
    void *LoggedData;
  } VOLTAGES_PWORK;                    /* '<S8>/VOLTAGES ' */

  struct {
    void *LoggedData;
  } MIXED_PWORK_c;                     /* '<S8>/MIXED ' */

  struct {
    void *LoggedData;
  } InterleavedCarriers_PWORK;         /* '<S8>/Interleaved  Carriers' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay1_IWORK;             /* '<S12>/Transport Delay1' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay1_IWORK_o;           /* '<S4>/Transport Delay1' */
} DW_SolarMicroinverterModelDig_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Filter1_CSTATE;               /* '<S1>/Filter1' */
  real_T Integrator1_CSTATE;           /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_m;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S7>/Integrator' */
  real_T Integrator1_CSTATE_k;         /* '<S4>/Integrator1' */
  real_T Integrator3_CSTATE;           /* '<S4>/Integrator3' */
  real_T SWFilter_CSTATE;              /* '<S11>/S//W Filter' */
  real_T SWFilter1_CSTATE;             /* '<S11>/S//W Filter1' */
  real_T HWFilter_CSTATE;              /* '<S11>/H//W Filter' */
  real_T HWFilter1_CSTATE;             /* '<S11>/H//W Filter1' */
} X_SolarMicroinverterModelDigi_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Filter1_CSTATE;               /* '<S1>/Filter1' */
  real_T Integrator1_CSTATE;           /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE;            /* '<S5>/Integrator' */
  real_T Integrator_CSTATE_m;          /* '<S6>/Integrator' */
  real_T Integrator_CSTATE_e;          /* '<S7>/Integrator' */
  real_T Integrator1_CSTATE_k;         /* '<S4>/Integrator1' */
  real_T Integrator3_CSTATE;           /* '<S4>/Integrator3' */
  real_T SWFilter_CSTATE;              /* '<S11>/S//W Filter' */
  real_T SWFilter1_CSTATE;             /* '<S11>/S//W Filter1' */
  real_T HWFilter_CSTATE;              /* '<S11>/H//W Filter' */
  real_T HWFilter1_CSTATE;             /* '<S11>/H//W Filter1' */
} XDot_SolarMicroinverterModelD_T;

/* State disabled  */
typedef struct {
  boolean_T Filter1_CSTATE;            /* '<S1>/Filter1' */
  boolean_T Integrator1_CSTATE;        /* '<S2>/Integrator1' */
  boolean_T Integrator_CSTATE;         /* '<S5>/Integrator' */
  boolean_T Integrator_CSTATE_m;       /* '<S6>/Integrator' */
  boolean_T Integrator_CSTATE_e;       /* '<S7>/Integrator' */
  boolean_T Integrator1_CSTATE_k;      /* '<S4>/Integrator1' */
  boolean_T Integrator3_CSTATE;        /* '<S4>/Integrator3' */
  boolean_T SWFilter_CSTATE;           /* '<S11>/S//W Filter' */
  boolean_T SWFilter1_CSTATE;          /* '<S11>/S//W Filter1' */
  boolean_T HWFilter_CSTATE;           /* '<S11>/H//W Filter' */
  boolean_T HWFilter1_CSTATE;          /* '<S11>/H//W Filter1' */
} XDis_SolarMicroinverterModelD_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            SolarMicroinverterModelDigita_B
#define BlockIO                        B_SolarMicroinverterModelDigi_T
#define rtX                            SolarMicroinverterModelDigita_X
#define ContinuousStates               X_SolarMicroinverterModelDigi_T
#define rtXdot                         SolarMicroinverterModelDig_XDot
#define StateDerivatives               XDot_SolarMicroinverterModelD_T
#define tXdis                          SolarMicroinverterModelDig_XDis
#define StateDisabled                  XDis_SolarMicroinverterModelD_T
#define rtP                            SolarMicroinverterModelDigita_P
#define Parameters                     P_SolarMicroinverterModelDigi_T
#define rtDWork                        SolarMicroinverterModelDigit_DW
#define D_Work                         DW_SolarMicroinverterModelDig_T

/* Parameters (auto storage) */
struct P_SolarMicroinverterModelDigi_T_ {
  real_T CARRIER_rep_seq_y[2];         /* Mask Parameter: CARRIER_rep_seq_y
                                        * Referenced by: '<S13>/Look-Up Table1'
                                        */
  real_T CARRIER1_rep_seq_y[2];        /* Mask Parameter: CARRIER1_rep_seq_y
                                        * Referenced by: '<S14>/Look-Up Table1'
                                        */
  real_T UNITSINE_Amp;                 /* Expression: 1
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  real_T UNITSINE_Bias;                /* Expression: 0
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  real_T UNITSINE_Freq;                /* Expression: 2*pi*50
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  real_T UNITSINE_Phase;               /* Expression: 0
                                        * Referenced by: '<S3>/UNIT SINE'
                                        */
  real_T POWER_Value;                  /* Expression: 215
                                        * Referenced by: '<S15>/POWER'
                                        */
  real_T RMSGridVoltage_Value;         /* Expression: 230
                                        * Referenced by: '<S15>/RMS GridVoltage'
                                        */
  real_T Gain1_Gain;                   /* Expression: sqrt(2)
                                        * Referenced by: '<S15>/Gain1'
                                        */
  real_T Filter1_A;                    /* Computed Parameter: Filter1_A
                                        * Referenced by: '<S1>/Filter1'
                                        */
  real_T Filter1_C;                    /* Computed Parameter: Filter1_C
                                        * Referenced by: '<S1>/Filter1'
                                        */
  real_T PerUnitizingGain_Gain;        /* Expression: 1/2.14
                                        * Referenced by: '<S1>/PerUnitizingGain'
                                        */
  real_T PIController_NumCoef[2];      /* Expression: [0.1805 -0.1595]
                                        * Referenced by: '<S1>/PI Controller'
                                        */
  real_T PIController_DenCoef[2];      /* Expression: [1 -1]
                                        * Referenced by: '<S1>/PI Controller'
                                        */
  real_T PIController_InitialStates;   /* Expression: 0
                                        * Referenced by: '<S1>/PI Controller'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S2>/Integrator1'
                                        */
  real_T Constant_Value;               /* Expression: period
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T LookUpTable1_bp01Data[2];     /* Expression: rep_seq_t - min(rep_seq_t)
                                        * Referenced by: '<S13>/Look-Up Table1'
                                        */
  real_T RateTransition3_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition3'
                                        */
  real_T DutyLimit2_UpperSat;          /* Expression: 0.02
                                        * Referenced by: '<S12>/Duty Limit2'
                                        */
  real_T DutyLimit2_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit2'
                                        */
  real_T RateTransition2_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition2'
                                        */
  real_T DutyLimit_UpperSat;           /* Expression: 0.75
                                        * Referenced by: '<S12>/Duty Limit'
                                        */
  real_T DutyLimit_LowerSat;           /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S5>/Integrator'
                                        */
  real_T CURRENTLIMIT_UpperSat;        /* Expression: 200
                                        * Referenced by: '<S5>/CURRENT LIMIT'
                                        */
  real_T CURRENTLIMIT_LowerSat;        /* Expression: -1
                                        * Referenced by: '<S5>/CURRENT LIMIT'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1/7
                                        * Referenced by: '<S5>/Gain3'
                                        */
  real_T TransportDelay1_Delay;        /* Expression: 8.5e-6
                                        * Referenced by: '<S12>/Transport Delay1'
                                        */
  real_T TransportDelay1_InitOutput;   /* Expression: 0
                                        * Referenced by: '<S12>/Transport Delay1'
                                        */
  real_T RateTransition4_X0;           /* Expression: 0
                                        * Referenced by: '<S1>/Rate Transition4'
                                        */
  real_T DutyLimit3_UpperSat;          /* Expression: 0.02
                                        * Referenced by: '<S12>/Duty Limit3'
                                        */
  real_T DutyLimit3_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit3'
                                        */
  real_T DutyLimit1_UpperSat;          /* Expression: 0.75
                                        * Referenced by: '<S12>/Duty Limit1'
                                        */
  real_T DutyLimit1_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S12>/Duty Limit1'
                                        */
  real_T Integrator_IC_p;              /* Expression: 0
                                        * Referenced by: '<S6>/Integrator'
                                        */
  real_T CURRENTLIMIT_UpperSat_a;      /* Expression: 200
                                        * Referenced by: '<S6>/CURRENT LIMIT'
                                        */
  real_T CURRENTLIMIT_LowerSat_a;      /* Expression: -1
                                        * Referenced by: '<S6>/CURRENT LIMIT'
                                        */
  real_T Gain3_Gain_g;                 /* Expression: 1/7
                                        * Referenced by: '<S6>/Gain3'
                                        */
  real_T Integrator_IC_b;              /* Expression: 0
                                        * Referenced by: '<S7>/Integrator'
                                        */
  real_T LIMIT_UpperSat;               /* Expression: 10
                                        * Referenced by: '<S7>/ LIMIT'
                                        */
  real_T LIMIT_LowerSat;               /* Expression: -0.5
                                        * Referenced by: '<S7>/ LIMIT'
                                        */
  real_T ESR_Gain;                     /* Expression: 0.05
                                        * Referenced by: '<S2>/ESR'
                                        */
  real_T Integrator1_IC_h;             /* Expression: 0
                                        * Referenced by: '<S4>/Integrator1'
                                        */
  real_T Integrator3_IC;               /* Expression: 0
                                        * Referenced by: '<S4>/Integrator3'
                                        */
  real_T RonRp_Value;                  /* Expression: 0.04
                                        * Referenced by: '<S5>/Ron+Rp'
                                        */
  real_T RonRp_Gain;                   /* Expression: 1/0.04
                                        * Referenced by: '<S5>/1//(Ron+Rp)'
                                        */
  real_T Resr_Gain;                    /* Expression: 0.05
                                        * Referenced by: '<S4>/Resr'
                                        */
  real_T VOLTAGELIMIT_UpperSat;        /* Expression: 100
                                        * Referenced by: '<S4>/VOLTAGE LIMIT'
                                        */
  real_T VOLTAGELIMIT_LowerSat;        /* Expression: 0
                                        * Referenced by: '<S4>/VOLTAGE LIMIT'
                                        */
  real_T TURNS_Gain;                   /* Expression: 7
                                        * Referenced by: '<S10>/TURNS'
                                        */
  real_T SWFilter_A;                   /* Computed Parameter: SWFilter_A
                                        * Referenced by: '<S11>/S//W Filter'
                                        */
  real_T SWFilter_C;                   /* Computed Parameter: SWFilter_C
                                        * Referenced by: '<S11>/S//W Filter'
                                        */
  real_T SWFilter1_A;                  /* Computed Parameter: SWFilter1_A
                                        * Referenced by: '<S11>/S//W Filter1'
                                        */
  real_T SWFilter1_C;                  /* Computed Parameter: SWFilter1_C
                                        * Referenced by: '<S11>/S//W Filter1'
                                        */
  real_T CURRENTREFERROR_Value;        /* Expression: 0
                                        * Referenced by: '<S11>/CURRENT REF ERROR'
                                        */
  real_T PerUnitizingGainBaseConversion_;/* Expression: 1.36/11
                                          * Referenced by: '<S11>/Per Unitizing Gain + Base Conversion'
                                          */
  real_T PIController_NumCoef_m[2];    /* Expression: [0.07 -0.06]
                                        * Referenced by: '<S11>/PI Controller'
                                        */
  real_T PIController_DenCoef_f[2];    /* Expression: [1 -1]
                                        * Referenced by: '<S11>/PI Controller'
                                        */
  real_T PIController_InitialStates_p; /* Expression: 0
                                        * Referenced by: '<S11>/PI Controller'
                                        */
  real_T deltaD2_Gain;                 /* Expression: 1/2
                                        * Referenced by: '<S11>/deltaD//2'
                                        */
  real_T HWFilter_A;                   /* Computed Parameter: HWFilter_A
                                        * Referenced by: '<S11>/H//W Filter'
                                        */
  real_T HWFilter_C;                   /* Computed Parameter: HWFilter_C
                                        * Referenced by: '<S11>/H//W Filter'
                                        */
  real_T HWFilter1_A;                  /* Computed Parameter: HWFilter1_A
                                        * Referenced by: '<S11>/H//W Filter1'
                                        */
  real_T HWFilter1_C;                  /* Computed Parameter: HWFilter1_C
                                        * Referenced by: '<S11>/H//W Filter1'
                                        */
  real_T Invert_Gain;                  /* Expression: -1
                                        * Referenced by: '<S11>/Invert'
                                        */
  real_T Constant_Value_f;             /* Expression: period
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T LookUpTable1_bp01Data_b[2];   /* Expression: rep_seq_t - min(rep_seq_t)
                                        * Referenced by: '<S14>/Look-Up Table1'
                                        */
  real_T Co_Gain;                      /* Expression: 1/(0.1e-6*3+0.015e-6 * 3)
                                        * Referenced by: '<S2>/1//Co'
                                        */
  real_T Gain2_Gain;                   /* Expression: sqrt(2)
                                        * Referenced by: '<S15>/Gain2'
                                        */
  real_T Cin_Gain;                     /* Expression: 1/(4*1800E-6)
                                        * Referenced by: '<S4>/1//Cin'
                                        */
  real_T Vmpp_Value;                   /* Expression: 36
                                        * Referenced by: '<S9>/Vmpp'
                                        */
  real_T TransportDelay1_Delay_l;      /* Expression: 1e-7
                                        * Referenced by: '<S4>/Transport Delay1'
                                        */
  real_T TransportDelay1_InitOutput_l; /* Expression: 0
                                        * Referenced by: '<S4>/Transport Delay1'
                                        */
  real_T Rin_Gain;                     /* Expression: 0.02
                                        * Referenced by: '<S4>/Rin'
                                        */
  real_T Lin_Gain;                     /* Expression: 1/0.22e-6
                                        * Referenced by: '<S4>/1//Lin'
                                        */
  real_T Rs_Gain;                      /* Expression: 1
                                        * Referenced by: '<S5>/Rs'
                                        */
  real_T DiodeDrop_Value;              /* Expression: 2
                                        * Referenced by: '<S5>/Diode Drop'
                                        */
  real_T N_Gain;                       /* Expression: 1/7
                                        * Referenced by: '<S5>/1//N'
                                        */
  real_T L_Gain;                       /* Expression: 1/55e-6
                                        * Referenced by: '<S5>/1//L'
                                        */
  real_T RonRp_Value_n;                /* Expression: 0.04
                                        * Referenced by: '<S6>/Ron+Rp'
                                        */
  real_T RonRp_Gain_d;                 /* Expression: 1/0.04
                                        * Referenced by: '<S6>/1//(Ron+Rp)'
                                        */
  real_T Rs_Gain_c;                    /* Expression: 2
                                        * Referenced by: '<S6>/Rs'
                                        */
  real_T DiodeDrop_Value_g;            /* Expression: 2
                                        * Referenced by: '<S6>/Diode Drop'
                                        */
  real_T N_Gain_p;                     /* Expression: 1/7
                                        * Referenced by: '<S6>/1//N'
                                        */
  real_T L_Gain_h;                     /* Expression: 1/50e-6
                                        * Referenced by: '<S6>/1//L'
                                        */
  real_T Rf_Gain;                      /* Expression: 2*0.2+2*60e-3 + 2*40e-3
                                        * Referenced by: '<S7>/Rf'
                                        */
  real_T Lf_Gain;                      /* Expression: 1/300e-6
                                        * Referenced by: '<S7>/1//Lf'
                                        */
  real_T ScaleDown_Gain;               /* Expression: 1/300
                                        * Referenced by: '<S8>/ScaleDown'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_SolarMicroinverterMod_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    void *blockIO;
    const void *constBlockIO;
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[11];
    real_T odeF[4][11];
    ODE4_IntgData intgData;
    void *dwork;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    time_T stepSize2;
    uint32_T clockTick3;
    uint32_T clockTickH3;
    time_T stepSize3;
    struct {
      uint16_T TID[4];
    } TaskCounters;

    struct {
      boolean_T TID0_2;
      boolean_T TID0_3;
      boolean_T TID1_2;
      boolean_T TID1_3;
    } RateInteraction;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[4];
    time_T offsetTimesArray[4];
    int_T sampleTimeTaskIDArray[4];
    int_T sampleHitArray[4];
    int_T perTaskSampleHitsArray[16];
    time_T tArray[4];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_P;

/* Block signals (auto storage) */
extern B_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_B;

/* Continuous states (auto storage) */
extern X_SolarMicroinverterModelDigi_T SolarMicroinverterModelDigita_X;

/* Block states (auto storage) */
extern DW_SolarMicroinverterModelDig_T SolarMicroinverterModelDigit_DW;

/* External function called from main */
extern time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
  ;

/* Model entry point functions */
extern void SolarMicroinverterModelDigitalControl_230V_initialize(void);
extern void SolarMicroinverterModelDigitalControl_230V_output0(void);
extern void SolarMicroinverterModelDigitalControl_230V_update0(void);
extern void SolarMicroinverterModelDigitalControl_230V_output(int_T tid);
extern void SolarMicroinverterModelDigitalControl_230V_update(int_T tid);
extern void SolarMicroinverterModelDigitalControl_230V_terminate(void);

/*====================*
 * External functions *
 *====================*/
extern SolarMicroinverterModelDigitalControl_230V_rtModel
  *SolarMicroinverterModelDigitalControl_230V(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Real-time Model object */
extern RT_MODEL_SolarMicroinverterMo_T *const SolarMicroinverterModelDigit_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SolarMicroinverterModelDigitalControl_230V'
 * '<S1>'   : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM'
 * '<S2>'   : 'SolarMicroinverterModelDigitalControl_230V/FLYBACK OUTPUT  CAPACITOR'
 * '<S3>'   : 'SolarMicroinverterModelDigitalControl_230V/GRID//LOAD'
 * '<S4>'   : 'SolarMicroinverterModelDigitalControl_230V/INPUT FILTER  CIRCUIT'
 * '<S5>'   : 'SolarMicroinverterModelDigitalControl_230V/INTERLEAVED FLYBACK INDUCTOR1'
 * '<S6>'   : 'SolarMicroinverterModelDigitalControl_230V/INTERLEAVED FLYBACK INDUCTOR2'
 * '<S7>'   : 'SolarMicroinverterModelDigitalControl_230V/OUTPUT FILTER  INDUCTOR'
 * '<S8>'   : 'SolarMicroinverterModelDigitalControl_230V/PROBE STATION'
 * '<S9>'   : 'SolarMicroinverterModelDigitalControl_230V/SOLAR PANEL  OUTPUT'
 * '<S10>'  : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM/FEEDFORWARD  NETWORK'
 * '<S11>'  : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM/LOAD SHARING  CONTROL SYSTEM'
 * '<S12>'  : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM/PWM MODULATOR'
 * '<S13>'  : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM/PWM MODULATOR/CARRIER'
 * '<S14>'  : 'SolarMicroinverterModelDigitalControl_230V/DIGITAL CONTROL  SYSTEM/PWM MODULATOR/CARRIER1'
 * '<S15>'  : 'SolarMicroinverterModelDigitalControl_230V/GRID//LOAD/PLL'
 */
#endif                                 /* RTW_HEADER_SolarMicroinverterModelDigitalControl_230V_h_ */
