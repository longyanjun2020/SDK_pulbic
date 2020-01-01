/****************************************************************************/
/*  File    : sys_sys_dbg.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : System debug utilities internal definitions                   */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/



#ifndef __SYS_SYS_DBG_H__
#define __SYS_SYS_DBG_H__

//#include "sys_sys.h"
#ifndef __SDK_SIMULATION__
#include "sys_rm_trc.ho"
//#include "vm_rtc.h"
#endif//ndef __SDK_SIMULATION__


/**
 *  @brief The enumeration defines the return code of the amera interface function.
 */
typedef enum{
  SYS_DBG_OK,               /**< Function complete successfully */
  SYS_DBG_FAIL,             /**< Function fail */
  SYS_DBG_PARAM_ERROR,      /**< The input parameter is wrong */
  SYS_DBG_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  SYS_DBG_REJECT,           /**< Request reject because of other function's confliction */
  SYS_DBG_ABORT,            /**< Request abort because of incorrect sequence */
  SYS_DBG_TIMEOUT           /**< Request command to MMP is no response */
} sys_DbgErrCode_e;

//#define __BACKTRACE_UART_PRINT_RAW_DATA__

#define TRC_MAX_TRCFILE_SIZE          (2 * 1024 * 1024)
#define MAX_BACKTRACE_BUFFER_SIZE     (1024)
#define RUNTIMETRACE_LOG_PATH                  L"/CARD/sysbt"
#define RUNTIMETRACE_LOG_PATH_IN_SD2      L"/SD_2/sysbt"
#define BACKTRACE_LOG_PATH               L"/CARD/sysbt"
#define BACKTRACE_LOG_PATH_IN_SD2  L"/SD_2/sysbt"

#define EXCEPTION_LOG_FILENAME                             L"/CARD/sysbt/bt"
#define STORED_MSG_FILENAME                                  L"/CARD/sysbt/bt"
#define STORED_MSG_NO_STACK_FILENAME                 L"/CARD/sysbt/bt"
#define MMP_EXCEPTION_LOG_FILENAME                     L"/CARD/sysbt/bt"
#define BACKUP_EXCEPTION_LOG_FILENAME                L"/CARD/sysbt/bt"
#define EXCEPTION_LOG_FILENAME_IN_SD2                 L"/SD_2/sysbt/bt"
#define STORED_MSG_FILENAME_IN_SD2                      L"/SD_2/sysbt/bt"
#define STORED_MSG_NO_STACK_FILENAME_IN_SD2     L"/SD_2/sysbt/bt"
#define MMP_EXCEPTION_LOG_FILENAME_IN_SD2         L"/SD_2/sysbt/bt"
#define BACKUP_EXCEPTION_LOG_FILENAME_IN_SD2    L"/SD_2/sysbt/bt"
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
#define MODEM_RAM_LOG_FILENAME                              L"/CARD/sysbt/rl"
#define MODEM_RAM_LOG_FILENAME_IN_SD2                L"/SD_2/sysbt/rl"
#endif

#define EXCEPTION_LOG_FILEEXT         L".dat"
#define STORED_MSG_FILEEXT            L".dat"
#define STORED_MSG_NO_STACK_FILEEXT   L".dat"
#define MMP_BACKTRACE_LOG_FILEEXT     L".m2"
#define BACKUP_EXCEPTION_LOG_FILEEXT  L".bak"
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
#define MODEM_RAM_LOG_FILEEXT         L"R.LOG"
#endif

#define BACKTRACE_IDX_FILENAME                    L"/CARD/sysbt/bt_index.idx"
#define BACKTRACE_IDX_FILENAME_IN_SD2        L"/SD_2/sysbt/bt_index.idx"

#define MAX_DIGITS_OF_IDX             (4)
#define MAX_BACKTRACE_FILES           (10)
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
#define MAX_MODEM_RAM_LOG_FILES      (5)
#endif
#define MAX_COMPOSE_TRACE_NAME        (48)

