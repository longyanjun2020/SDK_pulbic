/**
 * \file TASKS.C
 * \brief Idle tasks and utilities for TARGET
 * \page CPU_LOAD CPU Load measurement in real time
 * \section about What it is about
 *   Using __CPU_LOAD__ flag (in comdefs.hc for example) activates CPU Load measurment. This is given
 *   by a number ranging from 0 to to 100 wich is a percent of CPU actvity, aka CPU not sleeping.
 *   0% means the CPU is sleeping most of time
 *   100% means the CPU never sleeps
 *   This measurment is send on  a watch
 * \section HDIW How does it work
 * Each time the CPU goes sleeping, the RTC is gotten, once again when awakening. \n
 * Difference is cumulated in a counter (slept_time) and every X TDMA frames (user defined), this is computed vs the total time spent since last computation.\n
 * So CPU LOAD is 1-(slept_time/total_time)
 * \subsection ST Some Tricks
 *   \li In comdefs.hs, a compilation error is returned if CPU_LOAD is set without WATCH. Computing the CPU Load without returning is unuseful.
 *   \li When accumulating the slept time, result is shifted 2 bits right. It avoids overflow for a precision loss. At last, the CPU percent is an integer so there is no real impact
 *   \li The time counter used, W5Rtc, is only 2 seconds wide. it sometimes overflow while sleeping, the computation must be done accordingly
 *   \li More over, the computation is available only if there's no sleep longerthan 2,048 s Otherwise, it should be rewrote
 * \section HTUI How to use it
 * \li Set __CPU_LOAD_ flag on
 * \li Define a value for CPU_STEP that is the step, inTDMA frame, for computing the CPU load. For example, 100 is about 2 computation persec. A too fast computation is unreadable, a too slow is unmeaningful
 * \li In TMT, display the "SYS" Watch. The CPU field is the CPU Load
 * \section precision Precision
 * The precision of this measure has been related to one done with Logic Analyser. Here are some results\n
 * Logic Analyser measurement  	| Embedded CPU Load \n
 *        14.86 %				| 		13 % \n
 *        38.18 %				| 		35 % \n
 *        80.19 %				| 		80 % \n
 *
 * Contents :  InitDefaultWatches
 * Fint1ISR
 * Fint2ISR
 * RtkUserInitProc
 * idle_Task
*/


#include "stdcomp.h"
#include "sys_rtk_ho.h"
#include "osdefs.hc"
#include "sys_traces.ho"
#include "watch.ho"
#include "v24.hi"
#include "kernel.h"
#include "sys.ho"
#include "sys_tools.h"
//#include "sys_ftr.ho"
//#include "hwl_ext.h"
//#include "hwl_rf.h"
//#include "hwl_sys.h"
//#include "hwl_glob.h"
#include "init.ho"
#include "kernel.h" //For CPCM debug
#include "vm_types.ht"
#include "drv_clkgen_cmu.h"
#include "sys_speed_profile.h"
#include "e2p_defs.hi"
#include "mdl_cpu_pub.h"
#include "sys_sys_bootinit.h"
#ifdef __CHARGING_POWER_ON_WITHOUT_BATTERY_PRODUCTION_MODE__
#include "vm_e2p_app.ho"
#endif

#if defined(__arm)
#include "sys_arm_core.h"
#include "sys_sys_arm.h"
#endif
#include "drv_emi_sram_nor_pub.h"
#include "sys_mem.h"
#include "fms_defs.hm"
//#include "hwl_l1c.h"
#include "stdlib.hp"
//#include "drv_rtc.h"
#include "drv_timer_types.h"
#include "drv_timer_api.h"
#include "sys_dbg.h"
#include "sys_irq_ctrl_pub_types.h"
#include "sys_irq_ctrl_pub_api.h"
#include "sys_sleep.h"

#ifdef __RTK_STACK_DIAGNOSE__
#include "sys_rtk_hv.h"
#include "sys_rtk_config.h"
#endif

#include "remote.hi"
#include "sys_sys_isw_uart.h" // UartSendTrace
//#ifdef __L1C_WATCH__
//#include "l1cwatch.h"
//#endif

//#ifdef __TASK_PWDN__
//#include "hactim.ho"
//#endif

#include <stdarg.h>
//#include "csn1_cdc.h"

#ifdef __RTK_DIAGNOSE_ENHANCE__
#include "sys_rtk_backtrace.h"
#endif
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "drv_int_ctrl_pub_api.h"

#ifdef __LOGIC_ANALYSER__
#include "kernel.h" // RDO
#include "drv_io_chip_pub_types.h"
#include "drv_io_chip_pub_api.h"
u8 dbg_ItField = 0;
#define __USE_USER0_ADDRESSES__
#endif
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_rtk_defi.h"

#ifndef __CORE_SW_VERSION__
//#include "drv_disp.h"
#endif

#ifdef __RAM_DUMP__
#include "sys_rtk_ramdump.h"
#endif

#include "sys_sys_profiling.h"
#include "sys_sys_cpu.h"
#include "sys_sys_bootinit.h"

#if defined(__G1__)
#ifdef __TASK_PWDN__
#undef __TASK_PWDN__
#define sim1_DetectRackChanges(a) do{} while(0)
#endif
#endif

#if (defined(__ENABLE_DMA2D_HW__) && !defined(__SDK_SIMULATION__))
extern bool DrvDMA2DIsAvtive(void);
#else
#define DrvDMA2DIsAvtive() TRUE
#endif

#if defined(__I_SW__)
//void TbuWakeUpISR(void);
//void Csn1ErrFunc( const char * Fmt, ... );

#else
extern void hwl_InitIntFunc(void);
extern void hwl_ClearUnusedInt(void);

extern void FatFsInit(void);
extern void fat_N_init(void);
#endif

extern void Csn1ErrFunc(const char * Fmt, ...);


#ifdef __ABNORMAL_SLEEP_DEBUG__
#include "mdl_bat_itf_pub.h"

//#define SLPDBG_START_CPU_PROFILE_TIME    650       //3 sec.
#define SLPDBG_START_CPU_PROFILE_TIME    433       //2 sec.
//#define SLPDBG_ABNORMAL_WAKEUP_TIME      2167      //10 sec.
#define SLPDBG_ABNORMAL_WAKEUP_TIME      1733      //8 sec.
#define SLPDBG_POSTPONE_START_TIME       130010    //10 min.
extern u8 dev_SleepAnalysis;
extern u32 slpdbg_total_fn, slpdbg_wakeup_fn, slpdbg_sleep_fn, slpdbg_start_fn;
extern u8 slpdbg_abnormal_sleep;
extern u16 slpdbg_abnormal_sleep_count;
extern u8 slpdbg_cpu_profile_step;
extern u8 slpdbg_buffer_switch;
// cause of deep sleep failed
extern u16 slpdbg_sleep_fail_bitmap;
extern u32 slpdbg_irq_count[];
extern u16 slpdbg_vbat[];
extern u16 slpdbg_start_vbat;

extern void slpdbg_DumpSleepInfo(void);
extern BattErrorno_e MdlBatGetVoltage(u16 *Voltage, BatID_e BatID);
#endif //__ABNORMAL_SLEEP_DEBUG__

