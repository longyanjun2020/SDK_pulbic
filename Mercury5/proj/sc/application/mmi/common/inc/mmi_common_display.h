////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_common_display.h
* @version
* @brief   common display header file
*
*/

#ifndef __MMI_COMMON_DISPLAY_H__
#define __MMI_COMMON_DISPLAY_H__

#include "mmi_mae_common_def.h"

#include "mmi_mae_retcode.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_bitmap.h"
#include "mmi_mae_font.h"
#include "mmi_mae_display_base.h"


void DisplayRelease(MAE_DispId_t nDispId);


/**
 *  DisplayQueryInterface(MAE_DispId_t nDispId, MAE_IId nId, void **ppObj, IBase *pOwner)
 *
 *  @brief  Inherit addref from IBase to query interface.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  nId				[in]Interface ID to query, supports IID_DISPLAY and IID_BASE only
 *  @param  ppObj           [out]Reference to a pointer to a function table if this interface is supported
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_NOT_SUPPORTED Not support this interface
 *
 */
MAE_Ret DisplayQueryInterface
(
    MAE_DispId_t	nDispId,
    MAE_IId			nId,
    void			**ppObj,
    IBase			*pOwner
);


/**
 *  DisplaySetDestination(MAE_DispId_t nDispId, IBitmap *pBmpDst, IBase *pOwner)
 *
 *  @brief  This function sets new destination bitmap to IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pBmpDst         [in]Pointer to new destination IBitmap Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS   Success
 *  @retval MAE_RET_FAILED    Get BmpInfo of pBmpDst error
 *  @retval MAE_RET_BAD_PARAM Error parameter(s)
 *
 *  Note:
 *    If pBmpDst is NULL, system destination IBitmap will be set to IDisplay.
 *    IBITMAP_AddRef will be called on new destination bitmap.
 *    IBITMAP_Release will be called on old destination bitmap.
 *
 */
MAE_Ret DisplaySetDestination(MAE_DispId_t nDispId, IBitmap *pBmpDst, IBase *pOwner);

/**
 *  DisplaySetFont(MAE_DispId_t nDispId, IFont *pFont, IBase *pOwner)
 *
 *  @brief  This function sets new IFont to the IDisplay. The previous IFont will be returned.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pFont           [in]Pointer to new IFont Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Pointer to IFont    Success
 *  @retval NULL                Any error occurs
 *
 */
IFont* DisplaySetFont(MAE_DispId_t nDispId, IFont *pIFont, IBase *pOwner);

/**
 *  DisplayDrawRect(MAE_DispId_t nDispId, const Rect_t *pRect, RGBColor_t nClrBorder, RGBColor_t nClrFill, u32 nFlags)
 *
 *  @brief  This function draws a rectangle to the IDisplay
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pRect           [in]Pointer to the rectangle to draw
 *  @param  nClrBorder      [in]Color for border of the rectangle
 *  @param  nClrFill        [in]Color for filling the rectangle
 *  @param  nFlags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
void DisplayDrawRect
(
    MAE_DispId_t	nDispId,
    const Rect_t    *pRect,
    RGBColor_t      nClrBorder,
    RGBColor_t      nClrFill,
	u32				nFlags
);

/**
 *  DisplayDrawHLine(MAE_DispId_t nDispId, s32 x, s32 y, s32 len)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  len             [in]Length of the line
 *
 */
void DisplayDrawHLine(MAE_DispId_t nDispId, s32 x, s32 y, s32 len);

/**
 *  DisplayDrawVLine(MAE_DispId_t nDispId, s32 x, s32 y, s32 len)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  len             [in]Length of the line
 *
 */
void DisplayDrawVLine(MAE_DispId_t nDispId, s32 x, s32 y, s32 len);

/**
 *  DisplayDrawLine(MAE_DispId_t nDispId, s32 x1, s32 y1, s32 x2, s32 y2, u8 nBrushSize, DisplayDottedType_e eType)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  x1              [in]Start x
 *  @param  y1              [in]Start y
 *  @param  x2              [in]End x
 *  @param  y2              [in]End y
 *  @param  nBrushSize      [in]Brush size
 *  @param  eType           [in]Dotted line type
 *
 */
