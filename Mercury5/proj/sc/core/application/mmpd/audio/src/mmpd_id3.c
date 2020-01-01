/// @ait_only
//==============================================================================
//
//  File        : mmpd_id3.c
//  Description : ID3 function
//  Author      : Rogers Chen/Alterman
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_id3.c
*  @brief The MP3 ID3 tag functions
*  @author Rogers Chen
*  @version 1.0
*/
//#include "ait_utility.h"
#include "mmpd_fs.h"
#include "mmpd_id3.h"

#if (OMA_DRM_EN == 1)
#include "mmpd_omadrm.h"
#endif

#define RETURN_IF_ERROR(ret)    if(MMP_ERR_NONE != ret)\
                                    return ret;

/** @addtogroup MMPD_ID3
 *  @{
 */

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
static MMP_ULONG    m_ulMP3fileID;
static MMP_ULONG    m_ulID3PreSeekPos;
static MMP_ULONG    m_ulID3CacheAddr;
static MMP_ULONG    m_ulID3CacheSize;
static MMP_ULONG    m_ulID3MaxCacheSize;
static MMP_ULONG    m_ulID3UsedCacheSize;
static MMPD_AUDIO_PLAY_DATAPATH m_MediaPath;

static MMPD_ID3_ReadFile_FuncPtr MMPD_ID3_ReadFile;
MMP_BYTE m_bGenreStr[126][18] = {
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    "Folk",
    "Folk-Rock",
    "National Folk",
    "Swing",
    "Fast Fusion",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive Rock",
    "Psychedelic Rock",
    "Symphonic Rock",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listening",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Bass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
    "Ballad",
    "Power Ballad",
    "Rhythmic Soul",
    "Freestyle",
    "Duet",
    "Punk Rock",
    "Drum Solo",
    "Acapella",
    "Euro-House",
    "Dance Hall"
};
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_ID3_SetMediaPath
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath)
{
    m_MediaPath = mediapath;

    return  MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_ID3_SetParseCacheBuf
//  Description : 
//------------------------------------------------------------------------------
/** @brief Set the cache address and cache size for parsing ID3

@param[in] ulCacheAddr The address of cache dedicated to ID3 parser
@param[in] ulCacheSize The cache size (must be a multiple of 2)
@param[in] ilMaxCacheSize The total cache size can be used  (must be a multiple of 2)
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_ID3_SetParseCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize, 
                                    MMP_ULONG ulMaxCacheSize)
{
    #if (OMA_DRM_EN == 1)
    MMP_USHORT  usDrmEnable;

    MMPD_AUDIO_GetDRMEnable(&usDrmEnable, MMPD_OMADRM_FOR_PARSER);
    if (usDrmEnable && (ulCacheSize & 0x0F)) {
        PRINTF("Cache size shoule be a multiple of 16 (16-byte alignment)\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }
    #endif
    if ((ulCacheSize & 0x01) || (ulMaxCacheSize & 0x01)) {
        PRINTF("Cache size shoule be a multiple of 2\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }

    m_ulID3CacheAddr = ulCacheAddr;
    m_ulID3CacheSize = ulCacheSize;
    m_ulID3MaxCacheSize = ulMaxCacheSize;

    m_ulID3UsedCacheSize = m_ulID3CacheSize;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_ID3_ReloadCache
//  Description : 
//------------------------------------------------------------------------------
/** @brief Load data into cache if cache missed

@param[in] ulSeekpos Seek position to load data into cache (glID3CacheSize aligned)
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_ID3_ReloadCache(MMP_ULONG ulSeekpos) 
{
    MMP_ULONG   readsize;
    MMP_ERR     ret = MMP_ERR_NONE;
    #if (OMA_DRM_EN == 1)
    MMP_ULONG   ulDrmHeaderOff;
    MMP_USHORT  usDrmEnable;
    MMP_ULONG   ulDrmSeekPos;

    MMPD_AUDIO_GetDRMEnable(&usDrmEnable, MMPD_OMADRM_FOR_PARSER);
    if (usDrmEnable) {
        MMPD_AUDIO_GetDRMOffset(&ulDrmHeaderOff, MMPD_OMADRM_FOR_PARSER);   
        ulDrmSeekPos = ulSeekpos + ulDrmHeaderOff;
    }
    #endif

    // fist-time seek, backward seek or forward seek
    if(m_ulID3PreSeekPos == 0xFFFFFFFF) {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulDrmSeekPos - 0x10, MMPD_FS_SEEK_SET);
                RETURN_IF_ERROR(ret);
                ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulDrmSeekPos - 0x10, MMPD_FS_SEEK_SET);
                RETURN_IF_ERROR(ret);
                ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        }
    }
    else if(ulSeekpos < (m_ulID3PreSeekPos + m_ulID3UsedCacheSize)) {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulDrmSeekPos - 0x10, MMPD_FS_SEEK_SET);
                RETURN_IF_ERROR(ret);
                ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulDrmSeekPos - 0x10, MMPD_FS_SEEK_SET);
                RETURN_IF_ERROR(ret);
                ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            #endif
            break;
        }
    }
    else {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize - 0x10, MMPD_FS_SEEK_CUR);
                RETURN_IF_ERROR(ret);
                ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize, MMPD_FS_SEEK_CUR);
            }
            #else
            ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize, MMPD_FS_SEEK_CUR);
            #endif
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            #if (OMA_DRM_EN == 1)
            if (usDrmEnable) {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize - 0x10, MMPD_FS_SEEK_CUR);
                RETURN_IF_ERROR(ret);
                ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, 0x10, &readsize);
                RETURN_IF_ERROR(ret);
                MMPD_AUDIO_SetDRMIV((MMP_UBYTE *)m_ulID3CacheAddr, MMPD_OMADRM_FOR_PARSER);
            }
            else {
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize, MMPD_FS_SEEK_CUR);
            }
            #else
            ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos - m_ulID3PreSeekPos - m_ulID3UsedCacheSize, MMPD_FS_SEEK_CUR);
            #endif
            break;
        }
    }
    RETURN_IF_ERROR(ret);

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, m_ulID3UsedCacheSize, &readsize);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)m_ulID3CacheAddr, m_ulID3UsedCacheSize, &readsize);
        break;
    }
    RETURN_IF_ERROR(ret);

    #if (OMA_DRM_EN == 1)
    if (usDrmEnable) {
        MMPD_AUDIO_DecryptBufByKey((MMP_UBYTE *)m_ulID3CacheAddr, m_ulID3UsedCacheSize, MMPD_OMADRM_FOR_PARSER);
    }
    #endif

    m_ulID3PreSeekPos = ulSeekpos;

    return  ret;
}

//=========================================================================
//  Function    : MMPD_ID3_ReadCache
//  Description : 
//=========================================================================
/** @brief Read data from cache

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_ID3_ReadCache(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_UBYTE *source;

    source = (MMP_UBYTE *)m_ulID3CacheAddr + (ulSeekpos & (m_ulID3UsedCacheSize - 1));
    while(ulReadsize > 0) {
        *ubTarget++ = *source++;
        ulReadsize--;
    }
    
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_ID3_ReadFile
//  Description : 
//=========================================================================
/** @brief Read MP3 file with cache mechanism

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_ID3_ReadFileData(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_ULONG   readed_size, canread_size, rem_size;
    MMP_ULONG   cur_seekpos;
    MMP_ERR     ret = MMP_ERR_NONE;

    cur_seekpos = ulSeekpos;
    readed_size = 0;
    rem_size    = ulReadsize;

    while(readed_size < ulReadsize){
        if (((m_ulID3PreSeekPos) & ~(m_ulID3UsedCacheSize - 1)) != (cur_seekpos & ~(m_ulID3UsedCacheSize - 1))) {
            // cache miss
            ret = MMPD_ID3_ReloadCache(cur_seekpos & ~(m_ulID3UsedCacheSize - 1));
            RETURN_IF_ERROR(ret);
        }

        canread_size = m_ulID3UsedCacheSize - (cur_seekpos & (m_ulID3UsedCacheSize - 1));
        if (rem_size > canread_size) {
            MMPD_ID3_ReadCache(ubTarget, cur_seekpos, canread_size);
            rem_size -= canread_size;
            readed_size += canread_size;
            cur_seekpos += canread_size;
            ubTarget += canread_size;
        }
        else {
            MMPD_ID3_ReadCache(ubTarget, cur_seekpos, rem_size);
            readed_size += rem_size;
        }
    }

    return MMP_ERR_NONE;
}
#if 0
//=========================================================================
//  Function    : MMPD_ID3_GetV1Tag
//  Description : The ID3v1 tag occupies 128 bytes, beginning with 
//                the string TAG. (Not support Extended tag)
//=========================================================================
static MMP_BOOL MMPD_ID3_GetV1Tag(MMP_UBYTE *ubTagBuf)
{
    MMP_ULONG readsize;
    #if (OMA_DRM_EN == 1)
	MMP_USHORT  usDrmEnable;
	MMPD_AUDIO_GetDRMEnable(&usDrmEnable, MMPD_OMADRM_FOR_PARSER);
    #endif

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        #if (OMA_DRM_EN == 1)
        if (usDrmEnable) {
            MMPC_FS_FileSeek((void *)m_ulMP3fileID, -128-0x10, MMPD_FS_SEEK_END);
            MMPC_FS_FileRead((void *)m_ulMP3fileID, ubTagBuf, 0x10, &readsize);
            MMPD_AUDIO_SetDRMIV(ubTagBuf, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPC_FS_FileSeek((void *)m_ulMP3fileID, -128, MMPD_FS_SEEK_END);
        }
        MMPC_FS_FileRead((void *)m_ulMP3fileID, ubTagBuf, 128, &readsize);
        #else
        MMPC_FS_FileSeek((void *)m_ulMP3fileID, -128, MMPD_FS_SEEK_END);
        MMPC_FS_FileRead((void *)m_ulMP3fileID, ubTagBuf, 128, &readsize);
        #endif
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        #if (OMA_DRM_EN == 1)
        if (usDrmEnable) {
            MMPD_FS_FileSeek(m_ulMP3fileID, -128-0x10, MMPD_FS_SEEK_END);
            MMPD_FS_FileRead(m_ulMP3fileID, ubTagBuf, 0x10, &readsize);
            MMPD_AUDIO_SetDRMIV(ubTagBuf, MMPD_OMADRM_FOR_PARSER);
        }
        else {
            MMPD_FS_FileSeek(m_ulMP3fileID, -128, MMPD_FS_SEEK_END);
        }
        MMPD_FS_FileRead(m_ulMP3fileID, ubTagBuf, 128, &readsize);
        #else
        MMPD_FS_FileSeek(m_ulMP3fileID, -128, MMPD_FS_SEEK_END);
        MMPD_FS_FileRead(m_ulMP3fileID, ubTagBuf, 128, &readsize);
        #endif
        break;
    }
    #if (OMA_DRM_EN == 1)
    if (usDrmEnable) {
	    MMPD_AUDIO_DecryptBufByKey(ubTagBuf, 128, MMPD_OMADRM_FOR_PARSER);
    }
    #endif

    if (MEMCMP(ubTagBuf, "TAG", 3))
        return MMP_FALSE;

    return MMP_TRUE;
}
#endif
//=========================================================================
//  Function    : MMPD_ID3_GetV2TagHeader
//  Description : The ID3v2 header is 10 bytes
//=========================================================================
static MMP_BOOL MMPD_ID3_GetV2TagHeader(MMPD_ID3_V2_TAG_HEADER *id3v2Hdr, MMP_LONG *lTagSize, MMP_ULONG ulSeekPos)
{
    if (MMP_ERR_NONE != MMPD_ID3_ReadFile((MMP_UBYTE *)id3v2Hdr, ulSeekPos, 10))
        return MMP_FALSE;

    if (MEMCMP(id3v2Hdr->header, "ID3", 3))
        return MMP_FALSE;

    //The size is calculated as tag size excluding tag header
    *lTagSize = (id3v2Hdr->size[0] << 21) | (id3v2Hdr->size[1] << 14) | 
                  (id3v2Hdr->size[2] << 7) | (id3v2Hdr->size[3]);

    return MMP_TRUE;
}
#if 0
//=========================================================================
//  Function    : MMPD_ID3_SetV2TagLength
//  Description : 
//=========================================================================
static MMP_BOOL MMPD_ID3_SetV2TagLength(MMPD_ID3_V2_TAG_HEADER *id3v2Hdr, MMP_LONG newTagLen)
{
    if (!id3v2Hdr)
        return MMP_FALSE;

    id3v2Hdr->size[0] = (newTagLen & 0x0FE00000) >> 21;
    id3v2Hdr->size[1] = (newTagLen & 0x001FC000) >> 14;
    id3v2Hdr->size[2] = (newTagLen & 0x00003F80) >> 7;
    id3v2Hdr->size[3] =  newTagLen & 0x0000007F;

    return MMP_TRUE;
}
#endif
//=========================================================================
//  Function    : MMPD_ID3_GetV2FrameHeader
//  Description : 
//=========================================================================
static MMP_BOOL MMPD_ID3_GetV2FrameHeader(MMP_UBYTE *id3v2Frame, MMP_UBYTE bVersion,
                                          MMP_ULONG ulSeekpos, MMP_LONG *lFrameLen)
{
    MMPD_ID3_V2_FRAME_HEADER    *id3v2FrameHdr;
    MMPD_ID3_V2_2_FRAME_HEADER  *id3v2_2FrameHdr;

    switch(bVersion) {
    case 0x03:
    case 0x04:
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(id3v2Frame, ulSeekpos, 10))
            return MMP_FALSE;

        id3v2FrameHdr = (MMPD_ID3_V2_FRAME_HEADER *)id3v2Frame;
        //The size is calculated as frame size excluding frame header
        if (bVersion == 0x03) {
            *lFrameLen = (id3v2FrameHdr->size[0] << 24) | (id3v2FrameHdr->size[1] << 16) |
                         (id3v2FrameHdr->size[2] << 8) | (id3v2FrameHdr->size[3]);
        }
        else {
            *lFrameLen = (id3v2FrameHdr->size[0] << 21) | (id3v2FrameHdr->size[1] << 14) |
                         (id3v2FrameHdr->size[2] << 7) | (id3v2FrameHdr->size[3]);
        }
        break;
    case 0x02:
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(id3v2Frame, ulSeekpos, 6))
            return MMP_FALSE;

        id3v2_2FrameHdr = (MMPD_ID3_V2_2_FRAME_HEADER *)id3v2Frame;
        //The size is calculated as frame size excluding frame header
        *lFrameLen = (id3v2_2FrameHdr->size[0] << 16) |
                      (id3v2_2FrameHdr->size[1] << 8) | (id3v2_2FrameHdr->size[2]);
        break;
    }

    return MMP_TRUE;
}

#if 0
//=========================================================================
//  Function    : MMPD_ID3_SetV2FrameHeader
//  Description : 
//=========================================================================
static MMP_BOOL MMPD_ID3_SetV2FrameHeader(MMPD_ID3_V2_FRAME_HEADER *id3v2Frame,
                                            void *frameType, void *frameLen)
{
    MMP_LONG i;
    MMP_BYTE *type = frameType;
    MMP_UBYTE *length = frameLen;

    if (!id3v2Frame) {
        return MMP_FALSE;
    }
    else {
        MEMSET(id3v2Frame, 0, sizeof(MMPD_ID3_V2_FRAME_HEADER));
    }

    //Convert byte order of frame type to Big endian
    for (i = sizeof(id3v2Frame->frame_id) - 1; i > -1; i--)
        id3v2Frame->frame_id[i] = *type++;

    //Convert byte order of frame length to Big endian
    for (i = sizeof(id3v2Frame->size) - 1; i > -1; i--)
        id3v2Frame->size[i] = *length++;

    return MMP_TRUE;
}
#endif

//=========================================================================
//  Function    : MMPD_ID3_GetV2FrameAPIC
//  Description : Get attached picture and save to dynamic allocated buffer
//=========================================================================
static MMP_BOOL MMPD_ID3_GetV2FrameAPIC(MMPD_ID3_V2_TAG *id3v2Tag, MMP_UBYTE bVersion,
                                        MMP_ULONG ulSeekpos, MMP_LONG lFrameLen, 
                                        AllocZeroMemCBFunc *CallBackFunc)
{
    MMP_BOOL ret = MMP_TRUE;
    MMP_UBYTE ubBuf, bEncMode, bPicType; //Description has a max length of 64 bytes

    //Text encoding (1 byte)
    if(MMP_ERR_NONE != MMPD_ID3_ReadFile(&bEncMode, ulSeekpos, 1))
        return MMP_FALSE;
    ulSeekpos++;
    lFrameLen--;

    if ((bVersion == 0x03)||(bVersion == 0x04)) {
        //MIME type
        do {
            if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos, 1))
                return MMP_FALSE;
            ulSeekpos++;
            lFrameLen--;
        } while (ubBuf);
    }
    else if (bVersion == 0x02) {
        //Image format: preferably "PNG" [PNG] or "JPG" [JFIF]
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos++, 1))
            return MMP_FALSE;
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos++, 1))
            return MMP_FALSE;
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos++, 1))
            return MMP_FALSE;
        lFrameLen -= 3;
    }

    //Picture type (1 byte)
    if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&bPicType, ulSeekpos, 1))
        return MMP_FALSE;
    ulSeekpos++;
    lFrameLen--;

    //Description
    do {
        if(MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos, 1))
            return MMP_FALSE;
        ulSeekpos++;
        lFrameLen--;
    } while (ubBuf);

    if ((bEncMode == MMPD_ID3_TEXT_UCS_2) || (bEncMode == MMPD_ID3_TEXT_UTF16_BE)) {
        if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubBuf, ulSeekpos, 1))
            return MMP_FALSE;
        ulSeekpos++;
        lFrameLen--;
    }

    //Picture data: store to dynamic allocated memory
    if (CallBackFunc) {
        if ((*CallBackFunc)(lFrameLen, (void **)&id3v2Tag->bApic)) //allocated memory to store APIC
        {
            //Larger cache for better performance
            if (m_ulID3UsedCacheSize < m_ulID3MaxCacheSize) {
                m_ulID3UsedCacheSize = m_ulID3MaxCacheSize;
                m_ulID3PreSeekPos = 0xFFFFFFFF;            //Reset cache
            }
            if(MMP_ERR_NONE != MMPD_ID3_ReadFile(id3v2Tag->bApic, ulSeekpos, lFrameLen)) {
                //MMPC_System_FreeMem((void **)&id3v2Tag->bApic);
                id3v2Tag->bApic = NULL;
                ret = MMP_FALSE;
            }
            id3v2Tag->ulApicSize = lFrameLen;
            //recover to original cache settings
            if (m_ulID3UsedCacheSize != m_ulID3CacheSize) {
                m_ulID3UsedCacheSize = m_ulID3CacheSize;
                m_ulID3PreSeekPos = 0xFFFFFFFF;
            }
        }
    }

    return ret;
}

//=========================================================================
//  Function    : MMPD_ID3_GetV2FramePOPM
//  Description : Get popularimeter (rating/play count)
//=========================================================================
static MMP_BOOL MMPD_ID3_GetV2FramePOPM(MMPD_ID3_V2_TAG *id3v2Tag, MMP_ULONG ulSeekpos, MMP_LONG lFrameLen)
{
    MMP_UBYTE ubChar;

    //Email to user
    do {
        if(MMP_ERR_NONE != MMPD_ID3_ReadFile(&ubChar, ulSeekpos, 1))
            return MMP_FALSE;
        ulSeekpos++;
        lFrameLen--;
    } while (ubChar);
    
    //Rating
    if (MMP_ERR_NONE != MMPD_ID3_ReadFile(&id3v2Tag->ubRating, ulSeekpos, 1))
            return MMP_FALSE;
    ulSeekpos++;
    lFrameLen--;

    //Play count (at least 32-bits long)
    if (lFrameLen < 4)
        return MMP_FALSE;

    if (MMP_ERR_NONE != MMPD_ID3_ReadFile(id3v2Tag->ubPlayCnt, ulSeekpos, lFrameLen))
        return MMP_FALSE;
    id3v2Tag->ulPlayCntSize = lFrameLen;

    return MMP_TRUE;
}

//=========================================================================
//  Function    : MMPD_ID3_Genre2String
//  Description : Mapping to string if genre is number
//=========================================================================
static void MMPD_ID3_Genre2String(MMP_BYTE *bGenre, MMP_ULONG ulFrameLen, MMPD_ID3_TEXT_ENC_MODE encMode)
{
    MMP_UBYTE ubGenreIdx = 0;
    MMP_UBYTE ubGenreNum = sizeof(m_bGenreStr)/sizeof(m_bGenreStr[0]);
    MMP_LONG  i, inc;

    //PRINTF("ubGenreNum = %d\r\n", ubGenreNum);
    //PRINTF("Genre = %s\r\n", bGenre+1);

    switch(encMode) {
    case MMPD_ID3_TEXT_ISO_8859_1:
    case MMPD_ID3_TEXT_UTF8:
        i = 1;
        inc = 1;
        break;
    case MMPD_ID3_TEXT_UTF16_LE:
        i = 2;
        inc = 2;
        break;
    case MMPD_ID3_TEXT_UTF16_BE:
        i = 3;
        inc = 2;
        break;
    default:
        PRINTF("ID3v2 TCON frame with invalid encode type\r\n");
        //invalid genre, set all zero
        MEMSET(bGenre, 0 , ulFrameLen);
        return;
    }
    if ((bGenre[0] == '(') || (bGenre[1] == '(')) {
        while((bGenre[i] != ')') && (i < ulFrameLen)) {
            if ((bGenre[i] < '0') || (bGenre[i] > '9')) {
                //invalid genre, set all zero
                MEMSET(bGenre, 0 , ulFrameLen);
                return;
            }
            else {
                ubGenreIdx = ubGenreIdx * 10 + (bGenre[i] - '0');
                if (ubGenreIdx >= ubGenreNum) {
                    //invalid genre, set all zero
                    MEMSET(bGenre, 0 , ulFrameLen);
                    return;
                }
            }
            i += inc;
        }
    }
    else {
        return;
    }

    switch(encMode) {
    case MMPD_ID3_TEXT_ISO_8859_1:
    case MMPD_ID3_TEXT_UTF8:
        i = 0;
        do {
            *bGenre = m_bGenreStr[ubGenreIdx][i++];
        } while(*bGenre++ != '\0');
        break;
    case MMPD_ID3_TEXT_UTF16_LE:
        strtoUCS(bGenre, m_bGenreStr[ubGenreIdx]);
        break;
    case MMPD_ID3_TEXT_UTF16_BE:
        strtoUCS(&bGenre[1], m_bGenreStr[ubGenreIdx]);
        break;
    }
}

//=========================================================================
//  Function    : MMPD_ID3_ReadString
//  Description : Support <text string according to encoding> only.
//                Terminated strings are terminated with 0x00 if encoded with 
//                ISO-8859-1/UTF-8 and 0x0000 if encoded as UTF-16/UTF-16BE.
//=========================================================================
static void MMPD_ID3_ReadString(MMP_ULONG ulSeekpos, MMP_BYTE *bStr, MMP_LONG lStrLen,
                                MMPD_ID3_TEXT_ENC_MODE *encMode)
{
    MMP_UBYTE ubBOM[2] = {0, };

    MMPD_ID3_ReadFile((MMP_UBYTE *)encMode, ulSeekpos, 1);
    ulSeekpos++;
    lStrLen--;

    if (*encMode == MMPD_ID3_TEXT_UCS_2) {
        MMPD_ID3_ReadFile(ubBOM, ulSeekpos, 2);
        if ((ubBOM[0] == 0xFF) && (ubBOM[1] == 0xFE))
            *encMode = MMPD_ID3_TEXT_UTF16_LE;
        else if ((ubBOM[0] == 0xFE) && (ubBOM[1] == 0xFF))
            *encMode = MMPD_ID3_TEXT_UTF16_BE;
        else {
            *encMode = MMPD_ID3_TEXT_UNKNOWN;
            bStr[0] = bStr[1] = 0;
            return;
        }
        ulSeekpos += 2;
        lStrLen -= 2;
    }

    MMPD_ID3_ReadFile((MMP_UBYTE *)bStr, ulSeekpos, lStrLen);
}

//=========================================================================
//  Function    : MMPD_ID3_FillStrTerminate
//  Description : Support <text string according to encoding> only.
//                Terminated strings are terminated with 0x00 if encoded with 
//                ISO-8859-1/UTF-8 and 0x0000 if encoded as UTF-16/UTF-16BE.
//=========================================================================
static void MMPD_ID3_FillStrTerminate(MMP_BYTE *bEncStr, MMP_LONG lStrBufLen, MMPD_ID3_TEXT_ENC_MODE encMode)
{
    switch(encMode) {
    case MMPD_ID3_TEXT_ISO_8859_1:
    case MMPD_ID3_TEXT_UTF8:
        bEncStr[lStrBufLen - 1] = 0;
        break;
    case MMPD_ID3_TEXT_UCS_2:
    case MMPD_ID3_TEXT_UTF16_BE:
    case MMPD_ID3_TEXT_UTF16_LE:
        bEncStr[lStrBufLen - 2] = bEncStr[lStrBufLen - 1] = 0;
        break;
    }
}

#if 0
//=========================================================================
//  Function    : MMPD_ID3_WriteFile
//  Description : 
//=========================================================================
static MMP_ERR MMPD_ID3_WriteFile(MMP_ULONG ulSeekpos, MMP_UBYTE *data, MMP_LONG length)
{
    MMP_ERR ret = MMP_ERR_NONE;
    MMP_ULONG sizeWrite;

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
        RETURN_IF_ERROR(ret);
        ret = MMPC_FS_FileWrite((void *)m_ulMP3fileID, data, length, &sizeWrite);
        RETURN_IF_ERROR(ret);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
        RETURN_IF_ERROR(ret);
        ret = MMPD_FS_FileWrite(m_ulMP3fileID, data, length, &sizeWrite);
        RETURN_IF_ERROR(ret);
        break;
    }

    return ret;
}
#endif

#if 0
//=========================================================================
//  Function    : MMPD_ID3_AddV2Frame
//  Description : 
//=========================================================================
static MMP_ERR MMPD_ID3_AddV2Frame(MMP_ULONG ulStartPos, MMP_UBYTE *header, MMP_LONG headerLen,
                                                           MMP_UBYTE *frame, MMP_LONG frameLen)
{
    MMP_ULONG ulBufAddr[2];
    MMP_ULONG ulBufSize;
    MMP_ULONG ulRemLen2Write;
    MMP_ULONG ulSizeRW;
    MMP_LONG  lReadPos, lWritePos;
    MMP_LONG  i;
    MMP_ERR   ret = MMP_ERR_NONE;

    //Larger cache for better performance to insert frame
    if (m_ulID3UsedCacheSize < m_ulID3MaxCacheSize) {
        m_ulID3UsedCacheSize = m_ulID3MaxCacheSize;
        m_ulID3PreSeekPos = 0xFFFFFFFF;            //Reset cache
    }

    if ((headerLen + frameLen) > (m_ulID3UsedCacheSize >> 1)) {
        PRINTF("Cache buffer is too small to shift file content!\r\n");
        return MMP_AUDIO_ERR_INSUFFICIENT_BUF;
    }

    PRINTF("Start postion: %X\r\n", ulStartPos);

    //Divide cache buffer into two temp buf for file shifting
    ulBufSize = m_ulID3UsedCacheSize >> 1;
    ulBufAddr[0] = m_ulID3CacheAddr;
    ulBufAddr[1] = m_ulID3CacheAddr + ulBufSize;

    MEMCPY((void *)ulBufAddr[0], header, headerLen);
    MEMCPY((void *)(ulBufAddr[0] + headerLen), frame, frameLen);

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileGetSize((void *)m_ulMP3fileID, &ulRemLen2Write);
        RETURN_IF_ERROR(ret);
        ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)ulStartPos, MMPD_FS_SEEK_SET);
        RETURN_IF_ERROR(ret);
        ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)(ulBufAddr[0] + headerLen + frameLen), 
                                m_ulID3UsedCacheSize - headerLen - frameLen, &ulSizeRW);
        RETURN_IF_ERROR(ret);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileGetSize(m_ulMP3fileID, &ulRemLen2Write);
        RETURN_IF_ERROR(ret);
        ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)ulStartPos, MMPD_FS_SEEK_SET);
        RETURN_IF_ERROR(ret);
        ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)(ulBufAddr[0] + headerLen + frameLen), 
                                m_ulID3UsedCacheSize - headerLen - frameLen, &ulSizeRW);
        RETURN_IF_ERROR(ret);
        break;
    }

    ulRemLen2Write = ulRemLen2Write - ulStartPos + headerLen + frameLen;
    lWritePos = ulStartPos;
    lReadPos = ulStartPos + ulSizeRW;

    while (ulRemLen2Write > 0) {
        for (i = 0; i < 2; i++) {
            switch(m_MediaPath) {
            case MMPD_AUDIO_PLAY_FROM_MEM:
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)lWritePos - lReadPos, MMPD_FS_SEEK_CUR);
                RETURN_IF_ERROR(ret);
                if (ulRemLen2Write > ulBufSize) {
                    ret = MMPC_FS_FileWrite((void *)m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulBufSize, &ulSizeRW);
                    RETURN_IF_ERROR(ret);
                    lWritePos += ulSizeRW;
                    if (ulRemLen2Write > m_ulID3UsedCacheSize) {
                        ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, (MMP_LONG64)lReadPos - lWritePos, MMPD_FS_SEEK_CUR);
                        RETURN_IF_ERROR(ret);
                        ret = MMPC_FS_FileRead((void *)m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulBufSize, &ulSizeRW);
                        RETURN_IF_ERROR(ret);
                        lReadPos += ulSizeRW;
                    }
                    else {
                        lReadPos = lWritePos; //set seek offset to zero
                    }
                }
                else {
                    //Shift finish
                    ret = MMPC_FS_FileWrite((void *)m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulRemLen2Write, &ulSizeRW);
                    return ret;
                }
                break;
            case MMPD_AUDIO_PLAY_FROM_CARD:
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)lWritePos - lReadPos, MMPD_FS_SEEK_CUR);
                RETURN_IF_ERROR(ret);
                if (ulRemLen2Write > ulBufSize) {
                    ret = MMPD_FS_FileWrite(m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulBufSize, &ulSizeRW);
                    RETURN_IF_ERROR(ret);
                    lWritePos += ulSizeRW;
                    if (ulRemLen2Write > m_ulID3UsedCacheSize) {
                        ret = MMPD_FS_FileSeek(m_ulMP3fileID, (MMP_LONG64)lReadPos - lWritePos, MMPD_FS_SEEK_CUR);
                        RETURN_IF_ERROR(ret);
                        ret = MMPD_FS_FileRead(m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulBufSize, &ulSizeRW);
                        RETURN_IF_ERROR(ret);
                        lReadPos += ulSizeRW;
                    }
                    else {
                        lReadPos = lWritePos; //set seek offset to zero
                    }
                }
                else {
                    //Shift finish
                    ret = MMPD_FS_FileWrite(m_ulMP3fileID, (MMP_UBYTE *)ulBufAddr[i], ulRemLen2Write, &ulSizeRW);
                    return ret;
                }
                break;
            }
            ulRemLen2Write -= ulBufSize;
        }
    }

    return MMP_ERR_NONE;
}
#endif
//=========================================================================
//  Function    : MMPD_ID3_GetInfo
//  Description : 
//=========================================================================
/** @brief Get the ID3 information from a MP3 file

@param[in] bFileName The input MP3 file name.
@param[in] ulNameLen The length of file name.
@param[out] id3info The ID3 structure.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_ID3_GetInfo(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFileID,
                         MMPD_ID3_INFO *id3info, MMP_ULONG ulSeekPos, AllocZeroMemCBFunc *CallBackFunc, MMPD_ID3_ReadFile_Func *ReadFileFunc)
{
    MMP_ERR                     ret = MMP_ERR_NONE;
    MMP_BOOL                    findAPIC = MMP_FALSE;
    MMP_BOOL                    findPOPM = MMP_FALSE; //for Adagio only, use the first POPM always
    MMP_ULONG                   frame_type;
    MMP_ULONG                   parsed_byte = ulSeekPos;//0;
    MMP_LONG                    tag_size = 0, frame_len = 0;
    MMP_UBYTE                   ubExtHdr[4];
    MMP_UBYTE                   *pId3v2HdrPtr;
    MMPD_ID3_V2_TAG             *pId3v2Tag;
    MMPD_ID3_V2_TAG_HEADER      id3v2TagHdr;
    MMPD_ID3_V2_FRAME_HEADER    id3v2FrameHdr;
    MMPD_ID3_V2_2_FRAME_HEADER  id3v2_2FrameHdr;

    if (ulNameLen != 0) {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
        	ret = MMPC_FS_FileOpen(bFileName, "rb", (void **)&m_ulMP3fileID);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
        	ret = MMPD_FS_FileOpen(bFileName, ulNameLen, "rb", sizeof("rb"), &m_ulMP3fileID);
            break;
        default:
            ret = MMP_AUDIO_ERR_COMMAND_INVALID;
        }
    }
	else {
        if (ulFileID != 0) {
            m_ulMP3fileID = ulFileID;
            switch(m_MediaPath) {
            case MMPD_AUDIO_PLAY_FROM_MEM:
                ret = MMPC_FS_FileSeek((void *)m_ulMP3fileID, 0, MMPD_FS_SEEK_SET);
                break;
            case MMPD_AUDIO_PLAY_FROM_CARD:
                ret = MMPD_FS_FileSeek(m_ulMP3fileID, 0, MMPD_FS_SEEK_SET);
                break;
            default:
                ret = MMP_AUDIO_ERR_COMMAND_INVALID;
            }
        }
        else if (ReadFileFunc == NULL) {
            PRINTF("Invalid file ID!\r\n");
            ret =  MMP_AUDIO_ERR_OPENFILE_FAIL;
        }
	}

    if (ReadFileFunc == NULL) {
        MMPD_ID3_ReadFile = MMPD_ID3_ReadFileData;
    }
    else {
        MMPD_ID3_ReadFile = ReadFileFunc;
    }

    if (ret != MMP_ERR_NONE) {
        m_ulID3CacheAddr = 0; //Reset
        return ret;
    }

    m_ulID3PreSeekPos = 0xFFFFFFFF;

    if (MMPD_ID3_GetV2TagHeader(&id3v2TagHdr, &tag_size, parsed_byte)) {
        id3info->flag = ID3_V2_IN_AUDIO;
        id3info->sub_version = (id3v2TagHdr.ver << 8) | id3v2TagHdr.rev;
    }
    else {
        //PRINTF("No ID3v2 tag\r\n");
        goto CHECK_ID3_V1;
    }

    //PRINTF("ID3v2.%d.%d tag (length=0X%X) found\r\n", id3v2TagHdr.ver, id3v2TagHdr.rev, tag_size);
    parsed_byte += 10; //ID3v2 tag header is 10 bytes

    switch(id3v2TagHdr.ver) {
    case 0x02:
        if (id3v2TagHdr.flag & 0x3F) {
            id3info->flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2_2FrameHdr;
        break;
    case 0x03:
        if (id3v2TagHdr.flag & 0x1F) {
            id3info->flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        else {
            if (id3v2TagHdr.flag & 0x40) { //contains extended header
                parsed_byte += 10; //just skip extended header presently
            }
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2FrameHdr;
        break;
    case 0x04:
        if (id3v2TagHdr.flag & 0x0F) {
            id3info->flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        else {
            if (id3v2TagHdr.flag & 0x40) { //contains extended header
                MMPD_ID3_ReadFile(ubExtHdr, parsed_byte, 4);
                //just skip extended header presently
                parsed_byte += ((ubExtHdr[0] << 21) | (ubExtHdr[1] << 14) | 
                                (ubExtHdr[2] << 7)  | (ubExtHdr[3]));
            }
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2FrameHdr;
        break;
    default:
        id3info->flag = ID3_NONE_IN_AUDIO;
    }

    if (!(id3info->flag & ID3_V2_IN_AUDIO)) {
        PRINTF("Unsupport ID3v2 version!\r\n");
        goto CHECK_ID3_V1;
    }

    pId3v2Tag = &id3info->id3v2Tag;
    pId3v2Tag->ulPaddingSize = tag_size;

    while(1) {
        if (MMPD_ID3_GetV2FrameHeader(pId3v2HdrPtr, id3v2TagHdr.ver, parsed_byte, &frame_len)) {
            switch(id3v2TagHdr.ver) {
            case 0x03:
            case 0x04:
                frame_type = id3v2FrameHdr.frame_id[0] << 24 | id3v2FrameHdr.frame_id[1] << 16 |
                              id3v2FrameHdr.frame_id[2] << 8 | id3v2FrameHdr.frame_id[3];
                parsed_byte += 10;
                break;
            case 0x02:
                frame_type = id3v2_2FrameHdr.frame_id[0] << 16 |
                              id3v2_2FrameHdr.frame_id[1] << 8 | id3v2_2FrameHdr.frame_id[2];
                parsed_byte += 6;
                break;
            }

            switch(frame_type) {
            case MMPD_ID3_FRAME_APIC:
            case MMPD_ID3_FRAME_PIC:
                if ((id3info->metaType & MMPD_ID3_META_APIC) && !findAPIC) {
                    MMPD_ID3_GetV2FrameAPIC(pId3v2Tag, id3v2TagHdr.ver, parsed_byte, frame_len, CallBackFunc);
                    findAPIC = MMP_TRUE;
                }
                break;
            case MMPD_ID3_FRAME_POPM:
            case MMPD_ID3_FRAME_POP:
                // For Adagio only, just always use the first POPM with 4 bytes play count
                if (((id3info->metaType & MMPD_ID3_META_RATING) || 
                    (id3info->metaType & MMPD_ID3_META_PCOUNT)) && !findPOPM) {
                    MMPD_ID3_GetV2FramePOPM(pId3v2Tag, parsed_byte, frame_len);
                    if (pId3v2Tag->ulPlayCntSize == 4)
                        findPOPM = MMP_TRUE;
                }
                break;
            case MMPD_ID3_FRAME_TALB:
            case MMPD_ID3_FRAME_TAL:
                if (id3info->metaType & MMPD_ID3_META_ALBUM) {
                    if (frame_len <= sizeof(pId3v2Tag->bAlbum)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bAlbum,
                                            frame_len, &pId3v2Tag->albumEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bAlbum,
                                            sizeof(pId3v2Tag->bAlbum) - 1, &pId3v2Tag->albumEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bAlbum, sizeof(pId3v2Tag->bAlbum),
                                            pId3v2Tag->albumEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TCOM:
            case MMPD_ID3_FRAME_TCM:
                if (id3info->metaType & MMPD_ID3_META_AUTHOR) {
                    if (frame_len <= sizeof(pId3v2Tag->bComposer)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bComposer,
                                            frame_len, &pId3v2Tag->composerEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bComposer,
                                            sizeof(pId3v2Tag->bComposer) - 1, &pId3v2Tag->composerEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bComposer, sizeof(pId3v2Tag->bComposer),
                                            pId3v2Tag->composerEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TCON:
            case MMPD_ID3_FRAME_TCO:
                if (id3info->metaType & MMPD_ID3_META_GENRE) {
                    if (frame_len <= sizeof(pId3v2Tag->bGenre)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bGenre,
                                            frame_len, &pId3v2Tag->genreEncMode);
                        MMPD_ID3_Genre2String(pId3v2Tag->bGenre, frame_len,
                                            pId3v2Tag->genreEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bGenre,
                                            sizeof(pId3v2Tag->bGenre) - 1, &pId3v2Tag->genreEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bGenre, sizeof(pId3v2Tag->bGenre),
                                            pId3v2Tag->genreEncMode);
                        MMPD_ID3_Genre2String(pId3v2Tag->bGenre, sizeof(pId3v2Tag->bGenre),
                                            pId3v2Tag->genreEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TCOP:
            case MMPD_ID3_FRAME_TCR:
                if (id3info->metaType & MMPD_ID3_META_COPYRIGHT) {
                    if (frame_len <= sizeof(pId3v2Tag->bCopyright)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bCopyright,
                                            frame_len, &pId3v2Tag->copyrightEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bCopyright,
                                            sizeof(pId3v2Tag->bCopyright) - 1, &pId3v2Tag->copyrightEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bCopyright, sizeof(pId3v2Tag->bCopyright),
                                            pId3v2Tag->copyrightEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TIT1:
            case MMPD_ID3_FRAME_TT1:
                if (id3info->metaType & MMPD_ID3_META_DESCRIPTION) {
                    if (frame_len <= sizeof(pId3v2Tag->bDescription)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bDescription,
                                            frame_len, &pId3v2Tag->descriptionEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bDescription,
                                            sizeof(pId3v2Tag->bDescription) - 1, &pId3v2Tag->descriptionEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bDescription, sizeof(pId3v2Tag->bDescription),
                                            pId3v2Tag->descriptionEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TIT2:
            case MMPD_ID3_FRAME_TT2:
                if (id3info->metaType & MMPD_ID3_META_TITLE) {
                    if (frame_len <= sizeof(pId3v2Tag->bTitle)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bTitle,
                                            frame_len, &pId3v2Tag->titleEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bTitle,
                                            sizeof(pId3v2Tag->bTitle) - 1, &pId3v2Tag->titleEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bTitle, sizeof(pId3v2Tag->bTitle),
                                            pId3v2Tag->titleEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TPE1:
            case MMPD_ID3_FRAME_TP1:
                if (id3info->metaType & MMPD_ID3_META_ARTIST) {
                    if (frame_len <= sizeof(pId3v2Tag->bArtist)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bArtist,
                                            frame_len, &pId3v2Tag->artistEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bArtist,
                                            sizeof(pId3v2Tag->bArtist) - 1, &pId3v2Tag->artistEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bArtist, sizeof(pId3v2Tag->bArtist),
                                            pId3v2Tag->artistEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TRCK:
            case MMPD_ID3_FRAME_TRK:
                if (id3info->metaType & MMPD_ID3_META_TRACKNUM) {
                    if (frame_len <= sizeof(pId3v2Tag->bTrack)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bTrack,
                                            frame_len, &pId3v2Tag->trackEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bTrack,
                                            sizeof(pId3v2Tag->bTrack) - 1, &pId3v2Tag->trackEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bTrack, sizeof(pId3v2Tag->bTrack),
                                            pId3v2Tag->trackEncMode);
                    }
                }
                break;
            case MMPD_ID3_FRAME_TDRC:
            case MMPD_ID3_FRAME_TYER:
            case MMPD_ID3_FRAME_TYE:
                if (id3info->metaType & MMPD_ID3_META_YEAR) {
                    if (frame_len <= sizeof(pId3v2Tag->bYear)) {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bYear,
                                            frame_len, &pId3v2Tag->yearEncMode);
                    }
                    else {
                        MMPD_ID3_ReadString(parsed_byte, pId3v2Tag->bYear,
                                            sizeof(pId3v2Tag->bYear) - 1, &pId3v2Tag->yearEncMode);
                        MMPD_ID3_FillStrTerminate(pId3v2Tag->bYear, sizeof(pId3v2Tag->bYear),
                                            pId3v2Tag->yearEncMode);
                    }
                }
                break;
            default:
                if ((frame_type == 0) && (frame_len == 0)) //padding
                    goto CHECK_ID3_V1;
            }

            parsed_byte += frame_len;

            if ((parsed_byte - ulSeekPos) >= (tag_size + 10)) {
                break;
            }
            else {
                pId3v2Tag->ulPaddingSize -= (sizeof(id3v2FrameHdr) + frame_len);
            }
        }
        else {
            break;
        }
    }

CHECK_ID3_V1:
    #if 0
    //Alterman@20100117: search ID3v1 only when ID3v2 is not exist
    if (!(id3info->flag & ID3_V2_IN_AUDIO)) {
        if (MMPD_ID3_GetV1Tag((MMP_UBYTE *)&(id3info->id3v1Tag))) {
            //PRINTF("ID3v1 tag found\r\n");
        id3info->flag |= ID3_V1_IN_AUDIO;
    }
    }
    #endif

	if (ulNameLen != 0) {
	    switch(m_MediaPath) {
    	case MMPD_AUDIO_PLAY_FROM_MEM:
        	MMPC_FS_FileClose((void *)m_ulMP3fileID);
	        break;
    	case MMPD_AUDIO_PLAY_FROM_CARD:
        	MMPD_FS_FileClose(m_ulMP3fileID);
	        break;
    	}
	}
	m_ulID3CacheAddr = 0; //Reset

    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_ID3_GetInfo
//  Description : 
//=========================================================================
/** @brief Get the ID3 information from a MP3 file

@param[in] bFileName The input MP3 file name.
@param[in] ulNameLen The length of file name.
@param[out] id3info The ID3 structure.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_ID3_EditTag(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, 
                        MMPD_ID3_FRAME_ID frameType, MMP_UBYTE *payload, MMP_LONG payloadLen)
{
    MMP_ERR ret = MMP_ERR_NONE;
#if 0
    MMP_ULONG frame_type;
    MMP_LONG parsed_byte, tag_size, frame_len;
    MMPD_ID3_V2_TAG id3v2Tag;
    MMPD_ID3_V2_TAG_HEADER   id3v2TagHdr;
    MMPD_ID3_V2_FRAME_HEADER id3v2FrameHdr;
    MMP_LONG paddingStartOffset = 0; //the file position of padding
    MMP_LONG paddingSize = 0; //the size of padding in the end of tag
    MEMSET(&id3v2TagHdr, 0,sizeof(id3v2TagHdr));
    MEMSET(&id3v2FrameHdr, 0,sizeof(id3v2FrameHdr));

    parsed_byte = 0;
    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileOpen(bFileName, "a+", (void **)&m_ulMP3fileID);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileOpen(bFileName, ulNameLen, "a+", sizeof("a+"), &m_ulMP3fileID);
        break;
    default:
        ret = MMP_AUDIO_ERR_COMMAND_INVALID;
    }

    if (ret != MMP_ERR_NONE) {
        m_ulID3CacheAddr = 0; //Reset
        return ret;
    }

    m_ulID3PreSeekPos = 0xFFFFFFFF;
    if (MMPD_ID3_GetV2TagHeader(&id3v2TagHdr, &tag_size, parsed_byte) != MMP_TRUE) {
        #if 0
        MMP_UBYTE tmpBuf[20];
        #endif

        //case 5: No v2 tag, create v2 tag, add frame and shift file content
        PRINTF("No ID3v2 tag!\r\n");
        //Alterman@090304: Prevent long time for set meta data, just return fail
        #if 0
        id3v2TagHdr.header[0] = 'I';
        id3v2TagHdr.header[1] = 'D';
        id3v2TagHdr.header[2] = '3';
        id3v2TagHdr.ver = 0x03;
        id3v2TagHdr.rev = 0x00;
        id3v2TagHdr.flag = 0x00;
        tag_size = sizeof(MMPD_ID3_V2_FRAME_HEADER) + payloadLen;
        MMPD_ID3_SetV2TagLength(&id3v2TagHdr, tag_size);
        MMPD_ID3_SetV2FrameHeader(&id3v2FrameHdr, &frameType, &payloadLen);
        MEMCPY(tmpBuf, &id3v2TagHdr, sizeof(id3v2TagHdr));
        MEMCPY(tmpBuf + sizeof(id3v2TagHdr), &id3v2FrameHdr, sizeof(id3v2FrameHdr));

        ret = MMPD_ID3_AddV2Frame(0, tmpBuf, sizeof(tmpBuf), payload, payloadLen);
        #else
        ret = MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        #endif
        goto EDIT_TAG_EXIT;
    }

    if ((id3v2TagHdr.ver != 0x03) || (id3v2TagHdr.flag & 0x1F)) {
        PRINTF("Only ID3v2.3 tag supported\r\n");
        ret = MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        goto EDIT_TAG_EXIT;
    }
    parsed_byte = 10; //ID3v2 header is 10 bytes

    if (id3v2TagHdr.flag & 0x40) { //contains extended header
        parsed_byte += 10; //just skip extended header presently
    }

    paddingSize = tag_size;

    while(1) {
        if (MMPD_ID3_GetV2FrameHeader(&id3v2FrameHdr, id3v2TagHdr.ver, parsed_byte, &frame_len)) {
            parsed_byte += 10;

            frame_type = id3v2FrameHdr.frame_id[0] << 24 | id3v2FrameHdr.frame_id[1] << 16 |
                          id3v2FrameHdr.frame_id[2] << 8 | id3v2FrameHdr.frame_id[3];

            switch(frame_type) {
            case MMPD_ID3_FRAME_POPM:
                // For Adagio only, just always use the first POPM with 4 bytes play count
                MMPD_ID3_GetV2FramePOPM(&id3v2Tag, parsed_byte, frame_len);
                if (id3v2Tag.ulPlayCntSize == 4) {
                    //Case 1: Update POPM frame rating/play count
                    if (payloadLen > frame_len)
                    {
                        ret = MMP_AUDIO_ERR_PARAMETER;
                        goto EDIT_TAG_EXIT;                        
                    }
                    ret = MMPD_ID3_WriteFile(parsed_byte + frame_len - payloadLen, payload, payloadLen);
                    goto EDIT_TAG_EXIT;
                }
                break;
            }

            if (id3v2FrameHdr.frame_id[0] == 0) {
                paddingStartOffset = parsed_byte - 10;
                break;
            }

            if (parsed_byte >= tag_size + 10) {
                parsed_byte -= 10;
                break;
            }
            else {
                paddingSize -= (sizeof(id3v2FrameHdr) + frame_len);
                parsed_byte += frame_len;
            }
        }
        else {
            PRINTF("Get ID3v2 frame failed\r\n");
            goto EDIT_TAG_EXIT;
        }
    }

    if ((paddingStartOffset != 0) && (paddingSize != 0)) {
        MMPD_ID3_SetV2FrameHeader(&id3v2FrameHdr, &frameType, &payloadLen);
        if (paddingSize >= (sizeof(id3v2FrameHdr) + payloadLen)) {
            //Case 2: Replace padding with frame
            ret = MMPD_ID3_WriteFile(paddingStartOffset, (MMP_UBYTE *)&id3v2FrameHdr, sizeof(id3v2FrameHdr)); //Header
            if (MMP_ERR_NONE != ret)
                goto EDIT_TAG_EXIT;
            ret = MMPD_ID3_WriteFile(paddingStartOffset + sizeof(id3v2FrameHdr), payload, payloadLen);        //Payload
            if (MMP_ERR_NONE != ret)
                goto EDIT_TAG_EXIT;
        }
        else {
            //Case 3: No enough padding to replace, add frame and shift file content
            //Alterman@090304: Prevent long time for set meta data, just return fail
            PRINTF("No enough ID3v2 tag padding for insert POPM frame!\r\n");
            #if 0
            tag_size += (sizeof(MMPD_ID3_V2_FRAME_HEADER) + payloadLen - paddingSize);
            MMPD_ID3_SetV2TagLength(&id3v2TagHdr, tag_size);
            ret = MMPD_ID3_WriteFile(0, (MMP_UBYTE *)&id3v2TagHdr, sizeof(id3v2TagHdr)); //Update tag header
            if (MMP_ERR_NONE != ret)
                goto EDIT_TAG_EXIT;
            MMPD_ID3_SetV2FrameHeader(&id3v2FrameHdr, &frameType, &payloadLen);
            if (paddingSize <= sizeof(id3v2FrameHdr)) {
                ret = MMPD_ID3_WriteFile(paddingStartOffset, (MMP_UBYTE *)&id3v2FrameHdr, paddingSize); //Replace with partial frame header
                if (MMP_ERR_NONE != ret)
                    goto EDIT_TAG_EXIT;
                ret = MMPD_ID3_AddV2Frame(paddingStartOffset + paddingSize, (MMP_UBYTE *)&id3v2FrameHdr + paddingSize, 
                                    sizeof(id3v2FrameHdr) - paddingSize, payload, payloadLen);
            }
            else {
                MMPD_ID3_WriteFile(paddingStartOffset, (MMP_UBYTE *)&id3v2FrameHdr, sizeof(id3v2FrameHdr)); //Replace with frame header
                if (MMP_ERR_NONE != ret)
                    goto EDIT_TAG_EXIT;
                paddingSize -= sizeof(id3v2FrameHdr);
                ret = MMPD_ID3_WriteFile(paddingStartOffset + sizeof(id3v2FrameHdr), payload, paddingSize); //Replace with partial frame payload
                if (MMP_ERR_NONE != ret)
                    goto EDIT_TAG_EXIT;
                ret = MMPD_ID3_AddV2Frame(paddingStartOffset + paddingSize, NULL, 0, payload + paddingSize, payloadLen - paddingSize);
            }
            #else
            ret = MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
            #endif
        }
    }
    else {
        //Case 4: No padding, add frame and shift file content
        //Alterman@090304: Prevent long time for set meta data, just return fail
        PRINTF("No ID3v2 tag padding for insert POPM frame!\r\n");
        #if 0
        tag_size += sizeof(MMPD_ID3_V2_FRAME_HEADER) + payloadLen;
        MMPD_ID3_SetV2TagLength(&id3v2TagHdr, tag_size);
        ret = MMPD_ID3_WriteFile(0, (MMP_UBYTE *)&id3v2TagHdr, sizeof(id3v2TagHdr)); //Update tag header
        if (MMP_ERR_NONE != ret)
            goto EDIT_TAG_EXIT;
        MMPD_ID3_SetV2FrameHeader(&id3v2FrameHdr, &frameType, &payloadLen);
        ret = MMPD_ID3_AddV2Frame(parsed_byte, (MMP_UBYTE *)&id3v2FrameHdr, sizeof(id3v2FrameHdr), payload, payloadLen);
        #else
        ret = MMP_AUDIO_ERR_UNSUPPORT_FORMAT;
        #endif
    }

EDIT_TAG_EXIT:
    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        MMPC_FS_FileClose((void *)m_ulMP3fileID);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        MMPD_FS_FileClose(m_ulMP3fileID);
        break;
    }
    m_ulID3CacheAddr = 0; //Reset
#endif
    return ret;
}

//=========================================================================
//  Function    : MMPD_ID3_CheckFrameExist
//  Description : 
//=========================================================================
/** @brief Check if the specified frame exists or not in ID3v2 tag

@param[in] bFileName The input MP3 file name.
@param[in] ulNameLen The length of file name.
@param[in] ubPath The path of media source.
@param[out] bExist The frame exists or not in ID3v2 tag
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_ID3_CheckFrameExist(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFrame,
                                 MMPD_AUDIO_PLAY_DATAPATH ubPath, MMP_BOOL *bExist)
{
    #if (MP3HD_DEC_EN == 1)
    MMP_ERR                     ret = MMP_ERR_NONE;
    MMP_USHORT                  flag;
    MMP_ULONG                   frame_type;
    MMP_ULONG                   parsed_byte = 0;
    MMP_LONG                    tag_size = 0, frame_len = 0;
    MMP_UBYTE                   ubExtHdr[4];
    MMP_UBYTE                   *pId3v2HdrPtr;
    MMPD_ID3_V2_TAG             Id3v2Tag;
    MMPD_ID3_V2_TAG             *pId3v2Tag;
    MMPD_ID3_V2_TAG_HEADER      id3v2TagHdr;
    MMPD_ID3_V2_FRAME_HEADER    id3v2FrameHdr;
    MMPD_ID3_V2_2_FRAME_HEADER  id3v2_2FrameHdr;
    #endif

    *bExist = MMP_FALSE;

    #if (MP3HD_DEC_EN == 1)
    if (!m_ulID3CacheAddr || !m_ulID3CacheSize || !m_ulID3MaxCacheSize) {
        PRINTF("Please call MMPS_AUDIO_SetMP3PlayID3CacheBuf to set cache first!\r\n");
        return MMP_AUDIO_ERR_INVALID_FLOW;
    }

    if ((bFileName != NULL) && (ulNameLen != 0)) {
        switch(ubPath) {
        case MMPD_AUDIO_PLAY_FROM_CARD:
        	ret = MMPD_FS_FileOpen(bFileName, ulNameLen, "rb", sizeof("rb"), &m_ulMP3fileID);
            break;
        case MMPD_AUDIO_PLAY_FROM_MEM:
        case MMPD_AUDIO_PLAY_FROM_MMP_MEM:
        default:
            ret = MMP_AUDIO_ERR_COMMAND_INVALID;
        }
    }
	else {
        ret = MMP_AUDIO_ERR_OPENFILE_FAIL;
	}

    MMPD_ID3_ReadFile = MMPD_ID3_ReadFileData;
	m_ulID3PreSeekPos = 0xFFFFFFFF;
	
	if (ret != MMP_ERR_NONE) {
        m_ulID3CacheAddr = 0; //Reset
        return ret;
    }

    if (MMPD_ID3_GetV2TagHeader(&id3v2TagHdr, &tag_size, parsed_byte) == MMP_FALSE) {
        PRINTF("No ID3v2 tag\r\n");
        goto ID3_EXIT;
    }
    
    PRINTF("ID3 tag size = 0x%X\r\n", tag_size + 10);

    flag = ID3_V2_IN_AUDIO;
    parsed_byte += 10; //ID3v2 tag header is 10 bytes

    switch(id3v2TagHdr.ver) {
    case 0x02:
        if (id3v2TagHdr.flag & 0x3F) {
            flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2_2FrameHdr;
        break;
    case 0x03:
        if (id3v2TagHdr.flag & 0x1F) {
            flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        else {
            if (id3v2TagHdr.flag & 0x40) { //contains extended header
                parsed_byte += 10; //just skip extended header presently
            }
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2FrameHdr;
        break;
    case 0x04:
        if (id3v2TagHdr.flag & 0x0F) {
            flag = ID3_NONE_IN_AUDIO; //invaild flag
        }
        else {
            if (id3v2TagHdr.flag & 0x40) { //contains extended header
                MMPD_ID3_ReadFile(ubExtHdr, parsed_byte, 4);
                //just skip extended header presently
                parsed_byte += ((ubExtHdr[0] << 21) | (ubExtHdr[1] << 14) | 
                                (ubExtHdr[2] << 7)  | (ubExtHdr[3]));
            }
        }
        pId3v2HdrPtr = (MMP_UBYTE *)&id3v2FrameHdr;
        break;
    default:
        flag = ID3_NONE_IN_AUDIO;
    }

    if (!(flag & ID3_V2_IN_AUDIO)) {
        PRINTF("Unsupport ID3v2 version!\r\n");
        goto ID3_EXIT;
    }

    pId3v2Tag = &Id3v2Tag;
    pId3v2Tag->ulPaddingSize = tag_size;

    while(1) {
        if (MMPD_ID3_GetV2FrameHeader(pId3v2HdrPtr, id3v2TagHdr.ver, parsed_byte, &frame_len)) {
            switch(id3v2TagHdr.ver) {
            case 0x03:
            case 0x04:
                frame_type = id3v2FrameHdr.frame_id[0] << 24 | id3v2FrameHdr.frame_id[1] << 16 |
                             id3v2FrameHdr.frame_id[2] << 8 | id3v2FrameHdr.frame_id[3];
                parsed_byte += 10;
                break;
            case 0x02:
                frame_type = id3v2_2FrameHdr.frame_id[0] << 16 |
                              id3v2_2FrameHdr.frame_id[1] << 8 | id3v2_2FrameHdr.frame_id[2];
                parsed_byte += 6;
                break;
            }

            if (frame_type == ulFrame) {
                PRINTF("ID3 frame found\r\n");
                *bExist = MMP_TRUE;
                break;
            }

            if ((frame_type == 0) && (frame_len == 0)) //padding
                goto ID3_EXIT;

            parsed_byte += frame_len;

            if (parsed_byte >= (tag_size + 10))
                break;
            else
                pId3v2Tag->ulPaddingSize -= (sizeof(id3v2FrameHdr) + frame_len);
        }
        else {
            break;
        }
    }

ID3_EXIT:
    switch(ubPath) {
	case MMPD_AUDIO_PLAY_FROM_CARD:
    	MMPD_FS_FileClose(m_ulMP3fileID);
        break;
	}
	m_ulID3CacheAddr = 0; //Reset
	#endif

    return MMP_ERR_NONE;
}

/// @}
/// @end_ait_only

