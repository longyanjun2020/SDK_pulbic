PATH_H = \
    $(PATH_acc_inc)/pub \
    $(PATH_app)/CalendarApp/inc \
    $(PATH_app)/DialogApp/inc \
    $(PATH_app)/MessageViewerApp/inc \
    $(PATH_AppLauncher)/inc \
    $(PATH_audio)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_dynldr)/pub \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hopper)/pub \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_mae)/pub \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_mserv)/inc \
    $(PATH_mserv)/itf \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_ril_itf) \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
	$(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
    $(PATH_sim)/itf \
    $(PATH_srv)/AccessorySrv/inc/priv \
    $(PATH_srv)/AlarmSrv/inc/priv \
    $(PATH_srv)/AliveWdgSrv/inc/priv \
    $(PATH_srv)/AtSyncSrv/inc/priv \
    $(PATH_srv)/AudioPlayerSrv/inc/priv \
    $(PATH_srv)/AudioRecorderSrv/inc/priv \
    $(PATH_srv)/AudioSrv/inc/priv \
	$(PATH_srv)/BaseSrv/inc/priv \
    $(PATH_srv)/BtObexSrv/inc/priv \
    $(PATH_srv)/BtSrv/inc/priv \
    $(PATH_srv)/CallLogsrv/inc/priv \
    $(PATH_srv)/CameraSrv/inc/priv \
    $(PATH_srv)/CbSrv/inc/priv \
    $(PATH_srv)/CcSrv/inc/priv \
    $(PATH_srv)/ClipBoardSrv/inc/priv \
    $(PATH_srv)/ClSrv/inc/priv \
    $(PATH_srv)/CodecSrv/inc/priv \
    $(PATH_srv)/CoreSrv/inc/priv \
    $(PATH_srv)/CountDownTimerSrv/inc/priv \
    $(PATH_srv)/CphsSrv/inc/priv \
    $(PATH_srv)/DialogSrv/inc/priv \
    $(PATH_srv)/DrmAgentSrv/inc/priv \
    $(PATH_srv)/EmailSrv/inc/priv \
    $(PATH_srv)/EvtCenterSrv/inc/priv \
    $(PATH_srv)/FdnSrv/inc/priv \
    $(PATH_srv)/FmRadioSrv/inc/priv \
    $(PATH_srv)/GpsSrv/inc/priv \
    $(PATH_srv)/HashmapSrv/inc/priv \
    $(PATH_srv)/inc \
    $(PATH_srv)/JavaSrv/inc/priv \
    $(PATH_srv)/MessageContentSrv/inc/priv \
    $(PATH_srv)/MessageManagerSrv/inc/priv \
    $(PATH_srv)/MessageOrganizationSrv/inc/priv \
    $(PATH_srv)/mmi_cfgsrv/inc/priv \
    $(PATH_srv)/MmSrv/inc/priv \
    $(PATH_srv)/MmsSrv/inc/priv \
    $(PATH_srv)/MmsTransactionSrv/inc/priv \
    $(PATH_srv)/ObjProcessingSrv/inc/priv \
    $(PATH_srv)/PhbSrv/inc/priv \
    $(PATH_srv)/PlayListSrv/inc/priv \
    $(PATH_srv)/PreviewLine2Srv/inc/priv \
    $(PATH_srv)/PrivateprotectSrv/inc/priv \
    $(PATH_srv)/ProfileSrv/inc/priv \
    $(PATH_srv)/pub \
	$(PATH_srv)/SchedulerSrv/inc/priv \
	$(PATH_srv)/SchedulerSrv/inc \
    $(PATH_srv)/ShortcutsSrv/inc/priv \
    $(PATH_srv)/SimSrv/inc/priv \
    $(PATH_srv)/SmsSrv/inc/priv \
    $(PATH_srv)/SmsTransactionSrv/inc/priv \
    $(PATH_srv)/SocketSrv/inc/priv \
    $(PATH_srv)/SsSrv/inc/priv \
    $(PATH_srv)/StatusBarSrv/inc/priv \
    $(PATH_srv)/StkSrv/inc/priv \
    $(PATH_srv)/TouchShortcutSrv/inc/priv \
    $(PATH_srv)/TtsSrv/inc/priv \
    $(PATH_srv)/UsbSrv/inc/priv \
    $(PATH_srv)/VCalParserSrv/inc/priv \
    $(PATH_srv)/VCalStoreSrv/inc/priv \
    $(PATH_srv)/VendorSrv/inc/priv \
    $(PATH_srv)/VideoPlayerSrv/inc/priv \
    $(PATH_srv)/VtCcSrv/inc/priv \
    $(PATH_srv)/WlanSrv/inc/priv \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_utility)/inc \
    $(PATH_vfs)/pub \
    $(PATH_drm_vfs)/pub \
    $(PATH_drm_util)/pub \
    $(PATH_wap)/itf \
    $(PATH_http)/pub \
    $(PATH_rtsp)/pub \
    $(PATH_widget)/pub \
    $(PATH_avp)/pub
