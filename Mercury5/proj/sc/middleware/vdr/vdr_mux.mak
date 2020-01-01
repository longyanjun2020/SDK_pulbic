#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_vdr_mux)/src\
  $(PATH_vdr_mux)/src/mx
  
#ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
#PATH_C +=\
#  $(PATH_vdr)/src/vtmx
#PATH_H +=\
#  $(PATH_vdr)/inc/vtmx
#endif

PATH_H +=\
  $(PATH_vdr_mux)/pub\
  $(PATH_vdr_mux)/inc/mx\
  $(PATH_camera_mdl)/pub\
  $(PATH_vdr)/inc\
  $(PATH_scl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
       mdl_vdr_mx_atomarray.c\
	mdl_vdr_mx_mp4atom.c\
	mdl_vdr_mx_mp4creator.c\
	mdl_vdr_mx_mp4file.c\
	mdl_vdr_mx_mp4file_io.c\
	mdl_vdr_mx_mp4property.c\
	mdl_vdr_mx_mp4track.c\
	mdl_vdr_mx_util.c\
	mdl_vdr_sem_rbuffer.c

#ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
#SRC_C_LIST +=\
#	mdl_vdr_mx_vtmp4creator.c\
#	mdl_vdr_mx_vtmp4file.c\
#	mdl_vdr_mx_vtutil.c\
#	mdl_vdr_vtmem.c
#endif	
