#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_audio)/control/src

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_audio)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_timer)/inc\
	$(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_system_audio_codec)/wav_dec/inc\
    $(PATH_core_system_audio_codec)/wav_enc/inc\
    $(PATH_core_system_audio_codec)/mp3_dec/inc\
    $(PATH_core_system_audio_codec)/mp3_enc/inc\
    $(PATH_core_system_audio_codec)/aac_enc/inc\
    $(PATH_core_system_audio_codec)/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio_codec)/amr_dec/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_system_vid_recd)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_vid_play)/inc/parser\
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_include_application)\
    $(PATH_core_include_misc)\
    $(PATH_core_include_img_pipe)\
    $(PATH_mfe)/inc\
    $(PATH_mfe)/test\
    $(PATH_mfe)/pub\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_cam_os_wrapper)/pub\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_lib_audio_eq)/inc\
    $(PATH_core_lib_audio_eq_new)/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\

    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
    mmpf_amix.c\
    mmpf_audio.c\
    mmpf_audio_ctl.c\
    mmpf_aui_ctl.c\
    mmpf_multiaudstreams.c\
    mmpf_stream_ctl.c
