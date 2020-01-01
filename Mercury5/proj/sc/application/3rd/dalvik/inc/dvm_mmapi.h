/*
 * Copyright 2010 MStarSemi. All Rights Reserved.
 * $Id$
 */

#ifndef _DVM_MMAPI_H_
#define _DVM_MMAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#define JSR_MMAPI_TRACE_ON

/* Content types, the value is also defined in com.mstar.j2me.media.player.BasicPlayer.java */
#define MMAPI_CONTENTTYPE_UNKNOWN     -1
#define MMAPI_CONTENTTYPE_WAV          0
#define MMAPI_CONTENTTYPE_MIDI         1
#define MMAPI_CONTENTTYPE_TONESEQUENCE 2
#define MMAPI_CONTENTTYPE_AUDIO_AMR    3
#define MMAPI_CONTENTTYPE_AUDIO_MP3    4
#define MMAPI_CONTENTTYPE_AUDIO_AAC    5
#define MMAPI_CONTENTTYPE_AUDIO_AWB    6
#define MMAPI_CONTENTTYPE_AUDIO_MMF    7
#define MMAPI_CONTENTTYPE_AUDIO_MPEG   8
#define MMAPI_CONTENTTYPE_VIDEO_MPEG   9

// Player listener events, the value is also defined in com.mstar.j2me.media.player.BasicPlayer.java */
#define MMAPI_EVENT_EMPTY                      0
#define MMAPI_EVENT_DEVICE_BUFFERING_STARTED  -1
#define MMAPI_EVENT_DEVICE_BUFFERING_STOPPED  -2
#define MMAPI_EVENT_CLOSED                    -3
#define MMAPI_EVENT_DEVICE_AVAILABLE          -4
#define MMAPI_EVENT_DEVICE_UNAVAILABLE        -5
#define MMAPI_EVENT_DURATION_UPDATED          -6
#define MMAPI_EVENT_END_OF_MEDIA              -7
#define MMAPI_EVENT_ERROR                     -8
#define MMAPI_EVENT_RECORD_ERROR              -9
#define MMAPI_EVENT_RECORD_STARTED           -10
#define MMAPI_EVENT_RECORD_STOPPED           -11
#define MMAPI_EVENT_SIZE_CHANGED             -12
#define MMAPI_EVENT_STARTED                  -13
#define MMAPI_EVENT_STOPPED                  -14
#define MMAPI_EVENT_STOPPED_AT_TIME          -15
#define MMAPI_EVENT_VOLUME_CHANGED           -16

/**
 * Initialize MMAPI
 */
void dvm_mmapi_startup();

/**
 * Finilize MMAPI
 */
void dvm_mmapi_shutdown();

/**
 * Play a tone with the given duration and volume. MediaException will be
 * Thrown if the tone cannot be played.
 *
 * @param  note the note value
 * @param  duration The duration of the tone in milliseconds.
 * @param  volume volume range from 0 to 100. 100 represents the maximum value.
 */
void dvm_mmapi_playTone(int note, int duration, int volume);

/**
 * Create a native player with the given content type. MediaException will be
 * Thrown if the tone cannot be played.
 *
 * @param  contentType the content type.
 * @param  _isCapture the flag if it is a capturer. , a capture can capture the audio
 *                    from the microphone or the video from the camera.
 * @return the player ID.
 */
int dvm_mmapi_createPlayer(int contentType, int isCapturer);

/**
 * Set a media URL or complete media data for playing.. MediaException will be
 * Thrown if the media data can't be set.
 *
 * @param  playerId the player ID.
 * @param data the media URL or data, the data can't be used directly and
 *             must be copied in native.
 * @param isURL the flag if the data is a media URL.
 */
void dvm_mmapi_setMediaData(int playerId, char* data, int length, int isUrl);

/**
 * Get the duration of the media or -1 if the duration cannot be determined.
 *
 * @param  playerId the player ID.
 * @return the duration in microseconds or -1.
 */
long dvm_mmapi_getDuration(int playerId);

