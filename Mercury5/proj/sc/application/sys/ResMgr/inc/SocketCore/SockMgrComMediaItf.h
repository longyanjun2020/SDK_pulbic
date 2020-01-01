#ifndef _SOCKMGR_COMMEDIA_ITF_H_
#define _SOCKMGR_COMMEDIA_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrComMediaMgrItf.h"
#include "SockMgrResItf.h"
#include "SockMgrBearerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
	SockMgr_Res_e eResType  ;
	u16 uOwnerNum;
	SockMgr_ComMedia_e eComMediaID;
	u32 uSrcMailBox;
	u32 uDestMailBox;
	u8  uMaxChannelNum;
}SockMgr_ComMediaCreateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
SockMgr_ComMediaHdl_t SockMgr_ComMediaFactory_CreateComMedia(SockMgr_ComMediaCreateData_t *psCreateComMediaData) ;
void SockMgr_ComMediaFactory_DestroyComMedia(SockMgr_ComMediaHdl_t hComMedia);
SockMgr_ComMedia_e SockMgr_ComMedia_GetComMediaID(SockMgr_ComMediaHdl_t hComMedia) ;
u32  SockMgr_ComMedia_GetMailBoxID(SockMgr_ComMediaHdl_t hComMedia) ;
bool SockMgr_ComMedia_IsSupportBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_Bearer_e eBearer) ;
s32 SockMgr_ComMedia_PostMessage(SockMgr_ComMediaHdl_t hComMedia, void *pvMsg) ;
__SLDPM_FREE__ bool SockMgr_ComMedia_IsUsed(SockMgr_ComMediaHdl_t hComMedia) ;
bool SockMgr_ComMedia_GetBindBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t *phOwnerBearer) ;
bool SockMgr_ComMedia_BindBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer) ;
bool SockMgr_ComMedia_UnBindBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer);
bool SockMgr_ComMedia_IsChannelOwner(SockMgr_ComMediaHdl_t hComMedia, u32 uOwner, u8 *puChannelIdx);
bool SockMgr_ComMedia_IsChannelWaitRsp(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum, ResMgr_AppId_e eAppId, u32 uWaitFlag);
bool SockMgr_ComMedia_IsChannelWaitAnyRsp(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum, u32 uWaitFlag);
bool SockMgr_ComMedia_IsChannelSetWaitRsp(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum, ResMgr_AppId_e eAppId, u32 uWaitFlag);
void SockMgr_ComMedia_ChannelSetWaitRsp(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum, ResMgr_AppId_e eAppId, u32 uWaitFlag);
void SockMgr_ComMedia_ChannelReSetWaitRsp(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum, ResMgr_AppId_e eAppId, u32 uWaitFlag);
u32  SockMgr_ComMedia_GetChannelOwner(SockMgr_ComMediaHdl_t hComMedia, u8 uChannelNum);
bool SockMgr_ComMedia_OccupyChannel(SockMgr_ComMediaHdl_t hComMedia, u32 uOwner, u32 *puChannel);
bool SockMgr_ComMedia_RelChannel(SockMgr_ComMediaHdl_t hComMedia, u32 uOwner, u32 *puChannel);
u8 SockMgr_ComMedia_GetClientID(SockMgr_ComMediaHdl_t hComMedia);
u8 SockMgr_ComMedia_GetMaxChannelNum(SockMgr_ComMediaHdl_t hComMedia);
u8 SockMgr_ComMedia_GetUsedChannelNum(SockMgr_ComMediaHdl_t hComMedia);
u8 SockMgr_ComMedia_GetRemainChannelNum(SockMgr_ComMediaHdl_t hComMedia);

#endif/* _SOCKMGR_COMMEDIA_ITF_H_ */
