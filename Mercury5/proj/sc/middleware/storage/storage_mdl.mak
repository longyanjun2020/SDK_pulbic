#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_storage_mdl)/src
  
PATH_H +=\
    $(PATH_storage_mdl)/inc\
    $(PATH_storage)/pub\
    $(PATH_storage_mdl)/pub\
    $(PATH_disk)/pub

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_storage_mdl.c\
    mdl_stg2gpd.c\
    app_mount.c

