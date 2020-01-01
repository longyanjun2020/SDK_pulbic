//==============================================================================
/**
 @file AHC_DCF.c
 @brief Diamond 3GP Recorder Control Function
 @author Will Tseng
 @version 1.0
*/


#if 0
void __HEADER__(){}
#endif

#include "AHC_Config_SDK.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "aihc_dcf.h"
#include "aihc_browser.h"
#include "ahc_fs.h"
#include "ahc_media.h"
#include "ahc_parameter.h"
#include "ait_utility.h"
#include "mmps_system.h"

#if (GPS_CONNECT_ENABLE)
#include "gps_ctl.h"
#endif

#if 1//(DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)

#define DCF_ROOT_NAME_LEN		(16)
#define DCF_RESET_VALUE			(0)
#define DCF_INVALID_NUMBER_8	(0xFF)       ///< for 8  bits 
#define DCF_INVALID_NUMBER_16	(0xFFFF)     ///< for 16 bits 
#define DCF_INVALID_NUMBER_32	(0xFFFFFFFF) ///< for 32 bits 

#define DCF_BOSS_EQUAL			(0)
#define DCF_BOSS_1				(1)
#define DCF_BOSS_2				(2)

/**
@brief

------------------------------
tag1. DCFx
tag2. number

tag3. root name
tag4. kill dir key & file key
tag5. file control dir key & file key
tag6. Lock file free char
tag7. data
tag8. check sum

total size = 32 byte
------------------------------
------------------------------
offset = 32.
length (4 byte) = x = DCFX_ROOTNAME_SIZE = DCF_ROOT_NAME_LEN
root name (x byte) = 16 byte
20 byte
------------------------------
offset = 52.
length (4 byte) = x = 2 = DCFX_KEY_LENGTH
kill dir key (x byte) = 2 byte
kill file key (x byte) = 2 byte
8 byte
------------------------------
offset = 60.
length (4 byte) = x = 2 = DCFX_KEY_LENGTH
filectl dir key (x byte) = 2 byte
filectl file key (x byte) = 2 byte
8 byte
------------------------------
offset = 68.
length (flexible size) = x = DCFX_LOCKNAME_SIZE (replace by m_DcfDB[m_uiDBIndex].byFileFreeCharNum)
lock name (x byte) = 4 byte
8 byte
------------------------------
offset = 76.
length (4 byte) = x = DCFX_DATA_SIZE
4 byte
------------------------------
80

DATA

*/
#define DCFX_HEADER_PATTERN 	"DCFx"
#define DCFX_TAG_NUMBER			(5)
#define DCFX_TAG_SIZE			(4)
#define DCFX_HEADER_SIZE		(32)

#define DCFX_ROOTNAME_OFFSET	(2)
#define DCFX_ROOTNAME_SIZE		DCF_ROOT_NAME_LEN

#define DCFX_KILL_KEY_OFFSET	(3)
#define DCFX_FILECTL_KEY_OFFSET	(4)
#define DCFX_KEY_SIZE			(2)

#define DCFX_LOCKNAME_OFFSET	(5)
//#define DCFX_LOCKNAME_SIZE	FILE_FREE_CHAR_NUMBER//(4)

#define DCFX_DATA_OFFSET		(6)
#define DCFX_DATA_SIZE			(36)
/**
@brief	5*4 + 16 + 4*2 + 4 = 20 + 16 + 8 + 4 = 48

*/
//#define DCFX_REGION_SIZE		(DCFX_TAG_NUMBER*DCFX_TAG_SIZE + DCFX_ROOTNAME_SIZE + 4*DCFX_KEY_SIZE + DCFX_LOCKNAME_SIZE)

#define DCFX_TIME_LENGTH		(6)
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
typedef enum _DCF_REGION_ID
{
	DCF_REGION_ID_2  = 2,	///< 2G
	DCF_REGION_ID_4  = 4,	///< 4G
	DCF_REGION_ID_8  = 8,	///< 8G
	DCF_REGION_ID_16 = 16,	///< 16G
	DCF_REGION_ID_32 = 32,	///< 32G
	DCF_REGION_ID_64 = 64,	///< 64G
	DCF_REGION_ID_128 = 128	///< 128G

}DCF_REGION_ID;


typedef struct _DCFX_DB_INFO
{
	
	UINT32 uiRootNameOffset;
	//UINT32 uiRootNameSize;
	
	UINT32 uiKillCtlOffset;
	//UINT32 uiKillCtlSize;
	
	UINT32 uiFileCtlOffset;
	//UINT32 uiFileCtlSize;
	
	UINT32 uiLockFileOffset;
	//UINT32 uiLockFileSize;
	
	UINT32 uiDataOffset;
	//UINT32 uiDataSize;

}DCFX_DB_INFO;


#define DCFX_PAGE_DIRTY	(1)
#define DCFX_PAGE_CLEAR	(0)



// 40 byte
typedef struct _DCFX_DB_DATA{
	
	UINT16				uwPrevPos;	///< 2 bytes
	UINT16				uwNextPos;	///< 2 bytes
	UINT16				uwCurPos;	///< 2 bytes
	UINT16				byPadding1;	///< 2 bytes
	
	INT8 				chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];	///< 6 bytes,
	UINT16				uwDirKey;	///< 2 bytes
	/**
	@brief	the size of this string will be count as 6 not 5.
	*/
	INT8 				chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];	///< 5 bytes,
	
	UINT16				uwFileKey;	///< 2 bytes
	//UINT8				byPadding2;	///< 1 bytes

	AHC_FS_FILETIME		sFileTime;	///< 12 bytes.
	UINT32				uiFileSize;	///< 4 bytes.
	
}DCFX_DB_DATA;


typedef enum _DCF_DIR_MOUNT_TYPE
{
	DCF_DIR_MOUNT_TYPE_UNMOUNT  = 0x01,	///< the dir node is unmounted
	DCF_DIR_MOUNT_TYPE_MIN   = 0x02,	///< the min range of dir node
	DCF_DIR_MOUNT_TYPE_MAX   = 0x04,	///< the max range of dir node
	DCF_DIR_MOUNT_TYPE_KEY   = 0x08,	///< the key range of dir node
	DCF_DIR_MOUNT_TYPE_ALL   = 0x10,	///< the all range of dir node
	DCF_DIR_MOUNT_TYPE_MASK  = 0x1F
	
}DCF_DIR_MOUNT_TYPE;

/**
@brief total size of one file node is 20 bytes.
       ex: the total number of file nodes in one dir is 500
           the total number of dir nodes is 900
           total size of all the dir node is 900*500*20 = 9,000,000 = 8.1 MB
*/
typedef struct _DCF_FILE_NODE{
	/**
	@brief	the size of this string will be count as 6 not 5.
	*/
    INT8                    chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];    ///< 5 byte, 
    UINT16                  uwFileKey;		///< 2 byte, the key number
    UINT8                   byFileType;		///< 1 byte, file type, file extension.
	UINT8					byPadding[3];
	
    struct _DCF_FILE_NODE   *psPrev;		///< 4 byte, the previous file node
    struct _DCF_FILE_NODE   *psNext;		///< 4 byte, the next file node
    struct _DCF_FILE_NODE   *psNeighbor;	///< 4 byte, the same key number file node

} DCF_FILE_NODE;

/**
@brief total size of one dir node is 36 bytes.
       ex: the total number of dir nodes is 900
           total size of all the dir node is 900*36 = 32400 = 32kB
*/
typedef struct _DCF_DIR_NODE{

    UINT16                  uwDirKey;        ///< 2 byte, the key number of dir
    UINT16                  uwFileNodeCount; ///< 2 byte, the number of file node in the dir. 
    /**
    @brief	the two key below are used to maintain the file name. 
    		So plz do not use them for other case.
    */
    UINT16                  uwMaxFileKey;    ///< 2 byte, the max. key number of current file node which we added.
    UINT16                  uwNextFileKey;   ///< 2 byte, the next key number of file node which is used by cyclic record.
    
    DCF_FILE_NODE           *psRootFileNode; ///< 4 byte, the first file node in the dir.
    DCF_FILE_NODE           *psLastFileNode; ///< 4 byte, the last file node in the dir. 
    
    struct _DCF_DIR_NODE    *psPrev;         ///< 4 byte, the previous dir node
    struct _DCF_DIR_NODE    *psNext;         ///< 4 byte, the next dir node
    
    INT8                    chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];  ///< 6 byte, the free char of dir.
    /**
    DCF_DIR_MOUNT_TYPE
    */
    UINT8                   byMountMode;	///< 1 byte, the mount type of dir node
    UINT8                   byPadding;		///< 1 byte, use the cyclic file name of file node or not.

} DCF_DIR_NODE;

// 28 900*32 = 28800 = 29kB
typedef struct _DCF_OBJ_COUNT{

    UINT16      uwFileCountInFileType[MAX_DCF_SUPPORT_FILE_TYPE]; ///< 28 byte, the nubmer of file in the same filetype.
    UINT16		uwNonLockFileCount;	///< 2 byte,
	UINT16		uwDCFxFileCount;	///< 2 byte,

}DCF_OBJ_COUNT;

typedef struct _DCF_MEM_CTL{

    UINT8   *pMemPool;  ///< the start address of dir/file node memory pool.
    UINT32  uiMemOffset;///< the offset of used dir/file node memory pool.
    UINT32  uiMemSize;  ///< the max. size of dir/file node memory pool.
    UINT32  uiFreeMem;  ///< the free size of dir/file node memory pool.
    UINT32  uiMaxCount;
    UINT32  uiNodeSize;
}DCF_MEM_CTL;


typedef struct _DCF_FILE_MAP{
    
    UINT8   *pbyMapAddr;
    UINT32  uiMapSize;

}DCF_FILE_MAP;

typedef struct _DCF_SEARCH_CACHE{
    
    UINT32  *puiCacheAddr;
    UINT32  uiCacheSize;
    UINT32  uiSlotCount;
    UINT32  uiSlotSize;

}DCF_SEARCH_CACHE;

typedef struct _DCF_DATABASE{

    DCF_DIR_NODE    *psRootDirNode;		///< 4 byte, the root node of dir. 
    DCF_DIR_NODE    *psLastDirNode;		///< 4 byte, the end node of dir.
    /**
    @brief functional dir node.
    
    */
    DCF_DIR_NODE    *psPowerDirNode;	///< 4 byte, the current node of dir.
    DCF_DIR_NODE    *psFileCtlDirNode;	///< 4 byte, new-added file name is controlled by this dir node.
    DCF_DIR_NODE    *psBrowserDirNode;	///< 4 byte, no use now. just for flexible.

    UINT16          uwFileCtlDirKey;			///< 2 byte, the new-added dir key.
    UINT16          uwFileCtlFilekey;			///< 2 byte, the new-added file key.
    
    UINT16          uwKillDirKey;				///< 2 byte, the next kill dir key.
    UINT16          uwKillFileKey;				///< 2 byte, the next kill file key.
    
    UINT32			uiReadOnlyRegionCluster;	///< 4 byte, the memory space of read only file.
    UINT32			uiDCFxRegionCluster;		///< 4 byte, the memory space of Name Lock file.
    UINT32			uiNonLockRegionCluster;		///< 4 byte, the memory space of Non Lock file.

    UINT32          uiCurDirCountInDB;			///< 4 byte, the number of dir in the DCF database.
    /**
    @brief 14*4 = 52 byte, the total number of all the object of the same file type in the database.
    
    */
    UINT32          uiTotalFileCountInFileType[MAX_DCF_SUPPORT_FILE_TYPE];    
    
    /**	
    @brief	900*2 = 1800 byte, the count of file. not the count of file nodes.
    		the default value is DCF_INVALID_NUMBER_16 and DCF_INVALID_NUMBER_16 means no obj at this dir. 
    		MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1 = 999 - 100 + 1 = 900. 
    		900*2 = 1.76kB
	*/
    UINT16          uwTotalFileCountInDir[MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1];
    
    UINT32          uiBrowserIndex;
    UINT32          uiClustersTH;
    /**
    @brief  AIHC_DcfMountDB() will allocate the memory for all the dir.
    		this parameter can keep the total number of all the object of the same file type in the same dir.
    		dir number * ALIGN32(sizeof(DCF_OBJ_COUNT)) = 900 * 32 = 28800 = 29kB
    */
    DCF_OBJ_COUNT   **ppsFileCountInDir;
    /**
    @brief	the file map for power dir node.
    */
    DCF_FILE_MAP    sFileMap;
    /**
    @brief	the search cache for power dir node.
    */
    DCF_SEARCH_CACHE sSearchCache;
    
    /**	@brief	@ref AIHC_DcfMountDB() and DCF_DEFAULT_DIR_FREECHAR. 
			DCF directory naming : directory number + Free characters(5 alphanumerics).
			ex: 100ABCDE .*/
    INT8    chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];


    /**	@brief	@ref AIHC_DcfMountDB() and DCF_DEFAULT_FILE_FREECHAR.
			DCF file naming : Free(4 alphanumerics) + file number.
			ex: ABCD0001 .*/
    INT8    chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    
    /*
    static INT8         m_strDcfRootName[DCF_ROOT_NAME_LEN]  = "SM:\\DCIM";//"SD:\\DCIM";// Mark
    */
    INT8    chRootName[DCF_ROOT_NAME_LEN];
    
    /**
    @brief 	AHC_DCF_SetFreeChar() set the allowed file type dynamically. 
    		when enter different browser mode, you can count the number of file which you want to support.

    */
    INT8    chAllowedFileType[MAX_DCF_SUPPORT_FILE_TYPE];
    /**
    @brief  length and numbers of DirName and FileName
            these vars would be calculated by DCF_DEFAULT_DIR_FREECHAR DCF_DEFAULT_FILE_FREECHAR in AHC_Config_SDK.h
    */
    UINT8    byDirFreeCharNum;
    UINT8    byDirCharLength;
    UINT8    byFileFreeCharNum;
    UINT8    byFileCharLength;
    
    
} DCF_DATABASE;

typedef struct _DCF_SUBDB{

    DCF_FILE_NODE   *psRootFileNode;		///< 4 byte, the root node of dir. 
    DCF_FILE_NODE   *psLastFileNode;		///< 4 byte, the end node of dir.
    DCF_FILE_NODE   *psFileCtlFileNode;		///< 4 byte, the root node of dir. 
    DCF_FILE_NODE   *psKillFileNode;		///< 4 byte, the end node of dir.
    
    UINT32			uiCluster;		///< 4 byte, the memory space of file.
    UINT32          uwTotalFileCount;
    UINT32          uiBrowserIndex;
    INT8            chRootDirName[DCF_ROOT_NAME_LEN+1];
} DCF_SUBDB;

#if 0		 
void __VARIABLES__(){}
#endif
static DCF_DB_TYPE  m_sDBType;
static UINT32       m_uiDBIndex = 0;
static DCF_STORAGE_ALLOC m_AllocType = DCF_STORAGE_ALLOC_TYPE0;
static AHC_BOOL     m_bEnableBackground = AHC_TRUE;//AHC_FALSE;

#if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT!=LOCK_FILE_STOP)
extern UINT32	m_ulLockFileNum;
UINT32          m_ulLockFileTable[MAX_LOCK_FILE_NUM] = {0};
#endif

/**
@brief mount the DCF database or not.
*/
static AHC_BOOL     m_bMountDCF[DCF_DB_COUNT] = {AHC_FALSE};

static AHC_BOOL     m_bEnableDCF[DCF_DB_COUNT] = {AHC_TRUE};

static DCF_DATABASE m_DcfDB[DCF_DB_COUNT] = {0};



/**	@brief	@ref: AIHC_DcfMountDB(), the address of memory pool of DCF. 
			memory map : m_DcfDB.FileTypeCount */
static UINT32       m_ulDcfMemPool		= 0;

/**	@brief	@ref: AIHC_DcfMountDB(). the buffer allocation of DCF directory. 
*/
static DCF_MEM_CTL  m_sDirMem;

/**	@brief	@ref: AIHC_DcfMountDB(). the buffer allocation of DCF file.
*/
static DCF_MEM_CTL  m_sFileMem;


/**
@brief	make the page of name-locked file when you mount the DCF DB.

*/
static AHC_BOOL		m_bParsePage = AHC_FALSE;


static DCF_FILE_PROTECT m_sCyclicDeletedMask			= DCF_FILE_PROTECT_CHARLOCK|DCF_FILE_PROTECT_READONLY;
static DCF_FILE_PROTECT m_sFileDeletedMask				= DCF_FILE_PROTECT_CHARLOCK|DCF_FILE_PROTECT_READONLY;

static AHC_FS_FILETIME    m_sCyclicDeletedStartTime		= {0};
static AHC_FS_FILETIME    m_sCyclicDeletedEndTime		= {0};

static UINT32       m_ulMaxDcfDirNum    = MAX_DCF_DIR_NUM;
static UINT32       m_ulMaxDcfFileInDir = MAX_DCF_FILE_NUM;
/**
@brief count the file with attribute of hidden or not.
*/
static AHC_BOOL     m_bCountHiddenObj   = AHC_TRUE;
/**
@brief count the file with the limitation of m_ulFilterDate or not.
*/
static AHC_BOOL     m_bFilterByDate     = AHC_FALSE;
static UINT32       m_ulFilterDate[3];//YYYY / MM / DD


/**
@brief all the supported file type

*/
const INT8 			m_DcfSupportFileType[MAX_DCF_SUPPORT_FILE_TYPE][4]  = {	"JPG","TIF","AVI",
																			"MOV","MP4","3GP",
																			"WMV","MP3","OGG",
																			"WMA","WAV","ASF",
																			"THM","RAW","AAC",
																			"TS"};
																			
#if (GPS_CONNECT_ENABLE == 1)
    #if ((GPS_RAW_FILE_ENABLE == 1) && (GPS_KML_FILE_ENABLE == 1))
        #define DCF_AUXILIARY_MAX_NUMBER    (2)
    #elif (GPS_KML_FILE_ENABLE == 1)
        #define DCF_AUXILIARY_MAX_NUMBER    (1)

    #elif (GPS_RAW_FILE_ENABLE == 1)
        #define DCF_AUXILIARY_MAX_NUMBER    (1)
    #else
    	#define DCF_AUXILIARY_MAX_NUMBER    (1)
    #endif
#else
    	#define DCF_AUXILIARY_MAX_NUMBER    (1)	//Fix compiler error for AIT_BOARD_C000_P001
#endif///< (GPS_CONNECT_ENABLE == 1)

#if (GPS_CONNECT_ENABLE == 1)
    #if ((GPS_RAW_FILE_ENABLE == 1) && (GPS_KML_FILE_ENABLE == 1))
        static INT8 m_chAuxiliaryFileType[DCF_AUXILIARY_MAX_NUMBER][5]  = { GPS_KML_FILE_EXTENTION,                                                                            
                                                                            GPS_RAW_FILE_EXTENTION};
                                                                                    
    #elif (GPS_KML_FILE_ENABLE == 1)
        static INT8 m_chAuxiliaryFileType[DCF_AUXILIARY_MAX_NUMBER][5]  = { GPS_KML_FILE_EXTENTION };

    #elif (GPS_RAW_FILE_ENABLE == 1)
        static INT8 m_chAuxiliaryFileType[DCF_AUXILIARY_MAX_NUMBER][5]  = { GPS_RAW_FILE_EXTENTION };
    #else
    	static INT8 m_chAuxiliaryFileType[DCF_AUXILIARY_MAX_NUMBER][5]  = { NULL };
    #endif
#else
    static INT8 m_chAuxiliaryFileType[DCF_AUXILIARY_MAX_NUMBER][5]  = { NULL }; //Fix compiler error for AIT_BOARD_C000_P001
#endif///< (GPS_CONNECT_ENABLE == 1)

static INT8         m_chAuxiliaryFileName[DCF_AUXILIARY_MAX_NUMBER][DCF_MAX_FILE_NAME_SIZE];
static INT8         m_chAuxiliaryFileNameTemp[DCF_AUXILIARY_MAX_NUMBER][DCF_MAX_FILE_NAME_SIZE];
/**
The info of media.
*/
AHC_FS_DISK_INFO m_sMediaInfo;
UINT32		    m_uiBytesPerCluster;
DCF_REGION_ID    m_sDCFRegionID	= DCF_REGION_ID_4;
/**
@brief the case(DCF_FILE_DELETE_ALL_CAM) of AHC_DCF_FileOperation().

*/
static INT8         m_DcfFileName[DCF_MAX_FILE_NAME_SIZE];

/*
confirm the max dir/file key and min dir/file key when parse files.
index 0 => min dir/file key
index 1 => max dir/file key
*/
static DCF_KEY_PAIR m_sParsedKillKey[2] = {0};

static AHC_BOOL m_bMountCallBack = AHC_FALSE;

static PFuncDCFMountCallBack *DCFMountCallBack = NULL;

AHC_UF_Callback  *AHC_DCF_CB_GetStorageAllocationSetting = NULL;

/****************************************** SUB DB S ****************************************************/
#if (DCF_SUB_DB == 1)

static AHC_BOOL     m_bTurnOnSubDB = AHC_FALSE;
/*
sub-Database.
*/
static AHC_BOOL     m_bMountSubDCF      = AHC_FALSE;

static DCF_SUBDB    m_DCFSubDB = {0};

static INT8         m_chSubFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1] = "EMER";


/*

*/
static DCF_MEM_CTL  m_sSubFileMem;
#endif///< (DCF_SUB_DB == 1)
/****************************************** SUB DB E ****************************************************/
/****************************************** DCFX S ****************************************************/
#if (DCF_DCFX == 1)
/**
@brief	the temp file attribute buffer for DCFx.
*/
static UINT32		m_uiDCFxBufSize			= 0;
static UINT32		m_uiDCFxPageInfoSize	= 16;
static UINT32		m_uiDCFxDataSize		= 40;
static UINT32		m_uiDCFxDataMaxCount	= 100;

/**


*/
static DCFX_PAGE_CTL m_sPageCtl = {0};

/**
@brief	the temp buffer stores the data from the sd card or 
		new data from new-added files.
*/
static UINT8*		m_pbyDCFxTempBuffer	= 0;

/**
@brief	the work index of the golden page buffer.

*/
static UINT32		m_uiGPWorkIndex	= 0;

/**
@brief	the golden page for the top 100 data.

*/

static DCFX_GOLDEN_PAGE_BUFFER	m_GoldenPage[DCF_GOLDEN_PAGE_NUMBER] = {0};

/**
@brief	the data for one item of m_pbyDCFxTempBuffer.
*/
static DCFX_DB_DATA m_sDCFxSwapData[2]	= {0};

static INT8         m_chLockedFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1]   = DCF_CHARLOCK_PATTERN;
#ifdef VIDEO_DEFAULT_FLIE_FREECHAR
static INT8         m_chUnLockedFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1] = VIDEO_DEFAULT_FLIE_FREECHAR;
#else
static INT8         m_chUnLockedFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1] = "MOV_";
#endif
/**
@brief	the file name of dcfx file in the storage
*/
static INT8         m_chDCFxDBName[DCF_MAX_FILE_NAME_SIZE]  = "SM:\\DCIM\\X1.DB";
/**
@brief	the file handler of dcfx file in the storage
*/
static UINT32		m_uiDCFxFileID;
/**
@brief	the file status of dcfx file in the storage
*/
static AHC_BOOL		m_bDCFxOpened = AHC_FALSE;

/**
@brief	the offset of each tag.
*/
static DCFX_DB_INFO	m_sDCFxDBInfo = {32, 52, 60, 68, 76};

/**
@brief	the boundary of locked file.
*/

static UINT32		m_uiDCFxBoundary = 0;

#endif///< (DCF_DCFX == 1)
/****************************************** DCFX E ****************************************************/

/************************************Cahce Date of Get Info*************************************/
static DCF_INFO_CACHE InfoCacheData[DCF_GETINFO_CACHE_COUNT];

//==============================================================================
//
//                              INTERNAL FUNCTION PROTOTYPES
//
//==============================================================================
static UINT8 AIHC_DCF_WhichIsBoss(void *pPtr1, void *pPtr2, UINT32 uiLength);
static AHC_BOOL AIHC_DCF_AddDirNode(INT8 *pchDirName);
static AHC_BOOL AIHC_DCF_AddFileNode(DCF_DIR_NODE *psDirNode, DCF_FILE_NODE *psNewFileNode);
static AHC_BOOL AIHC_DCF_RemoveFileNode(DCF_DIR_NODE *psDirNode, DCF_FILE_NODE *psFileNode, AHC_BOOL bKeepMap);
static AHC_BOOL AIHC_DCF_UnmountDirNode(DCF_DIR_NODE *psDirNode, UINT16 uwDirKey, INT8 *pchDirName);
static AHC_BOOL AIHC_DCF_FindMinDirNode(UINT32 uiDBIndex, DCF_DIR_NODE **pDir, UINT8 byMountMode);
static AHC_BOOL AIHC_DCF_FindMinFileNode(UINT32 uiDBIndex, DCF_DIR_NODE  *psSearchDirNode, DCF_FILE_NODE **ppsFile);
static AHC_BOOL AIHC_DCF_FindDir(INT8 *pchDirName, UINT16 uwDirKey, DCF_DIR_NODE **ppsDir);
static AHC_BOOL AIHC_DCF_ChangeFileCtlDirNode(UINT16* puwDirKey, UINT16* puwFileKey, UINT8 *bCreateNewDir);
static AHC_BOOL AIHC_DCF_DeleteDir(DCF_DIR_NODE *psDirNode);
static AHC_BOOL AIHC_DCF_ClearEmptyDir(INT8* pchDirName, DCF_DIR_NODE *psDirNode);
static AHC_BOOL AIHC_DCF_ParseFile(	DCF_DIR_NODE *psDirNode, 
									INT8         *pchDirName, 
									UINT16       uwFileMaxCount,
									UINT16       uwTargetFilekey,
									DCF_DIR_MOUNT_TYPE type );

static void AIHC_DCF_ClearSearchCache(UINT32 uiDBIndex);

static AHC_BOOL AIHC_DCF_SetOneInFileMap(UINT16 uwFileKey, UINT8 byFileType);
static AHC_BOOL AIHC_DCF_CompareFileMap(UINT16 uwFileKey, UINT8 byNewFileType, UINT8* byOldFileType);
static void AIHC_DCF_ClearCompareFileMap(UINT32 uiDBIndex);
static AHC_BOOL AIHC_DCF_FindHoleInFileMap(UINT16 uwFileKeySt, UINT16 uwFileKeyEnd, UINT16* uwFileKey);
static AHC_BOOL AIHC_DCF_GetTypeInFileMap(UINT16 uwFileKey, UINT8* byFileType);
static AHC_BOOL AIHC_DCF_CalculateCluster(	INT8* 				pchFileFreeChar, 
											AHC_FS_ATTRIBUTE*	sFileAttribute, 
											UINT32				uiFileSize, 
											UINT16				uwDirKey, 
											AHC_BOOL			bAdd);


AHC_BOOL AIHC_DCF_DeleteFile(UINT16 uwDirKey, UINT16 uwFileKey, INT8 *pchFileName);
AHC_BOOL AIHC_DCF_CyclicDeletedMask(INT8* pchFileName, AHC_FS_ATTRIBUTE* sFileAttribute, AHC_FS_FILETIME* sFileTime);
#if (DCF_DCFX == 1)
AHC_BOOL AIHC_DCF_OpenDCFxFile(AHC_BOOL bOpen);
AHC_BOOL AIHC_DCF_WriteDCFxPage(void* pBufAddr);
static AHC_BOOL AIHC_DCF_UpdateDCFxPage(	DCF_DIR_NODE		*psDirNode, 
									INT8* 				pchFileFreeChar, 
									UINT16				uwFileKey,
									AHC_FS_ATTRIBUTE	sAttribute,
									AHC_FS_FILETIME     sFileTime,
									UINT32				uiFileSize);
static AHC_BOOL AIHC_DCF_ResetDCFxDB(UINT8 byIndex);
#endif ///< (DCF_DCFX == 1)

AHC_BOOL AHC_DCF_RegisterCallback(MMP_ULONG ulCBType, void *pCallback)
{
    switch(ulCBType) {
    case AHC_UFCB_GET_STORAGE_ALLOCATION_SETTING:
        AHC_DCF_CB_GetStorageAllocationSetting = (AHC_UF_Callback *)pCallback;
    break;
    }
    
    return AHC_TRUE;
}		

#if 0
void __MEMORY_API__(){}
#endif


#if (MEMORY_POOL_CTL == 0)
//temp
/**	@brief	the temp address of DCF buffer. need to confirm the buffer of OSD. */
UINT32 m_ulDCFTempBaseAddr = AHC_DCF_TEMP_BASE_ADDR;//0x4700000; //Rogers@20110926: HDMI browser switch mode.

void AIHC_SetTempDCFMemStartAddr(UINT32 addr) 
{
    m_ulDCFTempBaseAddr = addr;
}

void AIHC_GetTempDCFMemStartAddr(UINT32 *addr) 
{
    *addr = m_ulDCFTempBaseAddr;
}
#endif

/**
    @brief  Allocate memory pool for DCF APIs
    @param[in] ptr memory pointer
    @return MMP_ERR_NONE
*/
static void* AIHC_DcfMalloc(UINT32 size) {

    #if (MEMORY_POOL_CTL == 0)
    UINT8   *ptr;
    UINT32  mem_offset;
    UINT32  mem_align = 32;//32 byte align
        
    mem_offset = m_ulDCFTempBaseAddr & (mem_align - 1) ;
    
    if (mem_offset != 0)
        mem_offset = mem_align - mem_offset;
    
    ptr = (UINT8*)( m_ulDCFTempBaseAddr + mem_offset);

    return (void*)(ptr);

	#else ///< (MEMORY_POOL_CTL == 0)
	
    MMP_ULONG   MemAddr;
    void*       mem_handle;
    UINT8       *ptr;
    
    MMPS_System_GetPoolHandler(&mem_handle);
    MMPS_System_AllocateMemory(mem_handle, &MemAddr, MMP_FALSE, size, MMPS_SYSTEM_MEM_TOP, MMP_TRUE, NULL, 0);
    
    ptr = (UINT8*)( MemAddr);
    return (void*)(ptr);
    
    #endif ///< (MEMORY_POOL_CTL == 0)
}

/**
    @brief  Release memory pool for DCF APIs
    @param[in] ptr memory pointer
    @return MMP_ERR_NONE
*/
static void AIHC_DcfFree(void *ptr) {
    #if (MEMORY_POOL_CTL == 0)
    return;
    #endif
    #if (MEMORY_POOL_CTL == 1)
    void*       mem_handle;
    MMP_ULONG   MemAddr = (MMP_ULONG)ptr;
    
    if ( MemAddr != 0 ) {
        MMPS_System_AllocateMemory(mem_handle,&MemAddr,MMP_FALSE, 0 , MMPS_SYSTEM_MEM_TOP, MMP_FALSE, NULL, 0);
    }
    
    #endif
}


/**
 @brief This API allocate one Dir node from the mem pool

 This API allocate one Dir node from the mem pool
 
 Parameters:
 @retval DCF_DIR_NODE
*/
static DCF_DIR_NODE* AIHC_DcfAllocDirNode()
{

    DCF_DIR_NODE    *psDirNode;//*DirNode;
    UINT32          i;

            
    if ( m_sDirMem.uiFreeMem >= m_sDirMem.uiNodeSize) {

        for(i = 0 ; i < m_sDirMem.uiMaxCount ; i++) {
        
            if( (m_sDirMem.uiMemOffset + m_sDirMem.uiNodeSize) <= m_sDirMem.uiMemSize ){
            
                psDirNode   = (DCF_DIR_NODE*)(m_sDirMem.pMemPool + m_sDirMem.uiMemOffset);
            
            }else{
            
                psDirNode   = (DCF_DIR_NODE*)(m_sDirMem.pMemPool);
                m_sDirMem.uiMemOffset = 0;
            }
            
            if ( (psDirNode->uwDirKey == 0) || (psDirNode->uwDirKey == DCF_INVALID_NUMBER_16) ) {
                //un-used block
                
                MEMSET(psDirNode, DCF_RESET_VALUE, sizeof(DCF_DIR_NODE));
                
                break;
            }
            else {
                m_sDirMem.uiMemOffset += m_sDirMem.uiNodeSize;
                
                if( m_sDirMem.uiMemOffset >= m_sDirMem.uiMemSize )
                    m_sDirMem.uiMemOffset = 0;
            }
            
        }
        
        m_sDirMem.uiFreeMem   -= m_sDirMem.uiNodeSize;                            
        m_sDirMem.uiMemOffset += m_sDirMem.uiNodeSize;
        
        if( m_sDirMem.uiMemOffset >= m_sDirMem.uiMemSize )
            m_sDirMem.uiMemOffset = 0;
            
        return psDirNode;
    }
    else {
        return NULL;
    }
}

/**
 @brief This API free one Dir node from the mem pool

 make sure that you re-link the dir node behind or in front of the dir node which you want to kill.
 
 Parameters:
 @retval DCF_FILE_NODE
*/
static void AIHC_DcfFreeDirNode(DCF_DIR_NODE *psDirNode)
{
    if ( psDirNode != NULL ) {
    
        MEMSET(psDirNode, DCF_RESET_VALUE, sizeof(DCF_DIR_NODE));
        m_sDirMem.uiFreeMem   += sizeof(DCF_DIR_NODE);
    }
}

/**
 @brief This API allocate one File node from the mem pool

 This API allocate one File node from the mem pool
 
 Parameters:
 @retval DCF_FILE_NODE
*/
static DCF_FILE_NODE* AIHC_DcfAllocFileNode()
{
    DCF_FILE_NODE   *psFileNode = NULL;
    UINT32          i;
            
    if ( m_sFileMem.uiFreeMem >= m_sFileMem.uiNodeSize ){
    
        
        for( i = 0 ; i < m_sFileMem.uiMaxCount ; i++) {
        
            if ( (m_sFileMem.uiMemOffset + m_sFileMem.uiNodeSize) <= m_sFileMem.uiMemSize ){
                
                psFileNode   = (DCF_FILE_NODE*)(m_sFileMem.pMemPool + m_sFileMem.uiMemOffset);
                
            }else{
                
                psFileNode   = (DCF_FILE_NODE*)(m_sFileMem.pMemPool);
                
                m_sFileMem.uiMemOffset = 0;
            }
            
            /**
            @brief find the un-used memory of the file node memory pool.
            
            */
            if ( (psFileNode->uwFileKey == 0) || (psFileNode->uwFileKey == DCF_INVALID_NUMBER_16) ) {
                //un-used block
                
                MEMSET(psFileNode, DCF_RESET_VALUE, sizeof(DCF_FILE_NODE));
                
                break;
            }
            else {
                m_sFileMem.uiMemOffset += m_sFileMem.uiNodeSize;
                
                if( m_sFileMem.uiMemOffset >= m_sFileMem.uiMemSize )
                    m_sFileMem.uiMemOffset = 0;
            }
        }
        
        m_sFileMem.uiFreeMem   -= m_sFileMem.uiNodeSize;
        m_sFileMem.uiMemOffset += m_sFileMem.uiNodeSize;
        /**
        @brief Its dangerous.
        
        */
        if( m_sFileMem.uiMemOffset >= m_sFileMem.uiMemSize )
            m_sFileMem.uiMemOffset = 0;
            
        return psFileNode;
    }else{
        
        return NULL;
    }
}

/**
 @brief This API free one File node from the mem pool
 
 WARNING: you must release the memory of the first node!
 make sure that you re-link the file node behind or in front of the file node which you want to kill.
 
 Parameters:
 @retval DCF_FILE_NODE
*/
static void AIHC_DcfFreeFileNode(DCF_FILE_NODE *psFileNode)
{
    if ( psFileNode != NULL ) {

        MEMSET(psFileNode, DCF_RESET_VALUE, sizeof(DCF_FILE_NODE));
        
        m_sFileMem.uiFreeMem += sizeof(DCF_FILE_NODE);
    }
}

/**
@brief	free memory pool of file node based on the m_DcfDB.psBrowserDirNode.
		

*/
static AHC_BOOL AIHC_DCF_DynamicFreeFileNode(DCF_DIR_NODE *psMajorDirNode)
{

    DCF_DIR_NODE	*psTempDirNode;
    DCF_FILE_NODE	*psFileNode;

    
	if(m_DcfDB[m_uiDBIndex].psBrowserDirNode == NULL){

    	/** @brief	not enough memory */
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
    	printc("AIHC_DCF_DynamicFreeFileNode No browser dir node \r\n");
    	#endif
        if ( m_DcfDB[m_uiDBIndex].uiCurDirCountInDB > 0 ) {
        
        	AIHC_DCF_FindMinDirNode(m_uiDBIndex, 
        	                        &psTempDirNode, 
        	                        (DCF_DIR_MOUNT_TYPE_MIN | DCF_DIR_MOUNT_TYPE_MAX | DCF_DIR_MOUNT_TYPE_KEY | DCF_DIR_MOUNT_TYPE_ALL));
            
            if (psTempDirNode->uwDirKey != psMajorDirNode->uwDirKey) {
				/**
				@brief unmount the min dir node.
				*/
				#if (DCF_DEBUG  >= DCF_DEBUG_ALL)
		    	printc("AIHC_DCF_DynamicFreeFileNode unmount the min dir node \r\n");
		    	#endif
                AIHC_DCF_UnmountDirNode(psTempDirNode, psTempDirNode->uwDirKey, NULL);
                
            }
            else {
            	/**
            	@brief cyclic DCF should be considered. TBD
            	*/
				#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		    	printc("AIHC_DCF_DynamicFreeFileNode unmount the min file node \r\n");
		    	#endif
                AIHC_DCF_FindMinFileNode(m_uiDBIndex, psMajorDirNode, &psFileNode);
                AIHC_DCF_RemoveFileNode(psMajorDirNode, psFileNode, AHC_TRUE);

            }
            
        }else{
        	/**
        	@brief cyclic DCF should be considered. TBD
        	*/
  			#if (DCF_DEBUG  >= DCF_DEBUG_ALL)
            printc("[DCF] AIHC_DCF_DynamicFreeFileNode Not Expected\r\n");
            #endif
            AIHC_DCF_FindMinFileNode(m_uiDBIndex, psMajorDirNode, &psFileNode);
            AIHC_DCF_RemoveFileNode(psMajorDirNode, psFileNode, AHC_TRUE);

            
        }
        
	}else{

		UINT32 uiDistance;
		UINT32 uiResult;
		UINT16 uwDirkey;
		UINT16 uwTargetDirkey;
		
		psTempDirNode  = m_DcfDB[m_uiDBIndex].psRootDirNode;
		uwTargetDirkey = m_DcfDB[m_uiDBIndex].psBrowserDirNode->uwDirKey;
		
		uwDirkey   = 0;
		uiDistance = 0;
		uiResult   = 0;
		
		while(psTempDirNode != NULL){
			/**
			@brief	find the mounted dir node 
					and the distance between the key of psBrowserDirNode the and its key is far.
			*/
			if(psTempDirNode->byMountMode != DCF_DIR_MOUNT_TYPE_UNMOUNT){
			
				if(uwTargetDirkey > psTempDirNode->uwDirKey){
				
					uiDistance = uwTargetDirkey - psTempDirNode->uwDirKey;
					
				}else if(uwTargetDirkey > psTempDirNode->uwDirKey){
				
					uiDistance = psTempDirNode->uwDirKey - uwTargetDirkey;
					
				}else{
					uiDistance = 0;
				}
				
				if(uiDistance > uiResult){
					uiResult = uiDistance;
					uwDirkey = psTempDirNode->uwDirKey;
				}
			}
			
			psTempDirNode = psTempDirNode->psNext;
		
		}
		
		if(uwDirkey != 0){
  			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
            printc("[DCF] AIHC_DCF_DynamicFreeFileNode find the mounted dir node \r\n");
            #endif
			AIHC_DCF_FindDir(NULL, uwDirkey, &psTempDirNode);
	        AIHC_DCF_UnmountDirNode(psTempDirNode, psTempDirNode->uwDirKey, NULL);

		}else{
		
			if(uwTargetDirkey == psMajorDirNode->uwDirKey){
	  			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	            printc("[DCF] AIHC_DCF_DynamicFreeFileNode Remove the min key file node \r\n");
	            #endif
	            AIHC_DCF_FindMinFileNode(m_uiDBIndex, psMajorDirNode, &psFileNode);
	            AIHC_DCF_RemoveFileNode(psMajorDirNode, psFileNode, AHC_TRUE);

	            
            }else{
	  			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	            printc("[DCF] AIHC_DCF_DynamicFreeFileNode Unmount the dir node \r\n");
	            #endif
		        AIHC_DCF_UnmountDirNode(m_DcfDB[m_uiDBIndex].psBrowserDirNode, m_DcfDB[m_uiDBIndex].psBrowserDirNode->uwDirKey, NULL);

            }
		}
	}
	
	#if (DCF_DB_COUNT >= 2)
	if( m_sFileMem.uiFreeMem < m_sFileMem.uiNodeSize ){
	
	    UINT32 uiIndex = (m_uiDBIndex + 1) % DCF_DB_COUNT;
	    printc("DCF Free File Node and change DB\n");

    	AIHC_DCF_FindMinDirNode(uiIndex, 
    	                        &psTempDirNode, 
    	                        (DCF_DIR_MOUNT_TYPE_MIN | DCF_DIR_MOUNT_TYPE_MAX | DCF_DIR_MOUNT_TYPE_KEY | DCF_DIR_MOUNT_TYPE_ALL));
        
        if (psTempDirNode->uwDirKey != m_DcfDB[uiIndex].psPowerDirNode->uwDirKey) {
			/**
			@brief unmount the min dir node.
			*/
            AIHC_DCF_UnmountDirNode(psTempDirNode, psTempDirNode->uwDirKey, NULL);
            
        }
        else {
        	/**
        	@brief cyclic DCF should be considered. TBD
        	*/

            AIHC_DCF_FindMinFileNode(uiIndex, m_DcfDB[uiIndex].psPowerDirNode, &psFileNode);
            AIHC_DCF_RemoveFileNode(m_DcfDB[uiIndex].psPowerDirNode, psFileNode, AHC_TRUE);

        }
	}
	#endif///< (DCF_DB_COUNT >= 2)
	return AHC_TRUE;
}


static AHC_BOOL AIHC_DCF_MemCtl(UINT32* uiMemAddr)
{
    #define DCF_MEM_CTL_DEBUG (0)
    UINT32  i, uiDBIndex;
    UINT32  uiMaxDirCount, uiMaxAllowedFileMem;

    UINT32  uiMemStAddr     = *uiMemAddr;
    UINT32  uiMemEndAddr    = *uiMemAddr + MAX_DCF_MEM - 1;

    uiMaxDirCount = MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1;
    
    #if (DCF_MEM_CTL_DEBUG)
    printc("[DCF INFO] uiMemStAddr      : %x \n", uiMemStAddr);
    #endif
    /*
    DB Related memory space.
    */
    for(uiDBIndex = 0 ; uiDBIndex < DCF_DB_COUNT; uiDBIndex++){

      	/**	@brief	DCF memory map stage 1. 
      				the memory space of the pointer of (DCF_OBJ_COUNT*)
      	*/
    	uiMemStAddr				= ALIGN4(uiMemStAddr);
        m_DcfDB[uiDBIndex].ppsFileCountInDir	= (DCF_OBJ_COUNT**)uiMemStAddr;
        uiMemStAddr				+= ALIGN32(uiMaxDirCount * sizeof(DCF_OBJ_COUNT*));
        
        #if (DCF_MEM_CTL_DEBUG)
        printc("[DCF INFO] DB Index           : %d \n", uiDBIndex);
        printc("[DCF INFO] ppsFileCountInDir  : %x \n", m_DcfDB[uiDBIndex].ppsFileCountInDir);
        #endif
        
        for(i = 0 ; i < uiMaxDirCount ; i++) {
        	/**
        	@brief	the memory space of every dir.
        	
        	*/
            m_DcfDB[uiDBIndex].ppsFileCountInDir[i] = (DCF_OBJ_COUNT*)uiMemStAddr;
            
            #if 0//(DCF_MEM_CTL_DEBUG)
            printc("[DCF INFO] Dir Index(i)          : %d \n", i);
            printc("[DCF INFO] ppsFileCountInDir[i]  : %x \n", m_DcfDB[uiDBIndex].ppsFileCountInDir[i]);
            #endif
            
            uiMemStAddr += ALIGN32( sizeof(DCF_OBJ_COUNT) );

            MEMSET(m_DcfDB[uiDBIndex].ppsFileCountInDir[i], DCF_RESET_VALUE, ALIGN32( sizeof(DCF_OBJ_COUNT) ) );
        }

    	/**	@brief	DCF memory map stage 2. File Map */
        m_DcfDB[uiDBIndex].sFileMap.pbyMapAddr = (UINT8*)uiMemStAddr;
        m_DcfDB[uiDBIndex].sFileMap.uiMapSize  = MAX_DCF_FILE_KEYNUM - MIN_DCF_FILE_KEYNUM + 1;
        AIHC_DCF_ClearCompareFileMap(uiDBIndex);
        uiMemStAddr          += m_DcfDB[uiDBIndex].sFileMap.uiMapSize;
        
        /**	@brief	DCF memory map stage 3. Search Cache */
        uiMemStAddr		= ALIGN4(uiMemStAddr);
       	m_DcfDB[uiDBIndex].sSearchCache.uiSlotCount   = DCF_SEACH_CACHE_SLOT_COUNT;
       	m_DcfDB[uiDBIndex].sSearchCache.uiSlotSize    = DCF_SEACH_CACHE_SLOT_SIZE;
    	m_DcfDB[uiDBIndex].sSearchCache.puiCacheAddr  = (UINT32*)uiMemStAddr;
        m_DcfDB[uiDBIndex].sSearchCache.uiCacheSize   = m_DcfDB[uiDBIndex].sSearchCache.uiSlotCount * m_DcfDB[uiDBIndex].sSearchCache.uiSlotSize;
        AIHC_DCF_ClearSearchCache(uiDBIndex);
        uiMemStAddr		+= m_DcfDB[uiDBIndex].sSearchCache.uiCacheSize;  
        
        #if (DCF_MEM_CTL_DEBUG)
        printc("[DCF INFO] sFileMap.pbyMapAddr : %x \n", m_DcfDB[uiDBIndex].sFileMap.pbyMapAddr);
        printc("[DCF INFO] sFileMap.uiMapSize  : %d \n", m_DcfDB[uiDBIndex].sFileMap.uiMapSize);
        
        printc("[DCF INFO] sSearchCache.puiCacheAddr : %x \n", m_DcfDB[uiDBIndex].sSearchCache.puiCacheAddr);
        printc("[DCF INFO] sSearchCache.uiCacheSize  : %d \n", m_DcfDB[uiDBIndex].sSearchCache.uiCacheSize);
        #endif
    }   
    
    /**	@brief	DCF memory map stage 4. DCFX Related memory space. */
    #if (DCF_DCFX == 1)
    m_uiDCFxPageInfoSize	=  sizeof(DCFX_DB_PAGE);
    m_uiDCFxDataSize		=  sizeof(DCFX_DB_DATA);
    m_uiDCFxBufSize			= m_uiDCFxPageInfoSize + m_uiDCFxDataSize*m_uiDCFxDataMaxCount;
    
    uiMemStAddr			= ALIGN4(uiMemStAddr);  	
	m_pbyDCFxTempBuffer		= (UINT8*)uiMemStAddr;
	uiMemStAddr			+= m_uiDCFxBufSize; 	
	AIHC_DCF_ResetDCFxDB(0);

	MEMSET(&m_sPageCtl, DCF_RESET_VALUE, sizeof(DCFX_PAGE_CTL));

	
    uiMemStAddr			= ALIGN4(uiMemStAddr);  	
    {
    UINT32 i;
    
    for(i = 0; i < DCF_GOLDEN_PAGE_NUMBER; i++){
    	m_GoldenPage[i].pbyBuffer	= (UINT8*)uiMemStAddr;
    	uiMemStAddr			+= m_uiDCFxBufSize;
    }
    
    }
	
	AIHC_DCF_ResetDCFxDB(1);
    #endif///< (DCF_DCFX == 1)
    

    /**	@brief	DCF memory map stage 4. Sub DB Related memory space. */
    #if (DCF_SUB_DB == 1)

    {
	uiMemStAddr                 = ALIGN4(uiMemStAddr);
    m_sSubFileMem.pMemPool	    = (UINT8*)uiMemStAddr;
    m_sSubFileMem.uiMemOffset   = 0;	///< the offset of used file node memory pool.
    m_sSubFileMem.uiMaxCount    = DCF_SUB_FILE_MAX_COUNT;
    m_sSubFileMem.uiNodeSize    = sizeof(DCF_FILE_NODE);
    m_sSubFileMem.uiMemSize     = m_sSubFileMem.uiMaxCount*m_sSubFileMem.uiNodeSize;	///< the max. size of file node memory pool.
    m_sSubFileMem.uiFreeMem     = m_sSubFileMem.uiMemSize;


    MEMSET(m_sSubFileMem.pMemPool, DCF_RESET_VALUE, m_sSubFileMem.uiMemSize);

    uiMemStAddr		 += m_sSubFileMem.uiFreeMem;
    }
    #endif///< (DCF_SUB_DB == 1)

    
    /**	@brief	DCF memory map stage 5.
    			the initialization of DCF directory. 
	*/
	uiMemStAddr      = ALIGN4(uiMemStAddr);
    m_sDirMem.pMemPool	= (UINT8*)uiMemStAddr;

    /**
    @brief	dir node alignment.
    */
    
	m_sDirMem.uiMaxCount  = uiMaxDirCount*DCF_DB_COUNT;   
    m_sDirMem.uiMemOffset = 0;
    m_sDirMem.uiNodeSize  = sizeof(DCF_DIR_NODE);
    m_sDirMem.uiMemSize   = m_sDirMem.uiMaxCount * m_sDirMem.uiNodeSize; ///< MAX_DCF_DIR_MEM
    m_sDirMem.uiFreeMem   = m_sDirMem.uiMemSize;
    MEMSET(m_sDirMem.pMemPool, DCF_RESET_VALUE, m_sDirMem.uiMemSize);
    uiMemStAddr		+= m_sDirMem.uiMemSize; ///< 
    

    
    /**	@brief	DCF memory map stage 6. 
    			the initialization of DCF file. */
    uiMemStAddr       = ALIGN4(uiMemStAddr);
    m_sFileMem.pMemPool	 = (UINT8*)uiMemStAddr;
    m_sFileMem.uiNodeSize  = sizeof(DCF_FILE_NODE);
    /**
    @brief	file node alignment.
    */
    uiMaxAllowedFileMem = uiMemEndAddr - uiMemStAddr;
	m_sFileMem.uiMaxCount  = uiMaxAllowedFileMem / m_sFileMem.uiNodeSize;
	uiMaxAllowedFileMem   = m_sFileMem.uiMaxCount * m_sFileMem.uiNodeSize;

    m_sFileMem.uiMemOffset = 0;
    m_sFileMem.uiMemSize   = uiMaxAllowedFileMem; ///< MAX_DCF_FILE_MEM
    m_sFileMem.uiFreeMem   = m_sFileMem.uiMemSize;
    MEMSET(m_sFileMem.pMemPool, DCF_RESET_VALUE, m_sFileMem.uiMemSize);
    uiMemStAddr		 += m_sFileMem.uiMemSize;

    *uiMemAddr = uiMemStAddr;
    
	#if (DCF_MEM_CTL_DEBUG)

	printc("[DCF INFO] m_sDirMem \n");
	printc("[DCF INFO] pMemPool    : %x \n", m_sDirMem.pMemPool);
	printc("[DCF INFO] uiMemOffset : %d \n", m_sDirMem.uiMemOffset);
	printc("[DCF INFO] uiMemSize   : %d \n", m_sDirMem.uiMemSize);
	printc("[DCF INFO] uiFreeMem   : %d \n", m_sDirMem.uiFreeMem);
	printc("[DCF INFO] uiMaxCount  : %d \n", m_sDirMem.uiMaxCount);
	printc("[DCF INFO] uiNodeSize  : %d \n", m_sDirMem.uiNodeSize);
	
	printc("[DCF INFO] m_sFileMem \n");
	printc("[DCF INFO] pMemPool    : %x \n", m_sFileMem.pMemPool);
	printc("[DCF INFO] uiMemOffset : %d \n", m_sFileMem.uiMemOffset);
	printc("[DCF INFO] uiMemSize   : %d \n", m_sFileMem.uiMemSize);
	printc("[DCF INFO] uiFreeMem   : %d \n", m_sFileMem.uiFreeMem);
	printc("[DCF INFO] uiMaxCount  : %d \n", m_sFileMem.uiMaxCount);
	printc("[DCF INFO] uiNodeSize  : %d \n", m_sFileMem.uiNodeSize);
	#if(DCF_SUB_DB == 1)
	printc("[DCF INFO] m_sSubFileMem \n");
	printc("[DCF INFO] pMemPool    : %x \n", m_sSubFileMem.pMemPool);
	printc("[DCF INFO] uiMemOffset : %d \n", m_sSubFileMem.uiMemOffset);
	printc("[DCF INFO] uiMemSize   : %d \n", m_sSubFileMem.uiMemSize);
	printc("[DCF INFO] uiFreeMem   : %d \n", m_sSubFileMem.uiFreeMem);
	printc("[DCF INFO] uiMaxCount  : %d \n", m_sSubFileMem.uiMaxCount);
	printc("[DCF INFO] uiNodeSize  : %d \n", m_sSubFileMem.uiNodeSize);
	#endif///< DCF_SUB_DB == 1
	#endif
	
	#if (DCF_MEM_CTL_DEBUG)
    printc("[DCF INFO] *uiMemAddr       : %x \n", *uiMemAddr);
	printc("[DCF INFO] 2nd uiMemStAddr  : %x \n", uiMemStAddr);
	printc("[DCF INFO] uiMemEndAddr     : %x \n", uiMemEndAddr);
    #endif
    
    return AHC_TRUE;
}


static AHC_BOOL AIHC_DCF_MemFree(void)
{
    
    if ( m_ulDcfMemPool ) {
        AIHC_DcfFree((UINT8*)m_ulDcfMemPool);
        m_ulDcfMemPool = 0;
    }
   
    
    m_sDirMem.pMemPool  = NULL;
    m_sFileMem.pMemPool = NULL;
    
    #if (DCF_SUB_DB == 1)
    m_sSubFileMem.pMemPool = NULL;
    #endif

    return AHC_TRUE;
}

#if 0
void __DB_COUNTER__(){}
#endif

#if (FW_DCF_BACKGROUND == 0)
AHC_BOOL AIHC_DCF_LOCKDB(void)
{
	return AHC_TRUE;
}
AHC_BOOL AIHC_DCF_UNLOCKDB(void)
{
	return AHC_TRUE;
}
AHC_BOOL AIHC_DCF_LOCKPAGE(void)
{
	return AHC_TRUE;
}
AHC_BOOL AIHC_DCF_UNLOCKPAGE(void)
{
	return AHC_TRUE;
}
#endif ///< #if (FW_DCF_BACKGROUND == 0)

UINT32 AIHC_DCF_GetTotalFileCount(void)
{
	UINT32 uiFileSum = 0;
	UINT32 i;
	
	
	for(i = 0 ; i < MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1 ; i++){
		
		if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i] != DCF_INVALID_NUMBER_16){
		
			uiFileSum += m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i];
		}
	
	}

	return uiFileSum;
	
}


UINT32 AIHC_DCF_GetTotalAllowedFileCount(void)
{
	UINT32 uiFileSum = 0;
	UINT32 i;
		
	for(i = 0; i < MAX_DCF_SUPPORT_FILE_TYPE ;i++){
	
		if(m_DcfDB[m_uiDBIndex].chAllowedFileType[i] == 1){

			uiFileSum += m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[i];
		}
		
	}
	
	return uiFileSum;

}

/**

have to make sure that the dir node is already existed.
add file without adding the file node.

*/
AHC_BOOL AIHC_DCF_UpdateDBInfo(DCF_DIR_NODE *psDirNode, UINT16 uwFileKey, UINT8 byFileType, UINT8 byOldFileType, AHC_BOOL bDelete, AHC_BOOL bReadOnly)
{
	/*
	printc("AIHC_DCF_UpdateDBInfo \r\n");
	printc("uwFileKey     : %d  \r\n", uwFileKey);
	printc("byFileType    : %d  \r\n", byFileType);
	printc("byOldFileType : %d  \r\n", byOldFileType);
	printc("bDelete       : %d  \r\n", bDelete);
	*/
        
	if(bDelete == AHC_TRUE){
		/*
		printc("Before\r\n");
		printc("m_DcfDB.uwTotalFileCountInDir[]                      : %d  \r\n", m_DcfDB.uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]);
		printc("m_DcfDB.uiTotalFileCountInFileType[]                 : %d  \r\n", m_DcfDB.uiTotalFileCountInFileType[byFileType]);
		printc("m_DcfDB.ppsFileCountInDir[]->uwFileCountInFileType[] : %d  \r\n", m_DcfDB.ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[byFileType]);
        */
        m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]--;

        m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[byFileType]--;
        
        m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[byFileType]--;

		return AHC_TRUE;

	}else{
	
		if(byOldFileType != DCF_INVALID_NUMBER_8){

		    m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[byOldFileType]--;
		    m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[byOldFileType]--;
		    m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[byFileType]++;	
		    m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[byFileType]++;

		}else{
		
		    if(uwFileKey > psDirNode->uwMaxFileKey) {
		    
		        psDirNode->uwMaxFileKey = uwFileKey;
		    }
		    
		    m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]++;
		    m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[byFileType]++;

		    m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[byFileType]++;

	    }
	    
	    return AHC_TRUE;
    }
}

AHC_BOOL AIHC_DCF_ClearDBInfo(DCF_DIR_NODE *psDirNode)
{
	UINT32 i;

	if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ] == DCF_INVALID_NUMBER_16)
		return AHC_TRUE;
	
	for(i = 0; i < MAX_DCF_SUPPORT_FILE_TYPE; i++){

		m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[i] -= m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[i];

		m_DcfDB[m_uiDBIndex].ppsFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]->uwFileCountInFileType[i] = 0;
	}

	m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ] = 0;

	
	return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_GetMediaInfo(void)
{

	UINT64 uiiTotalBytes;
	
	// Get the info of media
    AHC_GetStorageMediaInfo(&m_sMediaInfo);

	m_uiBytesPerCluster = m_sMediaInfo.usBytesPerSector*m_sMediaInfo.usSecPerCluster;

	
	uiiTotalBytes = (UINT64)m_sMediaInfo.ulTotalClusters*m_uiBytesPerCluster;
	
	uiiTotalBytes = uiiTotalBytes/1024/1024/1024;

	if(uiiTotalBytes > 118){

		m_sDCFRegionID = DCF_REGION_ID_128;
	}else if(uiiTotalBytes > 58){

		m_sDCFRegionID = DCF_REGION_ID_64;
	}else if(uiiTotalBytes > 28){

		m_sDCFRegionID = DCF_REGION_ID_32;
	}else if(uiiTotalBytes >= 12){
	
		m_sDCFRegionID = DCF_REGION_ID_16;
	}else if(uiiTotalBytes >= 7){
	
		m_sDCFRegionID = DCF_REGION_ID_8;
	}else if(uiiTotalBytes >= 3){
	
		m_sDCFRegionID = DCF_REGION_ID_4;
	}else{
		m_sDCFRegionID = DCF_REGION_ID_2;
	}
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("BytesPerSec     : %d, \r\n", m_sMediaInfo.usBytesPerSector);
	printc("SecPerCluster   : %d, \r\n", m_sMediaInfo.usSecPerCluster);
	printc("TotalCluster    : %d, \r\n", m_sMediaInfo.ulTotalClusters);
	printc("FreelCluster    : %d, \r\n", m_sMediaInfo.ulFreeClusters);	
	printc("BytesPerCluster : %d, \r\n", m_uiBytesPerCluster);
	printc("DCFxRegionID    : %d, \r\n", m_sDCFRegionID);
    #endif	
	
	return AHC_TRUE;

}

/**
@brief	This API is used to calculate the cluster of the single file and maintain the counter of DB.
*/
static AHC_BOOL AIHC_DCF_CalculateCluster(	INT8* 				pchFileFreeChar, 
											AHC_FS_ATTRIBUTE*	sFileAttribute, 
											UINT32				uiFileSize, 
											UINT16				uwDirKey, 
											AHC_BOOL			bAdd)
{
	UINT64 uiiClusterPerFile;
	
	uiiClusterPerFile = (uiFileSize + m_uiBytesPerCluster - 1)/m_uiBytesPerCluster;

	if(bAdd == AHC_TRUE){
	
		if(*sFileAttribute & AHC_FS_ATTR_READ_ONLY){
	
			m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster += uiiClusterPerFile;
			
		}
		#if (DCF_DCFX == 1)
		else if(AIHC_DCF_WhichIsBoss(pchFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
	
			m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster += uiiClusterPerFile;
		    m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount++;
		    
        }
        #endif///< (DCF_DCFX == 1)
        else{
        	
			m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster += uiiClusterPerFile;
			m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount++;
			
        }
	
	}else{
	
		if(*sFileAttribute & AHC_FS_ATTR_READ_ONLY){
	
			m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster -= uiiClusterPerFile;
	
		}
		#if (DCF_DCFX == 1)
		else if(AIHC_DCF_WhichIsBoss(pchFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
	
			m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster -= uiiClusterPerFile;
			m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount--;
    
        }
        #endif///< (DCF_DCFX == 1)
        else{
        	
			m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster -= uiiClusterPerFile;
			m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount--;
			
        }

	}
	
	return AHC_TRUE;

}


#if 0
void __LOCAL_API__(){}
#endif

/**
 @brief Get the DCF root dir name

 This function get the DCF root dir name
 
 @retval DCF root dir name
*/
INT8* AIHC_DCF_GetRootName(void)
{
    return m_DcfDB[m_uiDBIndex].chRootName;
}
/**
 @brief This API returns the full path name

 This API returns the full path name
 
 Parameters:
 @param[out] pDirName       the full Dir Name.
 @param[in]  key            Dir key
 @param[in]  pFreeChars     Dir free chars
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_GetDirFullName(INT8 *pchDirName, UINT16 uwDirKey, INT8 *pchDirFreeChar)
{
    UINT32  i,j,d;
	UINT32  uiSplit = m_DcfDB[m_uiDBIndex].byDirCharLength - m_DcfDB[m_uiDBIndex].byDirFreeCharNum;///< 3
	
    for(i = 0 ; i < uiSplit ; i++) {
    	/**	@brief	get the directory number from the key. */
        d = 1;
        
        for(j = 0 ; j < (uiSplit - 1 - i) ; j++) {
            d = d * 10;
        }
        
        pchDirName[i] = (uwDirKey / d) + '0';	///< '0' = 0x30.
        
        uwDirKey -= (uwDirKey / d) * d;
    }
    
    for(i = uiSplit ; i < m_DcfDB[m_uiDBIndex].byDirCharLength ; i++) {
    	/**	@brief	Free characters(5 alphanumerics). */
        pchDirName[i] = pchDirFreeChar[i - uiSplit];
    }
    
    return AHC_TRUE;
}

/**
 @brief This API returns the full file name

 This API returns the full file name
 
 Parameters:
 @param[out] pFileName      the full file Name.
 @param[in]  key            File key
 @param[in]  pFreeChars     File free chars
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_GetFileFullName(INT8 *pchFileName, UINT16 uwFileKey, INT8 *pchFileFreeChars)
{
    UINT32  i,j,d;
  	UINT32  uiSplit = m_DcfDB[m_uiDBIndex].byFileCharLength - m_DcfDB[m_uiDBIndex].byFileFreeCharNum;///< 4

    for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++) {
        pchFileName[i] = pchFileFreeChars[i];
    }

    for(i = 0 ; i < uiSplit ; i++) {
        d = 1;
        
        for(j = 0 ; j < ( uiSplit - 1 - i ) ; j++ ) {
            d = d * 10;
        }
        
        pchFileName[m_DcfDB[m_uiDBIndex].byFileFreeCharNum + i] = (uwFileKey / d) + '0';
        
        uwFileKey -= (uwFileKey / d) * d;
    }

    return AHC_TRUE;
}
/**
@brief
@param[in] uiLength: the unit is byte.

*/
static UINT8 AIHC_DCF_WhichIsBoss(void *pPtr1, void *pPtr2, UINT32 uiLength)
{
    UINT32  i;
    UINT8*  pchPtr1 = pPtr1;
    UINT8*  pchPtr2 = pPtr2;
    
    
    for(i = 0 ; i < uiLength ; i++){
    
    	if(pchPtr1[i] > pchPtr2[i]){
    		
    		return DCF_BOSS_1;
    		
    	}else if(pchPtr1[i] < pchPtr2[i]){
    		
    		return DCF_BOSS_2;
    	}
    }

    return DCF_BOSS_EQUAL;
}

/**
make sure the addr which you pass is 16 bit alignment.
unit: UINT16(16bit)
*/
static UINT8 AIHC_DCF_WhichIsBoss16(void *pPtr1, void *pPtr2, UINT32 uiLength)
{
    UINT32  i;
    UINT16*  pchPtr1 = pPtr1;
    UINT16*  pchPtr2 = pPtr2;
    
    
    for(i = 0 ; i < uiLength ; i++){
    
    	if(pchPtr1[i] > pchPtr2[i]){
    		
    		return DCF_BOSS_1;
    		
    	}else if(pchPtr1[i] < pchPtr2[i]){
    		
    		return DCF_BOSS_2;
    	}
    }

    return DCF_BOSS_EQUAL;
}

/**
make sure the addr which you pass is 32 bit alignment.
*/
#if 0
static UINT8 AIHC_DCF_WhichIsBoss32(void *pPtr1, void *pPtr2, UINT32 uiLength)
{
    UINT32  i;
    UINT32*  pchPtr1 = pPtr1;
    UINT32*  pchPtr2 = pPtr2;

    
    for(i = 0 ; i < uiLength ; i++){

    	if(pchPtr1[i] > pchPtr2[i]){

    		return DCF_BOSS_1;
    		
    	}else if(pchPtr1[i] < pchPtr2[i]){

    		return DCF_BOSS_2;
    	}
    }

    return DCF_BOSS_EQUAL;
}
#endif
/**
 @brief This API gets the key and free chars from the path name

 This API gets the key and free chars from the path name
 
 Parameters:
 @param[in]   pDirName      The dir Name.
 @param[out]  key           Dir key
 @param[out]  pFreeChars    Dir free chars
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_GetDirKey(INT8 *pchDirName, UINT16 *puwDirKey, INT8 *pchDirFreeChars)
{
    BYTE    value;
    UINT32  i,j,d;
    UINT32  uiSplit = m_DcfDB[m_uiDBIndex].byDirCharLength - m_DcfDB[m_uiDBIndex].byDirFreeCharNum;///< 3
    
    value = STRLEN(pchDirName);
    /**	@brief	the length of string must be 8. 
    			Directory number + Free characters(5 alphanumerics).
    			Directory number : 100 ~ 999.
    			*/
    if ( value != m_DcfDB[m_uiDBIndex].byDirCharLength )
        return AHC_FALSE;
    
    *puwDirKey = 0;

    for(i = 0 ; i < uiSplit ; i++) {
    	/**	@brief	acquire the key of dir from the first 3 number(directory number). */
        value = pchDirName[i] - '0';	///< '0' = 0x30
        
        if ( (value < 0) || (value > 9) ){
        	/**	@brief	1~9, '1' = 0x31, '2' = 0x32, '9' = 0x39. */
            return AHC_FALSE;
        }
        
        d = 1;
        
        for(j = 0 ; j < (uiSplit - 1 - i) ; j++) {
        	/**	@brief	the first number is multiplied by 100.
        				the second number is multiplied by 10.
        				the third number is multiplied by 1.*/
            d = d * 10;
        }
        
        *puwDirKey += d * value;///< the directory number.
    }
    
    if ( ( *puwDirKey < MIN_DCF_DIR_KEYNUM ) || (*puwDirKey > MAX_DCF_DIR_KEYNUM) ){
		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
    	printc("AIHC_DCF_GetDirKey error - file number overflow... \r\n");
    	#endif
        return AHC_FALSE;
	}
	
    for ( i = uiSplit ; i < m_DcfDB[m_uiDBIndex].byDirCharLength ; i++) {
    	/**	@brief	the filter of the first 5 free characters. */
        value = pchDirName[i];
        
        if( ((value >= '0') && (value <= '9')) ||
        	((value >= 'A') && (value <= 'Z')) ||
            ((value >= 'a') && (value <= 'z')) ||
			(value == '_') ) {
        }
        else{
       		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
        	printc(FG_RED("AIHC_DCF_GetDirKey error - incorrect dir name... \r\n"));
        	#endif
            return AHC_FALSE;
		}
    }
    
    MEMCPY(pchDirFreeChars, &pchDirName[uiSplit], m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
    
    return AHC_TRUE;
}

/**
 @brief This API gets the key and free chars from the file name

 This API gets the key and free chars from the file name
 
 Parameters:
 @param[in]   pFileName     The file Name.
 @param[out]  key           File key
 @param[out]  pFreeChars    File free chars
 @param[out]  DcfFileType   DCF file type
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_GetFileKey(INT8 *pchFileName, UINT16 *puwFileKey, INT8 *pFileFreeChar, UINT8 *pbyFileType)
{
    BYTE    value;
    UINT32  i,j,d;
    UINT32  uiFileNameLen;
    INT8    Ext[FILE_EXT_LENGTH + 1];
    
    uiFileNameLen = STRLEN(pchFileName);
    /**
    @brief get the file name without file extension.
    
    */
    for(i = (uiFileNameLen - 1) ; i > 0 ; i--) {
    
        if (pchFileName[i] == '.')
            break;
    }
    
    //the length of the DCF File name , not including the extension,
    if ( i != m_DcfDB[m_uiDBIndex].byFileCharLength )
        return AHC_FALSE;
    

    for ( i = 0; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum; i++) {
    	/**	@brief	the filter of the first 4 free characters. */
        value = pchFileName[i];

        if( ((value >= '0') && (value <= '9')) ||
			((value >= 'A') && (value <= 'Z')) ||
            ((value >= 'a') && (value <= 'z')) ||
			(value == '_') ){
        }
        else{
			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
        	printc(FG_RED("[DCF ERROR] incorrect file name... \r\n"));
        	#endif
            return AHC_FALSE;
        }
    }
    
    *puwFileKey = 0;
    /**
    @brief translate the ASCII code to digit
    */
    for(i = 0 ; i < (m_DcfDB[m_uiDBIndex].byFileCharLength - m_DcfDB[m_uiDBIndex].byFileFreeCharNum) ; i++) {
    	/**	@brief	the filter of the rest 4 numbers. */
        value = pchFileName[m_DcfDB[m_uiDBIndex].byFileFreeCharNum + i] - '0';
        
        if ( (value < 0) || (value > 9) ){
			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
        	printc(FG_RED("[DCF ERROR] incorrect file number... \r\n"));
        	#endif
            return AHC_FALSE;
        }
        
        d = 1;
        
        for(j = 0 ; j < ((m_DcfDB[m_uiDBIndex].byFileCharLength - m_DcfDB[m_uiDBIndex].byFileFreeCharNum) - 1 - i) ; j++) {
            d = d * 10;
        }
        
        *puwFileKey += d * value;
    }
    
    if ( ( *puwFileKey < MIN_DCF_FILE_KEYNUM ) || (*puwFileKey > MAX_DCF_FILE_KEYNUM) ){
   		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
    	printc(FG_RED("[DCF ERROR] file number overflow... \r\n"));
    	#endif
        return AHC_FALSE;
	}
	
    MEMCPY(pFileFreeChar, &pchFileName[0], m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
    /**
    @brief parse the file type, file extension
    */
    MEMSET(Ext, DCF_RESET_VALUE, sizeof(Ext));
    
    //Convert to upper case
    for ( i = 0 ; i < FILE_EXT_LENGTH ; i++) {
    	/**	@brief	change the file extension. */
        value = pchFileName[ m_DcfDB[m_uiDBIndex].byFileCharLength + 1 + i];
        
        if ( (value >= 'A') && (value <= 'Z') ) {
            Ext[i] = value;
        }
        else if ( (value >= 'a') && (value <= 'z') ) {
            Ext[i] = 'A' + (value - 'a');
        }
        else {
            Ext[i] = value;
        }
    }
	/**
	@brief support this file type or not.
	
	*/
    *pbyFileType = DCF_INVALID_NUMBER_8;	///< intialize the value of DcfFileType.
    
    for(i = 0 ; i < MAX_DCF_SUPPORT_FILE_TYPE ; i++) {
    	/**	@brief	check the supproted file type. */
        if ( STRCMP((INT8*)m_DcfSupportFileType[i], (INT8*)Ext) == 0 ) {
            *pbyFileType = i;
            break;
        }
    }
    
    if( *pbyFileType == DCF_INVALID_NUMBER_8 ) {
   		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
    	printc(FG_RED("[DCF ERROR] N/A File Type... \r\n"));
		#endif
        return AHC_FALSE;
    }
              
    return AHC_TRUE;
}


/**
 @brief This API finds a specified dir node by its key

 This API finds a specified dir node by its key
 
 Parameters:
 @param[in]   DirName       The specified dir name. Not ueds yet.
 @param[in]   DirKey        Dir key
 @param[out]  pDir          The specified dir node
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_FindDir(INT8 *pchDirName, UINT16 uwDirKey, DCF_DIR_NODE **ppsDir)
{
    DCF_DIR_NODE *psTempDirNode;
    
    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("AIHC_DCF_FindDir \r\n");
    #endif
    
    if ( pchDirName == NULL ) {
    
		if( (m_DcfDB[m_uiDBIndex].psPowerDirNode != NULL) &&
			(m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey == uwDirKey) ){
			
			*ppsDir = m_DcfDB[m_uiDBIndex].psPowerDirNode;
			return AHC_TRUE;
		
		}
		/**
		TBD we can use the power dir node to speed up the proccess of searching the dir node.
		
		*/
        //find Max dir node
        psTempDirNode = m_DcfDB[m_uiDBIndex].psRootDirNode;
        
        #if (DCF_DEBUG >= DCF_DEBUG_ALL)
        printc("AIHC_DCF_FindDir search dir node \r\n");
        #endif
        
        while(psTempDirNode != NULL){
        	
            if( psTempDirNode->uwDirKey == uwDirKey ){
                break;
            }
            
        	psTempDirNode = psTempDirNode->psNext;
        }
        
        if ( psTempDirNode != NULL ) {
            *ppsDir = psTempDirNode;
            
            return AHC_TRUE;
        }
        else {
            *ppsDir = NULL;
            
            return AHC_FALSE;
        }

    }else{
    
		UINT16 uwSearchDirKey; 
		INT8   chDirFreeChars[MAX_FILE_FREE_CHAR_NUMBER];
		AIHC_DCF_GetDirKey(pchDirName, &uwSearchDirKey, chDirFreeChars);
		
		psTempDirNode = m_DcfDB[m_uiDBIndex].psRootDirNode;
		
        while(psTempDirNode != NULL){
            if ( psTempDirNode->uwDirKey == uwSearchDirKey ) {
                break;
            }        
        }
        
        if ( psTempDirNode != NULL ) {
            *ppsDir = psTempDirNode;
            
            return AHC_TRUE;
        }
        else {
            *ppsDir = NULL;
            
            return AHC_FALSE;
        }
    }
    
}
/**
@brief	we find the dir node according to the number of dir and the base dir node.

*/
static AHC_BOOL AIHC_DCF_FindFarDirNode(DCF_DIR_NODE *psBaseDir, DCF_DIR_NODE **ppsDir)
{
	DCF_DIR_NODE *psSearchDir;
	UINT32		uiDirCount;
	
	uiDirCount = m_DcfDB[m_uiDBIndex].uiCurDirCountInDB >> 1;
	psSearchDir = psBaseDir;
	
	while((psSearchDir != NULL) && (uiDirCount > 0)){
		
		if(psSearchDir == m_DcfDB[m_uiDBIndex].psLastDirNode){
		
			psSearchDir = m_DcfDB[m_uiDBIndex].psRootDirNode;

		}else{
			psSearchDir = psSearchDir->psNext;
		
		}

		uiDirCount--;

	}
	
	if(psSearchDir != NULL){
		
		*ppsDir = psSearchDir;
		
		return AHC_TRUE;
	}else{
	
		return AHC_FALSE;
	}

}

/**
 @brief This API finds the dir node with the minimun key

 This API finds the dir node with the minimun key
 
 Parameters:
 @param[out]  pDir          The specified dir node
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_FindMinDirNode(UINT32 uiDBIndex, DCF_DIR_NODE **pDir, UINT8 byMountMode)
{
    DCF_DIR_NODE *psTempDirNode;

    if( m_DcfDB[uiDBIndex].uiCurDirCountInDB > 0 ){

        psTempDirNode = m_DcfDB[uiDBIndex].psRootDirNode;

        while(psTempDirNode != NULL){

        	if(psTempDirNode->byMountMode & byMountMode){
        	
        		break;
        	}

        	psTempDirNode = psTempDirNode->psNext;
        }

		if(psTempDirNode != NULL){
        	*pDir = psTempDirNode;
        	return AHC_TRUE;
        }else{
        	*pDir = NULL;
        	return AHC_FALSE;
        }
        
    }else{
    
        *pDir = NULL;
        return AHC_FALSE;
    }    
}


/**
 @brief This API finds the dir node with the maximun key

 This API finds the dir node with the maximun key
 
 Parameters:
 @param[out]  pDir          The specified dir node
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_FindMaxDirNode(DCF_DIR_NODE **ppsDir, UINT8 byMountMode)
{
    DCF_DIR_NODE *psTempDirNode;
        
    if ( m_DcfDB[m_uiDBIndex].uiCurDirCountInDB > 0 ) {
    
        psTempDirNode = m_DcfDB[m_uiDBIndex].psLastDirNode;
		
		while(psTempDirNode != NULL){
		
			if(psTempDirNode->byMountMode & byMountMode){
				break;
			}
			
			psTempDirNode = psTempDirNode->psPrev;
		}
        
        if(psTempDirNode != NULL)
	        *ppsDir = psTempDirNode;
	    else
	    	*ppsDir = NULL;
        
        return AHC_TRUE;
    }
    else {
    
        *ppsDir = NULL;
        
        return AHC_FALSE;
    }    
}
/**
@brief This API will wrap back when you pass the last dir node.

@return, AHC_TRUE => Find one, AHC_FALSE => only itself

*/
static AHC_BOOL AIHC_DCF_FindNextDirNode(DCF_DIR_NODE **ppsDir)
{
	DCF_DIR_NODE	*psDir = *ppsDir;
	UINT16			uwStartDirKey;
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("AIHC_DCF_FindNextDirNode... \r\n");
	#endif
	
	uwStartDirKey = psDir->uwDirKey;
	
	do{
		if(psDir->psNext != NULL){
			/**
			@brief	the next
			*/
			psDir = psDir->psNext;
		}else{
			/**
			@brief	wrap back
			*/
			psDir = m_DcfDB[m_uiDBIndex].psRootDirNode;
		}
		/*
    	if(m_DcfDB.uwTotalFileCountInDir[psDir->uwDirKey] > 0){
    	
    		if( psDir->byDirAttribute == DCF_DIR_NONLOCK ){
    			break;
    		}else{
    			uwNonEmptyDir++;
    		}
    	}
		*/
	
	}while( (psDir->uwDirKey == uwStartDirKey) && (psDir->psNext != NULL) );
	
	*ppsDir = psDir;
	
	if(psDir->uwDirKey == uwStartDirKey){
	
		return AHC_FALSE;
	}else{

		return AHC_TRUE;	
	}

}

/**
@brief	find the dir node next to the other dir node with dir key.
*/
static AHC_BOOL AIHC_DCF_FindNextDirNodeByKey(UINT16 uwDirKey, DCF_DIR_NODE **ppsDir)
{
	DCF_DIR_NODE	*psDir;
	
	if(m_DcfDB[m_uiDBIndex].psRootDirNode == NULL){
		return AHC_FALSE;
	}
	
	psDir = m_DcfDB[m_uiDBIndex].psRootDirNode;
	
	while(psDir != NULL){
	
		if(psDir->uwDirKey > uwDirKey){
			break;
		}
		
		psDir = psDir->psNext;
	}

	if(psDir != NULL){
		/**
		@brief	find the one has the dir key is bigger than uwDirKey.
		*/
		*ppsDir = psDir;
	}else{
		/**
		@brief	no dir node has the dir key which is bigger than uwDirKey so 
				this dir node must be the last dir node. 
		*/
		*ppsDir = m_DcfDB[m_uiDBIndex].psRootDirNode;
	}

	return AHC_TRUE;

}

static AHC_BOOL AIHC_DCF_AddDirNode(INT8 *pchDirName)
{
    UINT16       uwDirKey;
    INT8         chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];
    DCF_DIR_NODE *psNewDirNode;
    DCF_DIR_NODE *pTempDirNode;
    
    MEMSET(chDirFreeChar, DCF_RESET_VALUE, sizeof(chDirFreeChar));
    
    if ( AIHC_DCF_GetDirKey(pchDirName, &uwDirKey , chDirFreeChar) == AHC_TRUE ) {
    
        psNewDirNode = AIHC_DcfAllocDirNode();

        if (psNewDirNode == NULL) {
        	#if (DCF_DEBUG >= DCF_DEBUG_ERR)
        	printc("[DCF ERROR] DIR NODE MEM POOL FULL 0x01 \r\n");
        	#endif
        	return AHC_FALSE;
        }
        
        psNewDirNode->uwDirKey    = uwDirKey;	///< setup the key
        psNewDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_UNMOUNT;

        STRCPY(psNewDirNode->chDirFreeChar, chDirFreeChar);
        
        if ( m_DcfDB[m_uiDBIndex].psRootDirNode == NULL ) {
        	/**	@brief	the first directory. */
            m_DcfDB[m_uiDBIndex].psRootDirNode   = psNewDirNode;
            m_DcfDB[m_uiDBIndex].psLastDirNode   = psNewDirNode;
        }
        else {

            if(psNewDirNode->uwDirKey < m_DcfDB[m_uiDBIndex].psLastDirNode->uwDirKey) {
				/**
				@brief the key of the dir node is smaller than the end dir node of database.
				*/
                pTempDirNode = m_DcfDB[m_uiDBIndex].psRootDirNode;	///< the root node of dir 
				
				while(pTempDirNode != NULL){
                    if( pTempDirNode->uwDirKey >= psNewDirNode->uwDirKey ){
                    	/**
                    	@brief the key of the temp dir node is bigger than the key of new dir node
                    	       so insert the new dir node in front of the temp dir node.
                    	*/
                        break;
                    }
                    
                    pTempDirNode = pTempDirNode->psNext;				
				
				}
				
                /**	@brief	insert this dir node into DCF DB. */
                if(pTempDirNode->psPrev == NULL){
                	/**	@brief	the temp dir node is the root dir node 
                	            so the new dir node become the root dir node. */
                	m_DcfDB[m_uiDBIndex].psRootDirNode = psNewDirNode;
            		psNewDirNode->psNext  = pTempDirNode;
            		psNewDirNode->psPrev  = NULL;                		
            		pTempDirNode->psPrev  = psNewDirNode;


                }else if( pTempDirNode->uwDirKey == psNewDirNode->uwDirKey ){
                
                	UINT8 byResult;
                	
                	//printc("the same dir key \r\n");
                	
                	byResult = AIHC_DCF_WhichIsBoss(pTempDirNode->chDirFreeChar, psNewDirNode->chDirFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
                	
                	if((byResult == DCF_BOSS_2) || (byResult == DCF_BOSS_EQUAL)){
                		AIHC_DcfFreeDirNode(psNewDirNode);
                		return AHC_TRUE;
                		
                	}else{
                		psNewDirNode->psPrev = pTempDirNode->psPrev;
                		psNewDirNode->psNext = pTempDirNode->psNext;
                		AIHC_DcfFreeDirNode(pTempDirNode);
                		m_DcfDB[m_uiDBIndex].uiCurDirCountInDB--;
                	}

                }else{
                    psNewDirNode->psNext            = pTempDirNode;
                    psNewDirNode->psPrev            = pTempDirNode->psPrev;
                    
                    pTempDirNode->psPrev->psNext   = psNewDirNode;
                    pTempDirNode->psPrev           = psNewDirNode;

                }

            }else if( psNewDirNode->uwDirKey == m_DcfDB[m_uiDBIndex].psLastDirNode->uwDirKey ){

            	UINT8 byResult;
            
            	byResult = AIHC_DCF_WhichIsBoss(m_DcfDB[m_uiDBIndex].psLastDirNode->chDirFreeChar, psNewDirNode->chDirFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
            	//printc("the same dir key \r\n");
            	
            	if( (byResult == DCF_BOSS_2) || (byResult == DCF_BOSS_EQUAL) ){

            		AIHC_DcfFreeDirNode(psNewDirNode);
            		return AHC_TRUE;
            		
            	}else{
            		psNewDirNode->psPrev = m_DcfDB[m_uiDBIndex].psLastDirNode->psPrev;
            		psNewDirNode->psNext = m_DcfDB[m_uiDBIndex].psLastDirNode->psNext;
            		
            		AIHC_DcfFreeDirNode(m_DcfDB[m_uiDBIndex].psLastDirNode);
            		
            		if(m_DcfDB[m_uiDBIndex].psLastDirNode == m_DcfDB[m_uiDBIndex].psRootDirNode){
            			m_DcfDB[m_uiDBIndex].psRootDirNode = psNewDirNode;
            		}
            		
            		m_DcfDB[m_uiDBIndex].psLastDirNode = psNewDirNode;
            		
            		m_DcfDB[m_uiDBIndex].uiCurDirCountInDB--;
            	}

            }else{
            	/**	
            	@brief	the key of the dir node is bigger than the end dir node of database.
            			add this node to the end. 
            	*/
                psNewDirNode->psNext           = NULL;
                psNewDirNode->psPrev           = m_DcfDB[m_uiDBIndex].psLastDirNode;

                m_DcfDB[m_uiDBIndex].psLastDirNode->psNext = psNewDirNode;
                m_DcfDB[m_uiDBIndex].psLastDirNode         = psNewDirNode;
            }
        }

        m_DcfDB[m_uiDBIndex].uiCurDirCountInDB++;
		m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM] = 0;///< initialize the total count of files.
		
		if(psNewDirNode->uwDirKey == m_DcfDB[m_uiDBIndex].uwFileCtlDirKey){
		
			m_DcfDB[m_uiDBIndex].psFileCtlDirNode = psNewDirNode;
		
		}
		
		
        return AHC_TRUE;
        
    }
    else {
        return AHC_FALSE;
    }
}
/**
@brief	clear the info of dir in the DB.
		parse the file in the dir depending on the mount type.

	psDirNode: the dir node
	pchDirName: the name of dir  
	uwFileMaxCount: the max number of file node
	uwTargetFilekey: the target key of DCF_DIR_MOUNT_TYPE_KEY
	type: the type of mount dir node

*/

AHC_BOOL AIHC_DCF_MountDirNode(	DCF_DIR_NODE	*psDirNode, 
								INT8			*pchDirName, 
								UINT16          uwFileMaxCount,
								UINT16			uwTargetFileKey,
								DCF_DIR_MOUNT_TYPE type)
								
								
{
	DCF_DIR_NODE   *psMountDirNode;
    INT8			chFullDirName[DCF_MAX_FILE_NAME_SIZE];
    UINT32			uiDirLength;

	if(psDirNode == NULL){
		if(pchDirName == NULL)
			return AHC_FALSE;
		else{
			AIHC_DCF_FindDir(pchDirName, 0, &psMountDirNode);
		}
		
	}else{
	
		psMountDirNode = psDirNode;
	}
    
    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
    printc("AIHC_DCF_MountDirNode DirKey : %d \r\n", psMountDirNode->uwDirKey);
    #endif
	/**
	TBD speed up the operation 
	*/
	AIHC_DCF_UnmountDirNode(psMountDirNode, psMountDirNode->uwDirKey, NULL);
	
    uiDirLength	= STRLEN(m_DcfDB[m_uiDBIndex].chRootName);
    MEMSET(chFullDirName, DCF_RESET_VALUE, sizeof(chFullDirName));
    MEMCPY(chFullDirName, m_DcfDB[m_uiDBIndex].chRootName, uiDirLength);
	STRCAT(chFullDirName, "\\");
	
	if(pchDirName == NULL)
	{
	    INT8 chDirName[MAX_DIR_CHAR_LENGTH + 1];
		MEMSET(chDirName, DCF_RESET_VALUE, sizeof(chDirName));
		AIHC_DCF_GetDirFullName(chDirName, psMountDirNode->uwDirKey, psMountDirNode->chDirFreeChar);
    	MEMCPY(chFullDirName + uiDirLength + 1, chDirName, m_DcfDB[m_uiDBIndex].byDirCharLength);
    	
	}else{
	
    	MEMCPY(chFullDirName + uiDirLength + 1, pchDirName, m_DcfDB[m_uiDBIndex].byDirCharLength);
	
	}
	
	AIHC_DCF_ParseFile(	psMountDirNode, 
						chFullDirName, 
						uwFileMaxCount,
						uwTargetFileKey,
						type );
	
	return AHC_TRUE;
}
/**
@brief	free the memory of all the file nodes in this dir node.
*/
static AHC_BOOL AIHC_DCF_UnmountDirNode(DCF_DIR_NODE *psDirNode, UINT16 uwDirKey, INT8 *pchDirName)
{
	DCF_DIR_NODE   *psUnmountDirNode = NULL;
    DCF_FILE_NODE  *psFileNode;
    	
	if(psDirNode == NULL){
		//TBD
	
	}else{
	
		psUnmountDirNode = psDirNode;
	}
	
	if(psUnmountDirNode->byMountMode == DCF_DIR_MOUNT_TYPE_UNMOUNT)
		return AHC_TRUE;
		

	psFileNode = psUnmountDirNode->psRootFileNode;
	
	while(psFileNode != NULL){
		AIHC_DCF_RemoveFileNode(psUnmountDirNode, psFileNode, AHC_TRUE);
		psFileNode = psUnmountDirNode->psRootFileNode;
	}	

	psUnmountDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_UNMOUNT;
	
	return AHC_TRUE;
}

/**
@brief remove the dir node out of the DB

*/

static AHC_BOOL AIHC_DCF_DeleteDir(DCF_DIR_NODE *psDirNode)
{
    if( psDirNode == NULL ){
        return AHC_FALSE;
    }

    
    AIHC_DCF_UnmountDirNode(psDirNode, psDirNode->uwDirKey, NULL);	
	
	/**
	@brief re-link the dir node.
	*/
    if( psDirNode == m_DcfDB[m_uiDBIndex].psRootDirNode ) {
        
        m_DcfDB[m_uiDBIndex].psRootDirNode          = psDirNode->psNext;

        if( m_DcfDB[m_uiDBIndex].psRootDirNode != NULL)
	        m_DcfDB[m_uiDBIndex].psRootDirNode->psPrev  = NULL;
        
    }else if( psDirNode == m_DcfDB[m_uiDBIndex].psLastDirNode ){
        
        m_DcfDB[m_uiDBIndex].psLastDirNode          = psDirNode->psPrev;

        if( m_DcfDB[m_uiDBIndex].psLastDirNode != NULL){
	        m_DcfDB[m_uiDBIndex].psLastDirNode->psNext  = NULL;
	    }
        
    }else{
        psDirNode->psPrev->psNext = psDirNode->psNext;
        psDirNode->psNext->psPrev = psDirNode->psPrev;
    }

    /**
    @brief need to modify all the counter of DB
    */
    m_DcfDB[m_uiDBIndex].uiCurDirCountInDB--;
    m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM] = DCF_INVALID_NUMBER_16;
	
	/**
	@brief	setup the link of functional dir node in DB.
	*/
    
    if(psDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){
    	m_DcfDB[m_uiDBIndex].psPowerDirNode = NULL;
    }
    
    if(psDirNode == m_DcfDB[m_uiDBIndex].psFileCtlDirNode){
    	/**
    	@brief	the file control node is deleted so we need to find a new one.
    	
    	*/
    	UINT16 uwDirKey  = psDirNode->uwDirKey;
    	UINT16 uwFileKey = 0;
    	UINT8  bCreateNewDir;
    	
    	if(AIHC_DCF_ChangeFileCtlDirNode(&uwDirKey, &uwFileKey, &bCreateNewDir) == AHC_TRUE){

	    	AIHC_DCF_FindDir(NULL, uwDirKey, &m_DcfDB[m_uiDBIndex].psFileCtlDirNode);
	    }else{
	    	m_DcfDB[m_uiDBIndex].psFileCtlDirNode = NULL;
	    }
    }
    
    if(psDirNode == m_DcfDB[m_uiDBIndex].psBrowserDirNode){
    	m_DcfDB[m_uiDBIndex].psBrowserDirNode = NULL;
    }
    
    if ( m_DcfDB[m_uiDBIndex].uiCurDirCountInDB == 0 ) {
        m_DcfDB[m_uiDBIndex].psRootDirNode		= NULL;
        m_DcfDB[m_uiDBIndex].psLastDirNode		= NULL;
        
        m_DcfDB[m_uiDBIndex].psPowerDirNode		= NULL;
        m_DcfDB[m_uiDBIndex].psFileCtlDirNode	= NULL;
        m_DcfDB[m_uiDBIndex].psBrowserDirNode	= NULL;
    }
    
    AIHC_DcfFreeDirNode(psDirNode);
    

    
    return AHC_TRUE;
}

/**
 @brief This API finds a specified file node by its key

 This API finds a specified file node by its key
 
 Parameters:
 @param[in]   FileName      The specified file name. Not ueds yet.
 @param[in]   FileKey       File key
 @param[out]  pFile         The specified file node
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_FindFileNode(DCF_DIR_NODE *pDirNode, INT8 *chFileName, UINT16 uwFileKey, DCF_FILE_NODE **pFile)
{
    DCF_FILE_NODE   *pTempFileNode;

    if( chFileName == NULL )
    {
        pTempFileNode = pDirNode->psRootFileNode;

        if(pDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode)
        {
        	/**
        	@brief use the m_puiSearchCache of power dir node to use two hierarchy
        	*/
	        UINT32 uiIndex;
	        uiIndex = uwFileKey/m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount;
	        
	        if(uiIndex == 0){
	        	
	        	pTempFileNode = pDirNode->psRootFileNode;
	        	
	        }else if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) != DCF_INVALID_NUMBER_32){
	        
	        	pTempFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1);

	        }else{
	        	
	        	UINT32 uiSearchIndex;
	        	
        		for( uiSearchIndex = uiIndex ; uiSearchIndex > 0 ; uiSearchIndex--){
        		
        			if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1)) != DCF_INVALID_NUMBER_32){
        				break;
        			}
        		}
        		
        		if(uiSearchIndex == 0){
        		
        			pTempFileNode = pDirNode->psRootFileNode;
        			
        		}else{
		        	pTempFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1) + 1);
		        }

	        }
	        
	       	while(pTempFileNode != NULL){
	        	
		   		if ( uwFileKey == pTempFileNode->uwFileKey ){
	    	        break;
	            }
	            
		        pTempFileNode = pTempFileNode->psNext;
	       	}        
        
        }else{
        	/**
        	@brief linear search.
        	
        	*/
        	while(pTempFileNode != NULL){
        		
	            if ( pTempFileNode->uwFileKey == uwFileKey ) {
	                break;
	            }
	            pTempFileNode = pTempFileNode->psNext;        	
        	}

        }


        if ( pTempFileNode != NULL ) {
            *pFile = pTempFileNode;
            
            return AHC_TRUE;
        }
        else {
            *pFile = NULL;

            return AHC_FALSE;
        }
        
    }else{
        //TBD
        *pFile = NULL;

        return AHC_FALSE;
    }
}

/**
 @brief This API finds the file node with the minimun key

 This API finds the file node with the minimun key in the same dir.
 
 Parameters:
 @param[out]  pFile          The specified file node
 
 @retval AHC_BOOL
*/
static AHC_BOOL AIHC_DCF_FindMinFileNode(UINT32 uiDBIndex, DCF_DIR_NODE *psSearchDirNode, DCF_FILE_NODE **ppsFile)
{
    DCF_DIR_NODE  *psDirNode;
    
    if(psSearchDirNode == NULL){
	    psDirNode = m_DcfDB[uiDBIndex].psRootDirNode;

	    while(psDirNode != NULL){
	    
	    	if( psDirNode->byMountMode & 
	    	    (DCF_DIR_MOUNT_TYPE_MIN | DCF_DIR_MOUNT_TYPE_MAX | DCF_DIR_MOUNT_TYPE_KEY | DCF_DIR_MOUNT_TYPE_ALL) ){
	    		break;
	    	}
	    	
	    	psDirNode = psDirNode->psNext;
	    }
    }else{
    	psDirNode = psSearchDirNode;
    }
    
    if( (psDirNode->uwFileNodeCount > 0) && (psDirNode != NULL) ) {
        
        *ppsFile = psDirNode->psRootFileNode;
        
        return AHC_TRUE;
    }
    else {
    
        *ppsFile = NULL;
        
        return AHC_FALSE;
    }    
}

/**
 @brief This API finds the file node with the maximun key

 This API finds the file node with the maximun key in the current dir node.
 
 Parameters:
 @param[out]  pFile          The specified file node
 
 @retval AHC_BOOL
*/
/*static*/ AHC_BOOL AIHC_DCF_FindMaxFileNode(DCF_DIR_NODE  *psSearchDirNode, DCF_FILE_NODE **ppsFile)
{
    DCF_DIR_NODE  *psDirNode;
    
    
    if(psSearchDirNode == NULL){
	    psDirNode = m_DcfDB[m_uiDBIndex].psLastDirNode;
	    
	    while(psDirNode != NULL){
	    
	    	if( psDirNode->byMountMode & 
	    	    (DCF_DIR_MOUNT_TYPE_MIN | DCF_DIR_MOUNT_TYPE_MAX | DCF_DIR_MOUNT_TYPE_KEY | DCF_DIR_MOUNT_TYPE_ALL) ){
	    		break;
	    	}
	    	
	    	psDirNode = psDirNode->psPrev;
	    }
    }else{
    	psDirNode = psSearchDirNode;
    }
    
    if( (psDirNode->uwFileNodeCount > 0) && (psDirNode != NULL) ) {
        
        *ppsFile = psDirNode->psLastFileNode;
        
        return AHC_TRUE;
        
    }else{
    
        *ppsFile = NULL;
        
        return AHC_FALSE;
    }
}

static AHC_BOOL AIHC_DCF_AddFileNode(DCF_DIR_NODE *psMajorDirNode, DCF_FILE_NODE *psNewFileNode)
{
    DCF_FILE_NODE   *psFileNode;
    AHC_BOOL        bSameFileKey = AHC_FALSE;
    AHC_BOOL        bUpdateCache = AHC_FALSE;
    UINT32			uiIndex = 0;

	
	if( (psMajorDirNode == NULL) || (psNewFileNode == NULL) )
	    return AHC_FALSE;

        
    //keep the max key value
    if(psNewFileNode->uwFileKey > psMajorDirNode->uwMaxFileKey) {
    
        psMajorDirNode->uwMaxFileKey = psNewFileNode->uwFileKey;
    }

    if ( psMajorDirNode->psRootFileNode == NULL ) {
    	// there is no file in the dir. why not clear the previous pointer of the new file node?
        psNewFileNode->psNext           = NULL;
        psMajorDirNode->psRootFileNode  = psNewFileNode; // the first file node is the new file node.
        psMajorDirNode->psLastFileNode  = psNewFileNode; // the first last node is the new file node.
        
        if(psMajorDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){
        	bUpdateCache = AHC_TRUE;
        	uiIndex = psNewFileNode->uwFileKey/m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount;
        }
    }
    else {
    
        psFileNode = psMajorDirNode->psRootFileNode;///< get the first file node in the dir

        if(psMajorDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode)
        {
        
			bUpdateCache = AHC_TRUE;
	        uiIndex = psNewFileNode->uwFileKey/m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount;
	        
	        if(uiIndex == 0){
	        	/**
	        	@brief never use the first period of cache.
	        	*/
	        	psFileNode = psMajorDirNode->psRootFileNode;
	        	
	        }else if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) != DCF_INVALID_NUMBER_32){
	        	/**
	        	@brief Cache hit.
	        	*/
	        	psFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1);
	        }else{
	        	/**
	        	@brief Cache miss.
	        	*/
	        	UINT32 uiSearchIndex;

	        	if( uiIndex > (m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount >> 1) ){
	        	
	        		for( uiSearchIndex = uiIndex ; uiSearchIndex < m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount ; uiSearchIndex++){
	        		
	        			if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1)) != DCF_INVALID_NUMBER_32){
	        				break;
	        			}
	        		}
	        		
	        		if(uiSearchIndex == m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount){
	        		
	        			psFileNode = psMajorDirNode->psLastFileNode;
	        			*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1) = (UINT32)psNewFileNode;
	        			
	        		}else{
			        	psFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1) + 1);
	        		}
	        		
	        	}else{
	        	
	        		for( uiSearchIndex = uiIndex ; uiSearchIndex > 0 ; uiSearchIndex--){
	        		
	        			if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1)) != DCF_INVALID_NUMBER_32){
	        				break;
	        			}
	        		}
	        		
	        		if(uiSearchIndex == 0){
	        		
	        			psFileNode = psMajorDirNode->psRootFileNode;
	        			
	        		}else{
			        	psFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiSearchIndex << 1) + 1);
			        }


	        	}
	        }
	        
	       	while(psFileNode != NULL){
	        	
		   		if ( psFileNode->uwFileKey >= psNewFileNode->uwFileKey )
	    	            break;
	            	
		        psFileNode = psFileNode->psNext;
	       	}

	        
        }else{
        
	        for( uiIndex = 0 ; uiIndex < psMajorDirNode->uwFileNodeCount ; uiIndex++) {
				/**	@brief	the flow of the DCF database should guarantee that, 
							the number of DCF file node is the same as psMajorDirNode->uwFileNodeCount. */
	            if ( psFileNode->uwFileKey >= psNewFileNode->uwFileKey )
	                break;
	            	
	            psFileNode = psFileNode->psNext;
	        }
        }
        
        /**	@brief	3 cases. */
        if (psFileNode == NULL) {
            /** @brief	case 1, there is no key number bigger than the new file node */
            
            // clear the next file node of the new file node.
            psNewFileNode->psNext            = NULL;
            // put the last file node in front of the new file node.
            psNewFileNode->psPrev            = psMajorDirNode->psLastFileNode;
            // put the new file node behind the last file node.
            psMajorDirNode->psLastFileNode->psNext = psNewFileNode;
            // set the new file node as the last file node in the dir.
            psMajorDirNode->psLastFileNode       = psNewFileNode;
        }
        else if ( psFileNode->uwFileKey > psNewFileNode->uwFileKey ) {
        
        	/**	@brief	case 2, there is one key number bigger than the new file node.
        				insert the new file node. */
            psNewFileNode->psNext           = psFileNode;
            psNewFileNode->psPrev           = psFileNode->psPrev;
            
            if( psFileNode->psPrev == NULL ) {
                /**	@brief	x -> temp file node -> ?,
                			x -> new file mode -> temp file node -> ? */
                			
                psMajorDirNode->psRootFileNode     = psNewFileNode;///< the first file node is the new file node
                psFileNode->psPrev      = psNewFileNode;
                
                if(psFileNode->psNext == NULL) {
                	/**	@brief	x -> temp file node -> x, 
                				x -> new file node -> temp file node -> x */
                    psMajorDirNode->psLastFileNode  = psFileNode;///< the last file node is the temp file node
                }else{
                	/**	@brief	x -> temp file node -> other file node, 
                				x -> new file node -> temp file node -> other file node. */
                }
            }
            else {
            	/**	@brief	other file node -> temp file node -> ?, 
            				other file node -> new file node -> temp file node -> ? */
                psFileNode->psPrev->psNext    = psNewFileNode;
                psFileNode->psPrev          = psNewFileNode;
                
                if(psFileNode->psNext == NULL) {
                	/**	@brief	other file node -> temp file node -> x,
                				other file node -> new file node -> temp file node -> x */
                    psMajorDirNode->psLastFileNode = psFileNode;///< the last file node is the temp file node
                }else{
                	/**	@brief	other file node -> temp file node -> other file node,
                				other file node -> new file node -> temp file node -> other file node. */
                
                }
            }
        }
        else if ( psFileNode->uwFileKey == psNewFileNode->uwFileKey ) {
        
        	bSameFileKey = AHC_TRUE;

            /**	@brief	case 3, there is one key number the same as the new file node.
            			the key of the new file node is the same as one of file nodes in dir. */
            psNewFileNode->psNext	= NULL;
            psNewFileNode->psPrev	= NULL;

            if ( psNewFileNode->byFileType <= psFileNode->byFileType) {

                /** @brief	replace the first node with the new file node.
                			the first file node is setup as the neighhor of the new file node. */
                psNewFileNode->psNext            = psFileNode->psNext;
                psNewFileNode->psPrev            = psFileNode->psPrev;
                
                psNewFileNode->psNeighbor        = psFileNode;
            	
                if( psFileNode->psPrev == NULL ) {
                	/**	x -> temp file node -> ?,
                		x -> new file node -> temp file node -> ? */
                    psMajorDirNode->psRootFileNode     = psNewFileNode;

                    if( psFileNode->psNext == NULL){
                    	/**	x -> temp file node -> x,
                    		x -> new file node -> x*/
                    	psMajorDirNode->psLastFileNode  = psNewFileNode;
                    }else{
                    	/**	x -> temp file node -> other file node,
                    		x -> new file node -> other file node*/
                    	psFileNode->psNext->psPrev = psNewFileNode;
                    
                    }
                
                }
                else if( psFileNode->psNext == NULL ) {
                	/**	other file node -> temp file node -> x, 
                		other file node -> new file node -> x*/
                    psFileNode->psPrev->psNext = psNewFileNode;
                    psMajorDirNode->psLastFileNode   = psNewFileNode;
                }
                else {
                	/**	other file node -> temp file node -> other file node,
                		other file node -> new file node -> other file node */
                    psFileNode->psPrev->psNext = psNewFileNode;
                    psFileNode->psNext->psPrev = psNewFileNode;
                }
                
                // clear the pointer of the temp file node 
                psFileNode->psNext           = NULL;
                psFileNode->psPrev           = NULL;

            }
            else {
				
				bUpdateCache = AHC_FALSE;
				
                while( psFileNode != NULL ){

                    if ( psNewFileNode->byFileType >= psFileNode->byFileType ) {
                    	/**
                    	@brief the new file node is the first file node in the same key number.
                    	*/                        
                        break;
                    }
                    
                    if(psFileNode->psNeighbor != NULL){
                		psFileNode = psFileNode->psNeighbor;
                	}else{
                		break;
                	}
                
                }
                
                if(psFileNode->psNeighbor == NULL){
                	psFileNode->psNeighbor = psNewFileNode;
                }else{
                	psNewFileNode->psNeighbor = psFileNode->psNeighbor;
                	psFileNode->psNeighbor    = psNewFileNode->psNeighbor;
                	
                }

            }///< if ( j == 0 )
        }///< end of if-else loop
    }

    if( bSameFileKey == AHC_FALSE ) {
        psMajorDirNode->uwFileNodeCount++;
    }
    
    /**
    @brief update search cache
    */
    if( bUpdateCache == AHC_TRUE ){
    	
      	/**
       	ex:
       	700 ~ 799 => 8th slot cache
       	*/
		uiIndex++;
		
		if(uiIndex != m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount){
		
	    	if( ( psNewFileNode->uwFileKey >= *(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) ) || 
	    		( *(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) == DCF_INVALID_NUMBER_32 ) ){
	    		
	    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) )    = psNewFileNode->uwFileKey;
	    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1) = (UINT32)psNewFileNode;
	    	}
    	}
    }
    
    return AHC_TRUE;

}

AHC_BOOL AIHC_DCF_AddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
    DCF_FILE_NODE   *psNewFileNode;
    DCF_DIR_NODE    *psMajorDirNode;
    
    UINT16          uwFileKey;
    INT8            chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    UINT8           byFileType;
    
    MEMSET(chFileFreeChar, DCF_RESET_VALUE, sizeof(chFileFreeChar));
    /**	
    @brief	find the dir node with uwDirKey as root node.
    */
    if ( AIHC_DCF_FindDir(NULL, uwDirKey, &psMajorDirNode) == AHC_FALSE ){
		AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    if ( AIHC_DCF_GetFileKey(pchFileName, &uwFileKey , chFileFreeChar, &byFileType) == AHC_TRUE ) {
    
    	AIHC_DCF_UpdateDBInfo(psMajorDirNode, uwFileKey, byFileType, DCF_INVALID_NUMBER_8, AHC_FALSE, AHC_FALSE);
    	
    	if(psMajorDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){
    	
    		UINT8 byOldFileType;
	    	AIHC_DCF_CompareFileMap(uwFileKey, byFileType, &byOldFileType);
	    	
	    	if(byOldFileType != DCF_INVALID_NUMBER_8){
    			#if (DCF_DEBUG >= DCF_DEBUG_ERR )
	    		printc("[DCF ERROR] AIHC_DCF_AddFile Map Error \r\n");
	    		#endif
				AHC_PRINT_RET_ERROR(0, 0);
	    		return AHC_FALSE;
    		}
    	}
    	
	    if( psMajorDirNode->byMountMode == DCF_DIR_MOUNT_TYPE_UNMOUNT ){
	    	/**
	    	@brief If the dir node is not mounted, add the info to DB only.
	    	*/
	    	#if (DCF_DEBUG >= DCF_DEBUG_ALL )
        	printc("AIHC_DCF_AddFile dir ndoe is unmounted \r\n");
        	#endif
		    return AHC_TRUE;

	    }else{

	    	if( psMajorDirNode->byMountMode != DCF_DIR_MOUNT_TYPE_ALL ){
	    		if(	(uwFileKey > psMajorDirNode->psRootFileNode->uwFileKey) || 
	    			(uwFileKey < psMajorDirNode->psLastFileNode->uwFileKey) ){
	    			
	    			return AHC_TRUE;	
	    		}
	    	
	    	}
	    }
    
		// allocate a new memory to the new file node
        psNewFileNode = AIHC_DcfAllocFileNode();

        while( psNewFileNode == NULL ){
        	/** @brief	not enough memory */
        	
        	#if (DCF_DEBUG >= DCF_DEBUG_ALL )
        	printc("AIHC_DCF_AddFile allocate memory again \r\n");
        	#endif
        	
			if(AIHC_DCF_DynamicFreeFileNode(psMajorDirNode)== AHC_FALSE){
				#if (DCF_DEBUG >= DCF_DEBUG_ERR)
				printc("[DCF ERROR] Free Memory Fail 0x02 \r\n");
				#endif
				AHC_PRINT_RET_ERROR(0, 0);
				return AHC_FALSE;
			}
			
            psNewFileNode = AIHC_DcfAllocFileNode();
            
        }/** end of while. not enough memory */

        if( psNewFileNode != NULL ){
			#if (DCF_DEBUG >= DCF_DEBUG_ALL )
        	printc("AIHC_DCF_AddFile add new file node \r\n");
        	#endif
        	
        	psNewFileNode->uwFileKey  = uwFileKey;
	        psNewFileNode->byFileType = byFileType;
	        MEMCPY(psNewFileNode->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
	        
        	return AIHC_DCF_AddFileNode(psMajorDirNode, psNewFileNode);
        	
        }else{
        	//should never happened!
        	#if (DCF_DEBUG >= DCF_DEBUG_ERR)
        	printc("[DCF ERROR] File Memory Full \r\n");
        	#endif
            return AHC_TRUE;
        }
    }
    else {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }
}

/**
@brief	releae the memory of file node. 
		additional: release the memory of neighbor of file node.TBD
*/
static AHC_BOOL AIHC_DCF_RemoveFileNode(DCF_DIR_NODE *psDirNode, DCF_FILE_NODE *psFileNode, AHC_BOOL bKeepMap)
{
    DCF_FILE_NODE   *psKillFileNode;

    //No more file entries, return SUCCESS
    if ( psDirNode->uwFileNodeCount == 0 )
        return AHC_TRUE;

    psDirNode->uwFileNodeCount--;
    
    if(psDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){

        /**
        @brief	replace the search cache.
        */
        UINT32			uiIndex;
        DCF_FILE_NODE	*psTempFileNode;
        
        uiIndex = psFileNode->uwFileKey/m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount;
        
        uiIndex++;
        
        if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) != DCF_INVALID_NUMBER_32){
        	/**
        	@brief Cache has this file mode. We have to replace another file node near this file node in the cache
        	*/
        	if(*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1)) == psFileNode->uwFileKey){
        	
        		psTempFileNode = (DCF_FILE_NODE*)*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1);
        		
        		if(psTempFileNode->psPrev != NULL){
        		
        			if((psTempFileNode->psPrev->uwFileKey/m_DcfDB[m_uiDBIndex].sSearchCache.uiSlotCount + 1) == uiIndex){
			    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) )    = psTempFileNode->psPrev->uwFileKey;
			    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1) = (UINT32)psTempFileNode->psPrev;
        			}else{
    		    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) )    = DCF_INVALID_NUMBER_32;
			    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1) = DCF_INVALID_NUMBER_32;
        			}
        			
        		}else{
		    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) )    = DCF_INVALID_NUMBER_32;
		    		*(m_DcfDB[m_uiDBIndex].sSearchCache.puiCacheAddr + (uiIndex << 1) + 1) = DCF_INVALID_NUMBER_32;        		
        		
        		}

        	}
        	
        }
        /**
        @brief clear one in file map
        */
        if(bKeepMap == AHC_FALSE)
	        AIHC_DCF_SetOneInFileMap(psFileNode->uwFileKey, DCF_INVALID_NUMBER_8);
    }
    
    if( psFileNode == psDirNode->psRootFileNode ) {
    	/**
    	@brief the file which is the root file node, is getting removed.
    	*/
        psDirNode->psRootFileNode         = psFileNode->psNext;
    
        if(psDirNode->psRootFileNode != NULL )
	        psDirNode->psRootFileNode->psPrev = NULL;
        else{
        	psDirNode->psLastFileNode = NULL;
        }
    }else if( psFileNode == psDirNode->psLastFileNode ) {
    	/**
    	@brief the file which is the last file node, is getting removed.
    	*/    
    	psDirNode->psLastFileNode = psFileNode->psPrev;
    
    	if(psDirNode->psLastFileNode != NULL )
	        psDirNode->psLastFileNode->psNext = NULL;
	        
		
    }else{
    
        psFileNode->psPrev->psNext = psFileNode->psNext;
        psFileNode->psNext->psPrev = psFileNode->psPrev;
    }
    
    if(psDirNode->uwFileNodeCount == 0)    
    	psDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_UNMOUNT;
    /**
    @brief free the memory of the file node and its neighbor.
    
    */
    psKillFileNode = psFileNode;
    
    while(psKillFileNode != NULL){

    	psFileNode     = psKillFileNode;
    	psKillFileNode = psKillFileNode->psNeighbor;
    	
    	AIHC_DcfFreeFileNode(psFileNode);
    }
        
    return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_FileDeletedMask(INT8* pchFileName, AHC_FS_ATTRIBUTE* sFileAttribute)
{

	if(m_sFileDeletedMask == DCF_FILE_PROTECT_NONE){
		/**
		@brief	kill all.
		*/
		return AHC_TRUE;
	
	}

	if(m_sFileDeletedMask & DCF_FILE_PROTECT_READONLY){
		/**
		@brief	the attribute of read only.
		*/
		if(*sFileAttribute & AHC_FS_ATTR_READ_ONLY) {
            return AHC_FALSE;
        }    
	}
	#if (DCF_DCFX == 1)
	if(m_sFileDeletedMask & DCF_FILE_PROTECT_CHARLOCK){
		/**
		@brief	the free character of file name is the same as the locked free char
		*/
		if( AIHC_DCF_WhichIsBoss(pchFileName, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL ){
	    	return AHC_FALSE;
	    }
	
	}
	#endif ///< (DCF_DCFX == 1)
	if(m_sFileDeletedMask & DCF_FILE_PROTECT_NONLOCK){
		if(!( (*sFileAttribute & AHC_FS_ATTR_READ_ONLY) 
		      #if (DCF_DCFX == 1)
		      || (AIHC_DCF_WhichIsBoss(pchFileName, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL)
		      #endif///< (DCF_DCFX == 1)
		      )){
            return AHC_FALSE;
        }    
	}


	return AHC_TRUE;
}

/**
@brief	When you want to delete one file, you should call this API.
		This API clear the counter of DB and release the memory of this file node.
		
WARNING: need to confirm the file node is the neighbor of one file node or not.

*/
AHC_BOOL AIHC_DCF_DeleteFile(UINT16 uwDirKey, UINT16 uwFileKey, INT8 *pchFileName)
{
    UINT16          uwRemoveFileKey;
    INT8            chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    UINT8           byFileType;
    
    DCF_FILE_NODE   *psFileNode;
    DCF_DIR_NODE    *psDirNode;
    //printc("AIHC_DCF_DeleteFile \r\n");
    //No more file entries, return SUCCESS
    if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM] == 0 )
        return AHC_TRUE;
    /**
    @brief use the dir key to find the dir.
    
    */
    
    if( uwDirKey != m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey ){
        
        if ( AIHC_DCF_FindDir(NULL, uwDirKey, &psDirNode) == AHC_FALSE ){
            return AHC_FALSE;
        }else{
	        AIHC_DCF_MountDirNode(psDirNode, 
								  NULL, 
								  0xFFFF,
							      0,
							      DCF_DIR_MOUNT_TYPE_UNMOUNT);
        }
    }
    else {
        psDirNode = m_DcfDB[m_uiDBIndex].psPowerDirNode;
    }

    if ( pchFileName != NULL ) {
        //Get key and free chars
        if ( AIHC_DCF_GetFileKey(pchFileName, &uwRemoveFileKey, chFileFreeChar, &byFileType) == AHC_FALSE )
            return AHC_FALSE;
    }
    else {
    	AIHC_DCF_GetTypeInFileMap(uwFileKey, &byFileType);
        uwRemoveFileKey = uwFileKey;                
    }
	/*
	@brief	keep the max file key even that the file is killed.
	if(uwRemoveFileKey == psDirNode->uwMaxFileKey){
		AIHC_DCF_GetKeyInFileMap(0xFFFF, &psDirNode->uwMaxFileKey, AHC_FALSE);
	}
	*/
    AIHC_DCF_UpdateDBInfo(psDirNode, uwRemoveFileKey, byFileType, byFileType, AHC_TRUE, AHC_FALSE);
    AIHC_DCF_SetOneInFileMap(uwRemoveFileKey, DCF_INVALID_NUMBER_8);
    //Find node
    if ( AIHC_DCF_FindFileNode(psDirNode, NULL, uwRemoveFileKey, &psFileNode) == AHC_TRUE ) {
		return AIHC_DCF_RemoveFileNode(psDirNode, psFileNode, AHC_FALSE);
    }else{
    	return AHC_TRUE;
    }


    
    return AHC_TRUE;

}

/**
@brief	delete the dir when it is empty.
		
*/
static AHC_BOOL AIHC_DCF_ClearEmptyDir(INT8* pchDirName, DCF_DIR_NODE *psDirNode)
{
	UINT32 uiDirNameSize;
	UINT32 uiDirID;
	UINT32 uiFileCount;
	
	uiDirNameSize = STRLEN(pchDirName);
	
	if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM] != DCF_INVALID_NUMBER_16){
		if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM] > 0){
			return AHC_FALSE;
		}
	}
	
	if(AHC_DCF_DirOpen(pchDirName, uiDirNameSize, &uiDirID) != AHC_ERR_NONE){
		return AHC_FALSE;
	}
	
	AHC_DCF_DirGetNumFiles(uiDirID, &uiFileCount);
	AHC_DCF_DirClose(uiDirID);
	
	if(uiFileCount > 0){
		return AHC_FALSE;
	}else{
		
		AHC_DCF_DirRemove((INT8*)pchDirName, uiDirNameSize); 

		if(psDirNode != NULL)
   			AIHC_DCF_DeleteDir(psDirNode);

		return AHC_TRUE;
	}

	
}

/**
@brief	The mask for AIHC_DCF_ParseFile()
*/
static AHC_BOOL AIHC_DCF_ParseFileMask(AHC_FS_ATTRIBUTE* sFileAttribute, AHC_FS_FILETIME* sFileTime)
{

    if ( ( m_bCountHiddenObj == AHC_TRUE ) && ( m_bFilterByDate == AHC_FALSE ) ){
        return AHC_TRUE;
    }
    else {
            
        if ( m_bCountHiddenObj == AHC_FALSE ) {

            if ( *sFileAttribute & AHC_FS_ATTR_HIDDEN ) {
                return AHC_FALSE;
            }
        }

        if ( m_bFilterByDate ) {
			/**
			@brief	this part is the filter of date.
			*/
            if ( !( (sFileTime->usYear  >= m_ulFilterDate[0]) &&
                    (sFileTime->usMonth >= m_ulFilterDate[1]) &&
                    (sFileTime->usDay   >= m_ulFilterDate[2]) ) )
            {
                return AHC_FALSE;
            }
        }
    }
    
    return AHC_TRUE;

}
/**
@brief	reset this counter of this dir node and parse all the file of this dir.
*/
static AHC_BOOL AIHC_DCF_ParseFile(	DCF_DIR_NODE *psDirNode, 
									INT8         *pchDirName, 
									UINT16       uwFileMaxCount,
									UINT16       uwTargetFilekey,
									DCF_DIR_MOUNT_TYPE type )
{
    INT8                chFileName[MAX_FULL_FILENAME_SIZE];
    INT8				chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    AHC_FS_ATTRIBUTE	attribute;
    AHC_FS_FILETIME		FileTimeStru;
    UINT32              uiFileSize;
    UINT32              uiFileID;
    UINT32              uiNameLength;
    UINT32              error;
    UINT8               byFileMode;
    
    UINT16              uwCurFileCount;
    
    MEMSET(chFileName, DCF_RESET_VALUE, sizeof(chFileName));
    MEMSET(chFileFreeChar, DCF_RESET_VALUE, sizeof(chFileFreeChar));
    
    uiNameLength    = STRLEN(pchDirName);
	uwCurFileCount  = 0;
	
	if(psDirNode->byMountMode == DCF_DIR_MOUNT_TYPE_ALL){
		/**
		@brief this dir node was already mounted.
		*/
		return AHC_TRUE;
	}
	/**
	@brief	make sure that the proccess of free the memory of file nodes is normal.
	*/
	if(uwFileMaxCount > m_sFileMem.uiMaxCount){
		uwFileMaxCount = m_sFileMem.uiMaxCount;
	}

    if(AHC_DCF_DirOpen(pchDirName, uiNameLength, &uiFileID) != AHC_ERR_NONE){
    	return AHC_FALSE;
    }
    
    byFileMode = AHC_FILE_NAME | AHC_ATTRIBUTE | AHC_ENTRY_SIZE | AHC_FILE_TIME;
	/**
	@brief clear the related info for this dir node.
	*/
    AIHC_DCF_ClearCompareFileMap(m_uiDBIndex);
    AIHC_DCF_ClearSearchCache(m_uiDBIndex);
    AIHC_DCF_ClearDBInfo(psDirNode);
    
    m_DcfDB[m_uiDBIndex].psPowerDirNode = psDirNode;
    psDirNode->byMountMode = type;
    

    
    while(1) {
    	/**	@brief	get files. */
        error = AHC_DCF_GetFileList( uiFileID,
                                     byFileMode,
                                     chFileName,
                                     &attribute,
                                     &FileTimeStru,
                                     &uiFileSize );

        if ( AHC_FS_ERR_NO_MORE_ENTRY == error ){
        	/**
        	@brief no files in this dir.
        	*/
            break;
        }
        
        if ( !(AHC_FS_ATTR_DIRECTORY & attribute) ){
			            
			UINT16          uwNewFileKey;
		    UINT8           byFileType;
		    UINT8           byOldFileType;
       	    DCF_FILE_NODE   *psNewFileNode;
       	    DCF_FILE_NODE   *psLimitFileNode;

			if ( AIHC_DCF_GetFileKey(chFileName, &uwNewFileKey , chFileFreeChar, &byFileType) == AHC_TRUE ) {
				if((DCFMountCallBack != NULL) && (m_bMountCallBack == AHC_TRUE)){
					(*DCFMountCallBack)(chFileName,
										chFileFreeChar,
										uwNewFileKey,
										byFileType,
										&attribute,
										&FileTimeStru,
										uiFileSize);
				
				}
				
				if(AIHC_DCF_CompareFileMap(uwNewFileKey, byFileType, &byOldFileType) == AHC_TRUE){
    				/**
    				@brief	maintain the file map and DB counter
    				*/
    				AIHC_DCF_UpdateDBInfo(psDirNode, uwNewFileKey, byFileType, byOldFileType, AHC_FALSE, AHC_FALSE);
    			}
    			
    			
    			if(m_bParsePage == AHC_TRUE){

    				UINT64 uiiClusterPerFile;
                    
                    //brief : to count name locked files number
                    #if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT!=LOCK_FILE_STOP) //TBD only for DBcount = 1
                        if(memcmp(chFileName, FILE_RENAME_STRING, strlen(FILE_RENAME_STRING))==0){
                            m_ulLockFileNum++;
                            AHC_DCF_UpdateLockFileTable(psDirNode->uwDirKey,uwNewFileKey,byFileType,NULL);
                        }
                    #endif
                    
    				uiiClusterPerFile = (uiFileSize + m_uiBytesPerCluster - 1)/m_uiBytesPerCluster;    			

	    			if(attribute & AHC_FS_ATTR_READ_ONLY){
	    				
	    				m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster += uiiClusterPerFile;
	    				
	    			}
	    			#if (DCF_DCFX == 1)
	    			else if(AIHC_DCF_WhichIsBoss(chFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
	    				/**
	    				@brief	parse the lock file.
	    				*/
	    				m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster += uiiClusterPerFile;
	    				m_DcfDB[m_uiDBIndex].ppsFileCountInDir[psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount++;
	    				
	    				AIHC_DCF_UpdateDCFxPage(psDirNode, chFileFreeChar, uwNewFileKey, attribute, FileTimeStru, uiFileSize);

	    			}
	    			#endif///< (DCF_DCFX == 1)
	    			else{
	    				m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster += uiiClusterPerFile;
	    				m_DcfDB[m_uiDBIndex].ppsFileCountInDir[psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount++;

	    			}
	    			
	    			if(AIHC_DCF_CyclicDeletedMask(chFileName, &attribute, &FileTimeStru) == AHC_TRUE){
	    			
	    				if(m_sParsedKillKey[0].uwDirKey == psDirNode->uwDirKey){
	    				
	    					if(m_sParsedKillKey[0].uwFileKey >= uwNewFileKey){
	    						m_sParsedKillKey[0].uwFileKey = uwNewFileKey;
	    					
	    					}
	    				
	    				}else if( (m_sParsedKillKey[0].uwDirKey > psDirNode->uwDirKey) || (m_sParsedKillKey[0].uwDirKey == 0)){

	    					m_sParsedKillKey[0].uwDirKey = psDirNode->uwDirKey;
	    					m_sParsedKillKey[0].uwFileKey = uwNewFileKey;
	    				}
	    				
	    				if(m_sParsedKillKey[1].uwDirKey == psDirNode->uwDirKey){
	    				
	    					if(m_sParsedKillKey[1].uwFileKey <= uwNewFileKey){
	    						m_sParsedKillKey[1].uwFileKey = uwNewFileKey;
	    					
	    					}
	    				
	    				}else if( (m_sParsedKillKey[1].uwDirKey < psDirNode->uwDirKey) || (m_sParsedKillKey[1].uwDirKey == 0)){

	    					m_sParsedKillKey[1].uwDirKey = psDirNode->uwDirKey;
	    					m_sParsedKillKey[1].uwFileKey = uwNewFileKey;
	    				}
	    			
	    			
	    			}

    			}
    			
				if ( AIHC_DCF_ParseFileMask(&attribute, &FileTimeStru) == AHC_TRUE ) {
				
					if(type != DCF_DIR_MOUNT_TYPE_UNMOUNT){
		        		
		        		uwCurFileCount++;
		        		
	        			if( (uwCurFileCount > uwFileMaxCount) && 
	        			    (type & (DCF_DIR_MOUNT_TYPE_MIN|DCF_DIR_MOUNT_TYPE_KEY|DCF_DIR_MOUNT_TYPE_MAX)) ){

	    					UINT16 uwRootKey = (psDirNode->psRootFileNode) ? psDirNode->psRootFileNode->uwFileKey : 0;
	    					UINT16 uwLastKey = (psDirNode->psLastFileNode) ? psDirNode->psLastFileNode->uwFileKey : 0xFFFF;
							
	        				if(type == DCF_DIR_MOUNT_TYPE_KEY){
	        				
    
	        					if(uwTargetFilekey >= uwLastKey){
	        						/**
	        						
	        							Root                    Last    T
	        							|------------------------|      |
	        						
	        						*/
									psLimitFileNode = psDirNode->psRootFileNode;
	        					
	        					}else if(uwTargetFilekey <= uwRootKey){
	        						/**
	        						
			        					    T	Root                    Last
			        						|	|------------------------|
	        						
	        						*/
	        						psLimitFileNode = psDirNode->psLastFileNode;
	        					
	        					}else{
	        						/**
	        						
			        					   	Root       T            Last
			        						|----------|-------------|
	        						
	        						*/
	        						if( (uwNewFileKey > uwLastKey) || (uwNewFileKey < uwRootKey) )
	        							continue;
	        							
	        						if( (uwTargetFilekey - uwRootKey) > (uwLastKey - uwTargetFilekey) ){
	        							/**
	        						
			        					   	Root             T      Last
			        						|----------------|-------|
	        						
	        							*/
	        							psLimitFileNode = psDirNode->psRootFileNode;
	        							
	        							if(uwNewFileKey == uwRootKey){
											AIHC_DCF_RemoveFileNode(psDirNode, psLimitFileNode, AHC_TRUE);
											continue;
										}
	        						
	        						}else{
	        							/**
	        						
			        					   	Root    T               Last
			        						|-------|----------------|
	        						
	        							*/
		        						psLimitFileNode = psDirNode->psLastFileNode;
	        							if(uwNewFileKey == uwLastKey){
											AIHC_DCF_RemoveFileNode(psDirNode, psLimitFileNode, AHC_TRUE);
											continue;
										}
	        						}
	        					}

	        				}else if(type == DCF_DIR_MOUNT_TYPE_MAX){
	    					    

	    					    
	        					if(uwNewFileKey < uwRootKey)
	        						continue;
								else
									psLimitFileNode = psDirNode->psRootFileNode;

	        				}else{//DCF_DIR_MOUNT_TYPE_MIN
	    					
								if(uwNewFileKey > uwLastKey)
									continue;
								else
									psLimitFileNode = psDirNode->psLastFileNode;

	        				}
	        				
                            if(psLimitFileNode != NULL)
	        				    AIHC_DCF_RemoveFileNode(psDirNode, psLimitFileNode, AHC_TRUE);
	        				
	        				psNewFileNode = AIHC_DcfAllocFileNode();

	        			}else{

		        			psNewFileNode = AIHC_DcfAllocFileNode();
		        			
		        			if(psNewFileNode == NULL){

			        			if(AIHC_DCF_DynamicFreeFileNode(psDirNode) == AHC_TRUE){
			        				psNewFileNode = AIHC_DcfAllocFileNode();
			        			}else{
		        					#if (DCF_DEBUG >= DCF_DEBUG_ERR )
			        				printc("[DCF ERROR] Free Memory Fail 0x01\r\n");
			        				#endif
			        				return AHC_FALSE;
			        			}
		        			}
	        			
	        			}
	        			
						/**	@brief	setup the file node which you wanna add. */
				        psNewFileNode->uwFileKey  = uwNewFileKey;
				        psNewFileNode->byFileType = byFileType;
		        
				        MEMCPY(psNewFileNode->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
				        
			        	AIHC_DCF_AddFileNode(psDirNode, psNewFileNode);

			        	
		        	
		        	}
		        	/*
		        	else{// bParseOnly = AHC_TRUE
		        		psDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_NONE;
		        	}
		        	*/
	        	}
	        }
	        /*
	        else{
	        	//invalid file name
	        }
			*/
		}
            
	}///< the end of while(1) loop
	
	if(psDirNode->uwFileNodeCount < m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]){
	
		if(psDirNode->byMountMode != DCF_DIR_MOUNT_TYPE_ALL){
			psDirNode->byMountMode = type;
		}else{
			psDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_MAX;
		
		}
	}else if (psDirNode->uwFileNodeCount == m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[ psDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM ]){
		psDirNode->byMountMode = DCF_DIR_MOUNT_TYPE_ALL;
	}else{
		printc("DCF ERROR\r\n");
	
	}
    
    error = AHC_DCF_DirClose(uiFileID);
                
    return AHC_TRUE;
}

/**
@brief	parse all the dir in the root dir 

@param[in]  pchFullDirName
@param[in]  uwDirNumber
@param[in]  bTop

*/
static AHC_BOOL AIHC_DCF_ParseDir(INT8* pchFullDirName, UINT16 uwDirNumber, AHC_BOOL bTop)
{
    UINT32              error;
    UINT32              uiDirID;
    UINT32              uiDirLength;  
    UINT8               byFileMode;
    AHC_FS_ATTRIBUTE	attribute;
    AHC_FS_FILETIME		FileTimeStru;
    UINT32              EntrySize;
    INT8                chDirName[MAX_FULL_FILENAME_SIZE];
    
    uiDirLength	= STRLEN(pchFullDirName);

	if(AHC_DCF_DirOpen(pchFullDirName, uiDirLength, &uiDirID) != AHC_ERR_NONE){
		AHC_DCF_DirClose(uiDirID);
		return AHC_FALSE;
	
	}
        
    byFileMode = AHC_FILE_NAME | AHC_ATTRIBUTE | AHC_ENTRY_SIZE;
        
    //PARSE DCF Directories
    while(1) {
    	
        error = AHC_DCF_GetFileList( uiDirID,
									 byFileMode,
									 chDirName,
									 &attribute,
									 &FileTimeStru,
									 &EntrySize );

        if ( AHC_FS_ERR_NO_MORE_ENTRY == error ){
        	/**
        	@brief no file in this dir
        	*/
            break;
        }

        // Skip first two items
        if( chDirName[0] == '.' )
        {
            continue;
        }

        if (AHC_FS_ATTR_DIRECTORY & attribute) {
        	/**	@brief	acquire the next directory. */
            AIHC_DCF_AddDirNode(chDirName);

        }
    }
    
    error = AHC_DCF_DirClose(uiDirID);

	return AHC_TRUE;

}



/**
@brief	this api is used to create the file name of cyclic record.

the interface of controlling m_DcfDB.psFileCtlDirNode.

*/
static AHC_BOOL AIHC_DCF_ChangeFileCtlDirNode(UINT16* puwDirKey, UINT16* puwFileKey, UINT8 *bCreateNewDir)
{

    UINT32		uiDirIndex;///< 0 ~ m_ulMaxDcfDirNum => MIN_DCF_DIR_KEYNUM ~ MIN_DCF_DIR_KEYNUM+m_ulMaxDcfDirNum.
	UINT16		uwDirKey;
	UINT16		uwFileKey;
	AHC_BOOL	bRecursive;
	
	if(m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwDirKey >= m_ulMaxDcfDirNum){
		/**
		@brief	find a new dir node from the min dir key.
		*/
		uiDirIndex = 0;
		bRecursive = AHC_FALSE;

	}else{
		/**
		@brief	find a new dir node from the file control dir key.
		*/	
		uiDirIndex = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM;
		bRecursive = AHC_TRUE;

	}

    for( ; uiDirIndex < m_ulMaxDcfDirNum ; uiDirIndex++){
    	/**
    	brief find the first empty dir from the min dir key.
    	*/
    	if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uiDirIndex] == DCF_INVALID_NUMBER_16){
    		break;
    	}
    	
    	if( (uiDirIndex == m_ulMaxDcfDirNum - 1) && (bRecursive == AHC_TRUE) ){
    		/**
    		@brief	return to the min dir key.
    		*/
    		printc("ChangeFileCtlDirNode handler 0x01 \r\n");
    		bRecursive		= AHC_FALSE;
    		uiDirIndex		= 0;
    	}
    	
    }
    
	if(uiDirIndex >= m_ulMaxDcfDirNum){
		/**
		@brief no empty dir
		*/
		DCF_DIR_NODE *psDir;
		/**
		@brief	all the dir is not empty 
				so find the dir with the max file key is not over than m_ulMaxDcfFileInDir.
		
		*/
		psDir = m_DcfDB[m_uiDBIndex].psLastDirNode;
		
		while(psDir != NULL){
		
			if(psDir->uwMaxFileKey < m_ulMaxDcfFileInDir){
				break;	
			}

			psDir = psDir->psPrev;

		}
		
		if(psDir != NULL){
			/**
			@brief	find one
			*/
			m_DcfDB[m_uiDBIndex].psFileCtlDirNode = psDir;
			uwDirKey      = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwDirKey;
			uwFileKey     = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwMaxFileKey + 1;

		}else{
			/**
			@brief	can not find one so fill the gap in the non-filled dir node.
			*/
			for(uiDirIndex = 0 ; uiDirIndex < m_ulMaxDcfDirNum ; uiDirIndex++ ){
				if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uiDirIndex] < m_ulMaxDcfFileInDir){
					break;
				}
			}
			
			if(uiDirIndex >= m_ulMaxDcfDirNum){
				printc("ChangeFileCtlDirNode handler 0x02 \r\n");
				return AHC_FALSE;
			
			}else{

		    	uwDirKey = MIN_DCF_DIR_KEYNUM + uiDirIndex;
		    	
		    	if(m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey != uwDirKey){
		    	
		    		AIHC_DCF_FindDir(NULL, uwDirKey, &psDir);
		    		AIHC_DCF_MountDirNode(psDir, 
										  NULL, 
										  0xFFFF,
									      0,
									      DCF_DIR_MOUNT_TYPE_UNMOUNT);
		    	}
		    	
				m_DcfDB[m_uiDBIndex].psFileCtlDirNode = m_DcfDB[m_uiDBIndex].psPowerDirNode;

				AIHC_DCF_FindHoleInFileMap(MIN_DCF_FILE_KEYNUM, m_ulMaxDcfFileInDir, &uwFileKey);
		    		
	    		if(uwFileKey == 0){
	    			printc("ChangeFileCtlDirNode handler 0x03 \r\n");
	    			return AHC_FALSE;
	    		}
	    		
	    		m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwNextFileKey = uwFileKey + 1;
	    		
		    }
		}
	    
	    *bCreateNewDir = AHC_FALSE;
	    
	}else{
		/**
		@brief the first empty dir
		*/
		uwDirKey		= MIN_DCF_DIR_KEYNUM + uiDirIndex;
		uwFileKey		= MIN_DCF_FILE_KEYNUM;
		*bCreateNewDir	= AHC_TRUE;
	
	} 
	   
	*puwDirKey  = uwDirKey;
	*puwFileKey = uwFileKey;
	
	return AHC_TRUE;
}

#if 0
void __SEARCH_CACHE__(){}
#endif

static void AIHC_DCF_ClearSearchCache(UINT32 uiDBIndex)
{
   MEMSET(m_DcfDB[uiDBIndex].sSearchCache.puiCacheAddr, DCF_INVALID_NUMBER_32, m_DcfDB[uiDBIndex].sSearchCache.uiCacheSize);
}


#if 0
void __FILE_MAP__(){}
#endif



static void AIHC_DCF_ClearCompareFileMap(UINT32 uiDBIndex)
{
   MEMSET(m_DcfDB[uiDBIndex].sFileMap.pbyMapAddr, DCF_INVALID_NUMBER_8, m_DcfDB[uiDBIndex].sFileMap.uiMapSize);
}

/**

compare the file type with the same file name

*/
static AHC_BOOL AIHC_DCF_CompareFileMap(UINT16 uwFileKey, UINT8 byNewFileType, UINT8* byOldFileType)
{

	if( byNewFileType < (*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uwFileKey - 1))) {
		/**
		@brief need to exchange the counter of file type
		*/
		*byOldFileType = *(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uwFileKey - 1);
		*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uwFileKey - 1) = byNewFileType;
		return AHC_TRUE;		

	}else{
		/**
		@brief no need
		*/
		return AHC_FALSE;
	
	}
}

static AHC_BOOL AIHC_DCF_GetTypeInFileMap(UINT16 uwFileKey, UINT8* byFileType)
{
	*byFileType = *(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uwFileKey - 1);
	return AHC_TRUE;		
}

static AHC_BOOL AIHC_DCF_SetOneInFileMap(UINT16 uwFileKey, UINT8 byFileType)
{
	*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uwFileKey - 1) = byFileType;
	return AHC_TRUE;
}
/**
@brief	parse the file key into the index of the file map.

		index: 0~m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize => file key : MIN_DCF_FILE_KEYNUM~MAX_DCF_FILE_KEYNUM

*/

static AHC_BOOL AIHC_DCF_ParseKeyInFileMap(UINT16 uwFileKey, UINT16* uwIndex)
{

	UINT32 uiSearchIndex, uiTargetIndex;
	UINT32 uiIndexSum;
	
	uiIndexSum = 0;
	
	uiTargetIndex = uwFileKey - MIN_DCF_FILE_KEYNUM + 1;
	
	for(uiSearchIndex = 0; uiSearchIndex < uiTargetIndex ; uiSearchIndex++){
		
		if( m_DcfDB[m_uiDBIndex].chAllowedFileType[*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uiSearchIndex)] == 1 ){
			uiIndexSum++;
		}
	}
	if(uiIndexSum == 0){
		*uwIndex = 0;
		return AHC_FALSE;
	}else{
		*uwIndex = uiIndexSum - 1;
		return AHC_TRUE;
	}

}


/**
@brief	get the file key in file map by corresponding position.
		1 => the first file node in file map is the allowed file type.
		It is for the browser mode which wanna get dcf info.
*/
static AHC_BOOL AIHC_DCF_ParseIndexInFileMap(UINT16 uwIndex, UINT16* uwFileKey)
{

	UINT32 uiSearchIndex;
	UINT32 uiIndexSum;
	
	uiIndexSum = 0;
	
	for(uiSearchIndex = 0; uiSearchIndex < m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize ; uiSearchIndex++){
		
		if( m_DcfDB[m_uiDBIndex].chAllowedFileType[*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uiSearchIndex)] == 1 ){
			uiIndexSum++;
		}
		
		if(uwIndex == uiIndexSum)
			break;
	
	}
	
	if(uwIndex == uiIndexSum){
		*uwFileKey = uiSearchIndex + 1;
		return AHC_TRUE;
	}else{
		*uwFileKey = DCF_INVALID_NUMBER_16;
		return AHC_FALSE;
	}
}


/**
@brief	find the key from the start position or end position of the file map
		start position => bMin = TRUE
		end position   => bMin = FALSE
*/
static AHC_BOOL AIHC_DCF_GetKeyInFileMap(UINT16 uwFileKeySt, UINT16* uwFileKey, AHC_BOOL bMin)
{

	UINT32 uiSearchIndex;

	if(bMin == AHC_FALSE){
	
		for(uiSearchIndex = m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize; uiSearchIndex > 0 ; uiSearchIndex--){
			
			if(*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uiSearchIndex - 1) != DCF_INVALID_NUMBER_8){
				break;
			}	
		}
		
		if(uiSearchIndex == 0){
			*uwFileKey = DCF_INVALID_NUMBER_16;
			return AHC_FALSE;
		}else{
			*uwFileKey = uiSearchIndex;
			return AHC_TRUE;
		}
		
	}else{

		for(uiSearchIndex = (uwFileKeySt - MIN_DCF_FILE_KEYNUM); uiSearchIndex < m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize ; uiSearchIndex++){
			
			if(*(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uiSearchIndex) != DCF_INVALID_NUMBER_8){
				break;
			}	
		}
		
		if(uiSearchIndex == m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize){
			*uwFileKey = DCF_INVALID_NUMBER_16;
			return AHC_FALSE;
		}else{
			*uwFileKey = uiSearchIndex + MIN_DCF_FILE_KEYNUM;
			return AHC_TRUE;
		}
	
	
	}
}
/**
@brief	map position : 0 ~ m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize <=> key : MIN_DCF_FILE_KEYNUM ~ MAX_DCF_FILE_KEYNUM.

		m_DcfDB[m_uiDBIndex].sFileMap.uiMapSize = MAX_DCF_FILE_KEYNUM - MIN_DCF_FILE_KEYNUM + 1;
		
WARNING: only find 
		
*/
static AHC_BOOL AIHC_DCF_FindHoleInFileMap(UINT16 uwFileKeySt, UINT16 uwFileKeyEnd, UINT16* uwFileKey)
{
	UINT32 uiHole;
	
	*uwFileKey = 0;
	
	if( (uwFileKeySt < MIN_DCF_FILE_KEYNUM) || (uwFileKeyEnd > MAX_DCF_FILE_KEYNUM) ){
		return AHC_TRUE;
	}
	
	
	for( uiHole = uwFileKeySt - MIN_DCF_FILE_KEYNUM ; uiHole < uwFileKeyEnd ; uiHole++ ){
		if( *(m_DcfDB[m_uiDBIndex].sFileMap.pbyMapAddr + uiHole) == DCF_INVALID_NUMBER_8){
			*uwFileKey = uiHole + MIN_DCF_FILE_KEYNUM;
			break;
		}
	}

	return AHC_TRUE;
}

#if 0
void __CYCLIC__(){}
#endif

/**
@brief	check the attribute of dir by AIHC_DCF_CyclicDeletedMask() and m_sCyclicDeletedMask.

AHC_TRUE	=> there are some files in this dir which can be deleted.
AHC_FALSE	=> there are no files in this dir which can be deleted.
*/
static AHC_BOOL AIHC_DCF_CheckDirStatus(UINT16 uwDirKey)
{
	AHC_BOOL bNonEmpty = AHC_FALSE;
	
	if(m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM] == DCF_INVALID_NUMBER_16){
		return AHC_FALSE;
	}
	#if (DCF_DCFX == 1)
	if(!(m_sCyclicDeletedMask & DCF_FILE_PROTECT_CHARLOCK)){
		
		if(m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount > 0)
			bNonEmpty = AHC_TRUE;
	}
	#endif///< #if (DCF_DCFX == 1)
	if(!(m_sCyclicDeletedMask & DCF_FILE_PROTECT_READONLY)){
		UINT16 uwReadOnly = m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM] - 
							m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount - 
							m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount;
							
		if(uwReadOnly > 0)
			bNonEmpty = AHC_TRUE;
	}
	
	if(!(m_sCyclicDeletedMask & DCF_FILE_PROTECT_NONLOCK)){
		if(m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount > 0)
			bNonEmpty = AHC_TRUE;
	}

	return bNonEmpty;
}

/**
@brief	when we do not have the kill dir key and kill file key, 
		its the mechanism to find one new kill dir key and kill file key.

*/
static AHC_BOOL AIHC_DCF_FindKillKey(void)
{
	DCF_DIR_NODE *psDir;
	
	if(m_DcfDB[m_uiDBIndex].psFileCtlDirNode == NULL){
	
		if(AIHC_DCF_FindMinDirNode(m_uiDBIndex, &psDir, DCF_DIR_MOUNT_TYPE_MASK) == AHC_FALSE){
			m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
			m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
			return AHC_FALSE;		
		}

	}else{
		if(AIHC_DCF_FindFarDirNode(m_DcfDB[m_uiDBIndex].psFileCtlDirNode, &psDir) == AHC_FALSE){
			m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
			m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
			return AHC_FALSE;
		}
	}
	
	{
	AHC_BOOL bFound = AHC_FALSE;
	
	do{
		if(AIHC_DCF_CheckDirStatus(psDir->uwDirKey) == AHC_TRUE){
			bFound = AHC_TRUE;
			break;
		}
		
	}while(AIHC_DCF_FindNextDirNode(&psDir) == AHC_TRUE);
	
	if(bFound == AHC_FALSE){
		m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
		m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
		return AHC_FALSE;
	}
	
	}
	

	if(AIHC_DCF_MountDirNode(psDir, NULL, 0xFFFF, 0, DCF_DIR_MOUNT_TYPE_MIN) == AHC_TRUE){
		
		m_DcfDB[m_uiDBIndex].uwKillDirKey	= psDir->uwDirKey;
		m_DcfDB[m_uiDBIndex].uwKillFileKey	= psDir->psRootFileNode->uwFileKey;
        printc("[DCF INFO] Find 1 KillDir: %d, KillFile : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
	}else{
	
		m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
		m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
        printc("[DCF INFO] Find 2 KillDir: %d, KillFile : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
		return AHC_FALSE;
	
	}
	
	
	return AHC_TRUE;
}


/**
@brief	change the kill key

*/
static AHC_BOOL AIHC_DCF_ChangeKillKey(void)
{
	DCF_DIR_NODE	*psDir;
	UINT16			uwFileKeySt;
    
    #if (DCF_DEBUG >= DCF_DEBUG_ALL )
    printc("[DCF INFO] chg KillDir: %d, KillFile : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
    #endif
    
	if(	(AIHC_DCF_FindDir(NULL, m_DcfDB[m_uiDBIndex].uwKillDirKey, &psDir) == AHC_TRUE) &&
		(AIHC_DCF_CheckDirStatus(psDir->uwDirKey) == AHC_TRUE) ){
		/**
		@brief	the dir node with kill dir key is not deleted and 
				the dir node has files which can be deleted by AIHC_DCF_DeleteCyclicFile().
		
		*/
	    if( psDir != m_DcfDB[m_uiDBIndex].psPowerDirNode ){

	        AIHC_DCF_MountDirNode(psDir, 
								  NULL, 
								  0xFFFF,
							      m_DcfDB[m_uiDBIndex].uwKillFileKey,
							      DCF_DIR_MOUNT_TYPE_KEY);
	    }else{
	        psDir = m_DcfDB[m_uiDBIndex].psPowerDirNode;
	    }
	    
	    uwFileKeySt = m_DcfDB[m_uiDBIndex].uwKillFileKey + 1;
	    
	}else{
		/**
		@brief	find the next dir node, which has files which can be deleted.
		
		*/
		AHC_BOOL bFound = AHC_FALSE;

		if(AIHC_DCF_FindNextDirNodeByKey(m_DcfDB[m_uiDBIndex].uwKillDirKey, &psDir) == AHC_FALSE){
			/**
			@brief	no other dir.
			*/
			m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
			m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
			return AHC_FALSE;
		}
		
		do{
			if(AIHC_DCF_CheckDirStatus(psDir->uwDirKey) == AHC_TRUE){
				bFound = AHC_TRUE;
				break;
			}
			
		}while(AIHC_DCF_FindNextDirNode(&psDir) == AHC_TRUE);
		
		if(bFound == AHC_FALSE){
			// no dir node
			m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
			m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
			return AHC_FALSE;
		}
		
        AIHC_DCF_MountDirNode(psDir, 
							  NULL, 
							  0xFFFF,
						      0,
						      DCF_DIR_MOUNT_TYPE_UNMOUNT);

		uwFileKeySt = MIN_DCF_FILE_KEYNUM;
		
	}
    
    if(psDir != NULL){
		/**
		@brief	found the dir node.
		*/
    	if(AIHC_DCF_GetKeyInFileMap(uwFileKeySt, &m_DcfDB[m_uiDBIndex].uwKillFileKey, AHC_TRUE) == AHC_FALSE){
    		/**
    		@brief	just in case
    		*/
			if(AIHC_DCF_FindNextDirNode(&psDir) == AHC_FALSE){

				m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
				m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
			    return AHC_FALSE;
			}
			/**
			@brief	mount the min range of dir node.
			*/
	        AIHC_DCF_MountDirNode(psDir, 
								  NULL, 
								  0xFFFF,
							      0,
							      DCF_DIR_MOUNT_TYPE_MIN);
							      
			uwFileKeySt = MIN_DCF_FILE_KEYNUM;
					
    		AIHC_DCF_GetKeyInFileMap(uwFileKeySt, &m_DcfDB[m_uiDBIndex].uwKillFileKey, AHC_TRUE);
    	}
    	
    	m_DcfDB[m_uiDBIndex].uwKillDirKey = psDir->uwDirKey;
    	
	}else{
		/**
		@brief	just in case.
		*/
		m_DcfDB[m_uiDBIndex].uwKillDirKey	= 0;
		m_DcfDB[m_uiDBIndex].uwKillFileKey	= 0;
		
		return AHC_FALSE;
	}
    
    #if (DCF_DEBUG >= DCF_DEBUG_ALL )
    printc("[DCF INFO] chg 2 KillDir: %d, KillFile : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
    #endif
	
	return AHC_TRUE;
}

/**
@brief	

AHC_TRUE => you can kill file.
AHC_FALSE => you can not kill file.

*/

AHC_BOOL AIHC_DCF_CyclicDeletedMask(INT8* pchFileName, AHC_FS_ATTRIBUTE* sFileAttribute, AHC_FS_FILETIME* sFileTime)
{

	if(m_sCyclicDeletedMask == DCF_FILE_PROTECT_NONE){
		/**
		@brief	kill all.
		*/
		return AHC_TRUE;
	
	}

	if(m_sCyclicDeletedMask & DCF_FILE_PROTECT_READONLY){
		/**
		@brief	the attribute of read only.
		*/
		if(*sFileAttribute & AHC_FS_ATTR_READ_ONLY) {
            return AHC_FALSE;
        }    
	}
	#if (DCF_DCFX == 1)
	if(m_sCyclicDeletedMask & DCF_FILE_PROTECT_CHARLOCK){
		/**
		@brief	the free character of file name is the same as the locked free char
		*/
		
		if( AIHC_DCF_WhichIsBoss(pchFileName, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL ){
	    	return AHC_FALSE;
	    }
	
	}
    #endif ///< (DCF_DCFX == 1)
	if(m_sCyclicDeletedMask & DCF_FILE_PROTECT_TIME){
		/**
		@brief	the time period is 
		*/
		if( (AIHC_DCF_WhichIsBoss16(sFileTime, &m_sCyclicDeletedEndTime, DCFX_TIME_LENGTH ) == DCF_BOSS_2 ) && 
			(AIHC_DCF_WhichIsBoss16(&m_sCyclicDeletedStartTime, sFileTime, DCFX_TIME_LENGTH) == DCF_BOSS_2 ) ){
				return AHC_FALSE;
		}
	
	}


	return AHC_TRUE;
}

/**
@brief	
*/
static AHC_BOOL AIHC_DCF_DeleteCyclicFile(UINT32* uiSize)
{
		
	DCF_DIR_NODE	*psDir;
	DCF_FILE_NODE	*psFile;
	INT8			chRootName[DCF_MAX_FILE_NAME_SIZE];

	*uiSize = 0;
    
    #if (DCF_DEBUG >= DCF_DEBUG_ALL )
    printc("DB: %d, Dir: %d, File: %d \r\n", m_uiDBIndex, m_DcfDB[m_uiDBIndex].uwKillDirKey,  m_DcfDB[m_uiDBIndex].uwKillFileKey);
    #endif
    
	if(AIHC_DCF_FindDir(NULL, m_DcfDB[m_uiDBIndex].uwKillDirKey, &psDir) == AHC_FALSE){
		/**
		@brief	no dir node has the dir key is the same as the m_DcfDB.uwKillDirKey.
		*/
		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
		printc("DCF Error 0x1 \n");
		#endif
		return AHC_FALSE;
	}
	
	if(psDir != m_DcfDB[m_uiDBIndex].psPowerDirNode){
		AIHC_DCF_MountDirNode(psDir, 
							  NULL, 
							  0xFFFF,
						      m_DcfDB[m_uiDBIndex].uwKillFileKey,
						      DCF_DIR_MOUNT_TYPE_KEY);
	
	}else{
	    
	    if(AIHC_DCF_FindFileNode(psDir, NULL, m_DcfDB[m_uiDBIndex].uwKillFileKey, &psFile) == AHC_FALSE){
	        
    		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
    		printc("DCF Error 0x21 \n");
    		#endif
	        
			AIHC_DCF_MountDirNode(psDir, 
								  NULL, 
								  0xFFFF,
							      m_DcfDB[m_uiDBIndex].uwKillFileKey,
							      DCF_DIR_MOUNT_TYPE_KEY);	    
	    
	    }

	}
	
	if(AIHC_DCF_FindFileNode(psDir, NULL, m_DcfDB[m_uiDBIndex].uwKillFileKey, &psFile) == AHC_TRUE){

		INT8				chSrcFileName[DCF_MAX_FILE_NAME_SIZE];
		INT8				chTempFileName[DCF_MAX_FILE_NAME_SIZE];
		AHC_FS_ATTRIBUTE	sFileAttribute;
		AHC_FS_FILETIME		sFileTime;
		UINT32				uiFileSize = 0;
		UINT32				uiNameLength;
		
		MEMSET(chRootName, DCF_RESET_VALUE, sizeof(chRootName));
	    MEMSET(chSrcFileName, DCF_RESET_VALUE, sizeof(chSrcFileName));
	    STRCPY(chSrcFileName, m_DcfDB[m_uiDBIndex].chRootName);
	    STRCAT(chSrcFileName, "\\");
	    
	    MEMSET(chTempFileName, DCF_RESET_VALUE, sizeof(chTempFileName));
		AIHC_DCF_GetDirFullName(chTempFileName, psDir->uwDirKey, psDir->chDirFreeChar);
	    STRCAT(chSrcFileName, chTempFileName);
	    
	    STRCPY(chRootName, chSrcFileName);
	    
	    MEMSET(chTempFileName, DCF_RESET_VALUE, sizeof(chTempFileName));
	    AIHC_DCF_GetFileFullName(chTempFileName, psFile->uwFileKey, psFile->chFileFreeChar);
        
        
        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        {
            UINT32 i;
            
            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
        		STRCPY(m_chAuxiliaryFileName[i], chSrcFileName);
        		STRCAT(m_chAuxiliaryFileName[i], "\\");
        		STRCAT(m_chAuxiliaryFileName[i], chTempFileName);
        		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
        	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
            }
        }
        #endif
	        
	    STRCAT(chTempFileName, EXT_DOT);
	    STRCAT(chTempFileName, m_DcfSupportFileType[psFile->byFileType]);
	    
	    STRCAT(chSrcFileName, "\\");
	    STRCAT(chSrcFileName, chTempFileName);
		
		uiNameLength = STRLEN(chSrcFileName);
		
		AHC_DCF_FileDirGetInfo(	chSrcFileName, 
								uiNameLength, 
								&sFileAttribute, 
								&sFileTime, 
								&uiFileSize);

		if(AIHC_DCF_CyclicDeletedMask(chTempFileName, &sFileAttribute, &sFileTime) == AHC_TRUE){

            AIHC_DCF_DeleteFile(psDir->uwDirKey, psFile->uwFileKey, NULL);
            
            if(AHC_DCF_FileRemove(chSrcFileName, uiNameLength) == AHC_ERR_NONE){
        
                #if (DCF_AUXILIARY_MAX_NUMBER > 0)
            	{
                UINT32 i;
                
                for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                    printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                    AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
                }
                
                }
            	#endif
            	
				AIHC_DCF_CalculateCluster(	chTempFileName, 
											&sFileAttribute, 
											uiFileSize, 
											psDir->uwDirKey, 
											AHC_FALSE);
				*uiSize = uiFileSize;
				
				AIHC_DCF_ClearEmptyDir((INT8*)chRootName, psDir);
			}else{
				*uiSize = 0;
			
			}
		}else{
			*uiSize = 0;
		}
		
		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
		printc("C F Name : %s , Size : %d \r\n", chSrcFileName, *uiSize);
		#endif

	}else{

		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
		printc("DCF Error 0x2 \r\n");
		#endif

        m_DcfDB[m_uiDBIndex].uwKillDirKey  = 0;  
        m_DcfDB[m_uiDBIndex].uwKillFileKey = 0;
	
	}
	// change	
	AIHC_DCF_ChangeKillKey();

	
	return AHC_TRUE;
}




#if 0
void __DCFX__(){}
#endif

#if (DCF_DCFX == 1)

/**


*/
static AHC_BOOL AIHC_DCF_ControlDCFxRegion(void)
{
	switch(m_sDCFRegionID){
	
	case DCF_REGION_ID_2:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_2G / 100;
		break;
	case DCF_REGION_ID_4:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_4G / 100;
		break;
	case DCF_REGION_ID_8:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_8G / 100;
		break;
	case DCF_REGION_ID_16:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_16G / 100;
		break;
	case DCF_REGION_ID_32:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_32G / 100;
		break;
	case DCF_REGION_ID_64:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_64G / 100;
		break;
	case DCF_REGION_ID_128:
		m_uiDCFxBoundary = m_sMediaInfo.ulTotalClusters * DCFX_REGION_128G / 100;
		break;
	default:
		break;

	}
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("DCFxBoundary    : %d, \r\n", m_uiDCFxBoundary);
	#endif
	
	return AHC_TRUE;
}

/**


*/
static AHC_BOOL AIHC_DCF_ConfirmDCFxDB(INT8* chFullRootName)
{
	UINT32	uiNameLength, uiReadCount, uiDirID;

	MEMSET(m_chDCFxDBName, DCF_RESET_VALUE, sizeof(m_chDCFxDBName));
	
	STRCPY(m_chDCFxDBName, chFullRootName);
	
	STRCAT(m_chDCFxDBName, AHC_DATA_DIR);
	
	uiNameLength = STRLEN(m_chDCFxDBName);
	
	if( AHC_DCF_DirOpen(m_chDCFxDBName, uiNameLength, &uiDirID) != AHC_ERR_NONE){
		AHC_DCF_DirCreate(m_chDCFxDBName, uiNameLength);
	}else{
		AHC_FS_DirClose (uiDirID);
	}

	{
		AHC_FS_ATTRIBUTE	sFileAttribute; 
	    AHC_FS_FILETIME		sFileTime;
		UINT32				uiFileSize;
			        
        AHC_DCF_FileDirGetInfo(m_chDCFxDBName, uiNameLength, &sFileAttribute, &sFileTime, &uiFileSize);
	
	    sFileAttribute |= AHC_FS_ATTR_HIDDEN;
        
        AHC_DCF_FileDirSetAttribute(m_chDCFxDBName, uiNameLength, sFileAttribute);
	}

	STRCAT(m_chDCFxDBName, "\\");
	
	STRCAT(m_chDCFxDBName, DCFX_DB_NAME);

	uiNameLength = STRLEN(m_chDCFxDBName);
	/**
	@brief confirm the file name which is wanted to be renamed.
	*/
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("DCFX File Name : %s \r\n", m_chDCFxDBName);
	#endif

	if(AHC_DCF_FileOpen(m_chDCFxDBName, uiNameLength, "rb", STRLEN("rb"), &m_uiDCFxFileID) == AHC_ERR_NONE){
		/**
		@brief	have luck file and confirm it is normal or not.
		*/
		UINT32 uiFileSize, uiErrRet = 0;
		
		uiErrRet = AHC_DCF_FileGetSize(m_uiDCFxFileID, &uiFileSize);
		if(uiErrRet)
			printc("GetFileSize error\r\n");
		
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		printc("Already have DCFX file size : %d \r\n", uiFileSize);
		#endif
		
		if(uiFileSize > (m_sDCFxDBInfo.uiKillCtlOffset + 8)){
			//AHC_DCF_FileSeek(m_uiDCFxFileID, 8, AHC_FS_SEEK_SET);

			// offset
			//AHC_DCF_FileRead(m_uiDCFxFileID, (UINT8*)(&m_sDCFxDBInfo), sizeof(DCFX_DB_INFO), &uiReadCount);

			AHC_DCF_FileSeek(m_uiDCFxFileID, m_sDCFxDBInfo.uiKillCtlOffset + 4, AHC_FS_SEEK_SET);
			AHC_DCF_FileRead(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwKillDirKey), 2, &uiReadCount);
			AHC_DCF_FileRead(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwKillFileKey), 2, &uiReadCount);
		}
		
		AHC_DCF_FileClose(m_uiDCFxFileID);

		if(AHC_DCF_FileRemove(m_chDCFxDBName, uiNameLength) != AHC_ERR_NONE){
			printc("Remove Fail \r\n");
		}

		AHC_DCF_FileOpen(m_chDCFxDBName, uiNameLength, "wb", STRLEN("wb"), &m_uiDCFxFileID);

	}else{
		printc("Create DCFX file \r\n");

		if(AHC_DCF_FileOpen(m_chDCFxDBName, uiNameLength, "wb", STRLEN("wb"), &m_uiDCFxFileID) != 0){
			printc("Create DCFX file failed \r\n");
		}

	}
	
	AHC_DCF_FileClose(m_uiDCFxFileID);
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("DCFX File End \r\n");
	#endif

	return AHC_TRUE;
}

AHC_BOOL AIHC_DCF_OpenDCFxFile(AHC_BOOL bOpen)
{
	if(!(bOpen^m_bDCFxOpened)){
		
		return AHC_TRUE;
	}

	if(bOpen == AHC_TRUE){

		UINT32	uiNameLength;
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		printc("open \r\n");
		#endif
		uiNameLength = STRLEN(m_chDCFxDBName);

		if(AHC_DCF_FileOpen(m_chDCFxDBName, uiNameLength, "r+", STRLEN("r+"), &m_uiDCFxFileID) == AHC_ERR_NONE){
			m_bDCFxOpened = AHC_TRUE;

		}else{
			m_bDCFxOpened = AHC_FALSE;
			return AHC_FALSE;
		}
	}else{
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		printc("close \r\n");
		#endif
		AHC_DCF_FileClose(m_uiDCFxFileID);
		m_bDCFxOpened = AHC_FALSE;
	}

	return AHC_TRUE;
}

AHC_BOOL AIHC_DCF_NeedSort(void)
{
	if(m_sPageCtl.uiPageIndex < m_sPageCtl.uiSortTotalCount){
		return AHC_TRUE;
	}else{
		return AHC_FALSE;
	}
}

static AHC_BOOL AIHC_DCF_InsertData(void *pBufAddr, DCFX_DB_PAGE *psPageInfo, DCFX_DB_DATA* psNewDCFxData)
{
	/**
	@brief	sort data
	*/
	psPageInfo->uiModified = DCFX_PAGE_DIRTY;
	
	if(psPageInfo->uiFirstItem == 0){
		/**
		@brief	the first data
		*/
		psNewDCFxData->uwPrevPos	= DCF_INVALID_NUMBER_16;
		psNewDCFxData->uwNextPos	= DCF_INVALID_NUMBER_16;
		psPageInfo->uiFirstItem		= psNewDCFxData->uwCurPos;
		psPageInfo->uiLastItem		= psNewDCFxData->uwCurPos;
	}else{
		DCFX_DB_DATA*	psPrevDCFxData;
		DCFX_DB_DATA*	psSearchDCFxData = (DCFX_DB_DATA*)((UINT8*)pBufAddr + psPageInfo->uiFirstItem);
		UINT32			uiSearchPos = m_uiDCFxPageInfoSize;
		AHC_BOOL		bFound = AHC_FALSE;
		// must modify
		while(uiSearchPos < psPageInfo->uiUsedBufferOffset){

			if(AIHC_DCF_WhichIsBoss16(&psNewDCFxData->sFileTime, &psSearchDCFxData->sFileTime, DCFX_TIME_LENGTH) == DCF_BOSS_2)
			{
				// get one.
				bFound = AHC_TRUE;
				break;
			}
			
			if(psSearchDCFxData->uwNextPos == DCF_INVALID_NUMBER_16){
				// no data at all 
				break;
			}
			
			uiSearchPos			+= m_uiDCFxDataSize;
			psSearchDCFxData	= (DCFX_DB_DATA*)((UINT8*)pBufAddr + psSearchDCFxData->uwNextPos);
		}
		
		
		if(bFound == AHC_FALSE ){

			psSearchDCFxData->uwNextPos	= psNewDCFxData->uwCurPos;
			psNewDCFxData->uwPrevPos	= psSearchDCFxData->uwCurPos;
			psNewDCFxData->uwNextPos	= DCF_INVALID_NUMBER_16;
			
		}else{

			if(psSearchDCFxData->uwPrevPos != DCF_INVALID_NUMBER_16){
				psPrevDCFxData = (DCFX_DB_DATA*)((UINT8*)pBufAddr + psSearchDCFxData->uwPrevPos);
				psPrevDCFxData->uwNextPos	= psNewDCFxData->uwCurPos;
				psNewDCFxData->uwPrevPos	= psPrevDCFxData->uwCurPos;
			}else{
				psNewDCFxData->uwPrevPos	= DCF_INVALID_NUMBER_16;
			}
			
			psNewDCFxData->uwNextPos	= psSearchDCFxData->uwCurPos;
			psSearchDCFxData->uwPrevPos	= psNewDCFxData->uwCurPos;
		
		}
		
		if(psNewDCFxData->uwPrevPos == DCF_INVALID_NUMBER_16){
			psPageInfo->uiFirstItem = psNewDCFxData->uwCurPos;
		}
		
		if(psNewDCFxData->uwNextPos == DCF_INVALID_NUMBER_16){
			psPageInfo->uiLastItem = psNewDCFxData->uwCurPos;
		}
		
	}

	return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_DeleteData(void *pBufAddr, DCFX_DB_PAGE *psPageInfo, DCFX_DB_DATA* psDCFxData)
{
	DCFX_DB_DATA* psTempDCFxData;
	
	psPageInfo->uiModified = DCFX_PAGE_DIRTY;
	
	if(psDCFxData->uwPrevPos == DCF_INVALID_NUMBER_16){
	
		if(psDCFxData->uwNextPos == DCF_INVALID_NUMBER_16){
			//delete the only one data
			psPageInfo->uiFirstItem			= 0;
			psPageInfo->uiLastItem			= 0;
			psPageInfo->uiUsedBufferOffset	= 0;

		}else{
			//the first data is killed.
			psTempDCFxData				= (DCFX_DB_DATA*)((UINT8*)pBufAddr + psDCFxData->uwNextPos);
			psTempDCFxData->uwPrevPos	= DCF_INVALID_NUMBER_16;
			psPageInfo->uiFirstItem		= psTempDCFxData->uwCurPos;	
		}

	}else{
	
		if(psDCFxData->uwNextPos == DCF_INVALID_NUMBER_16){
			//the last data is killed.
			psTempDCFxData				= (DCFX_DB_DATA*)((INT8*)pBufAddr + psDCFxData->uwPrevPos);
			psTempDCFxData->uwNextPos	= DCF_INVALID_NUMBER_16;
			psPageInfo->uiLastItem		= psTempDCFxData->uwCurPos;
		}else{
			// the mid data is killed
			DCFX_DB_DATA* psTempDCFxData2;
			psTempDCFxData				= (DCFX_DB_DATA*)((UINT8*)pBufAddr + psDCFxData->uwPrevPos);
			psTempDCFxData2				= (DCFX_DB_DATA*)((UINT8*)pBufAddr + psDCFxData->uwNextPos);
			
			psTempDCFxData->uwNextPos	= psTempDCFxData2->uwCurPos;
			psTempDCFxData2->uwPrevPos	= psTempDCFxData->uwCurPos;

		}
	
	}	
	
	MEMSET(psDCFxData, DCF_RESET_VALUE, m_uiDCFxDataSize);
	
	return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_WipeDCFxData(void* pBufAddr, DCFX_DB_DATA* psDCFxData)
{
	DCFX_DB_PAGE* psPageInfo;
	
	/**
	@brief	make sure the page is clear.
	*/
	psPageInfo = (DCFX_DB_PAGE*)pBufAddr;
	
	AIHC_DCF_DeleteData(pBufAddr, psPageInfo, psDCFxData);
	
	return AHC_TRUE;
}


static AHC_BOOL AIHC_DCF_LoadDCFxPage(UINT32 uiPageID, void* pBufAddr)
{
	UINT32 uiFilePos, uiReadCount;
	
	AIHC_DCF_OpenDCFxFile(AHC_TRUE);
	
	uiFilePos = m_sDCFxDBInfo.uiDataOffset + 4 + uiPageID*m_uiDCFxBufSize;

	AHC_DCF_FileSeek(m_uiDCFxFileID, uiFilePos, AHC_FS_SEEK_SET);
	AHC_DCF_FileRead(m_uiDCFxFileID, (UINT8*)(pBufAddr), m_uiDCFxBufSize, &uiReadCount);
	
	AIHC_DCF_OpenDCFxFile(AHC_FALSE);

	return AHC_TRUE;
}
/**
@brief	swap the pages.
*/
static AHC_BOOL AIHC_DCF_SwapDCFxPage(UINT32 uiPageID, void* pBufAddr)
{
	DCFX_DB_PAGE	*psPageInfo;
	UINT32			uiFilePos;
	UINT32			uiReadCount;
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("AIHC_DCF_SwapDCFxPage : %d \r\n", uiPageID);
	#endif
	
	psPageInfo = (DCFX_DB_PAGE*)(pBufAddr);
	
	if(psPageInfo->uiModified == DCFX_PAGE_DIRTY){
		AIHC_DCF_WriteDCFxPage(pBufAddr);
	
	}
	
	AIHC_DCF_OpenDCFxFile(AHC_TRUE);
	
	uiFilePos = m_sDCFxDBInfo.uiDataOffset + 4 + uiPageID*m_uiDCFxBufSize;

	AHC_DCF_FileSeek(m_uiDCFxFileID, uiFilePos, AHC_FS_SEEK_SET);
	AHC_DCF_FileRead(m_uiDCFxFileID, (UINT8*)(pBufAddr), m_uiDCFxBufSize, &uiReadCount);
	
	AIHC_DCF_OpenDCFxFile(AHC_FALSE);
	
	return AHC_TRUE;
}



static AHC_BOOL AIHC_DCF_ResetDCFxDB(UINT8 byIndex)
{
	DCFX_DB_PAGE*	psPageInfo;
	
	if(byIndex == 0){

		MEMSET(m_pbyDCFxTempBuffer, DCF_RESET_VALUE, m_uiDCFxBufSize);
		psPageInfo = (DCFX_DB_PAGE*)m_pbyDCFxTempBuffer;
		psPageInfo->uiUsedBufferOffset = m_uiDCFxPageInfoSize;
		
	}else if(byIndex == 1){

	    UINT32 i;
	    
	    for(i = 0; i < DCF_GOLDEN_PAGE_NUMBER; i++){
	    	
	    	MEMSET(m_GoldenPage[i].pbyBuffer, DCF_RESET_VALUE, m_uiDCFxBufSize);
	    	
			psPageInfo = (DCFX_DB_PAGE*)m_GoldenPage[i].pbyBuffer;
			psPageInfo->uiUsedBufferOffset = m_uiDCFxPageInfoSize;
	    }

		/*
		MEMSET(m_pbyDCFxGoldenBuffer, DCF_RESET_VALUE, m_uiDCFxBufSize);
		psPageInfo = (DCFX_DB_PAGE*)m_pbyDCFxGoldenBuffer;
		psPageInfo->uiUsedBufferOffset = m_uiDCFxPageInfoSize;
		*/
	}
	
	return AHC_TRUE;
}
/**
@brief	the buffer is filled or the buffer is dirty when you want to swap the page.

*/

AHC_BOOL AIHC_DCF_WriteDCFxPage(void* pBufAddr)
{
	UINT32			uiFilePos;
	UINT32			uiWriteCount;
	DCFX_DB_PAGE	*psPageInfo;
	
	AIHC_DCF_OpenDCFxFile(AHC_TRUE);
	
	psPageInfo = (DCFX_DB_PAGE*)pBufAddr;
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("Write Page ID : %d \r\n", psPageInfo->uiPageID);
	#endif
	
	uiFilePos = m_sDCFxDBInfo.uiDataOffset + 4 + psPageInfo->uiPageID*m_uiDCFxBufSize;

	AHC_DCF_FileSeek(m_uiDCFxFileID, uiFilePos, AHC_FS_SEEK_SET);
	AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)pBufAddr, m_uiDCFxBufSize, &uiWriteCount);
	
	psPageInfo->uiModified = DCFX_PAGE_CLEAR;
	
	if((psPageInfo->uiPageID + 1) > m_sPageCtl.uiWritedPageCount){
	
		m_sPageCtl.uiWritedPageCount = psPageInfo->uiPageID + 1;
	}
	
	AIHC_DCF_OpenDCFxFile(AHC_FALSE);
	
	return AHC_TRUE;
}

/**
@brief	
*/
AHC_BOOL AIHC_DCF_UpdateDCFxPage(	DCF_DIR_NODE		*psDirNode, 
									INT8* 				pchFileFreeChar, 
									UINT16				uwFileKey,
									AHC_FS_ATTRIBUTE	sAttribute,
									AHC_FS_FILETIME		sFileTime,
									UINT32				uiFileSize)
{
	DCFX_DB_DATA* psNewDCFxData;
	DCFX_DB_PAGE* psPageInfo;
	/**
	@brief	make sure the page is clear.
	*/
	psPageInfo = (DCFX_DB_PAGE*)m_pbyDCFxTempBuffer;
	
	if(psPageInfo->uiUsedBufferOffset >= m_uiDCFxBufSize){
	
		if(psPageInfo->uiPageID != (m_sPageCtl.uiPageTotalCount - 1)){
			/**
			@brief	swap the last page.
			*/
			AIHC_DCF_SwapDCFxPage(m_sPageCtl.uiPageTotalCount - 1, m_pbyDCFxTempBuffer);
			
			if(psPageInfo->uiUsedBufferOffset >= m_uiDCFxBufSize){
				/**
				@brief	clear
				*/
				AIHC_DCF_ResetDCFxDB(0);
			}
		
		}else{
			/**
			@brief	It is the last page.
			*/
			AIHC_DCF_WriteDCFxPage(m_pbyDCFxTempBuffer);
			/**
			@brief	add the new page
			*/
			AIHC_DCF_ResetDCFxDB(0);
		}
	}

	/**
	@brief	Its the new page
	*/
	if(psPageInfo->uiUsedBufferOffset == m_uiDCFxPageInfoSize){
		m_sPageCtl.uiPageTotalCount++;
		psPageInfo->uiPageID = m_sPageCtl.uiPageTotalCount - 1;
	}
	
	psNewDCFxData = (DCFX_DB_DATA*)(m_pbyDCFxTempBuffer + psPageInfo->uiUsedBufferOffset);
	
	MEMCPY(psNewDCFxData->chDirFreeChar, psDirNode->chDirFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
	psNewDCFxData->uwDirKey		= psDirNode->uwDirKey;	///< 2 bytes
	
	MEMCPY(psNewDCFxData->chFileFreeChar, pchFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
	psNewDCFxData->uwFileKey	= uwFileKey;	///< 2 bytes
	
	psNewDCFxData->uwCurPos		= psPageInfo->uiUsedBufferOffset;	///< 1 bytes
	//psNewDCFxData->sAttribute	= sAttribute;	///< 4 bytes.
	psNewDCFxData->sFileTime	= sFileTime;	///< 12 bytes.
	psNewDCFxData->uiFileSize	= uiFileSize;	///< 4 bytes.
	
	AIHC_DCF_InsertData(m_pbyDCFxTempBuffer, psPageInfo, psNewDCFxData);
	/**
	@brief	keep the used buffer space.
	*/
	psPageInfo->uiUsedBufferOffset += m_uiDCFxDataSize;

	#if (DCF_DEBUG >= DCF_DEBUG_ALL)

	printc("--------------- \r\n");
	printc("byPrevPos      : %d \r\n", psNewDCFxData->byPrevPos);
	printc("byNextPos      : %d \r\n", psNewDCFxData->byNextPos);
	printc("byCurPos       : %d \r\n", psNewDCFxData->byCurPos);
	
	printc("chDirFreeChar  : %s \r\n", psNewDCFxData->chDirFreeChar);
	printc("uwDirKey       : %d \r\n", psNewDCFxData->uwDirKey);
	printc("chFileFreeChar : %s \r\n", psNewDCFxData->chFileFreeChar);
	printc("uwFileKey      : %d \r\n", psNewDCFxData->uwFileKey);
	printc("sFileTime      : %d \r\n", psNewDCFxData->sFileTime);
	printc("uiFileSize     : %d \r\n", psNewDCFxData->uiFileSize);

	#endif
	return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_MergeDCFxPage(	DCFX_DB_PAGE**	ppsPrimaryPage,
										DCFX_DB_PAGE**	ppsSubPage, 
										void** 			ppPrimaryAddr, 
										void** 			ppSubAddr)
{
	DCFX_DB_PAGE*	psPrimaryPage;
	DCFX_DB_PAGE*	psSubPage;
	DCFX_DB_DATA*	psPrimaryData;
	DCFX_DB_DATA*	psSubData;
	UINT8 			byResult;
	UINT16 			uwSubPosCtl = 0;
	void*			pPrimaryAddr;
	void*			pSubAddr;
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("DCF MERGE S \r\n");
	#endif
	
	pPrimaryAddr	= *ppPrimaryAddr;
	pSubAddr		= *ppSubAddr;
	
	*ppsPrimaryPage	= (DCFX_DB_PAGE*)pPrimaryAddr;
	*ppsSubPage 	= (DCFX_DB_PAGE*)pSubAddr;
	// the page info in two buffers.
	psPrimaryPage	= *ppsPrimaryPage;//(DCFX_DB_PAGE*)pPrimaryAddr;
	psSubPage 		= *ppsSubPage;

	if(psSubPage->uiFirstItem == 0){
		// no data in th e sub buffer.
		return AHC_TRUE;
	}

	// condition 1
	{
	psPrimaryData	= (DCFX_DB_DATA*)((UINT8*)pPrimaryAddr + psPrimaryPage->uiFirstItem);
	psSubData		= (DCFX_DB_DATA*)((UINT8*)pSubAddr + psSubPage->uiLastItem);
	byResult		= AIHC_DCF_WhichIsBoss16(&psPrimaryData->sFileTime, &psSubData->sFileTime, DCFX_TIME_LENGTH);
	
	if( (byResult == DCF_BOSS_1) || (byResult == DCF_BOSS_EQUAL) ){
		/*
		all the data in the primary buffer is youngerer than that in the sub buffer.
		switch the golden page
		*/
		UINT8* pbyTempBuf = 0;
		//UINT32 uiBufOffset = 0;
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		printc("DCF MERGE Condition1 \r\n");
		#endif

		pbyTempBuf		= pPrimaryAddr;
		pPrimaryAddr	= pSubAddr;
		pSubAddr		= pbyTempBuf;
		
		*ppPrimaryAddr	= pPrimaryAddr;
		*ppSubAddr		= pSubAddr;
		
		*ppsPrimaryPage	= (DCFX_DB_PAGE*)pPrimaryAddr;
		*ppsSubPage 	= (DCFX_DB_PAGE*)pSubAddr;
		return AHC_TRUE;
	}
	
	}
	
	// condition 2
	{
	psPrimaryData	= (DCFX_DB_DATA*)((UINT8*)pPrimaryAddr + psPrimaryPage->uiLastItem);
	psSubData		= (DCFX_DB_DATA*)((UINT8*)pSubAddr + psSubPage->uiFirstItem);
	byResult		= AIHC_DCF_WhichIsBoss16(&psPrimaryData->sFileTime, &psSubData->sFileTime, DCFX_TIME_LENGTH);
	
	if( (byResult == DCF_BOSS_2) || (byResult == DCF_BOSS_EQUAL) ){
		/*
		all the data in the primary buffer is older than that in the sub buffer.
		*/
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)	
		printc("DCF MERGE Condition2 \r\n");
		#endif
		return AHC_TRUE;
	}
	
	}

	// condition 3
	while(1)
	{

		psPrimaryData	= (DCFX_DB_DATA*)((UINT8*)pPrimaryAddr + psPrimaryPage->uiLastItem);
		
		byResult = AIHC_DCF_WhichIsBoss16(&psPrimaryData->sFileTime, &psSubData->sFileTime, DCFX_TIME_LENGTH);

		uwSubPosCtl = psSubData->uwNextPos;
		
		if(byResult == DCF_BOSS_1){
			// get one
			// swap data
			MEMCPY(&m_sDCFxSwapData[0], psPrimaryData, m_uiDCFxDataSize);
			MEMCPY(&m_sDCFxSwapData[1], psSubData, m_uiDCFxDataSize);
			
			// delete the younger data in the primary buffer
			AIHC_DCF_DeleteData(pPrimaryAddr, psPrimaryPage, psPrimaryData);
			
			MEMCPY((DCFX_DB_DATA*)((UINT8*)pPrimaryAddr + m_sDCFxSwapData[0].uwCurPos), &m_sDCFxSwapData[1], m_uiDCFxDataSize);
			
			psPrimaryData				= (DCFX_DB_DATA*)((UINT8*)pPrimaryAddr + m_sDCFxSwapData[0].uwCurPos);
			psPrimaryData->uwCurPos		= m_sDCFxSwapData[0].uwCurPos;
			psPrimaryData->uwPrevPos	= DCF_INVALID_NUMBER_16;
			psPrimaryData->uwNextPos	= DCF_INVALID_NUMBER_16;
			
			AIHC_DCF_InsertData(pPrimaryAddr, psPrimaryPage, psPrimaryData);

			// delete the older data in the sub buffer
			AIHC_DCF_DeleteData(pSubAddr, psSubPage, psSubData);
			
			MEMCPY((DCFX_DB_DATA*)((UINT8*)pSubAddr + m_sDCFxSwapData[1].uwCurPos), &m_sDCFxSwapData[0], m_uiDCFxDataSize);
			
			psSubData				= (DCFX_DB_DATA*)((UINT8*)pSubAddr + m_sDCFxSwapData[1].uwCurPos);
			psSubData->uwCurPos		= m_sDCFxSwapData[1].uwCurPos;
			psSubData->uwPrevPos	= DCF_INVALID_NUMBER_16;
			psSubData->uwNextPos	= DCF_INVALID_NUMBER_16;
			
			AIHC_DCF_InsertData(pSubAddr, psSubPage, psSubData);
		}else{
			//
			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
			printc("DCF MERGE condition3 out \r\n");
			#endif
			break;
		}
		
		if(uwSubPosCtl == DCF_INVALID_NUMBER_16){
			break;
		}

		// get the next data in sub buffer.
		psSubData		= (DCFX_DB_DATA*)((UINT8*)pSubAddr + uwSubPosCtl);
	}
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("DCF MERGE E \r\n");
	#endif
	
	return AHC_TRUE;
}

/**
@brief	

*/
AHC_BOOL AIHC_DCF_GetGlodenPageIndex(UINT32* uiIndex, AHC_BOOL bFilled)
{
	UINT32	uiPageIndex;
	UINT32  uiCount;
	AHC_BOOL bResult = AHC_FALSE;
	DCFX_DB_PAGE*	psPageInfo;
	
	uiPageIndex = (m_uiGPWorkIndex + 1 ) % DCF_GOLDEN_PAGE_NUMBER;
	uiCount		= 0;
	
	while(uiCount < DCF_GOLDEN_PAGE_NUMBER){
		
		psPageInfo = (DCFX_DB_PAGE*)m_GoldenPage[uiPageIndex].pbyBuffer;
		
		if(bFilled == AHC_TRUE){
			if(psPageInfo->uiFirstItem != 0){
				*uiIndex = uiPageIndex;

				bResult = AHC_TRUE;
				break;			
			}
		}else{
			if(psPageInfo->uiFirstItem == 0){
				*uiIndex = uiPageIndex;

				bResult = AHC_TRUE;
				break;			
			}
		
		}

		uiPageIndex = (uiPageIndex + 1) % DCF_GOLDEN_PAGE_NUMBER;
		uiCount++;
	}

	return bResult;
}

/**

WARNING: this API may change the address of golden page and temp buffer.

@param[in]: uiIndex => the index of golden page buffer.

*/


AHC_BOOL AIHC_DCF_SortGoldenPage(UINT32 uiIndex)
{	
	DCFX_DB_PAGE*	psGoldenPageInfo;
	DCFX_DB_PAGE*	psPageInfo;
	UINT32			i;

	if(m_sPageCtl.uiPageIndex == m_sPageCtl.uiSortTotalCount){
		/**
		@brief no page in the storage.
		
		*/
		return AHC_FALSE;
	}
	
	//printc("AIHC_DCF_SortGoldenPage1 : %d %d %d \r\n", uiIndex, m_uiGPWorkIndex, m_sPageCtl.uiSortTotalCount);
	
	if(m_sPageCtl.uiPageIndex == 0){
	
		m_uiGPWorkIndex = uiIndex;
	}
		
	//printc("AIHC_DCF_SortGoldenPage2 : %d %d \r\n", uiIndex, m_uiGPWorkIndex);
	
	psGoldenPageInfo	= (DCFX_DB_PAGE*)m_GoldenPage[uiIndex].pbyBuffer;
	/**
	@brief	page id starts from 0.
	
	*/
	psPageInfo			= (DCFX_DB_PAGE*)m_pbyDCFxTempBuffer;
	
	if(psGoldenPageInfo->uiFirstItem != 0){
		return AHC_TRUE;
	}
	
	
	if(psPageInfo->uiPageID != m_sPageCtl.uiPageIndex){
		AIHC_DCF_SwapDCFxPage(m_sPageCtl.uiPageIndex, m_pbyDCFxTempBuffer);
		AIHC_DCF_LoadDCFxPage(m_sPageCtl.uiPageIndex, m_GoldenPage[uiIndex].pbyBuffer);
	}else{
		/**
		@brief	switch the buffer address because we only have the first page or the last page in the temp buffer.
				
		*/
		UINT8* pbyTempAddr;

		pbyTempAddr						= m_GoldenPage[uiIndex].pbyBuffer;
		m_GoldenPage[uiIndex].pbyBuffer	= m_pbyDCFxTempBuffer;
		m_pbyDCFxTempBuffer				= pbyTempAddr;
	
		psGoldenPageInfo	= (DCFX_DB_PAGE*)m_GoldenPage[uiIndex].pbyBuffer;
		psPageInfo			= (DCFX_DB_PAGE*)m_pbyDCFxTempBuffer;
		/**
		@brief	After changing the buffer address
		
		*/
		AIHC_DCF_ResetDCFxDB(0);
		//m_sPageCtl.uiPageIndex++;
	}
	
	/**
	@brief	merge the page to be the golden page.
			merging page start from m_sPageCtl.uiPageIndex to the last index.
			We have the last page in the DCFx temp buffer after the process of merge.
	*/
	for(i = m_sPageCtl.uiPageIndex + 1; i < m_sPageCtl.uiSortTotalCount; i++){
		
		AIHC_DCF_LoadDCFxPage(i, m_pbyDCFxTempBuffer);
		
		if(psPageInfo->uiFirstItem != 0){
			AIHC_DCF_MergeDCFxPage(&psGoldenPageInfo, &psPageInfo, (void*)&m_GoldenPage[uiIndex].pbyBuffer, (void*)&m_pbyDCFxTempBuffer);
			/**
			@brief move the position of the buffer in the storage forward.
			*/
			if(psPageInfo->uiModified == DCFX_PAGE_DIRTY)
				AIHC_DCF_WriteDCFxPage(m_pbyDCFxTempBuffer);
		}
	}
	
	/**
	@brief	add 1 to m_sPageCtl.uiPageIndex to be the next index.
	*/
	m_sPageCtl.uiPageIndex++;
	
	return AHC_TRUE;
}

/**
@brief	check this buffer still has files which can be deleted or not.

*/
static AHC_BOOL AIHC_DCF_CheckGoldenPageStatus(void)
{
	DCFX_DB_PAGE*	psPageInfo;
	AHC_BOOL		bResult;
	
	//AIHC_DCF_LOCKPAGE();
	
	psPageInfo		= (DCFX_DB_PAGE*)m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;
	
	if(psPageInfo->uiFirstItem != 0){
		//printc("AIHC_DCF_CheckGoldenPageStatus : %d \r\n", m_uiGPWorkIndex);
		bResult = AHC_TRUE;

	}else{
	
		bResult = AHC_FALSE;
	}
	
	//AIHC_DCF_UNLOCKPAGE();
	
	return bResult;
}


/**
@brief	
WARNING: you must check the status of golden page. 

*/
static AHC_BOOL AIHC_DCF_DeleteDCFxFile(void* pBufAddr, UINT32* uiSize)
{
	DCFX_DB_PAGE*	psPageInfo;
	DCFX_DB_DATA*	psDCFxData;	
	DCF_DIR_NODE*	psDir;
	DCF_FILE_NODE*	psFile;	
	INT8			chRootName[DCF_MAX_FILE_NAME_SIZE];
	
	*uiSize		= 0;

	//psPageInfo	= (DCFX_DB_PAGE*)m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;		
	//psDCFxData	= (DCFX_DB_DATA*)(m_GoldenPage[m_uiGPWorkIndex].pbyBuffer + psPageInfo->uiFirstItem);
	//printc("AIHC_DCF_DeleteDCFxFile : %x \r\n", pBufAddr);
	psPageInfo	= (DCFX_DB_PAGE*)pBufAddr;
	psDCFxData	= (DCFX_DB_DATA*)((UINT8*)pBufAddr + psPageInfo->uiFirstItem);
	/**
	@brief	fond the oldest file each pages
	*/
	if((psDCFxData->uwCurPos == DCF_INVALID_NUMBER_16) || (psPageInfo->uiFirstItem == 0)){
		return AHC_FALSE;
	}

	AIHC_DCF_FindDir(NULL, psDCFxData->uwDirKey, &psDir);

	if(psDir != m_DcfDB[m_uiDBIndex].psPowerDirNode){

		AIHC_DCF_MountDirNode(psDir, 
							  NULL, 
							  0xFFFF,
						      psDCFxData->uwFileKey,
						      DCF_DIR_MOUNT_TYPE_KEY);
	
	}else{

		if( (psDCFxData->uwFileKey < psDir->psRootFileNode->uwFileKey) ||
			(psDCFxData->uwFileKey > psDir->psLastFileNode->uwFileKey) ){
			AIHC_DCF_MountDirNode(psDir, 
								  NULL, 
								  0xFFFF,
							      psDCFxData->uwFileKey,
							      DCF_DIR_MOUNT_TYPE_KEY);
			
		}else{
			/**
			@brief	the kill key is in the file node of the dir node
			*/
		}

	
	}

	if(AIHC_DCF_FindFileNode(psDir, NULL, psDCFxData->uwFileKey, &psFile) == AHC_TRUE){

		INT8				chSrcFileName[DCF_MAX_FILE_NAME_SIZE];
		INT8				chTempFileName[DCF_MAX_FILE_NAME_SIZE];
		AHC_FS_ATTRIBUTE	sFileAttribute;
		AHC_FS_FILETIME		sFileTime;
		UINT32				uiFileSize = 0;
		UINT32				uiNameLength;

	    MEMSET(chRootName, DCF_RESET_VALUE, sizeof(chRootName));
	    MEMSET(chSrcFileName, DCF_RESET_VALUE, sizeof(chSrcFileName));
	    /*
	    SD:\\DCIM\\
	    */
	    STRCPY(chSrcFileName, m_DcfDB[m_uiDBIndex].chRootName);
	    STRCAT(chSrcFileName, "\\");
	    
	    /*
	    SD:\\DCIM\\100MEDIA\\
	    */
	    MEMSET(chTempFileName, DCF_RESET_VALUE, sizeof(chTempFileName));
		AIHC_DCF_GetDirFullName(chTempFileName, psDir->uwDirKey, psDir->chDirFreeChar);
	    STRCAT(chSrcFileName, chTempFileName);	    
	    STRCPY(chRootName, chSrcFileName);
	    STRCAT(chSrcFileName, "\\");
	    
	    /*
	    FILE0001.AVI
	    */
	    MEMSET(chTempFileName, DCF_RESET_VALUE, sizeof(chTempFileName));
	    AIHC_DCF_GetFileFullName(chTempFileName, psFile->uwFileKey, psFile->chFileFreeChar);
	    
        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        {
            UINT32 i;
            
            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
        		STRCPY(m_chAuxiliaryFileName[i], chSrcFileName);
        		STRCAT(m_chAuxiliaryFileName[i], "\\");
        		STRCAT(m_chAuxiliaryFileName[i], chTempFileName);
        		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
        	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
            }
        }
        #endif
        
	    
	    STRCAT(chTempFileName, EXT_DOT);
	    STRCAT(chTempFileName, m_DcfSupportFileType[psFile->byFileType]);
	    
	    /*
	    SD:\\DCIM\\100MEDIA\\FILE0001.AVI
	    */
	    STRCAT(chSrcFileName, chTempFileName);
			
		
		uiNameLength = STRLEN(chSrcFileName);
		
		AHC_DCF_FileDirGetInfo(	chSrcFileName, 
								uiNameLength, 
								&sFileAttribute, 
								&sFileTime, 
								&uiFileSize);
								

		if(	(AIHC_DCF_WhichIsBoss(psDCFxData->chDirFreeChar, psDir->chDirFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum) == DCF_BOSS_EQUAL) &&
			(AIHC_DCF_WhichIsBoss(psDCFxData->chFileFreeChar, psFile->chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL) ){
            AIHC_DCF_DeleteFile(psDir->uwDirKey, psFile->uwFileKey, NULL);
		}

        if(AHC_DCF_FileRemove(chSrcFileName, uiNameLength) == AHC_ERR_NONE){
        
            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        	{
            UINT32 i;
            
            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
            }
            
            }
        	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
        
			AIHC_DCF_CalculateCluster(	psDCFxData->chFileFreeChar, 
										&sFileAttribute, 
										uiFileSize, 
										psDir->uwDirKey, 
										AHC_FALSE);
			*uiSize = uiFileSize;
			
			/**
			@brief	confirm the dir is empty or not.
			*/
			AIHC_DCF_ClearEmptyDir((INT8*)chRootName, psDir);
		}else{

			*uiSize = 0;
		}
		
		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
		printc("X F Name : %s , Size : %d \r\n", chSrcFileName, uiFileSize);
		#endif
		
	}

	AIHC_DCF_WipeDCFxData(pBufAddr, psDCFxData);
	
	return AHC_TRUE;

}

#endif ///< (DCF_DCFX == 1)


#if 0
void __INTERNAL_API__(){}
#endif


void AIHC_DCF_DumpDCFxPage(UINT32 uiPageID)
{
	#if (DCF_DEBUG >= DCF_DEBUG_ALL) && DCF_DCFX
	
	DCFX_DB_DATA*	psDCFxData;
	DCFX_DB_PAGE*	psPageInfo;
	
	psPageInfo = (DCFX_DB_PAGE*)m_pbyDCFxTempBuffer;
	
	if(psPageInfo->uiPageID != uiPageID){
		AIHC_DCF_SwapDCFxPage(uiPageID, m_pbyDCFxTempBuffer);
	
	}
	
	psDCFxData = (DCFX_DB_DATA*)(m_pbyDCFxTempBuffer + psPageInfo->uiFirstItem);

	#if 1

	printc("PageID         : %d \r\n", psPageInfo->uiPageID);
	printc("FirstItem      : %d \r\n", psPageInfo->uiFirstItem);
	printc("LastItem       : %d \r\n", psPageInfo->uiLastItem);
	printc("UsedBufferOffset : %d \r\n", psPageInfo->uiUsedBufferOffset);
	printc("Modified       : %d \r\n", psPageInfo->uiModified);
	
	printc("byPrevPos      : %d \r\n", psDCFxData->uwPrevPos);
	printc("byNextPos      : %d \r\n", psDCFxData->uwNextPos);
	printc("byCurPos       : %d \r\n", psDCFxData->uwCurPos);
	
	printc("chDirFreeChar  : %s \r\n", psDCFxData->chDirFreeChar);
	printc("uwDirKey       : %d \r\n", psDCFxData->uwDirKey);
	printc("chFileFreeChar : %s \r\n", psDCFxData->chFileFreeChar);
	printc("uwFileKey      : %d \r\n", psDCFxData->uwFileKey);
	printc("Time Y         : %d \r\n", psDCFxData->sFileTime.usYear);
	printc("Time M         : %d \r\n", psDCFxData->sFileTime.usMonth);
	printc("Time D         : %d \r\n", psDCFxData->sFileTime.usDay);
	printc("Time H         : %d \r\n", psDCFxData->sFileTime.usHour);
	printc("Time M'        : %d \r\n", psDCFxData->sFileTime.usMinute);
	printc("Time S         : %d \r\n", psDCFxData->sFileTime.usSecond);
	printc("uiFileSize     : %d \r\n", psDCFxData->uiFileSize);
	#endif
	
	while(psDCFxData->uwNextPos != DCF_INVALID_NUMBER_16){
		psDCFxData = (DCFX_DB_DATA*)(m_pbyDCFxTempBuffer + psDCFxData->uwNextPos);
		#if 1
		printc("--------------- \r\n");
		printc("byPrevPos      : %d \r\n", psDCFxData->uwPrevPos);
		printc("byNextPos      : %d \r\n", psDCFxData->uwNextPos);
		printc("byCurPos       : %d \r\n", psDCFxData->uwCurPos);
		
		printc("chDirFreeChar  : %s \r\n", psDCFxData->chDirFreeChar);
		printc("uwDirKey       : %d \r\n", psDCFxData->uwDirKey);
		printc("chFileFreeChar : %s \r\n", psDCFxData->chFileFreeChar);
		printc("uwFileKey      : %d \r\n", psDCFxData->uwFileKey);
		printc("Time Y         : %d \r\n", psDCFxData->sFileTime.usYear);
		printc("Time M         : %d \r\n", psDCFxData->sFileTime.usMonth);
		printc("Time D         : %d \r\n", psDCFxData->sFileTime.usDay);
		printc("Time H         : %d \r\n", psDCFxData->sFileTime.usHour);
		printc("Time M'        : %d \r\n", psDCFxData->sFileTime.usMinute);
		printc("Time S         : %d \r\n", psDCFxData->sFileTime.usSecond);
		printc("uiFileSize     : %d \r\n", psDCFxData->uiFileSize);
		#endif

	}

	#endif

}


void AIHC_DCF_DumpDCFxPage2(UINT32 uiIndex)
{
	#if (DCF_DEBUG >= DCF_DEBUG_ALL) && DCF_DCFX
	
	DCFX_DB_DATA*	psDCFxData;
	DCFX_DB_PAGE*	psPageInfo;

	psPageInfo = (DCFX_DB_PAGE*)m_GoldenPage[uiIndex].pbyBuffer;

	
	psDCFxData = (DCFX_DB_DATA*)(m_GoldenPage[uiIndex].pbyBuffer + psPageInfo->uiFirstItem);

	#if 1
	printc("byPrevPos      : %d \r\n", psDCFxData->uwPrevPos);
	printc("byNextPos      : %d \r\n", psDCFxData->uwNextPos);
	printc("byCurPos       : %d \r\n", psDCFxData->uwCurPos);
	
	printc("chDirFreeChar  : %s \r\n", psDCFxData->chDirFreeChar);
	printc("uwDirKey       : %d \r\n", psDCFxData->uwDirKey);
	printc("chFileFreeChar : %s \r\n", psDCFxData->chFileFreeChar);
	printc("uwFileKey      : %d \r\n", psDCFxData->uwFileKey);
	printc("Time Y         : %d \r\n", psDCFxData->sFileTime.usYear);
	printc("Time M         : %d \r\n", psDCFxData->sFileTime.usMonth);
	printc("Time D         : %d \r\n", psDCFxData->sFileTime.usDay);
	printc("Time H         : %d \r\n", psDCFxData->sFileTime.usHour);
	printc("Time M'        : %d \r\n", psDCFxData->sFileTime.usMinute);
	printc("Time S         : %d \r\n", psDCFxData->sFileTime.usSecond);
	printc("uiFileSize     : %d \r\n", psDCFxData->uiFileSize);
	#endif
	
	while( (psDCFxData->uwNextPos != DCF_INVALID_NUMBER_16) && (psDCFxData->uwNextPos != 0) ){
		psDCFxData = (DCFX_DB_DATA*)(m_GoldenPage[uiIndex].pbyBuffer + psDCFxData->uwNextPos);
		#if 1
		printc("--------------- \r\n");
		printc("byPrevPos      : %d \r\n", psDCFxData->uwPrevPos);
		printc("byNextPos      : %d \r\n", psDCFxData->uwNextPos);
		printc("byCurPos       : %d \r\n", psDCFxData->uwCurPos);
		
		printc("chDirFreeChar  : %s \r\n", psDCFxData->chDirFreeChar);
		printc("uwDirKey       : %d \r\n", psDCFxData->uwDirKey);
		printc("chFileFreeChar : %s \r\n", psDCFxData->chFileFreeChar);
		printc("uwFileKey      : %d \r\n", psDCFxData->uwFileKey);
		printc("Time Y         : %d \r\n", psDCFxData->sFileTime.usYear);
		printc("Time M         : %d \r\n", psDCFxData->sFileTime.usMonth);
		printc("Time D         : %d \r\n", psDCFxData->sFileTime.usDay);
		printc("Time H         : %d \r\n", psDCFxData->sFileTime.usHour);
		printc("Time M'        : %d \r\n", psDCFxData->sFileTime.usMinute);
		printc("Time S         : %d \r\n", psDCFxData->sFileTime.usSecond);
		printc("uiFileSize     : %d \r\n", psDCFxData->uiFileSize);
		#endif

	}

	#endif

}
/**
 @brief This API dumps the DCF database

 This API dumps the DCF database 
 
*/
void AIHC_DCF_DumpDB(void)
{
	#if (DCF_DEBUG >= DCF_DEBUG_ERR)
	
    DCF_DIR_NODE    *DirNode = m_DcfDB[m_uiDBIndex].psRootDirNode;
    DCF_FILE_NODE   *FileNode,*TempFileNode;
    INT32           i,j;

    printc("\r\n ==== Start Dump DB ==== \r\n");
    printc("Max File Node Count      : %d \r\n", m_sFileMem.uiMaxCount);
    printc("CurDirCount              : %d \r\n", m_DcfDB[m_uiDBIndex].uiCurDirCountInDB);
    printc("MaxDirKey                : %d \r\n", m_DcfDB[m_uiDBIndex].psLastDirNode->uwDirKey);
    printc("KillDirKey               : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey);
    printc("KillFileKey              : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillFileKey);
    printc("ReadOnlyRegionCluster    : %d \r\n", m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster);
    printc("DCFxRegionCluster        : %d \r\n", m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster);
    printc("NonLockRegionCluster     : %d \r\n", m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster);

    
    if ( m_DcfDB[m_uiDBIndex].psPowerDirNode ) {
	printc("psPowerDirNode           : %d \r\n", m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey);
    }
    else {
	printc("psPowerDirNode           : N/A \r\n");
    }
    
    //printc("AllowedFiles             : %d \r\n", m_DcfDB.uiTotalAllowedFileCount);
    //printc("TotalFiles               : %d \r\n", m_DcfDB.uiTotalFileCount);

    
    for( i = 0; i < (MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1) ;i++) {
    
        if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i] != DCF_INVALID_NUMBER_16 ) {
	printc("DIR NUMBER : %d \r\n", i + MIN_DCF_DIR_KEYNUM);
	printc("TotalFileCount      	 : %d \r\n", m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i]);
	printc("TotalNonLockFileCount    : %d \r\n", m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwNonLockFileCount);
	printc("TotalDCFxFileCount       : %d \r\n", m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwDCFxFileCount);
    
            for(j=0; j < MAX_DCF_SUPPORT_FILE_TYPE;j++) {
                if(m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j]) {

	printc("FILE TYPE                : %d \r\n", j);
	printc("FileCountInDir&Type      : %d \r\n", m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j]);

                }
            }
        }
    }

    while(DirNode) {
        if ( DirNode->uwDirKey != DCF_INVALID_NUMBER_16 ) {
        	printc("------------------------DIR------------------------\r\n");
        	printc("DirKey      : %d \r\n", DirNode->uwDirKey);
            printc("DirFreeChar : %s \r\n", DirNode->chDirFreeChar);
        	printc("MaxFileKey  : %d \r\n", DirNode->uwMaxFileKey);
        	printc("NextFileKey : %d \r\n", DirNode->uwNextFileKey);
        	printc("LastFileKey : %d \r\n", DirNode->psLastFileNode->uwFileKey);
            
            FileNode = DirNode->psRootFileNode;

            while (FileNode) {
            
                if ( FileNode->uwFileKey != DCF_INVALID_NUMBER_16 ) {
	                printc("------------------------FILE------------------------\r\n");
					printc("FileKey      : %d \r\n", FileNode->uwFileKey);
		            printc("FileFreeChar : %s \r\n", FileNode->chFileFreeChar);
		        	printc("FileType     : %d \r\n", FileNode->byFileType);
                    
                    TempFileNode = FileNode->psNeighbor;
                    
                    while (TempFileNode) {
                    	printc("------------------------NEIGHBOR------------------------\r\n");
						printc("FileKey      : %d \r\n", TempFileNode->uwFileKey);
			            printc("FileFreeChar : %s \r\n", TempFileNode->chFileFreeChar);
			        	printc("FileType     : %d \r\n", TempFileNode->byFileType);
                    
                        TempFileNode = TempFileNode->psNeighbor;
                    }
                }
            
                FileNode = FileNode->psNext;
            }
        }
        
        DirNode = DirNode->psNext;
    }
    
    printc("\r\n ==== End Dump DB ==== \r\n");
    
    #endif
}

AHC_BOOL AIHC_DCF_DetectFreeStorage(UINT64* uiiSize)
{
	INT8	chVolume[6];
	UINT32	uiVolNameSize;

	MEMSET(chVolume, 0, sizeof(chVolume));
	
	if(AHC_GetVolumeName(chVolume, &uiVolNameSize) == AHC_FALSE)
		return AHC_FALSE;
		
	return AHC_DCF_GetFreeSpace(chVolume, uiVolNameSize, uiiSize);

}

/**
 @brief This API gets the valid path/file name for the next DCF object

 This API gets the valid path/file name for the next DCF object
 
 Parameters:
 
 @param[out]  pDirKey          The path key
 @param[out]  DirName          The path name
 @param[out]  FileName         The file name
 @param[out]  bCreateNewDir    Need to create new dir or not
 
 @retval AHC_BOOL
*/
AHC_BOOL AIHC_DCF_GetName(UINT16 *pDirKey, INT8 *DirName, INT8 *FileName, UINT8 *bCreateNewDir)
{
    UINT16 uwDirKey;
    UINT16 uwFileKey;
    AHC_BOOL bError = AHC_TRUE;
    
    AIHC_DCF_LOCKDB();
    
    if(m_DcfDB[m_uiDBIndex].psFileCtlDirNode == NULL){

		uwDirKey		= MIN_DCF_DIR_KEYNUM;
		uwFileKey		= MIN_DCF_FILE_KEYNUM;
		*bCreateNewDir	= AHC_TRUE;
		    
	}else if( m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwNextFileKey == 0 ){
		
		if(m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwMaxFileKey >= m_ulMaxDcfFileInDir){
			/**
			@brief get the next dir.
			*/
			AIHC_DCF_ChangeFileCtlDirNode(&uwDirKey, &uwFileKey, bCreateNewDir);
			
		}else{
			uwDirKey  = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwDirKey;
			uwFileKey = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwMaxFileKey + 1;
			*bCreateNewDir = AHC_FALSE;
		}
	
	
	}else{
		/**
		@brief cyclic
		*/
    	DCF_DIR_NODE *pDir;
    	
    	uwDirKey = m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwDirKey;

    	if(m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey != uwDirKey){
    	
    		AIHC_DCF_FindDir(NULL, uwDirKey, &pDir);
    		AIHC_DCF_MountDirNode(pDir, 
								  NULL, 
								  0xFFFF,
							      0,
							      DCF_DIR_MOUNT_TYPE_UNMOUNT);
    	}
    	
		m_DcfDB[m_uiDBIndex].psFileCtlDirNode = m_DcfDB[m_uiDBIndex].psPowerDirNode;
    	
		AIHC_DCF_FindHoleInFileMap(m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwNextFileKey, m_ulMaxDcfFileInDir, &uwFileKey);
    		
		if(uwFileKey == 0){
		
			m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwNextFileKey = 0;
			AIHC_DCF_ChangeFileCtlDirNode(&uwDirKey, &uwFileKey, bCreateNewDir);

		}else{
			m_DcfDB[m_uiDBIndex].psFileCtlDirNode->uwNextFileKey = uwFileKey + 1;
			*bCreateNewDir = AHC_FALSE;
		}
	
	}

	m_DcfDB[m_uiDBIndex].uwFileCtlDirKey  = uwDirKey;
	m_DcfDB[m_uiDBIndex].uwFileCtlFilekey = uwFileKey;
	
	*pDirKey = uwDirKey;
	
	if(*bCreateNewDir == AHC_FALSE){
		AIHC_DCF_GetDirFullName(DirName , uwDirKey , m_DcfDB[m_uiDBIndex].psFileCtlDirNode->chDirFreeChar );
	}else{
		AIHC_DCF_GetDirFullName(DirName , uwDirKey , (INT8 *)m_DcfDB[m_uiDBIndex].chDirFreeChar );
	}

    AIHC_DCF_GetFileFullName(FileName, uwFileKey, (INT8 *)m_DcfDB[m_uiDBIndex].chFileFreeChar);

    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("[DCF INFO] AIHC_DCF_GetName \r\n");
	printc("[DCF INFO] uwDirKey: %d, uwFileKey : %d \r\n", uwDirKey, uwFileKey);
	printc("[DCF INFO] DirName: %s, FileName : %s \r\n", DirName, FileName);
	#endif

    if (m_DcfDB[m_uiDBIndex].uiCurDirCountInDB > m_ulMaxDcfDirNum) {
        bError = AHC_FALSE;
    }
	
	if(m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster == 0){
		m_DcfDB[m_uiDBIndex].uwKillDirKey = uwDirKey;
	    m_DcfDB[m_uiDBIndex].uwKillFileKey = uwFileKey;
	}
    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
    printc("[DCF INFO] Get KillDir: %d, KillFileName : %d \r\n", m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
    #endif
	AIHC_DCF_UNLOCKDB();
	
    return bError;
}

AHC_BOOL AIHC_DCF_RemoveDir(UINT16 DirKey, INT8 *DirName)
{	
	DCF_DIR_NODE *psDirNode;
	AHC_BOOL bError;
	
	AIHC_DCF_LOCKDB();
	if(DirKey == m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey){
		
		psDirNode = m_DcfDB[m_uiDBIndex].psPowerDirNode;
	
	}else{
		AIHC_DCF_FindDir(NULL, DirKey, &psDirNode);
	}
	
	bError = AIHC_DCF_DeleteDir(psDirNode);
	
	AIHC_DCF_UNLOCKDB();
	
	return bError;
}


AHC_BOOL AIHC_DCF_RemoveFile(UINT16 DirKey, UINT16 FileKey,INT8 *FileName)
{
	AHC_BOOL bError;
	
	AIHC_DCF_LOCKDB();
	bError = AIHC_DCF_DeleteFile(DirKey, FileKey, FileName);
	AIHC_DCF_UNLOCKDB();
	
	return bError;
}
/**
 @brief This API adds one dir node to the database

 This API adds one dir node to the database
 
 Parameters:
 
 @param[in]  DirName          The dir name

 @retval AHC_BOOL
*/
AHC_BOOL AIHC_DCF_AddDir(INT8 *pchDirName)
{
	AHC_BOOL bError;
	
	AIHC_DCF_LOCKDB();
	
	bError = AIHC_DCF_AddDirNode(pchDirName);
	
	AIHC_DCF_UNLOCKDB();
	
	return bError;
}

/**
 @brief	This API adds one file node to the database

WARNING:	This API only is used to add file node after you use the file key from the API(AIHC_DCF_GetName()).
			Any other case is not considered!!!!
 
 Parameters:
 
 @param[in]  DirIndex         The dir key
 @param[in]  FileName         The file name
  
 @retval AHC_BOOL
*/
AHC_BOOL AIHC_DCF_PreAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
	AHC_BOOL bError;
	
	AIHC_DCF_LOCKDB();
	bError = AIHC_DCF_AddFile(uwDirKey, pchFileName);
	AIHC_DCF_UNLOCKDB();
	
	return bError;

}

AHC_BOOL AIHC_DCF_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
    /**
    @brief	maintian the counter of DB non-lock cluster.
    
    */
    INT8                chPathName[DCF_MAX_FILE_NAME_SIZE];
    INT8                chDirName[MAX_DIR_CHAR_LENGTH + 1];
    UINT32              uiPathLen;
    
    AHC_FS_ATTRIBUTE	sFileAttribute;
    AHC_FS_FILETIME		sFileTime;
    UINT32				uiFileSize;
	UINT64				uiiClusterPerFile;
    DCF_DIR_NODE    	*psMajorDirNode;
	
	AIHC_DCF_LOCKDB();
	
    if ( AIHC_DCF_FindDir(NULL, uwDirKey, &psMajorDirNode) == AHC_FALSE ){
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }

    MEMSET(chPathName , 0, sizeof(chPathName));
    MEMSET(chDirName  , 0, sizeof(chDirName));
    
    AIHC_DCF_GetDirFullName(chDirName, uwDirKey, psMajorDirNode->chDirFreeChar);
    
    STRCPY(chPathName,(INT8*)m_DcfDB[m_uiDBIndex].chRootName);
    STRCAT(chPathName,(INT8*)"\\");
    STRCAT(chPathName,(INT8*)chDirName);
    STRCAT(chPathName,(INT8*)"\\");
    STRCAT(chPathName,(INT8*)pchFileName);
	
    uiPathLen = STRLEN(chPathName);
    AHC_DCF_FileDirGetInfo(chPathName, uiPathLen, &sFileAttribute, &sFileTime, &uiFileSize);    
    
	uiiClusterPerFile = (uiFileSize + m_uiBytesPerCluster - 1)/m_uiBytesPerCluster;
	m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster += uiiClusterPerFile;
	
	m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM]->uwNonLockFileCount++;
	
	AIHC_DCF_UNLOCKDB();
	
	return AHC_TRUE;
    
}


/**
 @brief This API sets parameters for DCF

 This API sets parameters for DCF
 
 @param[in] wParamID     Parameter ID
 @param[in] Param        Parameter
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_DCF_SetParam(AHC_PARAM_ID wParamID,UINT32 Param)
{
	AIHC_DCF_LOCKDB();
	
    switch( wParamID ){
    
    case PARAM_ID_MAX_FILES_IN_DIR:
        {
            if ( Param > MAX_DCF_FILE_KEYNUM )
                return AHC_FALSE;
        
            m_ulMaxDcfFileInDir = Param;    
        }
        break;

    case PARAM_ID_MAX_DIR_IN_ROOT:
        {
            UINT32  MaxDirCount;
    
            MaxDirCount = MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1;
            
            if ( Param > MaxDirCount )
                return AHC_FALSE;
            
            m_ulMaxDcfDirNum = Param;
        
        }
        break;
        
    case PARAM_ID_DCF_DEL_EMPTY:
    	/**
    	@brief Delete all the empty dir. In other word, there is no file in the empty dir.
    	
    	*/
        if ( Param )
        {
        	DCF_DIR_NODE *psDirNode;
            UINT32  i;
            INT8   string[MAX_DIR_CHAR_LENGTH];
            INT8   DirName[DCF_MAX_FILE_NAME_SIZE];           
            
            if ( m_DcfDB[m_uiDBIndex].ppsFileCountInDir == NULL )
                return AHC_FALSE;

            for(i = MIN_DCF_DIR_KEYNUM ; i <= MAX_DCF_DIR_KEYNUM ; i++) {
            
                if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i - MIN_DCF_DIR_KEYNUM] == 0 ) {
                	
                	AIHC_DCF_FindDir(NULL, i, &psDirNode);
                	AIHC_DCF_GetDirFullName(string, psDirNode->uwDirKey, psDirNode->chDirFreeChar);

                    MEMSET(DirName, 0, sizeof(DirName));
                    STRCPY(DirName,  m_DcfDB[m_uiDBIndex].chRootName);
                    STRCAT(DirName,  "\\");
                    STRCAT(DirName,  string);
                
                    AHC_DCF_DirRemove(DirName, STRLEN(DirName));
                    AIHC_DCF_DeleteDir(psDirNode);
                }
            }
        }
        break;
        
    case PARAM_ID_DCF_COUNT_HIDDEN:
        {
            if ( Param )
                m_bCountHiddenObj = AHC_TRUE;
            else
                m_bCountHiddenObj = AHC_FALSE;
        }
        break;
        
    case PARAM_ID_FILTER_DCF_FILES_BY_DATE:
        {
            INT8*  string       = (INT8*)Param;
            INT32  i,j,mul,loop;
            
            m_bFilterByDate     = MMP_TRUE;
            
            m_ulFilterDate[0] = 0;
            
            for(i = 3; i>=0;i--) {
                mul  = 1;
                loop = 3 - i;
                
                for(j=0;j<loop;j++) {
                    mul = mul * 10;
                }
                
                m_ulFilterDate[0] += (string[i] - '0') * mul;
            }
            
            m_ulFilterDate[1] = 0;
            
            for(i = 6; i>=5;i--) {
                mul  = 1;
                loop = 6 - i;
                
                for(j=0;j<loop;j++) {
                    mul = mul * 10;
                }
                
                m_ulFilterDate[1] += (string[i] - '0') * mul;
            }
            
            m_ulFilterDate[2] = 0;
            for(i = 9; i>=8;i--) {
                mul  = 1;
                loop = 9 - i;
                
                for(j=0;j<loop;j++) {
                    mul = mul * 10;
                }
                
                m_ulFilterDate[2] += (string[i] - '0') * mul;
            }
        }
        break;
        
    default:
        break;
    }
    
    AIHC_DCF_UNLOCKDB();
    
    return AHC_TRUE;
}

/**
 @brief This API gets parameters for DCF

 This API gets parameters for DCF
 
 @param[in] wParamID     Parameter ID
 @param[out] Param       Parameter
 @retval AHC_TRUE Success.
*/
AHC_BOOL AIHC_DCF_GetParam(AHC_PARAM_ID wParamID,UINT32 *Param)
{
	AIHC_DCF_LOCKDB();
	
    switch( wParamID ){
    
    case PARAM_ID_NO_MORE_DCF_OBJS:
        {
            UINT32 MaxDcfFileCount = m_ulMaxDcfDirNum * m_ulMaxDcfFileInDir;

            //if ( m_DcfDB.uiTotalFileCount >= MaxDcfFileCount )
            if ( AIHC_DCF_GetTotalFileCount() >= MaxDcfFileCount )
                *Param = AHC_TRUE;
            else
                *Param = AHC_FALSE;
        }
        break;

    case PARAM_ID_CURRENT_DCF_OBJECT_COUNT:
        {
            *Param = m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey - MIN_DCF_DIR_KEYNUM];
        }
        break;
    default:
        break;
    }
	
	AIHC_DCF_UNLOCKDB();
	
    return AHC_TRUE;
}

void AIHC_DCF_SetMountCallBack(PFuncDCFMountCallBack* pCallBack)
{
	DCFMountCallBack = pCallBack;
}

static AHC_BOOL AIHC_DCF_DBInit(UINT32 uiDBIndex, 
                         INT8* pchRootDirName,
                         INT8* pchDirFreeChar,
                         INT8* pchFileFreeChar)
{

    UINT32  i;
    UINT32  uiMaxDirCount;
    
        
    uiMaxDirCount = MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1;

    MEMSET(&m_DcfDB[uiDBIndex], DCF_RESET_VALUE, sizeof(DCF_DATABASE));
    //set FreeCharLength of Dir and File
    AHC_DCF_DBInitFreeCharLength(uiDBIndex,pchDirFreeChar,pchFileFreeChar);
    
    for(i = 0 ; i < uiMaxDirCount ; i++) {
        m_DcfDB[uiDBIndex].uwTotalFileCountInDir[i] = DCF_INVALID_NUMBER_16;
    }
    
    for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byDirFreeCharNum ; i++) {
        m_DcfDB[uiDBIndex].chDirFreeChar[i]  = pchDirFreeChar[i];
    }
    
    for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++) {
        m_DcfDB[uiDBIndex].chFileFreeChar[i] = pchFileFreeChar[i];
    }


    /**	@brief	setup the name of root. default : SD:\\DCIM .*/
    MEMSET(m_DcfDB[uiDBIndex].chRootName, DCF_RESET_VALUE, DCF_ROOT_NAME_LEN);
    STRCPY(m_DcfDB[uiDBIndex].chRootName, (INT8*)AIHC_GetMediaRootName());
    STRCAT(m_DcfDB[uiDBIndex].chRootName, pchRootDirName);

    return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_MountDB(UINT32 uiDBIndex)
{
    UINT32              error;
    UINT32              uiDirLength;
    UINT32              uiDirID;
    INT8                chFullDirName[DCF_MAX_FILE_NAME_SIZE];
    
	m_sParsedKillKey[0].uwDirKey = 0;
	m_sParsedKillKey[0].uwFileKey = 0;
	m_sParsedKillKey[1].uwDirKey = 0;
	m_sParsedKillKey[1].uwFileKey = 0;
	
    //indicate the failure of DB initialization
    uiDirLength	= STRLEN(m_DcfDB[uiDBIndex].chRootName);
    
    MEMSET(chFullDirName, DCF_RESET_VALUE, sizeof(chFullDirName));
    MEMCPY(chFullDirName, m_DcfDB[uiDBIndex].chRootName, uiDirLength);
    
    error		= AHC_DCF_DirOpen(chFullDirName, uiDirLength, &uiDirID);

	m_DcfDB[uiDBIndex].uwKillDirKey	= 0;
	m_DcfDB[uiDBIndex].uwKillFileKey = 0;
    
    if( error ){
    
        AHC_DCF_DirCreate(chFullDirName, uiDirLength);	///< Create a new directory.
        #if (DCF_DCFX == 1)
        AIHC_DCF_ConfirmDCFxDB((INT8*)AIHC_GetMediaRootName());
        #endif//< (DCF_DCFX == 1)
        
    }else{
    
    	UINT64 uiFreeSpace;
    	
    	error = AHC_DCF_DirClose(uiDirID);
    	/**
    	@brief find all the dir node.
    	*/
    	#if (DCF_DCFX == 1)
    	AIHC_DCF_ConfirmDCFxDB((INT8*)AIHC_GetMediaRootName());
		#endif ///< (DCF_DCFX == 1)
		
		if(AIHC_DCF_DetectFreeStorage(&uiFreeSpace) == AHC_TRUE){
			/**
			@brief	just in case. If the free space of the storage is too small to store the data of page, 
					the storage may be crashed.
			*/
			if(uiFreeSpace < 0xFFFF){
			    INT8			chDirName[MAX_DIR_CHAR_LENGTH + 1];
			    DCF_DIR_NODE	*psParseDirNode;
			
				STRCAT(chFullDirName, "\\");

		        psParseDirNode = m_DcfDB[uiDBIndex].psRootDirNode;
		        
				MEMSET(chDirName, DCF_RESET_VALUE, m_DcfDB[m_uiDBIndex].byDirCharLength);
				AIHC_DCF_GetDirFullName(chDirName, psParseDirNode->uwDirKey, psParseDirNode->chDirFreeChar);
		    	MEMCPY(chFullDirName + uiDirLength + 1, chDirName, m_DcfDB[m_uiDBIndex].byDirCharLength);
		    	
				AIHC_DCF_GetDirFullName(chDirName, psParseDirNode->uwDirKey, psParseDirNode->chDirFreeChar);
				AIHC_DCF_ParseFile(psParseDirNode, chFullDirName, 1, 0, DCF_DIR_MOUNT_TYPE_MIN);
				AIHC_DCF_GetFileFullName(chDirName, psParseDirNode->psRootFileNode->uwFileKey, psParseDirNode->psRootFileNode->chFileFreeChar);
				AIHC_DCF_DeleteFile(psParseDirNode->uwDirKey, psParseDirNode->psRootFileNode->uwFileKey, chDirName);
			}
		
		}
		
	   	if(AIHC_DCF_ParseDir(chFullDirName, 0xFFFF, 1) == AHC_TRUE)
		{
		    /**
		    @brief configure what kind of mounting dir node by yourself.
		    */
		    INT8			chDirName[MAX_DIR_CHAR_LENGTH + 1];
		    DCF_DIR_NODE	*psParseDirNode;
		    INT32 			uiNodeCtl = m_sFileMem.uiMaxCount;
			
			STRCAT(chFullDirName, "\\");

	        psParseDirNode = m_DcfDB[uiDBIndex].psRootDirNode;

	        m_bParsePage = AHC_TRUE;
	        m_bMountCallBack = AHC_TRUE;
	        
			while(psParseDirNode != NULL){

				MEMSET(chDirName, DCF_RESET_VALUE, sizeof(chDirName));
			
				AIHC_DCF_GetDirFullName(chDirName, psParseDirNode->uwDirKey, psParseDirNode->chDirFreeChar);
		    	
		    	MEMCPY(chFullDirName + uiDirLength + 1, chDirName, m_DcfDB[m_uiDBIndex].byDirCharLength);

				if( (psParseDirNode == m_DcfDB[uiDBIndex].psRootDirNode) || (psParseDirNode == m_DcfDB[uiDBIndex].psLastDirNode) ){
					/**
					@brief	mount the first dir node and the last dir node.
					*/
		        	AIHC_DCF_ParseFile(psParseDirNode, chFullDirName, uiNodeCtl, 0, DCF_DIR_MOUNT_TYPE_MAX);

		        }else{
					/**
					@brief	unmount the other dir nodes.
					*/
		        	AIHC_DCF_ParseFile(psParseDirNode, chFullDirName, 0xFFFF, 0, DCF_DIR_MOUNT_TYPE_UNMOUNT);
		        }
	            
	            uiNodeCtl -= psParseDirNode->uwFileNodeCount;

	        	psParseDirNode = psParseDirNode->psNext;

			}
			
			m_bMountCallBack = AHC_FALSE;
			m_bParsePage = AHC_FALSE;
        }
		
        AIHC_DCF_FindMaxDirNode(&m_DcfDB[uiDBIndex].psFileCtlDirNode, DCF_DIR_MOUNT_TYPE_MASK);
    }

	if((m_DcfDB[uiDBIndex].uwKillDirKey != 0) && (m_DcfDB[uiDBIndex].uwKillFileKey != 0))
	{
		/**
		@brief	setup the kill dir key and file key
		
		*/
		DCF_DIR_NODE *pDir;
		if(AIHC_DCF_FindDir(NULL, m_DcfDB[uiDBIndex].uwKillDirKey, &pDir) == AHC_FALSE){
			m_DcfDB[uiDBIndex].uwKillDirKey  = 0;	
			m_DcfDB[uiDBIndex].uwKillFileKey = 0;
		}
	}else{
		m_DcfDB[uiDBIndex].uwKillDirKey = m_sParsedKillKey[0].uwDirKey;
	    m_DcfDB[uiDBIndex].uwKillFileKey = m_sParsedKillKey[0].uwFileKey;
	}
	
	{
        UINT32 uiTotalAllowedFileCount = AIHC_DCF_GetTotalAllowedFileCount();
    
        if (uiTotalAllowedFileCount > 0)
            m_DcfDB[uiDBIndex].uiBrowserIndex = uiTotalAllowedFileCount - 1;
        else
            m_DcfDB[uiDBIndex].uiBrowserIndex = 0;

        AIHC_Thumb_SetCurrentIdx(m_DcfDB[uiDBIndex].uiBrowserIndex);
    }
    
    #if (DCF_DCFX == 1)
    /**
    @brief	the files already exists in the SD card need to be sorted.
    
    */
    if(m_sPageCtl.uiPageTotalCount > 0){
		#if 0
		{
		DCFX_DB_PAGE*	psPageInfo;

		psPageInfo		= (DCFX_DB_PAGE*)m_pbyDCFxGoldenBuffer;
		
		AIHC_DCF_SortGoldenPage(&psPageInfo);
		
		}
		#endif
    	AIHC_DCF_WriteDCFxPage(m_pbyDCFxTempBuffer);
    	m_sPageCtl.uiSortTotalCount = m_sPageCtl.uiPageTotalCount;
    }
    
	if(AIHC_DCF_NeedSort() == AHC_TRUE){
		
		UINT32 uiIndex;

		if(AIHC_DCF_GetGlodenPageIndex(&uiIndex, AHC_FALSE) == AHC_TRUE){
			AIHC_DCF_SortGoldenPage(uiIndex);
		}
	
	}///< Sorting end
    #endif//< (DCF_DCFX == 1)
    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
    printc("[DCF INFO] Mount: %d, KillDir: %d, KillFileName : %d \r\n", m_uiDBIndex, m_DcfDB[m_uiDBIndex].uwKillDirKey, m_DcfDB[m_uiDBIndex].uwKillFileKey );
    #endif
    return AHC_TRUE;
}

/**
 @brief This API mounts the database

 This API mounts the database and intialize the database of DCF. 
 
 Parameters:
 
 @param[in]  MaxAllowedDirMem         The dir mem pool size
 @param[in]  MaxAllowedFileMem        The file mem pool size
 @param[in]  DefaultDirFreeChar       The default free chars for dirs
 @param[in]  DefaultFileFreeChar      The default free chars for files
 
 @retval AHC_BOOL
*/
AHC_BOOL AIHC_DcfMountDB(UINT32 uiMaxMem)
{
    #if (DCF_DEBUG >= DCF_DEBUG_ALL)
	UINT32				uiTime1, uiTime2;
	printc("DCF MOUNT S  \r\n");
	MMPF_OS_GetTime(&uiTime1);
	#else
	printc("DCF MOUNT S  : %x \r\n", m_ulDCFTempBaseAddr);
	#endif
	
	AIHC_DCF_LOCKDB();
    AIHC_DCF_LOCKPAGE();
    
    if( ( m_bMountDCF[0] == AHC_TRUE ) 
        #if ( DCF_DB_COUNT >= 2)
        && ( m_bMountDCF[1] == AHC_TRUE ) 
        #endif
        #if ( DCF_DB_COUNT >= 3)
        && ( m_bMountDCF[2] == AHC_TRUE ) 
        #endif
        #if ( DCF_DB_COUNT >= 4)
        && ( m_bMountDCF[3] == AHC_TRUE ) 
        #endif
    ){
    	AIHC_DCF_UNLOCKPAGE();
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }
    
    // reset DB

    AIHC_DCF_DBInit(0, DCF_ROOT_DIR_NAME, DCF_DEFAULT_DIR_FREECHAR, DCF_DEFAULT_FILE_FREECHAR);
    //set Lock File Table 
    
    #if (LIMIT_MAX_LOCK_FILE_NUM) //TBD only for DBcount = 1
    AHC_DCF_InitLockFileTable();
    #endif
    
    #if (DCF_DB_COUNT >= 2)    
    AIHC_DCF_DBInit(1, DCF_ROOT_DIR_NAME_2, DCF_DEFAULT_DIR_FREECHAR_2, DCF_DEFAULT_FILE_FREECHAR_2);
    #endif///< #if (DCF_DB_COUNT == 2)
    
    #if (DCF_DB_COUNT >= 3)
    AIHC_DCF_DBInit(2, DCF_ROOT_DIR_NAME_3, DCF_DEFAULT_DIR_FREECHAR_3, DCF_DEFAULT_FILE_FREECHAR_3);
    #endif///< #if (DCF_DB_COUNT == 3)
    
    #if (DCF_DB_COUNT >= 4)
    AIHC_DCF_DBInit(3, DCF_ROOT_DIR_NAME_4, DCF_DEFAULT_DIR_FREECHAR_4, DCF_DEFAULT_FILE_FREECHAR_4);
    #endif///< #if (DCF_DB_COUNT == 4)
	
    /**
    @brief memory allocation of DCF dir and file node pool
    */
    /**	@brief	the buffer for DCF. */
    m_ulDcfMemPool =  (MMP_ULONG)AIHC_DcfMalloc(uiMaxMem);
    
    if ( m_ulDcfMemPool == 0) {
    	#if (DCF_DEBUG >= DCF_DEBUG_ERR)
    	printc("AIHC_DcfMountDB error - acquire no free space. \r\n");
    	#endif
    	AIHC_DCF_UNLOCKPAGE();
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }
    
    AIHC_DCF_MemCtl(&m_ulDcfMemPool);
    
	AIHC_DCF_GetMediaInfo();
	
	#if (DCF_DCFX == 1)
    AIHC_DCF_ControlDCFxRegion();
    #endif///< (DCF_DCFX == 1)

    #if (DCF_DB_COUNT >= 5) 
    if(m_bEnableDCF[DCF_DB_TYPE_DB4_SHARE] == AHC_TRUE){
    
        m_uiDBIndex = DCF_DB_TYPE_DB4_SHARE;
        AIHC_DCF_MountDB(DCF_DB_TYPE_DB4_SHARE);
        m_DcfDB[DCF_DB_TYPE_DB4_SHARE].uiClustersTH = m_sMediaInfo.ulTotalClusters*DCF_CLUSTER_NUMERATOR_DB4/DCF_CLUSTER_DENOMINATOR;
        m_bMountDCF[DCF_DB_TYPE_DB4_SHARE] = AHC_TRUE;
    }
    #endif///< (DCF_DB_COUNT >= 5) 
    
    #if (DCF_DB_COUNT >= 4) 
    if(m_bEnableDCF[DCF_DB_TYPE_DB3_PHOTO] == AHC_TRUE){
    
        m_uiDBIndex = DCF_DB_TYPE_DB3_PHOTO;
        AIHC_DCF_MountDB(DCF_DB_TYPE_DB3_PHOTO);
        m_DcfDB[DCF_DB_TYPE_DB3_PHOTO].uiClustersTH = m_sMediaInfo.ulTotalClusters*DCF_CLUSTER_NUMERATOR_DB3/DCF_CLUSTER_DENOMINATOR;
        m_bMountDCF[DCF_DB_TYPE_DB3_PHOTO] = AHC_TRUE;
    }
    #endif///< (DCF_DB_COUNT >= 4) 
    
    #if (DCF_DB_COUNT >= 3)
    if(m_bEnableDCF[DCF_DB_TYPE_DB2_EVENT] == AHC_TRUE){
    
        m_uiDBIndex = DCF_DB_TYPE_DB2_EVENT;   
        AIHC_DCF_MountDB(DCF_DB_TYPE_DB2_EVENT);
        m_DcfDB[DCF_DB_TYPE_DB2_EVENT].uiClustersTH = m_sMediaInfo.ulTotalClusters*DCF_CLUSTER_NUMERATOR_DB2/DCF_CLUSTER_DENOMINATOR;
        m_bMountDCF[DCF_DB_TYPE_DB2_EVENT] = AHC_TRUE;
    }
    #endif///< (DCF_DB_COUNT >= 3) 

    #if (DCF_DB_COUNT >= 2) 
    if(m_bEnableDCF[DCF_DB_TYPE_DB1_PARKING] == AHC_TRUE){
    
        m_uiDBIndex = DCF_DB_TYPE_DB1_PARKING;   
        AIHC_DCF_MountDB(DCF_DB_TYPE_DB1_PARKING);
        m_DcfDB[DCF_DB_TYPE_DB1_PARKING].uiClustersTH = m_sMediaInfo.ulTotalClusters*DCF_CLUSTER_NUMERATOR_DB1/DCF_CLUSTER_DENOMINATOR;
        m_bMountDCF[DCF_DB_TYPE_DB1_PARKING] = AHC_TRUE;
    }
    #endif///< (DCF_DB_COUNT >= 2) 
    
    if(m_bEnableDCF[DCF_DB_TYPE_DB0_NORMAL] == AHC_TRUE){
    
        m_uiDBIndex = DCF_DB_TYPE_DB0_NORMAL;   
        AIHC_DCF_MountDB(DCF_DB_TYPE_DB0_NORMAL);
        m_bMountDCF[DCF_DB_TYPE_DB0_NORMAL] = AHC_TRUE;
        m_DcfDB[DCF_DB_TYPE_DB0_NORMAL].uiClustersTH = m_sMediaInfo.ulTotalClusters*DCF_CLUSTER_NUMERATOR_DB0/DCF_CLUSTER_DENOMINATOR;
    }
	/**
	@brief	make sure the operation of DCF background task is done.
	
	*/
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)	
    MMPF_OS_GetTime(&uiTime2);
	printc("DCF MOUNT E, Time : %d \r\n", uiTime2 - uiTime1);
	#else
	printc("DCF MOUNT E : %x, Size: %d\r\n", m_ulDcfMemPool, (m_ulDcfMemPool-m_ulDCFTempBaseAddr));
	#endif
	
	#if (DCF_SUB_DB == 1)
	AIHC_DCF_MountSubDB(DCF_SUB_ROOT_DIR_NAME);
	#endif
    
    #if ( UUID_XML_FEATURE == 1 )
    {
    UI_WriteSdUuidXML();
    }
    #endif
    
    AIHC_DCF_UNLOCKPAGE();
    AIHC_DCF_UNLOCKDB();	
    return AHC_TRUE;
}

/**
 @brief This API un-mounts the database

 This API un-mounts the database
 
 Parameters:
 
 @retval AHC_BOOL
*/
AHC_BOOL AIHC_DcfUnMountDB(void)
{
	/**
	@brief	make sure the operation of DCF background task is done.
	
	*/
	printc("AIHC_DcfUnMountDB S \r\n");
	
	AIHC_DCF_LOCKDB();
	AIHC_DCF_LOCKPAGE();
	
    if( (m_bMountDCF[0] == AHC_FALSE ) 
        #if ( DCF_DB_COUNT >= 2)
        && (m_bMountDCF[1] == AHC_FALSE ) 
        #endif    
        #if ( DCF_DB_COUNT >= 3)
        && (m_bMountDCF[2] == AHC_FALSE ) 
        #endif    
        #if ( DCF_DB_COUNT >= 4)
        && (m_bMountDCF[3] == AHC_FALSE ) 
        #endif    
    ){
    
    	AIHC_DCF_UNLOCKPAGE();
    	AIHC_DCF_UNLOCKDB();
    	
        return AHC_FALSE;
    }
    
    MEMSET(&m_DcfDB[0], DCF_RESET_VALUE, sizeof(DCF_DATABASE));
    m_bMountDCF[0] = AHC_FALSE;
    
    #if ( DCF_DB_COUNT >= 2)
    MEMSET(&m_DcfDB[1], DCF_RESET_VALUE, sizeof(DCF_DATABASE));
    m_bMountDCF[1] = AHC_FALSE;
    #endif///< #if ( DCF_DB_COUNT >= 2)

    #if ( DCF_DB_COUNT >= 3)
    MEMSET(&m_DcfDB[2], DCF_RESET_VALUE, sizeof(DCF_DATABASE));
    m_bMountDCF[2] = AHC_FALSE;
    #endif///< #if ( DCF_DB_COUNT >= 3)
	
    #if ( DCF_DB_COUNT >= 4)
    MEMSET(&m_DcfDB[3], DCF_RESET_VALUE, sizeof(DCF_DATABASE));
    m_bMountDCF[3] = AHC_FALSE;
    #endif///< #if ( DCF_DB_COUNT >= 4)
	    
    AIHC_DCF_MemFree();
    

    
    #if (DCF_SUB_DB == 1)
    AIHC_DCF_UnMountSubDB();
    #endif///< #if (DCF_SUB_DB == 1)
    
    AIHC_DCF_UNLOCKPAGE();
    AIHC_DCF_UNLOCKDB();
	printc("AIHC_DcfUnMountDB E \r\n");
    return AHC_TRUE;
}

/**
 @brief This API returns the status of m_bMountDCF[m_uiDBIndex]
 
 Parameters:

 @retval m_bMountDCF[m_uiDBIndex]  //AHC_TRUE: DCF mounted. AHC_FALSE: DCF unmounted. 
*/
AHC_BOOL AIHC_DCF_IsDBMounted(void)
{
	AHC_BOOL bMounted;
	
	AIHC_DCF_LOCKDB();
	bMounted = m_bMountDCF[m_uiDBIndex];
	AIHC_DCF_UNLOCKDB();
	
	return bMounted;
}

AHC_BOOL AIHC_DCF_CheckBackGround(void)
{
	AHC_BOOL bEnable;
	
	AIHC_DCF_LOCKDB();
	AIHC_DCF_LOCKPAGE();
	bEnable = m_bEnableBackground;
	AIHC_DCF_UNLOCKPAGE();
	AIHC_DCF_UNLOCKDB();
	return bEnable;
}

AHC_BOOL AIHC_DCF_EnableBackGround(AHC_BOOL bEnable)
{
	AIHC_DCF_LOCKDB();
	AIHC_DCF_LOCKPAGE();
	m_bEnableBackground = bEnable;
	AIHC_DCF_UNLOCKPAGE();
	AIHC_DCF_UNLOCKDB();
	return AHC_TRUE;
}


AHC_BOOL AIHC_DCF_GetIndex(	INT8 *pchDirName,
							INT8 *pchFileName, 
							UINT32 *puiIndex)
{
	DCF_DIR_NODE	*psDir;
	DCF_FILE_NODE	*psFile;
	UINT16			uwDirKey;
	UINT16			uwFileKey;
	INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];
	INT8			chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
	UINT8			byFileType;
	AHC_BOOL 		bFound = AHC_FALSE;
	AHC_BOOL		bResult;
	
	AIHC_DCF_LOCKDB();
	
	if(	(AIHC_DCF_GetDirKey(pchDirName, &uwDirKey, chDirFreeChar) == AHC_FALSE) ||
		(AIHC_DCF_GetFileKey(pchFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_FALSE) ){
		return AHC_FALSE;
	}else{
		if(m_DcfDB[m_uiDBIndex].chAllowedFileType[byFileType] != 1)
			return AHC_FALSE;
	}

	if(AIHC_DCF_FindDir(NULL, uwDirKey, &psDir) == AHC_TRUE){
		if(AIHC_DCF_WhichIsBoss(psDir->chDirFreeChar, chDirFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum) == DCF_BOSS_EQUAL){
			
			if( (uwFileKey < psDir->psRootFileNode->uwFileKey) ||
				(uwFileKey > psDir->psLastFileNode->uwFileKey) ){
				AIHC_DCF_MountDirNode(psDir, 
									  NULL, 
									  0xFFFF,
								      uwFileKey,
								      DCF_DIR_MOUNT_TYPE_KEY);
			}
			
			if(AIHC_DCF_FindFileNode(psDir, NULL, uwFileKey, &psFile) == AHC_TRUE){
				if(AIHC_DCF_WhichIsBoss(psFile->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
					bFound = AHC_TRUE;
				}
			}
		}
	}
	
	if(bFound == AHC_TRUE){

		UINT32 uiDirMaxCount, uiFileCountInDir, uiFileCountInDB;
		UINT32 i, j;
		UINT16 uwIndex;
		
	    uiDirMaxCount = uwDirKey - MIN_DCF_DIR_KEYNUM;
	    uiFileCountInDB = 0;
	    //Find the selected obj belong to which dir
	    for( i = 0 ; i < uiDirMaxCount ; i++ ) {
	    
	        if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i] != DCF_INVALID_NUMBER_16 ) {
	            
	            uiFileCountInDir = 0;
	            /**
	            @brief find the number of the files which are supported file type.
	            
	            */
	            for( j = 0; j < MAX_DCF_SUPPORT_FILE_TYPE ; j++ ) {
	            
	                if ( m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j] && m_DcfDB[m_uiDBIndex].chAllowedFileType[j] ) {
	                    uiFileCountInDir += m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j];
	                }
	            }

	            uiFileCountInDB += uiFileCountInDir;
	        }
	    }
	    
	    if(psDir != m_DcfDB[m_uiDBIndex].psPowerDirNode){
	    
	    	AIHC_DCF_MountDirNode(	psDir, 
									NULL, 
									0xFFFF,
									uwFileKey,
									DCF_DIR_MOUNT_TYPE_KEY);
	    
	    }else if(psDir->byMountMode == DCF_DIR_MOUNT_TYPE_UNMOUNT){
	    
	    	AIHC_DCF_MountDirNode(	psDir, 
									NULL, 
									0xFFFF,
									uwFileKey,
									DCF_DIR_MOUNT_TYPE_KEY);
	    
	    }
	    
		AIHC_DCF_ParseKeyInFileMap(uwFileKey, &uwIndex);
		*puiIndex = uwIndex + uiFileCountInDB;
		bResult = AHC_TRUE;
		
		
	}else{
		bResult = AHC_FALSE;
	}
	
	AIHC_DCF_UNLOCKDB();
	
	return bResult;
}

AHC_BOOL AIHC_DCF_GetInfo(UINT32 uiIndex, DCF_INFO *Info)
{
    UINT32              i, j;
    UINT32              uiDirMaxCount;
    UINT16              uwDirKey = 0;
    UINT16              uwFileKey;
    UINT32              uiFileIdx;
    UINT32              uiFileSize;
    UINT32              uiFileCountInDB = 0;
    DCF_DIR_NODE        *psDirNode;
    DCF_FILE_NODE       *psFileNode;
    UINT32              uiDirLength;
    INT8                TempString[DCF_MAX_FILE_NAME_SIZE];
    AHC_FS_ATTRIBUTE	attribute;
    AHC_FS_FILETIME		FileTimeStru;

    AHC_BOOL            bFileNodeInDB = AHC_FALSE;
    UINT32              uiFileCountInDir;
	UINT16				uwFileMapKey;
	
	AIHC_DCF_LOCKDB();
	
    if ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE )
    {
    	/**	check mount DCF database or not. */
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }

	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("[DCF INFO] AHC_DCF_GetInfobyIndex Index : %d \r\n", uiIndex);
	#endif

    uiDirMaxCount = MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1;
    
    //Find the selected obj belong to which dir
    for( i = 0 ; i < uiDirMaxCount ; i++ ) {
    
        if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i] != DCF_INVALID_NUMBER_16 ) {
            
            uiFileCountInDir = 0;
            /**
            @brief find the number of the files which are supported file type.
            
            */
            for( j = 0; j < MAX_DCF_SUPPORT_FILE_TYPE ; j++ ) {
            
                if ( m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j] && m_DcfDB[m_uiDBIndex].chAllowedFileType[j] ) {
                    uiFileCountInDir += m_DcfDB[m_uiDBIndex].ppsFileCountInDir[i]->uwFileCountInFileType[j];
                }
            }
            
            if ( ( uiFileCountInDB + uiFileCountInDir ) > uiIndex ) {
            	/**
            	@brief find the dir for the uiIndex.
            	*/
                uwDirKey  = MIN_DCF_DIR_KEYNUM + i;
                break;
            }

            uiFileCountInDB += uiFileCountInDir;
        }
    }

    //file offset in the found dir
    uiFileIdx = uiIndex - uiFileCountInDB;
    
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("[DCF INFO] AHC_DCF_GetInfobyIndex uiFileCountInDB  : %d \r\n", uiFileCountInDB);
	printc("[DCF INFO] AHC_DCF_GetInfobyIndex uiFileCountInDir : %d \r\n", uiFileCountInDir);
	printc("[DCF INFO] AHC_DCF_GetInfobyIndex uiFileIdx        : %d \r\n", uiFileIdx);
	printc("[DCF INFO] AHC_DCF_GetInfobyIndex uwDirKey         : %d \r\n", uwDirKey);
	#endif
	
    if( AIHC_DCF_FindDir(NULL, uwDirKey, &psDirNode) == AHC_TRUE ) {
        /**
        @brief	The DB has this dir node.
        
        */
        if ( psDirNode->uwFileNodeCount == m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM] ) {
        	/**
        	@brief the file node is in DB so do not find it in the storage.
        	*/
            bFileNodeInDB = AHC_TRUE;

        }else{
        
		    if(psDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){

		    	if(AIHC_DCF_ParseIndexInFileMap(uiFileIdx + 1, &uwFileMapKey) == AHC_TRUE){
		    		
		    		if(psDirNode->psLastFileNode->uwFileKey >= uwFileMapKey ){
		    			/**
		    			@brief power dir node already mount the file node.
		    			*/
		    			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		    			printc("[DCF INFO] AHC_DCF_GetInfobyIndex File Node in Map \r\n");
		    			#endif
		    			
		    			bFileNodeInDB = AHC_TRUE;
		    		
		    		}else{
		    			/**
		    			@brief power dir node already mount the file node.
		    			*/
		    			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		    			printc("[DCF INFO] AHC_DCF_GetInfobyIndex File Node Not in Map Need to re-parse \r\n");
		    			#endif
		    			bFileNodeInDB = AHC_FALSE;
		    		
		    		}
		    	
		    	}
		    }
        }
    }else{
    	/**
    	@brief no this dir node.
    	
    	*/
		#if (DCF_DEBUG >= DCF_DEBUG_ERR)
		printc("[DCF INFO] AHC_DCF_GetInfobyIndex No Dir Node \r\n");
		#endif
		AIHC_DCF_UNLOCKDB();
    	return AHC_FALSE;
    }
    

    
    
    if ( bFileNodeInDB == AHC_FALSE ){
		
		if(psDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){
			/**
			@brief already know the file key of the file with th index.
			*/
			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
			printc("[DCF INFO] AHC_DCF_GetInfobyIndex 1st Parse type KEY \r\n");
			#endif
			
    		AIHC_DCF_MountDirNode(psDirNode, 
								  NULL, 
								  m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM],
								  uwFileMapKey,
								  DCF_DIR_MOUNT_TYPE_KEY);

		}else{
    		/**
    		@brief do not know the file key of the file with th index so do the first parse of file node.
    		*/
    		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
    		printc("[DCF INFO] AHC_DCF_GetInfobyIndex 1st Parse type Min \r\n");
    		#endif
    		AIHC_DCF_MountDirNode(psDirNode, 
								  NULL, 
								  m_sFileMem.uiMaxCount,
								  0,
								  DCF_DIR_MOUNT_TYPE_MIN);
    	}
    	
    	

    }
    
	if(psDirNode == m_DcfDB[m_uiDBIndex].psPowerDirNode){
		if(AIHC_DCF_ParseIndexInFileMap(uiFileIdx + 1, &uwFileMapKey) == AHC_TRUE){
			uwFileKey = uwFileMapKey;		
		}else{
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		
		}
		
		#if (DCF_DEBUG >= DCF_DEBUG_ALL)
		printc("[DCF INFO] AHC_DCF_GetInfobyIndex uwFileMapKey : %d \r\n", uwFileMapKey);
		#endif
		
		if(AIHC_DCF_FindFileNode(psDirNode, NULL, uwFileKey, &psFileNode) == AHC_FALSE){
			/**
			@brief the first parse does not mount the file node so do the second mount for the file node.
			
			*/
			#if (DCF_DEBUG >= DCF_DEBUG_ALL)
			printc("[DCF INFO] AHC_DCF_GetInfobyIndex 2nd Parse type KEY \r\n");
			#endif
			AIHC_DCF_MountDirNode(psDirNode, 
								  NULL, 
								  m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDirKey - MIN_DCF_DIR_KEYNUM],
								  uwFileMapKey,
								  DCF_DIR_MOUNT_TYPE_KEY);
								  
			AIHC_DCF_FindFileNode(psDirNode, NULL, uwFileKey, &psFileNode);
		}
	}else{
	
		psFileNode = psDirNode->psRootFileNode;
		uiIndex = 0;
		
		while(psFileNode != NULL){
			if(m_DcfDB[m_uiDBIndex].chAllowedFileType[psFileNode->byFileType] == 1){
				uiIndex++;
			}
			if(uiIndex > uiFileIdx){
				break;
			}
			psFileNode = psFileNode->psNext;
		}
	
	}
	
    for( i = 0 ; i < m_DcfDB[m_uiDBIndex].byDirFreeCharNum ; i++ ) {
        Info->DirFreeChar[i] = psDirNode->chDirFreeChar[i];
    }
    
    for( i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++ ) {
        Info->FileFreeChar[i] = psFileNode->chFileFreeChar[i];
    }
    
    Info->FileType = psFileNode->byFileType;

    
    STRCPY(Info->FileName, m_DcfDB[m_uiDBIndex].chRootName);
    STRCAT(Info->FileName, "\\");
    
    MEMSET(TempString, 0, sizeof(TempString));
    AIHC_DCF_GetDirFullName(TempString, uwDirKey, (INT8*)Info->DirFreeChar);
    STRCAT(Info->FileName, TempString);
    STRCAT(Info->FileName, "\\");
    
    MEMSET(TempString, 0, sizeof(TempString));
    AIHC_DCF_GetFileFullName(TempString, psFileNode->uwFileKey, (INT8*)Info->FileFreeChar);
    STRCAT(Info->FileName, TempString);
    
    STRCAT(Info->FileName, EXT_DOT);
    STRCAT(Info->FileName, m_DcfSupportFileType[Info->FileType]);

    uiDirLength = STRLEN(Info->FileName);

    //AHC_DCF_FileDirGetAttribute(Info->FileName, uiDirLength, &attribute);
    //AHC_DCF_FileDirGetTime(Info->FileName, uiDirLength, &FileTimeStru);
    uiFileSize = 0;
    
    AHC_DCF_FileDirGetInfo(Info->FileName, uiDirLength, &attribute, &FileTimeStru, &uiFileSize);
    
    Info->uiFileSize = uiFileSize;
    Info->uwDirKey   = uwDirKey;
    Info->uwFileKey  = psFileNode->uwFileKey;
    
    if( attribute & AHC_FS_ATTR_READ_ONLY){
        Info->bReadOnly  = AHC_TRUE;
    }else{
        Info->bReadOnly  = AHC_FALSE;
    }
    
    #if (DCF_DCFX == 1)
    if( AIHC_DCF_WhichIsBoss((INT8*)Info->FileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL ){
    	Info->bCharLock = AHC_TRUE;
    }else
    #endif
    {
    	Info->bCharLock = AHC_FALSE;
    }
	
	
    Info->uwYear    = FileTimeStru.usYear;
    Info->uwMonth   = FileTimeStru.usMonth;
    Info->uwDay     = FileTimeStru.usDay;
    Info->uwHour    = FileTimeStru.usHour;
    Info->uwMinute  = FileTimeStru.usMinute;
    Info->uwSecond  = FileTimeStru.usSecond;
    
	AIHC_DCF_UNLOCKDB();
	
	return AHC_TRUE;
}

#if 0
void __SUB_DB__(){}
#endif

#if (DCF_SUB_DB == 1)
/**
 @brief This API allocate one File node from the mem pool

 This API allocate one File node from the mem pool
 
 Parameters:
 @retval DCF_FILE_NODE
*/
static DCF_FILE_NODE* AIHC_DCF_AllocSubFileNode()
{
    DCF_FILE_NODE   *psFileNode;
    UINT32          i;
	UINT32			uiFileNodeMaxCount;//loop_count;
            
    if ( m_sSubFileMem.uiFreeMem >= m_sSubFileMem.uiNodeSize ){
    
        uiFileNodeMaxCount = m_sSubFileMem.uiMaxCount;//m_sSubFileMem.uiMemSize / uiFileNodeSize;
        
        for( i = 0 ; i < uiFileNodeMaxCount ; i++) {
        
            if ( (m_sSubFileMem.uiMemOffset + m_sSubFileMem.uiNodeSize) <= m_sSubFileMem.uiMemSize ){
                
                psFileNode   = (DCF_FILE_NODE*)(m_sSubFileMem.pMemPool + m_sSubFileMem.uiMemOffset);
                
            }else{
                
                psFileNode   = (DCF_FILE_NODE*)(m_sSubFileMem.pMemPool);
                
                m_sSubFileMem.uiMemOffset = 0;
            }
            
            /**
            @brief find the un-used memory of the file node memory pool.
            
            */
            if ( (psFileNode->uwFileKey == 0) || (psFileNode->uwFileKey == DCF_INVALID_NUMBER_16) ) {
                //un-used block
                
                MEMSET(psFileNode, DCF_RESET_VALUE, sizeof(DCF_FILE_NODE));
                
                break;
            }
            else {
                m_sSubFileMem.uiMemOffset += m_sSubFileMem.uiNodeSize;
                
                if( m_sSubFileMem.uiMemOffset >= m_sSubFileMem.uiMemSize )
                    m_sSubFileMem.uiMemOffset = 0;
            }
        }
        
        m_sSubFileMem.uiFreeMem   -= m_sSubFileMem.uiNodeSize;
        m_sSubFileMem.uiMemOffset += m_sSubFileMem.uiNodeSize;
        /**
        @brief Its dangerous.
        
        */
        if( m_sSubFileMem.uiMemOffset >= m_sSubFileMem.uiMemSize )
            m_sSubFileMem.uiMemOffset = 0;
            
        return psFileNode;
    }else{
        
        return NULL;
    }
}

/**
 @brief This API free one File node from the mem pool
 
 WARNING: you must release the memory of the first node!
 make sure that you re-link the file node behind or in front of the file node which you want to kill.
 
 Parameters:
 @retval DCF_FILE_NODE
*/
static void AIHC_DCF_FreeSubFileNode(DCF_FILE_NODE *psFileNode)
{
    if ( psFileNode != NULL ) {

        MEMSET(psFileNode, DCF_RESET_VALUE, sizeof(DCF_FILE_NODE));
        
        m_sSubFileMem.uiFreeMem += sizeof(DCF_FILE_NODE);
    }
}

static AHC_BOOL AIHC_DCF_RemoveSubFileNode(DCF_FILE_NODE *psFileNode)
{
    DCF_FILE_NODE   *psKillFileNode;

    //No more file entries, return SUCCESS
    if ( m_DCFSubDB.uwTotalFileCount == 0 )
        return AHC_TRUE;

    m_DCFSubDB.uwTotalFileCount--;
    
    
    if( m_DCFSubDB.psFileCtlFileNode == psFileNode){

        if(m_DCFSubDB.psFileCtlFileNode->psNext != NULL){
            m_DCFSubDB.psFileCtlFileNode = m_DCFSubDB.psFileCtlFileNode->psNext;
        }else if(m_DCFSubDB.psFileCtlFileNode->psPrev != NULL){
            m_DCFSubDB.psFileCtlFileNode = m_DCFSubDB.psFileCtlFileNode->psPrev;
        }else{
            m_DCFSubDB.psFileCtlFileNode = NULL;
        
        }
    }
    
    if( m_DCFSubDB.psKillFileNode == psFileNode){

        if(m_DCFSubDB.psKillFileNode->psNext != NULL){
            m_DCFSubDB.psKillFileNode = m_DCFSubDB.psKillFileNode->psNext;
        }else if(m_DCFSubDB.psKillFileNode->psPrev != NULL){
            m_DCFSubDB.psKillFileNode = m_DCFSubDB.psKillFileNode->psPrev;
        }else{
            m_DCFSubDB.psKillFileNode = NULL;
        
        }
    }
    
    if( psFileNode == m_DCFSubDB.psRootFileNode ) {
    	/**
    	@brief the file which is the root file node, is getting removed.
    	*/
        m_DCFSubDB.psRootFileNode = psFileNode->psNext;
    
        if(m_DCFSubDB.psRootFileNode != NULL )
	        m_DCFSubDB.psRootFileNode->psPrev = NULL;
        else{
        	m_DCFSubDB.psLastFileNode = NULL;
        }
    }else if( psFileNode == m_DCFSubDB.psLastFileNode ) {
    	/**
    	@brief the file which is the last file node, is getting removed.
    	*/    
    	m_DCFSubDB.psLastFileNode = psFileNode->psPrev;
    
    	if(m_DCFSubDB.psLastFileNode != NULL )
	        m_DCFSubDB.psLastFileNode->psNext = NULL;
	        
		
    }else{
    
        psFileNode->psPrev->psNext = psFileNode->psNext;
        psFileNode->psNext->psPrev = psFileNode->psPrev;
    }

    /**
    @brief free the memory of the file node and its neighbor.
    
    */
    psKillFileNode = psFileNode;
    
    while(psKillFileNode != NULL){

    	psFileNode     = psKillFileNode;
    	psKillFileNode = psKillFileNode->psNeighbor;
    	
    	AIHC_DCF_FreeSubFileNode(psFileNode);
    }
        
    return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_AddSubFileNode(DCF_FILE_NODE *psNewFileNode)
{
    DCF_FILE_NODE   *psFileNode;
    AHC_BOOL        bSameFileKey = AHC_FALSE;
	AHC_BOOL        bChange = AHC_FALSE;
	
	if(psNewFileNode == NULL)
	    return AHC_FALSE;

    if (m_DCFSubDB.psFileCtlFileNode != NULL){
        
        if(m_DCFSubDB.psFileCtlFileNode == m_DCFSubDB.psLastFileNode){
            bChange = AHC_TRUE;
        
        }
    
    }

    if ( m_DCFSubDB.psRootFileNode == NULL ) {
    	// there is no file in the dir. why not clear the previous pointer of the new file node?
        psNewFileNode->psNext           = NULL;
        m_DCFSubDB.psRootFileNode  = psNewFileNode; // the first file node is the new file node.
        m_DCFSubDB.psLastFileNode  = psNewFileNode; // the first last node is the new file node.

    }
    else {
    
        psFileNode = m_DCFSubDB.psRootFileNode;///< get the first file node in the dir
	        
       	while(psFileNode != NULL){
        	
	   		if ( psFileNode->uwFileKey >= psNewFileNode->uwFileKey )
    	            break;
            	
	        psFileNode = psFileNode->psNext;
       	}

        
        /**	@brief	3 cases. */
        if (psFileNode == NULL) {
            /** @brief	case 1, there is no key number bigger than the new file node */
            
            // clear the next file node of the new file node.
            psNewFileNode->psNext            = NULL;
            // put the last file node in front of the new file node.
            psNewFileNode->psPrev            = m_DCFSubDB.psLastFileNode;
            // put the new file node behind the last file node.
            m_DCFSubDB.psLastFileNode->psNext = psNewFileNode;
            // set the new file node as the last file node in the dir.
            m_DCFSubDB.psLastFileNode       = psNewFileNode;
        }
        else if ( psFileNode->uwFileKey > psNewFileNode->uwFileKey ) {
        
        	/**	@brief	case 2, there is one key number bigger than the new file node.
        				insert the new file node. */
            psNewFileNode->psNext           = psFileNode;
            psNewFileNode->psPrev           = psFileNode->psPrev;
            
            if( psFileNode->psPrev == NULL ) {
                /**	@brief	x -> temp file node -> ?,
                			x -> new file mode -> temp file node -> ? */
                			
                m_DCFSubDB.psRootFileNode     = psNewFileNode;///< the first file node is the new file node
                psFileNode->psPrev      = psNewFileNode;
                
                if(psFileNode->psNext == NULL) {
                	/**	@brief	x -> temp file node -> x, 
                				x -> new file node -> temp file node -> x */
                    m_DCFSubDB.psLastFileNode  = psFileNode;///< the last file node is the temp file node
                }else{
                	/**	@brief	x -> temp file node -> other file node, 
                				x -> new file node -> temp file node -> other file node. */
                }
            }
            else {
            	/**	@brief	other file node -> temp file node -> ?, 
            				other file node -> new file node -> temp file node -> ? */
                psFileNode->psPrev->psNext    = psNewFileNode;
                psFileNode->psPrev          = psNewFileNode;
                
                if(psFileNode->psNext == NULL) {
                	/**	@brief	other file node -> temp file node -> x,
                				other file node -> new file node -> temp file node -> x */
                    m_DCFSubDB.psLastFileNode = psFileNode;///< the last file node is the temp file node
                }else{
                	/**	@brief	other file node -> temp file node -> other file node,
                				other file node -> new file node -> temp file node -> other file node. */
                
                }
            }
        }
        else if ( psFileNode->uwFileKey == psNewFileNode->uwFileKey ) {
        
        	bSameFileKey = AHC_TRUE;

            /**	@brief	case 3, there is one key number the same as the new file node.
            			the key of the new file node is the same as one of file nodes in dir. */
            psNewFileNode->psNext	= NULL;
            psNewFileNode->psPrev	= NULL;

            if ( psNewFileNode->byFileType <= psFileNode->byFileType) {

                /** @brief	replace the first node with the new file node.
                			the first file node is setup as the neighhor of the new file node. */
                psNewFileNode->psNext            = psFileNode->psNext;
                psNewFileNode->psPrev            = psFileNode->psPrev;
                
                psNewFileNode->psNeighbor        = psFileNode;
            	
                if( psFileNode->psPrev == NULL ) {
                	/**	x -> temp file node -> ?,
                		x -> new file node -> temp file node -> ? */
                    m_DCFSubDB.psRootFileNode     = psNewFileNode;

                    if( psFileNode->psNext == NULL){
                    	/**	x -> temp file node -> x,
                    		x -> new file node -> x*/
                    	m_DCFSubDB.psLastFileNode  = psNewFileNode;
                    }else{
                    	/**	x -> temp file node -> other file node,
                    		x -> new file node -> other file node*/
                    	psFileNode->psNext->psPrev = psNewFileNode;
                    
                    }
                
                }
                else if( psFileNode->psNext == NULL ) {
                	/**	other file node -> temp file node -> x, 
                		other file node -> new file node -> x*/
                    psFileNode->psPrev->psNext = psNewFileNode;
                    m_DCFSubDB.psLastFileNode   = psNewFileNode;
                }
                else {
                	/**	other file node -> temp file node -> other file node,
                		other file node -> new file node -> other file node */
                    psFileNode->psPrev->psNext = psNewFileNode;
                    psFileNode->psNext->psPrev = psNewFileNode;
                }
                
                // clear the pointer of the temp file node 
                psFileNode->psNext           = NULL;
                psFileNode->psPrev           = NULL;

            }
            else {
				
				
                while( psFileNode != NULL ){

                    if ( psNewFileNode->byFileType >= psFileNode->byFileType ) {
                    	/**
                    	@brief the new file node is the first file node in the same key number.
                    	*/                        
                        break;
                    }
                    
                    if(psFileNode->psNeighbor != NULL){
                		psFileNode = psFileNode->psNeighbor;
                	}else{
                		break;
                	}
                
                }
                
                if(psFileNode->psNeighbor == NULL){
                	psFileNode->psNeighbor = psNewFileNode;
                }else{
                	psNewFileNode->psNeighbor = psFileNode->psNeighbor;
                	psFileNode->psNeighbor    = psNewFileNode->psNeighbor;
                	
                }

            }///< if ( j == 0 )
        }///< end of if-else loop
    }
    
    if(bChange == AHC_TRUE){
    
        m_DCFSubDB.psFileCtlFileNode = m_DCFSubDB.psLastFileNode;
    }
    
    m_DCFSubDB.uwTotalFileCount++;
    
    return AHC_TRUE;

}

static AHC_BOOL AIHC_DCF_ParseSubFileMask(INT8* pchFileFreeChar, AHC_FS_ATTRIBUTE* sFileAttribute, AHC_FS_FILETIME* sFileTime)
{
    if(!STRCMP(pchFileFreeChar, m_chSubFileFreeChar)){
        return AHC_TRUE;
    
    }

    return AHC_FALSE;

}


static AHC_BOOL AIHC_DCF_ParseSubFile(INT8* pchDirName)
{
    INT8                chFileName[DCF_MAX_FILE_NAME_SIZE];
    INT8				chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    AHC_FS_ATTRIBUTE	attribute;
    AHC_FS_FILETIME		FileTimeStru;
    UINT32              uiFileSize;
    UINT32              uiFileID;
    UINT32              uiNameLength;
    UINT32              error;
    UINT8               byFileMode;
    
    UINT16              uwCurFileCount;
    
    MEMSET(chFileName, DCF_RESET_VALUE, sizeof(chFileName));
    MEMSET(chFileFreeChar, DCF_RESET_VALUE, sizeof(chFileFreeChar));
    
    uiNameLength    = STRLEN(pchDirName);
	uwCurFileCount  = 0;

    if(AHC_DCF_DirOpen(pchDirName, uiNameLength, &uiFileID) != MMP_ERR_NONE){
    	return AHC_FALSE;
    }
    
    byFileMode = AHC_FILE_NAME | AHC_ATTRIBUTE | AHC_ENTRY_SIZE | AHC_FILE_TIME;
   
    
    while(1) {
    	/**	@brief	get files. */
        error = AHC_DCF_GetFileList( uiFileID,
                                     byFileMode,
                                     chFileName,
                                     &attribute,
                                     &FileTimeStru,
                                     &uiFileSize );

        if ( AHC_FS_ERR_NO_MORE_ENTRY == error ){
        	/**
        	@brief no files in this dir.
        	*/
            break;
        }

        if ( !(AHC_FS_ATTR_DIRECTORY & attribute) ){
			            
			UINT16          uwNewFileKey;
		    UINT8           byFileType;
       	    DCF_FILE_NODE   *psNewFileNode;


       	    
			if ( AIHC_DCF_GetFileKey(chFileName, &uwNewFileKey , chFileFreeChar, &byFileType) == AHC_TRUE ) {

    			
				if ( AIHC_DCF_ParseSubFileMask(chFileFreeChar, &attribute, &FileTimeStru) == AHC_TRUE ) {



        			psNewFileNode = AIHC_DCF_AllocSubFileNode();
        			
        			if(psNewFileNode == NULL){
        			    // kill the old file directly.
                        INT8 chPathName[DCF_MAX_FILE_NAME_SIZE];
        			    
        			    MEMSET(chPathName, DCF_RESET_VALUE, sizeof(chPathName));
        			        
        			    if(uwNewFileKey > m_DCFSubDB.psRootFileNode->uwFileKey){
            			    
            			    INT8 chOldFileName[MAX_FILE_CHAR_LENGTH+1];    
            			    MEMSET(chOldFileName, DCF_RESET_VALUE, sizeof(chOldFileName));
            			
            			    /*
            			    SD:\\EMER\\
            			    */
            			    AIHC_DCF_GetFileFullName(chOldFileName, m_DCFSubDB.psRootFileNode->uwFileKey, m_DCFSubDB.psRootFileNode->chFileFreeChar);
            			    STRCPY(chPathName, m_DCFSubDB.chRootDirName);
            			    STRCAT(chPathName, "\\");
            			    /*
            			    SD:\\EMER\\EMER0001
            			    */
            			    STRCAT(chPathName, chOldFileName);
            			    
                            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                            {
                            UINT32 i;
                            
                            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                                MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
                        		STRCPY(m_chAuxiliaryFileName[i], chPathName);
                        		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
                        	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
                            }
                            
                            }
                            #endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
                            
            			    /*
            			    SD:\\EMER\\EMER0001.AVI
            			    */
                    	    STRCAT(chPathName, EXT_DOT);
                    	    STRCAT(chPathName, m_DcfSupportFileType[m_DCFSubDB.psRootFileNode->byFileType]);
                    	    AHC_DCF_FileRemove(chPathName, STRLEN(chPathName));
                    	    
                            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                        	{
                            UINT32 i;
                            
                            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                                printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                                AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
                            }
                            
                            }
                        	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
                    	    
                    	    
            			    AIHC_DCF_RemoveSubFileNode(m_DCFSubDB.psRootFileNode);
            			    
        			    }else{
            			    /*
            			    SD:\\EMER\\EMER0001
            			    */
            			    STRCPY(chPathName, m_DCFSubDB.chRootDirName);
            			    STRCAT(chPathName, "\\");
            			    STRCAT(chPathName, chFileName);
            			    
                            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                            {
                            UINT32 i;
                            
                            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                                MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
                        		STRCPY(m_chAuxiliaryFileName[i], chPathName);
                        		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
                        	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
                            }
                            
                            }
                            #endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
            			    
            			    /*
            			    SD:\\EMER\\EMER0001.AVI
            			    */
                    	    STRCAT(chPathName, EXT_DOT);
                    	    STRCAT(chPathName, m_DcfSupportFileType[byFileType]);
                    	    AHC_DCF_FileRemove(chPathName, STRLEN(chPathName));
                    	    
                            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                        	{
                            UINT32 i;
                            
                            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                                printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                                AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
                            }
                            
                            }
                        	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
                    	    
        			        break;
        			    }
        			    
        			    //printc("Delete : %s \n", chPathName);
        			    
        			    psNewFileNode = AIHC_DCF_AllocSubFileNode();
        			}
                    
                    uwCurFileCount++;

					/**	@brief	setup the file node which you wanna add. */
			        psNewFileNode->uwFileKey  = uwNewFileKey;
			        psNewFileNode->byFileType = byFileType;
	        
			        MEMCPY(psNewFileNode->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
			        
		        	AIHC_DCF_AddSubFileNode(psNewFileNode);
		        	
		        	{
		        	UINT64				uiiClusterPerFile;
		            
		            uiiClusterPerFile = (uiFileSize + m_uiBytesPerCluster - 1)/m_uiBytesPerCluster;
	
                	m_DCFSubDB.uiCluster += uiiClusterPerFile;
                    }

	        	}
	        }
	        /*
	        else{
	        	//invalid file name
	        }
			*/
		}
            
	}///< the end of while(1) loop
    m_DCFSubDB.uwTotalFileCount = uwCurFileCount;
    error = AHC_DCF_DirClose(uiFileID);
                
    return AHC_TRUE;
}

static AHC_BOOL AIHC_DCF_ChangeFilCtl(void)
{
    UINT32 uiDelta, uiMaxDelta;
    DCF_FILE_NODE* psTempFileNode;
    DCF_FILE_NODE* psMaxFileNode;

    /*
    search the fil ctl file node.
    */    
    if(m_DCFSubDB.psLastFileNode->uwFileKey < m_ulMaxDcfFileInDir){
        m_DCFSubDB.psFileCtlFileNode = m_DCFSubDB.psLastFileNode;

    }else{

        psTempFileNode  = m_DCFSubDB.psRootFileNode;
        psMaxFileNode   = m_DCFSubDB.psRootFileNode;
        uiMaxDelta      = 0;
        uiDelta         = 0;
        
        while(psTempFileNode != NULL){
            
            if(psTempFileNode->psNext != NULL){
            
                uiDelta = psTempFileNode->psNext->uwFileKey - psTempFileNode->uwFileKey;
                
                if(uiDelta >= uiMaxDelta){
                    psMaxFileNode = psTempFileNode;
                    uiMaxDelta = uiDelta;
                }
            }
            
            psTempFileNode = psTempFileNode->psNext;
        }
        
        m_DCFSubDB.psFileCtlFileNode = psMaxFileNode;
    }
    return AHC_TRUE;

}

AHC_BOOL AIHC_DCF_MountSubDB(INT8*  pchRootDirName)
{

    UINT32              error;
    UINT32              uiDirLength;
    UINT32              uiDirID;
    INT8                chFullDirName[DCF_MAX_FILE_NAME_SIZE];
    
    #if 0
	printc("DCF MOUNT SUB S  : %x \r\n", m_ulDcfMemPool);
	#else
	printc("DCF MOUNT SUB S \n");
    #endif
    
    if ( m_bMountSubDCF == AHC_TRUE ){
        return AHC_FALSE;
    }

    /**	@brief	setup the name of root. default : SD:\\EMER .*/
    MEMSET(m_DCFSubDB.chRootDirName, DCF_RESET_VALUE, DCF_ROOT_NAME_LEN);
    STRCPY(m_DCFSubDB.chRootDirName, (INT8*)AIHC_GetMediaRootName());
    STRCAT(m_DCFSubDB.chRootDirName, pchRootDirName);
        
    //indicate the failure of DB initialization
    uiDirLength	= STRLEN(m_DCFSubDB.chRootDirName);
    
    MEMSET(chFullDirName, DCF_RESET_VALUE, sizeof(chFullDirName));
    MEMCPY(chFullDirName, m_DCFSubDB.chRootDirName, uiDirLength);
    
    error = AHC_DCF_DirOpen(chFullDirName, uiDirLength, &uiDirID);

    if( error ){
    
        AHC_DCF_DirCreate(chFullDirName, uiDirLength);	///< Create a new directory.
        
    }else{
    	
    	error = AHC_DCF_DirClose(uiDirID);
    	/**
    	@brief find all the dir node.
    	*/			
        AIHC_DCF_ParseSubFile(chFullDirName);
    }
    
    {

    UINT32 uiDelta, uiMaxDelta;
    DCF_FILE_NODE* psTempFileNode;
    DCF_FILE_NODE* psMaxFileNode;

    /*
    search the fil ctl file node.
    */    
    AIHC_DCF_ChangeFilCtl();
    
    
    /*
    search the kill file node.
    */
    if(m_DCFSubDB.psFileCtlFileNode == m_DCFSubDB.psLastFileNode){
        m_DCFSubDB.psKillFileNode = m_DCFSubDB.psRootFileNode;
        
    }else{
        psTempFileNode  = m_DCFSubDB.psRootFileNode;
        psMaxFileNode   = m_DCFSubDB.psRootFileNode;
        uiMaxDelta      = 0;
        uiDelta         = 0;
        
        while(psTempFileNode != NULL){
            
            if(psTempFileNode->psPrev != NULL){
            
                uiDelta = psTempFileNode->uwFileKey - m_DCFSubDB.psFileCtlFileNode->uwFileKey;
                
                if(uiDelta >= uiMaxDelta){
                    psMaxFileNode = psTempFileNode;
                    uiMaxDelta = uiDelta;
                }
            }
            
            psTempFileNode = psTempFileNode->psNext;
        }
        
        m_DCFSubDB.psKillFileNode = psMaxFileNode;
    }
    }
    
    m_bMountSubDCF = AHC_TRUE;
    #if 0
	printc("DCF MOUNT SUB E : %x\r\n", m_ulDcfMemPool);
	#else
	printc("DCF MOUNT SUB E \n");
    #endif
    return AHC_TRUE;
}


AHC_BOOL AIHC_DCF_UnMountSubDB(void)
{
	/**
	@brief	make sure the operation of DCF background task is done.
	
	*/
	printc("UnMount SUB DB S \r\n");

    if( m_bMountSubDCF == AHC_FALSE ){
        return AHC_FALSE;
    }
    
    MEMSET(&m_DCFSubDB, DCF_RESET_VALUE, sizeof(DCF_SUBDB));

    m_bMountSubDCF = AHC_FALSE;

	printc("UnMount SUB DB E \r\n");
    return AHC_TRUE;
}

AHC_BOOL AIHC_DCF_GetSubName(INT8 *FileName)
{

    UINT16 uwFileKey;
    //m_DCFSubDB.psFileCtlFileNode
    if(m_DCFSubDB.psRootFileNode == NULL){

		uwFileKey = MIN_DCF_FILE_KEYNUM;
		#if 0
		printc("DCF Sub Get 0x01 \n");
        #endif
	}else if(m_DCFSubDB.psFileCtlFileNode->uwFileKey >= m_ulMaxDcfFileInDir ){
	
        AIHC_DCF_ChangeFilCtl();

        if(m_DCFSubDB.psFileCtlFileNode->uwFileKey < m_ulMaxDcfFileInDir){

            uwFileKey = m_DCFSubDB.psFileCtlFileNode->uwFileKey + 1;
            #if 0
            printc("DCF Sub Get 0x02 \n");
            #endif

        }else{
            printc("DCF Error 0x0422\n");
            uwFileKey = MIN_DCF_FILE_KEYNUM;
        }

	}else{
	    #if 0
        printc("DCF Sub Get 0x03 \n");
        #endif
	    uwFileKey = m_DCFSubDB.psFileCtlFileNode->uwFileKey + 1;

	}


    AIHC_DCF_GetFileFullName(FileName, uwFileKey, (INT8 *)m_chSubFileFreeChar);
    
    printc("Sub New Name : %s, Key : %d \n", FileName, uwFileKey);
    
    return AHC_TRUE;
}

AHC_BOOL AIHC_DCF_AddSubFile(INT8 *pchFileName)
{

    /**
    @brief	maintian the counter of DB non-lock cluster.
    
    */
    INT8                chPathName[DCF_MAX_FILE_NAME_SIZE];
    UINT32              uiPathLen;
    
    AHC_FS_ATTRIBUTE	sFileAttribute;
    AHC_FS_FILETIME		sFileTime;
    UINT32				uiFileSize;
	UINT64				uiiClusterPerFile;
    DCF_FILE_NODE       *psNewFileNode;
   
    UINT16              uwFileKey;
    INT8                chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    UINT8               byFileType;
    
    MEMSET(chFileFreeChar, DCF_RESET_VALUE, sizeof(chFileFreeChar));
    


    if ( AIHC_DCF_GetFileKey(pchFileName, &uwFileKey , chFileFreeChar, &byFileType) == AHC_TRUE ) {
            
		// allocate a new memory to the new file node
        psNewFileNode = AIHC_DCF_AllocSubFileNode();

        while( psNewFileNode == NULL ){
        	/** @brief	not enough memory */

		    // kill the old file directly.
    	    INT8 chOldFileName[MAX_FILE_CHAR_LENGTH+1];
    	    
		    MEMSET(chPathName, DCF_RESET_VALUE, sizeof(chPathName));
    	    MEMSET(chOldFileName, DCF_RESET_VALUE, sizeof(chOldFileName));
    	
    	    m_DCFSubDB.psKillFileNode = m_DCFSubDB.psKillFileNode ? m_DCFSubDB.psKillFileNode : m_DCFSubDB.psRootFileNode;
    	    
    	    AIHC_DCF_GetFileFullName(chOldFileName, m_DCFSubDB.psKillFileNode->uwFileKey, m_DCFSubDB.psKillFileNode->chFileFreeChar);
        	/*
		    SD:\\EMER\\EMER0001
		    */
    	    STRCPY(chPathName, m_DCFSubDB.chRootDirName);
    	    STRCAT(chPathName, "\\");
    	    STRCAT(chPathName, chOldFileName);
    	    
            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
            {
            UINT32 i;
            
            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
        		STRCPY(m_chAuxiliaryFileName[i], chPathName);
        		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
        	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
            }
            
            }
            #endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
    	    
    	    /*
    	    SD:\\EMER\\EMER0001.AVI
    	    */
    	    STRCAT(chPathName, EXT_DOT);
    	    STRCAT(chPathName, m_DcfSupportFileType[m_DCFSubDB.psKillFileNode->byFileType]);
    	    
    	    
    	    AHC_DCF_FileRemove(chPathName, STRLEN(chPathName));
    	    
            #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        	{
            UINT32 i;
            
            for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
            }
            
            }
        	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
        	
    	    AIHC_DCF_RemoveSubFileNode(m_DCFSubDB.psRootFileNode);

		    //printc("Delete : %s \n", chPathName);
		    
		    psNewFileNode = AIHC_DCF_AllocSubFileNode();
        			
            
        }/** end of while. not enough memory */

        if( psNewFileNode != NULL ){

        	psNewFileNode->uwFileKey  = uwFileKey;
	        psNewFileNode->byFileType = byFileType;
	        MEMCPY(psNewFileNode->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byDirFreeCharNum);
	        
        	AIHC_DCF_AddSubFileNode(psNewFileNode);
        	
        }else{

            return AHC_FALSE;
        }
    }
    else
        return AHC_FALSE;


    
    MEMSET(chPathName , 0, sizeof(chPathName));
      
    STRCPY(chPathName,(INT8*)m_DCFSubDB.chRootDirName);
    STRCAT(chPathName,(INT8*)"\\");
    STRCAT(chPathName,(INT8*)pchFileName);
	
    uiPathLen = STRLEN(chPathName);
    AHC_DCF_FileDirGetInfo(chPathName, uiPathLen, &sFileAttribute, &sFileTime, &uiFileSize);    
    
	uiiClusterPerFile = (uiFileSize + m_uiBytesPerCluster - 1)/m_uiBytesPerCluster;
	
	m_DCFSubDB.uiCluster += uiiClusterPerFile;

	
	return AHC_TRUE;
    
}

AHC_BOOL AIHC_DCF_DeleteSubFile(INT8 *pchFileName)
{
    UINT16          uwRemoveFileKey;
    INT8            chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1];
    UINT8           byFileType;
    AHC_BOOL        bFound = AHC_FALSE;
    DCF_FILE_NODE   *psTempFileNode;

    MEMSET(chFileFreeChar, 0, sizeof(chFileFreeChar));
    
    if ( pchFileName != NULL ) {
        //Get key and free chars
        if ( AIHC_DCF_GetFileKey(pchFileName, &uwRemoveFileKey, chFileFreeChar, &byFileType) == AHC_FALSE )
            return AHC_FALSE;
    }else{
        return AHC_FALSE;
    }
    
    psTempFileNode = m_DCFSubDB.psRootFileNode;
    
    while(psTempFileNode != NULL){
        
        if( !(STRCMP(psTempFileNode->chFileFreeChar, chFileFreeChar)) &&
            (psTempFileNode->uwFileKey == uwRemoveFileKey) &&
            (psTempFileNode->byFileType == byFileType) ){
            bFound = AHC_TRUE;
            break;
        }
        
        psTempFileNode = psTempFileNode->psNext;
        
    }
    
    //Find node
    if ( bFound == AHC_TRUE ) {
    


		return AIHC_DCF_RemoveSubFileNode(psTempFileNode);
    }else{
    	return AHC_TRUE;
    }


    
    return AHC_TRUE;

}


#endif

#if 0
void __DCF_API__(){}
#endif

/*
Only Support the major DCF folder.
*/

AHC_BOOL AHC_DCF_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable)
{   
    switch(sType){
    
    case DCF_DB_TYPE_DB0_NORMAL:
        m_bEnableDCF[DCF_DB_TYPE_DB0_NORMAL] = bEnable;
        break;
        
    #if (DCF_DB_COUNT >= 2)
    case DCF_DB_TYPE_DB1_PARKING:
        m_bEnableDCF[DCF_DB_TYPE_DB1_PARKING] = bEnable;
        break;
    #endif ///< (DCF_DB_COUNT >= 2)
    
    #if (DCF_DB_COUNT >= 3)
    case DCF_DB_TYPE_DB2_EVENT:
        m_bEnableDCF[DCF_DB_TYPE_DB2_EVENT] = bEnable;
		 break;
    #endif///< (DCF_DB_COUNT >= 3)
    
    #if (DCF_DB_COUNT >= 4)
    case DCF_DB_TYPE_DB3_PHOTO:
        m_bEnableDCF[DCF_DB_TYPE_DB3_PHOTO] = bEnable;
        break;
    #endif
    
    default:
        printc(FG_RED("[DCF ERR] DB%d NONE \r\n"), sType);
        return AHC_FALSE;
        break;
    }
    
    return AHC_TRUE;
}

/*
Only Support the major DCF folder.
*/

AHC_BOOL AHC_DCF_GetDBStatus(DCF_DB_TYPE sType)
{   
    
    switch(sType){
    
    case DCF_DB_TYPE_DB0_NORMAL:
    #if (DCF_DB_COUNT >= 2)
    case DCF_DB_TYPE_DB1_PARKING:
    #endif ///< (DCF_DB_COUNT >= 2)
    #if (DCF_DB_COUNT >= 3)
    case DCF_DB_TYPE_DB2_EVENT:
    #endif///< (DCF_DB_COUNT >= 3)
    #if (DCF_DB_COUNT >= 4)
    case DCF_DB_TYPE_DB3_PHOTO:
    #endif
        return m_bEnableDCF[sType];
        break;
    default:
        printc("[DCF ERR] DB NONE \n");
        return AHC_FALSE;
        break;
    }
    
    return AHC_TRUE;
}

/**
WARNING:    This API change the database of DCF and the operation of DCF.
            This api only can be called after you finish all the DCF operation for other database.

*/
AHC_BOOL AHC_DCF_SelectDB(DCF_DB_TYPE sType)
{
    printc("Work DCF Type : %d \n", sType);
    
    m_sDBType = sType;
    //clean Info cache by Jerry 
    memset(&InfoCacheData, 0, sizeof(InfoCacheData));
    
    switch(sType){
    case DCF_DB_TYPE_DB0_NORMAL:
        m_uiDBIndex = 0;
        
        #if(DCF_SUB_DB == 1)
        m_bTurnOnSubDB = AHC_FALSE;
        #endif///< DCF_SUB_DB == 1
        
        break;
    #if (DCF_DB_COUNT >= 2)
    case DCF_DB_TYPE_DB1_PARKING:
        m_uiDBIndex = 1;
        
        #if(DCF_SUB_DB == 1)
        m_bTurnOnSubDB = AHC_FALSE;
        #endif///< DCF_SUB_DB == 1
        break;
    #endif ///< (DCF_DB_COUNT >= 2)
    
    #if (DCF_DB_COUNT >= 3)
    case DCF_DB_TYPE_DB2_EVENT:
        m_uiDBIndex = 2;
        
        #if(DCF_SUB_DB == 1)
        m_bTurnOnSubDB = AHC_FALSE;
        #endif///< DCF_SUB_DB == 1
        break;
    #endif///< (DCF_DB_COUNT >= 3)
    
    #if (DCF_DB_COUNT >= 4)
    case DCF_DB_TYPE_DB3_PHOTO:
        m_uiDBIndex = 3;
        
        #if(DCF_SUB_DB == 1)
        m_bTurnOnSubDB = AHC_FALSE;
        #endif///< DCF_SUB_DB == 1
        break;
    #endif
    
    #if(DCF_SUB_DB == 1)
    case DCF_DB_TYPE_SUB_DB:
        m_bTurnOnSubDB = AHC_TRUE;
    
        break;
    #endif
    
    default:
        printc("[DCF ERR] DB NONE \n");
        return AHC_FALSE;
        break;
    }
    
    return AHC_TRUE;
}

DCF_DB_TYPE AHC_DCF_GetDB(void)
{
    return m_sDBType;
}

AHC_BOOL AHC_DCF_WriteInfo(void)
{
    #if (DCF_DCFX == 1)
	UINT32	uiWriteCount;
	UINT32	uiTagCtl;
	UINT32	uiError;
	
	#if (DCF_DEBUG >= DCF_DEBUG_ALL)
	printc("Write DCFx file \r\n");
	#endif
	
	#if(defined(DEVICE_GPIO_2NDSD_PLUG))
	
	#if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
	if(AHC_IsSDInserted() == AHC_FALSE)
	#elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
	if(AHC_IsSDInserted() == AHC_FALSE && AHC_Is2ndSDInserted() == AHC_FALSE)
	#endif//TWOSD_WORK_MODEL
	
	#else
	if(AHC_IsSDInserted() == AHC_FALSE)
	#endif
	{
		/**
		@brief need to modified again.
		*/
		printc("DCF NO SD \r\n");
		return AHC_FALSE;
	}
	
	if (AHC_FALSE == AIHC_DCF_OpenDCFxFile(AHC_TRUE)) {
		printc("AIHC_DCF_OpenDCFxFile fail\r\n");
		return AHC_FALSE;
	}
	
	uiError = AHC_DCF_FileSeek(m_uiDCFxFileID, 0, AHC_FS_SEEK_SET);
	if(uiError){
		printc("Error 0 \r\n");
	
	}
	// DCFx
	uiError		= AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(DCFX_HEADER_PATTERN), 4, &uiWriteCount);
	if(uiError){
		printc("Error 1 \r\n");
	
	}
	// tag number
	uiTagCtl	= DCFX_TAG_NUMBER;
	uiError		= AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), 4, &uiWriteCount);
	if(uiError){
		printc("Error 2 \r\n");
	
	}
	// offset
	uiError		= AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(&m_sDCFxDBInfo), sizeof(DCFX_DB_INFO), &uiWriteCount);
	if(uiError){
		printc("Error 3 \r\n");
	
	}
	// check sum
	{
	INT8* chCheckSum = "XXXX";
	//uiTagCtl = DCFX_TAG_NUMBER;
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(chCheckSum), 4/*sizeof(uiTagCtl)*/, &uiWriteCount);
	}
	if(uiError){
		printc("Error 4 \r\n");
	
	}
	// root name
	uiTagCtl = DCFX_ROOTNAME_SIZE;

	//printc("root name size : %d \r\n", uiTagCtl);	
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), 4, &uiWriteCount);
	if(uiError){
		printc("Error 5 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)m_DcfDB[m_uiDBIndex].chRootName, DCFX_ROOTNAME_SIZE, &uiWriteCount);
	if(uiError){
		printc("Error 6 \r\n");
	
	}
	// kill key
	uiTagCtl = DCFX_KEY_SIZE;
	
	//printc("kill key size : %d \r\n", uiTagCtl);
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), 4, &uiWriteCount);
	if(uiError){
		printc("Error 7 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwKillDirKey), DCFX_KEY_SIZE, &uiWriteCount);
	if(uiError){
		printc("Error 8 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwKillFileKey), DCFX_KEY_SIZE, &uiWriteCount);
	if(uiError){
		printc("Error 9 \r\n");
	
	}
	// file ctl key
	uiTagCtl = DCFX_KEY_SIZE;
	
	//printc("file ctl key size : %d \r\n", uiTagCtl);
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), 4, &uiWriteCount);
	if(uiError){
		printc("Error 10 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwFileCtlDirKey), DCFX_KEY_SIZE, &uiWriteCount);
	if(uiError){
		printc("Error 11 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(&m_DcfDB[m_uiDBIndex].uwFileCtlFilekey), DCFX_KEY_SIZE, &uiWriteCount);
	if(uiError){
		printc("Error 12 \r\n");
	
	}
	// lock free char
	uiTagCtl = m_DcfDB[m_uiDBIndex].byFileFreeCharNum;

	//printc("lock free character size : %d \r\n", uiTagCtl);	
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), 4, &uiWriteCount);
	if(uiError){
		printc("Error 13 \r\n");
	
	}
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum, &uiWriteCount);
	if(uiError){
		printc("Error 14 \r\n");
	
	}
	// lock free char
	uiTagCtl = DCFX_DATA_SIZE;
	uiError = AHC_DCF_FileWrite(m_uiDCFxFileID, (UINT8*)(uiTagCtl), sizeof(uiTagCtl), &uiWriteCount);
	if(uiError){
		printc("Error 15 \r\n");
	
	}
	AIHC_DCF_OpenDCFxFile(AHC_FALSE);
	#else ///< (DCF_DCFX == 1)
	printc("DCFX Unsupported\n");
	#endif
	return AHC_TRUE;
}


/**
 @brief This API set the free characters of the DCF files and directories.

 This API set the free characters of the DCF files and directories.
 It also setup the supported file type.
 
 
 Parameters:
 @param[in] byDir       Select the command influences the file or directory.
 @param[in] byOp        Select the operations (DCF_OPEN_EXIST / DCF_CREATE / DCF_SET_ONLY / DCF_SET_ALLOWED).
 						the datatype is DCF_OP.
 @param[in] byChars     Array contains DCF characters.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[])
{
    UINT8   Ext[FILE_EXT_LENGTH + 1];
    UINT32  i,j,len;
    AHC_BOOL bResult = AHC_TRUE;
    
    AIHC_DCF_LOCKDB();
    
    if( ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE) || ( byChars == NULL )){
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }
 	
 	
    len = STRLEN((INT8*)byChars);
    
    switch(byOp){
    
    case DCF_SET_ALLOWED:
    {

    MEMSET(Ext, DCF_RESET_VALUE , sizeof(Ext));

    if(len >= FILE_EXT_LENGTH) {
    	/**
    	@brief setup the supported file type.
    	
    	*/
        //m_DcfDB.uiTotalAllowedFileCount = 0;
        
        /**
        @brief clear all the supproted file type.
        */
        for(i = 0 ; i < MAX_DCF_SUPPORT_FILE_TYPE ; i++) {
            m_DcfDB[m_uiDBIndex].chAllowedFileType[i] = 0;
        }
        
        j = 0;
        /**
        @brief parse the file type.
        */
        while(len >= FILE_EXT_LENGTH) {

            for( i = 0 ; i < FILE_EXT_LENGTH ; i++) {
                Ext[i] = byChars[j+i];
            }
			/**
			@brief do the mapping of supported file type and set up the allowed file type
			*/
            for( i = 0 ; i < MAX_DCF_SUPPORT_FILE_TYPE; i++) {

                if( STRCMP((INT8*)m_DcfSupportFileType[i], (INT8*)Ext) == 0 ) {

                    m_DcfDB[m_uiDBIndex].chAllowedFileType[i] = 1;

                    break;
                }
            }
            
            len -= FILE_EXT_LENGTH;
            
            if(len > 0)
                len -= 1;
                
            j+= (FILE_EXT_LENGTH + 1);
        }///< the while loop
    }
    }
    break;
    
    case DCF_SET_FREECHAR:
    {
        
    if( byDir ){
    
        if(len > m_DcfDB[m_uiDBIndex].byDirFreeCharNum){
            bResult = AHC_FALSE;

        }else{
        
	        for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byDirFreeCharNum ; i++) {
	            m_DcfDB[m_uiDBIndex].chDirFreeChar[i] = byChars[i];
	        }
        }
        
    }else{
    
        if(len > m_DcfDB[m_uiDBIndex].byFileFreeCharNum){
            bResult = AHC_FALSE;
        }else{
        
	        for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++){
	            m_DcfDB[m_uiDBIndex].chFileFreeChar[i] = byChars[i];
	        }
        }
    }
            
    }
    break;

    case DCF_SET_LOCKED_CHAR:
    {
    
    #if (DCF_DCFX == 1)
    if(len > m_DcfDB[m_uiDBIndex].byFileFreeCharNum) {
        bResult = AHC_FALSE;
    }else{    
	    for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++) {
	        m_chLockedFileFreeChar[i] = byChars[i];
	    }
	}
    #else ///< (DCF_DCFX == 1)
    printc("DCFX Unsupported\n");
    #endif ///< (DCF_DCFX == 1)
    }
    break;
    
    case DCF_SET_UNLOCKED_CHAR:
    {
    #if (DCF_DCFX == 1)
    if(len > m_DcfDB[m_uiDBIndex].byFileFreeCharNum) {
        bResult = AHC_FALSE;
    }else{
    
	    for(i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++) {
	        m_chUnLockedFileFreeChar[i] = byChars[i];
	    }
	}
    #else ///< (DCF_DCFX == 1)
    printc("DCFX Unsupported\n");
    #endif ///< (DCF_DCFX == 1)
    }
    break;
    
    default:
    break;
    }
    
	AIHC_DCF_UNLOCKDB();
	//clean Info cache by Jerry 
    memset(&InfoCacheData, 0, sizeof(InfoCacheData));

	return bResult;
}

AHC_BOOL AHC_DCF_GetAllowedChar(INT8* pbyChar, UINT32 uiLength)
{
	UINT32 i;
	
	AHC_BOOL bFirst = AHC_FALSE;
	
	MEMSET(pbyChar, 0, uiLength);
	
	if(uiLength < MAX_DCF_SUPPORT_FILE_TYPE*4){
		return AHC_FALSE;	
	}
	
	for(i = 0; i < MAX_DCF_SUPPORT_FILE_TYPE; i++){
	
		if(m_DcfDB[m_uiDBIndex].chAllowedFileType[i] == 1){
			
			if(bFirst == AHC_TRUE){
				STRCAT(pbyChar, ",");
				pbyChar++;
			
			}
			
			MEMCPY(pbyChar, m_DcfSupportFileType[i], 3);
			
			bFirst = AHC_TRUE;
			
			pbyChar += 3;
		}
	
	}
	
	return AHC_TRUE;
}
/**
@brief This API set the DCF numbers used for DCF directories.
 
And the next file key will be the max file key plus 1.
 
1. find the dir with uwDirKey.
 

Parameters:
@param[in] wDirNum     Directory number, upon DCF rule.
 
@retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_SwitchKey(UINT16 uwDirKey)
{
    DCF_DIR_NODE    *psDirNode;
    
    AIHC_DCF_LOCKDB();
    
    if( m_bMountDCF[m_uiDBIndex] == AHC_FALSE){
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }
    
    if( uwDirKey ){
        if ( ( uwDirKey < MIN_DCF_DIR_KEYNUM ) || (uwDirKey > MAX_DCF_DIR_KEYNUM) ){
        	AIHC_DCF_UNLOCKDB();
            return AHC_FALSE;	///< the number of dir overflow
        }
    }

    if( uwDirKey ){

        if ( AIHC_DCF_FindDir(NULL, uwDirKey, &psDirNode) == AHC_TRUE) {
			/**
			@brief	dir node already exits
			*/
            if( psDirNode->uwMaxFileKey  >= MAX_DCF_FILE_KEYNUM ) {
	            AIHC_DCF_UNLOCKDB();
                return AHC_FALSE;
            }else{
            	m_DcfDB[m_uiDBIndex].psFileCtlDirNode = psDirNode;
            }
        }
        else {
        	/**
        	@brief add one new dir node and add one dir in storage.
        	*/
       	    INT8	chFullDirName[DCF_MAX_FILE_NAME_SIZE];
       	    INT8	chDirName[MAX_DIR_CHAR_LENGTH + 1];
       	    UINT32	uiDirLength;
		    
		    MEMSET(chFullDirName, DCF_RESET_VALUE, sizeof(chFullDirName));
		    MEMSET(chDirName, DCF_RESET_VALUE, sizeof(chDirName));

		    STRCPY(chFullDirName, m_DcfDB[m_uiDBIndex].chRootName);
		    STRCAT(chFullDirName, "\\");

		    AIHC_DCF_GetDirFullName(chDirName, uwDirKey, m_DcfDB[m_uiDBIndex].chDirFreeChar);
			STRCAT(chFullDirName, chDirName);

		    uiDirLength	= STRLEN(chFullDirName);
		    	    
		    if(AHC_DCF_DirCreate(chFullDirName, uiDirLength) == AHC_ERR_NONE){
		    
			    AIHC_DCF_AddDirNode(chDirName);
			    AIHC_DCF_FindDir(NULL, uwDirKey, &m_DcfDB[m_uiDBIndex].psFileCtlDirNode);
		    }else{
		    	AIHC_DCF_UNLOCKDB();
		    	return AHC_FALSE;
		    }
        }
    }
    AIHC_DCF_UNLOCKDB();
	return AHC_TRUE;
}

/**
 @brief This API get the max DCF objects specific by AHC_SetFileType() for operations (delete, lock..etc).

 
 Parameters:
 @param[out] pwImgIndex The pointer to returned object index.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_GetTotalFileCount(UINT32 *puiImgIndex)
{
	AHC_BOOL bResult;
	
	AIHC_DCF_LOCKDB();
	#if(DCF_SUB_DB == 1)
    if(m_bTurnOnSubDB == AHC_TRUE){
        if ( m_bMountSubDCF == AHC_FALSE)
        {
            // Clear the value in advance.
            *puiImgIndex = 0;
            bResult = AHC_FALSE;
        }else{

          	*puiImgIndex = m_DCFSubDB.uwTotalFileCount;

        	
        	bResult = AHC_TRUE;
        }
    }else
    #endif///< DCF_SUB_DB == 1
    {
        if ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE)
        {
            // Clear the value in advance.
            *puiImgIndex = 0;
            bResult = AHC_FALSE;
        }else{

          	*puiImgIndex = AIHC_DCF_GetTotalAllowedFileCount();

        	
        	bResult = AHC_TRUE;
        }
    
    }
    AIHC_DCF_UNLOCKDB();
	
	return bResult;
}

/**
 @brief This API set the index of current DCF object specific by AHC_SetFileType() for operations (delete, lock..etc).

 
 Parameters:
 @param[in] wImgIndex   The assigned object index.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_SetCurrentIndex(UINT32 uiImgIndex)
{
	AHC_BOOL	bResult;
	UINT32		uiTotalAllowedFileCount;
	
	AIHC_DCF_LOCKDB();
	
	#if(DCF_SUB_DB == 1)
	if(m_bTurnOnSubDB == AHC_TRUE){
	
        if ( m_bMountSubDCF == AHC_FALSE){
            bResult = AHC_FALSE;
        
        }else{
    	    uiTotalAllowedFileCount = m_DCFSubDB.uwTotalFileCount;
    	    
    	    if ( uiImgIndex >= uiTotalAllowedFileCount ) {
    	        uiImgIndex = uiTotalAllowedFileCount - 1;
    	    }
    	 
    	    m_DCFSubDB.uiBrowserIndex = uiImgIndex;
    	    
    	    bResult = AHC_TRUE;
        }
    }else
    #endif///< DCF_SUB_DB == 1
    {
        if ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE ){
            bResult = AHC_FALSE;
        
        }else{
    	    uiTotalAllowedFileCount = AIHC_DCF_GetTotalAllowedFileCount();
    	    
    	    if ( uiImgIndex >= uiTotalAllowedFileCount ) {
    	        uiImgIndex = uiTotalAllowedFileCount - 1;
    	    }
    	 
    	    m_DcfDB[m_uiDBIndex].uiBrowserIndex = uiImgIndex;
    	    
    	    bResult = AHC_TRUE;
        }
    
    
    }
    AIHC_DCF_UNLOCKDB();
    
	return bResult;
}

/**
 @brief This API get the index of current DCF object specific by AHC_SetFileType() for operations (delete, lock..etc).

 This API get the index of current DCF object specific by AHC_SetFileType() for operations (delete, lock..etc).
 
 Parameters:
 @param[out] pwImgIndex The pointer to returned object index.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_GetCurrentIndex(UINT32 *puiImgIndex)
{
	AHC_BOOL bResult;
	
    AIHC_DCF_LOCKDB();
    
    #if(DCF_SUB_DB == 1)
    if(m_bTurnOnSubDB == AHC_TRUE){
        if( m_bMountSubDCF == AHC_FALSE)
        {
            *puiImgIndex  = 0;
            bResult = AHC_FALSE;
        }else{
            
        	*puiImgIndex = m_DCFSubDB.uiBrowserIndex;
        	bResult = AHC_TRUE;
        }
    }else
    #endif///<DCF_SUB_DB == 1
    {
        if( m_bMountDCF[m_uiDBIndex] == AHC_FALSE )
        {
            *puiImgIndex  = 0;
            bResult = AHC_FALSE;
        }else{
            
        	*puiImgIndex = m_DcfDB[m_uiDBIndex].uiBrowserIndex;
        	bResult = AHC_TRUE;
        }
    }
    
    AIHC_DCF_UNLOCKDB();
    
	return bResult;
}
/**
@brief	give the dir name(100__DSC) and file name(MOV_0001.AVI) and return the value of index.

		index: 0~n
*/

AHC_BOOL AHC_DCF_GetIndexbyName(	INT8 *pchDirName,
							INT8 *pchFileName, 
							UINT32 *puiIndex)
{
    #if(DCF_SUB_DB == 1)
	if(m_bTurnOnSubDB == AHC_TRUE){
    	
    	UINT16 uwFileKey;
    	UINT32 uiIndex;
    	INT8 chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER + 1 ];
    	UINT8 byFileType;
    	DCF_FILE_NODE *psTempFileNode;
    	AHC_BOOL bFound = AHC_FALSE;
    	
    	if(AIHC_DCF_GetFileKey(pchFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_FALSE){
      		return AHC_FALSE;
    	}
    	
    	uiIndex = 0;
    	psTempFileNode = m_DCFSubDB.psRootFileNode;
    	
    	while(psTempFileNode != NULL){
    	
    	    if( !(STRCMP(psTempFileNode->chFileFreeChar, chFileFreeChar)) && 
    	        (psTempFileNode->uwFileKey == uwFileKey) &&
    	        (psTempFileNode->byFileType == byFileType) ){
    	            bFound = AHC_TRUE;
    	            break;
            }
            psTempFileNode = psTempFileNode->psNext;
            uiIndex++;
    	}
        
        if(bFound == AHC_TRUE){
            *puiIndex = uiIndex;
            return AHC_TRUE;
        }else{
            *puiIndex = 0;
            return AHC_FALSE;
        }
        
	}else
	#endif///< DCF_SUB_DB == 1
	{
	    return AIHC_DCF_GetIndex(pchDirName, pchFileName,  puiIndex);
	}

	return AHC_TRUE;
}
/**
 @brief Get DCF information

 Get the information of the selected DCF object.
 
 WARNING:	the browser mode use this API with the index 0~n.
 			0 => the first object.
 
 Parameters:
 @param[in]  wIndex         The index of query DCF object.
 @param[out] DCF_INFO       The information of the selected DCF object.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_GetInfobyIndex(UINT32 uiIndex, DCF_INFO *Info)
{
    #if(DCF_SUB_DB == 1)
    if(m_bTurnOnSubDB == AHC_TRUE){

    	
    	UINT32 uiFileIndex;
    	DCF_FILE_NODE *psTempFileNode;
    	AHC_BOOL bFound = AHC_FALSE;
        UINT32              i;

        UINT32              uiFileSize;
        UINT32              uiDirLength;
        INT8                TempString[DCF_MAX_FILE_NAME_SIZE];
        AHC_FS_ATTRIBUTE	attribute;
        AHC_FS_FILETIME		FileTimeStru;
    	
    	
    	uiFileIndex = 0;
    	psTempFileNode = m_DCFSubDB.psRootFileNode;
    	
    	while(psTempFileNode != NULL){
    	
    	    if( uiIndex == uiFileIndex ){
    	            bFound = AHC_TRUE;
    	            break;
            }
            psTempFileNode = psTempFileNode->psNext;
            uiFileIndex++;
    	}
        
        
        if(bFound == AHC_TRUE)
        {
            Info->uwDirKey = 0;
            MEMSET(Info->DirFreeChar, 0, m_DcfDB[m_uiDBIndex].byDirCharLength + 1);

            for( i = 0 ; i < m_DcfDB[m_uiDBIndex].byFileFreeCharNum ; i++ ) {
                Info->FileFreeChar[i] = psTempFileNode->chFileFreeChar[i];
            }
            
            Info->FileType = psTempFileNode->byFileType;

            
            STRCPY(Info->FileName, m_DCFSubDB.chRootDirName);
            STRCAT(Info->FileName, "\\");
            
            MEMSET(TempString, 0, sizeof(TempString));
            AIHC_DCF_GetFileFullName(TempString, psTempFileNode->uwFileKey, (INT8*)Info->FileFreeChar);
            STRCAT(Info->FileName, TempString);
            
            STRCAT(Info->FileName, EXT_DOT);
            STRCAT(Info->FileName, m_DcfSupportFileType[Info->FileType]);

            uiDirLength = STRLEN(Info->FileName);

            uiFileSize = 0;
            
            AHC_DCF_FileDirGetInfo(Info->FileName, uiDirLength, &attribute, &FileTimeStru, &uiFileSize);
            
            Info->uiFileSize = uiFileSize;
            Info->uwDirKey   = 0;
            Info->uwFileKey  = psTempFileNode->uwFileKey;
            
            if( attribute & AHC_FS_ATTR_READ_ONLY){
                Info->bReadOnly  = AHC_TRUE;
            }else{
                Info->bReadOnly  = AHC_FALSE;
            }
            
            #if (DCF_DCFX == 1)
            if( AIHC_DCF_WhichIsBoss((INT8*)Info->FileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL ){
            	Info->bCharLock = AHC_TRUE;
            }else
            #endif
            {
            	Info->bCharLock = AHC_FALSE;
            }
        	
        	
            Info->uwYear    = FileTimeStru.usYear;
            Info->uwMonth   = FileTimeStru.usMonth;
            Info->uwDay     = FileTimeStru.usDay;
            Info->uwHour    = FileTimeStru.usHour;
            Info->uwMinute  = FileTimeStru.usMinute;
            Info->uwSecond  = FileTimeStru.usSecond;
            
            return AHC_TRUE;

        }else{
            return AHC_FALSE;
        }

    }else
    #endif//< DCF_SUB_DB == 1
    {
    
	    return AIHC_DCF_GetInfo(uiIndex, Info);
	}
	
	return AHC_TRUE;
}

/**
 @brief This API get the DCF database of current mounted storage.

 This API get the DCF database of current mounted storage.
 
 Parameters:
 @param[out]  pDcfAttrib    Array of files indexes.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_GetDBInfo(DCF_DB_ATTRIB *pDcfAttrib)
{
    UINT32 i, uiMaxCount;
	AHC_BOOL bResult;
	
    AIHC_DCF_LOCKDB();

    if ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE ){
        bResult = AHC_FALSE;
    }else{
	    pDcfAttrib->uiFileCount = AIHC_DCF_GetTotalFileCount();//m_DcfDB.uiTotalFileCount;
	    pDcfAttrib->uiDirCount  = m_DcfDB[m_uiDBIndex].uiCurDirCountInDB;
	    
	    uiMaxCount = MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1;
	    
	    for( i = 0 ; i < uiMaxCount ; i++ ) {
	        if( m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[i] != DCF_INVALID_NUMBER_16 ) {
	            pDcfAttrib->uwDirKeyList[i] = MIN_DCF_DIR_KEYNUM + i;
	        }else{
	        	pDcfAttrib->uwDirKeyList[i] = 0;
	        }
	    }
	    
	    bResult = AHC_TRUE;
    }
    
    AIHC_DCF_UNLOCKDB();
    
	return bResult;
}

AHC_BOOL AHC_DCF_SetCyclicDeletedMask(DCF_FILE_PROTECT sType)
{
	m_sCyclicDeletedMask = sType;

	return AHC_TRUE;
}

AHC_BOOL AHC_DCF_GetCyclicDeletedMask(DCF_FILE_PROTECT* sType)
{
	*sType = m_sCyclicDeletedMask;

	return AHC_TRUE;
}

AHC_BOOL AHC_DCF_SetFileDeletedMask(DCF_FILE_PROTECT sType)
{
	m_sFileDeletedMask = sType;

	return AHC_TRUE;
}

AHC_BOOL AHC_DCF_GetFileDeletedMask(DCF_FILE_PROTECT* sType)
{

	*sType = m_sFileDeletedMask;
	return AHC_TRUE;
}

/**
@brief	delete file according to the m_DcfDB.uwKillDirKey and m_DcfDB.uwKillFilekey.

@param[out]	uiSize: return the size of deleted file 
		
*/
AHC_BOOL AHC_DCF_DeleteCyclicFile(UINT32* uiSize)
{
	UINT32		uiError = AHC_FALSE;
	#if (DCF_DCFX == 1)
	AHC_BOOL	bDCFxDelete = AHC_FALSE;
    #endif
	
	AIHC_DCF_LOCKDB();
	
	if( m_bMountDCF[m_uiDBIndex] == AHC_FALSE ){
		AIHC_DCF_UNLOCKDB();
		return AHC_FALSE;
	}
	
	#if 0
	printc("ReadOnlyRegionCluster : %d \r\n", m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster);
	printc("DCFxRegionCluster     : %d \r\n", m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster);
	printc("NonLockRegionCluster  : %d \r\n", m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster);
	#endif
	
	#if (DCF_DCFX == 1)
	if((m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster + m_DcfDB[m_uiDBIndex].uiReadOnlyRegionCluster) > m_uiDCFxBoundary){
		/**
		@brief	
		*/
		if(m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster > 0){
			// check the golden page or not 
			bDCFxDelete = AHC_TRUE;

		}else if(m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster > 0){
			bDCFxDelete = AHC_FALSE;
			
		}

	}else{
	
		if(m_DcfDB[m_uiDBIndex].uiNonLockRegionCluster > 0){
			bDCFxDelete = AHC_FALSE;
		}else if(m_DcfDB[m_uiDBIndex].uiDCFxRegionCluster > 0){
			bDCFxDelete = AHC_TRUE;
		}	
	}
	#endif///< (DCF_DCFX == 1)
	
	#if (DCF_DCFX == 1)
	if(bDCFxDelete == AHC_TRUE){
		UINT8* pbyBufAddr;
		
		
		AIHC_DCF_LOCKPAGE();
		/**
		@brief	check the status of the golden page. 
		*/
		if(AIHC_DCF_CheckGoldenPageStatus() == AHC_FALSE){

			UINT32 uiIndex;
			#if 0
			printc("GP EMPTY \r\n");
			printc("m_sPageCtl.uiPageIndex : %d \r\n", m_sPageCtl.uiPageIndex);
			printc("m_sPageCtl.uiPageTotalCount : %d \r\n", m_sPageCtl.uiPageTotalCount);
			printc("m_sPageCtl.uiSortTotalCount : %d \r\n", m_sPageCtl.uiSortTotalCount);
			printc("m_sPageCtl.uiWritedPageCount : %d \r\n", m_sPageCtl.uiWritedPageCount);
			#endif
			
			if(AIHC_DCF_GetGlodenPageIndex(&uiIndex, AHC_TRUE) == AHC_TRUE){
				/**
				@brief	get a golden page which is filled with sorted data.
				*/
				//printc("GET ONE GP : %d \r\n", m_uiGPWorkIndex);
				m_uiGPWorkIndex = uiIndex;
				pbyBufAddr = m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;
			}else{
				/**
				@brief	no golden page is filled with sorted data.
						get an index to merge a new golden page which is filled sorted data.
				
				*/
				//printc("No GP \r\n");
				
				if(m_sPageCtl.uiPageIndex < m_sPageCtl.uiSortTotalCount){
					//printc("Sort old page : %d  %d \r\n", m_sPageCtl.uiPageIndex, m_uiGPWorkIndex);
					AIHC_DCF_GetGlodenPageIndex(&uiIndex, AHC_FALSE);
					AIHC_DCF_SortGoldenPage(uiIndex);
					m_uiGPWorkIndex = uiIndex;
					pbyBufAddr = m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;				

				}else{
					if( (m_sPageCtl.uiPageTotalCount - 1) == m_sPageCtl.uiPageIndex){
						//printc("DELETE TEMP : %d \r\n", m_sPageCtl.uiPageIndex);
						/**
						@brief	the data of temp buffer is not writen to SD Card
						*/
						pbyBufAddr = m_pbyDCFxTempBuffer;
						
					}else{
						
						if(m_sPageCtl.uiPageIndex >= m_sPageCtl.uiPageTotalCount){
							printc("DCF PAGE ERROR 1 \r\n");
							return AHC_FALSE;
						}
						
						if(AIHC_DCF_GetGlodenPageIndex(&uiIndex, AHC_FALSE) == AHC_FALSE){
							printc("DCF PAGE ERROR 2 \r\n");
							AIHC_DCF_UNLOCKPAGE();
							AIHC_DCF_UNLOCKDB();
							return AHC_FALSE;
						}
						//printc("LOAD PAGE : %d %d \r\n", m_sPageCtl.uiPageIndex, m_uiGPWorkIndex);
						m_uiGPWorkIndex = uiIndex;
						pbyBufAddr = m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;
						AIHC_DCF_LoadDCFxPage(m_sPageCtl.uiPageIndex, pbyBufAddr);
						m_sPageCtl.uiPageIndex++;
					
					}		
				}

			}

		}else{
			//printc("FILLED \r\n");
			pbyBufAddr = m_GoldenPage[m_uiGPWorkIndex].pbyBuffer;
		
		}
		
		uiError = AIHC_DCF_DeleteDCFxFile(pbyBufAddr, uiSize);
		
		AIHC_DCF_UNLOCKPAGE();

	}else
	#endif///< (DCF_DCFX == 1)
	{
	
		
		if((0 == m_DcfDB[m_uiDBIndex].uwKillDirKey) || (0 == m_DcfDB[m_uiDBIndex].uwKillFileKey) ){
		
			if(AIHC_DCF_FindKillKey() == AHC_FALSE){
				printc("DCF Find Kill Key Fail \r\n");
				AIHC_DCF_UNLOCKDB();
				return AHC_FALSE;
			}
		}
		//printc("S D 2 \r\n");
		
		uiError = AIHC_DCF_DeleteCyclicFile(uiSize);
		//printc("S D 3 \r\n");

	}
    
	//clean Info cache by Jerry 
    memset(&InfoCacheData, 0, sizeof(InfoCacheData));
	AIHC_DCF_UNLOCKDB();

	return uiError;

}

/**
@brief	

@param[in]	uiSize: the size which you expect. unit is byte.
*/
AHC_BOOL AHC_DCF_DeleteCyclicFilebySize(UINT64 uiSize)
{
	UINT64 uiSizeSum = 0;
	UINT32 uiFileSize;
	UINT32 uiIndex = 0;
	UINT32 uiFileSum = AIHC_DCF_GetTotalFileCount();
	AHC_BOOL bResult = AHC_TRUE;
	
	while(uiSizeSum < uiSize){
	
		if(AHC_DCF_DeleteCyclicFile(&uiFileSize) == AHC_TRUE){
			uiSizeSum += uiFileSize;
			uiIndex++;
			
		}else{
			printc("DCF Error 0x3 \r\n");
			bResult = AHC_FALSE;
			break;

		}
		
		if(uiIndex > uiFileSum){
			printc("DCF Error 0x31, uiIndex: %d, uiFileSum: %d\r\n", uiIndex, uiFileSum);
			bResult = AHC_FALSE;
			break;
		
		}
	}
	
	#if (DCF_DEBUG >= DCF_DEBUG_ERR)
	printc("Cyclic Deletion : %d \r\n", uiSizeSum);
	#endif
	return bResult;
}
/**
 @brief This API executes file operations which are relevant to file/DIR/DCF objects.

 This API executes file operations which are relevant to file/DIR/DCF objects. 
 The blocking or non-blocking is selectable by setting PARAM_ID_FO_ASYNC.
 
 Parameters:
 @param[in]  pName          file name.
 @param[in]  byOperation    Indicates the operation.
 @param[in ] pDestPath      destination path name.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DCF_FileOperation(UINT8 *pPathName, 
                           UINT8 *pFileName, 
                           UINT8 byOperation, 
                           UINT8 *pDestPath, 
                           UINT8 *pDestFileName)
{
    UINT32              error = MMP_ERR_NONE;

    UINT16              uwFileKey; 
    UINT16              uwDirKey;
    UINT8               byFileType;
    
    INT8                chSrcFileName[DCF_MAX_FILE_NAME_SIZE];
    INT8                chDestFileName[DCF_MAX_FILE_NAME_SIZE];
    
    AHC_FS_ATTRIBUTE	sFileAttribute;
    UINT32              FileNameSize;
    UINT32              uiRootDirLen;
    UINT32              uiSrcDirLen;
    UINT32              uiDestDirLen;

    AIHC_DCF_LOCKDB();
    AIHC_DCF_LOCKPAGE();
    
    if ( m_bMountDCF[m_uiDBIndex] == AHC_FALSE ){
    	AIHC_DCF_UNLOCKPAGE();
    	AIHC_DCF_UNLOCKDB();
        return AHC_FALSE;
    }
    
    MEMSET(chSrcFileName , 0, sizeof(chSrcFileName));
    MEMSET(chDestFileName, 0, sizeof(chDestFileName));

    STRCPY(chSrcFileName,(INT8*)pPathName);
    STRCAT(chSrcFileName,(INT8*)"\\");
    STRCAT(chSrcFileName,(INT8*)pFileName);
    
    switch(byOperation){
    
    case DCF_FILE_READ_ONLY_ALL_CAM:
    {
	    AHC_FS_FILETIME	sFileTime;
	    UINT32			uiFileSize;
		AHC_BOOL		bValid = AHC_FALSE;
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];
		
        FileNameSize	= STRLEN(chSrcFileName);
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
        
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if(AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE){
            	bValid = AHC_TRUE;
            
            }
        }
        
        AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize);

        if(sFileAttribute & AHC_FS_ATTR_READ_ONLY){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_TRUE;
        }
        
		if(bValid == AHC_TRUE){
			AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
										&sFileAttribute, 
										uiFileSize,
										uwDirKey, 
										AHC_FALSE);
		}
		
        sFileAttribute |= AHC_FS_ATTR_READ_ONLY;
        
        AHC_DCF_FileDirSetAttribute(chSrcFileName, FileNameSize, sFileAttribute);
        
        if(bValid == AHC_TRUE){
            #if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT!=LOCK_FILE_STOP)
            m_ulLockFileNum++;
            #endif

			AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
										&sFileAttribute, 
										uiFileSize,
										uwDirKey, 
										AHC_TRUE);
		}
    }
	break;
    
    case DCF_FILE_NON_READ_ONLY_ALL_CAM:
    {
    
	    AHC_FS_FILETIME	sFileTime;
	    UINT32			uiFileSize;
		AHC_BOOL		bValid = AHC_FALSE;
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];
		
        FileNameSize = STRLEN(chSrcFileName);
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
        
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if(AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE){
            	bValid = AHC_TRUE;
            
            }
        }
        
        AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize);

        if(!(sFileAttribute & AHC_FS_ATTR_READ_ONLY)){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_TRUE;
        }

#if (LIMIT_MAX_LOCK_FILE_NUM)
		{
			extern UINT32 m_ulLockFileNum;
			
			if(m_ulLockFileNum>0) {
				m_ulLockFileNum--;
		    }
		}
#endif	

        if(bValid == AHC_TRUE){
			AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
										&sFileAttribute, 
										uiFileSize,
										uwDirKey, 
										AHC_FALSE);
		}
		
        sFileAttribute &= ~AHC_FS_ATTR_READ_ONLY;
        
        AHC_DCF_FileDirSetAttribute(chSrcFileName, FileNameSize, sFileAttribute);
        
        if(bValid == AHC_TRUE){
			AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
										&sFileAttribute, 
										uiFileSize, 
										uwDirKey,
										AHC_TRUE);
		}
	}
	break;
        
    case DCF_FILE_COPY:
	{
	    INT8 chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+ 1];
	    INT8 chFileFreeChar[MAX_FILE_CHAR_LENGTH + 1];
    	/**
    	@brief	copy the file from the position of source to the position of destination.
    			
    	*/
        STRCPY(chDestFileName, (INT8*)pDestPath);
        STRCAT(chDestFileName, (INT8*)"\\");
        STRCAT(chDestFileName, (INT8*)pDestFileName);
        
        error = AHC_DCF_FileCopy(chSrcFileName, STRLEN(chSrcFileName), chDestFileName, STRLEN(chDestFileName));

        if ( !error ) {
        
            uiRootDirLen = STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
            uiSrcDirLen  = STRLEN((INT8*)pPathName);
            uiDestDirLen = STRLEN((INT8*)pDestPath);
    
            /**
            @brief add the new file to DB or not.
            */
            if ( uiDestDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
                if ( AIHC_DCF_GetDirKey((INT8*)(pDestPath + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE ) {
                    //the file is a DCF obj        
                    if ( AIHC_DCF_GetFileKey((INT8*)pDestFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE ) {
                    
                    	DCF_DIR_NODE	*psDir;
                    	UINT8			byOldFileType;
                    	
                    	if(AIHC_DCF_FindDir(NULL, uwDirKey, &psDir) == AHC_TRUE){
                    		/**
                    		@brief	mount the dir node in order to get the file map.
                    				update the counter of DB.
                    		*/
	        	            AIHC_DCF_MountDirNode(	psDir, 
													NULL, 
													0,
													0,
													DCF_DIR_MOUNT_TYPE_UNMOUNT);
													
							if(AIHC_DCF_CompareFileMap(uwFileKey, byFileType, &byOldFileType) == AHC_TRUE)				
			    				AIHC_DCF_UpdateDBInfo(psDir, uwFileKey, byFileType, byOldFileType, AHC_FALSE, AHC_FALSE);
			    				
                    	}else{
                    		/**
                    		@brief	add one new dir.
                    		*/
                    		INT8 chDirName[MAX_DIR_CHAR_LENGTH + 1];
                    		
                    		MEMSET(chDirName , 0, sizeof(chDirName));
                    		
                    		AIHC_DCF_GetDirFullName(chDirName, uwDirKey, chDirFreeChar);
                    		AIHC_DCF_AddDirNode(chDirName);
                    		AIHC_DCF_AddFile(uwDirKey, (INT8*)pDestFileName);
                    		{
                    		// control the counter of DCFx region
                    		
                    		
                    		}
                    	}
                    }
                }
            }
        }else{
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
        }
        //clean Info cache by Jerry
        memset(&InfoCacheData, 0, sizeof(InfoCacheData));
    }
	break;
    
    case DCF_FILE_CHAR_LOCK_ALL_CAM:
    {
        #if (DCF_DCFX == 1)
		/**
		@brief	rename file => SM:\\DCIM\100__DSC\MOV_0001.AVI --> SM:\\DCIM\100__DSC\GLOK0001.AVI		

		*/
       	DCF_DIR_NODE	*psDir;
    	DCF_FILE_NODE	*psFile;
    	INT8 			chNodeFileName[MAX_FILE_CHAR_LENGTH+1];
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+1];
	    INT8			chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
	    AHC_FS_FILETIME sFileTime;
	    UINT32			uiFileSize;

		/**
		@brief	confirm the attribute of file.
		*/
        FileNameSize = STRLEN(chSrcFileName);

        if(AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize) != AHC_ERR_NONE){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
		}
		/**
		@brief	compare the dir 
		*/
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
		
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if( (AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE) &&
            	(AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE) ){
            	
            	if(AIHC_DCF_WhichIsBoss(chFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
            		// already locked.
            		AIHC_DCF_UNLOCKPAGE();
            		AIHC_DCF_UNLOCKDB();
            		return AHC_TRUE;
            	}
            	/**
            	@brief	valid file name.
            	*/
            	
            	AIHC_DCF_FindDir(NULL, uwDirKey, &psDir);
            	
            	if(psDir != NULL){

					if(psDir->byMountMode != DCF_DIR_MOUNT_TYPE_ALL){
						AIHC_DCF_MountDirNode(	psDir, 
												NULL, 
												0xFFFF,
												uwFileKey,
												DCF_DIR_MOUNT_TYPE_KEY);
					}
					
            		AIHC_DCF_FindFileNode(psDir, NULL, uwFileKey, &psFile);
            		MEMSET(chNodeFileName , 0, sizeof(chNodeFileName));
            		AIHC_DCF_GetFileFullName(chNodeFileName, psFile->uwFileKey, psFile->chFileFreeChar);
            		
                	if(AIHC_DCF_WhichIsBoss((INT8*)pFileName, chNodeFileName, m_DcfDB[m_uiDBIndex].byFileCharLength) == DCF_BOSS_EQUAL){
                		/**
                		@brief	its the target file.
                		*/
           				MEMCPY(psFile->chFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);

                	}else{
                		/**
                		@brief	its a neighbor or not.
                		*/
                		//printc("neighbor \r\n");
                		while(psFile->psNeighbor != NULL){
                		
                			psFile = psFile->psNeighbor;
                			if( (AIHC_DCF_WhichIsBoss(psFile->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL) &&
                				(byFileType == psFile->byFileType) ){
                				break;
                			}
                		}
                		
                		if(psFile != NULL){
                			/**
                			@brief its neighbor.
                			*/
                			MEMCPY(psFile->chFileFreeChar, m_chLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
                		}else{
                			AIHC_DCF_UNLOCKPAGE();
                			AIHC_DCF_UNLOCKDB();
                			return AHC_FALSE;
                		}
                		
                	}
            	}else{
            		/**
            		@brief no dir node
            		*/
            		AIHC_DCF_UNLOCKPAGE();
            		AIHC_DCF_UNLOCKDB();
            		return AHC_FALSE;
            	}

            }else{
            	AIHC_DCF_UNLOCKPAGE();
            	AIHC_DCF_UNLOCKDB();
            	return AHC_FALSE;
            }///< valid dir name and valid file name
            
        }else{
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
        
        }///< valid dir name length
		
		
		/**
		@brief	rename
		*/
		AIHC_DCF_GetFileFullName(chNodeFileName, uwFileKey, m_chLockedFileFreeChar);
		
        STRCPY(chDestFileName, (INT8*)pPathName);
        STRCAT(chDestFileName, (INT8*)"\\");
        STRCAT(chDestFileName, (INT8*)chNodeFileName);
        STRCAT(chDestFileName, EXT_DOT);
	    STRCAT(chDestFileName, m_DcfSupportFileType[psFile->byFileType]);
        
		uiDestDirLen    = STRLEN((INT8*)chDestFileName);

        if (strcmp(chSrcFileName, chDestFileName) == 0) {
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
        }
        
      	if(AHC_DCF_FileDirRename(chSrcFileName, FileNameSize, chDestFileName, uiDestDirLen) != AHC_ERR_NONE){
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		}

        #if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT != LOCK_FILE_STOP)
		m_ulLockFileNum++;
        #endif
		
		AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
									&sFileAttribute, 
									uiFileSize,
									uwDirKey, 
									AHC_FALSE);
									
		AIHC_DCF_CalculateCluster(	m_chLockedFileFreeChar, 
									&sFileAttribute, 
									uiFileSize, 
									uwDirKey,
									AHC_TRUE);
		
		AIHC_DCF_UpdateDCFxPage(psDir, m_chLockedFileFreeChar, uwFileKey, sFileAttribute, sFileTime, uiFileSize);
		AIHC_DCF_UNLOCKPAGE();
		#else///< (DCF_DCFX == 1)
		printc("DCFX Unsupported\n");
		#endif///< (DCF_DCFX == 1)
        //clean Info cache by Jerry
        memset(&InfoCacheData, 0, sizeof(InfoCacheData));
	}
    break;
    
    case DCF_FILE_CHAR_UNLOCK_ALL_CAM:
    {
        #if (DCF_DCFX == 1)
		/**
		@brief	rename file => SM:\\DCIM\100__DSC\MOV_0001.AVI --> SM:\\DCIM\100__DSC\GLOK0001.AVI		

		*/
       	DCF_DIR_NODE	*psDir;
    	DCF_FILE_NODE	*psFile;
    	INT8 			chNodeFileName[MAX_FILE_CHAR_LENGTH + 1];
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+1];
	    INT8			chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
	    AHC_FS_FILETIME sFileTime;
	    UINT32			uiFileSize;
		/**
		@brief	confirm the attribute of file.
		*/
        FileNameSize = STRLEN(chSrcFileName);

        if(AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize) != AHC_ERR_NONE){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
		}
		/**
		@brief	compare the dir 
		*/
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
		
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if( (AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE) &&
            	(AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE) ){
            	
            	if(AIHC_DCF_WhichIsBoss(chFileFreeChar, m_chUnLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL){
            		// already locked.
            		AIHC_DCF_UNLOCKPAGE();
            		AIHC_DCF_UNLOCKDB();
            		return AHC_TRUE;
            	}
            	/**
            	@brief	valid file name.
            	*/
            	AIHC_DCF_FindDir(NULL, uwDirKey, &psDir);
            	
            	if(psDir != NULL){
					
					if(psDir->byMountMode != DCF_DIR_MOUNT_TYPE_ALL){
						AIHC_DCF_MountDirNode(	psDir, 
												NULL, 
												0xFFFF,
												uwFileKey,
												DCF_DIR_MOUNT_TYPE_KEY);
					}
					
            		AIHC_DCF_FindFileNode(psDir, NULL, uwFileKey, &psFile);
            		MEMSET(chNodeFileName, 0, sizeof(chNodeFileName));
            		AIHC_DCF_GetFileFullName(chNodeFileName, psFile->uwFileKey, psFile->chFileFreeChar);
            		
                	if(AIHC_DCF_WhichIsBoss((INT8*)pFileName, chNodeFileName, m_DcfDB[m_uiDBIndex].byFileCharLength) == DCF_BOSS_EQUAL){
                		/**
                		@brief	its the target file.
                		*/
           				MEMCPY(psFile->chFileFreeChar, m_chUnLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);

                	}else{
                		/**
                		@brief	its a neighbor or not.
                		*/
                		//printc("neighbor \r\n");
                		while(psFile->psNeighbor != NULL){
                		
                			psFile = psFile->psNeighbor;
                			if( (AIHC_DCF_WhichIsBoss(psFile->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL) &&
                				(byFileType == psFile->byFileType) ){
                				break;
                			}
                		}
                		
                		if(psFile != NULL){
                			/**
                			@brief its neighbor.
                			*/
                			MEMCPY(psFile->chFileFreeChar, m_chUnLockedFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
                		}else{
                			AIHC_DCF_UNLOCKPAGE();
                			AIHC_DCF_UNLOCKDB();
                			return AHC_FALSE;
                		}
                		
                	}
            	}else{
            		/**
            		@brief no dir node
            		*/
            		AIHC_DCF_UNLOCKPAGE();
            		AIHC_DCF_UNLOCKDB();
            		return AHC_FALSE;
            	}

            }else{
            	AIHC_DCF_UNLOCKPAGE();
            	AIHC_DCF_UNLOCKDB();
            	return AHC_FALSE;
            }///< valid dir name and valid file name
            
        }else{
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
        
        }///< valid dir name length
		
		
		/**
		@brief	rename
		*/
		AIHC_DCF_GetFileFullName(chNodeFileName, uwFileKey, m_chUnLockedFileFreeChar);
		
        STRCPY(chDestFileName, (INT8*)pPathName);
        STRCAT(chDestFileName, (INT8*)"\\");
        STRCAT(chDestFileName, (INT8*)chNodeFileName);
		STRCAT(chDestFileName, EXT_DOT);
	    STRCAT(chDestFileName, m_DcfSupportFileType[psFile->byFileType]);
        
		uiDestDirLen    = STRLEN((INT8*)chDestFileName);

      	if(AHC_DCF_FileDirRename(chSrcFileName, FileNameSize, chDestFileName, uiDestDirLen) != AHC_ERR_NONE){
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		}

#if (LIMIT_MAX_LOCK_FILE_NUM)
		{
			extern UINT32 m_ulLockFileNum;
			
			if (m_ulLockFileNum > 0) {
			    m_ulLockFileNum--;
			}
		}
#endif	

		AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
									&sFileAttribute, 
									uiFileSize, 
									uwDirKey,
									AHC_FALSE);
									
		AIHC_DCF_CalculateCluster(	m_chUnLockedFileFreeChar, 
									&sFileAttribute, 
									uiFileSize, 
									uwDirKey,
									AHC_TRUE);
		#else///< (DCF_DCFX == 1)
		printc("DCFX Unsupported\n");
		#endif///< (DCF_DCFX == 1)
    }
    break;
    
    case DCF_FILE_MOVE_SUBDB:
    {
        #if (DCF_SUB_DB == 1)
		/**
		@brief	rename file => SM:\\DCIM\100__DSC\MOV_0001.AVI --> SM:\\EMER\EMER0001.AVI		

		*/
    	INT8 			chNodeFileName[MAX_FILE_CHAR_LENGTH+1];
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+1];
	    INT8			chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
	    AHC_FS_FILETIME sFileTime;
	    UINT32			uiFileSize;
	    
	    #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        INT8            chAuxiliaryTempFileName[DCF_AUXILIARY_MAX_NUMBER][DCF_MAX_FILE_NAME_SIZE];
        #endif///< (DCF_AUXILIARY_MAX_NUMBER > 0)
        
		/**
		@brief	confirm the attribute of file.
		*/
        FileNameSize = STRLEN(chSrcFileName);

        if(AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize) != MMP_ERR_NONE){

        	return AHC_FALSE;
		}
		/**
		@brief	compare the dir 
		*/
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
		
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if( (AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE) &&
            	(AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE) ){

            	/**
            	@brief	valid file name.
            	*/      
                AIHC_DCF_DeleteFile(uwDirKey, uwFileKey, (INT8*)pFileName);
				AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
											&sFileAttribute, 
											uiFileSize,
											uwDirKey, 
											AHC_FALSE);

            }else{
            	AIHC_DCF_UNLOCKPAGE();
            	AIHC_DCF_UNLOCKDB();
            	return AHC_FALSE;
            }///< valid dir name and valid file name
            
        }else{
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
        
        }///< valid dir name length
		
		
		/**
		@brief	rename
		*/
		MEMSET(chNodeFileName , DCF_RESET_VALUE, sizeof(chNodeFileName));
		AIHC_DCF_GetSubName(chNodeFileName);
		
        STRCPY(chDestFileName, (INT8*)m_DCFSubDB.chRootDirName);
        STRCAT(chDestFileName, (INT8*)"\\");
        STRCAT(chDestFileName, (INT8*)chNodeFileName);

        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        {
        UINT32 i;
        
        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
            MEMSET(chAuxiliaryTempFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
    		STRCAT(chAuxiliaryTempFileName[i], chDestFileName);
    		STRCAT(chAuxiliaryTempFileName[i], EXT_DOT);
    	    STRCAT(chAuxiliaryTempFileName[i], m_chAuxiliaryFileType[i]);
        }
        
        }
        #endif

        STRCAT(chDestFileName, EXT_DOT);
	    STRCAT(chDestFileName, m_DcfSupportFileType[byFileType]);
        
		uiDestDirLen    = STRLEN((INT8*)chDestFileName);
        
        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        {
        UINT32 i;
        
        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
            MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
    		MEMCPY(m_chAuxiliaryFileName[i], chSrcFileName, uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength + 1 + m_DcfDB[m_uiDBIndex].byFileCharLength);
    		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
    	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
        }
        
        }
        #endif
        
      	if(AHC_DCF_FileDirMove(chSrcFileName, FileNameSize, chDestFileName, uiDestDirLen) != AHC_ERR_NONE){
      	    printc("From %s to %s Failed \n", chSrcFileName, chDestFileName);
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		}
		
        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
        {
        UINT32 i;
        
        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
            AHC_DCF_FileDirMove(m_chAuxiliaryFileName[i], 
                                STRLEN(m_chAuxiliaryFileName[i]), 
                                chAuxiliaryTempFileName[i],
                                STRLEN(chAuxiliaryTempFileName[i]));
        }
        
        }
        #endif///< (DCF_AUXILIARY_MAX_NUMBER > 0)
		
		printc("From %s to %s \n", chSrcFileName, chDestFileName);
									
        STRCAT(chNodeFileName, EXT_DOT);
	    STRCAT(chNodeFileName, m_DcfSupportFileType[byFileType]);
	    
        AIHC_DCF_AddSubFile(chNodeFileName);
        
        {
		
        sFileAttribute |= AHC_FS_ATTR_READ_ONLY;
        
        AHC_DCF_FileDirSetAttribute(chDestFileName, uiDestDirLen, sFileAttribute);
        
        }
        
        #endif
		//clean Info cache by Jerry
        memset(&InfoCacheData, 0, sizeof(InfoCacheData));
    }
    break;
    
    case DCF_FILE_DELETE_ALL_CAM:
    {
    	INT8	chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+1];
	    INT8	chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
        INT32	i;
		UINT32	uiFileSize;
		AHC_FS_FILETIME sFileTime;

        FileNameSize = STRLEN(chSrcFileName);

		AHC_DCF_FileDirGetInfo(chSrcFileName, FileNameSize, &sFileAttribute, &sFileTime, &uiFileSize);
		
        if(AIHC_DCF_FileDeletedMask((INT8*)pFileName, &sFileAttribute) == AHC_FALSE){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
            return AHC_FALSE;
        }
        
        MEMSET( m_DcfFileName, 0, sizeof(m_DcfFileName) );

        for( i = FileNameSize ; i >= 0 ; i-- ) {
            if (chSrcFileName[i] == '.') {
                break;
            }
        }
        
        MEMCPY( m_DcfFileName, chSrcFileName, i+1 );
                
        uiSrcDirLen  = STRLEN((INT8*)pPathName);
        
        #if(DCF_SUB_DB == 1)
        if(m_bTurnOnSubDB == AHC_TRUE){
            
            uiRootDirLen = STRLEN((INT8*)m_DCFSubDB.chRootDirName);

            if ( uiSrcDirLen == uiRootDirLen ) {
            	/**
            	@brief clear the counter of DB and release the memory of file node if the file is counted into DB.
            	*/
                if ( AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE ) {

                        AIHC_DCF_DeleteSubFile((INT8*)pFileName);
                        
                        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                        {
                        UINT32 i;
                        
                        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                            MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
                    		MEMCPY(m_chAuxiliaryFileName[i], chSrcFileName, uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byFileCharLength);
                    		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
                    	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
                        }
                        
                        }
                        #endif///< #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                        
                        AHC_DCF_FileRemove(chSrcFileName, FileNameSize);

#if (LIMIT_MAX_LOCK_FILE_NUM)
                		{
                			extern UINT32 m_ulLockFileNum;

                            if ( (sFileAttribute & AHC_FS_ATTR_READ_ONLY) ||
                			#if (PROTECT_FILE_RENAME)
                			     (memcmp(chSrcFileName, FILE_RENAME_STRING, strlen(FILE_RENAME_STRING))==0) ||
                			#endif
                                 0
                			{
                				if(m_ulLockFileNum>0) {
                					m_ulLockFileNum--;
                			    }
                			}
                		}
#endif	
                        
                        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                    	{
                        UINT32 i;
                        
                        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                            printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                            AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
                        }
                        
                        }
                    	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)

                }else{
                	if (AHC_ERR_NONE == AHC_DCF_FileRemove(chSrcFileName, FileNameSize)) {
#if (LIMIT_MAX_LOCK_FILE_NUM)
            			extern UINT32 m_ulLockFileNum;
            			
                        if ( (sFileAttribute & AHC_FS_ATTR_READ_ONLY) ||
            			#if (PROTECT_FILE_RENAME)
            			     (memcmp(chSrcFileName, FILE_RENAME_STRING, strlen(FILE_RENAME_STRING))==0) ||
            			#endif
                             0
            			{
            				if(m_ulLockFileNum>0) {
            					m_ulLockFileNum--;
            				}
            			}
#endif	
                	}
                }

            }else{
                if (AHC_ERR_NONE == AHC_DCF_FileRemove(chSrcFileName, FileNameSize))
                {
#if (LIMIT_MAX_LOCK_FILE_NUM)
        			extern UINT32 m_ulLockFileNum;
        			
                    if ( (sFileAttribute & AHC_FS_ATTR_READ_ONLY) ||
        			#if (PROTECT_FILE_RENAME)
        			     (memcmp(chSrcFileName, FILE_RENAME_STRING, strlen(FILE_RENAME_STRING))==0) ||
        			#endif
                         0
        			{
        				if(m_ulLockFileNum>0)
        					m_ulLockFileNum--;
        			}
#endif
                }
        }else
        #endif ///< #if(DCF_SUB_DB)
        {
            uiRootDirLen = STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);

            //the dir is in the DCF root
            if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
            	/**
            	@brief clear the counter of DB and release the memory of file node if the file is counted into DB.
            	*/
                if ( AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE ) {
                    //the file is a DCF obj        
                    if ( AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE ) {
                    	
                        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                        {
                        UINT32 i;
                        
                        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                            MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
                    		MEMCPY(m_chAuxiliaryFileName[i], chSrcFileName, uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength + 1 + m_DcfDB[m_uiDBIndex].byFileCharLength);
                    		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
                    	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
                        }
                        
                        }
                        #endif
                    	
                    	
                        AIHC_DCF_DeleteFile(uwDirKey, uwFileKey, (INT8*)pFileName);
    					AIHC_DCF_CalculateCluster(	(INT8*)pFileName, 
    												&sFileAttribute, 
    												uiFileSize,
    												uwDirKey, 
    												AHC_FALSE);
                        
                        AHC_DCF_FileRemove(chSrcFileName, FileNameSize);
                        
                        #if (DCF_AUXILIARY_MAX_NUMBER > 0)
                    	{
                        UINT32 i;
                        
                        for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
                            printc("Remove Aux. File : %s \r\n", m_chAuxiliaryFileName[i]);
                            AHC_DCF_FileRemove(m_chAuxiliaryFileName[i], sizeof(m_chAuxiliaryFileName[i]));
                        }
                        
                        }
                    	#endif ///< (DCF_AUXILIARY_MAX_NUMBER > 0)
                        
                        if( (uwDirKey == m_DcfDB[m_uiDBIndex].uwKillDirKey) && (uwFileKey == m_DcfDB[m_uiDBIndex].uwKillFileKey) ){
                        	AIHC_DCF_ChangeKillKey();
                        }
                    }else{
                    	AHC_DCF_FileRemove(chSrcFileName, FileNameSize);
                    }
                    
                }else{
                	AHC_DCF_FileRemove(chSrcFileName, FileNameSize);
                }

            }else{
                AHC_DCF_FileRemove(chSrcFileName, FileNameSize);
            }
            
            {
            DCF_DIR_NODE* psDir;
            AIHC_DCF_FindDir(NULL, uwDirKey, &psDir);
            AIHC_DCF_ClearEmptyDir((INT8*)pPathName, psDir);
    		}        
        }
        //clean Info cache by Jerry
        memset(&InfoCacheData, 0, sizeof(InfoCacheData));

	}
	break;
	
	case DCF_FILE_RENAME:
	{
		/**
		@brief	rename file => SM:\\DCIM\100__DSC\MOV_0001.AVI --> SM:\\DCIM\100__DSC\REC_0001.AVI
		
		(UINT8 *pPathName, UINT8 *pFileName, UINT8 byOperation, UINT8 *pDestPath, UINT8 *pDestFileName) => 
		(SM:\\DCIM\100__DSC, MOV_0001.AVI, DCF_FILE_RENAME, NULL, REC_0001.AVI)
		
		*/
       	DCF_DIR_NODE	*psDir;
    	DCF_FILE_NODE	*psFile;
    	UINT16			uwDestFileKey = DCF_INVALID_NUMBER_16;
    	UINT8			byDestFileType;
    	INT8 			NodeFileName[MAX_FILE_CHAR_LENGTH+1];
    	INT8 			chDestFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
		INT8			chDirFreeChar[MAX_DIR_FREE_CHAR_NUMBER+1];
	    INT8			chFileFreeChar[MAX_FILE_FREE_CHAR_NUMBER+1];
	    
    	AHC_BOOL		bAddFile = AHC_FALSE;
		/**
		@brief	confirm the attribute of file.
		*/
        FileNameSize = STRLEN(chSrcFileName);
        
        if(AHC_DCF_FileDirGetAttribute(chSrcFileName, FileNameSize, &sFileAttribute) != AHC_ERR_NONE){
        	AIHC_DCF_UNLOCKPAGE();
        	AIHC_DCF_UNLOCKDB();
        	return AHC_FALSE;
        }
        
		/**
		@brief	the path of file name which is use to rename.
		*/
        STRCPY(chDestFileName, (INT8*)pPathName);
        STRCAT(chDestFileName, (INT8*)"\\");
        STRCAT(chDestFileName, (INT8*)pDestFileName);
		uiDestDirLen    = STRLEN((INT8*)chDestFileName);
		
		{
		/**
		@brief confirm the file name which is wanted to be renamed.
		*/
		UINT32 ulFileId;
		if(AHC_DCF_FileOpen(chDestFileName, uiDestDirLen, "r", STRLEN("r"), &ulFileId) == AHC_ERR_NONE){
			AHC_DCF_FileClose(ulFileId);
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		}
		}
		
		/**
		@brief	compare the dir 
		*/
		uiRootDirLen	= STRLEN((INT8*)m_DcfDB[m_uiDBIndex].chRootName);
		uiSrcDirLen		= STRLEN((INT8*)pPathName);
		/*
		if(AHC_DCF_FileDirRename(chSrcFileName, FileNameSize, chDestFileName, uiDestDirLen) != AHC_ERR_NONE){

			return AHC_FALSE;
		}
		*/
		AIHC_DCF_GetFileKey((INT8*)pDestFileName, &uwDestFileKey, chDestFreeChar, &byDestFileType);
		
        if ( uiSrcDirLen == (uiRootDirLen + 1 + m_DcfDB[m_uiDBIndex].byDirCharLength) ) {
        	/**
        	@brief	valid dir name is 8 character.
        	*/
            if( (AIHC_DCF_GetDirKey((INT8*)(pPathName + uiRootDirLen + 1), &uwDirKey, chDirFreeChar) == AHC_TRUE) &&
            	(AIHC_DCF_GetFileKey((INT8*)pFileName, &uwFileKey, chFileFreeChar, &byFileType) == AHC_TRUE) ){
            	/**
            	@brief	valid file name.
            	*/
            	AIHC_DCF_FindDir(NULL, uwDirKey, &psDir);
            	
            	if(psDir != NULL){
					
					if(psDir->byMountMode != DCF_DIR_MOUNT_TYPE_ALL){
						AIHC_DCF_MountDirNode(	psDir, 
												NULL, 
												0xFFFF,
												uwFileKey,
												DCF_DIR_MOUNT_TYPE_KEY);
					}
					
            		AIHC_DCF_FindFileNode(psDir, NULL, uwFileKey, &psFile);
            		
            		AIHC_DCF_GetFileFullName(NodeFileName, psFile->uwFileKey, psFile->chFileFreeChar);
            		
                	if(AIHC_DCF_WhichIsBoss((INT8*)pFileName, NodeFileName, m_DcfDB[m_uiDBIndex].byFileCharLength) == DCF_BOSS_EQUAL){
                		/**
                		@brief	its the target file.
                		*/
            			if(psFile->uwFileKey == uwDestFileKey){
            				MEMCPY(psFile->chFileFreeChar, chDestFreeChar, 4);
            			}else{
            				/*	
            				@brief delete the old file node and add the new file node
            				TBD
            				*/	                				
        					AIHC_DCF_RemoveFileNode(psDir, psFile, AHC_FALSE);
        					bAddFile = AHC_TRUE;
            			}

                	}else{
                		/**
                		@brief	its a neighbor or not.
                		*/
                		//printc("neighbor \r\n");
                		while(psFile->psNeighbor != NULL){
                		
                			psFile = psFile->psNeighbor;
                			if( (AIHC_DCF_WhichIsBoss(psFile->chFileFreeChar, chFileFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum) == DCF_BOSS_EQUAL) &&
                				(byDestFileType == psFile->byFileType) ){
                				break;
                			}
                		}
                		
                		if(psFile != NULL){
                			/**
                			@brief its neighbor.
                			*/
                			MEMCPY(psFile->chFileFreeChar, chDestFreeChar, m_DcfDB[m_uiDBIndex].byFileFreeCharNum);
                		}else{
                			bAddFile = AHC_TRUE;
                		}
                		
                	}
            	}else{
            		/**
            		@brief no dir node
            		*/
            		AIHC_DCF_UNLOCKPAGE();
            		AIHC_DCF_UNLOCKDB();
            		return AHC_FALSE;
            	}

            }///< valid dir name and valid file name
        }///< valid dir name length
		
		
		/**
		@brief	rename
		*/
      	if(AHC_DCF_FileDirRename(chSrcFileName, FileNameSize, chDestFileName, uiDestDirLen) != AHC_ERR_NONE){
			AIHC_DCF_UNLOCKPAGE();
			AIHC_DCF_UNLOCKDB();
			return AHC_FALSE;
		}
		
		/**
		@brief	add the new file node or not.
		*/
		if(bAddFile == AHC_TRUE){
			AIHC_DCF_AddFile(uwDirKey, (INT8*)pDestFileName);
		}
		
		{
		/**
		need to control the counter of DCFx region
		*/
		
		}
	
	}
	break;
	
    default:
	break;
    }///< the end of switch loop

    AIHC_DCF_UNLOCKPAGE();
    AIHC_DCF_UNLOCKDB();
    
    #if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT==LOCK_FILE_RENAME_CYCLIC)
    if (m_ulLockFileNum > MAX_LOCK_FILE_NUM)
    {
        printc("### %s,%d: exceed LIMIT_MAX_LOCK_FILE_NUM, %d\r\n", __FUNCTION__, __LINE__, m_ulLockFileNum);
        AHC_RollBackMinKeyProtectFile();
        printc("m_ulLockFileNum = %d\r\n", m_ulLockFileNum);
    }
    #endif

	return AHC_TRUE;
}

AHC_BOOL AHC_DCF_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly)
{
    DCF_DB_TYPE sCurType;
    UINT8       byFileType;
    INT8        chSrcName[DCF_MAX_FILE_NAME_SIZE];
    
    
    sCurType = AHC_DCF_GetDB();
    
    if(sFromType == sToType){
        return AHC_TRUE;
    }
    
    AHC_DCF_SelectDB(sFromType);
    
    {
    
    
    DCF_FILE_NODE   *psFileNode;
    DCF_DIR_NODE    *psDirNode;
    
    UINT16          uwFileKey;
    INT8            chFileFreeChar[MAX_DIR_FREE_CHAR_NUMBER + 1];

    
    MEMSET(chFileFreeChar, DCF_RESET_VALUE, sizeof(chFileFreeChar));
    /**	
    @brief	find the dir node with uwDirKey as root node.
    */
    if ( AIHC_DCF_FindDir(NULL, uwDirKey, &psDirNode) == AHC_FALSE ){
        AHC_DCF_SelectDB(sCurType);
        return AHC_FALSE;
    }

    if ( AIHC_DCF_GetFileKey(pchFileName, &uwFileKey , chFileFreeChar, &byFileType) == AHC_FALSE ) {
        AHC_DCF_SelectDB(sCurType);
        return AHC_FALSE;
    }
    
    if( (psDirNode->byMountMode == DCF_DIR_MOUNT_TYPE_UNMOUNT) ||
        (uwFileKey < psDirNode->psRootFileNode->uwFileKey) || 
        (uwFileKey > psDirNode->psLastFileNode->uwFileKey)  ){
        
        AIHC_DCF_MountDirNode(psDirNode, 
        					  NULL, 
        					  0xFFFF,
        				      uwFileKey,
        				      DCF_DIR_MOUNT_TYPE_KEY);
    }
    
    
    
    if(AIHC_DCF_FindFileNode(psDirNode, NULL, uwFileKey, &psFileNode) == AHC_FALSE){
        AHC_DCF_SelectDB(sCurType);
        return AHC_FALSE;
    }
    
    if( STRCMP(psFileNode->chFileFreeChar, chFileFreeChar) ){
        AHC_DCF_SelectDB(sCurType);
        return AHC_FALSE;
    }
    
    
    
    MEMSET(chSrcName, DCF_RESET_VALUE, sizeof(chSrcName));
    STRCPY(chSrcName, AIHC_DCF_GetRootName());
    STRCAT(chSrcName, "\\");

    {
    INT8   chSrcDirName[MAX_DIR_CHAR_LENGTH+1];
    MEMSET(chSrcDirName, DCF_RESET_VALUE, sizeof(chSrcDirName));
    AIHC_DCF_GetDirFullName(chSrcDirName, uwDirKey, psDirNode->chDirFreeChar);
    STRCAT(chSrcName, chSrcDirName);
    
    }
    
    
    STRCAT(chSrcName, "\\");
    
    #if (DCF_AUXILIARY_MAX_NUMBER > 0)
    {
    UINT32 i;
    INT8 chFileName[MAX_FILE_CHAR_LENGTH + 1];
    
    MEMSET(chFileName, 0, sizeof(chFileName));
    AIHC_DCF_GetFileFullName( chFileName, psFileNode->uwFileKey, psFileNode->chFileFreeChar);

    for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
        MEMSET(m_chAuxiliaryFileName[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
		STRCPY(m_chAuxiliaryFileName[i], chSrcName);
        STRCAT(m_chAuxiliaryFileName[i], chFileName);
		STRCAT(m_chAuxiliaryFileName[i], EXT_DOT);
	    STRCAT(m_chAuxiliaryFileName[i], m_chAuxiliaryFileType[i]);
    }
    
    }
    #endif
    
    STRCAT(chSrcName, pchFileName);

    AIHC_DCF_DeleteFile(uwDirKey, uwFileKey, pchFileName);
    }
    
    
    {
    UINT16 uwDestDirKey;

    INT8   chDestName[DCF_MAX_FILE_NAME_SIZE];
    INT8   chDestDirName[MAX_DIR_CHAR_LENGTH + 2];
    INT8   chDestFileName[MAX_FILE_CHAR_LENGTH + FILE_EXT_LENGTH + 2];
    UINT8  bCreateNewDir;
    
    AHC_DCF_SelectDB(sToType);

    MEMSET(chDestName, DCF_RESET_VALUE, sizeof(chDestName));
    MEMSET(chDestDirName, DCF_RESET_VALUE, sizeof(chDestDirName));
    MEMSET(chDestFileName, DCF_RESET_VALUE, sizeof(chDestFileName));

    AIHC_DCF_GetName(&uwDestDirKey, chDestDirName, chDestFileName, &bCreateNewDir);
    
    STRCPY(chDestName, AIHC_DCF_GetRootName());
    STRCAT(chDestName, "\\");
    STRCAT(chDestName, chDestDirName);
    
    if ( bCreateNewDir ) {
        AHC_DCF_DirCreate((INT8*)chDestName, STRLEN(chDestName));
        AIHC_DCF_AddDir(chDestDirName);
    }
    

            
    STRCAT(chDestName, "\\");
    
    #if (DCF_AUXILIARY_MAX_NUMBER > 0)
    {
    UINT32 i;

    for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
        MEMSET(m_chAuxiliaryFileNameTemp[i], DCF_RESET_VALUE, DCF_MAX_FILE_NAME_SIZE);
		STRCPY(m_chAuxiliaryFileNameTemp[i], chDestName);    
		STRCAT(m_chAuxiliaryFileNameTemp[i], chDestFileName);
		STRCAT(m_chAuxiliaryFileNameTemp[i], EXT_DOT);
	    STRCAT(m_chAuxiliaryFileNameTemp[i], m_chAuxiliaryFileType[i]);
    }
    
    }
    #endif

    STRCAT(chDestFileName, EXT_DOT);
    STRCAT(chDestFileName, m_DcfSupportFileType[byFileType]);
        
    STRCAT(chDestName, (INT8*)chDestFileName);

    
    AHC_DCF_FileDirMove(chSrcName, STRLEN(chSrcName), chDestName, STRLEN(chDestName));
    
    #if (DCF_AUXILIARY_MAX_NUMBER > 0)
    {
    UINT32 i;

    for(i = 0; i < DCF_AUXILIARY_MAX_NUMBER; i++){
        AHC_DCF_FileDirMove(m_chAuxiliaryFileName[i], STRLEN(m_chAuxiliaryFileName[i]), m_chAuxiliaryFileNameTemp[i], STRLEN(m_chAuxiliaryFileNameTemp[i]));
    }
    
    }
    #endif

    AIHC_DCF_PreAddFile(uwDestDirKey, chDestFileName);
    AIHC_DCF_PostAddFile(uwDestDirKey, chDestFileName);
    
    printc("From Name : %s \n", chSrcName);
    printc("To Name : %s \n", chDestName);
    
    MEMSET(chDestName, DCF_RESET_VALUE, sizeof(chDestName));
    STRCPY(chDestName, AIHC_DCF_GetRootName());
    STRCAT(chDestName, "\\");

    STRCAT(chDestName, chDestDirName);
        
    if(bReadOnly == AHC_TRUE)
    {
        AHC_DCF_FileOperation((UINT8*)chDestName,(UINT8*)chDestFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL, NULL);
    }else{
        AHC_DCF_FileOperation((UINT8*)chDestName,(UINT8*)chDestFileName, DCF_FILE_NON_READ_ONLY_ALL_CAM, NULL, NULL);
    }
    
    
    }
    
    AHC_DCF_SelectDB(sCurType);
    //clean Info cache by Jerry
	memset(&InfoCacheData, 0, sizeof(InfoCacheData));
    return AHC_TRUE;
}

UINT32 AHC_DCF_GetReadOnlyCluster(DCF_DB_TYPE sDB)
{
    if(sDB != DCF_DB_TYPE_SUB_DB){
	    return m_DcfDB[sDB].uiReadOnlyRegionCluster;
	}else{
	    return 0;
	}
}

UINT32 AHC_DCF_GetCyclicCluster(DCF_DB_TYPE sDB)
{
    if(sDB != DCF_DB_TYPE_SUB_DB){
        
        return 	m_DcfDB[sDB].uiDCFxRegionCluster + m_DcfDB[sDB].uiNonLockRegionCluster;
        
    }else{
        #if (DCF_SUB_DB == 1)
        return m_DCFSubDB.uiCluster;
        #else
        return 0;
        #endif
    }
}

UINT32 AHC_DCF_GetFileCluster(DCF_DB_TYPE sDB)
{
    if(sDB != DCF_DB_TYPE_SUB_DB){
        if (sDB >= DCF_DB_COUNT) {
            return 	m_DcfDB[DCF_DB_COUNT-1].uiReadOnlyRegionCluster + 
                    m_DcfDB[DCF_DB_COUNT-1].uiDCFxRegionCluster + 
                    m_DcfDB[DCF_DB_COUNT-1].uiNonLockRegionCluster;
        }
        
        return 	m_DcfDB[sDB].uiReadOnlyRegionCluster + 
                m_DcfDB[sDB].uiDCFxRegionCluster + 
                m_DcfDB[sDB].uiNonLockRegionCluster;
        
    }else{
        #if (DCF_SUB_DB == 1)
        return m_DCFSubDB.uiCluster;
        #else
        return 0;
        #endif
    }
}

UINT32 AHC_DCF_GetClusterTH(DCF_DB_TYPE sDB)
{
    return m_DcfDB[sDB].uiClustersTH;
}

UINT32 AHC_DCF_GetTotalCluster(void)
{
    return 	m_sMediaInfo.ulTotalClusters;
}

UINT32 AHC_DCF_GetClusterSize(void)
{
    return 	m_uiBytesPerCluster;
}

void AHC_DCF_GetMediaInfo(AHC_FS_DISK_INFO* sMediaInfo)
{
    sMediaInfo->ulTotalClusters = m_sMediaInfo.ulTotalClusters;
    sMediaInfo->ulFreeClusters = m_sMediaInfo.ulFreeClusters;
    sMediaInfo->usSecPerCluster = m_sMediaInfo.usSecPerCluster;
    sMediaInfo->usBytesPerSector = m_sMediaInfo.usBytesPerSector;
    return;
}

AHC_BOOL AHC_DCF_AdjustAllocation(DCF_STORAGE_ALLOC eType)
{
    UINT32 uiNumeratorDB0;
    UINT32 uiNumeratorDB1;
    UINT32 uiNumeratorDB2;
    UINT32 uiNumeratorDB3;
    //#if (DCF_DB_COUNT > 4)
    //UINT32 uiNumeratorDB4;
    //#endif
    
    UINT32 uiDenominator;
    
    switch(eType){

    case DCF_STORAGE_ALLOC_TYPE1:
        uiNumeratorDB0 = DCF_CLUSTER_NUMERATOR1_DB0;
        uiNumeratorDB1 = DCF_CLUSTER_NUMERATOR1_DB1;
        uiNumeratorDB2 = DCF_CLUSTER_NUMERATOR1_DB2;
        uiNumeratorDB3 = DCF_CLUSTER_NUMERATOR1_DB3;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;
    
    case DCF_STORAGE_ALLOC_TYPE2:
        uiNumeratorDB0 = DCF_CLUSTER_NUMERATOR2_DB0;
        uiNumeratorDB1 = DCF_CLUSTER_NUMERATOR2_DB1;
        uiNumeratorDB2 = DCF_CLUSTER_NUMERATOR2_DB2;
        uiNumeratorDB3 = DCF_CLUSTER_NUMERATOR2_DB3;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;
        
    case DCF_STORAGE_ALLOC_TYPE3:
        uiNumeratorDB0 = DCF_CLUSTER_NUMERATOR3_DB0;
        uiNumeratorDB1 = DCF_CLUSTER_NUMERATOR3_DB1;
        uiNumeratorDB2 = DCF_CLUSTER_NUMERATOR3_DB2;
        uiNumeratorDB3 = DCF_CLUSTER_NUMERATOR3_DB3;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;
        
    case DCF_STORAGE_ALLOC_TYPE0:
    default:
        uiNumeratorDB0 = DCF_CLUSTER_NUMERATOR_DB0;
        uiNumeratorDB1 = DCF_CLUSTER_NUMERATOR_DB1;
        uiNumeratorDB2 = DCF_CLUSTER_NUMERATOR_DB2;
        uiNumeratorDB3 = DCF_CLUSTER_NUMERATOR_DB3;
        //#if (DCF_DB_COUNT > 4)
        //uiNumeratorDB4 = DCF_CLUSTER_NUMERATOR_DB4;
        //#endif
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;
    }
    
    m_AllocType = eType;
    
    #if (DCF_DB_COUNT >= 4) 
    if(m_bEnableDCF[DCF_DB_TYPE_DB3_PHOTO] == AHC_TRUE){

        m_DcfDB[DCF_DB_TYPE_DB3_PHOTO].uiClustersTH = m_sMediaInfo.ulTotalClusters*uiNumeratorDB3/uiDenominator;

    }
    #endif///< (DCF_DB_COUNT >= 4) 
    
    #if (DCF_DB_COUNT >= 3)
    if(m_bEnableDCF[DCF_DB_TYPE_DB2_EVENT] == AHC_TRUE){

        m_DcfDB[DCF_DB_TYPE_DB2_EVENT].uiClustersTH = m_sMediaInfo.ulTotalClusters*uiNumeratorDB2/uiDenominator;

    }
    #endif///< (DCF_DB_COUNT >= 3) 

    #if (DCF_DB_COUNT >= 2) 
    if(m_bEnableDCF[DCF_DB_TYPE_DB1_PARKING] == AHC_TRUE){

        m_DcfDB[DCF_DB_TYPE_DB1_PARKING].uiClustersTH = m_sMediaInfo.ulTotalClusters*uiNumeratorDB1/uiDenominator;

    }
    #endif///< (DCF_DB_COUNT >= 2) 
    
    if(m_bEnableDCF[DCF_DB_TYPE_DB0_NORMAL] == AHC_TRUE){

        m_DcfDB[DCF_DB_TYPE_DB0_NORMAL].uiClustersTH = m_sMediaInfo.ulTotalClusters*uiNumeratorDB0/uiDenominator;
    }

    return AHC_TRUE;
}

void AHC_DCF_DBInitFreeCharLength(UINT32 uiDBIndex,
                                    INT8* pchDirFreeChar,
                                    INT8* pchFileFreeChar)
{
    UINT32 uiDirKeyDigitCount = 0;
    UINT32 uiFileKeyDigitCount = 0;
    UINT32 i;
    //Calculate uiDirKeyDigitCount & uiFileKeyDigitCount
    for(i = MAX_DCF_DIR_KEYNUM; i>0; i/=10){ 
        uiDirKeyDigitCount++; 
    } 
    for(i = MAX_DCF_FILE_KEYNUM; i>0; i/=10){ 
        uiFileKeyDigitCount++; 
    }
    //Set FileFreeCharNumber DirFreeCharNumber
    m_DcfDB[uiDBIndex].byDirFreeCharNum  = MIN(STRLEN(pchDirFreeChar),MAX_DIR_FREE_CHAR_NUMBER);
    m_DcfDB[uiDBIndex].byDirCharLength   = MIN(STRLEN(pchDirFreeChar) + uiDirKeyDigitCount,MAX_DIR_CHAR_LENGTH);
    m_DcfDB[uiDBIndex].byFileFreeCharNum = MIN(STRLEN(pchFileFreeChar),MAX_FILE_FREE_CHAR_NUMBER);
    m_DcfDB[uiDBIndex].byFileCharLength  = MIN(STRLEN(pchFileFreeChar) + uiFileKeyDigitCount,MAX_FILE_CHAR_LENGTH);
    if(STRLEN(pchDirFreeChar) > MAX_DIR_FREE_CHAR_NUMBER)
    {
        
        printc("Setting DirFreeCharNum exceeds MAX_DIR_FREE_CHAR_NUMBER !!\r\n");
        printc("DBIndex[%d] Enforce to set DirFreeCharNum = MAX_DIR_FREE_CHAR_NUMBER %d\r\n",uiDBIndex,MAX_DIR_FREE_CHAR_NUMBER);
    }
    if((STRLEN(pchDirFreeChar) + uiDirKeyDigitCount) > MAX_DIR_CHAR_LENGTH)
    {
        
        printc("Setting DirCharLength exceeds MAX_DIR_CHAR_LENGTH !!\r\n");
        printc("DBIndex[%d] Enforce to set DirCharLength = MAX_DIR_CHAR_LENGTH %d\r\n",uiDBIndex,MAX_DIR_CHAR_LENGTH);
    }
    if(STRLEN(pchFileFreeChar) > MAX_FILE_FREE_CHAR_NUMBER)
    {
        
        printc("Setting FileFreeCharNum exceeds MAX_FILE_FREE_CHAR_NUMBER !!\r\n");
        printc("DBIndex[%d] Enforce to set FileFreeCharNum = MAX_FILE_FREE_CHAR_NUMBER %d\r\n",uiDBIndex,MAX_FILE_FREE_CHAR_NUMBER);
    }
    if((STRLEN(pchFileFreeChar) + uiFileKeyDigitCount) > MAX_FILE_CHAR_LENGTH)
    {
        
        printc("Setting FileCharLength exceeds MAX_FILE_CHAR_LENGTH !!\r\n");
        printc("DBIndex[%d] Enforce to set FileCharLength = MAX_FILE_CHAR_LENGTH %d\r\n",uiDBIndex,MAX_FILE_CHAR_LENGTH);
    }

}

#if (LIMIT_MAX_LOCK_FILE_NUM)
void AHC_DCF_InitLockFileTable(void)
{
    extern UINT32   m_ulLockFileTable[MAX_LOCK_FILE_NUM];
    memset(m_ulLockFileTable, 0xFFFFFFFF, sizeof(m_ulLockFileTable));
}

void AHC_DCF_UpdateLockFileTable(UINT16    uwDirKey,
                                 UINT16    uwFileKey,
                                 UINT8     byFileType,
                                 AHC_BOOL *bDeleteFile)
{
    UINT32          i,j;
    AHC_BOOL        ahc_ret = AHC_TRUE;
    INT8            chPathName[DCF_MAX_FILE_NAME_SIZE];
    INT8            chFileName[DCF_MAX_FILE_NAME_SIZE];
    INT8            chRenameFileName[DCF_MAX_FILE_NAME_SIZE];
    INT8            chDirName[MAX_DIR_CHAR_LENGTH + 1];
    
    for(i=0;i<MAX_LOCK_FILE_NUM;i++)
    {
        // add Index to Table by step(0xFFFFFFFF = empty slot)
        if(m_ulLockFileTable[i] == 0xFFFFFFFF)
        {
            m_ulLockFileTable[i] = (byFileType << 28) + (uwDirKey << 16) + uwFileKey;
            for(j=0;j<i;j++)
            {
                if(m_ulLockFileTable[i] == m_ulLockFileTable[j])
                {
                    printc("0Have same Emer file name!!!,cancal updating\r\n");
                    m_ulLockFileTable[i] = 0xFFFFFFFF;
                    break;
                }
            }
            //printc("DcfInfo.uwFileKey %d\r\n",DcfInfo.uwFileKey);
            break;
        }
        //if no slot is empty
        if((i == MAX_LOCK_FILE_NUM-1)&&(m_ulLockFileTable[i] != 0xFFFFFFFF))
        {
            UINT32    uiTempLockFileData;
            UINT32    uiDeleteLockFileData;
            AHC_BOOL  bUpdate = AHC_TRUE;
            UINT16    uwDelDirKey;
            UINT16    uwDelFileKey;
            UINT8     byDelFileType;
            
            uiTempLockFileData = (byFileType << 28) + (uwDirKey << 16) + uwFileKey;
            for(j=0;j<MAX_LOCK_FILE_NUM;j++)
            {
                if(uiTempLockFileData == m_ulLockFileTable[j])
                {
                    printc("1Have same Emer file name!!!,cancal updating\r\n");
                    bUpdate = AHC_FALSE;
                    break;
                }
            }
            if(bUpdate == AHC_TRUE)
            {
                //Shift array 1 offset and add dirkey filekey to the last slot
                uiDeleteLockFileData = m_ulLockFileTable[0];
                for(j=0;j<MAX_LOCK_FILE_NUM-1;j++)
                {
                    m_ulLockFileTable[j] = m_ulLockFileTable[j+1];
                }
                //update last slot
                m_ulLockFileTable[MAX_LOCK_FILE_NUM - 1] = uiTempLockFileData;
                //sorting and find the min key file
                for(j=0;j<MAX_LOCK_FILE_NUM;j++)
                {
                    if((uiDeleteLockFileData & 0x0FFFFFFF) > (m_ulLockFileTable[j] & 0x0FFFFFFF))
                    {
                        //data exchange
                        uiTempLockFileData   = uiDeleteLockFileData;
                        uiDeleteLockFileData = m_ulLockFileTable[j];
                        m_ulLockFileTable[j] = uiTempLockFileData;
                    }
                    //else do nothing
                }
                //Rename file and delete it
                memset(chPathName,0,sizeof(chPathName));
                memset(chDirName,0,sizeof(chDirName));
                memset(chFileName,0,sizeof(chFileName));
                memset(chRenameFileName,0,sizeof(chRenameFileName));
                uwDelFileKey  =  uiDeleteLockFileData & 0x0000FFFF;
                uwDelDirKey   = (uiDeleteLockFileData & 0x0FFF0000)>>16;
                byDelFileType = (uiDeleteLockFileData & 0xF0000000)>>28;
                //printc("delete uwDelFileKey %d,uwDelDirKey %d\r\n",uwDelFileKey,uwDelDirKey);
                //Filename strcat
                AIHC_DCF_GetFileFullName(chFileName, uwDelFileKey, FILE_RENAME_STRING);
                STRCAT(chFileName, EXT_DOT);
                STRCAT(chFileName, m_DcfSupportFileType[byDelFileType]);
                //PathName strcat
                STRCPY(chPathName, m_DcfDB[m_uiDBIndex].chRootName);
                STRCAT(chPathName, "\\");
                AIHC_DCF_GetDirFullName(chDirName, uwDelDirKey, m_DcfDB[m_uiDBIndex].chDirFreeChar);
                STRCAT(chPathName, chDirName);
                //make Dir Path for ClearEmptyDir
                memset(chDirName,0,sizeof(chDirName));
                STRCPY(chDirName, chPathName);
                if(m_bParsePage == AHC_TRUE)
                {
                    STRCAT(chPathName, "\\");    
                    STRCAT(chPathName,(INT8*)chFileName);
                    AHC_DCF_FileRemove(chPathName, sizeof(chPathName));
                    printc("Remove FilePathName = %s\r\n",chPathName);
                    if(uwDelDirKey == m_DcfDB[m_uiDBIndex].psPowerDirNode->uwDirKey)
                    {
                        AIHC_DCF_DeleteFile(uwDelDirKey,uwDelFileKey,NULL);
                    }
                    else
                    {
                        DCF_FILE_NODE   *psFileNode;
                        DCF_DIR_NODE    *psDirNode;
                        if (AIHC_DCF_FindDir(NULL, uwDelDirKey, &psDirNode) == AHC_FALSE)
                        {
                            printc("Find Dir Node == FALSE %d\r\n",uwDelDirKey);
                        }
                        if (AIHC_DCF_FindFileNode(psDirNode, NULL, uwDelFileKey, &psFileNode) == AHC_TRUE ) {
		                    AIHC_DCF_RemoveFileNode(psDirNode, psFileNode, AHC_FALSE);
                        }else{
    	                    printc("Find File Node == FALSE %d\r\n",uwDelFileKey);
                        }
                        m_DcfDB[m_uiDBIndex].uwTotalFileCountInDir[uwDelDirKey - MIN_DCF_DIR_KEYNUM]--;
                        m_DcfDB[m_uiDBIndex].uiTotalFileCountInFileType[byDelFileType]--;
                        m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDelDirKey - MIN_DCF_DIR_KEYNUM]->uwFileCountInFileType[byDelFileType]--;
                        m_DcfDB[m_uiDBIndex].ppsFileCountInDir[uwDelDirKey - MIN_DCF_DIR_KEYNUM]->uwDCFxFileCount--;
                        AIHC_DCF_ClearEmptyDir((INT8*)chDirName,psDirNode);
                    }
                }
                else
                {
                    //make rename filename
                    memcpy(chRenameFileName, chFileName, strlen(chFileName));
                    memcpy(chRenameFileName, DCF_DEFAULT_FILE_FREECHAR, strlen(DCF_DEFAULT_FILE_FREECHAR));
                    //printc("byFileName %s\r\n",chFileName);
                    //Rename
                    ahc_ret = AHC_DCF_FileOperation((UINT8*)chPathName, (UINT8*)chFileName, DCF_FILE_RENAME, NULL, (UINT8*)chRenameFileName);
                    if(ahc_ret == AHC_FALSE)
                    {
                        printc("Rename failed\r\n");
                    }
                    //Delete the first slot file
                    ahc_ret = AHC_DCF_FileOperation((UINT8*)chPathName, (UINT8*)chRenameFileName, DCF_FILE_DELETE_ALL_CAM, NULL, NULL);
                    if(ahc_ret == AHC_FALSE)
                    {
                        printc("Delete failed\r\n");
                    }
                }
                if(bDeleteFile != NULL)
                {
                    *bDeleteFile = AHC_TRUE;
                }
            }
        }
    }  
    /*for(i=0;i<MAX_LOCK_FILE_NUM;i++)
    {
        printc("====m_ulLockFileTable[%d] 0x%x====\r\n",i,m_ulLockFileTable[i]);
        memset(chFileName,0,sizeof(chFileName));
    }
    printc("============================\r\n");*/
}
#endif

AHC_BOOL AHC_DCF_GetInfoFromCache(UINT32 uiIndex, DCF_INFO *Info)
{   
    AHC_BOOL error = AHC_TRUE;
    if(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].uiIndexPlus == uiIndex + 1){
        memcpy(Info, &(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].Info), sizeof(DCF_INFO));
    }
    else if(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].uiIndexPlus == DCF_RESET_VALUE){
        error = AHC_DCF_GetInfobyIndex(uiIndex, Info);
        InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].uiIndexPlus = uiIndex + 1;
        memcpy(&(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].Info), Info, sizeof(DCF_INFO));
    }
    else{
        memset(&(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT]), DCF_RESET_VALUE, sizeof(DCF_INFO_CACHE));
        error = AHC_DCF_GetInfobyIndex(uiIndex, Info);
        InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].uiIndexPlus = uiIndex + 1;
        memcpy(&(InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].Info), Info, sizeof(DCF_INFO));
    }
    //printc("InfoCacheData index %d\r\n",InfoCacheData[uiIndex%DCF_GETINFO_CACHE_COUNT].uiIndexPlus);
    return error;
}
#endif
