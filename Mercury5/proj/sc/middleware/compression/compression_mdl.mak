#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_compression_mdl)/src

PATH_H +=\
    $(PATH_compression_mdl)/inc\
    $(PATH_compression_mdl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_compression.c\
    mdl_cmp.c\
    lzf_d.c\
    Lzma2Dec.c\
    LzmaDec.c\
    MsLzma.c\
    lzf_c.c\
    fastlz.c\
    bra.c