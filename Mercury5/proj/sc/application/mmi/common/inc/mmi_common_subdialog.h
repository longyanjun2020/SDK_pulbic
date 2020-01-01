/**
 * @file    mmi_common_subdialog.h
 * @brief   These APIs are for sub display used - dual LCM.
 *          
 *
 * @author  
 * @version $Id: mmi_common_subdialog.h 33169 2010-05-16 05:19:42Z jerry-hy.liu $
 */
 
#ifndef __MMI_COMMON_SUBDIALOG_H__
#define __MMI_COMMON_SUBDIALOG_H__

#include "mmi_common_dialog.h"
/**
* MMI_CreateConfirmSubDialog
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
void MMI_CreateConfirmSubDialog
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
* MMI_CreateConfirmSubDialogById
* @brief	The same as MMI_CreateConfirmDialog except that the text input is used by text id.
*/
void MMI_CreateConfirmSubDialogById
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
* MMI_CreateInformationSubDialog
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
void MMI_CreateInformationSubDialog
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    MAE_WChar           *pTextBuffer, 
    WdgLayoutStyle_e    eLayoutStyle,
    s32                 nTimer,
    PFN_DlgHandler	    pfnDialogHdl
);

/**
* MMI_CreateInformationSubDialogById
* @brief	The same as MMI_CreateInformationDialog except that the text input is used by text id.
*/
void MMI_CreateInformationSubDialogById
(
    IApplet             *pOwner, 
    u16                 u16DialogViewID, 
    const u32           nTextID,
    WdgLayoutStyle_e    eLayoutStyle,
    s32                 nTimer,
    PFN_DlgHandler	    pfnDialogHdl
);


/**
* MMI_CreateWaitingSubDialog
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
void MMI_CreateWaitingSubDialog
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
* MMI_CreateWaitingSubDialogById
* @brief	The same as MMI_CreateWaitingDialog except that the text input is used by text id.
*           if nTextID is TXT_NULL_ID, it will also display default text (Please wait).
*/
void MMI_CreateWaitingSubDialogById
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
* MMI_CreateProgressSubDialog
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
void MMI_CreateProgressSubDialog
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
* MMI_CreateProgressSubDialogById
* @brief	The same as MMI_CreateProgressDialog except that the text input is used by text id.
*           if nTextID is TXT_NULL_ID, it will also display default text (Please wait).
*/
void MMI_CreateProgressSubDialogById
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
* MMI_CreateVolumeSubDialog
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
void MMI_CreateVolumeSubDialog
(
    IApplet *pOwner, 
    u8 VolumeLevel, 
    IWidget **ppVolumeWdg,
    PfnModelListener pFnVolumeMdlListener,
    PFN_DlgHandler pfnDialogHdl
);

/**
* MMI_CreateRedialSubDialog
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
void MMI_CreateRedialSubDialog
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
* MMI_CreateRedialSubDialogById
* @brief	The same as MMI_CreateRedialDialog except that the text input is used by text id.
*/
void MMI_CreateRedialSubDialogById
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
* MMI_CreateRecordingSubDialog
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
void MMI_CreateRecordingSubDialog
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
* MMI_CloseSubDialog
* @brief	Close the dialog immediately.
*           pfnDialogHdl() will receive MAE_EVT_DIALOG_DESTRUCT event.
*
* @param	pOwner(IApplet*)		The pointer of Applet
*
* @retval   void.
*
*/
void MMI_CloseSubDialog(IApplet *pOwner);

/**
* MMI_IsSubDialogExisted
* @brief	Check if the dialog is existed.
*
* @param	pOwner(IApplet*)		The pointer of Applet
*
* @retval   TRUE                    The dialog is existed.
* @retval   FALSE                   The dialog is not existed.
*/
boolean MMI_IsSubDialogExisted(IApplet *pOwner);

#endif /* __MMI_COMMON_SUBDIALOG_H__ */

