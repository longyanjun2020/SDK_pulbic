#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_jpeg)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_display)\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_jpeg)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_display)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_jpe)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_jpeg_ctl.c\

