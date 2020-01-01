/// @ait_only
//==============================================================================
//
//  File        : mmpd_audioDB.c
//  Description : audio database function
//  Author      : Will Chen
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_audioDB.c
*  @brief The audio database functions
*  @author Will Chen
*  @version 1.0
*/

//#include "ait_utility.h"
#include "mmpd_fs.h"
#include "mmpd_audiodb.h"

#if (AUDIO_HOST_DB_EN == 1)
#define END_OF_LGE_MM_DRIVE_TABLE "end"
MMP_BYTE  m_Subname[13][5] = 
{
    "MP3", 
    "AMR", 
    "AAC",
    "WMA",
    "OGG",    	
    "RM",
    "RMVB",
    "RA",
    "3GP",
    "MP4",
    "WAV",
    "MID", //jkcha test
    END_OF_LGE_MM_DRIVE_TABLE
};

                                    
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
/*static MMP_ULONG    m_ulNameDBID;
static MMP_ULONG    m_ulNameDBPreSeekPos;
static MMP_ULONG    m_ulNameDBCacheAddr;
static MMP_ULONG    m_ulNameDBCacheSize;
static MMP_ULONG	m_ulNameDBSize;

static MMP_ULONG    m_ulInfoDBID;
static MMP_ULONG    m_ulInfoDBPreSeekPos;
static MMP_ULONG    m_ulInfoDBCacheAddr;
static MMP_ULONG    m_ulInfoDBCacheSize;
static MMP_ULONG	m_ulInfoDBSize;
*/
static MMP_ULONG    m_ulDataBaseFileID;
static MMP_ULONG    m_ulAudioDBPreSeekPos;
static MMP_ULONG    m_ulAudioDBCacheAddr;
static MMP_ULONG    m_ulAudioDBCacheSize;
static MMP_ULONG64	m_ulDataBaseFileSize;
static MMPD_AUDIO_PLAY_DATAPATH m_MediaPath;

static	MMP_ULONG   m_ulAudioDBWriteFileID;
static	MMP_ULONG 	m_ulAudioDBWriteCacheAddr;
static	MMP_ULONG 	m_ulAudioDBWriteCacheCurPtr;
static	MMP_ULONG 	m_ulAudioDBWriteCacheSize;

static  MMP_UBYTE   *m_ubMallocPtrCur;
static  MMP_UBYTE   *m_ubDBMallocMem;
static  MMP_ULONG   m_ulDBMallocMemSize;

static	MMP_ULONG 	m_ulBTreeStart, m_ulBTreeEnd;
static	MMP_ULONG	m_ulBTreeCurrentCount;
static	MMPD_AUDIODB_BTACTION *m_action;
static	MMPD_AUDIODB_BTNODE	**m_returnTreeNodeLocator;

static	MMP_ULONG	m_ulBForestStart, m_ulBForestEnd;
static	MMP_ULONG	m_ulBForestCurrentCount = 0;
static	MMPD_AUDIODB_BFACTION *m_bforestaction;
static	MMPD_AUDIODB_BFNODE	**m_returnForestNodeLocator;

static  MMPD_AUDIODB_OBJECT_PROPERTY m_groupIndex;
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (FS_INPUT_ENCODE == UCS2)
void print_ucs2(MMP_BYTE *note, MMP_BYTE* wstr)
{
    PRINTF("[UCS2]%s: ", note);
    if (wstr[1]) {
		PRINTF("%2x %2x %2x %2x\r\n", (MMP_UBYTE)wstr[0], (MMP_UBYTE)wstr[1], (MMP_UBYTE)wstr[2], (MMP_UBYTE)wstr[3]);
    }
    else {
		for (; *(MMP_USHORT*)wstr!=0x0000; wstr+=2) {
		    PRINTF("%c", *wstr);
		}	    
		PRINTF("\n");
	}		
}

static MMP_ERR strcpy_w(MMP_BYTE *dst, MMP_BYTE *src)
{
	MMP_USHORT *s1 = (MMP_USHORT*)src;
	MMP_USHORT *d1 = (MMP_USHORT*)dst;

    for(; *s1 != 0; ) {
        *d1++ = *s1++;
    }
    *d1 = 0;

    return MMP_ERR_NONE;
}
static MMP_LONG strcmp_w(MMP_BYTE *str1, MMP_BYTE *str2)
{
	MMP_USHORT *s1 = (MMP_USHORT*)str1;
	MMP_USHORT *s2 = (MMP_USHORT*)str2;

    while (*s1 == *s2) {
        if(*s1 == 0)
            return 0;
        s1++;
        s2++;
    }
    return (MMP_LONG)*s1 - (MMP_LONG)*s2;
}
#endif

void *AUDIODB_MALLOC(MMP_ULONG size)
{
    MMP_UBYTE *ptr;

    ptr = m_ubMallocPtrCur;
    m_ubMallocPtrCur += size;
    if (m_ubMallocPtrCur > (m_ubDBMallocMem + m_ulDBMallocMemSize)) {
        PRINTF("AUDIODB_MALLOC fails\r\n");
        return NULL;
    }
    return  ptr;
}

