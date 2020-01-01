/**
* @file    mmi_srv_clipboard.h
* @brief
*
*/

#ifndef __MMI_SRV_CLIPBOARD_H__
#define __MMI_SRV_CLIPBOARD_H__


/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_clipboardsrv.h"

/*=============================================================*/
// type and define
/*=============================================================*/


/*=============================================================*/
// functions
/*=============================================================*/
/** SrvClipBoardClearContent
@brief  Clear content in clipboard.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           ClipBoardSRV is already terminated
*/
MAE_Ret SrvClipBoardClearContent(void);

/** SrvClipBoardInsertContent
@brief  Insert content string in clipboard.

@param[in]       pContentStr        pointer to content string which be inserted
@param[in]       nContentLength     Length of content string

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           ClipBoardSRV is already terminated
*/
MAE_Ret SrvClipBoardInsertContent(MAE_WChar *pContentStr, u32 nContentLength);

/** SrvClipBoardGetContent
@brief  Update a existing task in database
        [Note] This content string will free in Srv, User shall not free this pointer ppContentStr.

@param[in]       ppContentStr       reference to the pointer to content string which want to get
@param[in]       pContentLength     pointer to the length of content string which want to get
*/
void SrvClipBoardGetContent(MAE_WChar **ppContentStr, u32 *pContentLength);

#endif // __MMI_SRV_CLIPBOARD_H__

