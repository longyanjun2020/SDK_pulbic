/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaCapture.h
 *  Media Capturing Control
 */
 
/**
 * @addtogroup MediaControl_JSI_Capture
 *
 * @{
 */
 
#ifndef ___JKMEDIA_CAPTURE_H
#define ___JKMEDIA_CAPTURE_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 */

/**
 * Recording started.\ An event value for passing to AmMediaPostEvent().
 */
#define JKMEDIA_EVENT_RECORD_STARTED 10

/**
 * Recording finished.\ An event value for passing to AmMediaPostEvent().
 */
#define JKMEDIA_EVENT_RECORD_STOPPED  11

/**
 * Recording failed.\ An event value for passing to AmMediaPostEvent().
 */
#define JKMEDIA_EVENT_RECORD_ERROR -2

/**
 * A buffer is needed for subsequent recording.\ An event value for passing to AmMediaPostEvent().
 */
#define JKMEDIA_EVENT_RECORD_REQ_BUFFER 0x100

/**
 * Recording preparation in progress.\ A value to be returned by JKT_Media_RecordControl structure <i>getState()</i>.
 */
#define JKMEDIA_RECSTATE_READY 0

/**
 * Now recording.\ A value to be returned by JKT_Media_RecordControl structure <i>getState()</i>.
 */
#define JKMEDIA_RECSTATE_RECORDING 1

/**
 * Error occurred in recording.\ A value to be returned by JKT_Media_RecordControl structure <i>getState()</i>.
 */
#define JKMEDIA_RECSTATE_ERROR 0x10000

/**
 * Setting a maximum size limit for recording data is not supported.
 * @see {@link JKT_Media_RecordControl#setBufferLimit JKT_Media_RecordControl#setBufferLimit()}
 */
#define JKMEDIA_RECORD_SIZELIMIT_NOTSUPPORTED (-2)

/**
 * The minimum value of the media type that indicates an input device.
 * 
 * As the media type for an input device, set a value greater 
 * than or equal to this value to the <i>mediaType</i> member 
 * of JKT_MediaControl structure.
 */
#define JKMEDIA_TYPE_DEVICE_BASE 0x10000000

/**
 * The maximum value of the media type that indicates an input device.
 * 
 * As the media type for an input device, set a value less 
 * than or equal to this value to the <i>mediaType</i> member 
 * of JKT_MediaControl structure.
 */
#define JKMEDIA_TYPE_DEVICE_LIMIT 0x1fffffff

/**
 * A structure for holding encoding parameters.
 *
 * Java application passes encoding parameters to MMAPI
 * in the form of URL query. 
 * JBlend interprets it to keywords and values and 
 * sets them in this structure for passing the encoding parameters to the native system.
 */
typedef struct {
    /**
     * A pointer to the parameter keyword string.
     */
    JKWChar* pKey;
    /**
     * The number of characters in the parameter keyword string.
     */
    JKSint32 keyLength;
    /**
     * A pointer to the parameter value string.
     */
    JKWChar* pValue;
    /**
     * The number of characters in the parameter value string.
     */
    JKSint32 valueLength;
} JKT_Media_Param;


/**
 * Java application did not pass the encoding parameter.
 *
 * When this value is indicated, use the default value defined in the native system. 
 */
#define JKMEDIA_ENCODEPARAM_USE_DEFAULT 0x80000000

/**
 * A structure defining input device control functions.
 *
 * When the device manufacturer supports input device feature, 
 * implement functions defined in this structure.
 */
