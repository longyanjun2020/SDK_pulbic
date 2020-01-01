/****************************************************************************/
/*  File    : traces.c                                                                                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Traces and errors management                                                                    */
/*                                                                                                                                 */
/****************************************************************************/

/* __MSTAR_DUAL_SIM_REDUCE_CODE__ needs this definition for some declaration. */
#define __TRACE_C__


/************************************************************************
*   Include Files
************************************************************************/

//standard header
#include <string.h>
#if !defined( unix ) || defined( LINUX )
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include  "stdcomp.h"
#if defined (unix) || defined (LINUX)
#include "stdlib.hp"
#endif


//non-standard public header
#include  "sys_traces.ho"
#include "sys_rm_trc.ho"
#include "sys_rtk_ho.h"
#include "sys_sys.h"
#include "sys_sys_dbg.h"
#include "sys_rtk_incl.h"
#include "sys_sys_tools.h"
#ifdef __RTK_DIAGNOSE_ENHANCE__
#include "sys_rtk_backtrace.h"
#endif
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_util.h"


//non-standard private header
#include "remote.hi"
#include "dbg_scr.hi"
#include "osdefs.hc"
#include "e2p_defs.hi"
#include "fms_insd.hi"
#include "remote.ho"
#include "rtkproto.hp"
#ifdef __RTK_DIAGNOSE_ENHANCE__
#include "fms_trace.hi"
#endif



#define MAX_NUMBER_TRC_ARGS 6
#define QUICK_TRC_BUF_SIZE ((MAX_NUMBER_TRC_ARGS*4 /* StackSize */ + 2*4 /* r0 and r1 */)*200 /* Number of traces */)

__align(4)
static u8   gs_au8_QuickTraceBuf[QUICK_TRC_BUF_SIZE];
static volatile u8  *gs_pu8_Fill = (u8*)gs_au8_QuickTraceBuf;

#if 0
Mbox_t	SysMBox[RTK_MAX_SYSTEM_MBOXS] =
{
#ifdef __MSTAR_DUAL_SIM__
	"HWL  "	,   0,
	"SIM  "	,   1,
	"CC1  "	,   2,
	"SS1  "	,   3,
	"SMS1 "	,   4,
	"MM1  "	,   5,
	"RR1  "	,   6,
	"SPV1 "	,   7,
	"DATA "	,   8,
	"IR   "	,   9,
	"CC2  "	,  10,
	"SS2  "	,  11,
	"SMS2 "	,  12,
	"MM2  "	,  13,
	"RR2  "	,  14,
	"SPV2 "	,  15,
	"SM2  "	,  16,
	"SDCP2"	,  17,
	"MDL2 "	,  18,
	"IP1  "	,  19,
	"BAT  "	,  20,
	"LAPD1"	,  21,
	"MSR1 "	,  22,
	"SIMHD"	,  23,
	"OBX  "	,  24,
	"MDL1 "	,  25,
	"SM1  "	,  26,
	"PPS1 "	,  27,
	"SDCP1"	,  28,
	"LLC1 "	,  29,
	"RLD1 "	,  30,
	"RLU1 "	,  31,
	"[   ]"	,  32,
	"V24  "	,  33,
	"HAC  "	,  34,
	"ABB  "	,  35,
	"[   ]"	,  36,
	"[   ]"	,  37,
	"[   ]"	,  38,
	"[   ]"	,  39,
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
	"SIM2 "	,  40,
	"SIM2HD",  41,
#else
	"[   ]"	,  40,
	"[   ]"	,  41,
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
	"PPS2 "	,  42,
	"IP2  "	,  43,
	"CE   "	,  44,
	"MSR2 "	,  45,
	"LLC2 "	,  46,
	"RLD2 "	,  47,
	"RLU2 "	,  48,
	"LAPD2"	,  49,
#else
	"HWL  "	,   0,
	"SIM  "	,   1,
	"CC1  "	,   2,
	"SS1  "	,   3,
	"SMS1 "	,   4,
	"MM1  "	,   5,
	"RR1  "	,   6,
	"SPV1 "	,   7,
	"DATA "	,   8,
	"IR   "	,   9,
	"CC2  "	,  10,
	"SS2  "	,  11,
	"SMS2 "	,  12,
	"MM2  "	,  13,
	"RR2  "	,  14,
	"SPV2 "	,  15,
	"SM2  "	,  16,
	"SDCP2"	,  17,
	"MDL2 "	,  18,
	"IP1  "	,  19,
	"BAT  "	,  20,
	"LAPD1"	,  21,
	"MSR1 "	,  22,
	"SIMHD"	,  23,
	"OBX  "	,  24,
	"MDL1 "	,  25,
	"SM1  "	,  26,
	"PPS1 "	,  27,
	"SDCP1"	,  28,
	"LLC1 "	,  29,
	"RLD1 "	,  30,
	"RLU1 "	,  31,
	"[   ]"	,  32,
	"V24  "	,  33,
	"HAC  "	,  34,
	"ABB  "	,  35,
	"[   ]"	,  36,
	"[   ]"	,  37,
	"[   ]"	,  38,
	"[   ]"	,  39,
#endif
};

