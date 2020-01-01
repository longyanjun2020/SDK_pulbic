PATH_H = \
    $(PATH_AppLauncher)/inc \
    $(PATH_audio)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gss)/pub \
    $(PATH_image_codec)/pub \
    $(PATH_mae)/pub \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmicomn)/res \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_ucs2)/pub \
    $(PATH_utility)/inc \
    $(PATH_vfs)/pub \
    $(PATH_widget)/inc \
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
	mmi_baseapplet.c \
	mmi_common_calendar.c \
	mmi_common_content.c \
	mmi_common_dialog.c \
	mmi_common_encoding.c \
	mmi_common_intmgr.c \
	mmi_common_lang.c \
	mmi_common_mimetype.c \
	mmi_common_mms.c \
	mmi_common_sms.c \
	mmi_common_sms_storage.c \
	mmi_todolistapp_util.c \
	mmi_common_transition.c \
	mmi_common_util.c \
	mmi_common_util_menu.c \
	mmi_common_info.c \
	mmi_common_vtm.c \
	mmi_common_display.c \
	mmi_common_storage_mgr.c \
	mmi_common_window.c \
	mmi_common_hashtable.c \
	mmi_common_hashtable_util.c \
	mmi_common_queue.c \
	mmi_base_util.c \
	mmi_filemgr_util.c \
	mmi_subjecttb.c \
	mmi_subjectblockingtbl.c \
    mmi_common_private.c \
    mmi_common_apres.c \
    mmi_common_ifonedialer.c \
	mmi_blockingsubject.c \
    mmi_applaunchedsubject.c \
	mmi_subjectproxy.c \
	mmi_subjectcenter.c \
	mmi_subject.c \
	mmi_common_azan.c

#delete original {MMI_}PATH_H
PATH_C =\
	$(PATH_mmicomn)/src \
    $(PATH_mmicomn)/src/subject

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mCore/inc \
    $(PATH_mgl)/mScene/inc \
    $(PATH_mgl)/mTexture/inc \
    $(PATH_mgl)/mUtility/inc
endif

ifeq ($(filter __NOSIM_CAMP_ON_TEST_NETWORK__ ,$(PP_OPT_COMMON)),__NOSIM_CAMP_ON_TEST_NETWORK__)
PATH_H += $(PATH_vml)/inc
endif

#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_mmicomn.c

#add network setting cus use
ifeq ($(filter __NETWORK_SETTING_CUS__, $(PP_OPT_COMMON)), __NETWORK_SETTING_CUS__)
SRC_C_LIST += mmi_common_network_cus_parser.c
endif
