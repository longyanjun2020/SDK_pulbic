#ifndef __JAP_AUDIO_DEFINE_H__
#define __JAP_AUDIO_DEFINE_H__
/**
*
* @file    jap_audio.h
* @brief
*
* @author  Jim.Lee
* @version $Id: jap_media.h 37667 2009-08-12 09:50:30Z kris.wang $
*
*/

/* Aplix header - begin */
#include "JkMediaControl.h"
#include "AMMemory.h"
#include "AMMediaControl.h"
#include "AMTone.h"
/* Aplix header - end */

/* Mstar header - begin */
#include "jap_head.h"
#include "ven_codec.h"
/* Mstar header - end */

#define JAP_MEDIA_ACTTYPE_PLAY 		0x01
#define JAP_MEDIA_ACTTYPE_STOP		0x02

#define JAP_MEDIA_TYPE_WAV  		0x100
#define JAP_MEDIA_TYPE_MID			0x101
#define JAP_MEDIA_TYPE_MIDITONE		0x102
#define JAP_MEDIA_TYPE_MIDISHORT	0x103
#define JAP_MEDIA_TYPE_MIDILONG		0x104
#define JAP_MEDIA_TYPE_MIDIVOLUME	0x105
#define JAP_MEDIA_TYPE_MIDIPROG		0x106

#define MaxTotalChannelNum 16
#define Volume_Up           -1
#define Volume_Down         -2

#define Temp_Audio_Folder             L"/CARD/.system/java_audio"
#define MEDIATEMPFile_SEPARATOR_STR	   "/CARD/.system/java_audio/"
#define MEDIASTREAMFile_SEPARATOR_STR  JAP_PUBLIC_ROOT
#if defined(__DUAL_CARD__)
#define MEDIASTREAMFile_SEPARATOR_STR_CARD2  JAP_PUBLIC_ROOT_C2
#endif

#if defined(__ONBOARD_USER_STORAGE_MMI__)

#if defined(JAP_SUPPORT_DUAL_STORAGE_NAND)
#define MEDIASTREAMFile_SEPARATOR_STR_PHONE  JAP_PUBLIC_NAND_ROOT
#else 
#define MEDIASTREAMFile_SEPARATOR_STR_PHONE  JAP_PUBLIC_NOR_ROOT
#endif

#else
#define MEDIASTREAMFile_SEPARATOR_STR_PHONE  "/unknowndevice/"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
*	MIDI driver related structure
*	It's used while playing midi tone and sending midi event
*
**/
typedef JKUint32 Midi_Type_t;
typedef struct
{
	JKUint32 note;
	JKUint32 duration;
	JKUint32 volume;

} codec_midi_tone_t;

typedef struct
{
	JKUint32 channel;
	JKUint32 volume;

} codec_midi_chVolume_t;

typedef struct
{
	JKUint32 channel;
	JKUint32 bank;
	JKUint32 program;

} codec_midi_program_t;

typedef struct
{
	JKUint32 type;
	JKUint32 param1;
	JKUint32 param2;

} codec_midi_shortEvent_t;

typedef struct
{
	JKUint8* pLongEvent;	
	JKUint32 length;

} codec_midi_longEvent_t;

/* MIDI driver player instance */
typedef struct{
    JKSint32 channelVolume[MaxTotalChannelNum];
    JKUint8 masterVolume_level;
    JKSint32 masterVolume_value;
} MIDIInstance_t;

typedef struct{
	Midi_Type_t midiType;
	union
	{
		codec_midi_tone_t        midiTone;
		codec_midi_chVolume_t    midiChVolume;
		codec_midi_program_t     midiProgram;
        codec_midi_shortEvent_t  midiShortEvent;
		codec_midi_longEvent_t   midiLongEvent;
	} param;
}codec_play_midi_req_t;

