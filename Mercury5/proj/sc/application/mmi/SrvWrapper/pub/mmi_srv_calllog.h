/**
* @file    mmi_srv_calllog.h
* @brief   This is call log service wrapper header file
*          Call log service manages the storage of the logs in the handset. 
*          Service can read or write any logs or maintains specific data (for example, MO/MT call timer) stored in the handset storage. 
*          Service provides interface for others to access the logs and specific data without understanding the implementation of the call log storage.
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SRV_CALLLOG_H__
#define __MMI_SRV_CALLLOG_H__


/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_calllogsrv.h"

/*=============================================================*/
// Callback Function Declaration
/*=============================================================*/

///Note: The confirm(cnf) data structure may be destroyed after the callback is finished.
///      Please make a copy of it if you need it.

typedef void (*SrvCallLogReady_CB)(void *pThis);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_ADDLOG_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogAddCallLogCB)(void *pThis, Mmi_CallLogSrvAddLogCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the read full log request. (triggered by CALLLOGSRV_EVT_READLOG_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogReadFullLogCB)(void *pThis, Mmi_CallLogSrvReadFullLogCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_DELETEONELOG_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogDeleteOneLogCB)(void *pThis, Mmi_CallLogSrvDeleteOneLogCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_DELETEALLLOGS_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogDeleteAllLogsCB)(void *pThis, Mmi_CallLogSrvDeleteAllLogsCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_RESETCALLTIMEAC_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogResetCallTimeACCB)(void *pThis, Mmi_CallLogSrvResetCallTimeACCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_ADDCALLDURATION_END)

@param[out]     pThis           The pointer of Applet.
@param[out]     ptCnf           The confirm information of the request.
*/
typedef void (*SrvCallLogAddCallDurationCB)(void *pThis, Mmi_CallLogSrvAddCallDurationCnf_t *ptCnf);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_MISSEDCALLCOUNT_IND)

@param[out]     pThis           The pointer of Applet.
@param[out]     nMissedCount    The missed call count.
*/
typedef void (*SrvCallLogMissedCallCountChangedCB)(void *pThis, u32 nMissedCount);

/** SrvCallLogAddCallLogCB
@brief  The callback function to confirm the add call log request. (triggered by CALLLOGSRV_EVT_BLOCKEDCALLCOUNT_IND)

@param[out]     pThis           The pointer of Applet.
@param[out]     nBlockedCount   The blocked call count.
*/
typedef void (*SrvCallLogBlockedCallCountChangedCB)(void *pThis, u32 nBlockedCount);

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvCallLogAddCallLogAsync
@brief  This external interface is provided to add a call log to the system 

@param[in]    ptReq             Mmi_CallLogSrvAddLogReq_t. Cannot be null.
@param[in]    pfnCallback       SrvCallLogAddCallLogReqCB. Can be null if you don't care the result.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogAddCallLogAsync(Mmi_CallLogSrvAddLogReq_t *ptReq, SrvCallLogAddCallLogCB pfnCallback);

/** SrvCallLogReadSimpLog
@brief  This external interface is provided to get the simple call log of the sorting table.

@param[in]      ptReq           Mmi_CallLogSrvReadSimpLogReq_t structure. Cannot be null.
@param[in]      ptCnf           Mmi_CallLogSrvReadSimpLogCnf_t structure contains the data you want. Cannot be null.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogReadSimpLog(Mmi_CallLogSrvReadSimpLogReq_t *ptReq, Mmi_CallLogSrvReadSimpLogCnf_t *ptCnf);

/** SrvCallLogReadFullLogAsync
@brief  This external interface is provided to get the full data of a call log

@param[in]    ptReq             Mmi_CallLogSrvReadFullLogReq_t. Cannot be null.
@param[in]    pfnCallback       SrvCallLogReadFullLogCB. Can be null if you don't care the result.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogReadFullLogAsync(Mmi_CallLogSrvReadFullLogReq_t *ptReq, SrvCallLogReadFullLogCB pfnCallback);

/**SrvCallLogFuzzySearchByNumber
@brief: fuzzy search the callog by number    

@param[out] pVectorClass        Pointer to the search result by call log
@param[out] pu8Number           Pointer to the search number

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_NOT_SUPPORTED  The operation is not supported.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogFuzzySearchByNumber(VectorClass_t *pVectorClass, u8 *pu8Number);

/**SrvCallLogIsReady
@brief: check if calllog ready  
*/
boolean SrvCallLogIsReady(void);

