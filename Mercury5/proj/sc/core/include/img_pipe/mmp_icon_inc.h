//==============================================================================
//
//  File        : mmp_icon_inc.h
//  Description : INCLUDE File for the Firmware ICON engine control
//  Author      : Jerry Lai
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_ICON_INC_H_
#define _MMP_ICON_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "aitu_calendar.h"

/** @addtogroup MMPF_Icon
 *  @{
 */

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_ICON_COLOR
{
    MMP_ICON_COLOR_INDEX8 = 0,
    MMP_ICON_COLOR_RGB565,
    MMP_ICON_COLOR_INDEX1,
    MMP_ICON_COLOR_INDEX2,
    MMP_ICON_COLOR_NUM
} MMP_ICON_COLOR;

typedef enum _MMP_ICON_MIRROR
{
    MMP_ICON_MIRROR_NONE = 0x00,
    MMP_ICON_MIRROR_H    = 0x01,
    MMP_ICON_MIRROR_V    = 0x02,
    MMP_ICON_MIRROR_BOTH = MMP_ICON_MIRROR_H | MMP_ICON_MIRROR_V
} MMP_ICON_MIRROR;

typedef enum _MMP_STICKER_ID
{
    MMP_STICKER_ID_0 = 0,
    MMP_STICKER_ID_1,
    MMP_STICKER_ID_NUM
} MMP_STICKER_ID;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_STICKER_ATTR
{
    MMP_UBYTE           ubStickerId;
    MMP_ULONG           ulBaseAddr;
    MMP_USHORT          usStartX;
    MMP_USHORT          usStartY;
    MMP_USHORT          usWidth;
    MMP_USHORT          usHeight;
    MMP_ICON_COLOR      colorformat;
    MMP_ULONG           ulTpColor;
    MMP_BOOL            bTpEnable;
    MMP_BOOL            bSemiTpEnable; // Alpha blending.
    MMP_UBYTE           ubAlphaWeight;
    MMP_ICON_MIRROR     eMirrorType;
    AUTL_DATETIME       stDateTime;
} MMP_STICKER_ATTR;

/// @}

#endif //_MMP_ICON_INC_H_
