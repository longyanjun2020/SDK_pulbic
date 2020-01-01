#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_app_engine)/app_mgr/src

PATH_H +=\
  $(PATH_app_engine)/app_common/inc\
  $(PATH_app_engine)/app_mgr/inc\
  $(PATH_app_engine)/app_ips/timepitch_stretch/inc\
  $(PATH_app_engine)/app_ips/time_stretch/inc\
  $(PATH_app_engine)/app_ips/sc_fade/inc\
  $(PATH_app_engine)/app_ips/reverb/inc\
  $(PATH_app_engine)/app_ips/peq/inc\
  $(PATH_app_engine)/app_ips/hw_peq/inc\
  $(PATH_app_engine)/app_ips/hw_geq/inc\
  $(PATH_app_engine)/app_ips/hw_drc/inc\
  $(PATH_app_engine)/app_ips/hard_limiter/inc\
  $(PATH_app_engine)/app_ips/exp_vol/inc\
  $(PATH_app_engine)/app_ips/drclookahead_limiter/inc\
  $(PATH_app_engine)/app_ips/drc_limiter/inc\
  $(PATH_app_engine)/app_ips/drc_limiter_v2/inc\
  $(PATH_app_engine)/app_ips/3dsurround/inc\
  $(PATH_app_engine)/app_ips/bass/inc\
  $(PATH_app_engine)/app_ips/srs_wowhd/inc\
  $(PATH_srs_wowhd_3rd)/srs_common/inc\
  $(PATH_srs_wowhd_3rd)/srs_sa_trubass/inc\
  $(PATH_srs_wowhd_3rd)/srs_srs3d/inc\
  $(PATH_srs_wowhd_3rd)/srs_wowhd/inc

  
SRC_C_LIST +=\
  app_mgr.c\
  app_mgr_par.c
