/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : dispbasicgrap.h

  Contents: Basic structures and constants here

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 10.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#if 1
#include "dispbasicgrap_pub.h"
#else

#include "vm_types.ht"

#include "msgdidef.h"
#include "functypes.h"

#ifndef _DISP_BASIC_GRAPHIC_H_
#define _DISP_BASIC_GRAPHIC_H_

//===============================================
//    Color Space Coversion function table
//===============================================
typedef struct _st_color_conver_{
    fnCSCU32toU16       TrueToReal;
    fnCSCU16toU32       RealToTrue;
    fnCSCU8toU16        RGB332ToRGB565;
    fnCSC888toU16       RGB24ToReal;
    fnCSCGraytoU16      GrayToReal;
    fnCSCPaletteToU16   PaletteToReal;
    fnCSCU32toU32       BitsPerPixel;
}COLOCONVERT, *PCOLOCONVERT;

//===============================================
//    Point function table
//===============================================
typedef struct _st_point_operation_{
    fnSetPoint         SetPoint;
    fnGetPoint         GetPoint;
    fnSetPixel         SetPixel;
    fnGetPixel         GetPixel;
    fnSetPixels        SetPixels;
}POINTACTION, *PPOINTACTION;

//===============================================
//    function set
//===============================================
#ifdef _DISP_BASIC_GRAPHIC_BODY_

    u16  TrueColorToRealColorSW( u32 TrueColor);
    u32  RealColorToTrueColorSW( u16 RealColor );
    u16  RGB332ToRGB565SW(u8 color);
    u16  RGB24ToRealColorSW(u8 RColor,u8 GColor,u8 BColor);
    u16  GrayScaleToRealColorSW(u8 NbBitPerPix, u8 Color);
    u16  PaletteToRealColorSW(u8 colorIndex, u8 *pColorPalette, u16 nbPaletteColors,u16 nbBytePerPaletteColor);
    u32  BitsPerPixelSW(u32 format);

    u32  SetPointSW (MSGDI_DRAWPOINT *pParam);
    u32  GetPointSW (MSGDI_DRAWPOINT *pParam);

    s32  SetPixelSW (PMSGDI_DRAWPIXEL pParam);
    s32  GetPixelSW (PMSGDI_DRAWPIXEL pParam);
    s32  SetPixelsSW (PMSGDI_DRAWPIXELS pParam);
#else  //_DISP_BASIC_GRAPHIC_BODY_

    extern u16  TrueColorToRealColorSW( u32 TrueColor);
    extern u32  RealColorToTrueColorSW( u16 RealColor );
    extern u16  RGB332ToRGB565SW(u8 color);
    extern u16  RGB24ToRealColorSW(u8 RColor,u8 GColor,u8 BColor);
    extern u16  GrayScaleToRealColorSW(u8 NbBitPerPix, u8 Color);
    extern u16  PaletteToRealColorSW(u8 colorIndex, u8 *pColorPalette, u16 nbPaletteColors,u16 nbBytePerPaletteColor);
    extern u32  BitsPerPixelSW(u32 format);

    extern u32  SetPointSW (MSGDI_DRAWPOINT *pParam);
    extern u32  GetPointSW (MSGDI_DRAWPOINT *pParam);

    extern s32  SetPixelSW (PMSGDI_DRAWPIXEL pParam);
    extern s32  GetPixelSW (PMSGDI_DRAWPIXEL pParam);
    extern s32  SetPixelsSW (PMSGDI_DRAWPIXELS pParam);

#endif//_DISP_BASIC_GRAPHIC_BODY_

#endif //_DISP_BASIC_GRAPHIC_H_
#endif

