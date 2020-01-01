#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_vif)/src\

PATH_H += $(PATH_vif_hal)/inc\
    $(PATH_vif)/inc\
    $(PATH_isp)/inc\
    $(PATH_isp)/pub\
    $(PATH_isp_hal)/inc\

SRC_C_LIST = \
    drv_vif.c\
    vif_test.c\

