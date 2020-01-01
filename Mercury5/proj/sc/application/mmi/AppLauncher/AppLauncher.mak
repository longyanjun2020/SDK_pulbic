PATH_H = \
    $(PATH_AppLauncher)/inc \
    $(PATH_AppLauncher)/res \
    $(PATH_audio)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_mae)/pub \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_model)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_drm_util)/pub \
    $(PATH_application)mms/inc \
    $(PATH_application)wap/inc \
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
	mmi_launcher_alarm.c \
	mmi_launcher_bjx.c \
	mmi_launcher_bt.c \
	mmi_launcher_btnotify.c \
	mmi_launcher_calendar.c \
	mmi_launcher_calllog.c \
	mmi_launcher_callsetting.c \
	mmi_launcher_camera.c \
	mmi_launcher_cc.c \
	mmi_launcher_ccmta.c \
	mmi_launcher_common.c \
	mmi_launcher_consetting.c \
	mmi_launcher_dialer.c \
	mmi_launcher_dialog.c \
	mmi_launcher_ebook.c \
	mmi_launcher_em.c \
	mmi_launcher_eventcenter.c \
	mmi_launcher_filemanager.c \
	mmi_launcher_fmradio.c \
	mmi_launcher_fmsch.c \
	mmi_launcher_javaams.c \
	mmi_launcher_javafactory.c \
	mmi_launcher_keyguard.c \
	mmi_launcher_mca.c \
	mmi_launcher_mmsa.c \
	mmi_launcher_mplayer.c \
	mmi_launcher_msa.c \
	mmi_launcher_mta.c \
	mmi_launcher_networkcounter.c \
	mmi_launcher_off.c \
	mmi_launcher_on.c \
	mmi_launcher_phb.c \
	mmi_launcher_picpreviewapp.c \
	mmi_launcher_picviewer.c \
	mmi_launcher_sea.c \
	mmi_launcher_security.c \
	mmi_launcher_sendvia.c \
	mmi_launcher_setting.c \
	mmi_launcher_shortcutphb.c \
	mmi_launcher_sohuupdater.c \
	mmi_launcher_usb.c \
	mmi_launcher_ussd.c \
	mmi_launcher_videoplayer.c \
	mmi_launcher_videotelephony.c \
	mmi_launcher_voicemail.c \
	mmi_launcher_voicememo.c \
	mmi_launcher_wap.c \
	mmi_launcher_wlan.c \
	mmi_launcher_checkdisk.c

ifeq ($(filter __FDN_MMI__ ,$(PP_OPT_COMMON)),__FDN_MMI__)
SRC_C_LIST += \
	mmi_launcher_fdn.c 
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
SRC_C_LIST += \
    mmi_launcher_email.c
endif

ifeq ($(filter __GAME_ENGINE_EMU_MMI__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU_MMI__)
SRC_C_LIST += \
	mmi_launcher_emu.c
endif

ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
SRC_C_LIST += \
    mmi_launcher_calibration.c
endif

ifeq ($(filter __APP_MMI_SHORTCUT__, $(PP_OPT_COMMON)), __APP_MMI_SHORTCUT__)
SRC_C_LIST += \
    mmi_launcher_shortcut.c 
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
SRC_C_LIST += \
    mmi_launcher_vendor.c
endif

ifeq ($(filter __APP_MMI_WORLDCLOCK__, $(PP_OPT_COMMON)), __APP_MMI_WORLDCLOCK__)
SRC_C_LIST += \
    mmi_launcher_worldclock.c
endif


PATH_C =\
	$(PATH_AppLauncher)/src
#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_AppLauncher.c
