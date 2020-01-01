/// @ait_only
//==============================================================================
//
//  File        : mmpd_id3.h
//  Description : INCLUDE File for the Host ID3.
//  Author      : Rogers Chen/Alterman
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_id3.h
 *  @brief The header File for the Host ID3 functions
 *  @author Rogers Chen
 *  @version 1.0
 */

#ifndef _MMPD_ID3_H_
#define _MMPD_ID3_H_

#include "mmp_lib.h"
#include "mmpd_audio.h"
//#include "ait_utility.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define ID3_NONE_IN_AUDIO   0x0000
#define ID3_V1_IN_AUDIO     0x0001
#define ID3_V2_IN_AUDIO     0x0002  

#define TEXT_FRAME_MAX_LEN  256
#define	GNERE_FRAME_MAX_LEN	40
#define PLAY_CNT_MAX_LEN    8

extern  MMP_BYTE     m_bGenreStr[126][18];
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
//ID3v2 frames types
typedef enum _MMPD_ID3_META_TYPE
{
    MMPD_ID3_META_NONE           = 0x00000000,
    MMPD_ID3_META_TITLE          = 0x00000001,
    MMPD_ID3_META_ALBUM          = 0x00000002,
    MMPD_ID3_META_ARTIST         = 0x00000004,
    MMPD_ID3_META_COPYRIGHT      = 0x00000008,
    MMPD_ID3_META_AUTHOR         = 0x00000010,
    MMPD_ID3_META_DESCRIPTION    = 0x00000020,
    MMPD_ID3_META_GENRE          = 0x00000040,
    MMPD_ID3_META_YEAR           = 0x00000080,
    MMPD_ID3_META_TRACKNUM       = 0x00000100,
    MMPD_ID3_META_CLSF           = 0x00000200,
    MMPD_ID3_META_APIC           = 0x00000400,
    MMPD_ID3_META_RATING         = 0x00000800,
    MMPD_ID3_META_PCOUNT         = 0x00001000,
    MMPD_ID3_META_ALL			 = 0x00001FFF
} MMPD_ID3_META_TYPE;

//ID3v2 frames supported
typedef enum _MMPD_ID3_FRAME_ID
{
    MMPD_ID3_FRAME_APIC = 'A' << 24 | 'P' << 16 | 'I' << 8 | 'C',   //Attached picture
    MMPD_ID3_FRAME_POPM = 'P' << 24 | 'O' << 16 | 'P' << 8 | 'M',   //Popularimeter (rating/play count)
    MMPD_ID3_FRAME_TALB = 'T' << 24 | 'A' << 16 | 'L' << 8 | 'B',   //Album
    MMPD_ID3_FRAME_TCOM = 'T' << 24 | 'C' << 16 | 'O' << 8 | 'M',   //Composer
    MMPD_ID3_FRAME_TCON = 'T' << 24 | 'C' << 16 | 'O' << 8 | 'N',   //Content type (genre)
    MMPD_ID3_FRAME_TCOP = 'T' << 24 | 'C' << 16 | 'O' << 8 | 'P',   //Copyright
    MMPD_ID3_FRAME_TIT1 = 'T' << 24 | 'I' << 16 | 'T' << 8 | '1',   //Content group description
    MMPD_ID3_FRAME_TIT2 = 'T' << 24 | 'I' << 16 | 'T' << 8 | '2',   //Title/songname
    MMPD_ID3_FRAME_TPE1 = 'T' << 24 | 'P' << 16 | 'E' << 8 | '1',   //Lead performer (artist)
    MMPD_ID3_FRAME_TRCK = 'T' << 24 | 'R' << 16 | 'C' << 8 | 'K',   //Track number
    MMPD_ID3_FRAME_TYER = 'T' << 24 | 'Y' << 16 | 'E' << 8 | 'R',   //Year
    MMPD_ID3_FRAME_XHD3 = 'X' << 24 | 'H' << 16 | 'D' << 8 | '3',   //MP3HD info
    MMPD_ID3_FRAME_TDRC = 'T' << 24 | 'D' << 16 | 'R' << 8 | 'C',   //v2.4 Recording time (year)
    MMPD_ID3_FRAME_PIC  =  0  << 24 | 'P' << 16 | 'I' << 8 | 'C',   //v2.2 Attached picture
    MMPD_ID3_FRAME_POP  =  0  << 24 | 'P' << 16 | 'O' << 8 | 'P',   //v2.2 Popularimeter
    MMPD_ID3_FRAME_TAL  =  0  << 24 | 'T' << 16 | 'A' << 8 | 'L',   //v2.2 Album
    MMPD_ID3_FRAME_TCM  =  0  << 24 | 'T' << 16 | 'C' << 8 | 'M',   //v2.2 Composer
    MMPD_ID3_FRAME_TCO  =  0  << 24 | 'T' << 16 | 'C' << 8 | 'O',   //v2.2 Content type (genre)
    MMPD_ID3_FRAME_TCR  =  0  << 24 | 'T' << 16 | 'C' << 8 | 'R',   //v2.2 Copyright
    MMPD_ID3_FRAME_TT1  =  0  << 24 | 'T' << 16 | 'T' << 8 | '1',   //v2.2 Content group description
    MMPD_ID3_FRAME_TT2  =  0  << 24 | 'T' << 16 | 'T' << 8 | '2',   //v2.2 Title/songname
    MMPD_ID3_FRAME_TP1  =  0  << 24 | 'T' << 16 | 'P' << 8 | '1',   //v2.2 Lead performer (artist)
    MMPD_ID3_FRAME_TRK  =  0  << 24 | 'T' << 16 | 'R' << 8 | 'K',   //v2.2 Track number
    MMPD_ID3_FRAME_TYE  =  0  << 24 | 'T' << 16 | 'Y' << 8 | 'E'    //v2.2 Year
} MMPD_ID3_FRAME_ID;

