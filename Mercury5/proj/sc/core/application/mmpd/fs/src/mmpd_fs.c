/// @ait_only
//==============================================================================
//
//  File        : mmpd_fs.c
//  Description : File System Functions (Host Device Driver Interface).
//  Author      : Ricky Yeh
//  Revision    : 1.0
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_fs.h"
#include "mmph_hif.h"
#include "os_wrap.h"
#if (FORMAT_FREE_ENABLE)
#include "mmpf_fs_api.h" // use of "MMPF_FS_MakeFileDirEntry"
#include "fs_int.h"      // adding for use "FS_VOLUME"
#endif

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
/** @addtogroup MMPD_FS
 *  @{
 */

/**
 *
 * Default we use both MMPH_HIF_MemCopyHostToDev()
 *                and  MMPH_HIF_MemCopyHostToDev().
 *
 * Sometimes may be we need a internal debug,
 *  then you may refer to this DEFINE to use both MMPH_HIF_MemGetB()
 *                                           and  MMPH_HIF_MemSetB() instead.
 *
 */
#define _USE_FAST2_MODE_ (1)  ///< default set to 1.

/**
 *  DMA m_ulNam is used to transfer file name parameter between Host & Kernel.
 */
// it must locate in non-cache memory, you can dynamically change by MMPD_FS_SetFileNameDmaAddr()
static MMP_ULONG   m_ulNam;             ///< m_ulNam dma addr. file name buffer.
static MMP_ULONG   m_ulNamSize;         ///< m_ulNam dma size.

/**
 *  DMA m_ulBuf is most used to transfer read/write data between Host & Kernel.
 *  It also used for MMPD_FS_FileOpen(),MMPD_FS_FileCopy(),MMPD_FS_FileDirMove(),MMPD_FS_FileDirRename()
 *  to transfer 2nd file name parameter.
 */
// it must locate in non-cache memory, you can dynamically change by MMPD_FS_SetFileNameDmaAddr()
static MMP_ULONG    m_ulBuf;            ///< m_ulBuf dma addr. r/w transfer buffer.
static MMP_ULONG    m_ulBufSize ;       ///< m_ulBuf dma size. (1K at least)

#if (OMA_DRM_EN == 1)
MMP_ULONG m_ulDRMIVAddr[4];
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================




//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileOpen
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_OPEN  SUB(0x00)
//------------------------------------------------------------------------------
/**
 * @brief                 Opens an existing file or creates a new file depending on parameters.
 *
 * @param[in ] bFileName   Fully qualified file name.
 * @param[in ] ulNameSize  The length, in bytes, of FileName string,including the terminating null character.
 * @param[in ] bMode       Mode string for opening the file.
 * @param[in ] ulModeSize  The length, in bytes, of Mode string, including the terminating null characher.
 * @param[out] ulFileId    Return file id.
 *
 * @retval MMP_ERR_NONE     Succeed.
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
MMP_ERR MMPD_FS_FileOpen(MMP_BYTE *bFileName, MMP_ULONG ulNameSize,
                                MMP_BYTE *bMode, MMP_ULONG ulModeSize, MMP_ULONG *ulFileId)
{
    MMP_ERR mmpstatus;
    MMP_UBYTE null = 0x0;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)

    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bFileName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bMode    , ulModeSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulModeSize, (MMP_UBYTE*)&null  , 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpFileName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bpMode    , ulModeSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_OPEN | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
    if (mmpstatus == MMP_ERR_NONE) {
        *ulFileId = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }
    else {
        *ulFileId = 0;
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileClose
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_CLOSE  SUB(0x01)
//------------------------------------------------------------------------------
/**
 * @brief                 Close an open file.
 *
 * @param[in ] ulFileId     The file id which we want to close.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileClose(MMP_ULONG ulFileId)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulFileId);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_CLOSE | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMP_DBG_ERR(1, " @+@ ERROR:MMPD_FS_FileClose => HIF_SendCmd [%x]\r\n", ulFileId);
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
    if(mmpstatus){
        MMP_DBG_ERR(1, " @+@ ERROR:MMPD_FS_FileClose => HIF_GetParameterL [%x]\r\n", ulFileId);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileRead
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_READ  SUB(0x02)
//------------------------------------------------------------------------------
/**
 * @brief                 Reads data from an open file.
 *
 * @param[in ] ulFileId     File id which has already opened.
 * @param[out] ubData      Pointer to a data buffer for storing data transferred from file.
 * @param[in ] ulNumBytes   Number of bytes to be transferred from the file.
 * @param[out] ulReadCount  Number of bytes read.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileRead(MMP_ULONG ulFileId, MMP_UBYTE *ubData,
                                MMP_ULONG ulNumBytes, MMP_ULONG *ulReadCount)
{
    MMP_ULONG   read_size, tmp_read_size, tmp_read_count;
    MMP_UBYTE   *buf;
    MMP_ERR     mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    read_size = ulNumBytes;
    buf = ubData;
    *ulReadCount = 0;

    if (ulNumBytes == 0) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        *ulReadCount += tmp_read_count; // return read count
        return MMP_FS_ERR_INVALID_SIZE;
    }

    while (read_size) {
        if (read_size >= m_ulBufSize) {
            tmp_read_size = m_ulBufSize;
        } else {
            tmp_read_size = read_size;   //The last time.
        }

        MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, tmp_read_size);
        MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulFileId);
        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_READ | HIF_USR_CMD_FS_ACCESS);
        if (mmpstatus) {
            MMPH_HIF_ReleaseSem(GRP_IDX_USR);
            return mmpstatus;
        }

        mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

        if (mmpstatus) {
            MMPH_HIF_ReleaseSem(GRP_IDX_USR);
            return mmpstatus;
        }
        //  don't check this, only check status
        tmp_read_count = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);

        if (tmp_read_count != tmp_read_size) {
            MMPH_HIF_MemCopyDevToHost(buf, m_ulBuf, tmp_read_count);
            *ulReadCount += tmp_read_count;
            break;
        }

        MMPH_HIF_MemCopyDevToHost(buf, m_ulBuf, tmp_read_count);  // read: buf <--- Dma

        read_size -= tmp_read_count;
        buf += tmp_read_count;
        *ulReadCount += tmp_read_count;    // record finished size
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileWrite
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
MMP_ERR MMPD_FS_FileWrite(MMP_ULONG ulFileId, MMP_UBYTE *ubData,
                                 MMP_ULONG ulNumBytes, MMP_ULONG *ulWriteCount)
{
    MMP_ULONG write_size, tmp_write_size;
    MMP_UBYTE *buf;
    MMP_ERR   mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0x0);

    write_size = ulNumBytes;
    buf = ubData;
    *ulWriteCount = 0;  //clear

    while (write_size) {
        if (write_size >= m_ulBufSize) {
            tmp_write_size = m_ulBufSize;
        }
        else {
            tmp_write_size = write_size;
        }

        MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, tmp_write_size);
        MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulFileId);
        MMPH_HIF_MemCopyHostToDev(m_ulBuf, buf, tmp_write_size);

        mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_WRITE | HIF_USR_CMD_FS_ACCESS);
        if (mmpstatus) {
            MMPH_HIF_ReleaseSem(GRP_IDX_USR);
            return mmpstatus;
        }

        mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
        if (mmpstatus) {
            MMPH_HIF_ReleaseSem(GRP_IDX_USR);
            return mmpstatus;
        }

        write_size -= tmp_write_size;
        buf += tmp_write_size;
        *ulWriteCount += tmp_write_size;
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileSeek
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_SEEK  SUB(0x04)
//------------------------------------------------------------------------------
/**
 * @brief                 Set current position of the file pointer.
 *
 *                        This function moves the file pointer to a new location that is offset bytes from ulOrigin.
 *
 * @param[in ] ulFileId   File id which has already opened.
 * @param[in ] llOffset    lOffset for setting the file pointer position.
 * @param[in ] ulOrigin   Mode for positioning file pointer.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 *
 * @remarks               Valid values for parameter \a ulOrigin are:
 * @remarks \arg \b       MMPD_FS_SEEK_SET The starting point is zero or the beginning of the file.
 * @remarks \arg \b       MMPD_FS_SEEK_CUR The start point is the current value of the file pointer.
 * @remarks \arg \b       MMPD_FS_SEEK_END The starting point is the current end-of-file position.
 */

