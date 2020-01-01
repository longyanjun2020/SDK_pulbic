/***********************************************************************
Filename   : rvccorstrings.h
Description: ccore interfaces string generation
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
#ifndef RV_CCORE_STRINGS_H
#define RV_CCORE_STRINGS_H

#include "rvconfig.h"
#include "rvtypes.h"


/******************************************************************
                  Static check strings
 ******************************************************************/
#if (RV_CHECK_MASK & RV_CHECK_NULL)
#define RV_NULLCHECK_STRING "on"
#else
#define RV_NULLCHECK_STRING "off"
#endif
#if (RV_CHECK_MASK & RV_CHECK_RANGE)
#define RV_RANGECHECK_STRING "on"
#else
#define RV_RANGECHECK_STRING "off"
#endif
#if (RV_CHECK_MASK & RV_CHECK_OTHER)
#define RV_OTHERCHECK_STRING "on"
#else
#define RV_OTHERCHECK_STRING "off"
#endif

#define RV_CHECK_STRING "@(#)CHECKS" \
    ": NULL=" RV_NULLCHECK_STRING \
    ", Range=" RV_RANGECHECK_STRING \
    ", Other=" RV_OTHERCHECK_STRING




/******************************************************************
                  Operating systems strings
 ******************************************************************/

#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS)
#if (RV_OS_VERSION == RV_OS_SOLARIS_2_6)
#define RV_OS_STRING "Solaris 2.6"
#elif (RV_OS_VERSION == RV_OS_SOLARIS_7)
#define RV_OS_STRING "Solaris 7"
#elif (RV_OS_VERSION == RV_OS_SOLARIS_8)
#define RV_OS_STRING "Solaris 8"
#elif (RV_OS_VERSION == RV_OS_SOLARIS_9)
#define RV_OS_STRING "Solaris 9"
#elif (RV_OS_VERSION == RV_OS_SOLARIS_10)
#define RV_OS_STRING "Solaris 10"
#else
#define RV_OS_STRING "Solaris"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_LINUX)
#if (RV_OS_VERSION == RV_OS_LINUX_REDHAT_6_0)
#define RV_OS_STRING "Linux 6.0"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_6_1)
#define RV_OS_STRING "Linux 6.1"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_6_2)
#define RV_OS_STRING "Linux 6.2"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_7_0)
#define RV_OS_STRING "Linux 7.0"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_7_1)
#define RV_OS_STRING "Linux 7.1"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_7_2)
#define RV_OS_STRING "Linux 7.2"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_7_3)
#define RV_OS_STRING "Linux 7.3"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_9)
#define RV_OS_STRING "Linux 9"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_WS)
#define RV_OS_STRING "Linux WS"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_AS)
#define RV_OS_STRING "Linux AS"
#elif (RV_OS_VERSION == RV_OS_LINUX_REDHAT_ES)
#define RV_OS_STRING "Linux ES"
#elif (RV_OS_VERSION == RV_OS_LINUX_MVISTA_2_1)
#define RV_OS_STRING "MontaVista 2.1"
#elif (RV_OS_VERSION == RV_OS_LINUX_MVISTA_3_0)
#define RV_OS_STRING "MontaVista 3.0"
#elif (RV_OS_VERSION == RV_OS_LINUX_MVISTA_3_1)
#define RV_OS_STRING "MontaVista 3.1"
#elif (RV_OS_VERSION == RV_OS_LINUX_MVISTA_4_0)
#define RV_OS_STRING "MontaVista 4.0"
#elif (RV_OS_VERSION == RV_OS_LINUX_MVISTA_5_0)
#define RV_OS_STRING "MontaVista 5.0"
#elif (RV_OS_VERSION == RV_OS_LINUX_UCLINUX_2_4)
#define RV_OS_STRING "uClinux 2.4"
#elif (RV_OS_VERSION == RV_OS_LINUX_SUSE_9)
#define RV_OS_STRING "SUSE 9"
#elif (RV_OS_VERSION == RV_OS_LINUX_SUSE_8)
#define RV_OS_STRING "SUSE 8"
#else
#define RV_OS_STRING "Linux"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_WIN32)
#if (RV_OS_VERSION == RV_OS_WIN32_GENERIC)
#define RV_OS_STRING "Win32 Generic"
#elif (RV_OS_VERSION == RV_OS_WIN32_95)
#define RV_OS_STRING "Win 95"
#elif (RV_OS_VERSION == RV_OS_WIN32_98)
#define RV_OS_STRING "Win 98"
#elif (RV_OS_VERSION == RV_OS_WIN32_NT4)
#define RV_OS_STRING "Win NT4"
#elif (RV_OS_VERSION == RV_OS_WIN32_2000)
#define RV_OS_STRING "Win 2000"
#elif (RV_OS_VERSION == RV_OS_WIN32_XP)
#define RV_OS_STRING "Win XP"
#else
#define RV_OS_STRING "Win32"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_VXWORKS)
#if (RV_OS_VERSION == RV_OS_VXWORKS_2_0)
#define RV_OS_STRING "VxWorks 2.0"
#elif (RV_OS_VERSION == RV_OS_VXWORKS_2_1)
#define RV_OS_STRING "VxWorks 2.1"
#elif (RV_OS_VERSION == RV_OS_VXWORKS_2_2)
#define RV_OS_STRING "VxWorks 2.2"
#elif (RV_OS_VERSION == RV_OS_VXWORKS_2_2_PNE)
#define RV_OS_STRING "VxWorks 2.2 with PNE"
#elif (RV_OS_VERSION == RV_OS_VXWORKS_3_1)
#define RV_OS_STRING "VxWorks 3.1"
#else
#define RV_OS_STRING "VxWorks"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_PSOS)
#if (RV_OS_VERSION == RV_OS_PSOS_2_0)
#define RV_OS_STRING "pSOS 2.0"
#elif (RV_OS_VERSION == RV_OS_PSOS_2_5)
#define RV_OS_STRING "pSOS 2.5"
#elif (RV_OS_VERSION == RV_OS_PSOS_3_0)
#define RV_OS_STRING "pSOS 3.0"
#else
#define RV_OS_STRING "pSOS"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_OSE)
#if (RV_OS_VERSION == RV_OS_OSE_4_2)
#define RV_OS_STRING "OSE 4.2"
#elif (RV_OS_VERSION == RV_OS_OSE_4_4)
#define RV_OS_STRING "OSE 4.4"
#elif (RV_OS_VERSION == RV_OS_OSE_4_5)
#define RV_OS_STRING "OSE 4.5"
#elif (RV_OS_VERSION == RV_OS_OSE_4_6)
#define RV_OS_STRING "OSE 4.6"
#else
#define RV_OS_STRING "OSE"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)
#if (RV_OS_VERSION == RV_OS_NUCLEUS_4_4)
#define RV_OS_STRING "Nucleus 4.4"
#else
#define RV_OS_STRING "Nucleus"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY)
#if (RV_OS_VERSION == RV_OS_INTEGRITY_4_0)
#define RV_OS_STRING "INTEGRITY 4.0"
#else
#define RV_OS_STRING "INTEGRITY"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_HPUX)
#if (RV_OS_VERSION == RV_OS_HPUX_10_20)
#define RV_OS_STRING "HPUX 10.20"
#elif (RV_OS_VERSION == RV_OS_HPUX_11)
#define RV_OS_STRING "HPUX 11"
#else
#define RV_OS_STRING "HPUX"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_TRU64)
#if (RV_OS_VERSION == RV_OS_TYPE_TRU64_4_0)
#define RV_OS_STRING "TRU64 4.0"
#elif (RV_OS_VERSION == RV_OS_TYPE_TRU64_5_1)
#define RV_OS_STRING "TRU64 5.1"
#else
#define RV_OS_STRING "TRU64"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE)
#if (RV_OS_VERSION == RV_OS_UNIXWARE_7_1_1)
#define RV_OS_STRING "UnixWare 7.1.1"
#else
#define RV_OS_STRING "UnixWare"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_WINCE)
#if (RV_OS_VERSION == RV_OS_WINCE_2_11)
#define RV_OS_STRING "WinCE 2.11"
#elif (RV_OS_VERSION == RV_OS_WINCE_3_0)
#define RV_OS_STRING "WinCE 3.0"
#elif (RV_OS_VERSION == RV_OS_WINCE_4_0)
#define RV_OS_STRING "WinCE.NET"
#elif (RV_OS_VERSION == RV_OS_WINCE_5_0)
#define RV_OS_STRING "Windows Mobile 5"
#else
#define RV_OS_STRING "WinCE"
#endif
#elif (RV_OS_TYPE == RV_OS_TYPE_MOPI)
#if (RV_OS_VERSION == RV_OS_MOPI_1_4)
#define RV_OS_STRING "MOPI 1.4"
#else
#define RV_OS_STRING "MOPI"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_OSA)
#if (RV_OS_VERSION == RV_OS_OSA_4_1)
#define RV_OS_STRING "OSA 4.1"
#else
#define RV_OS_STRING "OSA"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_FREEBSD)
#if (RV_OS_VERSION == RV_OS_FREEBSD_4_1)
#define RV_OS_STRING "FreeBSD 4.1"
#else
#define RV_OS_STRING "FreeBSD"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_NETBSD)
#if (RV_OS_VERSION == RV_OS_NETBSD_3_0)
#define RV_OS_STRING "NetBSD 3.0"
#else
#define RV_OS_STRING "NetBSD"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_MAC)