void AUDIODB_FREE(void * ptr)
{
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIODB_MemAlloc
//  Description : Allocate a large memory that is used for pieces memory
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIODB_MemAlloc(void)
{
    if (m_ulDBMallocMemSize != 0) {
    	//already malloc	
    	return MMP_ERR_NONE;
	}    	
    #if 0 //Adagio
    m_ulDBMallocMemSize = (MAXFILESUPPORT*sizeof(MMPD_AUDIODB_BTNODE))+
                        (2*MAXFILESUPPORT*sizeof(MMPD_AUDIODB_BTNODE));
    PRINTF("Total memory allocated for DB = %d\r\n", m_ulDBMallocMemSize);
    if (MMPC_System_AllocZeroMem(m_ulDBMallocMemSize, (void **)&m_ubDBMallocMem) == MMP_FALSE) {
        m_ulDBMallocMemSize = 0;
        return MMP_SYSTEM_ERR_MALLOC;
    }
    #else //Demokit
    m_ulDBMallocMemSize = 0x3100000 - 0x3010000;
    m_ubDBMallocMem =(MMP_UBYTE *)0x3010000;
    #endif

    m_ubMallocPtrCur = m_ubDBMallocMem;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIODB_MemFree
//  Description : Free the large memory that is used for pieces memory
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIODB_MemFree(void)
{
	#if 0 //Adagio
    MMPC_System_FreeMem((void **)&m_ubDBMallocMem);
    #else
    #endif
    m_ulDBMallocMemSize = 0;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIODB_SetMediaPath
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_AUDIODB_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath)
{
    m_MediaPath = mediapath;

    return  MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIODB_SetParseCacheBuf
//  Description : 
//------------------------------------------------------------------------------
/** @brief Set the cache address and cache size for parsing AUDIODB

@param[in] ulCacheAddr The address of cache dedicated to AUDIODB parser
@param[in] ulCacheSize The size of cache (must be a multiple of 2)
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SetParseCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize)
{
    if (ulCacheSize % 2) {
        PRINTF("Cache size shoule be a multiple of 2\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }
   /* if(bDBType == AudioNameDB){
        m_ulNameDBCacheAddr = ulCacheAddr;
        m_ulNameDBCacheSize = ulCacheSize;
    } else if(bDBType == AudioInfoDB){
        m_ulInfoDBCacheAddr = ulCacheAddr;
        m_ulInfoDBCacheSize = ulCacheSize;
    }*/
    m_ulAudioDBCacheAddr = ulCacheAddr;
    m_ulAudioDBCacheSize = ulCacheSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_AUDIODB_ReloadCache
//  Description : 
//------------------------------------------------------------------------------
/** @brief Load data into cache if cache missed

@param[in] ulSeekpos Seek position to load data into cache (glAudioDBCacheSize aligned)
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_ReloadCache(MMP_ULONG ulSeekpos) 
{
    MMP_ULONG   readsize;
    MMP_USHORT  ret = MMP_ERR_NONE;
    
    // fist-time seek, backward seek or forward seek
    if(m_ulAudioDBPreSeekPos == 0xFFFFFFFF) {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            ret = MMPC_FS_FileSeek((void *)m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            ret = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            break;
        }
    }
    else if(ulSeekpos < (m_ulAudioDBPreSeekPos + m_ulAudioDBCacheSize)) {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            ret = MMPC_FS_FileSeek((void *)m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            ret = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos, MMPD_FS_SEEK_SET);
            break;
        }
    }
    else {
        switch(m_MediaPath) {
        case MMPD_AUDIO_PLAY_FROM_MEM:
            ret = MMPC_FS_FileSeek((void *)m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos - m_ulAudioDBPreSeekPos - m_ulAudioDBCacheSize, MMPD_FS_SEEK_CUR);
            break;
        case MMPD_AUDIO_PLAY_FROM_CARD:
            ret = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)ulSeekpos - m_ulAudioDBPreSeekPos - m_ulAudioDBCacheSize, MMPD_FS_SEEK_CUR);
            break;
        }
    }
	if (ret)
		return ret;

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        ret = MMPC_FS_FileRead((void *)m_ulDataBaseFileID, (MMP_UBYTE *)m_ulAudioDBCacheAddr, m_ulAudioDBCacheSize, &readsize);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
        ret = MMPD_FS_FileRead(m_ulDataBaseFileID, (MMP_UBYTE *)m_ulAudioDBCacheAddr, m_ulAudioDBCacheSize, &readsize);
        break;
    }
    ret = 0;
    
   /* if(bDBType == AudioNameDB)
        m_ulNameDBPreSeekPos = ulSeekpos;
    else if(bDBType == AudioInfoDB)
        m_ulInfoDBPreSeekPos = ulSeekpos;*/
    m_ulAudioDBPreSeekPos = ulSeekpos;
    
    return  ret;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_ReadCache
//  Description : 
//=========================================================================
/** @brief Read data from cache

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_ReadCache(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_UBYTE *source;

    source = (MMP_UBYTE *)m_ulAudioDBCacheAddr + (ulSeekpos & (m_ulAudioDBCacheSize - 1));
    while(ulReadsize > 0) {
        *ubTarget++ = *source++;
        ulReadsize--;
    }
    
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_ReadFile
//  Description : 
//=========================================================================
/** @brief Read MP3 file with cache mechanism

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_ReadFile(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize)
{
    MMP_ULONG   readed_size, canread_size, rem_size;
    MMP_ULONG   cur_seekpos;
    MMP_USHORT  ret;

    cur_seekpos = ulSeekpos;
    readed_size = 0;
    rem_size    = ulReadsize;

    while(readed_size < ulReadsize){
        if(((m_ulAudioDBPreSeekPos) & ~(m_ulAudioDBCacheSize - 1)) != (cur_seekpos & ~(m_ulAudioDBCacheSize - 1))) {
            // cache miss
          /*  if(m_ulDataBaseFileID == m_ulNameDBID)
                ret = MMPD_AUDIODB_ReloadCache(cur_seekpos & ~(m_ulAudioDBCacheSize - 1), AudioNameDB);
            else if(m_ulDataBaseFileID == m_ulInfoDBID)
                ret = MMPD_AUDIODB_ReloadCache(cur_seekpos & ~(m_ulAudioDBCacheSize - 1), AudioInfoDB);*/
                ret = MMPD_AUDIODB_ReloadCache(cur_seekpos & ~(m_ulAudioDBCacheSize - 1));
			if (ret)
				return ret;
        }

        canread_size = m_ulAudioDBCacheSize - (cur_seekpos & (m_ulAudioDBCacheSize - 1));
        if(rem_size > canread_size){
            MMPD_AUDIODB_ReadCache(ubTarget, cur_seekpos, canread_size);
            rem_size -= canread_size;
            readed_size += canread_size;
            cur_seekpos += canread_size;
            ubTarget += canread_size;
        }
        else{
            MMPD_AUDIODB_ReadCache(ubTarget, cur_seekpos, rem_size);
            readed_size += rem_size;
        }
    }

    return MMP_ERR_NONE;
}
#if 0
static MMP_ERR MMPD_AUDIODB_SwitchDatabase(MMP_BYTE bDBType)
{
    if(bDBType == AudioNameDB){
    
       // m_ulInfoDBPreSeekPos = m_ulAudioDBPreSeekPos;
        
        m_ulDataBaseFileID = m_ulNameDBID;
        m_ulAudioDBPreSeekPos = m_ulNameDBPreSeekPos;
        m_ulAudioDBCacheAddr = m_ulNameDBCacheAddr;
        m_ulAudioDBCacheSize = m_ulNameDBCacheSize;
        m_ulDataBaseFileSize = m_ulNameDBSize;
    } else if(bDBType == AudioInfoDB){
      //  m_ulNameDBPreSeekPos = m_ulAudioDBPreSeekPos;
        
        m_ulDataBaseFileID = m_ulInfoDBID;
        m_ulAudioDBPreSeekPos = m_ulInfoDBPreSeekPos;
        m_ulAudioDBCacheAddr = m_ulInfoDBCacheAddr;
        m_ulAudioDBCacheSize = m_ulInfoDBCacheSize;
        m_ulDataBaseFileSize = m_ulInfoDBSize;
    }
    return MMP_ERR_NONE;
}
#endif
//=========================================================================
//  Function    : MMPD_AUDIODB_Intialize
//  Description : 
//=========================================================================
/** @brief Initial audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_Initialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_BYTE *bMode)
{ 
	MMP_ERR	err = MMP_ERR_NONE;
    m_ulDataBaseFileID = 0;
	m_ulAudioDBPreSeekPos = 0xFFFFFFFF;
//	m_ulNameDBPreSeekPos = 0xFFFFFFFF;
//	m_ulInfoDBPreSeekPos = 0xFFFFFFFF;

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        err = MMPC_FS_FileOpen(bFileName, bMode, (void **)&m_ulDataBaseFileID);
        MMPC_FS_FileGetSize((void *)m_ulDataBaseFileID, &m_ulDataBaseFileSize);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
		err = MMPD_FS_FileOpen(bFileName, ulNameLen, bMode, STRLEN(bMode), &m_ulDataBaseFileID);
		MMPD_FS_FileGetSize(m_ulDataBaseFileID, &m_ulDataBaseFileSize);
        break;
    default:
        return MMP_AUDIO_ERR_COMMAND_INVALID;
    }
	return err;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_Finish
//  Description : 
//=========================================================================
/** @brief Finish audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_Finish(void)
{ 
	if (m_ulDataBaseFileID != 0) {
   		switch(m_MediaPath) {
		case MMPD_AUDIO_PLAY_FROM_MEM:
			MMPC_FS_FileClose((void *)m_ulDataBaseFileID);
			break;
		case MMPD_AUDIO_PLAY_FROM_CARD:
			MMPD_FS_FileClose(m_ulDataBaseFileID);
	        break;
	    default:
            return MMP_AUDIO_ERR_COMMAND_INVALID;
	    }
	    m_ulDataBaseFileID = 0;
	}  
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_DeleteDatabase
//  Description : 
//=========================================================================
/** @brief Finish audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_DeleteDatabase(MMP_BYTE *bFileName, MMP_ULONG ulNameLen)
{ 
	MMP_ERR	err;

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
		err = MMPD_FS_FileRemove(bFileName, ulNameLen);
		break;
    default:
        return MMP_AUDIO_ERR_COMMAND_INVALID;
    }
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_SetWriteCacheBuf
//  Description : 
//=========================================================================
/** @brief Set the cache address and cache size for writing AUDIODB

@param[in] ulCacheAddr The address of cache dedicated to AUDIODB parser
@param[in] ulCacheSize The size of cache (must be a multiple of 512)
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SetWriteCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize)
{
    if (ulCacheSize & 0x1FF) {
        PRINTF("Cache size shoule be a multiple of 512\r\n");
        return MMP_AUDIO_ERR_PARAMETER;
    }

    m_ulAudioDBWriteCacheAddr = ulCacheAddr;
    m_ulAudioDBWriteCacheSize = ulCacheSize;
    m_ulAudioDBWriteCacheCurPtr = 0;

    return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_WriteFile
//  Description : 
//=========================================================================
/** @brief Read MP3 file with cache mechanism

@param[in] ulSeekpos Seek position of file
@param[in] ulReadsize Size to read
@param[out] ubTarget Buffer which stores the read data
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_WriteFile(MMP_UBYTE *ubTarget, MMP_ULONG ulWriteSize)
{
	MMP_ULONG	ulWriteCount;
	MMP_ERR		err;

	if (m_ulAudioDBWriteCacheCurPtr + ulWriteSize >= m_ulAudioDBWriteCacheSize) {
		MEMCPY((MMP_UBYTE *)(m_ulAudioDBWriteCacheAddr + m_ulAudioDBWriteCacheCurPtr), ubTarget, 
				(m_ulAudioDBWriteCacheSize - m_ulAudioDBWriteCacheCurPtr));
	
	    switch(m_MediaPath) {
    	case MMPD_AUDIO_PLAY_FROM_MEM:
        	err = MMPC_FS_FileWrite((void *)m_ulAudioDBWriteFileID, (MMP_UBYTE *)m_ulAudioDBWriteCacheAddr, m_ulAudioDBWriteCacheSize, &ulWriteCount);
	        break;
    	case MMPD_AUDIO_PLAY_FROM_CARD:
			err = MMPD_FS_FileWrite(m_ulAudioDBWriteFileID, (MMP_UBYTE *)m_ulAudioDBWriteCacheAddr, m_ulAudioDBWriteCacheSize, &ulWriteCount);
	        break;
    	}

		if (ulWriteSize - (m_ulAudioDBWriteCacheSize - m_ulAudioDBWriteCacheCurPtr)) {
			MEMCPY((MMP_UBYTE *)(m_ulAudioDBWriteCacheAddr), ubTarget + (m_ulAudioDBWriteCacheSize - m_ulAudioDBWriteCacheCurPtr),
					ulWriteSize - (m_ulAudioDBWriteCacheSize - m_ulAudioDBWriteCacheCurPtr));
				
			m_ulAudioDBWriteCacheCurPtr = ulWriteSize - (m_ulAudioDBWriteCacheSize - m_ulAudioDBWriteCacheCurPtr);		
		}			
		else {
			m_ulAudioDBWriteCacheCurPtr = 0;
		}
	}
	else {
		MEMCPY((MMP_UBYTE *)(m_ulAudioDBWriteCacheAddr + m_ulAudioDBWriteCacheCurPtr), ubTarget, ulWriteSize);
	
		m_ulAudioDBWriteCacheCurPtr += ulWriteSize;
	}

    return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_CreateInitialize
//  Description : 
//=========================================================================
/** @brief Initial audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_CreateInitialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen)
{ 
	MMP_ERR	err = MMP_ERR_NONE;

    switch(m_MediaPath) {
    case MMPD_AUDIO_PLAY_FROM_MEM:
        err = MMPC_FS_FileOpen(bFileName, "w+b", (void **)&m_ulAudioDBWriteFileID);
        break;
    case MMPD_AUDIO_PLAY_FROM_CARD:
		err = MMPD_FS_FileOpen(bFileName, ulNameLen, "w+b", STRLEN("w+b"), &m_ulAudioDBWriteFileID);
        break;
    default:
        return MMP_AUDIO_ERR_COMMAND_INVALID;
    }
	return err;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_CreateFinish
//  Description : 
//=========================================================================
/** @brief Finish audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_CreateFinish(void)
{ 
	MMP_ULONG	ulWriteCount;
	MMP_ERR		err;

	if (m_ulAudioDBWriteFileID != 0) {
		if (m_ulAudioDBWriteCacheCurPtr) {
		    switch(m_MediaPath) {
    		case MMPD_AUDIO_PLAY_FROM_MEM:
        		err = MMPC_FS_FileWrite((void *)m_ulAudioDBWriteFileID, (MMP_UBYTE *)m_ulAudioDBWriteCacheAddr, m_ulAudioDBWriteCacheCurPtr, &ulWriteCount);
	        	break;
	    	case MMPD_AUDIO_PLAY_FROM_CARD:
				err = MMPD_FS_FileWrite(m_ulAudioDBWriteFileID, (MMP_UBYTE *)m_ulAudioDBWriteCacheAddr, m_ulAudioDBWriteCacheCurPtr, &ulWriteCount);
	    	    break;
            default:
                return MMP_AUDIO_ERR_COMMAND_INVALID;
	    	}
		}	    	
	
   		switch(m_MediaPath) {
		case MMPD_AUDIO_PLAY_FROM_MEM:
			MMPC_FS_FileClose((void *)m_ulAudioDBWriteFileID);
			break;
		case MMPD_AUDIO_PLAY_FROM_CARD:
			MMPD_FS_FileClose(m_ulAudioDBWriteFileID);
	        break;
        default:
            return MMP_AUDIO_ERR_COMMAND_INVALID;
	    }
	    m_ulAudioDBWriteFileID = 0;
	}  
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_AddNewObject
//  Description : 
//=========================================================================
/** @brief Add new object to audio database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_AddNewObject(MMPD_AUDIODB_AUDIOINFO AudInfo)
{
    MMPD_AUDIODB_WriteFile((MMP_UBYTE *)(&AudInfo), sizeof(MMPD_AUDIODB_AUDIOINFO));

    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_ListAudioInfo
//  Description : 
//=========================================================================
/** @brief List Audio information in database

@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_ListAudioInfo()
{
    MMP_ULONG DBFilePos = 0;
    MMPD_AUDIODB_AUDIOINFO infobuf;
    while(DBFilePos < m_ulDataBaseFileSize) {

        MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&infobuf), DBFilePos, sizeof(MMPD_AUDIODB_AUDIOINFO));
        DBFilePos += sizeof(MMPD_AUDIODB_AUDIOINFO);
        //if(count > 990)
        PRINTF("Name : %s\r\nArtist : %s\r\nAlbum : %s\r\n",infobuf.ubFullFileName,infobuf.bArtist,infobuf.bAlbum);       
       // count++;
    } 
    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_SearchAudioInfo
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] bFileName Search this file name is in the database or not.
@param[out] ulInfoPos Points to the position of audio information in database.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SearchAudioInfo(MMP_BYTE* bFileName, MMP_ULONG *ulInfoPos)
{
    MMPD_AUDIODB_AUDIOINFO infobuf;
    MMP_ULONG DBFilePos = 0;
    MMP_ULONG count = 0 ;
    
    
    while(DBFilePos < m_ulDataBaseFileSize) {
        MMPD_AUDIODB_ReadFile(infobuf.ubFullFileName, DBFilePos, AUDIODB_MAX_FILE_NAME_SIZE*2);
        #if (FS_INPUT_ENCODE == UCS2)
        if(strcmp_w(bFileName, (MMP_BYTE*)(infobuf.ubFullFileName)) == 0){
        #elif (FS_INPUT_ENCODE == UTF8)
        if(STRCMP(bFileName, (MMP_BYTE*)(infobuf.ubFullFileName)) == 0){
        #endif
            PRINTF("File is existed\r\n");
            *ulInfoPos = DBFilePos;
            DBFilePos += AUDIODB_MAX_FILE_NAME_SIZE*2;
            MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&(infobuf.bArtist)), DBFilePos, (TEXT_FRAME_MAX_LEN*2));
            DBFilePos += (TEXT_FRAME_MAX_LEN*2);
            MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&(infobuf.bAlbum)), DBFilePos, (TEXT_FRAME_MAX_LEN*2));
            //PRINTF("Name : %s\r\nTime : %d\r\nChan : %d\r\n",infobuf.ubFullFileName,infobuf.ulTotalTime,infobuf.ulChans);       
            PRINTF("Name : %s\r\nArtist : %s\r\nAlbum : %s\r\n",infobuf.ubFullFileName,infobuf.bArtist,infobuf.bAlbum);
            
            PRINTF("count : %d\r\n", count);
            return MMP_ERR_NONE;
        }
        DBFilePos += sizeof(MMPD_AUDIODB_AUDIOINFO);
        count++;
    }
    PRINTF("count : %d\r\n", count);
    return MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_DirtyFile
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] bFileName Search this file name is in the database or not.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_DirtyFile(MMPD_AUDIODB_AUDIOINFO  *infobuf, MMPD_AUDIODB_BTNODE *node)
{
	MMP_ERR		err;
	MMP_ULONG	writesize;

	infobuf->ubDirty = 1;

    //Because of the random access to the index file, do not use the cache mechanism.
	switch (m_MediaPath) {
	case MMPD_AUDIO_PLAY_FROM_MEM:
		break;
	case MMPD_AUDIO_PLAY_FROM_CARD:
		err = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)node->ulFileOffset, MMPD_FS_SEEK_SET);
		if (err)
			return err;
        err = MMPD_FS_FileWrite(m_ulDataBaseFileID, (MMP_UBYTE *)infobuf, sizeof(MMPD_AUDIODB_AUDIOINFO), &writesize);
		if (err)
			return err;
		break;
	}

    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_CheckDatabaseDirty
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] bFileName Search this file name is in the database or not.
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_CheckDatabaseDirty(MMP_ULONG *ulFileSize)
{
    MMPD_AUDIODB_AUDIOINFO	old_infobuf;
    MMPD_AUDIODB_AUDIOINFO	new_infobuf;
    MMP_ULONG				filepos = 0;
	MMP_ULONG				writesize = 0, readsize = 0;
	MMP_ERR					err;
    
   	// check for every files
    while (filepos < m_ulDataBaseFileSize) {
        MMPD_AUDIODB_ReadFile((MMP_UBYTE *)&old_infobuf, filepos, sizeof(MMPD_AUDIODB_AUDIOINFO));
        filepos += sizeof(MMPD_AUDIODB_AUDIOINFO);
        if (old_infobuf.ubDirty) {
        	// get the last entry
        	if (filepos == m_ulDataBaseFileSize) {
        		m_ulDataBaseFileSize -= sizeof(MMPD_AUDIODB_AUDIOINFO);
        	}
        	else {
				while (1) {
				    //Because of the random access to the index file, do not use the cache mechanism.
					switch(m_MediaPath) {
					case MMPD_AUDIO_PLAY_FROM_MEM:
						break;
					case MMPD_AUDIO_PLAY_FROM_CARD:
						err = MMPD_FS_FileSeek(m_ulDataBaseFileID, ((MMP_LONG64)m_ulDataBaseFileSize - sizeof(MMPD_AUDIODB_AUDIOINFO)), MMPD_FS_SEEK_SET);
						if (err) return err;
				        err = MMPD_FS_FileRead(m_ulDataBaseFileID, (MMP_UBYTE *)(&new_infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO), &readsize);
						if (err) return err;
						break;
					}

					m_ulDataBaseFileSize -= sizeof(MMPD_AUDIODB_AUDIOINFO);
					if (new_infobuf.ubDirty) {
						if (filepos == m_ulDataBaseFileSize) {
							m_ulDataBaseFileSize -= sizeof(MMPD_AUDIODB_AUDIOINFO);
							break;
						}
					}
					else {
						// move to the new position					
						err = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)filepos - sizeof(MMPD_AUDIODB_AUDIOINFO), MMPD_FS_SEEK_SET);
						if (err) return err;
				        err = MMPD_FS_FileWrite(m_ulDataBaseFileID, (MMP_UBYTE *)(&new_infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO), &writesize);
						if (err) return err;
						break;
					}
				}
			}	        	
        }
    }
    
    MMPD_FS_FileTruncate(m_ulDataBaseFileID, m_ulDataBaseFileSize);
    
    *ulFileSize = m_ulDataBaseFileSize;

    return MMP_ERR_NONE;
}
static MMP_ERR MMPD_AUDIODB_ConvertUCS2ByteOrder(MMP_BYTE* bDest, MMP_BYTE* bSrc)
{
    MMP_LONG i = 0;
    while((bSrc[i] != '\0') || (bSrc[i+1] != '\0'))
    {
        bDest[i] = bSrc[i+1];
        bDest[i+1] = bSrc[i];
        i+=2;
    }
    return MMP_ERR_NONE;
}

static MMP_ERR MMPD_AUDIODB_CopyId3v2Str(MMP_BYTE* bDest,MMP_LONG lDestLen, MMP_BYTE* bSrc, MMP_LONG lSrcLen)
{
    MMP_USHORT usBOM;
    MMP_LONG i = 1;
    MMP_USHORT *sDest = (MMP_USHORT *)bDest;

    switch(bSrc[0]){
    case MMPD_ID3_TEXT_ISO_8859_1:
        while (bSrc[i]) {
            if ((bSrc[i] < 0x20) || (bSrc[i] > 0x7E)) {
                return MMP_ERR_NONE;
            }
            i++;
        }
        i = 1;
        do {
            *sDest = bSrc[i++];
        } while((*sDest++ != '\0') && (i < (lDestLen>>1)));
        break;
    case MMPD_ID3_TEXT_UCS_2:
        usBOM = bSrc[1] << 8 | bSrc[2];
        if (usBOM == 0xFFFE) {
            //Little Endian
            MMPD_AUDIODB_ConvertUCS2ByteOrder(bDest, bSrc + 3);
        }
        else if (usBOM == 0xFEFF) {
            //Big Endian
            lSrcLen = ((lSrcLen - 3) > lDestLen) ? lDestLen : lSrcLen - 3;
            MEMCPY(bDest, bSrc + 3, lSrcLen);
        }
        break;
    default:
        PRINTF("not ISO8859-1 or UCS2\r\n");
        break;
    }
    return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_GetTitleFromFilename
//  Description : 
//=========================================================================
/** @brief Create binary tree

@param[in] bFileName : the input file name
@param[out] bTitleName : returned title
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_GetTitleFromFilename(MMP_BYTE* bFileName, MMP_BYTE *bTitleName)
{
    MMP_USHORT  usCurNamePos = 0;
    MMP_UBYTE   ubTitleLength = 0;
	MMP_ULONG	i;
    #if (FS_INPUT_ENCODE == UCS2)
    MMP_SHORT   *sFileName = (MMP_SHORT *)bFileName;
	#endif
	
    #if (FS_INPUT_ENCODE == UCS2)
    usCurNamePos = (uniStrlen(sFileName) >> 1) - 1;
    #elif (FS_INPUT_ENCODE == UTF8)
    usCurNamePos = STRLEN(bFileName) - 1;
    #endif
    while(usCurNamePos) {
       #if (FS_INPUT_ENCODE == UCS2)
       if (sFileName[usCurNamePos] == (MMP_SHORT)('\\')) {
       #elif (FS_INPUT_ENCODE == UTF8)
       if (bFileName[usCurNamePos] == '\\') {
       #endif
           break;
       }
       usCurNamePos -= 1;
    }
    
	
	#if (FS_INPUT_ENCODE == UCS2)
	strcpy_w(bTitleName, (MMP_BYTE*)(&sFileName[(usCurNamePos+1)]));
	#elif (FS_INPUT_ENCODE == UTF8)
 	STRCPY(bTitleName, (MMP_BYTE*)(bFileName+(usCurNamePos+1)));
 	#endif
    
    // Remove Subname ".XXX"
	#if (FS_INPUT_ENCODE == UCS2)
    sFileName = (MMP_SHORT *)bTitleName;
    usCurNamePos = (uniStrlen(sFileName) >> 1) - 1;
    ubTitleLength = usCurNamePos;
    #elif (FS_INPUT_ENCODE == UTF8)
    usCurNamePos = STRLEN(bFileName) - 1;
    #endif
    
    while(usCurNamePos) {
       #if (FS_INPUT_ENCODE == UCS2)  
       if (sFileName[usCurNamePos] == (MMP_SHORT)('.'))
       #elif (FS_INPUT_ENCODE == UTF8)
       if (bFileName[usCurNamePos] == '.')
       #endif
           break;
       usCurNamePos -= 1;
    }
    for (i = usCurNamePos ; i <= ubTitleLength; i++) {
		#if (FS_INPUT_ENCODE == UCS2)
		sFileName[i] = 0;
		#elif (FS_INPUT_ENCODE == UTF8)
		bTitleName[i] = 0;
		#endif    
    }
    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_AddAudioInfo
//  Description : 
//=========================================================================
/** @brief Create binary tree

@param[in] bAudioName : the input file name
@param[in] ulFileID : the input file id (open by getfilelistdb)
@param[int] ret : music type
@retval MMP_ERR_NONE Success.
*/
static MMP_ERR MMPD_AUDIODB_AddAudioInfo(MMP_BYTE* bAudioName, MMP_ULONG ulFileID, MMP_BYTE ret)
{
    MMPD_AUDIODB_AUDIOINFO	audioinfo;
    MMPD_ID3_INFO 			id3info;
    
    MEMSET(&audioinfo, 0, sizeof(MMPD_AUDIODB_AUDIOINFO));
    #if (FS_INPUT_ENCODE == UCS2)
    strcpy_w((MMP_BYTE *)audioinfo.ubFullFileName, bAudioName);
    #elif (FS_INPUT_ENCODE == UTF8)
    STRCPY((MMP_BYTE *)audioinfo.ubFullFileName, bAudioName);
    #endif

    //transfer to USC2
    if(ret == 2) { // MP3
        MEMSET(&id3info, 0, sizeof(id3info));

        id3info.metaType = MMPD_ID3_META_TITLE | 
        					MMPD_ID3_META_ALBUM | 
        					MMPD_ID3_META_ARTIST | 
        					MMPD_ID3_META_GENRE |
    						MMPD_ID3_META_RATING |		
    						MMPD_ID3_META_PCOUNT;

        MMPD_ID3_SetMediaPath(MMPD_AUDIO_PLAY_FROM_CARD);
        MMPD_ID3_GetInfo(bAudioName, 0, ulFileID, &id3info, 0, NULL, NULL);
            
        if(id3info.flag & ID3_V2_IN_AUDIO) {
            if(id3info.id3v2Tag.bAlbum[1]){
                MMPD_AUDIODB_CopyId3v2Str(audioinfo.bAlbum, sizeof(audioinfo.bAlbum), 
                                          id3info.id3v2Tag.bAlbum, sizeof(id3info.id3v2Tag.bAlbum));             
            }
            if(id3info.id3v2Tag.bArtist[1]){
                MMPD_AUDIODB_CopyId3v2Str(audioinfo.bArtist, sizeof(audioinfo.bArtist),
                                          id3info.id3v2Tag.bArtist, sizeof(id3info.id3v2Tag.bArtist));
            }
            if(id3info.id3v2Tag.bGenre[1]){
                MMPD_AUDIODB_CopyId3v2Str(audioinfo.bGenre, sizeof(audioinfo.bGenre), 
                                          id3info.id3v2Tag.bGenre, sizeof(id3info.id3v2Tag.bGenre));                
            }
            if(id3info.id3v2Tag.bTitle[1]){
                MMPD_AUDIODB_CopyId3v2Str(audioinfo.bTitle, sizeof(audioinfo.bTitle), 
                                          id3info.id3v2Tag.bTitle, sizeof(id3info.id3v2Tag.bTitle));
				if (uniStrlen((const short *)audioinfo.bTitle) == 0) 
					MMPD_AUDIODB_GetTitleFromFilename(bAudioName, audioinfo.bTitle);	                                          
            }
            else {
            	MMPD_AUDIODB_GetTitleFromFilename(bAudioName, audioinfo.bTitle);
            }
            audioinfo.ulPlayCount = id3info.id3v2Tag.ubPlayCnt[3] | 
            						(id3info.id3v2Tag.ubPlayCnt[2] << 8) |
            						(id3info.id3v2Tag.ubPlayCnt[1] << 16) |
            						(id3info.id3v2Tag.ubPlayCnt[0] << 24);
            audioinfo.ubRating = id3info.id3v2Tag.ubRating;
            #if 0
			if (audioinfo.ulPlayCount)
				PRINTF("Play Count = 0x%X\r\n", audioinfo.ulPlayCount);
			if (audioinfo.ubRating)
				PRINTF("Rating = 0x%X\r\n", audioinfo.ubRating);
            #endif
        }      
    }
    else {
    	MMPD_AUDIODB_GetTitleFromFilename(bAudioName, audioinfo.bTitle);
    }
          
    // Add to Database
    MMPD_AUDIODB_AddNewObject(audioinfo);
    
    return MMP_ERR_NONE;
}
#if (FS_INPUT_ENCODE == UCS2)
static MMP_LONG MMPD_AUDIODB_CmpUCS2AndUTF8(MMP_BYTE *str1, MMP_BYTE *str2)
{
    while(*(MMP_USHORT*)str1 == *str2)
    {
        if(*(MMP_USHORT*)str1 == 0x0000)
            return 0;
        str1 += 2;
        str2 += 1;
    }
    return (MMP_LONG)*(MMP_USHORT*)str1 - (MMP_LONG)*(MMP_BYTE*)str2;
}
#endif

