///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   sys_select.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_isoinfra.h>          /* Configuration header */

/* ------------------------------------------------------------------- */

#if !defined(_POSIX_SOURCE)

#if defined(__GNUC__)&&defined(__i686__)
#define INT_ISO_SELECT
#define BLD_ISO_SELECT_HEADER "sys/types.h"
#endif //defined(__GNUC__)&&defined(__i686__)


#ifdef INT_ISO_SELECT
#ifdef BLD_ISO_SELECT_HEADER
#include BLD_ISO_SELECT_HEADER
#else

#ifndef ONCE_ISO_SYS_SELECT_FD_SETS
#define ONCE_ISO_SYS_SELECT_FD_SETS

#ifndef	FD_SIZE
#define	FD_SIZE	256
#endif

#define	BTCOUNT	8

typedef unsigned int	fd_mask;
#define __NFDBITS	(sizeof(fd_mask) * BTCOUNT)	/* bits per mask */

#ifndef __howmany
#define	__howmany(__x, __y)	(((__x) + ((__y) - 1)) / (__y))
#endif

typedef	struct fd_set {
	fd_mask	fds_bits[__howmany(FD_SIZE, __NFDBITS)];
} fd_set;

#define	FD_SET(__n, __p)   ((__p)->fds_bits[(__n)/__NFDBITS] |= (1 << ((__n) % __NFDBITS)))
#define	FD_CLR(__n, __p)   ((__p)->fds_bits[(__n)/__NFDBITS] &= ~(1 << ((__n) % __NFDBITS)))
#define	FD_ISSET(__n, __p) ((__p)->fds_bits[(__n)/__NFDBITS] & (1 << ((__n) % __NFDBITS)))

#define	FD_COPY(__f, __t)                                       \
{                                                               \
    unsigned int _i;                                            \
    for( _i = 0; _i < __howmany(FD_SIZE, __NFDBITS) ; _i++ ) \
        (__t)->fds_bits[_i] = (__f)->fds_bits[_i];              \
}

#define	FD_ZERO(__p)                                            \
{                                                               \
    unsigned int _i;                                            \
    for( _i = 0; _i < __howmany(FD_SIZE, __NFDBITS) ; _i++ ) \
        (__p)->fds_bits[_i] = 0;                                \
}

#endif /* ONCE_ISO_SYS_SELECT_FD_SETS */

#ifndef __NEED_FD_SETS_ONLY

#ifndef ONCE_ISO_SYS_SELECT_H
#define ONCE_ISO_SYS_SELECT_H

#ifdef __cplusplus
extern "C" {
#endif

struct timeval;
extern int
select( int , fd_set * , fd_set * , fd_set * , struct timeval * );

#ifdef __cplusplus
}
#endif

#endif /* ONCE_ISO_SYS_SELECT_H multiple inclusion protection */

#endif /* __NEED_FD_SETS_ONLY */

#endif
#endif


#endif /* if !defined(_POSIX_SOURCE) */
/* ------------------------------------------------------------------- */

/* EOF sys/select.h */
