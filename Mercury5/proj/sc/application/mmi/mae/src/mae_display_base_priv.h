/**
 * \file    mae_display_base_priv.h
 * \brief   The document describes the private data structure used in mae_display_base.c
 *
 * @version
 */

#ifndef __MAE_DISPLAY_BASE_PRIV_H__
#define __MAE_DISPLAY_BASE_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_display_base.h"
#include "mmi_mae_display_forward.h"
#include "mmi_mae_display_types.h"

/******************************/
/*        DEFINITION          */
/******************************/

enum
{
    DBASE_UPDATEMODE_NORMAL = DISP_UPDATEMODE_NORMAL,
    DBASE_UPDATEMODE_PALETTE = DISP_UPDATEMODE_PALETTE,
    DBASE_UPDATEMODE_WAITING
};
typedef u8 DBaseUpdateMode_t;

typedef struct
{
    BitmapBase_t   *pBmp;
    FontBase_t     *pFont;
    u32            nWidth;
    u32            nHeight;
    RGBColor_t     nColorItem[CLR_TOTAL];
#ifdef __DISP_ML_MMI__
    Rect_t         tRcCA[MMI_DISP_LAYER_TOTAL];             //client area which is required to be updated
#else
	Rect_t		  tRcCA;
#endif
    DisplayMode_e  nDispMode;
    MAEDispId_t    nDispId;
	DBaseUpdateMode_t nUpdateMode;
#ifdef __DISP_ML_MMI__
    DisplayLayer_e nCurrentLayer;
#endif
}_DisplayBase_t;

#ifdef __DISP_ML_MMI__
void DISPLAYBASE_Init(void *pBmpDev, MAEDispId_t nDispId, DisplayLayer_e layer);
#else
void DISPLAYBASE_Init(void *pBmpDev, MAEDispId_t nDispId);
#endif

MAERet_t DISPLAYBASE_SetG3DBuffer(DisplayBase_t *pDisp, void *pBmp);

void DISPLAYBASE_Free(MAEDispId_t nDispId);

MAE_Ret DISPLAYBASE_EnableUpdate(MAEDispId_t nId);
MAE_Ret DISPLAYBASE_DisableUpdate(MAEDispId_t nId);

MAE_Ret DISPLAYBASE_DrawText_Portrait(DisplayBase_t *pDisp,
					   BitmapBase_t *pBmpBase,
					                  u32 nFontCate,
                                      u32 nFontSize,
                                      const u16 *pText,
                                      s32 nChars,
                                      s32 x,
                                      s32 y,
                                      const Rect_t *pRect,
                                      u32 nTypes, 
                                      u32 *pColors,
                                      u8  nNumColor);
MAE_Ret DISPLAYBASE_DrawText_Landscape(DisplayBase_t *pDisp,
					    BitmapBase_t *pBmpBase,
					                   u32 nFontCate, 
                                       u32 nFontSize,
                                       const u16 *pText,
                                       s32 nChars,
                                       s32 x,
                                       s32 y,
                                       const Rect_t *pRect,
                                       u32 nTypes,
                                       u32 *pColors,
                                       u8  nNumColor);

MAE_Ret DISPLAYBASE_BitBlt_Portrait(DisplayBase_t *pDisp,
                                    const Rect_t *pDstRc,
                                    const BitmapBase_t *pBmpSrc,
                                    const Rect_t *pSrcRc,
                                    RasterOp_t nRopCode);

MAE_Ret DISPLAYBASE_BitBlt_Landscape(DisplayBase_t *pDisp,
                                     const Rect_t *pDstRc,
                                     const BitmapBase_t *pBmpSrc,
                                     const Rect_t *pSrcRc,
                                     RasterOp_t nRopCode);

#endif //__MAE_DISPLAY_BASE_PRIV_H__