static MMP_BYTE MMPD_AUDIODB_CheckSubname(MMP_BYTE* bName)
{
    MMP_BYTE ret = 0;
    MMP_ULONG len;
    MMP_LONG i, dot = -1;
    MMP_LONG j = 0;
    #if (FS_INPUT_ENCODE == UCS2)
    MMP_BYTE bSubname[10];
	#elif (FS_INPUT_ENCODE == UTF8)
	MMP_BYTE bSubname[5];
	#endif    
    
    #if (FS_INPUT_ENCODE == UCS2)
    MEMSET(bSubname, 0, 10);
    len = uniStrlen((const MMP_SHORT *)bName);
    
    for(i = len-2; i > 0; i-=2) {
        if((bName[i] == '.') && (bName[i+1] == 0)) {
            dot = i;
            break;
        }
    }
    if(dot < 0) {
        //No SubName found
        return ret;
    }

    strcpy_w(bSubname, &bName[dot+2]);
    for(i = 0; i < 10; i+=2){  // lower to upper
        if(((bSubname[i] >= 0x61) && (bSubname[i+1] == 0))&&((bSubname[i] <= 0x7A) && (bSubname[i+1] == 0))) {
            bSubname[i] -= 0x20;
        }
    }
    
    while(j < 11) {
        if(!MMPD_AUDIODB_CmpUCS2AndUTF8(bSubname, m_Subname[j])) {
            if((bSubname[4] == '3') &&(bSubname[5] == 0)) {
                //find mp3
                return 2;
            }
            //find other audio
            return 1;
        }
        j++;
    }
    #elif (FS_INPUT_ENCODE == UTF8)
    MEMSET(bSubname, 0, 5);
    
    len = STRLEN(bName);
    for(i = len-1; i > 0; i--) {
        if(bName[i] == '.') {
            dot = i;
            break;
        }
    }
    if(dot < 0) {
        //No SubName found
        return ret;
    }
    STRCPY(bSubname, &bName[dot+1]);
    for(i = 0; i < 5; i++){  // lower to upper
        if((bSubname[i] >= 0x61)&&(bSubname[i] <= 0x7A)) {
            bSubname[i] -= 0x20;
        }
    }
    
    while(STRCMP(m_Subname[j], END_OF_LGE_MM_DRIVE_TABLE) != 0) {
        if(!STRCMP(bSubname, m_Subname[j])) {
            if(bSubname[2] == '3') {
                //find mp3
                return 2;
            }
            //find other audio;
            return 1;
        }
        j++;
    }
    #endif
    return ret;
}

