//------------------------------------------------------------------------------
//
//  File        : NR_cfg.c
//  Description : Source file of NR configuration
//  Author      : Pohan Chen
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
//#include "UartShell.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
    
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : NR_dbg_printf
//  Description : This function is used for NR library internal logging
//------------------------------------------------------------------------------
/**
 * @brief This function is called by NR library only for showing log
 */
void NR_dbg_printf(char *str, ...)
{
    /*printf take up Task stack 
      if declared char array is too large, it may cause memory override*/
    #if 0
    va_list arg_list;
	char  szOutput[50];// Output buffer to UART 

	va_start(arg_list, str);
	vsnprintf(szOutput, 50-1, str, arg_list);
    va_end(arg_list);
    RTNA_DBG_Str0(szOutput);
    #endif

}
