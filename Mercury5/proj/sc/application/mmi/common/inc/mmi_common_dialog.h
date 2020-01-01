/**
 * @file    mmi_common_dialog.h
 * @brief   
 *          
 *
 * @author  
 * @version $Id: mmi_common_dialog.h 33169 2009-06-12 05:19:42Z collin.chiang $
 */
 
#ifndef __MMI_COMMON_DIALOG_H__
#define __MMI_COMMON_DIALOG_H__

#include "DialogApp_resource.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_view.h"
#include "mmi_mae_softkey.h"
#include "mmi_common_dialog_id.h"
#include "mmi_mae_applet.h"



typedef struct {
	SoftkeyID_e nLSK;
	SoftkeyID_e nCSK;
	SoftkeyID_e nRSK;
	u32 nImgID;
	u8 nTextAlign;
	u8 nTextLayout;
	u32 nBGImgID;
} DialogViewInfo_t;

typedef MAE_Ret (*PFN_DlgHandler)(void *, MAEEvent_t, u32, u32);
typedef void (*pfnVolumeDlgListener) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel, IWidget *pWidget);

/**
* MMI_CreateConfirmDialog
* @brief	Create confirmation dialog(the window ID is WND_ID_DIALOG_CONFIRM)
*           If the registered softkey is pressed(LSK/CSK/RSK), the window manager will
*           trigger pfnDialogHdl() if existed.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*           The dialog will be closed automatically.
*
* @param	pOwner(IApplet*)		The pointer of Applet
* @param	u16DialogViewID(u16)	The dialog view ID defined in mmi_common_dialog_id.h
* @param	pTextBuffer(MAE_WChar*)	The text buffer which will be set into the text widget which is below the icon.
* @param	nLSK(SoftkeyID_e)		The softkey ID (refer to mae_softkey.h) for left softkey
* @param	nCSK(SoftkeyID_e)		The softkey ID (refer to mae_softkey.h) for middle softkey
* @param	nRSK(SoftkeyID_e)	    The softkey ID (refer to mae_softkey.h) for right softkey
* @param	eLayoutStyle		    The layout style (refer to mae_widget_properties.h) for this dialog view
*								    default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param    pfnDialogHdl            Thd callback function of Applet.
*
* @retVal	void
*/
void MMI_CreateConfirmDialog
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    MAE_WChar           *pTextBuffer,
    SoftkeyID_e         nLSK, 
    SoftkeyID_e         nCSK, 
    SoftkeyID_e         nRSK, 
    WdgLayoutStyle_e    eLayoutStyle,
    PFN_DlgHandler      pfnDialogHdl
);

/**
* MMI_CreateConfirmDialogById
* @brief	The same as MMI_CreateConfirmDialog except that the text input is used by text id.
*/
void MMI_CreateConfirmDialogById
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    const u32           nTextID,
    SoftkeyID_e         nLSK, 
    SoftkeyID_e         nCSK, 
    SoftkeyID_e         nRSK, 
    WdgLayoutStyle_e    eLayoutStyle,
    PFN_DlgHandler      pfnDialogHdl
);

/**
* MMI_CreateInformationDialog
* @brief	Create information dialog(the window id is WND_ID_DIALOG_INFO)
*           When time-out, the window manager will trigger pfnDialogHdl() if existed.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*           The dialog will be closed automatically.

* @param	pOwner(IApplet*)		The pointer of Applet
* @param	u16DialogViewID(u16)	The dialog view ID defined in mmi_common_dialog_id.h
* @param	pTextBuffer(MAE_WChar*)	The text buffer which will be set into the text widget which is below the icon.
* @param	eLayoutStyle		    The layout style (refer to mae_widget_properties.h) for this dialog view
*								    default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param    nTimer(s32)             When time-out, the dialog will be closed automatically.
* @param    pfnDialogHdl            Thd callback function of Applet.
*
* @retVal	void.
*/
void MMI_CreateInformationDialog
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    MAE_WChar           *pTextBuffer, 
    WdgLayoutStyle_e    eLayoutStyle,
    s32                 nTimer,
    PFN_DlgHandler	    pfnDialogHdl
);