Task_t	SysTask[RTK_MAX_SYSTEM_TASKS] =
{
#ifdef __MSTAR_DUAL_SIM__
#ifndef __MSTAR_DUAL_SIM_REDUCE_CODE__
	"IDLE "	,   0,
	"SS   "	,   1,
	"SMS  "	,   2,
	"CC   "	,   3,
	"SIM  "	,   4,
	"MM   "	,   5,
	"RR   "	,   6,
	"DL   "	,   7,
	"MSR  "	,   8,
	"DAT  "	,   9,
	"SPV  "	,  10,
	"HAC  "	,  11,
	"V24  "	,  12,
	"IP   "	,  13,
	"BATT "	,  14,
	"OBX  "	,  15,
	"ABB  "	,  16,
	"MDL  "	,  17,
	"PPS  "	,  18,
	"SM   "	,  19,
	"SDCP1"	,  20,
	"LLC  "	,  21,
	"RLD  "	,  22,
	"RLU  "	,  23,
	"CC2  "	,  24,
	"SS2  "	,  25,
	"SMS2 "	,  26,
	"MM2  "	,  27,
	"RR2  "	,  28,
	"DL2  "	,  29,
	"SPV2 "	,  30,
	"MSR2 "	,  31,
	"SM2  "	,  32,
	"SDCP2"	,  33,
	"LLC2 "	,  34,
	"RLD2 "	,  35,
	"RLU2 "	,  36,
	"MDL2 "	,  37,
	"CE   "	,  38,
	"PPS2 "	,  39,
	"IP2  "	,  40,
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
	"SIM2 "	,  41,
#else
	"[   ]"	,  41,
#endif
	"[   ]"	,  42,
	"[   ]"	,  43,
	"[   ]"	,  44,
	"[   ]"	,  45,
	"[   ]"	,  46,
	"[   ]"	,  47,
	"[   ]"	,  48,
	"[   ]"	,  49,
#else
	"IDLE "	,   0,
	"CE   "	,   1,
	"CC   "	,   2,
	"CC2  "	,   3,
	"SS   "	,   4,
	"SS2  "	,   5,
	"SMS  "	,   6,
	"SMS2 "	,   7,
	"MM   "	,   8,
	"MM2  "	,   9,
	"RR   "	,  10,
	"RR2  "	,  11,
	"DL   "	,  12,
	"DL2  "	,  13,
	"SPV  "	,  14,
	"SPV2 "	,  15,
	"MSR  "	,  16,
	"MSR2 "	,  17,
	"SM   "	,  18,
	"SM2  "	,  19,
	"SDCP1"	,  20,
	"SDCP2"	,  21,
	"LLC  "	,  22,
	"LLC2 "	,  23,
	"RLD2 "	,  24,
	"RLD  "	,  25,
	"RLU  "	,  26,
	"RLU2 "	,  27,
	"MDL  "	,  28,
	"MDL2 "	,  29,
	"SIM  "	,  30,
	"SIM2 "	,  31,
	"PPS  "	,  32,
	"IP   "	,  33,
	"DAT  "	,  34,
	"HAC  "	,  35,
	"V24  "	,  36,
	"BATT "	,  37,
	"OBX  "	,  38,
	"ABB  "	,  39,
	"[   ]"	,  40,
	"[   ]"	,  41,
	"[   ]"	,  42,
	"[   ]"	,  43,
	"[   ]"	,  44,
	"[   ]"	,  45,
	"[   ]"	,  46,
	"[   ]"	,  47,
	"[   ]"	,  48,
	"[   ]"	,  49,
#endif //__MSTAR_DUAL_SIM_REDUCE_CODE__
#else
	"IDLE "	,   0,
	"SS   "	,   1,
	"SMS  "	,   2,
	"CC   "	,   3,
	"SIM  "	,   4,
	"MM   "	,   5,
	"RR   "	,   6,
	"DL   "	,   7,
	"MSR  "	,   8,
	"DAT  "	,   9,
	"SPV  "	,  10,
	"HAC  "	,  11,
	"V24  "	,  12,
	"IP   "	,  13,
	"BATT "	,  14,
	"OBX  "	,  15,
	"ABB  "	,  16,
	"MDL  "	,  17,
	"PPS  "	,  18,
	"SM   "	,  19,
	"SDCP1"	,  20,
	"LLC  "	,  21,
	"RLD  "	,  22,
	"RLU  "	,  23,
	"CC2  "	,  24,
	"SS2  "	,  25,
	"SMS2 "	,  26,
	"MM2  "	,  27,
	"RR2  "	,  28,
	"DL2  "	,  29,
	"SPV2 "	,  30,
	"MSR2 "	,  31,
	"SM2  "	,  32,
	"SDCP2"	,  33,
	"LLC2 "	,  34,
	"RLD2 "	,  35,
	"RLU2 "	,  36,
	"MDL2 "	,  37,
	"CE   "	,  38,
	"PPS2 "	,  39,
#endif // __MSTAR_DUAL_SIM__
};
#endif

Diagnose_t Diagnose[] = {
        {"L3RR", 0},
        {"L3MM", 0},
        {"L3CC", 0},
        {"L3SS", 0},
        {"L3SM", 0},
        {"L3UT", 0},
        {"LAPD", 0},
#ifdef unix
        {"SCEN", 0},
#else
        {"WTCH", 0},
#endif
        {"FLASH", 0},
        {"SIM", 0},
        {"HAP", 0},
        {"MMK", 0},
        {"MMT", 0},
        {"MMI", 0},
        {"ATI", 0},
        {"SPV", 0},
        {"MSR", 0},
        {"DATA", 0},
        {"HAC", 0},
        {"UTC", 0},
        {"SEQ", 0},
        {"L1C", 0},
        {"HWL", 0},
        {"RTK", 0},
        {"CUS1", 0},
        {"CUS2", 0},
        {"CUS3", 0},
        {"CUS4", 0},
        {"CUS5", 0},
        {"CUS6", 0xffff},
        {"SYS", 0},
        {"IP", 0},
        {"L3GMM",  0},
        {"L3SMG",  0},
        {"SNDCP",  0},
        {"LLC",    0},
        {"RLD",    0},
        {"RLU",    0},
        {"GRR",    0},
        {"PPS",    0},
        {"CUS13", 0},
        {"CUS14", 0}
#ifdef __UMTS__
        {"URR1", 0},
        {"URR2", 0},
        {"URL",  0},
        {"UMA",  0},
        {"PDCP", 0},
        {"BMC",  0},
        {"UL1C", 0},
#endif
       ,{"CUS7",  0},
        {"CUS8",  0},
        {"CUS9",  0},
        {"OBX",  0},
        {"DEV",  0},
        {"FCM",    0},
        {"IOB",    0},
        {"MDL",    0},
        {"CUS10", 0},
        {"CUS11", 0},
        {"CUS12", 0},
#ifdef __MSTAR_DUAL_SIM__
        {"SPV2", 0},
        {"L1C2", 0},
        {"MSR2", 0},
        {"L3CC2", 0},
        {"L3SS2", 0},
        {"L3SM2", 0},
        {"MMT2", 0},
        {"ATI2", 0},
        {"MDL2",    0},
        {"L3GMM2", 0},
        {"GRR2", 0},
        {"CE",    0},
        {"L3MM2", 0},
        {"L3RR2", 0},
        {"LAPD2", 0},
        {"L3SMG2",  0},
        {"SNDCP2",  0},
        {"LLC2",    0},
        {"RLD2",    0},
        {"RLU2",    0},
        {"PPS2",    0},
        {"IP2",    0},
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
        {"SIM2",    0},
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#endif
        {"SDK1",    0},
        {"SDK2",    0},
        {"SDK3",    0},
        {"SDK4",    0},
        {"SDK5",    0},
        {"CUS20",    0},//auto test
        {"MIXED1",    0},
        {"MIXED2",    0},
        {"MIXED3",    0},
        {"MIXED4",    0},
        {"MIXED5",    0},
        {"MIXED6",    0},
        {"MIXED7",    0},
        {"MIXED8",    0},
        {"MIXED9",    0},
};

