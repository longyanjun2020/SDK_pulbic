//==============================================================================
//
//  File        : mmps_sensor.h
//  Description : INCLUDE File for the Host Application for Sensor.
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmps_sensor.h
 *  @brief The header File for the Host Sensor control functions
 *  @author Alan Wu
 *  @version 1.0
 */

#ifndef _MMPS_SENSOR_H_
#define _MMPS_SENSOR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_sensor.h"

/** @addtogroup MMPS_SENSOR
@{
*/

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR  MMPS_Sensor_Initialize(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_SNR_MODE eSnrMode, MMP_UBYTE ubHdrEnable, MMP_ULONG ulIqCfgIdx);
MMP_BOOL MMPS_Sensor_IsInitialized(MMP_UBYTE ubSnrSel);
MMP_ERR  MMPS_Sensor_ChangePreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_UBYTE ubWaitCount);
MMP_ERR  MMPS_Sensor_SetPreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode);
MMP_ERR  MMPS_Sensor_SetCaptureMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubCaptureMode);
MMP_ERR  MMPS_Sensor_GetCurPrevScalInputRes(MMP_UBYTE ubSnrSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight);
MMP_ERR  MMPS_Sensor_GetCurSensorOutputRes(MMP_UBYTE ubSnrSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight);
MMP_ERR  MMPS_Sensor_GetScalInputRes(MMP_UBYTE ubSnrSel, MMP_UBYTE ubMode, MMP_ULONG *ulWidth, MMP_ULONG *ulHeight);
MMP_UBYTE MMPS_Sensor_GetPreviewResNum(MMP_UBYTE ubSnrSel);
MMP_UBYTE MMPS_Sensor_GetDefPreviewMode(MMP_UBYTE ubSnrSel);
MMP_ERR  MMPS_Sensor_GetCurFpsx10(MMP_UBYTE ubSnrSel, MMP_ULONG *pulFpsx10);
MMP_ERR  MMPS_Sensor_PowerDown(MMP_UBYTE ubSnrSel);
MMP_ERR  MMPS_Sensor_SetSensorReg(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT usData);
MMP_ERR  MMPS_Sensor_GetSensorReg(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT *usData);
MMP_ERR  MMPS_Sensor_SetFlip(MMP_UBYTE ubSnrSel, MMP_UBYTE ubFlipType);
MMP_ERR  MMPS_Sensor_SetGain(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain, MMP_UBYTE ubType);
MMP_ERR  MMPS_Sensor_SetShutter(MMP_UBYTE ubSnrSel, MMP_UBYTE ubIndex, MMP_UBYTE ubType);
MMP_ERR  MMPS_Sensor_SetExposureLimit(MMP_ULONG ulBufaddr, MMP_ULONG ulDatatypeByByte, MMP_ULONG ulSize, MMP_UBYTE ubType);
MMP_ERR  MMPS_Sensor_SetNightMode(MMP_UBYTE ubSnrSel, MMP_ULONG ulMode, MMP_ULONG ulMinFPS);
MMP_ERR  MMPS_Sensor_Set3AFunction(MMP_UBYTE ubSnrSel, MMP_ISP_3A_FUNC sFunc, int pParam);
MMP_ERR  MMPS_Sensor_SetIQFunction(MMP_UBYTE ubSnrSel, MMP_ISP_IQ_FUNC sFunc, int pParam);
MMP_ERR  MMPS_Sensor_SetPreviewDelayCount(MMP_UBYTE ubSnrSel, MMP_UBYTE ubDelayCount);
MMP_ERR  MMPS_Sensor_RegisterCallback(MMP_UBYTE event, void *callback);

/* YUV Sensor */
void MMPS_Sensor_GetYUVSnrSrcType(MMP_SNR_YUV_SRC_TYPE *peSnrSrc);

/* Analog Decoder */
MMP_ERR MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(MMP_UBYTE ubSnrSel, void *callback, MMP_ULONG ulPeriod, MMP_BOOL bEn);
void MMPS_Sensor_GetAnaDecSrcType(MMP_SNR_ANADEC_SRC_TYPE *peSnrSrc);
void MMPS_Sensor_CheckAnaDecSrcType(MMP_UBYTE ubSnrSel, MMP_SNR_ANADEC_SRC_TYPE *sSnrTVSrc);
void MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_BOOL bEnable);

/// @}
MMP_ERR MMPS_Sensor_SetMirrorFlip(MMP_UBYTE ubSnrSel, MMP_SNR_ORIT Orit);

#endif // _MMPS_SENSOR_H_
