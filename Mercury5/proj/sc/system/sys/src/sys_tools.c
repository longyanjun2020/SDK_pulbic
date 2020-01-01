/**
 * \file SYSTOOLS.C
 * \brief system tools      .
 * Contents:   sys_BackTrace
 * sys_StatusRegister
 * sys_InitE2pErrorStack
 * sys_StoreErrorInE2p
 * sys_StoreBackTraceInE2p
 * sys_E2pErrorStackAnalysis
 * sys_DelayWatchDogReset
*/

#include "stdcomp.h"   /* Common define flags */
#include <string.h>
#include "sys_sys.h"
#include "sys_sys_bootinit.h"
#include "sys_traces.ho"
#include "fms_insd.hi"
#include "sys_dbg.h"
#include "sys_tools.h"
#include "sys_sys_bootinit.h"
#if !defined(__I_SW__)
#include "cus_capability.h"
#endif
#ifdef	__RTK_DIAGNOSE_ENHANCE__
#include "sys_rtk_backtrace.h"
#include "drv_rtc.h"
#endif


#ifdef __SYS_OSTICK_EXTENSION__
#include "sys_MsWrapper_cus_os_type.h"
#include "drv_timer_types.h"
#include "sys_sys_mbx_def.h"
#endif

#include "sys_sys_chip.h"

extern u32 sys_RAMSize;
extern s8 UartSendTrace(const char *strFormat, ...);

u32 sys_CustomRomSize;

volatile bool sys_CustomerWDogRst;

const u8 sys_ReversedByteTable[256] =
{
   0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
   0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
   0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
   0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
   0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
   0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
   0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
   0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
   0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
   0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
   0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
   0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
   0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
   0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
   0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
   0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
}
;

/**
 * \brief In case of change of the folowing define, take care of the constants
 * defined in kernel.i
 */


u32 SavedR14;  /* Used as parameter from RtkStatusRegister to RtkBackTrace. */

/**
 * \brief STATIC VARIABLES
 */
#ifdef __LOGIC_ANALYSER__  // Set this flag on enable to ouptu some data (task activity) on D0 IO. Useful for debugging only.
/**
*\brief 	state of the Data output signal
*/
#define 	SIGNAL_OUT_SIZE			16
volatile u16 	sys_signal_out_state 	= 0;
#endif //__LOGIC_ANALYSER__
/**
 * \brief Method used to compute the hardware id
 */
static bool sys_jtagState = TRUE;
static bool sys_HwWdtDbgState = FALSE;
static bool sys_sleepModeState = TRUE;
static u8 sys_MallocFailState = 0;

u8  CoreVersion[VM_SYS_CORE_VERSION_NB_CHAR];
u8  CusVersion[VM_SYS_CORE_VERSION_NB_CHAR];
u32 sys_CustomerRAMSize;

/**
 */
__ONCE_CALL_ON_BOOT__ void sys_StatusRegister (void)
{

    _TRACE ((_RTK | LEVEL_2, "sys_LastRstIsWatchDog = 0x%X",SysDebugStruct.WatchdogResetOccured));
    if (SysDebugStruct.WatchdogResetOccured == FALSE)
        return;

    // if Watchdog reset was expected, traces were sent before reset, so no need to restore them
    if (SysDebugStruct.ExpectedWatchdogReset == FALSE)
    {
#ifdef __FIXME__
        u32 j;
        for (j = 0; j < 12; j++) // R3 to R14
        {
            _ERROR ((_RTK, "r%i  0x%lx", (j+3), SysDebugStruct.ARMRegisters[j]));
        }
        SavedR14 = SysDebugStruct.ARMRegisters[11];
        _ERROR ((_RTK, "cpsr 0x%lx", SysDebugStruct.ARMRegisters[12]));
        sys_watchDogExtract();
#else
        UartSendTrace("[[ERROR]] Watchdog reset was not expected\n");
#endif
    }
}

/**
 * \brief: check in the debug area if the last reset was due to a Watchdog
 */
bool sys_WatchDogRstOccured (void)
{
	if (SysDebugStruct.WatchdogResetOccured == TRUE)
		return TRUE;
	return FALSE;
}

/**
 * \brief: check in the debug area if the last reset was due to a software reset (jump to 0)
 */
__ONCE_CALL_ON_BOOT__ bool sys_SoftRstOccured (void)
{
	if (SysDebugStruct.SoftResetOccured == TRUE)
		return TRUE;
	return FALSE;
}

/**
 * \brief: check in the debug area if the last reset was due to a Expected Watchdog
 */
