/**
 * Copyright 2006 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkMediaInputstream.h
 *  InputStream Streaming Playback JSI
 */
/**
 * @addtogroup InputStream_Playback_JSI
 * @{
 */

#ifndef __JKMEDIA_INPUTSTREAM_H__
#define __JKMEDIA_INPUTSTREAM_H__

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The extended control ID of #JKT_Media_InputstreamControl.
 */
#define JKT_MMAPI_MEDIA_CTRID_INPUTSTREAM           0x10000001

/**
 * The structure type for storing a streaming playback request from the native system and the processing result of JBlend 
 * for the request.
 *
 * For details of the information to be stored in this structure type, see the descriptions of the following event types:
 * - #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ
 * - #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY
 * - #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK
 * .
 */
typedef struct {
    /**
     * The player ID.
     */
    JKSint32 playerID;
    /**
     * The size of the data to be read or the offset position.
     */
    JKSint32 request_size;
    /**
     * The number of times to read.
     */
    JKSint32 read_times;
    /**
     * A pointer to the buffer.
     */
    JKUint8 *pBuffer;
    /**
     * The size in bytes of the buffer indicated by the <i>pBuffer</i> member.
     */
    JKSint32 size;
    /**
     * The processing result.
     */
    JKSint32 result;
} JKT_Media_InputstreamRequest;

/**
 * The structure type for defining functions to implement streaming playback from an <code>InputStream</code>.
 *
 * To support streaming playback from an <code>InputStream</code>, register an instance of this structure type as an extended control of the 
 * JKT_MediaControl. 
 * For details of the extended control, see @ref page_muse_extensible_struct and the description of JKT_MediaExtension.
 */