MMP_ERR MMPD_FS_FileSeek(MMP_ULONG ulFileId, MMP_LONG64 llOffset, MMP_ULONG ulOrigin)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, (MMP_ULONG)(llOffset & 0x00000000FFFFFFFF));
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, (MMP_ULONG)(llOffset >> 32));
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 8, ulOrigin);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 12, ulFileId);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_SEEK | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileTell
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
MMP_ERR MMPD_FS_FileTell(MMP_ULONG ulFileId, MMP_LONG64 *llFilePos)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulFileId);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_TELL | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
    if (mmpstatus == MMP_ERR_NONE) {
        *llFilePos = (MMP_LONG64)MMPH_HIF_GetParameterL(GRP_IDX_USR, 4) |
                     ((MMP_LONG64)MMPH_HIF_GetParameterL(GRP_IDX_USR, 8) << 32);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileCopy
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_COPY  SUB(0x06)
//------------------------------------------------------------------------------
/**
 * @brief                 Copy an existing file to a new file.
 *
 * @param[in ] bSrc       Pointer to a string that specifies the name of an existing file.
 * @param[in ] ulSrcSize    The length, in bytes, of bpSrc string, including the terminating null character.
 * @param[in ] bDest      Pointer to a string that specifies the name of the new file.
 * @param[in ] ulDestSize   The length, in bytes, of bpDest string, including the terminating null characher.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileCopy(MMP_BYTE *bSrc, MMP_ULONG ulSrcSize,
                         MMP_BYTE *bDest,MMP_ULONG ulDestSize)
{
    MMP_ERR mmpstatus;
    MMP_UBYTE null = 0;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bSrc,  ulSrcSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulSrcSize, (MMP_UBYTE*)&null,  1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulSrcSize + 1, (MMP_UBYTE*)&null,  1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bDest, ulDestSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulDestSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulDestSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bSrc,  ulSrcSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bDest, ulDestSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_COPY | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileTruncate
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_TRUNCATE  SUB(0x07)
//------------------------------------------------------------------------------
/**
 * @brief                 Truncates an file to the specified size.
 *
 *                        The function truncates a file. Be sure the file is not open yet before use. Opened file
 *                        should not call this function.
 *
 * @param[in ] ulFileId   File id which has already opened.
 * @param[in ] ulNewSize  New size of the file.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileTruncate(MMP_ULONG ulFileId, MMP_ULONG ulNewSize)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulFileId);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulNewSize);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_TRUNCATE | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileGetSize
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
MMP_ERR MMPD_FS_FileGetSize(MMP_ULONG ulFileId, MMP_ULONG64 *ulFileSize)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulFileId);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_GET_SIZE | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulFileSize = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
        *ulFileSize |= ((MMP_ULONG64)MMPH_HIF_GetParameterL(GRP_IDX_USR, 8)) << 32;
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileRemove
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
MMP_ERR MMPD_FS_FileRemove(MMP_BYTE *bpFileName, MMP_ULONG ulNameSize)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpFileName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpFileName, ulNameSize);
    #endif

    MMP_DBG_MSG(0, " @ MMPD_FS_FileRemove => [%s]\n", bpFileName);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_REMOVE | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMP_DBG_ERR(1, " @+@ ERROR:MMPD_FS_FileRemove => MMPH_HIF_SendCmd [%s]\n", bpFileName);
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
    if (mmpstatus){
        MMP_DBG_ERR(1, " @+@ ERROR:MMPD_FS_FileRemove => MMPH_HIF_GetParameterL [%s]\n", bpFileName);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirGetAttribute
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETATTRIBUTES  SUB(0x0A)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves attributes for a specified file or directory.
 *
 * @param[in ] bpName       Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute    retrieves the attributes value.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPD_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPD_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPD_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPD_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       MMPD_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPD_FS_FileDirGetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPD_FS_ATTRIBUTE *attribute)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_GETATTRIBUTES | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *attribute = MMPH_HIF_GetParameterB(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirGetInfo
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETINFO  SUB(0x2A)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves attributes for a specified file or directory.
 *
 * @param[in ] bpName       Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] attribute    retrieves the attributes value.
 * @param[out] ulpTimeStamp retrieves timestamp.
 * @param[out] ulpFileSize  retrieves the file size. If the input is a directory, then return 0
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPD_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPD_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPD_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPD_FS_ATTR_DIRECTORY  The given bpName is a directory.
 * @remarks \arg \b       MMPD_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPD_FS_FileDirGetInfo(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPD_FS_ATTRIBUTE *attribute, MMP_ULONG *ulpTimeStamp, MMP_ULONG *ulpFileSize)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_GETINFO | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        if(ulpTimeStamp)
            *ulpTimeStamp = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
        if(ulpFileSize)
            *ulpFileSize = MMPH_HIF_GetParameterL(GRP_IDX_USR, 8);
        if(attribute)
            *attribute = MMPH_HIF_GetParameterB(GRP_IDX_USR, 12);
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirGetFileTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_GETFILETIME  SUB(0x0B)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves timestamp for a specified file or directory.
 *
 * @param[in ] bpName      Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[out] ulpTimeStamp Retrieves timestamp.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileDirGetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMP_ULONG *ulpTimeStamp)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_GETTIME | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulpTimeStamp = (MMP_ULONG)MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirMove
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_MOVE  SUB(0x0C)
//------------------------------------------------------------------------------
/**
 * @brief                 Moves an existing file or a directory, including its childen.
 *
 * @param[in ] bNameSrc   Pointer to a string that names an existing file or directory.
 * @param[in ] ulSrcSize    The length, in bytes, of pFullNameSrc string, including the terminating null character.
 * @param[in ] bNameDest  Pointer to a string that specifies the name of the new file or directory. The file should not exist.
 * @param[in ] ulDestSize   The length, in bytes, of pFullNameDest string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_FileDirMove(MMP_BYTE *bNameSrc, MMP_ULONG ulSrcSize,
                                   MMP_BYTE *bNameDest,MMP_ULONG ulDestSize)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bNameSrc,  ulSrcSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulSrcSize, (MMP_UBYTE*)&null,  1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulSrcSize + 1, (MMP_UBYTE*)&null,  1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf ,(MMP_UBYTE*)bNameDest, ulDestSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulDestSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulDestSize + 1,(MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)pNameSrc,  ulSrcSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf ,(MMP_UBYTE*)bNameDest, ulDestSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_MOVE | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirRename
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_RENAME  SUB(0x0D)
//------------------------------------------------------------------------------
/**
 * @brief                 Renames an existing file or a directory.
 *
 * @param[in ] bOldName   Pointer to a string that names an existing file or directory.
 * @param[in ] ulOldNameSize The length, in bytes, of bpOldName string, including the terminating null character.
 * @param[in ] bNewName   Pointer to a string that specifies the name of the new file or directory.
 * @param[in ] ulNewNameSize The length, in bytes, of bpNewName string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               bpNewName should not point to a fullpath name ???
 *
 */
MMP_ERR MMPD_FS_FileDirRename(MMP_BYTE *bOldName,  MMP_ULONG ulOldNameSize,
                                     MMP_BYTE *bNewName,  MMP_ULONG ulNewNameSize)
{
    MMP_ULONG file_id;
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    mmpstatus = MMPD_FS_FileOpen(bNewName, ulNewNameSize, "r", strlen("r"), &file_id);

    if (mmpstatus == MMP_ERR_NONE) {
        MMPD_FS_FileClose(file_id);
        return MMP_FS_ERR_FILE_EXIST;
    }
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bOldName, ulOldNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulOldNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulOldNameSize + 1, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bNewName, ulNewNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulNewNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf + ulNewNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bOldName, ulOldNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulBuf, (MMP_UBYTE*)bNewName, ulNewNameSize);
    #endif

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_RENAME | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirSetAttribute
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_SETATTRIBUTES  SUB(0x0E)
//------------------------------------------------------------------------------
/**
 * @brief                 Set attributes for a specified file or directory.
 *
 * @param[in ] bpName      Pointer to a string that names an existing file or directory.
 * @param[in ] ulNameSize  The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] attribute   attribute to be set to the file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 *
 * @remarks               The attributes can be one or more of the following values:
 * @remarks \arg \b       MMPD_FS_ATTR_READ_ONLY  The file or directory is read-only. Applications can read the file but can not write
 *                                                to it or delete it. In the case of a directory, applications can not delete it.
 * @remarks \arg \b       MMPD_FS_ATTR_HIDDEN     The file or directory is hidden. It is not included in an ordinary directory listing.
 * @remarks \arg \b       MMPD_FS_ATTR_SYSTEM     The file or directory is part of, or is used exclusively by, the operating system.
 * @remarks \arg \b       MMPD_FS_ATTR_ARCHIVE    The file or directory is an archive file or directory.
 *                                                Applications can use this attribute to mark files for backup or removal.
 * @remarks               Above attributes can be combined with the \b OR operator (|) .
 */
MMP_ERR MMPD_FS_FileDirSetAttribute(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMPD_FS_ATTRIBUTE attribute)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    #endif

    MMPH_HIF_SetParameterB(GRP_IDX_USR, 0, attribute);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_SETATTRIBUTES | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FileDirSetTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_SETTIME  SUB(0x0F)
//------------------------------------------------------------------------------
/**
 * @brief                 Set the timestamp for a specified file or directory.
 *
 * @param[in ] bpName      Pointer to a string that specifies the name of a file or directory.
 * @param[in ] ulNameSize   The length, in bytes, of bpName string, including the terminating null character.
 * @param[in ] ulTimeStamp  Timestamp to be set to file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
  */
MMP_ERR MMPD_FS_FileDirSetTime(MMP_BYTE *bpName, MMP_ULONG ulNameSize, MMP_ULONG ulTimeStamp)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpName, ulNameSize);
    #endif

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulTimeStamp);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_USR, FS_FILE_DIR_SETTIME | HIF_USR_CMD_FS_ACCESS);
    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_USR);
        return mmpstatus;
    }

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirClose
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
MMP_ERR MMPD_FS_DirClose(MMP_ULONG ulDirID)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirID);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_CLOSE | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirGetNumFiles
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_GETNUMFILES  SUB(0x15)
//------------------------------------------------------------------------------
/**
 * @brief                 The function retrieves the number of files in a opened directory.
 *
 * @param[in ] ulDirID      Directory ID
 * @param[out] ulFileCount Retrieves the number of files in a directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_DirGetNumFiles(MMP_ULONG ulDirID, MMP_ULONG *ulFileCount)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirID);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_GETNUMFILES | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulFileCount = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirCreate
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_CREATE  SUB(0x16)
//------------------------------------------------------------------------------
/**
 * @brief                 Creates a new directory.
 *
 * @param[in ] bpDirName   Pointer to a string that specifies a fully qualified directory name.
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
MMP_ERR MMPD_FS_DirCreate(MMP_BYTE *bpDirName, MMP_ULONG ulNameSize)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDirName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDirName, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_CREATE | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirOpen
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_OPEN  SUB(0x17)
//------------------------------------------------------------------------------
/**
 * @brief                 Open an existing directory for reading.
 *
 * @param[in ] bDirName   Pointer to a string that specifies a fully qualified directory name.
 * @param[in ] ulNameSize The length, in bytes, of bpDirName string, including the terminating null character.
 * @param[out] ulDirID    Retrieves opened directory id.
 *
 * @retval MMP_ERR_NONE   Succeed.
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
MMP_ERR MMPD_FS_DirOpen(MMP_BYTE *bDirName, MMP_ULONG ulNameSize, MMP_ULONG *ulDirID)
{
    MMP_ERR mmpstatus;

    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bDirName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDirName, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_OPEN | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulDirID = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirRewind
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
MMP_ERR MMPD_FS_DirRewind(MMP_ULONG ulDirID)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirID);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_REWIND | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirRemove
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
MMP_ERR MMPD_FS_DirRemove(MMP_BYTE *bpDirName, MMP_ULONG ulNameSize)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDirName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDirName, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_REMOVE | HIF_USR_CMD_FS_ACCESS);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);


    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_HighLevelFormat
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
MMP_ERR MMPD_FS_HighLevelFormat(MMP_BYTE *bpDevice, MMP_ULONG ulNameSize)
{
    MMP_ERR mmpstatus;

    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDevice, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDevice, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_HIGH_LEVLE_FORMAT | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetFreeSpace
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
MMP_ERR MMPD_FS_GetFreeSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpFreeBytes)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_FREE_SPACE | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulpFreeBytes = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
        *ulpFreeBytes |= ((MMP_ULONG64)MMPH_HIF_GetParameterL(GRP_IDX_USR, 8)) << 32;
    }


    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetTotalSpace
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
MMP_ERR MMPD_FS_GetTotalSpace(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_ULONG64 *ulpTotal)
{
    MMP_ERR mmpstatus;

    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_TOTAL_SPACE | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulpTotal = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
        *ulpTotal |= ((MMP_ULONG64)MMPH_HIF_GetParameterL(GRP_IDX_USR, 8)) << 32;
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetNumVolumes
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
MMP_ERR MMPD_FS_GetNumVolumes(MMP_LONG *lpNumVols)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_NUM_VOLUMES | HIF_USR_CMD_FS_ACCESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *lpNumVols = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetVolumeName
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_VOLUME_NAME  SUB(0x20)
//------------------------------------------------------------------------------
/**
 * @brief                 Retrieves the name of specified volume.
 *
 *                        This function can be used to get the name of each available volume.
 *
 * @param[in ] lIndex      lIndex number of the volume.
 * @param[out] bpBuffer    Pointer to a buffer that receives the null-terminated string for the volume name.
 * @param[in ] lBufferSize sSize of the buffer to receive the null terminated string for the volume name.
 * @param[out] lpVolNamLen Retrieves the length, in bytes, of the string copied to bpBuffer,
 *                        \b not \b including the terminating null characher.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_GetVolumeName(MMP_LONG lIndex, MMP_BYTE *bpBuffer,
                               MMP_LONG lBufferSize, MMP_LONG *lpVolNamLen)
{
    MMP_ERR mmpstatus;
    MMP_UBYTE *ptr;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, lIndex);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, lBufferSize);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_VOLUME_NAME | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *lpVolNamLen = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);  // return length not include terminate char.
        ptr = (MMP_UBYTE*) bpBuffer;

        #if (_USE_FAST2_MODE_)
        MMPH_HIF_MemCopyDevToHost(ptr ,m_ulNam, *lpVolNamLen);  // host <- Dma
        ptr[ *lpVolNamLen ] = '\0';   //terminating null char
        #else
        MMPH_HIF_MemCopyDevToHost(ptr ,m_ulNam, *lpVolNamLen);  // host <- Dma
        #endif
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_IsVolumeMounted
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
MMP_ERR MMPD_FS_IsVolumeMounted(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{

    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_IS_VOLUME_MOUNTED | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

                                            // == 0 if volume information is already mounted or
                                            //          was mounted successfully.
                                            // != 0 in case of error, e.g. if the volume could not
                                            //          be found, is not detected or has incorrect
                                            //          file system information...

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_MountVolume
//  Description : HIF_USR_CMD_FS_ACCESS | FS_MOUNT_VOLUME  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                 Mount the volume
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_MountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{

    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_MOUNT_VOLUME | HIF_USR_CMD_FS_ACCESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
                                            // == 0 if volume information is already mounted or
                                            //          was mounted successfully.
                                            // != 0 in case of error, e.g. if the volume could not
                                            //          be found, is not detected or has incorrect
                                            //          file system information...


    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_UnmountVolume
//  Description : HIF_USR_CMD_FS_ACCESS | FS_UNMOUNT_VOLUME  SUB(0x21)
//------------------------------------------------------------------------------
/**
 * @brief                 Unmount the volume
 *
 * @param[in ] bpVolume    Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_UnmountVolume(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize)
{

    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_UNMOUNT_VOLUME | HIF_USR_CMD_FS_ACCESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
                                            // == 0 if volume information is already mounted or
                                            //          was mounted successfully.
                                            // != 0 in case of error, e.g. if the volume could not
                                            //          be found, is not detected or has incorrect
                                            //          file system information...


    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_CheckMediumPresent
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
MMP_ERR MMPD_FS_CheckMediumPresent(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMP_UBYTE *ubpValue)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_CHECK_MEDIUM_PRESENT | HIF_USR_CMD_FS_ACCESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ubpValue = MMPH_HIF_GetParameterB(GRP_IDX_USR, 4); // 0 - Volume is unmounted
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
                                         // 1 - Volume is still mounted
    return mmpstatus;
}


//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetVolumeInfo
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_VOLUME_INFO  SUB(0x23)
//------------------------------------------------------------------------------
/**
 * @brief                 Get volume information.
 *
 *                        This function can get volume information, which is the bytes size per secter and
 *                        the number of sector per cluster, also the number of free clusters and total clusters.
 *
 * @param[in ] bpVolume     Volume name string.
 * @param[in ] ulNameSize   The length, in bytes, of bpVolume string, including the terminating null character.
 * @param[out] pInfo        Disk info structure.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others           Fail.
 */