__ONCE_CALL_ON_BOOT__ bool sys_ExpectedWatchDogRstOccured (void)
{
    return SysDebugStruct.ExpectedWatchdogReset;
}


#ifdef __FIXME__
/**
 * \brief Get OneC version
 */
void sys_GetInfoVersion(ascii *pSize, ascii *pDate, ascii *pTime)
{
	const u8 max_stamp = 10;
	u8    i;
	ascii *Ptr = sys_GetBinInfo( );

	*pSize = '\0';
	*pDate = '\0';
	*pTime = '\0';

	if( Ptr )
	{
		/* Software size */
		for( i = 0; (*Ptr != ' ') && (i < max_stamp) ;  i++, Ptr++ )
			pSize[i] =  *Ptr;
		pSize[i] = '\0';

		/* Software date */
		Ptr++;
		for( i = 0; (*Ptr != ' ') && (i < max_stamp) ;  i++, Ptr++ )
			pDate[i] =  *Ptr;
		pDate[i] = '\0';

		/* Software date */
		Ptr++;
		for( i = 0; (*Ptr != ' ') && (i < max_stamp) ;  i++, Ptr++ )
			pTime[i] =  *Ptr;
		pTime[i] = '\0';
	}
}
#endif

/**
 * \brief Returns a hardware identifier
 * \return (u32) Hardware identifier or 0
 */
u32 sys_GetHardwareId(void)
{
#if !defined(__I_SW__)
	if (CusIsNandEnabled()==FALSE)
        return fms_GetHardwareId();
  	else
        return 0xFFFFFFFF;
#else
    #ifndef __NAND__
	    return fms_GetHardwareId();
    #else
        return 0xFFFFFFFF;
    #endif
#endif

}


/**
 */
u32 sys_GetModuleROMsize(void)
{
	return (sys_CustomRomSize);
}

/**
 */
u32 sys_GetModuleRAMsize(void)
{
	return (sys_RAMSize);
}

/**
 */
u8 sys_GetJtagState(void)
{
	return sys_jtagState;
}

/**
 */
void sys_SetJtagState(u8 value)
{
	sys_jtagState = value;
}

/**
 */
u8 sys_GetHwWdtDbgState(void)
{
	return sys_HwWdtDbgState;
}

/**
 */
void sys_SetHwWdtDbgState(u8 value)
{
	sys_HwWdtDbgState = value;
}

/**
 */
bool sys_GetSleepModeState(void)
{
	return sys_sleepModeState;
}

/**
 */
void sys_SetSleepModeState(bool enable)
{
	sys_sleepModeState = enable;
}

void sys_SetMallocFailState(u8 value)
{
	sys_MallocFailState = value;
}

u8 sys_GetMallocFailState(void)
{
	return sys_MallocFailState;
}


/**
 * \brief Let the baseband's watch dog terminate the code execution
 * Interface : n/a
 * \return n/a
 */
void sys_DieByWatchDog(void)
{
	// _TRACE((_SYS, "Waiting for a watch dog reset"));
	for(;;);
}

#ifdef __LOGIC_ANALYSER__
/*******************************************
*\defgroup OuputTracedoc   About the Real time output traces
*
*
*********************************************/
/**************************************************
 *\brief Assign a value to output AND save it for futur read
 *\return nothing
 *\ingroup OuputTracedoc
 ****************************************************/
void assign_output(u16 signal_value)
{
// for avoiding data bus glitch of previous writes...
	*g_ptFalseSignal	= signal_value;
	g_ptRealTimeOutput->DataOutput=signal_value;
	*g_ptFalseSignal	= signal_value;
	sys_signal_out_state = signal_value;
}
/**************************************************
 *\brief Put the whole D0-D15 signal down
 *\return nothing
* \ingroup OuputTracedoc
 ****************************************************/
void	sys_reset_all_signal(void)
{
	assign_output(0x0000);
}

