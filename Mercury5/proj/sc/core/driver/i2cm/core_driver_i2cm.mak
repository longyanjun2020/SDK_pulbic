#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_i2cm)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_gpio)/inc\
    $(PATH_core_driver_i2cm)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_MsWrapper)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_i2cm.c\

