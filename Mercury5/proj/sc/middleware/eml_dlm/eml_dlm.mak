#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_eml_dlm)/src
  
PATH_H += \
$(PATH_gss)/pub\
$(PATH_scl)/pub\
$(PATH_eml_dlm)/inc\
$(PATH_eml_dlm)/pub\
$(PATH_lcd)/pub\
$(PATH_disp)/pub\
$(PATH_dlm_entry_pub)

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
    mdl_eml_handle.c\
    mdl_eml_isw.c\
    mdl_eml_WhiteBox.c	\
    abi_headers_eml_dlm.c

ifeq ($(filter __DPM__, $(PP_OPT_COMMON)), __DPM__)
ifeq ($(filter __RTK_OVER_R2__, $(PP_OPT_COMMON)), __RTK_OVER_R2__)
REL_SRC_C_LIST += \
	mdl_eml_eml_main.c
endif
endif
