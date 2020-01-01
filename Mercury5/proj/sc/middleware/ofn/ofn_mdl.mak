#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_ofn_mdl)/src


PATH_H +=\
$(PATH_keypad_mdl)/pub\
$(PATH_drv)/ofn/pub\
$(PATH_ofn_mdl)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_ofn_mdl.c\
  mdl_ofn.c

PATH_H+=$(PATH_ofn_mdl)\inc
  
