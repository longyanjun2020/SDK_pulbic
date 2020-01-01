/**
* @file    mmi_wdg_softkey.h
* @author  kenny.wu@mstarsemi.com
* 
* @version $Id: mmi_wdg_softkey.h 8741 2008-04-08 13:22:30Z paul.ouyang $
*
*   Softkey widget is PropContainer base, which has two text-widgets or bitmap-widgets
*   to display left and right text, and one bitmap-widget to display center-softkey(CSK) 
*   image. The default type of left and right keys are text-widgets, There are two layout 
*   mode in softkey-widget, one is horizontal, the other is vertical.
*
*   Horizontal Softkey widget:
*   +------------------PropContainer-------------------+
*   |+-------------------++------++-------------------+|
*   || LSK               || CSK  ||           RSK     ||
*   |+-------------------++------++-------------------+|
*   +--------------------------------------------------+
*   CSK: a bitmap-widget
*   LSK: a text-widget(default) or bitmap-widget
*   RSK: a text-widget(default) or bitmap-widget
*
*   Vertical Softkey widget:
*    +---PropContainer---+
*    |+-----------------+|
*    ||        RSK      ||
*    |+-----------------+|
*    |+-----------------+|
*    ||        CSK      ||
*    |+-----------------+|
*    |+-----------------+|
*    ||        LSK      ||
*    |+-----------------+|
*    +-------------------+
*/
#ifndef __MMI_WDG_SOFTKEY_H__
#define __MMI_WDG_SOFTKEY_H__

#include "mmi_mae_widget.h"
#include "mmi_mae_softkey.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
	SK_BACKGROUND_DEFAULT = 0,    ///< Using default image.
	SK_BACKGROUND_TRANSPARENT,    ///< Background transparent.
	SK_BACKGROUND_END
}SK_BACKGROUND_MODE_e;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
/** WdgSoftkeyCreateForWnd
* @brief        Create SoftKey widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of SoftKey      Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgSoftkeyCreateForWnd
(
    HWIN            hWin,
    Pos_t                  *pPos,
    WidgetSize_t           *pSize,
    u16                    nWidgetID
);

/** WdgSoftkeyCreate
* @brief        Create SoftKey widget
*
* @retval       The pointer of SoftKey      Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgSoftkeyCreate
(
    void
);
/*=============================================================*/
/** WdgSoftkeySetLeftSoftkey
* @brief        Set left softkey of the softkey widget
*
* @param[in]    pWDGSoftKey       The SoftKey widget which want to be set
* @param[in]    nLeftSoftkey      Softkey ID
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetLeftSoftkey
(
    IWidget                 *pWDGSoftKey,
    SoftkeyID               nLeftSoftkey
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_LEFT_SOFTKEY, (u32)nLeftSoftkey);
}

/** WdgSoftkeySetMiddleSoftkey
* @brief        Set middle softkey of the softkey widget
*
* @param[in]    pWDGSoftKey       The SoftKey widget which want to be set
* @param[in]    nMiddleSoftkey    Softkey ID
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetMiddleSoftkey
(
    IWidget                 *pWDGSoftKey,
    SoftkeyID               nMiddleSoftkey
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_MIDDLE_SOFTKEY, (u32)nMiddleSoftkey);
}

/** WdgSoftkeySetRightSoftkey
* @brief        Set right softkey of the softkey widget
*
* @param[in]    pWDGSoftKey       The SoftKey widget which want to be set
* @param[in]    nRightSoftkey     Softkey ID
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetRightSoftkey
(
    IWidget                 *pWDGSoftKey,
    SoftkeyID               nRightSoftkey
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_RIGHT_SOFTKEY, (u32)nRightSoftkey);
}

/** WdgSoftkeySetSoftkeyBackgroundMode
* @brief        Set the background of the softkey widget
*
* @param[in]    pWDGSoftKey       The SoftKey widget which want to be set
* @param[in]    nMode              SK_BACKGROUND_DEFAULT: default image.
*                                 SK_BACKGROUND_TRANSPARENT: transparent background
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetSoftkeyBackgroundMode
(
    IWidget                 *pWDGSoftKey,
    SK_BACKGROUND_MODE_e    nMode
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_BG_IMAGE_MODE, (u32)nMode);
}

/** WdgSoftkeySetUserDefineLeftText
* @brief        Set Left Softkey User Define Text.
*
* @param[in]    pWDGSoftKey       The pointer of SoftKey
* @param[in]    pText             User Define Text
*
* @retval       None
*
*/
void WdgSoftkeySetUserDefineLeftText
(
    IWidget                 *pWDGSoftKey,
    MAE_WChar               *pText
);

