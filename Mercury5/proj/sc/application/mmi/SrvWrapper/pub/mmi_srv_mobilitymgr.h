/**
* @file    mmi_srv_mobilitymgr.h
* @brief   Mobility Service provide APIs for the network control purpose. 
*          For Example, to search the network, to register the network, attach GPRS, and etc.
*          
*/

#ifndef __MMI_SRV_MOBILITYMGR_H__
#define __MMI_SRV_MOBILITYMGR_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mmsrv.h"

/* callback function type */

/** SrvMobilityMgrNetworkSearchCnfCB
* @brief         The callback function to confirm the search-network request. (triggered by MMSRV_EVT_NetworkSearchCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Query network info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrNetworkSearchCnfCB)(void *pThis, MMSRV_NetworkQuerytCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrNetworkRegCnfCB
* @brief         The callback function to confirm the register-network request. (triggered by MMSRV_EVT_NetworkRegCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrNetworkRegCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);    

/** SrvMobilityMgrCellInfoCnfCB
* @brief         The callback function to confirm the query-cell-info request. (triggered by SrvCoreAppLaunchedCB)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Cell info
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrCellInfoCnfCB)(void *pThis, MMSRV_CellInfoCnf_t *pData, MAE_DualMode_t eDualMode); 

/** SrvMobilityMgrCleanBaListReq
* @brief         The callback function to clean BA list request.
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
*/
typedef void (* SrvMobilityMgrCleanBAListCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult); 

/** SrvMobilityMgrUpdatePreferredPLMNListCnfCB
* @brief         The callback function to confirm update-preferred-PLMN request. (triggered by MMSRV_EVT_UpdatePreferredPLMNListCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrUpdatePreferredPLMNListCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);   

/** SrvMobilityMgrQueryPreferredPLMNListCnfCB
* @brief         The callback function to confirm the query-preferred-PLMN request. (triggered by MMSRV_EVT_QueryPreferredPLMNListCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Query preferred PLMN info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrQueryPreferredPLMNListCnfCB)(void *pThis, MMSRV_PreferredPLMNQuerytCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrChangeBandCnfCB
* @brief         The callback function to confirm the powering on/off request. (triggered by MMSRV_EVT_ChangeBandCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrChangeBandCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrQueryBandCnfCB
* @brief         The callback function to confirm the powering on/off request. (triggered by MMSRV_EVT_QueryBandCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
*/
typedef void (* SrvMobilityMgrQueryBandCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MMI_MMSRV_Band_e eBand);

