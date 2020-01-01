/// @ait_only
//==============================================================================
//
//  File        : mmpd_audioparser.c
//  Description : Get Audio media spec function
//  Author      : CZLee
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_audioparser.c
*  @brief The audio get media spec functions
*  @author CZLEE
*  @version 1.0
*/
//#include "ait_utility.h"
#include "mmpd_fs.h"
#include "mmpd_audioparser.h"
#include "mmpd_audio.h"
#if (OMA_DRM_EN == 1)
#include "mmpd_omadrm.h"
#endif
#include "mmpd_id3.h"

#if (AAC_HOST_PARSER_EN == 1)
#include "libfaad\aac_comm.h"
#include "libfaad\aac.h"
#endif

/** @addtogroup MMPD_AUDPSR
 *  @{
 */

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
static	MMP_ULONG	m_ulParserfileID;
static	MMP_ULONG	m_ulParserPreSeekPos;
static	MMP_ULONG	m_ulParserCacheAddr;
static	MMP_ULONG	m_ulParserCacheSize;
static	MMPD_AUDIO_PLAY_DATAPATH m_mediaPath;
static	MMP_ULONG64	m_ulMediaFileSize;
//++ Start of mp3 parser
/* map these to the corresponding 2-bit values in the frame header */
#if (MP3_HOST_PARSER_EN == 1)
static	MMPD_AUDPSR_MP3DECINFO m_mp3DecInfo;

static const MMP_ULONG m_ulSamplerateTab[3][3] = {
  {44100, 48000, 32000},		/* MPEG-1 */
  {22050, 24000, 16000},		/* MPEG-2 */
  {11025, 12000,  8000},		/* MPEG-2.5 */
};

static const MMP_USHORT m_usBitrateTab[3][3][15] = {
	{
		/* MPEG-1 */
		{  0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448}, /* Layer 1 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384}, /* Layer 2 */
		{  0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320}, /* Layer 3 */
	},
	{
		/* MPEG-2 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256}, /* Layer 1 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 2 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 3 */
	},
	{
		/* MPEG-2.5 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256}, /* Layer 1 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 2 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 3 */
	},
};
//patch to get: sample per-frame
static const MMP_USHORT m_usSamplesPerFrameTab[3][3] = {
	{384, 1152, 1152 }, /* MPEG1 */
	{384, 1152,  576 }, /* MPEG2 */
	{384, 1152,  576 }, /* MPEG2.5 */
};
static MMP_BOOL m_bMp3InitFlag;
static MMP_BOOL m_bSearchVBRHeader;
#endif
//-- End of mp3 parser

//++ Start of wma parser
#if (WMA_HOST_PARSER_EN == 1)
static MMP_ULONG m_ulWMAFilePos;
static MMP_UBYTE m_ubUtf8Buf[512];
static MMP_UBYTE m_ubUtf16Buf[256];


static const MMPD_AUDPSR_ASFGUID asf_guid_header =
{0x75B22630, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const MMPD_AUDPSR_ASFGUID asf_guid_data =
{0x75B22636, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const MMPD_AUDPSR_ASFGUID asf_guid_index =
{0x33000890, 0xE5B1, 0x11CF, {0x89, 0xF4, 0x00, 0xA0, 0xC9, 0x03, 0x49, 0xCB}};

/* header level object guids */

static const MMPD_AUDPSR_ASFGUID asf_guid_file_properties =
{0x8cabdca1, 0xa947, 0x11cf, {0x8E, 0xe4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65}};

static const MMPD_AUDPSR_ASFGUID asf_guid_stream_properties =
{0xB7DC0791, 0xA9B7, 0x11CF, {0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65}};

static const MMPD_AUDPSR_ASFGUID asf_guid_content_description =
{0x75B22633, 0x668E, 0x11CF, {0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C}};

static const MMPD_AUDPSR_ASFGUID asf_guid_extended_content_description =
{0xD2D0A440, 0xE307, 0x11D2, {0x97, 0xF0, 0x00, 0xA0, 0xC9, 0x5E, 0xA8, 0x50}};

static const MMPD_AUDPSR_ASFGUID asf_guid_content_encryption =
{0x2211b3fb, 0xbd23, 0x11d2, {0xb4, 0xb7, 0x00, 0xa0, 0xc9, 0x55, 0xfc, 0x6e}};

static const MMPD_AUDPSR_ASFGUID asf_guid_extended_content_encryption =
{0x298ae614, 0x2622, 0x4c17, {0xb9, 0x35, 0xda, 0xe0, 0x7e, 0xe9, 0x28, 0x9c}};

/* stream type guids */

static const MMPD_AUDPSR_ASFGUID asf_guid_stream_type_audio =
{0xF8699E40, 0x5B4D, 0x11CF, {0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B}};

//sam: add video guid
static const MMPD_AUDPSR_ASFGUID asf_guid_stream_type_video =
{0xBC19EFC0, 0x5B4D, 0x11CF, {0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B}};
#endif
//-- End of wma parser

//++ Start of aacplus parser
MMP_ULONG	m_ulAACPlusObjectType;
MMP_ULONG   m_ulAACPlusNotSupport;
#if (AAC_HOST_PARSER_EN == 1)
static  MMP_ULONG   m_ulAACPlusFileOffset;
static  MMP_ULONG	m_ulAACPlusTagSize;
static  MMPD_AUDPSR_AACPLUS_HEADER_TYPE	m_AACPlusHeaderType;

static 	MMP_LONG	m_lAACPlusADTSSampleRate[] = 
		{96000, 88200, 64000, 48000, 44100,32000,24000,22050,
			16000,12000,11025,8000, 7350,0,0,0};
#endif
//-- End of aacplus parser

//++ Start of wav parser
#define STR_RIFF            (0x46464952)
#define STR_WAVE            (0x45564157)
#define STR_fmt             (0x20746d66)
#define STR_data            (0x61746164)
#define UNCOMPRESSED_PCM    (0x01)
//-- End of wav parser
//++ Start of ogg parser
#if (OGG_HOST_PARSER_EN == 1)
static  MMP_ULONG   m_ulOGGFileOffset;
#endif
//-- End of ogg parser

//++ Start of ra parser
#if (RA_HOST_PARSER_EN == 1)
MMP_ULONG	m_ulRAFileOffset;
MMP_LONG    m_lRAWorkingBuffer[RADEC_PARSER_WORKING_BUF_SIZE >> 2];	
#endif
//-- End of ra parser

//++ Start of amr parser
#if (AMR_HOST_PARSER_EN == 1)
#define AMR_MAGIC_NUMBER "#!AMR\n"
#define MAX_SERIAL_SIZE 244    /* max. num. of serial bits                 */
#define MAX_PACKED_SIZE (MAX_SERIAL_SIZE / 8 + 2)
#define MAX_PARSE_FRAMR_COUNT   500    // parse 500 AMR frames to get average bit rate

const MMP_USHORT m_usAMRPackedSize[16] = {12, 13, 15, 17, 19, 20, 26, 31, 5, 0, 0, 0, 0, 0, 0, 0};
const MMP_ULONG m_ulAMRBitRateTable[8] = {4750, 5150, 5900, 6700, 7400, 7950, 10200, 12200};
#endif
//-- End of amr parser
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_SetMediaPath
//  Description :
//------------------------------------------------------------------------------
/** @brief Set audio parser storage path, card mode or memory mode

@param[in] mediapath Select the storage path
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath)
{
    m_mediaPath = mediapath;

    return  MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_SetCacheBuf
//  Description : 
//------------------------------------------------------------------------------
/** @brief Set the cache address and cache size for parsing media spec

@param[in] ulCacheAddr The address of cache dedicated to media spec parser
@param[in] ulCacheSize The size of cache (must be a multiple of 2)
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_SetCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize)
{
    if (ulCacheSize % 2) {
        PRINTF("Cache size shoule be a multiple of 2\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }

    m_ulParserCacheAddr = ulCacheAddr;
    m_ulParserCacheSize = ulCacheSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_ReloadCache
//  Description : 
//------------------------------------------------------------------------------
/** @brief Load data into cache if cache missed

@param[in] ulSeekpos Seek position to load data into cache (m_ulParserCacheSize aligned)
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDPSR_ReloadCache(MMP_ULONG ulSeekpos) 
{
    MMP_ULONG   readsize;
    MMP_ERR     ret = MMP_ERR_NONE;

    #if (OMA_DRM_EN == 1)
    MMP_ULONG   headerOff;    
    MMP_USHORT  drmEn;
    MMP_ULONG   DRMSeekPos;
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PARSER);
    if (drmEn) {
        MMPD_AUDIO_GetDRMOffset(&headerOff, MMPD_OMADRM_FOR_PARSER);   
        DRMSeekPos = ulSeekpos + headerOff;
    }
    #endif

    // fist-time seek, backward seek or forward seek
    if (m_ulParserPreSeekPos == 0xFFFFFFFF) {
        switch(m_mediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)DRMSeekPos - 0x10, MMPD_FS_SEEK_SET);
                if (ret)
                	return ret;
                ret = MMPC_FS_FileRead((void *)m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
	            ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)DRMSeekPos - 0x10, MMPD_FS_SEEK_SET);
                if (ret)
                	return ret;
                ret = MMPD_FS_FileRead(m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        }
    }
    else if (ulSeekpos < (m_ulParserPreSeekPos + m_ulParserCacheSize)) {
        switch(m_mediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)DRMSeekPos - 0x10, MMPD_FS_SEEK_SET);
                if (ret)
                	return ret;
                ret = MMPC_FS_FileRead((void *)m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)DRMSeekPos - 0x10, MMPD_FS_SEEK_SET);
                if (ret)
                	return ret;
                ret = MMPD_FS_FileRead(m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        }
    }
    else {
        switch(m_mediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)DRMSeekPos - m_ulParserPreSeekPos - m_ulParserCacheSize - headerOff - 0x10, MMPD_FS_SEEK_CUR);
                if (ret)
                	return ret;
                ret = MMPC_FS_FileRead((void *)m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos - m_ulParserPreSeekPos - m_ulParserCacheSize, MMPD_FS_SEEK_CUR);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulParserfileID, (MMP_LONG64)ulSeekpos - m_ulParserPreSeekPos - m_ulParserCacheSize, MMPD_FS_SEEK_CUR);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (drmEn) {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)DRMSeekPos - m_ulParserPreSeekPos - m_ulParserCacheSize - headerOff - 0x10, MMPD_FS_SEEK_CUR);
                if (ret)
                	return ret;
                ret = MMPD_FS_FileRead(m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, 0x10, &readsize);
                if (ret)
                	return ret;
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulParserCacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos - m_ulParserPreSeekPos - m_ulParserCacheSize, MMPD_FS_SEEK_CUR);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulParserfileID, (MMP_LONG64)ulSeekpos - m_ulParserPreSeekPos - m_ulParserCacheSize, MMPD_FS_SEEK_CUR);
            #endif
            break;
        }
    }
    if (ret)
    	return ret;

    switch(m_mediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileRead((void *)m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, m_ulParserCacheSize, &readsize);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileRead(m_ulParserfileID, (MMP_UBYTE *)m_ulParserCacheAddr, m_ulParserCacheSize, &readsize);
        break;
    }
    if ((ret != MMP_ERR_NONE) && (ret != MMP_FS_ERR_EOF)) //Antonio@20091202, do not handle end of file
    	return ret;

    #if (OMA_DRM_EN == 1)
    if (drmEn) {
        MMPD_AUDIO_DecryptBufByKey((MMP_UBYTE *)m_ulParserCacheAddr, m_ulParserCacheSize, MMPD_OMADRM_FOR_PARSER);
    }
    #endif
    m_ulParserPreSeekPos = ulSeekpos;

    return  ret;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ReadCache
//  Description : 
//=========================================================================
/** @brief Read data from cache

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDPSR_ReadCache(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_UBYTE *source;

    source = (MMP_UBYTE *)m_ulParserCacheAddr + (ulSeekpos & (m_ulParserCacheSize - 1));
    while (ulReadsize > 0) {
        *ubTarget++ = *source++;
        ulReadsize--;
    }
    
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ReadFile
//  Description : 
//=========================================================================
/** @brief Read Audio file with cache mechanism

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_ReadFile(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_ULONG   readed_size, canread_size, rem_size;
    MMP_ULONG   cur_seekpos;
    MMP_ERR     ret;

    cur_seekpos = ulSeekpos;
    readed_size = 0;
    rem_size    = ulReadsize;

    while (readed_size < ulReadsize) {
        if (((m_ulParserPreSeekPos) & ~(m_ulParserCacheSize - 1)) != (cur_seekpos & ~(m_ulParserCacheSize - 1))) {
            // cache miss
            ret = MMPD_AUDPSR_ReloadCache(cur_seekpos & ~(m_ulParserCacheSize - 1));
		    if (ret && (ret != MMP_FS_ERR_EOF))
    			return ret;
        }

        canread_size = m_ulParserCacheSize - (cur_seekpos & (m_ulParserCacheSize - 1));
        if (rem_size > canread_size) {
            MMPD_AUDPSR_ReadCache(ubTarget, cur_seekpos, canread_size);
            rem_size -= canread_size;
            readed_size += canread_size;
            cur_seekpos += canread_size;
            ubTarget += canread_size;
        }
        else {
            MMPD_AUDPSR_ReadCache(ubTarget, cur_seekpos, rem_size);
            readed_size += rem_size;
        }
    }

    return MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_InitMP3HeaderParseInfo
//  Description : 
//------------------------------------------------------------------------------
/** @brief Init Mp3 information structures.

@param[out] pWrite The write pointer
@param[out] pWriteHigh The write high pointer
@return Always return success
*/
MMP_ERR MMPD_AUDPSR_InitMP3HeaderParseInfo(MMP_AUDIO_MP3_INFO *mp3info)
{
#if (MP3_HOST_PARSER_EN == 1)
    MEMSET(mp3info, 0, sizeof(MMP_AUDIO_MP3_INFO));

    m_bMp3InitFlag = MMP_FALSE;
    m_bSearchVBRHeader = MMP_TRUE;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_FindMP3VBRHeader
//  Description : 
//------------------------------------------------------------------------------
/** @brief Host parser mp3 and check mp3 is VBR or not

@param[in] buf Mp3 buffer address
@param[in] nBytes MP3 buffer size
@param[in] nBytes MP3 buffer size
@retval 0 VBR is found -1 VBR not found
*/
MMP_LONG MMPD_AUDPSR_FindMP3VBRHeader(MMP_UBYTE *buf, MMP_LONG nBytes, MMP_LONG *total_frm)
{
#if (MP3_HOST_PARSER_EN == 1)
	MMP_ULONG i;

    if(m_bSearchVBRHeader == MMP_TRUE) {
		//find vbr hearder
		*total_frm = 0;

        if ( (nBytes - 1 - MP3PARSER_MIN_DATA_REQ) < 0 )
            return -1;
        
	    for (i = 0; i < nBytes - 1 - MP3PARSER_MIN_DATA_REQ; i++) {	
		    if (buf[i]==0x58 && buf[i+1]==0x69 && buf[i+2]==0x6E && buf[i+3]==0x67) {
			    *total_frm = (MMP_ULONG)buf[i+8] << 24;
			    *total_frm |= (MMP_ULONG)buf[i+9] << 16;
			    *total_frm |= (MMP_ULONG)buf[i+10] << 8;
			    *total_frm |= (MMP_ULONG)buf[i+11] ;
			    m_bSearchVBRHeader = MMP_FALSE;
                return 0;  //VBR header found 
		    }
			else if (buf[i]==0x56 && buf[i+1]==0x42 && buf[i+2]==0x52 && buf[i+3]==0x49) {
			    *total_frm = (MMP_ULONG)buf[i+14] << 24;
			    *total_frm |= (MMP_ULONG)buf[i+15] << 16;
			    *total_frm |= (MMP_ULONG)buf[i+16] << 8;
			    *total_frm |= (MMP_ULONG)buf[i+17] ;

                m_bSearchVBRHeader = MMP_FALSE;				
	            return 0;  //VBR header found 
			}			
	    }	
	}
    else {
        return 0;  //VBR header found before
    }

    *total_frm = 0;
#endif
	return -1;  //did not found VBR header
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_ParseMP3FrameHeader
//  Description : 
//------------------------------------------------------------------------------
/** @brief Host parser mp3 frame header and get mp3 information

@param[out] mp3Info Send mp3 information
@param[in] buf mp3 buffer address
@retval Audio parser header error status.
*/
MMP_LONG MMPD_AUDPSR_ParseMP3FrameHeader(MMP_AUDIO_MP3_INFO *mp3Info, MMP_UBYTE *buf, MMP_LONG *framesize)
{
#if (MP3_HOST_PARSER_EN == 1)
	MMP_LONG verIdx;
    MMPD_AUDPSR_MP3FRAMEHEADER tFHdr;
	MMPD_AUDPSR_MP3FRAMEHEADER *fh = &tFHdr;
    MMP_LONG frame_size;

	if ((buf[0] & SYNCWORDH) != SYNCWORDH || (buf[1] & SYNCWORDL) != SYNCWORDL)
		return -1;

	/* read header fields - use bitmasks instead of GetBits() for speed, since format never varies */
	verIdx  =         (buf[1] >> 3) & 0x03;
    if(verIdx == 1)  return -1;    
	fh->ver =        (MMPD_AUDPSR_MP3MPEGVERSION)( verIdx == 0 ? MPEG25 : ((verIdx & 0x01) ? MPEG1 : MPEG2) );
	fh->ubLayer = 4 - ((buf[1] >> 1) & 0x03);     /* easy mapping of index to layer number, 4 = error */
//	fh->ubCRC =   1 - ((buf[1] >> 0) & 0x01);
	fh->ubBrIdx =      (buf[2] >> 4) & 0x0f;
	fh->ubSrIdx =      (buf[2] >> 2) & 0x03;
	fh->ubPaddingBit = (buf[2] >> 1) & 0x01;
	fh->ubPrivateBit = (buf[2] >> 0) & 0x01;
	fh->stereomode =   (MMPD_AUDPSR_MP3STEREOMODE)((buf[3] >> 6) & 0x03);      /* maps to correct enum (see definition) */    
	fh->ubModeExt =    (buf[3] >> 4) & 0x03;
//	fh->ubCopyFlag =   (buf[3] >> 3) & 0x01;
//	fh->ubOrigFlag =   (buf[3] >> 2) & 0x01;
//	fh->ubEmphasis =   (buf[3] >> 0) & 0x03;

	if (fh->ubSrIdx == 3 || fh->ubLayer == 4 || fh->ubBrIdx == 15)
		return -1;

    if(fh->ubLayer != 3) // Patch from AT team Sam@20090224
        return -1;
    
	if (fh->stereomode != Joint)		/* just to be safe (dequant, stproc check fh->ubModeExt) */
		fh->ubModeExt = 0;

    if (m_bMp3InitFlag == MMP_TRUE) {
	    if(mp3Info->usChans != (fh->stereomode == Mono ? 1 : 2))
            return -1;
	    if(mp3Info->usSampleRate != m_ulSamplerateTab[fh->ver][fh->ubSrIdx])
            return -1;
	    if(mp3Info->usLayer != fh->ubLayer)
            return -1;
	    if(mp3Info->usVersion != fh->ver)
            return -1;
//        if(m_mp3DecInfo.ulNextSyncWordFileOffset > m_mp3DecInfo.ulCurrentReSyncFileOffset)
//            return -1;
    }
    else {
        mp3Info->usChans = (fh->stereomode == Mono ? 1 : 2);
        mp3Info->usSampleRate = m_ulSamplerateTab[fh->ver][fh->ubSrIdx];
        mp3Info->usLayer = fh->ubLayer;
        mp3Info->usVersion = fh->ver;
        m_bMp3InitFlag = MMP_TRUE;    
        m_mp3DecInfo.ulSamplePerFrame = ((MMP_ULONG)m_usSamplesPerFrameTab[fh->ver][fh->ubLayer - 1]);
    }

	if (fh->ubBrIdx) {
		mp3Info->ulBitRate = ((MMP_ULONG)m_usBitrateTab[fh->ver][fh->ubLayer - 1][fh->ubBrIdx]) * 1000;
	}

    {
        MMP_ULONG frame_samples = m_mp3DecInfo.ulSamplePerFrame;
        /* Calculate number of bytes, calculation depends on layer */
        if (fh->ubLayer == 1) {
            frame_size = (12 * mp3Info->ulBitRate / mp3Info->usSampleRate
                                + fh->ubPaddingBit) * 4;
        }
        else {
            frame_size = frame_samples * mp3Info->ulBitRate / 8 / mp3Info->usSampleRate + 
                            fh->ubPaddingBit;
        }
        *framesize = frame_size;
//        m_mp3DecInfo.ulNextSyncWordFileOffset = m_mp3DecInfo.ulCurrentReSyncFileOffset + frame_size;
    }

	return 4;
#else
    return -1;
#endif
}
#if (WMA_HOST_PARSER_EN == 1)
//=========================================================================
//  Function    : MMPD_AUDPSR_ReadWMAFile
//  Description : 
//=========================================================================
/** @brief Read data to ubBuf

@param[in] ulSize Size to read
@param[out] ubBuf Buffer which stores the read data
@retval ulSize Success. -1 read file failed
*/
static MMP_LONG MMPD_AUDPSR_ReadWMAFile(MMP_UBYTE* ubBuf, MMP_ULONG ulSize)
{
    MMP_LONG ret;
    
   // cnt = fread(buf, 1, size, (FILE *)fd);
   
    ret = MMPD_AUDPSR_ReadFile(ubBuf, m_ulWMAFilePos, ulSize);
    if(ret == MMP_ERR_NONE){
        m_ulWMAFilePos += ulSize;
        return ulSize;
    }
    return -1;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_SeekWMAFile
//  Description : 
//=========================================================================
/** @brief Seek file position

@param[in] lOffset offset of file position
@param[in] lOrigin original position of file pointer
@retval 0 Success. -1 seek error
*/
static MMP_LONG MMPD_AUDPSR_SeekWMAFile(MMP_LONG lOffset, MMP_LONG lOrigin)
{
    m_ulWMAFilePos = lOrigin;
    m_ulWMAFilePos += lOffset;
    
    if(m_ulWMAFilePos < m_ulMediaFileSize) {
        return 0;
    }
    
    return -1; // error
}

//=========================================================================
//  Function    : MMPD_AUDPSR_IsGuidMatch
//  Description : 
//=========================================================================
/** @brief Compare GUID is matched or not

@retval 1 Matched. 0 Not matched.
*/
static MMP_LONG MMPD_AUDPSR_IsGuidMatch(const MMPD_AUDPSR_ASFGUID *guid1, const MMPD_AUDPSR_ASFGUID *guid2)
{
    int i;
    if((guid1->ulv1 != guid2->ulv1) || (guid1->usv2 != guid2->usv2) || (guid1->usv3 != guid2->usv3))
    {
        return 0;
    }
    for(i = 0; i < 8; i++)
    {
        if(guid1->ubv4[i]!= guid2->ubv4[i])
            return 0;
    }
    return 1;

}

//=========================================================================
//  Function    : MMPD_AUDPSR_ReadWMAGuid
//  Description : 
//=========================================================================
/** @brief Read the 16 byte GUID from a file

@param[out] guid GUID buffer which stores the read data
@retval -1 read GUID failed
*/
static MMP_LONG MMPD_AUDPSR_ReadWMAGuid(MMPD_AUDPSR_ASFGUID* guid)
{
    MMP_LONG lCnt;
    lCnt = MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&guid->ulv1, 4);
    lCnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&guid->usv2, 2);
    lCnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&guid->usv3, 2);
    lCnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)(guid->ubv4), 8);
    if(lCnt == WP_GIUD_SZ)
        return WP_GIUD_SZ;
    else
        return -1;
    
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ReadWMAObjectHeader
//  Description : 
//=========================================================================
/** @brief Read WMA object header from a file.

@param[out] obj object buffer which stores the read object header data.
@retval -1 read failed.
*/
static MMP_LONG MMPD_AUDPSR_ReadWMAObjectHeader(MMPD_AUDPSR_ASFOBJECT *obj)
{
    MMP_LONG lCnt;
    lCnt = MMPD_AUDPSR_ReadWMAGuid(&obj->guid);
    lCnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)(&obj->ullSize), 8);
    obj->ullDataLen = 0;
    
    if(lCnt == WP_OBJHDR_SZ)
        return WP_OBJHDR_SZ;
    else
        return -1;
    
}

