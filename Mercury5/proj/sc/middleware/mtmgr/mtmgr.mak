#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=\
	$(PATH_mtmgr)/src

PATH_H +=\
	$(PATH_mtmgr)/itf\
    $(PATH_storage)/pub\
    $(PATH_storage_mdl)/pub\
    $(PATH_mtmgr)/pub\
    $(PATH_disk)/pub

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
    abi_headers_mtmgr.c\
    mtmgr.c
else    
SRC_C_LIST =\
    mtmgr_dummy.c
endif