/**************************************************
 * \brief Put the whole D0-D15 signal high
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_set_all_signal(void)
{
	assign_output(0xFFFF);
}
/**************************************************
 * \brief This functions set the data bit signal_number  while resetting all the
 *          others.
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_set_only_signal_n(u8 signal_number)
{
	//if number out_of_range, don't do anything
	if(signal_number >= SIGNAL_OUT_SIZE)
		return;
	assign_output((u16) (1<<signal_number));
}
/**************************************************
 * \brief This functions reset the data bit signal_number  while resetting all the
 *          others.
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_reset_only_signal_n(u8 signal_number)
{
	//if number out_of_range, don't do anything
	if(signal_number >= SIGNAL_OUT_SIZE)
		return;
	assign_output((u16) ~(1<<signal_number));
}
/**************************************************
 * \brief This functions set the data bit signal_number
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_set_signal_n(u8 signal_number)
{
	//if number out_of_range, don't do anything
	if(signal_number >= SIGNAL_OUT_SIZE)
		return;
	assign_output(((u16) (1<<signal_number))| sys_signal_out_state);
}
/**************************************************
 * !\brief This functions reset the data bit signal_number
 *\param  number of the signal (from D0 to D15)
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_reset_signal_n(u8 signal_number)
{
	//if number out_of_range, don't do anything
	if(signal_number >= SIGNAL_OUT_SIZE)
		return;
	assign_output(((u16) ~(1<<signal_number)) & sys_signal_out_state);
}
/**************************************************
 *! \brief This functions codes a char on the data bus. The first bit is
 *           in start_bit value
 * \ waring : it does not preserve the signal state
 *\param  value to code and first bit's place
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_codes_value_on_signal(u8 value_to_code, u8 first_bit_place)
{
	//to high, use the maximum available
	if(first_bit_place+8>SIGNAL_OUT_SIZE)
		first_bit_place=SIGNAL_OUT_SIZE-8;

	assign_output((u16) (value_to_code<<first_bit_place));
}

/**************************************************
 * \brief This functions tests all the signal. when launching, a "pyramid"
 *          Signal should MUST appear on the output
 *\param  nothing
 * \return nothing
 * \ingroup OuputTracedoc
 ****************************************************/
void	sys_test_pyramid(void)
{
	char i;
	for (i=0;i<SIGNAL_OUT_SIZE; i++)
		sys_set_signal_n(i);

	for (i=SIGNAL_OUT_SIZE;i>0; i--)
		sys_reset_signal_n(i-1);
}
#endif


#ifdef __MSTAR_DUAL_SIM_E2P__

#define TYP_NOID    0x00                /* No identity                      */
#define TYP_IMSI    0x01                /* IMSI                             */
#define TYP_IMEI    0x02                /* IMEI                             */
#define TYP_IMEISV  0x03                /* IMEISV                           */
#define TYP_TMSI    0x04                /* TMSI                             */
#define MS_IDENTITY(_p_)     (((u8 *)_p_)[1] & 7)

__ONCE_CALL_ON_BOOT__
bool sys_IsValidImei(vm_Imei_t imei)
{
    u8 i=0;

    //Check length
    if( imei[0] != 8 )
        return FALSE;

    //Check type of identity
    if( MS_IDENTITY( imei ) != TYP_IMEI)
        return FALSE;

    //Check IMEI digits (numeric)
    if( (imei[1]>>4) > 9 )
        return FALSE;

    for( i=2; i<9; i++ )
    {
        if( ((imei[i]&0xf)>9) || ((imei[i]>>4)>9) )
            return FALSE;
    }

    return TRUE;
}
#endif


/**
 * \brief Get Core version
 * Interface : void opic_sysGetCoreVersion(char *pVersion)
 * \param [in,out] pVersion: String Pointer for the core version
 */
void SysGetCoreVersion(char *pVersion)
{
    CoreVersion[VM_SYS_CORE_VERSION_NB_CHAR-1] = 0x00;
    strcpy((char*)pVersion,(const char*)CoreVersion);
    return;
}

/**
 * \brief Print message through UART
 * Interface : void sys_UartPrintf(const char *fmt, ...)
 */
__RO_CODE_ON_BOOT__ void sys_UartPrintf(const char *fmt, ...)
{
#ifndef __I_SW__
    va_list args;
    char line_str[128];
    extern int vsprintf(char *buff, const char *fmt, va_list a);
    extern void sys_UartWriteString(u8* buf, u8 length);

    va_start(args, fmt);  /*lint !e530*/
    vsprintf(line_str, fmt, args);
    sys_UartWriteString((u8 *)line_str, strlen(line_str));
#endif
}


#ifdef __FIXME__
u32 sys_Platform_Verify(void)
{
	return (u32)sys_GetChipRevisionId() * 0xABBA;
}
#endif

#ifdef __RTK_OVER_R2__
volatile u32 SysTimerWdogctrlLen = 32;//SYS_TIMER_WDOGCTRL_LEN;
#else
volatile u32 SysTimerWdogctrlLen = SYS_TIMER_WDOGCTRL_LEN;
#endif

#ifdef __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
vm_rtcTimeFormat_t rtk_WatchDogResetTime;
#endif

