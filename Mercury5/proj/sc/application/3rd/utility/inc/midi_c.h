#ifndef __DELTA_MIDI_CONVERTER_HEADER__
#define __DELTA_MIDI_CONVERTER_HEADER__

#include "midic_types.h"

#define MIDI_HEADER_SIZE 14
#define MIDI_TRACK_HEADER_SIZE 8

#define MIDI_HEADER_TAG "MThd"
#define MIDI_TRACK_TAG  "MTrk"
typedef struct
{
  uint8_t *Buffer;  
  int32_t            Length; 
  int32_t            Index; 
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



// interface 
int32_t midic_Convert(int8_t *inBuffer,int32_t inBufferSize,int8_t *outBuffer,int32_t outBufferSize);
int32_t midic_GetTotalTime(int8_t *inBuffer,int32_t filesize);

#endif
