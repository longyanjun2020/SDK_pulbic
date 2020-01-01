/**
* @file    mmi_srv_simsrv.h
* @brief   
*          
*/

#ifndef __MMI_SRV_SIM_H__
#define __MMI_SRV_SIM_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_simsrv.h"
#include "mmi_if_sim.h"


typedef void (* SrvSimSIMActiveIndCB)(void *pThis, boolean bActivated, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimInitAppStartIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMStatusChangeIndCB)(void *pThis, COMMON_SIM_CARD_STATUS_e eStatus);
typedef void (* SrvSimNoSIMIndCB)(void *pThis);
typedef void (* SrvSimSIMIndReadyIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMMasterFileReadyCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMIMSIFileReadyCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMChangedIndCB)(void *pThis, boolean bSIMChanged, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMDeactivateIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMErrorIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimSIMNoRspIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimInitAppFinishedIndCB)(void *pThis, SIMSRV_INITAPP_TYPE_e eInitAppType);
typedef void (* SrvSimSIMReadyIndCB)(void *pThis, u8 nActiveSIM); //nActiveSIM: DUAL_MASTER/DUAL_SLAVE mae_common_def.h
typedef void (* SrvSimInitSMSReadyIndCB)(void *pThis);



typedef void (* SrvSimEnablePINCnfCB)(void *pThis, SIM_PIN_STATUS_e ePinStatus, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimDisablePINCnfCB)(void *pThis, SIM_PIN_STATUS_e ePinStatus, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimVerifyPINCnfCB)(void *pThis, SIM_PIN_STATUS_e ePinStatus, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimChangePINCnfCB)(void *pThis, SIM_PIN_STATUS_e ePinStatus, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimUnblockPINCnfCB)(void *pThis, SIM_PIN_STATUS_e ePinStatus, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimReadSIMFileCnfCB)(void *pThis, SIMSRV_FileReadCnf_t *tFileReadCnf, SIMSRV_SIM_ID_e eSIMID); // structure free function: _mmi_SIMSRV_FreeSIMReadCnf
typedef void (* SrvSimSetPreferredLangCnfCB)(void *pThis, SIM_Rslt_e eSIMRst, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimActivateSIMCnfCB)(void *pThis, SIMSRV_RESULT_e eResult, SIMSRV_SIM_ID_e eSIMID);
typedef void (* SrvSimStatusSIMFileCnfCB)(void *pThis,
                                                SIMSRV_FileStatusCnf_t *pFileStatusCnf,
                                                SIMSRV_SIM_ID_e eSIMID);// structure free function: _mmi_SIMSRV_FreeStatusFileCnfData
typedef void (* SrvSimDeactivateSIMforShutdownCnfCB)(void *pThis);



/** SrvSimSetSIMReadyIndCB
* @brief  Set callback function to listen SIM Ready Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMReadyInd.
*/
void SrvSimSetSIMReadyIndCB(SrvSimSIMReadyIndCB pfnCallBack);

/** SrvSimSetSIMActiveIndCB
* @brief  Set callback function to Listen SIM Active Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMActiveInd.
*/
void SrvSimSetSIMActiveIndCB(SrvSimSIMActiveIndCB pfnCallBack);

/** SrvSimSetInitAppStartIndCB
* @brief  Set callback function to listen SIM Init Applet Start Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_InitAppStartInd.
*/
void SrvSimSetInitAppStartIndCB(SrvSimInitAppStartIndCB pfnCallBack);

/** SrvSimSetInitSMSReadyIndCB
* @brief  Set callback function to listen SIM Init SMS Ready Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_InitSMSReadyInd.
*/
void SrvSimSetInitSMSReadyIndCB(SrvSimInitSMSReadyIndCB pfnCallBack);

/** SrvSimSetInitAppFinishedIndCB
* @brief  Set callback function to listen SIM Init Applet Finished Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_InitAppFinishedInd.
*/
void SrvSimSetInitAppFinishedIndCB(SrvSimInitAppFinishedIndCB pfnCallBack);

/** SrvSimSetSIMStatusChangeIndCB
* @brief  Set callback function to listen SIM Status Change Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMStatusChangeInd.
*/
void SrvSimSetSIMStatusChangeIndCB(SrvSimSIMStatusChangeIndCB pfnCallBack);

/** SrvSimSetNoSIMIndCB
* @brief  Set callback function to listen No SIM Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_NoSIMInd.
*/
void SrvSimSetNoSIMIndCB(SrvSimNoSIMIndCB pfnCallBack);

