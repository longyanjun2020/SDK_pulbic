#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_int)/src
  
INT_DRV_INC +=\
  inc

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
  abi_headers_int.c \
  sys_irq_ctrl.c\
  drv_riu_sw_irq.c\
  drv_int_ctrl.c

ifeq ($(filter __UPGRADE_SHARE_MEMORY__, $(PP_OPT_COMMON)), __UPGRADE_SHARE_MEMORY__)
SRC_C_LIST += mcu2mmp_irq_ctrl.c
endif


#-------------------------------------------------------------------------------
#	List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)

ifneq ($(filter __G1__, $(PP_OPT_COMMON)), __G1__)
SRC_C_LIST += ext_int_test.c
endif
SRC_C_LIST += intc_test.c

PATH_H +=\
  $(PATH_timer_hal)/pub

endif #__I_SW__


PATH_H += $(addprefix $(PATH_int)/, $(INT_DRV_INC))


