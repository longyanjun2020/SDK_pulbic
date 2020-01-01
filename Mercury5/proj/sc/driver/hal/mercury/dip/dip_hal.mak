#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C += \
    $(PATH_dip_hal)/src

PATH_H += \
    $(PATH_dip_hal)/inc\
    $(PATH_dip)/inc\
    $(PATH_efuse)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST = \
    hal_dip.c\