MMP_ERR MMPD_AUDIODB_AddMusic(MMP_BYTE* bFullFileName, MMP_ULONG ulFileID)
{
    MMP_BYTE    ret = 0;
    
    ret = MMPD_AUDIODB_CheckSubname(bFullFileName);
    
    if (ret) {
        MMPD_AUDIODB_AddAudioInfo(bFullFileName, ulFileID, ret);
    }
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_GetBTreeNodeInfo
//  Description : 
//=========================================================================
/** @brief Set the binary tree walk action

@param[out] infobuf : return the audio database information
@param[in] node : get the audio database information from the node offest
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_GetBTreeNodeInfo(MMPD_AUDIODB_AUDIOINFO *infobuf, MMPD_AUDIODB_BTNODE *node)
{
    MMP_ULONG	readsize = 0;
    MMP_ERR		ret = MMP_ERR_NONE;
    
    //Because of the random access to the index file, do not use the cache mechanism.
	switch(m_MediaPath) {
	case MMPD_AUDIO_PLAY_FROM_MEM:
		ret = MMPC_FS_FileSeek((void *)m_ulDataBaseFileID, (MMP_LONG64)node->ulFileOffset, MMPD_FS_SEEK_SET);
        ret = MMPC_FS_FileRead((void *)m_ulDataBaseFileID, (MMP_UBYTE *)(&infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO), &readsize);
		break;
	case MMPD_AUDIO_PLAY_FROM_CARD:
		ret = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)node->ulFileOffset, MMPD_FS_SEEK_SET);
        ret = MMPD_FS_FileRead(m_ulDataBaseFileID, (MMP_UBYTE *)infobuf, sizeof(MMPD_AUDIODB_AUDIOINFO), &readsize);
		break;
	}
	return ret;
}

static void MMPD_AUDIODB_BTreeWriteNode(MMPD_AUDIODB_BTNODE *node)
{
	MMPD_AUDIODB_AUDIOINFO   infobuf;
    MMP_ULONG	readsize;
    MMP_ERR		ret;
    
    //Because of the random access to the index file, do not use the cache mechanism.
	switch(m_MediaPath) {
	case MMPD_AUDIO_PLAY_FROM_MEM:
		ret = MMPC_FS_FileSeek((void *)m_ulDataBaseFileID, (MMP_LONG64)node->ulFileOffset, MMPD_FS_SEEK_SET);
        ret = MMPC_FS_FileRead((void *)m_ulDataBaseFileID, (MMP_UBYTE *)(&infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO), &readsize);
		break;
	case MMPD_AUDIO_PLAY_FROM_CARD:
		ret = MMPD_FS_FileSeek(m_ulDataBaseFileID, (MMP_LONG64)node->ulFileOffset, MMPD_FS_SEEK_SET);
        ret = MMPD_FS_FileRead(m_ulDataBaseFileID, (MMP_UBYTE *)(&infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO), &readsize);
		break;
	}

    MMPD_AUDIODB_WriteFile((MMP_UBYTE *)(&infobuf), sizeof(MMPD_AUDIODB_AUDIOINFO));
}
#if 0
MMP_ERR MMPD_AUDIODB_BTreeIterativeWalk(MMPD_AUDIODB_BTNODE *root)
{
    typedef             MMPD_AUDIODB_BTNODE*      STACK_TYPE;
    static STACK_TYPE   *stack_base = NULL;
    STACK_TYPE          *stack_top;
    MMPD_AUDIODB_BTNODE *curr_node;

    if (root == NULL)
		return MMP_ERR_NONE;

    if(stack_base == NULL) { // Reuse stack space
        if((stack_base = (STACK_TYPE*)MALLOC(sizeof(STACK_TYPE)*1024)) == NULL)
            return -1;
    }
    stack_top = stack_base;

    root->bVisited  = MMP_FALSE;
    *stack_top++    = root; // Push root to stack first

    while (stack_top != stack_base) { // Check if stack empty
        // Pop from stack
        curr_node = *(--stack_top);
        if (curr_node->bVisited == MMP_TRUE) {
            print_ucs2("node", curr_node->data);
        }
        else {
            if (curr_node->left) {
                curr_node->left->bVisited = MMP_FALSE;
                *stack_top++ = curr_node->left;
            }
            curr_node->bVisited = MMP_TRUE; // Set curr_node visited
            *stack_top++ = curr_node;
            if (curr_node->right) {
                curr_node->right->bVisited = MMP_FALSE;
                *stack_top++ = curr_node->right;
            }
        }
    }

	return MMP_ERR_NONE;
}
#endif
MMP_ERR MMPD_AUDIODB_BTreeWalkForward(MMPD_AUDIODB_BTNODE *node)
{
    if (node == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BTreeWalkForward(node->left);
	MMPD_AUDIODB_BTreeWriteNode(node);
	MMPD_AUDIODB_BTreeWalkForward(node->right);
	return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_SetBTreeWalk
//  Description : 
//=========================================================================
/** @brief Set the binary tree walk action

@param[in] ulStart : start entry to do the action (start from 0) 
@param[in] ulEnd : end entry to do the action
@param[in] action : action to do
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SetBTreeWalk(MMP_ULONG ulStart, MMP_ULONG ulEnd, MMPD_AUDIODB_BTACTION *action)
{
	m_ulBTreeStart = ulStart;
	m_ulBTreeEnd = ulEnd;
	m_ulBTreeCurrentCount = 0;
	m_action = action;
	
	return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeWalk
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] node : root node for binary tree
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BTreeWalk(MMPD_AUDIODB_BTNODE *node)
{
    if (node == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BTreeWalk(node->left);
	if (m_ulBTreeCurrentCount >= m_ulBTreeStart) {
		if (m_ulBTreeCurrentCount < m_ulBTreeEnd) {
			m_action(node);
		}
		else {
			return	MMP_ERR_NONE;
		}
	}
	m_ulBTreeCurrentCount++;
	MMPD_AUDIODB_BTreeWalk(node->right);
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeFilter
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] node : root node for binary tree
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BTreeFilter(MMPD_AUDIODB_BTNODE *node)
{
    if (node == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BTreeFilter(node->left);
	m_action(node);
	MMPD_AUDIODB_BTreeFilter(node->right);

	return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeFree
//  Description : 
//=========================================================================
/** @brief Search audio file information

@param[in] pnnode : root node to be free
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BTreeFree(MMPD_AUDIODB_BTNODE **pnode)
{
    MMPD_AUDIODB_BTNODE *node = *pnode;
	if (node == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BTreeFree(&(node->left));
	MMPD_AUDIODB_BTreeFree(&(node->right));
    //PRINTF("Free %d %s\n", ++free_cnt, node->data);
    AUDIODB_FREE(node);
    *pnode = NULL;

    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeSearch
//  Description : 
//=========================================================================
/**
 @brief Delete Node From BTree
 @param[in] locator : points to pointer to the node to be killed
 */
MMPD_AUDIODB_BTNODE **MMPD_AUDIODB_BTreeSearch(MMPD_AUDIODB_BTNODE **root, MMP_BYTE *bKey)
{
    MMP_LONG                d;
    MMPD_AUDIODB_BTNODE     *curr_node, **parent_ptr;

    if ((root == NULL) || (*root == NULL))
        return NULL;;

    #if (FS_INPUT_ENCODE == UCS2)
    if(*(MMP_USHORT*)bKey == 0x0000)
        return NULL;
    #elif (FS_INPUT_ENCODE == UTF8)
    if(bKey[0] == 0x00)
        return NULL;
	#endif

    parent_ptr  = root;
    curr_node   = *root;
    while (curr_node) {
        #if (FS_INPUT_ENCODE == UCS2)
        d = strcmp_w(bKey, curr_node->data);
        #elif (FS_INPUT_ENCODE == UTF8)
        d = STRCMP(bKey, curr_node->data);
        #endif
        if (d == 0) {
            return parent_ptr;
        }
        if (d > 0) {
            parent_ptr  = &(curr_node->right);
            curr_node   = curr_node->right;
        } else {
            parent_ptr  = &(curr_node->left);
            curr_node   = curr_node->left;
        }
    }
    return NULL;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeKillNode
//  Description : 
//=========================================================================
/**
 @brief Delete Node From BTree
 @param[in] locator : points to pointer to the node to be killed
 */
// 
MMP_ERR MMPD_AUDIODB_BTreeKillNode(MMPD_AUDIODB_BTNODE **locator, MMP_USHORT *usNodeCount)
{
    MMPD_AUDIODB_BTNODE *dead_node = *locator, *min_node;
//    dead_node = *locator;

    dead_node->usLifeTime--; // Decreament life time counter
    if(dead_node->usLifeTime >= 1)
        return MMP_ERR_NONE;

    if (dead_node->right) {
        // Find min node of right subtree
        min_node = dead_node->right;
        while (min_node->left)
            min_node = min_node->left;

        // Move left subtree to min node of right subtree
        min_node->left = dead_node->left;
        *locator = dead_node->right;
        //MMPD_AUDIODB_BTreeFree(dead_node);
    } else {
        *locator = dead_node->left;
        //MMPD_AUDIODB_BTreeFree(dead_node);    // Current FREE will cause all data be freed
    }
    *usNodeCount = *usNodeCount - 1;
    return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_BForestKillNode
//  Description : 
//=========================================================================
/**
 @brief Delete Node From BForest
 @param[in] locator : points to pointer to the node to be killed
 @param[in] usNodeCount : number of the node
 */
MMP_ERR MMPD_AUDIODB_BForestKillNode(MMPD_AUDIODB_BFNODE **locator, MMP_USHORT *usNodeCount)
{
    MMPD_AUDIODB_BFNODE *dead_node = *locator, *min_node;

	#if (FS_INPUT_ENCODE == UCS2)
    print_ucs2("Killing Forest Node", (*locator)->data);
    #endif

    if (dead_node->right) {
        // Find min node of right subtree
        min_node = dead_node->right;
        while (min_node->left)
            min_node = min_node->left;

        // Move left subtree to min node of right subtree
        min_node->left = dead_node->left;
        *locator = dead_node->right;
        //MMPD_AUDIODB_BForestFree(dead_node); // Current FREE will cause all data be freed
    } else {
        *locator = dead_node->left;
        //MMPD_AUDIODB_BForestFree(dead_node); // Current FREE will cause all data be freed
    }
    *usNodeCount = *usNodeCount - 1;

    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_KillTrack
//  Description : 
//=========================================================================
/**
 @brief Delete Node From BForest
 @param[in] bt_locator : points to pointer to the node to be killed
 @param[in] bf_locator : points to pointer to the pointer forest
 @param[in] itemindex
 @param[out] bfnode_counter 
 @param[in] infobuf 
 */
MMP_ERR MMPD_AUDIODB_KillTrack(MMPD_AUDIODB_BTNODE **bt_locator, MMPD_AUDIODB_BFNODE **bf_locator,
                                    MMPD_AUDIODB_OBJECT_PROPERTY itemindex, MMP_USHORT *bfnode_counter, 
                                    MMPD_AUDIODB_AUDIOINFO  *infobuf)
{
    MMPD_AUDIODB_BTNODE     **metadata_locator;
    MMP_BYTE                *metadata;

    if((bf_locator == NULL) || (*bf_locator == NULL)) {
        MMP_USHORT  usTmpCounter = 1;
        return MMPD_AUDIODB_BTreeKillNode(bt_locator, &usTmpCounter);
    }

    switch(itemindex) {
    case MMPD_AUDIODB_ALBUM:
        metadata = (MMP_BYTE*)(infobuf->bAlbum);
        break;
    case MMPD_AUDIODB_GENRE:
        metadata = (MMP_BYTE*)(infobuf->bGenre);
        break;
    case MMPD_AUDIODB_ARTIST:
    default:
        metadata = (MMP_BYTE*)(infobuf->bArtist);
    }
    // Treat empty string as 'Unkonw'
    #if (FS_INPUT_ENCODE == UCS2)
    if (*(MMP_USHORT*)metadata == 0x0000) {
        strcpy_w(metadata, "U\0n\0k\0n\0o\0w\0n\0\0\0"); // 'Unknow' UCS2 format
    }
    #elif (FS_INPUT_ENCODE == UTF8)
    if (metadata[0] == 0x00) {
        STRCPY(metadata, "Unknown");
    }
    #endif
    // Search for metadata in metadata tree
    
    #if (FS_INPUT_ENCODE == UCS2)
    print_ucs2("Search for", metadata);
    #endif

    metadata_locator = MMPD_AUDIODB_BTreeSearch(&((*bf_locator)->metadata_root), metadata);
    if (metadata_locator == NULL) {
    	#if (FS_INPUT_ENCODE == UCS2)
        print_ucs2("Search Metadata Failed", metadata);
        #endif
        return	MMP_AUDIO_ERR_DATABASE_NOT_FOUND;
	}        
    MMPD_AUDIODB_BTreeKillNode(metadata_locator, &((*bf_locator)->usMetadataCount));
    MMPD_AUDIODB_BTreeKillNode(bt_locator, &((*bf_locator)->usTreeNodeNumber));

	if ((*bf_locator)->usTreeNodeNumber == 0 && (*bf_locator)->usMetadataCount == 0) {
		PRINTF("No tree node available\r\n");	
        MMPD_AUDIODB_BForestKillNode(bf_locator, bfnode_counter);
	}        
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_AUDIODB_BTreeInsert(MMPD_AUDIODB_BTNODE ** tree, MMPD_AUDIODB_BTNODE * item) 
{

	MMPD_AUDIODB_BTNODE * cur_node;
	MMP_LONG	d;

	//Consider the head variable. If the head variable is NULL, this is the first element added to the tree, 
	//so set the head variable to point to it, and you're done: 
	if(!(*tree)) {
		*tree = item;
		return MMP_ERR_NONE;
	}

	//Start at the top of the tree: 
	cur_node = *tree;
	while (cur_node) {
		//Deal with unequal values. If the new value is less than the current value, 
		//the new element goes on the left. Add it immediately if there's nothing on the left. 
		//Otherwise, traverse left and loop: 
        switch(m_groupIndex) {
        case MMPD_AUDIODB_OBJECT_NAME:
        case MMPD_AUDIODB_ARTIST:
        case MMPD_AUDIODB_ALBUM:
        case MMPD_AUDIODB_GENRE:
	    #if (FS_INPUT_ENCODE == UCS2)
    	d = strcmp_w(item->data, cur_node->data);
	    #elif (FS_INPUT_ENCODE == UTF8)
    	d = STRCMP(item->data, cur_node->data);
	    #endif

		if (d >= 0) { 
			if (cur_node->right == NULL) { 
				cur_node->right = item; 
                    return MMP_ERR_NONE;
                }
                cur_node = cur_node->right;
            } else {
                if (cur_node->left == NULL) {
                    cur_node->left = item;
                    return MMP_ERR_NONE; 
                }
                cur_node = cur_node->left;
            }
            break;
        case MMPD_AUDIODB_PLAYCNT:
        case MMPD_AUDIODB_RATING:
            if (m_groupIndex == MMPD_AUDIODB_PLAYCNT) {
                d = (MMP_LONG)((MMP_ULONG)*item->data - (MMP_ULONG)*cur_node->data);
                //PRINTF("item->data = %d\r\n", (MMP_ULONG)*item->data);
                //PRINTF("cur_node->data = %d\r\n", (MMP_ULONG)*cur_node->data);
                PRINTF("diff = %d\r\n", d);
            }
            else {
                d = (MMP_LONG)((MMP_UBYTE)*item->data - (MMP_UBYTE)*cur_node->data);
                //PRINTF("item->data = %d\r\n", (MMP_UBYTE)*item->data);
                //PRINTF("cur_node->data = %d\r\n", (MMP_UBYTE)*cur_node->data);
                PRINTF("diff = %d\r\n", d);
            }
            if (d <= 0) {
                if (cur_node->right == NULL) {
                    cur_node->right = item; 
                    return MMP_ERR_NONE;
                }
                cur_node = cur_node->right;
            }
            else {
                if (cur_node->left == NULL) {
                    cur_node->left = item;
                    return MMP_ERR_NONE;
                }
                cur_node = cur_node->left;
            }
            break;
        }
    }
	
	return MMP_ERR_NONE;
}

MMP_ERR MMPD_AUDIODB_BTreeInsertSingle(MMPD_AUDIODB_BTNODE ** tree, MMP_USHORT *usNodeCounter
                                        , MMP_BYTE *tree_key, MMP_ULONG db_pos) 
{
	MMPD_AUDIODB_BTNODE     *cur_node, *new_node;
	MMP_LONG	d;

	//Consider the head variable. If the head variable is NULL, this is the first element added to the tree, 
	//so set the head variable to point to it, and you're done: 
	if(!(*tree)) {
        if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
    		return -1;
    	}
    	new_node->left = new_node->right = NULL;
        new_node->ulFileOffset = db_pos;
        new_node->usLifeTime    = 1; // >=1: node cannot be killed
    	#if (FS_INPUT_ENCODE == UCS2)
    	strcpy_w(new_node->data, tree_key);
    	#elif (FS_INPUT_ENCODE == UTF8)
    	STRCPY(new_node->data, tree_key);
    	#endif
    	*tree = new_node;
        *usNodeCounter = *usNodeCounter + 1;
		return MMP_ERR_NONE;
	}

	//Start at the top of the tree: 
	cur_node = *tree;
	while (cur_node) {
		//Deal with unequal values. If the new value is less than the current value, 
		//the new element goes on the left. Add it immediately if there's nothing on the left. 
		//Otherwise, traverse left and loop: 

	    #if (FS_INPUT_ENCODE == UCS2)
    	d = strcmp_w(tree_key, cur_node->data);
	    #elif (FS_INPUT_ENCODE == UTF8)
    	d = STRCMP(tree_key, cur_node->data);
	    #endif

        if (d == 0) {// Not allow replicated key
            cur_node->usLifeTime++;
            break;
        }
        else if (d > 0) {
            if(cur_node->right == NULL) {
                if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
            		return -1;
            	}
            	new_node->left = new_node->right = NULL;
                new_node->ulFileOffset = db_pos;
                new_node->usLifeTime    = 1; // >=1: node cannot be killed
            	#if (FS_INPUT_ENCODE == UCS2)
            	strcpy_w(new_node->data, tree_key);
            	#elif (FS_INPUT_ENCODE == UTF8)
            	STRCPY(new_node->data, tree_key);
            	#endif
            	cur_node->right = new_node;

			    *usNodeCounter = *usNodeCounter + 1;
			    break;
            }
			cur_node = cur_node->right;
	    } else {
	        if(cur_node->left == NULL) {
                if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
            		return -1;
            	}
            	new_node->left = new_node->right = NULL;
                new_node->ulFileOffset = db_pos;
                new_node->usLifeTime    = 1; // >=1: node cannot be killed
            	#if (FS_INPUT_ENCODE == UCS2)
            	strcpy_w(new_node->data, tree_key);
            	#elif (FS_INPUT_ENCODE == UTF8)
            	STRCPY(new_node->data, tree_key);
            	#endif
            	cur_node->left = new_node;

			    *usNodeCounter = *usNodeCounter + 1;
			    break;
	        }
			cur_node = cur_node->left;
	    }

	}
	
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_DBCreateTree
//  Description : 
//=========================================================================
/** @brief Create binary tree

@param[in] groupindex : create index
@param[out] ulNodeCount : the node count of the tree
@retval MMP_ERR_NONE Success.
*/
MMPD_AUDIODB_BTNODE *MMPD_AUDIODB_DBCreateTree(MMPD_AUDIODB_OBJECT_PROPERTY groupindex, MMP_ULONG *ulNodeCount)
{
    MMP_ULONG               DBFilePos;
    MMP_BOOL                ubTitleExist = MMP_FALSE;
    MMPD_AUDIODB_BTNODE     *first_node = NULL;
    MMPD_AUDIODB_BTNODE     *new_node;
    MMPD_AUDIODB_AUDIOINFO  infobuf;
    MMP_ULONG               count = 0;

	MMP_UBYTE   			*ubFileNamePos;
	MMP_LONG    			lLastSlash;
	
	m_groupIndex = groupindex;

    // Creating BTree From DB
    for(DBFilePos = 0; DBFilePos < m_ulDataBaseFileSize; DBFilePos += sizeof(MMPD_AUDIODB_AUDIOINFO)) {
        MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&infobuf), DBFilePos, sizeof(MMPD_AUDIODB_AUDIOINFO));

        switch(groupindex) {
        case MMPD_AUDIODB_OBJECT_NAME:
            ubTitleExist = MMP_FALSE;
            #if (FS_INPUT_ENCODE == UCS2)
            if (*(MMP_SHORT *)infobuf.bTitle)
                ubTitleExist = MMP_TRUE;
            #elif (FS_INPUT_ENCODE == UTF8)
            if (*(MMP_BYTE *)infobuf.bTitle)
                ubTitleExist = MMP_TRUE;
            #endif
            break;
        case MMPD_AUDIODB_PLAYCNT:
            if (infobuf.ulPlayCount == 0)
                goto DB_SKIP_DATA;
            break;
        case MMPD_AUDIODB_RATING:
            if (infobuf.ubRating == 0)
                goto DB_SKIP_DATA;
            break;
        }

        //Use malloc() to create a new element, always checking for an error:
        if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
            return NULL;
        }
        count += 1;
        new_node->left = new_node->right = NULL;
        new_node->ulFileOffset = DBFilePos;
        new_node->usLifeTime = 1;

        switch(groupindex) {
        case MMPD_AUDIODB_OBJECT_NAME:
            if(!ubTitleExist) {
                ubFileNamePos = infobuf.ubFullFileName;
                lLastSlash = -2;

                while(*(MMP_USHORT*)ubFileNamePos != 0x0000) {
                    #if (FS_INPUT_ENCODE == UCS2)
                    if ((ubFileNamePos[0] == '\\') && (ubFileNamePos[1] =='\0'))
                    #elif (FS_INPUT_ENCODE == UTF8)
                    if (*ubFileNamePos == '\\')
                    #endif
                        lLastSlash = (MMP_ULONG)ubFileNamePos - (MMP_ULONG)infobuf.ubFullFileName;
                    ubFileNamePos += 2;
                }

                #if (FS_INPUT_ENCODE == UCS2)
                strcpy_w(new_node->data, (MMP_BYTE*)(infobuf.ubFullFileName+(lLastSlash+2)));
                #elif (FS_INPUT_ENCODE == UTF8)
                STRCPY(new_node->data, (MMP_BYTE*)(infobuf.ubFullFileName+(lLastSlash+2)));
                #endif
            }
            else { // Use 'title' to sort
                #if (FS_INPUT_ENCODE == UCS2)
                strcpy_w(new_node->data, (MMP_BYTE*)(infobuf.bTitle));
                #elif (FS_INPUT_ENCODE == UTF8)
                STRCPY(new_node->data, (MMP_BYTE*)(infobuf.bTitle));
                #endif
            }
            break;
        case MMPD_AUDIODB_PLAYCNT:
            MEMCPY(new_node->data, &infobuf.ulPlayCount, sizeof(infobuf.ulPlayCount));
            break;
        case MMPD_AUDIODB_RATING:
            MEMCPY(new_node->data, &infobuf.ubRating, sizeof(infobuf.ubRating));
            break;
        }
        MMPD_AUDIODB_BTreeInsert(&first_node, new_node);
DB_SKIP_DATA:
        ; //for eliminate compiler error
    }
	
	*ulNodeCount = count;

    return first_node;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestFree
//  Description : 
//=========================================================================
/** @brief Free the forest

@param[in] pbfnode : forest node of the forest to be free
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BForestFree(MMPD_AUDIODB_BFNODE **pbfnode)
{
	if (*pbfnode == NULL)
		return MMP_ERR_NONE;

    MMPD_AUDIODB_BTreeFree(&((*pbfnode)->root));
	MMPD_AUDIODB_BForestFree(&((*pbfnode)->left));
	MMPD_AUDIODB_BForestFree(&((*pbfnode)->right));
    AUDIODB_FREE(*pbfnode);
    *pbfnode = NULL;

    return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestSearch
//  Description : 
//=========================================================================
/** @brief Find the forest node

@param[in] root : root node of the forest
@param[in] bKey : key string to be compare
@retval MMP_ERR_NONE Success.
*/
MMPD_AUDIODB_BFNODE *MMPD_AUDIODB_BForestSearch(MMPD_AUDIODB_BFNODE *root, MMP_BYTE *bKey)
{
	MMP_LONG            d;
	MMPD_AUDIODB_BFNODE *curr_node = NULL;

	if(root == NULL)
	    return NULL;


    #if (FS_INPUT_ENCODE == UCS2)
    if(*(MMP_USHORT*)bKey == 0x0000)
        return NULL;
    #elif (FS_INPUT_ENCODE == UTF8)
    if(bKey[0] == 0x00)
        return NULL;
	#endif

    curr_node = root;
    while (curr_node != NULL) {
        #if (FS_INPUT_ENCODE == UCS2)
        d = strcmp_w(bKey, curr_node->data);
        #elif (FS_INPUT_ENCODE == UTF8)
        d = STRCMP(bKey, curr_node->data);
        #endif
        if (d == 0)
            return curr_node;
        if (d > 0)
            curr_node = curr_node->right;
        else
            curr_node = curr_node->left;
    }
	return NULL;
}
/**
 @brief Iteratively create forest
 @param[in] forest_key: for 1st level sort, may NULL
 @param[in] tree_key: for 2nd level sort, not NULL
 */
MMP_ERR MMPD_AUDIODB_BForestInsertSingle(MMPD_AUDIODB_BFNODE **forest_root, MMP_BYTE *forest_key
                        ,MMP_BYTE *tree_key, MMP_ULONG db_pos)
{
    MMPD_AUDIODB_BFNODE     **pcurr_bfnode;
	MMP_LONG	            d;

    if (tree_key == NULL) { // Empty key
		return MMP_AUDIO_ERR_PARAMETER;
    }

	if (*forest_root == NULL) {
		PRINTF("===Node should not be NULL. error===\r\n");
		return MMP_AUDIO_ERR_PARAMETER;
	}

	// Start at the top of the forest
	pcurr_bfnode = forest_root;
	while (pcurr_bfnode) {
        #if (FS_INPUT_ENCODE == UCS2)
        d = strcmp_w(forest_key, (*pcurr_bfnode)->data);
        #elif (FS_INPUT_ENCODE == UTF8)
        d = STRCMP(forest_key, (*pcurr_bfnode)->data);
        #endif

        if (d == 0) {// Add to subtree
            // Insert nodes to 2nd tree
            return MMPD_AUDIODB_BTreeInsertSingle(&((*pcurr_bfnode)->metadata_root)
                                            , &((*pcurr_bfnode)->usMetadataCount), tree_key, db_pos);
        }

    	if (d > 0)
    		pcurr_bfnode = &((*pcurr_bfnode)->right);
    	else
    		pcurr_bfnode = &((*pcurr_bfnode)->left);

    	if (*pcurr_bfnode == NULL) {
			PRINTF("===Node should not be NULL. error===\r\n");
			return MMP_AUDIO_ERR_PARAMETER;
    	}
	}
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestInsert
//  Description : 
//=========================================================================
/**
 @brief Iteratively create forest
 @param[in] forest_key: for 1st level sort, may NULL
 @param[in] tree_key: for 2nd level sort, not NULL
 */
MMP_ERR MMPD_AUDIODB_BForestInsert(MMPD_AUDIODB_BFNODE **forest_root, MMP_BYTE *forest_key
                        ,MMP_BYTE *tree_key, MMP_ULONG db_pos, MMP_ULONG *pulNodeCounter)
{
    MMPD_AUDIODB_BFNODE     **pcurr_bfnode;
	MMPD_AUDIODB_BTNODE 	*new_node;
	MMP_LONG	            d;

    if (tree_key == NULL) { // Empty key
		return -1;
    }

	if (*forest_root == NULL) {

        if (((*forest_root) = (MMPD_AUDIODB_BFNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BFNODE))) == NULL) {
            return -1;
        }
        
        *pulNodeCounter = *pulNodeCounter + 1; // Increament node counter
        // Initialize forest node
        (*forest_root)->left  = NULL;
        (*forest_root)->right = NULL;
        (*forest_root)->root  = NULL;
        (*forest_root)->metadata_root   = NULL;
        (*forest_root)->usMetadataCount = 0;
        (*forest_root)->usTreeNodeNumber = 0;
        #if (FS_INPUT_ENCODE == UCS2)
        strcpy_w((*forest_root)->data, forest_key);
        #elif (FS_INPUT_ENCODE == UTF8)
        STRCPY((*forest_root)->data, forest_key);
        #endif

        if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
			return NULL;
		}

		new_node->left = new_node->right = NULL;
	    new_node->ulFileOffset = db_pos;
	    new_node->usLifeTime = 1;
		#if (FS_INPUT_ENCODE == UCS2)
		strcpy_w(new_node->data, tree_key);
		#elif (FS_INPUT_ENCODE == UTF8)
		STRCPY(new_node->data, tree_key);
		#endif

        (*forest_root)->usTreeNodeNumber++;
        return MMPD_AUDIODB_BTreeInsert(&((*forest_root)->root), new_node);
	}

	// Start at the top of the forest
	pcurr_bfnode = forest_root;
	while (pcurr_bfnode) {
        #if (FS_INPUT_ENCODE == UCS2)
        d = strcmp_w(forest_key, (*pcurr_bfnode)->data);
        #elif (FS_INPUT_ENCODE == UTF8)
        d = STRCMP(forest_key, (*pcurr_bfnode)->data);
        #endif

        if (d == 0) {// Add to subtree
            if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
    			return NULL;
    		}

    		new_node->left = new_node->right = NULL;
    	    new_node->ulFileOffset = db_pos;
    	    new_node->usLifeTime = 1;
    		#if (FS_INPUT_ENCODE == UCS2)
    		strcpy_w(new_node->data, tree_key);
    		#elif (FS_INPUT_ENCODE == UTF8)
    		STRCPY(new_node->data, tree_key);
    		#endif

            (*pcurr_bfnode)->usTreeNodeNumber++;
            return MMPD_AUDIODB_BTreeInsert(&((*pcurr_bfnode)->root), new_node);
        }

    	if (d > 0)
    		pcurr_bfnode = &((*pcurr_bfnode)->right);
    	else
    		pcurr_bfnode = &((*pcurr_bfnode)->left);

        if (*pcurr_bfnode == NULL) {
            if ((*pcurr_bfnode = (MMPD_AUDIODB_BFNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BFNODE))) == NULL) {
                return -1;
            }
            
            *pulNodeCounter = *pulNodeCounter + 1; // Increament node counter
            // Initialize forest node
    		(*pcurr_bfnode)->left  = NULL;
    		(*pcurr_bfnode)->right = NULL;
            (*pcurr_bfnode)->root  = NULL;
            (*pcurr_bfnode)->metadata_root      = NULL;
            (*pcurr_bfnode)->usMetadataCount    = 0;
            (*pcurr_bfnode)->usTreeNodeNumber = 0;
            #if (FS_INPUT_ENCODE == UCS2)
            strcpy_w((*pcurr_bfnode)->data, forest_key);
            #elif (FS_INPUT_ENCODE == UTF8)
            STRCPY((*pcurr_bfnode)->data, forest_key);
            #endif

            if ((new_node = (MMPD_AUDIODB_BTNODE *)AUDIODB_MALLOC(sizeof(MMPD_AUDIODB_BTNODE))) == NULL) {
    			return NULL;
    		}	

    		new_node->left = new_node->right = NULL;
    	    new_node->ulFileOffset = db_pos;
    	    new_node->usLifeTime = 1;
    		#if (FS_INPUT_ENCODE == UCS2)
    		strcpy_w(new_node->data, tree_key);
    		#elif (FS_INPUT_ENCODE == UTF8)
    		STRCPY(new_node->data, tree_key);
    		#endif

    		(*pcurr_bfnode)->usTreeNodeNumber++;
    		return MMPD_AUDIODB_BTreeInsert(&((*pcurr_bfnode)->root), new_node);
    	}
	}
	return MMP_ERR_NONE;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_SetBForestWalk