#ifdef __CPU_LOAD__
//!
#define CPU_STEP	100
#define RT_CLOCKS_PER_FRAME 148//!round of ( 32 * 4.615 )//! How many times 32k tick in a frame ?
volatile u32 PreemptionFlag; //!use an u32 for future use : mask related to which task has prempted / interrupted
volatile u32 slept_time;
volatile u16 RT_Clock;
#endif

/* + ALO - 13/01/2006 - Declare prototype */
extern void (*TbuWakeUpHandler)(void);

/* - ALO - 13/01/2006 - Declare prototype */

#ifdef __SLEEP_MODE_DEBUG_EXT2__
extern void (*Ext2Handler)(void);
void Ext2ISR(void);
void EXT2_enable_irq(void);
#endif

//#if defined (__NO_HACTIM_TASK__) && defined (__BLUETOOTH__)
//extern void BTUART_SetIrq(bool mask);
//#endif

#ifdef __RTK_STACK_DIAGNOSE__

u32 g_stackIndex = 0;
u32 g_StachCheck_DBCnt;
extern void RtkStackUsageCheck(u32 taskIndex);
extern u8 FiqStack[];
extern u8 FiqStackStart;
extern u8 IrqStack[];
extern u8 IrqStackStart;
extern u8 SupStack[];
extern u8 SupStackStart;
extern u8 BootStack[];
extern u8 BootStackStart;
extern u8 AbtStack[];
extern u8 AbtStackStart;
extern u8 UndefStack[];
extern u8 UndefStackStart;

#endif

u8          WDogCountRstExpected = TRUE;


u32         rtkWDDumpInfo[40];
u8          rtkWDDumpInfoIndex = 0;


/**
 * CSN1 variables
 */

//csn1_Init_t PartInit;

/**
 * \brief Init Wavecom's watches
 */
#ifdef __WATCH__
s16 hwl_Trc [NB_ITEMS_HWL_WATCH];
s16 Amr_Trc [NB_ITEMS_AMR_WATCH];
s16 Graph_Trc [NB_ITEMS_GRAPH_WATCH];
s16 Sys_Trc [NB_ITEMS_SYS_WATCH];

WatchDataChr_t WatchHwl [NB_ITEMS_HWL_WATCH]
    = {         0, 'C', 'C', 'H',     8, 'F', 'A', ' ',
                2 * 8, 'T', 'C', 'H',   3 * 8, 'R', 'x', 'q',
                4 * 8, 'S', 'C', 'H',   5 * 8, 'B', 's', 'i',
                6 * 8, 'F', 'O', 'I',   7 * 8, 'A', 'F', 'C',
                8 * 8, 'S', 'n', 'r',   9 * 8, 'T', 'o', 'i',
                10 * 8, 'M', 'o', 'n',  11 * 8, 'M', 'r', 's',
                12 * 8, 'M', 'p', 'w',  13 * 8, 'R', 'X', ' ',
                14 * 8, 'R', 'r', 's',  15 * 8, 'R', 'p', 'w',
                16 * 8, 'T', 'x', ' ',  17 * 8, 'T', 'A', ' ',
                18 * 8, 'N', 'r', 'j',  19 * 8, 'M', 'E', 't',
                20 * 8, 'V', 'a', 'd',  21 * 8, 'E', 'F', 'R',
                22 * 8, 'F', 'R', ' ',  23 * 8, 'H', 'R', ' ',
                24 * 8, 'U', 'c', 's',  25 * 8, 'D', 'c', 's',
                26 * 8, 'U', 'm', 'c',  27 * 8, 'D', 'm', 'c',
                28 * 8, 'N', 'b', 'R',  29 * 8, 'N', 'b', 'T'
      };

WatchDataChr_t WatchAmr [NB_ITEMS_AMR_WATCH]
    = {       0, 'S', 'P', 'V',     8, 'F', 'R', ' ',
              2 * 8, 'H', 'R', ' ',   3 * 8, 'D', 'R', 'X',
              4 * 8, 'C', '/', 'I',   5 * 8, 'T', 'H', '0',
              6 * 8, 'T', 'H', '1',   7 * 8, 'T', 'H', '2',
              8 * 8, 'I', 'C', 'I',   9 * 8, 'I', 'C', 'M',
              10 * 8, 'A', 'C', 'S',  11 * 8, '4', '7', '5',
              12 * 8, '5', '1', '5',  13 * 8, '5', '9', '0',
              14 * 8, '6', '7', '0',  15 * 8, '7', '4', '0',
              16 * 8, '7', '9', '5',  17 * 8, '1', '0', '2',
              18 * 8, '1', '2', '2',  19 * 8, 'P', 'H', 'I',
              20 * 8, 'C', 'M', 'U',  21 * 8, 'C', 'M', 'R',
              22 * 8, 'C', 'M', 'D',  23 * 8, 'C', 'M', 'C',
              24 * 8, 'P', 'h', 'R',  25 * 8, 'C', 'o', 'R',
              26 * 8, 'T', 'h', 'R',  27 * 8, 'A', 'O', 'K',
              28 * 8, 'A', 'E', 'R',  29 * 8, 'A', 'U', 'N'
      };

WatchDataChr_t WatchGraph [NB_ITEMS_GRAPH_WATCH]
    = {       0, 'F', 'I', '0',     8, 'F', 'I', '1',
              2 * 8, 'F', 'I', '2',   3 * 8, 'F', 'I', '3',
              4 * 8, 'C', 'I', '0',   5 * 8, 'C', 'I', '1',
              6 * 8, 'C', 'I', '2',   7 * 8, 'C', 'I', '3',
              8 * 8, 'F', 'O', 'I',    9 * 8, 'T', 'I', '0',
              10 * 8, 'T', 'I', '1',  11 * 8, 'T', 'I', '2',
              12 * 8, 'T', 'I', '3',  13 * 8, 'T', 'O', 'I',
              14 * 8, 'P', 'P', 'M',    15 * 8, 'P', 'W', '0',
              16 * 8, 'P', 'W', '1',  17 * 8, 'P', 'W', '2',
              18 * 8, 'P', 'W', '3',  19 * 8, 'A', 'G', 'C'
      };

WatchDataChr_t WatchSys [NB_ITEMS_SYS_WATCH]
    = {       0, 'C', 'P', 'U'     };

void InitDefaultWatches(void)
{
#if defined(__G1__)

#warning L1 related function is missed // TODO: FIXME

#else   // defined(__G1__)

#ifdef __HWL_WATCH__
    InitWatchWin(0, NB_ITEMS_HWL_WATCH, WatchHwl, hwl_Trc);
    InitWatchWin(4, NB_ITEMS_AMR_WATCH, WatchAmr, Amr_Trc);
    InitWatchWin(5, NB_ITEMS_GRAPH_WATCH, WatchGraph, Graph_Trc);
#endif

#ifdef __L1C_WATCH__
    InitWatchWin(1, NB_ITEMS_L1C_WATCH, Watch1L1c, l1c_Watch1);
    InitWatchWin(2, NB_ITEMS_L1C_WATCH, Watch2L1c, l1c_Watch2);
#endif

#endif  // defined(__G1__)

#ifdef __CPU_LOAD__
    InitWatchWin(6, NB_ITEMS_SYS_WATCH, WatchSys, Sys_Trc);
#endif
}
#endif // __WATCH__


