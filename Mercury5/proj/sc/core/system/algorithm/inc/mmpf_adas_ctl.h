//==============================================================================
//
//  File        : mmpf_adas_ctl.h
//  Description : INCLUDE File for the Firmware ADS\AS driver function
//  Author      : Jerry Li
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MMPF_ADAS_CTL_H_
#define _MMPF_ADAS_CTL_H_
    
#include "ldws.h"
//#include "config_fw.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
//LDWS define
#define LDWS_HALF_IMAGE_MODE_EN		(0) // Keep it as 0
#define LDWS_MIN_WORKING_PERIOD		(66) // unit: ms
#define LDWS_DBG					(0)
#define LDWS_WARN_SPEED				(60) // Unit: Km
//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================
typedef enum
{
	ADAS_CALL_BK_LDWS = 0,
	ADAS_CALL_BK_FCWS,
	ADAS_CALL_BK_SAG,
	ADAS_CALL_BK_WRITE_LOG
} ADAS_CALL_BK_TYPE;
//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================
extern LdwsSetupPosi   ldwsSetupPosi;
//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================
// Callback
typedef void (*PADAS_CALLBACK) (const void *, ADAS_CALL_BK_TYPE type);
//
void ADAS_open_txt(char * pStrFileName);
void ADAS_close_txt(void);
void _ADAS_CustomerInitPara(MMP_ULONG AlarmDelayTimeMS, MMP_ULONG AlarmRestTimeMS, MMP_ULONG AlarmSpeedThd,
							    MMP_ULONG AlarmTTCThd1, MMP_ULONG AlarmTTCThd2,
							    MMP_ULONG AlarmDISTThd1, MMP_ULONG AlarmDISTThd2);
void _ADAS_CustomerSpecifyPara(MMP_ULONG FocalLength, MMP_ULONG PixelSize,
							   MMP_ULONG DzoomN, MMP_ULONG DzoomM);
void _ADAS_CustomerCameraHeight( MMP_ULONG CameraHeight);
void _ADAS_CustomereCalibration( MMP_ULONG CablitionStarY,MMP_ULONG CablitionEndY);
void _ADAS_CustomerWarningMode( MMP_ULONG WarningMode);
void _ADAS_CustomerLdwsCalibratedParam( ldws_tuning_params LdwsCalibratedParam);
void _ADAS_GetCustomerPara(MMP_ULONG *pFocalLength, MMP_ULONG *pPixelSize,
							   MMP_ULONG *pDzoomN, MMP_ULONG *pDzoomM);
void ADAS_CTL_RegistCallback(PADAS_CALLBACK pfCallback);
int  adas_main(void);

#endif //_MMPF_ADAS_CTL_H_

