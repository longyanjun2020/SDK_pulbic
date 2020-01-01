/**
 * @file    http_pub.h
  */
#ifndef __HTTP_PUB_H__
#define __HTTP_PUB_H__

#include "ven_types.h"
/*=============================================================*/
// type and define
/*=============================================================*/
s32 HttpDownloadSendRequest(s32 sRequestType, s32 sParamSize, void *pReqParam);

#endif //__HTTP_PUB_H__
