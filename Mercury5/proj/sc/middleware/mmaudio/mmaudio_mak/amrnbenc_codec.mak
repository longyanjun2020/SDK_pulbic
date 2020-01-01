#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += AMRNB_ENC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_enc

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_enc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_drm_vfs)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
#PP_OPT_COMMON += DLM_AMRNB_CODEC
ifneq ($(filter DLM_AMRNB_CODEC ,$(PP_OPT_COMMON)),DLM_AMRNB_CODEC)
SRC_C_LIST +=   \
  ane_cb_search.c \
  ane_close_loop_ltp.c \
  ane_dtx.c \
  ane_gainQuant.c \
  ane_lpc.c \
  ane_main.c \
  ane_math.c \
  ane_open_loop.c \
  ane_tab.c \
  ane_vad2.c \
  ane_vad.c
endif

SRC_C_LIST +=   \
  ane_wrapper.c
