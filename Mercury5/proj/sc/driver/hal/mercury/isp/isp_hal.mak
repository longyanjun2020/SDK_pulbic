#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_isp_hal)/src
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    hal_isp.c \
    hal_clkpad.c \
    isp_interrupt_handler.c \
    hal_isp_shadow.c

PATH_H += $(PATH_isp_hal)/inc \
          $(PATH_isp)/inc\
          $(PATH_isp_mdl)/inc\
          $(PATH_isp)/pub

#ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
#PATH_H += $(PATH_cust_drv)/gpio/inc
#else
#PATH_H += $(PATH_cust_drv)/inc
#endif


