
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_clkgen)/src
  
PATH_H +=\
  $(PATH_emi)/pub
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
	drv_clkgen_cmu.c


SRC_C_LIST-y =

#-------------------------------------------------------------------------------
#	List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += \
	cmu_test.c \
	clkgen_test.c \
	pll_test.c
endif

