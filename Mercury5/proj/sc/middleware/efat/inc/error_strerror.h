#ifndef ONCE_ERROR_STRERROR_H
#define ONCE_ERROR_STRERROR_H
////////////////////////////////////////////////////////////////////////////////
///@file error_strerror.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


/* CONFIGURATION */
#include <pkgconf_error.h>         /* Configuration header */

/* INCLUDES */
#include <error_codes.h>       /* for Efat_ErrNo */

#ifdef __cplusplus
extern "C" {
#endif

/* FUNCTION PROTOTYPES */

/* Standard strerror() function as described by ISO C 1990 chap. 7.11.6.2.
 * This is normally provided by <string.h>
 */

extern char *
strerror( Efat_ErrNo );

/* prototype for the actual implementation. Equivalent to the above, but
 * used internally by this product in preference
 */

extern char *
__strerror( Efat_ErrNo );

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* ONCE_ERROR_STRERROR_H multiple inclusion protection */

/* EOF strerror.h */