#if (RV_OS_VERSION == RV_OS_MAC_DARWIN_8)
#define RV_OS_STRING "MAC Darwin 8"
#else
#define RV_OS_STRING "MAC Darwin"
#endif

#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)
#define RV_OS_STRING "Symbian 7.0"

#elif (RV_OS_TYPE == RV_OS_TYPE_RTK)
#define RV_OS_STRING "RTK x.x"

#else
#define RV_OS_STRING "Unknown OS"
#endif




/******************************************************************
                        Compiler strings
 ******************************************************************/

#if (RV_TOOL_TYPE == RV_TOOL_TYPE_GNU)

/* Actually this should be applied to all RV_TOOL_STRING settings, not
 * just GNU's, e.g. it should be moved BEFORE #if RV_TOOL_TYPE == ...
 */
#if !defined(RV_TOOL_USTRING)

#if (RV_TOOL_VERSION == RV_TOOL_GNU_CYG_2_7)
#define RV_TOOL_STRING "GNU-CygWin 2.7"
#elif (RV_TOOL_VERSION == RV_TOOL_GNU_2_9)
#define RV_TOOL_STRING "GNU 2.9"
#elif (RV_TOOL_VERSION == RV_TOOL_GNU_3_0)
#define RV_TOOL_STRING "GNU 3.0"
#elif (RV_TOOL_VERSION == RV_TOOL_GNU_3_3)
#define RV_TOOL_STRING "GNU 3.3"
#elif (RV_TOOL_VERSION == RV_TOOL_GNU_4_1)
#define RV_TOOL_STRING "GNU 4.1"
#else
#define RV_TOOL_STRING "GNU"
#endif /* RV_TOOL_VERSION == RV_TOOL_GNU_CYG_2_7*/

