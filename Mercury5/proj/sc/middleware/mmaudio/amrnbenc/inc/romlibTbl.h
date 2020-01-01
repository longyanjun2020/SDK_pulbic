
#ifndef ROM_LIBTBL_H
#define ROM_LIBTBL_H

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
//#include <pkgconf/app_shell.h>
//#include "audiodrv.h"
#if 0 //def  MP3_PLAYER
//#include <pkgconf/app_mp3player.h>
//#include "mp3decoder.h"
#endif
#ifdef  AMR_PLAYER
#include "amrdec_lib.h"
#endif
#ifdef  __AMR_REC__
#include "amrenc_lib.h"
#endif

#if 0

//===========================================================
//3D Surround related table
//===========================================================
typedef struct surroundLib_varStruct_t
{
    int     writeidx;
    int     readidx;
    int     mono_delay;
    int     stereo_delay;
} SURROUNDLIB_VARSTRUCT;

typedef int     fntabSurround_Dec(SURROUNDLIB_VARSTRUCT *, short *, int, bool *, int,
                                  U8 *, AudioSampleRate);

/* 3D surround library function table */
typedef struct surroundLib_functab_t
{
    fntabSurround_Dec           *Surround_Dec;
} SURROUNDLIB_FUNCTAB;

extern  SURROUNDLIB_VARSTRUCT   surroundLibVarStruct;
extern  SURROUNDLIB_FUNCTAB     const surroundLibFunctab, *surroundLibFunctabPtr;
extern  fntabSurround_Dec       fnSurround_Dec;

#define fpSurround_Dec          surroundLibFunctabPtr->Surround_Dec


//===========================================================
//MP3 decoder related table
//===========================================================
#if 0 //def  MP3_PLAYER
#ifndef NEW_AUDPLAYER
typedef int     fntabTag_parse(t_tag *, t_mad_stream const *);

#ifdef  ENABLE_LAYER_I_II_DECODE
typedef int ATTR_MIPS32 fntabMad_layer_I(t_mad_stream *, t_mad_frame *);
typedef int ATTR_MIPS32 fntabMad_layer_II(t_mad_stream *, t_mad_frame *);
#endif
typedef int     fntabMad_layer_III(t_mad_stream *, t_mad_frame *, void*, void *);


/* MP3 library function table */
typedef struct mp3Lib_functab_t
{
    fntabMad_bit_init           *Mad_bit_init;
    fntabMad_bit_length         *Mad_bit_length;
    fntabMad_bit_nextbyte       *Mad_bit_nextbyte;
    fntabMad_bit_skip           *Mad_bit_skip;
    fntabMad_bit_read           *Mad_bit_read;
#ifdef  ENABLE_LAYER_I_II_DECODE
    fntabMad_layer_I            *Mad_layer_I;
    fntabMad_layer_II           *Mad_layer_II;
#endif
    fntabMad_layer_III          *Mad_layer_III;
    fntabMad_stream_init        *Mad_stream_init;
    fntabMad_stream_finish      *Mad_stream_finish;
    fntabMad_stream_buffer      *Mad_stream_buffer;
    fntabMad_stream_sync        *Mad_stream_sync;
    fntabMad_synth_init         *Mad_synth_init;
    fntabMad_synth_frame        *Mad_synth_frame;
#ifdef  ENABLE_CRC_CHECK
    fntabMad_bit_crc            *Mad_bit_crc;
#endif
    fntabTag_parse              *Tag_parse;
} MP3LIB_FUNCTAB;


extern  MP3LIB_FUNCTAB          const mp3LibFunctab;


extern  fntabTag_parse          tag_parse;
#endif

#ifndef NEW_AUDPLAYER
#ifdef  ENABLE_LAYER_I_II_DECODE
extern  fntabMad_layer_I        mad_layer_I;
extern  fntabMad_layer_II       mad_layer_II;
#endif
extern  fntabMad_layer_III      mad_layer_III;

