/*****************************************************************************\
This software is protected by Copyright and the information
contained herein is confidential. Distribution, reproduction
as well as exploitation and transmission of its contents is
not allowed except if expressly permitted. Infringments
result in damage claims.
Copyright : Morning Star 2006/11 ~ 2010

File    : Functable.h

Contents: Remap these must implemented function

Historical :
--------------------------------------------------------------------------
Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
10.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/

/*****************************************************************************\
This software is protected by Copyright and the information
contained herein is confidential. Distribution, reproduction
as well as exploitation and transmission of its contents is
not allowed except if expressly permitted. Infringments
result in damage claims.
Copyright : Morning Star 2006/11 ~ 2010

File    : Functable.h

Contents: Remap these must implemented function

Historical :
--------------------------------------------------------------------------
Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
10.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#if 0
#include "dispfunctable_pub.h"
#else

#ifndef _FUNCTION_REMAPPING_
#define _FUNCTION_REMAPPING_

//===============================================
//    Constants
//===============================================
/*
How to report capabilities of multiMedia processor?
*/
//#define MMP_CAPS_
//===============================================
//    Definition
//===============================================

//In softwsre simulation mode, we always use sw functions to simulate all function
#ifdef __SDK_SIMULATION__
//===================================================================
//      function table for main panel

#define PrePanelInitReal            PrePanelInit
#define PostPanelInitReal           PostPanelInit
//#define GetScreenCapsReal           GetScreenCapsSW
#define GetScreenWidthReal          GetScreenWidth
#define GetScreenHeightReal         GetScreenHeight
#define GetScreenColorDepthReal     GetScreenColorDepth
//#define GetScreenSizeReal           GetScreenSizeSW
//#define GetScreenColorFormatReal    GetScreenColorFormatSW
//#define GetTransparencyColorReal    GetTransparencyColorSW
#define UpdateScreenReal            UpdateScreen
//#define UpdateScreenRealExt         UpdateScreenExt
#define UpdateScreenRealML          UpdateScreenML
//#define GetPanelAttributionReal     GetPanelAttributionSW
//#define SetContrastReal             SetContrastSW
//#define GetContrastReal             GetContrastSW

//#define GetBacklightReal            GetBacklightSW
//#define SetBacklightReal            SetBacklightSW
//#define GetPowerStateReal           GetPowerStateSW
//#define SetPowerStateReal           SetPowerStateSW

#define TrueToRealReal              TrueColorToRealColorSW
#define RealToTrueReal              RealColorToTrueColorSW
#define RGB332ToRGB565Real          RGB332ToRGB565SW
#define RGB24ToRealReal             RGB24ToRealColorSW
#define GrayToRealReal              GrayScaleToRealColorSW
#define PaletteToRealReal           PaletteToRealColorSW
#define BitsPerPixelReal            BitsPerPixelSW

#define SetPointReal                SetPointSW
#define GetPointReal                GetPointSW
#define SetPixelReal                SetPixelSW
#define GetPixelReal                GetPixelSW
#define SetPixelsReal               SetPixelsSW

#define SolidLineReal               SolidLineSW
#define MonoPatternLineReal         MonoPatternLineSW
#define ColorPaletteLineReal        ColorPaletteLineSW

#define DrawHLineReal               DrawHLineSW
#define DrawVLineReal               DrawVLineSW

#define CreateSurfaceReal           CreateSurfaceSW
#define DestroySurfaceReal          DestroySurfaceSW
//#define CreatePatternReal           CreatePatternSW
//#define DestroyPatternReal          DestroyPatternSW
#define GetSurfCapsReal             NULL
//#define GetSurfWidthReal            GetSurfWidthSW
//#define GetSurfHeightReal           GetSurfHeightSW
//#define GetSurfColorFormatReal      GetSurfColorFormatSW
//#define GetSurfStrideReal           GetSurfStrideSW
//#define GetSurfSizeReal             GetSurfSizeSW
#define GetSurfAddressReal          GetSurfAddressSW
#define GetPrimarySurfReal          GetPrimarySurfSW
//#define SetToOnScreenReal           SetToOnScreenSW

//#define SourceCopyReal              SourceCopySW
//#define DestInvertReal              DestInvertSW
//#define MaskFillReal                MaskFillSW
//#define MonoPatternCopyReal         MonoPatternCopySW
//#define ColorPatternCopyReal        ColorPatternCopySW
//#define SrcColorKeyReal             SrcColorKeySW
#define DstColorKeyReal             DstColorKeySW
#define StretchCopyReal             StretchBltSW
#define RotateCopyReal              RotateSW
#if (defined(__ENABLE_DMA2D_HW__) && !defined(__SDK_SIMULATION__))
#define BitBltReal				BitBltDMA2D			//return until HW done
#define FillSolidRectReal		FillSolidRectDMA2D	//return until HW done
#define BitBltQuickReal			BitBltQuickDMA2D	////return immediately
#define FillSolidRectQuickReal	FillSolidRectQuickDMA2D
#define DMA2DCmdFinishReal		DMA2DCmdFinish
#define FadeOutReal             FadeOutDMA2D
#define SrcColorKeyReal         SrcColorKeyDMA2D
#define SourceCopyReal          SourceCopyDMA2D
#else
#define BitBltReal                  BitBltSW
#define FillSolidRectReal           FillSolidRectSW
#define FadeOutReal                 FadeOutSW
#define SrcColorKeyReal             SrcColorKeySW
#define SourceCopyReal              SourceCopySW
#endif

#define BitBltAlphaMaskReal					   BitBltAlphaMaskSW
#define PerspectiveBltReal                 PerspectiveBltSW