const u32 Diagnose_Size = sizeof(Diagnose)/sizeof(Diagnose[0]);

const char *_empty_ = "";
const char *_dump_  = "%1$d %2$m";
const char *_dump4_ = "%1$d %4$m";

#if __ARMCC_VERSION > 220000
   #define FILL_FROM_VALIST(dst,src,sz)  memcpy(dst,src,sz)
#else /* __ARMCC_VERSION <= 220000 */
   #define FILL_FROM_VALIST(dst,src,sz)  memcpy(dst,(void*)*src,sz)
#endif /* __ARMCC_VERSION */

#ifdef __DBG_SCR__
static u8 trc_dbgScrDestinationMailbox = 0xFF;
#endif //__DBG_SCR__
void INT_TRACE(u32 id, char *fmt, va_list args);
static void KER_CENTRAL_TRACE (u32 id, char *fmt, va_list args);

#ifdef __RM_STORE_EXT_TRACE__
extern void rm_StoreTrcInFlash(void);
#endif //__RM_STORE_EXT_TRACE__
bool DisableErrorTrace = FALSE;

#if defined(__I_SW__) && !defined(__ISW_INFINITY__)
bool rm_DriverInitialized = FALSE;
#else
extern bool rm_DriverInitialized;
#endif
/****************************************************************************/
/*  Function  : dbg_AddField( )                                             */
/*--------------------------------------------------------------------------*/
/*  Scope     : Add field to debug screen                                   */
/*                                                                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  Msg               | X |   |   | Message                                 */
/*  Active            | X |   |   | on screen debug activated?              */
/*  NbField           | X |   |   | Number of fields                        */
/*  ...               | X |   |   | Variable number of arguments            */
/****************************************************************************/

#ifdef __DBG_SCR__
#define FIELD_CLUSTER 64
void __dbg_AddField(mmi_DebugMsg_t **Msg, bool Active, u32 NbField, ...)
{
 u32     i;
	va_list args;
	u16     MaxField;

	/* do it only if on screen debug activated for the requester */
	if (!Active) return;

    if (trc_dbgScrDestinationMailbox == 0xFF)
        return;
	/* no message, so allocate it */
	if (!*Msg)
	{
		/* allocate max N * FIELD_CLUSTER fields */
		MaxField = (NbField & ~(FIELD_CLUSTER-1)) + FIELD_CLUSTER;

		/* allocated debug fields MaxField - 1 because DebugMsg contains 1 field */
		if (!(*Msg = MsGetHeapMemory(sizeof(mmi_DebugMsg_t) + (MaxField - 1) * sizeof(vm_dbgField_t))))
			return;
		(*Msg)->Header.TypMsg = VM_DEBUG_IND;
		(*Msg)->Header.MbxDst = trc_dbgScrDestinationMailbox;
		(*Msg)->Header.Length = sizeof(mmi_DebugMsg_t) + (MaxField - 1) * sizeof(vm_dbgField_t);
		(*Msg)->mmi_DebugInd.NbField = 0;
		(*Msg)->mmi_DebugInd.MaxField = MaxField;
	}
	else if ((*Msg)->mmi_DebugInd.NbField + NbField > (*Msg)->mmi_DebugInd.MaxField)
	{
		mmi_DebugMsg_t *_Msg;

		/* allocate max N * FIELD_CLUSTER fields */
		MaxField = (((*Msg)->mmi_DebugInd.NbField + NbField) & ~(FIELD_CLUSTER-1)) + FIELD_CLUSTER;

		/* re-allocate msg, copy it and release old one */
		if (!(_Msg = MsGetHeapMemory(sizeof(mmi_DebugMsg_t) + (MaxField - 1) * sizeof(vm_dbgField_t))))
			return;

		/* copy old contents and update length in new message */
		memcpy(_Msg, *Msg, sizeof(mmi_DebugMsg_t) + (*Msg)->mmi_DebugInd.NbField * sizeof(vm_dbgField_t));
		_Msg->mmi_DebugInd.MaxField = MaxField;
		_Msg->Header.Length = sizeof(mmi_DebugMsg_t) + (MaxField - 1) * sizeof(vm_dbgField_t);

		MsReleaseMemory(*Msg);

		*Msg = _Msg;
	}
    (*Msg)->Header.MbxDst = trc_dbgScrDestinationMailbox;

	va_start(args, NbField);

	/* enough space in current message, get fields and copy them */
	for (i = 0; i < NbField; i++)
	{
		(*Msg)->mmi_DebugInd.Field[ (*Msg)->mmi_DebugInd.NbField ].Idx = va_arg(args, u32 );
		(*Msg)->mmi_DebugInd.Field[ (*Msg)->mmi_DebugInd.NbField++ ].Val = va_arg(args, u32 );
	}

	va_end(args);
}
#endif //__DBG_SCR__

/**
 * \fn     const s32 trc_dbgScrSubscribe(u8 mailbox);
 * \brief  Used to subscribe to the Debug Screen service. Only one mailbox can receive Debug Screen events.
 * \param [in] mailbox  mailbox that will receive the Debug Screen event
 * \return <0 if error, >=0 otherwise
 */
s32 trc_dbgScrSubscribe(u8 mailbox)
{
#ifdef __DBG_SCR__
    trc_dbgScrDestinationMailbox = mailbox;
#endif //__DBG_SCR__
    return 1;
}

void KER_ERROR_DIAGNOSE_UART(char * strfunc, int line)
{


    UartSendTrace("\n========== %s ========== \n", __FUNCTION__);
    UartSendTrace("Caller Function: %s\n", strfunc);
    UartSendTrace("Line: 0x%08x\n\n", line);

}

/****************************************************************************/
/*  Function  : KER_ERROR_DIAGNOSE ( )                                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Central error management routine                            */
/*                                                                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  Format for error trace                 */
/*  ...               | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

/*Implementation body of KER_ERROR_DIAGNOSE.   */
/*One can has any customization in its wrapper!       */
void KER_ERROR_DIAGNOSE_IMP (u32 id, char *fmt, va_list args)
{
	KER_VERROR_DIAGNOSE(id,fmt,args);
}

