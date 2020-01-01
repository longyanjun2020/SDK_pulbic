#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/sbcenc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/swmixer/src\
$(PATH_mmaudio)/src_converter/src\
$(PATH_mmaudio)/audiocontrol/src\
$(PATH_mmaudio)/id3/src\
$(PATH_mmaudio)/lyrics/src

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_com\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_dec\
$(PATH_mmaudio)/amrnb_codec/src/$(MMAUDIO_CPU)/amrnb_enc\
$(PATH_mmaudio)/cookdec/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/mp3L2_enc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_com\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_dec\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_enc\
$(PATH_mmaudio)/sbcenc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/wmadec/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio_codec)/aacdec/inc\
$(PATH_mmaudio)/audiocontrol/src\
$(PATH_mmaudio)/sbcenc/inc\
$(PATH_mmaudio)/amrnb_codec/inc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_mmaudio)/wav_codec/inc\
$(PATH_mmaudio)/cookdec/inc\
$(PATH_mmaudio)/wmadec/inc\
$(PATH_mmaudio)/id3/inc\
$(PATH_mmaudio_codec)/mp3dec/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_mmaudio)/swmixer/src\
$(PATH_mmaudio)/swmixer/inc\
$(PATH_mmaudio)/src_converter/inc\
$(PATH_app_engine)/app_mgr_shell/pub\
$(PATH_arp_engine)/arp_mgr_shell/pub\
$(PATH_drm_vfs)/pub

# PATH_H += $(PATH_mmaudio)/aacdec/src/ARM9E\

ifneq (, $(findstring G1_PLATFORM_AUD, $(PP_OPT_COMMON)))
PATH_C +=\
$(PATH_mmaudio)/aecproc/src\
$(PATH_mmaudio)/nsproc/src

PATH_H +=\
$(PATH_mmaudio)/aecproc/src\
$(PATH_mmaudio)/aecproc/inc\
$(PATH_mmaudio)/nsproc/src\
$(PATH_mmaudio)/nsproc/inc\
$(PATH_mmaudio)/pub\
$(PATH_mmaudio)/mstar_drc/inc

PP_OPT_COMMON += _aeon_mac_ __wma_aeon_mac__ __SW_DTMF_TONE__
ifeq ($(filter ENABLE_AAC_DEC ,$(PP_OPT_COMMON)),ENABLE_AAC_DEC)
PP_OPT_COMMON += HEAAC_V2_DEC
endif
endif



#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
#PP_OPT_COMMON += DLM_AMRNB_CODEC
ifneq ($(filter DLM_AMRNB_CODEC ,$(PP_OPT_COMMON)),DLM_AMRNB_CODEC)
SRC_C_LIST +=\
  anc_math.c \
  anc_tab.c
endif

SRC_C_LIST +=\
  a2dp_player.c \
  map_thread_mapping.c \
  map_player_util.c \
  abi_headers_mmaudio.c  \
  sw_dtmf_tone.c \
  map_api.c \
  map_parse.c \
  mar_api.c \
  mar_parse.c \
  mdw_pcm_newstream.c \
  lyrics.c \
  ID3.c \
  m4ameta.c \
  mplib.c \
  mplib_s.c \
  mplib_paas.c \
  downsamp.c \
  srcconvert.c \
  mdw_aud_stream_ring.c \
  sw_mixer.c \
  mdw_pcm_record.c \
  mdw_aud_clk.c

ifeq ($(filter ENABLE_AECPROC ,$(PP_OPT_COMMON)),ENABLE_AECPROC)
PATH_H +=\
$(PATH_mmaudio)/audiocontrol/inc \
$(PATH_mmaudio)/aecproc/inc \

SRC_C_LIST +=\
  mdw_aec_api.c \
  mdw_aec_ips.c
endif

ifneq (, $(findstring G1_PLATFORM_AUD, $(PP_OPT_COMMON)))
SRC_C_LIST +=\
  efr_dtx.c
endif


#GEN_PREPROCESS = 1
