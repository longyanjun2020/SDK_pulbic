/**
* @file    mmi_srv_client_commondefine.h
* @brief
*
*
* @author
* @version $Id: mmi_common_dialog.h 33169 2009-06-12 05:19:42Z collin.chiang $
*/

#ifndef __MMI_SRV_CLIENT_COMMONDEFINE_H__
#define __MMI_SRV_CLIENT_COMMONDEFINE_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_model.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_config.h"
/*-----------------------------------------------------*/

/// Add by SrvCore
#define CUS_MBX_SRV (0XFF)

//1-1 mapping with MAE_RET_XXX
typedef enum
{
    SRVCLIENT_RET_SUCCESS = 0, ///< operation completed successfully
    SRVCLIENT_RET_BAD_PARAM = 1, ///< invalid input parameters
    SRVCLIENT_RET_FAILED = 2, ///< WHAT? every code here is failed
    SRVCLIENT_RET_OUT_OF_MEMORY = 3, ///< memory is not enough to complete the operation
    SRVCLIENT_RET_NOT_SUPPORTED = 4, ///< the request is not supported
    //SRVCLIENT_RET_IID_NOTSUPPORTED        = 5, // use SRVCLIENT_RET_NOT_SUPPORTED instead
    // SRVCLIENT_RET_CLSID_NOT_SUPPORTED    = 6, // use SRVCLIENT_RET_NOT_SUPPORTED instead
    SRVCLIENT_RET_NOT_READY = 7,
    SRVCLIENT_RET_NOT_FOUND = 8, ///< the specified item is not found
    SRVCLIENT_RET_NOT_EMPTY = 9, ///< the content is not empty
    SRVCLIENT_RET_BUSY = 10,
    SRVCLIENT_RET_FS_FULL = 11,
    SRVCLIENT_RET_NOT_FIND_CLIENT = 12, ///< Do not find the Service Client

    SRVCLIENT_RET_NO_MORE_INSTANCES = 16, ///< the number of instances exceeds the system limit
    SRVCLIENT_RET_EVENT_QUEUE_FULL = 17, ///< shell's event queue is full
    SRVCLIENT_RET_ILLEGAL_OPERATION = 18, ///< the operation is not allowed; eg: posting events to an unrelated object,
    ///< or starting an embedded applet when it is not the focused applet
    SRVCLIENT_RET_UNHANDLED_EVENT = 19, ///< the event is not handled by the destination object
    SRVCLIENT_RET_APM_QUEUE_FULL = 20, ///< APM's action queue is full
    SRVCLIENT_RET_NO_MORE_APPLETS = 21, ///< the number of applets exceeds the limit
    SRVCLIENT_RET_UNHANDLED_MESSAGE = 22, ///< the rtk message doesn't have a registered handler
    SRVCLIENT_RET_DUPLICATE_HANDLER = 23, ///< trying to register an existing message handler again

    SRVCLIENT_RET_FILE_EXISTS = 32, ///< file exists
    SRVCLIENT_RET_FS_PHYSICAL_ERROR = 33, ///< physical error on file system
    SRVCLIENT_RET_FOLDER_NOT_FOUND = 34, ///< folder not found

    SRVCLIENT_RET_MEDIA_ALREADY_PLAYING = 48, ///< We cannot play a media file if it is already playing
    SRVCLIENT_RET_MEDIA_ALREADY_STOPPED = 49, ///< We cannot stop a media file if it is already stopped
    SRVCLIENT_RET_MEDIA_REJECT = 50, ///< There is other clients occupying media resousrce.
    SRVCLIENT_RET_MEDIA_INVALID_CLIENT = 51, ///< The client is invalid or already removed
    SRVCLIENT_RET_RESCTRL_RESOURCE_OCCUPIED = 52, ///< Cannot obtain the control of resource since there's someone use it with higer priority
    SRVCLIENT_RET_RESCTRL_ILLEGAL_USAGE = 53, ///< Cannot obtain the control because it already owns other resource
    SRVCLIENT_RET_RESCTRL_RESOURCE_WAITING = 54, ///< Cannot obtain the control,  but it is inserted to waiting queue.
    SRVCLIENT_RET_RESCTRL_REJECT = 55, ///< Cannot get resctrl while it is in unconfirmed suspend state
    SRVCLIENT_RET_CAMERA_REJECT = 56,  ///< the giving camera command is rejected by EMA
    SRVCLIENT_RET_TASKDB_NOMORE = 57, ///Change to next task in the list. If the current is the latest one, it should return TASKDB_NOMORE and nothing happens.

    SRVCLIENT_RET_RECORD_FULL = 61,///<phb's phiscal index is full
    SRVCLIENT_RET_NOT_MATCH = 62///<When the status is different between sorting table and contacts
} Srv_Ret;

