#ifndef _MIDI_GETINF_H_
#define _MIDI_GETINF_H_

#include "vm_types.ht"
#include "ms_io.h"
#include <stdint.h>

#define RIFF_MIDI_HEADER_LENGTH 20
#define MIDI_HEADER_SIZE 14
#define MIDI_TRACK_HEADER_SIZE 8
#define midic_bswap32(x) ( (((x) & 0xff000000) >> 24) |(((x) & 0x00ff0000) >> 8) | (((x) & 0x0000ff00) << 8) | (((x) & 0x000000ff) << 24))
#define midic_bswap16(x) ( (((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))


typedef struct
{
  uint8_t *Buffer;
  int32_t            Length;
  int32_t            Index;
  MSFILE file; //ccc add
  uint32_t TrkOffset; //ccc add
  void *audplayer;
} MIDI_Memory2;

typedef struct  // move from midi_c.h
{
  int8_t Tag[4] ;        // always 'MThd'
  int32_t  HeaderSize;     // always 6 in big endian
  int16_t Format;        // 0,1,2 in big engian
  int16_t TrackNum;      // total tracks in big engian
  int16_t DeltaPerQuote; // the number of delta-time ticks per quarter note in big engian
} MIDI_HEADER2;

typedef struct
{
  int8_t Tag[4] ;        // always 'MTrk'
  int32_t  TrackSize;     // Track size in big endian
} MIDI_TRACK_HEADER2;

typedef struct
{
  MIDI_TRACK_HEADER2 Header ;
  MIDI_Memory2       Pool;
  int32_t               Delta_Count;
  uint8_t     LastEvent;
  uint8_t     OneLoopExecution;
  int32_t               EndOfTrack;    
} MIDI_TRACK2;



extern s32 retrieve_MIDI_info(void *aud_player, void *pInfo);


#endif
