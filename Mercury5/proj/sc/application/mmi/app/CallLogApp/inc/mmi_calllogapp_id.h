#ifndef __MMI_CALLLOGAPP_ID_H__
#define __MMI_CALLLOGAPP_ID_H__

#define MMI_CALL_COST_MAX_ACCOUNT_LIMIT_SIZE    14   // 7 Character
#define MMI_CALL_COST_MAX_CURRENCY_SIZE         6    // 3 Character
#define MMI_CALL_COST_MAX_UNIT_SIZE             14   // 7 Character
#define MMI_MAX_PIN2_LENGTH                     16   // 4-8 Character

#define MIN_PIN2_PASSWORD_LEN 4
#define MAX_PIN2_PASSWORD_LEN 8

typedef enum
{
    CALLLOG_WND_LIST = WND_ID_APP_BASE,
    CALLLOG_WND_TIMER_MENU,
    CALLLOG_WND_COST_MENU,
    CALLLOG_WND_COST_SETTING_MENU,
    CALLLOG_WND_COST_SETTING_SETUNIT,//EMMI/mainline/proj/sc/application/mmi/app/CallSettingApp/res/mmi_callsettingapp_thm.rs
    CALLLOG_WND_COST_SETTING_SETCURRENCY,
    CALLLOG_WND_COST_SETTING_SETMAXUNIT,
    CALLLOG_WND_COST_RESETACCOUNT_ENTERPIN2,
    CALLLOG_WND_COST_SETTING_ENTERPIN2,
    CALLLOG_WND_TIMER_SELECT_SIM,
    CALLLOG_WND_COST_SELECT_SIM,
    CALLLOG_WND_LIST_SHOW_OPTION,
    CALLLOG_WND_DETAILTIME_SHOW_OPTION,
    CALLLOG_WND_DETAILTIME_SHOW_DETAIL,
    CALLLOG_WND_CUS,
    CALLLOG_WND_SELECT_DISPLAY_SIM
}CallogWndId_e;

typedef enum
{
	MNU_CALLLOGAPP_CALL_LIST_OPTION = 0,
	MNU_CALLLOGAPP_LO_VIEW,
	MNU_CALLLOGAPP_LO_CALL,
        MNU_CALLLOGAPP_LO_EDIT_BEFORE_CALL,
	MNU_CALLLOGAPP_LO_VIDEOCALL,
	MNU_CALLLOGAPP_LO_IPCALL,
	MNU_CALLLOGAPP_LO_SEND,
	MNU_CALLLOGAPP_LO_SAVE,
	MNU_CALLLOGAPP_LO_DELETE,
	MNU_CALLLOGAPP_LO_DELETE_ALL,
	MNU_CALLLOGAPP_LO_CALL_TIMERS,
	MNU_CALLLOGAPP_LO_CALL_COST,
	MNU_CALLLOGAPP_SEND_L2,
	MNU_CALLLOGAPP_SEND_SMS,
	MNU_CALLLOGAPP_SEND_MMS,
	MNU_CALLLOGAPP_CALL_TIMERS_MENU,
	MNU_CALLLOGAPP_CT_LAST_CALL,
	MNU_CALLLOGAPP_CT_RECEIVED_CALLS,
	MNU_CALLLOGAPP_CT_DIALED_CALLS,
	MNU_CALLLOGAPP_CT_RESET,
	MNU_CH_CALL_HISTORY,
	MNU_CH_MISSED_CALLS,
	MNU_CH_RECEIVED_CALLS,
	MNU_CH_DIALED_CALLS,
	MNU_CH_CLEANUP_ALL,
	MNU_CH_DURATION,
	MNU_CH_LAST,
	MNU_CH_RECEIVED,
	MNU_CH_DIALLED,
	MNU_CH_ALL,
	MNU_CH_CALL_COST,
	MNU_CH_LAST_CALL,
	MNU_CH_TOTAL_CALL_COST,
	MNU_CH_CREDIT,
	MNU_CH_RESET_COST,
	MNU_CH_SETTING,
	MNU_CH_CURRENCY,
	MNU_CH_PRICE_PER_UNIT,
	MNU_CH_SET_CREDIT,
	MNU_CALLLOGAPP_ADD_TO_BLACKLIST,
	MNU_CALLLOGAPP_DELETE_ALL_NO_SELECT,
	MNU_CALLLOGAPP_DISPLAY_SIM1,
	MNU_CALLLOGAPP_DISPLAY_SIM2,
	MNU_CALLLOGAPP_DISPLAY_ALL
}CalllogMenuId_e;

#endif //__MMI_CALLLOGAPP_ID_H__
