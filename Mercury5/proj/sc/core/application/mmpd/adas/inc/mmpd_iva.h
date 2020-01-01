/// @ait_only
//==============================================================================
//
//  File        : mmpd_iva.h
//  Description : Intelligent video analysis function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_IVA_H_
#define _MMPD_IVA_H_

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (SUPPORT_MDTC)
MMP_ERR MMPD_Sensor_InitializeVMD(void);
MMP_ERR MMPD_Sensor_SetVMDBuf(MMP_ULONG buf_addr, MMP_ULONG *buf_size);
MMP_ERR MMPD_Sensor_GetVMDResolution(MMP_ULONG *width, MMP_ULONG *height);
MMP_ERR MMPD_Sensor_RegisterVMDCallback(void *Callback);
MMP_ERR MMPD_Sensor_EnableVMD(MMP_BOOL bEnable);
MMP_ERR MMPD_Sensor_GetVMDWorkBuf(MMP_ULONG *ulWorkBuf, MMP_ULONG *ulBufSize);
#endif

#if (SUPPORT_ADAS)
MMP_ERR MMPD_Sensor_InitializeADAS(void);
MMP_ERR MMPD_Sensor_SetADASBuf(MMP_ULONG buf_addr, MMP_ULONG *buf_size, MMP_ULONG dma_buf_addr);
MMP_ERR MMPD_Sensor_GetADASResolution(MMP_ULONG *width, MMP_ULONG *height);
MMP_ERR MMPD_Sensor_SetADASFeature(MMP_BOOL ldws_on, MMP_BOOL fcws_on, MMP_BOOL sag_on);
MMP_ERR MMPD_Sensor_EnableADAS(MMP_BOOL bEnable);
MMP_ERR MMPD_Sensor_GetADASImgBuf(MMP_ULONG* ulInputLumaAddr);
MMP_ERR MMPD_Sensor_GetADASWorkBuf(MMP_ULONG* ulWorkAddr, MMP_ULONG* ulWorkSize);
#endif

#endif //_MMPD_IVA_H_