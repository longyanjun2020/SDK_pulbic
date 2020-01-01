// This is the main DLL file.

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include "FlashTranslater.h"

#ifdef __cplusplus 
extern "C" { 
#endif 

/* RAI */
#include "fms_rai.h"
#include "fms_rai_base.h"     /* frai_items_init */
#include "fms_rai_hash.h"     /* frai_hash_init */
#include "fms_rai_store.h"    /* frai_store_init */

/* FAT */
#include "fs_system.h"
#include "fs_browse.h"
#include "fs_stdio.h"

/* VFS */
#include "mdl_vfs_fat.ho"


#ifdef __cplusplus 
} 
#endif 


#define FMS_BASE_ADDRESS            (0x0C000000)
#define FMS_BASE_ADDR_MASK          (~FMS_BASE_ADDRESS)


#define FMS_AREA_MAXNUMBER          (11)
/* RAI info index in fms_DeviceMemUsage_t */
#define FMS_AREA_OBJECTS            (3)

#define FMS_FLASH_INFO_SIGNATURE    (0x12345678)

typedef struct fms_AreaLocus_t_
{
   u32 u32_StartAddr;
   u32 u32_Length;
} fms_AreaLocus_t;

#define FMS_FLASH_INFO_VERSION_1    (0x01000000)
#define FMS_FLASH_INFO_VERSION_2    (0x02000000)
#define FMS_FLASH_INFO_VERSION_3    (0x03000000)

/* Data structure for upload.info.bin */
/*  If the data structure needs to upgrade, we should do the following:
 *      1. Create one new version number, larger than the current one
 *      2. Add from the last field in fms_FlashInfo_t
 *      3. Sync with wintarget for dwl_b1.bin and DWLWin update
 *      4. In FileProspector project, use m_InfoVersion to isolate the new version handling
 *      5. Rebuild and update the FT_BUILD_VERSION to the new one
 */
typedef struct fms_FlashInfo_t_
{
    /* Version */
    u32 nVersion;               /* Version control */

/* FMS_FLASH_INFO_VERSION_1 - begin */
    /* fms_DeviceMemUsage_t */
    u32 u32_HighestCodeAddr;
    u32 u32_GsmCodeHighwater;
    fms_AreaLocus_t as_Areas[FMS_AREA_MAXNUMBER];

    /* Flash information */
    u32 nTotalFlashSize;        /* Total flash size */
    u32 nStartPos;              /* Start position of flash for upload.bin */
    u32 nSize;                  /* Size for upload.bin */
    u32 nSignature;             /* Signature for upload.info.bin */

    /* E2P information */
    u8  nRaiSectorNum;          /* E2P_OBJNUMBEROFSECTORS, WObjNumberOfSectors */
    u8  nCacheSize;             /* E2P_RAINUMBEROFENTRIES, WRaiEntriesNumber, unit is 0x100 */
    u8  nReserve1;              /* Reserve data */
    u8  nReserve2;              /* Reserve data */
/* FMS_FLASH_INFO_VERSION_1 - end */


/* FMS_FLASH_INFO_VERSION_2 - begin */

/* FMS_FLASH_INFO_VERSION_2 - end */


/* FMS_FLASH_INFO_VERSION_3 - begin */

/* FMS_FLASH_INFO_VERSION_3 - end */

} fms_FlashInfo_t;

RaiObjectClass::RaiObjectClass()   // Constructor
{
   nID = 0;
   nStatus = 0;
   nSize = 0;
   pnData = 0;
}

RaiObjectClass::~RaiObjectClass()   // Destructor
{
}

RaiObjectClass::RaiObjectClass(const RaiObjectClass &copyin)   // Copy constructor to handle pass by value.
{                             
   nID = copyin.nID;
   nStatus = copyin.nStatus;
   nSize = copyin.nSize;
   pnData = copyin.pnData;
}

RaiObjectClass& RaiObjectClass::operator=(const RaiObjectClass &rhs)
{
   this->nID = rhs.nID;
   this->nStatus = rhs.nStatus;
   this->nSize = rhs.nSize;
   this->pnData = rhs.pnData;
   return *this;
}

int RaiObjectClass::operator==(const RaiObjectClass &rhs) const
{
   if( this->nID != rhs.nID) return 0;
   if( this->nStatus != rhs.nStatus) return 0;
   if( this->nSize != rhs.nSize) return 0;
   if( this->pnData != rhs.pnData) return 0;
   return 1;
}