MMP_ERR MMPD_FS_GetVolumeInfo(MMP_BYTE *bpVolume, MMP_ULONG ulNameSize, MMPD_FS_DISK_INFO *pInfo)
{
    MMP_ERR mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpVolume, ulNameSize);
    #endif

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_VOLUME_INFO | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        pInfo->usBytesPerSector = MMPH_HIF_GetParameterW(GRP_IDX_USR, 4);
        pInfo->usSecPerCluster = MMPH_HIF_GetParameterW(GRP_IDX_USR, 6);
        pInfo->ulTotalClusters = MMPH_HIF_GetParameterL(GRP_IDX_USR, 8);
        pInfo->ulFreeClusters = MMPH_HIF_GetParameterL(GRP_IDX_USR, 12);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetFileList
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_FILE_LIST  SUB(0x24)
//------------------------------------------------------------------------------
/**
 * @brief                 Get the current directory entry information for the specified directory.
 *
 *                        This function gets the current directory entry: name, attributes, time, and size.
 *                        If no more entry in the directory, it will return MMPD_FS_ERR_NO_MORE_ENTRY.
 *
 * @param[in ] ulDirId    Directory ID.
 * @param[in ] uInfoMode  4 different mode. Mode attributes can be combined with the \b OR operator (|) .
 *                        \arg MMPD_FILE_NAME  enable \a bpBuffer to get entry name.
 *                        \arg MMPD_ATTRIBUTE  enable \a ubpAttr to get entry attributes.
 *                        \arg MMPD_FILE_TIME  enable \a pFileTime to get entry time structure.
 *                        \arg MMPD_ENTRY_SIZE enable \a ulpEntrySize to get entry size.
 * @param[out] bBuffer    Pointer to a buffer that get the entry name.
 * @param[out] attribute    Pointer to a integer that get the entry attributes.
 * @param[out] ulTimeStamp  Pointer to a buffer that get the entry time stamp.
 * @param[out] ulEntrySize  Pointer to a buffer that get the entry size.
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_GetFileList(MMP_ULONG ulDirId, MMP_UBYTE uInfoMode, MMP_BYTE* bBuffer,
                           MMPD_FS_ATTRIBUTE *attribute, MMP_ULONG* ulTimeStamp, MMP_ULONG* ulEntrySize)
{
    MMP_ERR mmpstatus;
    MMP_ULONG length;
    MMP_UBYTE *ptr;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirId);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, uInfoMode);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_FILE_LIST | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulTimeStamp  = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
        *ulEntrySize  = MMPH_HIF_GetParameterL(GRP_IDX_USR, 8);
        length        = MMPH_HIF_GetParameterL(GRP_IDX_USR, 12); // length not includes terminating null char.
        *attribute    = MMPH_HIF_GetParameterB(GRP_IDX_USR, 16);

        ptr = (MMP_UBYTE*)bBuffer;
        MMPH_HIF_MemCopyDevToHost(ptr ,m_ulNam, length);
        *(ptr+length) = '\0';       //terminating null char
        *(ptr+length+1) = '\0';     //support USC2 format, add one more terminating null char
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetDBFileList
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_FILE_LIST_DB  SUB(0x2D)
//------------------------------------------------------------------------------
/**
 * @brief                 Get the current directory entry information for the specified directory.
 *
 *                        This function gets the current directory entry: name, attributes, time, and size.
 *                        If no more entry in the directory, it will return MMPD_FS_ERR_NO_MORE_ENTRY.
 *
 * @param[in ] ulDirId    Directory ID.
 * @param[out] bBuffer    Pointer to a buffer that get the entry name.
 * @param[out] attribute    Pointer to a integer that get the entry attributes.
 * @param[out] ulFileID  Pointer to the output open file ID
 *
 * @retval MMP_ERR_NONE   Succeed.
 * @retval others         Fail.
 */
