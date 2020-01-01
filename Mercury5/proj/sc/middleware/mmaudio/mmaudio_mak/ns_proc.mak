#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PP_OPT_COMMON += NSPROC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/nsproc/src

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/nsproc/src\
$(PATH_mmaudio)/nsproc/inc



#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=   \
  audions_api.c \
  audions_kernal.c \
  audions_realft.c 