/**
 * Gets this Player's current media time in microseconds or -1 if the
 * media time cannot be determined.
 *
 * @param  playerId the player ID.
 * @return the current media time in microseconds or -1.
 */
long dvm_mmapi_getMediaTime(int playerId);

/**
 * Set this Player's media time in microseconds. MediaException will be
 * Thrown if the media time can't be set.
 *
 * @param  playerId the player ID.
 * @param  now The new media time in microseconds.
 * @return The actual media time set in microseconds. 
 */
long dvm_mmapi_setMediaTime(int playerId, long now);

/**
 * Open the media device to prepare playing the media. MediaException will be
 * Thrown if the player can't be prefetched.
 *
 * @param  playerId the player ID.
 * @return TRUE if success, FALSE means no media device available.
 */
int dvm_mmapi_prefetch(int playerId);

/**
 * Close the media device that has been open for the media. MediaException will be
 * Thrown if the player can't be prefetched.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_deallocate(int playerId);

/**
 * Start playing the media, If the Player was previously stopped by calling
 * dvm_mmapi_stop(), it will resume playback from where it was previously stopped.
*  MediaException will be Thrown if the media can't be started.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_start(int playerId);

/**
 * Stops the Player. It will pause the playback at the current media time.
*  MediaException will be Thrown if the media can't be started.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_stop(int playerId);

/**
 * Close the player and release its resources.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_close(int playerId);

/**
 * Receive the player event, the method can be block until a event happen if it won't
 * effect the Java VM. MediaException will be Thrown if player event can't be received.
 *
 * @param  playerId the player ID.
 * @return the player event or the time in milliseconds to wait before Java call it again. 
 */
int dvm_mmapi_receiveEvent(int playerId);

/**
 * Get the current volume of the player, the value is between 0 and 100.
 *
 * @param  playerId the player ID.
 * @return the current volume from 0 to 100.
 */
int dvm_mmapi_getVolume(int playerId);

/**
 * Set the player's volume. the value is between 0 and 100. 
 *
 * @param  playerId the player ID.
 * @param  volume the volume to be set.
 * @return The volume that was actually set.
 */
int dvm_mmapi_setVolume(int playerId, int volume);

/**
 * Seek to a given video frame. If the given frame number is less than the first
 * or larger than the last frame number in the media, seek will jump to either
 * the first or the last frame respectively.
 *
 * @param  playerId the player ID.
 * @param  frameNumber the frame to seek to.
 * @return The actual frame that the Player has seeked to.
 */
int dvm_mmapi_seek(int playerId, int frameNumber);

/**
 * Skip a given number of frames from the current position. If the given
 * framesToSkip will cause the position to extend beyond the first or last
 * frame, skip will jump to the first or last frame respectively.
 *
 * @param  playerId the player ID.
 * @param  framesToSkip the number of frames to skip from the current position.
 * @return the actual number of frames skipped.
 */
int dvm_mmapi_skip(int playerId, int framesToSkip);

/**
 * Converts the given frame number to the corresponding media time.
 *
 * @param  playerId the player ID.
 * @param  frameNumber the input frame number for the conversion.
 * @return the converted media time in microseconds for the given frame.
 *         If the conversion fails, -1 is returned.
 */
long dvm_mmapi_mapFrameToTime(int playerId, int frameNumber);


/**
 * Converts the given media time to the corresponding frame number..
 *
 * @param  playerId the player ID.
 * @param  mediaTime the input media time for the conversion in microseconds.
 * @return the converted frame number for the given media time.
 *         If the conversion fails, -1 is returned.
 */
int dvm_mmapi_mapTimeToFrame(int playerId, long mediaTime);

/**
  * Set the area where the video is displayed, the video can be clip or scale if the 
  * area is smaller or bigger than the the dimensions of the video. MediaException 
  * will be thrown if resizing is not supported or the operation failed due to
  * hardware or software limitations.
  *
  * @param  playerId the player ID.
  * @param  x the X-coordinate of the video with respect to the physics screen.
  * @param  y the Y-coordinate of the video with respect to the physics screen.
  * @param  width the width the video to be displayed.
  * @param  height the height the video to be displayed.
  */