MMP_ERR MMPD_FS_GetDBFileList(MMP_ULONG ulDirId, MMP_BYTE* bBuffer, MMPD_FS_ATTRIBUTE *attribute, MMP_ULONG *ulFileID)
{
    MMP_ERR mmpstatus;
    MMP_ULONG length;
    MMP_UBYTE *ptr;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirId);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_FILE_LIST_DB | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        length        = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4); // length not includes terminating null char.
        *ulFileID     = MMPH_HIF_GetParameterL(GRP_IDX_USR, 8);
        *attribute    = MMPH_HIF_GetParameterB(GRP_IDX_USR, 12);

        ptr = (MMP_UBYTE*)bBuffer;
        MMPH_HIF_MemCopyDevToHost(ptr ,m_ulNam, length);
        *(ptr+length) = '\0';       //terminating null char
        *(ptr+length+1) = '\0';     //support USC2 format, add one more terminating null char
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetCreationTime
//  Description : HIF_USR_CMD_FS_ACCESS | FS_FILE_DIR_SETTIME  SUB(0x25)
//------------------------------------------------------------------------------
/**
 * @brief                 Set the time structure for a new file or directory.
 *
 * @param[in ] ulTimeStamp  Timestamp to be set to file or directory.
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
  */
MMP_ERR MMPD_FS_SetCreationTime(MMP_ULONG ulTimeStamp)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulTimeStamp);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_CREATION_TIME | HIF_USR_CMD_FS_ACCESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetSDClass
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_GET_SDCLASS  SUB(0x08)
//------------------------------------------------------------------------------
/**
 * @brief
 *
 * @retval MMP_ERR_NONE     Succeed.
 * @retval others         Fail.
  */
