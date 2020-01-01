
#
#   Important : This software is protected by Copyright and the information
#               contained herein is confidential. Distribution, reproduction
#               as well as exploitation and transmission of its contents is
#               not allowed except if expressly permitted. Infringments
#               result in damage claims
#               Copyright Wavecom   S.A. (c)    $JustDate:$
#

# ****************************************************************************
# *  File    :  $Workfile:$         $Revision:$
# *--------------------------------------------------------------------------*
# *  Scope   :    Description of the librarie to generate                    *
# *                                                                          *
# *  Notes   :    to launch the compilation of the current library,          *
# *               type from output directory :                               *
# *                      make   -r  -f  ..//gen.mak TARGET=<target>          *
# *                                                                          *
# *                                                                          *
# *                                                                          *
# *  Changes     :                                                           *
# *--------------------------------------------------------------------------*
# *  Version VSS    | Date            | Author |    Modification             *
# *--------------------------------------------------------------------------*
# * $Log:$
#
# ****************************************************************************



#------------------------------------------------------------------------------
#   Description of some variables own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary    module (bin)
PROCESS     = lib
PATH_C +=\
    $(PATH_mmmanager_lib)/src

#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST += \
    MML_Concurrent.c


