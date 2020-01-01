/***********************************************************************
Filename   : rvarchconfig.h
Description: architechure specific configuration
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
#ifndef RV_ARCHCONFIG_H
#define RV_ARCHCONFIG_H

/* --------- platform type --------- */
#define RV_ARCH_TYPE RV_ARCH_TYPE_NONE
/* Deduce type of platform using compiler predefined macros. */
/* For now only GNU C compiler is supported */
#if defined(__GNUC__) && (__GNUC__)
#if (__amd64) || (__x86_64__) || (__x86_64) || (i386) || (__i386__) || \
    (__ia64__) || (_IA64) || (__IA64__)
#undef RV_ARCH_TYPE
#define RV_ARCH_TYPE RV_ARCH_TYPE_X86
#endif
#endif

#endif /* RV_ARCHCONFIG_H */
