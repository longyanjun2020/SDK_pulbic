#ifndef __MMI_COMMON_CALLLOG_TYPE_H__
#define __MMI_COMMON_CALLLOG_TYPE_H__

/*CalllogApp's data type definition that other libraries need*/

typedef enum
{
	CALLLOG_LIST_TYPE_MIN = 0,
    CALLLOG_LIST_TYPE_ALL = CALLLOG_LIST_TYPE_MIN,
	CALLLOG_LIST_TYPE_MISSED,
	CALLLOG_LIST_TYPE_RECEIVED,
	CALLLOG_LIST_TYPE_DAILED,
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
	CALLLOG_LIST_TYPE_BLOCKED,
	CALLLOG_LIST_TYPE_MAX = CALLLOG_LIST_TYPE_BLOCKED,
#else
	CALLLOG_LIST_TYPE_MAX = CALLLOG_LIST_TYPE_DAILED,
#endif
}CallLogListType_e;

typedef enum
{
	CALLLOG_AP_FID_LOG_LIST				= 0, // Normal type
	CALLLOG_AP_FID_COST_SETTING			= 1, // To Call cost setting.
}MMI_CALLLOG_AP_FID_TYPE_E ;


typedef struct
{
    CallLogListType_e eListType;
} MmiCalllogApFidListCalllog_t;

typedef struct
{
	u8 u8DualSimID;
} MmiCalllogApFidShowCallSetting_t;

/* The params to be passed to calllog app for starting up*/
typedef struct
{
    MMI_CALLLOG_AP_FID_TYPE_E eFid; //The function of calllogapp to be started

    union
    {
		MmiCalllogApFidListCalllog_t *pListCalllog;
		MmiCalllogApFidShowCallSetting_t *pShowCallSetting;
    }
    pParamData;
} CalllogAppParamData_t;

typedef enum
{
	MMI_CALLLOG_AP_SHOW_ALL_LIST			= 0,
	MMI_CALLLOG_AP_SHOW_MISSED_LIST		= 1,
	MMI_CALLLOG_AP_SHOW_RECEIVED_LIST	= 2,
	MMI_CALLLOG_AP_SHOW_DIALED_LIST		= 3,
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
	MMI_CALLLOG_AP_SHOW_BLOCK_LIST			= 4,
#endif	
	MMI_CALLLOG_AP_SHOW_DEFAULT_LIST	= MMI_CALLLOG_AP_SHOW_ALL_LIST
} MMI_CALLLOG_AP_SHOW_LIST_TYPE_E;

#endif //__MMI_COMMON_CALLLOG_TYPE_H__
