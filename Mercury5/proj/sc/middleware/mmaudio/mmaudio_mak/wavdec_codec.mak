#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += WAV_PLAYER

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/wav_codec/src/wav_dec

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio)/id3/inc\
$(PATH_mmaudio)/cookdec/inc\
$(PATH_mmaudio)/wmadec/inc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_mmaudio_codec)/aacdec/inc\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio_codec)/mp3dec/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_drm_vfs)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST +=   \
    wavdec.c