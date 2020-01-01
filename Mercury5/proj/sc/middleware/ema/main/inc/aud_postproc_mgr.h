///////////////////////////////////////////////////////////////////////////////
// aud_postproc_mgr.h
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
//                              Files Include
//=============================================================================
#ifdef WIN32
#include <stdio.h>
#include <math.h>
#include <string.h>
#else
#include "vm_types.ht"
#include "vm_stdio.ho"
#endif

//=============================================================================
//                              Function Define
//=============================================================================
#define GET_AUDIO_CALBI_TABLE_MESSAGE
#define ENABLE_PRINT_CALBI_TABLE_MESSAGE

#ifdef ENABLE_PRINT_CALBI_TABLE_MESSAGE
#ifdef WIN32
#define PRINTF_CALBI_DATA printf
#else
#define PRINTF_CALBI_DATA(_format_, ...)
#endif
#else
#ifdef WIN32
#define PRINTF_CALBI_DATA
#else
#define PRINTF_CALBI_DATA(_format_, ...)
#endif
#endif

#ifdef WIN32
#define vm_memcpy memcpy
#endif

//=============================================================================
//                              Parameter Define
//=============================================================================

// EQ Band Limit

#define MIN_EQ_BAND_INDEX 0
#define MAX_EQ_BAND_INDEX 4
#define MAX_EQ_BAND_SIZE  ((MAX_EQ_BAND_INDEX - MIN_EQ_BAND_INDEX) + 1)

// EQ Gain Limit
#define MIN_GAIN_INDEX (-36)
#define MAX_GAIN_INDEX (36)

// Channel Limit
#define MAX_CHANNEL_SIZE (2)

// Comment size
#define SIZEOF_COMMENT       (sizeof(char)*20)
#define SIZEOF_ID            (sizeof(short))
#define SIZEOF_SIZE          (sizeof(int))
#define SIZEOF_NUM           (sizeof(short))

// Engine ID
#define ENGINE_ID           ((short)0xA001)

// IPs ID
#define SURROUND_ID         ((short)0x0101)
#define USERPEQ_ID          ((short)0x0201)
#define SPEAKERPEQ_ID       ((short)0x0301)
#define DRCLIMITER_ID       ((short)0x0401)


//========================================================
// [Surround data stracture]:
//   unsigned char bEn;
//
// [User PEQ data stracture]:
//   unsigned char  bEn;
//   int            s32GlbGainIdx;
//   int            s32GIdx[5];
//   int            s32FC[5];
//   int            s32QIdx[5];
//   unsigned char  bPass[5];
//
// [Speaker PEQ data stracture]:
//   unsigned char  bEn;
//   int            s32GlbGainIdx;
//   int            s32GIdx[5];
//   int            s32FC[5];
//   int            s32QIdx[5];
//   unsigned char  bPass[5];
//
// [DRC Limiter data stracture]:
//   unsigned char   bEn;
//   short           s16LimitValueIdx[2];
//   unsigned short  u16ATTimeMs_idx[2];
//   unsigned short  u16RTTimeMs_idx[2];
//   int             s32DPGAdB_Idx[2];
//========================================================

// Data size
#define SIZEOF_SURROUND_DATA   (sizeof(unsigned char))
#define SIZEOF_USERPEQ_DATA    (sizeof(unsigned char) + sizeof(int) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(unsigned char)*MAX_EQ_BAND_SIZE))
#define SIZEOF_SPEAKERPEQ_DATA (sizeof(unsigned char) + sizeof(int) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(int)*MAX_EQ_BAND_SIZE) + (sizeof(unsigned char)*MAX_EQ_BAND_SIZE))
#define SIZEOF_DRCLIMITER_DATA (sizeof(unsigned char) + (sizeof(short)*MAX_CHANNEL_SIZE) + (sizeof(unsigned short)*MAX_CHANNEL_SIZE) + (sizeof(unsigned short)*MAX_CHANNEL_SIZE) + (sizeof(int)*MAX_CHANNEL_SIZE))

//=============================================================================
//                              Global Variable
//=============================================================================
extern unsigned char Audio_PostProcessing_Calibration_Table[2048];

int Get_IP_Data_Strc(unsigned short u16TargetIPID , unsigned short u32TargetModeIdx , unsigned char * ps8CalibTab , unsigned char * ps8ModeData);
int Get_Engine_ID(unsigned char * ps8CalibTab , unsigned short *u16EngineID);
int Set_UserEQ_Gain(int s32BandIdx , int s32GainIdx , unsigned char * ps8ModeData);
int Get_UserEQ_Gain(int s32BandIdx , int * s32GainIdx , unsigned char * ps8ModeData);

