#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_usb_host)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_display)\
    $(PATH_core_include_usb)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_usb)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_driver_dma)/inc\
    $(PATH_core_driver_rtc)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_jpeg)/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_rtc)/inc\
    $(PATH_core_system_usb_host)/inc\
    $(PATH_core_system_usb_dev)/uvc/inc\
    $(PATH_core_system_usb_dev)/vendor/inc\
    $(PATH_core_system_vid_recd)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_utility)/inc\
		$(PATH_hostuvc_mdl)/pub\
		$(PATH_usbhost)/pub\
		$(PATH_usbhost)/inc/include\
		$(PATH_utopia)/common/inc\
 		$(PATH_utopia)/msos/inc\
 		$(PATH_usbhost_hal)/inc\
		$(PATH_MsWrapper)/pub\
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_usbh_core.c\
    mmpf_usbh_ctl.c\
    mmpf_usbh_desc.c\
    mmpf_usbh_enum.c\
    mmpf_usbh_kernal.c\
    mmpf_usbh_uvc.c\
    mmpf_usbh_hub.c\

