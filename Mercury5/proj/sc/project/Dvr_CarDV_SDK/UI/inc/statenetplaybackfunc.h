//==============================================================================
//
//  File        : statenetplaybackfunc.h
//  Description : INCLUDE File for the StateNetPlaybackFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATENETPLAYBACKUNC_H_
#define _STATENETPLAYBACKUNC_H_

#if (defined(WIFI_PORT) && WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/ 

//#include "ahc_general.h"

#if 0 //these are now used in State*.c only
//void STATE_NET_PLAYBACK_DROP_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_DROP_EVENT);
//void STATE_NET_PLAYBACK_ENTER_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_ENTER_EVENT);
//void STATE_NET_PLAYBACK_EXIT_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_EXIT_EVENT);
//void STATE_NET_PLAYBACK_DISCONNECT_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_DISCONNECT_EVENT);
//void STATE_NET_PLAYBACK_SD_REMOVE_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_SD_REMOVE_EVENT);
//void STATE_NET_PLAYBACK_SD_DETECT_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_SD_DETECT_EVENT);
//void STATE_NET_PLAYBACK_USB_REMOVE_EVENT(UINT32 ulEvent, UINT32 ulParam);
DELC_AHC_EV_HANDLER(STATE_NET_PLAYBACK_USB_REMOVE_EVENT);
//void StateNetPlaybackMode(UINT32 ulEvent);
AHC_BOOL StateNetPlaybackFuncInit(void* pData);
AHC_BOOL StateNetPlaybackFuncShutDown(void* pData);
UINT32 StateNetPlaybackModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
#endif

#endif //#if (defined(WIFI_PORT) && WIFI_PORT == 1)
AHC_BOOL StateSelectFuncNetPlaybackMode(void);
#endif