// This function is required for built-in STL list functions like sort
int RaiObjectClass::operator<(const RaiObjectClass &rhs) const
{
   if( this->nID < rhs.nID ) return 1;
   if( this->nID == rhs.nID && this->nStatus < rhs.nStatus) return 1;
   if( this->nID == rhs.nID && this->nStatus == rhs.nStatus && this->nSize < rhs.nSize) return 1;
   return 0;
}

FlashTranslaterClass::FlashTranslaterClass()
{
    // Initialize
    m_pnMem = NULL;
    m_pvHashMem = NULL;
    m_strRootPath[0] = NULL;

    m_nCacheSize = 0;
    m_nSectorNum = 0;
    m_nSectorSize = 0;

    m_nActiveObj = 0;
    m_nDeletedObj = 0;
    m_nCopyObj = 0;
    m_nOrphanObj = 0;

    m_InfoVersion = FT_BUILD_VERSION;
    m_Convert2VersionAsciiStr(m_strVersion, m_InfoVersion);
}

FlashTranslaterClass::~FlashTranslaterClass()
{
    if (m_pnMem)
        free(m_pnMem);
    if (m_pvHashMem)
        free(m_pvHashMem);
}

#define MS_HEADER_LEN 16

int FlashTranslaterClass::SetFlashFilePath(const wchar_t* szBinaryName, const wchar_t* szBinInfoName, const wchar_t* szNumSector)
{
    FILE * phFile;
    fms_FlashInfo_t sFlashInfo;
    int             iRet = TRUE;
	char szNumSectorTemp[10] = "\0";

    // Open upload.info.bin
    phFile = _wfopen(szBinInfoName, TEXT("rb"));
    if (phFile)
    {
        fread(&sFlashInfo, sizeof(sFlashInfo), 1, phFile);
        fclose(phFile);
    }
    else
    {
        cout << "Wrong Binary information file!!" << endl;
        return FALSE;
    }

    // Version control
    if (FT_BUILD_VERSION < sFlashInfo.nVersion)
    {
        char caBinStrVersion[FT_VERSION_STR_LEN];

        m_Convert2VersionAsciiStr(caBinStrVersion, sFlashInfo.nVersion);
        cout << "Wrong version!!" << endl;
        cout << "\n   Binary information version: " << caBinStrVersion << endl;
        cout << "\n   File prospector version: " << GetVersionAnsciiStr() << endl;
        return FALSE;
    }
    
    m_InfoVersion = sFlashInfo.nVersion;
    m_Convert2VersionAsciiStr(m_strVersion, m_InfoVersion);

    // Check signature
    if (FMS_FLASH_INFO_SIGNATURE != sFlashInfo.nSignature)
    {
        cout << "Wrong Signature information!!" << endl;
        return FALSE;
    }

    phFile = _wfopen(szBinaryName, TEXT("rb"));
    if (phFile)
    {
        size_t  nSize;
        // Check the size of upload.bin
        fseek(phFile, 0, SEEK_END);
        nSize = ftell(phFile);
        if ( (nSize - MS_HEADER_LEN) == sFlashInfo.nSize)
        {
            u32 nRaiOffset = (sFlashInfo.as_Areas[FMS_AREA_OBJECTS].u32_StartAddr & FMS_BASE_ADDR_MASK);
            u32 nRaiLength = sFlashInfo.as_Areas[FMS_AREA_OBJECTS].u32_Length;
            nRaiOffset -= (sFlashInfo.nStartPos & FMS_BASE_ADDR_MASK);
            fseek(phFile, nRaiOffset + MS_HEADER_LEN, SEEK_SET);
            m_pnMem = (u8*)malloc(nRaiLength);
            assert(m_pnMem != NULL);
            fread(m_pnMem, 1, nRaiLength, phFile);
            m_nCacheSize = sFlashInfo.nCacheSize;
#if 1 // Temporary number of section from argument[3]
			// get number of sector
			if(szNumSector)
			{
				uStrTo8bitStr((u8*)szNumSectorTemp, (u16*)szNumSector);
				m_nSectorNum = atoi(szNumSectorTemp);
			}
			else m_nSectorNum = 7;
			m_nSectorSize = nRaiLength/m_nSectorNum;
#else
            m_nSectorNum = sFlashInfo.nRaiSectorNum; // old fashion method doesn't work now. 2010/01/22
            m_nSectorSize = nRaiLength/m_nSectorNum;
#endif
        }
        else
        {
            cout << "Wrong Binary file!!" << endl;
            iRet = FALSE;
        }
        fclose(phFile);
    }
    else
    {
        cout << "Wrong Binary file!!" << endl;
        return FALSE;
    }

    // Check the validity of uplaod.bin
    if (TRUE == iRet)
    {
    }





    return iRet;
}

