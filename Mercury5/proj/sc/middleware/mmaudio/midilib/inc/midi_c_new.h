#ifndef __MIDI_CONVERTER_HEADER__
#define __MIDI_CONVERTER_HEADER__

#include "midic_types_new.h"
#include "ms_io.h"

#define MIDI_HEADER_TAG "MThd"
#define MIDI_TRACK_TAG  "MTrk"

#if 0 // move to aud_getinfo.h
typedef struct
{
  uint8_t *Buffer;
  int32_t            Length;
  int32_t            Index;
  int32_t *file; //ccc add
  uint32_t TrkOffset; //ccc add
} MIDI_Memory;

typedef struct
{
  int8_t Tag[4] ;        // always 'MThd'
  int32_t  HeaderSize;     // always 6 in big endian
  int16_t Format;        // 0,1,2 in big engian
  int16_t TrackNum;      // total tracks in big engian
  int16_t DeltaPerQuote; // the number of delta-time ticks per quarter note in big engian
} MIDI_HEADER;

typedef struct
{
  int8_t Tag[4] ;        // always 'MTrk'
  int32_t  TrackSize;     // Track size in big endian
} MIDI_TRACK_HEADER;


typedef struct
{
  MIDI_TRACK_HEADER Header ;
  MIDI_Memory       Pool;
  int32_t               Delta_Count;
  uint8_t     LastEvent;
  uint8_t     OneLoopExecution;
  int32_t               EndOfTrack;
} MIDI_TRACK;
#endif

#include "stdint.h"

// interface
//int32_t midic_Convert(int8_t *inBuffer,int32_t inBufferSize,int8_t *outBuffer,int32_t outBufferSize);
//s32 midic_Convert(MSFILE fmidi,s32 filelength,s8 *outBuffer,s32 outBufferSize);
int32_t midic_Convert_M3(MSFILE fmidi,int32_t filelength,int8_t *outBuffer,int32_t outBufferSize);
//int32_t midic_GetTotalTime_New(int8_t *inBuffer,int32_t filesize);
//S32 midic_GetTotalTime_New(S32 *fmidi,S32 filesize);

#endif
