/**
* @file mmi_VideoStreaming_Util.h
*
* This header file defines the data structure of video streaming utility.
*
*/

#ifndef __MMI_VIDEOSTREAMING_UTIL_H__
#define __MMI_VIDEOSTREAMING_UTIL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mediasrv_common.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct VdoStmFileListHdl_t_ VdoStmFileListHdl_t; 

/*=============================================================*/
// Function Declaration
/*=============================================================*/
MAE_Ret VdoStmUtilFileListOpen(VdoStmFileListHdl_t **ppFileListHdl, MAE_WChar *pListPath, u16 nListSize);
MAE_Ret VdoStmUtilFileListClose(VdoStmFileListHdl_t *pFileListHdl);
MAE_Ret VdoStmUtilFileListAddItemToTail(VdoStmFileListHdl_t *pFileListHdl, void *pItem, u32 nItemSize);
MAE_Ret VdoStmUtilFileListUpdateItem(VdoStmFileListHdl_t *pFileListHdl, u16 nIndex, u32 nBeginPos, void *pData, u32 nSize);
MAE_Ret VdoStmUtilFileListDeleteItem(VdoStmFileListHdl_t *pFileListHdl, u16 nIndex);
MAE_Ret VdoStmUtilFileListGetItem(VdoStmFileListHdl_t *pFileListHdl, u16 nIndex, void **ppItem, u32 *pItemSize);
u16 VdoStmUtilFileListGetItemNum(VdoStmFileListHdl_t *pFileListHdl);
u16 VdoStmUtilFileListGetListSize(VdoStmFileListHdl_t *pFileListHdl);
MAE_Ret VdoStmUtilFileListSave(VdoStmFileListHdl_t *pFileListHdl);

MAE_WChar* VdoStmUtilGetExtensionByMime(MediaSrvMimeType_e eMimeType);

#endif /* __MMI_VIDEOSTREAMING_UTIL_H__ */