MMI_PATH_H =
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
    abi_headers_srv.c \
	mmi_accessorysrv.c \
	mmi_alarmsrv.c \
	mmi_alivewdgsrv.c \
	mmi_atsyncsrv.c \
	mmi_atsyncsrv_todolist.c \
	mmi_basesrv.c \
	mmi_btobexsrv.c \
	mmi_btobexsrv_sm.c \
	mmi_btsrv.c \
	mmi_btsrv_atcmd.c \
	mmi_btsrv_sm.c \
	mmi_btsrv_util.c \
	mmi_calllogsrv.c \
	mmi_calllogsrv_hsmgr.c \
	mmi_calllogsrv_sm.c \
	mmi_camerasrv.c \
	mmi_cbsrv.c \
	mmi_cbsrv_sm.c \
	mmi_ccsrv.c \
	mmi_ccsrv_crunch.c \
	mmi_ccsrv_ctmgr.c \
	mmi_ccsrv_sm.c \
	mmi_ccsrv_util.c \
	mmi_clsrv.c \
	mmi_vtccsrv.c \
	mmi_vtccsrv_crunch.c \
	mmi_vtccsrv_ctmgr.c \
	mmi_vtccsrv_sm.c \
	mmi_vtccsrv_util.c \
	mmi_cfgsrv.c \
	mmi_cfgsrv_citem_file_table.c \
	mmi_cfgsrv_master_reset_table.c \
	mmi_cfgsrv_mitem_allow_mr_table.c \
	mmi_cfgsrv_mitem_info_table.c \
	mmi_cfgsrv_mitem_notallow_mr_table.c \
	mmi_cfgsrv_sitem_table.c \
	mmi_clipboardsrv.c \
	mmi_coresrv.c \
	mmi_coresrv_custom.c \
	mmi_countdowntimersrv.c \
	mmi_cphssrv.c \
	mmi_cphssrv_sm.c \
	mmi_dialogsrv.c \
	mmi_drmagentsrv.c \
	mmi_drmagentsrv_util.c \
	mmi_evtcentersrv.c \
	mmi_evtcentersrv_logmsg.c\
	mmi_evtcentersrv_dialog.c\
	mmi_evtcentersrv_battery.c\
	mmi_evtcentersrv_accessory.c\
	mmi_evtcentersrv_alarm.c\
	mmi_evtcentersrv_calllog.c\
	mmi_evtcentersrv_mics.c\
	mmi_evtcentersrv_media.c\
	mmi_evtcentersrv_model.c\
	mmi_evtcentersrv_sms_mms.c\
	mmi_evtcentersrv_timer.c\
	mmi_evtcentersrv_bt.c\
	mmi_fdnsrv.c \
	mmi_fdnsrv_sm.c \
	mmi_fmradiosrv.c \
	mmi_gpssrv.c \
	mmi_hashmapsrv.c \
	mmi_javasrv.c \
	mmi_javasrv_sm.c \
	mmi_mediasrv_common.c \
	mmi_messagecontentsrv.c \
	mmi_messagemanagersrv.c \
	mmi_messageorganizationsrv.c \
	mmi_mmsrv.c \
	mmi_mmsrv_crunch.c \
	mmi_mmsrv_custom.c \
	mmi_mmsrv_sm.c \
	mmi_mmsrv_util.c \
	mmi_mmssrv.c \
	mmi_mmssrv_sm.c \
	mmi_mmstransactionsrv.c \
	mmi_audioplayersrv.c \
	mmi_objprocessingsrv.c \
	mmi_objprocessingsrv_sm.c \
	mmi_phbsrv_data_handle.c \
	mmi_phbsrv_utility.c \
	mmi_phbsrv.c \
	mmi_phbsrv_sm.c \
	mmi_playlistsrv.c \
	mmi_previewline2srv.c \
	mmi_privateprotectsrv.c \
	mmi_profilesrv.c \
	mmi_profilesrv_util.c \
	mmi_schedulersrv.c \
    mmi_schedulersrv_cb.c \
    mmi_schedulersrv_priv.c \
    mmi_schedulersrv_utility.c \
	mmi_shortcutssrv.c \
	mmi_simsrv.c \
	mmi_simsrv_sm.c \
	mmi_smssrv.c \
	mmi_smssrv_sm.c \
	mmi_smstransactionsrv.c \
	mmi_sssrv.c \
	mmi_sssrv_sm.c \
	mmi_sssrv_util.c \
	mmi_statusbarsrv.c \
	mmi_stksrv.c \
	mmi_touchshortcutsrv.c \
	mmi_tvsrv.c \
	mmi_usbsrv.c \
	mmi_vcalparsersrv.c \
	mmi_vcalstoresrv.c \
	mmi_vendorsrv.c \
	mmi_videoplayersrv.c \
	mmi_vtmsrv.c \
	mmi_codecsrv.c \
	mmi_audiorecordersrv.c \
	mmi_audiosrv.c \
	mmi_audioenvsrv.c \
	mmi_mediasrvutil_common.c \
	mmi_voicecallsrv.c \
	mmi_srvcommon.c \
	mmi_wlansrv.c \
	mmi_wlansrv_sm.c \
	mmi_socketsrv.c \
	mmi_srvstgr.c \
	mmi_ttssrv.c \
	mmi_ttssrv_dbl.c \
	mmi_ttssrv_play_sm.c \
	mmi_ttssrvstgr.c \
    mmi_videostreaming.c \
	mmi_videostreaming_util.c \
	UrlSrvClient.c\
	UrlSrvClientHelper.c\
	UrlSrvClientInternal.c\
	UrlSrvClientMsgHandler.c\
	UrlSrvClientStaticUrlHandler.c\
	UrlSrvCommon.c\
	UrlSrvServer.c\
	UrlSrvServerMgrItf.c\
	UrlSrvServerMsgHandler.c\
	UrlSrvUtil.c\
	UrlSrvUtilListener.c\
	UrlSrvUtilUrl.c\
	UriCommon.c\
	UriEscape.c\
	UriIP.c\
	UriParse.c\
	UriPort.c\
	UriQuery.c