int FlashTranslaterClass::LoadRaiObjects()
{
    u8 l__u8_CacheSize = m_nCacheSize;
    u32 l__u32_SizeHashMan, l__u32_SizeItemsMan, l__u32_NumberOfSectors = m_nSectorNum;

    cout << "Load RAI objects using FMS library.." << endl;

    /* Compute the required memory sizes to allocate and round'em up */
    l__u32_SizeItemsMan = ((3+frai_store_query_size(l__u32_NumberOfSectors))/4)*4;
    l__u32_SizeHashMan =  ((3+frai_hash_query_size(l__u8_CacheSize*0x100)  )/4)*4;

    if (m_pvHashMem)
        free(m_pvHashMem);

    /* Get memory for hash table and sector information */
    m_pvHashMem = malloc(l__u32_SizeHashMan + l__u32_SizeItemsMan);
    assert(m_pvHashMem != NULL);

    /* Initialise hash, items and storage management */
    frai_hash_init(l__u8_CacheSize*0x100, m_pvHashMem);

    frai_items_init((void*)m_pnMem);

    frai_store_init(  (void*)m_pnMem, 
                      m_nSectorSize, 
                      l__u32_NumberOfSectors, 
                      (u8*)m_pvHashMem + l__u32_SizeHashMan,
                      this
                      );

    return 1;
}

#ifdef __cplusplus 
extern "C" { 
#endif 

/* Use as callback function from frai_store_init */
void ftAddRaiToList(void* hFt, frai_item_status_t sStatus, fms_rai_id_t nID,
                    fms_rai_size_t nSize, u8* pnData)
{
    RaiObjectClass sRai;
    FlashTranslaterClass    *pFt;
    pFt = (FlashTranslaterClass*)hFt;

    sRai.nID = nID;
    sRai.nStatus = (u16)sStatus;
    sRai.nSize = nSize;
    sRai.pnData = pnData;

    pFt->Add2RaiList(&sRai);
}

#ifdef __cplusplus 
} 
#endif 


int FlashTranslaterClass::Add2RaiList(RaiObjectClass *psRai)
{
    switch (psRai->nStatus)
    {
    case FRAI_STATUS_ACTIVE:
        m_nActiveObj++;
        break;
    case FRAI_STATUS_DELETED:
        m_nDeletedObj++;
        break;
    case FRAI_STATUS_COPY:
        m_nCopyObj++;
        break;
    case FRAI_STATUS_ORPHAN:
        m_nOrphanObj++;
        break;
    default:
        assert(0);
        break;
    }

    m_sRaiList.push_back(*psRai);

    return TRUE;
}

int FlashTranslaterClass::DumpRaiObjects()
{


    cout << "Dump RAI object to PC.." << endl;

    m_sRaiList.sort();

    {
        list<RaiObjectClass>::iterator itRai;
        int iIdx = 0;
        fms_rai_id_t nPreID = 0;
        wchar_t strCurDir[MAX_PATH] = {0}, strTmp[MAX_PATH] = {0};

        GetCurrentDirectory(MAX_PATH, strCurDir);
        uStrcat((u16*)strCurDir, (u16*)TEXT("\\Dump"));
        CreateDirectory(strCurDir, NULL);
        uStrcat((u16*)strCurDir, (u16*)TEXT("\\RAIObjects"));
        CreateDirectory(strCurDir, NULL);
        uStrcat((u16*)strCurDir, (u16*)TEXT("\\"));

        for( itRai=m_sRaiList.begin(); itRai != m_sRaiList.end(); ++itRai)
        {
            if (nPreID == itRai->nID)
                iIdx++;
            else
                iIdx = 0;
            switch (itRai->nStatus)
            {
            case FRAI_STATUS_ACTIVE:
                wsprintf(strTmp, TEXT("%s%08X_Active.bin"), strCurDir, itRai->nID, itRai->nID);
                break;
            case FRAI_STATUS_DELETED:
                wsprintf(strTmp, TEXT("%s%08X_Deleted_%d.bin"), strCurDir, itRai->nID, iIdx);
                break;
            case FRAI_STATUS_COPY:
                wsprintf(strTmp, TEXT("%s%08X_Copy_%d.bin"), strCurDir, itRai->nID, iIdx);
                break;
            case FRAI_STATUS_ORPHAN:
                wsprintf(strTmp, TEXT("%s%08X_Orphan_%d.bin"), strCurDir, itRai->nID, iIdx);
                break;
            default:
                assert(0);
                break;
            }
            nPreID = itRai->nID;
            m_DumpMem2File(strTmp, itRai->pnData, itRai->nSize-sizeof(fms_rai_id_t));
        }
    }

    return TRUE;
}

