
#
#	Important :	This software is protected	by	Copyright and the	information
#					contained herein is confidential. Distribution,	reproduction
#					as	well as exploitation	and transmission of its	contents	is
#					not allowed	except if expressly permitted. Infringments
#					result in damage claims
#					Copyright Wavecom	S.A. (c)	$JustDate:$
#

# ****************************************************************************
# *  File	 :	$Workfile:$			$Revision:$
# *--------------------------------------------------------------------------*
# *  Scope	 :	  Description of the	librarie	to	generate							  *
# *																								  *
# *  Notes	 :	  to launch	the compilation of the current library,			  *
# *				  type from	output directory :										  *
# *						 make	-r	-f	..//gen.mak	TARGET=<target>					  *
# *																								  *
# *																								  *
# *																								  *
# *  Changes	 :																				  *
# *--------------------------------------------------------------------------*
# *  Version VSS	| Date			  | Author |	Modification					  *
# *--------------------------------------------------------------------------*
# *	$Log:$
#
# ****************************************************************************

#SCE_OPTIONS = -R -G -Cysc.cfg -N
#SCE_OPTIONS = -R -N

#------------------------------------------------------------------------------
#	Description	des variables propre	a la bibliothèque
#	Description	of	some variables	own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary	module (bin)
PROCESS		= lib

PATH_sdkven_example = $(PATH_vendor)/sdkven_example
PATH_C +=\
	  $(PATH_sdkven_example)/src
PATH_H +=\
	  $(PATH_sdkven_example)/inc\
  	  $(PATH_MsWrapper)/inc\
  	  $(PATH_dynldr)/pub

#------------------------------------------------------------------------------
#	Liste	des fichiers sources	de	la	bibliothèque ou de l'éxecutable a générer
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST += \
	sdkven_task.c\
	test_ven_ap.c\
	test_ven_codec.c\
	test_ven_file.c\
	test_ven_font.c\
	test_ven_graphics.c\
	test_ven_socket.c\
	test_ven_time.c\
 	ftp_client.c\
 	test_throughput.c\
 	sdkven_example.c

ifeq ($(filter __ENABLE_POLARSSL__ ,$(PP_OPT_COMMON)),__ENABLE_POLARSSL__)
SRC_C_LIST += \
	test_ssl.c
endif
