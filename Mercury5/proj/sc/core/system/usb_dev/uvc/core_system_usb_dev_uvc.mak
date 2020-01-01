#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# header file folder for this library 
PATH_H +=\
	$(PATH_core_application_mmps)/inc\
	$(PATH_core_application_mmps_sensor)/inc\
	$(PATH_core_application_mmps_usb)/inc\
	$(PATH_core_application_mmps_vid_recd)/inc\
	$(PATH_core_application_mmpd)/inc\
	$(PATH_core_application_mmpd_flow_ctl)/inc\
	$(PATH_core_application_mmpd_img_pipe)/inc\
	$(PATH_core_application_mmpd_sensor)/inc\
	$(PATH_core_application_mmpd_usb)/inc\
	$(PATH_core_application_mmph)/inc\
	$(PATH_core_application_component)/inc\
	$(PATH_core_system_audio_control)/inc\
	$(PATH_core_system_comp_ctl)/inc\
	$(PATH_core_system_dsc)/inc\
	$(PATH_core_system_mm)/inc\
	$(PATH_core_system_rtc)/inc\
	$(PATH_core_system_sys)/inc\
	$(PATH_core_system_os)/inc\
	$(PATH_core_system_host_if)/inc\
	$(PATH_core_system_usb_dev)/uvc/inc\
	$(PATH_core_system_misc)/inc\
	$(PATH_core_system_sensor)/inc\
	$(PATH_core_system_ptz)/inc\
	$(PATH_core_system_vid_play)/inc\
	$(PATH_core_system_vid_recd)/inc\
	$(PATH_core_system_usb_dev_common)/inc\
	$(PATH_core_system_fs)/inc\
	$(PATH_core_system_usb_dev)/vendor/inc\
	$(PATH_core_system_usb_dev)/uvc/inc\
	$(PATH_core_lib_isp)/inc\
	$(PATH_core_lib_fs)/inc\
	$(PATH_core_lib_gui_inc_Core)\
	$(PATH_core_utility)/inc\
	$(PATH_core_driver_common)/inc\
	$(PATH_core_driver_ccir)/inc\
	$(PATH_core_driver_display)/inc\
	$(PATH_core_driver_dma)/inc\
	$(PATH_core_driver_bsp)/inc\
	$(PATH_core_driver_mci)/inc\
	$(PATH_core_driver_uart)/inc\
	$(PATH_core_driver_pll)/inc\
	$(PATH_core_driver_misc)/inc\
	$(PATH_core_driver_jpeg)/inc\
	$(PATH_core_driver_usb)/inc\
	$(PATH_core_driver_timer)/inc\
	$(PATH_core_driver_img_pipe)/inc\
	$(PATH_core_include_misc)\
	$(PATH_core_include_usb)\
	$(PATH_core_include_application)\
	$(PATH_core_include_img_pipe)\
	$(PATH_core_include_display)\
    $(PATH_mfe)/inc\
    $(PATH_mfe)/test\
    $(PATH_mfe)/pub\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_cam_os_wrapper)/pub\
	$(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_isp)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm/mdtc/inc\
	$(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\
    
# c/cpp source code for this library 
PATH_C =\
    $(PATH_core_system_usb_dev)/uvc/src\
	
# c file list
SRC_C_LIST = \
	mmpf_usbpccam.c\
	mmpf_usbuac.c\
	mmpf_usbuvc.c\
	pCam_api.c\
	pCam_audio.c\
	pCam_usb.c\
