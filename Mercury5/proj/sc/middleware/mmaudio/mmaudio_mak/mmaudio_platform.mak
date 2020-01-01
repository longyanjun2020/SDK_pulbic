#-------------------------------------------------------------------------------
#   MMAUDIO platform-dependent make include file
#-------------------------------------------------------------------------------

ifeq ($(filter __MMAUDIO_ARM__, $(PP_OPT_COMMON)), __MMAUDIO_ARM__)
MMAUDIO_CPU := ARM9E
endif

ifeq ($(filter __MMAUDIO_AEON__, $(PP_OPT_COMMON)), __MMAUDIO_AEON__)
MMAUDIO_CPU := Aeon
endif

$(if $(MMAUDIO_CPU),,$(error MMAUDIO Platform Not Support!!!))

ifeq ($(filter __MMAUDIO_AEON__, $(PP_OPT_COMMON)), __MMAUDIO_AEON__)
PP_OPT_COMMON += G1_PLATFORM_AUD
endif

ifeq ($(COMPILER_VERSION), RVCTV22)
PP_OPT_COMMON += __ARM9E_RVDS22__
endif



ifeq ($(filter ENABLE_MP3_DEC ,$(PP_OPT_COMMON)),ENABLE_MP3_DEC)
PP_OPT_COMMON += MP3_DEC
endif
ifeq ($(filter ENABLE_AAC_DEC ,$(PP_OPT_COMMON)),ENABLE_AAC_DEC)
PP_OPT_COMMON += AAC_DEC
endif
ifeq ($(filter ENABLE_AMRNB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_DEC)
PP_OPT_COMMON += AMRNB_DEC
endif
ifeq ($(filter ENABLE_AMRWB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_DEC)
PP_OPT_COMMON += AMRWB_DEC
endif
ifeq ($(filter ENABLE_COOK_DEC ,$(PP_OPT_COMMON)),ENABLE_COOK_DEC)
PP_OPT_COMMON += COOK_DEC
endif
ifeq ($(filter ENABLE_WMA_DEC ,$(PP_OPT_COMMON)),ENABLE_WMA_DEC)
PP_OPT_COMMON += WMA_DEC
endif
#always enable wav because image capture need wav playback
#ifeq ($(filter ENABLE_WAV_DEC ,$(PP_OPT_COMMON)),ENABLE_WAV_DEC)
PP_OPT_COMMON += WAV_PLAYER
#endif
ifeq ($(filter ENABLE_AMRNB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_ENC)
PP_OPT_COMMON += AMRNB_ENC
endif
ifeq ($(filter ENABLE_AMRWB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_ENC)
PP_OPT_COMMON += AMRWB_ENC
endif
ifeq ($(filter ENABLE_MP3L2ENC ,$(PP_OPT_COMMON)),ENABLE_MP3L2ENC)
PP_OPT_COMMON += MP3L2ENC
endif
ifeq ($(filter ENABLE_MP3L3ENC ,$(PP_OPT_COMMON)),ENABLE_MP3L3ENC)
PP_OPT_COMMON += MP3L3ENC
endif

ifeq ($(filter ENABLE_WAV_ENC ,$(PP_OPT_COMMON)),ENABLE_WAV_ENC)
PP_OPT_COMMON += ENABLE_WAVENC_IMAADPCM
PP_OPT_COMMON += ENABLE_WAVENC_MGR
endif

ifeq ($(filter ENABLE_PCM_ENC ,$(PP_OPT_COMMON)),ENABLE_PCM_ENC)
PP_OPT_COMMON += PCM_ENC
endif

ifeq ($(filter ENABLE_AECPROC ,$(PP_OPT_COMMON)),ENABLE_AECPROC)
PP_OPT_COMMON += AECPROC
endif

ifeq ($(filter ENABLE_NSPROC ,$(PP_OPT_COMMON)),ENABLE_NSPROC)
PP_OPT_COMMON += NSPROC
endif

PP_OPT_COMMON += MIDI_PLAYER
