#ifndef __TUDOU_PORTING_H__
#define __TUDOU_PORTING_H__
#include "mmi_base_util.h"

char *Tudou_GetStorageType(void *pUserData);

char *Tudou_VideoInforPath(void *pUserData);

char *Tudou_GetDownLoadVideoInforPath(void *pUserData);

char *Tudou_GetcPicFilePath(void *pUserData);

char *Tudou_GetDownLoadVideoId(void *pUserData);

char *Tudou_GetDownLoadVideoPath(void *pUserData);

char *Tudou_GetVideoDetailFilePath(void *pUserData);

char *Tudou_GetTempFilePath(void *pUserData);

boolean TuDou_GetIsSignIn(void *pUserData);

char *Tudou_GetCurImsi(void *pUserData);

char *Tudou_GetCurImei(void *pUserData);

boolean *TuDou_GetIsEndKeyPress(void *pUserData);


boolean *TuDou_GetIsWaitComfirm(void *pUserData);


sg_http_session_struct **Tudou_GetHttpJsonSession(void *pUserData);


sg_http_session_struct **Tudou_GetHttpVideoDetailSession(void *pUserData);


sg_http_session_struct **Tudou_GetHttpDownLoadVideoSession(void *pUserData);

sg_http_session_struct **Tudou_GetHttpPicSession(void *pUserData);

sg_http_client_struct *Tudou_GetHttpClient(void *pUserData);

boolean *TuDou_GetIsIsHttpInit(void *pUserData);

char *Tudou_GetCurWapTitle(void *pUserData);

char *Tudou_GetCurWapUrl(void *pUserData);

boolean *TuDou_GetChannelWndDataIsInit(void *pUserData);

VectorClass_t  **Tudou_GetChannelWndDataColumeType(void *pUserData);

u32 *Tudou_GetChannelWndDataCurrentPage(void *pUserData);

df_video_detail_data **Tudou_GetDetailWndDataCurrentPageDetailData(void *pUserData);

//VectorClass_t  *vHotKeyList
VectorClass_t  **Tudou_GetSearchWndDataHotKeyList(void *pUserData);

u32 *Tudou_GetSearchWndDataHotKeyNum(void *pUserData);

VectorClass_t  **Tudou_GetChannelVideoList(void *pUserData);

VectorClass_t  **Tudou_GetVideoList(void *pUserData);

//pThis->uCurrentPage
u32 *TuDou_GetCurrentPage(void *pUserData);

//pThis->nVectorItemNum
u32 *TuDou_GetVectorItemNum(void *pUserData);

void TuDou_CreateTimerWaitRequestData(void *pUserData);

int TuDouGetHotWordPageSize(void);

int TuDouGetMainLcdWidth(void);

int TuDouGetMainLcdHeight(void);

int TuDouGetWndIdStart(void);

int TuDouGetWndIdDetail(void);

int TuDouGetWndIdChannel(void);

#endif