MMP_ERR MMPD_FS_GetSDClass(MMP_ULONG id, MMP_UBYTE *bClass)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, id);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, (MMP_ULONG)bClass);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_SDCLASS | HIF_USR_CMD_FS_SETADDRESS );

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetFileNameDmaAddr
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_FILENAME_ADDRESS  SUB(0x01)
//------------------------------------------------------------------------------
/**
 * @brief                 Set file name dma address and fs read write buffer address
 *
 *                        This function change file name dma address for different
                          memory allocation of each mode.
 *
 * @param[in ] ulNameAddr  name buffer start address (8 bytes alignment)
 * @param[in ] ulNameSize  name buffer size (at least 512 bytes)
 * @param[in ] ulBufAddr   parameter buffer start address(8 bytes alignment)
 * @param[in ] ulBufSize   parameter buffer size (at least 1024 bytes)
 *
 * @retval end of buffer size which is allocated.
 */
MMP_ERR MMPD_FS_SetFileNameDmaAddr(MMP_ULONG ulNameAddr, MMP_ULONG ulNameSize,
                             MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    m_ulNam = ulNameAddr;
    m_ulNamSize = ulNameSize;
    m_ulBuf = ulBufAddr;
    m_ulBufSize = ulBufSize;

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, m_ulNam);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, m_ulNamSize);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 8, m_ulBuf);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 12, m_ulBufSize);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_FILENAME_ADDRESS | HIF_USR_CMD_FS_SETADDRESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_DirGetNumDirs
//  Description : HIF_USR_CMD_FS_ACCESS | FS_DIR_GETNUMDIRS  SUB(0x26)
//------------------------------------------------------------------------------
/**
 *@brief        returns the number of dirs in a opend directory.
 *@param[in]    ulDirID  - dir id to get subdir number
 *@param[out]   ulDirCount - Number of directories in a directory.
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
 *@note         void
*/
MMP_ERR MMPD_FS_DirGetNumDirs(MMP_ULONG ulDirID, MMP_ULONG *ulDirCount)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulDirID);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_DIR_GETNUMDIRS | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulDirCount = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_INIT
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
MMP_ERR MMPD_FS_Initialize(void)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_INIT | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetMaxFileOpenSupport
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_MAX_FILE_COUNT  SUB(0x2C)
//------------------------------------------------------------------------------
/**
 *@brief        returns memory allocation size of SM.
 *
 *@retval       0   - no SM exist.
                !=0 - memory size required.
*/
MMP_ERR  MMPD_FS_GetMaxFileOpenSupport(MMP_ULONG *ulMaxFileCounts)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    *ulMaxFileCounts = 0;
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_MAX_FILE_COUNT | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulMaxFileCounts = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetMaxDirOpenSupport
//  Description : HIF_USR_CMD_FS_ACCESS | FS_GET_MAX_DIR_COUNT  SUB(0x2B)
//------------------------------------------------------------------------------
/**
 *@brief        returns memory allocation size of SM.
 *
 *@retval       0   - no SM exist.
                !=0 - memory size required.
*/
MMP_ERR  MMPD_FS_GetMaxDirOpenSupport(MMP_ULONG *ulMaxDirCounts)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    *ulMaxDirCounts = 0;
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_GET_MAX_DIR_COUNT | HIF_USR_CMD_FS_ACCESS);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulMaxDirCounts = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetSDTmpMemory
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_SD_TMP_ADDR  SUB(0x2)
//------------------------------------------------------------------------------
/**
 *@brief        set SD memory address and size ONLY for SDHC message handshake
 *@param[in]    ulStartAddr start address (8 bytes alignment)
 *@param[in]    ulSize CURRENTLY only support 64 byte
 *@warning The address has to be non-cached
 *@retval       MMP_ERR_NONE success.
 *@retval       Others fail.
*/
MMP_ERR  MMPD_FS_SetSDTmpMemory(MMP_ULONG ulStartAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulStartAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulSize);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_SD_TMP_ADDR | HIF_USR_CMD_FS_SETADDRESS);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
    return  MMP_ERR_NONE;
}

