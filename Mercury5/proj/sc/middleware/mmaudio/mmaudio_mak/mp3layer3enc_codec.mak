#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += MP3L3ENC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/mp3L3_enc/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/pub\
$(PATH_mmaudio)/mp3L3_enc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/mp3L3_enc/inc\
$(PATH_drm_vfs)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=   \
  mp3e_bitstream.c \
  mp3e_encode.c \
  mp3e_huffman.c \
  mp3e_math.c \
  mp3e_mdct.c \
  mp3e_oem.c \
  mp3e_pam.c \
  mp3e_quantize.c \
  mp3e_reservoir.c \
  mp3e_tab.c \
  mp3e_wrapper.c
  