/** SrvSimSetSIMIndReadyIndCB
* @brief  Set callback function to listen SIM Indicator Setup Ready Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMIndReadyInd.
*/
void SrvSimSetSIMIndReadyIndCB(SrvSimSIMIndReadyIndCB pfnCallBack);

/** SrvSimSetSIMMasterFileReadyCB
* @brief  Set callback function to listen SIM MasterFile Ready Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMMasterFileReady.
*/
void SrvSimSetSIMMasterFileReadyCB(SrvSimSIMMasterFileReadyCB pfnCallBack);

/** SrvSimSetSIMIMSIFileReadyCB
* @brief  Set callback function to listen SIM IMSI File Ready Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMIMSIFileReady.
*/
void SrvSimSetSIMIMSIFileReadyCB(SrvSimSIMIMSIFileReadyCB pfnCallBack);

/** SrvSimSetSIMChangedIndCB
* @brief  Set callback function to listen SIM Changed Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMChangedInd.
*/
void SrvSimSetSIMChangedIndCB(SrvSimSIMChangedIndCB pfnCallBack);

/** SrvSimSetSIMDeactivateIndCB
* @brief  Set callback function to listen SIM Deactivate Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMDeactivateInd.
*/
void SrvSimSetSIMDeactivateIndCB(SrvSimSIMDeactivateIndCB pfnCallBack);

/** SrvSimSetSIMErrorIndCB
* @brief  Set callback function to listen SIM SIMError Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMErrorInd.
*/
void SrvSimSetSIMErrorIndCB(SrvSimSIMErrorIndCB pfnCallBack);
#ifdef __SIM_NO_RSP_HANDLING__
/** SrvSimSetSIMNoRspIndCB
* @brief  Set callback function to listen SIM SIMNoRsp Indicator
* 
* @param[in]      pfnCallBack             Pointer to the callback function of SIMSRV_EVT_SIMNoRspErrInd.
*/
void SrvSimSetSIMNoRspIndCB(SrvSimSIMNoRspIndCB pfnCallBack);
#endif //__SIM_NO_RSP_HANDLING__
/** SrvSimGetPINStatus
* @brief  Get PIN status of specific SIM
* 
* @param[in]      eSIMID                  Specific SIM ID.
* @param[out]     pStatus                 Pointer to SIM status structure.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_READY               SIMSRV does not get PIN status from SIM card yet.
*/
MAE_Ret SrvSimGetPINStatus(SIMSRV_PIN_STATUS_t *pStatus, SIMSRV_SIM_ID_e eSIMID);

/** SrvSimGetPreferredLanguage
* @brief  Get preferred language of specific SIM.
* 
* @param[in]      eSIMID                  Specific SIM ID.
* @param[out]     pLangCode               Preferred language code.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_READY               If an error happen.
*/
MAE_Ret SrvSimGetPreferredLanguage(MAE_LANG_CODE_e *pLangCode, SIMSRV_SIM_ID_e eSIMID);

/** SrvSimGetEmergencyCode
* @brief  Get emergency call list
* 
* @param[in]      eSIMID              Specific SIM ID.
* @param[out]     pEcc                The emergency call list.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           SIMSRV does not get emergency code list from SIM card yet.
*/
MAE_Ret SrvSimGetEmergencyCode(SIMSRV_ECC_t *pEcc, SIMSRV_SIM_ID_e     eSIMID);

/** SrvSimGetIMSI
* @brief  Get IMSI
* 
* @param[in]      eSIMID              Specific SIM ID.
* @param[out]     pIMSI               Pointer to the IMSI.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           SIMSRV does not get IMSI from SIM card yet.
*/
MAE_Ret SrvSimGetIMSI(u8 *pIMSI, SIMSRV_SIM_ID_e     eSIMID);

/** SrvSimGetSIMServiceTable
* @brief  To Check if such SST feature is supported by specific SIM.
* 
* @param[in]      eFeature            Specific SST feature.
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE                    If SIM card supports this feature.
* @retval FALSE                   If SIM card does not support this feature.
*/
boolean SrvSimGetSIMServiceTable(SIMSRV_SST_FEATURE_e    eFeature,
                                 SIMSRV_SIM_ID_e         eSIMID);

