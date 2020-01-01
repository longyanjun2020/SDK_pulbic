/**
* @file    mmi_if_msgbody_def.h
* @version $Id: mmi_if_msgbody_def.h 7361 2008-03-06 02:30:32Z joe.hsu $
* @brief   This file defines the message body of all kind of message.
*
*/
#ifndef __MMI_PS_MSGBODY_H__
#define __MMI_PS_MSGBODY_H__

/* for cc message body */
#include "api_mrl_cc.h"
#ifdef __VT_3G324M__
/* for vtcc message body */
#include "api_mrl_vt.h"
#ifndef __PC_SIMULATOR__
#include "vt_types.h"
#endif
#include "api_cm_itf.h"
#include "cmmmi_sig.h"
#endif
/* for cphs message body */
#include "api_mrl_cphs.h"
/* for mm message body */
#include "api_mrl_rr.h"
#ifdef __3G_RIL_MMI__
#include "api_mrl_ps.h"
#else //__3G_RIL_MMI__
#include "api_mrl_gprs.h"
#endif //__3G_RIL_MMI__
#include "api_mrl_cphs.h"
#include "api_mrl_pwof.h"
/* for phb message body */
#include "api_mrl_phb.h"
/* for sim message body */
#include "api_mrl_sim.h"
#include "api_mrl_sec.h"
#include "api_mrl_stk.h"
/* for sms message body */
#include "api_mrl_sms.h"
#include "api_mrl_cb.h"
/* for ss message body */
#include "api_mrl_ss.h"
/* for timer message body */
//#include "sys_rtk_vmoshi.h"

/* for ss message body */
#include "api_mrl_wcus.h"

