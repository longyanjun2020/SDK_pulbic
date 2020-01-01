/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaStream.h
 *  Media Streaming Playback
 */
 
/**
 * @addtogroup MediaControl_JSI_Stream
 *
 * @{
 */

#ifndef __JKMEDIA_STREAM_H__
#define __JKMEDIA_STREAM_H__

#include "JkTypes.h"

/**
 * Event types
 */
/**
 * Buffering to streaming buffer started.
 */
#define JKMEDIA_EVENT_BUFFER_START 0x4000

/**
 * Buffering to streaming buffer completed.
 */
#define JKMEDIA_EVENT_BUFFER_STOP 0x4001

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure defining control functions for reading streaming media.
 */
typedef struct {
    /**
     * Gets the name of the URL scheme supported by this protocol.
     * @param pName
     *  A pointer to the buffer storing a pointer to the scheme name string.
     * @return
     *  Return the number of characters in the name (excluding null).
     */
    JKSint32 ( *getProtocolName )( JKWChar** pName );

    /**
     * Creates a media reading stream.
     *
     * @param pLocation A pointer to the buffer holding the URL string.
     * @param length    The number of the characters in the URL string.
     * @return          If the creation succeeds, return the identifier of 
     *                  the reading stream instance. The identifier must be 
     *                  a value of 0 or more. <br>
     *                  If the function fails, return a negative value.
     */
    JKSint32 ( *create )( JKWChar* pLocation, JKSint32 length );

    /**
     * Connects to the URL that was designated at instance creation.
     *
     * @param streamID The identifier of the stream instance.
     *                 The return value of create()() is designated.
     * @return         If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *                 if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *connect )( JKSint32 streamID );

    /**
     * Gets the permission name.
     *
     * @param streamID The stream instance ID.
     *                 The return value of create()() is designated.
     * @param pBuffer  A pointer to the buffer for storing the 
     *                 permission name.
     * @param length   The size (in characters) of the buffer pointed to by 
     *                 the <i>pBuffer</i> paramter.
     * @return         Return the number of characters of the permission name.
     *
     * If the given buffer is insufficient to hold the name, the native system 
     * should return the name length without writing to the buffer.
     * If the return value is greater than the size of the buffer,
     * JBlend allocates a buffer of the required size and call this function again.
     *
     * If it is not needed to perform security cheking, return 0.
     */
    JKSint32 ( *getPermission )( JKSint32 streamID, JKWChar* pBuffer, JKSint32 length );

    /**
     * Gets the MIME-type string of the streaming media.
     *
     * @param streamID The stream instance ID.
     *                 The return value of create()() is designated.
     * @param pBuffer  A pointer to the buffer for storing the 
     *                 MIME-type string.
     * @param length   The size (in characters) of the buffer pointed to by 
     *                 the <i>pBuffer</i> paramter.
     * @return         Return the number of characters of the MIME-type string.
     *
     * If the given buffer is insufficient to hold the string, the native system 
     * should return the string length without writing to the buffer.
     * If the return value is greater than the size of the buffer,
     * JBlend allocates a buffer of the required size and call this function again.
     */
    JKSint32 ( *getMimeType )( JKSint32 streamID, JKWChar* pBuffer, JKSint32 length );

    /**
     * Discards the media reading stream.
     *
     * @param streamID The stream instance ID.
     *                 The return value of create()() is designated.
     * @return         If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *                 if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *destroy )( JKSint32 streamID );
} JKT_MediaStream;

/**
 * A structure defining control functions for playing streaming media.
 */
typedef struct {
    /**
     * Opens a streaming media for checking whether it is playable. 
     *
     * @param pStream  A pointer to JKT_MediaStream function structure.
     * @param streamID The stream instance ID. The return value of the 
     *                 JKT_MediaStream structure <i>create()</i> is designated.
     * @return         If the operation succeeds, return a check management ID; 
     *                 if it fails, return 0.
     *
     * The native system must create an instance for checking and return its 
     * identifier if the operation succeeds.
     * Use values of JKMEDIA_CHECK_ID_BASE or above for the check management ID.
     *
     * The management ID returned by this function is designated in the 
     * following functions to identify the data for checking. <br>
     *  - JKT_MediaControl structure <i>check()</i>
     *  - JKT_MediaControl structure <i>getMediaSize()</i>
     *  - JKT_MediaControl structure <i>getDuration()</i>
     *  - <i>checkClose()()</i>
     *  .
     */
    JKSint32 ( *checkOpen )( JKT_MediaStream const* pStream, JKSint32 streamID );

    /**
     * Ends the checking started by checkOpen()().
     * 
     * @param streamID The check management ID. The return value of
     *                 <i>checkOpen()()</i> is designated.
     * @return         If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *                 if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *checkClose )( JKSint32 checkID );

    /**
     * Sets a media reading stream to the player.
     * 
     * @param id       The player ID.
     * @param pStream  A pointer to JKT_MediaStream function structure.
     * @param streamID The stream instance ID. The return value of
     *                 JKT_MediaStream structure <i>create()</i> is designated.
     * @return         If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *                 if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *setStream )( JKSint32 id, JKT_MediaStream const* pStream, JKSint32 streamID );
} JKT_Media_StreamControl;

/**
 * Gets the number of the protocols that support streaming playback.
 *
 * @return Return the number of the number of the protocols that support streaming playback.
 */
JKSint32 JkMediaStreamGetCount( void );

/**
 * Gets a structure that controls reading streaming media.
 *
 * @param The index of the protocol. 
 *        Values are designated between 0 and the JkMediaStreamGetCount() return value minus 1.
 */
JKT_MediaStream* JkMediaStreamGetController( JKSint32 count );

#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIA_STREAM_H__ */
