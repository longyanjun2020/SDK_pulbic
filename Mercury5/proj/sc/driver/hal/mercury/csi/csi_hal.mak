#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C += \
    $(PATH_csi_hal)/src

PATH_H += \
    $(PATH_csi_hal)/inc\
    $(PATH_csi)/inc\
    $(PATH_isp)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST = \
    hal_csi.c\

