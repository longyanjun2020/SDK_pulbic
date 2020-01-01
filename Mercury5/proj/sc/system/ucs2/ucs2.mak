#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_ucs2)/src

PATH_H +=\
    $(PATH_ucs2)/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	abi_headers_ucs2.c \
	util_ucs2.c \
	util_mem_ucs2.c
