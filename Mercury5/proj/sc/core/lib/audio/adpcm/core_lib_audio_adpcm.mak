#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_lib_audio_adpcm)/adpcm_enc/src\
    $(PATH_core_lib_audio_adpcm)/wav_dec/src\

PATH_H +=\
    $(PATH_core_lib_audio_adpcm)/adpcm_enc/inc\
    $(PATH_core_lib_audio_adpcm)/common/inc\
    $(PATH_core_lib_audio_adpcm)/wav_dec/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
    adpcm.c\
    pcm.c\
    adpcm_enc.c\
    g726.c