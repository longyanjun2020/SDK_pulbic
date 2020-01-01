/**
* @file mmi_audiosrv_priv.h
*
* Class Id: CLSID_AUDIOSRV
*
* @version $Id:
*/
#ifndef __MMI_AUDIOSRV_PRIV_H__
#define __MMI_AUDIOSRV_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_audiosrv.h"
#include "mmi_usbsrv.h"
#include "mmi_drmagentsrv.h"
#include "DlistItf.h"
/*-------------------------------------------------------------------------*/

typedef enum AudioSrvNotifyType_e_
{
    AUDIOSRV_NOTIFY__PLAYSTATUS = 0
   ,AUDIOSRV_NOTIFY__INTERRUPT
   ,AUDIOSRV_NOTIFY__ACCESSORY
   ,AUDIOSRV_NOTIFY__SPECTRUM
} AudioSrvNotifyType_e;

typedef enum AudioSrvPlayerStatus_e_
{
    AUDIOSRV_STATUS__IDLE
   ,AUDIOSRV_STATUS__PLAY
   ,AUDIOSRV_STATUS__PAUSE
} AudioSrvPlayerStatus_e;

typedef struct AudioSrvCbData_t_
{
    u32 nSrvInstId;
    u32 nAppInstId;
    u16 nAppId;
    u32 nCusData;
    void *pfnCallBack;
} AudioSrvCbData_t;

typedef struct AudioSrvClientItem_t_
{
    AudioSrvNotifyType_e eNotifyType;
    u32 nAppInstId;
    u32 nCusData;
    void *pfnCallBack;
    struct AudioSrvClientItem_t_ *pNext;
} AudioSrvClientItem_t;

typedef struct AudioSrv_t_
{
    DECLARE_FUNCTBL(IAUDIOSRV); // function table pointer
    u32 nRefCnt;     // reference count
    IUSBSRV *pIUSBSrv;
#ifdef __MMI_OMA_DRM_V1__
    IDRMAGENTSRV *pIDRMAGENTSrv;
#endif
    ModelListener_t tUSBListener;
    MAE_WChar *pPlayingURL;     // Playing URL
    u32 nPlayPosition;
    AudioSrvPlayMode_e ePlayMode;
    boolean bIsRegistered;
    boolean bPowerConsumptionStatus;
    boolean bIsSessionOpened;
    boolean bIsReset;
	AudioSrvPlayerStatus_e ePlayerStatus;   // Keep the status of player.
	AudioSrvPlayerStatus_e eSuspendStatus;  // Keep the status of player while being suspended.
    void *pAppInstance;             // The pointer to hold APP instance
    u16 nAppId;
    u32 nCusData;
    void *pfnCallBack;
    AudioSrvClientItem_t *pClientItemTable;
    DList_t *pPlayCbData;
} AudioSrv_t;

/*-------------------------------------------------------------------------*/
#endif /* __MMI_AUDIOSRV_PRIV_H__ */