//=============================================
// for LCDX....
#define ActivePIPReal               NULL
#define SetPIPaddressReal           NULL
#define DesactivePIPReal            NULL
#define DrawJpegPictureReal         NULL

//===================================================================
//      function table for sub-panel


#else //NOT __SDK_SIMULATION__
//If we are running on traget platform, turn on real hardware accelerator
#define PrePanelInitReal            PrePanelInit
#define PostPanelInitReal           PostPanelInit
//#define GetScreenCapsReal           GetScreenCapsSW
#define GetScreenWidthReal          GetScreenWidth
#define GetScreenHeightReal         GetScreenHeight
#define GetScreenColorDepthReal     GetScreenColorDepth
//#define GetScreenSizeReal           GetScreenSizeSW
//#define GetScreenColorFormatReal    GetScreenColorFormatSW
//#define GetTransparencyColorReal    GetTransparencyColorSW
#define UpdateScreenReal            UpdateScreen
//#define UpdateScreenRealExt         UpdateScreenExt
#define UpdateScreenRealML          UpdateScreenML
//#define GetPanelAttributionReal     GetPanelAttributionSW
//#define SetContrastReal             SetContrastSW
//#define GetContrastReal             GetContrastSW

#if _ENABLE_BACKLIGHT_IN_GDI_
#define GetBacklightReal            GetBacklightSW
#define SetBacklightReal            SetBacklightHW
#endif//_ENABLE_BACKLIGHT_IN_GDI_
//#define GetPowerStateReal           GetPowerStateSW
//#define SetPowerStateReal           SetPowerStateSW

#define TrueToRealReal              TrueColorToRealColorSW
#define RealToTrueReal              RealColorToTrueColorSW
#define RGB332ToRGB565Real          RGB332ToRGB565SW
#define RGB24ToRealReal             RGB24ToRealColorSW
#define GrayToRealReal              GrayScaleToRealColorSW
#define PaletteToRealReal           PaletteToRealColorSW
#define BitsPerPixelReal            BitsPerPixelSW

#define SetPointReal                SetPointSW
#define GetPointReal                GetPointSW
#define SetPixelReal                SetPixelSW
#define GetPixelReal                GetPixelSW
#define SetPixelsReal               SetPixelsSW

#define SolidLineReal               SolidLineSW
#define MonoPatternLineReal         MonoPatternLineSW
#define ColorPaletteLineReal        ColorPaletteLineSW

#define DrawHLineReal               DrawHLineSW
#define DrawVLineReal               DrawVLineSW

#define CreateSurfaceReal           CreateSurfaceSW
#define DestroySurfaceReal          DestroySurfaceSW
//#define CreatePatternReal           CreatePatternSW
//#define DestroyPatternReal          DestroyPatternSW
#define GetSurfCapsReal             NULL
//#define GetSurfWidthReal            GetSurfWidthSW
//#define GetSurfHeightReal           GetSurfHeightSW
//#define GetSurfColorFormatReal      GetSurfColorFormatSW
//#define GetSurfStrideReal           GetSurfStrideSW
//#define GetSurfSizeReal             GetSurfSizeSW
#define GetSurfAddressReal          GetSurfAddressSW
#define GetPrimarySurfReal          GetPrimarySurfSW
#define SetToOnScreenReal           SetToOnScreenSW

#define SourceCopyReal              SourceCopySW

//#define DestInvertReal              DestInvertSW
//#define MaskFillReal                MaskFillSW
//#define MonoPatternCopyReal         MonoPatternCopySW
//#define ColorPatternCopyReal        ColorPatternCopySW
//#define SrcColorKeyReal             SrcColorKeySW
#define DstColorKeyReal             DstColorKeySW
#ifdef _USE_G2D_PERF_
#define StretchCopyReal             StretchBltG2D
#else

#ifdef ENABLE_SCLDMA_HW
#define StretchCopyReal             StretchBltSclDMA
#else
#define StretchCopyReal             StretchBltSW
#endif

#endif

#define RotateCopyReal              RotateSW
#if (defined(__ENABLE_DMA2D_HW__) && !defined(__SDK_SIMULATION__))
#define BitBltReal					BitBltDMA2D			//return until HW done
#define FillSolidRectReal			FillSolidRectDMA2D	//return until HW done
#define BitBltQuickReal				BitBltQuickDMA2D	////return immediately
#define FillSolidRectQuickReal		FillSolidRectQuickDMA2D
#define DMA2DCmdFinishReal			DMA2DCmdFinish
#define FadeOutReal                 FadeOutDMA2D
#define SrcColorKeyReal             SrcColorKeyDMA2D
#else

#ifdef _USE_G2D_PERF_
#define BitBltReal                  BitBltG2D
#define FillSolidRectReal           FillSolidRectG2D
#else
#define BitBltReal                  BitBltSW
#define FillSolidRectReal           FillSolidRectSW
#endif

#define FadeOutReal                 FadeOutSW
#define SrcColorKeyReal             SrcColorKeySW
#endif

	#define BitBltAlphaMaskReal					   BitBltAlphaMaskSW
    #define PerspectiveBltReal                 PerspectiveBltSW
//=============================================
// for LCDX....
    #define ActivePIPReal               NULL
    #define SetPIPaddressReal           NULL
    #define DesactivePIPReal            NULL
    #define DrawJpegPictureReal         NULL

#endif//__SDK_SIMULATION__

#endif//_FUNCTION_REMAPPING_#ifndef _FUNCTION_REMAPPING_
#endif

