/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMTone.h
 *  Tone Sequence Parser Library Service Functions
 */

/**
 * @addtogroup MediaControl_JBI_ToneSequence
 * @{
 */

#ifndef __AM_TONE_H__
#define __AM_TONE_H__

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 *  Rest.
 */
#define AMTONE_SILENCE -1

/**
 *  Succeeded in getting the next tone event.
 */
#define AMTONE_GOT_NEXT_EVENT 1

/**
 *  Reached the end of the sequence.
 */
#define AMTONE_END_OF_SEQUENCE 0

/**
 *  Failed to get the next tone event because of an invalid sequence.
 */
#define AMTONE_INVALID_SEQUENCE -1

/**
 * Tone event structure.
 */
typedef struct AmT_ToneEventData {
	/**
	 *  Note.
	 *  Values from 0 to 127 are note events; #AMTONE_SILENCE indicates a rest 
         *  event.
	 */
	JKSint8 note;

	/**
	 *  The duration of the tone designated in the note member. The unit is 
         *  the interrupt interval designated in the usec parameter with AmToneCreateSeqData().
	 */
	JKSint32 count;

	/**
	 *  Volume. Values from 0 to 100 are designated, with 0 meaning silence.
	 */
	JKUint8 volume;
} AmT_ToneEventData;


/**
 * Sequence data handle.
 */
typedef void *AmToneSeqHandle;


/**
 *  Determines whether data is a tone sequence or not.
 * @param pData
 *  Initial address of the data (byte array)
 * @param size
 *  The size (in bytes) of the array indicated by <i>pData</i>.
 * @return
 *  0 is returned if the data stored in the array indicated by <i>pData</i> is a tone sequence.
 *  If not, or if determination could not be made, a negative value is returned.
 *
 *  This function does not check a tone sequence for internal data consistency.
 *
 */
JKSint32 AmToneIsData( JKUint8 *pData, JKSint32 size );

/**
 *  Generates sequence information from a tone sequence.
 * @param pData
 *  The inital address of the tone sequence (byte array)
 * @param size
 *  The size (in bytes) of the byte array indicated by <i>pData</i>
 * @param usec
 *  Interrupt interval (in microseconds) of the time used for playback
 * @param alloc
 *  A pointer to the memory allocation function.
 *  It is used by JBlend to allocate memory for storing the tone sequence information. 
 * @param free
 *  A pointer to the memory free function.
 *  It is used  by JBlend to free the memory holding the tone sequence information. 
 * @return
 *  The sequence information handle is returned.<br>
 *  JK_NULL is returned if sequence information could not be generated.
 *
 *  This function performs a detailed check of the tone sequence for internal
 *  data consistency.
 *
 */
AmToneSeqHandle AmToneCreateSeqData( JKUint8 *pData, JKSint32 size, JKSint32 usec,
                                     void *( *alloc )( JKUint32 ),
                                     void ( *free )( void * ) );

/**
 *  Disposes of sequence information.
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @return
 *  #JKMEDIA_RESULT_OK is returned if the dispose operation succeeds, or  
 *  #JKMEDIA_RESULT_ERROR if it fails.
 */
JKSint32 AmToneDeleteSeqData( AmToneSeqHandle handle );

/**
 *  Gets the next tone event to be played.
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @param pTone
 *  A pointer to the buffer for receiving the next tone event 
 *  ( #AmT_ToneEventData structure) to be played
 * @return
 *  #AMTONE_GOT_NEXT_EVENT is returned if the tone event is acquired, 
 *  #AMTONE_END_OF_SEQUENCE if the end of the sequence information was reached, and 
 *  #AMTONE_INVALID_SEQUENCE if the operation fails.
 *
 */
JKSint32 AmToneGetNextToneEvent( AmToneSeqHandle handle, AmT_ToneEventData* pTone );

/**
 *  Initializes the play position in sequence information.
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @return
 *  #JKMEDIA_RESULT_OK is returned if initialization succeeds, or #JKMEDIA_RESULT_ERROR if 
 *  it fails.
 *
 * Calling #AmToneGetNextToneEvent() right after this function is called gets the initial 
 * tone event in the sequence.
 */
JKSint32 AmToneResetSeqData( AmToneSeqHandle handle );

/**
 *  Changes the play position in sequence information.
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @param usec
 *  Designate the play position as microseconds from the head of the data.
 * @return
 *  #JKMEDIA_RESULT_OK is returned if the function succeeds, or #JKMEDIA_RESULT_ERROR if 
 *  it fails.
 */
JKSint32 AmToneSeekSeqData( AmToneSeqHandle handle, JKSint32 usec );

/**
 *  Gets the tone sequence total playing time (in microseconds).
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @return
 *  Value of 0 or more: Play back duration (Succeeded) <br>
 *  #JKMEDIA_RESULT_ERROR: (Failed)
 *
 * The tone sequence total playing time is already definite at the time #AmToneCreateSeqData() is called to create the sequence information handle.
 */
JKSint32 AmToneGetTotalTime( AmToneSeqHandle handle );

/**
 *  Gets the tone sequence tempo.
 * @param handle
 *  The sequence information handle. Designate the value returned by AmToneCreateSeqData().
 * @return
 *  The tempo is returned as a positive value if obtained successfully. If not, 
 *  #JKMEDIA_RESULT_ERROR is returned.
 */
JKSint32 AmToneGetTempo( AmToneSeqHandle handle );

/**
 *   Gets the total number of tone events.
 * @param handle
 *   The sequence information handle. Designate the return value of 
 *    #AmToneCreateSeqData().
 * @return
 *   A value of 0 or more: The total number of tone events <br>
 *   #JKMEDIA_RESULT_ERROR: The function failed
 */
JKSint32 AmToneGetTotalTones( AmToneSeqHandle handle );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__AM_TONE_H__ */

/** @} end of group */
