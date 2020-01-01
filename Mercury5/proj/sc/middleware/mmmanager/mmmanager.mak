
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
    $(PATH_mmmanager)/src

PATH_H +=\
  $(PATH_emi)/pub\
  $(PATH_gss)/pub\
  $(PATH_image_codec)/pub\
  $(PATH_avp)/pub\
  $(PATH_gpd_mdl)/pub
#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------
REL_SRC_C_LIST += \
            MML_Manager.c \
            MML_Utility.c \
            MML_Audio.c \
            MML_Video.c \
            MML_Image.c \
            MML_Display.c \
            MML_Game.c \
            MML_Usb.c \
            MML_Tv.c \
            MML_Camera.c \
            MML_Radio.c \
            MML_Gps.c \
            MML_Wlan.c \
            MML_VideoSdk.c \
            MML_Rfid.c \
            MML_CommTask.c \
            srv_resmgr_mml_glue.c \
			abi_headers_mmmanager.c \

SRC_ASM_LIST =

