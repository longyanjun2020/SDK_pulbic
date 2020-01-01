#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_io_hal)/src
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	hal_io_mercury5.c\
	hal_pwm.c
#	hal_io_chip.c

PATH_H +=\
 $(PATH_io_hal)/inc\
 $(PATH_io)/inc\
 $(PATH_io)/pub
 
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_H += $(PATH_cust_drv)/gpio/inc
else
PATH_H += $(PATH_cust_drv)/inc
endif


