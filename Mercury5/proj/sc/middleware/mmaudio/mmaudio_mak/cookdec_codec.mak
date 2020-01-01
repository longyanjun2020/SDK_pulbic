#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += COOK_DEC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/cookdec/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/cookdec/src/$(MMAUDIO_CPU)\
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

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=   \
  bitpack.c \
  buffers.c \
  category.c \
  cookdec_main.c \
  couple.c \
  envelope.c \
  fft.c \
  gainctrl.c \
  gecko2codec.c \
  huffman.c \
  hufftabs.c \
  memory_utils.c \
  mlt.c \
  pack_utils.c \
  ra8lbr_decode.c \
  rasl.c \
  ra_decode.c \
  ra_depack.c \
  ra_depack_internal.c \
  ra_wrapper.c \
  rm_io_default.c \
  rm_memory_default.c \
  rm_parser.c \
  rm_parser_internal.c \
  rm_stream.c \
  sqvh.c \
  stream_hdr_utils.c \
  string_utils.c \
  trigtabs.c \
  cook_getinfo.c