void KER_ERROR_DIAGNOSE (u32 id, char *fmt, ...)
{
	va_list args;
	/*lint -e(530) suppress "Symbol 'args' not initialized" */
	va_start(args, fmt);
	KER_ERROR_DIAGNOSE_IMP(id,fmt,args);
	va_end(args);
}

/****************************************************************************/
/*  Function  : BACKTRACE_FATAL ( )                                         */
/*--------------------------------------------------------------------------*/
/*  Scope     : BACKTRACE for FATAL & EXCEPTION                             */
/*                                                                          */
/*  Return    : none                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  l_u32_BackTraceId | x |   |   |                                         */
/*  fmt               | x |   |   |  Format for error trace                 */
/*  va_list           | x |   |   |  Variable number of arguments           */
/****************************************************************************/

void BACKTRACE_FATAL(u32 l_u32_BackTraceId, char * fmt, va_list args)
{
    u8 i = 0;
    sys_BackTraceFormat_t *l_ps_BackTrace;

    /*lint -e522 */
    MsDisableInterrupt();
    /*lint +e522 */
    MsBacktraceEntryCounterAdd();

#ifdef __RM_STORE_EXT_TRACE__
	// write the TMT trace data to flash before enhanced backtrace
    if((l_u32_BackTraceId & FATAL) || (l_u32_BackTraceId & EXCEPTION))
        rm_StoreTrcInFlash();
#endif //__RM_STORE_EXT_TRACE__

    rm_InterfaceStoreMsg(OVERWRITING);

    /* expect watch dog reset */
    sys_set_WDogRstFlag(0x13572468);

    if ((GET_IDENT(l_u32_BackTraceId) == _CUS1)
        || (GET_IDENT(l_u32_BackTraceId) == _CUS2)
        || (GET_IDENT(l_u32_BackTraceId) == _CUS3)
        || (GET_IDENT(l_u32_BackTraceId) == _CUS4)
        || (GET_IDENT(l_u32_BackTraceId) == _CUS5)
        || (GET_IDENT(l_u32_BackTraceId) == _CUS6))
        sys_CustomerWDogRst=TRUE; /* open mmi */

    sys_DelayWatchDogReset();

    /* print RTK memory status */
    MsDumpMemoryStatus();

    /* do a backtrace */
    if (!(l_u32_BackTraceId & NO_STACK ))
#if 0
        l_ps_BackTrace = MsGetHeapMemory((GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + BACKTRACE_SIZE));
#else
        l_ps_BackTrace = MsGetHeapMemory((GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + BACKTRACE_SIZE + MAX_TIME_INFO_BUF_SIZE + 4));
#endif
    else
        l_ps_BackTrace = MsGetHeapMemory((GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + 4));

    if(l_ps_BackTrace == NULL)
    {
        _TRACE((_SYS,"Not Enough Heap to create the Backtrace Buffer to store"));
    }
    else
    {
        u32 *l_pu32_ParamBuffer;
        l_ps_BackTrace->Type = l_u32_BackTraceId;
        l_ps_BackTrace->MsgPtr = fmt;

        l_pu32_ParamBuffer = (u32 *)l_ps_BackTrace->Data;

        for(i=0;i < (u8) (GET_PARAMETER(l_u32_BackTraceId)); i++)
        {
        	l_pu32_ParamBuffer[i] = va_arg(args,u32);
        }
        if(l_u32_BackTraceId & FATAL)
        {
        	if(!(l_u32_BackTraceId & NO_STACK))
        	    sys_BackTrace(SYS_RUN_TIME_ERROR,l_ps_BackTrace);
        	else
        	    sys_BackTrace(SYS_RUN_TIME_ERROR | NO_DUMP,l_ps_BackTrace);
        }

        if(l_u32_BackTraceId & EXCEPTION)
            sys_BackTrace(SYS_EXCEPTION_OCCURED,l_ps_BackTrace);

        MsReleaseHeapMemory(l_ps_BackTrace);
    }

    /* and then call user's fatal handler */
    trc_CustomErrorProcDiag( l_u32_BackTraceId );
}


/****************************************************************************/
/*  Function  : BACKTRACE_STORE ( )                                         */
/*--------------------------------------------------------------------------*/
/*  Scope     : BACKTRACE for STORE                                         */
/*                                                                          */
/*  Return    : none                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  l_u32_BackTraceId | x |   |   |                                         */
/*  fmt               | x |   |   |  Format for error trace                 */
/*  va_list           | x |   |   |  Variable number of arguments           */
/****************************************************************************/

void BACKTRACE_STORE(u32 l_u32_BackTraceId, char * fmt, va_list args)
{
	u8 i = 0;
	sys_BackTraceFormat_t *l_ps_BackTrace;

	if(!(l_u32_BackTraceId & NO_STACK))
#if 0
		l_ps_BackTrace = MsGetHeapMemory(GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + BACKTRACE_SIZE);
#else
		l_ps_BackTrace = MsGetHeapMemory(GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + BACKTRACE_SIZE + MAX_TIME_INFO_BUF_SIZE + 4);
#endif
	else
		l_ps_BackTrace = MsGetHeapMemory(GET_PARAMETER(l_u32_BackTraceId) * 4 + sizeof(sys_BackTraceFormat_t) + 4);

	if(l_ps_BackTrace == NULL)
	{
		_TRACE((_SYS,"Not Enough Heap to create the Backtrace Buffer to store"));
	}
	else
	{
		u32 *l_pu32_ParamBuffer;
		l_ps_BackTrace->Type = l_u32_BackTraceId;
		l_ps_BackTrace->MsgPtr = fmt;

		l_pu32_ParamBuffer = (u32 *)l_ps_BackTrace->Data;
		for(i=0;i < (u8) (GET_PARAMETER(l_u32_BackTraceId)); i++)
		{
			l_pu32_ParamBuffer[i] = va_arg(args,u32);
		}

		if(!(l_u32_BackTraceId & NO_STACK))
			sys_BackTrace (SYS_RUN_TIME_ERROR,l_ps_BackTrace);
		else
			sys_BackTrace(SYS_RUN_TIME_ERROR | NO_DUMP,l_ps_BackTrace);

		MsReleaseHeapMemory(l_ps_BackTrace);
	}
}

