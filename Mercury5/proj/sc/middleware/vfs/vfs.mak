#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
	$(PATH_vfs)/src

PATH_H +=\
	$(PATH_vfs)/itf\
	$(PATH_vfs)/inc\
	$(PATH_storage)/pub\
	$(PATH_storage_mdl)/pub\
  $(PATH_mtmgr)/pub\
  $(PATH_disk)/pub\
  $(PATH_rai)/pub


#-------------------------------------------------------------------------------
#	Extra compiler option for CC
#-------------------------------------------------------------------------------
PP_OPT_COMMON -= O3               
PP_OPT_COMMON += O2  

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
	abi_headers_vfs.c \
	vfs_file.c \
	vfs_fat.c \
	vfs_fat_tbl.c \
	vfs_fat_internal.c \
	vfs_fat_parser.c \
	vfs_verify.c \
	vfs_fat_wrapper.c
else    
SRC_C_LIST =\
 vfs_fat_dummy.c
endif


