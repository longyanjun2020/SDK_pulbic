#ifndef _FAITH_APPS_AUDIO_H_
#define _FAITH_APPS_AUDIO_H_

#include "vm_types.ht"
#include "ms_io.h"

#ifdef MIDI_PLAYER
#include "faithAPI.h"
#include "WPRM.h"
#endif

#define BIG3
#define ARM_SDRAM_ENABLE

//MIDI playback
#ifdef  MIDI_PLAYER
#define MIDI_TABLE_FROM_ROM

#define MIDI_WAVEBUFSIZE   107912
#define MIDI_WDATBUFSIZE   24*222 // sizeof(WPRM_WDAT) * 222
#define MIDI_WPRMBUFSIZE   40*493 // sizeof(WPRM) * 493
#define MIDI_WPRMPGMBUFSIZE  8*175 // sizeof(WPRM_PROGRAM)* 175
#define  MIDI_WPRMBANKBUFSIZE  516*2 //sizeof(WPRM_BANK)*2
#define MIDI_STACKBUFSIZE 17480 // 64 polyphony
#define MIDI_CONVBUFSIZE 4096
#define MIDI_STREAMBUFSIZE 30*1024 //max MIDI size in FLASH
#define MIDI_TABLEBUFSIZE 149364
#define MIDI_OUTBUFSIZE 4096
#define MIDI_CONVSTACKSIZE 4096
#define MIDI_TRACK_POOL_BUFEN 128
#define MIDI_TRACKPOOLBUFSIZE 40*MIDI_TRACK_POOL_BUFEN
#ifdef MIDI_TABLE_FROM_ROM
#define MIDITMPTABBUFSIZE 24*222+MIDI_WPRMBUFSIZE+MIDI_WPRMPGMBUFSIZE
#endif
#define midistreambuf       (MIDIPlayerDRAM_cached->_midistreambuf)
#define midistreamsizebuf   (MIDIPlayerDRAM_cached->_midistreamsizebuf)
#define midistackbuf        (MIDIPlayerDRAM_cached2->_midistackbuf)
#define midioutbuf          (MIDIPlayerDRAM_cached2->_midioutbuf)
#define midiiMelodyWork     (MIDIPlayerDRAM_cached->_midiiMelodyWork)
#define midiseqTrks         (MIDIPlayerDRAM_cached->_midiseqTrks)
#define midiwprmbankbuf     (MIDIPlayerDRAM_cached->_midiwprmbankbuf)
#define miditmptabbuf       (MIDIPlayerDRAM_cached->_miditmptabbuf)
#if 1
//#define miditablebuf        (MIDIPlayerDRAM_cached->_miditablebuf)
#else
#define midiwavebuf         (MIDIPlayerDRAM_cached->_midiwavebuf)
#define midiwdatbuf         (MIDIPlayerDRAM_cached->_midiwdatbuf)
#define midiwprmbuf         (MIDIPlayerDRAM_cached->_midiwprmbuf)
#define midiwprmpgmbuf      (MIDIPlayerDRAM_cached->_midiwprmpgmbuf)
#define midiprmwdatidx      (MIDIPlayerDRAM_cached->_midiprmwdatidx)
#define midiprmwdatoffset   (MIDIPlayerDRAM_cached->_midiprmwdatoffset)
#define midiwavoffset       (MIDIPlayerDRAM_cached->_midiwavoffset)
#define miditblTune         (MIDIPlayerDRAM_cached->_miditblTune)
#define miditblTvfFc        (MIDIPlayerDRAM_cached->_miditblTvfFc)
#define miditblTvfMq        (MIDIPlayerDRAM_cached->_miditblTvfMq)
#define miditblF2eg         (MIDIPlayerDRAM_cached->_miditblF2eg)
#define midiTimetbl         (MIDIPlayerDRAM_cached->_midiTimetbl)
#define midiLfotbl          (MIDIPlayerDRAM_cached->_midiLfotbl)
#define midiGaintbl         (MIDIPlayerDRAM_cached->_midiGaintbl)
#endif
#define miditrackpoolbuf    (MIDIPlayerDRAM_cached->_miditrackpoolbuf)
#define midigetinfobuf               (MIDIPaserDRAM_cached->_midigetinfobuf)
#if defined(ARM_SDRAM_ENABLE)
typedef struct midiplayer_sdram
{
     u8 _midistreambuf[MIDI_STREAMBUFSIZE];
     u8 _midistreamsizebuf[4];
//     u8 _midioutbuf[MIDI_OUTBUFSIZE];
     u8 _midiiMelodyWork[712];
     u8 _midiseqTrks[800];
     u8 _midiwprmbankbuf[MIDI_WPRMBANKBUFSIZE];
//     u8 _midistackbuf[MIDI_STACKBUFSIZE];
#ifndef MIDI_TABLE_FROM_ROM
     #if 1
     u8 _miditablebuf[MIDI_TABLEBUFSIZE];
     #else
     u8 _midiprmwdatidx[496];
     u8 _midiprmwdatoffset[176];
     u16 _midiwavoffset[224];
     u8 _midiwavebuf[MIDI_WAVEBUFSIZE];
     u8 _midiwdatbuf[MIDI_WDATBUFSIZE];
     u8 _midiwprmbuf[MIDI_WPRMBUFSIZE];
     u8 _midiwprmpgmbuf[MIDI_WPRMPGMBUFSIZE];
     u16 _miditblTune[1536];
     short _miditblTvfFc[16*97];
     short _miditblTvfMq[16*97];
     short _miditblF2eg[260];
     short _midiTimetbl[1024];
     short _midiLfotbl[768];
     short _midiGaintbl[256];
     #endif
#endif  // !MIDI_TABLE_FROM_ROM
     u8 _miditrackpoolbuf[MIDI_TRACKPOOLBUFSIZE];
#ifdef MIDI_TABLE_FROM_ROM
     u8 _miditmptabbuf[MIDITMPTABBUFSIZE];
#endif
} MIDIPLAYER_SDRAM;
typedef struct midiplayer_sdram2
{
     u8 _midioutbuf[MIDI_OUTBUFSIZE];
     u8 _midistackbuf[MIDI_STACKBUFSIZE];
} MIDIPLAYER_SDRAM2;

