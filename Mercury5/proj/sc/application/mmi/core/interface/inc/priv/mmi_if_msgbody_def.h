/**
* @file    mmi_if_msgbody_def.h
* @version $Id: mmi_if_msgbody_def.h 39944 2009-09-10 18:01:37Z sho.ding $
* @brief   This file defines the message body of all kind of message.
*
*/
#ifndef __MMI_IF_MSGBODY_DEF_H__
#define __MMI_IF_MSGBODY_DEF_H__

/* for acc message body */
#include "dev_acc_pub_types.h"
#include "dev_acc_pub_api.h"
/* for camera message body */
/* for camcorder message body */
/* for cc message body */
//#include "api_mrl_cc.h"
/* for cphs message body */
//#include "api_mrl_cphs.h"
/* for keypad message body */
#include "mdl_keypad_pub.h"
#include "vm_kbd.h"
/* for mm message body */
//#include "api_mrl_rr.h"
//#include "api_mrl_gprs.h"
//#include "api_mrl_cphs.h"
//#include "api_mrl_pwof.h"
/* for phb message body */
//#include "api_mrl_phb.h"
/* for rtc message body */
//<empty>
/* for sim message body */
//#include "api_mrl_sim.h"
//#include "api_mrl_sec.h"
//#include "api_mrl_stk.h"
/* for sms message body */
//#include "api_mrl_sms.h"
//#include "api_mrl_cb.h"
/* for ss message body */
//#include "api_mrl_ss.h"
/* for timer message body */
#ifdef __BLUETOOTH_MMI__
#include "drv_bt_api.h"

#ifdef __BLUETOOTH_OBEX_MMI__
#include "mmi_bt_msgdef.h"
#endif //__BLUETOOTH_OBEX_MMI__

#endif //__BLUETOOTH_MMI__

/* for USB message body */
#include "ABL_Usb.h"

/* for gpd message body */
#include "mdl_gpd_pub.h"

#include "sys_rtk_Vmoshi.h"
#include "mmi_media_msgdef.h"
#include "mmi_codec_msgdef.h"
#include "mmi_vfs_msgdef.h"
#include "mmi_camera_msgdef.h"
#include "mmi_gsensor_msgdef.h"
#ifdef __ATV_MMI__
#include "mmi_atv_msgdef.h"
#endif //__ATV_MMI__

#ifdef __APP_MMI_FM_RADIO__
#include "mmi_fmr_msgdef.h"
#endif //__APP_MMI_FM_RADIO__

#include "mmi_emu_msgdef.h"
#include "mmi_sys_msgdef.h"
#include "mmi_gps_msgdef.h"
#include "mmi_wlan_msgdef.h"
#include "mmi_atcmd_msgdef.h"

#ifdef __MAP_MMI_LBS__
#include "mmi_lbs_msgdef.h"
#endif

#ifdef __PROXIMITY_SENSOR_MMI__
#include "mmi_proximity_sensor_msgdef.h"
#endif

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
#include "mdl_cpu_pub.h"
#endif

#ifdef __TOUCH_SCREEN_MMI__
/* for touch screen message body */
//The definition of structures are copied from "Touchscreen_msg.h"
#include "mdl_touchscreen_msg_pub.h"
/*#define MAX_TOUCH_FINGER  2

typedef struct
{
    u16 Row;
	u16 Col;
} vm_TouchPoint_t;

typedef struct
{
    u8 nFunction;
	u8 nKeyMode;
	u8 nFingerNum;
	vm_TouchPoint_t pPoint[MAX_TOUCH_FINGER];
} MdlTouchScreenInfo_t;

typedef struct
{
    u16     x;
    u16     y;
    u16     pressure;
    u16     mode;
} MdlTouchScreenData_t;*/
#endif //__TOUCH_SCREEN_MMI__

typedef struct
{
	ABL_UsbErrCode_e eUsbResult;
	ABL_UsbAttach_e eUsbAttach;
} vm_UsbReturn_t;

