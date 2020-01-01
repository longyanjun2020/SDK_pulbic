#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS	= lib

#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
    drv_dmagen.c

# c/cpp source code for this library 
PATH_C +=\
  $(PATH_dmagen)/src

# header file folder for this library 
PATH_H +=\
  $(PATH_dmagen)/inc\
  $(PATH_hal)dmagen\inc\
  $(PATH_cam_os_wrapper)/pub\

