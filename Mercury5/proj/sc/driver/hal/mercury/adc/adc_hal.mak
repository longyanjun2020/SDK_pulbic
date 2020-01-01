#------------------------------------------------------------------------------
#	Description des variables propre 
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=\
  $(PATH_adc_hal)/src
  
PATH_H +=\
  $(PATH_adc_hal)/pub  
#------------------------------------------------------------------------------
#	Liste des fichiers sources 
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
	hal_saradc.c
