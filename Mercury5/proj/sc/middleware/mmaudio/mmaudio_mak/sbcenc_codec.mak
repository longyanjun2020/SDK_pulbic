#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/sbcenc/src/$(MMAUDIO_CPU)

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/sbcenc/src/$(MMAUDIO_CPU)\
$(PATH_mmaudio)/sbcenc/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  sbce_oem.c \
  sbce_syntax.c \
  sbce_analysis.c \
  sbce_calc_bit.c \
  sbce_tab.c 