#else /* defined(RV_TOOL_USTRING) */
#define RV_TOOL_STRING Macro2String(RV_TOOL_USTRING)
#endif /* defined(RV_TOOL_USTRING) */

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_SUN)
#if (RV_TOOL_VERSION == RV_TOOL_SUN_SPARCWORKS_4)
#define RV_TOOL_STRING "SUN SparkWorks 4"
#elif (RV_TOOL_VERSION == RV_TOOL_SUN_WORKSHOP_5)
#define RV_TOOL_STRING "SUN WorkShop 5"
#elif (RV_TOOL_VERSION == RV_TOOL_SUN_FORTE_6)
#define RV_TOOL_STRING "SUN Forte 6"
#else
#define RV_TOOL_STRING "SUN"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_DIAB)
#if (RV_TOOL_VERSION == RV_TOOL_DIAB_4_3)
#define RV_TOOL_STRING "Diab 4.3"
#elif (RV_TOOL_VERSION == RV_TOOL_DIAB_5_5)
#define RV_TOOL_STRING "Diab 5.5"
#else
#define RV_TOOL_STRING "Diab"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_GHS)
#if (RV_TOOL_VERSION == RV_TOOL_GHS_3_0_COMPAT)
#define RV_TOOL_STRING "GHS 3.0compat"
#elif (RV_TOOL_VERSION == RV_TOOL_GHS_3_5)
#define RV_TOOL_STRING "GHS 3.5"
#elif (RV_TOOL_VERSION == RV_TOOL_GHS_3_5_COMPAT)
#define RV_TOOL_STRING "GHS 3.5compat"
#elif (RV_TOOL_VERSION == RV_TOOL_GHS_4_0)
#define RV_TOOL_STRING "GHS 4.0"
#else
#define RV_TOOL_STRING "GHS"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_ADS)
#if (RV_TOOL_VERSION == RV_TOOL_ADS_1_0)
#define RV_TOOL_STRING "ADS 1.0"
#elif (RV_TOOL_VERSION == RV_TOOL_ADS_1_1)
#define RV_TOOL_STRING "ADS 1.1"
#elif (RV_TOOL_VERSION == RV_TOOL_ADS_1_2)
#define RV_TOOL_STRING "ADS 1.2"
#else
#define RV_TOOL_STRING "ADS"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_MSVC)
#if (RV_TOOL_VERSION == RV_TOOL_MSVC_6)
#define RV_TOOL_STRING "Visual C 6"
#elif (RV_TOOL_VERSION == RV_TOOL_MSVC_8)
#define RV_TOOL_STRING "Visual C 2005"
#else
#define RV_TOOL_STRING "Visual C"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_EMVC)
#if (RV_TOOL_VERSION == RV_TOOL_EMVC_3)
#define RV_TOOL_STRING "Embedded Visual C 3.0"
#else
#define RV_TOOL_STRING "Embedded Visual C"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_COMPAQC)
#if (RV_TOOL_VERSION == RV_TOOL_COMPAQC_5_6)
#define RV_TOOL_STRING "CompaqC 5.6"
#elif (RV_TOOL_VERSION == RV_TOOL_COMPAQC_6_4)
#define RV_TOOL_STRING "CompaqC 6.4"
#else
#define RV_TOOL_STRING "CompaqC"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_CADUL)
#if (RV_TOOL_VERSION == RV_TOOL_CADUL_7_00x)
#define RV_TOOL_STRING "CADUL 7.0"
#else
#define RV_TOOL_STRING "CADUL"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_HPUXC)
#if (RV_TOOL_VERSION == RV_TOOL_HPUXC_A_10_32_20)
#define RV_TOOL_STRING "HPUXC A.10.32.20"
#elif (RV_TOOL_VERSION == RV_TOOL_HPUXC_A_11_01_00)
#define RV_TOOL_STRING "HPUXC A.11.01.00"
#else
#define RV_TOOL_STRING "HPUXC"
#endif

