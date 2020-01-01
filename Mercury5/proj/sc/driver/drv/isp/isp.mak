# ****************************************************************************
# *  File    : $Workfile:   $       $Revision:  $
# *--------------------------------------------------------------------------*
# *  Scope   :   Description of the library to generate                     *
# *                                                                          *
# *                                                                          *
# ****************************************************************************




#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_isp)/src


PATH_H += $(PATH_isp_hal)/inc\
          $(PATH_isp)/inc\
          $(PATH_isp)/pub\
          $(PATH_acc_inc)/pub\
          $(PATH_isp_mdl)/inc

#  $(PATH_emi)/pub\
#  $(PATH_flash)/pub\
#  $(PATH_bus)/inc\
#  $(PATH_flash)/inc\
#  $(PATH_flash_hal)/inc\

#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =\
  drv_isp.c\
  drv_isp_shadow.c