void DisplayDrawLine(MAE_DispId_t nDispId, s32 x1, s32 y1, s32 x2, s32 y2, u8 nBrushSize,DisplayDottedType_e eType);

/**
 *  DisplayGetFontInfo(MAE_DispId_t nDispId, u32 nFontSize, FontInfo *pInfo)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  nFontSize       [in]Font size
 *  @param  pInfo           [out]Pointer of FontInfo to store info
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *  @retval Others              Reference to IFONT_GetInfo();
 *
 */
MAE_Ret DisplayGetFontInfo
(
	MAE_DispId_t	nDispId,
	u32 		    nFontCate,
	u32				nFontSize,
	FontInfo		*pInfo
);

/**
 *  DisplayGetFontInfoEx(MAE_DispId_t nDispId, u32 nFontSize, u32 FontType, FontInfo *pInfo)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  nFontSize       [in]Font size
 *  @param  FontType        [in]Font Type
 *  @param  pInfo           [out]Pointer of FontInfo to store info
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *  @retval Others              Reference to DisplayGetFontInfo();
 *
 */
MAE_Ret DisplayGetFontInfoEx
(
	MAE_DispId_t	nDispId,
	u32 			nFontCate,
	u32				nFontSize,
	u32				FontType,
	FontInfo		*pInfo
);

/**
 *  MAE_Ret DisplayMeasureText(MAE_DispId_t nDispId,
 *                               u32 nFontSize,
 *                               const u16 *pText,
 *                               u32 nLen,
 *                               u32 nMaxWidth,
 *                               u32 *pFits,
 *                               u32 *pPixels,
 *                               u32 nTypes)
 *
 *  @brief  This function counts how many characters can be drawn in the given
 *          width and how many pixels can be drawn with such characters.
 *
 *  @param  nDispId			[in]The specific display id
 *  @param  nFontSize       [in]Font size
 *  @param  pText           [in]Pointer to text buffer
 *  @param  nLen            [in]String length of the text buffer
 *  @param  nMaxWidth       [in]Width to fit in
 *  @param  pFits           [out]Number of character in pText can fit
 *  @param  pPixels         [out]Width of fit characters in pixels
 *  @param  nTypes          [in]Types of the text
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *
 *  Note:
 *    If MaxWidth is set to 0, this function will calculate the length of
 *    entire string of pText.
 *
 */
MAE_Ret DisplayMeasureText
(
	MAE_DispId_t	nDispId,
	u32             nFontCate,
	u32				nFontSize,
	const u16		*pText,
	u32				nLen,
	u32				nMaxWidth,
	u32				*pFits,
	u32				*pPixels,
	u32				nTypes
);

MAE_Ret DisplayMeasureTextEx
(
 MAE_DispId_t	nDispId,
 u32            nFontCate,
 u32				nFontSize,
 const u16		*pText,
 u32				nLen,
 u32				nMaxWidth,
 u32				*pFits,
 u32				*pPixels,
 u32				nTypes,
 boolean			bDispStr
 );

/**
 *  u32 DisplayDrawText(MAE_DispId_t nDispId,
 *                            s32 nFontSize,
 *                            const u16 *pText,
 *                            s32 nLen,
 *                            s32 x,
 *                            s32 y,
 *                            const Rect_t *pRect,
 *                            u32 nTypes)
 *
 *  @brief  This function draws text to the given region.
 *
 *  @param  nDispId			[in]The specific display id
 *  @param  nFontSize       [in]Font size
 *  @param  pText           [in]Pointer to text buffer
 *  @param  nLen            [in]String length of the text buffer
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  pRect           [in]Pointer to the region for draw
 *  @param  nTypes          [in]Types of the text
 *
 *  @retval Reference to the return value of IFONT_DrawText.
 *
 */
u32 DisplayDrawText
(
	MAE_DispId_t		nDispId,
	u32                 nFontCate,
	u32					nFontSize,
	const u16			*pText,
	s32					nLen,
	s32					x,
	s32					y,
	const Rect_t		*pRect,
	u32					nTypes
);