#elif (RV_TOOL_TYPE == RV_TOOL_TYPE_MWCCSYM)
#define RV_TOOL_STRING "MWCCSYM"
#else
#define RV_TOOL_STRING "Unknown tool"
#endif




/******************************************************************
                      Architecture strings
 ******************************************************************/

#if (RV_ARCH_ENDIAN == RV_ARCH_BIG_ENDIAN)
#define RV_ARCH_ENDIAN_STRING "Big Endian"
#elif (RV_ARCH_ENDIAN == RV_ARCH_LITTLE_ENDIAN)
#define RV_ARCH_ENDIAN_STRING "Little Endian"
#else
#error "Endian not defined right!"
#endif

#if (RV_ARCH_BITS == RV_ARCH_BITS_32)
#define RV_ARCH_BITS_STRING "32bit"
#elif (RV_ARCH_BITS == RV_ARCH_BITS_64)
#define RV_ARCH_BITS_STRING "64bit"
#else
#error "Bits not defined right!"
#endif




/******************************************************************
                       Interface strings
 ******************************************************************/

#if (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_USER_DEFINED)
#define RV_TIMESTAMP_STRING "UserDefined"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_LINUX)
#define RV_TIMESTAMP_STRING "Linux"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_VXWORKS_NORMAL)
#define RV_TIMESTAMP_STRING "VxWorksNormal"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_VXWORKS_TIMESTAMP)
#define RV_TIMESTAMP_STRING "VxWorksTimestamp"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_PSOS)
#define RV_TIMESTAMP_STRING "pSOS"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_OSE)
#define RV_TIMESTAMP_STRING "OSE"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_NUCLEUS)
#define RV_TIMESTAMP_STRING "NUCLEUS"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_SOLARIS)
#define RV_TIMESTAMP_STRING "Solaris"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_WIN32)
#define RV_TIMESTAMP_STRING "Win32"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_POSIX)
#define RV_TIMESTAMP_STRING "Posix"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_UNIXWARE)
#define RV_TIMESTAMP_STRING "UnixWare"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_MOPI)
#define RV_TIMESTAMP_STRING "MOPI"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_OSA)
#define RV_TIMESTAMP_STRING "OSA"
#elif (RV_TIMESTAMP_TYPE == RV_TIMESTAMP_RTK)
#define RV_TIMESTAMP_STRING "RTK"
#else
#define RV_TIMESTAMP_STRING "Unknown"
#endif

#if (RV_CLOCK_TYPE == RV_CLOCK_LINUX)
#define RV_CLOCK_STRING "Linux"
#elif (RV_CLOCK_TYPE == RV_CLOCK_VXWORKS)
#define RV_CLOCK_STRING "VxWorks"
#elif (RV_CLOCK_TYPE == RV_CLOCK_PSOS)
#define RV_CLOCK_STRING "pSOS"
#elif (RV_CLOCK_TYPE == RV_CLOCK_OSE)
#define RV_CLOCK_STRING "OSE"
#elif (RV_CLOCK_TYPE == RV_CLOCK_NUCLEUS)
#define RV_CLOCK_STRING "NUCLEUS"
#elif (RV_CLOCK_TYPE == RV_CLOCK_SOLARIS)
#define RV_CLOCK_STRING "Solaris"
#elif (RV_CLOCK_TYPE == RV_CLOCK_WIN32)
#define RV_CLOCK_STRING "Win32"
#elif (RV_CLOCK_TYPE == RV_CLOCK_TRU64)
#define RV_CLOCK_STRING "TRU64"
#elif (RV_CLOCK_TYPE == RV_CLOCK_UNIXWARE)
#define RV_CLOCK_STRING "UnixWare"
#elif (RV_CLOCK_TYPE == RV_CLOCK_MOPI)
#define RV_CLOCK_STRING "MOPI"
#elif (RV_CLOCK_TYPE == RV_CLOCK_OSA)
#define RV_CLOCK_STRING "OSA"
#elif (RV_CLOCK_TYPE == RV_CLOCK_RTK)
#define RV_CLOCK_STRING "RTK"
#else
#define RV_CLOCK_STRING "Unknown"
#endif

#if (RV_TM_TYPE == RV_TM_POSIX)
#define RV_TM_STRING "Posix"
#elif (RV_TM_TYPE == RV_TM_VXWORKS)
#define RV_TM_STRING "VxWorks"
#elif (RV_TM_TYPE == RV_TM_PSOS)
#define RV_TM_STRING "pSOS"
#elif (RV_TM_TYPE == RV_TM_OSE)
#define RV_TM_STRING "OSE"
#elif (RV_TM_TYPE == RV_TM_NUCLEUS)
#define RV_TM_STRING "NUCLEUS"
#elif (RV_TM_TYPE == RV_TM_WIN32)
#define RV_TM_STRING "Win32"
#elif (RV_TM_TYPE == RV_TM_WINCE)
#define RV_TM_STRING "WinCE"
#elif (RV_TM_TYPE == RV_TM_MOPI)
#define RV_TM_STRING "MOPI"
#elif (RV_TM_TYPE == RV_TM_OSA)
#define RV_TM_STRING "OSA"
#elif (RV_TM_TYPE == RV_TM_RTK)
#define RV_TM_STRING "RTK"
#else
#define RV_TM_STRING "Unknown"
#endif

