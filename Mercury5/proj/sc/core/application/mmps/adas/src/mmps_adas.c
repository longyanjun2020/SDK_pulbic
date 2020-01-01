//==============================================================================
//
//  File        : mmps_adas.c
//  Description : ADAS User Application Interface
//  Author      : Rony Yeh
//  Revision    : 1.0
//
//==============================================================================


//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "ldws.h"
#include "mmpf_adas_ctl.h"
#include "mmps_adas.h"

#if (SUPPORT_ADAS)

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_CustomerInitPara
//  Description : Initial the parameter by Customer for 
//                alarm delay/reset time/speed threshold/TTC & DIST threhold
//------------------------------------------------------------------------------
/**
 * @brief                 Initial the parameter by Customer for 
 *                        alarm delay/reset time/speed threshold/TTC & DIST threhold
 *
 * @param[in ] AlarmDelayTime  delay time of alarm <unit: ms>
 * @param[in ] AlarmRestTime   reset time of alarm <unit: ms>
 * @param[in ] AlarmSpeedThd   speed threshold of alarm
 * @param[in ] AlarmTTCThd1    TTC threshold1 of alarm
 * @param[in ] AlarmTTCThd2    TTC threshold2 of alarm
 * @param[in ] AlarmDISTThd1   DIST threshold1 of alarm
 * @param[in ] AlarmDISTThd2   DIST threshold2 of alarm
 *
 *
 */
void MMPS_ADAS_CustomerInitPara(MMP_ULONG AlarmDelayTimeMS, MMP_ULONG AlarmRestTimeMS, MMP_ULONG AlarmSpeedThd,
                                MMP_ULONG AlarmTTCThd1, MMP_ULONG AlarmTTCThd2,
                                MMP_ULONG AlarmDISTThd1, MMP_ULONG AlarmDISTThd2)
{
    _ADAS_CustomerInitPara( AlarmDelayTimeMS,  AlarmRestTimeMS,  AlarmSpeedThd,
                            AlarmTTCThd1,   AlarmTTCThd2,
                            AlarmDISTThd1,  AlarmDISTThd2);
}

//------------------------------------------------------------------------------
//  Function    : _ADAS_CustomerSpecifyPara
//  Description : Initial the Specify parameter by Customer for 
//                FocalLength , PixelSize , CameraHeight , DzoomN DzoomM ; please check <ADAS Integration Guide>
//------------------------------------------------------------------------------
/**
 * @brief  Initial the Specify parameter by Customer for 
//         FocalLength , PixelSize , CameraHeight , DzoomN DzoomM ; please check <ADAS Integration Guide>
 *
 *
 *
 *
 */
void MMPS_ADAS_CustomerSpecifyPara(MMP_ULONG FocalLength, MMP_ULONG PixelSize, MMP_ULONG DzoomN, MMP_ULONG DzoomM)
{
    _ADAS_CustomerSpecifyPara( FocalLength,  PixelSize, DzoomN,  DzoomM);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_CustomerCameraHeight
//  Description : Initial the Specify parameter by Customer for  CameraHeight
//------------------------------------------------------------------------------
void MMPS_ADAS_CustomerCameraHeight(MMP_ULONG CameraHeight)
{
    _ADAS_CustomerCameraHeight( CameraHeight);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_CustomerCalibration
//  Description : Initial the Specify parameter by Customer for  Calibration
//------------------------------------------------------------------------------
void MMPS_ADAS_CustomerCalibration(MMP_ULONG CablitionStarY,MMP_ULONG CablitionEndY)
{
    _ADAS_CustomereCalibration( CablitionStarY,CablitionEndY);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_CustomerWarningMode
//  Description : Initial the Specify parameter by Customer for  Calibration
//------------------------------------------------------------------------------
void MMPS_ADAS_CustomerWarningMode(MMP_ULONG WarningMode)
{
    _ADAS_CustomerWarningMode(WarningMode);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_CustomeLdwsCalibratedParam
//  Description :
//------------------------------------------------------------------------------
void MMPS_ADAS_CustomeLdwsCalibratedParam(ldws_tuning_params LdwsCalibratedParam)
{
    _ADAS_CustomerLdwsCalibratedParam(LdwsCalibratedParam);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_ADAS_RegisterCallBack
//  Description : Register ADAS call back function.
//------------------------------------------------------------------------------
void MMPS_ADAS_RegisterCallBack(PADAS_CALLBACK pfCallback)
{
    ADAS_CTL_RegistCallback(pfCallback);
}

#endif
