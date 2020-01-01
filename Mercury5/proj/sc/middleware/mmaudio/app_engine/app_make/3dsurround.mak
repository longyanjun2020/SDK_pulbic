#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_app_engine)/app_ips/3dsurround/src

PATH_H +=\
  $(PATH_app_engine)/app_common/inc\
  $(PATH_app_engine)/app_ips/3dsurround/inc

SRC_C_LIST +=\
  mstarsurround.c\
  mstarsurround_par.c