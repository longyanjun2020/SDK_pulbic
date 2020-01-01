#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_int_hal)/src

PATH_I +=\
  $(PATH_sys)/inc
  
PATH_H +=\
  $(PATH_sys)/inc
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    hal_int_irq.c\
#    hal_ext_int.c\
#    hal_int_irq.c\
#    hal_riu_sw_irq.c\
#	hal_sys_ext_int.c

SRC_C_LIST += hal_int_ctrl.c
ifeq ($(COMPILER_VERSION), RVCTV22)
SRC_ASM_LIST =\
  sys_isr_blossom.asm\
  sys_sleep_b5.asm
endif

ifeq ($(COMPILER_VERSION), ARMGCC)
SRC_ASM_LIST =\
  sys_isr_blossom.S\
  sys_isr_common.S
endif

PATH_H += $(PATH_io_hal)