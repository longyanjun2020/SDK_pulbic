///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   dwl_frame.h
// @author MStar Semiconductor Inc.
// @brief  Montage Wintarget downloader frame management header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DWL_FRAME_H
#define _DWL_FRAME_H

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdcomp.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
/* Read/Write function using a handle,
 * called by dwl_download and dwl_downloadInflate */
typedef void *dwl_handle_t;
typedef bool (*pf_read_t)(dwl_handle_t, void *, u32);
typedef s32 (*dwl_rwFunc_t)(void *, void *, u32);
typedef s32 (*dwl_setupFunc_t)(void *, u32, u32);

//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
s32 dwl_frameBufInit(u32 u32blkSize);
s32 dwl_download(void *phandle, dwl_rwFunc_t pf_write);
s32 dwl_downloadMultiBin(void *phandle, dwl_rwFunc_t pf_write, dwl_setupFunc_t pf_setup, u32 u32_targetcode);
s32 dwl_downloadInflate(void *io__p_Handle, dwl_rwFunc_t i__pf_Write);
s32 dwl_upload(void *phandle, pf_read_t pf_read, u32 u32totSize);

#endif  // _DWL_FRAME_H
