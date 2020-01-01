#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_misc)/src
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =

#
#-------------------------------------------------------------------------------
#   List of source files of verification to generate
#-------------------------------------------------------------------------------
#ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += misc_test.c
#endif


#