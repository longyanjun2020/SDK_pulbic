//==============================================================================
//
//  File        : AHC_FS.c
//  Description : File System Functions (Host Application Interface).
//  Author      : Ricky Yeh
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file AHC_FS.c
 *  @brief The File System control functions
 *  @author Ricky Yeh, Sunny 
 *  @version 1.0
 */
 
/*===========================================================================
 * Include files
 *===========================================================================*/  
 
#include "mmp_lib.h"
#include "ait_utility.h"
#include "ahc_fs.h"
#include "ahc_media.h"
#include "mmps_fs.h"
//#include "mmpd_fs.h"
#include "AHC_Config_SDK.h"


/** @addtogroup AHC_FS
@{
*/

/*===========================================================================
 * Main body
 *===========================================================================*/ 

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileOpen
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_OPEN  SUB(0x00)
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
 * @retval AHC_ERR_NONE   Succeed.
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
AHC_ERR AHC_FS_FileOpen(INT8 *bFileName, UINT32 ulNameSize,
                        INT8 *bMode, UINT32 ulModeSize, UINT32 *ulFileId)
{
	AHC_FS_SetCreationTime();
    return MMPD_FS_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileClose
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_CLOSE  SUB(0x01)
//------------------------------------------------------------------------------
/**
 * @brief                 Close an open file.
 *
 * @param[in ] ulFileId   The file id which we want to close.
 *
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
AHC_ERR AHC_FS_FileClose(UINT32 ulFileId)
{
    return MMPD_FS_FileClose(ulFileId);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileRead
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_READ  SUB(0x02)
//------------------------------------------------------------------------------
/**
 * @brief                   Reads data from an open file.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[out] ubData       Pointer to a data buffer for storing data transferred from file.
 * @param[in ] ulNumBytes   Number of bytes to be transferred from the file.
 * @param[out] ulReadCount  Number of bytes read.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileRead(UINT32 ulFileId, UINT8 *ubData,
                        UINT32 ulNumBytes, UINT32 *ulReadCount)
{
    if (ulNumBytes == 0)
        return MMP_FS_ERR_READ_FAIL;

    return MMPD_FS_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileWrite
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_WRITE  SUB(0x03)
//------------------------------------------------------------------------------
/**
 * @brief                   Writes data to an open file.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[in ] ubData       Pointer to data to be written to the file.
 * @param[in ] ulNumBytes   Number of bytes to be transferred to the file.
 * @param[out] ulWriteCount Number of bytes read.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileWrite(UINT32 ulFileId, UINT8 *ubData,
                         UINT32 ulNumBytes, UINT32 *ulWriteCount)
{
    if (ulNumBytes == 0)
        return MMP_FS_ERR_WRITE_FAIL;

    return MMPD_FS_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileSeek
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_SEEK  SUB(0x04)
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
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 *
 * @remarks               Valid values for parameter \a ulOrigin are:
 * @remarks \arg \b       AHC_FS_SEEK_SET The starting point is zero or the beginning of the file.
 * @remarks \arg \b       AHC_FS_SEEK_CUR The start point is the current value of the file pointer.
 * @remarks \arg \b       AHC_FS_SEEK_END The starting point is the current end-of-file position.
 */
AHC_ERR AHC_FS_FileSeek(UINT32 ulFileId, INT64 llOffset, UINT32 ulOrigin)
{
    return MMPD_FS_FileSeek(ulFileId, llOffset, ulOrigin);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileTell
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_TELL  SUB(0x05)
//------------------------------------------------------------------------------
/**
 * @brief                   Return current position of the file pointer.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[out] lFilePos     Current position of file pointer in the file.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileTell(UINT32 ulFileId, INT64 *llFilePos)
{
    return MMPD_FS_FileTell(ulFileId, llFilePos);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileCopy
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_COPY  SUB(0x06)
//------------------------------------------------------------------------------
/**
 * @brief                  Copy an existing file to a new file.
 *
 * @param[in ] bSrc        Pointer to a string that specifies the name of an existing file.
 * @param[in ] ulSrcSize   The length, in bytes, of bpSrc string, including the terminating null character.
 * @param[in ] bDest       Pointer to a string that specifies the name of the new file. The file should not exist
 * @param[in ] ulDestSize  The length, in bytes, of bpDest string, including the terminating null characher.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
 */
AHC_ERR AHC_FS_FileCopy(INT8 *bSrc, UINT32 ulSrcSize,
                        INT8 *bDest,UINT32 ulDestSize)
{
    return MMPD_FS_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileTruncate
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_TRUNCATE  SUB(0x07)
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
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
AHC_ERR AHC_FS_FileTruncate(UINT32 ulFileId, UINT32 ulNewSize)
{
    return MMPD_FS_FileTruncate(ulFileId, ulNewSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileGetSize
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_GET_SIZE  SUB(0x08)
//------------------------------------------------------------------------------
/**
 * @brief                  Get the current file size of a file.
 *
 * @param[in ] ulFileId    The file id which we want to get file size.
 * @param[out] ulFileSize  retrieves file size.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
 */
AHC_ERR AHC_FS_FileGetSize(UINT32 ulFileId, UINT32 *ulFileSize)
{
    MMP_ERR retVal;
	MMP_ULONG64 u64FSize = 0;

    retVal = MMPD_FS_FileGetSize(ulFileId, &u64FSize);

    if (retVal == MMP_ERR_NONE) {
        *ulFileSize = (UINT32) u64FSize;
        return AHC_ERR_NONE;
    }
    
    return AHC_FS_ERR_INVALID_SIZE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileRemove
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_REMOVE  SUB(0x09)
//------------------------------------------------------------------------------
/**
 * @brief                   Removes file from the media.
 *
 * @param[in ] bpFileName   Pointer to a string that specifies the name of an existing file which we want to remove.
 * @param[in ] ulNameSize   The length, in bytes, of bpFileName string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileRemove(INT8 *bpFileName, UINT32 ulNameSize)
{
    return MMPD_FS_FileRemove(bpFileName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirGetAttributes
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_GETATTRIBUTES  SUB(0x0A)
//------------------------------------------------------------------------------
/**
 * @brief                   Retrieves attributes for a specified file or directory.
 *
 * @param[in ] bpName      	Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute	retrieves the attributes value.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       AHC_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       AHC_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       AHC_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       AHC_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       AHC_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
AHC_ERR AHC_FS_FileDirGetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute)
{
    return MMPD_FS_FileDirGetAttribute(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE *)attribute);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirGetInfo
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_GETINFO  SUB(0x2A)
//------------------------------------------------------------------------------
/**
 * @brief                    Retrieves attributes/time and file size for a specified file or directory
 *
 * @param[in ] bpName      	 Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize    The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute	 retrieves the attributes value.
 * @param[out] timestructure retrieves time structure.
 * @param[out] ulpFileSize	 retrieves the file size. If the input is a directory, then return 0
 *
 * @retval AHC_ERR_NONE      Succeed.
 * @retval others            Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       AHC_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       AHC_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       AHC_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       AHC_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       AHC_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
AHC_ERR AHC_FS_FileDirGetInfo(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME *timestructure, UINT32 *ulpFileSize)
{
    AHC_ERR status;
    UINT32 	ulTimeStamp;

	status = MMPD_FS_FileDirGetInfo(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulpFileSize);
	
	if (status == AHC_ERR_NONE) {
        AHC_TimeStamp2FileTime(ulTimeStamp, timestructure);
    }
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirGetFileTime
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_GETFILETIME  SUB(0x0B)
//------------------------------------------------------------------------------
/**
 * @brief                 	    Retrieves time structure for a specified file or directory.
 *
 * @param[in ] bpName			Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize		The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] timestructure	Retrieves time structure.
 *
 * @retval AHC_ERR_NONE     	Succeed.
 * @retval others         		Fail.
 */
AHC_ERR AHC_FS_FileDirGetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME *timestructure)
{
    AHC_ERR status;
    UINT32 	ulTimeStamp;

    status = MMPD_FS_FileDirGetTime(bpName, ulNameSize, &ulTimeStamp);

    if (status == AHC_ERR_NONE) {
        AHC_TimeStamp2FileTime(ulTimeStamp, timestructure);
    }
    return status;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirMove
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_MOVE  SUB(0x0C)
//------------------------------------------------------------------------------
/**
 * @brief                   Moves an existing file or a directory, including its childen.
 *
 * @param[in ] bpNameSrc    Pointer to a string that names an existing file or directory.
 * @param[in ] ulSrcSize    The length, in bytes, of pFullNameSrc string, including the terminating null character.
 * @param[in ] bpNameDest   Pointer to a string that specifies the name of the new file or directory.
 * @param[in ] ulDestSize   The length, in bytes, of pFullNameDest string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileDirMove(INT8 *bpNameSrc, UINT32 ulSrcSize,
                           INT8 *bpNameDest,UINT32 ulDestSize)
{
    return MMPD_FS_FileDirMove(bpNameSrc, ulSrcSize, bpNameDest, ulDestSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirRename
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_RENAME  SUB(0x0D)
//------------------------------------------------------------------------------
/**
 * @brief                    Renames an existing file or a directory.
 *
 * @param[in ] bpOldName     Pointer to a string that names an existing file or directory.
 * @param[in ] ulOldNameSize The length, in bytes, of bpOldName string, including the terminating null character.
 * @param[in ] bpNewName     Pointer to a string that specifies the name of the new file or directory.
 * @param[in ] ulNewNameSize The length, in bytes, of bpNewName string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE      Succeed.
 * @retval others            Fail.
 *
 * @remarks               bpNewName should point to a fullpath name and new file should locate in the same
 *						  dir
 *
 */
AHC_ERR AHC_FS_FileDirRename(INT8 *bpOldName, UINT32 ulOldNameSize,
                             INT8 *bpNewName, UINT32 ulNewNameSize)
{
    if (strcmp(bpOldName, bpNewName) != 0)
        return MMPD_FS_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize);
    else
        return MMP_FS_ERR_FILE_REMNAME_FAIL;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirSetAttributes
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_SETATTRIBUTES  SUB(0x0E)
//------------------------------------------------------------------------------
/**
 * @brief                  Set attributes for a specified file or directory.
 *
 * @param[in ] bpName      Pointer to a string that names an existing file or directory.
 * @param[in ] ulNameSize  The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] attribute   attribute to be set to the file or directory.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       AHC_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       AHC_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       AHC_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       AHC_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
AHC_ERR AHC_FS_FileDirSetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE attribute)
{
    return MMPD_FS_FileDirSetAttribute(bpName, ulNameSize, (MMPD_FS_ATTRIBUTE)attribute);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_FileDirSetFileTime
//  Description : HIF_CMD_FS_ACCESS | FS_FILE_DIR_SETFILETIME  SUB(0x0F)
//------------------------------------------------------------------------------
/**

 * @brief                   Set the time structure for a specified file or directory.
 *
 * @param[in ] bpName		Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize	The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] time			Pointer to a time structure to be set to file or directory.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_FileDirSetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME* time)
{
    UINT32 ulTimeStamp;

    AHC_FileTime2TimeStamp(time, &ulTimeStamp);

    return MMPD_FS_FileDirSetTime(bpName, ulNameSize, ulTimeStamp);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirClose
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_CLOSE  SUB(0x10)
//------------------------------------------------------------------------------
/**
 * @brief                   This function close a directory referred by parameter usDirId.
 *
 * @param[in ] ulDirID      Directory ID which we want to close.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_DirClose(UINT32 ulDirID)
{
    return MMPD_FS_DirClose(ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirGetNumFiles
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_GETNUMFILES  SUB(0x15)
//------------------------------------------------------------------------------
/**
 * @brief                   The function retrieves the number of files in a opened directory.
 *
 * @param[in ] ulDirID      Directory ID
 * @param[out] ulFileCount  Retrieves the number of files in a directory.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_DirGetNumFiles(UINT32 ulDirID, UINT32 *ulFileCount)
{
    return MMPD_FS_DirGetNumFiles(ulDirID, ulFileCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirCreate
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_CREATE  SUB(0x16)
//------------------------------------------------------------------------------
/**
 * @brief                   Creates a new directory.
 *
 * @param[in ] bDirName     Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize   The length, in bytes, of bpDirName string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
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
AHC_ERR AHC_FS_DirCreate(INT8 *bDirName, UINT32 ulNameSize)
{
	AHC_FS_SetCreationTime();
    return MMPD_FS_DirCreate(bDirName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirOpen
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_OPEN  SUB(0x17)
//------------------------------------------------------------------------------
/**
 * @brief                  Open an existing directory for reading.
 *
 * @param[in ] bDirName    Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize  The length, in bytes, of bpDirName string, including the terminating null character.
 * @param[out] ulDirID     Retrieves opened directory id.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
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
AHC_ERR AHC_FS_DirOpen(INT8 *bDirName, UINT32 ulNameSize, UINT32 *ulDirID)
{
    return MMPD_FS_DirOpen(bDirName, ulNameSize, ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirRewind
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_REWIND  SUB(0x19)
//------------------------------------------------------------------------------
/**
 * @brief                   This function sets pointer for reading the next directory entry to the \b first \b entry in the directory.
 *
 * @param[in ] ulDirID      Directory ID
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_DirRewind(UINT32 ulDirID)
{
    return MMPD_FS_DirRewind(ulDirID);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirRemove
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_REMOVE  SUB(0x1A)
//------------------------------------------------------------------------------
/**
 * @brief                   Deletes a directory.
 *
 * @param[in ] bpDirName    Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize   The length, in bytes, of bpDirName string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 * @remarks                 This function will only delete a directory if it is empty.
 */
AHC_ERR AHC_FS_DirRemove(INT8 *bpDirName, UINT32 ulNameSize)
{
    return MMPD_FS_DirRemove(bpDirName, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_HighLevelFormat
//  Description : HIF_CMD_FS_ACCESS | FS_HIGH_LEVLE_FORMAT  SUB(0x1C)
//------------------------------------------------------------------------------
/**
 * @brief                 High-level formats a device.
 *
 *                        This means putting the management information required by the file system on the medium.
 *                        In case of FAT, this means primarily initialization of FAT and root directory, as well as the Bios parameter block.
 *
 * @param[in ] bpDevice   Name of the device to format.
 * @param[in ] ulNameSize The length, in bytes, of bpDevice string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
AHC_ERR AHC_FS_HighLevelFormat(INT8 *bpDevice, UINT32 ulNameSize)
{
    return MMPD_FS_HighLevelFormat(bpDevice, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GetFreeSpace
//  Description : HIF_CMD_FS_ACCESS | FS_GET_FREE_SPACE  SUB(0x1D)
//------------------------------------------------------------------------------
/**
 * @brief                   Get amount of free space on a specific volume.
 *
 *                          Note that free space larger than 4 gigabyte(GB) is reported as 0xFFFFFFFF since a UINT32
 *                          can not represent bigger values. If you don't need to know if there is more than 4 GB of free
 *                          space available, you can still reliably use this function.
 *
 * @param[in ] bpVolume     Pointer to a string that specifies the volume name.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ulpFreeBytes Retrieve the amount of free space in bytes.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 * @remarks                 Valid volume name means:
 * @remarks                 [DevName:[UnitNum:]]
 * @remarks \arg \a         DevName is the name of a device. If not specified, the first device in the volume table will be used.
 * @remarks \arg \a         UnitNum is the number of the unit of the device. If not specified, unit 0 will be used.
 * @remarks \b              Note that it is not allowed to specify \a UnitNum if \a DevName has not been specified.
 */
AHC_ERR AHC_FS_GetFreeSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpFreeBytes)
{
    return MMPD_FS_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GetStorageFreeSpace
//  Description : HIF_CMD_FS_ACCESS | FS_GET_FREE_SPACE  SUB(0x1D)
//------------------------------------------------------------------------------
/**
 * @brief                   Get amount of free space on a specific volume.
 *
 *                          Note that free space larger than 4 gigabyte(GB) is reported as 0xFFFFFFFF since a UINT32
 *                          can not represent bigger values. If you don't need to know if there is more than 4 GB of free
 *                          space available, you can still reliably use this function.
 *
 * @param[in ] byMediaID    The specified storage media.
 * @param[out] ulpFreeBytes Retrieve the amount of free space in bytes.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 * @remarks                 Valid volume name means:
 * @remarks                 [DevName:[UnitNum:]]
 * @remarks \arg \a         DevName is the name of a device. If not specified, the first device in the volume table will be used.
 * @remarks \arg \a         UnitNum is the number of the unit of the device. If not specified, unit 0 will be used.
 * @remarks \b              Note that it is not allowed to specify \a UnitNum if \a DevName has not been specified.
 */
AHC_ERR AHC_FS_GetStorageFreeSpace(UINT8 byMediaID, UINT64 *ulpFreeBytes)
{
    MMP_BYTE    *bpVolume;
    MMP_ULONG   ulVolNameSize;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }
    return MMPD_FS_GetFreeSpace(bpVolume, ulVolNameSize, ulpFreeBytes);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GetTotalSpace
//  Description : HIF_CMD_FS_ACCESS | FS_GET_TOTAL_SPACE  SUB(0x1E)
//------------------------------------------------------------------------------
/**
 * @brief                   Get amount of total size of a specific volume.
 *
 *                          Note that volume sizes larger than 4 GB are reported as 0xFFFFFFFF since a UINT32
 *                          can not represent bigger values. If you don't need to know if the total space is bigger
 *                          than 4GB, you can still reliably use this function.
 *
 * @param[in ] bpVolume     Pointer to a string that specifies the volume name.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ulpTotal     Retrieves the volume size in bytes.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_GetTotalSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpTotal)
{
    return MMPD_FS_GetTotalSpace(bpVolume, ulNameSize, ulpTotal);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GetNumVolumes
//  Description : HIF_CMD_FS_ACCESS | FS_GET_NUM_VOLUMES  SUB(0x1F)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves the number of available volumes.
 *
 *                        This function can be used to get the name of each available volume.
 *
 * @param[out] lpNumVols  Retrieves the number of available volumes.
 *
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
AHC_ERR AHC_FS_GetNumVolumes(INT32 *lpNumVols)
{
    return MMPD_FS_GetNumVolumes(lpNumVols);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GetVolumeName
//  Description : HIF_CMD_FS_ACCESS | FS_GET_VOLUME_NAME  SUB(0x20)
//------------------------------------------------------------------------------
/**
 * @brief                  Retrieves the name of specified volume.
 *
 *                         This function can be used to get the name of each available volume.
 *
 * @param[in ] lIndex      lIndex number of the volume.
 * @param[out] bpBuffer    Pointer to a buffer that receives the null-terminated string for the volume name.
 * @param[in ] lBufferSize Size of the buffer to receive the null terminated string for the volume name.
 * @param[out] lpVolNamLen Retrieves the length, in bytes, of the string copied to bpBuffer,
 *                        \b not \b including the terminating null characher.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
 */
AHC_ERR AHC_FS_GetVolumeName(INT32 lIndex, INT8 *bpBuffer,
                             INT32 lBufferSize, INT32 *lpVolNamLen)
{
    return MMPD_FS_GetVolumeName(lIndex, bpBuffer, lBufferSize, lpVolNamLen);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_MountVolume
//  Description : HIF_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                   Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume     Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_MountVolume(INT8 *bpVolume, UINT32 ulNameSize)
{
    return MMPD_FS_MountVolume(bpVolume, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_UnmountVolume
//  Description : HIF_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                   Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume     Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_UnmountVolume(INT8 *bpVolume, UINT32 ulNameSize)
{
    return MMPD_FS_UnmountVolume(bpVolume, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_IsVolumeMounted
//  Description : HIF_CMD_FS_ACCESS | FS_IS_VOLUME_MOUNTED  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                   Check if a volume is mounted and has correct file system information. If necessary the volume will be mounted.
 *
 * @param[in ] bpVolume     Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_IsVolumeMounted(INT8 *bpVolume, UINT32 ulNameSize)
{
    return MMPD_FS_IsVolumeMounted(bpVolume, ulNameSize);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_CheckMediumPresent
//  Description : HIF_CMD_FS_ACCESS | FS_CHECK_MEDIUM_PRESENT  SUB(0x22)
//------------------------------------------------------------------------------
/**
 * @brief                  Check whether a volume is still accessible or not.
 *
 *                         This function can be used to check if a volume is still accessible or not.
 *                         This can be useful to check periodically in a separate task if a volume is newly inserted, removed.
 *                         If the volume was removed, this function will unmount the volume. Therefore all
 *                         open file id to this volume will be invalid.
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize  The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] ubpValue    Retrieves the value.
 *                         \arg \b value \b 0 means volume is unmounted.
 *                         \arg \b value \b 1 means volume is still mounted.
 *
 * @retval AHC_ERR_NONE    Succeed.
 * @retval others          Fail.
 */
AHC_ERR AHC_FS_CheckMediumPresent(INT8 *bpVolume, UINT32 ulNameSize, UINT8 *ubpValue)
{
    return MMPD_FS_CheckMediumPresent(bpVolume, ulNameSize, ubpValue);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GET_VOLUME_INFO       
//  Description : HIF_CMD_FS_ACCESS | FS_GET_VOLUME_INFO  SUB(0x23)
//------------------------------------------------------------------------------
AHC_ERR AHC_FS_GetVolumeInfo(INT8 *bpVolume, UINT32 ulNameSize, AHC_FS_DISK_INFO *pInfo)
{
    return MMPS_FS_GetVolumeInfo(bpVolume, ulNameSize, (MMPS_FS_DISK_INFO *)pInfo);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GET_FILE_LIST
//  Description : HIF_CMD_FS_ACCESS | FS_GET_FILE_LIST  SUB(0x24)
//------------------------------------------------------------------------------
/**
 * @brief                   Get the current directory entry information for the specified directory.
 *
 *                          This function gets the current directory entry: name, attributes, time, and size.
 *                          If no more entry in the directory, it will return MMP_FS_ERR_NO_MORE_ENTRY.
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
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_GetFileList(UINT32 ulDirId, UINT8 ubInfoMode, INT8* bBuffer,
                           AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME* filetime, UINT32* ulEntrySize)
{
    UINT32	ulTimeStamp;
    AHC_ERR 	status;

    status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize);
    
	if (status ==  AHC_ERR_NONE) {

		#if 0
		if (bBuffer[0] == 0x2E) {
			status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize);
			if (status ==  AHC_ERR_NONE) {
				if(bBuffer[0] == 0x2E){
					status = MMPD_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, &ulTimeStamp, ulEntrySize );
				}
			}
		}
		#endif

		AHC_TimeStamp2FileTime(ulTimeStamp, filetime);
    }
    return status;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_GET_FILE_LIST_DB
//  Description : HIF_CMD_FS_ACCESS | FS_GET_FILE_LIST  SUB(0x24)
//------------------------------------------------------------------------------
/**
 * @brief                   Get the current directory entry information for the specified directory.
 *
 *                          This function gets the current directory entry: name, attributes, time, and size.
 *                          If no more entry in the directory, it will return MMP_FS_ERR_NO_MORE_ENTRY.
 *
 * @param[in ] ulDirId      Directory ID.
 * @param[out] bBuffer      Pointer to a buffer that get the entry name.
 * @param[out] attribute    Pointer to a integer that get the entry attribute.
 * @param[out] ulFileID     Pointer to the output open file ID.
 *
 * @retval AHC_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
AHC_ERR AHC_FS_GetDBFileList(UINT32 ulDirId, INT8* bBuffer, AHC_FS_ATTRIBUTE *attribute, UINT32 *ulFileID)
{
    return MMPD_FS_GetDBFileList(ulDirId, bBuffer, (MMPD_FS_ATTRIBUTE *)attribute, ulFileID);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_SetCreationTime
//  Description : HIF_CMD_FS_ACCESS | FS_SET_CREATION_TIME  SUB(0x25)
//------------------------------------------------------------------------------
/**
 * @brief                 Set the time structure for a new file or directory.
 *
 * @retval AHC_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
AHC_ERR AHC_FS_SetCreationTime(void)
{
	MMPS_FS_FILETIME	time;
	UINT32				ulTimeStamp;
    
    MMPC_FS_BBGetRTC(&time);
    AHC_FileTime2TimeStamp((AHC_FS_FILETIME*) &time, &ulTimeStamp);

    return MMPD_FS_SetCreationTime(ulTimeStamp);
}

//------------------------------------------------------------------------------
//  Function    : AHC_TimeStamp2FileTime
//  Description : utility function
//------------------------------------------------------------------------------
/**
 * @brief                   Convert a timestamp to a structure AHC_FS_FILETIME.
 *
 *                          Fills the pFileTime structure with the given ulTimeStamp.
 *
 * @param[in ] ulTimeStamp  ulTimeStamp.(src)
 * @param[out] time			Pointer to a structure AHC_FS_FILETIME.(dest)
 *
 * @return                  no return value.
 * @remarks                 This is an utility function.
 * @remarks                 A timestamp is packed value with the following format:
 * @remarks \arg            Bits( 0- 4) Second divided by 2.
 * @remarks \arg            Bits( 5-10) Minute (0-59)
 * @remarks \arg            Bits(11-15) Hour (0-23)
 * @remarks \arg            Bits(16-20) Day of month (1-31)
 * @remarks \arg            Bits(21-24) Month (January -> 1, February -> 2, ...)
 * @remarks \arg            Bits(25-31) Year offset from 1980. Add 1980 to get current year.
 */
void AHC_TimeStamp2FileTime(UINT32 ulTimeStamp, AHC_FS_FILETIME *time)
{
    MMP_USHORT Date, Time;

    Date = (MMP_USHORT)(ulTimeStamp >> 16);
    Time = (MMP_USHORT)(ulTimeStamp & 0xffff);
    
    if (time) {
        time->usYear   = (MMP_USHORT) ((Date >> 9) + 1980);
        time->usMonth  = (MMP_USHORT) ((Date & 0x1e0) >> 5);
        time->usDay    = (MMP_USHORT) ((Date & 0x1f));
        time->usHour   = (MMP_USHORT) (Time >> 11);
        time->usMinute = (MMP_USHORT) ((Time & 0x7e0) >> 5);
        time->usSecond = (MMP_USHORT) ((Time & 0x1f) << 1);
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_FileTime2TimeStamp
//  Description : utility function
//------------------------------------------------------------------------------
/**
 * @brief                   Convert a structure AHC_FS_FILETIME to a timestamp.
 *
 *                          Transfer to ulpTimeStamp with the given pFileTime.
 *
 * @param[in ] time			Pointer to a structure AHC_FS_FILETIME.(src)
 * @param[out] ulpTimeStamp TimeStamp.(dest)
 *
 * @return                  no return value.
 * @remarks                 This is an utility function.
 */
void AHC_FileTime2TimeStamp(const AHC_FS_FILETIME * time, UINT32 * ulpTimeStamp)
{
    MMP_USHORT Date, Time;

    if (ulpTimeStamp) {

        Date  = (MMP_USHORT) (((time->usYear - 1980) << 9) | (time->usMonth << 5) | time->usDay);
        Time  = (MMP_USHORT) ((time->usHour << 11) | (time->usMinute << 5) | (time->usSecond >> 1));

        *ulpTimeStamp = (UINT32)Date << 16 | (Time & 0xffff);
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_DirGetNumDirs
//  Description : HIF_CMD_FS_ACCESS | FS_DIR_GETNUMDIRS  SUB(0x26)
//------------------------------------------------------------------------------
/**
 *@brief        returns the number of dirs in a opend directory.
 *@param[in]    ulDirID  - dir id to get subdir number
 *@param[out]   ulDirCount - Number of files in a directory.
 *@retval       SUCCESS - return AHC_ERR_NONE.
 *              FAIL    - return !=0.
 *
 *@note         void
 */
AHC_ERR AHC_FS_DirGetNumDirs(UINT32 ulDirID, UINT32 *ulDirCount)
{
    return MMPD_FS_DirGetNumDirs(ulDirID, ulDirCount);
}

//------------------------------------------------------------------------------
//  Function    : AHC_FS_INIT
//  Description : HIF_CMD_FS_ACCESS | FS_INIT  SUB(0x27)
//------------------------------------------------------------------------------
/**
 *@brief        This function will initialize buffer and storage driver for file
 *              system access. Make sure this function will be called before 
 *              starting access file system.
 *
 *@retval       SUCCESS - return AHC_ERR_NONE.
 *              FAIL    - return !=0.
 *
 *@note         void
 */
AHC_ERR AHC_FS_Initialize(void)
{
    return MMPD_FS_Initialize();
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_IOCtl
//  Description : HIF_CMD_FS_STORAGE | FS_IO_CTL  SUB(0x05)
//------------------------------------------------------------------------------
/**
 * @brief   		storage direct io access
 * @param[in] 		bpDeviceName  device name (ex: SD:\ or SM:\)
 * @param[in] 		ulNameSize    device name length
 * @param[in] 		Cmd           io command
 * @param[in] 		Aux           parameter for io command
 * @param[in, out] 	pBuffer   	  data buffer for read/write or device information
 * @retval 			AHC_ERR_NONE  Succeed.
 * @retval 			others        Fail.
 */
 AHC_ERR AHC_FS_IOCtl(INT8 *bpDeviceName, UINT32 ulNameSize,
                      AHC_FS_IOCTL_CMD Cmd, AHC_FS_IOCTL_PARA *Aux, void *pBuffer)
{
    return MMPD_FS_IOCtl(bpDeviceName, ulNameSize, Cmd, (MMPD_FS_IOCTL_PARA*)Aux , pBuffer);
}

/// @}
