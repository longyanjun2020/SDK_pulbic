#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_pm_chip)/src\

PATH_H += $(PATH_pm_chip)/inc\
    
SRC_C_LIST = \
    drv_pm_chip.c\

