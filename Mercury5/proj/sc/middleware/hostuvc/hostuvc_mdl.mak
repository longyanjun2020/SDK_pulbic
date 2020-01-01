#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_hostuvc_mdl)/src

PATH_H +=\
	$(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
	$(PATH_core_application_component)/inc\
	$(PATH_core_include_application)\
	$(PATH_core_include_img_pipe)\
	$(PATH_core_include_usb)\
	$(PATH_core_driver_usb)/inc\
	$(PATH_core_system_comp_ctl)/inc\
	$(PATH_core_system_usb_dev)/uvc/inc\
  $(PATH_core_system_usb_dev)/vendor/inc\
	$(PATH_core_system_usb_host)/inc\
	$(PATH_core_system_fs)/inc\
	$(PATH_core_lib_fs)/inc\
	$(PATH_core_lib_gui_inc_Core)\
	$(PATH_core_utility)/inc\
	$(PATH_usbhost)/pub\
	$(PATH_usbhost)/inc/include\
	$(PATH_utopia)/common/inc\
  $(PATH_utopia)/msos/inc\
  $(PATH_usbhost_hal)/inc\
  $(PATH_MsWrapper)/pub\
  $(PATH_core_system_os)/inc\
  $(PATH_core_system_host_if)/inc\
  $(PATH_hostuvc_mdl)/pub\
  $(PATH_hostuvc_mdl)/inc


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			mdl_hostuvc_driver.c	\
			mdl_hostuvc_queue.c	\
			mdl_hostuvc_video.c	\
			mdl_hostuvc_status.c	\
