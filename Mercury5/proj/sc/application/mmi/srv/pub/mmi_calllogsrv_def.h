/**
* @file    mmi_calllogsrv_def.h
* @version
* @brief   Call log service definition header file
*
*/
#ifndef __MMI_CALLLOGSRV_DEF_H__
#define __MMI_CALLLOGSRV_DEF_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_phbsrv_def.h"
#include "mmi_common_custom.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_CALLLOG_FILTER_LOG_FULL 0xFFFFFFFF
#define MMI_CALLLOG_IDX_NOT_DEFINE 255

#define MMI_CALLLOG_MAX_IMSI_LEN 9 //9 bytes

//#define   MMI_CALLLOG_MAX_NUM_LOGS 20 // move to customization
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
#define	MMI_CALLLOG_MAX_NUM_TYPE 4
#else
#define	MMI_CALLLOG_MAX_NUM_TYPE 3
#endif
//#define   MMI_CALLLOG_MAX_NUM_TIME_LIST 10 // move to customization
#define MMI_CALLLOG_MAX_MISSED_COUNT_ALL 999 // u16
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
#define	MMI_CALLLOG_MAX_BLOCK_CALL_COUNT 999 // u16
#endif
#define MMI_CALLLOG_MAX_MISSED_COUNT_EACH 99 // u8
#define MMI_CALLLOG_MAX_MOMT_COUNT 65535

#define MMI_CALLLOG_INIT_CALL_COUNT 0
#define MMI_CALLLOG_INIT_CALL_TIME_AC 0

#define MMI_CALLLOG_FILTER_BITS_NUM (32)
#define MMI_CALLLOG_FILTER_NUM ((MMI_CALLLOG_MAX_NUM_LOGS+(MMI_CALLLOG_FILTER_BITS_NUM-1))/MMI_CALLLOG_FILTER_BITS_NUM)
/*=============================================================*/
// Data type definition
/*=============================================================*/

enum
{
    CALLLOG_TYPE_VOICE_CALL = 0,
    CALLLOG_TYPE_VIDEO_CALL = 1,
};
typedef u8 CallLogCallType_e;////

enum
{
    MMI_CALLLOG_TYPE_MISSED = 0
   ,MMI_CALLLOG_TYPE_RECEIVED = 1
   ,MMI_CALLLOG_TYPE_DIALED = 2
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
   ,MMI_CALLLOG_TYPE_BLOCK = 3
   ,MMI_CALLLOG_TYPE_ALL = 4
#else
   ,MMI_CALLLOG_TYPE_ALL = 3
#endif
} ;

typedef u8 MMI_CALLLOG_TYPE_E;

//#define MMI_CALLLOG_TYPE_DEFAULT_SHOW MMI_CALLLOG_TYPE_MISSED

typedef enum
{
    MMI_CALLLOG_SRV_STATUS_IDLE = 0
   ,MMI_CALLLOG_SRV_STATUS_BUSY = 1,
} MMI_CALLLOG_SRV_STATUS_E;

typedef enum
{
    MMI_CALLLOG_CALL_TIME_AC_LAST_CALL = 0
   ,MMI_CALLLOG_CALL_TIME_AC_MO_CALL
   ,MMI_CALLLOG_CALL_TIME_AC_MT_CALL
   ,MMI_CALLLOG_CALL_TIME_AC_ALL
} MMI_CALLLOG_CALL_TIME_AC_TYPE_E;

enum
{
    MMI_CALLLOG_SIM_TYPE_MASTER = 0
   ,MMI_CALLLOG_SIM_TYPE_SLAVE
   ,MMI_CALLLOG_SIM_TYPE_ALL
};

typedef u8 MMI_CALLLOG_SIM_TYPE_E;

typedef enum
{
    CALLLOG_MASK_NOTIFY = 1 << 0,
	CALLLOG_MASK_Ready =  1 << 1,
    CALLLOG_MASK_ALL = (s32)0xFFFFFFFF
} CallLogSrvEventMask_e;

typedef struct
{
    u8 u8Idx;
    u8 u8LogType;
} Mmi_CallLogAllLogSortingIdx_t;

