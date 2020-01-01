#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += AMRWB_ENC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_com\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_enc

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_com\
$(PATH_mmaudio)/amrwb_codec/src/$(MMAUDIO_CPU)/amrwb_enc\
$(PATH_mmaudio)/amrwb_codec/inc\
$(PATH_drm_vfs)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=   \
  awe_autocorr.c \
  awe_bits.c \
  awe_c2t64fx.c \
  awe_c4t64fx.c \
  awe_cod_main.c \
  awe_decim54.c \
  awe_dtx.c \
  awe_find_target.c \
  awe_lp_dec2.c \
  awe_pitch_gain.c \
  awe_q_gain2.c \
  awe_qpisf_2s_enc.c \
  awe_residu.c \
  awe_synthesis.c \
  awe_vad.c \
  awe_wrapper.c
