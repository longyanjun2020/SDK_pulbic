/**
* @file mmi_codecsrv.h
*
* Class Id: CLSID_CODECSRV
**/
#ifndef __MMI_CODECSRV_H__
#define __MMI_CODECSRV_H__

#include "mmi_mae_applet.h"
#include "mmi_class.h"
#include "mmi_mediasrv_common.h"
#include "ABL_GSS.h"

#define CODECSRV_EVT_RESMGR_SUSPEND_IND (CLSID_CODECSRV << 16 | 1)
#define CODECSRV_EVT_RESMGR_RESUME_IND (CLSID_CODECSRV << 16 | 2)

typedef struct
{
    u8 *pBuffer;
    u32 nBufferLen;
} CodecSrvEmuDataBuf_t;

typedef void (*CodecSrvEmuCmnCb)(void *pUserData, MediaSrvErrCode_e eErrCode);
typedef void (*CodecSrvEmuStopCb)(void *pUserData, MediaSrvErrCode_e eErrCode, CodecSrvEmuDataBuf_t *pBuffer);
typedef void (*CodecSrvEmuGetInfoCb)(void *pUserData, MediaSrvErrCode_e eErrCode, u32 nEmuInfo);
typedef void (*CodecSrvInterruptNotify)(void *pUserData, void *pEvtInfo);

typedef ABL_GssRenderConfig_t CodecSrvEmuGameParam_t;
typedef ABL_GssRenderStopConfig_t CodecSrvEmuGameStopParam_t;
typedef ABL_GssRenderInput_t CodecSrvEmuGameSetInputParam_t;
typedef ABL_GssGetInfoParam_t CodecSrvEmuGameGetInfoParam_t;

typedef ABL_GameInfo_t CodecSrvEmuGameInfo_t;

typedef struct
{
    u32 nInstanceId;
    CodecSrvEmuCmnCb pfnCnfCb;
} CodecSrvEmuCmnCbData_t;

typedef struct
{
    u32 nSrvInstance;
    u32 nInstanceId;
    CodecSrvEmuStopCb pfnCnfCb;
} CodecSrvEmuStopCbData_t;

typedef struct
{
    u32 nInstanceId;
    CodecSrvEmuGetInfoCb pfnCnfCb;
    u32 nInfoType;
} CodecSrvEmuGetInfoCbData_t;

typedef struct
{
    u8 nEventGroup;
    u32 nInstanceId;
    u32 nCusData;
    CodecSrvInterruptNotify pfnInterruptNotify;
} CodecSrvInterruptNotifyData_t;

typedef struct
{
    u32 nEvtCode;
    u32 nRetCode;
} CodecSrvInterruptNotify_t;

/**
 * ICAMERASRV Interfaces
 */
#define INHERIT_ICodecSrv(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(ICodecSrv);

#define ICodecSrvQueryInterface(pICntlr, id, pp, po) GET_FUNCTBL((pICntlr), ICodecSrv)->QueryInterface(pICntlr, id, pp, po)
#define ICodecSrvHandleEvent(pICntlr, e, p1, p2) GET_FUNCTBL((pICntlr), ICodecSrv)->HandleEvent(pICntlr, e, p1, p2)

typedef struct
{
    DECLARE_FUNCTBL(ICodecSrv); // function table pointer
    u32 nRefCnt;
    CodecSrvInterruptNotifyData_t *pInterruptNotifyData;
} CodecSrv_t;

MAE_Ret CodecSrvNew(MAE_ClsId id, void **ppObj);

/************************************************************************/
/* Codec Emugame Service Interface                                      */
/************************************************************************/
MAE_Ret CodecSrvEmuGameStart(CodecSrv_t *pICodecSrv, u32 nInstanceId, CodecSrvEmuGameParam_t *pParam, CodecSrvEmuCmnCb pfnCodecSrvCB);
MAE_Ret CodecSrvEmuGameStop(CodecSrv_t *pICodecSrv, u32 nInstanceId, CodecSrvEmuGameStopParam_t *pParam, CodecSrvEmuStopCb pfnCodecSrvCB);
MAE_Ret CodecSrvEmuGameSetInput(CodecSrv_t *pICodecSrv, u32 nInstanceId, CodecSrvEmuGameSetInputParam_t *pParam, CodecSrvEmuCmnCb pfnCodecSrvCB);
MAE_Ret CodecSrvEmuGameGetInfo(CodecSrv_t *pICodecSrv, u32 nInstanceId, CodecSrvEmuGameGetInfoParam_t *pParam, CodecSrvEmuGetInfoCb pfnCodecSrvCB);
MAE_Ret CodecSrvEmuGameCleanUp(CodecSrv_t *pICodecSrv, u32 nSrvClient, CodecSrvEmuCmnCb pfnCodecSrvCB);
MAE_Ret CodecSrvEmuOpenSession(CodecSrv_t *pICodecSrv, u32 nInstanceId);
MAE_Ret CodecSrvEmuCloseSession(CodecSrv_t *pICodecSrv, u32 nInstanceId);
MAE_Ret CodecSrvSetInterruptNotifyCb(CodecSrv_t *pICodecSrv, u32 nInstanceId, CodecSrvInterruptNotify pfnInterruptNotify);

#endif /* __MMI_CODECSRV_H__ */
