# Created by yunchu for MMI release adaption

#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=   $(PATH_batt)/src

#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------


SRC_C_LIST = \
    bat_cork.c
