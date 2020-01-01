//==============================================================================
//
//  File        : mmps_fs.c
//  Description : File System Functions (Host Application Interface).
//  Author      : Ricky Yeh
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_fs.c
 *  @brief The File System control functions
 *  @author Ricky Yeh, Sunny 
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
 
#include "mmp_lib.h"
#include "mmps_fs.h"
//#include "ait_utility.h"
#if (FORMAT_FREE_ENABLE)
#include "lib_retina.h"      //adding for use "extern" & "RTNA_DBG_Str" & "RTNA_DBG_Long"
#endif
#include "ahc_rtc.h"
#include "fs_cfg.h"

#define FS_USE_ICE  (0)

/** @addtogroup MMPS_FS
@{
*/
//==============================================================================
//
//								GLOBAL VARIABLES
//
//==============================================================================
#if (AHC_FS_SDNEWCACHE) //(FS_NEWBUFFER)
//extern FS_CACHE_INFO	SDCacheInfo;
extern   void *FS__FindCacheObjectMap(const FS_DEVICE_TYPE  *pSourceDeviceType);
#if(NEWCACHEDEBUGVIEW)
MMP_ULONG	ulgSDLinFirstDataSector = 0xFFFFFFFF;
MMP_ULONG	ulgSDHiddenSector = 0xFFFFFFFF;
#endif
#endif
//==============================================================================
//
//								EXTERN VARIABLE
//
//==============================================================================

#if (FORMAT_FREE_ENABLE)
extern  MMP_UBYTE   gubFormatFreeON;
extern  MMP_UBYTE   gubFolderNUM ;
extern  MMP_BYTE   FolderNameMatrix[FormatFreeFolderNumMAX][NameLenghLimit];
extern  FormatFreeFolderConfig   gbFolderConfig[FormatFreeFolderNumMAX];
//extern	int   _CalcNumLongEntries(const char * sLongName, int Len);
//extern	U64   ArrayAccumulation(MMP_ULONG * ArrayName,MMP_ULONG ArrayIndex);
//extern	  MMP_ERR  MMPF_FS_FormatFreeFATTable(FS_VOLUME  * pVolume , MMP_ULONG FileNoSUM); 
extern  int   _UTF8_StrLen(const char* s);
//extern  char * FS__strchrReverseFind( char *s, int c);
extern  MMP_UBYTE   gbWriteDataOnly;
//extern  void   (MMPF_FileSystem_FileNameRequire) (MMP_UBYTE	FolderIndex,MMP_UBYTE FileIndex,MMP_BYTE * pFileName);
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileOpen
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_OPEN  SUB(0x00)
//------------------------------------------------------------------------------
/**
 * @brief                 Opens an existing file or creates a new file depending on parameters.
 *
 * @param[in ] bFileName  Fully qualified file name.
 * @param[in ] ulNameSize The length, in bytes, of FileName string,including the terminating null character.
 * @param[in ] bMode      Mode string for opening the file.
 * @param[in ] ulModeSize The length, in bytes, of Mode string, including the terminating null characher.
 * @param[out] ulFileId   Return file id.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 *
 * @remarks               A fully qualified file name means:
 * @remarks \b            [DevName:[UnitNum:]][DirPathList]FileName
 * @remarks \arg \a       DevName is the name of a device. If not specified, the first device in volume table will be used.
 * @remarks \arg \a       UnitNum is the number of the unit for this device. If not specified, unit 0 will be used.
 * @remarks \arg \a       DirPathList means a complete path to an already existing subdirectory. The
 *                        path must start and end with a '\\' characher. If DirPathList is not specified,
 *                        the root directory on the device will be used.
 * @remarks \arg \a       FileName has to follow the standard FAT naming convertions.(8.3 or long file name)
 *
 * @remarks               The parameter \a bpMode points to a string. If the string is one of the following, file system
 *                        will open the file in the indicated mode.
 * @remarks \arg \b r     Open text file for reading.
 * @remarks \arg \b w     Truncate to zero length or create text file for writing.
 * @remarks \arg \b a     Append; open or create text file for writing at end-of-file.
 * @remarks \arg \b rb    Open binary file for reading.
 * @remarks \arg \b wb    Truncate to zero length or create binary file for writing.
 * @remarks \arg \b ab    Append; open or create binary file for writing at end-of-file.
 * @remarks \arg \b r+    Open text file for update (reading and writing).
 * @remarks \arg \b w+    Truncate to zero length or create text file for update.
 * @remarks \arg \b a+    Append; open or create text file for update, writing at end-of-file.
 * @remarks \arg \b r+b or \b rb+    Open binary file for update (reading and writing).
 * @remarks \arg \b w+b or \b wb+    Truncate to zero length or create binary file for update.
 * @remarks \arg \b a+b or \b ab+    Append; open or create bin file for update, writing at end-of-file.
 *
 * @remarks \a \b         Note! File system does not distinguish between binary and text mode, files are
 *                        always accessed in binary mode.
 */