/****************************************************************************/
/*  Function  : BACKTRACE_WATCHDOG ( )                                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : BACKTRACE for WATCHDOG                                      */
/*                                                                          */
/*  Return    : none                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  l_u32_BackTraceId | x |   |   |                                         */
/*  fmt               | x |   |   |  Format for error trace                 */
/*  va_list           | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void BACKTRACE_WATCHDOG(u32 l_u32_BackTraceId, char * fmt, va_list args)
{
	u8 i = 0;
	sys_BackTraceFormat_t *l_ps_BackTrace;
	u32 *l_pu32_ParamBuffer;

	l_ps_BackTrace = MsGetHeapMemory(GET_PARAMETER(l_u32_BackTraceId) *4 + sizeof(sys_BackTraceFormat_t) + BACKTRACE_SIZE);
	if(l_ps_BackTrace == NULL)
	{
		_TRACE((_SYS,"Not Enough Heap to create the Backtrace Buffer to store"));
		return;
	}
	l_ps_BackTrace->Type = l_u32_BackTraceId;
	l_ps_BackTrace->MsgPtr = fmt;

	l_pu32_ParamBuffer = (u32 *)l_ps_BackTrace->Data;
	for(i=0;i < (u8) (GET_PARAMETER(l_u32_BackTraceId)); i++)
	{
		l_pu32_ParamBuffer[i] = va_arg(args,u32);
	}
	sys_BackTrace (SYS_WATCH_DOG_EXTRACT,l_ps_BackTrace);
	MsReleaseHeapMemory(l_ps_BackTrace);
}

/****************************************************************************/
/*  Function  : INT_DUMP ( )                                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : DUMP message                                                */
/*                                                                          */
/*  Return    : none                                                        */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  type              | x |   |   |  dump(0) & dump4(4)                     */
/*  va_list           | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void INT_DUMP(u32 id, u32 type, va_list args)
{
	char *	buf;
	u16 	len;
	u8   	id3=0;
	u8   	chan = 0;
	u16  	ldump;
	u16* 	pdump;

	if( type == 0 )
	{
		ldump = va_arg(args, int);
		pdump = va_arg(args, u16 *);
	}
	else // if( type == 4 )
	{
		ldump = va_arg(args, int) + 2; // +2 for id3 & chan
		pdump = va_arg(args, u16 *);
		id3   = va_arg(args, int);
		chan  = va_arg(args, int);
	}
       if (ldump > (RM_TX_BUFFER_LENGTH/2))
       {
#if !defined(__BYPASS_CALLGRAPH__)
            _ERROR((_SYS, "INT_DUMP: DUMP too big, size = %d", ldump));
#endif
            return;
       }

	buf = (char *)(* rm_UserSend)(0, INFO_DUMP, 2 + ldump, 0); // +2 for trace id & level

	if( ! buf )
		return;

	/* copy the requester, the format string then copy the stack and */
	/* send it to PC */
	*buf = (u8) GET_IDENT(id);
	*(buf+1) = (u8) GET_LEVEL(id);

	//
	len = 2;

	if( id3 )
		buf[len++] = (u8) id3;

	if( chan )
		buf[len++] = (u8) chan;

	memcpy(buf + len, (char *) pdump, ldump - ((id3 ? 1 : 0) + (chan ? 1 : 0)));
}

/****************************************************************************/
/*  Function  : INT_TRACE( )                                           */
/*--------------------------------------------------------------------------*/
/*  Scope     : INTERNAL TRACE sub-routine                                  */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  Format for trace                       */
/*  va_list           | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void INT_TRACE(u32 id, char *fmt, va_list args)
{
	u8    StackSize;
	u16   ReqId;
	u32   RemoteTraceId;
	u8    *p;
	u16   len;

	// compute stack size & trace identifier to use.
	StackSize = GET_SIZE(id);
	ReqId = GET_IDENT(id);
	// reset RemoteTraceId
	RemoteTraceId = 0;


	/* reserve memory for trace */
	if (RM_STRING_FLAG_IS_TRUE(fmt))
	{
		len = 3;
		RemoteTraceId = ((u32) fmt) & ~RM_STRING_FLAG;
		fmt = "";
	}
	else
	{
		len = strlen("S: ") + strlen(fmt);
	}

	/* if StackSize is 0, means the pre-process on trace has not been done */
	/* so send 6 parameters by default.                                      */
	if (StackSize == 0)
		StackSize = 6*4;
	else
		StackSize = (StackSize - 1) << 2;

	p = (u8 *) (*rm_UserSend)(NULL, INFO_TRACE, 2 + len + 1 + StackSize + 2, 0);

	if (!p)
		return;

	/* set requester id */
	*p = (u8) ReqId;
	*(p+1) = (u8) (GET_LEVEL(id));

	/* copy format and dump if any */
	if (RemoteTraceId)
	{
		*(p+1) |= RM_FLAG >> 8; /* remote trace flag */
		memcpy(p+2, (void*) &RemoteTraceId, 4);
	}
	else
	{
		strcpy((char*)p + 2, "S: ");
		strcpy((char*)p + 2 + strlen("S: "), fmt);
	}

	len += 2 + 1;

	/* then copy the stack and send it to PC */
#if __ARMCC_VERSION > 220000
#ifdef __APCS_ADSABI
	memcpy(p+len, (u8*) *args, StackSize);
#else /* !__APCS_ADSABI */
	memcpy(p+len, (u8*) args.__ap, StackSize);
#endif /* __APCS_ADSABI */
#elif defined(__GNUC__)
#if defined(__arm)
    memcpy(p+len, (u8*) args.__ap, StackSize);
#else
	memcpy(p+len, args, StackSize);
#endif
#else /* __ARMCC_VERSION <= 220000 */
	memcpy(p+len, (u8*) *args, StackSize);
#endif /* __ARMCC_VERSION */
}

/****************************************************************************/
/*  Function  : KER_VERROR_DIAGNOSE ( )                                      */
/*--------------------------------------------------------------------------*/
/*  Scope     : Central error management routine                            */
/*                                                                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  Format for error trace                 */
/*  va_list           | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

void KER_VERROR_DIAGNOSE (u32 id, char *fmt, va_list args)
{
	if(TRUE == DisableErrorTrace && !(id & WARNING) && !(id & FATAL))
		return;

	if ((id & WARNING) == WARNING)
		id = (SysGetMPFlag()) ? id&(~WARNING) : (id&(~WARNING))|FATAL;

#ifndef __RTK_DIAGNOSE_ENHANCE__
	if ((id & FATAL) == FATAL)
	{
		static bool ls_b_fatal_error_reentrance = FALSE;
		MsEnterRegionInt();
		if (ls_b_fatal_error_reentrance)
		{
			/*
			* Let the processor die in a watch dog error
			* in order to prevent a fatal error to
			* trigger another one.
			* Such nested fatal errors will be noticeable at the next
			* start-up thanks to the watchdog reset backtrace.
			*/
			sys_DieByWatchDog();
		}
		else
			ls_b_fatal_error_reentrance = TRUE;
	}
