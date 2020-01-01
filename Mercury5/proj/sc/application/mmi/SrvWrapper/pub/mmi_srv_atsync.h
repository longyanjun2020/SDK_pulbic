/**
* @file    mmi_srv_atsync.h
* @brief  This service provides PC tool(msync tool) to synchronizes data and information with mobile phone,  
*            its sync functionality as follows,
*            1. sync phone book
*            2. sync sms
*            3. sync calendar
*            4. sync todo list
*            But mobile AP just only use the Start or Stop API and set callback for start and stop.
*            After mobile AP call the Start() and SrvAtSyncStartStatusCB be call , PC tool (msync tool) will send at command to mobile for synchronize data.
*/

#ifndef __MMI_SRV_ATSYNC_H__
#define __MMI_SRV_ATSYNC_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_atsyncsrv.h"

/** SrvAtSyncStartStatusCB
* @param[out]    pApplet           The pointer of the applet.
* @param[out]    eResult           The start result: 
*                                                      ATSYNCSRV_START_SUCCESS
*                                                      ATSYNCSRV_START_FAILED
*/
typedef void (*SrvAtSyncStartStatusCB)(void *pApplet, ATSYNC_START_RESULT_e eResult); 

/** SrvAtSyncStoppedCB
* @param[out]    pApplet           The pointer of the applet.
*/
typedef void (*SrvAtSyncStoppedCB)(void *pApplet);


/** SrvAtSyncSetStartStatusCB
@brief  Add a Callback function point to listen the ATSync Start result status.

@param[in]      pfnCallBack     the function which will be called to notify the detection of ATsync start result,
@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAILED                     AtSync is not ready. 
@retval MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
*/
MAE_Ret SrvAtSyncSetStartStatusCB(SrvAtSyncStartStatusCB pfnCallBack);

/** SrvAtSyncSetStartStatusCB
@brief  Add a Callback function point which will be trigger when the ATSync is stop 

@param[in]      pfnCallBack     the function which will be called to notify the detection of ATsync stop is happening
@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAILED                     AtSync is not ready. 
@retval MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
*/
MAE_Ret SrvAtSyncSetStoppedCB(SrvAtSyncStoppedCB pfnCallBack);

/** SrvAtSyncStart
@brief  start the ATSync and ready to sync, pair with SrvAtSyncStop

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
*/
MAE_Ret SrvAtSyncStart(void);

/** SrvAtSyncStop
@brief  stop the ATSync, Pair with SrvAtSyncStart

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAILED                     If doesn't call SrvAtSyncStart first. 
@retval MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
*/
MAE_Ret SrvAtSyncStop(void);

#ifdef ATSYNC_ATCMD_AUTOTEST
/** SrvAtSyncATRspCB
* @param[out]    pApplet           The pointer of the applet.
*/
typedef void (*SrvAtSyncATRspCB)(void *pApplet);//(void *pApplet, const u8 *AtString,u16 AtStringSize, u16 nSrcMailbox, u32 nATPort, u8 u8DualMode);

/** SrvAtSyncSetATRspCB
@brief  For UnitTest, add a Callback function point which will be trigger when ATSync Srv send the AT Command RSP to MSync Tool (PC Tool) 
@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
*/
MAE_Ret SrvAtSyncSetATRspCB(SrvAtSyncATRspCB pfnCallBack);
#endif

#endif /*__MMI_SRV_ATSYNC_H__*/
