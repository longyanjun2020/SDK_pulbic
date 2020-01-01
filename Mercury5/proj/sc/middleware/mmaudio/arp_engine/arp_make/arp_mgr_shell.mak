#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C +=\
  $(PATH_arp_engine)/arp_mgr_shell/src

PATH_H +=\
  $(PATH_arp_engine)/arp_common/inc\
  $(PATH_arp_engine)/arp_mgr/inc\
  $(PATH_arp_engine)/arp_mgr_shell/pub

SRC_C_LIST +=\
  arp_mgr_shell.c\
  abi_headers_arp_engine.c