#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_storage)/src

PATH_H +=\
  $(PATH_storage)/inc\
  $(PATH_storage)/pub\
  $(PATH_fcie)/inc\
  $(PATH_sdio)/inc
#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    drv_stg_2_hal.c\
    drv_stg_platform.c\
    drv_stg_intr.c\
    drv_sd.c\
    drv_reader.c


ifeq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PATH_H += $(PATH_system)/sys/inc

SRC_C_LIST += app_cli.c\
              drv_sd_spi.c
endif