#if (OMA_DRM_EN == 1)
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetDRMIVMemory
//  Description : FS_SET_DRM_IV_ADDR | FS_SET_SD_TMP_ADDR  SUB(0x7)
//------------------------------------------------------------------------------
/**
 *@brief        set DRM IV memory address and size for drm file need to read IV from file system
 *@param[in]    ulStartAddr start address
 *@param[in]    ulSize CURRENTLY only support 16 byte
 *@warning The address has to be non-cached
 *@retval       MMP_ERR_NONE success.
 *@retval       Others fail.
*/
MMP_ERR  MMPD_FS_SetDRMIVMemory(MMP_ULONG ulStartAddr, MMP_ULONG ulSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulStartAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulSize);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_DRM_IV_ADDR | HIF_USR_CMD_FS_SETADDRESS);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
    return MMP_ERR_NONE;
}
#endif
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetSMMEMAlloc
//  Description : HIF_USR_CMD_FS_STORAGE | FS_STORAGE_CONFIG  SUB(0x2)
//------------------------------------------------------------------------------
/**
 *@brief        returns memory allocation size of SM.
 *
 *@retval       0   - no SM exist.
                !=0 - memory size required.
*/
MMP_ERR  MMPD_FS_GetSMMEMAlloc(MMP_ULONG *ulBufferRequired)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    *ulBufferRequired = 0;

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_STORAGE_CONFIG | HIF_USR_CMD_FS_STORAGE);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulBufferRequired = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetSMMemory
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_SM_MAP_ADDR  SUB(0x4)
//------------------------------------------------------------------------------
/**
 *@brief        set SM memory address and size
 *@param[in]    ulStartAddr   - start address (8 bytes alignment)
 *@warning The address has to be non-cached
 *@param[out]   sSize        - memory size.
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.

*/
MMP_ERR  MMPD_FS_SetSMMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulStartAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, sSize);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_SM_MAP_ADDR | HIF_USR_CMD_FS_SETADDRESS);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetSNMEMAlloc
//  Description : HIF_USR_CMD_FS_STORAGE | FS_STORAGE_CONFIG  SUB(0x2)
//------------------------------------------------------------------------------
/**
 *@brief        returns memory allocation size of SN.
 *
 *@retval       0   - no SN exist.
                !=0 - memory size required.
*/
MMP_ERR  MMPD_FS_GetSNMEMAlloc(MMP_ULONG *ulBufferRequired)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    *ulBufferRequired = 0;

    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_STORAGE_CONFIG | HIF_USR_CMD_FS_STORAGE);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulBufferRequired = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetSNMemory
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_SM_MAP_ADDR  SUB(0x4)
//------------------------------------------------------------------------------
/**
 *@brief        set SN memory address and size
 *@param[in]    ulStartAddr   - start address (8 bytes alignment)
 *@warning The address has to be non-cached
 *@param[out]   sSize        - memory size.
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
*/
MMP_ERR  MMPD_FS_SetSNMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulStartAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, sSize);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_SN_MAP_ADDR | HIF_USR_CMD_FS_SETADDRESS);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_GetSFMEMAlloc
//  Description : HIF_USR_CMD_FS_STORAGE | FS_SF_STORAGE_CONFIG  SUB
//------------------------------------------------------------------------------
/**
 *@brief        returns memory allocation size of SF.
 *
 *@retval       0   - no SF exist.
                !=0 - memory size required.
*/
MMP_ERR  MMPD_FS_GetSFMEMAlloc(MMP_ULONG ulIdBufAddr, MMP_ULONG *ulBufferRequired)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    *ulBufferRequired = 0;

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulIdBufAddr);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SF_STORAGE_CONFIG | HIF_USR_CMD_FS_STORAGE);
    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    if (mmpstatus == MMP_ERR_NONE) {
        *ulBufferRequired = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}
