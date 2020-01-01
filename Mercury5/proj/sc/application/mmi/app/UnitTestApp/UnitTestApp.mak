#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

NO_PLATFORM_INCLUDE = yes

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
	mmi_unittestapp.c\
	ut_main.c \
	ut_generate.c \
	ut_utility.c

PATH_C =\
	$(PATH_UnitTestApp)/src

MMI_PATH_H += \
	$(PATH_UnitTestApp)/inc/priv \
	$(PATH_UnitTestApp)/inc \
	$(PATH_widget)/inc \
	$(PATH_widget)/pub \
	$(PATH_model)/inc \
	$(PATH_model)/pub \
	$(PATH_build) \
	$(PATH_srv)/inc \
  	$(PATH_srv)/pub \
	$(PATH_mmicomn)/cfg \
	$(PATH_app)/AliveWidget/inc \
	$(PATH_widget)/inc/priv \
	$(PATH_SrvWrapper)/pub \
	$(PATH_core)/interface/inc/priv \
	$(PATH_fc)/pub \
	$(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
	$(PATH_mmicomn)/inc \
	$(PATH_vfs)/itf \
	$(PATH_vfs)/pub \
	$(PATH_vfs)/inc \
	$(PATH_FileMgr)/pub \
	$(PATH_ril_itf) \
	$(PATH_rtk)/inc \
	$(PATH_rtk)/pub\
	$(PATH_rtk)/itf \
	$(PATH_rtk)/itf_open \
	$(PATH_ResMgr)/inc/ABL \
	$(PATH_ResMgr)/inc/DataStruct \
    $(PATH_mmmanager)/pub \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager_lib)/pub \
    $(PATH_mmmanager_lib)/inc \
	$(PATH_ResMgr)/inc/DBL \
	$(PATH_ResMgr)/inc/HAL \
	$(PATH_ResMgr)/inc/MediaCmd \
	$(PATH_ResMgr)/inc/ResMgr \
	$(PATH_ResMgr)/inc/Util \
	$(PATH_ResMgr)/inc \
	$(PATH_ResMgr)/pub \
 	$(PATH_time)/pub \
 	$(PATH_rtc)/pub \
	$(PATH_sys)/itf_open \
	$(PATH_sys)/itf	\
	$(PATH_sys)/pub \
	$(PATH_trc)/inc \
	$(PATH_trc)/pub \
	$(PATH_fms)/inc \
	$(PATH_esl)/pub \
	$(PATH_audio)/itf_open \
	$(PATH_middleware)/audio/pub \
	$(PATH_hal)audio/inc \
	$(PATH_batt)/pub \
    $(PATH_battery)/pub \
	$(PATH_cus_app)/inc \
	$(PATH_MsWrapper)/pub \
	$(PATH_acc_inc)/itf \
	$(PATH_acc_inc)/itf_open \
	$(PATH_acc_inc)/pub \
	$(PATH_middleware)/keypad/inc \
	$(PATH_middleware)/keypad/pub \
	$(PATH_bluetooth)/inc \
    $(PATH_bluetooth)/pub \
	$(PATH_gpd_mdl)/pub \
	$(PATH_cn)/pub \
	$(PATH_fms)/itf_open \
	$(PATH_fms)/pub \
	$(PATH_image_codec)/inc \
	$(PATH_image_codec)/pub \
	$(PATH_AppLauncher)/inc \
	$(PATH_mserv)/inc \
	$(PATH_mserv)/itf \
	$(PATH_NCCMms_target)/inc\
	$(PATH_NCCBrowser_target)/inc\
	$(PATH_gss)/pub \
	$(PATH_kernel_hal)/inc \
	$(PATH_pm)/inc \
	$(PATH_mae)/extras/datamgr \
	$(PATH_timer)/pub \
	$(PATH_timer_hal)/pub \
	$(PATH_int_hal)/inc \
	$(PATH_customer_define_folder)/pub \
  	$(PATH_ucs2)/pub \
	$(PATH_application)/email/inc \
	$(PATH_drv)/battery/pub \
	$(PATH_3rd)/utility/i18n/inc \
	$(PATH_middleware)/tscr/pub \
	$(PATH_cpu_mdl)/pub


ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
MMI_PATH_H +=\
    	$(PATH_java_common)/inc
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
MMI_PATH_H += \
	$(PATH_NCCEmail_target)/inc\
	$(PATH_i18n)/inc\
	$(PATH_email)/inc \
	$(PATH_email)/itf \
	$(PATH_srv)/EmailSrv/inc/priv \
	$(PATH_srv)/EmailSrv/inc
endif

ifeq ($(filter __ENABLE_DLM_SRVUT__ ,$(PP_OPT_COMMON)),__ENABLE_DLM_SRVUT__)
SRC_C_LIST += \
	ut_share_data.c