typedef struct {
    /**
     * Gets the MIME type of the media obtainable from external input device.
     * @param pType
     *   A pointer to the memory area for putting a pointer to the
     *   MIME type string of the media handled by the input device.
     * @return
     *   Return the character count of the string pointed to by the 
     *   pointer put in the memory area indicated by <i>pType</i> parameter.
     *
     * When this function is called, put in the memory area indicated by the 
     * <i>pType</i> parameter a pointer to the string that represents 
     * the MIME type of the media handled by the input device.
     *
     * This function is called both when Manager class is initialized and when 
     * a Java application calls the <code>realize</code> method of the 
     * <code>Player</code> instance that supports Live-media Capture.
     */
    JKSint32 ( *getMIMEType )( JKWChar** pType );
    /**
     * Passes to the native system the parameters for the use of the input device.
     * @param pParam
     *   A pointer to the JKT_Media_Param structure array holding parameters.
     *   This pointer remains valid until this function returns.
     * @param paramLen
     *   The element count of the JKT_Media_Param array pointed to by the 
     *   <i>pParam</i> parameter.
     * @return
     *   If the parameter is accepted normally, return #JKMEDIA_RESULT_OK.<br>
     *   Otherwise, return #JKMEDIA_RESULT_ERROR.
     *
     * If the input device has not been opened yet when this function is called,
     * check the validity of all the JKT_Media_Param structures pointed to by 
     * the <i>pParam</i> parameter. If the validity is verified, retain the 
     * parameters given in JKT_Media_Param structures in the native system.
     *
     * If the input device has been already opened when this function is called, 
     * only perform check of validity of the parameters and leave the parameters
     * retained in the native system unchanged.
     *
     * This function is called just before <i>open()</i>.
     * The parameters passed by this function must be applied to the input device
     * when <i>open()</i> is successively called after this function.
     */
    JKSint32 ( *setParam )( JKT_Media_Param* pParam, JKSint32 paramLen );
    /**
     * Opens the input device and sets parameters.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     * If the input device has not been opened yet when this function is called,
     * open the input device and apply to the device the parameters passed 
     * to <i>setParam()</i>.
     * If the device has been already opened, return #JKMEDIA_RESULT_ERROR 
     * without performing any processing.
     */
    JKSint32 ( *open )( void );
    /**
     * Closes an input device.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *   If the device is already closed, return 
     *     #JKMEDIA_RESULT_OK without doing further action.
     */
    JKSint32 ( *close )( void );
} JKT_Media_InputDeviceControl;

/**
 * A structure defining snapshot control functions.
 *
 * This structure defines functions for capturing a frame in the media
 * coming from an input device or the playing media.
 */
typedef struct {
    /**
     * Gets the number of available encoders.
     * @return
     *  Return the count of encoders that can be used for the media type.
     */
    JKSint32 ( *getEncoderCount )( void );

    /**
     * Gets the MIME-type of output format of an encoder.
     * @param i
     *  The index that identifies the encoder.
     *  Values are designated between 0 and the getEncoderCount()() return value minus 1.
     *  If a value outside of that range is designated, return 0.
     * @param pType
     *  A pointer to the buffer for storing a pointer to the MIME-type string of the encoder.
     * @return
     *  Return the number of characters in the MIME-type string.
     */
    JKSint32 ( *getEncoderType )( JKSint32 i, JKWChar** pType );

    /**
     * Prepares for taking a snapshot.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   When this function is called, the player must prepare for taking a snapshot.
     *   For the player which is handling an input device, the player should prepare
     *   for taking picture.
     */
    JKSint32 ( *prepare )( JKSint32 id );
    /**
     * Performs post-processing of snapshot-taking.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *unprepare )( JKSint32 id );

    /**
     * Sets an encoder and encoding parameters to the player
     * @param id
     *  The player ID.
     * @param pParam
     *  A pointer to the buffer holding the encoding parameters.
     *  An array of JKT_Media_Param structure is stored in this area.
     * @param paramLen
     *  The number of the encoding parameters (JKT_Media_Param).
     * @param pType
     *  A pointer to the buffer for storing a pointer to the MIME-type
     *  string of the media type that applicable encoder can provide.
     *  If no encoder is available, put JK_NULL.
     * @return
     *  If an applicable encoder exists, return the number of characters of MIME-type string
     *  that the native system stored in the buffer pointed to by pType.<br>
     *  Return 0 if no encoder is available. <br>
     *  Return 0 if there is keyword that the native system cannot handle, or if 
     *  parameter is invalid.
     *
     *  When this function is called, the native system must set encoder parameters
     *  designated by JKT_Media_Param structures to the player.
     *
     *  JBlend analyzes encoding parameters based on the MMAPI specification
     *  and gets the result as pairs of keyword and value, 
     *  and sets them in each JKT_Media_Param structure.
     *  The native system should check each JKT_Media_Param structure and set them
     *  to the player.
     *
     *  JBlend set JK_NULL to the JKT_Media_Param members for which 
     *  the Java application did not designate in the encoding parameters. 
     *  The native system should use default value for these parameters.
     *
     *  JBlend releases the memory area pointed to by the <i>pParam</i> parameter
     *  after this function returns; therefore, 
     *  the native system must make a copy of designated encoding parameters.
     */
    JKSint32 ( *setEncodeParam )( JKSint32 id, JKT_Media_Param* pParam, JKSint32 paramLen, JKWChar** pType );

    /**
     * Captures an image
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   When this function is called, the native system must capture the 
     *   image which the player is currently playing.
     *   The captured image should be stored in a buffer allocated 
     *   by the native system without being encoded.
     */
    JKSint32 ( *capture )( JKSint32 id );

    /**
     * Encodes the captured image.
     * @param id
     *  The player ID.
     * @param step
     *  A reserved parameter. Normally 0 is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *   To cause JBlend to wait for completion, return #JKMEDIA_RESULT_WAIT.
     *
     *   When this function is called, the native system must encode the captured image
     *   according to the encoding parameters that were designated by setEncodeParam()().
     */
    JKSint32 ( *encode )( JKSint32 id );

    /**
     * Gets the image of encoded result.
     * @param id
     *  The player ID.
     * @param pLength
     *  A pointer to the buffer for storing the size of the image.
     * @return
     *  Return a pointer to the buffer that holds the encoded image data.
     */
    JKUint8* ( *getImage )( JKSint32 id, JKSint32* pLength );

    /**
     * Discard captured result and encoded image.
     * @param id
     *  The player ID.
     *   JBlend callers this function, after image data acquisition by 
     *   getImage()(), or after post-processing by unprepare()().     
     */
    void ( *discardTemporary )( JKSint32 id );
} JKT_Media_SnapshotControl;