#if (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_POSIX)
#define RV_SEMAPHORE_STRING "Posix"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_VXWORKS)
#define RV_SEMAPHORE_STRING "VxWorks"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_PSOS)
#define RV_SEMAPHORE_STRING "pSOS"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_OSE)
#define RV_SEMAPHORE_STRING "OSE"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_NUCLEUS)
#define RV_SEMAPHORE_STRING "NUCLEUS"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_WIN32)
#define RV_SEMAPHORE_STRING "Win32"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_MOPI)
#define RV_SEMAPHORE_STRING "MOPI"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_OSA)
#define RV_SEMAPHORE_STRING "OSA"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_CONDVAR)
#define RV_SEMAPHORE_STRING "CondVars"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_NONE)
#define RV_SEMAPHORE_STRING "None"
#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_RTK)
#define RV_SEMAPHORE_STRING "RTK"
#else
#define RV_SEMAPHORE_STRING "Unknown"
#endif

#if (RV_LOCK_TYPE == RV_LOCK_POSIX)
#define RV_LOCK_STRING "Posix"
#elif (RV_LOCK_TYPE == RV_LOCK_VXWORKS)
#define RV_LOCK_STRING "VxWorks"
#elif (RV_LOCK_TYPE == RV_LOCK_PSOS)
#define RV_LOCK_STRING "pSOS"
#elif (RV_LOCK_TYPE == RV_LOCK_WIN32_MUTEX)
#define RV_LOCK_STRING "Win32Mutex"
#elif (RV_LOCK_TYPE == RV_LOCK_WIN32_CRITICAL)
#define RV_LOCK_STRING "Win32Critical"
#elif (RV_LOCK_TYPE == RV_LOCK_MOPI)
#define RV_LOCK_STRING "MOPI"
#elif (RV_LOCK_TYPE == RV_LOCK_OSA)
#define RV_LOCK_STRING "OSA"
#elif (RV_LOCK_TYPE == RV_LOCK_MANUAL)
#define RV_LOCK_STRING "Manual"
#elif (RV_LOCK_TYPE == RV_LOCK_RTK)
#define RV_LOCK_STRING "RTK"
#elif (RV_LOCK_TYPE == RV_LOCK_NONE)
#define RV_LOCK_STRING "None"
#else
#define RV_LOCK_STRING "Unknown"
#endif

#if (RV_MUTEX_TYPE == RV_MUTEX_POSIX)
#define RV_MUTEX_STRING "Posix"
#elif (RV_MUTEX_TYPE == RV_MUTEX_VXWORKS)
#define RV_MUTEX_STRING "VxWorks"
#elif (RV_MUTEX_TYPE == RV_MUTEX_PSOS)
#define RV_MUTEX_STRING "pSOS"
#elif (RV_MUTEX_TYPE == RV_MUTEX_WIN32_MUTEX)
#define RV_MUTEX_STRING "Win32Mutex"
#elif (RV_MUTEX_TYPE == RV_MUTEX_WIN32_CRITICAL)
#define RV_MUTEX_STRING "Win32Critical"
#elif (RV_MUTEX_TYPE == RV_MUTEX_MOPI)
#define RV_MUTEX_STRING "MOPI"
#elif (RV_MUTEX_TYPE == RV_MUTEX_MANUAL)
#define RV_MUTEX_STRING "Manual"
#elif (RV_MUTEX_TYPE == RV_MUTEX_RTK)
#define RV_MUTEX_STRING "RTK"
#elif (RV_MUTEX_TYPE == RV_MUTEX_NONE)
#define RV_MUTEX_STRING "None"
#else
#define RV_MUTEX_STRING "Unknown"
#endif

#if (RV_THREAD_TYPE == RV_THREAD_POSIX)
#define RV_THREAD_STRING "Posix"
#elif (RV_THREAD_TYPE == RV_THREAD_VXWORKS)
#define RV_THREAD_STRING "VxWorks"
#elif (RV_THREAD_TYPE == RV_THREAD_PSOS)
#define RV_THREAD_STRING "pSOS"
#elif (RV_THREAD_TYPE == RV_THREAD_OSE)
#define RV_THREAD_STRING "OSE"
#elif (RV_THREAD_TYPE == RV_THREAD_NUCLEUS)
#define RV_THREAD_STRING "NUCLEUS"
#elif (RV_THREAD_TYPE == RV_THREAD_WIN32)
#define RV_THREAD_STRING "Win32"
#elif (RV_THREAD_TYPE == RV_THREAD_WINCE)
#define RV_THREAD_STRING "WinCE"
#elif (RV_THREAD_TYPE == RV_THREAD_MOPI)
#define RV_THREAD_STRING "MOPI"
#elif (RV_THREAD_TYPE == RV_THREAD_OSA)
#define RV_THREAD_STRING "OSA"
#elif (RV_THREAD_TYPE == RV_THREAD_RTK)
#define RV_THREAD_STRING "RTK"
#elif (RV_THREAD_TYPE == RV_THREAD_NONE)
#define RV_THREAD_STRING "None"
#else
#define RV_THREAD_STRING "Unknown"
#endif

