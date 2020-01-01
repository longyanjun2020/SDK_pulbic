/**
 * \file    mmi_mae_display_base.h
 * \brief   The document describes the private data structure used in mae_display_base.c
 *
 * @version
 */

#ifndef __MMI_MAE_DISPLAY_BASE_H__
#define __MMI_MAE_DISPLAY_BASE_H__
/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_font_forward.h"
#include "mmi_mae_display_forward.h"
#include "mmi_mae_bitmap_forward.h"
#include "mmi_mae_graphic_forward.h"

/******************************/
/*        DEFINITION          */
/******************************/

MAE_Ret DISPLAYBASE_New(MAEDispId_t tDispId, void **ppDisp);
u32 DISPLAYBASE_Release(DisplayBase_t *pDisp);

/* API */
void DISPLAYBASE_DrawRect(DisplayBase_t *pDisp,
                          const Rect_t *pRect,
                          RGBColor_t nClrBorder,
                          RGBColor_t nClrFill,
                          u32 nFlags);
void DISPLAYBASE_DrawColorLine(DisplayBase_t *pDisp, s32 x1, s32 y1, s32 x2, s32 y2, RGBColor_t nColor, RasterOp_t nRop);
void DISPLAYBASE_DrawColorLineEx(DisplayBase_t *pDisp, s32 _x1, s32 _y1, s32 _x2, s32 _y2, RGBColor_t nColor, u8 nBrushSize, RasterOp_t nRop);
void DISPLAYBASE_DrawLine(DisplayBase_t *pDisp, s32 x1, s32 y1, s32 x2, s32 y2);
void DISPLAYBASE_DrawLineEx(DisplayBase_t *pDisp,
                            s32 x1,
                            s32 y1,
                            s32 x2,
                            s32 y2,
                            u8 nBrushSize,
                            DisplayDottedType_e nType);
MAE_Ret DISPLAYBASE_MeasureText(DisplayBase_t *pDisp,
                                u32 nFontCate, 
                                u32 nFontSize,
                                const u16 *pText,
                                u32 nLen,
                                u32 nMaxWidth,
                                u32 *pFits,
                                u32 *pPixels,
                                u32 nTypes);
MAE_Ret DISPLAYBASE_DrawText(DisplayBase_t *pDisp,
                         u32 nFontCate,
                         u32 nFontSize,
                         const u16 *pText,
                         s32 Chars,
                         s32 x,
                         s32 y,
                         const Rect_t *pRect,
                         u32 nTypes);

BitmapBase_t* DISPLAYBASE_GetDeviceBitmap(DisplayBase_t *pDisp);

/**
 *  DISPLAYBASE_SetDestination(DisplayBase_t *pDisp, BitmapBase_t *pBmpDst)
 *
 *  @brief  This function sets new destination bitmap to DisplayBase.
 *
 *  @param  pDisp           [in]Pointer to the DisplayBase
 *  @param  pBmpDst         [in]Pointer to new destination BitmapBase
 *
 *  @retval MAE_RET_SUCCESS   Success
 *  @retval MAE_RET_FAILED    Get BmpInfo of pBmpDst error
 *  @retval MAE_RET_BAD_PARAM Error parameter(s)
 *
 *  Note:
 *    If pBmpDst is NULL, system destination BitmapBase will be set to DisplayBase.
 *    The previous BitmapBase in pDisp will NOT be release automatically.
 *    User should release it manually.
 *
 */
MAE_Ret DISPLAYBASE_SetDestination(DisplayBase_t *pDisp, BitmapBase_t *pBmpDst);
BitmapBase_t* DISPLAYBASE_GetDestination(DisplayBase_t *pDisp);

RGBColor_t DISPLAYBASE_SetColor(DisplayBase_t *pDisp, u32 nItemId, RGBColor_t nRgb);
void DISPLAYBASE_ClearScreen(DisplayBase_t *pDisp);
void DISPLAYBASE_Update(DisplayBase_t *pDisp, u32 nType, boolean bUpdateQuick);
MAE_Ret DISPLAYBASE_BitBlt(DisplayBase_t *pDisp,
                           const Rect_t *pDstRc,
                           const BitmapBase_t *pBmpSrc,
                           const Rect_t *pSrcRc,
                           RasterOp_t nRopCode);
MAE_Ret DISPLAYBASE_BitBltL(DisplayBase_t *pDisp,
                               const Rect_t *pDstRc,
                               const BitmapBase_t *pBmpSrc,
                               const Rect_t *pSrcRc,
                               RasterOp_t nRopCode);
MAE_Ret DISPLAYBASE_GetDisplayId(DisplayBase_t *pDisp, MAEDispId_t *pID);
//MAE_Ret DISPLAYBASE_SetUpdateFunc(MAEDispId_t DispID, DISP_UPDATE_FUNC_PTR pUpdFunc, void *pData, boolean bSet);
MAE_Ret DISPLAYBASE_GetFontInfo(DisplayBase_t *pDisp,
                                   u32 nFontCate,
                                   u32 nFontSize,
                                   u32 FontType,
                                   FontInfo *pInfo);
void DISPLAYBASE_UpdateDevice(MAEDispId_t nId, boolean bPartial, boolean bIsFire);
MAE_Ret DISPLAYBASE_SetCARect(DisplayBase_t *pDisp, const Rect_t *prcCA);
MAE_Ret DISPLAYBASE_SetDispMode(DisplayBase_t  *pDisp, const DisplayMode_e nDispMode);
void DISPLAYBASE_DrawEllipse(DisplayBase_t *pDisp,
                             const Ellipse_t *pEllipse,
                             RGBColor_t nClrBorder,
                             RGBColor_t nClrFill,
                             u32 nFlags);
