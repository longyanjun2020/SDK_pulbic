/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaOption.h
 *  Optional Media Optional Control Function
 */

/**
 * @addtogroup MediaControl_JSI_Option
 *
 * @{
 */

#ifndef __JKMEDIAOPTION_H__
#define __JKMEDIAOPTION_H__

#include "JkTypes.h"
#include "JkMediaControl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
/**
 * Metadata is not ready yet
 */
#define JKMEDIA_METADATA_NOT_READY       -10

/**
 */
/**
 * No linear transformation available.
 */
#define JKMEDIA_SCALING_FIXED_SIZE        0
/**
 * Linear transformation can be performed with keeping image aspect ratio.
 */
#define JKMEDIA_SCALING_FIXED_ASPECT_RATIO 1
/**
 * Linear transformation can be performed with arbitrary 
 * magnification in x or y direction.
 */
#define JKMEDIA_SCALING_INDEPENDENT        2
/**
 * The value indicating equal magnification.
 * The value which multiplied actual magnification by this value is
 * passed as the parameter to JKT_Media_VideoControl structure <i>setBounds()</i>.
 */
#define JKMEDIA_SCALING_UNITY              0x100

/**
 */
/**
 * A structure defining speed control functions.
 */
typedef struct {
    /**
     * Sets the playback rate.
     * @param id
     *  The player ID. 
     * @param speedx100000
     *   A 100000 times the value of the ratio to media default playback speed.
     *   For the speed equal to the default speed, 100000 is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   When this function is called, the native system must set the <i>speedx100000</i> 
     *   parameter to the player, as a 100000 times the value of the playback rate, 
     *   to determine actual speed.
     *   The native system must also apply the tempo that has been set to the player in this determination.
     *   
     *   Actual speed is determined as follows.
     *
     *   speed = ([default speed] * <i>speedx100000</i> / 100000 ) * 
     *             ( [tempo set to the player] / [media default tempo])
     *
     *   The playback rate is designated as a A 100000 times the value of the ratio.
     *   Depending on the error in the playback clock etc., if such precision 
     *   is not possible, the native system can adopt possible precision.
     */
    JKSint32 ( *setSpeed )( JKSint32 id, JKSint32 speedx100000 );

    /**
     * Gets current playback rate.
     * @param id
     *  The player ID. 
     * @return
     *   Return a 100000 times the value of the playback rate set to the player.
     *   For the speed equal to the default speed, return 100000.
     *   If the operation fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getSpeed )( JKSint32 id );

    /**
     * Gets the range of available playback rate that can be set.
     * @param id
     *  The player ID. 
     * @param pMin
     *   A pointer to the buffer for storing the lower limit of playback rate.
     *   Store a 100000 times the value of the rate.
     * @param pMax
     *   A pointer to the buffer for storing the upper limit of playback rate.
     *   Store a 100000 times the value of the rate.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getSpeedRange )( JKSint32 id, JKSint32* pMin, JKSint32* pMax );
} JKT_Media_SpeedControl;

/**
 * A structure defining tempo control functions.
 *
 * When the device manufacturer implement this structure, 
 * #JKT_Media_SpeedControl must be implemented as well;
 * furthermore, these features must be controlled independently.
 *
 * The default value of tempo is 120 BPM. 
 * When no tempo designation is found in the media, use this value as the initial value.
 */
typedef struct {
    /**
     * Sets tempo
     * @param id
     *  The player ID. 
     * @param tempox1000
     *   A 1000 times the value of the tempo in BPM (Beats Per Minute) is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   When this function is called, the native system must set the <i>tempox1000</i> 
     *   parameter to the player, as a 1000 times the value of the tempo, 
     *   to determine actual tempo.
     *   The native system must also apply the playback rate that has 
     *   been set to the player in this determination.
     *   
     *   Actual speed is determined as follows.
     *
     *   speed = ([default speed] * playback rate ) * 
     *             ( [tempo set to the player] / [media default tempo])
     *
     *   The <i>tempox1000</i> is designated as a 1000 times the value of the tempo.
     *   Depending on the error in the playback clock etc., if such precision 
     *   is not possible, the native system can adopt possible precision. 
     */
    JKSint32 ( *setTempo )( JKSint32 id, JKSint32 tempox1000 );

    /**
     * Gets current tempo.
     * @param id
     *  The player ID. 
     * @return
     *   Return a 1000 times the value of the tempo set to the player.
     *   If the media does not contain tempo information, return 120000.
     */
    JKSint32 ( *getTempo )( JKSint32 id );
} JKT_Media_TempoControl;

/**
 * A structure defining stop time control
 */
typedef struct {
    /**
     * Sets the stop time.
     * @param id
     *  The player ID.
     * @param usecH
     *   The high 32 bits of the stop time in microseconds.
     *   #JKMEDIA_TIME_MAX_HIGH is designated to cancel the setting of stop time. 
     *   (i.e. the player should play to the end)
     * @param usecL
     *   The low 32 bits of the stop time in microseconds.
     *   #JKMEDIA_TIME_MAX_LOW is designated to cancel the setting of stop time. 
     *   (i.e. the player should play to the end)
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  When this function is called, in the native system set in the player 
     *  the stop time designated in <i>usecH</i> and <i>usecL</i>.
     * 
     *  The stop time is expressed in a 64 bit integer, in microseconds.
     *  The native system must set the maximum value
     *  (#JKMEDIA_TIME_MAX_HIGH, #JKMEDIA_TIME_MAX_LOW) 
     *  of 64 bit integer as the default stop time.
     *
     *  In the player for which a stop time was designated using this function, 
     *  handle as follows the stopping of play by stop time setting. 
     *  For details of player behavior in relation to a preset stop time, see 
     *  the description of the Java API 
     *  <code>javax.microedition.media.control StopTimeControl</code>
     *   interface.
     *
     *  <ul>
     *  <li>
     *  If a stop time longer than or equal to the media data single play duration is 
     *  designated, do not use the stop time to stop play. 
     *  If the designated stop time is a negative value, treat the media time 
     *  for stopping as being set at the beginning of the media data. 
     *  <li>
     *  When the media time reaches the stop time, stop playing and change
     *  the state to #JKMEDIA_STATE_PAUSED. 
     *  Then reset the stop time to its initial value and notify JBlend of a
     *   #JKMEDIA_EVENT_STOPPED_AT_TIME event. 
     *  <li>
     *  When the player is playing and the stop time is set earlier than the 
     *  media time, stop at the current media time and change the state to
     *  #JKMEDIA_STATE_PAUSED. 
     *  Then reset the stop time to its initial value and notify JBlend of a
     *   #JKMEDIA_EVENT_STOPPED_AT_TIME event. 
     *  initial value. 
     *  </ul>
     *
     *  If a play time designated by setTime() of the JKT_MediaControl 
     *  function structure exceeds both the stop time and the media data 
     *  duration, notify JBlend first of a stop time-related event. 
     *  That is, put the player in #JKMEDIA_STATE_PAUSED state in accord
     *  with stop processing based on the above stop time setting and 
     *  pass a #JKMEDIA_EVENT_STOPPED_AT_TIME event to JBlend, then 
     *   as soon as restart() is called, put the player in #JKMEDIA_STATE_READY 
     *   state and pass a #JKMEDIA_EVENT_END_OF_MEDIA event to JBlend.
     *
     *  This function is called only when a player is in the following states. 
     *  <ul>
     *    <li> #JKMEDIA_STATE_STARTED <br>
     *        It is not called, however, if a stop time has already been set by 
     *        setStopTime(). 
     *    <li> #JKMEDIA_STATE_DATA_SET 
     *    <li> #JKMEDIA_STATE_READY 
     *    <li> #JKMEDIA_STATE_PAUSED 
     *    <li> #JKMEDIA_STATE_ERROR 
     *  </ul>
     *
     */
    JKSint32 ( *setStopTime )( JKSint32 id, JKUint32 usecH, JKUint32 usecL );

    /**
     * Get the current stop time set in the player.
     * @param id
     *  The player ID
     * @param pUsecH
     *   A pointer to the buffer for storing the high 32 bit of the stop time in microseconds.
     *   If stop time is not set in the player, put #JKMEDIA_TIME_MAX_HIGH to the buffer.
     * @param pUsecL
     *   A pointer to the buffer for storing the low 32 bit of the stop time in microseconds.
     *   If stop time is not set in the player, put #JKMEDIA_TIME_MAX_LOW to the buffer.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  When this function is called, in the native system return the stop time
     *  set for the player. 
     *
     *  The stop time is expressed in a 64 bit integer, in microseconds.
     *  The native system must set the maximum value
     *  (#JKMEDIA_TIME_MAX_HIGH, #JKMEDIA_TIME_MAX_LOW) 
     *  of 64 bit integer as the default stop time.
     */
    JKSint32 ( *getStopTime )( JKSint32 id, JKUint32* pUsecH, JKUint32* pUsecL );
} JKT_Media_StopControl;

/**
 * A structure defining playback pitch control functions
 */
typedef struct {
    /**
     * Sets a playback pitch.
     * @param id
     *  The player ID.
     * @param decicent
     *   The playback pitch in milli(1/1000)-semitones.
     *   The value of 0 is designated for playing media at default pitch. 
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  The pitch change is specified in number of "milli(1/1000)- semitones." 
     *  If such precision is not possible, the native system can adopt possible precision. 
     *
     *  As for wave form data, such as PCM, changing its playback pitch causes playback speed change. 
     *  Device manufacturer should implement playback pitch control only for the media for which 
     *  playback pitch and playback speed can be controlled independently.
     */
    JKSint32 ( *setPitch )( JKSint32 id, JKSint32 decicent );

    /**
     * Gets current playback pitch.
     * @param id
     *  The player ID.
     * @return
     *  Return the pitch set in the player in "milli(1/1000)- semitones." 
     *  If the player is to play without pitch change, return 0.
     */
    JKSint32 ( *getPitch )( JKSint32 id );

    /**
     * Gets the range of available playback pitch that can be set.
     * @param id
     *  The player ID.
     * @param pMin
     *   A pointer to the buffer for storing the lower limit of pitch in milli(1/1000)- semitones.
     * @param pMin
     *   A pointer to the buffer for storing the upper limit of pitch in milli(1/1000)- semitones.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getPitchRange )( JKSint32 id, JKSint32* pMin, JKSint32* pMax );
} JKT_Media_PitchControl;

/**
 * A struncture defining metadata control functions.
 *
 * Functions defined here may be called while media data is being checked before playing.
 */
typedef struct {
    /**
     *  Gets the number of the metadata that can be acquired.
     * @param id
     *  The player ID.
     * @return
     *   Return the number of types that this control can retrieve.
     *   The number must be a positive value.
     *   The values from 0 to the return value minus 1 are used as an index to a metadata type.
     *
     * This function can be invoked between the invoking of the checkOpen() and 
     * checkClose() member functions of the JKT_MediaControl function structure.
     * The allocation and deallocation of resources necessary for the processing 
     * must be completed inside this function.
     */
    JKSint32 ( *getSize )( JKSint32 id );

    /**
     *  Gets the keyword string for a metadata type.
     * @param id
     *  The player ID.
     * @param num
     *  The metadata index.
     *  A value from 0 to #getSize()() return value minus 1 is designated.
     * @param pStr
     *  A pointer to the buffer for storing the keyword.
     * @param size
     *  The size of the buffer.
     * @return
     *   Return the number of characters that are stored in the buffer pointed
     *    by the <i>pStr</i> parameter.
     *   If the buffer size is insufficient, return the required buffer size.
     *
     * Put the keyword string of the metadata indicated by <i>num</i> in the 
     * buffer indicated by the <i>pStr</i> and size arguments, and return the 
     * number of characters of the stored string. 
     *  If the buffer size is not sufficient, 
     *  JBlend calls this function again after allocating a buffer of the 
     *  required size.
     *
     * This function can be invoked between the invoking of the checkOpen() and 
     * checkClose() member functions of the JKT_MediaControl function structure.
     * The allocation and deallocation of resources necessary for the processing 
     * must be completed inside this function.
     *
     *  If MMAPI is supported, use the following predefined keywords for 
     *  the indicated types.
     *  <dl>
     *    <dt>Author</dt>
     *      <dd>"author"</dd>
     *    <dt>Copyright Information</dt>
     *      <dd>"copyright"</dd>
     *    <dt>Date of creation</dt>
     *      <dd>"date"</dd>
     *    <dt>Title</dt>
     *      <dd>"title"</dd>
     *   </dl>
     
     */
    JKSint32 ( *getKey )( JKSint32 id, JKSint32 num, JKWChar* pStr, JKSint32 size );

    /**
     *  Gets the metadata string.
     * @param id
     *  The player ID.
     * @param num
     *  The metadata index.
     *  A value from 0 to #getSize()() return value minus 1 is designated.
     * @param pStr
     *  A pointer to the buffer for storing the metadata.
     * @param size
     *  The size of the buffer.
     * @return
     *   Return the number of characters that are stored in the buffer pointed to by the <i>pStr</i> parameter.<br>
     *   Return 0 if designated data does not exist in the media.<br>
     *   If the buffer size is insufficient, return the required buffer size without storing data to the buffer.<br>
     *   Return #JKMEDIA_METADATA_NOT_READY if the native system cannot get the metadata yet.<br> 
     *   Return #JKMEDIA_RESULT_ERROR if the operation fails for other reason. 
     *
     *  If the buffer size is not enough, JBlend calls this function 
     *  again after allocating buffer of required size.
     */
    JKSint32 ( *getValue )( JKSint32 id, JKSint32 num, JKWChar* pStr, JKSint32 size );
} JKT_Media_MetaDataControl;

/**
 * A structure defining MIDI device control functions.
 */
typedef struct {
    /**
     * Checks if MIDI device information is available.
     * @param id
     *  The player ID.
     * @return
     *   Return JK_TRUE if MIDI device information is availabe, otherwise return JK_FALSE.
     *
     *   If this function returns JK_FALSE, following functions must return #JKMEDIA_RESULT_ERROR.
     *    <ul>
     *    <li>getProgram()()
     *    <li>getBankListSize()()
     *    <li>getBankList()()
     *    <li>getProgramListSize()()
     *    <li>getProgramList()()
     *    <li>getProgramName()()
     *    <li>getKeyName()()
     *    </ul>
     */
    JKBool ( *canQuery )( JKSint32 id );

    /**
     * Gets channel volume.
     * @param id
     *  The player ID.
     * @param channel
     *  MIDI channel (0 to 15)
     * @return
     *   If the operation succeeds, return the current volume value (0 to 127); 
     *   if it fails, return -1.
     */
    JKSint32 ( *getChVolume )( JKSint32 id, JKSint32 channel );


    /**
     * Sets channel volume.
     * @param id
     *  The palyer ID.
     * @param channel
     *  MIDI channel (0 to 15)
     * @param volume
     *   The volume value. (0 to 127)
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *setChVolume )( JKSint32 id, JKSint32 channel, JKSint32 volume );

    /**
     * Gets sound bank and program number.
     * @param id
     *  The player ID.
     * @param channel
     *  MIDI channel (0 to 15)
     * @param pBank
     *   A pointer to the buffer for storing the bank identifier.
     *   Store a 14 bit integer that consists of higher 7 bit of the 
     *   bank select MSB and lower 7 bit of the bank select LSB.
     * @param pProgram
     *   A pointer to the buffer for storing the program number (0 to 127).
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getProgram )( JKSint32 id, JKSint32 channel, JKSint32* pBank, JKSint32* pProgram );

    /**
     * Sets a program number.
     * @param id
     *  The player ID.
     * @param channel
     *  MIDI channel (0 to 15)
     * @param bank
     *   The identifier of the sound bank to which the program is set.
     *   (A 14 bit integer that consists of higher 7 bit of the 
     *   bank select MSB and lower 7 bit of the bank select LSB.)
     * @param program
     *   The program number (0 to 127).
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *setProgram )( JKSint32 id, JKSint32 channel, JKSint32 bank, JKSint32 program );

    /**
     * Sends a short MIDI message.
     * @param id
     *  The player ID.
     * @param type
     *   The status byte of the message.
     * @param param1
     *   Parameter 1. 
     *   When no parameter is required for the message, 0 is designated.
     * @param param2
     *   Parameter 2. 
     *   When the message has 1 byte parameter only, 0 is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *sendShortEvent )( JKSint32 id, JKSint32 type, JKSint32 param1, JKSint32 param2 );

    /**
     * Sends a long MIDI message.
     * @param id
     *  The player ID
     * @param pData
     *   A pointer to the buffer holding data containing a long event. 
     *   The pointer is valid until this function returns. 
     * @param dataSize
     *   The size in bytes of data held in the buffer indicated by <i>pData</i>.
     * @param offset
     *   The offset of the long event from the beginning of the buffer indicated by <i>pData</i>. 
     * @param length
     *   The size in bytes of the long event. 
     * @return
     *   If the operation succeeds, return the size (in bytes) of the actually sent long event; 
     *   else return #JKMEDIA_RESULT_ERROR.
     *
     *    A long event indicated by the <i>pData</i>, <i>offset</i>, and 
     *    <i>length</i> parameters may contain 
     *    multiple system exclusive messages or short events.
     *    When this function is called, in the native system perform the appropriate
     *    processing in accord with the designated long event contents. 
     *    
     *   Figure 1 shows the relation of the data indicated by <i>pData</i> 
     *  to <i>dataSize</i>, <i>offset</i>, and <i>length</i>.
     *  @image html sendlongevent_data_en.gif "Figure 1. Relation of Data Indicated by pData to dataSize, offset, and length"
     */
    JKSint32 ( *sendLongEvent )( JKSint32 id, JKUint8* pData, JKSint32 dataSize, JKSint32 offset, JKSint32 length );

    /**
     * Gets the size of a list of sound banks
     * @param id
     *  The player ID.
     * @param isCustom
     *  Indicates whether the list is for custom banks. 
     * @return
     *   Return the size (in bytes) of a list of existing sound banks.
     *   If the operation fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getBankListSize )( JKSint32 id, JKBool isCustom );

    /**
     * Gets a list of sound banks
     * @param id
     *  The player ID.
     * @param isCustom
     *  Indicates whether the list is for custom banks. 
     * @param pList
     *   A pointer to the buffer for storing a list of sound banks.
     *   Store indentifiers of sound banks to the buffer in order.
     *   The lower 14 bit of each 32 bit integer must be a sound bank 
     *   identifier, which consists of higher 7 bit of the bank select 
     *   MSB and lower 7 bit of the bank select LSB.     
     * @param listSize
     *   The size (in bytes) of the buffer pointed to by <i>pList</i>.
     *   The return value of getBankListSize()() is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getBankList )( JKSint32 id, JKBool isCustom, JKSint32* pList, JKSint32 listSize );

    /**
     * Gets the size of a list of program numbers.
     * @param id
     *  The player ID.
     * @param bank
     *   The identifier of the sound bank.
     *   The lower 14 bit of this parameter is a sound bank 
     *   identifier, which consists of higher 7 bit of the bank select 
     *   MSB and lower 7 bit of the bank select LSB.     
     * @return
     *   Return the size (in bytes) of a list of programs existing in designated sound bank.
     *   If the operation fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getProgramListSize )( JKSint32 id, JKSint32 bank );

    /**
     * Gets a list of program numbers.
     * @param id
     *  The player ID.
     * @param bank
     *   The identifier of the sound bank.
     *   The lower 14 bit of the bank parameter is a sound bank 
     *   identifier, which consists of higher 7 bit of the bank select 
     *   MSB and lower 7 bit of the bank select LSB.     
     * @param pList
     *   A pointer to the buffer for storing a list of program numbers.
     * @param listSize
     *   The size (in bytes) of the buffer pointed to by <i>pList</i>.
     *   The return value of getProgramListSize()() is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getProgramList )( JKSint32 id, JKSint32 bank, JKSint32* pList, JKSint32 listSize );

    /**
     *  Gets the instrument name assigned to a program.
     * @param id
     *  The player ID.
     * @param bank
     *   The identifier of the sound bank.
     *   The lower 14 bit of this parameter is a sound bank 
     *   identifier, which consists of higher 7 bit of the bank select 
     *   MSB and lower 7 bit of the bank select LSB.     
     * @param program
     *  The progarm number.
     * @param pName
     *   A pointer to the buffer for storing the instrument name assgined to the pragram.
     * @param nameSize
     *   The size of the buffer pointed to by pName.
     * @return
     *   Return the number of the characters the native system has stored in the buffer
     *   pointed to by the pName parameter.
     *   No '\0' is needed for terminating the string. <br>
     *   When the buffer size is insufficient, return required buffer size. <br>
     *   Return 0 if there is no name associated to the program.<br>
     *   Return a negative value when the native system cannot acquire the name for some reason. 
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getProgramName )( JKSint32 id, JKSint32 bank, JKSint32 program, JKWChar* pName, JKSint32 nameSize );

    /**
     *  Gets the instrument name assigned to a key in a key-mapped bank.
     * @param id
     *  The player ID.
     * @param bank
     *   The identifier of the sound bank.
     *   The lower 14 bit of this parameter is a sound bank 
     *   identifier, which consists of higher 7 bit of the bank select 
     *   MSB and lower 7 bit of the bank select LSB.     
     * @param program
     *  The program number (key map number).
     * @param key
     *  The key number. (0 to 127)
     * @param pName
     *   A pointer to the buffer for sroring the instrument name.
     * @param nameSize
     *   The size (in bytes) of the buffer pointed to by the pName parameter.
     * @return
     *   Return the number of the characters of the designated key. <br>
     *   Return 0 if there is no name assigned to the key. <br>
     *   Return a negative value if the operation fails for other reason.
     *
     *   If the native system returns JK_FALSE  by canQuery()(), implement 
     *   this function so that it returns #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *getKeyName )( JKSint32 id, JKSint32 bank, JKSint32 program, JKSint32 key, JKWChar* pName, JKSint32 nameSize );
} JKT_Media_MIDIControl;

/**
 * A structure defining playback clock control functions.
 *
 * Device manufacturer should implement functions for this feature 
 * only if using common clock between players is possible.
 * When implementing this feature, device manufacturer must guarantee 
 * that the media time of the associated players does not shift. 
 */
typedef struct {
    /**
     * Associates a player as a base player having common clock.
     * @param id
     *  The player ID.
     * @param pControl
     *  A pointer to a JKT_MediaControl structure of the player that has base clock.
     *  If JK_NULL is designated, cancel using common playback clock.
     * @param masterID
     *  The player ID of the player that has base clock.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  This function is called to use same playback clock between players.
     *  The native system does not need to synchronize player operations such as playing or stopping.
     */
    JKSint32 ( *shareClock )( JKSint32 id, JKT_MediaControl const* pControl, JKSint32 masterID );

    /**
     * Gets current media time of a player.
     * @param id
     *  The player ID.
     * @param pTimeH
     *   A pointer to the buffer for storing the high 32 bit of media time.
     * @param pTimeL
     *   A pointer to the buffer for storing the low 32 bit of media time.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   The native system should store the media time in 64 bit value to the buffer.
     *   When structurally unacquirable, the present time presented by OS may be used.
     */
    JKSint32 ( *getClock )( JKSint32 id, JKUint32* pTimeH, JKUint32* pTimeL );
} JKT_Media_SyncControl;

/**
 * A structure defining media image display control functions.
 */
typedef struct {
    /**
     * Gets available linear transformation mode (expansion or reduction mode). 
     * @param id
     *  The player ID.
     * @return
     *    Return one of the following, as an available linear transformation mode.<br>
     *    #JKMEDIA_SCALING_FIXED_SIZE<br>
     *    #JKMEDIA_SCALING_FIXED_ASPECT_RATIO<br>
     *    #JKMEDIA_SCALING_INDEPENDENT<br>
     */
    JKSint32 ( *getScalingMode )( JKSint32 id );

    /**
     * Sets the display region and magnification.
     * @param id
     *  The player ID.
     * @param x
     *  The x coordinate (in pixel) of the upper left corner of the display region in real screen. 
     *  The value which indicates the outside of the real screen is never designated. 
     * @param y
     *  The y coordinate (in pixel) of the upper left corner of the display region in real screen. 
     *  The value which indicates the outside of the real screen is never designated. 
     * @param width
     *  The width of the display region, in pixels.
     *  The value which indicates the outside of the real screen is never designated. 
     * @param height
     *  The height of the display region, in pixels.
     *  The value which indicates the outside of the real screen is never designated. 
     * @param magX
     *  The result which multiplied x-direction magnification by #JKMEDIA_SCALING_UNITY
     * @param magY
     *  The result which multiplied y-direction magnification by #JKMEDIA_SCALING_UNITY
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  This function should perform parameter setting only;
     *  namely, it is not needed to perform repainting.
     *
     *  For details how the native system should reflect indicated parameters to image drawing, 
     *  see explanations of <i>repaint()()</i>.
     */
    JKSint32 ( *setBounds )( JKSint32 id, JKSint32 x, JKSint32 y,
                             JKSint32 width, JKSint32 height, JKSint32 magX, JKSint32 magY );

    /**
     * Sets the offset position of the media image in the display region. 
     * @param id
     *  The player ID.
     * @param offset_x
     *  The x position of the origin of media drawing region, 
     *  expressed as a x-direction offset (in pixels) relative to the display region.
     * @param offset_y
     *  The y position of the origin of media drawing region, 
     *  expressed as a x-direction offset (in pixels) relative to the display region.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  This function should perform parameter setting only;
     *  namely, it is not needed to perform repainting.
     *
     *  For details how the native system should reflect indicated parameters to image drawing, 
     *  see explanations of <i>repaint()()</i>.
     */
    JKSint32 ( *setOffset )( JKSint32 id, JKSint32 offset_x, JKSint32 offset_y );

    /**
     * Draws current frame to the virtual screen.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   The native system should draw the current frame on the virtual screen, 
     *   reflecting the parameters set by setBounds()() and setOffset()().
     *   Figure 1 shows the reflection of the parameters.
     *
     *  @image html video_drawing_offset_en.gif "Figure 1. Image Drawing Based on the Pamrameters set by setBounds() and setOffset()."
     *
     *  - The <i>x, y, width, height, magX</i>, and <i>magY</i> in Figure 1 indicate 
     *    the parameters of same name passed to the setBounds()() function.
     *  - The <i>offsetX</i>, and <i>offsetY</i> in Figure 1 indicate 
     *    the parameters of the same name passed to the setOffset()() function.
     *  - The W, and H in figure 1 indicate width and height of the source media image, respectively.
     *  .
     *  
     *  The display region is the real screen rectangle area expressed 
     *  with <i>x, y, width</i>, and <i>height</i>. 
     *  In this region, the native system has to draw the processed image to 
     *  the postion indicated by offsetX and offsetY.
     *  The processing must include expanding or reducing the source image
     *  according to the magnification indicated by <i>magX</i> and <i>magY</i>. 
     *  The drawing must take place only in the display region.
     *
     *  Depending on the source image size, display region, magnification, or offset, 
     *  there may be portion on which no image is drawn.
     *  The native system has to fill such portion with a background color.
     *  The background color is implementation-dependent.
     *
     *  The following is the consequences of the failure of this function 
     *  for the media types that are supported for MMAPI.
     *
     *  <ul>
     *   <li>When the player is in #JKMEDIA_STATE_READY state.<br>
     *       The first video frame is now displayed until Player.start is called.
     *
     *   <li>When the player is in #JKMEDIA_STATE_STARTED state.<br>
     *       A flicker of media playback may occur.
     *
     *   <li>When the player is in #JKMEDIA_STATE_PAUSED state. <br>
     *       When GUI component is repainted, the last frame displayed 
     *       by the player is not drawn in the repainting process.
     *  </ul>
     *
     *  @if MEXA
     *  For the MEXA 1.0.0 player, this function must succeed if it is 
     *  called after JKT_MediaControl structure <i>start()</i> is called, and
     *  it must return #JKMEDIA_RESULT_OK without repainting 
     *  if the function is called in the period after the function call of 
     *  <i>set()</i> for setting the media data to the player
     *  until the first function call of <i>start()</i>.
     *  @else
     *  @if JSCL
     *  For the JSCL 1.2.2 player, this function must succeed if it is 
     *  called after JKT_MediaControl structure <i>start()</i> is called, and
     *  it must return #JKMEDIA_RESULT_OK without repainting 
     *  if the function is called in the period after the function call of 
     *  <i>set()</i> for setting the media data to the player
     *  until the first function call of <i>start()</i>.
     *  @endif
     *  @if VSCL
     *  For the VSCL 1.1 player, this function must succeed if it is 
     *  called after JKT_MediaControl structure <i>start()</i> is called, and
     *  it must return #JKMEDIA_RESULT_OK without repainting 
     *  if the function is called in the period after the function call of 
     *  <i>set()</i> for setting the media data to the player
     *  until the first function call of <i>start()</i>.
     *  @endif
     *  @endif
     */
    JKSint32 ( *repaint )( JKSint32 id );

    /**
     * Starts updating the real screen.
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  At the initial state of a player, updating the real screen must be disabled.
     */
    JKSint32 ( *startUpdate )( JKSint32 id );

    /**
     * Pauses updating the real screen. 
     * @param id
     *  The player ID.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  When this function is called during play, the player should not 
     *  stop playing; namely, it just stop updating the real screen.
     *
     *  At the initial state of a player, updating the real screen must be disabled.
     */
    JKSint32 ( *stopUpdate )( JKSint32 id );
} JKT_Media_VideoControl;

/**
 * A structure defining frame positioning control functions.
 *
 * When the device manufacturer implement this structure, 
 * #JKT_Media_VideoControl must be implemented as well. 
 */
typedef struct {
    /**
     * Gets current frame number.
     * @param id
     *  The player ID.
     * @return
     *   Return the current frame number.
     */
    JKSint32 ( *getCurFrame )( JKSint32 id );

    /**
     * Gets the media time that corresponds to a frame.
     * @param id
     *  The player ID.
     * @param frame
     *  The frame number.
     * @param pUsecH
     *  A pointer to the buffer for storing the high 32 bit of the media time
     * (in microseconds) corresponding to the frame.
     * @param pUsecL
     *  A pointer to the buffer for storing the low 32 bit of the media time 
     * (in microseconds) corresponding to the frame.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *convFrameToTime )( JKSint32 id, JKSint32 frame, JKUint32* pUsecH, JKUint32* pUsecL );

    /**
     * Gets the frame number that corresponds to a media time.
     * @param id
     *  The player ID.
     * @param usecH
     *  The high 32 bit of the media time in microseconds.
     * @param usecL
     *  The low 32 bit of the media time in microseconds.
     * @param pFrame
     *  A pointer to the buffer for storing the frame number that corresponds 
     *  to designated media time.
     *  If there is no frame that has exact same  media time, returns a frame 
     *  number that corresponds to the nearest past of the designated media time.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; 
     *   if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *convTimeToFrame )( JKSint32 id, JKUint32 usecH, JKUint32 usecL, JKSint32* pFrame );
} JKT_Media_FrameControl;


/**
 * A structure difining media optional control functions.
 *
 * The functions for optional feature are defined in each 
 * function structure dedicated to a feature. 
 * To implement an optional feature, device manufacturer has 
 * to implement the structures and set their pointers to 
 * corresponding member in JKT_MediaOption, and set the pointer 
 * to the JKT_MediaOption to the <i>pOptionFuncs</i> member of the 
 * JKT_MediaControl structure. 
 *
 * To support playback rate control, for an example, 
 * the native system sets a pointer to a JKT_Media_SpeedControl 
 * to the <i>pSpeedFuncs</i> member of JKT_MediaOption.
 *
 * Device manufacturer can set JK_NULL to some JKT_MediaOption 
 * members that correspond to unsupported features. 
 *
 * The <i>pExtFuncs</i> member of JKT_MediaOption is reserved for future use;
 * set JK_NULL to this member.
 */
typedef struct {
    /**
     * A pointer to the function structure defining tempo control functions.
     */
    JKT_Media_TempoControl const* pTempoFuncs;
    /**
     * A pointer to the function structure defining playback rate control functions.
     */
    JKT_Media_SpeedControl const* pSpeedFuncs;
    /**
     * A pointer to the function structure defining stop control functions.
     */
    JKT_Media_StopControl const* pStopFuncs;
    /**
     * A pointer to the function structure defining playback pitch control functions.
     */
    JKT_Media_PitchControl const* pPitchFuncs;
    /**
     * A pointer to the function structure defining metadata control functions.
     */
    JKT_Media_MetaDataControl const* pMetaDataFuncs;
    /**
     * A pointer to the function structure defining MIDI device control functions.
     */
    JKT_Media_MIDIControl const* pMIDIFuncs;
    /**
     * A pointer to the function structure defining common playback clock control functions.
     */
    JKT_Media_SyncControl const* pSyncFuncs;
    /**
     * A pointer to the function structure defining media image display control functions.
     */
    JKT_Media_VideoControl const* pVideoFuncs;
    /**
     * A pointer to the function structure defining frame positioning control functions.
     */
    JKT_Media_FrameControl const* pFrameFuncs;
    /**
     * A pointer to the function structure defining snapshot control functions.
     */
    void const* pSnapshotFuncs;
    /**
     * A pointer to the function structure defining input device control functions.
     */
    void const* pInputDeviceFuncs;
    /**
     * A pointer to the function structure defining recording control functions.
     */
    void const* pRecordFuncs;
    /**
     * Reserved for future use.
     */
     void const* pExtFuncs;
} JKT_MediaOption;

#ifdef __cplusplus
}
#endif

#endif /* !__JKMEDIAOPTION_H__ */

/** @} end of group */
