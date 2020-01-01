/**
 * \file    mae_bitmap_base_priv.h
 * \brief   The document describes the private data structure used in mae_bitmap.c
 *
 * @version $Id: mae_bitmap_base_priv.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MAE_BITMAP_BASE_PRIV_H__
#define __MAE_BITMAP_BASE_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_bitmap_types.h"
#include "mmi_mae_bitmap_base.h"

#include "mmi_mae_graphic_types.h"
/******************************/
/*        DEFINITION          */
/******************************/

#define BMP_UPDATE_DIRTY_AREA(PBMP, PRC) \
        { if(PBMP->tRcDirtyArea.w <= 0 || PBMP->tRcDirtyArea.h <= 0) \
              MEMCPY(&PBMP->tRcDirtyArea, PRC, sizeof(Rect_t)); \
          else \
              RectUnion((&PBMP->tRcDirtyArea), (&PBMP->tRcDirtyArea), (PRC));}

typedef struct
{
    DIB_t        *pDib;
    Rect_t      tRcDirtyArea;
    u32         nColorScheme;
    u32         nTransType;     ///< transparent type
    RGBColor_t  tClrTrans;      ///< transparent color; if the bitmap is indexed bitmap, this records index instead of color value
    RGBColor_t *pPalette;      ///< palette
    u8          nConstAlpha;  ///< const alpha value for all pixels (equal to 255-transparency)
    u8          nCntPalette;    ///< number of palette entries, max 256 entries
    boolean     bNeedFreeDib;  ///< If the DIB is manually insert, set to FALSE
}_BitmapBase_t;

/******************************/
/*         VARIABLES          */
/******************************/
extern const u8 g_nBitMask[];
extern const u8 g_nRGB16_5to8[];
extern const u8 g_nRGB16_6to8[];
extern const u8 g_nAlpha8[];

/* Utilities */
void BITMAPBASE_CorrectRect(_BitmapBase_t *pBmpDst, Rect_t *pDstRc, _BitmapBase_t *pBmpSrc, Rect_t *pSrcRc, u32 Type);

#endif //__MAE_BITMAP_BASE_PRIV_H__

