#ifndef ONCE_ERROR_ERRNO_H
#define ONCE_ERROR_ERRNO_H
////////////////////////////////////////////////////////////////////////////////
///@file error_errno.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


/* CONFIGURATION */

//#include <pkgconf/error.h>         /* Configuration header */
#include <pkgconf_error.h>         /* Configuration header */

#ifdef PKG_ERROR_ERRNO

/* INCLUDES */

#include <error_codes.h>       /* for Efat_ErrNo */

#ifdef __cplusplus
extern "C" {
#endif

/* FUNCTION PROTOTYPES */




/* VARIABLES */


#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* ifdef PKG_ERROR_ERRNO */

#endif /* ONCE_ERROR_ERRNO_H multiple inclusion protection */

/* EOF errno.h */

