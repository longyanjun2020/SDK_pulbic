// FlashTranslater.h

#pragma once

#include <vector>
#include <list>
using namespace std;

/* Build version, IMPORTANT, this should be sync with WinTarget */
#define FT_BUILD_VERSION        (0x01000000)

/* ex. 3.5.7.13 */
#define FT_VERSION_STR_LEN      (20)

#define FT_MAX_CHAR_LFN         (256)


typedef struct FileInfo_t_
{
    u16     strPath[FT_MAX_CHAR_LFN + 1];
} FileInfo_t;

typedef std::vector<FileInfo_t>  FileList_t;

class RaiObjectClass
{
   public:
      u32   nID;
      u16   nStatus;
      u16   nSize;
      u8*   pnData;

      RaiObjectClass();
      RaiObjectClass(const RaiObjectClass &);
      ~RaiObjectClass();
      RaiObjectClass &operator=(const RaiObjectClass &rhs);
      int operator==(const RaiObjectClass &rhs) const;
      int operator<(const RaiObjectClass &rhs) const;
};

class FlashTranslaterClass
{
public:
	FlashTranslaterClass();
    virtual ~FlashTranslaterClass();

    /* Entry point: Input: upload.bin, upload.info.bin */
    int SetFlashFilePath(const wchar_t* szBinaryName, const wchar_t* szBinInfoName, const wchar_t* szNumSector);

    /* Load RAI objects using FMS library */
    int LoadRaiObjects();

    /* Add one RAI object to m_sRaiList */
    int Add2RaiList(RaiObjectClass *psRai);

    /* Load FAT service using FAT and VFS library */
    int LoadFatLibrary();

    /* Load file tree to m_fileList */
    int LoadFileTree();

    /* Dump RAI object to PC */
    int DumpRaiObjects();

    /* Dump file tree to PC */
    int DumpFileTree();

    /* Dump statistics information to PC */
    int DumpStatistics();

    /* Return the version number (u32) */
    u32 GetVersion();

    /* Return the version number (char *) */
    char * GetVersionAnsciiStr();

private:
    u32         m_InfoVersion;                  /* Version control for backward compatible */
    u8          *m_pnMem;                       /* Memory buffer for NOR flash on RAI region */
    void        *m_pvHashMem;                   /* Hash table buffer */
    u16         m_strRootPath[FT_MAX_CHAR_LFN + 1];    /* Root path, /NOR_Flash */

    /* Information from upload.info.bin */
    u8          m_nCacheSize;                   /* WRaiEntriesNumber, unit is 0x100 */
    u8          m_nSectorNum;                   /* WObjNumberOfSectors */
    u32         m_nSectorSize;                  /* nRaiLength/m_nSectorNum */

    /* STL list for RAI objects */
    list<RaiObjectClass>    m_sRaiList;
    int         m_nActiveObj;                   /* Total number of Active RAI objects */
    int         m_nDeletedObj;                  /* Total number of Deleted RAI objects */
    int         m_nCopyObj;                     /* Total number of Copy RAI objects */
    int         m_nOrphanObj;                   /* Total number of Orphan RAI objects */

    /* STL vector for file tree */
    FileList_t  m_fileList;

    /* For version string display */
    char        m_strVersion[FT_VERSION_STR_LEN];

    /* Sub functions */
    void m_StrReplace(u16 *pnPath, u16 nFrom, u16 nTo);   /* Replace nFrom by nTo in pnPath */
    void m_DumpMem2File(wchar_t *pnPath, u8 *pnMem, s32 iSize);     /* Dump memory to file */
    int  m_Convert2VersionAsciiStr(char * pcOut, u32 nVersion);     /* Convert u32 Version to ASCII string */
};
