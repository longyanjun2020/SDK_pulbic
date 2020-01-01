#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#include $(PATH_mmaudio_common)/mmaudio_platform.mak
ifneq (, $(findstring G1_PLATFORM_AUD, $(PP_OPT_COMMON)))
PP_OPT_COMMON += _aeon_mac_ __wma_aeon_mac__ __SW_DTMF_TONE__
ifeq ($(filter ENABLE_AAC_DEC ,$(PP_OPT_COMMON)),ENABLE_AAC_DEC)
PP_OPT_COMMON += HEAAC_V2_DEC
endif
endif



#ifeq ($(filter __SMALL_ROM_32__ ,$(PP_OPT_COMMON)),__SMALL_ROM_32__)
#PP_OPT_COMMON += \
#MP3_DEC \
#AAC_DEC \
#AMRNB_DEC \
#WAV_PLAYER \
#MIDI_PLAYER
#else
PP_OPT_COMMON += \
MP3_DEC \
AAC_DEC \
AMRNB_DEC \
AMRWB_DEC \
WAV_PLAYER \
MIDI_PLAYER
#endif


# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/audiocontrol/src/getinfo

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/audiocontrol/inc\
$(PATH_mmaudio)/midilib/inc\
$(PATH_mmaudio)/id3/inc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio_codec)/aacdec/inc\
$(PATH_mmaudio_codec)/mp3dec/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_drm_vfs)/pub




#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  wavd_getinfo.c \
  midi_getinf.c \
  aacd_getinfo.c \
  and_getinfo.c \
  awd_getinfo.c \
  mp3d_getinfo.c
