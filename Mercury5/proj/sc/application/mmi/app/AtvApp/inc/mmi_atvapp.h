////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_atv.h
* @version
* @brief   ATV header file
*
*/
#ifndef __MMI_ATVAPP_H__
#define __MMI_ATVAPP_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"

#include "mmi_tvsrv_def.h"
#include "mmi_atvapp_id.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define     MMI_ATVAPP_DEFAULT_CHANNEL	        2
#define     MMI_ATVAPP_DEFAULT_VOUME	        5
#define     MMI_ATVAPP_DEFAULT_RATIO		    TVSRV_RATIO__4_3
#define     MMI_ATVAPP_DEFAULT_REGION		    TVSRV_TV_REGION__CHINA
#define     MMI_ATVAPP_DEFAULT_REGION_INDEX	    0

#ifdef __LCM_QCIF_PLUS__
#define     MMI_ATVAPP_DEFAULT_CAPTURE_SIZE     TVSRV_CAP_RES__QCIF_PLUS_220_176
#else
#define     MMI_ATVAPP_DEFAULT_CAPTURE_SIZE     TVSRV_CAP_RES__QVGA_320_240
#endif

#define     MMI_ATVAPP_DEFAULT_CAPTURE_SOUND    TVSRV_TV_CAPTURE_SOUND__ON
#define     MMI_ATVAPP_DEFAULT_CAPTURE_QUALITY  TVSRV_IMG_QUALITY__NORMAL
#define     MMI_ATVAPP_DEFAULT_SHOT_MODE		TVSRV_TV__SINGLE
//#define     MMI_ATVAPP_DEFAULT_CAPTURE_STORAGE  IATV_TV_STORAGE_CARD
#define     MMI_ATVAPP_DEFAULT_SOUND_PATH		TVSRV_SOUND_PATH__DOWNLOAD

#ifdef __ATV_CMMB__
#define     MMI_ATVAPP_CHANNEL_MAX			    128//512
#else
#define     MMI_ATVAPP_CHANNEL_MAX			    118
#endif
#define     MMI_ATVAPP_VOLUME_MAX			    8
#define     MMI_ATVAPP_VOLUME_MIN			    0
#define     MMI_ATVAPP_FUPDATE_SCREEN_TIMER	    1
#define     MMI_ATVAPP_IUPDATE_SCREEN_TIMER	    500
#define     MMI_ATVAPP_WATCH_CONTROLBAR         10000
#define     MMI_ATVAPP_WATCH_VOLUMEBAR          10000
#define     MMI_ATVAPP_WATCH_DLG			    2000
#define     MMI_ATVAPP_CAPTURE_DLG			    500
#define     MMI_ATVAPP_STATUS_TIMER			    5000
#define     MMI_ATVAPP_MESSAGE_MAX			    100
//#define		MMI_ATVAPP_CAPTURE_PATH 		    L"Pictures/TV"

#if defined(__LCM_LANDSCAPE__)
#define     MMI_ATVAPP_DEFAULT_ROTATE		    TVSRV_ROTATE__NONE
#define     ATVAPP_DISPMODE DISPMODE_PORTRAIT_ONLY
#else
#define     MMI_ATVAPP_DEFAULT_ROTATE		    TVSRV_ROTATE__90
#define     ATVAPP_DISPMODE DISPMODE_LANDSCAPE_ONLY
#endif
#ifdef __ATV_CMMB__
#define     MMI_ATVAPP_ESG_BUFFER_SIZE    (60*1024)
#define     MMI_ATVAPP_CAT_BUFFER_SIZE    512
#define     MMI_ATVAPP_CACARDNUM_BUFFER_SIZE     8
#define     MMI_ATVAPP_TIME_SLOT_LENGTH  5
#define     MMI_ATVAPP_PROGRAM_BEGIN  600
#define     MMI_ATVAPP_PROGRAM_END  690
#define     MMI_ATVAPP_BROADCAST_BEGIN  700
#define     MMI_ATVAPP_BROADCAST_END  800
#define     MMI_ATVAPP_DISPLAY_OUTPUT_LEFT  0
#define     MMI_ATVAPP_DISPLAY_OUTPUT_TOP  0
#define     MMI_ATVAPP_DISPLAY_OUTPUT_WIDTH  320
#define     MMI_ATVAPP_DISPLAY_OUTPUT_HEIGHT  240
#endif

typedef enum
{
    ATVAPP_SEARCH_TYPE_SERVICE = 1,
    ATVAPP_SEARCH_TYPE_SERVICEAUX,
    ATVAPP_SEARCH_TYPE_SCHEDULE,
    ATVAPP_SEARCH_TYPE_CONTENT,
    ATVAPP_SEARCH_TYPE_SERVICEPARA
} AtvSearchType_e;

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    u32	  nCityLabelId;
    u32   nFrequentPoint;
    u16   nFrequentPointDisplay;
    u16   nChannelNumber;
} ATVFrequenyPoint_t;

typedef struct
{
	u32				  u32ChannelNum;
	u32				  u32ChannelMax;
	TvSrvRegion_e	  eLastArea;
	u32				  u32LastChannelIndex;
	u8				  u8LastVolume;
	TvSrvRatio_e	  eLastRatio;
	TvSrvRotate_e	  eLastRotate;
	TvSrvRegion_e	  eLastRegion;
	u16				  u16LastRegionIndex;
	TvSrvRegion_t	  tLastRegion;
}ATVInfo_t;

#ifdef __ATV_CMMB__
typedef struct
{
    u32             nFrequency;
    u32             nProgramServiceID;
    u8              nProgramServiceTimeSlot[MMI_ATVAPP_TIME_SLOT_LENGTH];
    u32             nEmmServiceID;
    u8              nEmmServiceTimeSlot[MMI_ATVAPP_TIME_SLOT_LENGTH];
    MAE_WChar       u16ChannelName[MMI_ATVAPP_CHANNEL_NAME_MAX+1];
} ATVFrequency_t;
#endif

typedef struct
{
#ifdef __ATV_CMMB__
    ATVFrequency_t tFrequency;
#endif
	MAE_WChar   u16ChannelName[MMI_ATVAPP_CHANNEL_NAME_MAX+1];
}ATVChannelInfo_t;

typedef struct
{
	u32               u32ChannelIndex[MMI_ATVAPP_CHANNEL_MAX];
	ATVChannelInfo_t  tChannelInfo[MMI_ATVAPP_CHANNEL_MAX];
}ATVChannelsInfo_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret AtvAppNew
(
    MAE_ClsId   nClsId,
    void        **ppObj
);
#endif /* __MMI_ATVAPP_H__ */
