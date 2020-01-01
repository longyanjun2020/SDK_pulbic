#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_rtc)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_rtc)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_core_system_os)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_rtc.c\

