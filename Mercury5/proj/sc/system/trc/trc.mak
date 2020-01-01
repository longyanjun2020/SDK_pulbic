#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_trc)/src

PATH_H += \
     $(PATH_trc)/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
  abi_headers_trc.c\
  rm_trc.c\
  rm_rpc.c
else
SRC_C_LIST =\
  abi_headers_trc.c\
  rm_trc.c\
  rm_rpc.c\
  trc_dummy.c
endif