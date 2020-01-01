#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmps_audio)/src\

PATH_H +=\
		$(PATH_core_application_mmps_audio)/inc\
		$(PATH_core_application_mmps_fs)/inc\
		$(PATH_core_application_mmpd_audio)/inc\
		$(PATH_core_application_mmpd_fs)/inc\
		$(PATH_core_application_mmpd_system)/inc\
		$(PATH_core_driver_bsp)/inc\
		$(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
		$(PATH_core_driver_common)/inc\
		$(PATH_core_application_mmph)/inc\
		$(PATH_core_driver_audio)/inc\
		$(PATH_core_include_application)\
		$(PATH_core_include_misc)/\
		$(PATH_core_include_display)\
		$(PATH_core_driver_timer)/inc\
		$(PATH_core_system_host_if)/inc\
		$(PATH_core_system_os)/inc\
		$(PATH_core_application_mmps)/inc\
		$(PATH_core_system_audio_control)/inc\
		$(PATH_core_system_audio_codec_aac_enc)/inc\
		$(PATH_core_system_audio_codec_aacplus_dec)/inc\
		$(PATH_core_system_audio_codec_adpcm_enc)/inc\
		$(PATH_core_system_audio_codec_wav_dec)/inc\
		$(PATH_core_system_audio_codec_wav_enc)/inc\
		$(PATH_core_lib_audio_aac_enc)/inc\
		$(PATH_core_lib_audio_adpcm_common)/inc\
		$(PATH_core_lib_gui_inc_Core)\
		$(PATH_core_lib_fs)/inc\
		$(PATH_core_utility)/inc\
		
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
		mmps_audio.c\
		mmps_aui.c