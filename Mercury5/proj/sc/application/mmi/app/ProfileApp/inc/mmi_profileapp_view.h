/*****************************************************************************************
* @profileapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __profileapp_view__H
#define __profileapp_view__H

#include "mmi_profileapp_priv.h"

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppMainListViewWdgList_t;

MAE_Ret ProfileAppCreateMainListView(HWIN hWin, ProfileAppMainListViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppOptionViewWdgList_t;

MAE_Ret ProfileAppCreateOptionView(HWIN hWin, ProfileAppOptionViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppEditListViewWdgList_t;

MAE_Ret ProfileAppCreateEditListView(HWIN hWin, ProfileAppEditListViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppVibrateTypeViewWdgList_t;

MAE_Ret ProfileAppCreateVibrateTypeView(HWIN hWin, ProfileAppVibrateTypeViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppVoiceCallsRingingTypeViewWdgList_t;

MAE_Ret ProfileAppCreateVoiceCallsRingingTypeView(HWIN hWin, ProfileAppVoiceCallsRingingTypeViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppMessageToneViewWdgList_t;

MAE_Ret ProfileAppCreateMessageToneView(HWIN hWin, ProfileAppMessageToneViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppCalendarToneViewWdgList_t;

MAE_Ret ProfileAppCreateCalendarToneView(HWIN hWin, ProfileAppCalendarToneViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppAlarmToneViewWdgList_t;

MAE_Ret ProfileAppCreateAlarmToneView(HWIN hWin, ProfileAppAlarmToneViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppVoiceCallsViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateVoiceCallsView(HWIN hWin, ProfileAppVoiceCallsViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppMessagingViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateMessagingView(HWIN hWin, ProfileAppMessagingViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppCalendarViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateCalendarView(HWIN hWin, ProfileAppCalendarViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppAlarmViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateAlarmView(HWIN hWin, ProfileAppAlarmViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
#ifdef __PROFILEAPP_SMALLROM__
    IWidget *pVolumeBGImageWdg;
#endif
    IWidget *pIVolumeWdg;
}ProfileAppVolumeViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateVolumeView(HWIN hWin, ProfileAppVolumeViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppFileMgrViewWdgList_t;

__SLDPM_FREE__ MAE_Ret ProfileAppCreateFileMgrView(HWIN hWin, ProfileAppFileMgrViewWdgList_t *pWdgList);

//*******************************************************************//
#ifdef __USER_DEFINE_POWERONOFF_MELODY__

typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppPowerOnViewWdgList_t;

MAE_Ret ProfileAppCreatePowerOnView(HWIN hWin, ProfileAppPowerOnViewWdgList_t *pWdgList);

//*******************************************************************//


typedef struct
{
    IWidget *pIMenuWdg;
}ProfileAppPowerOffViewWdgList_t;

MAE_Ret ProfileAppCreatePowerOffView(HWIN hWin, ProfileAppPowerOffViewWdgList_t *pWdgList);

//*******************************************************************//
#endif //__POWER_ON_OFF_RINGTONE_SETTING__

#endif //__profileapp_view__H
