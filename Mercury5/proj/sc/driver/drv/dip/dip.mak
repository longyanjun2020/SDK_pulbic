#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_dip)/src\

PATH_H += $(PATH_dip_hal)/inc\
    $(PATH_dip)/inc\
    $(PATH_gop_hal)/inc\
    $(PATH_pm_chip)/inc\

SRC_C_LIST = \
    drv_dip.c\
    dip_test.c
    