MMI_PATH_H +=\
	$(PATH_dlm_entry)/inc
else
SRC_C_LIST +=\
	ut_acc_if.c \
	ut_accessory_if.c \
	ut_accessory_req.c \
	ut_alarm_if.c \
	ut_alarm_req.c \
	ut_atsync_if.c \
	ut_atsync_req.c \
    ut_audio_example.c \
	ut_audioenv_req.c \
    ut_audioenv_example.c \
    ut_audioplayer_req.c \
	ut_audioplayer_if.c \
	ut_audiorecorder_example.c \
	ut_audioplayer_example.c \
	ut_audiorecorder_if.c \
	ut_audiorecorder_req.c \
	ut_battery_req.c \
	ut_bt_if.c \
	ut_bt_req.c \
	ut_btobex_if.c \
	ut_btobex_req.c \
	ut_calllog_req.c \
	ut_camcoder_notify.c \
	ut_camcoder_req.c \
	ut_camcoder_example.c \
	ut_camera_notify.c \
	ut_camera_req.c \
	ut_camera_example.c \
	ut_capability_req.c \
	ut_cbs_if.c \
	ut_cbs_req.c \
	ut_cc_if.c \
	ut_cc_req.c \
	ut_cfg_req.c \
	ut_client_req.c \
	ut_clipboard_req.c \
	ut_clock_if.c \
	ut_clock_req.c \
	ut_codec_example.c \
	ut_codec_req.c \
	ut_codepage_convert_req.c \
	ut_config_if.c \
	ut_config_req.c \
	ut_core_req.c \
	ut_cphs_req.c \
	ut_eventdb_if.c \
	ut_eventdb_req.c \
	ut_evtcenter_if.c \
	ut_evtcenter_req.c \
	ut_fdn_if.c \
	ut_fdn_req.c \
	ut_filemgr_req.c \
	ut_fmradio_req.c \
	ut_fmradio_example.c \
	ut_gps_if.c \
	ut_gps_req.c \
	ut_imagemaker_req.c \
	ut_java_if.c \
	ut_java_req.c \
	ut_mci_req.c \
	ut_mm_if.c \
	ut_mms_if.c \
	ut_mms_req.c \
	ut_mmstx_if.c \
	ut_mmstx_req.c \
	ut_mobilitymgr_if.c \
	ut_mobilitymgr_req.c \
	ut_moi_if.c \
	ut_moi_req.c \
	ut_motiondetector_if.c \
	ut_motiondetector_req.c \
	ut_mplayer_req.c \
	ut_msgmgr_if.c \
	ut_msgmgr_req.c \
	ut_emugame_req.c \
	ut_emugame_example.c \
	ut_objprocessing_if.c \
	ut_objprocessing_req.c \
	ut_phb_if.c \
	ut_phb_req.c \
	ut_playlist_if.c \
	ut_playlist_req.c \
	ut_playlist_example.c \
	ut_previewline2_req.c \
	ut_profile_if.c \
	ut_profile_req.c \
	ut_sensormgr_if.c \
	ut_sensormgr_req.c \
	ut_sensormgr_example.c\
	ut_shortcut_req.c \
	ut_shortcut_example.c \
	ut_sim_if.c \
	ut_sim_req.c \
	ut_sim_example.c \
	ut_simsync_example.c \
	ut_sms_if.c \
	ut_sms_req.c \
	ut_smstx_if.c \
	ut_smstx_req.c \
	ut_ss_if.c \
	ut_ss_req.c \
	ut_stk_if.c \
	ut_stk_req.c \
	ut_subject_resconflict_req.c \
	ut_taskdb_req.c \
	ut_taskdbmgr_if.c \
	ut_taskdbmgr_req.c \
	ut_touch_req.c \
	ut_touch_example.c\
	ut_touchshortcut_example.c \
	ut_touchshortcut_if.c \
	ut_touchshortcut_req.c \
	ut_tv_notify.c \
	ut_tv_req.c \
	ut_usb_req.c \
	ut_usb_example.c \
	ut_vcalparser_req.c \
	ut_vcalstore_req.c \
	ut_vendor_if.c \
	ut_vendor_req.c \
	ut_videoplayer_if.c \
	ut_videoplayer_req.c \
	ut_videoplayer_example.c\
	ut_voicecall_req.c \
	ut_wlan_if.c \
	ut_wlan_req.c \
	ut_datamgr_req.c \
	ut_db_utility_req.c \
	ut_filemgr_example.c \
	ut_socket_req.c \
        ut_clock_example.c
endif

C_OPTIONS += --diag_suppress 1,9,14,42,47,66,68,69,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1134,1215,1256,1293,1294,1295,1296,2874
