/**
* @file    mmi_srv_ss.h
* @brief   SS Service provide APIs for the supplimental service control purpose. 
*          For Example, to activate/de-activate call-divert, to activate/de-activate call-barring, to send USSD settings, and etc.
*
*/

#ifndef __MMI_SRV_SS_H__
#define __MMI_SRV_SS_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_sssrv.h"

/* callback function type */

/** SrvSsCallDivertCB
* @brief         The callback function to confirm the call-divert request. (triggered by SSSRV_EVT_CFXCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pCallDivert            The confirm information of the request.
*/
typedef void (*    SrvSsCallDivertCB)(void *pThis, SSSRV_CallDivertCnf_t *pCallDivert);

/** SrvSsCallBarringCB
* @brief         The callback function to confirm the call-barring request. (triggered by SSSRV_EVT_CBXCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pCallBarring           The confirm information of the request.
*/
typedef void (*    SrvSsCallBarringCB)(void *pThis, SSSRV_CallBarringCnf_t *pCallBarring);

/** SrvSsCallWaitingCB
* @brief         The callback function to confirm the call-waiting request. (triggered by SSSRV_EVT_CWXCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pCallWaiting           The confirm information of the request.
*/
typedef void (*    SrvSsCallWaitingCB)(void *pThis, SSSRV_CallWaitingCnf_t *pCallWaiting);

/** SrvSsLineIdentityCB
* @brief         The callback function to confirm the line-identity request. (triggered by SSSRV_EVT_CLXCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pLineIdentity          The confirm information of the request.
*/
typedef void (*    SrvSsLineIdentityCB)(void *pThis, SSSRV_ClxCnf_t *pLineIdentity);

/** SrvSsUSSDCB
* @brief         The callback function to confirm the USSD request. (triggered by SSSRV_EVT_USSDCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pUSSD                  The confirm information of the request.
*/
typedef void (*    SrvSsUSSDCB)(void *pThis, SSSRV_USSDCnf_t *pUSSD);

/** SrvSsUSSDIndCB
* @brief         The callback function to confirm the USSD indication. (triggered by SSSRV_EVT_USSDInd)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pUSSDInd               The indication information of USSD.
*/
typedef void (*    SrvSsUSSDIndCB)(void *pThis, SSSRV_USSDInd_t *pUSSDInd);

/** SrvSsUSSDErrCB
* @brief         The callback function to confirm the USSD error indication. (triggered by SSSRV_EVT_USSDErr)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pUSSDInd               The error indication information of USSD.
*/
typedef void (*    SrvSsUSSDErrCB)(void *pThis, SSSRV_USSDErr_t *pUSSDErr);

/** SrvSsBarringPwdChangeCB
* @brief         The callback function to confirm the call-barring-password-change request. (triggered by SSSRV_EVT_PWDCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    eRslt                  The result of the request.
*/
typedef void (*    SrvSsBarringPwdChangeCB)(void *pThis, MMI_SSSRV_SS_Result_e eRslt);

/** SrvSsSetClosedUserGroupCB
* @brief         The callback function to confirm the set-CUG request. (triggered by SSSRV_EVT_SetCUGCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    eRslt                  The result of the request.
*/
typedef void (*    SrvSsSetClosedUserGroupCB)(void *pThis, MMI_SSSRV_SS_Result_e eRslt);

/** SrvSsQueryClosedUserGroupCB
* @brief         The callback function to confirm the query-CUG request. (triggered by SSSRV_EVT_QueCUGCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pQueCUG                The confirm information of the request.
*/
typedef void (*    SrvSsQueryClosedUserGroupCB)(void *pThis, SSSRV_UserGroupQueCnf_t *pQueCUG);

/** SrvSsSetAdviseOfChargeCB
* @brief         The callback function to confirm the set-AoC request. (triggered by SSSRV_EVT_SetAOCCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pAdviseOfCharge        The confirm information of the request.
*/
typedef void (*    SrvSsSetAdviseOfChargeCB)(void *pThis, SSSRV_AOCCnf_t *pAdviseOfCharge);

/** SrvSsQueAdviseOfChargeCB
* @brief         The callback function to confirm the query-AoC request. (triggered by SSSRV_EVT_QueAOCCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pAdviseOfCharge        The confirm information of the request.
*/
typedef void (*    SrvSsQueAdviseOfChargeCB)(void *pThis, SSSRV_AOCQueCnf_t *pAdviseOfCharge);

