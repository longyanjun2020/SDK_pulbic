#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += CAMERA_SLDLM
endif
endif

PATH_C +=\
    $(PATH_camera_mdl)/src

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_H += $(PATH_camera_mdl)/inc\
          $(PATH_camera_top)/inc\
          $(PATH_camera_mdl)/pub\
          $(PATH_vdr)/pub\
          $(PATH_compression_mdl)/pub\
          $(PATH_gss)/pub\
          $(PATH_scl)/pub\
          $(PATH_sensorif)/pub\
          $(PATH_usb_mdl)/pub\
          $(PATH_gpd_mdl)/pub\
          $(PATH_disp)/pub
          
          
PATH_H +=\
    $(PATH_emi)/pub\
    $(PATH_dynscl)/pub

ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
PATH_H += \
  $(PATH_lcd)/pub\
  $(PATH_scl_hal)/pub
endif

ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_tv_mdl)/pub
endif
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
    abi_headers_camera_mdl.c\
    mdl_camera_main.c\
    mdl_camera_task.c\
    mdl_camera_comm.c\
    mdl_camera_api.c\
    mdl_camera_vt.c\
    mdl_camera_video.c\
    Abi_headers_camera_mdl.c
else    
SRC_C_LIST =\
    mdl_camera_dummy.c
endif


