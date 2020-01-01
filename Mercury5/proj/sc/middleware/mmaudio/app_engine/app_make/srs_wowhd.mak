#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_app_engine)/app_ips/srs_wowhd/src

PATH_H +=\
  $(PATH_mmaudio)/audiocontrol/inc\
  $(PATH_srs_wowhd_3rd)/srs_common/inc\
  $(PATH_srs_wowhd_3rd)/srs_sa_trubass/inc\
  $(PATH_srs_wowhd_3rd)/srs_srs3d/inc\
  $(PATH_srs_wowhd_3rd)/srs_wowhd/inc\
  $(PATH_app_engine)/app_common/inc\
  $(PATH_app_engine)/app_mgr/inc\
  $(PATH_app_engine)/app_ips/srs_wowhd/inc\
  $(PATH_drm_vfs)/pub

SRC_C_LIST +=\
  srs_wowhd.c\
  srs_wowhd_par.c