/**
 * @file mmi_mae_applet.h
 *
 * This header file defines the IApplet interface.
 *
 * Applets are special objects which are not directly used by other components in MAE platform.
 * Their life cycle is controled by the AP manager, and the event handler is called in shell
 * when processing the events. We don't export the macros to use the methods of an applet
 * because other components in MAE platform shall not call the methods of an applet directly.
 *
 * @version $Id: mmi_mae_applet.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MMI_MAE_APPLET_H__
#define __MMI_MAE_APPLET_H__
//
// header files
//
#include "mmi_mae_common_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_graphic_forward.h"

//
// types and definitions
//


//
// IApplet interface
//
// methods of IApplet interface
#ifdef __AP_USE_ML__
#define INHERIT_IApplet(IName) \
	INHERIT_IHandler(IName); \
	void    (*Draw) (IName*, const MAE_DispId_t, Rect_t*, boolean); \
	void    (*DrawOnBmp) (IName*, const MAE_DispId_t, Rect_t*, IBase *); \
	void    (*PrepareTransitionFrame) (IName*); \
	boolean (*IsFullOpaque) (IName*, const MAE_DispId_t); \
	boolean (*GetInvalidateRect) (IName*, const MAE_DispId_t, Rect_t**);\
	void *  (*GetClientTable) (IName*);\
	void *  (*GetCBListModule) (IName*);\
    void    (*DisplayInvisible) (IName*, MAE_DispId_t, boolean);\
	boolean (*Update3DMode) (IName*);\
	void    (*RestoreThm)(IName*)
#else
#define INHERIT_IApplet(IName) \
	INHERIT_IHandler(IName); \
	void    (*Draw) (IName*, const MAE_DispId_t, Rect_t*, boolean); \
	void    (*DrawOnBmp) (IName*, const MAE_DispId_t, Rect_t*, IBase *); \
	void    (*PrepareTransitionFrame) (IName*); \
	boolean (*IsFullOpaque) (IName*, const MAE_DispId_t); \
	boolean (*GetInvalidateRect) (IName*, const MAE_DispId_t, Rect_t*);\
	void *  (*GetClientTable) (IName*);\
	void *  (*GetCBListModule) (IName*);\
    void    (*DisplayInvisible) (IName*, MAE_DispId_t, boolean);\
	boolean (*Update3DMode) (IName*);\
	void    (*RestoreThm)(IName*)
#endif
// defines the base structure of an IApplet object
DEFINE_INTERFACE(IApplet);


/**
* isTop: is this applet at the top of all applets.
*/
#define IAPPLET_Draw(pApplet, DisplayId, pRect, isTop) \
	GET_FUNCTBL((pApplet),IApplet)->Draw((pApplet),DisplayId,pRect,isTop)

#define IAPPLET_DrawOnBmp(pApplet, DisplayId, pRect, pBmp) \
	GET_FUNCTBL((pApplet),IApplet)->DrawOnBmp((pApplet),DisplayId,pRect,pBmp)

#define IAPPLET_PrepareTransitionFrame(pApplet) \
	GET_FUNCTBL((pApplet),IApplet)->PrepareTransitionFrame((pApplet))

/**
*/
#define IAPPLET_IsFullOpaque(pApplet, DisplayId) \
	GET_FUNCTBL((pApplet),IApplet)->IsFullOpaque((pApplet),DisplayId)

/**
*/
#define IAPPLET_GetInvalidateRect(pApplet, DisplayId, pRect) \
	GET_FUNCTBL((pApplet),IApplet)->GetInvalidateRect((pApplet),DisplayId,pRect)

/**
*/
#define IAPPLET_GetClientTable(pApplet) \
	GET_FUNCTBL((pApplet),IApplet)->GetClientTable((pApplet))

/**
*/
#define IAPPLET_GetCBListModule(pApplet) \
	GET_FUNCTBL((pApplet),IApplet)->GetCBListModule((pApplet))

/**
*/
#define IAPPLET_DisplayInvisible(pApplet, nDisp, isInVisable) \
	GET_FUNCTBL((pApplet),IApplet)->DisplayInvisible((pApplet), nDisp, isInVisable)

/**
*/
#define IAPPLET_Update3DMode(pApplet) \
	GET_FUNCTBL((pApplet),IApplet)->Update3DMode((pApplet))
	
/**
*/
#define IAPPLET_RestoreThm(pApplet) \
        GET_FUNCTBL((pApplet),IApplet)->RestoreThm((pApplet))	
/*=============================================================*/
// functions
/*=============================================================*/

#endif	//__MAE_APPLET_H__
// end of file
