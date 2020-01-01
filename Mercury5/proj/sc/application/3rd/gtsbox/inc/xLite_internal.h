// xstrike lite engine
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_internal.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_INTERNAL_H__
#define __XLITE_INTERNAL_H__

/*!
 * Support platform:
 * MTK: XLITE_MTK
 * GTS EMUX: XLITE_EMUX
 * VRE: XLITE_VRE
 * LVM: XLITE_LVM
 * WINCE: XLITE_WCE
 */

#if defined(XLITE_MTK)

#pragma message ("Platform setting:XLITE_MTK")
#define _XLITE_PLATFORM_ID				1

#elif defined(XLITE_MMK)

#pragma message ("Platform setting:XLITE_MMK")
#define _XLITE_PLATFORM_ID				2

#elif defined(XLITE_EMUX)

#pragma message ("Platform setting:XLITE_EMUX")
#define _XLITE_PLATFORM_ID				3

#elif defined(XLITE_VRE)

#pragma message ("Platform setting:XLITE_VRE")
#define _XLITE_PLATFORM_ID					4

#elif defined(XLITE_WCE)

#pragma message ("Platform setting:XLITE WM")
#define XLITE_NO_NETWORK
#define _XLITE_PLATFORM_ID				5

#elif defined(XLITE_LVM)

#pragma message ("Platform setting:XLITE_LVM")
#define _XLITE_PLATFORM_ID				6

#elif defined(XLITE_WM)
#pragma message ("Platform setting:XLITE_WM")
#	define _XLITE_PLATFORM_ID				7

#elif defined(XLITE_ASNA)
#pragma message ("Platform setting:XLITE_ASNA")
#define _XLITE_PLATFORM_ID				8
#define xlite_sprintf sprintf

#else

#pragma message "Unknown platform: optional:[ XLITE_MTK , XLITE_EMUX , XLITE_VRE ]"

#endif

#include "xlite_type.h"
#include "xlite_sal.h"


#endif