typedef struct
{
     u8 _midigetinfobuf[20*1024];
}MIDIPARSER_MEM_SDRAM;

#endif  // ARM_SDRAM_ENABLE
#endif  // MIDI_PLAYER


extern MIDIPLAYER_SDRAM *MIDIPlayerDRAM_cached;
extern MIDIPLAYER_SDRAM2 *MIDIPlayerDRAM_cached2;
extern MIDIPARSER_MEM_SDRAM *MIDIPaserDRAM_cached;
/* MIDI */
typedef s32 fntab_PlayMIDI(u8 getTimeFlag,  const ms_fnchar *filename, u8 shareMem);
typedef s32 fntabMIDIAPI_SynthInit( void (*ledCallback)(void*,int), void (*vibCallback)(void*,int), void (*lcdCallback)(void*,int), void *callbackParam );
typedef s32 fntabMIDIAPI_SeqSetFile( void* pImg, unsigned long nImgLength );
typedef s32 fntabMIDIAPI_SeqSeek( unsigned long timeMSEC );
typedef s32 fntabMIDIAPI_SeqPlay(void);
typedef s32 fntabMIDIAPI_Proc( s16 *pBuf );
typedef unsigned long fntabMIDIAPI_SeqGetPos(void);
typedef void fntabMIDIAPI_SynthExit(void);
typedef s32 fntabMIDI_GetTotalTime(MSFILE fmidi, s32 filesize, void *Inst);
typedef void fntabMIDI_CreateTask(void *task, void *pfunproc);
typedef s32 fntabMIDIPlayer_PauseOn(void);
typedef s32 fntabMIDIPlayer_PauseOff(void);
typedef s32 fntabMIDIPlayer_Stop(void);
typedef s32 fntabMIDIAPI_SeqSetFile_game( void* pImg, unsigned long nImgLength );
typedef s32 fntabMIDIAPI_Proc_game( s16 *pBuf );
typedef s32 fntab_PlayMIDI_game(u8 getTimeFlag, s8 *filename, u8 u8gametype);
typedef void fntab_MIDI_FlushDcache(void);



typedef struct MIDIPlayer_FuncTable
{
    fntab_PlayMIDI                  *PlayMIDI;
    fntabMIDIAPI_SynthInit          *MIDIAPI_SynthInit;
    fntabMIDIAPI_SeqSetFile         *MIDIAPI_SeqSetFile;
    fntabMIDIAPI_SeqSeek            *MIDIAPI_SeqSeek;
    fntabMIDIAPI_SeqPlay            *MIDIAPI_SeqPlay;
    fntabMIDIAPI_Proc               *MIDIAPI_Proc;
    fntabMIDIAPI_SeqGetPos          *MIDIAPI_SeqGetPos;
    fntabMIDIAPI_SynthExit          *MIDIAPI_SynthExit;
    fntabMIDI_GetTotalTime          *MIDI_GetTotalTime;
    fntabMIDI_CreateTask            *MIDI_CreateTask;
    fntabMIDIPlayer_PauseOn         *MIDIPlayer_PauseOn;
    fntabMIDIPlayer_PauseOff        *MIDIPlayer_PauseOff;
    fntabMIDIPlayer_Stop            *MIDIPlayer_Stop;
    fntabMIDIAPI_SeqSetFile_game    *MIDIAPI_SeqSetFile_game;
    fntabMIDIAPI_Proc_game          *MIDIAPI_Proc_game;
    fntab_PlayMIDI_game             *PlayMIDI_game;
    fntab_MIDI_FlushDcache          *MIDI_FlushDcache;
}MIDIPLAYER_FUNCTABLE;