typedef struct {
    /**
     *        Gets the data size necessary for media data checking.
     * @param pBuffer
     *        The address of the buffer holding the initial portion of the media data.
     *        #JK_NULL can be specified.
     * @param length
     *        The size in bytes of the data indicated by <i>pBuffer</i>.
     * @param isMarkSupported
     *        A boolean value is passed depending on the return value of the <code>markSupported</code> method of 
     *        the <code>InputStream</code> set for the <code>Player</code> object as follows:
     *        - <code>true</code>: #JK_TRUE
     *        - <code>false</code>: #JK_FALSE
     *        .
     *        Note that, when this value is #JK_FALSE, it is not possible to change the stream read position 
     *        by a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event
     * @return
     *        Return the size in bytes of the media data header that is necessary for data checking.<br>
     *        Return -1 when whole media data is necessary. <br>
     *        Return -2 when only the remaining media data is necessary.
     *
     * JBlend calls this function immediately before 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} 
     * in the data check sequence for playback.
     *
     * This function should return the size of the media data header that is necessary and sufficient 
     * for the check by 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()}.
     * In general, media formats are specified to contain format information in the header portion and 
     * play data after the header.
     * In such cases, this function should analyze and return the size of the header. 
     *
     * JBlend reads from the <code>Inputstream</code> the data of the size returned from this function, and passes the data to 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()}.
     *
     * Depending on the media data format, there exist cases in which a few bytes at the beginning of the 
     * data must be read to analyze the header in detail. 
     * In such cases, return the necessary and minimum size of that data at the 1st call to this function.
     * JBlend reads from the stream the bytes indicated by this function and calls this function again.
     *
     * JBlend repeatedly calls this function until this function returns the same value as <i>length</i> or -1.
     * At the 1st call, JBlend passes #JK_NULL in <i>pBuffer</i> and 0 in <i>length</i>.
     * At succeeding calls, the buffer indicated by <i>pBuffer</i> and <i>length</i> holds 
     * the header portion whose size is returned in the previous call.
     *
     * Note that this function should return the total size of the header to be read from the beginning of the stream, rather than 
     * how many more bytes to be read from the current stream position.
     * That is, the value that can be returned from this function is either a value of <i>length</i> or greater or -1.
     *
     * When data needs not be read from the stream at all, this function can return 0 at the 1st call.
     *
     * If this function returns -1, JBlend reads whole media data from the <code>InputStream</code> and passes it to 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} and 
     * {@link JKT_Media_InputstreamControl#set JKT_Media_InputstreamControl#set()}.
     *
     * If this function returns -2, JBlend reads the remaining media data from the <code>InputStream</code> and passes it to 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} and 
     * {@link JKT_Media_InputstreamControl#set JKT_Media_InputstreamControl#set()}. 
    */
    JKSint32 ( *precheck )( const JKUint8 *pBuffer, const JKSint32 length, JKBool isMarkSupported );
    /**
     *        Passes media data initial portion to the native system to check if it is playable.
     * @param pBuffer
     *        The address of the buffer holding the media data initial portion.
     *        The buffer remains valid until {@link JKT_Media_InputstreamControl#checkClose JKT_Media_InputstreamControl#checkClose()}
     *        is called.
     * @param length
     *        The size in bytes of the buffer indicated by <i>pBuffer</i>.
     *        This size is identical to the value described by the final return value of 
     *        {@link JKT_Media_InputstreamControl#precheck JKT_Media_InputstreamControl#precheck()}.
     *        For example, when precheck() has returned -1, this parameter value is the size of whole media.
     * @param isMarkSupported
     *        A boolean value is passed depending on the return value of the <code>markSupported</code> method of 
     *        the <code>InputStream</code> set for the <code>Player</code> as follows:
     *        - <code>true</code>: #JK_TRUE
     *        - <code>false</code>: #JK_FALSE
     *        .
     *        Note that, when this value is #JK_FALSE, it is not possible to change the stream read position 
     *        by a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event
     * @return
     *        Generate an instance for data checking, and if the operation succeeds, return a check management ID. 
     *        Use values of #JKMEDIA_CHECK_ID_BASE or above for the check management ID. 
     *        If the operation fails, return 0.
     *
     * For a JKT_MediaControl with which a JKT_Media_InputstreamControl is registered as an extended control, 
     * JBlend calls this function instead of {@link JKT_MediaControl#checkOpen JKT_MediaControl#checkOpen()}.
     *
     * The management ID returned by this function is passed in the {@link JKT_MediaControl#check JKT_MediaControl#check()} function 
     * <i>checkID</i> parameter.
     */
    JKSint32 ( *checkOpen )( const JKUint8 *pBuffer, const JKSint32 length, JKBool isMarkSupported );
    /**
     *        Ends the checking started by {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()}.
     * @param checkID
     *        The check management ID. 
     *        The value returned by {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} is designated.  
     * @return
     *        - #JKMEDIA_RESULT_OK<br>
     *          if the function succeeds.
     *        - #JKMEDIA_RESULT_ERROR<br>
     *          if the function fails.
     *
     * For a JKT_MediaControl with which a JKT_Media_InputstreamControl is registered as an extended control, 
     * JBlend calls this function instead of {@link JKT_MediaControl#checkClose JKT_MediaControl#checkClose()}.
     *
     * If a JVM suspend or terminate request is issued after 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} 
     * is called but before this function is called, in some cases JBlend will not call this function. 
     * The native system should therefore allocate and free the resources for the check not in 
     * {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()} 
     * and this function but in {@link JKT_MediaControl#check JKT_MediaControl#check()}. 
     */
    JKSint32 ( *checkClose )( JKSint32 checkID );
    /**
     *        Sets the header portion of the media for playing. 
     * @param id
     *        The player ID.
     *        The value returned by {@link JKT_MediaControl#create JKT_MediaControl#create()} is designated.
     * @param pData
     *        A pointer to the buffer holding the header portion of the media data. 
     *        The same value as the <i>pBuffer</i> parameter to 
     *        {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()}
     *        is designated.
     *        The media data indicated by <i>pData</i> remains valid until
     *        {@link JKT_MediaControl#set JKT_MediaControl#set()} is called passing #JK_NULL in its <i>pData<i> parameter.
     * @param length
     *        The size in bytes of the media data indicated by <i>pData</i>.
     *        The same value as the <i>length</i> parameter to 
     *        {@link JKT_Media_InputstreamControl#checkOpen JKT_Media_InputstreamControl#checkOpen()}
     *        is designated.
     * @param extraID
     *        The additional information identifier that 
     *        {@link JKT_MediaControl#check JKT_MediaControl#check()} has passed to JBlend.
     * @param isMarkSupported
     *        A boolean value is passed depending on the return value of the <code>markSupported</code> method of 
     *        the <code>InputStream</code> set for the <code>Player</code> as follows:
     *        - <code>true</code>: #JK_TRUE
     *        - <code>false</code>: #JK_FALSE
     *        .
     *        Note that, when this value is #JK_FALSE, it is not possible to change the stream read position 
     *        by a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event
     * @return
     *        - #JKMEDIA_RESULT_OK<br>
     *          if the function succeeds.
     *        - #JKMEDIA_RESULT_WAIT<br>
     *          if the function performs its processing asynchronously.
     *        - #JKMEDIA_RESULT_ERROR<br>
     *          if the function fails.
     *
     * Set the initial portion of the media data to the player.
     *
     * For a JKT_MediaControl with which a JKT_Media_InputstreamControl is registered as an extended control, 
     * JBlend calls this function instead of {@link JKT_MediaControl#set JKT_MediaControl#set()}.
     * When, however, the <code>Player\#close</code> method is called, for the purpose of clearing 
     * the media data in the player, JBlend calls {@link JKT_MediaControl#set JKT_MediaControl#set()} 
     * passing #JK_NULL in the <i>pData</i> parameter.
     *
     * Note that, the buffer indicated by <i>pData</i> and <i>length</i> holds only the media data portion 
     * which is described by the final return value of 
     * {@link JKT_Media_InputstreamControl#precheck JKT_Media_InputstreamControl#precheck()}.
     * If remaining data is necessary for play, 
     * the native system must issue #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ events to request the remaining data.
     *
     * If {@link JKT_Media_InputstreamControl#precheck JKT_Media_InputstreamControl#precheck()}
     * has returned a value of 0 or more, then when this function is called, 
     * the stream access position for reading by a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event is 
     * at a <i>length</i> bytes offset from the beginning of the stream.
     * If {@link JKT_Media_InputstreamControl#precheck JKT_Media_InputstreamControl#precheck()}
     * has returned a value of -1 or -2, the stream access position has reached the end of stream.
     *
     * The processing of this function can be performed synchronously or asynchronously.
     *
     * @par Synchronous processing
     * If processing is performed synchronously in this function and succeeds, 
     * change the player state to #JKMEDIA_STATE_NODATA, then return #JKMEDIA_RESULT_OK.
     * @par Asynchronous processing
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT, and notify 
     * JBlend of the result by calling AmMediaPostEvent() from a task other than the JVM task. 
     * If the processing succeeds, change the player state to #JKMEDIA_STATE_NODATA, then 
     * pass a #JKMEDIA_EVENT_JOB_DONE event. 
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed when processing fails.
     *
     * If the operation fails in either synchronous or asynchronous processing, do not change the player state.
     */
    JKSint32 ( *set )( JKSint32 id, const JKUint8 *pData, const JKSint32 length, JKSint32 extraID, JKBool isMarkSupported );
    /**
     *        Notifies the native system of the result of a processing requested from the native system to the <code>InputStream</code>.
     * @param id
     *        The player ID.
     *        The value returned by {@link JKT_MediaControl#create JKT_MediaControl#create()} is designated.
     * @param pRequest
     *        A pointer to the JKT_Media_InputstreamRequest structure holding the processing result.
     *        This pointer points to the JKT_Media_InputstreamRequest structure pointed to by the 
     *        {@link JKT_MediaEvent#usecL usecL} member of the JKT_MediaEvent structure that the native system has passed with a
     *        #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event or a
     *        #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event.
     *
     * This function is called to notify the native system of the result of the processing requested by the native system with a 
     * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event or a
     * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event.
     *
     * For details of the values set in the JKT_Media_InputstreamRequest structure pointed to by the 
     * <i>pRequest</i> parameter, see the descriptions of 
     * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ and 
     * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK.
     */
    void ( *requestComplete )( JKSint32 id, JKT_Media_InputstreamRequest *pRequest );
} JKT_Media_InputstreamControl;


#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIA_INPUTSTREAM_H__ */

/** @} end of group */
