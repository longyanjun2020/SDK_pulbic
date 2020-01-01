PATH_H = \
    $(PATH_app)/AliveWidget/inc \
    $(PATH_audio)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_hopper)/pub \
    $(PATH_mae)/pub \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_widget)/inc \
    $(PATH_widget)/inc/priv \
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
	mae_view.c \
	mae_viewmgr.c \
	mae_windowmgr.c \
	mmi_view_wrapper.c

PATH_C =\
	$(PATH_widget)/src_priv

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mCore/inc \
    $(PATH_mgl)/mEgl/inc \
    $(PATH_mgl)/mScene/inc \
    $(PATH_mgl)/mTexture/inc \
    $(PATH_mgl)/mUtility/inc
endif
