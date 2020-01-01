PATH_H = \
    $(PATH_acc_inc)/pub \
    $(PATH_AppLauncher)/inc \
    $(PATH_ati)/inc \
    $(PATH_audio)/pub \
    $(PATH_batt)/pub \
    $(PATH_battery)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_compression_mdl)/pub \
    $(PATH_core)/interface/inc/priv \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_dynldr)/pub \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_fms)/itf \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hopper)/pub \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_io)/pub \
    $(PATH_keypad)/pub \
    $(PATH_keypad_mdl)/pub \
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
    $(PATH_pm)/inc \
    $(PATH_pm)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_ril_itf)\
    $(PATH_rtc)/inc \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_sim)/itf_open \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_tscr)/pub \
    $(PATH_tscr_mdl)/pub \
    $(PATH_vfs)/pub \
    $(PATH_drm_util)/pub \
    $(PATH_vml)/itf \
    $(PATH_wap)/itf \
    $(PATH_widget)/pub \
    $(PATH_rtk)/itf_open\
    $(PATH_avp)/pub \
    $(PATH_drv)/acc/pub

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
    mmiext_main.c \
    mmi_main.c \
    mmi_clstbl.c \
    mmi_if_acc.c \
    mmi_if_ati.c \
    mmi_if_atv.c \
    mmi_if_atcmd.c \
    mmi_if_atsync.c \
    mmi_if_atsync_phb.c \
    mmi_if_atsync_sms.c \
    mmi_if_autotest.c\
    mmi_if_battery.c \
    mmi_if_bt.c \
    mmi_if_cc.c \
    mmi_if_cm.c \
    mmi_if_h324m.c \
    mmi_if_vtcc.c \
    mmi_if_cdmms.c \
    mmi_if_cdwap.c \
    mmi_if_cdprov.c \
    mmi_if_codec.c \
    mmi_if_cphs.c \
    mmi_if_gsensor.c \
    mmi_if_proximity_sensor.c \
    mmi_if_gps.c \
    mmi_if_java.c \
    mmi_if_keypad.c \
    mmi_if_mm.c \
    mmi_if_ss.c \
    mmi_if_phb.c \
    mmi_if_rtc.c \
    mmi_if_sim.c \
    mmi_if_sms.c \
    mmi_if_sys.c \
    mmi_if_timer.c \
    mmi_if_touchscreen.c \
    mmi_if_usb.c \
    mmi_if_vfs.c \
    mmi_if_wlan.c\
    mmi_if_socket.c\
    mmi_if_hopper.c \
    mmi_req_bt.c \
    mmi_req_cc.c \
    mmi_req_cm.c \
    mmi_req_vtcc.c \
    mmi_req_cdmms.c \
    mmi_req_cdwap.c \
    mmi_req_cdprov.c \
    mmi_req_mm.c \
    mmi_req_phb.c \
    mmi_req_ss.c \
    mmi_req_usb.c \
    mmi_req_vendor.c \
    mmi_cb_acc.c \
    mmi_cb_atcmd.c \
    mmi_cb_atv.c \
    mmi_cb_bt.c \
    mmi_cb_codec.c \
    mmi_cb_gsensor.c \
    mmi_cb_proximity_sensor.c \
    mmi_cb_gps.c \
    mmi_cb_sys.c \
    mmi_cb_usb.c \
    mmi_cb_vfs.c \
    mmi_cb_wlan.c\
    mmi_req_cphs.c \
    mmi_req_java.c \
    mmi_req_rtk.c \
    mmi_req_sim.c \
    mmi_req_sms.c \
    mmi_req_wlan.c \
    mmi_req_socket.c \
    mmi_util_ati.c \
    mmi_util_fs.c \
    mmi_util_pwroff.c \
    mmi_util_rtc.c \
    mmi_util_keypad.c \
    mmi_if_touchscreen_simulator_test.c

ifeq ($(filter __RTSP_STREAMING__ ,$(PP_OPT_COMMON)),__RTSP_STREAMING__)
SRC_C_LIST += \
    mmi_if_rtsp.c \
    mmi_req_rtsp.c

MMI_PATH_H += \
    $(PATH_3rd)/rtsp/inc \
    $(PATH_3rd)/rtsp/pub
endif

ifeq ($(filter __SDK_API__ ,$(PP_OPT_COMMON)),__SDK_API__)
SRC_C_LIST += \
    mmi_if_vendor.c
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
SRC_C_LIST += \
    mmi_if_email.c \
    mmi_req_email.c

MMI_PATH_H += \
    $(PATH_3rd)/email/inc \
    $(PATH_3rd)/email/itf \
    $(PATH_srv)/EmailSrv/inc/priv \
    $(PATH_srv)/EmailSrv/inc
endif


#delete original {MMI_}PATH_H

ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
MMI_PATH_H +=\
    $(PATH_java)/common/inc

ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER__)
MMI_PATH_H +=\
    $(PATH_nccjpl)/inc \
    $(PATH_nccjpl)/itf
endif
endif

PATH_C =\
    $(PATH_core) \
    $(PATH_core)/interface/src

ifeq ($(filter __MAP_MMI_LBS__ ,$(PP_OPT_COMMON)),__MAP_MMI_LBS__)

SRC_C_LIST += \
    mmi_cb_lbs.c\
    mmi_if_lbs.c

MMI_PATH_H +=\
    $(PATH_map)/core/exFramework/fwBase/inc \
    $(PATH_map)/core/exFramework/fwUtil/inc \
    $(PATH_map)/core/exFramework/fwTimer/inc \
    $(PATH_map)/core/exServ/inc \
    $(PATH_app)/MapApp/inc
endif

ifeq ($(filter __TTS__ ,$(PP_OPT_COMMON)),__TTS__)
SRC_C_LIST += \
    mmi_if_tts.c \
    mmi_req_tts.c

MMI_PATH_H +=\
    $(PATH_srv)/ttssrv/inc \
    $(PATH_application)/3rd/tts/inc
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

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)),__NCCQQ_MMI__)
MMI_PATH_H += \
    $(PATH_srv)/QQSrv/inc \
    $(PATH_qq)/itf \
    $(PATH_qq)/inc

SRC_C_LIST += \
    mmi_if_qq.c \
    mmi_req_qq.c
endif

ifeq ($(filter __OFN_DRV__ ,$(PP_OPT_COMMON)), __OFN_DRV__)
MMI_PATH_H += \
    $(PATH_middleware)/ofn/pub
endif

ifeq ($(filter __BALL_DRV__ ,$(PP_OPT_COMMON)), __BALL_DRV__)
MMI_PATH_H += \
    $(PATH_middleware)/ball/pub
endif

ifeq ($(filter __HANDWRITING_MMI__ ,$(PP_OPT_COMMON)), __HANDWRITING_MMI__)
SRC_C_LIST += \
    mmi_util_handwriting.c \
    mmi_util_hw_sinovoice.c \
    mmi_util_hw_guobi.c

MMI_PATH_H += \
    $(PATH_sinovoice)/inc
endif
ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)),__RFID__)
MMI_PATH_H += \
    $(PATH_mae)/inc \
    $(PATH_rfid_mdl)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_esl)/pub \
    $(PATH_rtk)/itf


SRC_C_LIST += \
	mmi_if_rfidreader.c \
	mmi_cb_rfidreader.c
endif

#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_core.c
