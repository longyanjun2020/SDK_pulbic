//==============================================================================
//
//  File        : ahc_warningmsg.h
//  Description : INCLUDE File for the AHC Warning message porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_WARNINGMSG_H_
#define _AHC_WARNINGMSG_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _WMSG_INFO {
    WMSG_NONE = 0           ,
    WMSG_CARD_ERROR         ,
    WMSG_STORAGE_FULL       ,
    WMSG_NO_CARD            ,
    WMSG_LOW_BATTERY        ,
    WMSG_FILE_ERROR         ,
    WMSG_CARD_LOCK          ,
    WMSG_CARD_SLOW          ,
    WMSG_ADAPTER_ERROR      ,
    WMSG_INVALID_OPERATION  ,
    WMSG_CANNOT_DELETE      ,
    WMSG_BATTERY_FULL       ,
    WMSG_LENS_ERROR         ,
    WMSG_HDMI_TV            ,
    WMSG_FHD_VR             ,
    WMSG_PLUG_OUT_SD_CARD   ,
    WMSG_WAIT_INITIAL_DONE  ,
    WMSG_INSERT_SD_AGAIN    ,
    WMSG_FORMAT_SD_PROCESSING,
    WMSG_FORMAT_SD_CARD_OK  ,
    WMSG_FORMAT_SD_CARD_FAIL,
    WMSG_COME2EMER          ,
    WMSG_TIME_ERROR         ,
    WMSG_SHOW_FW_VERSION    ,
    WMSG_START_RECORD       ,
    WMSG_START_NORMAL_RECORD,
    WMSG_SPEEDCAM_ADDED     ,
    WMSG_ADD_SPEEDCAM       ,
    WMSG_DEL_SPEEDCAM       ,
    WMSG_NO_POI_SPACE       ,
    WMSG_WAIT_GPS_FIX       ,
    WMSG_PARKING_MODE_DISABLE,
    WMSG_LDWS_RightShift    ,
    WMSG_LDWS_LeftShift     ,
    WMSG_SEAMLESS_ERROR     ,
    WMSG_FORMAT_SD_CARD     ,
    WMSG_LOCK_CURRENT_FILE  ,
    WMSG_UNLOCK_CUR_FILE    ,
    WMSG_DELETE_FILE_OK     ,
    WMSG_PROTECT_FILE_OK    ,
    WMSG_GOTO_POWER_OFF     ,
    WMSG_NO_FILE_IN_BROWSER ,
    WMSG_CAPTURE_CUR_FRAME  ,
    WMSG_FCWS               ,
    WMSG_FATIGUEALERT       ,
    WMSG_OPENFILE_WAIT      ,
    WMSG_NO_CARD1           ,
    WMSG_NO_CARD2           ,
    WMSG_CARD2_FULL         ,
    WMSG_NO_CARD2_2         ,
    WMSG_BACKUP_FINISH      ,
    WMSG_MOTION_OPERATING_DESCRIPTION,
    WMSG_MSG_EMERGENCY_FILE_FULL,
    WMSG_REMIND_HEADLIGHT,
    WMSG_PARKING_OPERATING_DESCRIPTION,

    END_OF_WMSG
} WMSG_INFO;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _AHC_WMSG_CFG {
    UINT16 DisplayID;
    UINT32 StartX;
    UINT32 StartY;
    UINT32 DisplayWidth;
    UINT32 DisplayHeight;
    UINT32 byBkColor;
    UINT32 byBoundColor;
} AHC_WMSG_CFG;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL    AHC_WMSG_Config(void);
WMSG_INFO   AHC_WMSG_GetInfo(void);
AHC_BOOL    AHC_WMSG_States(void);
AHC_BOOL    AHC_WMSG_IsTimeOut(UINT32 msTimer);
AHC_BOOL    AHC_WMSG_SetLensError(UINT32 Number);
AHC_BOOL    AHC_WMSG_GetLensError(UINT32 *Number);
void        AHC_WMSG_SetStringID(WMSG_INFO sWMSGInfoIndex, UINT32 uiStringID);
AHC_BOOL    AHC_WMSG_Draw(AHC_BOOL Enable, WMSG_INFO WMSGInfo, UINT8 WMSGShowTime);
void        AHC_WMSG_SetWMSG(AHC_WMSG_CFG* pSrcWMSG);
void        AHC_WMSG_GetWMSG(AHC_WMSG_CFG* pDestWMSG);
void        AHC_WMSG_Init(void);

#endif // _AHC_WARNINGMSG_H_
