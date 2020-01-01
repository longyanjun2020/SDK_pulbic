#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H +=\
  $(PATH_vdr_top)/pub\
  $(PATH_vdr)/pub\
  $(PATH_jpe)/pub\
  $(PATH_camera_mdl)/pub\
  $(PATH_scl)/pub\
  $(PATH_vdr)/inc/cus

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
	mdl_vdr_isw_main.c\
	mdl_vdr_mem.c\
	mdl_vdr_system.c\
	mdl_vdr_vdo_h263i.c\
	mdl_vdr_vdo_utility.c\
	mdl_vdr_biliner.c
	