u32 rtk_SoftwareWatchDogCounts = 0xffffffff;



#ifdef __CPU_LOAD__
/*!
* \brief  compute the average idle period
*
*/
u16 Filter(u16 FiltIdlePeriod, u16 IdlePeriod)
{

    FiltIdlePeriod = (FiltIdlePeriod + IdlePeriod) >> 1; //Mean = sum/2
    return(FiltIdlePeriod);

}
#endif


/**
 * \brief Top level handler for E2P restore
 * \Check if E2P need to be restored
 */
/*
__ONCE_CALL_ON_BOOT__ void E2PRestore(void)
{
    Settings_t     Settings;
//    u32            Tmp_u32;
//    u16            Tmp_u16;
    u8             Tmp_u8;

    sys_E2pAccessWrapper(SYS_DIRTYE2P_READ, &Tmp_u8);//vm_e2pRead

    if(Tmp_u8 == 1)
    {

        sys_E2pAccessWrapper(SYS_NETMODE_BK_READ, &Tmp_u8);
        sys_E2pAccessWrapper(SYS_VM_NETMODE_WRITE, &Tmp_u8);//vm_e2pWrite
#ifdef __MSTAR_DUAL_SIM_E2P__
        sys_E2pAccessWrapper(SYS_NETMODE_2_BK_READ, &Tmp_u8);
        sys_E2pAccessWrapper(SYS_VM_NETMODE_2_WRITE, &Tmp_u8);
#endif

        sys_E2pAccessWrapper(SYS_SETTINGS_BK_READ, &Settings);
        sys_E2pAccessWrapper(SYS_SETTINGS_WRITE, &Settings);

#ifdef __MSTAR_DUAL_SIM_E2P__
        sys_E2pAccessWrapper(SYS_SETTINGS_2_BK_READ, &Settings);
        sys_E2pAccessWrapper(SYS_SETTINGS_2_WRITE, &Settings);
#endif
        sys_E2pAccessWrapper(SYS_STATUSREPORT_BK_READ, &Tmp_u8);
        sys_E2pAccessWrapper(SYS_STATUSREPORT_WRITE, &Tmp_u8);
#ifdef __MSTAR_DUAL_SIM_E2P__
        sys_E2pAccessWrapper(SYS_STATUSREPORT_2_BK_READ, &Tmp_u8);
        sys_E2pAccessWrapper(SYS_STATUSREPORT_2_WRITE, &Tmp_u8);
#endif

        Tmp_u8 = 0;
        sys_E2pAccessWrapper(SYS_DIRTYE2P_WRITE, &Tmp_u8);
    }


}
*/

static u8 sys_MpFlag = 0;


static void Sys_ReadMpFlag(void)
{
    sys_E2pAccessWrapper(SYS_MPRELEASE_READ, &sys_MpFlag);

    UartSendTrace("SYS_MPRELEASE_READ(sys_MpFlag) = %d (default 0)\n", sys_MpFlag);
}

/**
 * \brief  get MP flag utility func
 */
__RO_CODE_ON_BOOT__ u8 SysGetMPFlag(void)
{
    return sys_MpFlag;
}


/**
 * \brief System initialization
 */
__ONCE_CALL_ON_BOOT__ void RtkUserInitProc(int argc, char **argv)
{
    extern bool CusIsNandEnabled(void);
    if(CusIsNandEnabled() == TRUE)
    {
        FMS_LOCK(E2P_SEM);
    }

    sys_HwWdtDebugData.nBootUpSequence = 150;

    sys_CustomInitProc(argc, argv);

    sys_HwWdtDebugData.nBootUpSequence = 151;

    /* If E2P dirty is set, restore E2P data */
    // E2PRestore();

    sys_HwWdtDebugData.nBootUpSequence = 152;

#if defined(__TASK_PWDN__) || defined(__G1__)
    sys_SetSleepModeState(1);
#else
    sys_SetSleepModeState(0);
#endif // __TASK_PWDN__

    sys_HwWdtDebugData.nBootUpSequence = 153;

    /* Make sure that V24 is fully initialized BEFORE starting tasks */
    /* and if serial is off, re-set v24 to off state                 */
    if(v24_SerialOn & V24_UART1_MASK)
        v24_RequestExt(V24_SETUP_PORT, 0x0f, V24_UART1);
    if(v24_SerialOn & V24_UART2_MASK)
        v24_RequestExt(V24_SETUP_PORT, 0x0f, V24_UART2);

    sys_HwWdtDebugData.nBootUpSequence = 154;

#if defined(__G1__) || defined(__INFINITY__)
#ifdef __FIXME__
#warning L1 related function is missed // TODO: FIXME
#endif
#else  // defined(__G1__)
    hwll1_ReadE2pParameters();
#endif // defined(__G1__)

    sys_HwWdtDebugData.nBootUpSequence = 155;

    Sys_ReadMpFlag();
#if !defined(__G1__)
    sys_config_null_attribute();  //after Sys_ReadMpFlag do this right away
#endif // defined(__G1__)

    sys_HwWdtDebugData.nBootUpSequence = 156;

#ifdef __RAM_DUMP__
    ReadRamDumpFlag();
#endif

    sys_HwWdtDebugData.nBootUpSequence = 157;

    //Dynamically change SysTimerWdogctrlLen after reading mp_release flag from e2p.
    if(!SysGetMPFlag())
    {
#if	defined(__SOFTWARE_WATCHDOG__)
        rtk_SoftwareWatchDogCounts = SysTimerWdogctrlLen;
#endif
        DrvWDTimer0Ack();
        DrvWDTimer1Ack();
    }
    else
    {
        // change HW WDT to hardware reset in MP_RELEASE mode
        DrvWDTimer0IntEnable(FALSE);
        DrvWDTimer1IntEnable(FALSE);
    }

    sys_HwWdtDebugData.nBootUpSequence = 158;

#ifdef __BB_OSTICK_HOLD__
    DrvTimerOstickHoldEnable();
#endif//def __BB_OSTICK_HOLD__

    sys_HwWdtDebugData.nBootUpSequence = 159;


    RtkConnectTimerInterrupt(NULL);

    /* peterwei: set OSTICK INT priority */
    // TODO :> to find the corresponding function
    //SetInterruptPriority(6, OSTICK_IT_POS); //general INT has priority 7

    sys_HwWdtDebugData.nBootUpSequence = 160;

#if defined(__RTK_OSTICK_ENHANCE__)
    RtkConnectGlobalTimerInterrupt(NULL);
#endif

#if defined (__RTK_PROFILE_ENHANCE__)
    RtkConnectTimeSoftInterrupt();
#endif

    sys_HwWdtDebugData.nBootUpSequence = 161;

    /*
    **          Mapping           Address              Memory Protection          Type
    **
    ** +-----------------------+ 0x07000000 --------+
    ** |  Above External RAM   |                    | SYS_MEM_PROT_RTK_AREA_SPACE R/W
    ** +-----------------------+ 0x06000000+RAMSIZE-+
    ** | E    |   Debug Area   |
    ** | x    |----------------+
    ** | t R  |  Customer RAM  |
    ** | e A  |----------------+ -------------------+
    ** | r M  |   Wavecom RAM  |                    | SYS_MEM_PROT_WAVECOM_RAM    W
    ** | n    |                |                    |
    ** | a    |----------------+ &EndOfITStacks ----+
    ** | l    |    IT Stacks   |
    ** +-----------------------+ 0x06000000
    ** |   Shared Registers    |
    ** +-----------------------+ 0x05000000
    ** | Registers Peripherals |
    ** +-----------------------+ 0x04000000
    ** |         USER 1        |
    ** +-----------------------+ 0x03000000
    ** |         USER 0        |
    ** +-----------------------+ 0x02000000
    ** |  internal RAM/FLASH   |
    ** +-----------------------+ 0x01000000 --------+
    ** |         FLASH         |                    | SYS_MEM_PROT_FLASH_SPACE    W
    ** +-----------------------+ 0x00000000 --------+
    **
    ** Warning : on WHAT product, in the sys_MemoryProtection, last address is included in protection zone
    **
    */

    /* Wavecom RAM is allowed to be used */
    SYS_MEM_PROT_SUSPEND(SYS_MEM_PROT_WAVECOM_RAM);

    sys_HwWdtDebugData.nBootUpSequence = 162;

    /* Initialize CSN1 */
//		PartInit.StdIn  = NULL;
//		PartInit.StdOut = NULL;
//#ifdef __I_SW__
//        PartInit.StdErr = NULL;
//#else
//        PartInit.StdErr = (void (*)(const char *, va_list)) Csn1ErrFunc;
//#endif
//		if (csn1_Init(&PartInit) < 0)
//    		    _ERROR((_L3UT, ERR_S "Error Csn1_Init" ERR_E));

    sys_HwWdtDebugData.nBootUpSequence = 163;

#if !defined(__I_SW__)
    FatFsInit();
    fat_N_init();
    MsInitSem(DRM_SEM, 1);
#endif


    sys_HwWdtDebugData.nBootUpSequence = 164;

    sys_HwWdtDebugData.nBootUpSequence = 165;

#ifndef __I_SW__
    /* Due to system premain will invoke the spi read/write, put the sem init in here */
    MsInitSem(SPI1_SEM, 1); // SPI access will use the semaphore.
#endif //__I_SW__

#if defined(__EMI_POOL_PROTECT__) && !defined(__RTK_OVER_R2__)
    //Initialize emi pool protection
    sys_EmiPoolProtectInit();
#endif //defined(__EMI_POOL_PROTECT__)

    sys_HwWdtDebugData.nBootUpSequence = 166;


}


