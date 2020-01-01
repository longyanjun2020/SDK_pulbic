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
* @file    UriParserExport.h
* @brief   define the config & data type for uri parser 
*          the caller only include this file to use uri parser
*          
*/
#ifndef __MMI_URI_PARSER_EXPORT_H__
#define __MMI_URI_PARSER_EXPORT_H__

#ifdef __cplusplus
extern "C" {
#endif/* __cplusplus */


/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UriType.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/


/*=============================================================*/
// Type Declarations
/*=============================================================*/

/// the main struct to
/// describe ipv4 address
typedef struct
{
	u8 uData[4]; 
}URI_Ip4; 

/// the main struct to
/// describe ipv6 address
typedef struct
{
	u8 uData[16]; 
}URI_Ip6; 

/// the main struct to 
/// describe the start position
/// and end position in a text
typedef struct
{
	const URI_CHAR *pchTextStart;
	const URI_CHAR *pchAfterTextEnd;
}URI_Text_t;

/// the main struct to
/// describe path segment in uri
typedef struct URI_PathSegment_t
{
    URI_Text_t sText;
    struct URI_PathSegment_t *psNext;
}URI_PathSegment_t;

/// the main struct to 
/// describe host text in uri
typedef struct{
	URI_Ip4 *psIp4;
	URI_Ip6 *psIp6;
	URI_Text_t *psTextIpFuture; 
} URI_HostText_t; 

/// the main struct to describe URI
typedef struct
{
	URI_Text_t sScheme; 
	URI_Text_t sUserInfo; 
	URI_Text_t sHostText; 
	URI_HostText_t sHostData; 
	URI_Text_t sPortNum; 
	URI_PathSegment_t *psPathHead; 
	URI_PathSegment_t *psPathTail;
	URI_Text_t sQuery; 
	URI_Text_t sFragment; 
	URI_BOOL bAbsolutePath; 
	URI_BOOL bOwner; 
	void *pvReserved; 
}URI_Uri_t; 

/// the main struct use 
/// to parse URI
typedef struct
{
	URI_Uri_t *pUri; 
	URI_ErrCode_e eErrorCode; 
	const URI_CHAR *pchErrorPos;
	void *pvReserved;
}URI_ParseState_t; 

/// the main struct 
/// to parse querylist
typedef struct URI_QueryList_t
{
	const URI_CHAR *pStrKey;
	const URI_CHAR *pStrValue;
	struct URI_QueryList_t* psNext;
}URI_QueryList_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void URI_FreeUri(URI_Uri_t *pUri);

URI_ErrCode_e URI_ParseUri
(
  URI_ParseState_t *psParseState,
  const URI_CHAR *cpStrUri
);

URI_ErrCode_e URI_ParseUriEx
(
  URI_ParseState_t *psParseState, 
  const URI_CHAR *pchTextStart, 
  const URI_CHAR *pchAfterTextEnd
);

URI_ErrCode_e URI_DissectQueryMalloc
(
 URI_QueryList_t **ppsQueryList, 
 s32 * psItemCount,
 const URI_CHAR * pchFirst, 
 const URI_CHAR * pchAfterLast
);

URI_ErrCode_e URI_DissectQueryMallocEx
(
 URI_QueryList_t **ppQueryList, 
 s32 *psItemCount,
 const URI_CHAR * pchFirst, 
 const URI_CHAR * pchAfterLast,
 URI_BOOL bPlusToSpace, 
 URI_BreakConversion_e eBreakConversion
); 

static URI_ErrCode_e URI_ComposeQueryEngine
(
  URI_CHAR *pchDest,
  const URI_QueryList_t *cpsQueryList,
  s32 sMaxChars, 
  s32 *psCharsWritten, 
  s32 *psCharsRequired,
  URI_BOOL bSpaceToPlus, 
  URI_BOOL bNormalizeBreaks
);

URI_ErrCode_e URI_ComposeQueryMalloc
(
  URI_CHAR **ppchDest,
  const URI_QueryList_t *psQueryList
);

URI_ErrCode_e URI_ComposeQueryMallocEx
(
  URI_CHAR **ppDest,
  const URI_QueryList_t *psQueryList,
  URI_BOOL bSpaceToPlus, 
  URI_BOOL bNormalizeBreaks
);

URI_ErrCode_e URI_ComposeQueryCharsRequired
(
  const URI_QueryList_t *psQueryList,
  s32 *pchCharsRequired
);

URI_ErrCode_e URI_ComposeQueryCharsRequiredEx
(
  const URI_QueryList_t *psQueryList,
  s32 *psCharsRequired, 
  URI_BOOL bSpaceToPlus, 
  URI_BOOL bNormalizeBreaks
);

URI_ErrCode_e URI_ComposeQuery
(
  URI_CHAR *pchDest,
  const URI_QueryList_t *psQueryList, 
  s32 sMaxChars, 
  s32 *psCharsWritten
);

URI_ErrCode_e URI_ComposeQueryEx
(
  URI_CHAR * pchDest,
  const URI_QueryList_t *psQueryList, 
  s32 sMaxChars, 
  s32 *psCharsWritten,
  URI_BOOL bSpaceToPlus, 
  URI_BOOL bNormalizeBreaks
);

void URI_FreeQueryList
(
  URI_QueryList_t *psQueryList
);


#ifdef __cplusplus
}
#endif/* __cplusplus */
#endif/* __MMI_URI_PARSER_EXPORT_H__ */
