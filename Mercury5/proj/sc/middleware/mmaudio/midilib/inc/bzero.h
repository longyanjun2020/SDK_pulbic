#if ! defined( common_bzero_h )
#define common_bzero_h
/*****************************************************************************/
/* common_bzero_h                                                            */
/* bzero.h                                                                   */
/* 2006/09                                                                   */
/* Copyright 2006 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

extern
void
BZERO(
    void *          p,
    unsigned long   size
);
#define BZERO_8ALIGN BZERO

/*****************************************************************************/
#endif  /* ! defined( common_bzero_h ) */