#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
extern u32 g_nSysDikQbOverheadSum;
extern u32 g_nSysDikQbOverheadCount;
extern u32 g_nSysDikQbOverheadMax;
extern u32 g_nSysDiuQbOverheadSum;
extern u32 g_nSysDiuQbOverheadCount;
extern u32 g_nSysDiuQbOverheadMax;
extern u32 g_nSysEikQbOverheadSum;
extern u32 g_nSysEikQbOverheadCount;
extern u32 g_nSysEikQbOverheadMax;
extern u32 g_nSysEiuQbOverheadSum;
extern u32 g_nSysEiuQbOverheadCount;
extern u32 g_nSysEiuQbOverheadMax;
extern u32 g_nSysIsrQbOverheadSum;
extern u32 g_nSysIsrQbOverheadCount;
extern u32 g_nSysIsrQbOverheadMax;
#endif

#if defined(__SEPARATE_INTERRUPT_API__)
extern u32 g_nSysDisableInterrupt;
extern u32 g_nSysDisableInterrupt_k;
#endif

#if defined(__INTERRUPT_INTEGRITY_PROTECT__)
extern u32 g_nSysDisableIntIndex;
extern void* g_apSysDisableIntLr[4];
extern u32 g_anSysDisableIntCpsr[4];
extern u32 sys_bDiQbCountExceed;
extern u32 sys_bDiTickCountExceed;


#if defined(__arm)
#pragma arm section rwdata = "imi_variable", zidata = "imi_variable"
#endif
// To record the isr check fint error
u32 sys_IsrCheckAbIsr = 0;
u32 sys_IsrCheckAbIsrNumber = 0;
u32 sys_IsrCheckAbLr = 0;
u32 sys_IsrCheckAbSp = 0;
bool sys_bFintCheckReady = FALSE;
#if defined(__arm)
#pragma arm section
#endif

void idleCheckIntIntegrity(void)
{
    u32 uCpuStatus = 0;
#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
    MsIntMask_e  MaskInt = 0;
#endif
    u32 uIntCheckErrorMask = 0;

    // Check CPSR: IRQ should be enabled.
    if(RtkRunInIsrContext())
    {
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] CPU status abnormal: IRQ has been disabled"));
        uIntCheckErrorMask |= CPSR_IBIT_ERR_MASK;
    }

    // Check interrupt mask: FINT mask should be enabled.
    if((g_ptW5IrqControl->u32_Mask0 & TBU_FINT_IT_MSK) == 0)
    {
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] INT register status abnormal: Fint has been masked"));
        uIntCheckErrorMask |= IRQC_FINT_ERR_MASK;
    }

    // Check TBU register
    if((g_ptW5TbuC->u32_IntCtrl & TBU_FINT_ENA) == 0)
    {
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] TBU register status abnormal: Fint has been masked"));
        uIntCheckErrorMask |= TBUC_FINT_ERR_MASK;
    }

#if defined(__SEPARATE_INTERRUPT_API__)
    // Check RTK2_DISABLE/RTK2_ENABLE, should be paired called.
    if(g_nSysDisableInterrupt)
    {
        //u32 uIndex = (g_nSysDisableIntIndex==0)? 3: g_nSysDisableIntIndex-1;
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] RTK2_DISABLE has been called"));
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] LR: %08x, CPSR: %08x", g_apSysDisableIntLr[uIndex], g_anSysDisableIntCpsr[uIndex]));
        uIntCheckErrorMask |= API_PAIR_USR_ERR_MASK;
    }

    // Check RTK2_DISABLE_K/RTK2_ENABLE_K, should be paired called.
    if(g_nSysDisableInterrupt_k)
    {
        //_TRACE((_RTK|LEVEL_1, "[Sys Enhance] RTK2_DISABLE_K has been called"));
        uIntCheckErrorMask |= API_PAIR_KER_ERR_MASK;
    }
#endif

    if(uIntCheckErrorMask)
        RtkExceptionRoutine(IDLE_SCHEDULE_INTERRUPT_CORRUPT, uIntCheckErrorMask);