/** SrvCallLogSetReadyCB
@brief  This external interface is provided to wait calllog ready

@param[in]    pfnCnfCB             callback function. 

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogSetReadyCB(SrvCallLogReady_CB pfnCnfCB);

/** SrvCallLogDeleteOneLogAsync
@brief  This external interface is provided to delete a call log

@param[in]    ptReq             Mmi_CallLogSrvDeleteOneLogReq_t. Cannot be null.
@param[in]    pfnCallback       SrvCallLogDeleteOneLogCB .Can be null if  you don't care the result.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogDeleteOneLogAsync(Mmi_CallLogSrvDeleteOneLogReq_t *ptReq, SrvCallLogDeleteOneLogCB pfnCallback);

/** SrvCallLogDeleteAllLogsAsync
@brief  This external interface is provided to delete all call logs in the same type

@param[in]    ptReq             Mmi_CallLogSrvDeleteAllLogsReq_t. Cannot be null.
@param[in]    pfnCallback       SrvCallLogDeleteAllLogsCB. Can be null if  you don't care the result.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogDeleteAllLogsAsync(Mmi_CallLogSrvDeleteAllLogsReq_t *ptReq, SrvCallLogDeleteAllLogsCB pfnCallback);

/** SrvCallLogGetCallTimeAC
@brief  This external interface is provided to get value of specific time accumulator

@param[in]      ptReq           Mmi_CallLogSrvGetCallTimeACReq_t structure. Cannot be null.
@param[in]      ptCnf           Mmi_CallLogSrvGetCallTimeACCnf_t structure contains the data you want. Cannot be null.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
@retval  MAE_RET_NOT_FOUND      If ptCnf->u32Time == 0 && ptCnf->u16Count == 0.
*/
MAE_Ret SrvCallLogGetCallTimeAC(Mmi_CallLogSrvGetCallTimeACReq_t *ptReq, Mmi_CallLogSrvGetCallTimeACCnf_t *ptCnf);

/** SrvCallLogResetCallTimeACAsync
@brief  This external interface is provided to reset the time accumulator

@param[in]    ptReq             Mmi_CallLogSrvDeleteAllLogsReq_t. Cannot be null.
@param[in]    pfnCallback       SrvCallLogResetCallTimeACCB .Can be null if  you don't care the result.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_NOT_SUPPORTED  The operation is not supported.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogResetCallTimeACAsync(Mmi_CallLogSrvResetCallTimeACReq_t *ptReq, SrvCallLogResetCallTimeACCB pfnCallback);

/** SrvCallLogAddMissedCountListener
@brief  This external interface is provided for other APs to add a listener to the missed call counter

@param[in]      pMdl            the model listener

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_NOT_SUPPORTED  The operation is not supported.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogAddMissedCountListener(ModelListener_t *pMdl);

/** SrvCallLogSetMissedCallCountChangedCB
@brief  This external interface is provided for other APs to register/deregister a callback function to listen the missed call counter

@param[in]      pfnCallback     the callback function SrvCallLogMissedCallCountChangedCB

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogSetMissedCallCountChangedCB(SrvCallLogMissedCallCountChangedCB pfnCallback);

/** SrvCallLogNotifyMissedCallCountChange
@brief  Provide for CC to notify others the missed call count is changed.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogNotifyMissedCallCountChange(void);

/** SrvCallLogGetLogStatus
@brief  This external interface is provided to get the call logs size of any type

@param[in]      ptReq           Mmi_CallLogSrvLogStatusReq_t structure. Cannot be null.
@param[in]      ptCnf           Mmi_CallLogSrvLogStatusCnf_t structure contains the data you want. Cannot be null.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCallLogGetLogStatus(Mmi_CallLogSrvLogStatusReq_t *ptReq, Mmi_CallLogSrvLogStatusCnf_t *ptCnf);

/** SrvCallLogAddCallDurationAsync
@brief  This This external interface is provided to update the MT/MO/last call time accumulator by the inputcall duration

@param[in]      ptReq           Mmi_CallLogSrvAddCallDurationReq_t. Cannot be null.
@param[in]      pfnCallback     the callback function SrvCallLogAddCallDurationCB

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_BAD_PARAM      If input parameter error. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogAddCallDurationAsync(Mmi_CallLogSrvAddCallDurationReq_t *ptReq, SrvCallLogAddCallDurationCB pfnCallback);

/** SrvCallLogDeleteFile
@brief  Delete the calllogs' file

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogDeleteFile(void);

/** SrvCallLogGetLastDialedCallLog
@brief  This external interface is provided to get the last dialed call log (sync function)

@param[out]     pLog        the return result. Cannot be null.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_NOT_FOUND      If u8NumberLen is 0.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
*/
MAE_Ret SrvCallLogGetLastDialedCallLog(Mmi_CallLogSimpRecord_t *pLog);