//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetSFMemory
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_SF_MAP_ADDR  SUB
//------------------------------------------------------------------------------
/**
 *@brief        set SF memory address and size
 *@param[in]    ulStartAddr  - start address.
 *@warning The address has to be non-cached
 *@param[out]   sSize        - memory size.
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.

*/
MMP_ERR  MMPD_FS_SetSFMemory(MMP_ULONG ulStartAddr, MMP_SHORT sSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulStartAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, sSize);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_SET_SF_MAP_ADDR | HIF_USR_CMD_FS_SETADDRESS);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_SetFATGlobalBufAddr
//  Description : HIF_USR_CMD_FS_SETADDRESS | FS_SET_FAT_GLOBALBUF_ADDR  SUB(0x6)
//------------------------------------------------------------------------------
/**
 *@brief        set fs global buffer address and size, size should be multiple of 512bytes
 *@param[in]    ulBufStart  - fat cache start address (4-byte alignment would be good in dram access)
 *@param[in]    ulFATCacheLen - FAT cache size per storage device(at least 1kBytes),
 *@warning      The address has to be non-cached
 *@retval       end of dma address which is allocated(fat cache size + total file/dir handle tmp buffer[1KB per handler])
*/
MMP_ULONG  MMPD_FS_SetFATGlobalBufAddr(MMP_ULONG ulBufStart, MMP_ULONG ulFATCacheLen)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, ulBufStart);
    MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, ulFATCacheLen);
    MMPH_HIF_SendCmd(GRP_IDX_USR, HIF_USR_CMD_FS_SETADDRESS | FS_SET_FAT_GLOBALBUF_ADDR);

    mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
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
 * @param[in,out] pBuffer   data buffer for read/write or device information



 * @retval MMP_ERR_NONE       Succeed.
 * @retval others           Fail.
 */
MMP_ERR MMPD_FS_IOCtl(MMP_BYTE *bpDeviceName, MMP_ULONG ulNameSize,
                        MMPD_FS_IOCTL_CMD Cmd, MMPD_FS_IOCTL_PARA *Aux,
                        void *pBuffer)
{
    MMP_ULONG   access_size, tmp_size;
    MMP_UBYTE   *buf;
    MMP_ERR     mmpstatus;
    #if (_USE_FAST2_MODE_)
    MMP_UBYTE null = 0x0;
    #endif

    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);

    access_size = Aux->ulPara[1]*512;
    buf = (MMP_UBYTE *)pBuffer;

    #if (_USE_FAST2_MODE_)
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDeviceName, ulNameSize);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulNam + ulNameSize + 1, (MMP_UBYTE*)&null, 1);
    #else
    MMPH_HIF_MemCopyHostToDev(m_ulNam, (MMP_UBYTE*)bpDeviceName, ulNameSize);
    #endif

    switch (Cmd) {
        case MMPD_FS_CMD_RESET_STORAGE:
        case MMPD_FS_CMD_GET_DEVINFO:
        case MMPD_FS_CMD_WRITE_PROTECT:
        case MMPD_FS_CMD_CARD_DETECT:
        case MMPD_FS_CMD_FINISH_WRITE:
        case MMPD_FS_CMD_GET_CARDSTATUS:
        case MMPD_FS_CMD_UNMOUNT_MEDIUM:
        case MMPD_FS_CMD_MOUNT_MEDIUM:
        case MMPD_FS_CMD_RESET_MEDIUM:
            MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, Cmd);

            MMPH_HIF_SendCmd(GRP_IDX_USR, FS_IO_CTL | HIF_USR_CMD_FS_STORAGE);
            mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

            if (mmpstatus){
                MMPH_HIF_ReleaseSem(GRP_IDX_USR);
                return mmpstatus;
            }
            ((MMP_ULONG *)pBuffer)[0] = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);
            break;

        case MMPD_FS_CMD_PWR_DISABLE:
            MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, Cmd );
            MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, Aux->ulPara[0]);

            MMPH_HIF_SendCmd(GRP_IDX_USR, FS_IO_CTL | HIF_USR_CMD_FS_STORAGE );

            mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);
            if (mmpstatus) {
                MMPH_HIF_ReleaseSem(GRP_IDX_USR);
                return mmpstatus;
            }
            ((MMP_ULONG *)pBuffer)[0] = MMPH_HIF_GetParameterL(GRP_IDX_USR, 4);

            break;

        case MMPD_FS_CMD_READ_SECTOR:

            while (access_size) {
                if (access_size >= m_ulBufSize) {
                    tmp_size = m_ulBufSize;
                }
                else {
                    tmp_size = access_size;
                }

                MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, Cmd );
                MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, Aux->ulPara[0]);
                MMPH_HIF_SetParameterL(GRP_IDX_USR, 8, (tmp_size/512));

                MMPH_HIF_SendCmd(GRP_IDX_USR, FS_IO_CTL | HIF_USR_CMD_FS_STORAGE);
                mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

                if (mmpstatus) {
                    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
                    return mmpstatus;
                }

                MMPH_HIF_MemCopyDevToHost(buf, m_ulBuf, tmp_size );

                access_size -= tmp_size;
                buf += tmp_size;
            }
            break;
        case MMPD_FS_CMD_WRITE_SECTOR:

            while (access_size) {
                if (access_size >= m_ulBufSize) {
                    tmp_size = m_ulBufSize;
                }
                else {
                    tmp_size = access_size;
                }

                MMPH_HIF_SetParameterL(GRP_IDX_USR, 0, Cmd );

                MMPH_HIF_SetParameterL(GRP_IDX_USR, 4, Aux->ulPara[0]);
                MMPH_HIF_SetParameterL(GRP_IDX_USR, 8, (tmp_size/512));


                MMPH_HIF_MemCopyHostToDev( m_ulBuf, buf, tmp_size );

                MMPH_HIF_SendCmd(GRP_IDX_USR, FS_IO_CTL | HIF_USR_CMD_FS_STORAGE);
                mmpstatus = MMPH_HIF_GetParameterL(GRP_IDX_USR, 0);

                if (mmpstatus) {
                    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
                    return mmpstatus;
                }
                access_size -= tmp_size;
                buf += tmp_size;
            }
            break;
        default:
            break;
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_USR);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_CacheClear
//  Description : HIF_USR_CMD_FS_ACCESS | FS_CACHE_CLEAR  SUB(0x2E)
//------------------------------------------------------------------------------
/**
 *@brief        Invalidate the File System cache manually

  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
 *@note         void
*/
void MMPD_FS_CacheClear(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_CACHE_CLEAR | HIF_USR_CMD_FS_ACCESS);
    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_CacheInvalidate
