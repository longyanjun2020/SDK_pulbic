
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_timer)/src

PATH_H +=\
$(PATH_timer_hal)/pub\
$(PATH_timer_hal)/inc
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
	drv_timer.c \
	drv_timer_ctrl.c \
	abi_headers_timer.c


#-------------------------------------------------------------------------------
#   List of source files of verification to generate
#-------------------------------------------------------------------------------
#ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
#SRC_C_LIST += timer_test.c
#endif

