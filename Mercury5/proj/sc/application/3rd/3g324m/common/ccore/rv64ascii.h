/***********************************************************************
Filename   : rv64ascii.h
Description: rv64ascii header file
             This module provides functions for converting 64 bit numbers
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
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

#ifndef RV_64ASCII_H
#define RV_64ASCII_H

#include "rvccore.h"
#include "rvstdio.h"

#if !defined(RV_64TOASCII_TYPE) || ((RV_64TOASCII_TYPE != RV_64TOASCII_STANDARD) && \
    (RV_64TOASCII_TYPE != RV_64TOASCII_WIN32) && (RV_64TOASCII_TYPE != RV_64TOASCII_MANUAL))
#error RV_64TOASCII_TYPE not set properly
#endif

/* Minimum buffer size required for ASCII strings of 64 bit numbers */
#define RV_64TOASCII_BUFSIZE 22

/* Minimum buffer size required for HEX strings of 64 bit numbers */
#define RV_64TOHEX_BUFSIZE 18

/* Declare some variables needed to support printing 64 bit numbers 
 * n - maximal number of 64 bit variables in single call to various printing 
 *     routines. 
 */
#define RV_64TOASCII_SUPPORT(n) \
RvChar __64buf__[n][RV_64TOASCII_BUFSIZE]


/* Returns ascii representation of 64 bit signed integer radix 10 */
#define RV_64TOA(i64, i)   Rv64toA(i64, __64buf__[i])

/* Returns ascii representation of 64 bit unsigned integer radix 10 */
#define RV_64UTOA(u64, i)  Rv64UtoA(u64, __64buf__[i])

/* Returns ascii representation of 64 bit unsigned integer radix 16 */
#define RV_64UTOH(u64, i)  Rv64UtoHex(u64, __64buf__[i])


#if defined(__cplusplus)
extern "C" {
#endif

/* Prototypes: See documentation blocks below for details. */

/********************************************************************************************
 * Rv64AsciiInit
 * Initializes the rv64ascii module. Must be called once (and
 * only once) before any other functions in the module are called.
 * INPUT   :
 * OUTPUT  :
 * RETURN  : RV_OK on success.
 */
RvStatus Rv64AsciiInit(void);

/********************************************************************************************
 * Rv64AsciiEnd
 * Shuts down the rv64ascii module. Must be called once (and
 * only once) when no further calls to this module will be made.
 * INPUT   :
 * OUTPUT  :
 * RETURN  : RV_OK on success.
 */
RvStatus Rv64AsciiEnd(void);

/********************************************************************************************
 * Rv64UtoA
 * Converts an unsigned 64 bit integer (RvUint64) to a decimal string.
 * INPUT   : num64              - The unsigned 64 bit number to be converted.
 * OUTPUT  : buf                - The buffer where resulting string will be placed
 * RETURN  : A pointer to buf if successful otherwise NULL.
 * NOTE:  The buffer (buf) should be at least RV_64TOASCII_BUFSIZE bytes long
 *        or the end of the buffer may be overwritten.
 */
RVCOREAPI RvChar * RVCALLCONV Rv64UtoA(
    IN RvUint64 num64,
    OUT RvChar *buf);

/********************************************************************************************
 * Rv64UtoA
 * Converts an signed 64 bit integer (RvInt64) to a decimal string.
 * INPUT   : num64              - The unsigned 64 bit number to be converted.
 * OUTPUT  : buf                - The buffer where resulting string will be placed
 * RETURN  : A pointer to buf if successful otherwise NULL.
 * NOTE:  The buffer (buf) should be at least RV_64TOASCII_BUFSIZE bytes long
 *        or the end of the buffer may be overwritten.
 */
RVCOREAPI RvChar * RVCALLCONV Rv64toA(
    IN RvInt64 num64,
    OUT RvChar *buf);

/********************************************************************************************
 * Rv64UtoA
 * Converts an unsigned 64 bit integer (RvUint64) to a hexadecimal string.
 * INPUT   : num64              - The unsigned 64 bit number to be converted.
 * OUTPUT  : buf                - The buffer where resulting string will be placed
 * RETURN  : A pointer to buf if successful otherwise NULL.
 * NOTE:  The buffer (buf) should be at least RV_64TOHEX_BUFSIZE bytes long
 *        or the end of the buffer may be overwritten.
 */
RVCOREAPI RvChar * RVCALLCONV Rv64UtoHex(
    IN RvUint64 num64,
    OUT RvChar *buf);

/******************************************************************************
 * RvAto64
 * Converts an NULL-terminated string to signed 64 bit integer (RvInt64).
 * INPUT   : str - The string to be converted.
 * RETURN  : 64 bit integer
 */
RVCOREAPI void RVCALLCONV RvAto64(IN RvChar* str, OUT RvInt64* pNum64);

#if defined(__cplusplus)
}
#endif

#endif /* RV_64ASCII_H */