//=========================================================================
//  Function    : MMPD_AUDPSR_EncodeUtf8
//  Description : 
//=========================================================================
/** @brief Encode a UCS value as UTF-8 and return a pointer after this UTF-8 char.

@param[in] ulUcs A value would be encoded.
@param[out] ubUtf8 A pointer points UTF-8 encoded value
@retval ubUtf8 Success
*/
static MMP_UBYTE* MMPD_AUDPSR_EncodeUtf8(MMP_ULONG ulUcs, MMP_UBYTE *ubUtf8)
{
    MMP_LONG lTail = 0;

    const MMP_UBYTE ubUtf8Comp[6] =
    {
        0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
    };

#define MASK   (0xC0) /* 11000000 */
#define COMP   (0x80) /* 10x      */    

    if (ulUcs > 0x7F)
        while (ulUcs >> (5*lTail + 6))
            lTail++;

    *ubUtf8++ = (MMP_UBYTE)((ulUcs >> (6*lTail)) | ubUtf8Comp[lTail]);
    while (lTail--)
        *ubUtf8++ = (MMP_UBYTE)(((ulUcs >> (6*lTail)) & (MASK ^ 0xFF)) | COMP);

#undef MASK
#undef COMP

    return ubUtf8;
}


//=========================================================================
//  Function    : MMPD_AUDPSR_DecodeUtf16LE
//  Description : 
//=========================================================================
/** @brief Decode a LE utf16 string from a disk buffer into a fixed-sized
           utf8 buffer.

@param[in] usUtf16Bytes Length of UTF-16 buffer.
@param[out] ubUtf8 UTF-8 value.
@retval 0 Success.
*/
static MMP_LONG MMPD_AUDPSR_DecodeUtf16LE(MMP_USHORT usUtf16Bytes,
                                          MMP_UBYTE  **ubUtf8,
                                          MMP_LONG*  lUtf8Bytes
                                          )
{
    MMP_ULONG ulUcs;
    MMP_LONG n;
    MMP_UBYTE* ubUtf16 = m_ubUtf16Buf;
    MMP_UBYTE* ubNewUtf8;

    n = MMPD_AUDPSR_ReadWMAFile(m_ubUtf16Buf, WP_MIN(sizeof(m_ubUtf16Buf), usUtf16Bytes));
    if( n < 0 )
        return -1;
        
    usUtf16Bytes -= n;

    while (n > 0) {
        /* Check for a surrogate pair */
        if (ubUtf16[1] >= 0xD8 && ubUtf16[1] < 0xE0) {
            if (n < 4) {
                /* Run out of utf16 bytes, read some more */
                m_ubUtf16Buf[0] = ubUtf16[0];
                m_ubUtf16Buf[1] = ubUtf16[1];

                n = MMPD_AUDPSR_ReadWMAFile((m_ubUtf16Buf + 2), WP_MIN(sizeof(m_ubUtf16Buf)-2, usUtf16Bytes));
                if( n < 0 )
                    return -1;
                ubUtf16 = m_ubUtf16Buf;
                usUtf16Bytes -= n;
                n += 2;
            }

            if (n < 4) {
                /* Truncated utf16 string, abort */
                break;
            }
            ulUcs = 0x10000 + ((ubUtf16[0] << 10) | ((ubUtf16[1] - 0xD8) << 18)
                             | ubUtf16[2] | ((ubUtf16[3] - 0xDC) << 8));
            ubUtf16 += 4;
            n -= 4;
        } else {
            ulUcs = (ubUtf16[0] | (ubUtf16[1] << 8));
            ubUtf16 += 2;
            n -= 2;
        }

        if (*lUtf8Bytes > 6) {
            ubNewUtf8 = MMPD_AUDPSR_EncodeUtf8(ulUcs, *ubUtf8);
            *lUtf8Bytes -= (ubNewUtf8 - *ubUtf8);
            *ubUtf8 += (ubNewUtf8 - *ubUtf8);
        }

        /* We have run out of utf16 bytes, read more if available */
        if ((n == 0) && (usUtf16Bytes > 0)) {
            n = MMPD_AUDPSR_ReadWMAFile((m_ubUtf16Buf), WP_MIN(sizeof(m_ubUtf16Buf), usUtf16Bytes));
            if( n < 0 )
                return -1;
            ubUtf16 = m_ubUtf16Buf;
            usUtf16Bytes -= n;
        }
    }

    *ubUtf8[0] = 0;
    --*lUtf8Bytes;

    if (usUtf16Bytes > 0) {
        /* Skip any remaining bytes */
        if(MMPD_AUDPSR_SeekWMAFile(usUtf16Bytes, m_ulWMAFilePos) < 0)
            return -2;
        
    }

    return 0;
}
//=========================================================================
//  Function    : MMPD_AUDPSR_ParseWMAHeader
//  Description : 
//=========================================================================
/** @brief Host audio parse WMA information

@param[out] wfx Get WMA file media spec information
@retval 0 Success.
*/
static MMP_LONG MMPD_AUDPSR_ParseWMAHeader(MMP_AUDIO_WMA_INFO* wmainfo, MMP_LONG *lAudioStream)
{
    MMPD_AUDPSR_ASFOBJECT current;
    MMPD_AUDPSR_ASFOBJECT header;
    MMP_ULONG64 ullDataLen;
    MMP_LONG 	i;
    MMP_LONG 	lFileProp = 0;
    MMP_ULONG64 ullPlayDuration = 0;
    MMP_USHORT  flags;
    MMP_ULONG   ulSubObjects = 0;
    MMP_LONG 	WMAProPar_IsVBRflag = 0;

    MMP_USHORT  CodecID = 0;       //see above codec ID definitions
    //MMP_USHORT  BitsPerSample = 0;
    MMP_USHORT  DRMInfo;
    MMP_USHORT  AVInfo = 0;
	MMP_ULONG   AvgBitRate = 0;
	MMP_UBYTE   ubData[6];

    /* Clean up tag buffers */
    MEMSET(m_ubUtf8Buf, 0, sizeof(m_ubUtf8Buf));
    MEMSET(m_ubUtf16Buf, 0, sizeof(m_ubUtf16Buf));

    *lAudioStream = -1;

    if(MMPD_AUDPSR_ReadWMAObjectHeader((MMPD_AUDPSR_ASFOBJECT *) &header) < 0)
        return ASF_ERROR_EOF;

    if (header.ullSize < 30) {
        /* invalid size for header object */
        return ASF_ERROR_OBJECT_SIZE;
    }

    if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ulSubObjects, 4) < 0)
        return ASF_ERROR_EOF;

    /* Two reserved bytes - do we need to read them? */
    if(MMPD_AUDPSR_SeekWMAFile(2, m_ulWMAFilePos)<0)
        return ASF_ERROR_SEEK;

    if (ulSubObjects > 0) {
        header.ullDataLen = header.ullSize - 30;

        /* TODO: Check that we have datalen bytes left in the file */
        ullDataLen = header.ullDataLen;

        for (i = 0; i<(MMP_LONG)ulSubObjects; i++) {
            if (ullDataLen < 24) {
                PRINTF("not enough data for reading object\n");
                break;
            }

            if(MMPD_AUDPSR_ReadWMAObjectHeader(&current) < 0)
                return ASF_ERROR_EOF;

            if (current.ullSize > ullDataLen || current.ullSize < 24) {
                break;
            }

            if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_file_properties)) {
				MMP_LONG cnt;
				MMP_ULONG64 tmp64;
				MMP_ULONG64 pre_roll;

				if (current.ullSize < 104)
					return ASF_ERROR_OBJECT_SIZE;

				if (lFileProp) {
					/* multiple file properties objects not allowed */
					return ASF_ERROR_INVALID_OBJECT;
				}

				lFileProp = 1;
				/* All we want is the play duration - uint64_t at offset 40 */
				if(MMPD_AUDPSR_SeekWMAFile(40, m_ulWMAFilePos) < 0) /* mmsid(16)+TotalSz(8)+CreatTime(8)+Pkts(8) */
					return ASF_ERROR_SEEK;
                    
				cnt  = MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ullPlayDuration, 8);
				cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp64, 8); //send duration
				cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&pre_roll, 8);

				if(cnt != (8*3))
					return ASF_ERROR_EOF;

				ullPlayDuration /= 10000;  //ms
				ullPlayDuration -= pre_roll;

				wmainfo->ulTotalTime = (MMP_ULONG)ullPlayDuration; //ms

				/* Read the packet size - uint32_t at offset 68 */                
				cnt  = MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp64, 4); //flags
				cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp64, 4); //min pkt sz
				cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp64/*(char *)&wfx->packet_size*/, 4); //max pkt sz
				cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&wmainfo->ulBitRate, 4); //bps
                    
				if(cnt != (4*4))
					return ASF_ERROR_EOF;

				/* Skip bytes remaining in object */
				if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24/*guid+size*/ - 80), m_ulWMAFilePos) < 0)
					return ASF_ERROR_SEEK;
	            } 
	            else if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_stream_properties)) {
                    MMPD_AUDPSR_ASFGUID guid;
                    MMP_ULONG ulPropDataLen;

                    if (current.ullSize < 78)
                        return ASF_ERROR_OBJECT_SIZE;

                    if((MMPD_AUDPSR_ReadWMAGuid(&guid)) < 0)
                        return ASF_ERROR_EOF;

                    if(MMPD_AUDPSR_SeekWMAFile(24, m_ulWMAFilePos) < 0)
                        return ASF_ERROR_SEEK;

                    if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ulPropDataLen,4) < 0)
                        return ASF_ERROR_EOF;
                    
                    if(MMPD_AUDPSR_SeekWMAFile(4, m_ulWMAFilePos) < 0)
                        return ASF_ERROR_SEEK;

                    if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&flags, 2) < 0)
                        return ASF_ERROR_EOF;

                    if (!MMPD_AUDPSR_IsGuidMatch(&guid, &asf_guid_stream_type_audio)) {
                        if (MMPD_AUDPSR_IsGuidMatch(&guid, &asf_guid_stream_type_video)) {
                            AVInfo |= 0x02;     //sam: has video stream
                        }

                        if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 50), m_ulWMAFilePos) < 0)
                            return ASF_ERROR_SEEK;

                    } else if (*lAudioStream == -1) {
                        AVInfo |= 0x01;     //sam: has Audio stream
                        if(MMPD_AUDPSR_SeekWMAFile(4, m_ulWMAFilePos) < 0)
							return ASF_ERROR_SEEK;

                        if (ulPropDataLen < 18) {
                            return ASF_ERROR_INVALID_LENGTH;
                        }
                        /* Parse & check */
                        {
                            MMP_LONG cnt;
                            MMP_LONG tmp32;
                          
                            cnt  = MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&CodecID, 2);
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&wmainfo->usChans, 2);
                            #if 1 //Alterman@20100329: to avoid overflow
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&wmainfo->ulSampleRate, 4);
                            #else
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&wmainfo->usSampleRate, 2);

                            MMPD_AUDPSR_SeekWMAFile(2, m_ulWMAFilePos);
                            cnt += 2;
                            #endif
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&AvgBitRate, 4);  //sam: equal to Audio bitrate if input is a Aud+Vid file.
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp32 /*&wfx->blockalign*/, 2);
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&wmainfo->usBitsPerSample, 2);
                            cnt += MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp32 /*&wfx->datalen*/, 2);
                            
                            if(cnt != (2+2+4+4+2+2+2))
                                return ASF_ERROR_EOF;

                            AvgBitRate *= 8;                            
                        }

                        /* Round bitrate to the nearest kbit */

                        if (CodecID == ASF_CODEC_ID_WMAV1) {
                            wmainfo->usVersion = 1;
                            if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)(ubData), 4) < 0)
                                return ASF_ERROR_EOF;
                            if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 72 - 4), m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                            *lAudioStream = flags & 0x7f;
                            
                        } else if (CodecID == ASF_CODEC_ID_WMAV2) {
                            wmainfo->usVersion = 2;                        
                            if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)(ubData), 6) < 0)
                                return ASF_ERROR_EOF;
                            if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 72 - 6), m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                            *lAudioStream = flags & 0x7f;
                            
                        } else if (CodecID == ASF_CODEC_ID_WMAV3) {
                            wmainfo->usVersion = 3; //WMAPro
                            if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 72), m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                            *lAudioStream = flags & 0x7f;
                            
                        } else {
                            wmainfo->usVersion = 0;
                            PRINTF("Unsupported WMA codec\n");
                            if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 72), m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                        }

                    }
            } else if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_content_description)) {
                /* set flag */            
                wmainfo->usTagInfo = 1;
                if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24), m_ulWMAFilePos)<0) //skip
                    return ASF_ERROR_SEEK;
            } else if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_extended_content_description)) {
                    MMP_USHORT count;
                    MMP_LONG i;
                    MMP_LONG bytesleft = (int)(current.ullSize - 24);

                    if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&count, 2) < 0)
                        return ASF_ERROR_EOF;
                    
                    bytesleft -= 2;

                    for (i=0; i < count; i++) {
                        MMP_USHORT length, type;
                        MMP_UBYTE* utf8 = m_ubUtf8Buf;
                        MMP_LONG utf8length = sizeof(m_ubUtf8Buf);

                        if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&length, 2) < 0)
                            return ASF_ERROR_EOF;
                        if(MMPD_AUDPSR_DecodeUtf16LE(length, &utf8, &utf8length) < 0)
                            return ASF_ERROR_EOF;
                            
                        bytesleft -= 2 + length;

                        if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&type, 2) < 0)
                            return ASF_ERROR_EOF;
                        if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&length, 2) < 0)
                            return ASF_ERROR_EOF;

                        /* check VBR flag */
                        //if(!strcmp("IsVBR",utf8buf)) {
                        if(STRCMP("IsVBR",(char *)m_ubUtf8Buf) == 0) {
                            MMP_ULONG tmp32;
                            if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&tmp32, 4)<0)
                                return ASF_ERROR_EOF;
                            if(tmp32 != 0) {
                                WMAProPar_IsVBRflag = 2; //WMAProPar_IsVBRflag != 0  => has VBR flag
                                wmainfo->usVbrInfo = 2;   //VBR flag set
                            }
                            else {
                                WMAProPar_IsVBRflag = 1; //WMAProPar_IsVBRflag != 0  => has VBR flag
                                wmainfo->usVbrInfo = 0;   //VBR flag not set
                            }
                            if(MMPD_AUDPSR_SeekWMAFile(length-4, m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                        } else {
                            if(MMPD_AUDPSR_SeekWMAFile(length, m_ulWMAFilePos)<0)
                                return ASF_ERROR_SEEK;
                        }
                        bytesleft -= 4 + length;
                    }

                    if(MMPD_AUDPSR_SeekWMAFile(bytesleft, m_ulWMAFilePos) < 0)
                        return ASF_ERROR_SEEK;
                    
            } else if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_content_encryption)
                || MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_extended_content_encryption)) {

                MMP_ULONG ulHasEncryptedData;

                if(MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ulHasEncryptedData, 4) < 0)
                    return ASF_ERROR_EOF;

                if(ulHasEncryptedData)
                    DRMInfo = 1;
                
                if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24 - 4), m_ulWMAFilePos) < 0)
                    return ASF_ERROR_SEEK;
            } else {
                if(MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24), m_ulWMAFilePos) < 0)
                    return ASF_ERROR_SEEK;
            }

            ullDataLen -= current.ullSize;
        }

        if (i != (MMP_LONG)ulSubObjects || ullDataLen != 0) {
            return ASF_ERROR_INVALID_VALUE;
        }
    }
    
    if(WMAProPar_IsVBRflag == 0) {//sam: if not by metadata => by calculation
        if((WP_ABS((MMP_LONG)AvgBitRate - (MMP_LONG)wmainfo->ulBitRate) > 1500) && 
            ((AVInfo & 0x02) == 0))
            wmainfo->usVbrInfo = 1;  //sam: if there is any video stream, always force to CBR if VBR flag is not presented.
        else
            wmainfo->usVbrInfo = 0;
    }
    
    wmainfo->ulBitRate = AvgBitRate;

    return 0;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ParseWMAContentObj
