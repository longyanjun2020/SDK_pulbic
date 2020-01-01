//==============================================================================
//
//  File        : statenetstreamingfunc.h
//  Description : INCLUDE File for the StateNetStreamingFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATE_NET_STREAMING_FUNC_H_
#define _STATE_NET_STREAMING_FUNC_H_

#if (defined(WIFI_PORT) && WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void STATE_NET_STREAMING_WIRELESS_SET_STREAMING_MODE(UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL StateNetStreamingModeInit(void* pData);
AHC_BOOL StateNetStreamingModeShutDown(void* pData);
UINT32 StateNetStreamingModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL StateSelectFuncNetStreamingMode(void);
#endif //#if (defined(WIFI_PORT) && WIFI_PORT == 1)
#endif //_STATE_NET_STREAMING_FUNC_H_

