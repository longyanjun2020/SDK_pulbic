#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += FMRX_SLDLM
endif
endif

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PATH_C +=\
$(PATH_mmaudio)/audiocontrol/src

PATH_H +=\
$(PATH_mmaudio)/pub\
$(PATH_mmaudio)/arp_engine/arp_mgr/inc \
$(PATH_mmaudio)/audiocontrol/inc \
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
$(PATH_mmaudio)/midilib/inc\
$(PATH_mmaudio)/mp3L2_enc/inc\
$(PATH_mmaudio)/mp3L3_enc/inc\
$(PATH_mmaudio)/src_converter/inc\
$(PATH_mmaudio)/aud_spectrum/inc\
$(PATH_app_engine)/app_ips/sc_fade/inc\
$(PATH_app_engine)/app_mgr_shell/pub\
$(PATH_arp_engine)/arp_mgr_shell/pub\
$(PATH_compression_mdl)/pub\
$(PATH_fmrx)/pub\
$(PATH_drm_vfs)/pub\
$(PATH_audio_drv)/pub


ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_tv_mdl)/pub
endif

# PATH_H += $(PATH_mmaudio)/aacdec/src/ARM9E\

ifneq (, $(findstring G1_PLATFORM_AUD, $(PP_OPT_COMMON)))
PP_OPT_COMMON += _aeon_mac_ __wma_aeon_mac__ __SW_DTMF_TONE__
ifeq ($(filter ENABLE_AAC_DEC ,$(PP_OPT_COMMON)),ENABLE_AAC_DEC)
PP_OPT_COMMON += HEAAC_V2_DEC
endif
endif

ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
PP_OPT_COMMON += MDW_A2DP_PLAYBACK_RB_FEATURE
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  mdw_aud_handle.c \
  mdl_fmr_handle.c \
  mdl_fmr_map.c    \
  mdw_dec_plugin.c \
  mdw_enc_plugin.c \
  mdw_aud_mapdma.c \
  mdw_aud_mar_in.c \
  mdw_midi_compress.c \
  aud_spectrum_map.c \
  mdl_a2dp.c \
  mdl_a2dp_api.c \
  a2dp_io_itf.c \
  a2dp_common_api.c