ifeq ($(filter __EMAIL_MMI__ , $(PP_OPT_COMMON)),__EMAIL_MMI__)
SRC_C_LIST += \
	mmi_emailsrv.c
endif

ifeq ($(filter __NCCQQ_MMI__ , $(PP_OPT_COMMON)),__NCCQQ_MMI__)
SRC_C_LIST += \
	mmi_qqsrv.c
endif

ifeq ($(filter __CALLER_LOCATION__ , $(PP_OPT_COMMON)),__CALLER_LOCATION__)
SRC_C_LIST += \
	mmi_clsrv.c
endif

ifeq ($(filter __SXMENGINE__ ,$(PP_OPT_COMMON)),__SXMENGINE__)
MMI_PATH_H += $(PATH_application)/3rd/sxmengine/inc
endif
#delete original {MMI_}PATH_H
ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
MMI_PATH_H += \
	$(PATH_NCCEmail_target)/inc\
	$(PATH_i18n)/inc\
	$(PATH_srv)/EmailSrv/inc/priv \
	$(PATH_srv)/EmailSrv/inc
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)),__NCCQQ_MMI__)
MMI_PATH_H += \
	$(PATH_srv)/QQSrv/inc/priv \
	$(PATH_srv)/QQSrv/inc \
	$(PATH_3rd)/qq/inc