/** SrvMobilityMgrChangeLineCnfCB
* @brief         The callback function to confirm the change-line request. (triggered by MMSRV_EVT_ChangeLineCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Change line info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrChangeLineCnfCB)(void *pThis, MMSRV_ChangeLineCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrQueryLineCnfCB
* @brief         The callback function to confirm the query-line request. (triggered by MMSRV_EVT_QueryLineCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Query line info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrQueryLineCnfCB)(void *pThis, MMSRV_QueryLineCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrGPRSAttachCnfCB
* @brief         The callback function to confirm the attach-GPRS request. (triggered by MMSRV_EVT_GPRSAttachCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
#ifdef __GPRS_MMI__
typedef void (* SrvMobilityMgrGPRSAttachCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
/** SrvMobilityMgrAbortCnfCB
* @brief         The callback function to confirm the abort request. (triggered by MMSRV_EVT_AbortCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrAbortCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrSignalStrengthIndCB
* @brief         The callback function to confirm the signal-strngth-change indication. (triggered by MMSRV_EVT_SignalStrengthInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Signal strngth info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrSignalStrengthIndCB)(void *pThis, MMSRV_SignalStrengthInd_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrGPRSRegStatusIndCB
* @brief         The callback function to confirm the GPRS-register-change indication. (triggered by MMSRV_EVT_GPRSRegStatusInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              GPRS register info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
#ifdef __GPRS_MMI__
typedef void (* SrvMobilityMgrGPRSRegStatusIndCB)(void *pThis, MMSRV_GPRSRegInd_t *pData, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
/** SrvMobilityMgrNetworkRegIndCB
* @brief         The callback function to confirm the network-register-state indication. (triggered by MMSRV_EVT_NetworkRegInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eState             Network register state.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrNetworkRegIndCB)(void *pThis, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrNetworkTypeIndCB
* @brief         The callback function to confirm the network-type-change indication. (triggered by MMSRV_EVT_NetworkTypeInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eType              Network type info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrNetworkTypeIndCB)(void *pThis, MMI_MMSRV_NetworkType_e eType, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrOnlineCnfCB
* @brief         The callback function to confirm the on-line request. (triggered by MMSRV_EVT_OnlineCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrOnlineCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrOfflineCnfCB
* @brief         The callback function to confirm the off-line request. (triggered by MMSRV_EVT_OfflineCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrOfflineCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrLineServiceIndCB
* @brief         The callback function to confirm the line-service-change indication. (triggered by MMSRV_EVT_LineServiceInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eLine              Line CFU info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrLineServiceIndCB)(void *pThis, MMI_MMSRV_Line_CFU_e eLine, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrQueryWgprsCnfCB
* @brief         The callback function to confirm the query-WGPRS request. (triggered by MMSRV_EVT_QueryWgprsCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              WGPRS confirm info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
#ifdef __GPRS_MMI__
typedef void (* SrvMobilityMgrQueryWgprsCnfCB)(void *pThis, MMSRV_QueryWGPRSCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrMSClassCnfCB
* @brief         The callback function to confirm the mobile-station-class request. (triggered by MMSRV_EVT_MSClassCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              Mobile station class confirm info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrMSClassCnfCB)(void *pThis, MMSRV_MSClassCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrPDPContextActCnfCB
* @brief         The callback function to confirm the PDP-conetext act request. (triggered by MMSRV_EVT_GPRS_PDPContextActCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pData              PDP conetext act confirm info.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrPDPContextActCnfCB)(void *pThis, MMSRV_GPRSPDPContextActCnf_t *pData, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrAddPDPContextCnfCB
* @brief         The callback function to confirm the add-PDP-context request. (triggered by MMSRV_EVT_GPRS_AddPDPContextCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrAddPDPContextCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrSetQoSCnfCB
* @brief         The callback function to confirm the set-QoS request. (triggered by MMSRV_EVT_GPRS_SetQoSCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrSetQoSCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
/** SrvMobilityMgrSyncAutoTimeZoneCB
* @brief         The callback function to confirm the sync-auto-timezone request. (triggered by MMSRV_EVT_SyncAutoTimeZone)
*
* @param[out]    pThis              The pointer of the applet.
*/
typedef void (* SrvMobilityMgrSyncAutoTimeZoneCB)(void *pThis);

/** SrvMobilityMgrChangeNetAccessModeCnfCB
* @brief         The callback function to confirm the powering on/off request. (triggered by MMSRV_EVT_ChangeNetAccessModeCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrChangeNetAccessModeCnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrSetIMEICnfCB
* @brief         The callback function to confirm the set IMEI request. (triggered by MMSRV_EVT_SetIMEICnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eResult            The result of the request.
* @param[out]    eDualMode          The DualSIM ID to indicate master or slave.
*/
typedef void (* SrvMobilityMgrSetIMEICnfCB)(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);

/* APIs */

/** SrvMobilityMgrSetSignalStrengthIndCB
* @brief  Register/deregister a callback function to listen to the signal strength
*
* @param[in]      pfnCallBack             SrvMobilityMgrSignalStrengthIndCB, a callback function pointer
*/
void SrvMobilityMgrSetSignalStrengthIndCB(SrvMobilityMgrSignalStrengthIndCB pfnCallBack);

/** SrvMobilityMgrSetGPRSRegStatusIndCB
* @brief  Register/deregister a callback function to listen to the GPRS register status
*
* @param[in]      pfnCallBack             SrvMobilityMgrGPRSRegStatusIndCB, a callback function pointer
*/
#ifdef __GPRS_MMI__
void SrvMobilityMgrSetGPRSRegStatusIndCB(SrvMobilityMgrGPRSRegStatusIndCB pfnCallBack);
#endif //__GPRS_MMI__
/** SrvMobilityMgrSetNetworkRegIndCB
* @brief  Register/deregister a callback function to listen to the network register status
*
* @param[in]      pfnCallBack             SrvMobilityMgrNetworkRegIndCB, a callback function pointer
*/
__SLDPM_FREE__ void SrvMobilityMgrSetNetworkRegIndCB(SrvMobilityMgrNetworkRegIndCB pfnCallBack);

