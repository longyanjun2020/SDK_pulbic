/***********************************************************************
Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..
RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/


#ifndef _OIDUTILS_H
#define _OIDUTILS_H

#ifdef __cplusplus
extern "C" {
#endif





typedef enum
{
    numberForm, /* 0 2 3 */
    nameForm, /* itu-t 2 3 */
    nameAndNumberForm /* itu-t(0) 2 3 */
} form;



RVINTAPI int RVCALLCONV
oidEncodeOID(
    IN  int         oidSize,
    OUT char        *oid,
    IN  const char  *buff);


RVINTAPI int RVCALLCONV
oidDecodeOID(
         IN  int oidSize,
         IN  char* oid,
         OUT int buffSize,
         OUT char* buff,
         IN  form f);


/*=========================================================================**
**  == oidDecodeOIDInt() ==                                                **
**                                                                         **
**  Converts a BER OID representation into an array of components.         **
**                                                                         **
**  PARAMETERS:                                                            **
**      oidSize         The length, in bytes, of the encoded OID value.    **
**                                                                         **
**      oid             A pointer to the encoded OID value buffer.         **
**                                                                         **
**      buffSize        The length, in integers of the target buffer       **
**                                                                         **
**      buff            A pointer to the target decoding buffer, or NULL.  **
**                      The target buffer is an array of integers          **
**                                                                         **
**                                                                         **
**  RETURNS:                                                               **
**      The length, in integers, of the decoded part of OID,               **
**      or a negative integer error code.                                  **
**                                                                         **
**  Use this function to decode OID values returned by stack components    **
**  such as PVT.                                                           **
**                                                                         **
**                                                                         **
**=========================================================================*/
RVINTAPI int RVCALLCONV
oidDecodeOIDInt(
        IN  int             oidSize,
        IN  char*           oid,
        IN  int             buffSize,
        OUT int *           buff);



#ifdef __cplusplus
}
#endif

#endif  /* _OIDUTILS_H */

