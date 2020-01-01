
SRC_C_LIST = \
    mmi_qqapp.c \
    mmi_qqapp_util.c

PATH_C = $(PATH_QQApp)/src

PATH_H = 
PATH_H += $(PATH_QQApp)/inc
PATH_H += $(PATH_QQApp)/res
PATH_H += $(PATH_QQApp)/inc/priv

PATH_H += \
    $(PATH_acc_inc)/pub \
    $(PATH_app)/AlarmApp/inc \
    $(PATH_app)/AlarmApp/inc/priv \
    $(PATH_app)/AlarmApp/res \
    $(PATH_app)/AliveWidget/inc \
    $(PATH_app)/AliveWidget/inc/priv \
    $(PATH_app)/AliveWidget/res \
    $(PATH_app)/AtvApp/inc/priv \
    $(PATH_app)/AtvApp/inc \
    $(PATH_app)/AtvApp/res \
    $(PATH_app)/BjxApp/inc \
    $(PATH_app)/BjxApp/inc/priv \
    $(PATH_app)/BjxApp/res \
    $(PATH_app)/BmiApp/inc \
    $(PATH_app)/BmiApp/inc/priv \
    $(PATH_app)/BmiApp/res \
    $(PATH_app)/CalculatorApp/inc \
    $(PATH_app)/CalculatorApp/inc/priv \
    $(PATH_app)/CalculatorApp/res \
    $(PATH_app)/CalendarApp/inc \
    $(PATH_app)/CalendarApp/inc/priv \
    $(PATH_app)/CalendarApp/res \
    $(PATH_app)/CalibrationApp/inc \
    $(PATH_app)/CalibrationApp/inc/priv \
    $(PATH_app)/CalibrationApp/res \
    $(PATH_app)/CallLogApp/inc \
    $(PATH_app)/CallLogApp/inc/priv \
    $(PATH_app)/CallLogApp/res \
    $(PATH_app)/CallSettingApp/inc \
    $(PATH_app)/CallSettingApp/inc/priv \
    $(PATH_app)/CallSettingApp/res \
    $(PATH_app)/CamApp/inc \
    $(PATH_app)/CamApp/inc/priv \
    $(PATH_app)/CamApp/res \
    $(PATH_app)/CbSettingApp/inc \
    $(PATH_app)/CbSettingApp/inc/priv \
    $(PATH_app)/CbSettingApp/res \
    $(PATH_app)/CcApp/inc \
    $(PATH_app)/CcApp/inc/priv \
    $(PATH_app)/CcApp/res \
    $(PATH_app)/CcMtaApp/inc \
    $(PATH_app)/CcMtaApp/inc/priv \
    $(PATH_app)/CcMtaApp/res \
    $(PATH_app)/ConSettingApp/inc \
    $(PATH_app)/ConSettingApp/inc/priv \
    $(PATH_app)/ConSettingApp/res \
    $(PATH_app)/DesktopWidget/inc \
    $(PATH_app)/DesktopWidget/inc/priv \
    $(PATH_app)/DialerApp/inc \
    $(PATH_app)/DialerApp/inc/priv \
    $(PATH_app)/DialerApp/res \
    $(PATH_app)/DialogApp/inc \
    $(PATH_app)/DialogApp/inc/priv \
    $(PATH_app)/DialogApp/res \
    $(PATH_app)/EmApp/inc \
    $(PATH_app)/EmApp/inc/priv \
    $(PATH_app)/EmApp/res \
    $(PATH_app)/EvtCenterApp/inc \
    $(PATH_app)/EvtCenterApp/inc/priv \
    $(PATH_app)/EvtCenterApp/res \
    $(PATH_app)/FavoritePhbApp/inc \
    $(PATH_app)/FavoritePhbApp/inc/priv \
    $(PATH_app)/FavoritePhbApp/res \
    $(PATH_app)/FdnApp/inc \
    $(PATH_app)/FdnApp/inc/priv \
    $(PATH_app)/FdnApp/res \
    $(PATH_app)/FileMgrApp/inc \
    $(PATH_app)/FileMgrApp/inc/priv \
    $(PATH_app)/FileMgrApp/res \
    $(PATH_app)/IdleApp/inc \
    $(PATH_app)/IdleApp/inc/priv \
    $(PATH_app)/IdleApp/res \
    $(PATH_app)/IdlePreviewApp/inc \
    $(PATH_app)/IdlePreviewApp/inc/priv \
    $(PATH_app)/IdlePreviewApp/res \
    $(PATH_app)/KeyGuardApp/inc \
    $(PATH_app)/KeyGuardApp/inc/priv \
    $(PATH_app)/KeyGuardApp/res \
    $(PATH_app)/MainMenuApp/inc \
    $(PATH_app)/MainMenuApp/inc/priv \
    $(PATH_app)/MainMenuApp/res \
    $(PATH_app)/MessageCenterApp/inc \
    $(PATH_app)/MessageCenterApp/inc/priv \
    $(PATH_app)/MessageCenterApp/res \
    $(PATH_app)/MessageEditorApp/inc \
    $(PATH_app)/MessageEditorApp/inc/priv \
    $(PATH_app)/MessageEditorApp/res \
    $(PATH_app)/MessageTemplateApp/inc \
    $(PATH_app)/MessageTemplateApp/inc/priv \
    $(PATH_app)/MessageTemplateApp/res \
    $(PATH_app)/MessageViewerApp/inc \
    $(PATH_app)/MessageViewerApp/inc/priv \
    $(PATH_app)/MessageViewerApp/res \
    $(PATH_app)/MmsSettingApp/inc \
    $(PATH_app)/MmsSettingApp/inc/priv \
    $(PATH_app)/MmsSettingApp/res \
    $(PATH_app)/MplayerApp/inc \
    $(PATH_app)/MplayerApp/inc/priv \
    $(PATH_app)/MplayerApp/res \
    $(PATH_app)/NetworkApp/inc \
    $(PATH_app)/NetworkApp/inc/priv \
    $(PATH_app)/NetworkApp/res \
    $(PATH_app)/OffApp/inc \
    $(PATH_app)/OffApp/inc/priv \
    $(PATH_app)/OffApp/res \
    $(PATH_app)/OnApp/inc \
    $(PATH_app)/OnApp/inc/priv \
    $(PATH_app)/OnApp/res \
    $(PATH_app)/PhbApp/inc \
    $(PATH_app)/PhbApp/inc/priv \
    $(PATH_app)/PhbApp/res \
    $(PATH_app)/PicPreviewApp/inc \
    $(PATH_app)/PicPreviewApp/inc/priv \
    $(PATH_app)/PicPreviewApp/res \
    $(PATH_app)/PicViewerApp/inc \
    $(PATH_app)/PicViewerApp/inc/priv \
    $(PATH_app)/PicViewerApp/res \
    $(PATH_app)/ProfileApp/inc \
    $(PATH_app)/ProfileApp/inc/priv \
    $(PATH_app)/ProfileApp/res \
    $(PATH_app)/RemoteControlApp/inc/priv \
    $(PATH_app)/RemoteControlApp/inc \
    $(PATH_app)/SecApp/inc \
    $(PATH_app)/SecApp/inc/priv \
    $(PATH_app)/SecApp/res \
    $(PATH_app)/SendViaApp/inc \
    $(PATH_app)/SendViaApp/inc/priv \
    $(PATH_app)/SendViaApp/res \
    $(PATH_app)/SettingApp/inc \
    $(PATH_app)/SettingApp/inc/priv \
    $(PATH_app)/SettingApp/res \
    $(PATH_app)/ShortcutPhbApp/inc \
    $(PATH_app)/ShortcutPhbApp/inc/priv \
    $(PATH_app)/ShortcutPhbApp/res \
    $(PATH_app)/ShortcutsApp/inc \
    $(PATH_app)/ShortcutsApp/inc/priv \
    $(PATH_app)/ShortcutsApp/res \
    $(PATH_app)/SmsSettingApp/inc \
    $(PATH_app)/SmsSettingApp/inc/priv \
    $(PATH_app)/SmsSettingApp/res \
    $(PATH_app)/StkApp/inc \
    $(PATH_app)/StkApp/inc/priv \
    $(PATH_app)/StkApp/res \
    $(PATH_app)/UnitConverterApp/inc \
    $(PATH_app)/UnitConverterApp/inc/priv \
    $(PATH_app)/UnitConverterApp/res \
    $(PATH_app)/UsbApp/inc \
    $(PATH_app)/UsbApp/inc/priv \
    $(PATH_app)/UsbApp/res \
    $(PATH_app)/UssdApp/inc \
    $(PATH_app)/UssdApp/inc/priv \
    $(PATH_app)/UssdApp/res \
    $(PATH_app)/VendorApp/inc \
    $(PATH_app)/VendorApp/inc/priv \
    $(PATH_app)/VendorApp/res \
    $(PATH_app)/VideoPlayerApp/inc \
    $(PATH_app)/VideoPlayerApp/inc/priv \
    $(PATH_app)/VideoPlayerApp/res \
    $(PATH_app)/VoiceMailApp/inc \
    $(PATH_app)/VoiceMailApp/inc/priv \
    $(PATH_app)/VoiceMailApp/res \
    $(PATH_app)/VoiceMemoApp/inc \
    $(PATH_app)/VoiceMemoApp/inc/priv \
    $(PATH_app)/VoiceMemoApp/res \
    $(PATH_app)/WorldClockApp/inc \
    $(PATH_app)/WorldClockApp/inc/priv \
    $(PATH_app)/WorldClockApp/res \
    $(PATH_AppLauncher)/inc \
    $(PATH_audio)/itf_open \
    $(PATH_audio)/pub \
    $(PATH_batt)/pub \
    $(PATH_battery)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_bus)/inc \
    $(PATH_bus)/pub \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_cust_mmi)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_flash)/pub \
    $(PATH_fms)/inc \
    $(PATH_fms)/itf \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hal)/audio/inc \
    $(PATH_hal)/io/pub \
    $(PATH_hal)/jpe/inc \
    $(PATH_hal)/kernel/inc \
    $(PATH_hal)/pm/inc \
    $(PATH_hwlaud)/inc \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_io)/pub \
    $(PATH_mae)/pub \
    $(PATH_mae)/src \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmicomn)/res \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_mserv)/inc \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_pm)/inc \
    $(PATH_pm_mdl)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_storage)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_tscr)/pub \
    $(PATH_utility)/inc \
    $(PATH_vfs)/pub \
    $(PATH_drm_util)/pub \
    $(PATH_wap)/itf \
    $(PATH_widget)/inc \
    $(PATH_widget)/inc/priv \
    $(PATH_widget)/pub \
    $(PATH_v24)/pub

MMI_PATH_H = 

# Library module (lib) or Binary module (bin)
PROCESS		= lib

ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_H += $(PATH_cust_drv)/keypad/inc
else
PATH_H += $(PATH_cust_drv)/inc
endif

ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER__)
PATH_H +=\
	$(PATH_java)/nccjpl/inc
endif

ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
PATH_H += \
    $(PATH_JavaAmsApp)/inc \
    $(PATH_JavaFactoryApp)/inc \
    $(PATH_java_common)/inc
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
PATH_H += \
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc
endif

ifeq ($(filter __SXMENGINE__ ,$(PP_OPT_COMMON)),__SXMENGINE__)
PATH_H += $(PATH_sxmengine)/inc
endif

ifeq ($(filter __TTS__ ,$(PP_OPT_COMMON)),__TTS__)
PATH_H += $(PATH_tts)/inc
endif

ifeq ($(filter __ATV_CMMB__ ,$(PP_OPT_COMMON)), __ATV_CMMB__)
PATH_H += $(PATH_zlib)/inc
endif