int FlashTranslaterClass::LoadFatLibrary()
{
    u8  				nNum;
    u32 				*pnList;
    u16					strName[VFS_MAX_VOL_NAME_LEN + 1];

    cout << "Load FAT service using FAT and VFS library.." << endl;

    // Init NOR FS
    fs_init(15);

    fat_N_list_volumes(&nNum, &pnList);
    fat_N_mount(VFS_VOL_NOR);
    fat_N_get_volume_name(VFS_VOL_NOR, strName);

    m_strRootPath[0] = NULL;
    uStrAddChar(m_strRootPath, VFS_SEPARATOR_CHR);
    uStrcat(m_strRootPath, strName);

    return 1;
}

int FlashTranslaterClass::LoadFileTree()
{
    File_List_Head_t	*spList = NULL;
    s32 				iIdx;
    VFS_File_Info_t     sInfo;
    u16                 strPath[MAX_CHAR_LFN + 1] = {0};
    FileList_t          sTempList;
    FileInfo_t          sTempInfo;
    bool                bIsRoot = true;

    cout << "Load file tree.." << endl;

    // Root
    uStrcpy(sTempInfo.strPath, m_strRootPath);
    uStrAddChar(sTempInfo.strPath, VFS_SEPARATOR_CHR);
    sTempList.push_back(sTempInfo);

    while (!sTempList.empty())
    { // Browse file/directory tree
    	uStrcpy(strPath, sTempList.back().strPath); // Prepare absolute path
        fat_N_change_dir(strPath, &spList);
        sTempList.pop_back();
        for (iIdx = 0; iIdx < fat_N_get_nb_files(spList); iIdx++)
        {
            fat_N_get_file_info(spList, iIdx, &sInfo);
            uStrcpy(sTempInfo.strPath, strPath);
            if (false == bIsRoot)
                uStrAddChar(sTempInfo.strPath, VFS_SEPARATOR_CHR);
            uStrcat(sTempInfo.strPath, sInfo.Long_File_Name);

            m_fileList.push_back(sTempInfo);
            if (sInfo.Attributes & A_SUBDIR)
			    sTempList.push_back(sTempInfo);
        }
        bIsRoot = false;
        fat_N_free_list(spList);
    }

    return 1;
}

void FlashTranslaterClass::m_StrReplace(u16 *pnPath, u16 nFrom, u16 nTo)
{
	while(*pnPath != 0)
	{
		if (*pnPath == nFrom)
            *pnPath = nTo;
        pnPath++;
	}
}

int FlashTranslaterClass::DumpFileTree()
{
    wchar_t strCurDir[MAX_PATH] = {0}, strTmp[MAX_PATH] = {0};
    FileList_t::iterator iterFile;
    File_Simple_Info_t sInfo;

    cout << "\nDump file tree to PC.." << endl;

    GetCurrentDirectory(MAX_PATH, strCurDir);
    uStrcat((u16*)strCurDir, (u16*)TEXT("\\Dump"));
    CreateDirectory(strCurDir, NULL);
    uStrcpy((u16*)strTmp, (u16*)strCurDir);

    uStrcat((u16*)strCurDir, m_strRootPath);
    m_StrReplace((u16*)strCurDir, VFS_SEPARATOR_CHR, '\\');
    CreateDirectory(strCurDir, NULL);
    uStrcpy((u16*)strCurDir, (u16*)strTmp); // strCurDir: ~\Dump

    for (iterFile=m_fileList.begin(); iterFile!=m_fileList.end(); iterFile++)
    {
        uStrcpy((u16*)strTmp, (u16*)strCurDir);
        if (FAT_NO_ERROR == fat_N_get_file_info_by_name((*iterFile).strPath, &sInfo))
        {
            uStrcat((u16*)strTmp, (*iterFile).strPath);
            m_StrReplace((u16*)strTmp, VFS_SEPARATOR_CHR, '\\');
            if (sInfo.Attributes & A_SUBDIR)
            {
                CreateDirectory(strTmp, NULL);
            }
			else
            {
                u8      *pnMem;
                s32     iFid;

                iFid = fat_N_open((*iterFile).strPath, O_RDONLY);
                if (iFid >= 0)
                {
                    pnMem = (u8*)malloc(sInfo.Size);
                    assert(pnMem != NULL);
                    fat_N_read(iFid, pnMem, sInfo.Size);
                    m_DumpMem2File(strTmp, pnMem, sInfo.Size);
                    fat_N_close(iFid);
                    free(pnMem);
                }
                else
                {
                    assert(0);
                }
            }
        }
    }

    return 1;
}