#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
    // Profile information
    if(g_SysEiuQbOverheadCount >= 1000)
    {
        _TRACE((_RTK | LEVEL_1, "                                         "));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] g_SysEiuQbOverheadCount = %d", g_SysEiuQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Average EI_U QB count = %d", g_nSysEiuQbOverheadSum / g_SysEiuQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Maximum EI_U QB count = %d", g_nSys_EiuQbOverheadMax));
        g_SysEiuQbOverheadCount = g_nSysEiuQbOverheadSum = g_nSys_EiuQbOverheadMax = 0;
    }
    if(g_nSysEikQbOverheadCount >= 300000)
    {
        _TRACE((_RTK | LEVEL_1, "                                         "));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] g_nSysEikQbOverheadCount = %d", g_nSysEikQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Average EI_K QB count = %d", g_nSysEikQbOverheadSum / g_nSysEikQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Maximum EI_K QB count = %d", g_nSys_EikQbOverheadMax));
        g_nSysEikQbOverheadCount = g_nSysEikQbOverheadSum = g_nSys_EikQbOverheadMax = 0;
    }
    if(g_nSysDiuQbOverheadCount >= 1000)
    {
        _TRACE((_RTK | LEVEL_1, "                                         "));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] g_nSysDiuQbOverheadCount = %d", g_nSysDiuQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Average DI_U QB count = %d", sys_DiuQbOverheadSum / g_nSysDiuQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Maximum DI_U QB count = %d", g_nSysDiuQbOverheadMax));
        g_nSysDiuQbOverheadCount = sys_DiuQbOverheadSum = g_nSysDiuQbOverheadMax = 0;
    }
    if(g_nSysDikQbOverheadCount >= 300000)
    {
        MaskInt = MsDisableInterrupt();
        _TRACE((_RTK | LEVEL_1, "                                         "));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] g_nSysDikQbOverheadCount = %d", g_nSysDikQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Average DI_K QB count = %d", g_nSysDikQbOverheadSum / g_nSysDikQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Maximum DI_K QB count = %d", g_nSysDikQbOverheadMax));
        g_nSysDikQbOverheadCount = g_nSysDikQbOverheadSum = g_nSysDikQbOverheadMax = 0;
        MsEnableInterrupt(MaskInt);
    }

    if(g_nSysIsrQbOverheadCount >= 2000)
    {
        _TRACE((_RTK | LEVEL_1, "                                         "));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] g_SysIsrQbOverheadCount = %d", g_nSysIsrQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Average ISR check QB count = %d", g_nSysIsrQbOverheadSum / g_nSysIsrQbOverheadCount));
        _TRACE((_RTK | LEVEL_1, "[Sys Enhance] Maximum ISR check QB count = %d", g_nSysIsrQbOverheadMax));
        g_nSysIsrQbOverheadCount = g_nSysIsrQbOverheadSum = g_nSysIsrQbOverheadMax = 0;
    }
#endif
}

#endif

#if defined(__SEPARATE_INTERRUPT_API_PROFILE__)
void profileIsrQbCount(u32 qb1, u32 qb2)
{
    u32 uTotalQbCount = ((5000 + qb2 - qb1) % 5000);
    if(uTotalQbCount > 500)
        return;

    g_nSysIsrQbOverheadCount++;
    g_nSysIsrQbOverheadSum += uTotalQbCount;
    if(uTotalQbCount > g_nSysIsrQbOverheadMax)
        g_nSysIsrQbOverheadMax = uTotalQbCount;
}
#endif



#if defined(__G1_INTERRUPT_PROFILE__)
u32 g_nSysDikQbOverheadSum = 0;
u32 g_nSysDikQbOverheadCount = 0;
u32 g_nSysDikQbOverheadMax = 0;
u32 g_nSysDiuQbOverheadSum = 0;
u32 g_nSysDiuQbOverheadCount = 0;
u32 g_nSysDiuQbOverheadMax = 0;
u32 g_nSysEikQbOverheadSum = 0;
u32 g_nSysEikQbOverheadCount = 0;
u32 g_nSysEikQbOverheadMax = 0;
u32 g_nSysEiuQbOverheadSum = 0;
u32 g_nSysEiuQbOverheadCount = 0;
u32 g_nSysEiuQbOverheadMax = 0;
u32 g_nSysIsrQbOverheadSum = 0;
u32 g_nSysIsrQbOverheadCount = 0;
u32 g_nSysIsrQbOverheadMax = 0;

void getProfileTick(u32* puTick)
{
    *puTick = DrvTimerOstickGetCount();
}
#endif


#if (defined(__SEPARATE_INTERRUPT_API__) && defined(__SEPARATE_INTERRUPT_API_PROFILE__)) \
    || defined(__G1_INTERRUPT_PROFILE__)

u32 sys_DikQbCount1 = 0;
u32 sys_DikQbCount2 = 0;
u32 sys_DiuQbCount1 = 0;
u32 sys_DiuQbCount2 = 0;
u32 sys_EikQbCount1 = 0;
u32 sys_EikQbCount2 = 0;
u32 sys_EiuQbCount1 = 0;
u32 sys_EiuQbCount2 = 0;

void profileDikQbCount(void)
{
    u32 uTotalQbCount = ((5000 - sys_DikQbCount1 + sys_DikQbCount2) % 5000);
    if(uTotalQbCount > 100)
        return;

    g_nSysDikQbOverheadCount++;
    g_nSysDikQbOverheadSum += uTotalQbCount;
    if(uTotalQbCount > g_nSysDikQbOverheadMax)
        g_nSysDikQbOverheadMax = uTotalQbCount;
}

void profileDiuQbCount(void)
{
    u32 uTotalQbCount = ((5000 - sys_DiuQbCount1 + sys_DiuQbCount2) % 5000);
    if(uTotalQbCount > 100)
        return;

    g_nSysDiuQbOverheadCount++;
    g_nSysDiuQbOverheadSum += uTotalQbCount;
    if(uTotalQbCount > g_nSysDiuQbOverheadMax)
        g_nSysDiuQbOverheadMax = uTotalQbCount;
}

void profileEikQbCount(void)
{
    u32 uTotalQbCount = ((5000 - sys_EikQbCount1 + sys_EikQbCount2) % 5000);
    if(uTotalQbCount > 100)
        return;

    g_nSysEikQbOverheadCount++;
    g_nSysEikQbOverheadSum += uTotalQbCount;
    if(uTotalQbCount > g_nSysEikQbOverheadMax)
        g_nSysEikQbOverheadMax = uTotalQbCount;
}

void profileEiuQbCount(void)
{
    u32 uTotalQbCount = ((5000 - sys_EiuQbCount1 + sys_EiuQbCount2) % 5000);
    if(uTotalQbCount > 100)
        return;

    g_nSysEiuQbOverheadCount++;
    g_nSysEiuQbOverheadSum += uTotalQbCount;
    if(uTotalQbCount > g_nSysEiuQbOverheadMax)
        g_nSysEiuQbOverheadMax = uTotalQbCount;
}
#endif