//  Description : 
//=========================================================================
/** @brief Host audio parse WMA content description object

@param[in] ullSize Object size
@param[out] meta Get WMA file meta data in content description object
@retval 0 Success.
*/
static MMP_LONG MMPD_AUDPSR_ParseWMAContentObj(MMP_ULONG64 ullObjSize, MMPD_ID3_INFO *meta)
{
    MMP_USHORT  usTitleLen = 0;
    MMP_USHORT  usAuthorLen = 0;
    MMP_USHORT  usCopyrightLen = 0;
    MMP_USHORT  usDescriptionLen = 0; 
    MMP_USHORT  usRatingLen = 0;
    MMP_ULONG   ulReadLen = 0;

    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&usTitleLen, 2) < 0)
        return ASF_ERROR_EOF;
    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&usAuthorLen, 2) < 0)
        return ASF_ERROR_EOF;
    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&usCopyrightLen, 2) < 0)
        return ASF_ERROR_EOF;
    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&usDescriptionLen, 2) < 0)
        return ASF_ERROR_EOF;
    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&usRatingLen, 2) < 0)
        return ASF_ERROR_EOF;
    PRINTF("title %d, author %d copyright %d description %d rating %d\r\n",
        usTitleLen, usAuthorLen, usCopyrightLen, usDescriptionLen, usRatingLen);

    /* Get title info */
    if (usTitleLen && (meta->metaType & MMPD_ID3_META_TITLE)) {
        if ((usTitleLen + 2) < sizeof(meta->id3v2Tag.bTitle))
            ulReadLen = usTitleLen;
        else
            ulReadLen = sizeof(meta->id3v2Tag.bTitle) - 2; //for null-terminator
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&meta->id3v2Tag.bTitle, ulReadLen) < 0)
            return ASF_ERROR_EOF;
        meta->id3v2Tag.bTitle[ulReadLen] = meta->id3v2Tag.bTitle[ulReadLen + 1] = 0; //null terminator
        meta->id3v2Tag.titleEncMode = MMPD_ID3_TEXT_UTF16_BE;

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(usTitleLen - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
    }
    /* Get author info */
    if (usAuthorLen && (meta->metaType & MMPD_ID3_META_AUTHOR)) {
        if ((usAuthorLen + 2) < sizeof(meta->id3v2Tag.bArtist))
            ulReadLen = usAuthorLen;
        else
            ulReadLen = sizeof(meta->id3v2Tag.bArtist) - 2; //for null-terminator
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&meta->id3v2Tag.bArtist, ulReadLen) < 0)
            return ASF_ERROR_EOF;
        meta->id3v2Tag.bArtist[ulReadLen] = meta->id3v2Tag.bArtist[ulReadLen + 1] = 0; //null terminator
        meta->id3v2Tag.artistEncMode = MMPD_ID3_TEXT_UTF16_BE;

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(usAuthorLen - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
    }
    /* Get copyright info */
    if (usCopyrightLen && (meta->metaType & MMPD_ID3_META_COPYRIGHT)) {
        if ((usCopyrightLen + 2) < sizeof(meta->id3v2Tag.bCopyright))
            ulReadLen = usCopyrightLen;
        else
            ulReadLen = sizeof(meta->id3v2Tag.bCopyright) - 2; //for null-terminator
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&meta->id3v2Tag.bCopyright, ulReadLen) < 0)
            return ASF_ERROR_EOF;
        meta->id3v2Tag.bCopyright[ulReadLen] = meta->id3v2Tag.bCopyright[ulReadLen + 1] = 0; //null terminator
        meta->id3v2Tag.copyrightEncMode = MMPD_ID3_TEXT_UTF16_BE;

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(usCopyrightLen - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
    }
    /* Get description info */
    if (usDescriptionLen && (meta->metaType & MMPD_ID3_META_DESCRIPTION)) {
        if ((usDescriptionLen + 2) < sizeof(meta->id3v2Tag.bDescription))
            ulReadLen = usDescriptionLen;
        else
            ulReadLen = sizeof(meta->id3v2Tag.bDescription) - 2; //for null-terminator
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&meta->id3v2Tag.bDescription, ulReadLen) < 0)
            return ASF_ERROR_EOF;
        meta->id3v2Tag.bDescription[ulReadLen] = meta->id3v2Tag.bDescription[ulReadLen + 1] = 0; //null terminator
        meta->id3v2Tag.descriptionEncMode = MMPD_ID3_TEXT_UTF16_BE;

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(usDescriptionLen - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
    }
    /* Get rating info */
    if (usRatingLen && (meta->metaType & MMPD_ID3_META_RATING)) {
        if (usRatingLen <= sizeof(meta->id3v2Tag.ubRating))
            ulReadLen = usRatingLen;
        else
            ulReadLen = sizeof(meta->id3v2Tag.ubRating);
        if (MMPD_AUDPSR_ReadWMAFile(&meta->id3v2Tag.ubRating, ulReadLen) < 0)
            return ASF_ERROR_EOF;

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(usRatingLen - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
    }

    if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)ullObjSize - 24 - 10 - usTitleLen - usAuthorLen -
                                          usCopyrightLen - usDescriptionLen - usRatingLen, m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;

    return 0;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ParseWMAExtContentObj
