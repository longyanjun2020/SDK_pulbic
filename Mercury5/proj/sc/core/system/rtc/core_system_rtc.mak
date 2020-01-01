#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_rtc)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_system_rtc)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_core_utility)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_rtc_ctl.c\