//  Description : 
//=========================================================================
/** @brief Set the binary tree walk action

@param[in] ulStart : start entry to do the action (start from 0) 
@param[in] ulEnd : end entry to do the action
@param[in] action : action to do
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SetBForestWalk(MMP_ULONG ulStart, MMP_ULONG ulEnd, MMPD_AUDIODB_BFACTION *action)
{
	m_ulBForestStart = ulStart;
	m_ulBForestEnd = ulEnd;
	m_ulBForestCurrentCount = 0;
	m_bforestaction = action;
	
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestWalk
//  Description : 
//=========================================================================
/** @brief Set the binary tree walk action

@param[in] ulStart : start entry to do the action (start from 0) 
@param[in] ulEnd : end entry to do the action
@param[in] action : action to do
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BForestWalk(MMPD_AUDIODB_BFNODE *bfnode)
{
    if (bfnode == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BForestWalk(bfnode->left);
	if (m_ulBForestCurrentCount >= m_ulBForestStart) {
		if (m_ulBForestCurrentCount < m_ulBForestEnd) {
			m_bforestaction(bfnode);
		}
		else {
			return	MMP_ERR_NONE;
		}
	}
	m_ulBForestCurrentCount++;


	MMPD_AUDIODB_BForestWalk(bfnode->right);
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestFilter
//  Description : 
//=========================================================================
/** @brief Set the binary tree walk action

@param[in] ulStart : start entry to do the action (start from 0) 
@param[in] ulEnd : end entry to do the action
@param[in] action : action to do
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BForestFilter(MMPD_AUDIODB_BFNODE *bfnode)
{
    if (bfnode == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BForestFilter(bfnode->left);
	m_bforestaction(bfnode);
	MMPD_AUDIODB_BForestFilter(bfnode->right);
	return MMP_ERR_NONE;
}


//=========================================================================
//  Function    : MMPD_AUDIODB_SetBTreeIndex
//  Description : 
//=========================================================================
/** @brief Search node for delete, set the search range

@param[in] ulStart : start index
@param[in] ulEnd : end index
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_SetBTreeIndex(MMP_ULONG ulStart, MMP_ULONG ulEnd)
{
	m_ulBTreeStart = ulStart;
	m_ulBTreeEnd = ulEnd;
	m_ulBTreeCurrentCount = 0;

	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BTreeIndexSearch
//  Description : 
//=========================================================================
/** @brief Search node for delete

@param[in] node : input node
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_AUDIODB_BTreeIndexSearch(MMPD_AUDIODB_BTNODE **node)
{
    if ((node == NULL) || (*node == NULL))
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BTreeIndexSearch(&((*node)->left));
	if (m_ulBTreeCurrentCount >= m_ulBTreeStart) {
		if (m_ulBTreeCurrentCount < m_ulBTreeEnd) {
			m_returnTreeNodeLocator = node;
		}
		else {
			return	MMP_ERR_NONE;
		}
	}
	m_ulBTreeCurrentCount++;
	MMPD_AUDIODB_BTreeIndexSearch(&((*node)->right));
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_GetBTreeNodeLocator
//  Description : 
//=========================================================================
/** @brief Search node for delete

@param[in] treenode : root node of the tree 
@param[in] ulIndex : index of the tree
@retval MMP_ERR_NONE Success.
*/
MMPD_AUDIODB_BTNODE **MMPD_AUDIODB_GetBTreeNodeLocator(MMPD_AUDIODB_BTNODE **treenode, MMP_ULONG ulIndex)
{
	m_returnTreeNodeLocator = NULL;

	MMPD_AUDIODB_SetBTreeIndex(ulIndex, ulIndex + 1);
	MMPD_AUDIODB_BTreeIndexSearch(treenode);
	
	return m_returnTreeNodeLocator;
}
// Forest Index Search Related
MMP_ERR MMPD_AUDIODB_SetBForestIndex(MMP_ULONG ulStart, MMP_ULONG ulEnd)
{
	m_ulBForestStart = ulStart;
	m_ulBForestEnd = ulEnd;
	m_ulBForestCurrentCount = 0;

	return MMP_ERR_NONE;
}
MMP_ERR MMPD_AUDIODB_BForestIndexSearch(MMPD_AUDIODB_BFNODE **node)
{
    if ((node == NULL) || (*node == NULL))
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BForestIndexSearch(&((*node)->left));
	if (m_ulBForestCurrentCount >= m_ulBForestStart) {
		if (m_ulBForestCurrentCount < m_ulBForestEnd) {
			m_returnForestNodeLocator = node;
		}
		else {
			return	MMP_ERR_NONE;
		}
	}
	m_ulBForestCurrentCount++;

	MMPD_AUDIODB_BForestIndexSearch(&((*node)->right));
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_GetBForestNodeLocator
//  Description : 
//=========================================================================
/** @brief Search node for delete

@param[in] forestnode : root node of the forest 
@param[in] ulIndex : index of the tree
@retval MMP_ERR_NONE Success.
*/
MMPD_AUDIODB_BFNODE **MMPD_AUDIODB_GetBForestNodeLocator(MMPD_AUDIODB_BFNODE **forestnode, MMP_ULONG ulIndex)
{
	m_returnForestNodeLocator = NULL;

	MMPD_AUDIODB_SetBForestIndex(ulIndex, ulIndex + 1);
	MMPD_AUDIODB_BForestIndexSearch(forestnode);
	
	return m_returnForestNodeLocator;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_BForestWriteTree
//  Description : 
//=========================================================================
/** @brief Write the forest into files.

 @param[out] bfnode: The forest root node
 */

MMP_ERR MMPD_AUDIODB_BForestWriteTree(MMPD_AUDIODB_BFNODE *bfnode)
{
    if (bfnode == NULL)
		return MMP_ERR_NONE;

	MMPD_AUDIODB_BForestWriteTree(bfnode->left);
	#if (FS_INPUT_ENCODE == UCS2)
	print_ucs2("walk", bfnode->data);
	#endif
    PRINTF("Number of tree nodes = %d\n", bfnode->usTreeNodeNumber);
    PRINTF("Meta count = %d\n", bfnode->usMetadataCount);
	MMPD_AUDIODB_BTreeWalkForward(bfnode->root);
	MMPD_AUDIODB_BForestWriteTree(bfnode->right);
	return MMP_ERR_NONE;
}
//=========================================================================
//  Function    : MMPD_AUDIODB_DBCreateForest
//  Description : 
//=========================================================================
/** @brief Create forest tree

 @param[out] node: The forest root node
 @param[in] groupindex: sorting index
 @param[out] ulCount: forest node count
 */
MMPD_AUDIODB_BFNODE *MMPD_AUDIODB_DBCreateForest(MMPD_AUDIODB_OBJECT_PROPERTY groupindex, MMP_ULONG *ulNodeCounter)
{
    MMP_ULONG               DBFilePos = 0;
    MMP_BYTE                bTitle = MMP_FALSE;
    MMPD_AUDIODB_AUDIOINFO  infobuf;
	MMPD_AUDIODB_BFNODE     *forest_root = NULL;
    MMP_BYTE                *metadata = NULL;
    MMP_UBYTE   			*ubFileNamePos = NULL;
    MMP_LONG    			lLastSlash = 0;
    
    *ulNodeCounter = 0;

    m_groupIndex = groupindex;
    switch(groupindex) {
    case MMPD_AUDIODB_ALBUM:
        metadata = (MMP_BYTE*)(infobuf.bAlbum);
        break;
    case MMPD_AUDIODB_GENRE:
        metadata = (MMP_BYTE*)(infobuf.bGenre);
        break;
    case MMPD_AUDIODB_ARTIST:
    default:
        metadata = (MMP_BYTE*)(infobuf.bArtist);
    }

    // Creating Forest From DB
    for(DBFilePos = 0; DBFilePos < m_ulDataBaseFileSize; DBFilePos += sizeof(MMPD_AUDIODB_AUDIOINFO)) {
        MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&infobuf), DBFilePos, sizeof(MMPD_AUDIODB_AUDIOINFO));
        // Use file name to sort if 'title' not in metadata
        // Copy Unkown to metadata if 'metadata' used for 1st sorting is empty
        #if (FS_INPUT_ENCODE == UCS2)
		bTitle = (*(MMP_SHORT*)infobuf.bTitle == 0x0000)? MMP_FALSE: MMP_TRUE;
		if (*(MMP_SHORT*)metadata == 0x0000)
			strcpy_w(metadata, "U\0n\0k\0n\0o\0w\0n\0\0\0"); // 'Unknow' UCS2 format
        #elif (FS_INPUT_ENCODE == UTF8)
		bTitle = (infobuf.bTitle[0] == 0x00)? MMP_FALSE: MMP_TRUE;
		if (*metadata == 0x00)
			STRCPY(metadata, "Unknown");
        #endif
//        print_ucs2("Read Group", metadata);

        if (bTitle == MMP_FALSE) {
            ubFileNamePos = infobuf.ubFullFileName;
            lLastSlash = -2;
            // Find last '\' in full file name
            while(*(MMP_USHORT*)ubFileNamePos != 0x0000) {
	            #if (FS_INPUT_ENCODE == UCS2)
                if ((ubFileNamePos[0] == '\\') && (ubFileNamePos[1] =='\0'))
                #elif (FS_INPUT_ENCODE == UTF8)
                if(*ubFileNamePos == '\\')
                #endif
                    lLastSlash = (MMP_ULONG)ubFileNamePos - (MMP_ULONG)infobuf.ubFullFileName;
                ubFileNamePos   += 2;
            }
//            print_ucs2("Read Filename", (MMP_BYTE*)(infobuf.ubFullFileName+(lLastSlash+2)));
            MMPD_AUDIODB_BForestInsert(&forest_root, metadata, (MMP_BYTE*)(infobuf.ubFullFileName+(lLastSlash+2)), DBFilePos, ulNodeCounter);
        }
        else { // Use 'title' to sort
//            print_ucs2("Read Title", (MMP_BYTE*)(infobuf.bTitle));
            MMPD_AUDIODB_BForestInsert(&forest_root, metadata, (MMP_BYTE*)(infobuf.bTitle), DBFilePos, ulNodeCounter);
        }
    }

    return forest_root;
}