typedef struct
{
    u32 u32LastCallTimeAC;
    u32 u32AllMOTimeAC;
    u32 u32AllMTTimeAC;
    u32 u32LastCallTimeACSlave;
    u32 u32AllMOTimeACSlave;
    u32 u32AllMTTimeACSlave;
    u32 au32LogFilter[MMI_CALLLOG_MAX_NUM_TYPE][MMI_CALLLOG_FILTER_NUM];
    Mmi_CallLogAllLogSortingIdx_t atAllLogsSortingIdx[MMI_CALLLOG_MAX_NUM_TYPE *MMI_CALLLOG_MAX_NUM_LOGS];
    u8 u8IdxToFile[MMI_CALLLOG_MAX_NUM_TYPE][MMI_CALLLOG_MAX_NUM_LOGS];
    u16 u16MOCount;
    u16 u16MTCount;
    u16 u16MOCountSlave;
    u16 u16MTCountSlave;
    u16 u16MissedCount;
	u16	u16MissedCountSlave; 
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
	u16	u16BlockCallCount;
	u16	u16BlockCallCountSlave;
#endif
	u8 au8IMSIMsater[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
	u8 au8IMSISlave[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
    ////        
    u32 u32VideoLastCallTimeAC;
    u32 u32VideoAllMOTimeAC;
    u32 u32VideoAllMTTimeAC;
    u32 u32VideoLastCallTimeACSlave;
    u32 u32VideoAllMOTimeACSlave;
    u32 u32VideoAllMTTimeACSlave;
    u16 u16VideoMOCount;
    u16 u16VideoMTCount;
    u16 u16VideoMOCountSlave;
    u16 u16VideoMTCountSlave;    
} Mmi_CallLogFileHeader_t;

#define MMI_CALLLOG_FILE_HEADER_SIZE sizeof(Mmi_CallLogFileHeader_t)

typedef struct
{
    u8 au8Number[MMI_PHB_NUMBER_LEN ]; //GAX:[MMI_PHB_NUMBER_LEN + 1]
    u32 au32Time[MMI_CALLLOG_MAX_NUM_TIME_LIST];
	u32 au32TimeDuration[MMI_CALLLOG_MAX_NUM_TIME_LIST];
    u8 au8IMSI[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
    u8 u8Align;
    u8 u8MissCount;
    u8 u8NumberLen;
    u8 u8LogType;
    CallLogCallType_e eCallLogCallType;////
} Mmi_CallLogFullRecord_t;

#define MMI_CALLLOG_FILE_LOG_BLOCK_SIZE sizeof(Mmi_CallLogFullRecord_t)* MMI_CALLLOG_MAX_NUM_LOGS

typedef struct
{
    u8 au8Number[MMI_PHB_NUMBER_LEN];
    u8 au8IMSI[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
    u8 u8Align;
    u32 u32LatestTime;
    u8 u8MissCount;
    u8 u8NumberLen;
    u8 u8LogType;
    CallLogCallType_e eCallLogCallType;////
} Mmi_CallLogSimpRecord_t;

typedef struct
{
    Mmi_CallLogFileHeader_t tHeader;
    Mmi_CallLogSimpRecord_t tCallBuf[MMI_CALLLOG_MAX_NUM_TYPE][MMI_CALLLOG_MAX_NUM_LOGS];
    u8 u8CallSize[MMI_CALLLOG_MAX_NUM_TYPE];
    u8 u8ServiceStatus;
} Mmi_CallLogControlBuffer_t;

typedef struct
{
    u8 au8Number[MMI_PHB_NUMBER_LEN];
    u32 u32LatestTime;
	u32 au32TimeDuration;
    u8 u8NumberLen;
    u8 u8SimType;
    u8 u8LogType;
    CallLogCallType_e eCallLogCallType;////
} Mmi_CallLogLogChangedNotify_t;

typedef struct
{
    // Call log phone number
    u8 au8Number[MMI_PHB_NUMBER_LEN];
    // Call log start time
    u32 u32CallStartTime;
    CallLogCallType_e eCallLogCallType;////  
    u32 u32CallDuration;
    // Identify the length of above phone number
    u8 u8NumberLen;
    // Identify the sim type of this call log
    MMI_CALLLOG_SIM_TYPE_E iSimType;
    // Identify the log type of this call log
    MMI_CALLLOG_TYPE_E iCallLogType;
} Mmi_CallLogSrvAddLogReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
} Mmi_CallLogSrvAddLogCnf_t;

typedef struct
{
    // Which log of the sorting table you want
    u16 u16SortIdx;
    // Identify the log type of this call log
    MMI_CALLLOG_TYPE_E iCallLogType;
	MMI_CALLLOG_SIM_TYPE_E iSimtype;
    u8 u8DontResetCounter;
} Mmi_CallLogSrvReadSimpLogReq_t;

typedef struct
{
    // Use to store the returned simple record
    Mmi_CallLogSimpRecord_t tSimpRecord;
} Mmi_CallLogSrvReadSimpLogCnf_t;

typedef struct
{
    // Use to identify which full log you want
    u16 u16SortIdx;
    // Identify the log type of this call log
    MMI_CALLLOG_TYPE_E iCallLogType;
	MMI_CALLLOG_SIM_TYPE_E iSimtype;
} Mmi_CallLogSrvReadFullLogReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
    // Use to store the returned full record
    Mmi_CallLogFullRecord_t tFullRecord;
} Mmi_CallLogSrvReadFullLogCnf_t;

typedef struct
{
    // Use to identify which one needs to delete
    u16 u16SortIdx;
    // Identify the log type of this call log
    MMI_CALLLOG_TYPE_E iCallLogType;
	MMI_CALLLOG_SIM_TYPE_E iSimtype;
} Mmi_CallLogSrvDeleteOneLogReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
} Mmi_CallLogSrvDeleteOneLogCnf_t;

typedef struct
{
    // Identify the sim type
    MMI_CALLLOG_SIM_TYPE_E iSimType;
    // Identify the log type
    MMI_CALLLOG_TYPE_E iCallLogType;
} Mmi_CallLogSrvDeleteAllLogsReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
} Mmi_CallLogSrvDeleteAllLogsCnf_t;