/** SrvSimEnablePINReq
* @brief  Request to enable PIN.
* 
* @param[in]      pPINValue           The pointer to PIN string.
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         Callback function for SrvSimEnablePINCnfCB.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If an error happen.
* @retval MAE_RET_BUSY                There is a duplicate request in waiting queue already. Reject the later one.
*/
MAE_Ret SrvSimEnablePINReq(u8 *pPINValue, SIMSRV_SIM_ID_e eSIMID, SrvSimEnablePINCnfCB pfnCallBack);

/** SRV_FilrMgr_DisablePINReq
* @brief  Request to disable PIN.
* 
* @param[in]      pPINValue           The pointer to PIN string.
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]	  pfnCallBack	      Callback function for SrvSimDisablePINCnfCB.		
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
* @retval MAE_RET_BUSY                There is a duplicate request in waiting queue already. Reject the later one.
*/
MAE_Ret SrvSimDisablePINReq(u8 *pPINValue, SIMSRV_SIM_ID_e eSIMID, SrvSimDisablePINCnfCB pfnCallBack);

/** SrvSimVerifyPINReq
* @brief  Request to verify PIN
* 
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      eType               PIN type
* @param[in]      pPINValue           The pointer to PIN string.
* @param[in]      pfnCallBack         The pointer callback function for SIMSRV_EVT_VerifyPINCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
* @retval MAE_RET_BUSY                There is a duplicate request in waiting queue already. Reject the later one.
*/
MAE_Ret SrvSimVerifyPINReq(SIMSRV_PIN_TYPE_e eType,
                           u8 *pPINValue,
                           SIMSRV_SIM_ID_e eSIMID,
                           SrvSimVerifyPINCnfCB pfnCallBack);

/** SrvSimChangePINReq
* @brief  Request to change PIN
* 
* @param[in]      eType               PIN type
* @param[in]      pOldValue           The pointer to old PIN string.
* @param[in]      pNewValue           The pointer to new PIN string.
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         The pointer callback function for SIMSRV_EVT_ChangePINCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
* @retval MAE_RET_BUSY                If there is already a change PIN request in queue.
*/
MAE_Ret SrvSimChangePINReq(SIMSRV_PIN_TYPE_e eType,
                           u8 *pOldValue,
                           u8 *pNewValue,
                           SIMSRV_SIM_ID_e eSIMID,
                           SrvSimChangePINCnfCB pfnCallBack);


/** SrvSimUnblockPINReq
* @brief  Request to unlock PIN
* 
* @param[in]      eType               PIN type
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pPUKValue           The pointer to PUK string.
* @param[in]      pPINValue           The pointer to PIN string.
* @param[in]      pfnCallBack         The pointer callback function for SIMSRV_EVT_UnblockPINCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
* @retval MAE_RET_BUSY                If here is already an Unblock PIN request in queue.
*/
MAE_Ret SrvSimUnblockPINReq(SIMSRV_PIN_TYPE_e eType,
                            u8 *pPUKValue,
                            u8 *pPINValue,
                            SIMSRV_SIM_ID_e eSIMID,
                            SrvSimUnblockPINCnfCB pfnCallBack);

/** SrvSimReadFileReq
* @brief  Request to read file
* 
* @param[in]      eFileID                 SIM file ID.
* @param[in]      eSIMID                  Specific SIM ID.
* @param[in]      pfnCallBack             The pointer callback function for SIMSRV_EVT_ReadSIMFileCnf.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_READY               If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimReadFileReq(SIMSRV_SIM_FILE_ID_e    eFileID,
                          SIMSRV_SIM_ID_e         eSIMID,
                          SrvSimReadSIMFileCnfCB pfnCallBack);

/** SrvSimSetPreferredLanguage
* @brief  Set preferred language
* 
* @param[in]      eLangCode           preferred language.
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         The pointer callback function for SIMSRV_EVT_SetPreferredLangCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimSetPreferredLanguage(MAE_LANG_CODE_e                   eLangCode,
                                   SIMSRV_SIM_ID_e                  eSIMID,
                                   SrvSimSetPreferredLangCnfCB  pfnCallBack);

/** SrvSimGetMccMnc
* @brief  Get mcc, mnc
* 
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      bActiveSIM          Is active SIM.
* @param[out]     pMccMnc             Mcc and Mnc value
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           SIMSRV does not get MCC/MNC from SIM card yet.
*/
MAE_Ret SrvSimGetMccMnc(MccMnc_t *pMccMnc, SIMSRV_SIM_ID_e eSIMID, boolean bActiveSIM);

