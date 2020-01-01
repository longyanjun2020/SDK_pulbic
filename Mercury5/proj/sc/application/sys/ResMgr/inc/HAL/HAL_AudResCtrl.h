/**
* @file HAL_AudioPathCtrl.h
*
* This header file defines the APIs of audio path controller
* in HW adaptor layer
*/

#ifndef __HAL_AUDPATHCTRL_H__
#define __HAL_AUDPATHCTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "HAL_AudResCtrlItf.h"
#include "ResMgr_CmdMgrStgrItf.h"
#include "DataStructItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define MCHAN(_CHAN1_,_CHAN2_) \
        (1 << (AUD_CHAN__##_CHAN1_ * AUD_CHAN__NUM + AUD_CHAN__##_CHAN2_))

#define IS_ALLOW_MUL_CHAN(_FALG_,_CHAN1_,_CHAN2_) \
        (_FALG_ & (1 << (_CHAN1_ * AUD_CHAN__NUM + _CHAN2_)))

//Allow Voice / Stereo channel (Any App) + Voice channel (Keypad)
#define ALLOW_KPD_CHAN                  0x0019

#define GET_RES_ID(_APP_ID_, _CHAN_)    ((_CHAN_) * RES_MGR_APP_ID__NUM + (_APP_ID_))
#define GET_CHAN(RES_ID)                ((RES_ID) / RES_MGR_APP_ID__NUM)
#define GET_APP_ID(RES_ID)              ((RES_ID) % RES_MGR_APP_ID__NUM)
#define AUD_DEFAULT_VOL_RANGE           8

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum AudDev_e_
{
    AUD_DEVICE__HEADSET,
    AUD_DEVICE__BT_HEADSET,
    AUD_DEVICE__SPEAKER,
    AUD_DEVICE__NUM
} AudDev_e;

typedef struct AudChanResInfo_t_
{
    u16 uResNum;
    AudChannel_e const *pChannelInfo;
} AudChanResInfo_t;

typedef struct AudResCtrl_TravData_t_
{
    AudChannel_e eNewReqChannel;
    u16 uNewReqAppId;
    u16 uNewReqResID;
    ResCtrlHandle_t pConflictResCtrlHdl;
    bool bConflict;
} AudResCtrl_TravData_t;

/*
    RM will decide which pref path that user want to follow according to this defined value.
    For example, if user set AUD_PREF_PATH_OPT__FOLLOW_CC in ResMgr_AppIdPathConfig,
    rm will only follow cc pref path and won't fallow fm radio pref path.
    Because cc is 1st priority, rm will follow cc pref path with any Opt setting.
*/
#define AUD_PREF_PATH__CC 0x02
#define AUD_PREF_PATH__FM 0x04
#define AUD_PREF_PATH__EM 0x08
#define AUD_PREF_PATH__VT 0x10

#define AUD_PREF_PATH_OPT__NOT_FOLLOW    0x00
#define AUD_PREF_PATH_OPT__NEW_PREF      0x01
#define AUD_PREF_PATH_OPT__FOLLOW_CC     (AUD_PREF_PATH__CC)
#define AUD_PREF_PATH_OPT__FOLLOW_FM     (AUD_PREF_PATH__FM | AUD_PREF_PATH__CC)
#define AUD_PREF_PATH_OPT__FOLLOW_EM     (AUD_PREF_PATH__EM | AUD_PREF_PATH__CC)
#define AUD_PREF_PATH_OPT__FOLLOW_VT     (AUD_PREF_PATH__VT | AUD_PREF_PATH__CC)
#define AUD_PREF_PATH_OPT__FOLLOW        0XFE

#define AUD_PREF_PATH_OPT__FOLLOW_EX_CC (AUD_PREF_PATH_OPT__FOLLOW ^ AUD_PREF_PATH__CC)
#define AUD_PREF_PATH_OPT__FOLLOW_EX_FM (AUD_PREF_PATH_OPT__FOLLOW ^ AUD_PREF_PATH__FM)

typedef AudPath_e (*GetDefPath)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);
typedef void (*UpdatePrefPath)(CmdMgrStgrHdl_t pStgrHdl, void *pItem);
typedef void (*ClearPrefPath)(CmdMgrStgrHdl_t pStgrHdl, void *pItem);
typedef void (*MaskDevStatus)(CmdMgrStgrHdl_t pStgrHdl, u16 *pSpeakerStatus, u16 *pHeadsetStatus, u16 *pBtHeadsetStatus);

typedef void (*SetPathConfig)(ResMgr_AppId_e eAppId, ResMgr_ConfigId_e eConfigId);

typedef struct AudPrefPathItem_t_
{
    ResMgr_AppId_e eAppId;
    AudPath_e ePath;
    MediaResInfo_e eMediaFormat;
} AudPrefPathItem_t;

typedef struct AudPrefPathOp_t_
{
    UpdatePrefPath UpdatePath;
    ClearPrefPath ClearPath;
} AudPrefPathOp_t;

typedef bool const *AudMultiChanInfo_t;

typedef struct ResMgr_AppIdPathConfig_t_
{
    bool                    bUseNormalPath;
    u8                      nPrefPathOpt;
    const AudPath_e         *gAppNormalPath;
    const AudPath_e         *gAppSpecPath;
    const GetDefPath        pfnGetDefPath;
    const AudPrefPathOp_t   gAppUpdatePrefPath;
    AudMultiChanInfo_t      gMultiChan[RES_MGR_APP_ID__NUM+1];  /* Add 1 for guard pattern */
}ResMgr_AppIdPathConfig_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__HAL_AUDPATHCTRL_H__