/** SrvSsAccumulatedCallMeterCB
* @brief         The callback function to confirm the accumulated-call-meter request. (triggered by SSSRV_EVT_ACMCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pAccumulatedCallMeter  The confirm information of the request.
*/
typedef void (*    SrvSsAccumulatedCallMeterCB)(void *pThis, SSSRV_ACMCnf_t *pAccumulatedCallMeter);

/** SrvSsAccumulatedCallMeterMaxCB
* @brief         The callback function to confirm the accumulated-call-meter-maximum-value request. (triggered by SSSRV_EVT_AMMCnf)
*
* @param[out]    pThis                  The pointer of the applet.
* @param[out]    pAccumulatedCallMeterMax   The confirm information of the request.
*/
typedef void (*    SrvSsAccumulatedCallMeterMaxCB)(void *pThis, SSSRV_ACMMaxCnf_t *pAccumulatedCallMeterMax);

/** SrvSsPriceUnitCB
* @brief         The callback function to confirm the price-unit request. (triggered by SSSRV_EVT_PUCCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pPriceUnit         The confirm information of the request.
*/
typedef void (*    SrvSsPriceUnitCB)(void *pThis, SSSRV_PUCCnf_t *pPriceUnit);


/* APIs */

/** SrvSsSetUSSDIndCB
* @brief  Register/deregister a callback function to listen to USSD indication
* 
* @param[in]      pfnCallBack         SrvSsUSSDIndCB, a callback function pointer
*/
void SrvSsSetUSSDIndCB(SrvSsUSSDIndCB pfnCallBack);


/** SrvSsSetUSSDErrCB
* @brief  Register/deregister a callback function to listen to USSD Err indication
* 
* @param[in]      pfnCallBack         SrvSsUSSDErrCB, a callback function pointer
*/
void SrvSsSetUSSDErrCB(SrvSsUSSDErrCB pfnCallBack);


/** SrvSsCallDivertReq
* @brief  Activate/de-activate/query/erase call-divert settings.
* 
* @param[in]      pRegData            Call-divert request data.
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSCallDivertCB   SrvSsCallDivertCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a call divert request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsCallDivertReq(SSSRV_CallDivertReq_t *pReqData,
                           MAE_DualMode_t        eDualMode,
                           SrvSsCallDivertCB     pfnSSCallDivertCB);

/** SrvSsCallBarringReq
* @brief  Activate/de-activate/query/erase call-barring settings.
* 
* @param[in]      pRegData            Change-barring request data.
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSCallDivertCB   SrvSsCallBarringCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a call barring request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsCallBarringReq(SSSRV_CallBarringReq_t  *pReqData,
                            MAE_DualMode_t          eDualMode,
                            SrvSsCallBarringCB      pfnSSCallBarringCB);

/** SrvSsChangeBarringPwdReq
* @brief  Change call-barring password
* 
* @param[in]      pRegData                    Change barring password request data.
* @param[in]      eDualMode                   DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSBarringPwdChangeCB     SrvSsBarringPwdChangeCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a change barring password request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsChangeBarringPwdReq(SSSRV_ChangeBarringPwdReq_t    *pReqData,
                                 MAE_DualMode_t                 eDualMode,
                                 SrvSsBarringPwdChangeCB        pfnSSBarringPwdChangeCB);

/** SrvSsCallWaitingReq
* @brief    Activate/de-activate/query/erase call-waiting settings.
* 
* @param[in]      pRegData            Call-waiting request data.
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSCallWaitingCB  SrvSsCallWaitingCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a call waiting request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsCallWaitingReq(SSSRV_CallWaitingReq_t  *pReqData,
                            MAE_DualMode_t          eDualMode,
                            SrvSsCallWaitingCB      pfnSSCallWaitingCB);

/** SrvSsUSSDReq
* @brief    Send a USSD string to network.
* 
* @param[in]      pRegData            USSD request data.
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSUSSDCB         SrvSsUSSDCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a USSD request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
* @return MAE_RET_NOT_SUPPORTED       If no SIM activated.
*/
MAE_Ret SrvSsUSSDReq(SSSRV_USSDReq_t *pReqData, MAE_DualMode_t eDualMode, SrvSsUSSDCB pfnSSUSSDCB);

