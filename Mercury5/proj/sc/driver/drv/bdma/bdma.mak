
#
#  Important : This software is protected by Copyright and the information
#              contained herein is confidential. Distribution, reproduction
#              as well as exploitation and transmission of its contents is
#              not allowed except if expressly permitted. Infringments
#              result in damage claims.
#              Copyright Wavecom S.A. (c) $JustDate:$
#

# ****************************************************************************
# *  File    : $Workfile:   $       $Revision:   1.0  $
# *--------------------------------------------------------------------------*
# *  Scope   :   Description of the library to generate                     *
# *                                                                          *
# *  Notes   :   to launch the compilation of the current library,           *
# *              type from output directory :                                *
# *                   make -f ../gen.mak TARGET=<target>                    *
# *                                                                          *
# *                                                                          *
# *                                                                          *
# *  Changes    :                                                            *
# *--------------------------------------------------------------------------*
# *  Version PVCS  | Date           | Author |   Modification                *
# *--------------------------------------------------------------------------*
# *   $Log:$
# ****************************************************************************




#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS	= lib

# c/cpp source code for this library 
PATH_C +=\
  $(PATH_bdma)/src

# header file folder for this library 
PATH_H +=\
  $(PATH_bdma)/inc\
  $(PATH_bdma)/pub\
  $(PATH_hal)bdma\inc\
  $(PATH_sys)/pub\
  $(PATH_utopia_msos)/inc\
  $(PATH_utopia_common)/inc\
  $(PATH_utopia_chip)/inc
#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
  abi_headers_bdma.c \
  drv_bdma.c \
  bdma_test.c