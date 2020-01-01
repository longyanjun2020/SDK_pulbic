#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_sensor)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_hdr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_isp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_display)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_display)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_i2cm)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_usb_dev)/uvc/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_isp_mdl)/inc\
    $(PATH_isp_mdl)/inc/camalgo\
    $(PATH_isp_mdl)/inc/iqfile\
    $(PATH_isp_mdl)/inc/common\
    $(PATH_isp_mdl)/inc/sensorDB\
    $(PATH_isp)/inc\
    $(PATH_isp)/pub\
    $(PATH_isp_mdl)/inc\
	$(PATH_isp)/inc\
	$(PATH_isp_mdl)/inc/common\
	$(PATH_isp_mdl)/inc/camalgo\
	$(PATH_isp)/pub\
	$(PATH_sensorif)/inc\
	$(PATH_isp_hal)/inc\
	$(PATH_isp)/inc\
	$(PATH_mfe)/pub\
	$(PATH_scl)/pub/rtk\
	$(PATH_scl)/pub\
	$(PATH_scl_hal)/inc/drv\
	
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_sensor.c\
    sensor_common.c\