/* MIDI player instance */
typedef struct{
    JKUint8* pData;
    JKUint32 length;
    JKSint32 loop;
    JKSint32 durationH;
    JKSint32 durationL;
    JKUint8 masterVolume_level;
    JKSint32 masterVolume_value;	
    JKSint32 time;
    u16*     midi_filename;
    MIDIInstance_t  midi_drv;	
    ven_codec_mediaFileInfo_t mediaInfo;
    
    u16*    midi_filenameAddr; //Used to record the memory address which allocate by midiControl.c
}MIDIPlayer_t;


#ifdef JAP_AMR_SUPPORT

/* AMR player instance */
typedef struct{
    JKUint8* pData;
    JKUint32 length;
    JKSint32 loop;
    JKSint32 durationH;
    JKSint32 durationL;
    JKUint8 masterVolume_level;
    JKSint32 masterVolume_value;	
    JKSint32 time;
    u16*     amr_filename;
    //MIDIInstance_t  midi_drv;	
    ven_codec_mediaFileInfo_t mediaInfo;
    
    u16*    amr_filenameAddr; //Used to record the memory address which allocate by midiControl.c
}AMRPlayer_t;
#endif


/* WAV player instance */
typedef struct  {
    JKUint8* pData;
    JKUint32 length;
    JKSint32 loop;
    JKSint32 durationH;
    JKSint32 durationL;
    JKUint8 masterVolume_level;
    JKSint32 masterVolume_value;	
    JKSint32 time;
    u16*     wav_filename;
    ven_codec_mediaFileInfo_t mediaInfo;

    u16*    wav_filenameAddr; //Used to record the memory address which allocate by midiControl.c
} WAVPlayer_t;

/* Tone Player instance */
typedef struct {
    u16 timerID;
    JKUint8 *pData;
    JKSint32 length;
    JKSint32 volume;
    JKSint32 usec;
    AmT_ToneEventData   lastnote;
    AmToneSeqHandle handle;
    JKSint32 loop_count;
} tonePlayer_t;

/* MP3 player instance */
typedef struct  {
    JKUint8* pData;
    JKUint32 length;
    JKSint32 loop;
    JKSint32 durationH;
    JKSint32 durationL;
    JKUint8 masterVolume_level;
    JKSint32 masterVolume_value;	
    JKSint32 time;
    u16*     mp3_filename;
    ven_codec_mediaFileInfo_t mediaInfo;

    u16*     mp3_filenameAddr;
} MP3Player_t;

/*Common player for all kind of type*/
typedef struct tPlayer {
	void* pNext;
	JKSint32 id;
	JKSint32 status;
	JKSint32 mediatype;
    bool isfileStreamPB;
	union
	{
		MIDIPlayer_t	midiPlayer;
		WAVPlayer_t  wavPlayer;
		MIDIInstance_t midiDriverPlayer;
		tonePlayer_t tonePlyaer;
		MP3Player_t mp3Player;

#ifdef JAP_AMR_SUPPORT
        AMRPlayer_t amrPlayer;
#endif
        
	}playerType;
} Player;

/**
 *  jap_ams_OpenMediaHandle
 *
 *  @brief  Create media handle
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_ams_OpenMediaHandle(void);

/**
 *  jap_ams_GetMediaHandle
 *
 *  @brief  get media handle
 *
 *  @retval Media handle value
 *          
 */
int jap_ams_CloseMediaHandle(void);

/**
 *  jap_ams_CloseMediaHandle
 *
 *  @brief  Release media handle
 *
 *  @retval 1 if success
 *          0 if failed
 */
int jap_ams_GetMediaHandle(void);

/**
 *   jap_media_insertPlayer
 *
 *  @brief  Create player instance.
 *
 *  @retval JKMEDIA_RESULT_OK if success
 *          JKMEDIA_RESULT_ERROR if failed
 **/
