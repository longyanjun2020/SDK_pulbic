#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_mz)/

PATH_I +=\
  $(PATH_mz)/
PATH_H +=\
  $(PATH_mz)/

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  drv_uminiz.c
