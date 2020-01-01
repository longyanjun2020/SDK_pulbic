#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmpd_flow_ctl)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_ldc)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmpd_display)/inc\
    $(PATH_core_application_mmpd_img_pipe)/inc\
    $(PATH_core_application_mmpd_system)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_ccir)/inc\
    $(PATH_core_driver_mci)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_ptz)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_cam_os_wrapper)/pub\
    $(PATH_scl)/pub\
    $(PATH_scl)/inc/rtk\
    $(PATH_scl)/pub/rtk\
    $(PATH_scl_hal)/inc/drv\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpd_fctl.c\
    mmpd_ptz.c\

