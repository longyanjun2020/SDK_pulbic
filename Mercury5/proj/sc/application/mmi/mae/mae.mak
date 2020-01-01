PATH_H = \
    $(PATH_acc_inc)/pub \
    $(PATH_arm)/pub \
    $(PATH_audio)/pub \
    $(PATH_batt)/pub \
    $(PATH_battery)/pub \
    $(PATH_build) \
    $(PATH_compression_mdl)/pub \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hopper)/pub \
    $(PATH_image_codec)/pub \
    $(PATH_mae)/extras/datamgr \
    $(PATH_mae)/extras/util \
    $(PATH_mae)/inc \
    $(PATH_mae)/pub \
    $(PATH_mae)/src \
    $(PATH_mae)/src/fonts \
    $(PATH_mae)/src/le \
    $(PATH_mae)/src/models \
    $(PATH_mae_porting)/inc \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_pm)/inc \
    $(PATH_pm)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_truetype)/freetype2/inc \
    $(PATH_tscr_mdl)/pub \
    $(PATH_vfs)/pub \
    $(PATH_drm_vfs)/pub \
    $(PATH_vml)/inc \
    $(PATH_widget)/pub \
    $(PATH_zlib)/inc

MMI_PATH_H = 
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#delete original {MMI_}PATH_H
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
    abi_headers_mae.c \
	mae_main.c \
	mae_resource.c \
	mae_customization.c \
	mae_apm.c \
	mae_apm_util.c \
	mae_battery.c \
	mae_bitmap.c \
	mae_bitmap_common.c \
	mae_clstbl.c \
	mae_clock.c \
	mae_codec_util.c \
	mae_config.c \
	mae_contentmgr.c \
	mae_dev.c \
	mae_dib.c \
	mae_display.c \
	mae_eventdb.c \
	mae_font.c \
	mae_font_thai.c \
	mae_font_latine.c \
	mae_font_hebrew.c \
	mae_font_hindi.c \
	mae_font_bengali.c \
	mae_font_devanagari.c \
	mae_font_telugu.c \
	mae_font_tamil.c \
	mae_handler.c \
	mae_helper.c \
	mae_helper_exp.c \
	mae_image.c \
	mae_imagemaker.c \
	mae_md5.c \
	mae_motiondetector_game.c \
	mae_msgdispatcher.c \
	mae_notifier.c \
	mae_rescache.c \
	mae_shell.c \
	mae_shell_dispmgr.c \
	mae_shell_memory.c \
	mae_shell_timer.c \
	mae_sysstat.c \
	mae_sm.c \
	mae_sm_debug.c \
	mae_touchsrv.c \
	mae_util.c \
	mae_util_gles.c\
	mae_util_easing.c\
	rb_tree.c \
	mae_rightsdb.c \
	mae_logdb.c \
	mae_logdbmgr.c \
	mae_taskdb.c \
	mae_taskdbmgr.c \
	mae_file_util.c \
	mae_clock_base.c \
	mae_bitmap_base.c \
	mae_bitmap_base_common.c \
	mae_font_base.c \
	mae_display_base.c \
	mae_sensormgr.c \
	mae_motiondetector.c \
	mae_motiondetector_orientation.c \
	mae_motiondetector_action.c \
	mae_motiondetector_turnover.c \
	mae_gps.c \
	mae_bidi.c \
	mae_text_arabic.c \
	mae_text_util.c \
	mae_text.c \
	mae_thmmgr.c \
	mae_datamgr.c \
	ut_datamgr_utility.c \
	mae_verinfo.c\
	mae_gesture_recog.c \
	mae_font_vector.c

#add src for models
SRC_C_LIST += \
	mae_model.c \
	mae_datamodel.c \
	mae_interfacemodel.c \
	mae_imagemodel.c \
	mae_arraymodel.c \
	mae_vectormodel.c

#add src for models
SRC_C_LIST += \
	mae_le.c \
	mae_le_otf.c \
	mae_le_otf_common.c \
	mae_le_otf_def.c \
	mae_le_otf_pos.c \
	mae_le_otf_subst.c \
	mae_le_util.c

#add src for minizip used in dalvik
ifeq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)),__DALVIK__)
SRC_C_LIST += \
	minizip_ioapi_mem.c \
	minizip_unzip.c \
	rb_tree.c
endif

#add src for KMX Font use
ifeq ($(filter __MMI_SCRIPT_EASY__, $(PP_OPT_COMMON)), __MMI_SCRIPT_EASY__)
SRC_C_LIST += kmx_font_table.c
SRC_C_LIST += mae_font_kmx.c
endif

#delete original {MMI_}PATH_H

PATH_C =\
	$(PATH_mae)/src \
	$(PATH_mae)/src/models \
	$(PATH_mae)/src/resource \
	$(PATH_mae)/src/le \
	$(PATH_mae)/extras/util \
	$(PATH_mae)/extras/datamgr

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc
endif

ifneq ($(filter  __DUAL_BATT_DRV__ ,$(PP_OPT_COMMON)),  __DUAL_BATT_DRV__)
MMI_PATH_H += \
	$(PATH_ati)/inc \
	$(PATH_io)/pub \
	$(PATH_sim)/itf_open \
	$(PATH_vml)/itf
endif

ifeq ($(filter __MMI_SCRIPT_EASY__, $(PP_OPT_COMMON)), __MMI_SCRIPT_EASY__)
MMI_PATH_H += \
	$(PATH_mae)/inc/kmx

PATH_C +=\
	$(PATH_mae)/src/fonts/kmx
endif
ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)),__RFID__)

MMI_PATH_H += \
    $(PATH_rfid_mdl)/pub \
    $(PATH_esl)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_mmmanager)/pub

SRC_C_LIST += mae_rfidreader.c
endif

