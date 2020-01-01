#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

PP_OPT_COMMON += ENABLE_AUD_SPECTRUM

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/aud_spectrum/src

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/aud_spectrum/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST +=   \
  aud_spectrum.c \
  audspecsharedmem.c 