#ifndef __I_SW__
void sys_startProfilIsr(void)
{
    static u32 under_process = FALSE;
    MsIntMask_e itMask;

    if(under_process == TRUE)
    {
        _TRACE((_RTK | LEVEL_1, "sys_startProfilIsr: it's under process!"));
        return;
    }
    else if(sys_bSwdISRProfileOn == TRUE)
    {
        _TRACE((_RTK | LEVEL_1, "sys_startProfilIsr: ISR profile is already started!"));
        return;
    }
    under_process = TRUE;

    isr_execution_func = (u32*)MsGetIramMemory(sizeof(u32) * isr_execution_array_size);
    if(!isr_execution_func)
    {
        _TRACE((_RTK | LEVEL_1, "failed to allocate iram for isr_execution_func"));
        isr_execution_func = (u32*)MsAllocateMem(sizeof(u32) * isr_execution_array_size);
        if(!isr_execution_func)
            _TRACE((_RTK | LEVEL_1, "failed to allocate eram for isr_execution_func"));
    }

    isr_execution_ticks = (u32*)MsGetIramMemory(sizeof(u32) * isr_execution_array_size);
    if(!isr_execution_ticks)
    {
        _TRACE((_RTK | LEVEL_1, "failed to allocate iram for isr_execution_ticks"));
        isr_execution_ticks = (u32*)MsAllocateMem(sizeof(u32) * isr_execution_array_size);
        if(!isr_execution_ticks)
            _TRACE((_RTK | LEVEL_1, "failed to allocate eram for isr_execution_ticks"));
    }

    isr_execution_services = (u32*)MsGetIramMemory(sizeof(u32) * isr_execution_array_size);
    if(!isr_execution_services)
    {
        _TRACE((_RTK | LEVEL_1, "failed to allocate iram for isr_execution_services"));
        isr_execution_services = (u32*)MsAllocateMem(sizeof(u32) * isr_execution_array_size);
        if(!isr_execution_services)
            _TRACE((_RTK | LEVEL_1, "failed to allocate eram for isr_execution_services"));
    }

    nested_isr_accumulation = (u32*)MsGetIramMemory(sizeof(u32) * isr_accumulation_array_size);
    if(!nested_isr_accumulation)
    {
        _TRACE((_RTK | LEVEL_1, "failed to allocate iram for nested_isr_accumulation"));
        nested_isr_accumulation = (u32*)MsAllocateMem(sizeof(u32) * isr_accumulation_array_size);
        if(!nested_isr_accumulation)
            _TRACE((_RTK | LEVEL_1, "failed to allocate eram for nested_isr_accumulation"));
    }

    if((!isr_execution_func) || (!isr_execution_ticks) || (!isr_execution_services) || (!nested_isr_accumulation))
    {
        if(isr_execution_func)
        {
            MsReleaseMemory(isr_execution_func);
            isr_execution_func = NULL;
        }
        if(isr_execution_ticks)
        {
            MsReleaseMemory(isr_execution_ticks);
            isr_execution_ticks = NULL;
        }
        if(isr_execution_services)
        {
            MsReleaseMemory(isr_execution_services);
            isr_execution_services = NULL;
        }
        if(nested_isr_accumulation)
        {
            MsReleaseMemory(nested_isr_accumulation);
            nested_isr_accumulation = NULL;
        }
    }
    else
    {
        memset(isr_execution_func, 0, sizeof(u32)*isr_execution_array_size);
        memset(isr_execution_ticks, 0, sizeof(u32)*isr_execution_array_size);
        memset(isr_execution_services, 0, sizeof(u32)*isr_execution_array_size);
        memset(nested_isr_accumulation, 0, (sizeof(u32)*isr_accumulation_array_size));

        itMask = MsDisableInterrupt();
        sys_bSwdISRProfileOn = TRUE;
        MsEnableInterrupt(itMask);
    }
    under_process = FALSE;
}
#endif

void sys_dumpIsrProfileInfo(void)
{
    u32 k, percent, isr_total = 0;
    MsIntMask_e itMask;

    if(sys_bSwdISRProfileOn == FALSE)
    {
        _TRACE((_RTK | LEVEL_1, "sys_dumpIsrProfileInfo: ISR profile is never started!"));
        return;
    }

    itMask = MsDisableInterrupt();
    sys_bSwdISRProfileOn = FALSE;

    for(k = 0; k < isr_execution_array_size; k++)
        isr_total += isr_execution_ticks[k];

    _TRACE((_RTK | LEVEL_1, "PURE_ISR		: QbCount = 0x%0.8x", isr_total));
    _TRACE((_RTK | LEVEL_1, "ISR = PURE_ISR + COMMON HANDLER"));

    for(k = 0; k < isr_execution_array_size; k++)
    {
        if(isr_execution_func[k] && isr_execution_ticks[k])
        {
            percent = (u32)(((float)isr_execution_ticks[k] * 1000) / (float)isr_total);
            _TRACE((_RTK | LEVEL_1, "QbCount = 0x%0.8x, QbPercent = %0.2d.%d , service 0x%0.8x times isr_func <SYMBOL> (0x%0.8x)"
                    , isr_execution_ticks[k], percent / 10, percent % 10, isr_execution_services[k], isr_execution_func[k]));
        }
    }

    if(isr_execution_func)
    {
        MsReleaseMemory(isr_execution_func);
        isr_execution_func = NULL;
    }
    if(isr_execution_ticks)
    {
        MsReleaseMemory(isr_execution_ticks);
        isr_execution_ticks = NULL;
    }
    if(isr_execution_services)
    {
        MsReleaseMemory(isr_execution_services);
        isr_execution_services = NULL;
    }
    if(nested_isr_accumulation)
    {
        MsReleaseMemory(nested_isr_accumulation);
        nested_isr_accumulation = NULL;
    }

    MsEnableInterrupt(itMask);
}


/**
 * \brief idle task
 */

