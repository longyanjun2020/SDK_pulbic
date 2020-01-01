#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_audio)/codec/aacplus_dec/src

ifeq ($(OSTYPE), linux)
PATH_H +=\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_lib_audio_aacplus_dec)/inc\
    $(PATH_core_lib_audio)/aac_inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_audio_control)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_vid_play)/inc/parser\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_lib_audio_eq)/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc

else	    
PATH_H +=\
    $(PATH_core_system_audio)/codec/aacplus_dec/inc\
    $(PATH_core_system_audio)/codec/aac_enc/inc\
    $(PATH_core_system_audio)/codec/adpcm_enc/inc\
    $(PATH_core_system_audio)/codec/wav_enc/inc\
    $(PATH_core_system_audio)/codec/wav_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_dec/inc\
    $(PATH_core_system_audio)/codec/mp3_enc/inc\
    $(PATH_core_lib_audio_aacplus_dec)/inc\
    $(PATH_core_lib_audio)/aac_inc\
    $(PATH_core_lib_audio_adpcm_common)/inc\
    $(PATH_core_lib_audio_mp3_dec)/inc\
    $(PATH_core_lib_audio_mp12_dec)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_audio_control)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_utility)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_system_buffering)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_vid_play)/inc/parser\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_lib_audio_eq)/inc\
    $(PATH_core_system_audio)/codec/pcm_enc/inc\
    /usr/include\
    
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
    aacplus_parser.c\
    mmpf_aacplusdecapi.c