//  Description : HIF_USR_CMD_FS_ACCESS | FS_CACHE_INVALIDATE  SUB(0x2F)
//------------------------------------------------------------------------------
/**
 *@brief        Clear the File System cache manually

  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
 *@note         void
*/
void MMPD_FS_CacheInvalidate(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_USR, 0);
    MMPH_HIF_SendCmd(GRP_IDX_USR, FS_CACHE_INVALIDATE | HIF_USR_CMD_FS_ACCESS);
    MMPH_HIF_ReleaseSem(GRP_IDX_USR);
}
//------------------------------------------------------------------------------
//	Function	: MMPD_FS_GetSDCID
//	Description : 
//------------------------------------------------------------------------------
/**
 *@brief		  Get SD card CID info
  @param[in] SD_ID    SD card ID
  @param[in] CID      pointer CID and driver would store CID in it 
  @return SUCCESS - return MMP_ERR_NONE.
*/
MMP_ERR MMPD_FS_GetSDCID(MMP_ULONG SD_ID,MMP_BYTE *CID)
{
	return MMPF_FS_GetSDCID(SD_ID, CID);
}

#if (FORMAT_FREE_ENABLE)
//------------------------------------------------------------------------------
//  Function    : MMPD_FORMATFREE_CheckMedia
//  Description :
//------------------------------------------------------------------------------
/**
 *@brief          Check FormatFree FatTable for correctness

 *@warning
  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
 */
MMP_ERR MMPD_FORMATFREE_CheckMedia(MMP_BYTE bMedia)
{
    return MMPF_FORMATFREE_CheckMedia(bMedia);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FORMATFREE_Format
//  Description :
//------------------------------------------------------------------------------
/**
 *@brief          FormatFree format construction

 *@warning
  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
*/
MMP_ERR MMPD_FORMATFREE_Format(MMP_BYTE bMedia)
{
    return MMPF_FORMATFREE_Format(bMedia);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FORMATFREE_GetIdealFileNumInFolder
//  Description : Get ideal total files number in a Format Free folder
//                Note: This API should be called after MMPF_FORMATFREE_CheckMedia()
//                      or MMPF_FORMATFREE_Format().
//------------------------------------------------------------------------------
/**
 * @param[in ]    byFolderIndex - Folder index
 * @param[out]
 *
 *@retval         Ideal total files number

 * @remarks
 */
MMP_ULONG MMPD_FORMATFREE_GetIdealFileNumInFolder(MMP_BYTE byFolderIndex)
{
    return MMPF_FORMATFREE_GetIdealFileNumInFolder( byFolderIndex );
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FormatFreeFATTable
//  Description : Establish the FAT table for format free
//------------------------------------------------------------------------------
/**
 *@brief          Create the FAT table according correct Folder / File numbers and size
 *@param[in]      pVolume : media FS_Volume pointer
 *@param[in]      FileNoSUM : Sum of numbers of all files in all folders
 *@warning
  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
*/
MMP_ERR MMPD_FS_FormatFreeFATTable(FS_VOLUME  * pVolume, MMP_ULONG FileNoSUM)
{
    return MMPF_FS_FormatFreeFATTable(pVolume, FileNoSUM);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_FormatFreeFATCheck
//  Description : Check the media FAT table with the one which created by MMPS_FORMATFREE_Format
//------------------------------------------------------------------------------
/**
 *@brief          Check the FAT table according correct Folder / File numbers and size
 *@param[in]      pVolume : media FS_Volume pointer
 *@param[in]
 *@warning
 *@retval       SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
*/
MMP_ERR MMPD_FS_FormatFreeFATCheck(FS_VOLUME  * pVolume)
{
    return MMPF_FS_FormatFreeFATCheck(pVolume);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FS_MakeFileDirEntry
//  Description :
//------------------------------------------------------------------------------
/**
 *@brief          Create the File Name Directory Entry inside each folder
 *@param[in]      pVolume : media FS_Volume pointer
 *@param[in]      pFileName : Filename <char pointer>
 *@param[in]      FileNUM : File Number of the folder
 *@param[in]      FileSize : File Size for each file
 *@param[in]      FolderClusterNumber : Folder Cluster ID
 *@param[in]      FileClusterNumber   : File Starting Cluster ID
 *@warning
  *@retval      SUCCESS - return MMP_ERR_NONE.
                FAIL    - return !=0.
*/
MMP_ERR MMPD_FS_MakeFileDirEntry(FS_VOLUME * pVolume, const MMP_BYTE *pFileName, MMP_ULONG FileNUM ,MMP_ULONG FileSize, U64 FolderClusterNumber, U64 FileClusterNumber, MMP_ULONG ParentClusterID)
{
    return MMPF_FS_MakeFileDirEntry(pVolume, pFileName, FileNUM, FileSize, FolderClusterNumber, FileClusterNumber, ParentClusterID);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_FORMATFREE_RegisterCallback
//  Description :
//------------------------------------------------------------------------------
/**
 *@brief          Register Callback under Format Free
  @param[in] Event    Specified the event for register.
  @param[in] CallBack The callback to be executed when the specified event happens.
  @return It reports the status of the operation.
  @warn The registered callback will not be auto deleted, please register a NULL
      to delete it.
*/
MMP_ERR MMPD_FORMATFREE_RegisterCallback(MMPD_FileSystem_EVENT Event, void *CallBack)
{
    MMP_ULONG e;

    switch (Event) {
    case MMPD_FileSystem_EVENT_FileName_Require:
        e = MMPF_FileSystem_EVENT_FileName_Require;
        break;
    case MMPF_FileSystem_EVENT_NONE:
    default:
        e = 0;
        break;
    }
    return MMPF_FORMATFREE_RegisterCallback(e, CallBack);
}

#endif // #if (FORMAT_FREE_ENABLE)

/// @}
/// @end_ait_only
