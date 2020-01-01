#
#  Important : This software is protected by Copyright and the information
#              contained herein is confidential. Distribution, reproduction
#              as well as exploitation and transmission of its contents is
#              not allowed except if expressly permitted. Infringments
#              result in damage claims.
#              Copyright Wavecom S.A. (c) $Date:  $
#

# ****************************************************************************
# *  File    : $Workfile:   $       $Revision:  $
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
# *  Version PVCS                                                            *
# *--------------------------------------------------------------------------*
# *   $LogWavecom:$
# --------------------------------------------------------------------------
#  Date     | Author | Revision       | Description
# ----------+--------+----------------+-------------------------------------
# ****************************************************************************




#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=\
  $(PATH_rai)/src

PATH_H +=\
$(PATH_rai)/pub  
#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_rai.c\
  rai_cache.c