u32 DisplayDrawTextEx
(
 MAE_DispId_t			nDispId,
 u32                 nFontCate,
 u32					nFontSize,
 const u16				*pText,
 s32					nLen,
 s32					x,
 s32					y,
 const Rect_t			*pRect,
 u32					nTypes
 );

/**
 *  DisplayGetDeviceBitmap(MAE_DispId_t nDispId, IBase* pOwner)
 *
 *  @brief  This function returns device IBitmap.
 *
 *  @param  nDispId			[in]The specific display id
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to the device IBitmap.
 *
 */
IBitmap* DisplayGetDeviceBitmap(MAE_DispId_t nDispId, IBase* pOwner);

/**
 *  DisplayGetDestination(MAE_DispId_t nDispId, IBase* pOwner)
 *
 *  @brief  This function returns current destination IBitmap.
 *
 *  @param  nDispId			[in]The specific display id
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to current destination IBitmap.
 *
 */
IBitmap* DisplayGetDestination(MAE_DispId_t nDispId, IBase *pOwner);

/**
 *  DisplayCreateBitmap(MAE_DispId_t nDispId, u16 w, u16 h, IBase* pOwner)
 *
 *  @brief  This function creates a new IBitmap with given width and height.
 *
 *  @param  nDispId			[in]The specific display id
 *  @param  w               [in]width of new IBitmap
 *  @param  h               [in]height of new IBitmap
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to new created IBitmap.
 *
 */
IBitmap* DisplayCreateBitmap(MAE_DispId_t nDispId, u16 w, u16 h, IBase *pOwner);

/**
 *  DisplaySetColor(MAE_DispId_t nDispId, u32 nItemId, RGBColor_t rgb)
 *
 *  @brief  This function set the color of specified color item. Previous color value of the specified item will be returned.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  nItemId         [in]Item ID, use ids defined in ColorItemId_tag
 *  @param  rgb             [in]Color value to set
 *
 *  @retval Previous color value of the specified item.
 *
 */
RGBColor_t DisplaySetColor(MAE_DispId_t nDispId, u32 nItemId, RGBColor_t rgb);

/**
 *  DisplayClearScreen(MAE_DispId_t nDispId)
 *
 *  @brief  This function clears display bitmap with background color.
 *
 *  @param  nDispId          [in]The specific display id
 *
 */
void DisplayClearScreen(MAE_DispId_t nDispId);

/**
 *  DisplaySetCARect(MAE_DispId_t nDispId, const Rect_t *pRcCA)
 *
 *  @brief  This function sets client area of the screen.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pRcCA           [in]Pointer to struct Rect of new client area
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pRcCA is NULL
 *
 */
MAE_Ret DisplaySetCARect(MAE_DispId_t nDispId, const Rect_t *pRcCA);

/**
 *  DisplayGetCARect(MAE_DispId_t nDispId, const Rect_t *pRcCA)
 *
 *  @brief  This function gets client area of the screen.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pRcCA           [out]Pointer to the memory to store struct Rect of client area
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pRcCA is NULL
 *
 *  Note:
 *    If the pRcCA is NULL, the client area will be reset to whole bitmap
 *
 */
MAE_Ret DisplayGetCARect(MAE_DispId_t nDispId, const Rect_t *pRcCA);

/**
 *  DisplaySetDispMode(MAE_DispId_t nDispId, const DisplayMode_e nDispMode)
 *
 *  @brief  This function sets display mode of the IDisplay.
 *
 *  @param  nDispId          [in]The specific display id
 *  @param  nDispMode        [in]New display mode
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp is NULL
 *
 */
MAE_Ret DisplaySetDispMode(MAE_DispId_t nDispId, const DisplayMode_e nDispMode);

/**
 *  DisplayGetDispMode(MAE_DispId_t nDispId, const DisplayMode_e *pDispMode)
 *
 *  @brief  This function gets current display mode of the IDisplay.
 *
 *  @param  nDispId          [in]The specific display id
 *  @param  pDispMode        [out]Pointer to the memory to store display mode
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispMode is NULL
 *
 */
