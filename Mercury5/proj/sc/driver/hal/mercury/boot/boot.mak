#------------------------------------------------------------------------------
#   Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS     = lib
PATH_C +=\
  $(PATH_boot)/src
#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_I +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf

PATH_H +=\
    $(PATH_efuse)/inc

PATH_ASM +=\
  $(PATH_boot)/src\
  $(PATH_sys)/src\
  $(PATH_rtk)/src/arm

ifeq ($(COMPILER_VERSION),ARMGCC)
SRC_ASM_LIST =\
  sys_boot_infinity.S\
  start.S
else
SRC_ASM_LIST =\
  sys_boot_blossom.asm
endif

SRC_C_LIST =\
  hal_boot.c
