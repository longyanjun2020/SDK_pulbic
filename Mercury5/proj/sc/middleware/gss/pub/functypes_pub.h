/*****************************************************************************\
This software is protected by Copyright and the information
contained herein is confidential. Distribution, reproduction
as well as exploitation and transmission of its contents is
not allowed except if expressly permitted. Infringments
result in damage claims.
Copyright : Morning Star 2006/11 ~ 2010

File    : panelinfo.h

Historical :
--------------------------------------------------------------------------
Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#include "vm_types.ht"

#include "msgdidef.h" /* CR_1500: file name shall be in lower case */

#ifndef _FUNCTION_TYPES_H_
#define _FUNCTION_TYPES_H_
//===============================================
//    Constant
//===============================================
/*
#define MS_SURFACE_SYSTEM_MEMORY    0x0001
#define MS_SURFACE_VIDEO_MEMORY     0x0002

#define MS_SURFACE_OVERLAY          0x0010
#define MS_SURFACE_GLASS            0x0020 // with transparent color support

#define MS_SURFACE_HINT_ALIGN4      0x100
#define MS_SURFACE_HINT_ALIGN8      0x200
#define MS_SURFACE_HINT_ALIGN16     0x400
#define MS_SURFACE_HINT_ALIGN32     0x800

// Color format
#define MS_COLOR_FORMAT_RGB322      0x00000001
#define MS_COLOR_FORMAT_RGB444	    0x00000002
#define MS_COLOR_FORMAT_RGB666	    0x00000004
#define MS_COLOR_FORMAT_RGB565	    0x00000008
#define MS_COLOR_FORMAT_RGB888	    0x00000010

#define MS_COLOR_FORMAT_ARGB1555    0x00000100
#define MS_COLOR_FORMAT_ARGB4444    0x00000200
#define MS_COLOR_FORMAT_ARGB8888    0x00000400

#define MS_COLOR_FORMAT_PALETTE_2   0x00001000
#define MS_COLOR_FORMAT_PALETTE_4   0x00002000
#define MS_COLOR_FORMAT_PALETTE_16  0x00004000
#define MS_COLOR_FORMAT_PALETTE_256 0x00008000

*/
//===============================================
//    Structures
//===============================================
typedef PMSSURFACE  (*fnCreateSurface)(u16, u16, u32);
//typedef PMSSURFACE  (*fnCreatePattern)(u32);
typedef u32         (*fnDestroySurface)(PMSSURFACE);
typedef u16         (*fnGetSurfWORD)(PMSSURFACE);
typedef u32         (*fnGetSurfDWORD)(PMSSURFACE);
typedef PMSSURFACE  (*fnGetPrimary)(u32);
typedef PMSSURFACE  (*fnSetToOnScreen)(u32, PMSSURFACE);

typedef u32  (*fnCSCU32toU32)(u32);
typedef u16  (*fnCSCU32toU16)(u32);
typedef u16  (*fnCSCU8toU16)(u8);
typedef u32  (*fnCSCU16toU32)(u16);
typedef u16  (*fnCSC888toU16)(u8,u8,u8);

typedef u16  (*fnCSCGraytoU16)(u8, u8);
typedef u16  (*fnCSCPaletteToU16)(u8, u8*, u16, u16);
typedef u32  (*fnSetPoint)(PMSGDI_DRAWPOINT);
typedef u32  (*fnGetPoint)(PMSGDI_DRAWPOINT);
typedef s32  (*fnSetPixel)(PMSGDI_DRAWPIXEL);
typedef s32  (*fnGetPixel)(PMSGDI_DRAWPIXEL);
typedef s32  (*fnSetPixels)(PMSGDI_DRAWPIXELS);

typedef u8   (*fnGetByte)(void);
typedef u16  (*fnGetWORD)(void);
typedef u32  (*fnGetDWORD)(void);
typedef bool (*fnGetBool)(void);
typedef s32  (*fnGetAttribution)(PATTRIBUTION);
typedef u8   (*fnGetLevel)(u32, u32);

typedef u32  (*fnSetByte)(u8);
typedef u32  (*fnSetWORD)(u16);
typedef u32  (*fnSetDWORD)(u32);
typedef u32  (*fnSetAttribution)(PATTRIBUTION);
typedef u32  (*fnTakeAction)(void);
typedef s8   (*fnSetLevel)(u32, u8);

typedef u8   (*fnGetByteByIndex)(u32);
typedef u16  (*fnGetWordByIndex)(u32);
typedef u32  (*fnGetDWByIndex)(u32);

typedef s32  (*fnUpdateScreen)(u32, PMSUPDATELAYER);
typedef s32  (*fnUpdateScreenML)(u32 , PMSUPDATE);
typedef u32  (*fnSetAddress)(u32, u32);
typedef u32  (*fnEnableMdlScreenLayer)(u32, bool);
typedef u32  (*fnSetMdlScreenCtrl)(u32, bool);
typedef bool  (*fnIsMdlScreenLayerEnable)(u32);

typedef bool (*fnIsAbleToDrawPic)  (void *param);
typedef s32  (*fnFillSolidRect)(PMSBLT_FILLSOLID);
typedef s32  (*fnSourceCopy)(PMSBLT_SRCCOPY);
typedef u32  (*fnDestInvert)(PMSBLT_DSTINVERT);//ROP: 0x55, DSTINVERT
typedef u32  (*fnFillPatternRect)(PMSBLT_FILLPATT);
typedef u32  (*fnMaskFill)(PMSBLT_MASKFILL);
typedef u32  (*fnMonoPatternCopy)(PMSBLT_PATTPAINT);
typedef u32  (*fnColorPatternCopy)(PMSBLT_PATTCOPY);
typedef s32  (*fnColorkey)(PMSBLT_COLORKEY);
typedef s32  (*fnRotateCopy)(PMSBLT_SRCCOPY, u32);
typedef s32  (*fnBitBlt)(PMSBLT_BITBLT);
typedef s32  (*fnBitBltAlphaMask)(PMSBLT_BITBLT_ALPHA);
typedef s32  (*fnFadeOut)(PMSBLT_BITBLT);
typedef s32  (*fnPerspectiveBlt)(PMSBLT_PERSPECTIVEBLT);
typedef u8   (*fnG3DPowerOn)(void);
typedef u8   (*fnG3DPowerOff)(void);

#endif //_FUNCTION_TYPES_H_
