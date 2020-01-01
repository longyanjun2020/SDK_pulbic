#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_spinand_hal)/src
PATH_H +=\
  $(PATH_spinand_hal)/inc\
  $(PATH_spinand)/inc\
  $(PATH_bdma)/inc\
  $(PATH_bdma)/pub\
  $(PATH_hal)bdma\inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_spinand.c