//  Description : 
//=========================================================================
/** @brief Host audio parse WMA extended content description object

@param[in] ullSize Object size
@param[out] meta Get WMA file meta data in externded content description object
@retval 0 Success.
*/
static MMP_LONG MMPD_AUDPSR_ParseWMAExtContentObj(MMP_ULONG64 ullObjSize, MMPD_ID3_INFO *meta)
{
    MMP_USHORT  count = 0;
    MMP_BOOL    bFindPic = MMP_FALSE;
    MMP_LONG    i = 0;
    MMP_LONG    bytesleft = (MMP_LONG)(ullObjSize - 24);
    MMP_USHORT  length = 9, type = 0;
    MMP_ULONG   ulReadLen = 0;

    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&count, 2) < 0) //content descriptors conunt
        return ASF_ERROR_EOF;

    bytesleft -= 2;

    for(i = 0; i < count; i++) {
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&length, 2) < 0) //descriptor name length
            return ASF_ERROR_EOF;

        if ((length + 2) < sizeof(m_ubUtf16Buf)) {
            if (MMPD_AUDPSR_ReadWMAFile(m_ubUtf16Buf, length) < 0) //descriptor name length
                return ASF_ERROR_EOF;
            m_ubUtf16Buf[length] = m_ubUtf16Buf[length + 1] = 0;
        }
        else {
            m_ubUtf16Buf[0] = m_ubUtf16Buf[1] = 0; //skip this descriptor
            if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)length, m_ulWMAFilePos) < 0)
                return ASF_ERROR_SEEK;
        }

        bytesleft -= 2 + length;

        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&type, 2) < 0) //descirptor value data type
            return ASF_ERROR_EOF;
        if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&length, 2) < 0) //descriptor value length
            return ASF_ERROR_EOF;

        ulReadLen = 0;
        if ((meta->metaType & MMPD_ID3_META_ARTIST) &&
            (MEMCMP(L"WM/AlbumArtist", m_ubUtf16Buf, 28) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bArtist))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bArtist) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bArtist, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bArtist[ulReadLen] = meta->id3v2Tag.bArtist[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.artistEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bArtist))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bArtist) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bArtist, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bArtist[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.artistEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_ALBUM) &&
                 (MEMCMP(L"WM/AlbumTitle", m_ubUtf16Buf, 26) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bAlbum))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bAlbum) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bAlbum, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bAlbum[ulReadLen] = meta->id3v2Tag.bAlbum[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.albumEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bAlbum))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bAlbum) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bAlbum, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bAlbum[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.albumEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_GENRE) &&
                 (MEMCMP(L"WM/Genre", m_ubUtf16Buf, 16) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bGenre))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bGenre) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bGenre, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bGenre[ulReadLen] = meta->id3v2Tag.bGenre[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.genreEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bGenre))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bGenre) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bGenre, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bGenre[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.genreEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_TRACKNUM) &&
                 (MEMCMP(L"WM/TrackNumber", m_ubUtf16Buf, 28) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bTrack))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bTrack) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bTrack, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bTrack[ulReadLen] = meta->id3v2Tag.bTrack[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.trackEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bTrack))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bTrack) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bTrack, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bTrack[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.trackEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
            else if (type == 0x0003) {
                MMP_ULONG ulTrackNum = 0, ulTmpTrackNum = 0;
                MMP_UBYTE ubLength = 0;
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ulTrackNum, 4) < 0)
                    return ASF_ERROR_EOF;
                ulReadLen = 4;

                ulTmpTrackNum = ulTrackNum;
                while (ulTmpTrackNum > 0) {
                    ulTmpTrackNum /= 10;
                    ubLength++;
                    if (ubLength > 255)
                        break;
                }
                PRINTF("TrackNum = %d\r\n", ulTrackNum);
                PRINTF("Length of TrackNum = %d\r\n", ubLength);
                if ((ubLength < 255) && (ubLength < sizeof(meta->id3v2Tag.bTrack))) {
                    ulTmpTrackNum = ulTrackNum;
                    meta->id3v2Tag.bTrack[ubLength--] = 0;
                    while (ulTmpTrackNum) {
                        meta->id3v2Tag.bTrack[ubLength--] = (ulTmpTrackNum%10) + '0';
                        ulTmpTrackNum /= 10;
                    }
                    meta->id3v2Tag.trackEncMode = MMPD_ID3_TEXT_ISO_8859_1;
                }
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_YEAR) &&
                 (MEMCMP(L"WM/Year", m_ubUtf16Buf, 14) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bYear))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bYear) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bYear, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bYear[ulReadLen] = meta->id3v2Tag.bYear[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.yearEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bYear))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bYear) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bYear, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bYear[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.yearEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_AUTHOR) &&
                 (MEMCMP(L"WM/Composer", m_ubUtf16Buf, 22) == 0)) {
            if (type == 0x0000) { //unicode string
                if ((length + 2) < sizeof(meta->id3v2Tag.bComposer))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bComposer) - 2; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bComposer, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bComposer[ulReadLen] = meta->id3v2Tag.bComposer[ulReadLen + 1] = 0; //null terminator
                meta->id3v2Tag.composerEncMode = MMPD_ID3_TEXT_UTF16_BE;
            }
            else if (type == 0x0001) { //byte array
                if ((length + 1) < sizeof(meta->id3v2Tag.bComposer))
                    ulReadLen = length;
                else
                    ulReadLen = sizeof(meta->id3v2Tag.bComposer) - 1; //for null-terminator
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bComposer, ulReadLen) < 0)
                    return ASF_ERROR_EOF;
                meta->id3v2Tag.bComposer[ulReadLen] = 0; //null terminator
                meta->id3v2Tag.composerEncMode = MMPD_ID3_TEXT_ISO_8859_1;
            }
        }
        else if ((meta->metaType & MMPD_ID3_META_APIC) && (bFindPic == MMP_FALSE) &&
                 (MEMCMP(L"WM/Picture", m_ubUtf16Buf, 20) == 0)) {
            //picture type
            if (MMPD_AUDPSR_ReadWMAFile(m_ubUtf8Buf, 1) < 0)
                return ASF_ERROR_EOF;
            ulReadLen = 1;
            //picture data length
            if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&meta->id3v2Tag.ulApicSize, 4) < 0)
                return ASF_ERROR_EOF;
            ulReadLen += 4;
            //MIME
            do {
                if (MMPD_AUDPSR_ReadWMAFile(m_ubUtf8Buf, 2) < 0)
                    return ASF_ERROR_EOF;
                ulReadLen += 2;
            } while (m_ubUtf8Buf[0] | m_ubUtf8Buf[1]);
            //description
            do {
                if (MMPD_AUDPSR_ReadWMAFile(m_ubUtf8Buf, 2) < 0)
                    return ASF_ERROR_EOF;
                ulReadLen += 2;
            } while (m_ubUtf8Buf[0] | m_ubUtf8Buf[1]);
            //picture data
            if (MMPC_System_AllocZeroMem(meta->id3v2Tag.ulApicSize, (void **)&meta->id3v2Tag.bApic)) {
                if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)meta->id3v2Tag.bApic, meta->id3v2Tag.ulApicSize) < 0) {
                    MMPC_System_FreeMem((void **)&meta->id3v2Tag.bApic);
                    meta->id3v2Tag.bApic = NULL;
                    meta->id3v2Tag.ulApicSize = 0;
                    return ASF_ERROR_EOF;
                }
            }
            ulReadLen += meta->id3v2Tag.ulApicSize;
            bFindPic = MMP_TRUE;
        }

        if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(length - ulReadLen), m_ulWMAFilePos) < 0)
            return ASF_ERROR_SEEK;
        bytesleft -= 4 + length;
    }

    if (MMPD_AUDPSR_SeekWMAFile(bytesleft, m_ulWMAFilePos) < 0)
        return ASF_ERROR_SEEK;

    return 0;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_ParseWMATag
//  Description : 
//=========================================================================
/** @brief Host audio parse WMA meta data

@param[out] meta Get WMA file meta data
@retval 0 Success.
*/
static MMP_LONG MMPD_AUDPSR_ParseWMATag(MMPD_ID3_INFO *meta)
{
    MMPD_AUDPSR_ASFOBJECT current;
    MMPD_AUDPSR_ASFOBJECT header;
    MMP_ULONG64 ullDataLen;
    MMP_LONG 	i;
    MMP_ULONG   ulSubObjects;

    /* Clean up tag buffers */
    MEMSET(m_ubUtf8Buf, 0, sizeof(m_ubUtf8Buf));
    MEMSET(m_ubUtf16Buf, 0, sizeof(m_ubUtf16Buf));
    meta->flag = ID3_V2_IN_AUDIO;

    if (MMPD_AUDPSR_ReadWMAObjectHeader((MMPD_AUDPSR_ASFOBJECT *) &header) < 0)
        return ASF_ERROR_EOF;

    if (header.ullSize < 30) {
        /* invalid size for header object */
        return ASF_ERROR_OBJECT_SIZE;
    }

    if (MMPD_AUDPSR_ReadWMAFile((MMP_UBYTE *)&ulSubObjects, 4) < 0)
        return ASF_ERROR_EOF;

    /* Two reserved bytes - do we need to read them? */
    if (MMPD_AUDPSR_SeekWMAFile(2, m_ulWMAFilePos)<0)
        return ASF_ERROR_SEEK;

    if (ulSubObjects > 0) {
        header.ullDataLen = header.ullSize - 30;

        /* TODO: Check that we have datalen bytes left in the file */
        ullDataLen = header.ullDataLen;

        for (i = 0; i<(MMP_LONG)ulSubObjects; i++) {
            if (ullDataLen < 24) {
                PRINTF("not enough data for reading object\n");
                break;
            }

            if (MMPD_AUDPSR_ReadWMAObjectHeader(&current) < 0)
                return ASF_ERROR_EOF;

            if (current.ullSize > ullDataLen || current.ullSize < 24) {
                break;
            }

            if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_content_description)) {
                MMPD_AUDPSR_ParseWMAContentObj(current.ullSize, meta);
            }
            else if (MMPD_AUDPSR_IsGuidMatch(&current.guid, &asf_guid_extended_content_description)) {
                MMPD_AUDPSR_ParseWMAExtContentObj(current.ullSize, meta);
            }
            else {
                if (MMPD_AUDPSR_SeekWMAFile((MMP_LONG)(current.ullSize - 24), m_ulWMAFilePos) < 0)
                    return ASF_ERROR_SEEK;
            }

            ullDataLen -= current.ullSize;
        }
    }

    return 0;
}
#endif
#if (AAC_HOST_PARSER_EN == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_FillAACPlusBuffer
//  Description :
//------------------------------------------------------------------------------
/** @brief Internal function for AACPlus parser to fill data into aacplus data buffer

@param[in] aacplusbuf AACPlus bitstream input
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_FillAACPlusBuffer(MMPD_AUDPSR_AACPLUS_BUFFER *aacplusbuf)
{
    if (aacplusbuf->bytes_consumed > 0) {
        if (aacplusbuf->bytes_into_buffer) {
            MEMCPY((void*)aacplusbuf->buffer, (void*)(aacplusbuf->buffer + aacplusbuf->bytes_consumed),
				aacplusbuf->bytes_into_buffer*sizeof(MMP_UBYTE));
        }

		if (!aacplusbuf->at_eof) {
			MMPD_AUDPSR_ReadFile((aacplusbuf->buffer + aacplusbuf->bytes_into_buffer), m_ulAACPlusFileOffset, aacplusbuf->bytes_consumed);
			m_ulAACPlusFileOffset += aacplusbuf->bytes_consumed;

            aacplusbuf->bytes_into_buffer += aacplusbuf->bytes_consumed;
        }

        aacplusbuf->bytes_consumed = 0;

        if (aacplusbuf->bytes_into_buffer > 3) {
            if (MEMCMP(aacplusbuf->buffer, "TAG", 3) == 0)
                aacplusbuf->bytes_into_buffer = 0;
        }
        if (aacplusbuf->bytes_into_buffer > 11) {
            if (MEMCMP(aacplusbuf->buffer, "LYRICSBEGIN", 11) == 0)
                aacplusbuf->bytes_into_buffer = 0;
        }
        if (aacplusbuf->bytes_into_buffer > 8) {
            if (MEMCMP(aacplusbuf->buffer, "APETAGEX", 8) == 0)
                aacplusbuf->bytes_into_buffer = 0;
        }
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_ParseAACPlusADTS
//  Description :
//------------------------------------------------------------------------------
/** @brief Internal function for AACPlus parser to parse the ADTS header

@param[in] aacplusbuf AACPlus bitstream input
@param[out] bitrate AACPlus bitrate
@param[out] length
@retval MMP_ERR_NONE Success.
*/

