#if !defined(ID3_H)
#define ID3_H

#include "ms_io.h"
#include "apps_audio.h"
#include "esl_aud_itf.h"

#define ID3_IMG_LIMIT_SIZE       128*1024

typedef enum _ID3Version_
{
    ID3_V1 = 1,
    ID3_V2 = 2
}ID3Version;

typedef enum _ID3Contentype_
{
    TITLE_SERIAL,
    ARTIST_SERIAL,
    ALBUM_SERIAL,
    YEAR_SERIAL,
    COMMENT_SERIAL,
    TRACK_SERIAL,
    PICTURE_SERIAL, 
    TOTALNUM_SERIAL
    //type_genre
 } ID3ContentType;

/*
labeled encoding byte order byte sequence
ID3_ISO_8859_1 only english, digit, number
UTF-16LE little-endian 34 6C, 7A 00, 34 D8 1E DD
UTF-16BE big-endian 6C 34, 00 7A, D8 34 DD 1E
UTF-16 little-endian, with BOM FF FE, 34 6C, 7A 00, 34 D8 1E DD
UTF-16 big-endian, with BOM FE FF, 6C 34, 00 7A, D8 34 DD 1E
*/
typedef enum _EncodingScheme_
{
    ID3_ISO_8859_1=ESL_AUD_ISO_8859_1,/*Latin-1*/
    ID3_UTF16=ESL_AUD_UTF16,/*begin with "FF FE"*/
    ID3_UTF16BE=ESL_AUD_UTF16BE,/*no "FF FE", BE=big Endian*/
    ID3_UTF8=ESL_AUD_UTF8 /*one kind of Unicode, available length*/
} EncodingScheme;


typedef enum _ID3Error_
{
    ID3_ERR_OK=1,
    ID3_ERR_NO_TAG=-1
} ID3Error;

typedef struct _ID3V1TagContent_
{
    char title[31];
    char artist[31];
    char album[31];
    char comment[31];
    char year[5];
    unsigned char genre;
    unsigned char track;
}ID3V1TagContent;


/* ID3 string */
typedef struct _ID3String_
{
  EncodingScheme encoding;
  char *string;
} ID3String;


s32 ID3GetTagLen
(
	const ms_fnchar *fileName,
    u32     *u32TagLen
);

/* Get the contents of ID3 tag from one mp3 file */
int ID3GetTagContent
(
    const ms_fnchar *fileName,
    u8	*pBuf,
    esl_AudID3V1Info_t *id3Info
);


extern unsigned short ID3mdx_byteused ;
extern unsigned short ID3mdx_maxbyte ;
extern unsigned char *ID3mdx_ptr;
#endif /* ID3_H */