void dvm_mmapi_setDisplayArea(int playerId, int x, int y, int width,  int height);

/**
 * Show or hide the video.
 *
 * @param  playerId the player ID.
 * @param  visible Show the video if 1, hide it if 0.
 */
void dvm_mmapi_setVisible(int playerId, int visible);

/**
 * Set the video to show on the full screen. MediaException will be thrown if
 * fullScreenMode is true but the full screen mode is not supported.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_setDisplayFullScreen(int playerId, int fullScreenMode);

/**
 * Return the width of the source video. The width must be a positive number.
 *
 * @param  playerId the player ID.
 * @return the width of the source video.
 */
int dvm_mmapi_getSourceWidth(int playerId);

/**
 * Return the height of the source video. The height must be a positive number.
 *
 * @param  playerId The player ID.
 * @return The height of the source video.
 */
int dvm_mmapi_getSourceHeight(int playerId);

/**
 * Get the size of a snapshot of the displayed content. Features and format of
 * the captured image are specified by imageType. MediaException will be thrown
 * if the Player does not support snapshots.
 *
 * @param  playerId the player ID.
 * @param  imageType The unicode string to indicate the image format and resolution.
 * @param  imageLen The length of the unicode string.
 * @return The snapshot size.
 */
int dvm_mmapi_getSnapshotSize(int playerId,  const unsigned short* imageType, int typeLen);

/**
 * Get a snapshot of the displayed content. Features and format of
 * the captured image are specified by imageType. MediaException will be thrown
 * if the Player does not support snapshots or the buffer length is smaller or bigger
 * than the snapshot size.
 *
 * @param  playerId the player ID.
 * @param  imageType The unicode string to indicate the image format and resolution.
 * @param  imageLen The length of the unicode string.
 * @param  dataBuf The buffer to store the snapshot data.
 * @param  bufLen the length of the buffer.
 */
void dvm_mmapi_getSnapshotData(int playerId,
                               const unsigned short* imageType,
                               int typeLen,
                               char* dataBuf,
                               int bufLen);

/**
 * Set the record size limit. When recording is in progress, INT_EVENT_END_OF_MEDIA
 * will be sent from native in the following cases:
 * - Record size limit is reached
 * - If the requested size is less than the already recorded size
 * - No more space is available.
 * To remove the record size limit, set it to 0x7FFFFFFF. By default, the record
 * size limit is not set.
 * MediaException will be thrown if setting the record size limit is not supported.
 *
 * @param  playerId the player ID.
 * @param size The record size limit in number of bytes.
 * @return The actual size limit set.
 */
int dvm_mmapi_setRecordSizeLimit(int playerId, int size);

/**
 * Start recording the media. MediaException will be thrown if fail to start recording the media.
 *
 * @param  playerId the native player ID.
 */
void dvm_mmapi_startRecord(int playerId);

/**
 * Stop recording the media. After calling it, dvm_mmapi_nStartRecord() can be called to
 * resume the recording or restarting recording. MediaException will be thrown if fail
 * to stop recording the media.
 *
 * @param  playerId the player ID.
 */
void dvm_mmapi_stopRecord(int playerId);

/**
 * Read the record data. the method will be called by loop to get a complete record data.
 * MediaException will be thrown if fail to get the record data.
 *
 * @param playerId the player ID.
 * @param buf the buffer to store the record data.
 * @param size the size of the record data.
 * @return the actual size of the date get.
 */
int dvm_mmapi_readRecordData(int playerId, char* buf, int size);

/**
 * Erase the current recording, the recorded data will be released after the method.
 * MediaException will be thrown if fail to get the record data.
 *
 * @param  playerId the native player ID.
 */
void dvm_mmapi_resetRecord(int playerId);

#ifdef __cplusplus
}
#endif

#endif //_DVM_MMAPI_H_
