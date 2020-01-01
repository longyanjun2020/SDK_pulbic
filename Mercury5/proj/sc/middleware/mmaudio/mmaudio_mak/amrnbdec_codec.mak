#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += AMRNB_DEC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_dec

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_dec\
$(PATH_mmaudio_codec)/aacdec/inc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio)/cookdec/inc\
$(PATH_mmaudio)/wmadec/inc\
$(PATH_mmaudio)/id3/inc\
$(PATH_mmaudio_codec)/mp3dec/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_drm_vfs)/pub

# PATH_H += $(PATH_mmaudio)/aacdec/src/ARM9E\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
#PP_OPT_COMMON += DLM_AMRNB_CODEC
ifneq ($(filter DLM_AMRNB_CODEC ,$(PP_OPT_COMMON)),DLM_AMRNB_CODEC)
SRC_C_LIST +=   \
  and_dtx.c \
  and_frame.c \
  and_main.c \
  and_post_filter.c \
  and_tab.c
endif
SRC_C_LIST +=   \
  and_wrapper.c