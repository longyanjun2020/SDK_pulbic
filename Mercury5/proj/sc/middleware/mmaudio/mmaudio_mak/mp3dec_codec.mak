#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += MP3_DEC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/mp3dec/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/mp3dec/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/pub\
$(PATH_mmaudio_codec)/mp3dec/inc\
$(PATH_mmaudio)/id3/inc\
$(PATH_mmaudio)/cookdec/inc\
$(PATH_mmaudio)/wmadec/inc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_mmaudio_codec)/aacdec/inc\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio)/mp3L2_enc/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_drm_vfs)/pub


ifeq ($(COMPILER_VERSION), RVCTV22)
C_OPTIONS += \
   -O3 -Otime
else
C_OPTIONS += \
   -O2
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------- 
SRC_C_LIST +=   \
  mp3d_huffman.c \
  mp3d_imdctl.c \
  mp3d_decode.c \
  mp3d_header.c \
  mp3d_layer1.c \
  mp3d_layer2.c \
  mp3d_oem.c \
  mp3d_output.c \
  mp3d_stereo.c \
  mp3d_stream.c \
  mp3d_sync.c \
  mp3d_tab.c \
  mp3d_wrapper.c
