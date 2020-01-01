#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H +=\
  $(PATH_sys)/inc

PATH_C +=\
  $(PATH_cpu_mdl)/src

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_cpu_mdl.c\
  mdl_cpu.c