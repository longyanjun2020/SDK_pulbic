
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
#	Description des variables propre à la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_bus)/src

#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable à générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
   opic_bus.c\
	bus_cork.c


SRC_ASM_LIST =

