#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
	$(PATH_drm_util)/src

PATH_H +=\
$(PATH_drm_util)/pub
#-------------------------------------------------------------------------------
#	Extra compiler option for CC
#-------------------------------------------------------------------------------
PP_OPT_COMMON -= O3
PP_OPT_COMMON += O2

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_drm_util.c\
	mdl_drm_util.c
