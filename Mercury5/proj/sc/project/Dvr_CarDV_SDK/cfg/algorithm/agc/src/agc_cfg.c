//------------------------------------------------------------------------------
//
//  File        : agc.c
//  Description : Source file of AGC configuration
//  Author      : Pohan Chen
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
#include <stdio.h>
#include <stdarg.h>
#include "agc_cfg.h"
#include "lib_retina.h"
//#include "UartShell.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

short  gsAGCMaxGain     = DEFAULT_AGC_MAX_GAIN;
short  gsAGCMinGain     = DEFAULT_AGC_MIN_GAIN;
short  gsAGCTargetLevel = DEFAULT_TARGET_LEVEL;
short  gsAGCHoldTime    = DEFAULT_HOLD_TIME;
short  gsAGCBlockSize   = DEFAULT_AGC_BlockSize;

short  gsAGCDurationMs  = DEFAULT_AGCDurationMs;
short  gsAGCSatDropGain = DEFAULT_AGCSatDropGain;

void AGC_dbg_printf(char *str, ...)
{
    /*printf take up Task stack 
      if declared char array is too large, it may cause memory override*/
    #if 1
    va_list arg_list;
	char  szOutput[50];// Output buffer to UART 

	va_start(arg_list, str);
	vsnprintf(szOutput, 50-1, str, arg_list);
    va_end(arg_list);
    RTNA_DBG_Str0(szOutput);
    #endif

}