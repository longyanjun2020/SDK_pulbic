#ifndef __MMI_VOICEMAILAPP_VIEW_ID_H__
#define __MMI_VOICEMAILAPP_VIEW_ID_H__

#include "mmi_mae_menumodel.h"
#include "mae_menulabel.h"
#include "mmi_wdg_menu.h"
#include "mmi_wdg_scrollbar.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_view_id_range.h"
//#include "mmi_cphssrv_def.h"

#define VOICEMAIL_MAX_CHAR  20 //MailNumberSize
#define VOICEMAIL_MAX_BYTELEN VOICEMAIL_MAX_CHAR*sizeof(MAE_WChar)

enum
{
/* View ID start */
	VOICEMAIL_SELECT_SIM_VIEW =MMI_VIEW_ID_AP_BEGIN, 
	VOICEMAIL_SETTING_MENU_VIEW, 
	VOICEMAIL_NUMBER_EDITOR_VIEW, 
	VOICEMAIL_NOTIFICATION_SETTING_VIEW
/* View ID end */
};

enum
{
/* Widget ID start */
	VOICEMAIL_SETTING_TITLE,
	VOICEMAIL_SETTING_MENU_WDG,
	VOICEMAIL_SCROLLBAR_WDG,
	VOICEMAIL_NUMBER_EDITOR_WDG,
};

enum VoiceMail_Setting_Item_e
{
    /* Binary ID start */
    VOICEMAIL_SET_ITEM_START=0,
    VOICEMAIL_SET_NUMBER_L1=VOICEMAIL_SET_ITEM_START,
    VOICEMAIL_SET_NUMBER_L2,    
    //VOICEMAIL_SET_NOTIFICATION, @@~~ remove from UI
    VOICEMAIL_SET_ITEM_TOTAL,
    VOICEMAIL_SET_ITEM_UNKNOW
};

enum VoiceMail_Setting_Notification_Item_e
{
    /* Binary ID start */
    VOICEMAIL_NOTIFICATION_SET_ITEM_START=0,
    VOICEMAIL_NOTIFICATION_SET_ON=VOICEMAIL_NOTIFICATION_SET_ITEM_START,
    VOICEMAIL_NOTIFICATION_SET_OFF,
    VOICEMAIL_NOTIFICATION_SET_ITEM_TOTAL
};
#endif /* __MMI_VOICEMAILAPP_VIEW_ID_H__ */
