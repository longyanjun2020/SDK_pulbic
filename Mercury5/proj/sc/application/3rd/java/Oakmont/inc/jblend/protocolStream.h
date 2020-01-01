/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file protocolStream.h
 * Data stream from file
 */

#ifndef __PROTOCOL_STREAM_H__
#define __PROTOCOL_STREAM_H__

#include "JkMediaStream.h"

/**
 * The structure of functions necessary for the control of media streams both for microJBlend and platform.
 * The expansion of the structure is available in the following way, because microJBlend knows only
 * the address of the JKT_MediaStream instance.
 */
typedef struct {
    /**
     * Media stream structure
     */
    JKT_MediaStream stream;

    /**
     * Get streamBuffer instance.
     * @param streamID
     *   stream ID
     * @return
     *   A handle of the streamBuffer instance
     */
    void* ( *getFileStreamInstance )( JKSint32 streamID );
} ProtocolStream_T;

#endif /* !__PROTOCOL_STREAM_H__ */
