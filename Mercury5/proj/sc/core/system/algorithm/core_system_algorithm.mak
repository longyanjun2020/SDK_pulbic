#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------


# c file list
SRC_C_LIST = \
	  adas_test.c\
	  mmpf_adas.c\
	  mmpf_adas_ctl.c\
	  mmpf_fdtc.c\
	  mmpf_vmd.c\
	  #mmpf_fdtc_ctl.c\
	  #mmpf_eis.c\

# header file folder for this library
PATH_H +=\
	$(PATH_ahc)/inc\
	$(PATH_core_application_mmpd_flow_ctl)/inc\
	$(PATH_core_application_mmps_display)/inc\
	$(PATH_core_application_mmps_system)/inc\
	$(PATH_core_application_mmps_vid_recd)/inc\
	$(PATH_core_application_mmps_sensor)/inc\
	$(PATH_core_system_algorithm)/inc\
	$(PATH_core_lib_algorithm)/adas/inc\
	$(PATH_core_lib_algorithm)/mdtc/inc\
	$(PATH_core_lib_isp)/inc\
	$(PATH_core_lib_fs)/inc\
	$(PATH_core_lib_gui_inc_Config)\
	$(PATH_core_lib_gui_inc_Core)\
	$(PATH_core_driver_bsp)/inc\
	$(PATH_core_driver_common)/inc\
	$(PATH_core_driver_display)/inc\
	$(PATH_core_driver_dma)/inc\
	$(PATH_core_driver_dip)/inc\
	$(PATH_core_driver_i2cm)/inc\
	$(PATH_core_driver_img_pipe)/inc\
	$(PATH_core_driver_pll)/inc\
	$(PATH_core_driver_timer)/inc\
	$(PATH_core_driver_uart)/inc\
	$(PATH_core_include_application)\
	$(PATH_core_include_display)\
	$(PATH_core_include_img_pipe)\
	$(PATH_core_include_misc)\
	$(PATH_core_include_usb)\
	$(PATH_core_system_gsensor)/inc\
	$(PATH_core_driver_gpio)/inc\
	$(PATH_core_system_host_if)/inc\
	$(PATH_core_system_misc)/inc\
	$(PATH_core_system_os)/inc\
	$(PATH_core_system_sensor)/inc\
	$(PATH_core_system_sys)/inc\
	$(PATH_core_utility)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm/ldws/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm/mdtc/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg)/isp/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_sdk)/inc\
	$(PATH_project_Dvr_CarDV_SDK_UI)/inc\
	$(PATH_project_Dvr_CarDV_SDK_Menu)/inc\
	$(PATH_project_Dvr_CarDV_SDK_Draw)/inc\
	$(PATH_project_Dvr_CarDV_SDK_OSDIcon_position)/inc\
	$(PATH_vendor_gsensor)/\
	$(PATH_vendor_gps)/inc\
		

# c/cpp source code for this library
PATH_C =\
	$(PATH_core_system_algorithm)/src\