#if (RV_OSMEM_TYPE == RV_OSMEM_MALLOC)
#define RV_OSMEM_STRING "Malloc"
#elif (RV_OSMEM_TYPE == RV_OSMEM_OSE)
#define RV_OSMEM_STRING "OSE"
#elif (RV_OSMEM_TYPE == RV_OSMEM_NUCLEUS)
#define RV_OSMEM_STRING "NUCLEUS"
#elif (RV_OSMEM_TYPE == RV_OSMEM_PSOS)
#define RV_OSMEM_STRING "pSOS"
#elif (RV_OSMEM_TYPE == RV_OSMEM_VXWORKS)
#define RV_OSMEM_STRING "VxWorks"
#elif (RV_OSMEM_TYPE == RV_OSMEM_OSA)
#define RV_OSMEM_STRING "OSA"
#elif (RV_OSMEM_TYPE == RV_OSMEM_RTK)
#define RV_OSMEM_STRING "RTK"
#elif (RV_OSMEM_TYPE == RV_OSMEM_SYMBIAN)
#define RV_OSMEM_STRING "Symbian"
#else
#define RV_OSMEM_STRING "Unknown"
#endif

#if (RV_HOST_TYPE == RV_HOST_BSD)
#define RV_HOST_STRING "BSD"
#elif (RV_HOST_TYPE == RV_HOST_POSIX)
#define RV_HOST_STRING "Posix"
#elif (RV_HOST_TYPE == RV_HOST_VXWORKS)
#define RV_HOST_STRING "VxWorks"
#elif (RV_HOST_TYPE == RV_HOST_PSOS)
#define RV_HOST_STRING "pSOS"
#elif (RV_HOST_TYPE == RV_HOST_OSE)
#define RV_HOST_STRING "OSE"
#elif (RV_HOST_TYPE == RV_HOST_NUCLEUS)
#define RV_HOST_STRING "NUCLEUS"
#elif (RV_HOST_TYPE == RV_HOST_WIN32)
#define RV_HOST_STRING "Win32"
#else
#define RV_HOST_STRING "Unknown"
#endif

#if (RV_SELECT_TYPE == RV_SELECT_SELECT)
#define RV_SELECT_STRING "select()"
#elif (RV_SELECT_TYPE == RV_SELECT_POLL)
#define RV_SELECT_STRING "poll()"
#elif (RV_SELECT_TYPE == RV_SELECT_DEVPOLL)
#define RV_SELECT_STRING "/dev/poll"
#elif (RV_SELECT_TYPE == RV_SELECT_EPOLL)
#define RV_SELECT_STRING "epoll"
#elif (RV_SELECT_TYPE == RV_SELECT_KQUEUE)
#define RV_SELECT_STRING "Kqueue"
#elif (RV_SELECT_TYPE == RV_SELECT_WIN32_WSA)
#define RV_SELECT_STRING "WSASelect()"
#elif (RV_SELECT_TYPE == RV_SELECT_WIN32_COMPLETION)
#define RV_SELECT_STRING "CompletionPorts"
#else
#define RV_SELECT_STRING "Unknown"
#endif

#if (RV_SOCKET_TYPE == RV_SOCKET_BSD)
#define RV_SOCKET_STRING "BSD"
#elif (RV_SOCKET_TYPE == RV_SOCKET_WIN32_WSA)
#define RV_SOCKET_STRING "WinSock2"
#elif (RV_SOCKET_TYPE == RV_SOCKET_PSOS)
#define RV_SOCKET_STRING "pSOS"
#elif (RV_SOCKET_TYPE == RV_SOCKET_NUCLEUS)
#define RV_SOCKET_STRING "NUCLEUS"
#elif (RV_SOCKET_TYPE == RV_SOCKET_SYMBIAN)
#define RV_SOCKET_STRING "Symbian"
#else
#define RV_SOCKET_STRING "Unknown"
#endif
#if (RV_NET_TYPE & RV_NET_IPV6)
#define RV_NET_IPV6_STRING "+IPv6"
#else
#define RV_NET_IPV6_STRING ""
#endif
#if (RV_NET_TYPE & RV_NET_SCTP)
#define RV_NET_SCTP_STRING "+SCTP"
#else
#define RV_NET_SCTP_STRING ""
#endif