#endif

	if( fmt == _dump_ )
	{
		INT_DUMP(id, 0, args);
	}
	else if( fmt == _dump4_ )
	{
		INT_DUMP(id, 4, args);
	}
	else
	{
#if !defined(__BYPASS_CALLGRAPH__)
		u8 	StackSize = GET_SIZE(id);
		u32	l_u32_BackTraceId = id;
#endif

		INT_TRACE(id, fmt, args);

#if !defined(__BYPASS_CALLGRAPH__)

		/* if StackSize is 0, means the pre-process on trace has not been done */
		/* Set number of args for backtrace(6 + string of the trace = 7) */
		if (StackSize == 0)
			l_u32_BackTraceId = PUTMSK(id, 7, 27);
		//sys_DelayWatchDogReset();


		if (l_u32_BackTraceId & CLEAR)
		{
			static u8 prevent_recursion_clear = 0; //prevent recursion

			prevent_recursion_clear = 1;
			if(0 == prevent_recursion_clear)
				sys_InitE2pErrorStack();
			prevent_recursion_clear = 0;
		}

		/* and stops it error is fatal */
		if ((l_u32_BackTraceId & FATAL)|| (l_u32_BackTraceId & EXCEPTION))
		{
#ifdef __RTK_DIAGNOSE_ENHANCE__
			_RtkAssertRoutine(l_u32_BackTraceId & 0xF80000FF, (u32)fmt, args);
#else
			BACKTRACE_FATAL(l_u32_BackTraceId, fmt, args);
#endif
		}

		if(!SysGetMPFlag())
		{
			static u8 prevent_recursion = 0; //prevent recursion

			// Skip if uninitialized, or later memory allocate will assert
			if(rm_DriverInitialized == FALSE)
				return;

			if(!prevent_recursion)
			{
				prevent_recursion = 1;

				if ((l_u32_BackTraceId & STORE))
					BACKTRACE_STORE(l_u32_BackTraceId, fmt, args);

				if ((l_u32_BackTraceId & WATCHDOG))
					BACKTRACE_WATCHDOG(l_u32_BackTraceId, fmt, args);

				prevent_recursion = 0;
			}
		}
#endif
	}
}


/****************************************************************************/
/*  Function  : KER_ERROR_NO_DIAGNOSE( )                                    */
/*--------------------------------------------------------------------------*/
/*  Scope     : Central error management routine                            */
/*                                                                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  none                                   */
/****************************************************************************/
void KER_ERROR_NO_DIAGNOSE (u32 id, u32 variadic)
{
	if ((id & WARNING) == WARNING)
		id = (SysGetMPFlag()) ? id&(~WARNING) : (id&(~WARNING))|FATAL;

	if (id & FATAL)
	{
		/* expect watch dog reset */
		sys_set_WDogRstFlag(0x13572468);

		if ((GET_IDENT(id) == _CUS1)
			|| (GET_IDENT(id) == _CUS2)
			|| (GET_IDENT(id) == _CUS3)
			|| (GET_IDENT(id) == _CUS4)
			|| (GET_IDENT(id) == _CUS5)
			|| (GET_IDENT(id) == _CUS6))
				sys_CustomerWDogRst=TRUE; /* open mmi */

		trc_CustomErrorProcNoDiag( id );
	}
}

/****************************************************************************/
/*  Function  : trc_PurgeQuickTrcBuf                                        */
/*--------------------------------------------------------------------------*/
/*  Scope     : Purge the quick trace buffer                                */
/*              Call in idle task                                           */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*                    |   |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void trc_PurgeQuickTrcBuf(void)
{
  u32       id;
  char     *fmt;
  u32      *l_pu32_Purge = (u32 *)gs_au8_QuickTraceBuf;
#if (__ARMCC_VERSION > 220000) && !defined(__APCS_ADSABI)
  va_list   l_pu32_Args;
#else
#if defined(__GNUC__)
  va_list   l_pu32_Args;
#else
  u8*   l_pu32_Args;
#endif
#endif

  // Max QUICK_TRC_BUF_SIZE/32 traces can be stored
  // Treat the quick trace buffer
  while ((gs_pu8_Fill < (&gs_au8_QuickTraceBuf[QUICK_TRC_BUF_SIZE]-(MAX_NUMBER_TRC_ARGS+2)*4))
      && ((u8 *)l_pu32_Purge < gs_pu8_Fill))
  {
    id = *l_pu32_Purge;
    fmt = (char*)(l_pu32_Purge[1]);
    // va_list is a pointer on a structure
#if (__ARMCC_VERSION > 220000) && !defined(__APCS_ADSABI)
    l_pu32_Args.__ap = l_pu32_Purge + 2;
#else
#if defined(__GNUC__)
    l_pu32_Args.__ap = l_pu32_Purge + 2;
#else
    l_pu32_Args = (u8*)(l_pu32_Purge + 2);
#endif
#endif
    KER_CENTRAL_TRACE(id,fmt,l_pu32_Args);
    l_pu32_Purge += MAX_NUMBER_TRC_ARGS + 2;
  }
  // Init Fill pointer
  gs_pu8_Fill = (u8 *)&gs_au8_QuickTraceBuf[0];
}

/****************************************************************************/
/*  Function  : trc_QuickTrace                                              */
/*--------------------------------------------------------------------------*/
/*  Scope     : Store trace arguments in a buffer                           */
/*              The arguments will be treated in idle task                  */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  Format for trace                       */
/*  args              | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
static void trc_QuickTrace(u32 id, char *fmt, va_list args)
{
        MsIntMask_e Mask;

        if(MsBacktraceEntryCounterCheck())
            return; //forbidden under exception

        Mask = MsDisableInterrupt();

        // QUICK_TRC_BUF_SIZE/32 traces can be stored
        if (gs_pu8_Fill < ((u8 *)&gs_au8_QuickTraceBuf[QUICK_TRC_BUF_SIZE]-(MAX_NUMBER_TRC_ARGS+2)*4))
        {
            * (u32 *)gs_pu8_Fill = id;
            * (u32 *)(gs_pu8_Fill+4) = (u32) fmt;

#if __ARMCC_VERSION > 220000
#ifdef __APCS_ADSABI
            FILL_FROM_VALIST(gs_pu8_Fill+2*4, args, MAX_NUMBER_TRC_ARGS*4);
#else /* !__APCS_ADSABI */
            FILL_FROM_VALIST((u8*)gs_pu8_Fill+2*4, args.__ap, MAX_NUMBER_TRC_ARGS*4);
