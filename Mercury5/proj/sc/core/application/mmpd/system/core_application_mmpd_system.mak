#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmpd_system)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_application_mmpd_system)/inc\
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
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpd_system.c\
    mmpd_dma.c\
    mmpd_i2cm.c\
    mmpd_pio.c\
    mmpd_pwm.c\
    mmpd_rtc.c\
    mmpd_uart.c\

