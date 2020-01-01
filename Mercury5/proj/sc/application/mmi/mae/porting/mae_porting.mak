PATH_H = \
    $(PATH_acc_inc)/pub \
    $(PATH_arm)/pub \
    $(PATH_build) \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_dynldr)/pub \
    $(PATH_fc)/pub \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_mae)/pub \
    $(PATH_mae)/inc \
    $(PATH_mae_porting)/inc \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/inc \
    $(PATH_MsWrapper)/pub \
    $(PATH_rtc)/inc \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_tscr)/pub \
    $(PATH_tscr_mdl)/pub \
    $(PATH_vfs)/pub \
    $(PATH_hal)/kernel/inc    

MMI_PATH_H = 
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C +=\
	$(PATH_mae_porting)/src\

SRC_C_LIST += \
	mae_customization_pl.c\
	mae_layout_pl.c\
	mae_touchsrv_pl.c\
	mae_mime_pl.c\
	mae_clock_pl.c\
	mae_rtc_pl.c\
	mae_timer_pl.c\
	mae_memory_pl.c\
	mae_dev_pl.c\
	mae_dib_pl.c\
	mae_display_pl.c\
	mae_font_pl.c

#delete original {MMI_}PATH_H

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
MMI_PATH_H += \
	$(PATH_g3d)/inc\
	$(PATH_g3d)/inc/EGL\
	$(PATH_g3d)/inc/GLES\
	$(PATH_g3d)/inc/KHR\
	$(PATH_g3d)/inc/g3d
endif