MAE_Ret DisplayGetDispMode(MAE_DispId_t nDispId, const DisplayMode_e *pDispMode);

/**
 *  DisplayGetDisplayId(MAE_DispId_t nDispId, MAE_DispId_t *pDispId)
 *
 *  @brief  This function can get current display id which specifies that the display object is
 *          displayed in main display or sub display.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pDispId         [out]Pointer to the memory to store display id
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispId is NULL
 *
 */
MAE_Ret DisplayGetDisplayId(MAE_DispId_t nDispId, MAE_DispId_t *pDispId);

/**
 *  DisplayUpdate(MAE_DispId_t nDispId, u32 nType)
 *
 *  @brief  This function updates the screen if the IBitmap in the given IDisplay is device bitmap.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  nType           reserved
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispMode is NULL
 *
 */
void DisplayUpdate(MAE_DispId_t nDispId, u32 nType);

/**
 *  DisplayBitBlt(MAE_DispId_t nDispId,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  RasterOp_t nRopCode)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others          Refer to IBITMAP_Bitblt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
MAE_Ret DisplayBitBlt
(
	MAE_DispId_t		nDispId,
	const Rect_t		*pDstRc,
	const IBitmap		*pIBmpSrc,
	const Rect_t		*pSrcRc,
	RasterOp_t			nRopCode
);

/**
 *  DisplayDrawEllipse(MAE_DispId_t nDispId, const Ellipse_t *pEllipse, RGBColor_t nClrBorder, RGBColor_t nClrFill, u32 nFlags)
 *
 *  @brief  This function draws a ellipse to the IDisplay
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pEllipse        [in]Pointer to the ellipse to draw
 *  @param  nClrBorder      [in]Color for border of the ellipse
 *  @param  nClrFill        [in]Color for filling the ellipse
 *  @param  nFlags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
void DisplayDrawEllipse
(
		MAE_DispId_t		nDispId,
		const Ellipse_t		*pEllipse,
		RGBColor_t			nClrBorder,
		RGBColor_t			nClrFill,
		u32					nFlags
);

/**
 *  DisplayDrawArc(MAE_DispId_t nDispId, const Arc_t *pArc, RGBColor_t nClrBorder, RGBColor_t nClrFill, u32 nFlags)
 *
 *  @brief  This function draws a ellipse to the IDisplay
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pArc
 *  @param  nClrBorder      [in]Color for border of the ellipse
 *  @param  nClrFill        [in]Color for filling the ellipse
 *  @param  nFlags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
void DisplayDrawArc
(
		MAE_DispId_t	nDispId,
		const Arc_t		*pArc,
		RGBColor_t		nClrBorder,
		RGBColor_t		nClrFill,
		u32				nFlags
);

/**
 *  DisplayFadeout(MAE_DispId_t nDispId,
 *                   const Rect_t *pDstRc,
 *                   FadeoutLevel_t FadeoutLevel,
 *					 Mae_FadeoutSourceType_e eSourceType)
 *
 *  @brief  This function make the fadeout effect to display buffer according to the destination rectangle and fadeout level.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  FadeoutLevel    [in]Fadeout level, reference to mmi_mae_graphic_types.h
 *  @param  eSourceType

 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval MAE_RET_SUCCESS      Successfully.
 *
 *  Note:
 *
 */
MAE_Ret DisplayFadeout
(
	MAE_DispId_t	nDispId,
	const Rect_t	*pDstRc,
	FadeoutLevel_t	tFdoLevel,
	Mae_FadeoutSourceType_e eSourceType
);

/**
 *  DisplayDrawTriangle(MAE_DispId_t nDispId,
 *                            const Triangle_t *pTriangle,
 *                            RGBColor_t nClrBorder,
 *                            RGBColor_t nClrFill,
 *                            u32 nFlags)
 *
 *  @brief  This function draws a triangle to the IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pTriangle		[in]Pointer to the triangle to draw
 *  @param  nClrBorder		[in]Color for border of the ellipse
 *  @param  nClrFill        [in]Color for filling the ellipse
 *  @param  nFlags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
  *
 *  Note:
 *
 */