MMP_LONG MMPD_AUDPSR_ParseAACPlusADTS(MMPD_AUDPSR_AACPLUS_BUFFER *aacplusbuf, MMP_LONG *bitrate)
{
    MMP_LONG frame_length;
    MMP_LONG samplerate, i;
    float frames_per_sec, bytes_per_frame;
    MMP_UBYTE *adts_ptr;

    for (i = 0; i+2 < AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS; i++) {
       int profile_test; 
       profile_test = (((aacplusbuf->buffer[i+2] & 0xC0) == 0x40) || ((aacplusbuf->buffer[i+2] & 0xC0) == 0x00));
    
       if ((aacplusbuf->buffer[i] == 0xFF)&&((aacplusbuf->buffer[i+1] & 0xF6) == 0xF0)&& profile_test){ 
			m_AACPlusHeaderType = MMPD_AUDPSR_AACPLUS_ADTS_FORMAT;            
			break;
		}
    }

    if(m_AACPlusHeaderType != MMPD_AUDPSR_AACPLUS_ADTS_FORMAT)
        return -1;

    adts_ptr = &aacplusbuf->buffer[i];

    samplerate = m_lAACPlusADTSSampleRate[(*(adts_ptr+2)&0x3c)>>2];

	frame_length = ((((MMP_ULONG)(*(adts_ptr+3)) & 0x3)) << 11)
                | (((MMP_ULONG)(*(adts_ptr+4))) << 3) | ((*(adts_ptr+5)) >> 5);

    frames_per_sec = (float)samplerate/1024.0f;

    bytes_per_frame = (float)frame_length;

    *bitrate = (MMP_LONG)(8. * bytes_per_frame * frames_per_sec + 0.5);

    return i;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_ParseAACPlusADTSFile
//  Description :
//------------------------------------------------------------------------------
/** @brief Internal function for AACPlus parser to parse the ADTS header

@param[in] aacplusbuf AACPlus bitstream input
@param[out] bitrate AACPlus bitrate
@param[out] length
@retval MMP_ERR_NONE Success.
*/
#if 1 // ERIC new
MMP_LONG MMPD_AUDPSR_ParseAACPlusADTSFile(MMPD_AUDPSR_AACPLUS_BUFFER *aacplusbuf, MMP_LONG *bitrate)
{
    MMP_LONG frame_length = 0;
    float frames_per_sec = 0, bytes_per_frame = 0;
    MMP_LONG samplerate = 0;
    MMP_LONG frames = 0;
    MMP_LONG t_framelength = 0;

    /* Read all frames to ensure correct time and bitrate */
//2009-07-29 Eric modify to match firmware(pre-decode n frames)
//    for (frames = 0;frames<500 /* */; frames++)
    for (frames = 0;frames<(512+AAC_PRE_DECODE_FRAMES) /* */; frames++)
    {
        if (!aacplusbuf->at_eof)
        {
            /* check syncword */
            if (!((aacplusbuf->buffer[0] == 0xFF)&&((aacplusbuf->buffer[1] & 0xF6) == 0xF0)))
                break;

            if (frames == 0)
                samplerate = m_lAACPlusADTSSampleRate[(aacplusbuf->buffer[2]&0x3c)>>2];

            frame_length = ((((MMP_ULONG)aacplusbuf->buffer[3] & 0x3)) << 11)
                | (((MMP_ULONG)aacplusbuf->buffer[4]) << 3) | (aacplusbuf->buffer[5] >> 5);

            //2009-07-29 Eric modify to match firmware(pre-decode n frames)
            if(frames >= AAC_PRE_DECODE_FRAMES)
                t_framelength += frame_length;

            if (frame_length > aacplusbuf->bytes_into_buffer)
                break;

		    aacplusbuf->file_offset += frame_length;
		    aacplusbuf->bytes_consumed = frame_length;
		    aacplusbuf->bytes_into_buffer -= frame_length;

	        MMPD_AUDPSR_FillAACPlusBuffer(aacplusbuf);
        } else {
            break;
        }
    }


    frames_per_sec = (float)samplerate/1024.0f;
    if (frames != 0)
//2009-07-29 Eric modify to match firmware(pre-decode n frames)    
//        bytes_per_frame = (float)t_framelength/(float)frames;
        bytes_per_frame = (float)t_framelength/(float)(frames-AAC_PRE_DECODE_FRAMES);   
    else
        bytes_per_frame = 0;
    *bitrate = (int)(8. * bytes_per_frame * frames_per_sec + 0.5);


    return 0;
}
#else
MMP_LONG MMPD_AUDPSR_ParseAACPlusADTSFile(MMPD_AUDPSR_AACPLUS_BUFFER *aacplusbuf, MMP_LONG *bitrate)
{
    MMP_LONG frame_length;
    float frames_per_sec, bytes_per_frame;
    MMP_LONG samplerate;
    MMP_LONG frames;
    MMP_LONG t_framelength = 0;

    /* Read all frames to ensure correct time and bitrate */
    for (frames = 0;frames < (512 + AAC_PRE_DECODE_FRAMES); frames++) {				
        if (!aacplusbuf->at_eof) {
            /* check syncword */
            if (!((aacplusbuf->buffer[0] == 0xFF)&&((aacplusbuf->buffer[1] & 0xF6) == 0xF0)))
                break;

            if (frames == 0)
                samplerate = m_lAACPlusADTSSampleRate[(aacplusbuf->buffer[2]&0x3c)>>2];

            frame_length = ((((MMP_ULONG)aacplusbuf->buffer[3] & 0x3)) << 11)
                | (((MMP_ULONG)aacplusbuf->buffer[4]) << 3) | (aacplusbuf->buffer[5] >> 5);

            //2009-07-29 Eric modify to match firmware(pre-decode n frames)
            if(frames >= AAC_PRE_DECODE_FRAMES)
                t_framelength += frame_length;

            if (frame_length > aacplusbuf->bytes_into_buffer)
                break;

		    aacplusbuf->file_offset += frame_length;
		    aacplusbuf->bytes_consumed = frame_length;
		    aacplusbuf->bytes_into_buffer -= frame_length;

	        MMPD_AUDPSR_FillAACPlusBuffer(aacplusbuf);
        } else {
            break;
        }
    }

    frames_per_sec = (float)samplerate/1024.0f;
    if (frames != 0) {
        //2009-07-29 Eric modify to match firmware(pre-decode n frames)    
        bytes_per_frame = (float)t_framelength/(float)(frames - AAC_PRE_DECODE_FRAMES);
    }
    else
        bytes_per_frame = 0;
    *bitrate = (MMP_LONG)(8. * bytes_per_frame * frames_per_sec + 0.5);

    return 0;
}
#endif
#endif
#if (OGG_HOST_PARSER_EN == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDPSR_GetOGGMetaData
//  Description :
//------------------------------------------------------------------------------
/** @brief A simple parser to read vital metadata from an Ogg Vorbis file. Can also handle parsing Ogg Speex files for metadata. Returns
	false if metadata needed by the codec couldn't be read.

@param[out] ogginfo
@retval MMP_ERR_NONE Success.
*/
#define OGG_BITRATE_FW_MODE (1)
static MMP_LONG MMPD_AUDPSR_GetOGGMetaData(MMP_AUDIO_OGG_INFO *ogginfo)
{
    /* An Ogg File is split into pages, each starting with the string 
     * "OggS". Each page has a timestamp (in PCM samples) referred to as
     * the "granule position".
     *
     * An Ogg Vorbis has the following structure:
     * 1) Identification header (containing samplerate, numchannels, etc)
     * 2) Comment header - containing the Vorbis Comments
     * 3) Setup header - containing codec setup information
     * 4) Many audio packets...
     *
     * An Ogg Speex has the following structure:
     * 1) Identification header (containing samplerate, numchannels, etc)
     *    Described in this page: (http://www.speex.org/manual2/node7.html)
     * 2) Comment header - containing the Vorbis Comments
     * 3) Many audio packets.
     */

    /* Use the path name of the id3 structure as a temporary buffer. */
    MMP_UBYTE	tbuf[OGGP_MAX_PATH];
    MMP_UBYTE	*buf = tbuf;
    MMP_LONG comment_size;
    MMP_LONG remaining = 0;
    MMP_LONG last_serial = 0;
    MMP_LONG serial;
    MMP_LONG segments;

    MMP_LONG i;
    MMP_LONG eof = MMP_FALSE;
    
    MMP_USHORT  OggCodecID;
    MMP_LONG	OggTotalSamples;
    MMP_ULONG   OggTotalTime;      //ms


  	MMPD_AUDPSR_ReadFile(buf, m_ulOGGFileOffset, 92);
  	m_ulOGGFileOffset += 92;
    
    /* All Ogg streams start with OggS */
    if (MEMCMP(buf, "OggS", 4) != 0) {
        return ASF_ERROR_FILEHDR;
    }

    /* Check for format magic and then get metadata */
    if (MEMCMP(&buf[29], "vorbis", 6) == 0) {
    	#if (OGG_BITRATE_FW_MODE == 1)
        int tBitRateUpper;
        int tBitRateLower;
    	#endif
    
        OggCodecID = OGGPFMT_OGG_VORBIS;
        ogginfo->usChans= buf[39];
        ogginfo->usSampleRate = (MMP_USHORT)(buf[40] | (buf[41] << 8) | (buf[42] << 16) | (buf[43] << 24));

		#if (OGG_BITRATE_FW_MODE == 1)
        ogginfo->ulBitRate = buf[48] | (buf[49] << 8) | (buf[50] << 16) | (buf[51] << 24);
		#endif

		#if (OGG_BITRATE_FW_MODE == 1)
        tBitRateUpper = buf[44] | (buf[45] << 8) | (buf[46] << 16) | (buf[47] << 24);
        tBitRateLower = buf[52] | (buf[53] << 8) | (buf[54] << 16) | (buf[55] << 24);

        if(tBitRateUpper >= tBitRateLower)
            ogginfo->usVbrInfo = 1;
        else
            ogginfo->usVbrInfo = 0;

		#else
        ogginfo->usVbrInfo = 1;
		#endif        

		m_ulOGGFileOffset = 58; 
    }
    else
    {
        /* Unsupported format, try to print the marker, catches Ogg/FLAC at least */
        OggCodecID = OGGPFMT_UNKNOWN;
        return ASF_ERROR_UNKNW_FMT;
    }

    /* We need to ensure the serial number from this page is the same as the
     * one from the last page (since we only support a single bitstream).
     */
    serial = buf[14] | (buf[15] << 8) | (buf[16] << 16) | (buf[17] << 24);

	MMPD_AUDPSR_ReadFile(buf, m_ulOGGFileOffset, 27);
  	m_ulOGGFileOffset += 27;

    if (MEMCMP(buf, "OggS", 4) != 0) {
        return ASF_ERROR_PKTHDR;
    }

    segments = buf[26];

    /* read in segment table */
	MMPD_AUDPSR_ReadFile(buf, m_ulOGGFileOffset, segments);
  	m_ulOGGFileOffset += segments;

    /* The second packet in a vorbis stream is the comment packet. It *may*
     * extend beyond the second page, but usually does not. Here we find the
     * length of the comment packet (or the rest of the page if the comment
     * packet extends to the third page).
     */
    for (i = 0; i < segments; i++) {
        remaining += buf[i];
        
        /* The last segment of a packet is always < 255 bytes */
        if (buf[i] < 255) {
              break;
        }
    }

    comment_size = remaining;
    
    if (OggCodecID == OGGPFMT_OGG_VORBIS) {
        /* Now read in packet header (type and id string) */
		MMPD_AUDPSR_ReadFile(buf, m_ulOGGFileOffset, 7);
  		m_ulOGGFileOffset += 7;

        remaining -= 7;

        /* The first byte of a packet is the packet type; comment packets are
         * type 3.
         */
        if (buf[0] != 3) {
            return ASF_ERROR_CMTHDR;
        }
    }

    /* Failure to read the tags isn't fatal. */
//    read_vorbis_tags(fd, id3, remaining);

    /* We now need to search for the last page in the file - identified by 
     * by ('O','g','g','S',0) and retrieve totalsamples.
     */

    /* A page is always < 64 kB */
    if (m_ulMediaFileSize < 64 * 1024)
    	m_ulOGGFileOffset = 0;
    else
    	m_ulOGGFileOffset = m_ulMediaFileSize - 64*1024;	

    remaining = 0;

    while (eof == MMP_FALSE) { 
		MMPD_AUDPSR_ReadFile(&buf[remaining], m_ulOGGFileOffset, OGGP_MAX_PATH - remaining);
  		m_ulOGGFileOffset += OGGP_MAX_PATH - remaining;
  		
        if (m_ulOGGFileOffset >= m_ulMediaFileSize) {
            eof = MMP_TRUE;
        } 
        else { 
        	if ((m_ulMediaFileSize - m_ulOGGFileOffset) > (OGGP_MAX_PATH - remaining))
	            remaining += (OGGP_MAX_PATH - remaining);
	        else {
	        	remaining += (m_ulMediaFileSize - m_ulOGGFileOffset);
	        }    
        }
        
        /* Inefficient (but simple) search */
        i = 0;
        
        while (i < (remaining - 3)) {
            if ((buf[i] == 'O') && (MEMCMP(&buf[i], "OggS", 4) == 0)) {
                if (i < (remaining - 17)) {
                    /* Note that this only reads the low 32 bits of a
                     * 64 bit value.
                     */
                     OggTotalSamples = buf[i + 6] | (buf[i + 7] << 8) | (buf[i + 8] << 16) | (buf[i + 9] << 24);
                     last_serial = buf[i + 14] | (buf[i + 15] << 8) | (buf[i + 16] << 16) | (buf[i + 17] << 24);

                    /* If this page is very small the beginning of the next
                     * header could be in buffer. Jump near end of this header
                     * and continue */
                    i += 27;
                } 
                else {
                    break;
                }
            } 
            else {
                i++;
            }
        }

        if (i < remaining) {
            /* Move the remaining bytes to start of buffer.
             * Reuse var 'segments' as it is no longer needed */
            segments = 0;
            while (i < remaining)
            {
                buf[segments++] = buf[i++];
            }
            remaining = segments;
        }
        else {
            /* Discard the rest of the buffer */
            remaining = 0;
        }
    }

    /* This file has mutiple vorbis bitstreams (or is corrupt). */
    /* FIXME we should display an error here. */
    if (serial != last_serial){
        return ASF_ERROR_MULTISTREAM;
    }

    if(ogginfo->usSampleRate)
        OggTotalTime = (MMP_ULONG)(((MMP_ULONG64) OggTotalSamples * 1000) / ogginfo->usSampleRate); //ms
    else
        OggTotalTime = 0;
    if (OggTotalTime == 0) {
        return ASF_ERROR_INVALID_TOTALTIME;
    }
    
    #if (OGG_BITRATE_FW_MODE == 1)
    #else
    ogginfo->ulBitRate = (MMP_ULONG)((((MMP_ULONG64) m_ulMediaFileSize - comment_size) * 8 * 1000) / OggTotalTime); //bps
    #endif
    
    return 0;
}
#endif
#if (WAV_HOST_PARSER_EN == 1)
//=========================================================================
//  Function    : MMPD_AUDPSR_ParseWAVHeader
//  Description : 
//=========================================================================
/** @brief Host audio parse WAV information

@param[out] wavinfo Get WAV file media spec information
@retval 0 Success.
*/
static MMP_ERR MMPD_AUDPSR_ParseWAVHeader(MMP_AUDIO_WAV_INFO* wavinfo)
{
    MMPD_AUDPSR_WAV_CHUNK_HDR       chunk;
    MMPD_AUDPSR_WAV_SUBCHUNK_HDR    SubChunkHdr;
    MMPD_AUDPSR_WAV_FMT_HDR         fmtSubChunk;
    MMP_LONG  lChunkCnt = 0;
    MMP_ULONG ulWAVFilePos = 0;

    MEMSET(&chunk, 0, sizeof(chunk));
    MEMSET(&fmtSubChunk, 0, sizeof(fmtSubChunk));

    if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&chunk, 0, sizeof(chunk)))
        return MMP_FS_ERR_READ_FAIL;

    //Check RIFF header
    if ((chunk.ulChunkID != STR_RIFF) || (chunk.ulFormat != STR_WAVE)) {
        PRINTF("chunk.ulChunkID = %X\r\n", chunk.ulChunkID);
        PRINTF("chunk.ulFormat = %X\r\n", chunk.ulFormat);
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    ulWAVFilePos += sizeof(chunk);

    // Check fmt and data chunk.
    do {
        if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&SubChunkHdr, ulWAVFilePos, sizeof(SubChunkHdr)))
            return MMP_FS_ERR_READ_FAIL;
        ulWAVFilePos += sizeof(SubChunkHdr);

        if (SubChunkHdr.ulSubChunkID == STR_fmt) {
            if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&fmtSubChunk, ulWAVFilePos, sizeof(fmtSubChunk)))
                return MMP_FS_ERR_READ_FAIL;
        }

        ulWAVFilePos += SubChunkHdr.ulSubChunkSize;
        lChunkCnt++;
    } while((SubChunkHdr.ulSubChunkID != STR_data) && (lChunkCnt < 16));

    if ((lChunkCnt >= 16) && (SubChunkHdr.ulSubChunkID != STR_data)) {
		PRINTF("lChunkCnt >= 16 and can not fine data sub-chunk\r\n");
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
	}

    if (fmtSubChunk.usAudioFmt == UNCOMPRESSED_PCM) {
        wavinfo->ulBitRate      = fmtSubChunk.ulByteRate << 3;
        wavinfo->usChans        = fmtSubChunk.usChans;
        wavinfo->usSampleRate   = fmtSubChunk.ulSampleRate;
		if(fmtSubChunk.ulByteRate)
            wavinfo->ulTotalTime    = (((MMP_ULONG64)SubChunkHdr.ulSubChunkSize * 100) / fmtSubChunk.ulByteRate) * 10;
        else {
            wavinfo->ulTotalTime = 0;
            wavinfo->usNotSupport = 1;
        }
    }
    else {
        PRINTF("Unsupport wave compressed code\r\n");
        wavinfo->ulBitRate = 0;
    }
    if (wavinfo->ulBitRate == 0 || wavinfo->usChans == 0)
        wavinfo->usNotSupport = 1;

    return MMP_ERR_NONE;
}
#endif
#if (AMR_HOST_PARSER_EN == 1)
//=========================================================================
//  Function    : MMPD_AUDPSR_ParseAMRHeader
//  Description : 
//=========================================================================
/** @brief Host audio parse AMR information

@param[out] amrinfo Get AMR file media spec information
@retval 0 Success.
*/
#if 0
static MMP_ERR MMPD_AUDPSR_ParseAMRHeader(MMP_AUDIO_AMR_INFO* amrinfo)
{
    unsigned char toc, q, ft;
	MMP_UBYTE magic[8];
	unsigned char packed_bits[MAX_PACKED_SIZE];
	int   ParseTime;                      // total parse time in ms
	int   FrameCount;     
	int   ParsedFrameSize;                 // parsed AMR frame size in byte  
	int frame_size;

    MMP_ULONG ulAMRFilePos = 0;

    
    if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)magic, 0, STRLEN(AMR_MAGIC_NUMBER)))
        return MMP_FS_ERR_READ_FAIL;

    //Check header
    if (MEMCMP((const char *)magic, AMR_MAGIC_NUMBER, STRLEN(AMR_MAGIC_NUMBER))){
        PRINTF("Parser AMR header fail!!\r\n");
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    ulAMRFilePos += STRLEN(AMR_MAGIC_NUMBER);

	/*-----------------------------------------------------------------------*
	* process serial bitstream frame by frame                               *
	*-----------------------------------------------------------------------*/
	FrameCount = 0;
	ParsedFrameSize = 0;

    while (MMP_ERR_NONE == MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&toc, ulAMRFilePos, 1))	
	{
		ulAMRFilePos++;

		/* read rest of the frame based on ToC byte */
		q  = (toc >> 2) & 0x01;
		ft = (toc >> 3) & 0x0F;
		frame_size = packed_size[ft];
		MMPD_AUDPSR_ReadFile((MMP_UBYTE *)packed_bits, ulAMRFilePos, frame_size);

		ulAMRFilePos += frame_size;
		ParsedFrameSize += frame_size+1;  
		++FrameCount;

		//for CBR 
		if(FrameCount == 1) {
			amrinfo->usMode = ft;
			amrinfo->usSampleSize = frame_size + 1;
		}	

		if(FrameCount >= MAX_PARSE_FRAMR_COUNT)
			break;
	}
	
	ParseTime = 20 * FrameCount;
	amrinfo->ulBitRate = (MMP_ULONG)(ParsedFrameSize * 8000)/ParseTime;
	amrinfo->ulTotalTime = ((m_ulMediaFileSize-STRLEN(AMR_MAGIC_NUMBER)) * 8 * 1000)/ amrinfo->ulBitRate; //unit: milli-sec
    amrinfo->usSampleRate = 8000;

    return MMP_ERR_NONE;
}
#else
static MMP_ERR MMPD_AUDPSR_ParseAMRHeader(MMP_AUDIO_AMR_INFO* amrinfo)
{
    MMP_UBYTE ubTOC = 0, ubQ, ubFT;
	MMP_UBYTE ubMagic[8];
	MMP_UBYTE ubPackedBits[MAX_PACKED_SIZE];
	MMP_ULONG ulParseTime;                      // total parse time in ms
    MMP_ULONG ulFrameCount;     
	MMP_ULONG ulParsedFrameSize;                // parsed AMR frame size in byte  
	MMP_ULONG ulFrameSize;
    MMP_ULONG ulAMRFilePos = 0;
 
    if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)ubMagic, 0, sizeof(AMR_MAGIC_NUMBER)-1))
        return MMP_FS_ERR_READ_FAIL;

    //Check header
    if (MEMCMP((MMP_UBYTE *)ubMagic, AMR_MAGIC_NUMBER, sizeof(AMR_MAGIC_NUMBER)-1)){
        PRINTF("Parser AMR header fail!!\r\n");
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    ulAMRFilePos += (sizeof(AMR_MAGIC_NUMBER)-1);

	/*-----------------------------------------------------------------------*
	* process serial bitstream frame by frame                               *
	*-----------------------------------------------------------------------*/
	ulFrameCount = 0;
	ulParsedFrameSize = 0;

    while (MMP_ERR_NONE == MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&ubTOC, ulAMRFilePos, 1))	
	{
		ulAMRFilePos++;

		/* read rest of the frame based on ToC byte */
		ubQ  = (ubTOC >> 2) & 0x01;
		ubFT = (ubTOC >> 3) & 0x0F;
		ulFrameSize = m_usAMRPackedSize[ubFT];
		MMPD_AUDPSR_ReadFile((MMP_UBYTE *)ubPackedBits, ulAMRFilePos, ulFrameSize);

		ulAMRFilePos += ulFrameSize;
		ulParsedFrameSize += ulFrameSize+1;  
		++ulFrameCount;

		//for CBR 
		if(ulFrameCount == 1) {
			amrinfo->usMode = ubFT;
			amrinfo->usSampleSize = ulFrameSize + 1;
		}	

		if(ulFrameCount >= MAX_PARSE_FRAMR_COUNT)
			break;
	}
	
	ulParseTime = 20 * ulFrameCount;
	amrinfo->ulBitRate = (MMP_ULONG)(ulParsedFrameSize * 8000)/ulParseTime;
    amrinfo->usSampleRate = 8000;
    if(amrinfo->ulBitRate)
        amrinfo->ulTotalTime = ((MMP_ULONG64)(m_ulMediaFileSize-sizeof(AMR_MAGIC_NUMBER)+1) * 8 * 1000)/ amrinfo->ulBitRate; //unit: milli-sec
    else {
      amrinfo->ulTotalTime = 0;
      amrinfo->usNotSupport = 1;
      return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    return MMP_ERR_NONE;
}
#endif
#endif