/** SrvSimIsWhiteSIMCard
* @brief  To check if the SIM card is white SIM
* 
* @param[in]      eSIMID          Specific SIM ID.
* 
* @retval TRUE                    If white SIM.
* @retval FALSE                   If not white SIM.
*/
boolean SrvSimIsWhiteSIMCard(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimGetSIMCardStatus
* @brief  Get current activated SIM card status.
* 
* @retval       COMMON_SIM_CARD_UNKNOW              Not receive SIM indication yet.
* @retval       COMMON_SIM_CARD_NOSIM               No SIM inserted for both single mode and DUO mode.
* @retval       COMMON_SIM_CARD_SINGLE              SIM inserted and activated for single SIM mode.
* @retval       COMMON_SIM_CARD_SINGLE_INACTIVATE   SIM inserted and inactivated for single SIM mode.
* @retval       COMMON_SIM_CARD_SINGLE_MASTER       Master SIM inserted and activated for DUO mode. Slave SIM is not inserted.
* @retval       COMMON_SIM_CARD_SINGLE_MASTER_INACTIVATE        Master SIM inserted and inactivated for DUO mode. Slave SIM is not inserted.
* @retval       COMMON_SIM_CARD_SINGLE_SLAVE            Slave SIM inserted and activated for DUO mode. Master SIM is not inserted.
* @retval       COMMON_SIM_CARD_SINGLE_SLAVE__INACTIVATE        Slave SIM inserted and inactivated for DUO mode. Master SIM is not inserted.
* @retval       COMMON_SIM_CARD_DUAL_MASTER         Master SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
* @retval       COMMON_SIM_CARD_DUAL_SLAVE          Slave SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
* @retval       COMMON_SIM_CARD_DUAL_BOTH_ACTIVE        Both Master and Slave SIM are inserted and activated for DUO mode.
* @retval       COMMON_SIM_CARD_DUAL_BOTH_INACTIVE  Both Master and Slave SIM are inserted but not activated for DUO mode.
*/
__SLDPM_FREE__ COMMON_SIM_CARD_STATUS_e SrvSimGetSIMCardStatus(void);

/** SrvSimActivateSIMReq
* @brief  Request to activate SIM
* 
* @param[in]      bActivated          Activate/deactivate SIM.
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         Pointer to the callback function of SIMSRV_EVT_ActivateSIMCnf.
*/
void SrvSimActivateSIMReq(boolean bActivated,
                          SIMSRV_SIM_ID_e eSIMID,
                          SrvSimActivateSIMCnfCB pfnCallBack);

/** SrvSimGetSIMInsertStatus
* @brief  Get SIM insert status
* 
* @retval       SIMSRV_SIM_INSERT_UNKNOW        Not receive SIM indication yet.
* @retval       SIMSRV_SIM_INSERT_NOSIM         No SIM inserted for both single mode and DUO mode.
* @retval       SIMSRV_SIM_INSERT_SINGLE        SIM inserted for single SIM mode
* @retval       SIMSRV_SIM_INSERT_MASTER        Master SIM inserted only of DUO mode.
* @retval       SIMSRV_SIM_INSERT_SLAVE         Slave SIM inserted only for DUO mode.
* @retval       SIMSRV_SIM_INSERT_BOTH          Both Master and Slave SIM are inserted for DUO mode.
*/
SIMSRV_SIM_INSERT_e SrvSimGetSIMInsertStatus(void);
#ifdef __QUAD_SIM_DUAL_STANDBY__
/** SrvSimGetSIMRackInsertStatus
* @brief  Get SIM Rack insert status

* @param[out]   p_eAllRackInsertedStaus          the inserted status of each rack.
* SIMSRV_SIM_INSERT_NEW_e
*       SIMSRV_SIM_INSERT_NEW_UNKNOW        Not receive SIM indication yet.
*       SIMSRV_SIM_INSERT         SIM is inserted.
*       SIMSRV_SIM_NOT_INSERT        SIM is not inserted.
*       SIMSRV_SIM_INSERT_UNDEFINESIM         Undefined SIM card ID.

* @retval       MAE_RET_SUCCESS SIMSRV returns IMSI value.
* @retval       MAE_RET_NOT_READY   SIMSRV is not activated. 
* 
*/
MAE_Ret SrvSimGetSIMRackInsertStatus (SIMSRV_SIM_INSERT_NEW_e *p_eAllRackInsertedStaus);

/** SrvSimSelectRack
* @brief  Select Rack.

* @param[in]    eIPId          specific logical SIM ID.
* @param[in]    eRackId        specific rack ID.

* @retval       MAE_RET_SUCCESS SIMSRV returns IMSI value.
* @retval       MAE_RET_BAD_PARAM   Parameters are invalid.
* @retval       MAE_RET_NOT_READY   SIMSRV is not activated. 
* 
*/
MAE_Ret SrvSimSelectRack(SIMSRV_SIM_ID_e eIPId, SIMSRV_SIM_RACK_ID_e eRackId);
#endif
/** SrvSimIsSIMReady
* @brief  Check if SIM is ready.
* 
* @retval TRUE    Both Master and Slave SIM are ready. 
* @retval FALSE   There is at least one SIM not ready.
*/
boolean SrvSimIsSIMReady(void);

/** SrvSimIsSIMIndicationReady
* @brief  Check if RACK indication is ready.
* 
* @retval TRUE    ready. 
* @retval FALSE   not ready.
*/
boolean SrvSimIsSIMIndicationReady(void);

/** SrvSimCancelActivateSIMReq
* @brief  Cancel activate SIM request
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimCancelActivateSIMReq(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimIsSIMChanged
* @brief  Check if the SIM card is inserted when previous powering on.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE    Changed. 
* @retval FALSE   not Changed.
*/
boolean SrvSimIsSIMChanged(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimIsSIMMasterFileReady
* @brief  Check if the Master file is read.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE    ready. 
* @retval FALSE   not ready.
*/
boolean SrvSimIsSIMMasterFileReady(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimShutdown
* @brief  Request to shutdown.
* 
* @param[in]      eCause                  power off cause.
* @param[in]      bSavePowerOnOffCause    Is it necessary to save power off cause?
*/
void SrvSimShutdown(ONOFF_Cause_e eCause, boolean bSavePowerOnOffCause);

/** SrvSimIsSSTFeatureValid
* @brief  Check if specific SST feature is valid.
* 
* @param[in]      eFeature            specific SST feature
* @param[in]      eSIMID              Specific SIM ID.
* @param[out]     pbIsValid           The validation result.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_SUPPORTED       If wrong eFeature.
*/
MAE_Ret SrvSimIsSSTFeatureValid(SIMSRV_SST_FEATURE_e eFeature, SIMSRV_SIM_ID_e eSIMID, boolean *pbIsValid);

/** SrvSimStatusFileReq
* @brief  Request to status of SIM file.
* 
* @param[in]      eFileID             File ID
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         Pointer to the callback function of SIMSRV_EVT_StatusSIMFileCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimStatusFileReq(SIMSRV_SIM_FILE_ID_e     eFileID,
                            SIMSRV_SIM_ID_e          eSIMID,
                            SrvSimStatusSIMFileCnfCB pfnCallBack);

/** SrvSimIsSIMIMSIFileReady
* @brief  Check if SIM IMSI file (SIMSRV_FILE_IMSI, 0x6f07) is ready.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE    ready. 
* @retval FALSE   not ready.
*/
boolean SrvSimIsSIMIMSIFileReady(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimSendSIMCardStatusChangedReq
* @brief  Ask to send SIM card status change event.
*/
void SrvSimSendSIMCardStatusChangedReq(void);

/** SrvSimIgnoreSIMCardStatusChangeInd
* @brief  To ignore SIM card status change indication
*/
void SrvSimIgnoreSIMCardStatusChangeInd(void);

/** SrvSimCancelPINPUKCheckingAndDeactivateSIMReq
* @brief  To cancel PIN/PUK checking and deactivate SIM (do not need to do SrvSimActivateSIMReq set false action).
* 
* @param[in]      eSIMID              Specific SIM ID.
* @param[in]      pfnCallBack         Pointer to the callback function of SIMSRV_EVT_ActivateSIMCnf.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimCancelPINPUKCheckingAndDeactivateSIMReq(SIMSRV_SIM_ID_e eSIMID, SrvSimActivateSIMCnfCB pfnCallBack);

/** SrvSimDeactivateSIMForShutdown
* @brief  Request to deactivate SIM because system is going to shutdown.
* 
* @param[in]      pfnCallBack         Pointer to the callback function for SIMSRV_EVT_DeactivateSIMforShutdownCnf.
*/
void SrvSimDeactivateSIMForShutdown(SrvSimDeactivateSIMforShutdownCnfCB    pfnCallBack);

/** SrvSimIsInitAppFinished
* @brief  Check the status of initializing applet process.
* 
* @param[in]      eInitAppType        the initialized applet type
* 
* @retval TRUE    Finished. 
* @retval FALSE   not finished.
*/
boolean SrvSimIsInitAppFinished(SIMSRV_INITAPP_TYPE_e eInitAppType);

/** SrvSimIsSIMPreviousInserted
* @brief  Check if specific SIM was inserted in previous powering-on time.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE    Inserted. 
* @retval FALSE   not inserted.
*/
boolean SrvSimIsSIMPreviousInserted(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimGetPreviousIMSI
* @brief  Get previous IMSI.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvSimGetPreviousIMSI(u8 *pIMSI, SIMSRV_SIM_ID_e eSIMID);

/** SrvSimSaveIMSItoInsertedIMSIList
* @brief  Request to save SIM to inserted IMSI list.
* 
* @param[in]      eSIMID              Specific SIM ID.
*/
void SrvSimSaveIMSItoInsertedIMSIList(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimIsSIMActive
* @brief  Check if specific SIM is active.
* 
* @param[in]      eSIMID              Specific SIM ID.
* 
* @retval TRUE    Active. 
* @retval FALSE   not active.
*/
boolean SrvSimIsSIMActive(SIMSRV_SIM_ID_e eSIMID);

/** SrvSimGetSIMOPName
* @brief  Get operator name string from SIM
* 
* @param[in]      eFileID             Specific file ID.
* @param[in]      eSIMID              Specific SIM ID.
* @param[out]     pstOPName           Pointer to name string structure.
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_FAILED              If an error happen.
* @retval MAE_RET_NOT_READY           The file is not ready.
* @retval MAE_RET_NOT_SUPPORTED       The request file is not supported.
*/
MAE_Ret SrvSimGetSIMOPName(SIMSRV_SIM_FILE_ID_e    eFileID,
                           SIMSRV_OPName_t         *pstOPName,
                           SIMSRV_SIM_ID_e         eSIMID);
#ifdef __QUAD_SIM_DUAL_STANDBY__
/** SrvSimGetSimInfo
* @brief  Get SIM Info
* 
* @para[out] MaxSimNum             maximun number of SIM card supported
* @para[out] MaxActiveSimNum     maximun number of active SIM card supported

* @retval TRUE    success. 
* @retval FALSE   input strcture is null.
*/
boolean SrvSimGetSIMInfo(SIMSRV_SimInfo_t *ptSimInfo);
#endif
/** SrvSimActivateBothSIMReq
* @brief  Request to activate both SIMs.
* 
* @param[in]      bActivated          Activate or not.
* @param[in]      pfnCallBack         Pointer to the callback function of ISIMSRV_ActivateBothSIMReq.
*/
void SrvSimActivateBothSIMReq(boolean bActivated ,SrvSimActivateSIMCnfCB pfnCallBack);
#ifdef __QUAD_SIM_DUAL_STANDBY__
/** SrvSimDisableSIM
* @brief  Disable SIM to deactivate phbsrv and smssrv.
* 
* @param[in]      eSIMID              Specific SIM ID.
*/
void SrvSimDisableSIM(SIMSRV_SIM_ID_e eSIMID);
#endif

/**
* SrvSimRawIMSIToASCII
* @brief        Transfer raw IMSI BCD format to ASCII string.
*
* @param    pRawIMSI    Pointer of raw IMSI in BCD format.
* @param    pstrASCII   Pointer of return ASCII string and return ASCII string buffer size must no less than (MAX_IMSI_LEN+1).
*
*/
void SrvSimRawIMSIToASCII(u8 *pRawIMSI, u8 *pstrASCII);

/**
* SrvSimGetMccMncFromIMSII
* @brief        Transfer raw IMSI  to mccmnc.
*
* @param    pIMSI    Pointer of raw IMSI.
* @param    pMccMnc   Pointer of return mcc mnc.
*
*/
MAE_Ret SrvSimGetMccMncFromIMSII(u8* pIMSI, MccMnc_t* pMccMnc);
#ifdef __SIM_NO_RSP_HANDLING__
void SrvSimTestSIMNoRspInd(u8 eSIMID);
#endif
#endif  //__MMI_SRV_SIM_H__

/*-----------------------------------------------------*/