#define fpMad_bit_init          mp3LibFunctabPtr->Mad_bit_init
#define fpMad_bit_length        mp3LibFunctabPtr->Mad_bit_length
#define fpMad_bit_nextbyte      mp3LibFunctabPtr->Mad_bit_nextbyte
#define fpMad_bit_skip          mp3LibFunctabPtr->Mad_bit_skip
#define fpMad_bit_read          mp3LibFunctabPtr->Mad_bit_read
#ifdef  ENABLE_LAYER_I_II_DECODE
#define fpMad_layer_I           mp3LibFunctabPtr->Mad_layer_I
#define fpMad_layer_II          mp3LibFunctabPtr->Mad_layer_II
#endif
#define fpMad_layer_III         mp3LibFunctabPtr->Mad_layer_III
#define fpMad_stream_init       mp3LibFunctabPtr->Mad_stream_init
#define fpMad_stream_finish     mp3LibFunctabPtr->Mad_stream_finish
#define fpMad_stream_buffer     mp3LibFunctabPtr->Mad_stream_buffer
#define fpMad_stream_sync       mp3LibFunctabPtr->Mad_stream_sync
#define fpMad_synth_init        mp3LibFunctabPtr->Mad_synth_init
#define fpMad_synth_frame       mp3LibFunctabPtr->Mad_synth_frame
#ifdef  ENABLE_CRC_CHECK
#define fpMad_bit_crc           mp3LibFunctabPtr->Mad_bit_crc
#endif
#endif

#ifndef NEW_AUDPLAYER
#define fpTag_parse             mp3LibFunctabPtr->Tag_parse
#endif

#endif  // MP3_PLAYER
#endif

//===========================================================
//AMR decoder related table
//===========================================================

typedef struct amrLib_varStruct_t
{
    unsigned char   *AMRHeapBuf;
} AMRLIB_VARSTRUCT;



typedef void*       fntabAmrDecInit(AMRLIB_VARSTRUCT *);
#ifndef ETSI
typedef void        fntabAmrDecDecode(void *, unsigned char *, short *, int);
#else
typedef void        fntabAmrDecDecode(void *, short *, short *, int);
#endif

/* AMR decoder library function table */
typedef struct amrDecLib_functab_t{
    fntabAmrDecInit         *amrDecInit;
	fntabAmrDecDecode       *amrDecDecode;
} AMRDECLIB_FUNCTAB;

extern  AMRLIB_VARSTRUCT        amrLibVarStruct;
extern  AMRDECLIB_FUNCTAB       const amrDecLibFunctab, *amrDecLibFunctabPtr;
extern  fntabAmrDecInit         Decoder_Interface_init;
extern  fntabAmrDecDecode       Decoder_Interface_Decode;

#define fpAmrDecInit            amrDecLibFunctabPtr->amrDecInit
#define fpAmrDecDecode          amrDecLibFunctabPtr->amrDecDecode



//===========================================================
//AMR encoder related table
//===========================================================
#ifdef  __AMR_REC__
typedef int*        fntabAmrEncInit(AMRLIB_VARSTRUCT *, int);
#ifndef ETSI
typedef int         fntabAmrEncEncode(enc_interface_State *, enum Mode, short *, unsigned char *, int);
#else
typedef int         fntabAmrEncEncode(enc_interface_State *, enum Mode, short *, short *, int);
#endif

/* AMR encoder library function table */
typedef struct amrEncLib_functab_t{
    fntabAmrEncInit         *amrEncInit;
	fntabAmrEncEncode       *amrEncEncode;
} AMRENCLIB_FUNCTAB;

extern  AMRENCLIB_FUNCTAB       const amrEncLibFunctab, *amrEncLibFunctabPtr;
extern  fntabAmrEncInit         Encoder_Interface_init;
extern  fntabAmrEncEncode       Encoder_Interface_Encode;

#define fpAmrEncInit            amrEncLibFunctabPtr->amrEncInit
#define fpAmrEncEncode          amrEncLibFunctabPtr->amrEncEncode
#endif

#endif  // ROM_LIBTBL_H
