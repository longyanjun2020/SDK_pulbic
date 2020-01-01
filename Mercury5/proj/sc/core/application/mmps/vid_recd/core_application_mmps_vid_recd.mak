#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmps_vid_recd)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_hdr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_ptz)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_snr)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_usb)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_ldc)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_vidrec)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm/ldws/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm/mdtc/inc\
    $(PATH_core_application_mmps_adas)/inc\
    $(PATH_core_application_mmps_audio)/inc\
    $(PATH_core_application_mmps_dsc)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmps_fs)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_sensor)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_application_mmpd_audio)/inc\
    $(PATH_core_application_mmpd_dsc)/inc\
    $(PATH_core_application_mmpd_fs)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmpd_display)/inc\
    $(PATH_core_application_mmpd_img_pipe)/inc\
    $(PATH_core_application_mmpd_sensor)/inc\
    $(PATH_core_application_mmpd_system)/inc\
    $(PATH_core_application_mmpd_vid_recd)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_include_usb)\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_algorithm)/adas/inc\
    $(PATH_core_lib_algorithm)/mdtc/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_ccir)/inc\
    $(PATH_core_driver_mci)/inc\
    $(PATH_core_driver_jpeg)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_dip)/inc\
    $(PATH_core_driver_display)/inc\
    $(PATH_core_system_algorithm)/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_system_audio_codec_aac_enc)/inc\
    $(PATH_core_system_audio_codec_aacplus_dec)/inc\
    $(PATH_core_system_audio_codec_adpcm_enc)/inc\
    $(PATH_core_system_audio_codec_wav_dec)/inc\
    $(PATH_core_system_audio_codec_wav_enc)/inc\
    $(PATH_core_system_audio_codec_mp3_enc)/inc\
    $(PATH_core_system_audio_codec_mp3_dec)/inc\
    $(PATH_core_system_audio_codec_pcm_enc)/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_usb_dev)/uvc/inc\
    $(PATH_core_system_usb_host)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_vid_recd)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib)/fs/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_MsWrapper)/pub\
    $(PATH_fc)/pub\
    $(PATH_jpe)/pub\
    $(PATH_mfe)/inc\
    $(PATH_mfe)/test\
    $(PATH_mfe)/pub\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_cam_os_wrapper)/pub\
    $(PATH_scl)/pub\
    $(PATH_scl)/inc/rtk\
    $(PATH_scl)/pub/rtk\
    $(PATH_scl_hal)/inc/drv\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmps_3gprecd.c\
    mmps_uvcrecd.c\
    mmps_mjpeg.c\