typedef struct
{
    // Identify the log type
    MMI_CALLLOG_TYPE_E iCallLogType;
	MMI_CALLLOG_SIM_TYPE_E iSimType;
} Mmi_CallLogSrvLogStatusReq_t;

typedef struct
{
    // Identify the call log size for the specified log type
    u16 u16CallLogSize;
} Mmi_CallLogSrvLogStatusCnf_t;

typedef struct
{
    // Identify the sim type
    MMI_CALLLOG_SIM_TYPE_E iSimType;
    // Identify the type of call time accumulator
    MMI_CALLLOG_CALL_TIME_AC_TYPE_E iCallTimeACType;
    CallLogCallType_e eCallLogCallType;////
} Mmi_CallLogSrvGetCallTimeACReq_t;

typedef struct
{
    // The value of time accumulator in seconds
    u32 u32Time;
    // The value of call count
    u16 u16Count;
} Mmi_CallLogSrvGetCallTimeACCnf_t;

typedef struct
{
    // Identify the sim type
    MMI_CALLLOG_SIM_TYPE_E iSimType;
    // Identify the type of call time accumulator
    MMI_CALLLOG_CALL_TIME_AC_TYPE_E iCallTimeACType;
    CallLogCallType_e eCallLogCallType;////    
} Mmi_CallLogSrvResetCallTimeACReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
} Mmi_CallLogSrvResetCallTimeACCnf_t;

typedef struct
{
    //MMI_CALLLOG_CALL_TIME_AC_TYPE_E       iCallTimeACType;  // deprecated, do not use it
    // Identify the sim type
    MMI_CALLLOG_SIM_TYPE_E iSimType;
    // MO call duration
    u32 u32MOTimeDuration;
    // MT call duration
    u32 u32MTTimeDuration;
    // Last call duration
    u32 u32LastCallDuration;
    CallLogCallType_e eCallLogCallType;////
} Mmi_CallLogSrvAddCallDurationReq_t;

typedef struct
{
    // Identify the result of the confirm callback function
    MAE_Ret iSrvResult;
} Mmi_CallLogSrvAddCallDurationCnf_t;
/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __MMI_CALLLOGSRV_DEF_H__ */
