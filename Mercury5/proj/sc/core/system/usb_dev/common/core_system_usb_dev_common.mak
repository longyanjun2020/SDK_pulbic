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
    mmpf_usbdescr.c\
    mmpf_usbint.c\
    mmpf_usbpub.c\
    mmpf_usbstd.c\
    mmpf_usb_ctl.c\
        
# cpp file list
#SRC_CPP_LIST = \
#	C4.cpp\
#	C5.cpp\
#	C6.cpp

# asm file list
#SRC_ASM_LIST =\
#	A1.asm\
#	A2.asm

# header file folder for this library 
PATH_H +=\
	$(PATH_core_application_mmps)/inc\
	$(PATH_core_application_mmps_usb)/inc\
	$(PATH_core_application_mmps_vid_recd)/inc\
	$(PATH_core_application_mmpd)/inc\
	$(PATH_core_application_mmpd_flow_ctl)/inc\
	$(PATH_core_application_mmpd_usb)/inc\
	$(PATH_core_application_mmph)/inc\
	$(PATH_core_system_audio_control)/inc\
	$(PATH_core_system_mm)/inc\
	$(PATH_core_system_sys)/inc\
	$(PATH_core_system_os)/inc\
	$(PATH_core_system_host_if)/inc\
	$(PATH_core_system_usb_dev)/uvc/inc\
	$(PATH_core_system_misc)/inc\
	$(PATH_core_system_sensor)/inc\
	$(PATH_core_system_vid_play)/inc\
	$(PATH_core_system_vid_recd)/inc\
	$(PATH_core_system_usb_dev_common)/inc\
	$(PATH_core_system_fs)/inc\
	$(PATH_core_system_usb_dev)/vendor/inc\
	$(PATH_core_system_usb_dev)/msdc/inc\
	$(PATH_core_lib_isp)/inc\
	$(PATH_core_lib_fs)/inc\
	$(PATH_core_lib_gui_inc_Core)\
	$(PATH_core_utility)/inc\
	$(PATH_core_driver_common)/inc\
	$(PATH_core_driver_ccir)/inc\
	$(PATH_core_driver_bsp)/inc\
	$(PATH_core_driver_mci)/inc\
	$(PATH_core_driver_uart)/inc\
	$(PATH_core_driver_pll)/inc\
	$(PATH_core_driver_misc)/inc\
	$(PATH_core_driver_usb)/inc\
	$(PATH_core_driver_timer)/inc\
	$(PATH_core_driver_img_pipe)/inc\
	$(PATH_core_include_misc)\
	$(PATH_core_include_usb)\
	$(PATH_core_include_application)\
	$(PATH_core_include_img_pipe)\
	$(PATH_core_include_display)\
	$(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_isp)/inc\
	$(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\
	
	#$(PATH_sc)/core/lib/isp/include\
	#$(PATH_core_system_host_if)/inc\
	#$(PATH_cardv_cfg)/cfg/core/inc\
	#$(PATH_core_driver_common)/inc\
	#$(PATH_core_system_os)/inc\
	
	#$(PATH_core_application_mmps)/inc\
	#$(PATH_core_driver_usb)/inc\
	#$(PATH_core_driver_misc)/inc\
	#$(PATH_core_driver_img_pipe)/inc\
	#$(PATH_core_system_fs)/inc\
	#$(PATH_core_driver_bsp)/inc\
	#$(PATH_core_include_misc)\
	#$(PATH_core_application_mmpd)/inc\
	#$(PATH_core_include_display)\
	#$(PATH_core_include_application)\
	#$(PATH_cardv_cfg)/cfg/fs\
	#$(PATH_cardv_cfg)/cfg/usb\
	#$(PATH_cardv_cfg)/cfg/snr\
	


			
#	$(PATH_ex20)/ex21/ex22\
#	$(PATH_ex23)/ex24/ex25/ex26/ex27\
#	$(PATH_ex28)/ex29/ex30/ex31

# c/cpp source code for this library 
PATH_C =\
	$(PATH_core_system_usb_dev)/common/src\
# $(PATH_ex1)/ex2/ex3\
# $(PATH_ex4)/ex5/ex6/ex7/ex8\
# $(PATH_ex9)/ex10/ex11/ex12

# assembler source code for this library 
#PATH_ASM =\
# $(PATH_ex31)/ex32/ex33\
# $(PATH_ex34)/ex35/ex36/ex37/ex38\
# $(PATH_ex39)/ex40/ex41/ex42

# mark C_OPTIONS if there is no cpp files would be compiled
#C_OPTIONS += \
#	--cpp