/**
 * A structure defining recording control functions.
 */
typedef struct {
    /**
     * Get the number of applicable encoder types.
     * @return
     *  Return the number of encoders that can applicable to the media type.
     */
    JKSint32 ( *getEncoderCount )( void );

    /**
     * Gets the MIME-type of the encoder output format.
     * @param i
     *  The index identifying an encoder.
     *  Values are designated between 0 and the getEncoderCount()() return value minus 1. 
     * @param pType
     *  A pointer to the buffer for storing a pointer to the MIME-type 
     *  string an encoder corresponds to.
     * @return
     *  Return the number of the characters in the MIME-type string pointed to by the pointer
     *  stored in the buffer pointed to by <i>pType</i>.
     */
    JKSint32 ( *getEncoderType )( JKSint32 i, JKWChar** pType );

    /**
     * Sets the encoding parameter.
     * @param id
     *  The player ID.
     * @param pParam
     *  A pointer to the buffer holding the encoding parameters.
     *  An array of JKT_Media_Param structure is stored in this area.
     * @param paramLen
     *  The number of the encoding parameters (JKT_Media_Param).
     * @param pType
     *  A pointer to the buffer for storing a pointer to the MIME-type
     *  string of set encoder.
     *  If the native system failed to set encoder, put JK_NULL and return 0.
     * @return
     *  Return the number of the characters of the MIME-type string pointed to by the pointer stored in the buffer.
     *
     *
     *  When this function is called, the native system has to set encoder parameters
     *  designated by JKT_Media_Param structures to the player.
     *
     *  JBlend analyzes encoding parameters based on the MMAPI specification
     *  and gets the result as pairs of keyword and value, 
     *  and sets them in each JKT_Media_Param structure.
     *  The native system should check each JKT_Media_Param structure and set them
     *  to the player.
     *
     *  JBlend set JK_NULL to the JKT_Media_Param members for which 
     *  the Java application did not designate in the encoding parameters. 
     *  The native system should use default values for these parameters.
     *
     *  JBlend releases the memory area pointed to by the <i>pParam</i> parameter
     *  after this function returns; therefore, 
     *  the native system must make a copy of designated encoding parameters.
     */
    JKSint32 ( *setEncodeParam )( JKSint32 id, JKT_Media_Param* pParam, JKSint32 paramLen, JKWChar** pType );

    /**
     *  Returns whether the native system allocates recording buffer.
     * @param id
     *  The player ID.
     * @return
     *  If the native system allocates recording buffer by itself, return JK_TRUE.
     *  Otherwise, return JK_FALSE.
     *
     *  If the native system does not allocate recording buffer by itself,
     *  JBlend allocates it in the Java heap.
     *  The function to be called during recording differ with this 
     *  allocation method.
     *
     *  Functions to be called when the native system allocates buffer.
     *  - initBuffer()()
     *  - getBufferCount()()
     *  - getBuffer()()
     *  .
     *  
     *  Functions to be called when JBlend allocates buffer.
     *  - getBufferUnitSize()()
     *  - addBuffer()()
     *  .
     */
    JKBool ( *usePlatformBuffer )( JKSint32 id );

    /**
     * Gets the size of the buffer to be allocated in Java heap.
     * @param id
     *  The player ID.
     * @return
     *  Return the size of buffer (in bytes) which JBlend adds in Java heap.
     *
     *  JBlend calls this function only if usePlatformBuffer()() returns JK_FALSE.
     */
    JKSint32 ( *getBufferUnitSize )( JKSint32 id );

    /**
     * Passes the address and size of the recording buffer allocated in Java heap.
     * @param id
     *  The player ID.
     * @param pBuffer
     *  The address of the recording buffer.
     * @param size
     *  The size of the recording buffer.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  JBlend calls this function only if usePlatformBuffer()() returns JK_FALSE.
     */
    JKSint32 ( *addBuffer )( JKSint32 id, JKUint8* pBuffer, JKSint32 size );

    /**
     *        Sets a maximum size limit of recording data.
     * @param id
     *        The player ID.
     * @param size
     *        The size limit of recording data.
     * @return
     *        - #JKMEDIA_RESULT_OK<br>
     *          if the function succeeds in setting the maximum size limit with the <i>size</i> parameter.
     *          If the limit size actually set is less than <i>size</i>, return that value instead.
     *        - #JKMEDIA_RECORD_SIZELIMIT_NOTSUPPORTED <br>
     *          if the native system does not support setting of a maximum size limit for recording data.
     *          Whether or not to support the setting should not depend on the value of <i>size</i>.
     *        - #JKMEDIA_RESULT_ERROR <br>
     *          if the function fails for any other reason.
     *          If the value of <i>size</i> is less than the minimum data capacity that can store valid recording data, 
     *          return #JKMEDIA_RESULT_ERROR.
     *        .
     *<p>
     * When the total amount of recorded data has reached to 
     * the limit, the native system must stop recording.
     *
     * Depending on the timing this function is called,
     * there is possibility that buffer has been already allocated 
     * and the total buffer size has become bigger than the <i>size</i> parameter.
     */
    JKSint32 ( *setBufferLimit )( JKSint32 id, JKSint32 size );

    /**
     * Initializes the native system recording buffer.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  JBlend calls this function only if usePlatformBuffer()() returns JK_TRUE.
     */
    JKSint32 ( *initBuffer )( JKSint32 id );

    /**
     * Gets the number of recording buffers allocated in the native system.
     * @param id
     *  The player ID.
     * @return
     *  Return the number of the recording buffers.
     *  Return 0 if no recording buffer exists.
     *  Based on the return value of this function, JBlend 
     *  reads recorded data in small fragments by getBuffer()().
     *
     *  The function getBuffer()() performs synchronized operation;
     *  the more the buffer size is greater, the longer the operation 
     *  takes time and therefore it blocks Java threads. 
     *  A memory fragmentation problem should also be taken into 
     *  consideration because the recorded data is copied to the 
     *  Java heap. 
     *  To avoid these problems, it is recommended that the native system 
     *  passes the recorded data to JBlend in small fragments 
     *  by getBuffer()(). 
     *
     *  JBlend calls this function only if usePlatformBuffer()() returns JK_TRUE.
     */
    JKSint32 ( *getBufferCount )( JKSint32 id );

    /**
     * Gets the address and size of a buffer holding recorded data.
     * @param id
     *  The player ID.
     * @param count
     *  The index of the buffer.
     *  Values are designated between 0 and the getBufferCount()() return value minus 1. 
     * @param pLength
     *  A pointer to the buffer for storing the buffer size.
     * @return
     *  Return a pointer to the buffer.
     *
     *  JBlend calls this function only if usePlatformBuffer()() returns JK_TRUE.
     */
    JKUint8* ( *getBuffer )( JKSint32 id, JKSint32 count, JKSint32* pLength );

    /**
     * Starts recording.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *startRecord )( JKSint32 id );

    /**
     * Stops recording.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *stopRecord )( JKSint32 id );

    /**
     * Gets current recording state.
     * @param id
     *  The player ID.
     * @return
     *  Return one of the following.
     *  <ul>
     *   <li> #JKMEDIA_RECSTATE_READY
     *   <li> #JKMEDIA_RECSTATE_RECORDING
     *   <li> #JKMEDIA_RECSTATE_ERROR
     *  </ul>
     */
    JKSint32 ( *getState )( JKSint32 id );

    /**
     * Gets the size of the recorded data.
     * @param id
     *  The player ID.
     * @return
     *  Return the recorded data size, in bytes.
     */
    JKSint32 ( *getRecordedSize )( JKSint32 id );

    /**
     * Processes recording buffer contents and prepares for output. 
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  JBlend calls this function when recording is completed.
     *  After calling this function, JBlend calls getBuffer()() 
     *  to get recorded data.
     */
    JKSint32 ( *complete )( JKSint32 id );

    /**
     * Discard all of the recording buffers.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  When this function is called, the native system must discard recording buffers allocated by the native system.
     *
     *  To start another recording using current buffers, JBlend calls initBuffer()() without 
     *  calling this function.
     */
    JKSint32 ( *discard )( JKSint32 id );
} JKT_Media_RecordControl;

#ifdef __cplusplus
}
#endif

#endif /* !___JKMEDIA_CAPTURE_H */

/** @} end of group */