/**
* MMI_CreateInformationDialogById
* @brief	The same as MMI_CreateInformationDialog except that the text input is used by text id.
*/
void MMI_CreateInformationDialogById
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    const u32           nTextID,
    WdgLayoutStyle_e    eLayoutStyle,
    s32                 nTimer,
    PFN_DlgHandler	    pfnDialogHdl
);


/**
* MMI_CreateWaitingDialog
* @brief	Create confirmation dialog(the window ID is WND_ID_DIALOG_WAITING)
*           If the registered softkey is pressed(LSK/CSK/RSK), the window manager will
*           trigger pfnDialogHdl() if existed.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*           The dialog will be closed automatically.
*
* @param	pOwner(IApplet*)   The pointer of Applet
* @param	pTitleTextBuffer   The text buffer which will be set into the text widget which is above the waiting animation
* @param	pTextBuffer        The text buffer which will be set into the text widget which is below the waiting animation
*                              if text buffer is NULL, it will display default text (Please wait)
*                              if caller want to set this text as null string, caller should give a NOT NULL text buffer with length as 0
* @param	nLSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for left softkey
* @param	nCSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for middle softkey
* @param	nRSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for right softkey
* @param	eLayoutStyle       The layout style (refer to mae_widget_properties.h) for this dialog view
*                              default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param    pfnDialogHdl       Thd callback function of Applet.
*
* @retVal	void.
*/
__SLDPM_FREE__ void MMI_CreateWaitingDialog
(
    IApplet             *pOwner, 
    MAE_WChar           *pTitleTextBuffer,
    MAE_WChar           *pTextBuffer,
    SoftkeyID_e         nLSK, 
    SoftkeyID_e         nCSK, 
    SoftkeyID_e         nRSK, 
    WdgLayoutStyle_e    eLayoutStyle,
    PFN_DlgHandler      pfnDialogHdl
);

/**
* MMI_CreateWaitingDialogById
* @brief	The same as MMI_CreateWaitingDialog except that the text input is used by text id.
*           if nTextID is TXT_NULL_ID, it will also display default text (Please wait).
*/
void MMI_CreateWaitingDialogById
(
    IApplet             *pOwner,
    const u32           nTitleID,
    const u32           nTextID,
    SoftkeyID_e         nLSK, 
    SoftkeyID_e         nCSK, 
    SoftkeyID_e         nRSK, 
    WdgLayoutStyle_e    eLayoutStyle,
    PFN_DlgHandler      pfnDialogHdl
);

/**
* MMI_CreateProgressDialog
* @brief    Create progress dialog (the window ID is WND_ID_DIALOG_PROGRESS)
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*
* @param    pOwner(IApplet*)           The pointer of Applet
* @param    pTitleTextBuffer           The text buffer which will be set into the text widget which is above the icon.
* @param    pTextBuffer                The text buffer which will be set into the text widget which is below the icon.
*                                      if text buffer is NULL, it will display default text (Please wait)
*                                      if caller want to set this text as null string, caller should give a NOT NULL text buffer with length as 0
* @param    nLSK                       The softkey ID (refer to mae_softkey.h) for left softkey
* @param    nCSK                       The softkey ID (refer to mae_softkey.h) for middle softkey
* @param    nRSK                       The softkey ID (refer to mae_softkey.h) for right softkey
* @param    ppProgressWdg              The pointer for storing the created progress widget instance 
* @param    eLayoutStyle               The layout style (refer to mae_widget_properties.h) for this dialog view
*                                       default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param    pfnDialogHdl               Thd callback function of Applet
*
* @retVal   void.
*/
void MMI_CreateProgressDialog
(
    IApplet *pOwner, 
    MAE_WChar *pTitleTextBuffer, 
    MAE_WChar *pTextBuffer,
    SoftkeyID_e nLSK, 
    SoftkeyID_e nCSK, 
    SoftkeyID_e nRSK, 
    IWidget **ppProgressWdg,   
    WdgLayoutStyle_e eLayoutStyle, 
    PFN_DlgHandler   pfnDialogHdl
);

