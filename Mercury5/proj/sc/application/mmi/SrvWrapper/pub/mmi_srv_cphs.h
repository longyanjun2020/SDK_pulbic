/**
* @file    mmi_srv_cphs.h
* @brief
*
*
* @author
* @version $Id:
*/

#ifndef __MMI_SRV_CPHS_H__
#define __MMI_SRV_CPHS_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_cphssrv.h"


typedef void (*SrvCphsQueryMailBoxCB)(void *pThis, MMI_CPHSSRV_Result_e eResult, u32 nSimID);
typedef void (*SrvCphsSetMailBoxNumberCB)(void *pThis, MMI_CPHSSRV_Result_e eResult, u32 nSimID);
typedef void (*SrvCphsReadFunctionalityCB)(void *pThis, MMI_CPHSSRV_Result_e eResult, u32 nSimID);
typedef void (*SrvCphsSetRequestCB)(void *pThis, MMI_CPHSSRV_Result_e eResult, u32 nSimID);


/** SrvCphsSetQueryMailBoxCB
@brief  The interface of Service Client is use to set CB to listen query mail box confirm

@param[in]      pfnCallBack     SrvCphsQueryMailBoxCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetQueryMailBoxCB(SrvCphsQueryMailBoxCB pfnCallBack);


/** SrvCphsSetSetMailBoxNumberCB
@brief  The interface of Service Client is use to set CB to listen set mail box number confirm

@param[in]      pfnCallBack     SrvCphsSetMailBoxNumberCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetSetMailBoxNumberCB(SrvCphsSetMailBoxNumberCB pfnCallBack);

/** SrvCphsSetReadFunctionalityCB
@brief  The interface of Service Client is use to set CB to listen set mail box number confirm

@param[in]      pfnCallBack     SrvCphsReadFunctionalityCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetReadFunctionalityCB(SrvCphsReadFunctionalityCB pfnCallBack);

/** SrvCphsSetSetRequestCB
@brief  The interface of Service Client is use to set CB to listen set mail box number confirm

@param[in]      pfnCallBack     SrvCphsSetRequestCB Call back function point

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetSetRequestCB(SrvCphsSetRequestCB pfnCallBack);

/** SrvCphsQueryVMStatusReq
@brief  The interface is provided APPs to send query_voice_mail_status req

@param[in]      eDualMode       which SIM you want to query

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsQueryVMStatusReq(MAE_DualMode_t eDualMode);

/** SrvCphsQueryLineReq
@brief  The interface is provided APPs to send query_Line_req

@param[in]      eDualMode       which SIM you want to query

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsQueryLineReq(MAE_DualMode_t eDualMode);

/** SrvCphsQueryMailBoxReq
@brief  The interface is provided APPs to send query_mail_box req

@param[in]      eDualMode       which SIM you want to query

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsQueryMailBoxReq(MAE_DualMode_t eDualMode);

/** SrvCphsSetMailBoxNumberReq
@brief  The interface is provided APPs to send set_mail_box_number req

@param[in]    eDualMode         which SIM you want to query
@param[in]    eLine             which Line you want to set
@param[in]    eType             Number type (national/international)
@param[in]    pStrNumber        Number with null terminator

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetMailBoxNumberReq(MAE_DualMode_t eDualMode,
                                   MMI_CPHSSRV_Line_Service_e  eLine,
                                   MMI_CPHS_Type_e             eType,
                                   u8 *pStrNumber);

/** SrvCphsQueryVoiceMailIndicatorReq
@brief  The interface is provided APPs to send read_functionality_req to get the voice mail indicator functionality is activate or deactivate

@param[in]      eDualMode       which SIM you want to query

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsQueryVoiceMailIndicatorReq(MAE_DualMode_t eDualMode);

/** SrvCphsSetVoiceMailIndicatorReq
@brief  The interface is provided APPs to send set_request to activate/deactivate the Voice Mail indicator

@param[in]      eDualMode       which SIM you want to query.
@param[in]      eMode           Activate/Deactivate

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsSetVoiceMailIndicatorReq(MAE_DualMode_t eDualMode, MMI_CPHS_Mode_e  eMode);

/** SrvCphsGetMailBoxNumber
@brief  The interface is provided APPs to retrieve the mailbox number which keep in the cphs service

@param[in]    eDualMode         which SIM you want to query.
@param[in]    eLine             which Line you want to get
@param[in]    pNumber           The pointer of MMI_CPHS_MailBoxNumber_t structure (can't be NULL)
@param[out]   pbSavedInSIM      The pointer of the output boolean bSavedInSIM, if bSavedInSIM is FALSE means that the SIM doesn't support the CPHS and the number is saved in phone

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
@retval MAE_RET_NOT_READY       MailBoxNumber type.
@retval MAE_RET_NOT_SUPPORTED   MailBoxNumber type.
*/
MAE_Ret SrvCphsGetMailBoxNumber(MAE_DualMode_t eDualMode,
                                MMI_CPHSSRV_Line_Service_e eLine,
                                MMI_CPHS_MailBoxNumber_t *pNumber,
                                boolean *pbSavedInSIM);

/** SrvCphsGetVoiceMailIndicatorSetting
@brief  The interface is provided APPs to retrieve the Voice Mail indicator setting (active/deactive)

@param[in]    eDualMode         which SIM that caller has ask to set mailbox number
@param[in]    pbActiveMode      The boolean pointer (can't be NULL)

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            Cphs Srv is already terminated.
*/
MAE_Ret SrvCphsGetVoiceMailIndicatorSetting(MAE_DualMode_t eDualMode, boolean *pbActiveMode);

/** SrvCphsCancelSetMailBoxNumberReq
@brief  The interface is provided APPs to cancel the mailbox number setting request and the setting confirm event.
        if the setting request is already set to ril layer, CPHS service will just cancel the
        confirm event, that means CPHS will release the reference of the request caller

@param[in]    eDualMode         which SIM that caller has ask to set mailbox number
@param[in]    eLine             which SIM that caller has ask to set mailbox number

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_FOUND       Service can't find the related request.
*/
MAE_Ret SrvCphsCancelSetMailBoxNumberReq(MAE_DualMode_t eDualMode, MMI_CPHSSRV_Line_Service_e eLine);

/** SrvCphsCancelSetVoiceMailIndicatorReq
@brief  The interface is provided APPs to cancel the VM indicator setting request and the
        setting confirm event. if the setting request is already set to ril layer,
        CPHS service will just cancel the confirm event, that means CPHS will release
        the reference of the request caller

@param[in]    eDualMode         which SIM that caller has ask to set mailbox number

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_FOUND       Service can't find the related request.
*/
MAE_Ret SrvCphsCancelSetVoiceMailIndicatorReq(MAE_DualMode_t eDualMode);


/*-----------------------------------------------------*/
#endif //__MMI_SRV_CPHS_H__
