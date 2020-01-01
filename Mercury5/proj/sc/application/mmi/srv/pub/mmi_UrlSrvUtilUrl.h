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
* @brief   define the interface for url object
*          
*          
*/

#ifndef __MMI_URL_SRV_UTIL_URL_H__
#define __MMI_URL_SRV_UTIL_URL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_UrlSrvCommonSchemeTbl.h"
#include "vm_types.ht"
#ifndef __URL_SRV_UT__
#include "mmi_launcher_common.h"
#endif/* __URL_SRV_UT__*/
#include "mmi_srv_client_commondefine.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define MAX_URL_SCHEME_LEN SRV_MAX_URL_SCHEME_LEN  
#define MAX_URL_HOST_LEN   SRV_MAX_URL_HOST_LEN
#define MAX_URL_ARG_LEN    (32)

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* UrlSrvUrlHdl_t;
typedef void* UrlSrvUrlBuilder_t;
/// SRV_UrlHdl_t


typedef struct
{
	const MAE_WChar *pwKey;
	const MAE_WChar *pwValue;
}UrlSrvUrlQuaryPair_t;
/// SRV_UrlQueryPair_t

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void ToAppletSchemeStr
(
 UrlSrvUrlScheme_e eSchemeID, 
 MAE_WChar pwStrUrlScheme[MAX_URL_SCHEME_LEN]
 );

void ToAppletHostStr
(
 UrlSrvUrlHost_e eHostID, 
 MAE_WChar pwStrUrlHost[MAX_URL_HOST_LEN]
 );

UrlSrvUrlBuilder_t UrlSrvBuildUrlStart
(
 MAE_WChar pwStrScheme[MAX_URL_SCHEME_LEN], 
 MAE_WChar pwStrHost[MAX_URL_HOST_LEN]
);


// UrlSrvUrlBuilder_t UrlSrvBuildUrlStart
// (
//  MAE_WChar pwStrScheme[MAX_URL_SCHEME_LEN], 
//  MAE_WChar *pwStrHost
// );


UrlSrvUrlBuilder_t UrlSrvAddUrlString
(
 UrlSrvUrlBuilder_t pUrlBuilder, 
 const MAE_WChar *cpwStr
);

UrlSrvUrlBuilder_t UrlSrvAddUrlParam
(
 UrlSrvUrlBuilder_t ptUrlBuilder, 
 const MAE_WChar *cpwKey, 
 const MAE_WChar *cpwValue
 );

UrlSrvUrlBuilder_t UrlSrvAddUrlParamFromInt
(
 UrlSrvUrlBuilder_t ptUrlBuilder, 
 const MAE_WChar *cpwKey, 
 s32 sValue
 );

UrlSrvUrlBuilder_t UrlSrvAddUrlParamFromUInt
(
 UrlSrvUrlBuilder_t pUrlBuilder, 
 const MAE_WChar *cpwKey, 
 u32 uValue
 );

UrlSrvUrlBuilder_t UrlSrvAddUrlParamFromLong
(
 UrlSrvUrlBuilder_t pUrlBuilder, 
 const MAE_WChar *cpwKey, 
 s64 sValue
 );

MAE_Ret UrlSrvBuildUrlEnd
(
 UrlSrvUrlBuilder_t ptUrlBuilder, 
 UrlSrvUrlHdl_t *ppUrl
 );

/// eg. "browse://file?mode=0&type=all"
/// Create an url object
MAE_Ret UrlSrvUrlCreate
(
 const MAE_WChar* cpwStrUrl, 
 UrlSrvUrlHdl_t *ppUrl
 );

/// Destroy an url object
void UrlSrvUrlDestroy
(
 UrlSrvUrlHdl_t pUrl
 );

/// Get the original url text
/// eg."browse://file?mode=0&type=0"
const MAE_WChar* UrlSrvUrlGetText
(
 UrlSrvUrlHdl_t pUrl
 );

const MAE_WChar* UrlSrvUrlToStr
(
 UrlSrvUrlHdl_t pUrl
 );

/// Get the url scheme
/// eg. "browse"
const MAE_WChar* UrlSrvUrlGetScheme
(
 UrlSrvUrlHdl_t pUrl
 );

const MAE_WChar* UrlSrvGetScheme
(
 UrlSrvUrlHdl_t pUrl
 );

/// Get the url host text
/// eg. "file"
const MAE_WChar* UrlSrvUrlGetHostText
(
 UrlSrvUrlHdl_t pUrl
 );

const MAE_WChar* UrlSrvGetHost
(
 UrlSrvUrlHdl_t pUrl
 );

/// Get the parameter value from a Query string
/// eg."browse://file?mode=0&type=0"
/// mode/type are keys used to get a certain value.
MAE_Ret UrlSrvGetParam
(
 UrlSrvUrlHdl_t pUrl, 
 const MAE_WChar *cpwKey, 
 const MAE_WChar **cppwValue
 );

///The same as UrlSrvGetParam, but will convert the result to integer
MAE_Ret UrlSrvGetParamAsInt
(
 UrlSrvUrlHdl_t pUrl, 
 MAE_WChar *pwKey, 
 s32 *psInt
 );

MAE_Ret UrlSrvGetParamAsUInt
(
 UrlSrvUrlHdl_t pUrl, 
 MAE_WChar *pwKey, 
 u32 *puInt
 );

///The same as UrlSrvGetParam, but will convert the result to long
MAE_Ret UrlSrvGetParamAsLong
(
 UrlSrvUrlHdl_t pUrl, 
 MAE_WChar *pwKey, 
 s64 *psLong
 );

/// Get query pairs
/// eg. key = "mode" value = "0"
///     key = "type" value = "all"
MAE_Ret UrlSrvUrlGetQueryList
(
 UrlSrvUrlHdl_t pUrl, 
 UrlSrvUrlQuaryPair_t **ppsQueryPairs, 
 s32 *psItemCount
 );

/// Check whether the url handler will be notified or not
boolean UrlSrvServerCheckUrl
(
 u16 uEvt, 
 void *pvEvtParm, 
 void *pvOwner, 
 void *pvCusData
 );

/// Notify the url handler
boolean UrlSrvServerNotifyUrl
(
 u16 uEvt, 
 void *pvEvtParm, 
 void *pvOwner, 
 void *pvCusData
 );

#endif/* __MMI_URL_SRV_UTIL_URL_H__ */