int FlashTranslaterClass::DumpStatistics()
{
    TCHAR   strTmp[MAX_PATH] = {0};
    FILE    *phFile;
    u32 	nFree = 0, nTotal = 0;
    fms_rai_stats_t     sRai;

    cout << "\nDump statistics information to PC.." << endl;

    GetCurrentDirectory(MAX_PATH, strTmp);
    uStrcat((u16*)strTmp, (u16*)TEXT("\\Dump\\statistics.txt"));

    fat_N_get_volume_space_info(VFS_VOL_NOR, &nTotal, &nFree);
    phFile = _wfopen(strTmp, TEXT("w"));

    fms_rai_stats(&sRai);

    if (phFile)
    { /* Dump information */
        fprintf(phFile, "RAI information:\n");
        fprintf(phFile, "\tlength: %d, sector number: %d, secotr size: %d\n", m_nSectorNum*m_nSectorSize, m_nSectorNum, m_nSectorSize);
        fprintf(phFile, "\ttotal dump objects number: %d\n", m_sRaiList.size());
        fprintf(phFile, "\t\tactive objects number: %d, deleted objects number: %d\n", m_nActiveObj, m_nDeletedObj);
        fprintf(phFile, "\t\tcopy objects number: %d, orphan objects number: %d\n", m_nCopyObj, m_nOrphanObj);
        
        fprintf(phFile, "\ttotal byte amount of immediately available memory: %d\n", sRai.mem_free);
        fprintf(phFile, "\tbyte amount of immediately available CONTIGUOUS memory: %d\n", sRai.mem_contig);
        fprintf(phFile, "\tbyte amount of memory available after complete garbage collection: %d\n", sRai.mem_avail);
        fprintf(phFile, "\ttotal storage byte space: %d\n", sRai.mem_limit);

        fprintf(phFile, "\nNOR FS information:\n");
        fprintf(phFile, "\ttotal size: %d, free size: %d\n", nTotal, nFree);
        fprintf(phFile, "\tfile/directory number: %d\n", m_fileList.size());
        fclose(phFile);
    }

    /* Dump RAI raw data */
    GetCurrentDirectory(MAX_PATH, strTmp);
    uStrcat((u16*)strTmp, (u16*)TEXT("\\Dump\\rai_raw.bin"));
    m_DumpMem2File(strTmp, m_pnMem, m_nSectorNum*m_nSectorSize);


    return 1;
}

void FlashTranslaterClass::m_DumpMem2File(wchar_t *pnPath, u8 *pnMem, s32 iSize)
{
    FILE    *phFile;

    phFile = _wfopen((wchar_t*)pnPath, TEXT("wb"));

    cout << "." ;

    if (phFile)
    {
        fwrite(pnMem, iSize, 1, phFile);
        fclose(phFile);
    }
    else
    {
        assert(0);
    }
}

int FlashTranslaterClass::m_Convert2VersionAsciiStr(char * pcOut, u32 nVersion)
{
    sprintf(pcOut, "%d.%d.%d.%d", 
        (nVersion >> 24) & 0xFF,
        (nVersion >> 16) & 0xFF,
        (nVersion >> 8) & 0xFF,
        (nVersion >> 0) & 0xFF        
        );
    return TRUE; 
}

u32 FlashTranslaterClass::GetVersion()
{
    return m_InfoVersion;
}

char * FlashTranslaterClass::GetVersionAnsciiStr()
{
    return m_strVersion;
}