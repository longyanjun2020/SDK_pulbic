/**
* @file mae_dispcanvas_priv.h
*
* @version $Id: mae_dispcanvas_priv.h 8943 2008-04-11 04:37:49Z steve.lee $
*/

#ifndef __MAE_DISPCANVAS_PRIV_H__
#define __MAE_DISPCANVAS_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_dispcanvas.h"


/*=============================================================*/
// type and define
/*=============================================================*/
//the main structure for a DispCanvas
typedef struct {
	DECLARE_FUNCTBL(IDispCanvas);      //function table pointer
	u32               RefCnt;         //reference count
	IDisplay         *IDisplayObj;    //this is a pointer of model listener link list
#ifdef __AP_USE_ML__
    DisplayLayer_e     nCurLayer;    // indicate the layer of buffer in pDisp 
#if defined(__G3D_MMI__)
    u32              bClientAreaForceFullScreen;
    u32			     bIs3DOn:1;
#endif    
#endif
} DispCanvas_t;




/*=============================================================*/
// functions
/*=============================================================*/
u32 DispCanvas_AddRef(IDispCanvas *pIDispCanvas);
u32 DispCanvas_Release(IDispCanvas *pIDispCanvas);
MAE_Ret DispCanvas_QueryInterface(IDispCanvas *pIDispCanvas, MAE_IId iId, void **ppObj, IBase *pOwner);
MAE_Ret DispCanvas_SetDisplay(IDispCanvas *pIDispCanvas, IDisplay *pIDisplay, IBase *pOwner);
MAE_Ret DispCanvas_GetDisplay(IDispCanvas *pIDispCanvas, IDisplay **ppIDisplay, IBase *pOwner);
MAE_Ret DispCanvas_SetBitmap(IDispCanvas *pIDispCanvas, IBitmap *pIBitmap, IBase *pOwner);
MAE_Ret DispCanvas_GetBitmap(IDispCanvas *pIDispCanvas, IBitmap **ppIBitmap, IBase *pOwner);
MAE_Ret DispCanvas_SetCARect(IDispCanvas *pIDispCanvas, const Rect_t *pRect);
MAE_Ret DispCanvas_GetCARect(IDispCanvas *pIDispCanvas, Rect_t *pRect);

MAE_Ret DispCanvas_New(MAE_ClsId ClsId, void **ppDispCanvasObj);
void DispCanvasStrucInit(DispCanvas_t *pThis, const FUNCTBL(IDispCanvas) *FtblPtr);

#ifdef __AP_USE_ML__
MAE_Ret DispCanvas_SetLayerCARect(IDispCanvas *pIDispCanvas, const Rect_t *pRect, DisplayLayer_e nLayer);
MAE_Ret DispCanvas_GetLayerCARect(IDispCanvas *pIDispCanvas, Rect_t *pRect, DisplayLayer_e nLayer);
MAE_Ret DispCanvas_SetLayer(IDispCanvas *pIDispCanvas, DisplayLayer_e nLayer);
MAE_Ret DispCanvas_GetLayer(IDispCanvas *pIDispCanvas, DisplayLayer_e *pLayer);
#endif

MAE_Ret DispCanvas_SetClientAreaForceFullScreen(IDispCanvas *pIDispCanvas, boolean bOn);

MAE_Ret DispCanvas_Set3dMode(IDispCanvas *pIDispCanvas, boolean bOn);
MAE_Ret DispCanvas_Get3dMode(IDispCanvas *pIDispCanvas, boolean *pbOn);

#endif //__MAE_DISPCANVAS_PRIV_H__
/*=============================================================*/
// end of file
