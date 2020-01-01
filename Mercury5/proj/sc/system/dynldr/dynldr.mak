#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_dynldr)/src

PATH_H +=\
  $(PATH_dynldr)/inc\
  $(PATH_compression_mdl)/pub

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_dynldr.c \
  sys_dlm_mgr.c	\
  sys_sldlm_mgr.c \
  sys_dpm_mgr.c \
  sys_mmap_mgr.c

