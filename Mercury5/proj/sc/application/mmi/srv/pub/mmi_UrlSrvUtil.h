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
* @file    UrlSrvUtilUrl.h
* @brief   Utility
*          
*          
*/

#ifndef __MMI_URL_SRV_UTIL_H__
#define __MMI_URL_SRV_UTIL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_srv_client_commondefine.h"
#include "mmi_srv_client_platformdefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* StrHandle;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** UrlSrvEncodeURLMalloc
* @brief      Encode url query list 
*
* @param[in]  cpStr          String you want to encode
*
* @retval     Encoded string (Must free by UrlSrvFreeUrlMalloc)
*
*/
const MAE_WChar* UrlSrvEncodeURLMalloc
(
  const MAE_WChar *cpwStr
);

/** UrlSrvDecodeURLMalloc
* @brief      Decode encoded string
*
* @param[in]  cpStr          String you want to decode
*
* @retval     Decoded string (Must free by UrlSrvFreeUrlMalloc)
*
*/
const MAE_WChar* UrlSrvDecodeURLMalloc
(
  const MAE_WChar *cpwStr
);

/** UrlSrvFreeUrlMalloc
* @brief      Decode encoded string
*
* @param[in]  cpStr          String you want to free
*
* @retval     None
*
*/
void UrlSrvFreeUrlMalloc
(
  const MAE_WChar *cpwStr
);

/** StrCreateInstance
* @brief      Create an instance for re-sizable string
*
* @param[in]  pwStr  Initial value for the string
*
* @retval     Handle to string instance
*
*/
StrHandle StrCreateInstance
(
  const MAE_WChar *pwStr
);

/** StrDestroyInstance
* @brief      Destroy an instance for re-sizable string
*
* @param[in]  hStr  Handle to string instance
*
* @retval     None
*
*/
void StrDestroyInstance
(
  StrHandle hStr
);

/** StrNCompare
* @brief      Compare string with string instance
*
* @param[in]  hStr     Handle to string instance
* @param[in]  pwStr    String you want to compare
* @param[in]  uStrLen  Length you want to compare
*
* @retval     if hStr > pwStr return 1
*             else if hStr == pwStr return 0
*             else return -1
*
*/
s32 StrNCompare
(
  StrHandle hStr, 
  const MAE_WChar *cpwStr, 
  u32 uStrLen
);

/** StrNCompare
* @brief      Compare string with string instance
*
* @param[in]  hStr     Handle to string instance
* @param[in]  pwStr    String you want to compare
*
* @retval     if hStr > pwStr return 1
*             else if hStr == pwStr return 0
*             else return -1
*
*/
s32 StrCompare
(
  StrHandle hStr, 
  const MAE_WChar *cpwStr
);


/** StrNAppend
* @brief      Append hStr with pwStr
*
* @param[in]  hStr     Handle to string instance
* @param[in]  pwStr    String you want to compare
* @param[in]  uStrLen  Length you want to append
*
* @retval     if hStr > pwStr return 1
*             else if hStr == pwStr return 0
*             else return -1
*
*/
StrHandle StrNAppend
(
  StrHandle hStr, 
  const MAE_WChar *cpwStr, 
  u32 uStrLen
);

/** StrNAppend
* @brief      Append hStr with pwStr
*
* @param[in]  hStr     Handle to string instance
* @param[in]  pwStr    String you want to compare
*
* @retval     if hStr > pwStr return 1
*             else if hStr == pwStr return 0
*             else return -1
*
*/
StrHandle StrAppend
(
  StrHandle hStr, 
  const MAE_WChar *cpwStr
);

/** StrLength
* @brief      Length for string
*
* @param[in]  hStr     Handle to string instance
*
* @retval     u32
*
*/
u32 StrLength
(
  StrHandle hStr
);

/** StrGetStr
* @brief      MAE_Wchar string for string instance
*
* @param[in]  hStr     Handle to string instance
* @param[out] hStr     Length to the string instance
*
* @retval     const MAE_WChar* string
*
*/
const MAE_WChar* StrGetStr
(
  StrHandle hStr, 
  u32 *puStrLen
);

/** UrlSrvUtilMallocMsg
* @brief      Utility for malloc message
*
* @param[in]  uMsgType     Type to the message
* @param[in]  uBodySize    Size of message body
*
* @retval     A message
*
*/
void* UrlSrvUtilMallocMsg
(
  s16 uMsgType, 
  s16 uBodySize
);

/** UrlSrvUtilSendMsg
* @brief      Utility for sending msg
*
* @param[in]  uDstMbx  Mailbox to the destination
* @param[in]  pvMsg    Message you want to send
*
* @retval     s16
*
*/
s16 UrlSrvUtilSendMsg
(
  u16 uDstMbx, 
  void *pvMsg
);

u32 UrlSrvUtilStrLen
(
  const MAE_WChar* cpStr
);

boolean UrlSrvUtilStrEqual
(
  const MAE_WChar* cpStrSrc, 
  const MAE_WChar* cpStrDst
);

boolean UrlSrvUtilStrNEqual
(
 const MAE_WChar* cpStrSrc, 
 const MAE_WChar* cpStrDst,
 u32 uLen
);

MAE_WChar* UrlSrvUtilFindStr
(
  const MAE_WChar* cpStrSrc,
  const MAE_WChar* cpStrDst
);

const MAE_WChar* UrlSrvUtilStrDup
(
  const MAE_WChar* cpwStrSrc
); 

int UrlSrvUtilSprintf
(
  MAE_WChar *cpStr, 
  s32 nCount, 
  const MAE_WChar *cpStrFormat,
  ...
);

#ifdef __URL_SRV_UT__
    #define UrlSrvUtilSprintf swprintf_s
#else
    #define UrlSrvUtilSprintf mae_swprintf
#endif/* __URL_SRV_UT__ */

s32 UrlSrvUtilAtoi
(
  const MAE_WChar *cpwStr
);

void UrlSrvUtilItoa
(
  s32 sValue, 
  MAE_WChar cpwStr[]
);

s64 UrlSrvUtilAtol
(
  const MAE_WChar *cpwStr
);

void UrlSrvUtilLtoa
(
  s64 sValue, 
  MAE_WChar cpwStr[]
);

u8 UrlSrvIsAlpha
(
  MAE_WChar pwStr
);

u8 UrlSrvIsDigit
(
  MAE_WChar pwStr
);

void UrlSrvWItoa
(
  s32 n,
  MAE_WChar s[]
);

void UrlSrvWLtoa
(
  s64 n,
  MAE_WChar s[]
);

s64 UrlSrvWAtol
(
  const MAE_WChar* pwStr
);

MAE_WChar UrlSrvToLower
(
  MAE_WChar cwStr
);

#define UrlSrvMalloc        SRV_MALLOC

void UrlSrvFree
(
  const void *pvMem
);

void UrlSrvMemAddRef
(
  void *pvMem
);

#endif/* __MMI_URL_SRV_UTIL_H__ */