/** SrvSsUSSDCancelReq
* @brief  Cancel the current USSD request.
* 
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsUSSDCancelReq(MAE_DualMode_t eDualMode);

/** SrvSsSetUserGroupReq
* @brief    Set closed-user-group information.
* 
* @param[in]      pRegData                    User group request data.
* @param[in]      eDualMode                   DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSSetClosedUserGroupCB   SrvSsSetClosedUserGroupCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a CUG set request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsSetUserGroupReq(SSSRV_UserGroupReq_t       *pReqData,
                             MAE_DualMode_t             eDualMode,
                             SrvSsSetClosedUserGroupCB  pfnSSSetClosedUserGroupCB);

/** SrvSsQueryUserGroupReq
* @brief    Query the current closed-user-group information.
* 
* @param[in]      eDualMode                       DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSQueryClosedUserGroupCB     SrvSsQueryClosedUserGroupCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a CUG query request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsQueryUserGroupReq(MAE_DualMode_t eDualMode, SrvSsQueryClosedUserGroupCB pfnSSQueryClosedUserGroupCB);

/** SrvSsSetAdviseOfChargeReq
* @brief    Set advise-of-charge information.
* 
* @param[in]      eReqType                    Requested operation.
* @param[in]      eDualMode                   DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSSetAdviseOfChargeCB    SrvSsSetAdviseOfChargeCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a AoC set request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsSetAdviseOfChargeReq(MMI_SSSRV_AOC_ReqType_e eReqType,
                                  MAE_DualMode_t eDualMode,
                                  SrvSsSetAdviseOfChargeCB pfnSSSetAdviseOfChargeCB);

/** SrvSsQueryAdviseOfChargeReq
* @brief    Query the current advise-of-charge information.
* 
* @param[in]      eDualMode                   DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSQueAdviseOfChargeCB    SrvSsQueAdviseOfChargeCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a AoC query request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsQueryAdviseOfChargeReq(MAE_DualMode_t eDualMode, SrvSsQueAdviseOfChargeCB pfnSSQueAdviseOfChargeCB);

/** SrvSsAccumulatedCallMeterReq
* @brief    Query/reset the advise-of-charge related information for accumulated-call-meter value in the SIM file.
* 
* @param[in]      pReqData                        AccumulatedCallMeter request data.
* @param[in]      eDualMode                       DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSAccumulatedCallMeterCB     SrvSsAccumulatedCallMeterCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a ACM request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsAccumulatedCallMeterReq(SSSRV_ACMReq_t *pReqData,
                                     MAE_DualMode_t eDualMode,
                                     SrvSsAccumulatedCallMeterCB   pfnSSAccumulatedCallMeterCB);

/** SrvSsAccumulatedCallMeterMaxReq
* @brief    Query/update the advise-of-charge related information for accumulated-call-meter maximum value in the SIM file.
* 
* @param[in]      pReqData                        ACMMax request data.
* @param[in]      eDualMode                       DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSAccumulatedCallMeterMaxCB  SrvSsAccumulatedCallMeterMaxCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a ACMMax request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsAccumulatedCallMeterMaxReq(SSSRV_ACMMaxReq_t *pReqData,
                                        MAE_DualMode_t eDualMode,
                                        SrvSsAccumulatedCallMeterMaxCB pfnSSAccumulatedCallMeterMaxCB);

/** SrvSsPriceUnitReq
* @brief    Set/query price-per-unit and currency settings in the SIM file.
* 
* @param[in]      pReqData            price per unit and currency request data
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSPriceUnitCB    SrvSsPriceUnitCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a PUC request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsPriceUnitReq(SSSRV_PUCReq_t *pReqData, MAE_DualMode_t eDualMode, SrvSsPriceUnitCB  pfnSSPriceUnitCB);

/** SrvSsActionCancelReq
* @brief    Cancel the previous request.
* 
* @param[in]      eReqType            SS request type
* 
* @retval MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvSsActionCancelReq(SSSRV_REQUEST_TYPE_e eReqType);

/** SrvSsLineIdentityQueryReq
* @brief    Query line-identity request.
* 
* @param[in]      eCIType			  SS CI Request type
* @param[in]      eDualMode           DualSIM ID: DUAL_MASTER/DUAL_SLAVE
* @param[in]      pfnSSLineIdentityCB SrvSsLineIdentityCB, a callback function pointer
* 
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_BUSY                If there is already a Line Identity request in queue / SSSrv is terminated.
* @retval MAE_RET_BAD_PARAM           If wrong parameters. 
* @return MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvSsLineIdentityQueryReq(MMI_SSSRV_CI_ReqType_e eCIType,
                                  MAE_DualMode_t eDualMode,
                                  SrvSsLineIdentityCB pfnSSLineIdentityCB);


/*-----------------------------------------------------*/
#endif //__MMI_SRV_SS_H__
