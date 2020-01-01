/**
* @file    mmi_mae_dispcanvas.h
* @brief   This file defines the interface of IDispCanvas.
* 
* @version $Id: mmi_mae_dispcanvas.h 38757 2009-08-27 13:09:15Z steve.lee $
*/
#ifndef __MMI_MAE_DISPCANVAS_H__
#define __MMI_MAE_DISPCANVAS_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_bitmap.h"
#include "mmi_mae_display.h"


/*=============================================================*/
// type and define
/*=============================================================*/



/*=============================================================*/
// interface
/*=============================================================*/
//IDispCanvas interface
#ifdef __AP_USE_ML__
#define INHERIT_IDispCanvas(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret   (*SetDisplay)     (IName*, IDisplay*, IBase*); \
	MAE_Ret   (*GetDisplay)     (IName*, IDisplay**, IBase*); \
	MAE_Ret   (*SetBitmap)      (IName*, IBitmap*, IBase*); \
	MAE_Ret   (*GetBitmap)      (IName*, IBitmap**, IBase*); \
	MAE_Ret   (*SetCARect)      (IName*, const Rect_t*); \
	MAE_Ret   (*GetCARect)      (IName*, Rect_t*); \
	MAE_Ret	(*SetLayerCARect)		(IName*, const Rect_t*, DisplayLayer_e); \
	MAE_Ret   (*GetLayerCARect)      (IName*, Rect_t*, DisplayLayer_e); \
	MAE_Ret	(*SetLayer)		 (IName*, DisplayLayer_e); \
	MAE_Ret	(*GetLayer)		 (IName*, DisplayLayer_e*); \
    MAE_Ret   (*SetClientAreaForceFullScreen)      (IName*, boolean); \
    MAE_Ret   (*Set3dMode)      (IName*, boolean); \
    MAE_Ret   (*Get3dMode)      (IName*, boolean*)

#else
#define INHERIT_IDispCanvas(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret   (*SetDisplay)     (IName*, IDisplay*, IBase*); \
	MAE_Ret   (*GetDisplay)     (IName*, IDisplay**, IBase*); \
	MAE_Ret   (*SetBitmap)      (IName*, IBitmap*, IBase*); \
	MAE_Ret   (*GetBitmap)      (IName*, IBitmap**, IBase*); \
	MAE_Ret   (*SetCARect)      (IName*, const Rect_t*); \
    MAE_Ret   (*GetCARect)      (IName*, Rect_t*); \
    MAE_Ret   (*SetClientAreaForceFullScreen)      (IName*, boolean); \
    MAE_Ret   (*Set3dMode)      (IName*, boolean); \
    MAE_Ret   (*Get3dMode)      (IName*, boolean*)
#endif


//INTERFACE_DEFINE(IDispCanvas);
DEFINE_INTERFACE(IDispCanvas);



/** 
* IDISPCANVAS_QueryInterface
* @brief	This function queries another interface from IDispCanvas object. 
*           It will return an interface object which you want to query if successful.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[in]   iid(MAE_IId)            An interface id to be queried.
* @param[out]  ppObj(void**)           A pointer of void pointer to retrieve an interface object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval	MAE_RET_SUCCESS         Success.
* @retval	MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*/
#define IDISPCANVAS_QueryInterface(pIDC,iid,ppObj,pOwner)      GET_FUNCTBL((pIDC),IDispCanvas)->QueryInterface(pIDC,iid,ppObj,pOwner)

/**
* IDISPCANVAS_SetDisplay(IDispCanvas* pIDC, IDisplay* pID, IBase* pOwner)
*
* @brief  This function sets new IDisplay to the IDisplayCanvas.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[in]   pID(IDisplay*)          A pointer of new IDisplay to set to canvas
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval MAE_RET_SUCCESS           Success
*
* @note  IDISPLAY_AddRef will be called on new IDisplay.
*        IDISPLAY_Release will be called on old IDisplay.
*
*/
#define IDISPCANVAS_SetDisplay(pIDC,pID,pOwner)            GET_FUNCTBL((pIDC),IDispCanvas)->SetDisplay(pIDC,pID,pOwner)

/**
* IDISPCANVAS_GetDisplay(IDispCanvas* pIDC, IDisplay** ppID, IBase* pOwner)
*
* @brief  This function gets current IDisplay in the IDisplayCanvas.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[out]  ppID(IDisplay**)        A pointer of IDisplay pointer to retrieve an IDisplay object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
*
*/
#define IDISPCANVAS_GetDisplay(pIDC,ppID,pOwner)           GET_FUNCTBL((pIDC),IDispCanvas)->GetDisplay(pIDC,ppID,pOwner)

/**
* IDISPCANVAS_SetBitmap(IDispCanvas* pIDC, IBitmap* pIB, IBase* pOwner)
*
* @brief  This function sets new destination IBitmap to the IDisplay in the IDisplayCanvas.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[in]   pIB(IBitmap*)           A pointer of new IBitmap to set to canvas
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
*
* @note  If pIB is NULL, system destination IBitmap will be set to IDisplayCanvas.
*        IBITMAP_AddRef will be called on new destinateion bitmap.
*        IBITMAP_Release will be called on old destinateion bitmap.
*
*/
#define IDISPCANVAS_SetBitmap(pIDC,pIB,pOwner)             GET_FUNCTBL((pIDC),IDispCanvas)->SetBitmap(pIDC, pIB,pOwner)

