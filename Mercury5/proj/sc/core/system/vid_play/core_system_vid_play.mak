#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_core_system_vid_play)/src\

PATH_H += \
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_application_mmpd_audio)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmpd_vid_play)/inc\
    $(PATH_core_application_mmpd_fs)/inc\
    $(PATH_core_application_mmps_audio)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_vid_play)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_application_mmps_fs)/inc\
    $(PATH_core_application_component)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_vid_play)/inc/parser\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_audio)/control/inc\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_mci)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_driver_dma)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_display)/inc\
    $(PATH_scalar_c3_mvop)/inc\
    $(PATH_core_lib_video_avc_dec)/inc\
    $(PATH_utopia)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_utopia_vdec)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_hvd)/inc\
    $(PATH_bdma)/inc\
    $(PATH_bdma)/pub\
    $(PATH_dec_scl)/inc\
    $(PATH_Pnl)/inc\
    $(PATH_Pnl_hal)/inc\
    $(PATH_scl)/inc/pq\
    $(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_lib_video_avc_dec)/inc\
        
SRC_C_LIST = \
    mmpf_h264dec.c\
    mmpf_3gpparser.c\
    mmpf_mjpgdec.c\
    mmpf_mp4vdec.c\
    mmpf_viddec_ctrl.c\
    mmpf_vidplay_ctl.c\
    mmpf_vpp.c\
    mmpf_player.c\
    mmpf_mjpgdec.c\
    mmp_tsparser_inc.c\
    appDemo_h264.c\
    apiVDEC.c