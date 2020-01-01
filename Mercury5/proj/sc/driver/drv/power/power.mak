#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=\
  $(PATH_power)/src

PATH_H +=\
  $(PATH_adc)/pub\
  $(PATH_adc_hal)/pub\
  $(PATH_acc_inc)/pub
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
	drv_power.c \
	abi_headers_power.c