void DisplayDrawTriangle
(
	MAE_DispId_t			nDispId,
	const Triangle_t		*pTriangle,
	RGBColor_t				nClrBorder,
	RGBColor_t				nClrFill,
	u32						nFlags
);

/**
 *  DisplayStretchBlt(MAE_DispId_t nDispId,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  RasterOp_t nRopCode)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others				 Refer to IBITMAP_StretchBlt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
MAE_Ret DisplayStretchBlt
(
	MAE_DispId_t		nDispId,
	const Rect_t		*pDstRc,
	const IBitmap		*pIBmpSrc,
	const Rect_t		*pSrcRc,
	RasterOp_t			nRopCode
);

/**
 *  DisplayPerspectiveBlt(MAE_DispId_t nDispId,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  RasterOp_t nRopCode,
 *                  u16 nDir)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  nDispId         [in]The specific display id
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *  @param  nDir          [in]Perspective direction
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others          Refer to IBITMAP_StretchBlt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
MAE_Ret DisplayPerspectiveBlt
(
	MAE_DispId_t		nDispId,
	const Rect_t		*pDstRc,
	const IBitmap		*pIBmpSrc,
	const Rect_t		*pSrcRc,
	RasterOp_t			nRopCode,
	u16					nDir
);

/**
*  DisplayEnableUpdate(MAEDispId_t nDispID)
*
*  @brief  This function enables display to update screen
*
*  @param  nDispID            [in]ID of display to set
*
*  @retval MAE_RET_SUCCESS     Successful
*  @retval MAE_RET_BAD_PARAM   Error display ID
*/
MAE_Ret DisplayEnableUpdate(MAEDispId_t nId);

/**
*  DisplayDisableUpdate(MAEDispId_t nDispID)
*
*  @brief  This function disables display to update screen
*
*  @param  nDispID            [in]ID of display to set
*
*  @retval MAE_RET_SUCCESS     Successful
*  @retval MAE_RET_BAD_PARAM   Error display ID
*/
MAE_Ret DisplayDisableUpdate(MAEDispId_t nDispID);

/**
 *  DisplayUpdateDevice(MAEDispId_t id, boolean bPartial)
 *
 *  @brief  This function forces display to update screen
 *
 *  @param  nDispID            [in]ID of display to set
 *  @param  bPartial          [in]If do partial update
 *
 */
void DisplayUpdateDevice(MAEDispId_t nDispID, boolean bPartial);

/**
 *  DisplayForceUpdateScreen(MAEDispId_t id, boolean bPartial)
 *
 *  @brief  This function forces display to redraw applets and update screen (
 *
 *  @param  None
 *
 */
void DisplayForceUpdateScreen(void);

/**
 *  DisplayLastUpdateIs3DMode(void)
 *
 *  @brief  This function returns if the last update mode is 3D (TRUE) or 2D (FALSE)
 *
 *  @param  None            
 *
 *  @retval TRUE     3D
 *  @retval FALSE   2D
 */
boolean DisplayLastUpdateIs3DMode(void);

#ifdef __DISP_ML_MMI__
/**
 *  DisplayCreateLayer(MAE_DispId_t nDispId,
 *                       DisplayLayer_e layer,
 *                       u32 nWidth,
 *                       u32 nHeight,
 *						 u32 nFormat)
 *
 *  @brief  This function is to create layer according parameter layer.
 *
 *  @param nDispId      [in]The specific display id
 *  @param layer        [in]Identify which layer
 *  @param nWidth       [in]the width of created layer
 *  @param nHeight      [in]the height of created layer
 *  @param nFormat      [in]the format of created layer  (565 with color key, or ARGB888)
 *
 *  @note
 *
 */
MAERet_t DisplayCreateLayer(MAE_DispId_t nDispId, DisplayLayer_e layer, u32 nWidth, u32 nHeight, u32 nFormat);

