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
	mmi_unittestsrv.c\
	ut_srv_base.c \
	ut_srv_videoplayer.c

PATH_C =\
	$(PATH_UnitTestSrv)/src

MMI_PATH_H += \
	$(PATH_UnitTestSrv)/inc/priv \
	$(PATH_UnitTestSrv)/inc \
	$(PATH_UnitTestApp)/inc \
    $(PATH_srv)/pub \
    $(PATH_srv)/BaseSrv/inc/priv \
    $(PATH_srv)/VideoPlayerSrv/inc/priv \
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
	$(PATH_middleware)/drm_util/pub

C_OPTIONS += --diag_suppress 1,9,14,42,47,66,68,69,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1134,1215,1256,1293,1294,1295,1296,2874
