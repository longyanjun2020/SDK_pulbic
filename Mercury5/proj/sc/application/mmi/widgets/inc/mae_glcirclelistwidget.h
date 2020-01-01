/**
 * @file    mae_glcirclewidget.h
 * @brief   This file defines the interface of 3D circle list widget
 * @version $Id$
 */

#ifndef __MAE_GLCIRCLELISTWIDGET_H__
#define __MAE_GLCIRCLELISTWIDGET_H__

#if defined(__3D_UI_KINGMOVIE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

enum
{
	GLCLWDG_MAX_DISP_FIVE = 5,
	GLCLWDG_MAX_DISP_SEVEN = 7,
    GLCLWDG_MAX_DISP_NINE = 9,	
    GLCLWDG_MAX_DISP_NONE
};
typedef u8 GLCircleListMaxDispNum_e;

enum
{
	GLCLWDG_ANIM_TYPE_SLIDE = 0,
	GLCLWDG_ANIM_TYPE_ZOOMIN,
	GLCLWDG_ANIM_TYPE_ZOOMOUT,	
	GLCLWDG_ANIM_TYPE_NONE
};
typedef u8 GLCircleListAnimType_e;

/** PfnWdgGlCircleListWdgEventCB
* @brief
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  param             Relative info
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgGlCircleListWdgEventCB) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** WdgGlCircleListWdgRegisterSlideAnimDoneEventCb
* @brief        Register callback
*
* @param[in]    pGlClWdg                Pointer to the GlCircleListWdg
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgGlCircleListWdgRegisterSlideAnimDoneEventCb
(
    IWidget                         *pGlClWdg,
    PfnWdgGlCircleListWdgEventCB    pfn,
    void                            *pUserData
);

/** WdgGlCircleListWdgRegisterZoomAnimDoneEventCb
* @brief        Register callback
*
* @param[in]    pGlClWdg                Pointer to the GlCircleListWdg
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgGlCircleListWdgRegisterZoomAnimDoneEventCb
(
    IWidget                         *pGlClWdg,
    PfnWdgGlCircleListWdgEventCB    pfn,
    void                            *pUserData
);

/** WdgGlCircleListWdgDeregisterZoomAnimDoneEventCb
* @brief        Deregister callback
*
* @param[in]    pGlClWdg                Pointer to the GlCircleListWdg
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/

MAE_Ret WdgGlCircleListWdgDeregisterZoomAnimDoneEventCb
(
    IWidget                         *pGlClWdg,
    PfnWdgGlCircleListWdgEventCB    pfn,
    void                            *pUserData
);

/** WdgGlCircleListWdgDeregisterSlideAnimDoneEventCb
* @brief        Deregister callback
*
* @param[in]    pGlClWdg                Pointer to the GlCircleListWdg
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgGlCircleListWdgDeregisterSlideAnimDoneEventCb
(
    IWidget                         *pGlClWdg,
    PfnWdgGlCircleListWdgEventCB    pfn,
    void                            *pUserData
);

/** WdgCircleListCreate
* @brief        Create CircleList widget.
*
* @retval       The pointer of CircleList         Success.
* @retval       NULL                                Failed.
*
*/
IWidget* WdgGlCircleListWdgCreate
(
    void
);

/** WdgCircleListCreateForWnd
* @brief        Create CircleList Widget and set the CircleList value for Window.
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWdgId         The widget unique ID of window
* @param[in]    nLayoutStyle   Layout Style

*
* @retval       The pointer of CircleList         Success.
* @retval       NULL                                  Failed.
*
*/
IWidget* WdgGlCircleListWdgCreateForWnd
(
    HWIN               hWin,
    Pos_t              *pPos,
    WidgetSize_t       *pSize,
    u16                nWdgId
);