#if (RV_PORTRANGE_TYPE == RV_PORTRANGE_SLIM)
#define RV_PORTRANGE_STRING "Slim"
#elif (RV_PORTRANGE_TYPE == RV_PORTRANGE_FAST)
#define RV_PORTRANGE_STRING "Fast"
#else
#define RV_PORTRANGE_STRING "Unknown"
#endif

#if (RV_64TOASCII_TYPE == RV_64TOASCII_STANDARD)
#define RV_64TOASCII_STRING "Standard"
#elif (RV_64TOASCII_TYPE == RV_64TOASCII_WIN32)
#define RV_64TOASCII_STRING "Win32"
#elif (RV_64TOASCII_TYPE == RV_64TOASCII_MANUAL)
#define RV_64TOASCII_STRING "Manual"
#else
#define RV_64TOASCII_STRING "Unknown"
#endif

#if (RV_ASSERT_ENABLE == RV_YES)
#define RV_ASSERT_STRING "None"
#elif (RV_ASSERT_TYPE == RV_ASSERT_ANSI)
#define RV_ASSERT_STRING "Ansi"
#elif (RV_ASSERT_TYPE == RV_ASSERT_WINCE)
#define RV_ASSERT_STRING "WinCE"
#elif (RV_ASSERT_TYPE == RV_ASSERT_RTK)
#define RV_ASSERT_STRING "RTK"
#else
#define RV_ASSERT_STRING "Unknown"
#endif

#if (RV_STDIO_TYPE == RV_STDIO_ANSI)
#define RV_STDIO_STRING "Ansi"
#elif (RV_STDIO_TYPE == RV_STDIO_STUB)
#define RV_STDIO_STRING "Stub"
#elif (RV_STDIO_TYPE == RV_STDIO_OSE_DEBUG)
#define RV_STDIO_STRING "OSEDbg"
#elif (RV_STDIO_TYPE == RV_STDIO_WINCE_DEBUG)
#define RV_STDIO_STRING "WinCEDbg"
#else
#define RV_STDIO_STRING "Unknown"
#endif

#if (RV_LOGLISTENER_TYPE == RV_LOGLISTENER_WIN32)
#define RV_LOGLISTENER_STRING "Win32"
#elif (RV_LOGLISTENER_TYPE == RV_LOGLISTENER_FILE_AND_TERMINAL)
#define RV_LOGLISTENER_STRING "File&Term"
#elif (RV_LOGLISTENER_TYPE == RV_LOGLISTENER_TERMINAL)
#define RV_LOGLISTENER_STRING "Terminal"
#elif (RV_LOGLISTENER_TYPE == RV_LOGLISTENER_UDP)
#define RV_LOGLISTENER_STRING "UDP"
#elif (RV_LOGLISTENER_TYPE == RV_LOGLISTENER_NONE)
#define RV_LOGLISTENER_STRING "None"
#else
#define RV_LOGLISTENER_STRING "Unknown"
#endif

#if (RV_DNS_TYPE == RV_DNS_WIN32)
#define RV_DNS_STRING "Win32"
#elif (RV_DNS_TYPE == RV_DNS_BIND)
#define RV_DNS_STRING "Bind"
#elif (RV_DNS_TYPE == RV_DNS_ARES)
#define RV_DNS_STRING "Ares"
#elif (RV_DNS_TYPE == RV_DNS_NONE)
#define RV_DNS_STRING "None"
#else
#define RV_DNS_STRING "Unknown"
#endif

#if (RV_TLS_TYPE != RV_TLS_NONE)
#define RV_TLS_STRING "OpenSSL"
#else
#define RV_TLS_STRING "None"
#endif

/* Modules full strings */
#define RV_TIMING_MODULES_STRING "@(#)TIME" \
    ": Timestamp=" RV_TIMESTAMP_STRING \
    ", Clock=" RV_CLOCK_STRING \
    ", Tm=" RV_TM_STRING

#if (RV_THREADNESS_TYPE == RV_THREADNESS_SINGLE)
#define RV_THREAD_MODULES_STRING "@(#)THREADS: None"
#else
#define RV_THREAD_MODULES_STRING "@(#)THREADS" \
    ": Semaphore=" RV_SEMAPHORE_STRING \
    ", Lock=" RV_LOCK_STRING \
    ", Mutex=" RV_MUTEX_STRING \
    ", Thread=" RV_THREAD_STRING
#endif

#define RV_MEMORY_MODULES_STRING "@(#)MEMORY" \
    ": OsMem=" RV_OSMEM_STRING

#if (RV_NET_TYPE != RV_NET_NONE)
#define RV_NETWORK_MODULES_STRING "@(#)NETWORK" \
    ": Host=" RV_HOST_STRING \
    ", Select=" RV_SELECT_STRING \
    ", Socket=" RV_SOCKET_STRING RV_NET_IPV6_STRING RV_NET_SCTP_STRING \
    ", PortRange=" RV_PORTRANGE_STRING \
    ", DNS=" RV_DNS_STRING \
    ", TLS=" RV_TLS_STRING
