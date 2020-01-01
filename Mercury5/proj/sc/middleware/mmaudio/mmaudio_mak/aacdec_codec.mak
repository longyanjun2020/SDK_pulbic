#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += AAC_DEC
ifneq (, $(findstring G1_PLATFORM_AUD, $(PP_OPT_COMMON)))
PP_OPT_COMMON += HEAAC_V2_DEC
endif

# paths to C source files in "src" directories
PATH_C += $(PATH_mmaudio)/aacdec/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/aacdec/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/pub\
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
  aacd_huffman.c \
  aacd_mdct.c   \
  aacd_decode.c \
  aacd_output.c \
  aacd_ram_oem.c \
  aacd_recon.c \
  aacd_stream.c \
  aacd_syntax.c \
  aacd_tab.c \
  aacd_tool.c \
  ps_dec.c \
  ps_syntax.c \
  ps_tables.c \
  sbr_adct.c \
  sbr_common.c \
  sbr_dec.c \
  sbr_fbt.c \
  sbr_hfadj.c \
  sbr_hfgen.c \
  sbr_huff.c \
  sbr_hufftab.c \
  sbr_qmf.c \
  sbr_sdct.c \
  sbr_syntax.c \
  sbr_tab.c \
  mp4_config2.c \
  mp4_decode.c \
  mp4_parser.c \
  aacd_main.c



ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)

PP_OPT_COMMON +=\
  G1_PLATFORM_AUD

else

ifeq ($(COMPILER_VERSION),RVCTV22)
PP_OPT_COMMON +=\
  __ARM9E_RVDS22__
endif

endif
