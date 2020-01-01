#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# c file list
SRC_C_LIST = \
    os_wrap.c\

# header file folder for this library 
PATH_H +=\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_system_os)/inc\

# c/cpp source code for this library 
PATH_C =\
    $(PATH_core_system_os)/src\

