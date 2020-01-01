// add from Sharebuffer.h
#ifdef  __AMR_REC__
#define AMR_REC_BUF_SIZE  8 * 1024
#define AMR_REC_BUF       U8 _AMRRECODER[AMR_REC_BUF_SIZE];
#define AMR_REC_SRAM_SIZE 22 * 1024
#define AMR_REC_SRAM      U8 _AMRRECODER[AMR_REC_SRAM_SIZE];
#else
#define AMR_REC_BUF
#define AMR_REC_SRAM
#endif  //__AMR_REC__
#define amrrecStackSize                 AMRREC_STACKSIZE    //extern U16 amrrecStackSize;



#ifndef AUD_STACK_DRAM
#ifdef NEW_AUDPLAYER
#define AUD_STACK_DRAM_SIZE 20 * 1024
#define AUD_STACK_DRAM      U8 _AUDPLAYER[AUD_STACK_DRAM_SIZE];
#define AUD_STACK_SRAM_SIZE 20 * 1024
#define AUD_STACK_SRAM      U8 _AUDPLAYER[AUD_STACK_SRAM_SIZE];
#else
#define AUD_STACK_SRAM
#define AUD_STACK_DRAM
#endif
#endif //

// add end from Sharebuffer.h


// add from Globalvar.h
#define REC_AMR_SIZE_THRESHOLD              1
// add from Globalvar.h end

// add from Utility.h
typedef enum
{
    _CREATE = 0,
    _DELETE = 1,
} FILE_CREATE;
//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    FILE_UNKNOWN = 0,
    FILE_MP3 = 1,
    FILE_3GP = 2,
    FILE_JPEG = 3,
    FILE_AMR = 4,
    FILE_AAC = 5,
    FILE_BMP = 6,
    FILE_GIF = 7,
    FILE_PNG = 8,
    PCM_STREAM = 9,
    FILE_MIDI = 11,
    FILE_264  = 12,
    FILE_263  = 13,
    FILE_FLV1 = 14,
    FILE_M4V  = 15,
    FILE_MP4  = 16,
    FILE_WAV  = 17,
    FILE_PCM  = 18,
    FILE_RM   = 19,
    FILE_RVC   = 20,
    FILE_QRCODE  = 21,
#if defined(MONTAGE_APP_MDTV)
    CMMB_STREAM = 22,
    FILE_MFS  = 24,
#endif
    FILE_AMRWB   = 25,
    FILE_WMA   = 26,
    FILE_COOK   = 27,
    FILE_FLV    = 28,
    FILE_APE = 29,
    FILE_IMAADPCM3BIT = 30,
    FILE_IMAADPCM4BIT = 31,
    FILE_MSADPCM4BIT  = 32,
} FILE_TYPE;
// add from Utility.h end


// add from encoder.c
#define AMR_MAGIC_NUMBER "#!AMR\n"

// add from encoder.c end