/** WdgGlCircleListWdgIsAnimated
* @brief        Check animation of GlCircleListWdg finish or not.
*
* @param[in]    pClWdg       The pointer of GlCircleList
*
* @retval       TRUE/FALSE.
*
*/
boolean WdgGlCircleListWdgIsAnimated
(
    IWidget             *pClWdg
);
/** WdgGlCircleListWdgAddItemByBmp
* @brief        The function add a widget in the CircleList
*
* @param[in]    pClWdg       The pointer of GlCircleList
* @param[in]    pBitmap      A pointer of item image to add

* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret WdgGlCircleListWdgAddItemByBmp
(
    IWidget             *pClWdg,
    IWidget             *pCaptureCntr,
    u32                 nCateStrId
);

/** WdgGlCircleListWdgRemoveAll
* @brief        The function add a widget in the CircleList
*
* @param[in]    pClWdg       The pointer of GlCircleList

* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret WdgGlCircleListWdgRemoveAll
(
    IWidget             *pClWdg
);
/** WdgGlCircleListWdgAddItemByImgId
* @brief        The function add a widget in the CircleList
*
* @param[in]    pClWdg       The pointer of GlCircleList
* @param[in]    nImageID     An ID of item image to add

* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret WdgGlCircleListWdgAddItemByImgId
(
    IWidget             *pClWdg,
    u32                 nImageID,
    u32                 nCateStrId      
);
/** WdgGlCircleListWdgRemoveItemById
* @brief        The function delete a item from the GlCircleList. (compatible to WdgAbsContainer)
*
* @param[in]    pClWdg      The pointer of GlCircleList
* @param[in]    nDelItemId  The number of object to delete
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgRemoveItemById
(
    IWidget             *pClWdg,
    u32                 nDelItemId
);

/** WdgGlCircleListWdgAddItemByImgId
* @brief        The function add a widget in the CircleList
*
* @param[in]    pClWdg       The pointer of GlCircleList
* @param[in]    nUpdateIdx   The item index to update
* @param[in]    pBitmap      An bmp of item image to add
* @param[in]    nCateStrId   An String ID of item to add

* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret WdgGlCircleListWdgUpdateItemByBmp
(
    IWidget             *pClWdg,
    u8                  nUpdateIdx,    
    IWidget             *pCaptrueCntr,
    u32                 nCateStrId
);

/** WdgGlCircleListWdgAddItemByImgId
* @brief        The function add a widget in the CircleList
*
* @param[in]    pClWdg       The pointer of GlCircleList
* @param[in]    nUpdateIdx   The item index to update
* @param[in]    nImageID     An ID of item image to add
* @param[in]    nCateStrId   An String ID of item to add

* @retval       MAE_RET_SUCCESS           Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret WdgGlCircleListWdgUpdateItemByImgId
(
    IWidget             *pClWdg,
    u8                  nUpdateIdx,
    u32                 nImageID,
    u32                 nCateStrId
);

/** WdgGlCircleListWdgSetItemSize
* @brief        The function set item size of the GlCircleList.
*
* @param[in]    pClWdg      The pointer of GlCircleList
* @param[in]    pItemSize   The pointer of widgetsize
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgSetItemSize
(
    IWidget             *pClWdg,
    WidgetSize_t        *pItemSize
);

/** WdgGlCircleListWdgSetMaxDispNum
* @brief        The function set maximum display item number of the GlCircleList.
*
* @param[in]    pClWdg      The pointer of GlCircleList
* @param[in]    pDispNum    The enumeration of display number
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgSetMaxDispNum
(
    IWidget                     *pClWdg,
    GLCircleListMaxDispNum_e    pDispNum
);

/** WdgGlCircleListWdgStartAnimation
* @brief        The function start animation of the GlCircleList.
*
* @param[in]    pClWdg      The pointer of GlCircleList
* @param[in]    eAnimType  The type of animation of GlCircleList
* @param[in]    nDistance   The distance between user press and move
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgStartAnimation
(
    IWidget                 *pGlClWdg,
    GLCircleListAnimType_e  eAnimType,
    s32                     nDistance    
);

/** WdgGlCircleListWdgStopAnimation
* @brief        The function stop the excuting animation of the GlCircleList.
*
* @param[in]    pClWdg      The pointer of GlCircleList
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgStopAnimation
(
    IWidget     *pGlClWdg
);

/** WdgGlCircleListWdgGetFocusNumber
* @brief        The function to get focus number of the GlCircleList.
*
* @param[in]    pClWdg              The pointer of GlCircleList
* @param[in]    nCurFcsNumber       The focus number of GlCircleList
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgGetFocusNumber
(
    IWidget                         *pGlClWdg,
    u8                              *nCurFcsNumber
);

/** WdgGlCircleListWdgSetFocusNumber
* @brief        The function to get focus number of the GlCircleList.
*
* @param[in]    pClWdg              The pointer of GlCircleList
* @param[in]    nCurFcsNumber       The focus number of GlCircleList
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
MAE_Ret WdgGlCircleListWdgSetFocusNumber
(
    IWidget                         *pGlClWdg,
    u8                              nFcsNumber
);

/** WdgGlCircleListWdgDoLayout
* @brief        The function to get focus number of the GlCircleList.
*
* @param[in]    pClWdg              The pointer of GlCircleList
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
void WdgGlCircleListWdgDoLayout
(
    IWidget                         *pGlClWdg
);

/** WdgGlCircleListWdgSetTextBgImgById
* @brief        The function to get focus number of the GlCircleList.
*
* @param[in]    pClWdg              The pointer of GlCircleList
*
* @retval       MAE_RET_SUCCESS   Success. Successfully to remove.
* @retval       MAE_RET_FAILED    Failed. pClWdg is NULL or not found.
*
*/
void WdgGlCircleListWdgSetTextBgImgById
(
    IWidget                         *pGlClWdg,
    u32                             nLeftId,
    u32                             nMiddleId,
    u32                             nRightId    
);

#endif //__3D_UI_KINGMOVIE__

#endif /* __MAE_GLMENUWIDGET_H__ */
