/**
 * @file    mmi_wdg_statusbar.h
 * @brief   The document describes the interface of StatusBar Widget
 *
 *   Status Bar widget, relative to Softkey widget located in the below of screen, is above
 *   in the screen. It can be hide by main layout or Fadeout widget, or show up to display
 *   some informations. Therefore, AP can decide whether or not to display the Status bar.
 *
 *     ex: Status Bar widget
 *     +---------------------+
 *     | +----------------+  |
 *     | |  Status Bar    |  |
 *     | +----------------+  |
 *     |         Main        |
 *     |                     |
 *     |                     |
 *     |        Window       |
 *     | +----------------+  |
 *     | |    Softkey     |  |
 *     | +----------------+  |
 *     +---------------------+
 *
 */
#ifndef __MMI_WDG_STATUSBAR_H__
#define __MMI_WDG_STATUSBAR_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define STATUSBAR_PROPORTION_SEGMENT_NUM    eTotalSegment

enum StatbarCompWdg_tag
{
	STATUSBAR_BATT,
	STATUSBAR_RSSI,
	STATUSBAR_NTYPE_HEGPRS,
#ifdef __WLAN_MMI__
	STATUSBAR_NTYPE_WIFI,
#endif
	STATUSBAR_USRPROFILE,
	STATUSBAR_CCSS,
	STATUSBAR_WAPMSG1,
	STATUSBAR_WAPMSG2,
#ifndef  __LCM_QQVGA_MMI__
	STATUSBAR_OTHERIMG,
#endif
#ifdef __DUAL_SIM_MMI__
	STATUSBAR_SLAVE_RSSI,
#ifdef __SLAVE_NTYPE_IN_STATBAR__
	STATUSBAR_SLAVE_NTYPE,
#endif
	STATUSBAR_SLAVE_CCSS,
#endif
	STATUSBAR_ROAMING,
	STATUSBAR_BT,
#if !defined(__LCM_QQVGA_MMI__) && !defined(__MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__)
	STATUSBAR_VIBRATEING,
#endif
	STATUSBAR_ALARM,
	STATUSBAR_BG,
#ifndef  __LCM_QQVGA_MMI__
	STATUSBAR_MEDIAPLAYING,
#endif
#ifdef __NCCQQ_MMI__
    STATUSBAR_QQ,
#endif
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
	STATUSBAR_BLOCKCALL,
#endif
#ifdef __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
	STATUSBAR_MISSCALL,
#endif
	//// insert component which is IBitmap before this line
	STATUSBAR_COMP_BMPWDG_SUM,

	STATUSBAR_DUMMY = STATUSBAR_COMP_BMPWDG_SUM - 1, ///< do not modify this line

	//// insert component without interface model after this line
#ifndef  __LCM_QQVGA_MMI__
	STATUSBAR_TIMETEXT,
#endif
	STATUSBAR_COMP_WDG_SUM
};

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgStatusbarCreateForWnd
* @brief        Create Statusbar Widget and set the Statusbar value for Window
*
* @param[in]    hWin                The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    bBGEnable           Set true or false to enable or disable
*
* @retval       The pointer of Statusbar    Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgStatusbarCreateForWnd
(
    HWIN                    hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    boolean                 bBGEnable
);
/*=============================================================*/
/** WdgStatusbarCreate
* @brief        Create Statusbar widget
*
* @retval       The pointer of Statusbar    Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgStatusBarCreate
(
    void
);

/** WdgStatusbarSetSelfBGEnable
* @brief        Set the Statusbar's BG enable or disable
*
* @param[in]    pWDGStatusbar     The pointer of IWidget interface object
* @param[in]    bBGEnable         Set true or false to enable or disable
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgStatusbarSetSelfBGEnable
(
    IWidget                 *pWDGStatusbar,
    boolean                 bBGEnable
)
{
    return WdgCommonSetProperty(pWDGStatusbar, PROP_STATUSBAR_WDG_BG_ENABLE, (u32)bBGEnable);
}

#ifdef __MMI_STATUSBAR_AUTO_ARRANGE__

/** WdgStatusbarGetWidthProportion
* @brief        Get Status Bar Segment Width Proportion
*
* @param[in]    pWDGStatusbar     Status Bar Widget Pointer
* @param[out]   pProp             Segment Width Proportion pointer
* @param[in]    nSize             Segment Size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgStatusbarGetWidthProportion
(
    IWidget                 *pWDGStatusbar,
    u32                     *pProp,
    u32                      nSize
);

/** WdgStatusbarSetWidthProportion
* @brief        Set Status Bar Segment Width Proportion
*
* @param[in]    pWDGStatusbar     Status Bar Widget Pointer
* @param[in]    pProp             Segment Width Proportion pointer
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgStatusbarSetWidthProportion
(
    IWidget                 *pWDGStatusbar,
    u32                     *pProp
);

/** WdgStatusbarGetPriority
* @brief        Get Status Bar Icon Priority
*
* @param[in]    pWDGStatusbar     Status Bar Widget Pointer
* @param[out]   pPriority         Icon Priority, Starting from left to right
* @param[in]    nSize             Number of Icons in Priority array
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgStatusbarGetPriority
(
    IWidget                 *pWDGStatusbar,
    u8                      *pPriority,
    u32                      nSize
);

/** WdgStatusbarSetPriority
* @brief        Set Status Bar Icon Priority
*
* @param[in]    pWDGStatusbar     Status Bar Widget Pointer
* @param[in]    pPriority         Icon Priority, Starting from left to right
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgStatusbarSetPriority
(
    IWidget                 *pWDGStatusbar,
    u8                      *pPriority
);

#endif /*__MMI_STATUSBAR_AUTO_ARRANGE__ */

#endif /*__MMI_WDG_STATUSBAR_H__ */
