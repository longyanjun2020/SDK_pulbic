#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += ENABLE_WAVENC_IMAADPCM
PP_OPT_COMMON += ENABLE_WAVENC_MGR

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/wav_codec/src/wav_enc

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_drm_vfs)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST +=   \
  ima_adpcm_enc.c \
  wavenc_mgr.c