typedef enum Srv_TaskId_e_
{
    SRV_CLIENT_TASK_ID__MMI,
    SRV_CLIENT_TASK_ID__JAVA,
    SRV_CLIENT_TASK_ID__IPTV,
    SRV_CLIENT_TASK_ID__WAP,
    SRV_CLIENT_TASK_ID__MMS,
    SRV_CLIENT_TASK_ID__SDK,
    SRV_CLIENT_TASK_ID__RES_MGR,
    SRV_CLIENT_TASK_ID__SERVICE,
    SRV_CLIENT_TASK_ID__SDK1,
    SRV_CLIENT_TASK_ID__SDK2,
    SRV_CLIENT_TASK_ID__SDK3,
    SRV_CLIENT_TASK_ID__SDK4,
    SRV_CLIENT_TASK_ID__SDK5,
    SRV_CLIENT_TASK_ID__NUM,
    SRV_CLIENT_TASK_ID__INVALID = 0xFF
} Srv_TaskId_e;


typedef enum Srv_AppId_e_
{
    SRV_CLIENT_APP_ID__BEGIN = 0,
    SRV_CLIENT_APP_ID__MMI_ALL = SRV_CLIENT_APP_ID__BEGIN,
    SRV_CLIENT_APP_ID__CCMTA,
    SRV_CLIENT_APP_ID__CCAPP,
    SRV_CLIENT_APP_ID__FILEMGR,
    SRV_CLIENT_APP_ID__PHB,
    SRV_CLIENT_APP_ID__POWEROFF,
    SRV_CLIENT_APP_ID__POWERON,
    SRV_CLIENT_APP_ID__PROFILE,
    SRV_CLIENT_APP_ID__SETTING,
    SRV_CLIENT_APP_ID__COUNTDOWNTIMER,
    SRV_CLIENT_APP_ID__EBOOK,
    SRV_CLIENT_APP_ID__EM,
    SRV_CLIENT_APP_ID__VENDOR,
    SRV_CLIENT_APP_ID__MPLAYER,
    SRV_CLIENT_APP_ID__VIDEOPLAYER,
    SRV_CLIENT_APP_ID__VOICEMEMO,
    SRV_CLIENT_APP_ID__EMUGAME,
    SRV_CLIENT_APP_ID__NATIVEGAME,
    SRV_CLIENT_APP_ID__FMRADIO,
    SRV_CLIENT_APP_ID__CAMERA,
    SRV_CLIENT_APP_ID__IPTV,
    SRV_CLIENT_APP_ID__EVENTCENTER,
    SRV_CLIENT_APP_ID__ATV,
    SRV_CLIENT_APP_ID__USB,
    SRV_CLIENT_APP_ID__JAVA,
    SRV_CLIENT_APP_ID__RES_MGR,
    SRV_CLIENT_APP_ID__SERVICE,
    SRV_CLIENT_APP_ID__SYS,
    SRV_CLIENT_APP_ID__KEYPAD,
    SRV_CLIENT_APP_ID__STK,
    SRV_CLIENT_APP_ID__MMS,
    SRV_CLIENT_APP_ID__AVR,
    SRV_CLIENT_APP_ID__SDK1,
    SRV_CLIENT_APP_ID__SDK2,
    SRV_CLIENT_APP_ID__SDK3,
    SRV_CLIENT_APP_ID__SDK4,
    SRV_CLIENT_APP_ID__SDK5,
    SRV_CLIENT_APP_ID__NUM,
    SRV_CLIENT_APP_ID__INVALID = 0xFF
} Srv_AppId_e;


/************************************************************************/
/* Important Note: [To add a new Service Type in ServiceType_e]

   After adding a new Service Type here,programmers must add a
   corresponding element in gSrvCreateInfo[] defined in mmi_srv_client.c

   Fail to follow the rule, the simulator will be aborted when any service client can not be found.
   */
/************************************************************************/

