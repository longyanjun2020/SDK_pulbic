/*!
*  @file mmi_mae_bitmap.h
*
*  @This file contains the IBITMAP API.
*
*  @author SteveLee@MStar
*  @version $Id: mmi_mae_bitmap.h 291 2009-02-27 13:08:01Z kenny.wu $
*/

#ifndef __MMI_MAE_BITMAP_H__
#define __MMI_MAE_BITMAP_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_bitmap_forward.h"
#include "mmi_mae_graphic_forward.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_dib_forward.h"
/*
----------------------------
| IBitmap                  |
|   ---------------------  |
|   | BitmapBase        |  |
|   |   --------------  |  |
|   |   | DIB        |  |  |
|   |   |            |  |  |
|   |   |            |  |  |
|   |   |            |  |  |
|   |   --------------  |  |
|   ---------------------  |
----------------------------
*/

#define INHERIT_IBitmap(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret     (*GetInfo)    (IName*, BitmapInfo_t*); \
	MAE_Ret     (*GetPixel)   (IName*, u32, u32, RGBColor_t*); \
	MAE_Ret     (*SetPixel)   (IName*, u32, u32, RGBColor_t, RasterOp_t); \
	MAE_Ret     (*SetPixels)  (IName*, u32, Point_t*, RGBColor_t, RasterOp_t); \
	MAE_Ret     (*GetTransInfo)     (IName*, TransparentInfo_t*); \
	MAE_Ret     (*SetTransInfo)     (IName*, TransparentInfo_t*); \
	MAE_Ret     (*GetTransType)     (IName*, u32*); \
	MAE_Ret     (*SetTransType)     (IName*, u32); \
	MAE_Ret     (*GetTransColor)    (IName*, RGBColor_t*); \
	MAE_Ret     (*SetTransColor)    (IName*, RGBColor_t*); \
	MAE_Ret     (*GetTransMask)     (IName*, u8**, u32*); \
	MAE_Ret     (*SetTransMask)     (IName*, u32, u8*, u32); \
	MAE_Ret     (*CreateAlphaMask)     (IName*,u8); \
	MAE_Ret     (*GetTransparency)    (IName*, u8*); \
	MAE_Ret     (*SetTransparency)    (IName*, u8); \
	MAE_Ret     (*DrawHLine)  (IName*, u32, u32, u32, RGBColor_t, RasterOp_t); \
	MAE_Ret     (*DrawVLine)  (IName*, u32, u32, u32, RGBColor_t, RasterOp_t); \
	MAE_Ret     (*FillRect)   (IName*, const Rect_t*, RGBColor_t, RasterOp_t); \
	MAE_Ret     (*BltIn)      (IName*, const Rect_t*, IBitmap*, const Rect_t*, RasterOp_t); \
	MAE_Ret     (*GetDib)     (IName*, void**);\
	MAE_Ret     (*StretchBlt)      (IName*, const Rect_t*, IBitmap*, const Rect_t*,  RasterOp_t, u32);\
	MAE_Ret     (*PerspectiveBlt)      (IName*, const Rect_t*, IBitmap*, const Rect_t*,  RasterOp_t, u32, u16);\
	MAE_Ret     (*SetGradientAlphaMask)(IName*, u32, u8, u8)

DEFINE_INTERFACE(IBitmap);

/* Bmp create functions */

/*! @brief This function creates a IBitmap object with the given BitmapInfo
*
*  @param [out]ppIBmp Pointer to the memory to store the pointer of new IBitmap
*  @param [in] pinfo  Pointer to BitmapInfo of the new IBitmap
*  @param [in] pOwner The owner instance which intends to create IBitmap
*
*  @return Error code
*/
MAE_Ret IBITMAP_NewFromBmpinfo(IBitmap **ppIBmp, BitmapInfo_t *pInfo, IBase* pOwner);

/*! @brief This function creates a IBitmap object with the given IDIB
*
*  @param [out]ppIBmp Pointer to the memory to store the pointer of new IBitmap
*  @param [in] pdib   Pointer to DIB to create IBitmap
*  @param [in] pOwner The owner instance which intends to create IBitmap
*
*  @return Error code
*
*  @note User should not release the DIB before the created IBitmap is freed
*        After the IBitmap is freed, user should release the DIB.
*/
MAE_Ret IBITMAP_NewFromDib(IBitmap **ppIBmp, pDIB pDib, IBase* pOwner);

