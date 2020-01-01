#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib
PATH_C +=\
  $(PATH_disp)/src

PATH_H +=\
$(PATH_scl)/pub\
$(PATH_scl_hal)/pub\
$(PATH_lcd)/pub\
$(PATH_disp)/pub
#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
  abi_headers_disp.c \
  drv_disp.c

#------------------------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += disp_test.c
endif