#endif /* __APCS_ADSABI */
#elif defined(__GNUC__)
#if defined(__arm)
            memcpy((u8*)gs_pu8_Fill+2*4, args.__ap,  MAX_NUMBER_TRC_ARGS*4);
#else
            memcpy((u8*)gs_pu8_Fill+2*4, args,  MAX_NUMBER_TRC_ARGS*4);
#endif
#else /* __ARMCC_VERSION <= 220000 */
            FILL_FROM_VALIST(gs_pu8_Fill+2*4, args, MAX_NUMBER_TRC_ARGS*4);
#endif /* __ARMCC_VERSION */

            gs_pu8_Fill += (MAX_NUMBER_TRC_ARGS + 2)*4;
            MsEnableInterrupt(Mask);
        }
        else
        {
            MsEnableInterrupt(Mask);
            _ERROR((_SYS | LEVEL_0,"trc_QuickTrace: Quick Trace Buffer Overflow, be careful of trace order"));
            // Do not loose data even if buffer full
            KER_CENTRAL_TRACE(id,fmt,args);
        }
}

#ifdef __DIAGNOSE__

static bool KER_TRACE_AVAILABE_CHECK(u32 id)
{

	if( (TRUE == DisableErrorTrace && !(id & WARNING) && !(id & FATAL))
		|| (rm_DriverInitialized == FALSE) // Skip if uninitialized, or later memory allocate will assert
		|| (GET_IDENT(id) > GLOBAL_LAST_SUBPROCESS)
		|| (0 == Trc_isLevelActive(GET_IDENT(id),id)) )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
/****************************************************************************/
/*  Function  : KER_CENTRAL_TRACE( )                                                */
/*--------------------------------------------------------------------------*/
/*  Scope     : Central trace management routine                            */
/*                                                                          */
/*                                                                          */
/*  Return    : none                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  id                | x |   |   |  Source ID for the request              */
/*  fmt               | x |   |   |  Format for trace                       */
/*  va_list           | x |   |   |  Variable number of arguments           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
//this API should be called only by KER_TRACE_IMP/trc_QuickTrace/trc_PurgeQuickTrcBuf
// in order to detect calling trc_QuickTrace or KER_CENTRAL_TRACE
static void KER_CENTRAL_TRACE (u32 id, char *fmt, va_list args)
{
	if (TRUE == KER_TRACE_AVAILABE_CHECK(id))
	{
		if( fmt == _dump_ )
		{
			INT_DUMP(id, 0, args);
		}
		else if( fmt == _dump4_ )
		{
			INT_DUMP(id, 4, args);
		}
		else
		{
			INT_TRACE(id, fmt, args);
		}
	}
}

/*Implementation body of KER_TRACE.              */
/*One can has any customization in its wrapper! */
void KER_TRACE_IMP (u32 id, char *fmt, va_list args)
{
	if (TRUE == KER_TRACE_AVAILABE_CHECK(id))
	{
		if( ((Rtk_RegionCount == 0)&&(gs_pu8_Fill == (u8 *)&gs_au8_QuickTraceBuf[0]))
			|| (RM_STRING_FLAG_IS_FALSE(fmt)) // string pointer can NOT call trc_QuickTrace
			|| (fmt == _dump_)
			|| (fmt == _dump4_) )
		{
			KER_CENTRAL_TRACE(id,fmt,args);
		}
		else
		{
			trc_QuickTrace(id,fmt,args);
		}
	}
}

void KER_TRACE (u32 id, char *fmt, ...)
{
	va_list args;
	/*lint -e(530) suppress "Symbol 'args' not initialized" */
	va_start(args, fmt);
	KER_TRACE_IMP(id,fmt,args);
	va_end(args);
}

void KER_VTRACE (u32 id, char *fmt, va_list args)
{
	KER_TRACE_IMP(id, fmt, args);
}
#endif /* __DIAGNOSE__ */

/**
  *
  * \fn		const s32 trc_setDiagnoseName(u32 i_u32_ID, char *newName);
  * \brief	Used to change the name of a Diagnose Item
  * \param	[in]i_u32_ID: Trace id (1st argument to vm_dbgTrace()
  * \param	[in]newName:  New name for the Diagnose element (in ASCII) (<VM_DBG_NB_MAX_CHAR_DIAGNOSE_NAME)
  * \return	  <0 if error, >=0 otherwise
  *
  */
s32 trc_setDiagnoseName(u32 i_u32_ID, char *newName)
{
    u32 l_u32_ReqId = GET_IDENT(i_u32_ID);

    if (strlen(newName) >= VM_DBG_NB_MAX_CHAR_DIAGNOSE_NAME)
        return -1;
    memcpy(Diagnose[l_u32_ReqId].Name, newName, (strlen(newName)+1));
    return 1;
}

/**
  *
  * \fn		const s32 trc_getDiagnoseName(u32 i_u32_ID, char presentName);
  * \brief	Used to get the present name of a Diagnose Item
  * \param	[in]i_u32_ID: Trace id (1st argument to vm_dbgTrace()
  * \param	[in]name:  name of the given Diagnose element (in ASCII)
  * \return	  <0 if error, >=0 otherwise
  *
  */
s32 trc_getDiagnoseName(u32 i_u32_ID, char *presentName)
{
    u32 l_u32_ReqId = GET_IDENT(i_u32_ID);

    memcpy(presentName, Diagnose[l_u32_ReqId].Name, VM_DBG_NB_MAX_CHAR_DIAGNOSE_NAME);
    return 1;
}

/**
 * \fn const s32 trc_StartFlipFlapTraceBuffering(u8 mailbox);
 * \brief This function starts the Flip/Flap trace buffer usage
 * \param [in] mailbox: client mailbox that will receive Trace Buffer events
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_StartFlipFlapTraceBuffering(u8 mailbox)
{
    // if we are in NOOVERWRITING mode, it means that we are connected to TMT, so it's useless to call
    // this function
   /* if (rm_GetInterfaceStoreMsg() == NOOVERWRITING)
        return -1;*/

#ifdef __TMT_TRACE_STORE_SD__
    // move to NOOVERWRITING mode, because it's simplier in Flip/Flap mode

    //
     //rm_DisableStoreMsg();
    if (rm_ActivateFlipFlap(mailbox))
    {
    return 1;
    }
    //rm_InterfaceStoreMsg(NOOVERWRITING);
    return 0;
#else // __TMT_TRACE_STORE_SD__
    return -2;
#endif // __TMT_TRACE_STORE_SD__
}
/**
 * \fn const s32 trc_StopFlipFlapTraceBuffering(bool saveTrc);
 * \brief This function stop the Flip/Flap trace buffer usage
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_StopFlipFlapTraceBuffering(bool saveTrc)
{
   #ifdef __TMT_TRACE_STORE_SD__
    rm_DeactivateFlipFlap(saveTrc);
    if (saveTrc == FALSE)
    {
    rm_DisableStoreMsg();
    }
   #endif
    return 0;
}
/**
 * \fn const s32 trc_AckFlipFlapBuffer(vm_dbgTrcBuffer_t *used_buffer);
 * \brief This function acknoledge the given buffer, informaing that it has been
 *        taken into account and can be used by the DBG service.
 * \param [in] used_buffer: pointer on the buffer that is free to be used again
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_AckFlipFlapBuffer(vm_dbgTrcBuffer_t *used_buffer)
{
#ifdef __TMT_TRACE_STORE_SD__
    // mark the buffer as free in RM
    rm_AckFlipFlapBuffer(used_buffer);
    return 1;
#else // __TMT_TRACE_STORE_SD__
    return -2;
#endif // __TMT_TRACE_STORE_SD__
}
/**
 * \fn const s32 trc_StartCircularTraceBuffering(u8 mailbox);
 * \brief This function starts the Flip/Flap trace buffer usage
 * \param [in] mailbox: client mailbox that will receive Trace Buffer events
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_StartCircularTraceBuffering(u8 mailbox, bool isAudioDump)
{
    // if we are in NOOVERWRITING mode, it means that we are connected to TMT, so it's useless to call
    // this function
    /*
    if (rm_GetInterfaceStoreMsg() == NOOVERWRITING)
        return -1;
     */
