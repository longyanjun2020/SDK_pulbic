# Library module (lib) or Binary module (bin)
PROCESS = lib

#Varaible description:
#  SRC_C_LIST: the source files of this library
#  PATH_C:     the directory that contains all the source files
#  PATH_H:     the directory that contains all the header files
#
#Note: PATH_H should contain only
#        (1) the public and private header directories of this library,
#            usually called {priv, inc, src}, and
#        (2) public header directories of other libraries,
#            called pub (or inc, if pub is not present)
#Note: This library may not be compiled due to the compile option.
#      Please see
#      //EMMI/mainline/proj/sc/customer/product/common/mak/lib_paths.mak
#      for furthur information.
#Note: To get this .mak be found by the build process, a proper variable
#      should be defined. For example, you need to define the variable
#      PATH_Foo for Foo.mak so that the system knows where to find
#      the file Foo.mak and builds Foo.lib for you.
#      See also
#      //EMMI/mainline/proj/sc/customer/product/common/mak/paths.mak
#      //EMMI/mainline/proj/sc/customer/product/common/mak/paths_pub.mak
PATH_H = \
    $(PATH_AliveWidget)/inc \
    $(PATH_AndroidIdleApp)/inc \
    $(PATH_AndroidIdleApp)/res \
    $(PATH_AndroidIdleApp)/inc/priv \
    $(PATH_AndroidMainMenuApp)/inc \
    $(PATH_AppLauncher)/inc \
    $(PATH_audio_mdl)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_CallLogApp)/inc \
    $(PATH_CamApp)/inc \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_DesktopWidget)/inc \
    $(PATH_DesktopWidget)/inc/priv \
    $(PATH_esl)/pub \
    $(PATH_EvtCenterApp)/inc \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_FileMgrApp)/inc \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gss)/pub \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_mae)/pub \
    $(PATH_MainMenuApp)/inc \
    $(PATH_MessageCenterApp)/inc \
    $(PATH_MessageEditorApp)/inc \
    $(PATH_MessageViewerApp)/inc \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_MplayerApp)/inc \
    $(PATH_mserv)/inc \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
	$(PATH_OnApp)/inc \
	$(PATH_OffApp)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
	$(PATH_SettingApp)/inc \
    $(PATH_ShortcutsApp)/inc \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_widget)/inc \
    $(PATH_widget)/inc/priv \
    $(PATH_widget)/pub

#MMI_PATH_H is deprecated, keep it for the purpose of compatibility
MMI_PATH_H = 






SRC_C_LIST = \
    mmi_android_idleapp.c \
    mmi_android_idleapp_util.c

PATH_C = $(PATH_AndroidIdleApp)/src






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


