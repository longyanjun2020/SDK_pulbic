#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += VDR_SLDLM
endif
endif

PATH_C +=\
  $(PATH_vdr_top)/src
  
PATH_H +=\
$(PATH_vdr)/inc\
$(PATH_vdr_top)/pub\
$(PATH_camera_mdl)/pub\
$(PATH_scl)/pub\
$(PATH_vdr)/inc/mx
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
	mdl_vdr_top.c
