////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_UNITTEST_H__
#define __MDL_UNITTEST_H__

#include "vm_types.ht"
#include "srv_resmgr_mml_forward.h"
#include "srv_resmgr_mmlcommon_types.h"
#include "sys_MsWrapper_cus_os_util.h"
#if 0
#include "mml_gps.h"
#include "mml_wlan.h"
#endif
#include "sys_MsWrapper_cus_os_flag.h"
#include "sys_rtk_semaphores.h"

#define UT_DBG_LEVEL            (_CUS2 | LEVEL_29)

#define UT_TIMEOUT_INVALID      0xFFFFFFFFUL
#define UT_MAX_FILE_NAME_LEN    64

typedef struct
{
    u8 u8TaskID;
    u8 u8Resv[3];
    u32 u32UtReportIdx;
    u8 *pDlmName;
} UtInitStruct;

typedef struct
{
    u32 u32ErrCode;
} UtFreeStruct;

typedef enum
{
    UT_ERROR_FAIL = -1,
    UT_ERROR_SUCCESS = 0,
    UT_ERROR_FINISH,
    UT_ERROR_NUM
} UtErrCode_e;

typedef enum
{
    UT_PASS_PASS = 0,
    UT_PASS_FAIL,
    UT_PASS_MARK,
    UT_PASS_STOP,
    UT_PASS_NONE
} UtPassCode_e;

typedef enum
{
    KEYPAD_EVENT = MML_GET_UCGEVENT_BASE(MML_UCGID_MANAGER) + 100,
} MmlUtEvent_e;

// From Main Code
extern s32 UtCaseInit(void *uis);
extern s32 UtCaseParseMsg(void* pMsg);
extern s32 UtCaseEnd(void *ufs);
extern void* UtMalloc(u32 u32Size);
extern s32 UtFree(void** ptr);
extern u8 UtGetTaskID(void);
extern s8 UtSendTrace(u32 Level, const char *strFormat, ...);
extern void UtRemoveMainNotify(u8 u8GroupID);
extern void UtAddMainNotify(u8 u8GroupID);
extern void UtSetMsgFromDlm(u8 *u8Msg, ...);

// From Main Code: Emulator
extern u32 UtGetEmlPlayTaskID(void);


// From Dlm Code
extern MmlErrCode_e UtMdlResponseCallBack(u16 uSenderId, u32 uUserValue, u8 eErrCode, void *pGssInfo);
extern void UtMdlNotifyCallBack(u16 uSenderId, u32 uUserValue, void *pNotifyInfo);
extern void UtMdlInformCallBack(u32 uUserValue, void *pInformInfo);
extern s16 UtSendCmd(u32 u32UseCaseID, void* pDataPtr, u32 u32DataSize);
extern s32 UtTimerTrigger(u32 u32TimeCnt);
extern s32 UtResponseTrigger(u32 u32UseCaseID, u32 u32ErrCode, void *pResponsePayload);
extern s32 UtNotifyTrigger(u32 u32NotifyEvent, void *pNotifyPayload);
extern s32 UtInformTrigger(u32 u32InformID, void *pInformPayload);
extern s32 UtInit(void);
extern void UtEnd(void);
extern int UtDbgTrace(u32 level, const char *pFmt, ...);
extern int UtDbgError(u32 level, const char *pFmt, ...);


// From Dlm Code: FS
extern void ut_mdl_free_file_list(u16*** pFileList);
extern u32 ut_mdl_get_file_num(u8* pPath, u32 u32ExtCnt, u16* pExt, u32 u32MinFileSize, u32 u32MaxFileSize, u32 u32Num, u16*** pFileList);

// From Dlm Code: Report
extern void ut_mdl_report_init(void);
extern void ut_mdl_report_puts(u8* string, ...);
extern void ut_mdl_report_uputs(u16* string);

// From Dlm Code: Profile
extern void ut_mdl_profile_add(u32 u32TaskID);
extern void ut_mdl_profile_start(void);
extern void ut_mdl_profile_end(void);
extern u32 ut_mdl_profile_query(u32 u32TaskID);
extern void ut_mdl_profile_report(void);

