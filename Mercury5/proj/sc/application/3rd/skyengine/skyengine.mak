
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

ifeq ($(filter __SKYENGINE__ ,$(PP_OPT_COMMON)),__SKYENGINE__)
PP_OPT_COMMON += __MMI_DSM__
endif

PATH_H +=\
      $(PATH_dynldr)/pub

PATH_H +=\
	  $(PATH_mmicomn)/inc
	  
#------------------------------------------------------------------------------
#	Liste	des fichiers sources	de	la	bibliothèque ou de l'éxecutable a générer
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------

#Add files here
ifeq ($(filter __SKYENGINE__ ,$(PP_OPT_COMMON)),__SKYENGINE__)
REL_SRC_C_LIST += mmidsm.c
REL_SRC_C_LIST += mmidsmapi.c
REL_SRC_C_LIST += mythroad.c
REL_SRC_C_LIST += mrp_ui.c
REL_SRC_C_LIST += sgl_gal.c
REL_SRC_C_LIST += sgl_heap.c
REL_SRC_C_LIST += sgl_rect.c
REL_SRC_C_LIST += sgl_window.c
REL_SRC_C_LIST += smp_list.c
REL_SRC_C_LIST += smp_scrollbar.c
REL_SRC_C_LIST += smp_textinfo.c
REL_SRC_C_LIST += smp_toolbar.c
REL_SRC_C_LIST += mmidsmconvert.c
endif