#ifdef __TMT_TRACE_STORE_SD__
    // move to NOOVERWRITING mode, because it's simplier in Flip/Flap mode
    //rm_DisableStoreMsg();

    if (rm_ActivateCircular(mailbox, isAudioDump))
    {
       return 1;
    }

    // rm_InterfaceStoreMsg(OVERWRITING);

    return 0;
#else // __TMT_TRACE_STORE_SD__
    return -2;
#endif // __TMT_TRACE_STORE_SD__
}
/**
 * \fn const s32 trc_StopCircularTraceBuffering(void);
 * \brief This function stop the Flip/Flap trace buffer usage
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_StopCircularTraceBuffering(bool saveTrc)
{
   #ifdef __TMT_TRACE_STORE_SD__
    rm_DeactivateCircular(saveTrc);
   if (saveTrc == FALSE)
   {
      rm_DisableStoreMsg();
   }
   #endif
    return 0;
}
/**
 * \fn const s32 trc_AckCircularBuffer(vm_dbgTrcBuffer_t *used_buffer);
 * \brief This function acknoledge the given buffer, informaing that it has been
 *        taken into account and can be used by the DBG service.
 * \param [in] used_buffer: pointer on the buffer that is free to be used again
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_AckCircularBuffer(vm_dbgTrcBuffer_t *used_buffer)
{
#ifdef __TMT_TRACE_STORE_SD__
    // mark the buffer as free in RM
    rm_AckCircularBuffer(used_buffer);
    return 1;
#else // __TMT_TRACE_STORE_SD__
    return -2;
#endif // __TMT_TRACE_STORE_SD__
}

/**
 * \fn const s32 trc_SetProfileIndicator(void);
 * \brief This function stop the Flip/Flap trace buffer usage
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_SetProfileIndicator(u8 indicator)
{
   #ifdef __TMT_TRACE_STORE_SD__
     rm_SetGroupIndicator(indicator);
   #endif
    return 0;
}
/**
 * \fn const s32 trc_QueryIsActive(void);
 * \brief This function stop the Flip/Flap trace buffer usage
 * \return <0 if error,  >=0 otherwise
 */
bool trc_QueryIsActive(void)
{
   #ifdef __TMT_TRACE_STORE_SD__
    return rm_QueryIsActive();
   #else
    return TRUE;
   #endif
}


void trc_SaveTraceToSD(void)
{
   #ifdef __TMT_TRACE_STORE_SD__
   rm_SaveTraceToSD();
   #endif
}

//SIM debugging
#define MAX_DIAG_NUMBER (GSM_LAST_SUBPROCESS + GPRS_LAST_SUBPROCESS + EXTENDED2_LAST_SUBPROCESS + DUAL_SIM_EXTENDED_LAST_SUBPROCESS + DUAL_SIM_EXTENDED2_LAST_SUBPROCESS)
void trc_SetLevelForSIM(void)
{
    u16 i;
    for(i=0; i<MAX_DIAG_NUMBER; i++)
    {
        if(strcmp(Diagnose[i].Name,"SIM")==0)
        {
            Diagnose[i].Level |= 0xff000212; //1,4,9,24~31
            break;
        }
    }
}
void trc_SetLevelForSIM2(void)
{
    u16 i;
    for(i=0; i<MAX_DIAG_NUMBER; i++)
    {
        if(strcmp(Diagnose[i].Name,"SIM2")==0)
        {
            Diagnose[i].Level |= 0xff000212; //1,4,9,24~31
            break;
        }
    }
}

#if defined (__UPGRADE_HSL_OVER_SHMCONN__)||defined(__UPGRADE_GENIE_OVER_SHMCONN__)||defined(__UPGRADE_RAMLOG_OVER_SHMCONN__)
/**
 * \fn const s32 trc_AckCircularBuffer(vm_dbgTrcBuffer_t *used_buffer);
 * \brief This function acknoledge the given buffer, informaing that it has been
 *        taken into account and can be used by the DBG service.
 * \param [in] used_buffer: pointer on the buffer that is free to be used again
 * \return <0 if error,  >=0 otherwise
 */
s32 trc_AckModemLog(u32 trace_type)
{
#ifdef __TMT_TRACE_STORE_SD__
    // mark the buffer as free in RM
    rm_AckModemLog(trace_type);
    return 1;
#else // __TMT_TRACE_STORE_SD__
    return -2;
#endif // __TMT_TRACE_STORE_SD__
}
#endif

