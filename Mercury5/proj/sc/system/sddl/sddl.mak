#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H +=\
    $(PATH_sddl)/pub \
    $(PATH_drvutil_hal)/inc
    
PATH_C +=\
  $(PATH_sddl)/src

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_sddl.c \
  sys_sddl.c
