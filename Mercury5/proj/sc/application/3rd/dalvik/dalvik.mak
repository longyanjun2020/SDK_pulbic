
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

####ifeq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)),__DALVIK__)
SRC_C_LIST += syscall.c
SRC_C_LIST += dvk_device.c
SRC_C_LIST += dvk_dialog.c
SRC_C_LIST += dvk_display.c
SRC_C_LIST += dvk_kpd.c
SRC_C_LIST += dvm_mmapi.c
SRC_C_LIST += dvm_wma.c
SRC_C_LIST += dvk_network.c
SRC_C_LIST += jpxy_task.c
SRC_C_LIST += java_task.c
SRC_C_LIST += java_debug.c
SRC_C_LIST += java_event_queue.c
SRC_C_LIST += java_out_msg.c
SRC_C_LIST += dvm_storage.c
SRC_C_LIST += Dalvik_ams.c
SRC_C_LIST += Dalvik_installer.c
SRC_C_LIST += Dalvik_SuiteInfo.c
SRC_C_LIST += java_ams.c
SRC_C_LIST += java_ams_pars.c
SRC_C_LIST += dvk_permission.c
SRC_C_LIST += dvm_assert.c
SRC_C_LIST += dvk_utils.c
SRC_C_LIST += dvm_alarm.c

MMI_PATH_H += \
	$(PATH_mae)/extras/util
#####endif



