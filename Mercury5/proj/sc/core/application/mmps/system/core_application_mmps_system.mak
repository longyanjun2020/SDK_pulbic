#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmps_system)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_fs)/inc\
    $(PATH_core_application_mmpd_audio)/inc\
    $(PATH_core_application_mmpd_system)/inc\
    $(PATH_core_application_mmpd_fs)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_dma)/inc\
    $(PATH_core_driver_gpio)/inc\
    $(PATH_core_driver_i2cm)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_pwm)/inc\
    $(PATH_core_driver_rtc)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_driver_uart)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_system_rtc)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib)/fs/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_MsWrapper)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmps_system.c\
    mmps_dma.c\
    mmps_i2cm.c\
    mmps_pio.c\
    mmps_pwm.c\
    mmps_rtc.c\
    mmps_uart.c\

