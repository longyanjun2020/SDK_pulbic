PATH_H = \
    $(PATH_core)/pub \
    $(PATH_fc)/pub \
    $(PATH_mae)/pub \
    $(PATH_model)/pub \
    $(PATH_model)/src \
    $(PATH_rtk)/pub \
	$(PATH_sdk)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub

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
	mae_imeassistmodel.c \
	mae_menumodel.c \
	mae_softkeymodel.c \
	mae_textmodel.c
ifeq ($(filter __MMI_SCRIPT_EASY_EDITOR__ ,$(PP_OPT_COMMON)),__MMI_SCRIPT_EASY_EDITOR__)
SRC_C_LIST += kmx_textmodel.c
endif

#delete original {MMI_}PATH_H

#Add temporarily
#delete original {MMI_}PATH_H
PATH_C =\
	$(PATH_model)/src
#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_model.c