void sys_DelayWatchDogReset(void)
{
	extern u32 backtrace_entry_counter_check(void);
#ifdef __SOFTWARE_WATCHDOG__
	// reset software watch dog counter
	extern u32 rtk_SoftwareWatchDogCounts;
	rtk_SoftwareWatchDogCounts = SysTimerWdogctrlLen;
#endif //__SOFTWARE_WATCHDOG__

	DrvWDTimer0Ack();
#ifndef __RTK_OVER_R2__
	DrvWDTimer1Ack();
#else
	// debug purpose only
	sys_delay_wd_stamp = DrvTimerGlobalTimerGetTick();
#endif

#if defined(__RTK_DIAGNOSE_ENHANCE__)
	if(!SysGetMPFlag() && (backtrace_entry_counter_check() == 0))
	{
		_RECORD_MSG_HISTORY(RESET_WD, 0, 0);
		backtrace_ToolResetTaskMgr(FALSE);
	}
#endif

#if defined(__SOFTWARE_WATCHDOG_PROFILE__)
	// Do not reset when profile mode on, it will call the function itself
	if(!sys_queryProfileState() && (backtrace_entry_counter_check() == 0))
		sys_resetSwdProfileInfo();
#endif
}

void sys_Delay( u32 i_u32_Delay_us )
{
	SYS_UDELAY(i_u32_Delay_us);
}

void resetWatchdog(void)
{
    #if defined(__SOFTWARE_WATCHDOG__) && defined(__RTK_DIAGNOSE_ENHANCE__)
    extern  u32             rtk_SoftwareWatchDogCounts;
    rtk_SoftwareWatchDogCounts = SysTimerWdogctrlLen;
    #endif

    DrvWDTimer0Ack();
    DrvWDTimer1Ack();
}

bool sys_IsUserMode(void)
{
    extern bool v24_IsUserMode(void);
#ifndef __I_SW__
    return v24_IsUserMode();
#else
    return TRUE;
#endif
}

#ifdef __SYS_OSTICK_EXTENSION__


#define SYS_OSTICK_EXT_MAX_HW_COUNT	        DrvTimerGetGlobalTimerMaxCount()
#define SYS_OSTICK_EXT_CHECK_PERIOD_COUNT	DrvTimerUserToHwTickOstick(DrvTimerHwToUserTick(SYS_OSTICK_EXT_MAX_HW_COUNT) - 1000)

/*
 * Wrapper OS tick extension implementation
 */
typedef struct SYS_OSTICK_EX_CB
{
	rtk_TimerId_t timer_id;
	u32 wrap_count;
	u32 tick_prev;
}	SYS_OSTICK_EX_CB_t;

static SYS_OSTICK_EX_CB_t sys_OsTickHwTimerWrapCB = {0x0, 0x0, 0x0};

static void sys_CheckOsTickWrapAround(void)
{
	u32 tick_now = 0;

	tick_now = DrvTimerGlobalTimerGetTick();

	// check wrap around
	if(sys_OsTickHwTimerWrapCB.tick_prev > tick_now)
	{
		sys_OsTickHwTimerWrapCB.wrap_count++;
	}
	sys_OsTickHwTimerWrapCB.tick_prev = tick_now;
}


static void sys_OsTickWrapMonitor(MsTimerId_e eTimerID, u32 UserData)
{
	if(eTimerID != sys_OsTickHwTimerWrapCB.timer_id) _ERROR((_SYS | FATAL, "ERROR: %d",eTimerID));

	sys_CheckOsTickWrapAround();
}

/* Register a periodical RTK timer to monitor HW timer wrap around
 * The period should be less than HW timer wrap around period
 */
__ONCE_CALL_ON_BOOT__ rtk_ErrCode_e sys_RegisterOsTickExMonitor(void)
{
	return MsStartCbTimerNative(&sys_OsTickHwTimerWrapCB.timer_id, sys_OsTickWrapMonitor, 0, SYS_OSTICK_EXT_CHECK_PERIOD_COUNT, SYS_OSTICK_EXT_CHECK_PERIOD_COUNT);
}

u64 sys_GetOsTickus(void)
{
	rtk_MaskImage_t  MaskInterrupt;
	u64 count = 0;

	MaskInterrupt = RTK2_DISABLE_K();

	sys_CheckOsTickWrapAround();

	count = ((u64)SYS_OSTICK_EXT_MAX_HW_COUNT * sys_OsTickHwTimerWrapCB.wrap_count + sys_OsTickHwTimerWrapCB.tick_prev);

	RTK2_ENABLE_K(MaskInterrupt);

	return DrvTimerGlobalTimerTick2MsEx(count*1000);
}
#endif
