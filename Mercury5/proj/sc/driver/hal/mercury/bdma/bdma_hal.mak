#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# c/cpp source code for this library 
PATH_C +=\
  $(PATH_bdma_hal)/src\

# header file folder for this library 
PATH_H +=\
  $(PATH_bdma_hal)/inc\
  $(PATH_hal)timer/pub\
  $(PATH_sys)/pub\

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_bdma.c  