/**
* MMI_CreateProgressDialogById
* @brief	The same as MMI_CreateProgressDialog except that the text input is used by text id.
*           if nTextID is TXT_NULL_ID, it will also display default text (Please wait).
*/
void MMI_CreateProgressDialogById
(
    IApplet *pOwner,
    const u32 nTitleID,
    const u32 nTextID,
    SoftkeyID_e nLSK,
    SoftkeyID_e nCSK,
    SoftkeyID_e nRSK,
    IWidget **ppProgressWdg, 
    WdgLayoutStyle_e eLayoutStyle,
    PFN_DlgHandler   pfnDialogHdl
);

/**
* MMI_CreateVolumeDialog
* @brief Create volume dialog (window id is COMMON_DIALOG_VOLUME)
*        pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*
* @param pOwner(IApplet*)           The pointer of Applet
* @param VolumeLevel(u8)            Set VolumeWdg as default focus widget
* @param ppVolumeWdg                The pointer for storing the created volume widget instance
* @param pFnVolumeMdlListener       Thd model listener of the volume widget.
* @param pfnDialogHdl               Thd callback function of Applet
*
* @retVal viod.
*/
void MMI_CreateVolumeDialog
(
    IApplet *pOwner, 
    u8 VolumeLevel, 
    IWidget **ppVolumeWdg,
    PfnModelListener pFnVolumeMdlListener,
    PFN_DlgHandler pfnDialogHdl
);

/**
* MMI_CreateRedialDialog
* @brief Create redial dialog(window id is COMMON_DIALOG_REDIAL)
*        pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*
* @param pOwner(IApplet*)           The pointer of Applet
* @param pTextBuffer                The text buffer which will be set into the text widget which is below the icon.
*                                   if caller want to set this text as null string, caller should give a NOT NULL text buffer with length as 0
* @param nLSK                       The softkey ID (refer to mae_softkey.h) for left softkey
* @param nCSK                       The softkey ID (refer to mae_softkey.h) for middle softkey
* @param nRSK                       The softkey ID (refer to mae_softkey.h) for right softkey
* @param ppRedialWdg                The pointer for storing the created progress widget instance 
* @param eLayoutStyle		        The layout style (refer to mae_widget_properties.h) for this dialog view
*								    default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param pfnDialogHdl               Thd callback function of Applet
*
* @retVal void.
*/
void MMI_CreateRedialDialog
(
    IApplet *pOwner,    
    MAE_WChar *pTextBuffer,
    SoftkeyID_e nLSK, 
    SoftkeyID_e nCSK, 
    SoftkeyID_e nRSK, 
    IWidget **ppRedialWdg,   
    WdgLayoutStyle_e eLayoutStyle,
    PFN_DlgHandler pfnDialogHdl
);

/**
* MMI_CreateRedialDialogById
* @brief	The same as MMI_CreateRedialDialog except that the text input is used by text id.
*/
void MMI_CreateRedialDialogById
(
    IApplet *pOwner,    
    const u32 nTextID,
    SoftkeyID_e nLSK, 
    SoftkeyID_e nCSK, 
    SoftkeyID_e nRSK, 
    IWidget **ppRedialWdg,   
    WdgLayoutStyle_e eLayoutStyle,
    PFN_DlgHandler pfnDialogHdl
);

