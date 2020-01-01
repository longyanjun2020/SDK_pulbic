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
#include <string.h>
#include "functypes_pub.h" /* CR_1500: file name shall be in lower case */
//#include "dispbasicgrap_pub.h"
#include "graphdevice.h"

#ifndef _DISP_SURFACE_OPERATION_H_
#define _DISP_SURFACE_OPERATION_H_
//===============================================
//    Constant
//===============================================
#define BLT_ROP_SRCCOPY        0xCC
#define BLT_ROP_DEST           0xAA      //!< destination (existing drawing)
#define BLT_ROP_SOURCE         0xCC      //!< source (image being transferred)
#define BLT_ROP_PATTERN        0xF0      //!< pattern (active brush)
#define BLT_ROP_BLACKNESS      0x00
#define BLT_ROP_NOTSRCERASE    0x11      //!< ~(DEST | SOURCE)
#define BLT_ROP_NOTSRCCOPY     0x33      //!< ~SOURCE
#define BLT_ROP_SRCERASE       0x44      //!< ~DEST & SOURCE
#define BLT_ROP_DSTINVERT      0x55      //!< ~DEST
#define BLT_ROP_PATINVERT      0x5A      //!< DEST ^ PATTERN
#define BLT_ROP_SRCINVERT      0x66      //!< DEST ^ SOURCE
#define BLT_ROP_SRCAND         0x88      //!< DEST & SOURCE
#define BLT_ROP_MERGECOPY      0xC0      //!< PATTERN & SOURCE
#define BLT_ROP_SRCCOPY        0xCC      //!< SOURCE (generally the default)
#define BLT_ROP_MERGEPAINT     0xBB      //!< DEST | ~SOURCE
#define BLT_ROP_SRCPAINT       0xEE      //!< DEST | SOURCE
#define BLT_ROP_PATCOPY        0xF0      //!< PATTERN
#define BLT_ROP_PATPAINT       0xFB      //!< DEST | ~SOURCE | PATTERN
#define BLT_ROP_WHITENESS      0xFF

//===============================================
//    Structures
//===============================================

typedef struct _st_bitblt_operation_
{
	fnFillSolidRect     FillSolidRect;
	fnSourceCopy        SourceCopy;
	//fnDestInvert        DestInvert;
	//fnMaskFill          MaskFill;
	//fnMonoPatternCopy   MonoPatternCopy;
	//fnColorPatternCopy  ColorPatternCopy;
	fnColorkey          SrcColorKey;
	fnColorkey          DstColorKey;
	fnBitBlt        StretchCopy;
	fnRotateCopy        RotateCopy;
	fnBitBlt            BitBlt;
	fnBitBltAlphaMask	BitBltAlphaMask;
	fnFadeOut           FadeOut;
	fnPerspectiveBlt   PerspectiveBlt;
}BITBLTACTION, *PBITBLTACTION;

//===============================================
//    functions
//===============================================
#ifdef _DISP_SURFACE_OPERATION_BODY_

s32  FillSolidRectSW(PMSBLT_FILLSOLID pParam);
u32  DestInvertSW(PMSBLT_DSTINVERT pParam);//ROP: 0x55, DSTINVERT
s32  SourceCopySW(PMSBLT_SRCCOPY pParam);//ROP: 0xCC, SRCCOPY,
u32  SourceCopy_ss(PMSBLT_SRCCOPY pParam);
//u32  FillPatternRectSW(PMSBLT_FILLPATT pParam);
u32  MaskFillSW(PMSBLT_MASKFILL pParam);
s32  SrcColorKeySW(PMSBLT_COLORKEY pParam);
s32  DstColorKeySW(PMSBLT_COLORKEY pParam);
s32  MergeImages16(PMSSURFACE pOutSurf,PMSSURFACE pInSurf, PMSSURFACE pCKSurf,
				   PMSREGION pAreaOut,  PMSREGION  pAreaIn, PMSREGION  pAreaCK, u16 colorkey);
s32  StretchBltSW(PMSBLT_SRCCOPY pParam);
s32  RotateSW(PMSBLT_SRCCOPY pParam, u32 uAngle);

s32 BitBltSW(PMSBLT_BITBLT pParam);
s32 BitBltAlphaMaskSW( PMSBLT_BITBLT_ALPHA pParam );
s32 FadeOutSW(PMSBLT_BITBLT pParam);
s32 PerspectiveBltSW(PMSBLT_PERSPECTIVEBLT pParam);
void FlushSurface(PMSSURFACE  pSrcSurf);

