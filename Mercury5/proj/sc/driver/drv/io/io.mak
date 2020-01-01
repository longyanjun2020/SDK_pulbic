#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_io)/src
  
IO_DRV_INC +=\
  inc\
  pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
		drv_gpio.c\
		gpio_test.c\
		drv_pwm.c
#  abi_headers_io.c\
#  drv_io_chip.c


#-------------------------------------------------------------------------------
#   List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += dipb_test.c \
              io_test.c \
              padctrl_test.c
endif


PATH_H += $(addprefix $(PATH_io)/, $(IO_DRV_INC))

ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_H += $(PATH_cust_drv)/gpio/inc
else
PATH_H += $(PATH_cust_drv)/inc
endif



