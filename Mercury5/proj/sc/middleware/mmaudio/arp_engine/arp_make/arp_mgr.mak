#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_arp_engine)/arp_mgr/src

PATH_H +=\
  $(PATH_arp_engine)/arp_common/inc\
  $(PATH_arp_engine)/arp_mgr/inc\
  $(PATH_arp_engine)/arp_ips/arp_sw_agc/inc\
  $(PATH_arp_engine)/arp_ips/arp_hw_agc/inc\
  $(PATH_arp_engine)/arp_ips/arp_exp_vol/inc

SRC_C_LIST +=\
  arp_mgr.c\
  arp_mgr_par.c