/**
 *  DisplayReleaseLayer(MAE_DispId_t nDispId,
 *                        DisplayLayer_e layer)
 *
 *  @brief  This function is to release layer according parameter layer.
 *
 *  @param  nDispId       [in]The specific display id
 *  @param  layer         [in]Identify which layer
 *
 *  @note
 *
 */
MAERet_t DisplayReleaseLayer(MAE_DispId_t nDispId, DisplayLayer_e layer);

/**
 *  DisplaySetCurrentLayer(MAE_DispId_t nDispId,
 *                        DisplayLayer_e layer)
 *
 *  @brief  This function is to set current layer according parameter layer.
 *
 *  @param  nDispId       [in]The specific display id
 *  @param  layer         [in]Identify which layer
 *
 *  @note
 *
 */
MAERet_t DisplaySetCurrentLayer(MAE_DispId_t nDispId, DisplayLayer_e layer);

/**
 *  DisplaySetLayerOffset(MAE_DispId_t nDispId,
 *                        DisplayLayer_e layer,
 *						  s32 x,
 *                        s32 y)
 *
 *  @brief  This function is to set the offset of the given layer.
 *
 *  @param  nDispId       [in]The specific display id
 *  @param  layer         [in]Identify which layer
 *  @param  x             [in]x offset of the layer
 *  @param  y             [in]y offset of the layer
 *
 *  @note
 *
 */
MAERet_t DisplaySetLayerOffset(MAE_DispId_t nDispId, DisplayLayer_e layer, s32 x, s32 y);

/**
 *  DisplaySetLayerVisible(MAE_DispId_t nDispId,
 *                        DisplayLayer_e layer,
 *						  u8 bVisible)
 *
 *  @brief  This function is to set the given layer visible.
 *
 *  @param  nDispId       [in]The specific display id
 *  @param  layer         [in]Identify which layer
 *  @param  bVisible      [in]layer visible flag

 *  @note
 *
 */
MAERet_t DisplaySetLayerVisible(MAE_DispId_t nDispId, DisplayLayer_e layer, u8 bVisible);

/**
*  DisplayReleaseAllLayer(MAE_DispId_t nDispId)
*
*  @brief  This function is to merge all layer to base layer
*
*  @param  nDispId         [in]The specific display id

*  @note
*
*/
MAERet_t DisplayReleaseAllLayer(MAE_DispId_t nDispId);

MAERet_t DisplayGetLayerCARect(MAE_DispId_t nDispId, Rect_t* pRc, DisplayLayer_e nLayer);

#endif  // end __DISP_ML_MMI__

//3Dswitch
void DisplaySet3DMode(MAE_DispId_t nDispId, boolean bIsOn);
boolean DisplayGet3DMode(MAE_DispId_t nDispId);


/**
 *  DisplaySetOSDEnableAlphaMask( MAE_DispId_t nDispId, boolean bIsEnable )
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
MAE_Ret DisplaySetOSDEnableAlphaMask( u16 nClsId, MAE_DispId_t nDispId, boolean bIsEnable );

/**
 *  DisplayGetOSDEnableAlphaMask( MAE_DispId_t nDispId )
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
boolean DisplayGetOSDEnableAlphaMask( MAE_DispId_t nDispId );

/**
 *  DisplaySetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency )
 *
 *  @brief  To set Transparency value to camera/videoplayer/camcorder app , give each pixel alpha value by transparency
 *
 *  @param  nDispId              [in] display screen ID
 *  @param  nTransparency        [in] OSD global alpha blending value
 *
 *  @retval 
 *
 *  Note: the default transparency is 255 ( Opaque fully)
 *
 */
MAE_Ret DisplaySetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency );


/**
 *  DisplayGetDPM( MAE_DispId_t nDispId)
 *
 *  @brief  To get the amount of pixels per 10 Centimeters.
 *
 *  @param  nDispId              [in] display screen ID
 *
 *  @retval the amount of pixels per 10 centimeters
 *
 *
 */
u32 DisplayGetDPM( MAE_DispId_t nDispId );

#endif /* __MMI_COMMON_DISPLAY_H__ */

