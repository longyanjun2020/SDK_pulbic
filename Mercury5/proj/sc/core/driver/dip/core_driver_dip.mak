#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_dip)/src\

PATH_H +=\
    $(PATH_core_driver_dip)/inc\
    $(PATH_dip)/inc\
    $(PATH_dip_hal)/inc\
    $(PATH_pm_chip)/inc\
	
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    dip_ctl.c\