//=========================================================================
//  Function    : MMPD_AUDIODB_DBMetadataCount
//  Description : 
//=========================================================================
/** @brief Insert the second tree into the original tree

 @param[out] forest_root: The forest root node
 @param[in] groupindex: sorting index
 @param[out] itemindex: second sorting index
 */
MMP_ERR MMPD_AUDIODB_DBMetadataCount(MMPD_AUDIODB_BFNODE *forest_root, MMPD_AUDIODB_OBJECT_PROPERTY groupindex, 
                                    MMPD_AUDIODB_OBJECT_PROPERTY itemindex)
{
    MMP_ULONG               DBFilePos = 0;
    MMPD_AUDIODB_AUDIOINFO  infobuf;
    MMP_BYTE                *groupdata = NULL, *itemdata = NULL;

    switch(groupindex) {
    case MMPD_AUDIODB_ALBUM:
        groupdata = (MMP_BYTE*)(infobuf.bAlbum);
        break;
    case MMPD_AUDIODB_GENRE:
        groupdata = (MMP_BYTE*)(infobuf.bGenre);
        break;
    case MMPD_AUDIODB_ARTIST:
    default:
        groupdata = (MMP_BYTE*)(infobuf.bArtist);
    }

    switch(itemindex) {
    case MMPD_AUDIODB_ALBUM:
        itemdata = (MMP_BYTE*)(infobuf.bAlbum);
        break;
    case MMPD_AUDIODB_ARTIST:
    default:
        itemdata = (MMP_BYTE*)(infobuf.bArtist);
    }

    // Creating Forest From DB
    for(DBFilePos = 0; DBFilePos < m_ulDataBaseFileSize; DBFilePos += sizeof(MMPD_AUDIODB_AUDIOINFO)) {
        MMPD_AUDIODB_ReadFile((MMP_UBYTE *)(&infobuf), DBFilePos, sizeof(MMPD_AUDIODB_AUDIOINFO));
        // Use file name to sort if 'title' not in metadata
        // Copy Unkown to metadata if 'metadata' used for 1st sorting is empty
        #if (FS_INPUT_ENCODE == UCS2)
		if (*(MMP_SHORT*)itemdata == 0x0000)
		    strcpy_w(itemdata, "U\0n\0k\0n\0o\0w\0n\0\0\0"); // 'Unknow' UCS2 format
		if (*(MMP_SHORT*)groupdata == 0x0000)
			strcpy_w(groupdata, "U\0n\0k\0n\0o\0w\0n\0\0\0"); // 'Unknow' UCS2 format
        #elif (FS_INPUT_ENCODE == UTF8)
        if (itemdata[0] == 0x00)
            STRCPY(itemdata, "Unknown");
		if (*groupdata == 0x00)
			STRCPY(groupdata, "Unknown");
        #endif
        //print_ucs2("_group", groupdata);
        //print_ucs2("_album", itemdata);
        MMPD_AUDIODB_BForestInsertSingle(&forest_root, groupdata, itemdata, DBFilePos);
    }

    return MMP_ERR_NONE;
}
#endif
