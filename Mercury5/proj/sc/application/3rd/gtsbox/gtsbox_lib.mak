
#
#	Important :	This software is protected	by	Copyright and the	information
#					contained herein is confidential. Distribution,	reproduction
#					as	well as exploitation	and transmission of its	contents	is
#					not allowed	except if expressly permitted. Infringments
#					result in damage claims
#					Copyright Wavecom	S.A. (c)	$JustDate:$
#

# ****************************************************************************

# Add vendor pre-build library here

ifeq ($(filter __MMI_GTSBOX__ ,$(PP_OPT_COMMON)),__MMI_GTSBOX__)
	LIBS_3RD += gtsbox_gts.lib

ifeq (__LCM_QVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 240x320_rvct_mblog.lib
endif

ifeq (__LCM_WQVGA_240_400__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 240x400_rvct_mblog.lib
endif

ifeq (__LCM_QCIF_PLUS__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 176x220_rvct_mblog.lib
endif

ifeq (__LCM_HVGA_320_480__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 320x480_rvct_mblog.lib
endif

ifeq (__LCM_WVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 480x800_rvct_mblog.lib
endif

ifeq (__LCM_LANDSCAPE_QVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 320x240_rvct_mblog.lib
endif

ifeq (__LCM_LANDSCAPE_QCIF__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 220x176_rvct_mblog.lib
endif

ifeq (__LCM_LANDSCAPE_WQVGA_240_400__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 400x240_rvct_mblog.lib
endif

ifeq (__LCM_LANDSCAPE_HVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 480x320_rvct_mblog.lib
endif

ifeq (__LCM_LANDSCAPE_WVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 480x800_rvct_mblog.lib
endif

ifeq (__LCM_QQVGA__, $(strip $(LCM_RESOLUTION)))
LIBS_3RD += 128x160_rvct_mblog.lib
endif


endif
