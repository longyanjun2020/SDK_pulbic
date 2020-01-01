#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_jpd)/src

PATH_H +=\
    $(PATH_jpd)/inc\
    $(PATH_jpd_hal)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_core_system_os)\inc\
    $(PATH_sys)/pub\
    $(PATH_fc)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    drvNJPD.c\
    osalNJPD.c