/*! @brief This function creates a IBitmap object with the given BitmapBase_t
*
*  @param [out]ppIBmp       Pointer to the memory to store the pointer of new IBitmap
*  @param [in] pBitmapBase  Pointer to BitmapBase_t to create IBitmap
*  @param [in] pOwner       The owner instance which intends to create IBitmap
*
*  @return Error code
*
*  @note User should not release pBitmapBase before the created IBitmap is freed
*        After the IBitmap is freed, user should release pBitmapBase.
*/
MAE_Ret IBITMAP_NewFromBmpBase(IBitmap **ppIBmp, BitmapBase_t *pBitmapBase, IBase *pOwner);

/*! @brief This function queries interfaces of the given IBitmap */
#define IBITMAP_QueryInterface(pIbmp,id,pp,pOwner)      GET_FUNCTBL(pIbmp,IBitmap)->QueryInterface(pIbmp,id,pp,pOwner)

/*! @brief This function gets bitmap information of an IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [out]p1    Pointer to the memory to fill with struct BitmapInfo
*
*  @return Error code
*/
#define IBITMAP_GetInfo(pIbmp,p1)                GET_FUNCTBL(pIbmp,IBitmap)->GetInfo(pIbmp,p1)

/*! @brief This function gets the color of given point on the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] x     x position of the point
*  @param [in] y     y position of the point
*  @param [out]pclr  Pointer to the memory to fill with the color of the point
*
*  @return Error code
*/
#define IBITMAP_GetPixel(pIbmp,x,y,pclr)         GET_FUNCTBL(pIbmp,IBitmap)->GetPixel(pIbmp,x,y,pclr)

/*! @brief This function sets the color to the given point on the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] x     x position of the point
*  @param [in] y     y position of the point
*  @param [in] clr   RGBColor_t to set to the point
*  @param [in] rop   Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*/
#define IBITMAP_SetPixel(pIbmp,x,y,clr,rop)      GET_FUNCTBL(pIbmp,IBitmap)->SetPixel(pIbmp,x,y,clr,rop)

/*! @brief This function sets the color to the points in the point list on the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] c     Count of the pointer list
*  @param [in] p1    Pointer to a pointer list to set color
*  @param [in] clr   RGBColor_t to set
*  @param [in] rop   Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*/
#define IBITMAP_SetPixels(pIbmp,c,p1,clr,rop)    GET_FUNCTBL(pIbmp,IBitmap)->SetPixels(pIbmp,c,p1,clr,rop)

/*! @brief This function gets the transparent info of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [out]pInfo Pointer to the memory to fill with transparent info
*
*  @return Error code
*/
#define IBITMAP_GetTransInfo(pIbmp,pInfo)            GET_FUNCTBL(pIbmp,IBitmap)->GetTransInfo(pIbmp,pInfo)

/*! @brief This function sets the transparent info to the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] pInfo Pointer transparent info structure to set to IBitmap
*
*  @return Error code
*/
#define IBITMAP_SetTransInfo(pIbmp,pInfo)            GET_FUNCTBL(pIbmp,IBitmap)->SetTransInfo(pIbmp,pInfo)

/*! @brief This function gets the transparent type of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [out]p     Pointer to the memory to fill with transparent type
*
*  @return Error code
*/
#define IBITMAP_GetTransType(pIbmp,p)            GET_FUNCTBL(pIbmp,IBitmap)->GetTransType(pIbmp,p)

/*! @brief This function sets the transparent type of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] t     Transparent type to set to the IBitmap
*
*  @return Error code
*/
#define IBITMAP_SetTransType(pIbmp,t)            GET_FUNCTBL(pIbmp,IBitmap)->SetTransType(pIbmp,t)

/*! @brief This function gets the transparent color of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [out]pclr  Pointer to the memory to fill with transparent color
*
*  @return Error code
*/
#define IBITMAP_GetTransColor(pIbmp,pclr)        GET_FUNCTBL(pIbmp,IBitmap)->GetTransColor(pIbmp,pclr)

/*! @brief This function sets the transparent type of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] pclr  Pointer to the transparent color to set to the IBitmap
*
*  @return Error code
*
*  Note: (1)If pclr==NULL, the transparent type of the IBitmap will be reset to TRANS_NONE
*        (2)If pclr!=NULL, the transparent type of the IBitmap will be reset to TRANS_COLOR
*/
#define IBITMAP_SetTransColor(pIbmp,pclr)        GET_FUNCTBL(pIbmp,IBitmap)->SetTransColor(pIbmp,pclr)

/*! @brief This function gets the transparent mask of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] ppm   Pointer to the memory to fill with transparent mask
*  @param [out]ps    Pointer to the memory to fill with size of the transparent mask(in bytes)
*
*  @return Error code
*/
#define IBITMAP_GetTransMask(pIbmp,ppm,ps)       GET_FUNCTBL(pIbmp,IBitmap)->GetTransMask(pIbmp,ppm,ps)