void idle_Task(void)
{
#ifdef __WATCH__
    u8    i;
#ifdef __CPU_LOAD__ //CPU Load info are outputting only if watch are ON
    static u8 last_rtc = 0;
//	vm_rtcTimeFormat_t system_time;
    static u16 prevRT_Clock;
    u16 IdlePeriod, FiltIdlePeriod = 0;
    MsIntMask_e ItMask;
    bool interrupted = TRUE;
    static u16 prev_bgd_loop_count = 0;
    static u16 delta_cnt;
    static u16 bgd_loop_count = 0;
    static s32 frame_cnt = 0, prev_frame_cnt = 0;
    extern s32 hac_GlobalFn;
    u32 idle_time;
#endif
#endif
#ifndef __I_SW__
    extern u8 sys_lastJtagState;
#endif
    static u32 idle_loops = 0;
    static u8 cmd_loops = 0;  //by Eric

//#ifdef __RTK_STACK_DIAGNOSE__
    //u16 nQb1, nQb2, Qb;
    //MsIntMask_e ItMask;
//#endif


    /*
    ** Check for a watchdog reset and trace it
    */
    if(sys_WatchDogRstOccured())
    {
        u32 l_u32_LastPort = 0;
        // Activate User Mode if HAPC mode was activated before reset
        l_u32_LastPort = sys_DbgGetLastUsedHapcPort();
        if(l_u32_LastPort)  // if 0, it means that it was not a HAPC port
#if defined(__V24_COMPOSITE_USB___)
            rm_RecoverV24UserMode(l_u32_LastPort);
#else
            v24_RequestExt(V24_ENABLE_USER_MODE, VM_V24_USER_MODE, l_u32_LastPort);
#endif
    }

#ifdef __WATCH__
    InitDefaultWatches();
    for(i = 0; i < NB_MAX_WATCH; i++) Watches[i].Enable = (Diagnose[_WTCH].Level >> i) & 1;
#endif

    {
#ifndef __I_SW__
        // Eric YK Wu adds debug code to record idle entry time
        extern void recordPoweOnTimestamp(u32 timestamp);
        recordPoweOnTimestamp(DrvTimerStdaTimerGetTick());
#endif
    }
//#if !defined(__G1__)
//    hwl_InitIntFunc(); // register interrupt function
//#endif

#ifdef __KERNEL_DEBUG__
    {
        extern void MsHMEMLoggingFilterRegister(MsTaskId_e taskID);
        MsHMEMLoggingFilterRegister(MsCurrTask());
    }
#endif

#ifdef __SYS_OSTICK_EXTENSION__
    sys_RegisterOsTickExMonitor();
#endif

    while(1)
    {
#ifdef __FIXME__
        MsSysAutoCpuIdleAdjust();
#endif

#ifdef __ABNORMAL_SLEEP_DEBUG__
        if(slpdbg_cpu_profile_step == 1)
        {
            // Reset all profile information
            sys_startProfiling("SLPDBG");
            slpdbg_cpu_profile_step = 2;
        }
        else if(slpdbg_cpu_profile_step == 3)
        {
            // Trace dump to TMT
            sys_bSwdProfileOn = FALSE;
            //since buffer is only 2KB, keep 4 records
            //if(slpdbg_abnormal_sleep_count <= 4)
            {
                sys_dumpProfileInfo("SLPDBG", 1);
                // Dump all information
                slpdbg_DumpSleepInfo();

                slpdbg_buffer_switch = 1;
                _DBGINFO((_HWL, "RF RX Win (%i frame, %i qb) TX win (%i qb)", Hwlrf_RxWinSumFc, Hwlrf_RxWinSumQb, Hwlrf_TxWinSumQb));
                slpdbg_buffer_switch = 0;
            }
            slpdbg_cpu_profile_step = 0;
        }
#endif //__ABNORMAL_SLEEP_DEBUG__

#ifdef __RTK_STACK_DIAGNOSE__

        //ItMask = RTK2_DISABLE();
        //nQb1 = g_ptW5TbuC->u16_QbCnt;
        //RtkStackUsageCheck(g_stackIndex);
        //nQb2 = g_ptW5TbuC->u16_QbCnt;
        //RTK2_ENABLE(ItMask);
        //Qb = (5000 + nQb2 - nQb1) % 5000;
        //_TRACE((_SYS|LEVEL_2, "RtkStackUsageCheck: g_stackIndex [%d] takes [%d]QbCnt",g_stackIndex, Qb));
        //g_stackIndex++;

        //if(g_stackIndex > RTK_FIRST_CUSTOMER_TASKID + rtk_CustomerTasksCount + 3)
        //	g_stackIndex = 0;

#endif

#if defined(__CPU_LOAD__) && defined(__WATCH__)
        bgd_loop_count++;
        //!First, compute the average idle task execution time
#warning RTC for arm is different
        g_ptIncenseRtcReg->rtc_pwr_en |= RTC_CPU_ITF_EN;
        RT_Clock = g_ptIncenseRtcReg->u16_Cnt;
//    g_ptIncenseRtcReg->rtc_pwr_en &= ~RTC_CPU_ITF_EN;

        prevRT_Clock = RT_Clock;
        PreemptionFlag = 0;
        interrupted = TRUE;
        i = hac_GlobalFn;
        if(i >= (last_rtc + CPU_STEP))
        {

            delta_cnt = bgd_loop_count - prev_bgd_loop_count;
            prev_bgd_loop_count = bgd_loop_count;
            idle_time = delta_cnt * FiltIdlePeriod;
            _TRACE((_SYS | LEVEL_2, "frame %d to %d", prev_frame_cnt, hac_GlobalFn));
            frame_cnt = hac_GlobalFn - prev_frame_cnt;
            prev_frame_cnt = hac_GlobalFn;

            if(idle_time > (frame_cnt * RT_CLOCKS_PER_FRAME))
                idle_time = frame_cnt * RT_CLOCKS_PER_FRAME;
            idle_time = 100 * ((idle_time >> 2) + slept_time) / ((frame_cnt * RT_CLOCKS_PER_FRAME) >> 2) ;


            if(slept_time > ((frame_cnt * RT_CLOCKS_PER_FRAME) >> 2))
                slept_time = ((frame_cnt * RT_CLOCKS_PER_FRAME) >> 2);
            _TRACE((_SYS | LEVEL_2, "Slept %d x32k over last 4s", slept_time));
            slept_time = 100 * slept_time / ((frame_cnt * RT_CLOCKS_PER_FRAME) >> 2) ;
            _TRACE((_SYS | LEVEL_2, "It about %d per cent", slept_time));

            Sys_Trc [CPU]  = 100 - slept_time;
            //! So, how many idle loop do we ran in the last CPU_LOAD_STEP sec

            slept_time = 0;
            last_rtc = hac_GlobalFn ;
        }
        if(i < last_rtc)
            last_rtc = i;

#endif /*__CPU_LOAD__*/

        if(v24_SerialOn != 0)
        {
            // Treat the quick trace buffer
            trc_PurgeQuickTrcBuf();
            while(v24_PollRxTx()) {}
        }

        /* ---------------- Call user's idle function ----------------------*/

        // Handle the rest of idle hook functions!
        sys_CustomIdleProc2();

        // Eric: here we handle RX cmd 3 times then continue, to react in time
        do
        {
            cmd_loops++;
            if(cmd_loops > 3)
            {
                cmd_loops = 0;
                continue;
            }
        }
        while(sys_CustomIdleProc());

        /* ------------------- Manage watch windows ------------------------*/

#ifdef __DIAGNOSE__
        if(v24_SerialOn != 0)
        {
#ifdef __WATCH__
            UpdtWatchWin();
#endif /* __WATCH__ */
        }
#endif /* __DIAGNOSE__  */

#ifdef __CPU_LOAD__
        bgd_loop_count++;
        ItMask = MsDisableInterrupt();
//any int or preemption must set this flag
        if(PreemptionFlag == 0)
            interrupted = FALSE;

        MsEnableInterrupt(ItMask);


        if(RT_Clock > prevRT_Clock)
            IdlePeriod = RT_Clock - prevRT_Clock;
        else
            IdlePeriod = FiltIdlePeriod;

        if(!interrupted)
            FiltIdlePeriod = Filter(FiltIdlePeriod, IdlePeriod);


#endif

#if defined(__G1__) || defined(__INFINITY__)
#warning FIXME for G1 or __INFINITY__
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2)] = 0;
#else
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2)    ] = (u32) g_ptW5IrqControl->u32_Mask0;
#endif
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2) + 1] = (u32) rtk_SoftwareWatchDogCounts;
        /* --------------------- Manage power down -------------------------*/

#if defined(__TASK_PWDN__) || defined(__G1__)
#if defined(__G1__)
#warning check to implement G1 fint wake up function.
#else

        //   hwl_ClearUnusedInt();

#endif

        if(sys_GetSleepModeState() == TRUE && !DrvDMA2DIsAvtive())
        {
#ifdef __LOGIC_ANALYSER__
            UP_GPIO(SLEEP_GPIO)
#endif

#if defined(__INTERRUPT_INTEGRITY_PROTECT__)
            idleCheckIntIntegrity();
#endif  // __INTERRUPT_INTEGRITY_PROTECT__

#if !defined(__I_SW__)
            sys_GotoSleep();
#endif

#ifdef __LOGIC_ANALYSER__
            DOWN_GPIO(SLEEP_GPIO)
#endif
        }
