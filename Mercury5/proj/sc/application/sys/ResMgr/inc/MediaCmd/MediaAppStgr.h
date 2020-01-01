/**
* @file MediaAppStgr.h
*
* This header file defines the interfaces of media app command
* tStgr
*/

#ifndef __MEDIAAPPSTGR_H__
#define __MEDIAAPPSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_AppStgr.h"
#include "MediaCmn.h"
#include "MediaUtil.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaRingBuffInfo_e_
{
    MEDIA_RINGBUFF_INFO__BODY_SIZE = 0,
    MEDIA_RINGBUFF_INFO__FREE_SPACE,
    MEDIA_RINGBUFF_INFO__FILLED_SIZE,
    MEDIA_RINGBUFF_INFO__STREAMING_HDL,
} MediaRingBuffInfo_e;

typedef struct MediaRingBuffInitCtrl_t_
{
    ResMgr_AppId_e eAppId;
	ResMgr_RingBuff_t *pRingBuffInfo;
    u32 uBuffBodySize;
} MediaRingBuffInitCtrl_t;

typedef struct MediaRingBuffUninitCtrl_t_
{
    ResMgr_AppId_e eAppId;
	ResMgr_RingBuffHdl_t pRingBuffHdl;
} MediaRingBuffUninitCtrl_t;

typedef struct MediaRingBuffPushCtrl_t_
{
    ResMgr_AppId_e eAppId;
	ResMgr_RingBuffHdl_t pRingBuffHdl;
	void *pUserData;
	u32 uDataSize;
	ResMgr_ErrorCode_e *pResult;
} MediaRingBuffPushCtrl_t;

typedef struct MediaRingBuffPopCtrl_t_
{
    ResMgr_AppId_e eAppId;
	ResMgr_RingBuffHdl_t pRingBuffHdl;
	void *pUserData;
	u32 uDataSize;
	ResMgr_ErrorCode_e *pResult;
} MediaRingBuffPopCtrl_t;

typedef struct MediaRingBuffGetInfoCtrl_t_
{
    ResMgr_AppId_e eAppId;
	ResMgr_RingBuffHdl_t pRingBuffHdl;
	MediaRingBuffInfo_e eInfoType;
	u32 *pOutVal;
} MediaRingBuffGetInfoCtrl_t;

typedef struct MediaRingBuffSetDataEndCtrl_t_
{
    ResMgr_AppId_e eAppId;
    ResMgr_RingBuffHdl_t pRingBuffHdl;
} MediaRingBuffSetDataEndCtrl_t;

typedef struct MediaRetrieveBuffInfoCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_Format_e eDataFormat;
    void *pUserData;
    u32 uDataSize;
    u8 *pCacheBuf;
    Media_AudCodecInfo_t *pCodecInfo;
    ResMgr_ErrorCode_e *pResult;
} MediaRetrieveBuffInfoCtrl_t;

typedef struct MediaRingBuffInfo_t_
{
    u8 *pOriBuffAddr;
    u32 uBuffSize;
    u32 uBuffHandle;
} MediaRingBuffInfo_t;

typedef struct MediaAppStgr_t_
{
    ResMgr_AppStgr_t tAppStgr;
} MediaAppStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffInitReq(ResMgr_AppId_e eAppId, ResMgr_RingBuff_t *pRingBuffInfo, u32 uBufferBodySize);
bool MediaAppStgr_HandleRingBuffInit(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffUninitReq(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl);
bool MediaAppStgr_HandleRingBuffUninit(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffPushReq(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, void *pUserData, u32 uDataSize, ResMgr_ErrorCode_e *pResult);
bool MediaAppStgr_HandleRingBuffPush(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffPopReq(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, void *pUserData, u32 uDataSize, ResMgr_ErrorCode_e *pResult);
bool MediaAppStgr_HandleRingBuffPop(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffGetInfoReq(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, MediaRingBuffInfo_e eInfoType, u32 *pOutVal);
bool MediaAppStgr_HandleRingBuffGetInfo(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRingBuffSetDataEndReq(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl);
bool MediaAppStgr_HandleRingBuffSetDataEnd(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaAppStgr_CreateRetrieveBuffInfoReq(ResMgr_AppId_e eAppId, Media_Format_e eDataFormat, void *pUserData, u32 uDataSize, u8 *pCacheBuf, Media_AudCodecInfo_t *pCodecInfo, ResMgr_ErrorCode_e *pResult);
bool MediaAppStgr_HandleRetrieveBuffInfo(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

#endif //__MEDIATASKSTGR_H__