/*! @brief This function sets the transparent mask of the IBitmap
*				IBITMAP_CreateAlphaMask and IBITMAP_SetTransMask are mutually exclusive, you should only apply one.
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] b     Bits of transparent info for each pixel, now support 8 bits only.
*  @param [in] pm    Pointer to the transparent mask
*  @param [in] s     Size of transparent mask in bytes
*
*  @return Error code
*
*  @note Old transparent mask will be freed
*/
#define IBITMAP_SetTransMask(pIbmp,b,pm,s)       GET_FUNCTBL(pIbmp,IBitmap)->SetTransMask(pIbmp,b,pm,s)

/*! @brief This function create and set the u8 transparent mask for the IBitmap, 
*		        the size is width*height of the IBitmap. And also set transparent type to TRANS_ALPHA.
*				IBITMAP_CreateAlphaMask and IBITMAP_SetTransMask are mutually exclusive, you should only apply one.
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] nInitValue The initial value to be memset on the alpha mask, should be 0~255
*
*  @return Error code
*
*  @note If old transparent mask exist, only memset the initial value
*/
#define IBITMAP_CreateAlphaMask(pIbmp,nInitValue)       GET_FUNCTBL(pIbmp,IBitmap)->CreateAlphaMask(pIbmp,nInitValue)

/*! @brief This function gets the transparency info of the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [out]pt   Pointer to the memory to store transparency
*
*  @return Error code
*/
#define IBITMAP_GetTransparency(pIbmp,pt)       GET_FUNCTBL(pIbmp,IBitmap)->GetTransparency(pIbmp,pt)

/*! @brief This function sets the transparency to the IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] t     Transparency value. 0 to 255, 255 is full transparent
*
*  @return Error code
*
*  @note Old transparent mask will be freed
*/
#define IBITMAP_SetTransparency(pIbmp,t)       GET_FUNCTBL(pIbmp,IBitmap)->SetTransparency(pIbmp,t)

/*! @brief This function draws a horizontal line on the given IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] x     x start position of the point
*  @param [in] y     y start position of the point
*  @param [in] l     Length of the line to draw in pixels
*  @param [in] clr   RGBColor_t to draw
*  @param [in] rop   Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*/
#define IBITMAP_DrawHLine(pIbmp,x,y,l,clr,rop)   GET_FUNCTBL(pIbmp,IBitmap)->DrawHLine(pIbmp,x,y,l,clr,rop)

/*! @brief This function draws a vertical line on the given IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] x     x start position of the point
*  @param [in] y     y start position of the point
*  @param [in] l     Length of the line to draw in pixels
*  @param [in] clr   RGBColor_t to draw
*  @param [in] rop   Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*/
#define IBITMAP_DrawVLine(pIbmp,x,y,l,clr,rop)   GET_FUNCTBL(pIbmp,IBitmap)->DrawVLine(pIbmp,x,y,l,clr,rop)

/*! @brief This function draws a rectangular on the given IBitmap
*
*  @param [in] pIbmp Pointer to the IBitmap
*  @param [in] prc   Pointer to the struct Rect to draw
*  @param [in] clr   RGBColor_t to draw
*  @param [in] rop   Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*/
#define IBITMAP_FillRect(pIbmp,prc,clr,rop)      GET_FUNCTBL(pIbmp,IBitmap)->FillRect(pIbmp,prc,clr,rop)

/*! @brief This function blits an area of source IBitmap to destination IBitmap
*
*  @param [in] pIbmp  Pointer to the destination IBitmap
*  @param [in] pDstRc Pointer to the area of source IBitmap to blit in
*  @param [in] pSrc   Pointer to the source IBitmap
*  @param [in] pSrcRc Pointer to the area of source IBitmap to blit to destination IBitmap
*  @param [in] rop    Raster operation code, refer to definition of RasterOp_t.
*
*  @return Error code
*
*  Note: Now only supports the same size blit
*/
#define IBITMAP_BltIn(pIbmp,pDstRc,pSrc,pSrcRc,rop)  GET_FUNCTBL(pIbmp,IBitmap)->BltIn(pIbmp,pDstRc,pSrc,pSrcRc,rop)

/*! @brief This function gets the DIB of the given IBitmap
*
*  @param [in] pIbmp Pointer to the destination IBitmap
*  @param [out]pp    Pointer to the memory to fill with DIB pointer
*
*  @return Error code
*/
#define IBITMAP_GetDib(pIbmp,pp)                 GET_FUNCTBL(pIbmp,IBitmap)->GetDib(pIbmp,pp)

