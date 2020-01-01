#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmpd_vid_recd)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_application_mmpd_system)/inc\
    $(PATH_core_application_mmpd_vid_recd)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_include_usb)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_mci)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_usb_host)/inc\
    $(PATH_core_system_vid_recd)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_usb_dev)/uvc/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_utility)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_mfe)/inc\
    $(PATH_mfe)/test\
    $(PATH_mfe)/pub\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_cam_os_wrapper)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpd_3gpmgr.c\
    mmpd_uvcrecd.c\

