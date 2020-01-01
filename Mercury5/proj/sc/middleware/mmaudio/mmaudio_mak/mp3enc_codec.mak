#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += MP3L2ENC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/mp3L2_enc/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/mp3L2_enc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/mp3L2_enc/inc\
$(PATH_drm_vfs)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=   \
  mp2e_encode.c \
  mp2e_oem.c \
  mp2e_psycho.c \
  mp2e_scale_bit.c \
  mp2e_stream.c \
  mp2e_subband.c \
  mp2e_tab.c \
  mp2e_wrapper.c
