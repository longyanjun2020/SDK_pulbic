#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_dynldr)/src_cus

PATH_H +=\
  $(PATH_dynldr)/inc\
  $(PATH_compression_mdl)/pub

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  sys_dlm_api.c\
  sys_sldlm_cfg.c\
  sys_sldlm_api.c\
  sys_dpm_cfg.c\
  sys_dpm_api.c\
  sys_mmap_cfg.c\
  sys_mmap_api.c

