/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : displine.h

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#if 1
#include "displine_pub.h"
#else

#include <string.h>
#include "functypes.h" /* CR_1500: file name shall be in lower case */
#include "dispbasicgrap.h"

#ifndef _DISP_DRAW_LINE_H_
#define _DISP_DRAW_LINE_H_
//===============================================
//    Constants
//===============================================

//===============================================
//    Structures
//===============================================

typedef u32  (*fnSolidLine)(PMSSOLIDLINE);
typedef u32  (*fnPatternLine)(PMSPATTERNLINE);
typedef void (*fnMonoPatternLine)(u32 PixelPerByte, u32 Shift, u32 C_Width, u16* pDstPage, u8 *pPicture);
typedef void (*fnColorPaletteLine)(u32 NbBitPerPixel, u32 Shift, u32 C_Width, u16 *pDisplay, u8 *pPicture,
                               u8 *pColorPalette, u16 nbPaletteColors, u16 nbBytePerPaletteColor);
typedef s32  (*fnDrawHLine)(PMSDRAWLINE);
typedef s32  (*fnDrawVLine)(PMSDRAWLINE);

typedef struct _st_line_operation_{
    fnSolidLine          SolidLine;
    //fnPatternLine         PatternLine;
    fnMonoPatternLine    MonoPatternLine;
    fnColorPaletteLine   ColorPaletteLine;
    fnDrawHLine          DrawHLine;
    fnDrawVLine          DrawVLine;
}LINEACTION;

//===============================================
//    functions
//===============================================

#ifdef _DISP_DRAW_LINE_BODY_

    u32 SolidLineSW(PMSSOLIDLINE pParam);
    void MonoPatternLineSW(u32 PixelPerByte, u32 Shift, u32 C_Width, u16* pDstPage, u8 *pPicture);
    void ColorPaletteLineSW(u32 NbBitPerPixel, u32 Shift, u32 C_Width, u16 *pDisplay, u8 *pPicture,
                            u8 *pColorPalette, u16 nbPaletteColors, u16 nbBytePerPaletteColor);

    s32 DrawHLineSW(PMSDRAWLINE pParam);
    s32 DrawVLineSW(PMSDRAWLINE pParam);
#else //_DISP_DRAW_LINE_BODY_

    extern u32 SolidLineSW(PMSSOLIDLINE pParam);
    extern void MonoPatternLineSW(u32 PixelPerByte, u32 Shift, u32 C_Width, u16* pDstPage, u8 *pPicture);
    extern void ColorPaletteLineSW(u32 NbBitPerPixel, u32 Shift, u32 C_Width, u16 *pDisplay, u8 *pPicture,
                                   u8 *pColorPalette, u16 nbPaletteColors, u16 nbBytePerPaletteColor);

    extern s32 DrawHLineSW(PMSDRAWLINE pParam);
    extern s32 DrawVLineSW(PMSDRAWLINE pParam);
#endif //_DISP_DRAW_LINE_BODY_

#endif//_DISP_DRAW_LINE_H_
#endif
