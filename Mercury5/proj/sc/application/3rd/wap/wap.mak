PATH_H = \
    $(PATH_audio)/pub \
    $(PATH_core)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_dynldr)/pub \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_fms)/pub \
    $(PATH_i18n)/inc \
    $(PATH_mae)/pub \
    $(PATH_mmmanager)/pub \
    $(PATH_mmmanager)/inc \
    $(PATH_mserv)/inc \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_utility)/inc \
    $(PATH_wap)/inc \
    $(PATH_wap)/itf

MMI_PATH_H = 

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
SRC_C_LIST += wap_action.c
SRC_C_LIST += wap_app.c
SRC_C_LIST += wap_comm.c
SRC_C_LIST += wap_config.c
SRC_C_LIST += wap_display.c
SRC_C_LIST += wap_mime.c
SRC_C_LIST += wap_porting.c

#------------------------------------------------------------------------------
#	Below complire option sholud be sync to WAP kernel and i18n mak file
#------------------------------------------------------------------------------
ifneq ($(filter __GB2312_TO_UNICODE__ __UNICODE_TO_GB2312__, $(PP_OPT_COMMON)),)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += \
	I18N_GBK_SUPPORT
else
PP_OPT_COMMON += \
	I18N_GB2312_SUPPORT
endif
endif

PP_OPT_COMMON += \
    DB_USING_CACHE
