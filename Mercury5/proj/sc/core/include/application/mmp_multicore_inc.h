//==============================================================================
//
//  File        : mmp_multicore_inc.h
//  Description : INCLUDE File for the Multi-Core Handshaking Interface
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_MULTICORE_INC_H_
#define _MMP_MULTICORE_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "cpucomm.h"
#include "cpucomm_core.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/*
 * Don't try to modify the value if you don't know what you are doing.
 */
#define MAX_REQ_PARAM_SIZE  (SWAP_BUFFER_SIZE)
#define MAX_RESP_PARAM_SIZE (SWAP_BUFFER_SIZE)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/*
 * Common request class
 */
typedef struct _DUALCORE_REQ_OBJ {
    /* The actual length of request data, MAX is MAX_REQ_PARAM_SIZE */
    MMP_UBYTE   ubLength;
    /* Request ID */
    MMP_UBYTE   ubID;
    /* Timeout to stop waiting slave core ACK, 0 means never stop */
    MMP_USHORT  usTimeout;
} DUALCORE_REQ_OBJ;

/*
 * Common request object
 */
typedef struct _DUALCORE_REQ {
    DUALCORE_REQ_OBJ    req;
    MMP_UBYTE           ubData[MAX_REQ_PARAM_SIZE];
} DUALCORE_REQ;

/*
 * Common response class
 */
typedef struct _DUALCORE_RESP_OBJ {
    /* The actual length of response data, MAX is MAX_RESP_PARAM_SIZE */
    MMP_UBYTE   ubLength;
    /* Reqeust ID */
    MMP_UBYTE   ubID;
    /* Timeout to stop waiting response, 0 means never stop */
    MMP_USHORT  usTimeout;
} DUALCORE_RESP_OBJ;

/*
 * Common response object
 */
typedef struct _DUALCORE_RESP {
    DUALCORE_RESP_OBJ   resp;
    MMP_UBYTE           ubData[MAX_RESP_PARAM_SIZE];
} DUALCORE_RESP;

#endif // _MMP_MULTICORE_INC_H_