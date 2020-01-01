/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_FontMgr.h
 *
 * DESCRIPTION
 *      This file contains the interfaces of freetype usage.
 *
 * HISTORY
 *      2008.05.15       Manton Wang         Initial Version
 *      2010.02.02       Chunwei Wang
 *-----------------------------------------------------------------------------
 */

#ifndef __MGL_FONT_MGR_H__
#define __MGL_FONT_MGR_H__

#ifdef __FREETYPE_VECTOR_FONT__
/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct _T_FONT_METRIC_TAG
{
    mgl_u8       u8Width;
    mgl_u8       u8Height;
    mgl_u8       u8BearingX;
    mgl_u8       u8BearingY;
    mgl_u8       u8Advance;
} T_FONT_METRIC_DATA, *T_FONT_METRIC_PTR;

typedef enum FontSrc_Tag
{
    FONT_FROM_FILE_NAME,
    FONT_FROM_RAW_DATA
}FontSrc;

typedef struct T_FONT_SOURCE_TAG
{
    FontSrc            srcFormat;
    mgl_u8             *pRawData;
    mgl_u32            rawDataSize;
    mgl_u16            *pFileName;
}T_FONT_SOURCE_DATA, *T_FONT_SOURCE_PTR;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_boolean mgl_FontMgr_Init(T_FONT_SOURCE_PTR pFontSrc, mgl_u16 cacheKBs);
mgl_void* mgl_FontMgr_GetBMP(mgl_u16 uniChar, mgl_u16 fontSize, T_FONT_METRIC_PTR ptFontMetric, mgl_boolean *pIsCache);
mgl_void mgl_FontMgr_End(mgl_void);

#endif /*  __FREETYPE_VECTOR_FONT__  */
#endif /* __MGL_FONT_MGR_H__ */