JKSint32 jap_media_insertPlayer(Player* pTempPlayer);

 /**
 *   jap_media_destroyPlayer
 *
 *  @brief  Destroy player instance.
 *
 *  @retval JKMEDIA_RESULT_OK if success
 *          JKMEDIA_RESULT_ERROR if failed
 **/
JKSint32 jap_media_destroyPlayer(Player* p);

/**
 *   jap_media_getPlayerHeader
 *
 *  @brief  Get player header of the list.
 *
 *  @retval player instance if success
 *          JK_NULL if failed
 **/
Player* jap_media_getPlayerHeader(void);

/**
 *   jap_media_getPlayer
 *
 *  @brief  Get player instance coresppondent to given ID.
 *
 *  @retval player instance if success
 *          JK_NULL if failed
 **/
Player* jap_media_getPlayer(JKSint32 id );

/**
 *   jap_media_getPlayerID
 *
 *  @brief  Get player ID.
 *
 *  @retval player id if success
 *          JKMEDIA_RESULT_ERROR if failed
 **/
JKSint32 jap_media_getPlayerID(void );

/**
 *   _setPlayerStatus2Ready
 *
 *  @brief  Set all players to READY status
 *
 *  @retval void
 *
 **/
static void _setPlayerStatus2Ready(void);

/**
 *   jap_media_stopAllAudio
 *
 *  @brief  Stop all audio playing in system
 *
 *  @param  stopPlayer     [in] need to stop player
 *
 *  @retval void
 *
 **/
JKSint32 jap_media_stopAllAudio(bool stopPlayer);

/**
 *   jap_media_playAudioPath
 *
 *  @brief  Play audio, it supports both file path mode and source buffer mode.
 *  @param  path                 [in]media data path used to play
 *  @param  pathLength       [in]media data path length
 *  @param  volume              [in]Volume level
 *  @param  loop                 [in]loop playing or not
 *  @param  position            [in]start playing position
 *  @param  id                     [in] Player ID if using Async method or -1 using Sync method
 *  @retval void
 *
 **/
JKSint32 jap_media_playAudioPath(JKUint16* path, JKUint16 pathLength, JKSint32 position, ven_codec_mediaVolume_t volume, bool loop, JKSint32 id);

/**
 *   jap_media_playAudioRaw
 *
 *  @brief  Play audio, it supports both file path mode and source buffer mode.
 *  @param  mediaFormat                 [in]media type
 *  @param  buffer       			    	  [in]media data
 *  @param  dataLen              		  [in]data lengthl
 *  @param  volume                          [in]Volume level
 *  @param  loop                              [in]loop playing or not
 *  @param  id                                 [in] Player ID if using Async method or -1 using Sync method
 *  @retval void
 *
 **/
JKSint32 jap_media_playAudioRaw(ven_codec_mediaFormat_t mediaFormat, JKUint8* buffer, JKSint32 dataLen, ven_codec_mediaVolume_t volume, bool loop, JKSint32 id);

/**
 *   jap_media_playMidiComm
 *
 *  @brief  Play midi related type
 *  @param  pMidiReq             [in] codec_play_midi_req_t
 *  @retval void
 *
 **/
JKSint32 jap_media_playMidiComm(codec_play_midi_req_t* pMidiReq);

/**
*   Jap_media_getCurVolumeLevel
*
*  @brief  get current volume Level
*
*  @retval audio volume level [0-8]
*
**/
JKUint8 Jap_media_getCurVolumeLevel(void);

/**
*   Jap_media_getVolume
*
*  @brief  get current volume
*
*  @retval audio volume [0-127]
*
**/
JKSint32 Jap_media_getVolume(void);

/**
*   Jap_media_setVolume
*
*  @brief  set current volume of JAVA profile
*
*  @retval -1 fail; 0 success
*
**/
JKSint32 Jap_media_setVolume(JKSint32 vol);


#ifdef __cplusplus
}
#endif

#endif /* __JAP_AUDIO_DEFINE_H__ */