//=========================================================================
//  Function    : MMPD_AUDPSR_Intialize
//  Description : 
//=========================================================================
/** @brief Initial audio parser

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_Initialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFileID)
{ 
	MMP_ERR	err = MMP_ERR_NONE;

    m_ulParserfileID = 0;
	m_ulParserPreSeekPos = 0xFFFFFFFF;

    if (ulNameLen != 0) {
        switch(m_mediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            err = MMPC_FS_FileOpen(bFileName, "rb", (void **)&m_ulParserfileID);
            if (err != MMP_ERR_NONE) return err;
            
            MMPC_FS_FileGetSize((void *)m_ulParserfileID, &m_ulMediaFileSize);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            err = MMPD_FS_FileOpen(bFileName, ulNameLen, "rb", sizeof("rb"), &m_ulParserfileID);
            if (err != MMP_ERR_NONE) return err;
            
    	    MMPD_FS_FileGetSize(m_ulParserfileID, &m_ulMediaFileSize);
            break;
        default:
            return MMP_AUDIO_ERR_COMMAND_INVALID;
        }
    }
    else {
        if (ulFileID != 0) {
            m_ulParserfileID = ulFileID;
            switch(m_mediaPath) {
            case MMPD_AUDIO_PLAY_FROM_MEM:
                MMPC_FS_FileGetSize((void *)m_ulParserfileID, &m_ulMediaFileSize);
                MMPC_FS_FileSeek((void *)m_ulParserfileID, 0, MMPD_FS_SEEK_SET);
                break;
            case MMPD_AUDIO_PLAY_FROM_CARD:
        	    MMPD_FS_FileGetSize(m_ulParserfileID, &m_ulMediaFileSize);
                MMPD_FS_FileSeek(m_ulParserfileID, 0, MMPD_FS_SEEK_SET);
                break;
            default:
                return MMP_AUDIO_ERR_COMMAND_INVALID;
            }
        }
        else {
            PRINTF("Invalid file ID!\r\n");
            return MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
    }

	return err;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetMp3Info
//  Description : 
//=========================================================================
/** @brief Host audio parse mp3 information

@param[in] bFileName The input MP3 file name
@param[in] ulNameLen The length of file name
@param[out] mp3info Get Mp3 file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetMp3Info(MMP_AUDIO_MP3_INFO *mp3info)
{
#if (MP3_HOST_PARSER_EN == 1)
	MMP_ULONG 	curSeekPos = 0;
    MMP_UBYTE 	inBuf[MP3_IN_BUF_SIZE];
    MMP_ULONG 	i = 0;
    MMP_LONG 	MP3TotalFrame = 0;
    MMP_LONG 	rt = 0;
    MMP_ULONG 	readBufSize = 0, newReadBufSize = 0, dataInbufCnt = 0;
    MMP_LONG 	HeaderOffset = 0;
	MMP_LONG	MaxSyncNo = 0;
   	MMP_LONG	br[MP3_VALID_FRAME_NO];    
    MMP_LONG 	index = 0;
    MMP_ULONG 	avgBR = 0;   	
    MMPD_ID3_V2_TAG_HEADER id3v2Hdr;   
    MMP_ERR     status = MMP_ERR_NONE;
    MMP_LONG    frameSize = 0;
    MMP_USHORT  newHeaderOffset = 0;
    //samyu@091124, for improving CBR parsing speed.
    MMP_UBYTE   IsVBR = 0;
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  drmEn;
    MMP_ULONG   headerOff;
    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PARSER);
    MMPD_AUDIO_GetDRMOffset(&headerOff, MMPD_OMADRM_FOR_PARSER);   
    #endif

    if (MMP_ERR_NONE != MMPD_AUDPSR_ReadFile((MMP_UBYTE *)&id3v2Hdr, curSeekPos, 10))
        return MMP_FS_ERR_READ_FAIL;

    if (MEMCMP(id3v2Hdr.header, "ID3", 3) == 0)
    {
        curSeekPos = (id3v2Hdr.size[0] << 21) | (id3v2Hdr.size[1] << 14) | 
                  (id3v2Hdr.size[2] << 7) | (id3v2Hdr.size[3]);
        curSeekPos += 10;
        m_ulMediaFileSize -= curSeekPos;
    }

    //The size is calculated as tag size excluding tag header
    readBufSize = MP3_IN_BUF_SIZE;
    if (m_ulMediaFileSize - curSeekPos < readBufSize)
        readBufSize = m_ulMediaFileSize - curSeekPos;
    status = MMPD_AUDPSR_ReadFile(inBuf, curSeekPos, readBufSize);
    if ((status != MMP_FS_ERR_EOF) && (status != MMP_ERR_NONE)) {
        return status;
    }
    curSeekPos += readBufSize;
    dataInbufCnt = readBufSize; //Sam@20091222
    // BufferLeft = readBufSize;
    /* Reset MP3 Info */
    MMPD_AUDPSR_InitMP3HeaderParseInfo(mp3info);   
    MaxSyncNo = MP3_MAX_RESYNC_NO;

    rt = MMPD_AUDPSR_FindMP3VBRHeader(inBuf, readBufSize, &MP3TotalFrame);
    //if (rt < 0)
    //    return MMP_FALSE;
    if(MP3TotalFrame != 0) {
        mp3info->usVbr = 2;  //has vbr header
    }    
   /* this for-loop is to find average bit rate if VBR header is not present. */
	for(i = 0; i < MP3_VALID_FRAME_NO; i++) {
	    /*  Try to find VBR header 
            Will search whole input buffer.
        */
        frameSize = 0;
        newHeaderOffset = 0;
        /*  Try to find sync word & parse the header */
//  		PRINTF("readBufSize: %x", readBufSize);
        //samyu@091215
        if(m_bMp3InitFlag == MMP_TRUE) {
            if ((inBuf[HeaderOffset] & SYNCWORDH) != SYNCWORDH || (inBuf[HeaderOffset+1] & SYNCWORDL) != SYNCWORDL) {
                m_bMp3InitFlag = MMP_FALSE;
                if(index != 0)
                    index--;
                MEMSET(mp3info, 0, sizeof(MMP_AUDIO_MP3_INFO));
                rt = -2;
                break;
            }
        }

        do {
            rt = MMPD_AUDPSR_ParseMP3FrameHeader(mp3info, &inBuf[HeaderOffset], &frameSize);
            HeaderOffset += 1; //byte
            readBufSize -= 1; //byte
//            m_mp3DecInfo.ulCurrentReSyncFileOffset++;
        } while ((rt < 0) && (readBufSize > MP3PARSER_MIN_DATA_REQ)); //do-while loop: simple resync, cannot skip ID3 tag.        
		if (rt >= 0) {
            HeaderOffset += (frameSize - 1); //byte
            if (frameSize <= (readBufSize - MP3PARSER_MIN_DATA_REQ))
            {
                readBufSize -= (frameSize - 1); //byte
            }
            else
            {
                if (frameSize > readBufSize)
                {
                    newHeaderOffset = frameSize - readBufSize - 1;
                    readBufSize = 0;
                }
                else
                {
                    readBufSize = readBufSize - (frameSize - 1);
                }
            }
//            m_mp3DecInfo.ulCurrentReSyncFileOffset += (frameSize - 1);
//            PRINTF("frame_size: %x, %x, %x, %x", frameSize, HeaderOffset, newHeaderOffset, readBufSize);                

			/* syncword found */
            if(mp3info->usVbr == 0) {
                //samyu@091124, for improving CBR parsing speed.
                if( (index != 0) && (IsVBR == 0) ) {
                    if( index < MP3_CBR_CHK_FRM_NO ){
                        if ( br[0] != mp3info->ulBitRate )
                            IsVBR = 1;
                    }
                    else{
                        //first MP3_CBR_CHK_FRM_NO frames are CBR
                        break;  //break for-loop
                    }
                }

                /* record the bit-rate of this frame */
                if(index < MP3_VALID_FRAME_NO)
                {
                    br[index++] = mp3info->ulBitRate;
                }
            }
            else if(mp3info->usVbr == 2) {
                /* VBR header present and syncword found => break the for-loop */
                break;
            }
            MaxSyncNo = MP3_MAX_RESYNC_NO;
		}
        else {
            if( index != 0 )
                rt = 0; /* we have success before */

            /* syncword not found */
			if(MaxSyncNo-- <= 0) {
                break;
			}
		}

        /* Shift the residue data in input buffer */
        if (readBufSize <= MP3PARSER_MIN_DATA_REQ)
        {
            //Sam@20091222
            //MEMCPY(inBuf, &inBuf[MP3_IN_BUF_SIZE - readBufSize], readBufSize);
            MEMCPY(inBuf, &inBuf[dataInbufCnt - readBufSize], readBufSize);
            /* Get new input */
    	    newReadBufSize = MP3_IN_BUF_SIZE - readBufSize;
            curSeekPos += newHeaderOffset;
            //if (m_ulMediaFileSize - curSeekPos < newReadBufSize)
                //newReadBufSize = m_ulMediaFileSize - curSeekPos;
/*
            if (m_ubAsyncMode)
            {
                MMPD_AUDPSR_ReloadCacheAsyncGet(&inBuf[readBufSize]);
            }
            else
            {
*/
		    if (rt >= 0) {
                newReadBufSize = MP3_PAR_NEW_SIZE;                 
		    }
	    if (m_ulMediaFileSize - curSeekPos < newReadBufSize)
	    	newReadBufSize = m_ulMediaFileSize - curSeekPos;
                status = MMPD_AUDPSR_ReadFile(&inBuf[readBufSize], curSeekPos, newReadBufSize); 
                if ((status != MMP_FS_ERR_EOF) && (status != MMP_ERR_NONE))
                {
                    return status;
                }
/*
            }
*/
            curSeekPos += newReadBufSize;        
            //BufferLeft += fread(inBuf, sizeof(unsigned char), INBUF_SZ-BufferLeft, m_ulParserfileID);
            //readBufSize = newReadBufSize;
        HeaderOffset = 0;
        readBufSize = readBufSize + newReadBufSize;
            dataInbufCnt = readBufSize; //Sam@20091222
        if(curSeekPos >= m_ulMediaFileSize)
            break;  //reach eof
        }
    }
    if(rt < 0) {/* syncword lost */
        PRINTF("\r\n Cannot parse this file!!!\r\n");
        mp3info->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    else {/* syncword found */
        /* If VBR header does not present => 
           check if the bitrate for every frame is the same or not.
           if not all the same ==> assume it's VBR.
        */
        if(mp3info->usVbr == 0) {
	        for(i = 1; i < index; i++) {
                if(br[0] != br[i]) {
	                mp3info->usVbr = 1; /* not same => assume it's VBR */
			        break;
	   	        }
            }
        }

        /* Determine Average bit-rate */
	    if(mp3info->usVbr == 2) {/* has VBR header */
            if(MP3TotalFrame != 0)
		        avgBR = (mp3info->usSampleRate / (m_mp3DecInfo.ulSamplePerFrame/8)) * (m_ulMediaFileSize / MP3TotalFrame);
            else
		        avgBR = 0;
	    }
        else if(mp3info->usVbr == 1) {/* does not have VBR header but it's VBR. */
            /* average the bitrate of every frame */
            MMP_ULONG total = 0;
	        for(i = 0; i < index; i++) {
                total += br[i];
            }
            avgBR = total/index;
        }
	    else if(mp3info->usVbr == 0) {
            /* for CBR */
		    avgBR = mp3info->ulBitRate;
	    }
        #if (OMA_DRM_EN == 1)
        if (drmEn) {
            m_ulMediaFileSize -= headerOff;
        }    
        #endif
        /* Calculate the total time by average bitrate */
        if(avgBR != 0) {
            mp3info->ulTotalTime = (MMP_ULONG)((MMP_ULONG64)m_ulMediaFileSize*100 / (avgBR / 8) *  10);
        }
		else
			mp3info->ulTotalTime = 0;
        PRINTF("\r\nm_ulMediaFileSize       = %d\r\n", m_ulMediaFileSize);
        PRINTF("Bit-Rate       = %d bps\r\n", mp3info->ulBitRate);
        PRINTF("Avg. Bit-Rate  = %d bps\r\n", avgBR);
        PRINTF("VBR Type       = %d\r\n", mp3info->usVbr);
        PRINTF("Sample Rate    = %d Hz\r\n",mp3info->usSampleRate);
        PRINTF("Channel(s)     = %d\r\n", mp3info->usChans);
        PRINTF("Layer          = %d\r\n", mp3info->usLayer);
        /* Version: MPEG1=0, MPEG2=1, MPEG2.5=2 */
        PRINTF("Version        = %d\r\n", mp3info->usVersion); 
        PRINTF("Total Time     = %d\r\n", mp3info->ulTotalTime);

        if ((mp3info->usSampleRate < 8000) || (mp3info->usSampleRate > 48000)) {
            PRINTF("Unsupport sample rate\r\n!");
            mp3info->usNotSupport = 1;
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        }
    }
#endif
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetWMAInfo
//  Description : 
//=========================================================================
/** @brief Host audio init and get WMA information

@param[out] wfx Get WMA file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetWMAInfo(MMP_AUDIO_WMA_INFO *wmainfo)
{
#if (WMA_HOST_PARSER_EN == 1)
    MMP_LONG	ret;
    MMP_LONG	audiostream;	

    m_ulWMAFilePos = 0;
    
    MEMSET(wmainfo, 0, sizeof(MMP_AUDIO_WMA_INFO));
    
    ret = MMPD_AUDPSR_ParseWMAHeader(wmainfo, &audiostream);

    if (ret < 0) {
        /*
        Error Codes:
        ASF_ERROR_INTERNAL       = -1,  // incorrect input to API calls 
        ASF_ERROR_OUTOFMEM       = -2,  // some malloc inside program failed 
        ASF_ERROR_EOF            = -3,  // unexpected end of file 
        ASF_ERROR_IO             = -4,  // error reading or writing to file 
        ASF_ERROR_INVALID_LENGTH = -5,  // length value conflict in input data 
        ASF_ERROR_INVALID_VALUE  = -6,  // other value conflict in input data 
        ASF_ERROR_INVALID_OBJECT = -7,  // ASF object missing or in wrong place 
        ASF_ERROR_OBJECT_SIZE    = -8,  // invalid ASF object size (too small) 
        ASF_ERROR_SEEKABLE       = -9,  // file not seekable 
        ASF_ERROR_SEEK           = -10, // file is seekable but seeking failed 
        ASF_ERROR_ENCRYPTED      = -11  // file is encrypted 
        */
        PRINTF("ASF: parsing error - error code: %d\n",ret);
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    if (audiostream == -1) {
        PRINTF("ASF: No WMA streams found\n");
        return MMP_AUDIO_ERR_NO_AUDIO_FOUND;
    }

    /* Show Info */
    PRINTF("WMA file info.: \n");
    PRINTF("WMA Version     = %d \n", wmainfo->usVersion);
    PRINTF("Channel(s)      = %d \n", wmainfo->usChans);
    PRINTF("Sample Rate     = %d Hz\n", wmainfo->ulSampleRate);
    PRINTF("Audio Bitrate   = %d bps\n", wmainfo->ulBitRate);
    PRINTF("VBR             = %s\n", (wmainfo->usVbrInfo) ? "Yes":"No");
    if (wmainfo->usVbrInfo) PRINTF("VBR Type        = %d \n", wmainfo->usVbrInfo);
    PRINTF("Tag             = %s\n", (wmainfo->usTagInfo) ? "Yes":"No");
    PRINTF("Bit Per Sample  = %d\n", wmainfo->usBitsPerSample);
    PRINTF("Total Time      = %d ms\n", wmainfo->ulTotalTime);

    if ((wmainfo->ulSampleRate < 8000) || (wmainfo->ulSampleRate > 48000) || (wmainfo->usBitsPerSample > 16)) {
        PRINTF("Unsupport sample rate or bit per sample!\r\n");
        wmainfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif
    return MMP_ERR_NONE;

}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetWMAMetaData
//  Description : 
//=========================================================================
/** @brief Host WMA meta data parsing

@param[out] id3info Get WMA file meta data
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetWMAMetaData(MMPD_ID3_INFO *id3info)
{
#if (WMA_HOST_PARSER_EN == 1)
    MMP_LONG	ret;	

    m_ulWMAFilePos = 0;

    ret = MMPD_AUDPSR_ParseWMATag(id3info);

    if (ret < 0) {
        /*
        Error Codes:
        ASF_ERROR_INTERNAL       = -1,  // incorrect input to API calls 
        ASF_ERROR_OUTOFMEM       = -2,  // some malloc inside program failed 
        ASF_ERROR_EOF            = -3,  // unexpected end of file 
        ASF_ERROR_IO             = -4,  // error reading or writing to file 
        ASF_ERROR_INVALID_LENGTH = -5,  // length value conflict in input data 
        ASF_ERROR_INVALID_VALUE  = -6,  // other value conflict in input data 
        ASF_ERROR_INVALID_OBJECT = -7,  // ASF object missing or in wrong place 
        ASF_ERROR_OBJECT_SIZE    = -8,  // invalid ASF object size (too small) 
        ASF_ERROR_SEEKABLE       = -9,  // file not seekable 
        ASF_ERROR_SEEK           = -10, // file is seekable but seeking failed 
        ASF_ERROR_ENCRYPTED      = -11  // file is encrypted 
        */
        PRINTF("ASF: parsing error - error code: %d\n", ret);
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif

    return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDPSR_GetAACPlusInfo
//  Description : 
//=========================================================================
/** @brief Host audio parse aacplus information

@param[out] aacplusinfo Get AACPLUS file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetAACPlusInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo)
{
#if (AAC_HOST_PARSER_EN == 1)
    MMP_ULONG	samplerate;
    MMP_UBYTE	channels;

    MMP_LONG parse_count = 1;

    faacDecHandle hDecoder;
    faacDecFrameInfo frameInfo;
    faacDecConfigurationPtr config;
    MMPD_AUDPSR_AACPLUS_BUFFER b;
    
    MMP_LONG bread;
    MMP_LONG bitrate = 0;
    MMP_UBYTE b_buf[AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS];
    MMP_LONG offset;
    
	m_ulAACPlusFileOffset = 0;

	m_ulAACPlusObjectType = 0; 
	m_ulAACPlusNotSupport = 0; 


    MEMSET(&b, 0, sizeof(MMPD_AUDPSR_AACPLUS_BUFFER));

    b.buffer = (MMP_UBYTE*)&b_buf;
    
    MEMSET(b.buffer, 0, AACPLUS_MIN_STREAMSIZE * AACPLUS_MAX_CHANNELS);

	MMPD_AUDPSR_ReadFile(b.buffer, m_ulAACPlusFileOffset, AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS);
	m_ulAACPlusFileOffset += AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
    b.bytes_into_buffer = AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
    b.bytes_consumed = 0;
    b.file_offset = 0;

    m_ulAACPlusTagSize = 0;
    if (!MEMCMP(b.buffer, "ID3", 3)) {
        /* high bit is not used */
        MMP_LONG tmp_size; 
        m_ulAACPlusTagSize = (b.buffer[6] << 21) | (b.buffer[7] << 14) | (b.buffer[8] <<  7) | (b.buffer[9] <<  0);

        m_ulAACPlusTagSize += 10;
        
        tmp_size = m_ulAACPlusTagSize;
        while(tmp_size > 1024) {
		    b.file_offset += 1024;
		    b.bytes_consumed = 1024;
		    b.bytes_into_buffer -= 1024;
            
            MMPD_AUDPSR_FillAACPlusBuffer(&b);
            tmp_size -= 1024;    
        }
            

	    b.file_offset += tmp_size;
	    b.bytes_consumed = tmp_size;
	    b.bytes_into_buffer -= tmp_size;
        MMPD_AUDPSR_FillAACPlusBuffer(&b);
    }

    hDecoder = faacDecOpen();

    /* Set the default object type and samplerate */
    /* This is useful for RAW AAC files */
    config = faacDecGetCurrentConfiguration(hDecoder);
    config->defObjectType = LC;
    config->downMatrix = 0;
    config->useOldADTSFormat = 0;
    faacDecSetConfiguration(hDecoder, config);

    /* get AAC infos for printing */
    m_AACPlusHeaderType = 0;
    if (MEMCMP(b.buffer, "ftyp", 4) == 0) {
        PRINTF("3GP format, not AAC format\r\n"); 
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    else if (MEMCMP(b.buffer, "ADIF", 4) == 0) {
        int skip_size = (b.buffer[4] & 0x80) ? 9 : 0;
        bitrate = ((MMP_ULONG)(b.buffer[4 + skip_size] & 0x0F)<<19) |
            ((MMP_ULONG)b.buffer[5 + skip_size]<<11) |
            ((MMP_ULONG)b.buffer[6 + skip_size]<<3) |
            ((MMP_ULONG)b.buffer[7 + skip_size] & 0xE0);

        bitrate = (MMP_LONG)bitrate;
        m_AACPlusHeaderType = MMPD_AUDPSR_AACPLUS_ADIF_FORMAT;
    }
    else {
        offset = MMPD_AUDPSR_ParseAACPlusADTS(&b, &bitrate);
        if(offset == -1) {
            PRINTF("ADTS Sync not found.\r\n"); 
            return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        }    
	    b.file_offset += offset;
	    b.bytes_consumed = offset;
	    b.bytes_into_buffer -= offset;
        MMPD_AUDPSR_FillAACPlusBuffer(&b);
    }

    if ((bread = faacDecInit(hDecoder, b.buffer,
        b.bytes_into_buffer, &samplerate, &channels)) < 0) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
    b.file_offset += bread;
    b.bytes_consumed = bread;
    b.bytes_into_buffer -= bread;
    MMPD_AUDPSR_FillAACPlusBuffer(&b);

    if (m_AACPlusHeaderType == MMPD_AUDPSR_AACPLUS_ADTS_FORMAT) { 
		MMPD_AUDPSR_ParseAACPlusADTSFile(&b, &bitrate);
       
		m_ulAACPlusFileOffset = m_ulAACPlusTagSize;
      // re-initialize bit buffer
		MEMSET(b.buffer, 0, AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS);
       
		MMPD_AUDPSR_ReadFile(b.buffer, m_ulAACPlusFileOffset, AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS);
		m_ulAACPlusFileOffset += AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
       
		b.bytes_into_buffer = AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
		b.bytes_consumed = 0;
		b.file_offset = m_ulAACPlusTagSize;              
    }

#if 1
    if(m_ulAACPlusObjectType == LC)
    {
	    do {
	        faacDecDecode(hDecoder, &frameInfo, b.buffer, b.bytes_into_buffer);

	        /* update buffer indices */
	        if (frameInfo.bytesconsumed > AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS)
	            frameInfo.bytesconsumed = AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
		    b.file_offset += frameInfo.bytesconsumed;
		    b.bytes_consumed = frameInfo.bytesconsumed;
		    b.bytes_into_buffer -= frameInfo.bytesconsumed;

	        if (frameInfo.error > 0) {
	            PRINTF("Error code : %d\n", frameInfo.error);
	        }

	        /* fill buffer */
	        MMPD_AUDPSR_FillAACPlusBuffer(&b);
	        
	        parse_count--;
	    } while (parse_count != 0);
    }
    else
    {
        frameInfo.samplerate = samplerate;
        frameInfo.channels = channels;    
    }
#else
    do {
        faacDecDecode(hDecoder, &frameInfo, b.buffer, b.bytes_into_buffer);

        /* update buffer indices */
        if (frameInfo.bytesconsumed > AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS)
            frameInfo.bytesconsumed = AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
	    b.file_offset += frameInfo.bytesconsumed;
	    b.bytes_consumed = frameInfo.bytesconsumed;
	    b.bytes_into_buffer -= frameInfo.bytesconsumed;

        if (frameInfo.error > 0) {
            PRINTF("Error code : %d\n", frameInfo.error);
            switch (frameInfo.error) {
            case 4:
            case 8:
            case 9:
            case 10:
            case 12:
            case 16:
            case 17:
                //Not serious error
                break;
            default:
                return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
            }
        }

        /* fill buffer */
        MMPD_AUDPSR_FillAACPlusBuffer(&b);
        
        parse_count--;
        if ((m_ulAACPlusObjectType != AACPLUS_V1) && (m_ulAACPlusObjectType != AACPLUS_V2)) {
            faacDecDecode(hDecoder, &frameInfo, b.buffer, b.bytes_into_buffer);

            /* update buffer indices */
            if (frameInfo.bytesconsumed > AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS)
                frameInfo.bytesconsumed = AACPLUS_MIN_STREAMSIZE*AACPLUS_MAX_CHANNELS;
    	    b.file_offset += frameInfo.bytesconsumed;
    	    b.bytes_consumed = frameInfo.bytesconsumed;
    	    b.bytes_into_buffer -= frameInfo.bytesconsumed;

            if (frameInfo.error > 0) {
                PRINTF("Error code 2: %d\n", frameInfo.error);
                switch (frameInfo.error) {
                case 4:
                case 8:
                case 9:
                case 10:
                case 12:
                case 16:
                case 17:
                    //Not serious error
                    break;
                default:
                    return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
                }
            }
        }
        /* fill buffer */
        MMPD_AUDPSR_FillAACPlusBuffer(&b);
    } while (parse_count != 0);
#endif

    /* print AAC file info */
    switch (m_AACPlusHeaderType) {
    case MMPD_AUDPSR_AACPLUS_RAW_FORMAT:
        PRINTF("RAW\n\n");
        break;
    case MMPD_AUDPSR_AACPLUS_ADIF_FORMAT:
    case MMPD_AUDPSR_AACPLUS_ADTS_FORMAT:
    	if (m_AACPlusHeaderType == MMPD_AUDPSR_AACPLUS_ADIF_FORMAT) {
			PRINTF("ADIF, ");
		}
		else {
	    	PRINTF("ADTS, ");
		}	

        switch (m_ulAACPlusObjectType) {
        case LC:
	        PRINTF("AAC-LC, ");
	        break;
        case AACPLUS_V1:
            PRINTF("AACPLUS_V1, ");   
			break;
        case AACPLUS_V2:
            PRINTF("AACPLUS_V2, ");         
			break;
        case MAIN:
            PRINTF("MAIN, ");         
			break;			
		}
        PRINTF("%d kbps, %lx Hz, %d channels\r\n", bitrate, frameInfo.samplerate, frameInfo.channels);
        break;
    }

   	aacplusinfo->usNotSupport = (MMP_USHORT)m_ulAACPlusNotSupport;

	aacplusinfo->ulBitRate = (MMP_ULONG)bitrate;
	aacplusinfo->usHeaderType = m_AACPlusHeaderType;
    aacplusinfo->usSampleRate = (MMP_USHORT)frameInfo.samplerate;   // sampling rate
    aacplusinfo->usChans = (MMP_USHORT)frameInfo.channels;        // channel num
    if(aacplusinfo->ulBitRate)
        aacplusinfo->ulTotalTime = (MMP_ULONG)((MMP_ULONG64)m_ulMediaFileSize*100/(aacplusinfo->ulBitRate/8)*10);
    else {
        aacplusinfo->ulTotalTime = 0;
        aacplusinfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    PRINTF("aacplusinfo->ulBitRate: %x\r\n", aacplusinfo->ulBitRate);
    PRINTF("aacplusinfo->usHeaderType: %x\r\n", aacplusinfo->usHeaderType);
    PRINTF("aacplusinfo->usSampleRate: %x\r\n", aacplusinfo->usSampleRate);
    PRINTF("aacplusinfo->usChans: %x\r\n", aacplusinfo->usChans);
    PRINTF("aacplusinfo->ulTotalTime: %x\r\n", aacplusinfo->ulTotalTime);    
    PRINTF("aacplusinfo->usNotSupport: %x\r\n", aacplusinfo->usNotSupport);

    if ((aacplusinfo->usSampleRate < 8000) || (aacplusinfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate\r\n!");
        aacplusinfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetWAVInfo
//  Description : 
//=========================================================================
/** @brief Host audio init and get WAV information

@param[out] wavinfo Get WAV file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetWAVInfo(MMP_AUDIO_WAV_INFO *wavinfo)
{
#if (WAV_HOST_PARSER_EN == 1)
    MMP_ERR ret;
    
    MEMSET(wavinfo, 0, sizeof(MMP_AUDIO_WAV_INFO));

    ret = MMPD_AUDPSR_ParseWAVHeader(wavinfo);

    if (ret != MMP_ERR_NONE) {
        PRINTF("Parsing error - error code: %d\n", ret);
        wavinfo->usNotSupport = 1;
        return ret;
    }
    else if (wavinfo->usNotSupport) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    /* Show Info */
    PRINTF("WAV file info.: \n");
    PRINTF("Channel(s)      = %d \n", wavinfo->usChans);
    PRINTF("Sample Rate     = %d Hz\n", wavinfo->usSampleRate);
    PRINTF("Audio Bitrate   = %d bps\n", wavinfo->ulBitRate);
    PRINTF("Total Time      = %d ms\n", wavinfo->ulTotalTime);
    
    if ((wavinfo->usSampleRate < 8000) || (wavinfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate\r\n!");
        wavinfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif
    return MMP_ERR_NONE;

}
//=========================================================================
//  Function    : MMPD_AUDPSR_GetOGGInfo
//  Description : 
//=========================================================================
/** @brief Host audio parse ogg information

@param[out] aacplusinfo Get OGG file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetOGGInfo(MMP_AUDIO_OGG_INFO *ogginfo)
{
#if (OGG_HOST_PARSER_EN == 1)
	MMP_LONG	res;

	MEMSET(ogginfo, 0, sizeof(MMP_AUDIO_OGG_INFO));

	m_ulOGGFileOffset = 0;

    /* Start to parse asf file format */
    res = MMPD_AUDPSR_GetOGGMetaData(ogginfo);

    if (res < 0) {
        /*
        Error Codes:
        ASF_ERROR_FILEIO            = -1,  // File read/seek error 
        ASF_ERROR_FILEHDR           = -2,  // File not start with "OggS" 
        ASF_ERROR_UNKNW_FMT         = -3,  // File is not OGG Vorbis, may be it's FLAC or Speex 
        ASF_ERROR_PKTHDR            = -4,  // Invalid packet header
        ASF_ERROR_CMTHDR            = -5,  // Invalid comment header
        ASF_ERROR_MULTISTREAM       = -6,  // Multiple vorbis streams is not supported 
        ASF_ERROR_INVALID_TOTALTIME = -7,  // Invalid total time 
        */
        PRINTF("OGG: parsing error - error code: %d\n",res);
        ogginfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
	if (ogginfo->ulBitRate == 0) {
		ogginfo->usNotSupport = 1;
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
	}		
	else
		ogginfo->usNotSupport = 0;
	ogginfo->ulTotalTime = (MMP_ULONG)((MMP_ULONG64)m_ulMediaFileSize*100/(ogginfo->ulBitRate/8)*10);

    
    PRINTF("ogginfo->ulBitRate: %d\r\n", ogginfo->ulBitRate);
    PRINTF("ogginfo->usSampleRate: %d\r\n", ogginfo->usSampleRate);
    PRINTF("ogginfo->usChans: %d\r\n", ogginfo->usChans);
    PRINTF("ogginfo->ulTotalTime: %d\r\n", ogginfo->ulTotalTime);    
    PRINTF("ogginfo->usVbrInfo: %x\r\n", ogginfo->usVbrInfo);    
    PRINTF("ogginfo->usNotSupport: %x\r\n", ogginfo->usNotSupport);

    if ((ogginfo->usSampleRate < 8000) || (ogginfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate\r\n!");
        ogginfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetRACurFileOffset
//  Description : 
//=========================================================================
/** @brief Host audio parse ra information

@param[out] ulFileOffset
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetRACurFileOffset(MMP_ULONG *ulFileOffset)
{
#if (RA_HOST_PARSER_EN == 1)
	*ulFileOffset = m_ulRAFileOffset;
#endif
	return MMP_ERR_NONE;

}
//=========================================================================
//  Function    : MMPD_AUDPSR_SetRACurFileOffset
//  Description : 
//=========================================================================
/** @brief Host audio parse ra information

@param[out] ulFileOffset
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_SetRACurFileOffset(MMP_ULONG ulFileOffset)
{
#if (RA_HOST_PARSER_EN == 1)
	m_ulRAFileOffset = ulFileOffset;
#endif
	return MMP_ERR_NONE;

}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetRAInfo
//  Description : 
//=========================================================================
/** @brief Host audio parse ra information

@param[out] rainfo Get ra file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetRAInfo(MMP_AUDIO_RA_INFO *rainfo)
{
#if (RA_HOST_PARSER_EN == 1)
    MMP_ULONG           ulCodec4CC     = 0;
    MMP_ULONG           ulChannels     = 0;
    MMP_ULONG           ulSampleRate   = 0;
    MMP_ULONG           i              = 0;
    MMP_ULONG           ulNumStreams   = 0;

	HX_RESULT			retVal = HXR_FAIL;
    MMP_UBYTE           ucBuf[RM2WAV_INITIAL_READ_SIZE];
	radec_info			raInfo;
	radec_info 			*pInfo;
	rm_parser*          RADec_pParser        = HXNULL;
	rm_stream_header*   RADec_pStreamHdr     = HXNULL;
	ra_depack*          RADec_pDepack        = HXNULL;
	ra_decode*          RADec_pDecode        = HXNULL;
	ra_format_info*     RADec_pCodecInfo     = HXNULL;

	m_ulRAFileOffset = 0;
    rainfo->usNotSupport = 1;

	rm_memory_init((MMP_UBYTE *)m_lRAWorkingBuffer, RADEC_PARSER_WORKING_BUF_SIZE);

	pInfo = &raInfo;

    /* Read the first few bytes of the file */
    MMPD_AUDPSR_ReadFile(ucBuf, m_ulRAFileOffset, RM2WAV_INITIAL_READ_SIZE);

    /* Seek back to the beginning */
	m_ulRAFileOffset = 0;

    /* Make sure this is an .rm file */
    if (!rm_parser_is_rm_file_ait(ucBuf, RM2WAV_INITIAL_READ_SIZE)) {
  		PRINTF("is not an .rm file.\r\n");
		return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
	}

    /* Create the parser struct */
	RADec_pParser = rm_parser_create((void*)NULL, (rm_error_func_ptr)NULL);

    /* Set the FILE* into the parser */
    rm_parser_init_stdio(RADec_pParser, NULL);

    /* Read all the headers at the beginning of the .rm file */
    retVal = rm_parser_read_headers(RADec_pParser);

    /* Get the number of streams */
    ulNumStreams = rm_parser_get_num_streams(RADec_pParser);
    if (ulNumStreams == 0) {
  		PRINTF("Error: rm_parser_get_num_streams() returns 0\r\n");
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    /* Now loop through the stream headers and find the audio stream */
    for (i = 0; i < ulNumStreams && retVal == HXR_OK; i++) {
        retVal = rm_parser_get_stream_header(RADec_pParser, i, &RADec_pStreamHdr);
        if (retVal == HXR_OK) {
            if (rm_stream_is_realaudio(RADec_pStreamHdr)) {
				pInfo->usStreamNum = (MMP_USHORT) i;
                break;
            }
            else {
                /* Destroy the stream header */
                rm_parser_destroy_stream_header(RADec_pParser, &RADec_pStreamHdr);
            }
        }
    }

    /* Do we have a RealAudio stream in this .rm file? */
    if (!RADec_pStreamHdr) {
  		PRINTF("There is no RealAudio stream in this file.\r\n");
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    /* Create the RealAudio depacketizer */
    RADec_pDepack = ra_depack_create((void*) pInfo,
                               (ra_block_avail_func_ptr)NULL,
                               NULL,
                               (rm_error_func_ptr)NULL);

    /* Assign the ra_depack pointer to the info struct */
    pInfo->pDepack = RADec_pDepack;

    /* Initialize the RA depacketizer with the stream header */
    ra_depack_init(RADec_pDepack, RADec_pStreamHdr);

    /*
     * Get the codec 4CC of substream 0. We 
     * arbitrarily choose substream 0 here.
     */
    ulCodec4CC = ra_depack_get_codec_4cc(RADec_pDepack, 0);

    if (ulCodec4CC == 0x636F6F6B) {/* 'cook' */
		pInfo->raBackendCodec = RA_BACKEND_COOK;
		pInfo->PcmOutMaxSamples = 4480;//flavor 25, 22400/5=4480 is max frame size.
		PRINTF("radec ra8lbr. cook.\r\n");
    }
    else if (ulCodec4CC == 0x72616163 || /* 'raac' */
             ulCodec4CC == 0x72616370) {  /* 'racp' */
		pInfo->raBackendCodec = RA_BACKEND_RAAC;
		//2048=AAC output size
		pInfo->PcmOutMaxSamples = 2048;
		PRINTF("radec ra10. raac.\r\n");
    }

    /* Create the ra_decode object */
    RADec_pDecode = ra_decode_create(HXNULL, (rm_error_func_ptr)NULL);

    /* Assign the decode object into the rm2wav_info struct */
    pInfo->pDecode = RADec_pDecode;

    /*
     * Get the bitstream header information. Again,
     * we arbitrarily choose substream 0.
     */
    ra_depack_get_codec_init_info(RADec_pDepack, 0, &RADec_pCodecInfo);

    /* Init the ra_decode object */
    /* Assign the backend function pointers */
    if (ulCodec4CC == 0x61747263) { /* 'atrc' */
    }
    else if (ulCodec4CC == 0x636F6F6B) { /* 'cook' */
        RADec_pDecode->fpInit = ra8lbr_decode_init;
        RADec_pDecode->fpGetChannels = ra8lbr_decode_getchannels;
        RADec_pDecode->fpGetSampleRate = ra8lbr_decode_getrate;
    }
    else if (ulCodec4CC == 0x73697072) { /* 'sipr' */
    }
    else if (ulCodec4CC == 0x72616163 || /* 'raac' */
             ulCodec4CC == 0x72616370) {   /* 'racp' */
        RADec_pDecode->fpInit = aac_decode_init;
        RADec_pDecode->fpGetChannels = aac_decode_getchannels;
        RADec_pDecode->fpGetSampleRate = aac_decode_getrate;
    }
    else
    {
        /* error - codec not supported */
        retVal = HXR_DEC_NOT_FOUND;
    }

    if (retVal == HXR_OK && RADec_pDecode && RADec_pDecode->fpInit && RADec_pCodecInfo)
    {
        retVal = RADec_pDecode->fpInit(HXNULL, 0, RADec_pCodecInfo,
                                   &RADec_pDecode->pDecode, RADec_pDecode->pUserMem,
                                   RADec_pDecode->fpMalloc, RADec_pDecode->fpFree);
    }

    /* Get the number of channels */
    retVal = ra_decode_getchannels(RADec_pDecode, (unsigned long int *)&ulChannels);
    if (retVal != HXR_OK) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

    /* Get the sample rate */
    retVal = ra_decode_getrate(RADec_pDecode, (unsigned long int *)&ulSampleRate);
    if (retVal != HXR_OK) {
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }

	// get information by rm_parser interface
    pInfo->max_bit_rate = rm_parser_get_max_bit_rate(RADec_pParser);
    pInfo->avg_bit_rate = rm_parser_get_avg_bit_rate(RADec_pParser);
    pInfo->duration = rm_parser_get_duration(RADec_pParser);
    retVal = ra_decode_getchannels(RADec_pDecode, (unsigned long int *)&pInfo->Channels);
    retVal = ra_decode_getrate(RADec_pDecode, (unsigned long int *)&pInfo->SampleRate);

    rainfo->ulBitRate = pInfo->avg_bit_rate; //bit rate
    rainfo->usSampleRate = pInfo->SampleRate;//sampling rate
    rainfo->usChans = pInfo->Channels;       //channel num
    rainfo->ulTotalTime = pInfo->duration;   //unit: milli-sec
    rainfo->usNotSupport = 0;   			 //0 : supported format; 1 : not supported format

    PRINTF("rainfo->ulBitRate: %d\r\n", rainfo->ulBitRate);
    PRINTF("rainfo->usSampleRate: %d\r\n", rainfo->usSampleRate);
    PRINTF("rainfo->usChans: %d\r\n", rainfo->usChans);
    PRINTF("rainfo->ulTotalTime: %d\r\n", rainfo->ulTotalTime);    
    PRINTF("rainfo->usVbrInfo: %x\r\n", (raInfo.raBackendCodec == RA_BACKEND_RAAC) ? 1:0);    
    PRINTF("rainfo->usNotSupport: %x\r\n", rainfo->usNotSupport);

    if ((rainfo->usSampleRate < 8000) || (rainfo->usSampleRate > 48000)) {
        PRINTF("Unsupport sample rate\r\n!");
        rainfo->usNotSupport = 1;
        return MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
    }
#endif
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDPSR_GetAMRInfo
//  Description : 
//=========================================================================
/** @brief Host audio init and get AMR information

@param[out] amrinfo Get AMR file media spec information
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_GetAMRInfo(MMP_AUDIO_AMR_INFO *amrinfo)
{
#if (AMR_HOST_PARSER_EN == 1)
	MMP_ERR ret;
    
    MEMSET(amrinfo, 0, sizeof(MMP_AUDIO_AMR_INFO));

    ret = MMPD_AUDPSR_ParseAMRHeader(amrinfo);

    if (ret != MMP_ERR_NONE) {
        PRINTF("Parsing error - error code: %d\n", ret);
        amrinfo->usNotSupport = 1;
        return ret;
    }

    /* Show Info */
    PRINTF("AMR file info.: \n");
	PRINTF("Audio Bitrate   = %d bps\n", amrinfo->ulBitRate);
    PRINTF("Sample Rate     = %d Hz\n", amrinfo->usSampleRate);
    PRINTF("Total Time      = %d ms\n", amrinfo->ulTotalTime); //unit: milli-sec

	//for CBR 
	PRINTF("Mode            = %d \n", amrinfo->usMode);
	PRINTF("Sample Size     = %d \n", amrinfo->usSampleSize);
#endif
    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDPSR_Finish
//  Description : 
//=========================================================================
/** @brief Finish audio parser
@param[in] bCloseFile Close file or not in parser finalization
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDPSR_Finish(MMP_BOOL bCloseFile)
{ 
    if (bCloseFile && (m_ulParserfileID != 0)) {
        switch(m_mediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            MMPC_FS_FileClose((void *)m_ulParserfileID);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            MMPD_FS_FileClose(m_ulParserfileID);
            break;
        default:
            return MMP_AUDIO_ERR_COMMAND_INVALID;
        }
        m_ulParserfileID = 0;
    }    
    return MMP_ERR_NONE;
}



/// @}
/// @end_ait_only

