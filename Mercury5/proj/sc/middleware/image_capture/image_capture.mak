#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += CAPTURE_SLDLM
endif
endif

PATH_C +=\
  $(PATH_image_capture)/src
  
PATH_H += \
            $(PATH_image_capture)/inc\
            $(PATH_image_capture)/pub\
            $(PATH_image_codec)/pub\
            $(PATH_camera_mdl)/pub\
            $(PATH_scl)/pub\
            $(PATH_gss)/pub\
            $(PATH_jpe)/pub
            
ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_tv_mdl)/pub
endif            
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
  abi_headers_image_capture.c\
  mdl_image_capture_handle.c\
  mdl_imgcapture_main.c\
  imgcapture_header.c

#------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += imgcapture_i_sw_test.c
endif