MMP_ERR MMPS_FS_FileOpen(MMP_BYTE *bFileName, MMP_ULONG ulNameSize,
                         MMP_BYTE *bMode, MMP_ULONG ulModeSize, MMP_ULONG *ulFileId)
{
	MMPS_FS_SetCreationTime();
    return MMPD_FS_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileClose
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_CLOSE  SUB(0x01)
//------------------------------------------------------------------------------
/**
 * @brief                 Close an open file.
 *
 * @param[in ] ulFileId   The file id which we want to close.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileClose(MMP_ULONG ulFileId)
{
    return MMPD_FS_FileClose(ulFileId);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileRead
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_READ  SUB(0x02)
//------------------------------------------------------------------------------
/**
 * @brief                 Reads data from an open file.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[out] ubData       Pointer to a data buffer for storing data transferred from file.
 * @param[in ] ulNumBytes   Number of bytes to be transferred from the file.
 * @param[out] ulReadCount  Number of bytes read.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
MMP_ERR MMPS_FS_FileRead(MMP_ULONG ulFileId, MMP_UBYTE *ubData,
                         MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount)
{
    if (ulNumBytes == 0)
        return MMP_FS_ERR_READ_FAIL;

    return MMPD_FS_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileWrite
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_WRITE  SUB(0x03)
//------------------------------------------------------------------------------
/**
 * @brief                 Writes data to an open file.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[in ] ubData       Pointer to data to be written to the file.
 * @param[in ] ulNumBytes   Number of bytes to be transferred to the file.
 * @param[out] ulWriteCount Number of bytes read.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileWrite(MMP_ULONG ulFileId, MMP_UBYTE *ubData,
                          MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount)
{
    if (ulNumBytes == 0)
        return MMP_FS_ERR_WRITE_FAIL;

    return MMPD_FS_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileSeek
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_SEEK  SUB(0x04)
//------------------------------------------------------------------------------
/**
 * @brief                 Set current position of the file pointer.
 *
 *                        This function moves the file pointer to a new location that is offset bytes from ulOrigin.
 *
 * @param[in ] ulFileId   File id which has already opened.
 * @param[in ] llOffset   Offset for setting the file pointer position.
 * @param[in ] ulOrigin   Mode for positioning file pointer.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 *
 * @remarks               Valid values for parameter \a ulOrigin are:
 * @remarks \arg \b       MMPS_FS_SEEK_SET The starting point is zero or the beginning of the file.
 * @remarks \arg \b       MMPS_FS_SEEK_CUR The start point is the current value of the file pointer.
 * @remarks \arg \b       MMPS_FS_SEEK_END The starting point is the current end-of-file position.
 */
MMP_ERR MMPS_FS_FileSeek(MMP_ULONG ulFileId, MMP_LONG64 llOffset, MMP_ULONG ulOrigin)
{
    return MMPD_FS_FileSeek(ulFileId, llOffset, ulOrigin);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileTell
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_TELL  SUB(0x05)
//------------------------------------------------------------------------------
/**
 * @brief                 Return current position of the file pointer.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[out] lFilePos     Current position of file pointer in the file.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileTell(MMP_ULONG ulFileId, MMP_LONG64 *llFilePos)
{
    return MMPD_FS_FileTell(ulFileId, llFilePos);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileCopy
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_COPY  SUB(0x06)
//------------------------------------------------------------------------------
/**
 * @brief                 Copy an existing file to a new file.
 *
 * @param[in ] bSrc        Pointer to a string that specifies the name of an existing file.
 * @param[in ] ulSrcSize   The length, in bytes, of bpSrc string, including the terminating null character.
 * @param[in ] bDest       Pointer to a string that specifies the name of the new file. The file should not exist
 * @param[in ] ulDestSize  The length, in bytes, of bpDest string, including the terminating null characher.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileCopy(MMP_BYTE *bSrc, MMP_ULONG ulSrcSize,
                         MMP_BYTE *bDest,MMP_ULONG ulDestSize)
{
    return MMPD_FS_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileTruncate
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_TRUNCATE  SUB(0x07)
//------------------------------------------------------------------------------
/**
 * @brief                 Truncates an file to the specified size.
 *
 *                        The function truncates a file. Be sure the file is not open yet before use. Opened file
 *                        should not call this function.
 *
 * @param[in ] ulFileId   File id which has already opened. file should be opened at 'a' mode
 * @param[in ] ulNewSize  New size of the file.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileTruncate(MMP_ULONG ulFileId, MMP_ULONG ulNewSize)
{
    return MMPD_FS_FileTruncate(ulFileId, ulNewSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileGetSize
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_GET_SIZE  SUB(0x08)
//------------------------------------------------------------------------------
/**
 * @brief                 Get the current file size of a file.
 *
 * @param[in ] ulFileId     The file id which we want to get file size.
 * @param[out] ulFileSize  retrieves file size.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileGetSize(MMP_ULONG ulFileId, MMP_ULONG64 *ulFileSize)
{
    return MMPD_FS_FileGetSize(ulFileId, ulFileSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileRemove
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_REMOVE  SUB(0x09)
//------------------------------------------------------------------------------
/**
 * @brief                 Removes file from the media.
 *
 * @param[in ] bpFileName  Pointer to a string that specifies the name of an existing file which we want to remove.
 * @param[in ] ulNameSize   The length, in bytes, of bpFileName string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileRemove(MMP_BYTE *bpFileName, MMP_ULONG ulNameSize)
{
    return MMPD_FS_FileRemove(bpFileName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirGetAttributes
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETATTRIBUTES  SUB(0x0A)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves attributes for a specified file or directory.
 *
 * @param[in ] bpName      	Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute	retrieves the attributes value.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPS_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPS_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPS_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPS_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       MMPS_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPS_FS_FileDirGetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE *attribute)
{
    return MMPD_FS_FileDirGetAttribute(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE *)attribute);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirGetInfo
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETINFO  SUB(0x2A)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves attributes/time and file size for a specified file or directory
 *
 * @param[in ] bpName      	Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute	retrieves the attributes value.
 * @param[out] timestructure retrieves time structure.
 * @param[out] ulpFileSize	retrieves the file size. If the input is a directory, then return 0
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPS_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPS_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPS_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPS_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       MMPS_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPS_FS_FileDirGetInfo(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE *attribute, MMPS_FS_FILETIME *timestructure, MMP_ULONG *ulpFileSize)
{
    MMP_ERR status;
    MMP_ULONG ulTimeStamp;

	status = MMPD_FS_FileDirGetInfo(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulpFileSize);
	if (status == MMP_ERR_NONE) {
        _TimeStamp2FileTime(ulTimeStamp, timestructure);
    }
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirGetFileTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETFILETIME  SUB(0x0B)

//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves time structure for a specified file or directory.
 *
 * @param[in ] bpName			Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize		The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] timestructure	Retrieves time structure.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileDirGetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_FILETIME *timestructure)
{
    MMP_ERR status;
    MMP_ULONG ulTimeStamp;

    status = MMPD_FS_FileDirGetTime(bpName, ulNameSize, &ulTimeStamp);
    if (status == MMP_ERR_NONE) {
        _TimeStamp2FileTime(ulTimeStamp, timestructure);
    }
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirMove
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_MOVE  SUB(0x0C)
//------------------------------------------------------------------------------
/**
 * @brief                 Moves an existing file or a directory, including its childen.
 *
 * @param[in ] bpNameSrc   Pointer to a string that names an existing file or directory.
 * @param[in ] ulSrcSize    The length, in bytes, of pFullNameSrc string, including the terminating null character.
 * @param[in ] bpNameDest  Pointer to a string that specifies the name of the new file or directory.
 * @param[in ] ulDestSize   The length, in bytes, of pFullNameDest string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileDirMove(MMP_BYTE *bpNameSrc, MMP_ULONG ulSrcSize,
                            MMP_BYTE *bpNameDest,MMP_ULONG ulDestSize)
{
    return MMPD_FS_FileDirMove(bpNameSrc, ulSrcSize, bpNameDest, ulDestSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirRename
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_RENAME  SUB(0x0D)
//------------------------------------------------------------------------------
/**
 * @brief                 Renames an existing file or a directory.
 *
 * @param[in ] bpOldName   Pointer to a string that names an existing file or directory.
 * @param[in ] ulOldNameSize The length, in bytes, of bpOldName string, including the terminating null character.
 * @param[in ] bpNewName   Pointer to a string that specifies the name of the new file or directory.
 * @param[in ] ulNewNameSize The length, in bytes, of bpNewName string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               bpNewName should point to a fullpath name and new file should locate in the same
 *						  dir
 *
 */
MMP_ERR MMPS_FS_FileDirRename(MMP_BYTE *bpOldName, MMP_ULONG ulOldNameSize,
                              MMP_BYTE *bpNewName, MMP_ULONG ulNewNameSize)
{
    return MMPD_FS_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirSetAttributes
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_SETATTRIBUTES  SUB(0x0E)
//------------------------------------------------------------------------------
/**
 * @brief                 Set attributes for a specified file or directory.
 *
 * @param[in ] bpName      Pointer to a string that names an existing file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] attribute 	attribute to be set to the file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPS_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPS_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPS_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPS_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPS_FS_FileDirSetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_ATTRIBUTE attribute)
{
    return MMPD_FS_FileDirSetAttribute(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE)attribute);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_FileDirSetFileTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_SETFILETIME  SUB(0x0F)
//------------------------------------------------------------------------------
/**

 * @brief                 Set the time structure for a specified file or directory.
 *
 * @param[in ] bpName		Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize	The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] time			Pointer to a time structure to be set to file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_FileDirSetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPS_FS_FILETIME* fsTime)
{
    MMP_ULONG ulTimeStamp;

    _FileTime2TimeStamp(fsTime, &ulTimeStamp);

    return MMPD_FS_FileDirSetTime(bpName, ulNameSize, ulTimeStamp);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirClose
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_CLOSE  SUB(0x10)
//------------------------------------------------------------------------------
/**
 * @brief                 This function close a directory referred by parameter usDirId.
 *
 * @param[in ] ulDirID      Directory ID which we want to close.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_DirClose(MMP_ULONG ulDirID)
{
    return MMPD_FS_DirClose(ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirGetNumFiles
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_GETNUMFILES  SUB(0x15)
//------------------------------------------------------------------------------
/**
 * @brief                 The function retrieves the number of files in a opened directory.
 *
 * @param[in ] ulDirID      Directory ID
 * @param[out] ulFileCount  Retrieves the number of files in a directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_DirGetNumFiles(MMP_ULONG ulDirID, MMP_ULONG *ulFileCount)
{
    return MMPD_FS_DirGetNumFiles(ulDirID, ulFileCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirCreate
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_CREATE  SUB(0x16)
//------------------------------------------------------------------------------
/**
 * @brief                 Creates a new directory.
 *
 * @param[in ] bDirName   Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize   The length, in bytes, of bpDirName string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 * @remarks               Note!! This function will not create the whole bpDirName,it will only create a directory in an already existing path.
 * @remarks               A fully qualified file name means:
 * @remarks \b            [DevName:[UnitNum:]][DirPathList]DirectoryName
 * @remarks \arg \a       DevName is the name of a device. If not specified, the first device in volume table will be used.
 * @remarks \arg \a       UnitNum is the number of the unit for this device. If not specified, unit 0 will be used.
 * @remarks \arg \a       DirPathList means a complete path to an already existing subdirectory. The
 *                        path must start and end with a '\\' characher. If DirPathList is not specified,
 *                        the root directory on the device will be used.
 * @remarks \arg \a       DirectoryName and all directory names have to follow the standard FAT naming convertions(8.3 or long file name),
 *                        if support for long file names is not enabled.
 */
MMP_ERR MMPS_FS_DirCreate(MMP_BYTE *bDirName, MMP_ULONG ulNameSize)
{
	MMPS_FS_SetCreationTime();
    return MMPD_FS_DirCreate(bDirName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirOpen
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_OPEN  SUB(0x17)
//------------------------------------------------------------------------------
/**
 * @brief                 Open an existing directory for reading.
 *
 * @param[in ] bDirName    Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize  The length, in bytes, of bpDirName string, including the terminating null character.
 * @param[out] ulDirID     Retrieves opened directory id.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 * @remarks               A fully qualified directory name means:
 * @remarks \b            [DevName:[UnitNum:]][DirPathList]DirectoryName
 * @remarks \arg \a       DevName is the name of a device. If not specified, the first device in volume table will be used.
 * @remarks \arg \a       UnitNum is the number of the unit for this device. If not specified, unit 0 will be used.
 * @remarks \arg \a       DirPathList means a complete path to an already existing subdirectory. The
 *                        path must start and end with a '\\' characher. If DirPathList is not specified,
 *                        the root directory on the device will be used.
 * @remarks \arg \a       DirectoryName and all directory names have to follow the standard FAT naming convertions(8.3 or long file name),
 *                        if support for long file names is not enabled.
 */
MMP_ERR MMPS_FS_DirOpen(MMP_BYTE *bDirName, MMP_ULONG ulNameSize, MMP_ULONG *ulDirID)
{
    return MMPD_FS_DirOpen(bDirName, ulNameSize, ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirRewind
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_REWIND  SUB(0x19)
//------------------------------------------------------------------------------
/**
 * @brief                 This function sets pointer for reading the next directory entry to the \b first \b entry in the directory.
 *
 * @param[in ] ulDirID      Directory ID
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_DirRewind(MMP_ULONG ulDirID)
{
    return MMPD_FS_DirRewind(ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirRemove
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_REMOVE  SUB(0x1A)
//------------------------------------------------------------------------------
/**
 * @brief                 Deletes a directory.
 *
 * @param[in ] bpDirName   Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize   The length, in bytes, of bpDirName string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 * @remarks               This function will only delete a directory if it is empty.
 */
MMP_ERR MMPS_FS_DirRemove(MMP_BYTE *bpDirName, MMP_ULONG ulNameSize)
{
    return MMPD_FS_DirRemove(bpDirName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_HighLevelFormat
//  Description : HIF_USR_CMD_FS_ACCESS | FS_HIGH_LEVLE_FORMAT  SUB(0x1C)
//------------------------------------------------------------------------------
/**
 * @brief                 High-level formats a device.
 *
 *                        This means putting the management information required by the file system on the medium.
 *                        In case of FAT, this means primarily initialization of FAT and root directory, as well as the Bios parameter block.
 *
 * @param[in ] bpDevice    Name of the device to format.
 * @param[in ] ulNameSize   The length, in bytes, of bpDevice string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_HighLevelFormat(MMP_BYTE *bpDevice, MMP_ULONG ulNameSize)
{
    return MMPD_FS_HighLevelFormat(bpDevice, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetFreeSpace
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_FREE_SPACE  SUB(0x1D)
//------------------------------------------------------------------------------
/**
 * @brief                 Get amount of free space on a specific volume.
 *
 *                        Note that free space larger than 4 gigabyte(GB) is reported as 0xFFFFFFFF since a MMP_ULONG
 *                        can not represent bigger values. If you don't need to know if there is more than 4 GB of free
 *                        space available, you can still reliably use this function.
 *
 * @param[in ] bpVolume    Pointer to a string that specifies the volume name.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ulpFreeBytes Retrieve the amount of free space in bytes.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 * @remarks               Valid volume name means:
 * @remarks               [DevName:[UnitNum:]]
 * @remarks \arg \a       DevName is the name of a device. If not specified, the first device in the volume table will be used.
 * @remarks \arg \a       UnitNum is the number of the unit of the device. If not specified, unit 0 will be used.
 * @remarks \b            Note that it is not allowed to specify \a UnitNum if \a DevName has not been specified.
 */
MMP_ERR MMPS_FS_GetFreeSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpFreeBytes)
{
    return MMPD_FS_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetTotalSpace
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_TOTAL_SPACE  SUB(0x1E)
//------------------------------------------------------------------------------
/**
 * @brief                 Get amount of total size of a specific volume.
 *
 *                        Note that volume sizes larger than 4 GB are reported as 0xFFFFFFFF since a MMP_ULONG
 *                        can not represent bigger values. If you don't need to know if the total space is bigger
 *                        than 4GB, you can still reliably use this function.
 *
 * @param[in ] bpVolume    Pointer to a string that specifies the volume name.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ulpTotal     Retrieves the volume size in bytes.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_GetTotalSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpTotal)
{
    return MMPD_FS_GetTotalSpace(bpVolume, ulNameSize, ulpTotal);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetNumVolumes
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_NUM_VOLUMES  SUB(0x1F)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves the number of available volumes.
 *
 *                        This function can be used to get the name of each available volume.
 *
 * @param[out] lpNumVols   Retrieves the number of available volumes.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_GetNumVolumes(MMP_LONG *lpNumVols)
{
    return MMPD_FS_GetNumVolumes(lpNumVols);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetVolumeName
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_VOLUME_NAME  SUB(0x20)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves the name of specified volume.
 *
 *                        This function can be used to get the name of each available volume.
 *
 * @param[in ] lIndex      lIndex number of the volume.
 * @param[out] bpBuffer    Pointer to a buffer that receives the null-terminated string for the volume name.
 * @param[in ] lBufferSize Size of the buffer to receive the null terminated string for the volume name.
 * @param[out] lpVolNamLen Retrieves the length, in bytes, of the string copied to bpBuffer,
 *                        \b not \b including the terminating null characher.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_GetVolumeName(MMP_LONG lIndex, MMP_BYTE *bpBuffer,
                              MMP_LONG lBufferSize, MMP_LONG *lpVolNamLen)
{
    return MMPD_FS_GetVolumeName(lIndex, bpBuffer, lBufferSize, lpVolNamLen);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_MountVolume
//  Description : HIF_USR_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                 Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_MountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{	
	#if (AHC_FS_SDNEWCACHE)
    #if defined (ALL_FW)
    MMP_ERR 	bResult;
    const FS_DEVICE_TYPE * pFSDeviceType;
	FS_VOLUME*	pVolume;
	MMP_ULONG	ulFatNumSectors = SECTOR_INDEX_INVALIDATE;
	MMP_ULONG	ulFirstDataSector = SECTOR_INDEX_INVALIDATE;
	MMP_ULONG	ulHiddenSector = SECTOR_INDEX_INVALIDATE;
    FS_CACHE_INFO   *pCacheInfoPhyObject; 
    void            *pCacheInfoPhyObjMISC;  

	bResult = MMPD_FS_MountVolume(bpVolume, ulNameSize);    
    
	//if (bpVolume == "SD:\\") {
	pVolume = FS__FindVolume(bpVolume, NULL);
    pFSDeviceType = pVolume->Partition.Device.pType;
    pCacheInfoPhyObjMISC = FS__FindCacheObjectMap(pFSDeviceType);
    pCacheInfoPhyObject = (FS_CACHE_INFO *)pCacheInfoPhyObjMISC; 
    
	if(bResult == MMP_ERR_NONE) {          
		ulFatNumSectors = pVolume->FSInfo.FATInfo.NumSectors; 		
		ulFirstDataSector = pVolume->FSInfo.FATInfo.FirstDataSector;
		ulHiddenSector = pVolume->Partition.StartSector;
		#if(NEWCACHEDEBUGVIEW)
		ulgSDLinFirstDataSector = pVolume->FSInfo.FATInfo.FirstDataSector;
		ulgSDHiddenSector = pVolume->Partition.StartSector;
		#endif
		//ulFatNumSectors = pVolume->Partition.NumSectors;
        
		//SDCacheInfo.pf_SetFatNumSectors(&SDCacheInfo,ulFatNumSectors);
		if(pCacheInfoPhyObject){
			
            if(pCacheInfoPhyObject->pf_SetFatNumSectors)
                (pCacheInfoPhyObject->pf_SetFatNumSectors)(pCacheInfoPhyObject,ulFatNumSectors);
            			
			if(pCacheInfoPhyObject->pf_SetFirstDataSector)
                (pCacheInfoPhyObject->pf_SetFirstDataSector)(pCacheInfoPhyObject,ulFirstDataSector);
			
			if(pCacheInfoPhyObject->pf_SetHiddenSector)
                (pCacheInfoPhyObject->pf_SetHiddenSector)(pCacheInfoPhyObject,ulHiddenSector);   
        }       
    }
	else {				
		ulFatNumSectors = SECTOR_INDEX_INVALIDATE;
		ulFirstDataSector = SECTOR_INDEX_INVALIDATE;
		ulHiddenSector = SECTOR_INDEX_INVALIDATE;	
		#if(NEWCACHEDEBUGVIEW)
		ulgSDLinFirstDataSector = SECTOR_INDEX_INVALIDATE;
		ulgSDHiddenSector = SECTOR_INDEX_INVALIDATE;
        #endif
		
		//SDCacheInfo.pf_SetFatNumSectors(&SDCacheInfo,ulFatNumSectors);
		if(pCacheInfoPhyObject){
			
            if(pCacheInfoPhyObject->pf_SetFatNumSectors)
                (pCacheInfoPhyObject->pf_SetFatNumSectors)(pCacheInfoPhyObject,ulFatNumSectors);

			if(pCacheInfoPhyObject->pf_SetFirstDataSector)
                (pCacheInfoPhyObject->pf_SetFirstDataSector)(pCacheInfoPhyObject,ulFirstDataSector);
			
			if(pCacheInfoPhyObject->pf_SetHiddenSector)
                (pCacheInfoPhyObject->pf_SetHiddenSector)(pCacheInfoPhyObject,ulHiddenSector);
        }
	}
	
	return bResult;
	
    #else
    return MMPD_FS_MountVolume(bpVolume, ulNameSize);
    #endif    
    #else
    return MMPD_FS_MountVolume(bpVolume, ulNameSize);
    #endif	
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_UnmountVolume
//  Description : HIF_USR_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                 Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_UnmountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{		
	#if (AHC_FS_SDNEWCACHE)
    #if defined (ALL_FW)
    MMP_ERR 	bResult;
    const FS_DEVICE_TYPE * pFSDeviceType;
	FS_VOLUME*	pVolume;
	MMP_ULONG	ulFatNumSectors = SECTOR_INDEX_INVALIDATE;
	MMP_ULONG	ulFirstDataSector = SECTOR_INDEX_INVALIDATE;
	MMP_ULONG	ulHiddenSector = SECTOR_INDEX_INVALIDATE;
    FS_CACHE_INFO   *pCacheInfoPhyObject; 
    void            *pCacheInfoPhyObjMISC;		

	bResult = MMPD_FS_UnmountVolume(bpVolume, ulNameSize);

    pVolume = FS__FindVolume(bpVolume, NULL);
    pFSDeviceType = pVolume->Partition.Device.pType;
    pCacheInfoPhyObjMISC = FS__FindCacheObjectMap(pFSDeviceType);
    pCacheInfoPhyObject = (FS_CACHE_INFO *)pCacheInfoPhyObjMISC; 

    if(bResult == MMP_ERR_NONE) {          
        ulFatNumSectors = SECTOR_INDEX_INVALIDATE;
		ulFirstDataSector = SECTOR_INDEX_INVALIDATE;
		ulHiddenSector = SECTOR_INDEX_INVALIDATE;
		#if(NEWCACHEDEBUGVIEW)
		ulgSDLinFirstDataSector = SECTOR_INDEX_INVALIDATE;
		ulgSDHiddenSector = SECTOR_INDEX_INVALIDATE;
        #endif
		//SDCacheInfo.pf_SetFatNumSectors(&SDCacheInfo,ulFatNumSectors);	
		if(pCacheInfoPhyObject){
			
            if(pCacheInfoPhyObject->pf_SetFatNumSectors)
                (pCacheInfoPhyObject->pf_SetFatNumSectors)(pCacheInfoPhyObject,ulFatNumSectors);

			if(pCacheInfoPhyObject->pf_SetFirstDataSector)
                (pCacheInfoPhyObject->pf_SetFirstDataSector)(pCacheInfoPhyObject,ulFirstDataSector);
			
			if(pCacheInfoPhyObject->pf_SetHiddenSector)
                (pCacheInfoPhyObject->pf_SetHiddenSector)(pCacheInfoPhyObject,ulHiddenSector);	
        }       
    }
	return bResult;
	
    #else
    return MMPD_FS_MountVolume(bpVolume, ulNameSize);
    #endif
	#else

    return MMPD_FS_UnmountVolume(bpVolume, ulNameSize);	
    #endif	
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_IsVolumeMounted
//  Description : HIF_USR_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                 Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_IsVolumeMounted(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{
    return MMPD_FS_IsVolumeMounted(bpVolume, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_CheckMediumPresent
//  Description : HIF_USR_CMD_FS_ACCESS | FS_CHECK_MEDIUM_PRESENT  SUB(0x22)
//------------------------------------------------------------------------------
/**
 * @brief                 Check whether a volume is still accessible or not.
 *
 *                        This function can be used to check if a volume is still accessible or not.
 *                        This can be useful to check periodically in a separate task if a volume is newly inserted, removed.
 *                        If the volume was removed, this function will unmount the volume. Therefore all
 *                        open file id to this volume will be invalid.
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ubpValue     Retrieves the value.
 *                        \arg \b value \b 0 means volume is unmounted.
 *                        \arg \b value \b 1 means volume is still mounted.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_CheckMediumPresent(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_UBYTE *ubpValue)
{
    return MMPD_FS_CheckMediumPresent(bpVolume, ulNameSize, ubpValue);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetVolumeInfo
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_VOLUME_INFO  SUB(0x23)
//------------------------------------------------------------------------------
MMP_ERR MMPS_FS_GetVolumeInfo(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMPS_FS_DISK_INFO *pInfo)
{
    return MMPD_FS_GetVolumeInfo(bpVolume, ulNameSize, (MMPD_FS_DISK_INFO *)pInfo);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GET_FILE_LIST
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_FILE_LIST  SUB(0x24)
//------------------------------------------------------------------------------
/**
 * @brief                 Get the current directory entry information for the specified directory.
 *
 *                        This function gets the current directory entry: name, attributes, time, and size.
 *                        If no more entry in the directory, it will return MMP_FS_ERR_NO_MORE_ENTRY.
 *
 * @param[in ] ulDirId      Directory ID.
 * @param[in ] ubInfoMode   4 different mode. Mode attributes can be combined with the \b OR operator (|) .
 *                          \arg MMPS_FILE_NAME  enable \a bpBuffer to get entry name.
 *                          \arg MMPS_ATTRIBUTE  enable \a ubpAttr to get entry attributes.
 *                          \arg MMPS_FILE_TIME  enable \a pFileTime to get entry time structure.
 *                          \arg MMPS_ENTRY_SIZE enable \a ulpEntrySize to get entry size.
 * @param[out] bBuffer      Pointer to a buffer that get the entry name.
 * @param[out] attribute    Pointer to a integer that get the entry attribute.
 * @param[out] filetime     Pointer to a buffer that get the entry time structure.
 * @param[out] ulEntrySize  Pointer to a buffer that get the entry size.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
MMP_ERR MMPS_FS_GetFileList(MMP_ULONG ulDirId, MMP_UBYTE ubInfoMode, MMP_BYTE* bBuffer,
                           MMPS_FS_ATTRIBUTE *attribute, MMPS_FS_FILETIME* filetime, MMP_ULONG* ulEntrySize)
{
    MMP_ULONG	ulTimeStamp;
    MMP_ERR 	status;

    status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize);
	if (status ==  MMP_ERR_NONE) {
//		if(bBuffer[0] == 0x2E) {
//			status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize);
//			if (status ==  MMP_ERR_NONE) {
//				if(bBuffer[0] == 0x2E){
//					status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize );
//				}
//			}
//		}
		_TimeStamp2FileTime(ulTimeStamp, filetime);
    }
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GET_FILE_LIST_DB
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_FILE_LIST  SUB(0x24)
//------------------------------------------------------------------------------
/**
 * @brief                 Get the current directory entry information for the specified directory.
 *
 *                        This function gets the current directory entry: name, attributes, time, and size.
 *                        If no more entry in the directory, it will return MMP_FS_ERR_NO_MORE_ENTRY.
 *
 * @param[in ] ulDirId      Directory ID.
 * @param[out] bBuffer      Pointer to a buffer that get the entry name.
 * @param[out] attribute    Pointer to a integer that get the entry attribute.
 * @param[out] ulFileID     Pointer to the output open file ID.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
MMP_ERR MMPS_FS_GetDBFileList(MMP_ULONG ulDirId, MMP_BYTE* bBuffer, MMPS_FS_ATTRIBUTE *attribute, MMP_ULONG *ulFileID)
{
    return MMPD_FS_GetDBFileList(ulDirId, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, ulFileID);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_SetCreationTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_SET_CREATION_TIME  SUB(0x25)
//------------------------------------------------------------------------------
/**
 * @brief                 Set the time structure for a new file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_SetCreationTime(void)
{
	MMPS_FS_FILETIME	fstime;
	MMP_ULONG			ulTimeStamp;
    
    MMPC_FS_BBGetRTC(&fstime);
    _FileTime2TimeStamp(&fstime, &ulTimeStamp);

    return MMPD_FS_SetCreationTime(ulTimeStamp);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_GetSDClass
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_GET_SDCLASS  SUB(0x08)
//------------------------------------------------------------------------------
/**
 * @brief                 
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPS_FS_GetSDClass(MMP_ULONG id, MMP_UBYTE *bClass)
{
    return MMPD_FS_GetSDClass(id, bClass);
}

//------------------------------------------------------------------------------
//  Function    : _TimeStamp2FileTime
//  Description : utility function
//------------------------------------------------------------------------------
/**
 * @brief                 Convert a timestamp to a structure MMPS_FS_FILETIME.
 *
 *                        Fills the pFileTime structure with the given ulTimeStamp.
 *
 * @param[in ] ulTimeStamp  ulTimeStamp.(src)
 * @param[out] time			Pointer to a structure MMPS_FS_FILETIME.(dest)
 *
 * @return                no return value.
 * @remarks               This is an utility function.
 * @remarks               A timestamp is packed value with the following format:
 * @remarks \arg          Bits( 0- 4) Second divided by 2.
 * @remarks \arg          Bits( 5-10) Minute (0-59)
 * @remarks \arg          Bits(11-15) Hour (0-23)
 * @remarks \arg          Bits(16-20) Day of month (1-31)
 * @remarks \arg          Bits(21-24) Month (January -> 1, February -> 2, ...)
 * @remarks \arg          Bits(25-31) Year offset from 1980. Add 1980 to get current year.
 */
void _TimeStamp2FileTime(MMP_ULONG ulTimeStamp, MMPS_FS_FILETIME *fstime)
{
    MMP_USHORT Date, Time;

    Date = (MMP_USHORT)(ulTimeStamp >> 16);
    Time = (MMP_USHORT)(ulTimeStamp & 0xffff);
    
    if (fstime) {
        fstime->usYear   = (MMP_USHORT) ((Date >> 9) + 1980);
        fstime->usMonth  = (MMP_USHORT) ((Date & 0x1e0) >> 5);
        fstime->usDay    = (MMP_USHORT) ((Date & 0x1f));
        fstime->usHour   = (MMP_USHORT) (Time >> 11);
        fstime->usMinute = (MMP_USHORT) ((Time & 0x7e0) >> 5);
        fstime->usSecond = (MMP_USHORT) ((Time & 0x1f) << 1);
    }
}

//------------------------------------------------------------------------------
//  Function    : _FileTime2TimeStamp
//  Description : utility function
//------------------------------------------------------------------------------
/**
 * @brief                 Convert a structure MMPS_FS_FILETIME to a timestamp.
 *
 *                        Transfer to ulpTimeStamp with the given pFileTime.
 *
 * @param[in ] time			Pointer to a structure MMPS_FS_FILETIME.(src)
 * @param[out] ulpTimeStamp TimeStamp.(dest)
 *
 * @return                no return value.
 * @remarks               This is an utility function.
 */
void _FileTime2TimeStamp(const MMPS_FS_FILETIME * fstime, MMP_ULONG * ulpTimeStamp)
{
    MMP_USHORT Date, Time;

    if (ulpTimeStamp){
        Date  = (MMP_USHORT) (((fstime->usYear - 1980) << 9) |  (fstime->usMonth << 5) | fstime->usDay);
        Time  = (MMP_USHORT) ((fstime->usHour << 11) |  (fstime->usMinute << 5) |  (fstime->usSecond >> 1));
        *ulpTimeStamp = (MMP_ULONG)Date << 16 | (Time & 0xffff);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_DirGetNumDirs
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_GETNUMDIRS  SUB(0x26)
//------------------------------------------------------------------------------
/**
 *@brief        returns the number of dirs in a opend directory.
 *@param[in]    ulDirID  - dir id to get subdir number
 *@param[out]   ulDirCount - Number of files in a directory.
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.

 *@note         void
*/
MMP_ERR MMPS_FS_DirGetNumDirs(MMP_ULONG ulDirID, MMP_ULONG *ulDirCount)
{
    return MMPD_FS_DirGetNumDirs(ulDirID, ulDirCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FS_INIT
//  Description : HIF_USR_CMD_FS_ACCESS | FS_INIT  SUB(0x27)
//------------------------------------------------------------------------------
/**
 *@brief        This function will initialize buffer and storage driver for file
                system access. Make sure this function will be called before 
                starting access file system.

  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.

 *@note         void
*/
MMP_ERR MMPS_FS_Initialize(void)
{
    return MMPD_FS_Initialize();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_IOCtl
//  Description : HIF_USR_CMD_FS_STORAGE | FS_IO_CTL  SUB(0x05)
//------------------------------------------------------------------------------
/**
 * @brief   storage direct io access
 * @param[in] bpDeviceName   device name (ex: SD:\ or SM:\)
 * @param[in] ulNameSize      device name length
 * @param[in] Cmd           io command
 * @param[in] Aux           parameter for io command
 * @param[in, out] pBuffer   data buffer for read/write or device information
 * @retval MMP_ERR_NONE       Succeed.
 * @retval others           Fail.
 */
 MMP_ERR MMPS_FS_IOCtl(MMP_BYTE *bpDeviceName, MMP_ULONG ulNameSize,
                       MMPS_FS_IOCTL_CMD Cmd, MMPS_FS_IOCTL_PARA *Aux,
                       void *pBuffer)
{
    return MMPD_FS_IOCtl(bpDeviceName, ulNameSize , Cmd, (MMPD_FS_IOCTL_PARA*)Aux , pBuffer);
}

#if (FORMAT_FREE_ENABLE)
//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_Enable
//  Description : Enable the FormatFree function
//------------------------------------------------------------------------------
/**
 * @brief         EnableStatus is used to Enable / Disable FormatFree function in FS driver layer
 *                        
 *
 * @param[in ]    EnableStatus    : enable / disable flag status
 * @param[out]  
 * @retval  
 * @remarks 
 */
void MMPS_FORMATFREE_Enable( MMP_BYTE  EnableStatus )
{
    if (EnableStatus)
        gubFormatFreeON = 1;
    else
        gubFormatFreeON = 0;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_EnableWrite
//  Description : Enable the FormatFree Write or Disable
//------------------------------------------------------------------------------
/**
 * @brief         gbWriteDataOnly is used to control FormatFree Write Process in FS driver layer
 *                Enable/Disable for FormatFree Write or Normal Write
 * 
 *
 * @param[in ]    EnableStatus    : enable / disable flag status
 * @param[out]  
 * @retval
 * @remarks
 */
void MMPS_FORMATFREE_EnableWrite(MMP_BYTE  EnableStatus )
{
    if (EnableStatus)
        gbWriteDataOnly = 1;
    else
        gbWriteDataOnly = 0;
}    

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_GetWriteEnable
//  Description : Enable the FormatFree Write or Disable
//------------------------------------------------------------------------------
/**
 * @brief         get gbWriteDataOnly by this function
 *                
 * 
 *
 * @param[in ]    EnableStatus    : enable / disable flag status
 * @param[out]  
 * @retval
 * @remarks
 */
void MMPS_FORMATFREE_GetWriteEnable(MMP_UBYTE* WriteDataOnly )
{
    *WriteDataOnly = gbWriteDataOnly;
}    

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_ConfigInfo
//  Description : Initial the FolderConfiguration structure
//------------------------------------------------------------------------------
/**
 * @brief                 Folder default configuration for Format Free
 *
 * @param[in ]            FormatFreeFolderConfig * pFolderConfig : structure pointer which is prepared for parameter passing
 						  MMP_BYTE RootFolder                    :  						  
 						  (0)Assign FileNumber/FileSizeMB/SpacePercentage<ex: SD:0:\\Normal\\F> ; (1)Not assign FileNumber/FileSizeMB/SpacePercentage<ex: SD:0:\\Normal>
                          MMP_BYTE FolderIndex                   : Sequence of the Folder structure pointer, must be in order
                          MMP_BYTE * FolderName                  : Folder name under Root Directory Entry
                          MMP_BYTE * FileNameInFolder            : File Name under this Folder
 * @param[out] 
 *
 * @retval                 SUCCESS - return MMP_ERR_NONE.
                           FAIL    - return !=0.
 * @remarks               
 */

MMP_ERR MMPS_FORMATFREE_ConfigInfo( FormatFreeFolderConfig * pFolderConfig, MMP_BYTE RootFolder, MMP_BYTE FolderIndex, MMP_BYTE * FolderName, MMP_BYTE * FileNameInFolder )
{
    FormatFreeFolderConfig * pFolderInfo = NULL;
    pFolderInfo = pFolderConfig;
	
    if ( pFolderInfo == NULL ){
		RTNA_DBG_Str(0, "sturcture pointer address is zero \r\n");
        return -2;
    }
	if (FolderName == '\0'){
		RTNA_DBG_Str(0, "Folder Name is Empty \r\n");
		//return -2;
	}
	if (FileNameInFolder == '\0'){
		//RTNA_DBG_Str(0, "File Name is Empty \r\n");
		//return -2;
	}	
			   
	MEMCPY( FolderNameMatrix[FolderIndex],FolderName,(_UTF8_StrLen(FolderName)+1) );               
	//STRCPY(FolderNameMatrix[FolderIndex],FolderName);
		
	MEMCPY( gbFolderConfig[FolderIndex].FileNameInside , FileNameInFolder , (_UTF8_StrLen(FileNameInFolder)+1) );  

	if(RootFolder) {
		gbFolderConfig[FolderIndex].FileNumber = 0;	
		gbFolderConfig[FolderIndex].FileSizeMB = 0;
        gbFolderConfig[FolderIndex].SpacePercentage = 0; 
	}
	else {
		//gbFolderConfig[FolderIndex].FileNumber = pFolderInfo->FileNumber;
	    gbFolderConfig[FolderIndex].FileSizeMB = pFolderInfo->FileSizeMB;
        gbFolderConfig[FolderIndex].SpacePercentage = pFolderInfo->SpacePercentage; 
	}
 
	
	/*
	if (pFolderInfo->FileNumber){
		RTNA_DBG_Str(0, "FileNumber must be zero in initial stage \r\n");
		return -2;
	}
	*/
	
	/*
    if ( (pFolderInfo->FileSizeMB) == 0 ){
		RTNA_DBG_Str(0, "FileSize must not be zero in initial stage \r\n");
		return -2;
	}
	if ( (pFolderInfo->SpacePercentage) == 0 ){
		RTNA_DBG_Str(0, "SpacePercentage must not be zero in initial stage \r\n");
		return -2;
	}
	*/
	
    //assign correct numbers of Folder for gubFolderNUM  
    if (FolderIndex == 0)
        gubFolderNUM = 1;
	else if (FolderIndex >= gubFolderNUM)
	    gubFolderNUM   = (FolderIndex+1);
		
	return  0;	  
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_CheckMedia
//  Description : FormatFree Check function
//------------------------------------------------------------------------------
/**
 * @brief                 Execute the check function of Format Free
 *
 *                        
 *
 * @param[in ] 
 * @param[out] 
 *
 * @retval                 SUCCESS - return MMP_ERR_NONE.
                           FAIL    - return !=0.
 * @remarks               
 */
MMP_ERR MMPS_FORMATFREE_CheckMedia(MMP_BYTE bMedia)
{
    return MMPD_FORMATFREE_CheckMedia(bMedia); 
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_Format
//  Description : Use FormatFree API to Format the media under FormatFree Format
//------------------------------------------------------------------------------
/**
 * @brief                 Not Regular Format, Specail FormatFree Procedure
 *
 * @param[in ] 
 * @param[out] 
 *
 *@retval                 SUCCESS - return MMP_ERR_NONE.
                          FAIL    - return !=0.

 * @remarks               
 */
MMP_ERR MMPS_FORMATFREE_Format(MMP_BYTE bMedia)
{
    return MMPD_FORMATFREE_Format(bMedia);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_FORMATFREE_GetIdealFileNumInFolder
//  Description : Get ideal total files number in a Format Free folder
//                Note: This API should be called after MMPS_FORMATFREE_CheckMedia()
//                      or MMPS_FORMATFREE_Format().
//------------------------------------------------------------------------------
/**
 * @param[in ]    byFolderIndex - Folder index
 * @param[out] 
 *
 *@retval         Ideal total files number

 * @remarks               
 */
MMP_ULONG MMPS_FORMATFREE_GetIdealFileNumInFolder(MMP_BYTE byFolderIndex)
{
    return MMPD_FORMATFREE_GetIdealFileNumInFolder( byFolderIndex );
}

//------------------------------------------------------------------------------
//	Function	: MMPS_FORMATFREE_RegisterCallback
//	Description : 
//------------------------------------------------------------------------------
/**
 *@brief		  Register Callback under Format Free
  @param[in] Event    Specified the event for register.
  @param[in] CallBack The callback to be executed when the specified event happens.
  @return It reports the status of the operation.
  @warn The registered callback will not be auto deleted, please register a NULL
      to delete it.		
*/
MMP_ERR MMPS_FORMATFREE_RegisterCallback(MMPS_FileSystem_EVENT Event, void *CallBack)
{
    MMPS_FileSystem_EVENT e;

    switch (Event) {    
    case MMPS_FileSystem_EVENT_FileName_Require:
    	e = MMPD_FileSystem_EVENT_FileName_Require;
        break;
    default:
        e = MMPD_FileSystem_EVENT_NONE;
        break;
    }

    return MMPD_FORMATFREE_RegisterCallback(e, CallBack);
}

#endif //#if (FORMAT_FREE_ENABLE)

#if ( defined(ALL_FW) || defined(SD_BOOT) || defined(MBOOT_SRAM_FW)  )
//In order to use FS in bootloader add defined(MBOOT_SRAM_FW) 
MMP_USHORT MMPC_FS_FileOpen(MMP_BYTE *bFileName, MMP_BYTE *bMode, void **FileHandle)
{
#if (FS_USE_ICE == 0)
    MMP_USHORT filenamelength;
    #if (FS_INPUT_ENCODE == UCS2)
    MMP_BYTE    ucs2_file[200];
    #endif

    #if (FS_INPUT_ENCODE == UCS2)
    uniStrcpy(ucs2_file, bFileName);
    filenamelength = uniStrlen((short *)ucs2_file);
    #elif (FS_INPUT_ENCODE == UTF8)
    filenamelength = STRLEN(bFileName);
    #endif

    if (MMP_ERR_NONE != MMPS_FS_FileOpen(bFileName, filenamelength, bMode,
                                    STRLEN(bMode), (MMP_ULONG*)FileHandle))
    {
        MMPS_FS_FileClose(*(MMP_ULONG *)FileHandle);
        PRINTF("open file failed.\r\n");
        return 1;
    }
    else {
        return 0;
    }
#else
    *(FILE**)FileHandle = fopen(bFileName, bMode);
    if (*(FILE**)FileHandle == NULL) {
        PRINTF("open %s failed.\r\n", bFileName);
        return 1;
    }
    else {
        return 0;
    }
#endif
}

/** @brief Close file.
*/
MMP_USHORT MMPC_FS_FileClose(void *FileHandle)
{
#if (FS_USE_ICE == 0)
    if (MMP_ERR_NONE != MMPS_FS_FileClose((MMP_ULONG)FileHandle))
    {
        PRINTF("close file failed.\r\n");
        return 1;
    }
    else {
        return 0;
    }
#else
    if (FileHandle == NULL) {
        return 1;
    }
    return fclose((FILE*)FileHandle);
#endif
}

/**
@brief  Seek File(Memory mode)

@param[in] *file_handle : file handle pointer
@param[in] file_offset : Offset for setting the file pointer position
@param[in] file_orign : Mode for positioning file pointer
    -   0 : SEEK_SET
    -   1 : SEEK_CUR
    -   2 : SEEK_END
@return NONE
*/
MMP_USHORT MMPC_FS_FileSeek(void *file_handle, MMP_LONG64 file_offset, MMP_ULONG file_orign)
{
#if (FS_USE_ICE == 0)
    MMP_SHORT origin;

    if(file_orign==0)
        origin = MMPS_FS_SEEK_SET;
    else if(file_orign==1)
        origin = MMPS_FS_SEEK_CUR;
    else
        origin = MMPS_FS_SEEK_END;

    if ( MMP_ERR_NONE != MMPS_FS_FileSeek((MMP_ULONG)file_handle,file_offset,origin) ) {
        return 1;
    }
    else {
        return 0;
    }
#else
    int origin;

    if(file_orign == 0) {
        origin = SEEK_SET;
    }
    else if(file_orign == 1) {
        origin = SEEK_CUR;
    }
    else {
        origin = SEEK_END;
    }

    if (file_handle == NULL) {
        return 1;
    }
    return fseek((FILE*) file_handle, file_offset, origin);
#endif
}

/**
@brief  Write File(Memory mode)

@param[in]  FileHandle  : file handle pointer
@param[in]  uData       : data buffer pointer
@param[in]  ulNumBytes  : write bytes
@param[out] ulWriteCount: actual transfer file size
@return none
*/
MMP_USHORT MMPC_FS_FileWrite(void *FileHandle, MMP_UBYTE *uData, MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount)
{
#if (FS_USE_ICE == 0)
    if (MMP_ERR_NONE != MMPS_FS_FileWrite((MMP_ULONG)FileHandle, uData, ulNumBytes, ulWriteCount)) {
        PRINTF("file write failed.\r\n");
        return 1;
    }
    else {
        return 0;
    }
#else
    *ulWriteCount = fwrite(uData, sizeof(MMP_UBYTE), ulNumBytes, (FILE*) FileHandle);

    if (ulNumBytes == *ulWriteCount) {
        return 0;
    }
    else {
        return ferror((FILE*) FileHandle);
    }
#endif
}

/**
@brief  Read File(Memory mode)

@param[in] *FileHandle : file handle pointer
@param[in] *uData : data buffer pointer
@param[in] ulNumBytes : read bytes
@param[out] *ulReadCount : actual transfer file size
@return none
*/
MMP_USHORT MMPC_FS_FileRead(void *FileHandle, MMP_UBYTE *uData, MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount)
{
#if (FS_USE_ICE == 0)
    if (MMP_ERR_NONE != MMPS_FS_FileRead((MMP_ULONG)FileHandle, uData, ulNumBytes, ulReadCount)) {
        PRINTF("file read failed.\r\n");
        return 1;
    }
    else {
        return 0;
    }
#else
    *ulReadCount = fread(uData, 1, ulNumBytes, (FILE*) FileHandle);

    if (ulNumBytes == *ulReadCount) {
        return 0;
    }
    else {
        return ferror((FILE*) FileHandle);
    }

#endif
}

MMP_USHORT MMPC_FS_FileGetSize(void *FileHandle, MMP_ULONG64 *ulFileSize)
{
#if (FS_USE_ICE == 0)
    if (MMP_ERR_NONE != MMPS_FS_FileGetSize((MMP_ULONG)FileHandle, ulFileSize)) {
        PRINTF("get file size failed.\r\n");
    }
    else {
    }
#else
    long file_pos;

    file_pos = ftell((FILE*) FileHandle);
    fseek((FILE*) FileHandle, 0, SEEK_END);
    *ulFileSize = ftell((FILE*)FileHandle);
    fseek((FILE*) FileHandle, file_pos, SEEK_SET);
#endif

    return 0;
}

/** @brief Return current position of the file pointer.

@param[in] FileHandle The file handler which has been already opened.
@param[out] lFilePos The Current position of file pointer in the file.
@retval 0 Succeed.
@retval others Fail.
*/
MMP_USHORT MMPC_FS_FileTell(void *FileHandle, MMP_LONG64 *llFilePos)
{
#if (FS_USE_ICE == 0)
    return MMPS_FS_FileTell((MMP_ULONG)FileHandle, llFilePos);
#else
    *llFilePos = ftell((FILE*)FileHandle);
    return (*llFilePos == -1);
#endif
}

/** @brief Get Basebnad RTC information to set correct file createion time.
*/
void MMPC_FS_BBGetRTC(MMPS_FS_FILETIME *pTimeStru)
{
#if 0//( defined(SD_BOOT) || defined(MBOOT_SRAM_FW) )
//In order to use FS in bootloader add defined(MBOOT_SRAM_FW) 
    pTimeStru->usYear = 2006;
    pTimeStru->usMonth = 12;
    pTimeStru->usDay = 31;
    pTimeStru->usHour = 23;
    pTimeStru->usMinute = 55;
    pTimeStru->usSecond = 42;
#else
    #if 1
    // if want to use RTC of baseband, add BB RTC infomation here
    // CarDV, read HW RTC is too slow (8328)
    AHC_RTC_TIME        m_sRTCTime;

    AHC_RTC_GetTime(&m_sRTCTime);

    pTimeStru->usYear = m_sRTCTime.uwYear;
    pTimeStru->usMonth = m_sRTCTime.uwMonth;
    pTimeStru->usDay = m_sRTCTime.uwDay;
    pTimeStru->usHour = m_sRTCTime.uwHour;
    pTimeStru->usMinute = m_sRTCTime.uwMinute;
    pTimeStru->usSecond = m_sRTCTime.uwSecond;
    #endif
#endif
}
#endif

MMP_ERR MMPS_FS_GetSDCID(MMP_ULONG SD_ID,MMP_BYTE *CID)
{
	return MMPD_FS_GetSDCID(SD_ID, CID);
}

/// @}
