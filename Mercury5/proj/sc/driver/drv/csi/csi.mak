#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_csi)/src\

PATH_H += $(PATH_csi_hal)/inc\
    $(PATH_csi)/inc\
    $(PATH_isp)/pub\

SRC_C_LIST = \
    drv_csi.c\