endif

PATH_C =\
	$(PATH_srv)/AccessorySrv/src \
	$(PATH_srv)/AlarmSrv/src \
	$(PATH_srv)/AliveWdgSrv/src \
	$(PATH_srv)/AtSyncSrv/src \
	$(PATH_srv)/BaseSrv/src \
	$(PATH_srv)/BtObexSrv/src \
	$(PATH_srv)/BtSrv/src \
	$(PATH_srv)/CallLogsrv/src \
	$(PATH_srv)/CameraSrv/src \
	$(PATH_srv)/CbSrv/src \
	$(PATH_srv)/CcSrv/src \
	$(PATH_srv)/ClSrv/src \
	$(PATH_srv)/VtCcSrv/src \
	$(PATH_srv)/ClipBoardSrv/src \
	$(PATH_srv)/CoreSrv/src \
	$(PATH_srv)/CountDownTimerSrv/src \
	$(PATH_srv)/CphsSrv/src \
	$(PATH_srv)/DialogSrv/src \
	$(PATH_srv)/DrmAgentSrv/src \
	$(PATH_srv)/EvtCenterSrv/src \
	$(PATH_srv)/FdnSrv/src \
	$(PATH_srv)/FmRadioSrv/src \
	$(PATH_srv)/GpsSrv/src \
	$(PATH_srv)/HashmapSrv/src \
	$(PATH_srv)/JavaSrv/src \
	$(PATH_srv)/MediaSrvCmn/src \
	$(PATH_srv)/MessageContentSrv/src \
	$(PATH_srv)/MessageManagerSrv/src \
	$(PATH_srv)/MessageOrganizationSrv/src \
	$(PATH_srv)/mmi_cfgsrv/src \
	$(PATH_srv)/MmSrv/src \
	$(PATH_srv)/MmsSrv/src \
	$(PATH_srv)/MmsTransactionSrv/src \
	$(PATH_srv)/AudioPlayerSrv/src \
	$(PATH_srv)/ObjProcessingSrv/src/ \
	$(PATH_srv)/PhbSrv/src \
	$(PATH_srv)/PlayListSrv/src \
	$(PATH_srv)/PreviewLine2Srv/src \
	$(PATH_srv)/PrivateprotectSrv/src \
	$(PATH_srv)/ProfileSrv/src \
	$(PATH_srv)/SchedulerSrv/src \
	$(PATH_srv)/ShortcutsSrv/src \
	$(PATH_srv)/SimSrv/src \
	$(PATH_srv)/SmsSrv/src \
	$(PATH_srv)/SmsTransactionSrv/src \
	$(PATH_srv)/SrvCommon/src \
	$(PATH_srv)/SsSrv/src \
	$(PATH_srv)/StatusBarSrv/src \
	$(PATH_srv)/StkSrv/src \
	$(PATH_srv)/TouchShortcutSrv/src \
	$(PATH_srv)/TtsSrv/src \
	$(PATH_srv)/TvSrv/src \
	$(PATH_srv)/UsbSrv/src \
	$(PATH_srv)/VCalParserSrv/src \
	$(PATH_srv)/VCalStoreSrv/src \
	$(PATH_srv)/VendorSrv/src \
	$(PATH_srv)/VideoPlayerSrv/src \
	$(PATH_srv)/VtmSrv/src \
	$(PATH_srv)/CodecSrv/src \
	$(PATH_srv)/AudioRecorderSrv/src \
	$(PATH_srv)/AudioSrv/src \
	$(PATH_srv)/AudioEnvSrv/src \
	$(PATH_srv)/MediaSrvUtil/src \
	$(PATH_srv)/UrlSrv/src \
	$(PATH_srv)/UrlSrv/src/UriParser \
	$(PATH_srv)/VoiceCallSrv/src\
	$(PATH_srv)/WlanSrv/src \
	$(PATH_srv)/ClSrv/src \
	$(PATH_srv)/TtsSrv/src \
	$(PATH_srv)/SocketSrv/src

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PATH_C += \
	$(PATH_srv)/EmailSrv/src

