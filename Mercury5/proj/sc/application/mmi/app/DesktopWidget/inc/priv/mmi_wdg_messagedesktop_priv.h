/**
 * @file    mmi_wdg_message_priv.h
 * @brief   The internal structure of the messagewidget

 */

#ifndef __MMI_WDG_MESSAGE_PRIV_H__
#define __MMI_WDG_MESSAGE_PRIV_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__)

#include "img_data.h"
#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_common_cfg.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"

typedef enum
{
    Message_Desktop_Message_Inbox,
    Message_Desktop_Message_Draft,
    Message_Desktop_Message_Outbox,
    Message_Desktop_Message_Sent,
    Message_Desktop_Message_Num,
} MessageDesktop_Idx_e;

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET

    // Subwidget codes
    IWidget         *pTitleTextWidget;

    IWidget         *pFocusWidget;

    IWidget         *pNumText[Message_Desktop_Message_Num];
    IWidget         *pUnreadNumText;
    ISIMSRV         *pISIMSrv;
    ISMS            *pSMSSrv;
    ISMI            *pSMISrv;
    IMMS            *pMMSSrv;
    boolean         bSMSReady;
    boolean         bMMSReady;
    COMMON_SIM_CARD_STATUS_e SIMStatus;
    MessageDesktop_Idx_e	ePressedMsgIdx;
} MessageWdg_t;

/*********************************************************/
/* Local Functions */
/*********************************************************/

#endif // __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_PROFILE_PRIV_H__
/*=============================================================*/
// end of file
