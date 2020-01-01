#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to Customizable source files
PATH_C +=\
  $(PATH_trc)/src_cus

PATH_H += \
     $(PATH_trc)/inc\
     $(PATH_gpd_mdl)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  opec_dbg.c\
  rm_tools.c
