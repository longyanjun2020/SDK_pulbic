#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_hwconfig)/src

HWCONFIG_DRV_INC +=\
  inc
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  drv_hw_config.c

PATH_H += $(addprefix $(PATH_hwconfig)/, $(HWCONFIG_DRV_INC))

 