void DISPLAYBASE_DrawArc(DisplayBase_t *pDisp,
                            const Arc_t *pArc,
                            RGBColor_t nClrBorder,
                            RGBColor_t nClrFill,
                            u32 nFlags);
void DISPLAYBASE_DrawTriangle(DisplayBase_t *pDisp,
                            const Triangle_t *pTriangle,
                            RGBColor_t nClrBorder,
                            RGBColor_t nClrFill,
                            u32 nFlags);

/**
 *  DISPLAYBASE_Fadeout(DisplayBase_t *pDisp, const Rect_t *pDstRc, FadeoutLevel_t nFdoLevel)
 *
 *  @brief  This function makes the fadeout effect to the display buffer in displaybase.
 *
 *  @param  pDisp           [in]Pointer to the DisplayBase
 *  @param  pDstRc          [in]Pointer to a rectangle which will make fadeout effect.
 *  @param  nFdoLevel       [in]The level of fadeout effect.
 *
 *  @retval MAE_RET_SUCCESS   Successfully
 *  @retval MAE_RET_BAD_PARAM Error parameter(s)
 *
 *  Note:
 *
 */
MAERet_t DISPLAYBASE_Fadeout(DisplayBase_t *pDisp,
                           const Rect_t *pDstRc,
                           FadeoutLevel_t nFdoLevel,
                           Mae_FadeoutSourceType_e eSourceType);

void DISPLAYBASE_UpdateUserBitmap(MAEDispId_t nId, BitmapBase_t *pDstBmp);
void DISPLAYBASE_UpdateVendorBitmap(MAEDispId_t nId, BitmapBase_t *pDstBmp, boolean bPartial, boolean bUpdateQuick);

MAE_Ret DISPLAYBASE_StretchBlt(DisplayBase_t *pDisp,
                           const Rect_t *pDstRc,
                           const BitmapBase_t *pBmpSrc,
                           const Rect_t *pSrcRc,
                           RasterOp_t nRopCode);

MAE_Ret DISPLAYBASE_PerspectiveBlt(DisplayBase_t *pDisp,
                           const Rect_t *pDstRc,
                           const BitmapBase_t *pBmpSrc,
                           const Rect_t *pSrcRc,
                           RasterOp_t nRopCode,
                           u16 nDir);

u32 DISPLAYBASE_GetScreenUpdateTime(void);

/**
 *  DISPLAYBASE_IsUpdateFinish( DisplayBase_t *pDisp)
 *
 *  @brief  This function return whether driver finish updating screen or not
 *
 *  @param  pDisp           [in]Pointer to the DisplayBase

 *  @retval True	Finish or input parameter is invalid 
 *  @retval False	Not Finish
 *
 *  Note:
 *
 */
boolean DISPLAYBASE_IsUpdateFinish( DisplayBase_t *pDisp);


/**
 *  DISPLAYBASE_SetOSDEnableAlphaMask( MAE_DispId_t nDispId, boolean bIsEnable )
 *
 *  @brief  To enable/disable camera/videoplayer/camcorder app to using alpha mask, give each pixel alpha value by alpha mask
 *
 *  @param  nClsId			  [in] applet class ID
 *  @param  nDispId           [in] display screen ID
 *  @param  bIsEnable         [in] enable/disable OSD per pixel alpha blending
 *  @retval 
 *
 *  Note:
 *
 */
MAE_Ret DISPLAYBASE_SetOSDEnableAlphaMask( u16 nClsId, MAE_DispId_t nDispId, boolean bIsEnable );

/**
 *  DISPLAYBASE_GetOSDEnableAlphaMask( MAE_DispId_t nDispId )
 *
 *  @brief  To get camera/videoplayer/camcorder app is using alpha mask or not
 *
 *  @param  nDispId              [in] display screen ID
 *
 *  @retval TRUE				[out]OSD is per pixel alpha blending
 *          FALSE				[out]OSD is NOT per pixel alpha blending
 *
 *  Note:
 *
 */
boolean DISPLAYBASE_GetOSDEnableAlphaMask( MAE_DispId_t nDispId );

/**
 *  DISPLAYBASE_SetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency )
 *
 *  @brief  To set Transparency value to camera/videoplayer/camcorder app, give each pixel alpha value by transparency
 *
 *  @param  nDispId              [in] display screen ID
 *  @param  nTransparency        [in] OSD global alpha blending value
 *
 *  @retval 
 *
 *  Note: the default transparency is 255 ( Opaque fully)
 *
 */
MAE_Ret DISPLAYBASE_SetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency );

/**
 *  DISPLAYBASE_GetDPM( MAE_DispId_t nDispId)
 *
 *  @brief  To get the amount of pixels per 10 Centimeters.
 *
 *  @param  nDispId              [in] display screen ID
 *
 *  @retval the amount of pixels per 10 centimeters
 *
 *
 */
u32 DISPLAYBASE_GetDPM( MAE_DispId_t nDispId );

#ifdef __DISP_ML_MMI__
MAERet_t DISPLAYBASE_SetCurrentLayer(DisplayBase_t *pDisp, DisplayLayer_e layer);
MAERet_t DISPLAYBASE_SetLayerOffset(DisplayBase_t *pDisp, DisplayLayer_e layer, s32 x, s32 y);
MAERet_t DISPLAYBASE_SetLayerVisible(DisplayBase_t *pDisp, DisplayLayer_e layer, u8 bVisible);
#endif

#endif //__MAE_DISPLAY_BASE_H__
