#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_vid_recd)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_lib_audio)/aac_enc/inc\
    $(PATH_core_lib_audio)/adpcm/common/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_usb)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/g711_enc/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_system_audio)/src/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_usb_dev)/uvc/inc\
    $(PATH_core_system_usb_host)/inc\
    $(PATH_core_system_vid_recd)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_mfe)/inc\
    $(PATH_mfe)/test\
    $(PATH_mfe)/pub\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_jpe)/pub\
    $(PATH_cam_os_wrapper)/pub\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_3gpmgr.c\
    mmpf_3gpmux.c\
    mmpf_avimux.c\
    mmpf_clksync.c\
    mmpf_fpsctl.c\
    mmpf_h264enc.c\
    mmpf_mp4venc.c\
	mmpf_mts.c\
    mmpf_vr_thumb.c\
    mfe_test_mv5.c\

