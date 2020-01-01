PATH_H = \
	$(PATH_core)/pub \
    $(PATH_fc)/pub \
    $(PATH_mae)/pub

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
ifeq ($(filter __IME_MMI_MY__, $(PP_OPT_COMMON)), __IME_MMI_MY__)
SRC_C_LIST += mylang.c
endif

ifeq ($(filter __IME_MMI_SG__ , $(PP_OPT_COMMON)),__IME_MMI_SG__)
SRC_C_LIST += \
	WD_PublicIme.c \
	SG_English_Public.c
endif
ifeq ($(filter __IME_MMI_SG_ARABIC__ , $(PP_OPT_COMMON)),__IME_MMI_SG_ARABIC__)
    SRC_C_LIST += SG_Arabic_Public.c
endif
ifeq ($(filter __IME_MMI_SG_FRENCH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_FRENCH__)
    SRC_C_LIST += SG_French_Public.c
endif
ifeq ($(filter __IME_MMI_SG_INDONESIAN__ , $(PP_OPT_COMMON)),__IME_MMI_SG_INDONESIAN__)
    SRC_C_LIST += SG_Indonesian_Public.c
endif
ifeq ($(filter __IME_MMI_SG_VIETNAMESE__ , $(PP_OPT_COMMON)),__IME_MMI_SG_VIETNAMESE__)
    SRC_C_LIST += SG_Vietnamese_Public.c
endif
ifeq ($(filter __IME_MMI_SG_MALAY__ , $(PP_OPT_COMMON)),__IME_MMI_SG_MALAY__)
    SRC_C_LIST += SG_Malay_Public.c
endif
ifeq ($(filter __IME_MMI_SG_THAI__ , $(PP_OPT_COMMON)),__IME_MMI_SG_THAI__)
    SRC_C_LIST += SG_Thai_Public.c
endif
ifeq ($(filter __IME_MMI_SG_PORTUGUESE__ , $(PP_OPT_COMMON)),__IME_MMI_SG_PORTUGUESE__)
    SRC_C_LIST += SG_Portuguese_Public.c
endif
ifeq ($(filter __IME_MMI_SG_POLISH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_POLISH__)
    SRC_C_LIST += SG_Polish_Public.c
endif
ifeq ($(filter __IME_MMI_SG_PERSIAN__ , $(PP_OPT_COMMON)),__IME_MMI_SG_PERSIAN__)
    SRC_C_LIST += SG_Persian_Public.c
endif
ifeq ($(filter __IME_MMI_SG_ITALIAN__ , $(PP_OPT_COMMON)),__IME_MMI_SG_ITALIAN__)
    SRC_C_LIST += SG_Italian_Public.c
endif
ifeq ($(filter __IME_MMI_SG_CZECH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_CZECH__)
    SRC_C_LIST += SG_Czech_Public.c
endif
ifeq ($(filter __IME_MMI_SG_RUSSIAN__ , $(PP_OPT_COMMON)),__IME_MMI_SG_RUSSIAN__)
    SRC_C_LIST += SG_Russian_Public.c
endif
ifeq ($(filter __IME_MMI_SG_DUTCH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_DUTCH__)
    SRC_C_LIST += SG_Dutch_Public.c
endif
ifeq ($(filter __IME_MMI_SG_GERMAN__ , $(PP_OPT_COMMON)),__IME_MMI_SG_GERMAN__)
    SRC_C_LIST += SG_German_Public.c
endif
ifeq ($(filter __IME_MMI_SG_HINDI__ , $(PP_OPT_COMMON)),__IME_MMI_SG_HINDI__)
    SRC_C_LIST += SG_Hindi_Public.c
endif
ifeq ($(filter __IME_MMI_SG_TURKISH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_TURKISH__)
    SRC_C_LIST += SG_Turkish_Public.c
endif
ifeq ($(filter __IME_MMI_SG_BENGALI__ , $(PP_OPT_COMMON)),__IME_MMI_SG_BENGALI__)
    SRC_C_LIST += SG_Bengali_Public.c
endif
ifeq ($(filter __IME_MMI_SG_GREEK__ , $(PP_OPT_COMMON)),__IME_MMI_SG_GREEK__)
    SRC_C_LIST += SG_Greek_Public.c
endif
ifeq ($(filter __IME_MMI_SG_SPANISH__ , $(PP_OPT_COMMON)),__IME_MMI_SG_SPANISH__)
    SRC_C_LIST += SG_Spanish_Public.c
endif

ifeq ($(filter __IME_MMI_CSTAR__, $(PP_OPT_COMMON)), __IME_MMI_CSTAR__)
    SRC_C_LIST += kmx_version.c
endif 

ifeq ($(filter __IME_MMI_MY__ ,$(PP_OPT_COMMON)),__IME_MMI_MY__)
MMI_PATH_H += $(PATH_ime)/my/inc
endif

ifeq ($(filter __IME_MMI_SG__ ,$(PP_OPT_COMMON)),__IME_MMI_SG__)
MMI_PATH_H += $(PATH_ime)/sg/inc 
endif
