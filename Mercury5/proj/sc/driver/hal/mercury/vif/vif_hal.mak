#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C += \
    $(PATH_vif_hal)/src

PATH_H += \
    $(PATH_vif_hal)/inc\
    $(PATH_vif)/inc\
    $(PATH_isp)/inc\
    $(PATH_isp)/pub\
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST = \
    hal_vif.c\

