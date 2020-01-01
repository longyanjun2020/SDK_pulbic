PATH_H = \
    $(PATH_AppLauncher)/inc \
    $(PATH_audio)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_gss)/pub \
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
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/inc/priv \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_widget)/pub

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
	mmi_srv_accessory.c \
	mmi_srv_alarm.c \
	mmi_srv_alivewdg.c \
	mmi_srv_atsync.c \
	mmi_srv_battery.c \
	mmi_srv_bt.c \
	mmi_srv_btobex.c \
	mmi_srv_calllog.c \
	mmi_srv_camera.c \
	mmi_srv_camcoder.c \
	mmi_srv_cbs.c \
	mmi_srv_cc.c \
	mmi_srv_cfg.c \
	mmi_srv_client.c \
	mmi_srv_client_commondefine.c \
	mmi_srv_clienttable.c \
	mmi_srv_clipboard.c \
	mmi_srv_clock.c \
	mmi_srv_config.c \
	mmi_srv_core.c \
	mmi_srv_countdowntimer.c \
	mmi_srv_cphs.c \
	mmi_srv_drmagent.c \
	mmi_srv_eventdb.c \
	mmi_srv_evtcenter.c \
	mmi_srv_fdn.c \
	mmi_srv_filemgr.c \
	mmi_srv_fmradio.c \
	mmi_srv_fstream.c \
	mmi_srv_gps.c \
	mmi_srv_imagemaker.c \
	mmi_srv_java.c \
	mmi_srv_mci.c \
	mmi_srv_audio.c \
	mmi_srv_mms.c \
	mmi_srv_mmstx.c \
	mmi_srv_mobilitymgr.c \
	mmi_srv_moi.c \
	mmi_srv_motiondetector.c \
	mmi_srv_audioplayer.c \
	mmi_srv_msgmgr.c \
	mmi_srv_objprocessing.c \
	mmi_srv_pedometer.c \
	mmi_srv_phb.c \
	mmi_srv_playlist.c \
	mmi_srv_previewline2.c \
	mmi_srv_profile.c \
        mmi_srv_scheduler.c \
	mmi_srv_sensormgr.c \
	mmi_srv_shortcut.c \
	mmi_srv_sim.c \
	mmi_srv_sms.c \
	mmi_srv_smstx.c \
	mmi_srv_ss.c \
	mmi_srv_stk.c \
	mmi_srv_taskdb.c \
	mmi_srv_taskdbmgr.c \
	mmi_srv_touch.c \
	mmi_srv_touchshortcut.c \
	mmi_srv_tts.c \
	mmi_srv_tv.c \
	mmi_srv_usb.c \
	mmi_srv_vcalparser.c \
	mmi_srv_vcalstore.c \
	mmi_srv_vendor.c \
	mmi_srv_videoplayer.c \
	mmi_srv_audiorecorder.c \
	mmi_srv_audioenv.c \
	mmi_srv_codec.c \
	mmi_srv_emugame.c \
	mmi_srv_voicecall.c \
	mmi_srv_wlan.c \
	mmi_srv_socket.c \
	mmi_srv_cl.c \
	mmi_srv_privateprotect.c

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)), __EMAIL_MMI__)
SRC_C_LIST +=\
	mmi_srv_email.c

MMI_PATH_H += \
	$(PATH_3rd)/email/inc \
	$(PATH_3rd)/email/itf \
	$(PATH_srv)/EmailSrv/inc/priv \
	$(PATH_srv)/EmailSrv/inc
endif

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)), __VT_3G324M__)
SRC_C_LIST +=\
	mmi_srv_vtcc.c \
	mmi_srv_vtm.c

MMI_PATH_H += \
	$(PATH_srv)/VtCcSrv/inc/priv \
	$(PATH_srv)/VtmSrv/inc/priv \
	$(PATH_srv)/VtmSrv/inc \
	$(PATH_vdr)/pub \
	$(PATH_vt_mm)/pub \
	$(PATH_vt_task)/pub
endif


ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)),__NCCQQ_MMI__)
SRC_C_LIST += \
	mmi_srv_qq.c

MMI_PATH_H += \
    $(PATH_srv)/QQSrv/inc/priv \
    $(PATH_srv)/QQSrv/inc
endif

ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
MMI_PATH_H +=\
	$(PATH_java)/common/inc
endif

PATH_C =\
	$(PATH_SrvWrapper)/src
#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_SrvWrapper.c