/** SrvMobilityMgrSetNetworkTypeIndCB
* @brief  Register/deregister a callback function to listen to the network type status
*
* @param[in]      pfnCallBack             SrvMobilityMgrNetworkTypeIndCB, a callback function pointer
*/
void SrvMobilityMgrSetNetworkTypeIndCB(SrvMobilityMgrNetworkTypeIndCB pfnCallBack);

/** SrvMobilityMgrSetLineServiceIndCB
* @brief  Register/deregister a callback function to listen to the line service status
*
* @param[in]      pfnCallBack             SrvMobilityMgrLineServiceIndCB, a callback function pointer
*/
void SrvMobilityMgrSetLineServiceIndCB(SrvMobilityMgrLineServiceIndCB pfnCallBack);

/** SrvMobilityMgrGetMMServiceStatus
* @brief  Get MM Service status.
*
* @retval MMI_MMSRV_STATUS_INITIAL    If MM SRV is initializing.
* @retval MMI_MMSRV_STATUS_IDLE       If MM SRV is ready to accept request. 
* @retval MMI_MMSRV_STATUS_BUSY       If MM SRV is busy and will reject AP's request.
* @retval MMI_MMSRV_STATUS_TERMINATE  If MM SRV is going to terminate.                                                                                                                  
*/
MMI_MMSRV_Status_e SrvMobilityMgrGetMMServiceStatus(void);

/** SrvMobilityMgrNetworkSearchReq
* @brief  Search the available network.
*
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a call back function which trigger when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
*/
MAE_Ret SrvMobilityMgrNetworkSearchReq(MAE_DualMode_t eDualMode, SrvMobilityMgrNetworkSearchCnfCB pfnCallBack);

/** SrvMobilityMgrNetworkRegReq
* @brief  Register or de-register on PLMN.
*
* @param[in]      eRegMode            register mode or de-register
* @param[in]      eOperFormat         operator format. 
* @param[in]      pOper               operator data
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a call back function which trigger when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrNetworkRegReq(MMI_MMSRV_RegMode_e eRegMode,
                                    MMI_MMSRV_Oper_Format_e eOperFormat,
                                    u8 *pOper,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrNetworkRegCnfCB pfnCallBack);

#ifdef __3G_RIL_MMI__
/** SrvMobilityMgrNetworkRegReqEx
* @brief  This external interface is provided to register or de-register on PLMN.
*
* @param[in]      eRegMode            register mode or de-register
* @param[in]      eOperFormat         operator format. 
* @param[in]      pOper               operator data
* @param[in]      eAct                network access technology
* @param[in]      eDualMode           DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a call back function which trigger when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrNetworkRegReqEx(MMI_MMSRV_RegMode_e eRegMode,
                                    MMI_MMSRV_Oper_Format_e eOperFormat,
                                    u8 *pOper,
                                    MMI_MMSRV_RR_ACT_e eAct,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrNetworkRegCnfCB pfnCallBack);
#endif // __3G_RIL_MMI__

/** SrvMobilityMgrUpdatePreferredListReq
* @brief  Update the preferred PLMN list in EF_PLMNsel SIM file.
*
* @param[in]      nIndex              index
* @param[in]      eOperFormat         operator format.
* @param[in]      pOper               operator data
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrUpdatePreferredListReq(u8 nIndex,
                                             MMI_MMSRV_Oper_Format_e eOperFormat,
                                             u8 *pOper,
                                             MAE_DualMode_t eDualMode,
                                             SrvMobilityMgrUpdatePreferredPLMNListCnfCB pfnCallBack);

#ifdef __3G_RIL_MMI__
/** SrvMobilityMgrUpdatePreferredListReq
* @brief  Update the preferred PLMN list in EF_PLMNsel SIM file.
*
* @param[in]      nIndex              index
* @param[in]      eOperFormat         operator format.
* @param[in]      pOper               operator data
* @param[in]      uActMask            Access technology mask, refer MMI_MMSRV_RR_ACT_MASK_e
* @param[in]      eDualMode           DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a call back function which trigger when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrUpdatePreferredListReqEx(u8 nIndex, MMI_MMSRV_Oper_Format_e  eOperFormat,
                                             u8 *pOper,
                                             u16 uActMask,
                                             MAE_DualMode_t eDualMode,
                                             SrvMobilityMgrUpdatePreferredPLMNListCnfCB pfnCallBack);
#endif //#ifdef __3G_RIL_MMI__

/** SrvMobilityMgrQueryPreferredListReq
* @brief  Query the preferred PLMN list in EF_PLMNsel SIM file. 
*
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a PreferPlmnQuery in queue.
*/
MAE_Ret SrvMobilityMgrQueryPreferredListReq(MAE_DualMode_t eDualMode,
                                            SrvMobilityMgrQueryPreferredPLMNListCnfCB pfnCallBack);