//#ifdef __LIGHT_SLEEP_IN_IDLE__
        else
        {
            sys_GotoLightSleep();
        }
//#endif
#endif

#if defined(__SOFTWARE_WATCHDOG_PROFILE__)
        //sys_SwdCountProfile();

        // Dump previous software watchdog timeout information
        sys_SwdTimeoutDump();
#endif

#if defined(__INTERRUPT_INTEGRITY_PROTECT__)
        else
        {
            idleCheckIntIntegrity();
        }
#endif  // __INTERRUPT_INTEGRITY_PROTECT__


#if defined(__G1__)
#warning FIXME for G1
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2) + 2] = 0;
#else
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2) + 2] = 0;
#endif
        rtkWDDumpInfo[(rtkWDDumpInfoIndex << 2) + 3] = (u32) rtk_SoftwareWatchDogCounts;
        rtkWDDumpInfoIndex = (rtkWDDumpInfoIndex + 1) % 10;

#if defined(__CHIPDRV_R2_WDT__) || defined(__CHIPDRV_INFINITY_WDT__) //__G1__
        sys_DelayWatchDogReset();
#else
        WDogCountRstExpected = TRUE;
#endif

        // check the current Jtag status and E2P_SYSFEATURE value every 100 idle cycles
        idle_loops ++;
        if(idle_loops >= 100)
        {
            idle_loops = 0;
#ifndef __I_SW__
            if(sys_lastJtagState != sys_GetJtagState())
            {
                if(0 == sys_lastJtagState)
                {
                    _TRACE((_SYS | LEVEL_0, ">>>>> enable Jtag in idle task"));
                    DrvWDTimer0Enable(FALSE);
                    DrvWDTimer1Enable(FALSE);
                    DrvClkgenEnablePower(PERIPH_JTAG, TRUE);
                    sys_lastJtagState = 1;
                }
                else if(1 == sys_lastJtagState)
                {
                    _TRACE((_SYS | LEVEL_0, ">>>>> disable Jtag in idle task"));
                    sys_lastJtagState = 0;
                }
                else
                {
                    _TRACE((_SYS | LEVEL_0, ">>>>> wrong Jtag state %d in idle task", sys_lastJtagState));
                }
                sys_SetJtagState(sys_lastJtagState);
            }
#endif
        }
    }
}


#ifndef __I_SW__
void timer_Task(void)
{
    extern bool MsReceiveEx(MsMailbox_e eMailbox, MsObj_t *pMsg);
    MsObj_t  Obj;
    MsCbTimer_t cbtimer;
    u32 tickStart = 0, tickEnd = 0, tickDiff;
    vm_sys_SpeedProfile_e profile_index = VM_SYS_SPEED_PROFILE_SLOW;
    static int cb_run_period_limit_us[VM_SYS_SPEED_PROFILE_LAST] = {93, 83, 73, 63};
    int cb_period_us = 0;
    int limit_period_us = 0;

    Obj.Msg = (void*)&cbtimer;

    while(1)
    {
        memset((void*)&cbtimer, 0, sizeof(cbtimer));
        MsReceiveEx(TIMER_MBX, &Obj);

        if(cbtimer.pfCB)
        {
            tickStart = DrvTimerStdaTimerGetTick();
            cbtimer.pfCB(cbtimer.eTimerID, cbtimer.UserData);
            tickEnd = DrvTimerStdaTimerGetTick();
            if(tickEnd > tickStart) tickDiff = tickEnd - tickStart;
            else tickDiff = DrvTimerGetStdaTimerMaxCount() - tickEnd + tickStart;

            // Convert to us
            cb_period_us = DrvTimerStdaTimerTick2Us(tickDiff);

            // determine criteria per current speed profile
            profile_index = sys_getSpeedProfile(VM_SPEED_PROFILE_TARGET_CPU);
            if(profile_index >= VM_SYS_SPEED_PROFILE_LAST)
                limit_period_us = cb_run_period_limit_us[VM_SYS_SPEED_PROFILE_SLOW];
            else
                limit_period_us = cb_run_period_limit_us[profile_index];

            if(cb_period_us >= limit_period_us)
            {
                _TRACE((_SYS | LEVEL_23, "timer_Task callback 0x%8X processing %d ticks. (SPEED_PROFILE: 0x%x)", (u32)cbtimer.pfCB, tickDiff, profile_index));
            }
        }
        else
        {
            _ERROR((_SYS | FATAL, "timer_Task NULL callback  id=0x%0.8x, userdata=0x%0.8x", cbtimer.eTimerID, cbtimer.UserData));
        }
    }
}

#if defined (__RTK_OVER_R2__)
#include "sys_r2.h"
#endif
#include "sys_sys_dpm_mgr.h"
typedef struct
{
    pDpmCtrlBlk_t ptrDpmCtrlBlk;
    u32 vaddr;
    u32 op;
} Body_t;
#include "stdmsg.ht"
#include "osdefs.hc"

MsTaskId_e dsr_TaskId;

void dsr_Task(void)
{
    MsObj_t  Obj;
    Msg_t *pMsg;

    dsr_TaskId = MsCurrTask();

    while(1)
    {
        MsReceive(DSR_MBX, &Obj, NULL);

        pMsg = (Msg_t *)Obj.Msg;
        MdlCpuRequestSpeed(MDL_CPU_DSR, MDL_CPU_SUPFAST);

        if(pMsg->Header.TypMsg != VM_OS_TIMER_EXPIRED)
        {
            if(pMsg->Header.TypMsg == 0xABCD)
            {
                extern void MsMmapSwap(Msg_t * pMsg);
                MsMmapSwap(pMsg);
            }
            else if(pMsg->Header.TypMsg == 0xABCE)  /* DPM text demand paging */
            {
                extern void DpmTextSwap(Msg_t * pMsg);
                DpmTextSwap(pMsg);
            }
            else if(pMsg->Header.TypMsg == 0xABCF)  /* DPM data demand paging */
            {
                extern void DpmDataSwap(Msg_t * pMsg);
                DpmDataSwap(pMsg);
            }
#if 0 /* sys-load SL-DLM used */
            else if(pMsg->Header.TypMsg == 0xABCA)
            {
                extern void SldlmSystemLoadModule(Msg_t * pMsg);
                SldlmSystemLoadModule(pMsg);
            }
#endif
        }

        MdlCpuRequestSpeed(MDL_CPU_DSR, MDL_CPU_SLOW);

        if(Obj.Msg)
            MsReleaseMemory(Obj.Msg);
    }
}

#else //__I_SW__

void mdl_Task(void)
{
   MsObj_t   Mdl_Obj;
   vm_msg_t       *pMsgRec = (vm_msg_t *)NULL;

   /*
   **   Create Applicative TASK
   */
   cus_Main();

   /*
   **   READ Middleware MAILBOX
   */

  while( 1 )
  {
    MsReceive(VM_MBX_MDL, &Mdl_Obj, NULL);
    pMsgRec = (vm_msg_t *) Mdl_Obj.Msg;

    // Give received message to Middleware parser function
    //Mdl_Parse(pMsgRec);

    if (RTK_OBJ_EVENT != Mdl_Obj.Type)
    {
	    // Release message pointer
	    MsReleaseMemory(pMsgRec);
    }
  }
}

#endif //__I_SW__

