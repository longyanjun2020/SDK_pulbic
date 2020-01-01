/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Utility_file.h
 *
 * DESCRIPTION
 *      MStar Framework file functions.
 *
 * HISTORY
 *      2008.05.01       Mickey Chiang         Initial Version
 *      2008.10.03       Jimmy Hsu             Restructure
 *
 *-----------------------------------------------------------------------------
 */
#ifndef __M_UTILITY_FILE_H__
#define __M_UTILITY_FILE_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"

/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
    E_SEEK_SET=0,
    E_SEEK_CUR=1,
    E_SEEK_END=2
};

typedef mgl_u32 MGL_FILE;
/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
MGL_FILE* mglFILEOpen(const mgl_s8 *pwszFilename, const mgl_s8 *pszMode);
mgl_s32 mglFILEClose(MGL_FILE* pHandle);
mgl_s32 mglFILERead(MGL_FILE* pHandle, mgl_void *pvBuffer, mgl_u32 u32Size);
mgl_s32 mglFILEReadEx(mgl_void *pvBuffer, mgl_u32 size, mgl_u32 count, MGL_FILE* pHandle);
mgl_s32 mglFILEWrite(MGL_FILE* pHandle, const mgl_void *pvBuffer, mgl_u32 u32Size);
mgl_s32 mglFILESeek(MGL_FILE* pHandle, mgl_s32 s32Offset, mgl_s32 s32Where);
mgl_s32 mglFILETell(MGL_FILE* pHandle);
mgl_s32 mglFILEDelet(const mgl_u16 *pwszFilename);
mgl_s32 mglFILEGetSize(const mgl_u16 *pwszFilename);

#endif /* __M_UTILITY_FILE_H__ */
