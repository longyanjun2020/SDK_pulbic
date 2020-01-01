#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_comp_ctl)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmp_component_ctl.c\