/**
* MMI_CreateRecordingDialog
* @brief	Create recording dialog(the window ID is WND_ID_DIALOG_RECORDING)
*           If the registered softkey is pressed(LSK/CSK/RSK), the window manager will
*           trigger pfnDialogHdl() if existed.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_CONSTRUCT event at first.
*           The dialog will be closed automatically.
*
* @param	pOwner(IApplet*)   The pointer of Applet
* @param	nLSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for left softkey
* @param	nCSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for middle softkey
* @param	nRSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for right softkey  
* @param    ppRecordingWdg         The pointer for storing the created progress widget instance
*
* @param	eLayoutStyle       The layout style (refer to mae_widget_properties.h) for this dialog view
*                              default layout style is LAYOUT_STYLE_VERTICAL (defined in vdf)
* @param    pfnDialogHdl       Thd callback function of Applet.
*
* @retVal	void.
*/
void MMI_CreateRecordingDialog
(
    IApplet *pOwner,   
    SoftkeyID_e nLSK, 
    SoftkeyID_e nCSK, 
    SoftkeyID_e nRSK, 
    IWidget **ppRecordingWdg,     
    WdgLayoutStyle_e eLayoutStyle,
    PFN_DlgHandler pfnDialogHdl
);

/**
* MMI_CancelInfoDialogTimer
* @brief	Cancel the information dialog timer.
*
* @param	pOwner(IApplet*)		The pointer of Applet
*
* @retval   void.
*
*/
void MMI_CancelInfoDialogTimer(IApplet *pOwner);


/**
* MMI_CloseDialog
* @brief	Close the dialog immediately.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_DESTRUCT event.
*
* @param	pOwner(IApplet*)		The pointer of Applet
*
* @retval   void.
*
*/
__SLDPM_FREE__ void MMI_CloseDialog(IApplet *pOwner);

/**
* MMI_IsDialogExisted
* @brief	Check if the dialog is existed.
*
* @param	pOwner(IApplet*)		The pointer of Applet
*
* @retval   TRUE                    The dialog is existed.
* @retval   FALSE                   The dialog is not existed.
*/
boolean MMI_IsDialogExisted(IApplet *pOwner);

/**
* MMI_SetCurrDialogSoftkeys
* @brief	Set the current dialog softkeys again if wanted. 
*           Only useful for confirm/waiting/progress/redial/recording dialog now. 
*
* @param	pOwner(IApplet*)		The pointer of Applet
* @param	nLSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for left softkey
* @param	nCSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for middle softkey
* @param	nRSK(SoftkeyID_e)  The softkey ID (refer to mae_softkey.h) for right softkey
*
* @retval   void.
*/
void MMI_SetCurrDialogSoftkeys
(
    IApplet *pOwner,
    SoftkeyID_e         nLSK, 
    SoftkeyID_e         nCSK, 
    SoftkeyID_e         nRSK    
);

/**
* MMI_SetCurrDialogNoticeText
* @brief	Set the current dialog notice text again if wanted.
*           Only useful for waiting/progress/redial dialog.
*
* @param	pOwner(IApplet*)		The pointer of Applet
* @param    pTextBuffer             The text buffer which will be set into the text widget 
*                                   which is below the icon.
*
* @retval   void.
*/
void MMI_SetCurrDialogNoticeText(IApplet *pOwner, MAE_WChar *pTextBuffer);

/**
* MMI_SetCurrDialogAcceptAnyKey
* @brief	If set current dialog accept any key, all the key codes(except END key) will transmit to 
*           the dialog handler function. 
*           If dialog handler function returns MAE_RET_SUCCESS, this key is seen as handled.
*           (It means this key code will not pass to App callback:MAE_EVT_KEY_PRESS function.)
*           By default the dialog just receives LSK/CSK/RSK, if not need to receive other keys, do not 
*           call this function.
*
* @param	pOwner(IApplet*)		The pointer of Applet.
*
* @retval   void.
*/
void MMI_SetCurrDialogAcceptAnyKey(IApplet *pOwner);

#endif /* __MMI_COMMON_DIALOG_H__ */