/*! @brief This function stretch blits an area of source IBitmap to destination IBitmap
*
*  @param [in] pIbmp  Pointer to the destination IBitmap
*  @param [in] pDstRc Pointer to the area of source IBitmap to blit in
*  @param [in] pSrc   Pointer to the source IBitmap
*  @param [in] pSrcRc Pointer to the area of source IBitmap to blit to destination IBitmap
*  @param [in] rop    Raster operation code, refer to definition of RasterOp_t.
*  @param [in] t    BitmapBlitType_e
*
*  @return Error code
*
*  Note: supports different size blit (scale up, scale down, ...)
*/
#define IBITMAP_StretchBlt(pIbmp,pDstRc,pSrc,pSrcRc,rop,t)  GET_FUNCTBL(pIbmp,IBitmap)->StretchBlt(pIbmp,pDstRc,pSrc,pSrcRc,rop,t)

/*! @brief This function perspective blits an area of source IBitmap to destination IBitmap
*
*  @param [in] pIbmp  Pointer to the destination IBitmap
*  @param [in] pDstRc Pointer to the area of source IBitmap to blit in
*  @param [in] pSrc   Pointer to the source IBitmap
*  @param [in] pSrcRc Pointer to the area of source IBitmap to blit to destination IBitmap
*  @param [in] rop    Raster operation code, refer to definition of RasterOp_t.
*  @param [in] t    BLIT_TYPE
*  @param [in] nDir    direction
*
*  @return Error code
*
*/
#define IBITMAP_PerspectiveBlt(pIbmp,pDstRc,pSrc,pSrcRc,rop,t,nDir)  GET_FUNCTBL(pIbmp,IBitmap)->PerspectiveBlt(pIbmp,pDstRc,pSrc,pSrcRc,rop,t,nDir)


/*! @brief This function set a gradient alpha mask to destination IBitmap
*
*  @param [in] pIbmp  Pointer to the destination IBitmap
*  @param [in] nDir   direction( the vaule of nDir : DIRECTION_LEFT/ DIRECTION_RIGHT/ DIRECTION_UP/  DIRECTION_DOWN) 
*  @param [in] nMaxAlpha   the maximun alpha value
*  @param [in] nMinAlpha   the minimun alpha value
*
*  @return Error code
*
*/
#define IBITMAP_SetGradientAlphaMask( pIbmp, nDir, nMaxAlpha, nMinAlpha)  GET_FUNCTBL(pIbmp,IBitmap)->SetGradientAlphaMask( pIbmp, nDir, nMaxAlpha, nMinAlpha)

/*! @brief This function use to change the color format of pIbmpSrc into pIbmp, 
*                currently only support 8 bit convert to 16 bit now
*
*  @param [in] pIbmp  Pointer to the destinate IBitmap, should be 16 bits format
*  @param [in] pIbmp  Pointer to the source IBitmap, should be 8 bits format
*
*  @return Error code
*
*/
MAE_Ret IBITMAP_ChangeFormat(IBitmap *pIBmp, IBitmap *pIBmpSrc);

#define SWAP(A,B) do{(A)^=(B);(B)^=(A);(A)^=(B);}while(0)
/*
	Convert coordinate of the given rect. 90 degree counter-clockwise.
 */
#define RcCvrt90CCW(_pRc,_W,_H) do{SWAP((_pRc)->x,(_pRc)->y); \
	                               (_pRc)->y=(_W)-(_pRc)->y-(_pRc)->w; \
	                               SWAP((_pRc)->w,(_pRc)->h);}while(0)
/*
	Convert coordinate of the given rect. 90 degree clockwise.
 */
#define RcCvrt90CW(_pRc,_W,_H) do{SWAP((_pRc)->x,(_pRc)->y); \
	                              (_pRc)->x=(_H)-(_pRc)->x-(_pRc)->h; \
	                              SWAP((_pRc)->w,(_pRc)->h);}while(0)
/*
	Convert coordinate of the given rect. 180 degree clockwise.
 */
#define RcCvrt180(_pRc,_W,_H) do{(_pRc)->x=(_W)-(_pRc)->x-(_pRc)->w; \
	                             (_pRc)->y=(_H)-(_pRc)->y-(_pRc)->h;}while(0)

/*
	Convert coordinate of the given point. 90 degree counter-clockwise.
 */
#define PntCvrt90CCW(_x,_y,_W,_H) do{SWAP((_x),(_y)); \
                                     (_y) = (_W)-1-(_y);}while(0)
/*
	Convert coordinate of the given point. 90 degree clockwise.
 */
#define PntCvrt90CW(_x,_y,_W,_H) do{SWAP((_x),(_y)); \
                                    (_x) = (_H)-1-(_x);}while(0)
/*
	Convert coordinate of the given point. 180 degree clockwise.
 */
#define PntCvrt180(_x,_y,_W,_H) do{(_x) = (_W)-1-(_x); \
                                   (_y) = (_H)-1-(_y);}while(0)

#endif //__MAE_BITMAP_H__