/** SrvMobilityMgrChangeBandReq
* @brief  Change call waiting settings. 
*
* @param[in]      eBandID             band frequency
* @param[in]      eDualMode           Mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrChangeBandReq(MMI_MMSRV_Band_e eBandID,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrChangeBandCnfCB pfnCallBack);

#ifdef __3G_RIL_MMI__
/** SrvMobilityMgrChangeBandReqEx
* @brief  The external interface is provided to change call waiting setting. 
*
* @param[in]      bandSel             band frequency
* @param[in]      eDualMode           DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a call back function which trigger when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
MAE_Ret SrvMobilityMgrChangeBandReqEx(MMSRV_BandSelectionInfo_t bandSel,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrChangeBandCnfCB pfnCallBack);
#endif

/** SrvMobilityMgrChangeLineReq
* @brief  Change the active line.
* 
* @param[in]    eLineNumber           line number to activate
* @param[in]    eDualMode             mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]    pfnCallBack           a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a change line request in queue.
*/
MAE_Ret SrvMobilityMgrChangeLineReq(MMI_MMSRV_Line_Service_e eLineNumber,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrChangeLineCnfCB pfnCallBack);

/** SrvMobilityMgrGprsAttachReq
* @brief  Attach or detach to the GPRS network. 
* 
* @param[in]      eOperation          assign to attach or detach
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_READY           If Service is not ready.
* @retval MAE_RET_BUSY                If Service is busy.
*/
#ifdef __GPRS_MMI__
MAE_Ret SrvMobilityMgrGprsAttachReq(MMI_MMSRV_GPRS_Reg_e eOperation,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrGPRSAttachCnfCB pfnCallBack);
#endif //__GPRS_MMI__
/** SrvMobilityMgrAbortReq
* @brief  Cancel the current RIL network request.
*
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvMobilityMgrAbortReq(MAE_DualMode_t eDualMode, SrvMobilityMgrAbortCnfCB pfnCallBack);

/** SrvMobilityMgrQueryNetworkStatus
* @brief  Get the current network registration status.
* 
* @param[out]     pOut                The network registration information output data which is prepared by caller.
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
*/
__SLDPM_FREE__ MAE_Ret SrvMobilityMgrQueryNetworkStatus(MMSRV_NetworkRegInfo_t *pOut, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrOnlineReq
* @brief  Set the MS to online mode, MM service will camp on network    
* 
* @param[in]  eMode                   set network searching screen prompt or not.
* @param[in]  pfnCallBack             a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a OnlineReqData request in queue.
*/
MAE_Ret SrvMobilityMgrOnlineReq(MMI_MMSRV_SearchMode_e eMode,
                                SrvMobilityMgrOnlineCnfCB pfnCallBack);

/** SrvMobilityMgrOfflineReq
* @brief   Set the MS to offline mode, MM service will camp off network    
* 
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a OfflineReqData request in queue.
*/
MAE_Ret SrvMobilityMgrOfflineReq(SrvMobilityMgrOfflineCnfCB pfnCallBack);

/** SrvMobilityMgrQueryLineReq
* @brief   Query the current MS line service settings.   
* 
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a LineQuery request in queue.
*/
MAE_Ret SrvMobilityMgrQueryLineReq(MAE_DualMode_t eDualMode, SrvMobilityMgrQueryLineCnfCB pfnCallBack);

/** SrvMobilityMgrQueryBandReq
* @brief  Query current band settings.
* 
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a BandQuery request in queue.
*/
MAE_Ret SrvMobilityMgrQueryBandReq(MAE_DualMode_t eDualMode, SrvMobilityMgrQueryBandCnfCB pfnCallBack);

/** SrvMobilityMgrMSClassReq
* @brief  Query the mobile station class information.
* 
* @param[in]      pReq                mobile class request
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a MSClass request in queue.
*/
#ifdef __GPRS_MMI__
MAE_Ret SrvMobilityMgrMSClassReq(MMSRV_MSClassReq_t *pReq,
                                 MAE_DualMode_t eDualMode,
                                 SrvMobilityMgrMSClassCnfCB pfnCallBack);

/** SrvMobilityMgrGPRSPDPContextActReq
* @brief   Active/de-active the GPRS session.
* 
* @param[in]      pReq                PDP session request
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a GPRS PDP context action request in queue.
*/
MAE_Ret SrvMobilityMgrGPRSPDPContextActReq(MMSRV_GPRSPDPContextActReq_t *pReq,
                                           MAE_DualMode_t eDualMode,
                                           SrvMobilityMgrPDPContextActCnfCB pfnCallBack);

/** SrvMobilityMgrGPRSAddPDPContextReq
* @brief   Add a PDP context request.
* 
* @param[in]      pReq                PDP context request
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a GPRS PDP context add request in queue.
*/
MAE_Ret SrvMobilityMgrGPRSAddPDPContextReq(MMSRV_GPRSPDPContextAddReq_t *pReq, 
                                           MAE_DualMode_t eDualMode, 
                                           SrvMobilityMgrAddPDPContextCnfCB pfnCallBack);

/** SrvMobilityMgrGPRSDeletePDPContextReq
* @brief   Delete a PDP context request.    
* 
* @param[in]      nCid                
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a GPRS PDP context delete request in queue.
*/
MAE_Ret SrvMobilityMgrGPRSDeletePDPContextReq(u8 nCid, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrGPRSSetQoSReq
* @brief   Set GPRS QoS settings.
* 
* @param[in]      pReq                QoS settings
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a GPRS QoS set request in queue.
*/
MAE_Ret SrvMobilityMgrGPRSSetQoSReq(MMSRV_GPRSQoSSetReq_t *pReq,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrSetQoSCnfCB pfnCallBack);

/** SrvMobilityMgrGPRSQueQoSReq
* @brief   Set GPRS QoS queue type.
* 
* @param[in]      pReq                QoS queue type
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a GPRS QoS query request in queue.
*/
MAE_Ret SrvMobilityMgrGPRSQueQoSReq(MMSRV_GPRSQoSQueReq_t *pReq, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__

/** SrvMobilityMgrCellInfoReq
* @brief   Get cell information.
*  
* @param[in]      pReq                cell inforamtion
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a Cell Info query request in queue.
*/
MAE_Ret SrvMobilityMgrCellInfoReq(MMSRV_CellInfoReq_t *pReq,
                                  MAE_DualMode_t eDualMode,
                                  SrvMobilityMgrCellInfoCnfCB pfnCallBack);

MAE_Ret SrvMobilityMgrCleanBaListReq(SrvMobilityMgrCleanBAListCnfCB pfnCallBack);

/** SrvMobilityMgrGetLineStatus
* @brief   Get line status.
* 
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE       
* 
* @retval MMI_MMSRV_Line_Service_e
*/
MMI_MMSRV_Line_Service_e SrvMobilityMgrGetLineStatus(MAE_DualMode_t eDualMode);

/** SrvMobilityMgrSyncWithTimezone
* @brief   Sync time-zone.
* 
* @param[in]      bYesNo              TRUE for getting and updating time-zone in configuration and FALSE for no updating
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvMobilityMgrSyncWithTimezone(boolean bYesNo, SrvMobilityMgrSyncAutoTimeZoneCB pfnCallBack);

/** SrvMobilityMgrQueryNITZNetworkInfo
* @brief   Query NITZ network information.
* 
* @param[in]      nCurDualID          Current dual ID
* @param[out]     pOut                result structure if PLMN record found.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_NOT_FOUND           If NITZ Network info not found.
*/
MAE_Ret SrvMobilityMgrQueryNITZNetworkInfo(u8 nCurDualID, MMSRV_NITZNetworkInfo_t *pOut);

/** SrvMobilityMgrResetNetworkReq
* @brief   Reset the network. If MS is online, MS will offline then online; otherwise, do nothing.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a OfflineReqData request in queue.
*/
MAE_Ret SrvMobilityMgrResetNetworkReq(void);

/** SrvMobilityMgrQueryGprsStatus
* @brief   Get the current GPRS network registration status.
* 
* @param[out]     pOut                the GPRS network registration information output data
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
*/
#ifdef __GPRS_MMI__
MAE_Ret SrvMobilityMgrQueryGprsStatus(MMSRV_GPRSRegInfo_t *pOut, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrSetWgprsReq
* @brief   Set GPRS related initialize settings.      
* 
* @param[in]      pReq                WGPRS request, GPRS parameters customization
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a WGPRS set request in queue.
*/
MAE_Ret SrvMobilityMgrSetWgprsReq(MMSRV_WGPRSReq_t *pReq, MAE_DualMode_t eDualMode);

/** SrvMobilityMgrQueryWgprsReq
* @brief   Query GPRS related initialize settings.      
* 
* @param[in]      pReq                WGPRS query request    
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a WGPRS query request in queue.
*/
MAE_Ret SrvMobilityMgrQueryWgprsReq(MMSRV_QueryWGPRSReq_t *pReq,
                                    MAE_DualMode_t eDualMode,
                                    SrvMobilityMgrQueryWgprsCnfCB pfnCallBack);

/** SrvMobilityMgrChangeNetAccessModeReg
* @brief   Get the current GPRS network registration status.      
* 
* @param[in]      eAccessMode         network access mode: MMI_MMSRV_NETACCESS_GSM_ONLY / MMI_MMSRV_NETACCESS_GPRS_PREFERRED           
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a OfflineReqData request in queue.
* @retval MAE_RET_FAILED              It's in AIRPLANE_MODE now, MMSrv do nothing.
*/
MAE_Ret SrvMobilityMgrChangeNetAccessModeReg(MMI_MMSRV_NetAccess_Mode_e eAccessMode,
                                             MAE_DualMode_t eDualMode,
                                             SrvMobilityMgrChangeNetAccessModeCnfCB pfnCallBack);
#endif //__GPRS_MMI__

/** SrvMobilityMgrSetIMEIReq
* @brief   Set Master or Slave IMEI.      
* 
* @param[in]      eDualMode           mode: DUAL_MASTER / DUAL_SLAVE
* @param[in]      pIMEI         	  IMEI code with length 15           
* @param[in]      pfnCallBack         a callback function which will be triggered when ready
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If shell wants to terminate service, ignore request. 
* @retval MAE_RET_BUSY                If there is already a OfflineReqData request in queue.
* @retval MAE_RET_FAILED              It's in AIRPLANE_MODE now, MMSrv do nothing.
*/
MAE_Ret SrvMobilityMgrSetIMEIReq(MAE_DualMode_t eDualMode, u8 *pIMEI, SrvMobilityMgrSetIMEICnfCB pfnCallBack);

#ifdef __3G_RIL_MMI__
/** SrvMobilityMgrGetNetworkQueryStatusReq
* @brief   This external interface is provided to get current network query status      
* 
* @param[in]        eDualMode                           DUAL_MASTER / DUAL_SLAVE
*
* @param[out]      bIsNetworkInfoQueried           TRUE / FALSE
*
* @retval MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvMobilityMgrGetNetworkQueryStatusReq(MAE_DualMode_t eDualMode, boolean *bIsNetworkInfoQueried);

/** SrvMobilityMgrSetNetworkQueryStatusReq
* @brief   This external interface is provided to get current network query status      
* 
* @param[in]      eDualMode                           DUAL_MASTER / DUAL_SLAVE
* @param[in]      bIsNetworkInfoQueried           TRUE / FALSE
* 
* @retval MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvMobilityMgrSetNetworkQueryStatusReq(MAE_DualMode_t eDualMode, boolean bIsNetworkInfoQueried);

/** SrvMobilityMgrGetNetworkSettingInfoReq
* @brief   This external interface is provided to get current network setting info      
*
* @param[in]        eDualMode                           DUAL_MASTER / DUAL_SLAVE
*
* @param[out]      pNetworkSettingInfo           
* 
* @retval MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvMobilityMgrGetNetworkSettingInfoReq(MAE_DualMode_t eDualMode, MMSRV_NetworkSettingInfo_t *pNetworkSettingInfo);

#endif // __3G_RIL_MMI__
#endif //__MMI_SRV_MOBILITYMGR_H__
/*-----------------------------------------------------*/
