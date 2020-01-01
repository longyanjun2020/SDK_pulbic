#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_ut_mdl)/src
  
PATH_H +=\
$(PATH_ut_mdl)/inc\
$(PATH_keypad_mdl)/pub\
$(PATH_image_codec)/pub\
$(PATH_gss)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
    abi_headers_ut_mdl.c\
    mdl_unittest.c