// From Dlm Code: Mem
extern void ut_mdl_mem_report_init(void);
extern void ut_mdl_mem_report_end(void);
extern void ut_mdl_mem_free(void);
extern void ut_mdl_mem_preserve(u32 u32Size);


// From Dlm Code: Notify
extern void UtReplaceNotify(u8 u8GroupID);
extern void UtRestoreNotify(u8 u8GroupID);

// From Dlm code: Task
extern void ut_mdl_suspend_task(u32 u32TaskID);

// Form Dlm code: KeyPad
extern void ut_mdl_replace_keypad_event(void);
extern void ut_mdl_restore_keypad_event(void);


// In Dlm Code
extern u8 u8TaskID;
extern u32 u32UtReportIdx;
extern u32 u32TimeCnt;
extern u32 u32TimePer;
extern u32 u32ErrorCode;
extern u8 *pDlmName;

#define UT_MBX u8TaskID

//===============================================================================
//                  Common Area for Dlm Test Case
//===============================================================================

typedef enum
{
    UT_EML_FAIL_ICP_INIT            = 0x00000001,
    UT_EML_FAIL_AUDIO_INIT          = 0x00000002,
    UT_EML_FAIL_DISP_INIT           = 0x00000004,
    UT_EML_FAIL_ICPBUF_ALLOC        = 0x00000008,
    UT_EML_FAIL_DISPBUF_ALLOC       = 0x00000010,
    UT_EML_FAIL_HEAPBUF_ALLOC       = 0x00000020,
    UT_EML_FAIL_HANG_CONDITION      = 0x00000040,
} UtEmlFailCondition_e;

//===============================================================================
//                                SYS Unit Test
//===============================================================================


//============================
//          MailBox
//============================

rtk_Mailbox_t * UT_RtkGetMbxPtr( rtk_MailboxId_t MboxNo );


//============================
//          Flag
//============================

Ms_Flag_t * UT_GetUtFlagPtr(void);
Ms_Flag_t * UT_GetUtFlagPtr2(void);


//============================
//          Timer
//============================

rtk_Timer_t * UT_GetRtk_PtrFirstUsedTimer(void);
rtk_Timer_t * UT_GetRtk_PtrFirstExpiredTimer(void);
rtk_Timer_t * UT_GetRtk_PtrFirstFreeTimer(void);


//============================
//          Task
//============================

void * UT_RtkGetTaskPtr(MsTaskId_e TaskId);

rtk_Task_t  * UT_RTKGetCirrentTaskPtr(void);
rtk_Task_t  * UT_GetRtk_TaskPrioList(void);

MsTaskId_e * UT_GetUtDynTskID1(void);
MsTaskId_e * UT_GetUtDynTskID2(void);
MsTaskId_e * UT_GetPtrUtDynTskID(u32 TaskId);

MsTaskCreateArgs_t * UT_GetPtrUtDynTskArg1(void);
MsTaskCreateArgs_t * UT_GetPtrUtDynTskArg2(void);
MsTaskCreateArgs_t * UT_GetPtrUtDynTskArg(u32);


//============================
//         Semaphore
//============================


// Native Semaphore

rtk_Semaphor_t * UT_GetUTSemPtr( rtk_SemId_t rtkSemaphorNumber );

rtk_SemId_t UT_GetUTSemID1(void);
rtk_SemId_t UT_GetUTSemID2(void);
rtk_SemId_t UT_GetUTSemID3(void);
rtk_SemId_t UT_GetUTSemID(u32);

// Dynamic Semaphore

void UT_InitUTDynSem1(s32 semInitValue);
void UT_InitUTDynSem2(s32 semInitValue);

rtk_SemaphoreHandle_t UT_GetUTDynSemPtr1(void);
rtk_SemaphoreHandle_t UT_GetUTDynSemPtr2(void);

void UT_DynSemDestroy(rtk_SemaphoreHandle_t dynSem);

#endif