#if defined(__RUNTIME_TRC_LONG_NAME__)
#define TRC_RUNTIME_FILENAME          "/CARD/sysbt/Trace_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.TTL"
#define TRC_AUDIODATA_FILE            "/CARD/sysbt/AUD_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.TTL"
#define TRC_EXTERNAL_FILENAME         "/CARD/sysbt/Trace_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d_OFF.TTL"
#define TRC_LOSTINFO_FILENAME         "/CARD/sysbt/Trace_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d_LOST.LOG"
#define TRC_RUNTIME_IN_SD2_FILENAME   "/SD_2/sysbt/Trace_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.TTL"
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
#define TRC_MODEM_GENIE_FILENAME         "/CARD/sysbt/Trace_Genie_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.LOG"
#define TRC_MODEM_MCU_FILENAME         "/CARD/sysbt/Trace_MCU_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.LOG"
#define TRC_MODEM_DSP_FILENAME         "/CARD/sysbt/Trace_DSP_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.LOG"
//#define TRC_MODEM_RAM_FILENAME         "/CARD/sysbt/Trace_DSP_%0.2d-%0.2d_%0.2d-%0.2d-%0.2d.LOG"
#endif
#else
#define TRC_RUNTIME_FILENAME          "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dT.TTL"
#define TRC_AUDIODATA_FILE            "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dA.TTL"
#define TRC_EXTERNAL_FILENAME         "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dX.TTL"
#define TRC_LOSTINFO_FILENAME         "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dL.LOG"
#define TRC_RUNTIME_IN_SD2_FILENAME   "/SD_2/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dT.TTL"
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
#define TRC_MODEM_GENIE_FILENAME          "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dG.LOG"
#define TRC_MODEM_MCU_FILENAME          "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dC.LOG"
#define TRC_MODEM_DSP_FILENAME          "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dD.LOG"
//#define TRC_MODEM_RAM_FILENAME          "/CARD/sysbt/%0.1c%0.1c%0.1c%0.2d%0.2dR.LOG"
#define MODEM_RAM_LOG_IDX_FILENAME                       L"/CARD/sysbt/Ram_log.idx"
#define MODEM_RAM_LOG_IDX_FILENAME_IN_SD2         L"/SD_2/sysbt/Ram_log.idx"
#endif

#endif


typedef struct
{
#if defined(__RTK_OVER_R2__)
  u32    abort_adress;
  u32    sp;
  u32    r2;
  u32    r3;
  u32    r4;
  u32    r5;
  u32    r6;
  u32    r7;
  u32    r8;
  u32    lr;
  u32    r10;
  u32    r11;
  u32    r12;
  u32    r13;
  u32    r14;
  u32    r15;
  u32    r16;
  u32    r17;
  u32    r18;
  u32    r19;
  u32    r20;
  u32    r21;
  u32    r22;
  u32    r23;
  u32    r24;
  u32    r25;
  u32    r26;
  u32    r27;
  u32    r28;
  u32    r29;
  u32    r30;
  u32    r31;
  u32    orig_gpr3;
  u32    cpsr;
  u32    esr;
  u32    epcr;
  u32    eear;
  u32    epos;
  u32    eacc;
  u32    etype;
  u32    r0;
  u32    r1;
  u32    r9;
  u32    pc;
  u32    vector;
#else
  u32    abort_adress;
  u32    pc;
  u32    cpsr;
  u32    lr;
  u32    sp;
  u32    r0;
  u32    r1;
  u32    r2;
  u32    r3;
  u32    r4;
  u32    r5;
  u32    r6;
  u32    r7;
  u32    r8;
  u32    r9;
  u32    r10;
  u32    r11;
  u32    r12;
  u32    dfsr;
  u32    ifsr;
  u32    fault_ar;
#endif
} sys_exceptionDump_t;

typedef struct
{
	u8 enterHalCheckFastHandler;
	u8 nBootUpSequence;
	u8 irqScheduleHistoryCnt;
	u8 irq1ScheduleHistoryCnt;
	u8 irqScheduleHistory[16];
	u8 irq1ScheduleHistory[16];
	u8 taskScheduleHistory[16];
	u8 taskScheduleStateHistory[16];
	u32 taskScheduleTickHistory[16];
	u16 taskScheduleHistoryCnt;
	u8 Backtrace1stFlow;
	u8 Backtrace2ndFlow;
	u8 BacktraceOver1Time;
	u8 oriCause;
	u8 ori2Cause;
	u8 nRamDumpResult;
	u16 nRamdumpRecord[4];
	u16 nRamDump2ndResult[4];
} sys_HwWdtDebugData_t;