/**
* IDISPCANVAS_GetBitmap(IDispCanvas* pIDC, IBitmap** ppIB, IBase* pOwner)
*
* @brief  This function gets current destination IBitmap of the IDisplay in the IDisplayCanvas.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[out]  ppIB(IBitmap**)         A pointer of IBitmap pointer to retrieve an IBitmap object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
*
*/
#define IDISPCANVAS_GetBitmap(pIDC,ppIB,pOwner)            GET_FUNCTBL((pIDC),IDispCanvas)->GetBitmap(pIDC, ppIB,pOwner)

/**
* IDISPCANVAS_SetCARect(IDispCanvas* pIDC, const Rect_t* pRC)
*
* @brief  This function sets client area of the display canvas.
*
* @param[in]   pIDC(IDispCanvas*)      A pointer of IDispCanvas interface object.
* @param[in]   pRC(const Rect_t*)      Pointer to struct Rect of new client area
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given pRC is NULL
*
*/
#define IDISPCANVAS_SetCARect(pIDC,pRC)           GET_FUNCTBL((pIDC),IDispCanvas)->SetCARect(pIDC, pRC)

/**
* IDISPCANVAS_GetCARect(IDispCanvas* pIDC, Rect_t* pRC)
*
* @brief  This function gets client area of the display canvas.
*
* @param[in]   pIDC(IDispCanvas*)      Pointer to the IDispCanvas interface object
* @param[in]   pRC(Rect_t*)            Pointer to the memory to store struct Rect of client area
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given pRC is NULL
*
* @note  If the pRC is NULL, the client area will be reset to whole display canvas
*
*/
#define IDISPCANVAS_GetCARect(pIDC,pRC)           GET_FUNCTBL((pIDC),IDispCanvas)->GetCARect(pIDC, pRC)

#ifdef __AP_USE_ML__
/**
* IDISPCANVAS_SetLayerCARect(IDispCanvas* pIDC, Rect_t* pRC, DisplayLayer_e nLayer)
*
* @brief  This function gets client area of the display canvas.
*
* @param[in]   pIDC(IDispCanvas*)      Pointer to the IDispCanvas interface object
* @param[in]   pRC(Rect_t*)            Pointer to the memory to store struct Rect of client area
* @param[in]	 nLayer						specify the layer
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given pRC is NULL
*
* @note  If the pRC is NULL, the client area will be reset to whole display canvas
*
*/
#define IDISPCANVAS_SetLayerCARect(pIDC,pRC,nLayer)           GET_FUNCTBL((pIDC),IDispCanvas)->SetLayerCARect(pIDC, pRC,nLayer)

/**
* IDISPCANVAS_GetLayerCARect(IDispCanvas* pIDC, Rect_t* pRC, DisplayLayer_e nLayer)
*
* @brief  This function gets client area of the display canvas.
*
* @param[in]   pIDC(IDispCanvas*)      Pointer to the IDispCanvas interface object
* @param[in]   pRC(Rect_t*)            Pointer to the memory to store struct Rect of client area
* @param[in]	 nLayer						specify the layer
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given pRC is NULL
*
* @note  If the pRC is NULL, the client area will be reset to whole display canvas
*
*/
#define IDISPCANVAS_GetLayerCARect(pIDC,pRC,nLayer)           GET_FUNCTBL((pIDC),IDispCanvas)->GetLayerCARect(pIDC, pRC,nLayer)
/**
* IDISPCANVAS_SetLayer(IDispCanvas* pIDC, DisplayLayer_e nLayer)
*
* @brief  This function sets the used layer of the IDisplay
*
* @param[in]   pIDC(IDispCanvas*)      Pointer to the IDispCanvas interface object
* @param[in]   nLayer(DisplayLayer_e)            indicate the layer
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given nLayer is illegal
*
*/
#define IDISPCANVAS_SetLayer(pIDC,nLayer)           GET_FUNCTBL((pIDC),IDispCanvas)->SetLayer(pIDC, nLayer)

/**
* IDISPCANVAS_GetLayer(IDispCanvas* pIDC, DisplayLayer_e *pLayer)
*
* @brief  This function gets the used layer of the IDisplay
*
* @param[in]   pIDC(IDispCanvas*)      Pointer to the IDispCanvas interface object
* @param[in]   pLayer(DisplayLayer_e)            indicate the returned layer
*
* @retval MAE_RET_SUCCESS           Success
* @retval MAE_RET_FAILED            If there is no IDisplay in the IDisplayCanvas
* @retval MAE_RET_BAD_PARAM         If given nLayer is illegal
*
*/
#define IDISPCANVAS_GetLayer(pIDC,pLayer)           GET_FUNCTBL((pIDC),IDispCanvas)->GetLayer(pIDC, pLayer)

#endif

#define IDISPCANVAS_SetClientAreaForceFullScreen(pIDC,bOn)           GET_FUNCTBL((pIDC),IDispCanvas)->SetClientAreaForceFullScreen(pIDC, bOn)

#define IDISPCANVAS_Set3dMode(pIDC,bOn)           GET_FUNCTBL((pIDC),IDispCanvas)->Set3dMode(pIDC, bOn)
#define IDISPCANVAS_Get3dMode(pIDC,pbOn)           GET_FUNCTBL((pIDC),IDispCanvas)->Get3dMode(pIDC, pbOn)

/*=============================================================*/
// functions
/*=============================================================*/



#endif	//__MAE_DISPCANVAS_H__
/*=============================================================*/
// end of file
