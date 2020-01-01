/**
* @file		mmi_wdg_viewercontainer_priv.h
* @version	$Id: mmi_wdg_viewercontainer_priv.h 37261 2009-08-05 12:20:57Z steve.lee $
* @brief	
*
*/
#ifndef __MMI_WDG_VIEWERCONTAINER_PRIV_H__
#define __MMI_WDG_VIEWERCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_viewercontainer.h"
#include "mae_containerbase.h"
#include "mae_wdgbackground.h"
#include "mmi_layout.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/**
* Main data structure for a viewer-container.
*/
typedef struct {
	ContainerBase_t  CntrBase;    ///< Use this as a base structure.
	s32              nOffsetX;    ///< x coordinate offset for layout. Should NOT be minus.
	s32              nOffsetY;    ///< y coordinate offset for layout. Should NOT be minus.
	RGBColor_t       FocusBorderClr; ///< This is a temporary solution to draw focus widget's border
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv       *pITouchSrv;  ///< Touch service pointer.
	s32              nTsStartX;   ///< Used to keep the touch pressed x position.
	s32              nTsStartY;   ///< Used to keep the touch pressed y position.
	s32              nTsStartOffsetX; ///< record the nOffsetX while receiving touch press event
	s32              nTsStartOffsetY; ///< record the nOffsetY while receiving touch press event
#endif //__TOUCH_SCREEN_MMI__
	u16              nStep;       ///< every moving step in pixels by touch on scroll
	MAE_Key_t        MoveNextKey; ///< the key value to move focus to next widget
	MAE_Key_t        MovePrevKey; ///< the key value to move focus to previous widget
	MAE_Key_t        nUpKeyCode;      ///< the Key value to scroll up
	MAE_Key_t        nDownKeyCode;    ///< the Key value to scroll down
	MAE_Key_t        nLeftKeyCode;    ///< the Key value to scroll left
	MAE_Key_t        nRightKeyCode;   ///< the Key value to scroll right

	/// the following is status flags
#ifdef __TOUCH_SCREEN_MMI__
	u8               bIsTouchPressed; ///< If this container is touch pressed now.
#endif //__TOUCH_SCREEN_MMI__
	
} _ViewerContainer_t;


/**
* Data structure of widget cell in viewer-container
*/
typedef struct {
	WidgetCell_t    WCellBase;    ///< A widget cell base data structure.
	s32             original_x;
	s32             original_y;
	u32             bCanFocus : 1;    ///< A flag to indicate if this child widget cell can be focused.
	u32             bDrawFocusBorder : 1;    ///< A flag to indicate if need to draw border when this cell is focused.
} _ViewerCntWdgCell_t;


enum {
	DIR_VERTICAL = 0,
	DIR_HORIZONTAL,
	DIR_END
};
typedef u8 _Direction_et;

#define DEF_MOVE_STEP_PIXELS MAIN_LCD_ONELINE_HEIGHT

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret ViewerContainer_New(MAEClsId_t ClsID, void **ppObj);
boolean _ViewerContainer_DefHandleEvent(IContainer *pIC, MAEEvent_t evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t ViewerContainer_Ctor(_ViewerContainer_t *pThis);
void ViewerContainer_Dtor(_ViewerContainer_t *pThis);


void ViewerContainer_SetSize(IContainer *pIViewerCntr,
								 WidgetSize_t *pWSize);
void ViewerContainer_GetPreferredSize(IContainer *pIViewerCntr,
                                      WidgetSize_t *pSize);

MAERet_t ViewerContainer_Add(IContainer *pIViewerCntr,
                             IWidget *WidgetPtr, 
                             IWidget *RefWidgetPtr, 
                             boolean isUpper, 
                             const void *DescPtr);
MAERet_t ViewerContainer_Delete(IContainer *pIViewerCntr,
                                IWidget *WidgetPtr);
void ViewerContainer_Invalidate(IContainer *pIViewerCntr, 
                                IWidget *WidgetPtr, 
                                const Rect_t *WRectPtr, 
                                InvFlag_t Flags);

MAERet_t ViewerContainer_SetPosAndFocus(IContainer *pIViewerCntr, 
                                        IWidget *pWdg,
                                        const WViewerDesc_t *pstDesc);
MAERet_t ViewerContainer_GetPosAndFocus(IContainer *pIViewerCntr, 
                                        IWidget *pWdg,
                                        WViewerDesc_t *pstDesc ///< output
                                        );

#endif //__MMI_WDG_VIEWERCONTAINER_PRIV_H__
/*=============================================================*/
// end of file
