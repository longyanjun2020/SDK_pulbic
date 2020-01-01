#ifndef __MMI_WDG_GROUP_H__
#define __MMI_WDG_GROUP_H__
/* ===========================================================*/
// Description
/* ===========================================================*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum {
	//time group
	GROUP_APPLET_WORLDCLOCK = 0,
	GROUP_APPLET_ALARM,                
	GROUP_APPLET_STOPWATCH,              
	GROUP_APPLET_COUNTDOWNTIMER,
	//dialer group
	GROUP_APPLET_DIALER,
	GROUP_APPLET_CALLLOG,
	GROUP_APPLET_PHONEBOOK,
	GROUP_APPLET_FAVORITEPHB,
	//calendar group
	GROUP_APPLET_CALENDAR_MONTH,
	GROUP_APPLET_CALENDAR_WEEKLY,
	GROUP_APPLET_CALENDAR_DAY,
	GROUP_APPLET_CALENDAR_EVENTLIST,
}GROUP_APPLET_TYPE;

enum
{
	/* Group Widget notify events */
	WdgGroup_Event_Notify_VisibleCB = 1,
	WdgGroup_Event_Notify_InvisibleCB,
	WdgGroup_Event_End
};
typedef u16 WdgGroup_Event_e;

typedef void (*PfnWdgGroupVisible) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bVisible, IWidget *pIWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgGroupCreateForWnd
* @brief        Group widget create function for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    nFoLevel       The fadeout's level
*
* @retval       The pointer of Group   Success.
* @retval       NULL                     Failed.
*
*/
IWidget* WdgGroupCreateForWnd
(
    HWIN      hWin,
    Pos_t            *pPos,
    WidgetSize_t     *pSize,
    u16              nWidgetID
);

/*=============================================================*/
/** WdgGroupCreate
* @brief        Create Group widget
*
* @retval       The pointer of Group     Success.
* @retval       NULL                       Failed.
*
*/
IWidget* WdgGroupCreate
(
    void
);

/*=============================================================*/
/** WdgGroupSetAppletType
* @brief        Set applet's Type
*
* @param[in] nClsId        class ID of AP
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_FAILED         Failed.
*
*/
void WdgGroupSetAppletType(IWidget *pWdg, GROUP_APPLET_TYPE nGroupAppType);

/*=============================================================*/
/** WdgGroupAutoLayout
* @brief        Auto layout
*
* @param[in] pIWidget        The pointer of widget
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_FAILED         Failed.
*
*/
MAE_Ret WdgGroupAutoLayout(IWidget *pIWidget);

/* Register/Deregister callback function */
MAE_Ret WdgGroupRegisterVisibleCb
(
    IWidget                     *pWDG3DLoader,
    PfnWdgGroupVisible          pfn,
    void                        *pUserData
);

MAE_Ret WdgGroupRegisterInvisibleCb
(
	IWidget 					*pWDG3DLoader,
	PfnWdgGroupVisible			pfn,
	void						*pUserData
);

MAE_Ret WdgGroupDeregisterVisibleCb
(
    IWidget                     *pWDG3DLoader,
    PfnWdgGroupVisible        	pfn,
    void                        *pUserData
);

MAE_Ret WdgGroupDeregisterInvisibleCb
(
    IWidget                     *pWDG3DLoader,
    PfnWdgGroupVisible        	pfn,
    void                        *pUserData
);

#endif //__MMI_WDG_GROUP_H__
/*=============================================================*/
// end of file