typedef union {
	/************************** acc message body *****************************/
	dev_accPlugInd_t PlugInd;

	/************************** camera message body **************************/

	/************************** keypad message body **************************/
	VKEYCODE         vcode;
	vm_kbdInd_t      scancode;

	/************************** rtc message body *****************************/
	//<empty>

	/************************** timer message body ***************************/
	vm_osTimerMsgBody_t vm_osTimerMsgBody;

#ifdef __TOUCH_SCREEN_MMI__
	/************************** timer message body ***************************/
	//need to update from "Touchscreen_msg.h"
	MdlTouchScreenData_t   tsData;
	MdlTouchScreenInfo_t   tsInfo;
#endif //__TOUCH_SCREEN_MMI__

#ifdef __BLUETOOTH_MMI__
	/************************** bluetooth message body ***************************/
	//need to update from "Api_bt_mmi.h"
	BT_PowerOnOffCnf_t   	BtPowerOnOffCnf;
	BT_InquiryInd_t		BtInquiryInd;
	BT_InquiryCnf_t		BtInquiryCnf;
	BT_NameQueryCnf_t	BtNameQueryCnf;
	BT_PinCodeReq_t		BtPinCodeReq;
	BT_ACLLinkInd_t		BtACLLinkInd;
	BT_ACLLinkCnf_t		BtACLLinkCnf;
	BT_PairDoneInd_t		BtPairDoneInd;
	BT_DeleteDeviceCnf_t	BtDeleteDeviceCnf;
	BT_SetLocalNameCnf_t	BtSetLocalNameCnf;
	BT_SetDiscoveryCnf_t	BtSetDiscoveryCnf;

	BT_AudioLinkInd_t		BtAudioLinkInd;
	BT_AudioLinkCnf_t		BtAudioLinkCnf;
	BT_AudioCallInd_t		BtAudioCallInd;
	BT_AudioCallCnf_t		BtAudioCallCnf;
	BT_AudioVolInd_t		BtAudioVolInd;
	BT_HF_ATCmdInd_t	BtHfATCmdInd;
#ifdef __BLUETOOTH_DRV_MSTAR_ACRUX2__
	BT_PinPonTestRsp_t	BtPinPonTestRsp;
#endif
#ifdef __BLUETOOTH_OBEX_MMI__
	BT_OBEXLinkCnf_t		BtObexLinkCnf;
	BT_SendFileCnf_t		BtObexSendCnf;
	BT_RecvFileReq_t		BtObexRecvInd;
	BT_RecvFileCnf_t		BtObexRecvCnf;
	BT_TransStatusInd_t		BtObexTransStatusInd;
	BT_FileWriteInd_t		BtObexFileWriteInd;
	BT_WriteFileInd_t		BtObexWriteFileInd;
#endif //__BLUETOOTH_OBEX_MMI__
	BT_ChipResetReq_t		BtChipResetInd;
	BT_RfTestModeCnf_t      BtRfTestModeCnf;
#ifdef __BLUETOOTH_A2DP_MMI__
    BT_A2dpLinkCnf_t        BtA2dpLinkCnf;
    BT_A2dpLinkInd_t        BtA2dpLinkInd;
    BT_A2dpActionCnf_t      BtA2dpActionCnf;
    BT_StatusChangedInd_t   BtA2dpStatusChangedInd;//From ResMgr
    BT_UnblockBTInd_t       BtA2dpUnblockBTInd; //From BT Task
#ifdef __BLUETOOTH_AVRCP_MMI__
	BT_AvrcpActionInd_t     BtAvrcpActionInd;
    BT_AvrcpActionCnf_t     BtAvrcpActionCnf;
#endif /* __BLUETOOTH_AVRCP_MMI__ */
#endif /* __BLUETOOTH_A2DP_MMI__ */

#ifdef __BLUETOOTH_RDA_STACK__
	// __BLUETOOTH_DRV_RDA5868__
	BT_RdaEvent_t           BtRdaEven;
	BT_SdpServiceCnf_t      BtSdpServiceCnf;
#else
	// __BLUETOOTH_DRV_TI6300__
      #if !defined(__BLUETOOTH_DRV_MSTAR_ACRUX2__)
      BT_TIEvent_t            BtTIEven;
      #endif
      BT_SdpServiceCnf_t      BtSdpServiceCnf;
#endif  /* __BLUETOOTH_RDA_STACK__ */

#if defined (__BLUETOOTH_DRV_MSTAR__)
    BT_AudioPktTypInd_t     BtAudioPkyTypInd;
    BT_AudioLinkConnInd_t   BtAudioLinkConnInd;
    BT_AclModeChangeInd_t   BtAclModeChangeInd;
#endif /* #if defined(__BLUETOOTH_DRV_MSTAR__) */

#endif //__BLUETOOTH_MMI__

	/************************** media message body **************************/
	mmi_mediaMsgBody_t		mediaRsp;

	/************************** camera message body **************************/
	CamMsgBody_t			camRsp;
	/************************** codec message body **************************/
	mmi_CodecMsgBody_t      CodecRsp;

	/************************** usb message body **************************/
	/* USB START */
	vm_UsbReturn_t			tUsbReturn;
	/* USB END */

	/************************** gpd message body **************************/
	MdlGpdAcsInfo_t		stGpdAcsInfo;
	mmi_VfsMsgBody_t		vfsRsp;
	mmi_GpdGsensorCbMsgBody_t		gSensorCnf;
	mmi_GpdGsensorNotifyMsgBody_t	gSensorInd;
#ifdef __PROXIMITY_SENSOR_MMI__
	mmi_GpdPaiSensorNotifyMsgBody_t	gPaiSensorInd;
#endif

#ifdef __ATV_MMI__
	AtvMsgBody_t			atvRsp;
#endif //__ATV_MMI__

#ifdef __APP_MMI_FM_RADIO__
	FMRMsgBody_t		    fmrRsp;
	FMRResMgrMsgBody_t	    tFMRResMgrInd;
#endif //__APP_MMI_FM_RADIO__
	mmi_EmuMsgBody_t        tEmuCnf;
	mmi_EmuResMgrMsgBody_t	tEmuResMgrInd;
	mmi_EMANotify_t			emaNotify;

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
    MdlCpuReportData_t      ReportData;
#endif

	/************************** gps message body **************************/
	mmi_GpsMsgBody_t			gpsRsp;

#ifdef __MAP_MMI_LBS__
       mmi_LbsMsgBody_t                     lbsRsp;
#endif
	/************************** content db message body **************************/
    /************************** WLAN message body *************************/
    mmi_WLANMsgBody_t       wlanRsp;
    mmi_WLANMsgBSSData_t    wlanBSSRsp;
    mmi_WLANMsgAQUVer_t     wlanAQUVerRsp;
    mmi_WLANMsgEMData_t     wlanEMRsp;

    mmi_AtCmdIndMsgBody_t   tAtCmdInd;

#ifdef  __TOUCH_SCREEN_FWUPDATE_MMI__
    MdlTouchScreenFwUpdate_t tsfwupdate;
#endif	
} vm_msgBody_t;

#include "vm_msgt.ht"


#endif /* __MMI_IF_MSGBODY_DEF_H__ */

