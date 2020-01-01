#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib

PATH_C +=\
    $(PATH_sensordriver)/src

PATH_H +=\
  	$(PATH_sensordriver)/inc\
		$(PATH_sensorif)/pub\
  	$(PATH_bus)/pub\
		$(PATH_isp_hal)/inc\
		$(PATH_isp)/inc\
		$(PATH_isp)/pub\
		$(PATH_isp_mdl)/inc\
    $(PATH_ahc)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_isp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_sdk)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_lib_gui_inc_Config)\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_lib_isp)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_misc)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_project_Dvr_CarDV_SDK_UI)/inc\

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------


SRC_C_LIST = \
    	drv_ms_cus_ar0237.c\
	drv_ms_cus_ar0238.c\
	drv_ms_cus_ar0239.c\
	drv_ms_cus_ar0330_MIPI.c\
	drv_ms_cus_bg0836.c\
	drv_ms_cus_bg0836_MIPI.c\
	drv_ms_cus_C2390_MIPI.c\
	drv_ms_cus_imx123_MIPI.c\
	drv_ms_cus_imx307_MIPI.c\
	drv_ms_cus_imx327_MIPI.c\
	drv_ms_cus_imx323.c\
	drv_ms_cus_ov4689_MIPI.c\
	drv_ms_cus_ov2718_MIPI.c\
	drv_ms_cus_ps5260_MIPI.c\
	drv_ms_cus_ps5280_MIPI.c\
	drv_ms_cus_pr2000_MIPI.c\
	drv_ms_cus_pr2000_BT656.c\
	drv_ms_cus_sc2363_MIPI.c\
	drv_ms_cus_sc4233_MIPI.c\
	drv_ms_cus_rn6752.c\
	drv_ms_cus_rn6852.c\
	drv_ms_cus_rn6778.c\
	drv_ms_cus_rn6752_MIPI.c\
	drv_ms_cus_rn6852_MIPI.c\
	drv_ms_cus_nvp6124b.c\
	drv_ms_cus_tp2825.c\
	drv_ms_cus_tp2852_MIPI.c\
	drv_ms_cus_bit1603.c\
	drv_ms_cus_DM5150.c\
	drv_ms_cus_DH9931.c\
	drv_ms_cus_N3.c\
	drv_ms_cus_ov2710_MIPI.c\
	drv_ms_cus_ov2718_PARL.c\
	drv_ms_cus_cp8220.c\
	drv_ms_cus_none_MIPI.c\
	sensordriver_i2c.c \