/** WdgSoftkeySetUserDefineRightText
* @brief        Set Right Softkey User Define Text.
*
* @param[in]    pWDGSoftKey       The pointer of SoftKey
* @param[in]    pText             User Define Text
*
* @retval       None
*
*/
void WdgSoftkeySetUserDefineRightText
(
    IWidget                 *pWDGSoftKey,
    MAE_WChar               *pText
);

/** WdgSoftkeySetUserDefineLeftIcon
* @brief        Set Left Softkey User Define Image.
*
* @param[in]    pWDGSoftKey       The pointer of SoftKey
* @param[in]    pImage            User Define Image
*
* @retval       None
*
*/
void WdgSoftkeySetUserDefineLeftIcon
(
    IWidget                 *pWDGSoftKey,
    IImage                  *pImage
);

/** WdgSoftkeySetUserDefineRightIcon
* @brief        Set Left Softkey User Define Image.
*
* @param[in]    pWDGSoftKey       The pointer of SoftKey
* @param[in]    pImage            User Define Image
*
* @retval       None
*
*/
void WdgSoftkeySetUserDefineRightIcon
(
    IWidget                 *pWDGSoftKey,
    IImage                  *pImage
);

/** WdgSoftkeySetMiddleSoftkeyBG
* @brief        Set background of middle softkey
*
* @param[in]    pWDGSoftKey         The SoftKey widget which want to be set
* @param[in]    nImageID            Image ID
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetMiddleSoftkeyBG
(
    IWidget             *pWDGSoftKey,
    u32                 nImageID
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_MIDDLE_BG_IMAGE, (u32)nImageID);
}

/** WdgSoftkeySetLRSoftkeyBG
* @brief        Set background of Left and Right softkey
*
* @param[in]    pWDGSoftKey         The SoftKey widget which want to be set
* @param[in]    nImageID            Image ID
*
* @retval       None
*
*/
__INLINE void WdgSoftkeySetLRSoftkeyBG
(
    IWidget             *pWDGSoftKey,
    u32                 nImageID
)
{
    WdgCommonSetProperty(pWDGSoftKey, PROP_LRKEY_BG_IMAGE, (u32)nImageID);
}

/** WdgSoftkeySetUserDefineMiddleIcon
* @brief        Set Middle Softkey User Define Image.
*
* @param[in]    pWDGSoftKey       The pointer of SoftKey
* @param[in]    pImage            User Define Image
*
* @retval       None
*
*/
void WdgSoftkeySetUserDefineMiddleIcon
(
    IWidget                 *pWDGSoftKey,
    IImage                  *pImage
);
/*=============================================================*/
/** WdgSoftkeyGetLeftSoftkey
* @brief        Get current left softkey ID
*
* @param[in]    pWDGSoftKey        The SoftKey widget which want to be set
*
* @retval       Softkey ID
*
*/
SoftkeyID WdgSoftkeyGetLeftSoftkey
(
    IWidget                 *pWDGSoftKey
);

/** WdgSoftkeyGetMiddleSoftkey
* @brief        Get current middle softkey ID
*
* @param[in]     pWDGSoftKey       The SoftKey widget which want to be get
*
* @retval       Softkey ID
*
*/
SoftkeyID WdgSoftkeyGetMiddleSoftkey
(
    IWidget                 *pWDGSoftKey
);

/** WdgSoftkeyGetRightSoftkey
* @brief        Get right middle softkey ID
*
* @param[in]    pWDGSoftKey        The SoftKey widget which want to be get
*
* @retval       Softkey ID
*
*/
SoftkeyID WdgSoftkeyGetRightSoftkey
(
    IWidget                 *pWDGSoftKey
);

/** WdgSoftkeyGetSoftkeyBackgroundMode
* @brief        Get the background of the softkey widget
*
* @param[in]    pWDGSoftKey       The SoftKey widget which want to be get
*                                 SK_BACKGROUND_TRANSPARENT: transparent background
*
* @retval       pMode             SK_BACKGROUND_DEFAULT: default image.
*                                 SK_BACKGROUND_TRANSPARENT: transparent background
*
*/
SK_BACKGROUND_MODE_e WdgSoftkeyGetSoftkeyBackgroundMode
(
    IWidget                 *pWDGSoftKey
);

#ifdef __UI_STYLE_MMI_IFONE__
u32 GetTextIdBySoftkeyID(u32 softkeyID);
#endif

#endif /*__MMI_WDG_SOFTKEY_H__ */
