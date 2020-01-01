/**
 *
 * @file    ven_comdef_priv.h
 * @brief   This file is the collection of common definitions for SDK/MMI internal using
 *
 * @author  Steve.Lee
 * @version $Id: ven_comdef_priv.h 40108 2009-09-12 12:04:25Z code.lin $
 *
 */

#ifndef __VEN_COMDEF_PRIV_H__
#define __VEN_COMDEF_PRIV_H__

/******************************************/
/*           Include files                */
/******************************************/
#include "ven_types.h"
#include "ven_sdk.h"
#include "ven_common_def.h"
#include "ABL_Common.h"
#include "ResMgr_Common.h"

/******************************************/
/*              Definitions               */
/******************************************/

#ifndef ABS
#define ABS(_v) (((_v)<0)?(-(_v)):(_v))
#endif

enum
{
	IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_MIN,
	IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_DEFAULT = IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_MIN,  //All app life cycle, suspend org background audio
	IVEN_BACKGRUNDAUDIO_SUSPEDN_TYPE_ON = IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_DEFAULT,
	IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_OFF,  //Do not suspend  background audio auto 
	IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_MAX =  IVEN_BACKGRIUNDAUDIO_SUSPEND_TYPE_OFF
};
typedef u8 iven_backgroundaudio_e;

// Message parser prototype
typedef void (*VEN_MSG_PARSER_FUNC_PTR)(ven_msg_t MsgID, vm_msg_t *pMessage);

typedef ven_app_id_t iVen_App_ID;

typedef struct
{
	void        *pMediaClient;
    iVen_App_ID appID;
    u8          bForceCPUHigh;
    u8          nStatusBar_TableIndex;
	u8			 nBackgroundAudioSuspendType; //type of iven_backgroundaudio_e
} iVen_Handle_t;

typedef struct
{
    ven_msg_t MsgID;
    VEN_MSG_PARSER_FUNC_PTR pfnMsgParser;
} ven_msg_parser_data_t;

/*  The structures in req/rsp msg header */
typedef struct
{
    void *pCBFunc;
    u32 UserData;
} iVen_Callback_Info_t;

typedef struct
{
    u32 AP_ID;
    bool bSync;
    union
    {
        iVen_Callback_Info_t CbInfo;    ///< for async req
        u32  SemID;                            ///< for sync req
    } Resp;
} iVen_AsyncReq_BodyBase_t;

typedef struct
{
    u32 AP_ID;
    iVen_Callback_Info_t CbInfo;
} iVen_AsyncRsp_BodyBase_t;

enum
{
    CONTENT_OP_NONE = 0,
    CONTENT_OP_ADD,     ///< File is added to DB as a new content due to file creation or attribute change (hidden -> normal)
    CONTENT_OP_DEL,     ///< File is removed from DB due to file delete ot attribute change (hidden -> normal)
    CONTENT_OP_UPDATE_URL,  ///< Update content URL due to file rename/move
    CONTENT_OP_UPDATE_SIZE,  ///< Update content URL size to file write/truncate
    CONTENT_OP_HIDDEN,  ///< Update content due to file attribute change
    CATEGORY_OP_ADD,    ///< Category is added due to directory create
    CATEGORY_OP_DEL,    ///< Category is deleted due to directory remove
};
typedef u8 content_op_t;

/******************************************/
/*         Function declarations          */
/******************************************/
u16 ven_getTaskIDByAppID(iVen_App_ID appId);
void ven_setBacklightStatus(bool bBacklightOn);
u32 ven_handle_getHandleByAppId(ven_app_id_t appId);
bool ven_handle_checkHandleValid(u32 handle);
ResMgr_TaskId_e ven_getResMgrTaskIDByAppID(iVen_App_ID appId);
ResMgr_TaskId_e ven_getResMgrTaskIDBySdkTaskID(VenApp_TaskId_e taskId);
ResMgr_TaskId_e ven_getResMgrTaskIDByTaskID(u16 taskId);
ResMgr_AppId_e ven_getResMgrApIDByAppID(iVen_App_ID appId);
VenApp_TaskId_e ven_getSDKTaskIDByAppID(iVen_App_ID appId);

#endif /* __VEN_COMDEF_PRIV_H__ */