MMI_PATH_H += \
	$(PATH_3rd)/email/inc \
	$(PATH_3rd)/email/itf
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)),__NCCQQ_MMI__)
PATH_C += \
	$(PATH_srv)/QQSrv/src
endif

ifeq ($(filter __JAVA_MMI__ , $(PP_OPT_COMMON)),__JAVA_MMI__)

MMI_PATH_H += \
	$(PATH_java_common)/inc

endif

ifeq ($(filter __TTS__ , $(PP_OPT_COMMON)),__TTS__)

MMI_PATH_H += \
    $(PATH_application)/3rd/tts/inc

endif

ifeq ($(filter __HOPPER__ , $(PP_OPT_COMMON)),__HOPPER__)

MMI_PATH_H += \
    $(PATH_hopper)/pub
endif



ifeq ($(filter __3G_RIL_MMI__ ,$(PP_OPT_COMMON)),__3G_RIL_MMI__)
MMI_PATH_H +=\
	$(PATH_3g_cm)/itf\
	$(PATH_3g_conn)/itf\
	$(PATH_3g_conn)/inc\
	$(PATH_3g_mdlut)/itf\
	$(PATH_3g_mux)/itf\
	$(PATH_3g_mux)/inc\
	$(PATH_3g_ril)/itf\
	$(PATH_3g_ril)/inc\
	$(PATH_drv)/int/pub
endif

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
PATH_3g324m = $(PATH_3rd)/3g324m

MMI_PATH_H +=\
    $(PATH_3g324m)/include/3g324m\
    $(PATH_3g324m)/include/asn1\
    $(PATH_3g324m)/include/common\
    $(PATH_3g324m)/include/h245\
    $(PATH_3g324m)/include/h323addons

MMI_PATH_H +=\
	$(PATH_vdr)/pub \
	$(PATH_vt_mm)/pub \
	$(PATH_vt_task)/pub
endif

ifeq ($(filter __WAP_MMI_CDWAP__ , $(PP_OPT_COMMON)),__WAP_MMI_CDWAP__)
MMI_PATH_H += \
    $(PATH_application)/3rd/wap/itf

endif

ifneq ($(filter __ENABLE_SLDLM_ZMOLENGINE__ , $(PP_OPT_COMMON)),)
PATH_H +=\
	$(PATH_sys)/itf\
    $(PATH_sys)/pub
endif

ifeq ($(filter  __SXMENGINE__, $(PP_OPT_COMMON)), __SXMENGINE__)
MMI_PATH_H += \
	$(PATH_3rd)/sxmengine/inc
endif

ifeq ($(filter  __NATIVE_GAME_MMI_PEDOMETER__, $(PP_OPT_COMMON)), __NATIVE_GAME_MMI_PEDOMETER__)
PATH_C += \
    $(PATH_srv)/PedometerSrv/src

SRC_C_LIST += \
    mmi_pedometersrv.c

MMI_PATH_H += \
    $(PATH_srv)/PedometerSrv/inc/priv
endif
