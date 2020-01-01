#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_sys)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_misc)\
    $(PATH_core_application_component)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_driver_gpio)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_MsWrapper)/pub\
    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_system.c\
    mmpf_msg.c\

