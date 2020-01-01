/**
*     If AP wants to show current volume level or lets users adjust the volume, Volume
*     widget can achieve this goal. Volume widget can display volume level stairs and 
*     indicates current level. Users can use up/down navigation keys to tune volume 
*     up/down. Volume widget also provides silence mode to force AP mute. 
*     
*
*          ex: Volume widget
*           +---------------------------------+
*            |    +----------+       ------   |
*            |    |          |       ------   |
*            |    |   IMG    |       ------   |  <- volume level stairs
*            |    |          |       ------   |
*            |    |          |       ------   |
*            |    |          |       ======   |  <- current level
*            |    +----------+       ======   |
*           +---------------------------------+
*
*
*/

#ifndef __MMI_WDG_VOLUME_H__
#define __MMI_WDG_VOLUME_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef u8 VolumeWdgStyle_e;
enum{
    VOLUMEWDG_STYLE_DEFAULT,
    VOLUMEWDG_STYLE_FULLSCREEN = VOLUMEWDG_STYLE_DEFAULT,
    VOLUMEWDG_STYLE_DIALOG
};

/** VolumeWdgInfo_t
*
* @brief    u8MaxScale:     
*           u8CurrentLevel:
*
*/
typedef struct{
	u8	u8MaxScale;
	u8	u8CurrentLevel;
}VolumeWdgInfo_t;

/** PfnWdgVolumeVolumeChange
* @brief      CB register by "WdgVolumeRegisterVolumeChangeCb"
*             and will be trigger when volume changed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nCurrentLevel     The current level of volume.
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgVolumeVolumeChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel,IWidget *pWidget);

/** PfnWdgVolumeVolumeTimeout
* @brief      CB register by "WdgVolumeRegisterVolumeTimeoutCb"
*             and will be trigger when volume timeout.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgVolumeVolumeTimeout) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);
/*=============================================================*/
// functions
/*=============================================================*/
/** WdgVolumeCreateForWnd
* @brief        Create Volume widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    nStyle              Volume widget style
* @param[in]    nLevel              Volume widget initial value
*
* @retval       The pointer of Volume       Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgVolumeCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    VolumeWdgStyle_e         nStyle,
    u8                      nLevel
);

/** WdgVolumeCreate
* @brief        Create Volume widget
*
* @param[in]    nStyle              Volume widget style
*
* @retval       The pointer of Volume       Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgVolumeCreate
(
    VolumeWdgStyle_e         nStyle  
);

/** WdgVolumeSetInitialValue
* @brief        Set Volume widget initial value
*
* @param[in]    pWDGVolume        The pointer of IWidget interface object
* @param[in]    nLevel            Volume widget initial value
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgVolumeSetInitialValue
(
    IWidget                 *pWDGVolume,
    u8                      nLevel
);

/** WdgVolumeSetSilentMode
* @brief        Set Volume widget silence mode on / off
*
* @param[in]    pWDGVolume        The pointer of IWidget interface object
* @param[in]    bSilentModeOn     Volume widget silence mode on / off
*
* @retval       None
*
*/
void WdgVolumeSetSilentMode
(
    IWidget                 *pWDGVolume,
    boolean                 bSilentModeOn
);

/** WdgVolumeSetMuteButtonDisable
* @brief        Set mute button visible/invisible.
*
* @param[in]    pWDGVolume          The pointer of IWidget interface object
* @param[in]    bDisableMuteButton  Mute button visible/invisible.
*
* @retval       None
*
*/
void WdgVolumeSetMuteButtonDisable
(
    IWidget                 *pWDGVolume,
    boolean                 bDisableMuteButton
);

/** WdgVolumeSetAudioSettingOnly
* @brief        Set Volume widget audio setting only
*
* @param[in]    pWDGVolume        The pointer of IWidget interface object
* @param[in]    bAudioSettingOnly Volume widget audio setting only
*
* @retval       None
*
*/
void WdgVolumeSetAudioSettingOnly
(
    IWidget                 *pWDGVolume,
    boolean                 bAudioSettingOnly
);

/** WdgVolumeSetNotAllowMuteLevel
* @brief        Allow volume level be adjusted or not when mute
*
* @param[in]    pWDGVolume          The pointer of IWidget interface object
* @param[in]    bNotAllowMuteLevel  Volume widget not allow mute level on / off
*                                   TRUE: Not allow volume level be adjusted in mute mode.
*                                   FALSE: Allow volume level be adjusted in mute mode.
*
* @retval       None
*
*/
void WdgVolumeSetNotAllowMuteLevel
(
    IWidget                 *pWDGVolume,
    boolean                 bNotAllowMuteLevel
);

/** WdgVolumeGetCurrentLevel
* @brief        Get Volume widget current level
*
* @param[in]    pWDGVolume        The pointer of IWidget interface object
*
* @retval       Level             Volume widget volume level
*
*/
u8 WdgVolumeGetCurrentLevel
(
    IWidget                 *pWDGVolume
);

/** WdgVolumeGetSlientMode
* @brief        Get Volume widget silent mode on / off
*
* @param[in]    pWDGVolume        The pointer of IWidget interface object
*
* @retval       bSilentModeOn     Volume widget silent mode on / off
*
*
*/
boolean WdgVolumeGetSlientMode
(
    IWidget                 *pWDGVolume
);

/** WdgVolumeGetMuteButtonDisable
* @brief        Get Volume widget mute button disable / enable
*
* @param[in]    pWDGVolume          The pointer of IWidget interface object
*
* @retval       bDisableMuteButton  Volume widget button disable
*
*/
boolean WdgVolumeGetMuteButtonDisable
(
    IWidget                 *pWDGVolume
);

/** WdgVolumeGetNotAllowMuteLevel
* @brief        Get Volume widget not allow mute level on / off
*
* @param[in]    pWDGVolume          The pointer of IWidget interface object
*
* @retval       bNotAllowMuteLevel  Volume widget not allow mute level on / off
*
*/
boolean WdgVolumeGetNotAllowMuteLevel
(
    IWidget                 *pWDGVolume
);

/** WdgVolumeRegisterVolumeChangeCb
* @brief        Register volume change callback; CB will be triggered if volume changed.
*
* @param[in]    pWDGVolume        The Volume widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgVolumeRegisterVolumeChangeCb
(
    IWidget                     *pWDGVolume,
    PfnWdgVolumeVolumeChange    pfn,
    void                        *pUserData
);

/** WdgVolumeRegisterVolumeTimeoutCb
* @brief        Register volume timeout callback; CB will be triggered if volume timeout.
*
* @param[in]    pWDGVolume        The Volume widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgVolumeRegisterVolumeTimeoutCb
(
    IWidget                     *pWDGVolume,
    PfnWdgVolumeVolumeTimeout   pfn,
    void                        *pUserData
);

/** WdgVolumeDeregisterVolumeChangeCb
* @brief        Deregister size change callback
*
* @param[in]    pWDGVolume        The Volume widget which want to unregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgVolumeDeregisterVolumeChangeCb
(
    IWidget                     *pWDGVolume,
    PfnWdgVolumeVolumeChange    pfn,
    void                        *pUserData
);

/** WdgVolumeDeregisterVolumeTimeoutCb
* @brief        Deregister data change callback
*
* @param[in]    pWDGVolume        The Volume widget which want to unregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgVolumeDeregisterVolumeTimeoutCb
(
    IWidget                     *pWDGVolume,
    PfnWdgVolumeVolumeTimeout   pfn,
    void                        *pUserData
);
#endif //__MMI_WDG_VOLUME_H__
/*=============================================================*/
// end of file