#if defined (__RTK_OVER_R2__)
extern sys_HwWdtDebugData_t gsys_HwWdtDebugData;
extern sys_HwWdtDebugData_t *psys_HwWdtDebugData;
#define sys_HwWdtDebugData (*psys_HwWdtDebugData)
#else
extern sys_HwWdtDebugData_t sys_HwWdtDebugData;
#endif
extern u8 rm_DbgStoreRuntimeTraceFlow;
extern u8 rm_finalTraceFlow;
extern int rm_DbgStoreRuntimeTraceEfatResult;

typedef struct
{  //do NOT change its order due to hard code in asm
	u32 previous_Rtk_RegionCount;
	u32 previous_sys_sp;
	u32 previous_sys_lr;
	u32 previous_irq_sp;
	u32 previous_irq_lr;
} sys_wdt_mode_info_t;

typedef struct
{
  u32 abortSp;
  u32 abortPC;
  u32 callerSp;
  u32 callerLr;
} armExceptionState_t;

typedef struct
{
  u32 Type;
  char *MsgPtr;
  u8  Data[];
}sys_BackTraceFormat_t;

#ifndef __RTK_DIAGNOSE_ENHANCE__
/********* Registers Index in RtkRegister *********/
#define R13  0
#define R14  1
#define _PC  2
#endif

/********* BackTrace size Parameters **************/
#ifndef __RTK_DIAGNOSE_ENHANCE__
#define STACK_TO_STORE 512
#define BACKTRACE_SIZE (u32)(STACK_TO_STORE + 16)  //8 bytes => R14,PC, 4 bytes => HAPC Id, 4 bytes hapc flow size
#else
#define BACKTRACE_SIZE (u32)(CUR_STACK_TO_STORE + 16)  //8 bytes => R14,PC, 4 bytes => HAPC Id, 4 bytes hapc flow size
#endif
#define ENHANCED_BACKTRACE_STACK_TO_STORE 256
//fms trace only can support maximum size 32744. Set maximum size to 31K to prevent backtrace write failed
#define FULL_BACKTRACE_MAXSIZE 31744

/******* Back Trace Types *******/

#define SYS_RUN_TIME_ERROR      1 << 0
#define SYS_WATCH_DOG_ANALYSIS  1 << 1
#define SYS_WATCH_DOG_EXTRACT   1 << 2
#define SYS_EXCEPTION_OCCURED   1 << 3

#define NO_DUMP                 1 << 7

#if defined(__RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__)&& !defined(__SDK_SIMULATION__) && defined(__RTK_DIAGNOSE_ENHANCE__)
#define DEBUG_AREA_SIZE                 (((((RTK_MAX_TASKS+1)*(TASK_STACK_TO_STORE+24))>>10)<<10)+4096) //refer to sys_WatchDogTimeout()  //0xA000  		/* 40KBytes */
#else
#define DEBUG_AREA_SIZE                 0x10000  		/* 40KBytes */
#endif

#define DUMP_TRACE_FIRST_OBJECT_ID (fms_rai_id_t)0xABCD0000

#define	MAX_TIME_INFO_STR_SIZE	(32)
#define MAX_TIME_INFO_BUF_SIZE	(MAX_TIME_INFO_STR_SIZE + sizeof(u32) * 2)

#define EXCEPTION_DATA_ABORT                             0x00000001
#define EXCEPTION_PREFETCH_ABORT                         0x00000002
#define EXCEPTION_UNDEF_ABORT                            0x00000003

//MST Modification: Bug 719
#define BINARY_DATE_AND_TIME_LENGTH                      12

extern void RtkGetSpAndPc(void);                   // Get SP and PC and fill RtkRegisters
extern void RtkGetExceptionState(void);            // Fill RtkExceptionRegisters xhen arm exception occured
extern void RtkSetExceptionSp(void);


//extern u32 AbtStackStart;
//extern u32 UndefStackStart;

