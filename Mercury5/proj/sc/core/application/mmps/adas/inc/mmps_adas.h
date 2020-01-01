//==============================================================================
//
//  File        : mmps_Adas.h
//  Description : INCLUDE File for the irda decode.
//  Author      : lei.qin
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPS_ADAS_H_
#define _MMPS_ADAS_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "ait_config.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPS_ADAS_CustomerInitPara(MMP_ULONG AlarmDelayTimeMS, MMP_ULONG AlarmRestTimeMS, MMP_ULONG AlarmSpeedThd,
							    MMP_ULONG AlarmTTCThd1, MMP_ULONG AlarmTTCThd2,
							    MMP_ULONG AlarmDISTThd1, MMP_ULONG AlarmDISTThd2);
void MMPS_ADAS_CustomerSpecifyPara(MMP_ULONG FocalLength, MMP_ULONG PixelSize, MMP_ULONG DzoomN, MMP_ULONG DzoomM);
void MMPS_ADAS_CustomerCameraHeight(MMP_ULONG CameraHeight);
void MMPS_ADAS_CustomerCalibration(MMP_ULONG CablitionStarY,MMP_ULONG CablitionEndY);
void MMPS_ADAS_CustomerWarningMode(MMP_ULONG WarningMode);
void MMPS_ADAS_CustomeLdwsCalibratedParam(ldws_tuning_params LdwsCalibratedParam);
void MMPS_ADAS_RegisterCallBack(PADAS_CALLBACK pfCallback);






/// @}
#endif // _MMPS_IRDA_H_