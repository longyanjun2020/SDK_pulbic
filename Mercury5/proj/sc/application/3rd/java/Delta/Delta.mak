
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


#------------------------------------------------------------------------------
#	Liste	des fichiers sources	de	la	bibliothèque ou de l'éxecutable a générer
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------
#REL_SRC_C_LIST

####ifeq ($(filter __JAVA_DELTA__ ,$(PP_OPT_COMMON)),__JAVA_DELTA__)
SRC_C_LIST += java_debug.c
SRC_C_LIST += jpxy_app.c
SRC_C_LIST += java_app.c
SRC_C_LIST += DualMemPool.c
SRC_C_LIST += java_in_msg.c
SRC_C_LIST += java_out_msg.c
SRC_C_LIST += nemomp.c
SRC_C_LIST += nemomp_charconv.c
SRC_C_LIST += nemomp_comm.c
SRC_C_LIST += nemomp_files.c
SRC_C_LIST += nemomp_network.c
SRC_C_LIST += nemomp_time.c
SRC_C_LIST += nemomp_standard.c
SRC_C_LIST += nemomp_device.c
SRC_C_LIST += nemomp_display.c
SRC_C_LIST += nemomp_event.c
SRC_C_LIST += nemomp_font.c
SRC_C_LIST += nemomp_media_audio.c
SRC_C_LIST += nemomp_mmi.c
SRC_C_LIST += nemomp_storage.c
SRC_C_LIST += nemomp_ams.c
SRC_C_LIST += nemomp_files_adv.c
SRC_C_LIST += nemomp_push.c
SRC_C_LIST += nemomp_props.c 
SRC_C_LIST += nemomp_wma_sms.c

SRC_C_LIST += platform_malloc.c
#SRC_C_LIST += nemomp_malloc.c

SRC_C_LIST += java_event_queue.c
SRC_C_LIST += java_ams.c
SRC_C_LIST += java_ams_pars.c
SRC_C_LIST += java_ams_http.c
SRC_C_LIST += java_preinstall.c
SRC_C_LIST += JamlistMemPool.c
SRC_C_LIST += nemomp_media_ctrl.c
SRC_C_LIST += nemomp_media_dev.c
SRC_C_LIST += nemomp_media_video.c
#####endif


