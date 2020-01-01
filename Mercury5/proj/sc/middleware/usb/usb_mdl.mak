#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += USB_SLDLM
endif
endif

PATH_C +=\
    $(PATH_usb_mdl)/src

PATH_H +=\
$(PATH_mtmgr)/pub\
$(PATH_usb_mdl)/pub\
$(PATH_usb)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
    abi_headers_usb_mdl.c\
    mdl_usb_main.c
else
SRC_C_LIST = \
	   mdl_usb_dummy.c
endif
PATH_H+=$(PATH_usb_mdl)/inc
    
