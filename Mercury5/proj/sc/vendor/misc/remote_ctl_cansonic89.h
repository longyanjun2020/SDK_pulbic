//------------------------------------------------------------------------------
//
//  File        : fdtc_ctl.h
//  Description : face detection and smile detecton
//  Author      : ChenChu Hsu
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _remote_ctl_cansonic89_H_
#define _remote_ctl_cansonic89_H_

#include "includes_fw.h"
#include "mmpf_typedef.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "mmpf_system.h"
#include "dsc_Key.h"
#include "remote_ctl.h"
#include "lib_retina.h"

typedef struct _RMT_CTL_TIME
{
    MMP_ULONG	ulPreemptiveSig;	///< SigTime = SignalTime (us)
    MMP_ULONG	ulLogical0Sig;		///< (us)
    MMP_ULONG	ulLogical1Sig;		///< (us)
	MMP_ULONG	ulRepeatedSig;		///< (us)
	MMP_ULONG	ulSigTolerance;		///< (us)
	
    MMP_ULONG	ulRepeatedInterval;	///< (us)
	MMP_ULONG	ulRepeatedIntervalTolerance;///< (us)
	
} RMT_CTL_TIME;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
typedef void RmtCtlCallBackFunc(MMP_ULONG);
void RMT_CTL_Initalize_89(MMP_GPIO_PIN piopin, MMPF_TIMER_ID timerID, RmtCtlCallBackFunc* callBackFunc);
void RMT_CTL_InitailizeInterval_89(RMT_CTL_TIME *timeInterval);
#endif