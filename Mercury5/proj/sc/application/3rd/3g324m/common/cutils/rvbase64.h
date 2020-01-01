/*****************************************************************************
Filename    : rvbase64.h
Description :b64 encoding decoding routines..
************************************************************************
        Copyright (c) 2006 RADVISION Inc. and RADVISION Ltd.
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

#if defined(__cplusplus)
extern "C" {
#endif 
    

/********************************************************************************************
 * rvEncodeB64
 * Performs encode B64 operation of inLen bytes in inTxt buffer.
 * INPUT   :
 *           inTxt - the buffer to be encoded.
 *           inLen - the length of buffer to be encoded
 *           outTxt - this buffer is used as encoding destination
 *           outLen - size of 'outTxt' buffer
 *           
 * RETURN  : number of used bytes in the 'outTxt' or -1 if function fails
 */
RVCOREAPI
RvInt rvEncodeB64(
                     IN RvUint8* inTxt,   
                     IN RvInt inLen,      
                     INOUT RvUint8* outTxt, 
                     IN RvInt outLen);   
                     

/********************************************************************************************
 * rvDecodeB64
 * Performs decode B64 operation of inLen bytes in inTxt buffer.
 * INPUT   :
 *           inTxt - the buffer to be decoded.
 *           inLen - the length of buffer to be decoded
 *           outTxt - this buffer is used as decoding destination
 *           outLen - size of 'outTxt' buffer
 *           
 * RETURN  : number of used bytes in the 'outTxt' or -1 if function fails
 */
RVCOREAPI
RvInt rvDecodeB64(
                  IN RvUint8* inTxt,  
                  IN RvInt inLen,     
                  INOUT RvUint8* outTxt, 
                  IN RvInt outLen);
                  
#if defined(__cplusplus)
}
#endif 