#else
#define RV_NETWORK_MODULES_STRING "@(#)NETWORK: Disabled."
#endif

#define RV_ANSI_MODULES_STRING "@(#)ANSI" \
    ": 64Ascii=" RV_64TOASCII_STRING \
    ", Assert=" RV_ASSERT_STRING \
    ", StdIo=" RV_STDIO_STRING \
    ", LogListener=" RV_LOGLISTENER_STRING


/******************************************************************
                       rvusrconfig.h strings
 ******************************************************************/
#if defined(RV_SOCKET_ENABLE_IPV6_TOS) && !(RV_SOCKET_ENABLE_IPV6_TOS==0)
#define RV_SOCKET_ENABLE_IPV6_TOS_STRING "yes"
#else
#define RV_SOCKET_ENABLE_IPV6_TOS_STRING "no"
#endif

#if defined(RV_SOCKET_USE_FAKED_IPV6_TCLASS) && !(RV_SOCKET_USE_FAKED_IPV6_TCLASS==0)
#define RV_SOCKET_USE_FAKED_IPV6_TCLASS_STRING "yes"
#else
#define RV_SOCKET_USE_FAKED_IPV6_TCLASS_STRING "no"
#endif

#if defined(RV_IMS_IPSEC_ENABLED) && !(RV_IMS_IPSEC_ENABLED==RV_NO)
#define RV_IMS_IPSEC_ENABLED_STRING "yes"
#else
#define RV_IMS_IPSEC_ENABLED_STRING "no"
#endif

#if defined(RV_DNS_USES_HOSTS) && !(RV_DNS_USES_HOSTS==RV_NO)
#define RV_DNS_USES_HOSTS_STRING "yes"
#else
#define RV_DNS_USES_HOSTS_STRING "no"
#endif

#if defined(RV_DNS_USES_CACHING) && !(RV_DNS_USES_CACHING==RV_NO)
#define RV_DNS_USES_CACHING_STRING "yes"
#else
#define RV_DNS_USES_CACHING_STRING "no"
#endif

#if defined(RV_DNS_CACHE_SANITY) && !(RV_DNS_CACHE_SANITY==RV_NO)
#define RV_DNS_CACHE_SANITY_STRING "yes"
#else
#define RV_DNS_CACHE_SANITY_STRING "no"
#endif

#if defined(RV_USE_POSIX_TIMESTAMPS) && !(RV_USE_POSIX_TIMESTAMPS==RV_NO)
#define RV_USE_POSIX_TIMESTAMPS_STRING "yes"
#else
#define RV_USE_POSIX_TIMESTAMPS_STRING "no"
#endif

#if defined(RV_USE_RDTSC_TIMESTAMPS) && !(RV_USE_RDTSC_TIMESTAMPS==RV_NO)
#define RV_USE_RDTSC_TIMESTAMPS_STRING "yes"
#else
#define RV_USE_RDTSC_TIMESTAMPS_STRING "no"
#endif

#if defined(RV_SELECT_KQUEUE_GROUPS) && !(RV_SELECT_KQUEUE_GROUPS==RV_NO)
#define RV_SELECT_KQUEUE_GROUPS_STRING "yes"
#else
#define RV_SELECT_KQUEUE_GROUPS_STRING "no"
#endif

#if defined(RV_EHD_HOSTFILE)
#define RV_EHD_HOSTFILE_STRING RV_EHD_HOSTFILE
#else
#define RV_EHD_HOSTFILE_STRING "none"
#endif

#if defined(RV_QUEUE_TYPE) && (RV_QUEUE_TYPE==RV_QUEUE_STANDARD)
#define RV_QUEUE_TYPE_STRING "standard"
#else
#define RV_QUEUE_TYPE_STRING "none"
#endif

#define RV_USR_CONFIG_STRING "@(#)USR_CONFIG:" \
    " EnableIpv6Tos=" RV_SOCKET_ENABLE_IPV6_TOS_STRING \
    ", UseFakedIpv6TClass=" RV_SOCKET_USE_FAKED_IPV6_TCLASS_STRING \
    ", IpsecEnabled=" RV_IMS_IPSEC_ENABLED_STRING "\0@(#)USR_CONFIG:" \
    " DnsUsesHosts=" RV_DNS_USES_HOSTS_STRING \
    ", DnsUsesCaching=" RV_DNS_USES_CACHING_STRING \
    ", DnsCacheSanity=" RV_DNS_CACHE_SANITY_STRING "\0@(#)USR_CONFIG:" \
    " UsePosixTimestamps=" RV_USE_POSIX_TIMESTAMPS_STRING \
    ", UseRdtscTimestamps=" RV_USE_RDTSC_TIMESTAMPS_STRING \
    ", SelectKqueueGroups=" RV_SELECT_KQUEUE_GROUPS_STRING "\0@(#)USR_CONFIG:" \
    " EhdHostFile=" RV_EHD_HOSTFILE_STRING \
    ", QueueType=" RV_QUEUE_TYPE_STRING

#endif /* RV_CCORE_STRINGS_H */