typedef struct SysDebugStruct_s {
    u32 powerOffFlag; //0x12345678 after correct power on and 0 after correct power off
    bool WatchdogResetOccured;
    bool ExpectedWatchdogReset;
    bool CustomerWatchdogReset;
    bool SoftResetOccured;
    u8 Rtk_CurrentTask;
    u32	RtkRegisters[4];
    s32 hac_GlobalFn;
    u32 ARMRegisters[13]; ///< R3 to R14 + CPSR
    u8  CustomerInfoReset;         // Used by the customer to communicate thru a reset
    u8  ResetCause;                // from dwl, firmware
    u16  LastUsedHapcPort;
#ifdef __MCP_WITHOUT_NOR__
    u32 BackTraceLength;
    u8 BackBuffer[STACK_TO_STORE];
#endif // __MCP_WITHOUT_NOR__
    u16 incenseRegs[20];
	u16 incenseRegs_backup[20]; //used to backup
#ifdef __REAL_TIME_PROBLEM_DIAGNOSE__
    /* Fields added to enrich HW watchdog timeout information. */
    void* sys_LastPcDisablingIt[4];
    u32   sys_LastPcDisablingItCpsr[4];
    u32   sys_LastPcDisablingItIndex;
    u32 sys_CpsrSnapShot;
    void* sys_ActiveIsr;
#endif
#if 1//def __SW_THERMISTER__
    u32    sys_reset_after_dl_magic_number;
#endif
} SysDebugStruct_t;

extern SysDebugStruct_t SysDebugStruct;

typedef enum
{
    SYS_DDA_NO_RESET = 0xFF,
    SYS_DDA_UNWANTED_RESET = 0,
    SYS_DDA_CUSTOMER_RESET,
    SYS_DDA_FROM_XDWL_RESET,
    SYS_DDA_FATAL_ERROR,
    SYS_DDA_FATAL_REENTRANT_ERROR,
    SYS_DDA_FAKE_SHUTDOWN_BY_WDT
} sys_DdaResetStatus_t;

typedef u32 (*Sys_BackTraceCB)(u32 *buffer, u32 bufferLen);

/* Prototypes */
void sys_BackTrace (u8 State, sys_BackTraceFormat_t *i__s_BackTraceHeader);
void sys_BackTrace_analysis_HWD(void);
s32 sys_DbgMoveBackTraceToFs (void);
void StoreARMRegisters(u32 storeAddr);
void sys_DbgSetLastUsedHapcPort(u8 Port, u8 HapcMode);
u16 sys_DbgGetLastUsedHapcPort(void);
void sys_InitE2pErrorStack(void);
void sys_E2pErrorStackAnalysis(void);
void sys_E2pErrorSingleStackAnalysis(void);
s32 sys_PutTraceBufferInFlash (void);
s32 sys_DeleteTraceBufferInFlash (void);
s32 sys_GetTraceBufferFromFlash (u8 **buffer, u32 *size);
void sys_watchDogExtract(void);

#ifdef __RTK_DIAGNOSE_ENHANCE__
void sys_DumpE2pError(bool isDumpOne);
#endif

void sys_DumpInfoLcd(u32 Port, u32 Width, u32 Height, u8 *pDispBuf);

#ifdef __RTK_DIAGNOSE_ENHANCE__
void sys_CnBackTrace(u32 *Backtrace);
void sys_CnIsException(bool	bException);
void sys_CnGetBackTrace(u8 **buffer, u16 *bufferLen);
#endif

u8 SysGetInfoReset(void);
void SysSetInfoReset(u8 nScrValue);
sys_DbgErrCode_e sys_DbgStoreTrcLostInfo(vm_dbgTrcLostInfo_t *pInfoBuf);
sys_DbgErrCode_e sys_DbgStoreRuntimeTrace(vm_dbgTrcBuffer_t *pTrcBuf);
sys_DbgErrCode_e sys_DbgStoreBackTrace(void);
#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||(__UPGRADE_GENIE_OVER_SHMCONN__)||(__UPGRADE_RAMLOG_OVER_SHMCONN__)
sys_DbgErrCode_e sys_DbgStoreModemLog(vm_dbgTrcModemLog_t *pInfoBuf);
#endif

sys_DbgErrCode_e sys_get_task_stack_profile(void* pStkInfo);
#endif //__SYS_SYS_DBG_H__

