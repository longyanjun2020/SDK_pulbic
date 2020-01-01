#ifndef ONCE_PKGCONF_LIBM_H
#define ONCE_PKGCONF_LIBM_H
/*
 * File <pkgconf/libm.h>
 *
 * This file is generated automatically by the configuration
 * system. It should not be edited. Any changes to this file
 * may be overwritten.
 */

/***** proc output start *****/
//#include <pkgconf/system.h>
#include <pkgconf_system.h>
typedef enum {
    NUM_LIBM_COMPAT_UNINIT= 0,  // Default state. DO NOT set it to this
    NUM_LIBM_COMPAT_POSIX = 1,  // ANSI/POSIX 1003.1
    NUM_LIBM_COMPAT_IEEE  = 2,  // IEEE-754
    NUM_LIBM_COMPAT_XOPEN = 3,  // X/OPEN Portability guide issue 3
                                   // (XPG3)
    NUM_LIBM_COMPAT_SVID  = 4   // System V Interface Definition 3rd
                                   // edition
} Efat_libm_compat_t;

/****** proc output end ******/
#define PKG_LIBM_MATHFP 1
#define PKG_LIBM_COMPATIBILITY 1
#define INT_LIBM_COMPAT 1
#define INT_LIBM_COMPAT_1
#define NUM_LIBM_COMPATIBILITY POSIX
#define NUM_LIBM_COMPATIBILITY_POSIX
#define PKG_LIBM_COMPATIBILITY_DEFAULT POSIX
#define PKG_LIBM_COMPATIBILITY_DEFAULT_POSIX
#define NUM_LIBM_COMPAT_DEFAULT NUM_LIBM_COMPAT_POSIX
#define NUM_LIBM_COMPAT_DEFAULT_NUM_LIBM_COMPAT_POSIX
#define FUN_LIBM_SVID3_scalb 1
#define PKG_LIBM_THREAD_SAFETY 1
#define NUM_LIBM_X_TLOSS 1.41484755040569E+16
#define PKG_LIBM_OPTIONS 1

#endif
