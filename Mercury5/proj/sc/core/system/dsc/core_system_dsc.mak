#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_dsc)/src\
    $(PATH_core_system_dsc)/test/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_ptz)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_include_vid_recd)\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui)/inc\Core\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_display)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_jpeg)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_dsc)/test/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_ptz)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_exif)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_jpd)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_sys)/pub\
    $(PATH_fc)/pub\
    $(PATH_drvutil_hal)/inc\
    $(PATH_jpe)/pub\
    $(PATH_jpe)/test/common\
    $(PATH_cam_os_wrapper)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_jpeg_dec.c\
    mmpf_jpeg_enc.c\
    mmpf_jpeg_enc_rc.c\
    mmpf_jpeg_enc_mgr.c\
    mmpf_dsc.c\
    appDemo_NJPD.c\