typedef enum
{
    SERVICEMIN = 0,
    ACCESSORYSERVICE = SERVICEMIN,
    FILEMGRSERVICE,
    FSTREAMSERVICE,
    USBSERVICE,
    CORESERVICE,
    CFGSERVICE,
    MOISERVICE,
    MCISERVICE,
    SMSSERVICE,
    PHBSERVICE,
    CCSERVICE,
    CALLLOGSERVICE,
    CPHSSERVICE,
    SSSERVICE,
    SMSTXSERVICE,
    CBSSERVICE,
    MMSSERVICE,
    MMSTXSERVICE,
    MSGMGRSERVICE,
    FDNSERVICE,
    BTSERVICE,
    GPSSERVICE,
    BATTERYSERVICE,
    IMAGEMAKERSERVICE,
    CAMERASERVICE,
    TVSERVICE,
    OBJPROCESSINGSERVICE,
    CONFIGSERVICE,
    TOUCHSERVICE,
    FMRADIOSERVICE,
    ALIVEWDGSERVICE,
    EVTCENTERSERVICE,
    EVENTDBSERVICE,
    PROFILESERVICE,
    CLOCKSERVICE,
    SIMSERVICE,
    AUDIOPLAYERSERVICE,
    PLAYLISTSERVICE,
    MOTIONDETECTORSERVICE,
    SHORTCUTSERVICE,
//    THEMEMGR,
    PEDOMETERSERVICE,
    PREVIEWLINE2SERVICE,
    TASKDB,
    TASKDBMGR,
    BTOBEXSERVICE,
    ATSYNCSERVICE,
    CLIPBOARDSERVICE,
    SENSORMGR,
    VPARAMSERVICE,
    VPROPERTYSERVICE,
    VEVENTSERVICE,
    VCALENDARSERVICE,
    ALARMSERVICE,
    STKSERVICE,
    VCALSTORESERVICE,
    VENDORSERVICE,
    TOUCHSHORTCUTSERVICE,
    JAVASERVICE,
#ifdef __EMAIL_MMI__
	EMAILSERVICE,
#endif
#ifdef __NCCQQ_MMI__
	QQSERVICE,
#endif
    MMSERVICE,
    AUDIORECORDERSERVICE,
    AUDIOENVSERVICE,
    AUDIOSERVICE,
    VIDEOSERVICE,
    CODECSERVICE,
    VOICECALLSERVICE,
	VFSFILEMGRSERVICE,
    WLANSERVICE,
    SOCKETSERVICE,
	TTSSERVICE,
    CLSERVICE,
    VTCCSERVICE,
    VTMSERVICE,
    COUNTDOWNTIMERSERVICE,
    SCHEDULERSERVICE,
	PRIVATEPROTECTSERVICE,
//
    DRMAGENTSERVICE,
//	
    SERVICEMAX
} ServiceType_e;

/*=====================================
Srv App IndType to CB Module Definition
======================================*/
#define MAXSRVCLIENTNUM 30

typedef struct SrvCBNode_TAG
{
    struct SrvCBNode_TAG *pPrev;
    u32 IndType;
    void *EvToCBFunc;
    void *CastParaToCBFunc;
    u32 nExternInfo;
    struct SrvCBNode_TAG *pNext;
} SrvCBNode_t;

typedef struct SrvCBListModule_TAG
{
    SrvCBNode_t *pSrvCBNode;
} SrvCBListModule_t;


/*=====================================
Srv Client Definition
======================================*/
#define SRVMASKALL 0xFFFFFFFF

typedef struct SrvClient_TAG
{
    struct SrvClient_TAG *pPrev;
    Srv_TaskId_e eClientTask;
    Srv_AppId_e eClientAPID;
    SrvCBListModule_t *pAppCbModule;
    u32 *pInstance;
    u32 *pService;
    u32 nSrvClientFlag;
    void *SrvListener;
    u32 nModelListenerMask; // temp use for Srv model lisenter; replace AP's effert
	u32	*pClientData;
    struct SrvClient_TAG *pNext;
} SrvClient_t;


typedef struct SrvClientRoot_TAG
{
    ServiceType_e eSrvType;
    u32 *pSrvData;
    SrvClient_t *pNext;
} SrvClientRoot_t;


typedef struct SrvTaskArray_TAG
{
    SrvClientRoot_t SrvClientRoot[SERVICEMAX];
} SrvTaskArray_t;


typedef struct SrvClientTaskInfo_TAG
{
    SrvTaskArray_t *pSrvTaskArray;
    s32 nClientTask;
} SrvClientTaskInfo_t;

typedef MAE_Ret (*SRV_Create)(SrvClient_t *pClient, s32 *pData);
typedef MAE_Ret (*SRV_Destroy)(SrvClient_t *pClient, s32 *pData);

typedef struct SrvCleintCreate_TAG
{
    ServiceType_e eServType;
    SRV_Create pfnCreate;
    SRV_Destroy pfnDestroy;
} SrvCleintCreate_t;


//Generic func
Srv_TaskId_e SrvClientGetTaskIdByAppId(Srv_AppId_e eAppId);

#endif //__MMI_SRV_CLIENT_COMMONDEFINE_H__