/** SrvCallLogResetMissCallCount
@brief  This external interface is provided to reset the miss call count

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogResetMissCallCount(MMI_CALLLOG_SIM_TYPE_E iSimType);


/** SrvCallLogGetMissCallCount
@brief  This external interface is used to get the current miss count recorded in calllog service. 
        The miss count will be automatically reset after SrvCallLogReadSimpLog is called.

@param[out]     pu16MissCount        The returned result. Cannot be null.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            If call log srv is terminated or busy.
@retval MAE_RET_FAILED          The data cannot be retrieved
@retval MAE_RET_BAD_PARAM       If pu16MissCount is NULL 
*/
MAE_Ret SrvCallLogGetMissCallCount(u16 *pu16MissCount);

/** SrvCallLogSetBlockedCallCountChangedCB
@brief  This external interface is provided for other APs to register/deregister a callback function to listen the blocked call counter

@param[in]      pfnCallback     the callback function SrvCallLogBlockedCallCountChangedCB

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_BUSY           The service is busy for doing other requests and waiting confirms.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogSetBlockedCallCountChangedCB(SrvCallLogBlockedCallCountChangedCB pfnCallback);

/** SrvCallLogNotifyBlockedCallCountChange
@brief  provide for CC to notify others the blocked call count is changed.

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogNotifyBlockedCallCountChange(void);

/** SrvCallLogResetBlockCallCount
@brief  This external interface is provided to reset the block call count

@retval  MAE_RET_SUCCESS        If successful.
@retval  MAE_RET_NOT_READY      CallLogSrv is already terminated. 
@retval  MAE_RET_OUT_OF_MEMORY  Memory is not enough to complete the operation.
@retval  MAE_RET_FAILED         If an error occurs.
*/
MAE_Ret SrvCallLogResetBlockCallCount(MMI_CALLLOG_SIM_TYPE_E iSimType);

/** SrvCallLogResetLogCounter
@brief  This external interface is provided to reset the missed/blocked counter of logs belong to the type

@retval  MAE_RET_SUCCESS        If successful.
*/
MAE_Ret SrvCallLogResetLogCounter(u8 u8LogType, MMI_CALLLOG_SIM_TYPE_E iSimType);

/** SrvCallLogGetMissedCallNumBySim
@brief  This external interface is provided to get missed call number of specific SIM
*/
__SLDPM_FREE__ u16 SrvCallLogGetMissCallCountBySim(u8 u8SimID);

/** SrvCallLogGetLogSortingIdxByNum
@brief  This external interface is provided to get sorting idx of log in specific type by number
*/
u16 SrvCallLogGetLogSortingIdxByNum(u8 *pu8Num, u8 u8LogType, u8 *pu8IMSI, CallLogCallType_e eCallLogCallType, u8 u8ListType, MMI_CALLLOG_SIM_TYPE_E u8DisplaySimType);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_CALLLOG_H__

