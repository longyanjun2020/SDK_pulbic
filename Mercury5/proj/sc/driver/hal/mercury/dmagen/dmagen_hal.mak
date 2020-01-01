#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_dmagen.c

# c/cpp source code for this library 
PATH_C +=\
  $(PATH_dmagen_hal)/src\

# header file folder for this library 
PATH_H +=\
  $(PATH_dmagen_hal)/inc\
  $(PATH_cam_os_wrapper)/pub\

