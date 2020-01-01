#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_fc)/src

PATH_I +=\
  $(PATH_fc)/pub
    
PATH_ASM +=\
  $(PATH_fc)/src

PATH_H +=\
  $(PATH_fc)/pub

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
  abi_headers_fc.c
else
SRC_C_LIST =\
  abi_headers_fc.c
endif

ifeq ($(COMPILER_VERSION),X86LINUXGCC)
SRC_ASM_LIST =
endif
