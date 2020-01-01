#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmps_sensor)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmps_sensor)/inc\
    $(PATH_core_application_mmpd_sensor)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_isp_mdl)/inc\
    $(PATH_isp)/inc\
    $(PATH_isp)/pub\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmps_sensor.c\