//Frames that allow different types of text encoding contains a text
//encoding description byte.
typedef enum _MMPD_ID3_TEXT_ENC_MODE
{
    MMPD_ID3_TEXT_ISO_8859_1 = 0x00, //ISO-8859-1
    MMPD_ID3_TEXT_UCS_2      = 0x01, //UTF-16 with BOM
    MMPD_ID3_TEXT_UTF16_BE   = 0x02, //UTF-16 Big Endian without BOM
    MMPD_ID3_TEXT_UTF8       = 0x03, //UTF-8
    MMPD_ID3_TEXT_UTF16_LE   = 0x04, //UTF-16 Little Endian without BOM
    MMPD_ID3_TEXT_UNKNOWN    = 0xFF  //Unknown encoding
} MMPD_ID3_TEXT_ENC_MODE;

typedef struct _MMPD_ID3_V1_TAG {
    MMP_BYTE 	bTag[3];
    MMP_BYTE 	bTitle[30];
    MMP_BYTE 	bArtist[30];
    MMP_BYTE 	bAlbum[30];
    MMP_BYTE 	bYear[4];
    MMP_BYTE 	bComment[30];
    MMP_UBYTE 	ubGenre;
} MMPD_ID3_V1_TAG;

//Strings dependent on encoding is represented as <text string according to encoding>.
//If ISO-8859-1 is used first byte should be 0x00, if Unicode (UCS-2) is used it should be 0x01.
//[id3v2.4.0] UTF-16: 0x01; UTF-16BE: 0x02; UTF-8: 0x03
typedef struct _MMPD_ID3_V2_TAG {
    MMP_BYTE    bAlbum[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bComposer[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bCopyright[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bDescription[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bTitle[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bArtist[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bTrack[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bYear[TEXT_FRAME_MAX_LEN*2];
    MMP_BYTE    bGenre[GNERE_FRAME_MAX_LEN*2];
    MMP_UBYTE   ubPlayCnt[PLAY_CNT_MAX_LEN];
    MMP_UBYTE   *bApic;
    MMP_ULONG   ulApicSize;
    MMP_ULONG   ulPlayCntSize;
    MMP_ULONG   ulPaddingSize;
    MMP_UBYTE   ubRating;
    MMPD_ID3_TEXT_ENC_MODE  albumEncMode;
    MMPD_ID3_TEXT_ENC_MODE  composerEncMode;
    MMPD_ID3_TEXT_ENC_MODE  copyrightEncMode;
    MMPD_ID3_TEXT_ENC_MODE  descriptionEncMode;
    MMPD_ID3_TEXT_ENC_MODE  titleEncMode;
    MMPD_ID3_TEXT_ENC_MODE  artistEncMode;
    MMPD_ID3_TEXT_ENC_MODE  trackEncMode;
    MMPD_ID3_TEXT_ENC_MODE  yearEncMode;
    MMPD_ID3_TEXT_ENC_MODE  genreEncMode;
} MMPD_ID3_V2_TAG;

typedef struct _MMPD_ID3_INFO {
    MMP_USHORT          flag;
	MMP_USHORT          sub_version;
    MMPD_ID3_V1_TAG     id3v1Tag;
    MMPD_ID3_V2_TAG     id3v2Tag;
    MMPD_ID3_META_TYPE  metaType;
} MMPD_ID3_INFO;

typedef struct _MMPD_ID3_V2_TAG_HEADER {
    MMP_BYTE    header[3];
    MMP_BYTE    ver;
    MMP_BYTE    rev;
    MMP_BYTE    flag;
    MMP_BYTE    size[4];
} MMPD_ID3_V2_TAG_HEADER;

typedef struct _MMPD_ID3_V2_FRAME_HEADER {
    MMP_BYTE    frame_id[4];
    MMP_UBYTE   size[4];
    MMP_BYTE    flags[2];
} MMPD_ID3_V2_FRAME_HEADER;

typedef struct _MMPD_ID3_V2_2_FRAME_HEADER {
    MMP_BYTE    frame_id[3];
    MMP_UBYTE   size[3];
} MMPD_ID3_V2_2_FRAME_HEADER;
typedef MMP_ERR (MMPD_ID3_ReadFile_Func)(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize);
typedef MMPD_ID3_ReadFile_Func*  MMPD_ID3_ReadFile_FuncPtr;

typedef MMP_BOOL AllocZeroMemCBFunc(MMP_LONG size, void **ptr);

//==============================================================================
//
//                               FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath);
MMP_ERR	MMPD_ID3_SetParseCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize, MMP_ULONG ulMaxCacheSize);
//MMP_ERR MMPD_ID3_GetInfo(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFileID, MMPD_ID3_INFO *id3info, 
//                         MMP_ULONG ulSeekPos, AllocZeroMemCBFunc *CallBackFunc, MMPD_ID3_ReadFile_Func *ReadFileFunc);
MMP_ERR MMPD_ID3_EditTag(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMPD_ID3_FRAME_ID frameType,
                         MMP_UBYTE *payload, MMP_LONG payloadLen);
MMP_ERR MMPD_ID3_CheckFrameExist(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFrame,
                         MMPD_AUDIO_PLAY_DATAPATH ubPath, MMP_BOOL *bExist);
/// @}
#endif // _MMPD_ID3_H_
/// @end_ait_only