#ifdef _USE_G2D_PERF_
s32 BitBltG2D(PMSBLT_BITBLT pParam);
s32  FillSolidRectG2D(PMSBLT_FILLSOLID pParam);
s32 StretchBltG2D(PMSBLT_BITBLT pParam);
#endif

#if (defined(__ENABLE_DMA2D_HW__) && !defined(__SDK_SIMULATION__))
s32 BitBltDMA2D(PMSBLT_BITBLT pParam);
s32 FillSolidRectDMA2D(PMSBLT_FILLSOLID pParam);
s32 BitBltQuickDMA2D(PMSBLT_BITBLT pParam);
s32 FillSolidRectQuickDMA2D(PMSBLT_FILLSOLID pParam);
s32 DMA2DCmdFinish();
s32 FadeOutDMA2D(PMSBLT_BITBLT pParam);
s32  SrcColorKeyDMA2D(PMSBLT_COLORKEY pParam);
s32  SourceCopyDMA2D(PMSBLT_SRCCOPY pParam)
#endif


#else  //_DISP_SURFACE_OPERATION_BODY_

extern s32  FillSolidRectSW(PMSBLT_FILLSOLID pParam);
extern u32  DestInvertSW(PMSBLT_DSTINVERT pParam);
extern s32  SourceCopySW(PMSBLT_SRCCOPY pParam);
extern u32  SourceCopy_ss(PMSBLT_SRCCOPY pParam);
//extern u32  FillPatternRectSW(PMSBLT_FILLPATT pParam);
extern u32  MaskFillSW(PMSBLT_MASKFILL pParam);
extern s32  SrcColorKeySW(PMSBLT_COLORKEY pParam);
extern s32  DstColorKeySW(PMSBLT_COLORKEY pParam);
extern s32  MergeImages16(PMSSURFACE pOutSurf,PMSSURFACE pInSurf, PMSSURFACE pCKSurf,
						  PMSREGION pAreaOut,  PMSREGION  pAreaIn, PMSREGION  pAreaCK, u16 colorkey);
extern s32  StretchBltSW(PMSBLT_BITBLT pParam);
extern s32  RotateSW(PMSBLT_SRCCOPY pParam, u32 uAngle);

extern s32 BitBltSW(PMSBLT_BITBLT pParam);
extern s32 BitBltAlphaMaskSW( PMSBLT_BITBLT_ALPHA pParam );
    extern s32 FadeOutSW(PMSBLT_BITBLT pParam);
    extern s32 PerspectiveBltSW(PMSBLT_PERSPECTIVEBLT pParam);
    extern void FlushSurface(PMSSURFACE  pSrcSurf);
#ifdef _USE_G2D_PERF_
    extern s32 BitBltG2D(PMSBLT_BITBLT pParam);
    extern s32  FillSolidRectG2D(PMSBLT_FILLSOLID pParam);
    extern s32 StretchBltG2D(PMSBLT_BITBLT pParam);
#endif

#ifdef ENABLE_SCLDMA_HW
    extern s32 StretchBltSclDMA (PMSBLT_BITBLT pParam);
    extern s32 RotateSclDMA(PMSBLT_SRCCOPY pParam, u32 uAngle);
#endif

#if (defined(__ENABLE_DMA2D_HW__) && !defined(__SDK_SIMULATION__))
	extern s32 BitBltDMA2D(PMSBLT_BITBLT pParam);
	extern s32 FillSolidRectDMA2D(PMSBLT_FILLSOLID pParam);
	extern s32 BitBltQuickDMA2D(PMSBLT_BITBLT pParam);
	extern s32 FillSolidRectQuickDMA2D(PMSBLT_FILLSOLID pParam);
	extern s32 DMA2DCmdFinish(void);
    extern s32 FadeOutDMA2D(PMSBLT_BITBLT pParam);
    extern s32  SrcColorKeyDMA2D(PMSBLT_COLORKEY pParam);
    extern s32  SourceCopyDMA2D(PMSBLT_SRCCOPY pParam);
#endif


#endif //_DISP_SURFACE_OPERATION_BODY_

#endif //_DISP_SURFACE_OPERATION_H_
