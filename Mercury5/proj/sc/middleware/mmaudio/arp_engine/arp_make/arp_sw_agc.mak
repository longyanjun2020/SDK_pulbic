#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_arp_engine)/arp_ips/arp_sw_agc/src

PATH_H +=\
  $(PATH_arp_engine)/arp_common/inc\
  $(PATH_arp_engine)/arp_ips/arp_sw_agc/inc

SRC_C_LIST +=\
  arp_sw_agc.c\
  arp_sw_agc_par.c
