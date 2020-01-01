#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
  $(PATH_keypad_mdl)/src
  
PATH_H +=\
$(PATH_keypad_mdl)/inc\
$(PATH_keypad_mdl)/pub\
$(PATH_acc_inc)/pub\
$(PATH_lcd)/pub\
$(PATH_gpd_mdl)/pub\
$(PATH_gpd)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_keypad_mdl.c\
  mdl_keypad.c
