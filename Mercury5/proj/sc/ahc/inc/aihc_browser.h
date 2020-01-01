/**
 @file aihc_browser.h
 @brief Header File for the AHC browser API.
 @author 
 @version 1.0
*/

#ifndef _AIHC_BROWSER_H_
#define _AIHC_BROWSER_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _AHC_THUMB_ATTRIBUTE {
    UINT16  u16ThumbPerRow;
    UINT16  u16ThumbPerCol;
    UINT16  u16ThumbHGap;
    UINT16  u16ThumbVGap;
    UINT16  u16TgtThumbW;       // The Target Thumbnail Width.
    UINT16  u16TgtThumbH;       // The Target Thumbnail Height.
    UINT16  u16CurIdx;          // The Working DCF Index.
    UINT32  u32BkColor;         // The Thumbnail Page Background Color
    UINT32  u32FocusColor;      // The Thumbnail Page Focus Color
    UINT32  u32DispStartX;      // The Thumbnail Display Area Start X-Pos
    UINT32  u32DispStartY;      // The Thumbnail Display Area Start Y-Pos
    UINT32  u32DispAreaW;       // The Thumbnail Display Area Width
    UINT32  u32DispAreaH;       // The Thumbnail Display Area Height
    UINT32  uiIdxMap[MAX_DCF_IN_THUMB];
} AHC_THUMB_ATTRIBUTE;

typedef struct _AHC_THUMB_DRAW_FOCUS {
    UINT16  usThumbDrawFocusMaxCount;
    UINT16  usFocusWidth;
    UINT16  usFocusHeight;
    POINT   pFocusStart[20/*THUMB_PER_LINE*THUMB_PER_COLUMN*/];
} AHC_THUMB_DRAW_FOCUS;

/*===========================================================================
 * Function prototype 
 *===========================================================================*/

AHC_BOOL AIHC_Thumb_SetCurrentIdx(UINT32 pwIndex);

#endif
