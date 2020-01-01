//==============================================================================
//
//  File        : mmps_iva.h
//  Description : INCLUDE File for the Intelligent video analysis function.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPS_IVA_H_
#define _MMPS_IVA_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "ait_config.h"

/** @addtogroup MMPS_IVA
@{
*/

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPS_IVA_EVENT {
    MMPS_IVA_EVENT_MDTC = 0x0,
    MMPS_IVA_EVENT_MAX
} MMPS_IVA_EVENT;

typedef enum _MMPS_IVA_ADAS_FEATURE {
    MMPS_ADAS_LDWS = 0x0,
    MMPS_ADAS_FCWS,
    MMPS_ADAS_SAG,
    MMPS_ADAS_FEATURE_NUM
} MMPS_IVA_ADAS_FEATURE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (SUPPORT_MDTC)
MMP_ERR  MMPS_Sensor_AllocateVMDBuffer(MMP_ULONG *ulStartAddr, MMP_BOOL bAllocate);
MMP_ERR  MMPS_Sensor_GetVMDResolution(MMP_ULONG *ulWidth, MMP_ULONG *ulHeight);
MMP_ERR  MMPS_Sensor_EnableVMD(MMP_BOOL bEnable);
MMP_BOOL MMPS_Sensor_IsVMDEnable(void);
MMP_ERR MMPS_Sensor_RegisterVMDCallback(MMP_UBYTE event, void *callback);
MMP_ERR MMPS_Sensor_GetVMDWorkBuf(MMP_ULONG *ulWorkBuf, MMP_ULONG *ulBufSize);
#endif

#if (SUPPORT_ADAS)
MMP_ERR  MMPS_Sensor_AllocateADASBuffer(MMP_ULONG *ulStartAddr, MMP_BOOL bAllocate, MMP_ULONG ulADASBufSize);
MMP_ERR  MMPS_Sensor_GetADASResolution(MMP_ULONG *ulWidth, MMP_ULONG *ulHeight);
MMP_ERR  MMPS_Sensor_SetADASFeatureEn(MMPS_IVA_ADAS_FEATURE feature, MMP_BOOL bEnable);
MMP_BOOL MMPS_Sensor_GetADASFeatureEn(MMPS_IVA_ADAS_FEATURE feature);
MMP_ERR  MMPS_Sensor_EnableADAS(MMP_BOOL bEnable);
MMP_ERR MMPS_Sensor_GetADASImgBuf(MMP_ULONG* ulInputLumaAddr);
MMP_ERR MMPS_Sensor_GetADASWorkBuf(MMP_ULONG* ulWorkAddr, MMP_ULONG* ulWorkSize);
MMP_BOOL MMPS_Sensor_IsADASEnable(void);
#endif

/// @}
#endif // _MMPS_IVA_H_