extern s32  PlayMIDI(u8 getTimeFlag, const ms_fnchar *filename, u8 shareMem);
extern s32 PlayMIDI_game(u8 getTimeFlag, s8 *filename,u8 u8gametype);
extern s32 FaithAPI_SynthInit( void (*ledCallback)(void*,int), void (*vibCallback)(void*,int), void (*lcdCallback)(void*,int), void *callbackParam );
extern s32 FaithAPI_SeqSetFile( void* pImg, unsigned long nImgLength );
extern s32 FaithAPI_SeqSetFile_game( void* pImg, unsigned long nImgLength );
extern s32 FaithAPI_SeqSeek(unsigned long timeMSEC );
extern s32 FaithAPI_SeqPlay(void);
extern s32 FaithAPI_Proc(s16 *pBuf );
extern s32 FaithAPI_Proc_game(s16 *pBuf );
extern unsigned long FaithAPI_SeqGetPos(void);
extern void FaithAPI_SynthExit(void);
extern s32 midic_GetTotalTime_New(MSFILE fmidi,s32 filesize, void *Inst);
extern void MIDI_CreateTask(void *task, void *pfunproc);
extern s32 MIDIPlayer_PauseOn(void);
extern s32 MIDIPlayer_PauseOff(void);
extern s32 MIDIPlayer_Stop(void);
extern void MIDI_FlushDcache(void);
extern void MIDI_PlayNotSupport(void);
extern s32 MIDI_NotSupport_Stop(void);

#ifdef  CYGCFG_COMMON_PACKAGE
#define MIDIPLAY_FP                 ((MIDIPLAYER_FUNCTABLE *)&__audio_functab_start)
#else
extern MIDIPLAYER_FUNCTABLE         MIDIPlayerFuncTable;
#define MIDIPLAY_FP                 (&MIDIPlayerFuncTable)
#endif

#define fnGetInfoMIDIGetTotalTime       AUDGETINFO_FP->midic_GetTotalTime


#define fnPlayMIDI                  MIDIPLAY_FP->PlayMIDI
#define fnMIDIFaithAPI_SynthInit    MIDIPLAY_FP->MIDIAPI_SynthInit
#define fnMIDIFaithAPI_SeqSetFile   MIDIPLAY_FP->MIDIAPI_SeqSetFile
#define fnMIDIFaithAPI_SeqSeek      MIDIPLAY_FP->MIDIAPI_SeqSeek
#define fnMIDIFaithAPI_SeqPlay      MIDIPLAY_FP->MIDIAPI_SeqPlay
#define fnMIDIFaithAPI_Proc         MIDIPLAY_FP->MIDIAPI_Proc
#define fnMIDIFaithAPI_SeqGetPos    MIDIPLAY_FP->MIDIAPI_SeqGetPos
#define fnMIDIFaithAPI_SynthExit    MIDIPLAY_FP->MIDIAPI_SynthExit
#define fnMIDI_GetTotalTime         MIDIPLAY_FP->MIDI_GetTotalTime
#define fnMIDI_CreateTask           MIDIPLAY_FP->MIDI_CreateTask
#define fnMIDI_PauseOn              MIDIPLAY_FP->MIDIPlayer_PauseOn
#define fnMIDI_PauseOff             MIDIPLAY_FP->MIDIPlayer_PauseOff
#define fnMIDI_Stop                 MIDIPLAY_FP->MIDIPlayer_Stop
#define fnMIDIFaithAPI_SeqSetFile_game  MIDIPLAY_FP->MIDIAPI_SeqSetFile_game
#define fnMIDIFaithAPI_Proc_game    MIDIPLAY_FP->MIDIAPI_Proc_game
#define fnPlayMIDI_game             MIDIPLAY_FP->PlayMIDI_game
#define fnMIDI_FlushDcache          MIDIPLAY_FP->MIDI_FlushDcache




#endif