typedef union {
	/************************** cc message body ******************************/
	Mrl_CC_CallRefInd_t         MrlCcCallRefInd;
	Mrl_CC_AlertInd_t           MrlCcAlertInd;
	Mrl_CC_DialingRsp_t         MrlCcDialingRsp;
	Mrl_CC_RelInd_t             MrlCcRelInd;    
	Mrl_CC_CHLDRsp_t            MrlCcCHLDRsp;
	Mrl_CC_RingInd_t            MrlCcRingInd;   
	Mrl_CC_AcceptRsp_t          MrlCcAcceptRsp;   
	Mrl_CC_DTMFRsp_t            MrlCcDTMFRsp;        
	Mrl_CC_HangUpRsp_t          MrlCcHangUpRsp;
	Mrl_CC_HangUpOutgoingCallRsp_t	MrlCcHangUpOutgoingCallRsp;
	Mrl_CC_CSSUInd_t               MRLCcCssuInd;
	Mrl_CC_CSSIInd_t               MRLCcCssiInd;
	Mrl_CC_TchInd_t			MRLTchInd;
	Mrl_CC_ConnectInd_t		MRLCcConnectInd;
	Mrl_CC_AbortDtmfRsp_t   MRLCcAbortDtmfRsp;
	Mrl_CC_CallOperRsp_t    MRLCcCallOperRsp;
	Mrl_CC_CLCCRsp_t        MRLCcClccRsp;
    Mrl_CC_ProgInd_t        MrlCcProgressInd;

#ifdef __VT_3G324M__
	/************************** vtcc message body ******************************/
    //RIL
	Mrl_VT_CallRefInd_t     MrlVtCcCallRefInd;
	Mrl_VT_AlertInd_t       MrlVtCcAlertInd;
	Mrl_VT_DialingRsp_t     MrlVtCcDialingRsp;
	Mrl_VT_RelInd_t         MrlVtCcRelInd;    
	Mrl_VT_RingInd_t        MrlVtCcRingInd;   
	Mrl_VT_AcceptRsp_t      MrlVtCcAcceptRsp;   
	Mrl_VT_TchInd_t			MrLVtCcTchInd;
	Mrl_VT_ConnectInd_t		MrLVtCcConnectInd;
    Mrl_VT_ProgInd_t        MrlVtCcProgressInd;
    Mrl_VT_HangupRsp_t      MrlVtCcHangUpRsp;
    Mrl_VT_FallbackRsp_t    MrlVtCcFallbackRsp;    
#ifndef __PC_SIMULATOR__
    //VT
    VtCallStateInd_t        tVtCallStateInd;
    VtUserInputDtmfCnf_t    tVtUserInputDtmfCnf;
    VtChannelOnOffInd_t     tVtChannelOnOffInd;
#endif
    //CM
    MmiCmGetChannelNumberCnf tMmiCmGetChannelNumberCnf;
    MmiCmDisconnectCnf       tMmiCmDisconnectCnf;
    MmiCmDisconnectInd       tMmiCmDisconnectInd;
#endif

	/************************** cphs message body ****************************/
	//need to update, copy form mml_ase.ht
    Mrl_CPHS_WMBNRsp_t	    	    MrlCphsWmbnRsp;	
    Mrl_CPHS_MailBoxRsp_t	   	    MrlCphsMailBoxRsp;
	Mrl_CPHS_WALSRsp_t              MrlCphsWALSRsp;
	Mrl_CPHS_AlternateLineRsp_t     MrlCphsAlternateLineRsp;
	Mrl_CPHS_DivertedCallRsp_t      MrlCphsDivertedCallRsp;
	Mrl_CPHS_WDCIInd_t      		MrlCphsWdciInd;
	Mrl_CPHS_SetRsp_t               MrlCphsSetRsp;
#ifdef __3G_RIL_MMI__
    Mrl_CPHS_MMWIInd_t				MrlCphsMmwiInd;
#else // __3G_RIL_MMI__
	Mrl_CPHS_WVMIInd_t				MrlCphsWvmiInd;
#endif // __3G_RIL_MMI__
	Mrl_CPHS_VoiceMailRsp_t			MrlCphsWMRsp;
    Mrl_CPHS_ReadFunctionalityRsp_t MrlCphsReadFctRsp;
	/************************** mm message body ******************************/
    /*  RR management */
    /* PLMN part */
    Mrl_RR_SelPlmnRsp_t             MrlRrSelPlmnRsp;   
    Mrl_RR_PlmnListCnf_t            MrlRrPlmnListCnf;
    Mrl_RR_UpdatePlmnListRsp_t      MrlRrUpdatePlmnListRsp;
    Mrl_RR_PreferListCnf_t          MrlRrPreferListCnf;
    Mrl_RR_RegModeCnf_t             MrlRrRegisteredPlmnQueCnf;

    /* Network part */
    Mrl_RR_CellInfoRsp_t            MrlRrCellInfoRsp;
    Mrl_RR_AbortRsp_t               MrlRrAbortRsp;
    Mrl_RR_NetworkRegUnsol_t        MrlRrNetwRegUnsol;
    
    Mrl_RR_SignalUnsol_t            MrlRrCsq;
    Mrl_RR_BandSelRsp_t             MrlRrBandSelRsp;
    Mrl_RR_BandCnf_t                MrlRrBandCnf;
    Mrl_RR_NITZUnsol_t              MrlRrNitz;
#ifdef __PROGRAM_TEMP_IMEI_MMI__
	// Store IMEI cnf
	Mrl_RR_Store_IMEICnf_t			MrlRrStoreIMEICnf;
#endif
#ifdef __GPRS_MMI__
    //GPRS realted
#ifdef __3G_RIL_MMI__
    Mrl_PS_AttachCnf_t            MrlPsCgattRsp;
	Mrl_PS_NetworkRegUnsol_t	    MrlPsNetwregUnsol;
    Mrl_PS_MSClassCnf_t		    MrlPsCgclassCnf;
	Mrl_PS_QueryMSClassCnf_t	    MrlPsQueryCgclassCnf;
    Mrl_PS_ActiveSessionCnf_t	    MrlPsActiveCgactCnf;
    Mrl_PS_DeactiveSessionCnf_t	MrlPsDeactiveCgactCnf;
    Mrl_PS_AddPDPCtxCnf_t		    MrlPsAddCgdcontCnf;
    Mrl_PS_DeletePDPCtxCnf_t	    MrlPsDeleteCgdcontCnf;
    Mrl_PS_SetQoSCnf_t		    MrlPsSetCgqreqCgqminCnf;
    Mrl_PS_QueryQoSCnf_t		    MrlPsQueryCgqreqCgqminCnf;
    //WGPRS
    Mrl_PS_CustomizationCnf_t		   MrlPsConfigCnf;
    Mrl_PS_QueryCustomizationCnf_t   MrlPsQueryConfigCnf;
#else //#ifdef __3G_RIL_MMI__
    Mrl_GPRS_AttachCnf_t            MrlGprsCgattRsp;
	Mrl_GPRS_NetworkRegUnsol_t	    MrlGprsNetwregUnsol;
    Mrl_GPRS_MSClassCnf_t		    MrlGprsCgclassCnf;
	Mrl_GPRS_QueryMSClassCnf_t	    MrlGprsQueryCgclassCnf;
    Mrl_GPRS_ActiveSessionCnf_t	    MrlGprsActiveCgactCnf;
    Mrl_GPRS_DeactiveSessionCnf_t	MrlGprsDeactiveCgactCnf;
    Mrl_GPRS_AddPDPCtxCnf_t		    MrlGprsAddCgdcontCnf;
    Mrl_GPRS_DeletePDPCtxCnf_t	    MrlGprsDeleteCgdcontCnf;
    Mrl_GPRS_SetQoSCnf_t		    MrlGprsSetCgqreqCgqminCnf;
    Mrl_GPRS_QueryQoSCnf_t		    MrlGprsQueryCgqreqCgqminCnf;
    //WGPRS
    Mrl_GPRS_CustomizationCnf_t		   MrlGprsWgprsCnf;
    Mrl_GPRS_QueryCustomizationCnf_t   MrlGprsQueryWgprsCnf;
#endif //#ifdef __3G_RIL_MMI__
#endif //__GPRS_MMI__
    /*  POWER ON/OFF     */
	Mrl_PWOF_CfunRsp_t              MrlPwofCfunRsp;
	//Mrl_PWON_CfunReq_t				MrlPwonCfunReq;
	Mrl_PWON_CfunRsp_t				MrlPwonCfunRsp;
#ifndef __3G_RIL_MMI__ // we don't have this in 3D RIL
    Mrl_PWON_WsatpRsp_t             MrlPwonWsatpRsp;
#endif //#ifdef __3G_RIL_MMI__


	/************************** phb message body *****************************/
    Mrl_PHB_QueryStorageStatusCnf_t		MrlPHBQueryStorageStatusCnf;
    Mrl_PHB_ReadEntryCnf_t				MrlPHBReadEntryCnf;
    Mrl_PHB_WriteEntryCnf_t				MrlPHBWriteEntryCnf;
    Mrl_PHB_DeleteEntryCnf_t			MrlPHBDeleteEntryCnf;
    Mrl_PHB_DeleteAllEntryCnf_t			MrlPHBDeleteAllEntryCnf;
    Mrl_PHB_AvoidInitCnf_t				MrlPHBAvoidInitCnf;
    Mrl_PHB_SetVoiceMailNumberCnf_t		MrlPHBSetVoiceMailNumberCnf;
    Mrl_PHB_SetExtendedModeCnf_t		MrlPHBSetExtendedModeCnf;
    Mrl_PHB_SIMEntryReadyInd_t			MrlPHBSIMEntryReadyInd;
    Mrl_PHB_SetFDNModeCnf_t				MrlPHBSetFDNModeCnf;
    Mrl_PHB_FdnAdnSwapReadyInd_t		MrlPHBFdnAdnSwapReadyInd;
	Mrl_PHB_ChecksumInd_t                 MrlPHBChecksumInd;
#ifdef __3G_RIL_MMI__
	Mrl_PHB_HiddenKeyCnf_t			MrlPHBHiddenKeyCnf;
	Mrl_PHB_ReadGroupEntryCnf_t		MrlPHBReadGroupEntryCnf;
	Mrl_PHB_WriteGroupEntryCnf_t		MrlPHBWriteGroupEntryCnf;
#endif //#ifdef __3G_RIL_MMI__
	/************************** rtc message body *****************************/
	//<empty>

	/************************** sim message body *****************************/
	Mrl_SIM_FileStatusCnf_t		MrlSimFileStatusCnf;
	Mrl_SIM_ReadCnf_t			MrlSimReadCnf;
	Mrl_SIM_ErrorInd_t			MrlSimErrorInd;
	Mrl_SIM_LP_ReadCnf_t		MrlSimLpReadCnf;
	Mrl_SIM_LP_QueryCnf_t		MrlSimLpQueryCnf;
	Mrl_SIM_LP_WriteCnf_t		MrlSimLpWriteCnf;

	Mrl_SEC_PINEnableCnf_t	    MrlSecPinEnableCnf;
#ifndef __3G_RIL_MMI__
	Mrl_SEC_PINDisableCnf_t	    MrlSecPinDisableCnf;
#endif //!__3G_RIL_MMI__
	Mrl_SEC_PINVerifyCnf_t	    MrlSecPinVerifyCnf;
	Mrl_SEC_PINUnblockCnf_t	    MrlSecPinUnblockCnf;
	Mrl_SEC_PINChangeCnf_t	    MrlSecPinChangeCnf;
	Mrl_SEC_RemAttpNumRsp_t		MrlSecPinStatusCnf;
	Mrl_SEC_PUK1BlockedInd_t		MrlSecPukBlockInd;
	Mrl_SEC_QueryFacLockCnf_t		MrlSecQueryFacLockCnf;
	
	Mrl_Stlk_SETUP_MENU_Ind_t            MrlStlkSetupMenuInd;
	Mrl_Stlk_DISPLAY_TEXT_Ind_t          MrlStlkDispTextInd;
	Mrl_Stlk_GET_INKEY_Ind_t             MrlStlkGetInkeyInd;
	Mrl_Stlk_GET_INPUT_Ind_t             MrlStlkGetInputInd;
	Mrl_Stlk_SETUP_CALL_Ind_t            MrlStlkSetupCallInd;
	Mrl_Stlk_PLAY_TONE_Ind_t             MrlStlkPlayToneInd;
	Mrl_Stlk_SEL_ITEM_Ind_t              MrlStlkSelItemInd;
	Mrl_Stlk_REFRESH_Ind_t               MrlStlkRefreshInd;
	Mrl_Stlk_SEND_SS_Ind_t               MrlStlkSendSsInd;
	Mrl_Stlk_SEND_SMS_Ind_t              MrlStlkSendSmsInd;
	Mrl_Stlk_SEND_USSD_Ind_t             MrlStlkSendUssdInd;
	Mrl_Stlk_SETUP_EVENT_LIST_Ind_t      MrlStlkSetupEvtListInd;
	Mrl_Stlk_SETUP_IDLE_MODE_TEXT_Ind_t  MrlStlkSetupIdleModeTextInd;
	Mrl_Stlk_SEND_DTMF_Ind_t             MrlStlkSendDtmfInd;
	Mrl_Stlk_LANGUAGE_NOTIFICATION_Ind_t MrlStlkLangNotiInd;
    Mrl_Stlk_LAUNCH_BROWSER_Ind_t MrlStlkLaunchBrowserInd;
	Mrl_Stlk_Error_Ind_t                 MrlStlkErrorInd;

	/************************** sms message body *****************************/
    Mrl_SMS_MoCnf_t					MrlSmsMoCnf;
	Mrl_SMS_ReadCnf_t				MrlSmsReadCnf;
	Mrl_SMS_StoreCnf_t				MrlSmsStoreCnf;
	Mrl_SMS_DelCnf_t				MrlSmsDelCnf;
	Mrl_SMS_SetSCACnf_t				MrlSmsSetScaCnf;
	Mrl_SMS_QuerySCACnf_t			MrlQueryScaCnf;
	Mrl_SMS_ModStatusCnf_t			MrlSmsModStatusCnf;
	Mrl_SMS_QueryStorageCnf_t		MrlSmsQueryStorageCnf;
	Mrl_SMS_SetParamCnf_t			MrlSmsSetParamCnf;
	Mrl_SMS_QueryParamCnf_t			MrlSmsQueryParamCnf;
	Mrl_SMS_SetRecvStorageCnf_t		MrlSetRecvStorageCnf;
    Mrl_SMS_WCMER_Cnf_t             MrlSmsSetStoreMeIndexCnf;
    Mrl_SMS_WCMEC_Cnf_t             MrlSmsSetCapacityCnf;
    Mrl_SMS_StoreMEReq_t            MrlSmsStoreMeReqInd;
	Mrl_SMS_MTInd_t					MrlSmsMtInd;
	Mrl_SMS_CBInd_t					MrlSmsCbInd;
	Mrl_SMS_SRInd_t					MrlSmsSrInd;  

    Mrl_SMS_SyncSetStatusReportCnf_t         MrlSmsSetStatusReportCnf;
	Mrl_SMS_SetMoreMsgCnf_t			MrlSmsSetMoreMsgCnf;
    Mrl_SMS_Event_Ind_t         	MrlSmsEventInd;
	
	//related CB msg
	Mrl_CB_SetCBMICnf_t				MrlCbSetCbmiCnf;
	Mrl_CB_SetRngCBMICnf_t			MrlCbSetRngCbmiCnf;
	Mrl_CB_ActivCnf_t				MrlCbActivCbmiCnf;
	Mrl_CB_ActivRngMIDCnf_t			MrlCbActivRngCbmiCnf;
	Mrl_CB_CBMInd_t					MrlCbInd;    
	//Mrl_SMS_QueryCBMICnf_t		MrlSmsQueryCbmiCnf;
	//Mrl_SMS_SetCBMTypeCnf_t		MrlSmsSetCbmTypeCnf;

	/************************** ss message body ******************************/
    //SS CLCK
    Mrl_SS_CbxCnf_t     MrlSsClckCnf;
    //SS CUSD
    Mrl_SS_UssdInd_t    MrlSsUssdInd;
    Mrl_SS_UssdCnf_t    MrlSsUssdCnf;
    Mrl_SS_UssdNot_t    MrlSsUssdNot;
    Mrl_SS_UssdErr_t    MrlSsUssdErr;
    Mrl_SS_CfxCnf_t     MrlSsCcfcCnf;
    Mrl_SS_CwxCnf_t     MrlSsCcwaCnf;
    Mrl_SS_ClxCnf_t     MrlSsClxCnf;
    Mrl_SS_PwdCnf_t     MrlssChangePwdCnf;
    //SS CUG
    Mrl_SS_CugCnf_t                 MrlSsCcugCnf;
    Mrl_SS_QueryCugCnf_t            MrlSsCcugQueCnf;
    //SS AOC
    Mrl_SS_AoCCnf_t                 MrlSsCaocCnf;
    Mrl_SS_QueryAoCCnf_t            MrlSsCaocQueCnf;
    Mrl_SS_CCMInd_t                 MrlSsCccmInd;
    //SS ACM
    Mrl_SS_ACMCnf_t                 MrlSsCacmCnf;
    //SS AMM
    Mrl_SS_AMMCnf_t                 MrlSsCammCnf;
    //SS PUC
    Mrl_SS_PUCCnf_t                 MrlSsCpucCnf;

    /*AT+WCUS*/
    // Phonebook
    Mrl_WCUS_PHB_QueryStorageInd_t       MrlWcusPhbQueryStorInd;
    Mrl_WCUS_PHB_QueryStorageRsp_t       MrlWcusPhbQueryStorRsp;

    Mrl_WCUS_PHB_SetStorageRsp_t         MrlWcusPhbSetStorRsp;
    Mrl_WCUS_PHB_SetStorageInd_t         MrlWcusPhbSetStorInd;

    Mrl_WCUS_PHB_QueryTotalInd_t         MrlWcusPhbQueryTotalInd;
    Mrl_WCUS_PHB_QueryTotalRsp_t         MrlWcusPhbQueryTotalRsp;
    
    Mrl_WCUS_PHB_QueryUsedInd_t          MrlWcusPhbQueryUsedInd;
    Mrl_WCUS_PHB_QueryUsedRsp_t          MrlWcusPhbQueryUsedRsp;

    Mrl_WCUS_PHB_ReadAllFieldsInd_t      MrlWcusPhbReadAllFieldsInd;
    Mrl_WCUS_PHB_ReadAllFieldsRsp_t      MrlWcusPhbReadAllFieldsRsp;
    
    Mrl_WCUS_PHB_QueryNextIndexInd_t     MrlWcusPhbQueryNextIndexInd;
    Mrl_WCUS_PHB_QueryNextIndexRsp_t     MrlWcusPhbQueryNextIndexRsp;

    Mrl_WCUS_PHB_WriteAllFieldsInd_t     MrlWcusPhbWriteAllFieldsInd;   
    Mrl_WCUS_PHB_WriteAllFieldsRsp_t     MrlWcusPhbWriteAllFieldsRsp;   

    Mrl_WCUS_PHB_DeleteEntryInd_t        MrlWcusPhbDeleteEntryInd;
    Mrl_WCUS_PHB_DeleteEntryRsp_t        MrlWcusPhbDeleteEntryRsp;

    Mrl_WCUS_PHB_QuerySupportFieldInd_t  MrlWcusPhbQuerySupportFieldInd;
    Mrl_WCUS_PHB_QuerySupportFieldRsp_t  MrlWcusPhbQuerySupportFieldRsp;

    
    /*SMS*/
    Mrl_WCUS_SMS_QueryStorageInd_t       MrlWcusSmsQueryStorInd;
    Mrl_WCUS_SMS_QueryStorageRsp_t       MrlWcusSmsQueryStorRsp;

    Mrl_WCUS_SMS_SetStorageRsp_t         MrlWcusSmsSetStorRsp;
    Mrl_WCUS_SMS_SetStorageInd_t         MrlWcusSmsSetStorInd;

    Mrl_WCUS_SMS_QueryTotalInd_t         MrlWcusSmsQueryTotalInd;
    Mrl_WCUS_SMS_QueryTotalRsp_t         MrlWcusSmsQueryTotalRsp;
    
    Mrl_WCUS_SMS_QueryUsedInd_t          MrlWcusSmsQueryUsedInd;
    Mrl_WCUS_SMS_QueryUsedRsp_t          MrlWcusSmsQueryUsedRsp;
    
    Mrl_WCUS_SMS_QueryNextIndexInd_t     MrlWcusSmsQueryNextIndexInd;
    Mrl_WCUS_SMS_QueryNextIndexRsp_t     MrlWcusSmsQueryNextIndexRsp;
    
    Mrl_WCUS_SMS_ReadAllFieldsInd_t      MrlWcusSmsReadAllFieldsInd;
    Mrl_WCUS_SMS_ReadAllFieldsRsp_t      MrlWcusSmsReadAllFieldsRsp;
    
    Mrl_WCUS_SMS_DeleteEntryInd_t        MrlWcusSmsDeleteInd;
    Mrl_WCUS_SMS_DeleteEntryRsp_t        MrlWcusSmsDeleteRsp;
    
    Mrl_WCUS_SMS_WriteAllFieldsInd_t     MrlWcusSmsWriteAllFieldsInd;   
    Mrl_WCUS_SMS_WriteAllFieldsRsp_t     MrlWcusSmsWriteAllFieldsRsp; 
    
    Mrl_WCUS_SMS_QuerySupportFieldInd_t  MrlWcusSmsQuerySupportFieldInd;
    Mrl_WCUS_SMS_QuerySupportFieldRsp_t  MrlWcusSmsQuerySupportFieldRsp;
    
    Mrl_WCUS_SMS_SendInd_t				 MrlWcusSmsSendInd;
    Mrl_WCUS_SMS_SendRsp_t				 MrlWcusSmsSendRsp;

    /*Call Log*/
    Mrl_WCUS_CALLLOG_QueryTotalInd_t     MrlWcusCallLogQueryTotalInd;
    Mrl_WCUS_CALLLOG_QueryTotalRsp_t     MrlWcusCallLogQueryTotalRsp;
    
    Mrl_WCUS_CALLLOG_QueryUsedInd_t      MrlWcusCallLogQueryUsedInd;
    Mrl_WCUS_CALLLOG_QueryUsedRsp_t      MrlWcusCallLogQueryUsedRsp;
    
    Mrl_WCUS_CALLLOG_ReadAllFieldsInd_t  MrlWcusCallLogReadAllFieldsInd;
    Mrl_WCUS_CALLLOG_ReadAllFieldsRsp_t  MrlWcusCallLogReadAllFieldsRsp;

    Mrl_WCUS_CALLLOG_WriteAllFieldsInd_t MrlWcusCallLogWriteAllFieldsInd;   
    Mrl_WCUS_CALLLOG_WriteAllFieldsRsp_t MrlWcusCallLogWriteAllFieldsRsp;   

    Mrl_WCUS_CALLLOG_DeleteEntryInd_t    MrlWcusCallLogDeleteEntryInd;
    Mrl_WCUS_CALLLOG_DeleteEntryRsp_t    MrlWcusCallLogDeleteEntryRsp;

} vm_msgBody_t;

#include "vm_msgt.ht"
//#include "mrl_dual_msg.ht"


#endif /* __MMI_PS_MSGBODY_H__ */
