////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_filemgr_fstream.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_FSTREAM_H__
#define __SRV_FILEMGR_FSTREAM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_mae_interface_def.h"
#include "srv_filemgr_data_types.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define FILEMGR_STREAM_SIZE_UNAVAILABLE         0xFFFFFFFF
#define FILEMGR_FS_ERROR		                (~0)	// Refer to EOF on file system, indicating that errors on file system during FS write.
#define FILEMGR_FS_VOLUME_FULL                  (~1)    // Refer to EOF on file system, indicating that errors on volume full during FS write
#define MAE_FS_ERROR		                    (~0)	// Refer to EOF on file system, indicating that errors on file system during FS write.

/*=============================================================*/
// Type Declarations
/*=============================================================*/

enum
{
    FILEMGR_STREAM__NOTIFY = 0,
    FILEMGR_STREAM__SUCEESS,
    FILEMGR_STREAM__ERROR
};

typedef u32 FileMgrStreamState;
typedef enum FileMgrSeekType_enum
{
    FILEMGR_SEEK__CUR, // Current position of file pointer
    FILEMGR_SEEK__END, // End of file
    FILEMGR_SEEK__SET  // Beginning of file
} FileMgrSeekType_e;

typedef struct
{
    void *pHandle; // file handle
    void *pInfo; // file information to this file, valid only if this file is created as read only.
    u8 nVolume; // index of volume where this file locates.
} FileMgrFileInit_t;

typedef struct
{
    void *pBuffer; // Data buffer
    u32 nCount; // number of bytes storing to the file stream
    void *pCallBackFuncPtr; // Callback function which will be executed while the operation is done. User can free pBuffer in this callback.
} FileMgr_WriteCmd_t; // copy the command of FStream_write to perform asynchrous API.

typedef struct FileMgrFileCallback_tag
{
    s32 nRetCode; // return code after file write
    void *pCaller; // the object instance who use ifstream
    void *pUserData; // anything that caller wish to receive during call back. Ex: someone may add id here to distinguish something if he use same callback function
} FileMgrFileCallback_t;

typedef struct FileMgrStreamCallback_tag
{
    FileMgrStreamState nState;
    u32 nByteRead;
    void *pBufferPtr;
} FileMgrStreamCallback_t;

typedef void (*PfnFileMgr_StreamCallback)(void *pUser, FileMgrStreamCallback_t *pInfo);

typedef struct FileMgr_Stream_tag
{
    u32 nRefCnt; // reference nCount
    u32 nStreamSize; // valid if this stream is opened as read mode, passed from IFileMgr.
    void *pCbPtr; // call back pointer
    void *pCbParam; // parameter of callback pointer
    FileMgrStreamCallback_t *pCBReadData; // Pointer to read callback data.
    void *pFp; //VFS_FILE *pFp; // File Handle
    s32	nReadSessionID;
    s32	nWriteSessionID;
    FileMgr_WriteCmd_t* pCmd; // Store last write command.
    FileMgrFileCallback_t *pCBData; // Pointer to callback data, the memory belongs to caller
    u16 nBufSize; // length of read buffer
    u8 nVolume; // volume id of this file. The valid value is MAE_VOL_NOR, MAE_VOL_NAND, MAE_VOL_SD
} FileMgr_Stream_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/** FileMgrOpenFile
@brief  Open a file and get its fstream class

@param[out]     ppStream            get the Client of FStream Service; it can use to operate the Fstream Service
@param[in]      pStrURL             File url
@param[in]      nMode               The open mode of file
@param[in]      pOwner              IBase


@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. do not open the file
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret FileMgrOpenFile(FileMgr_Stream_t **ppStreamResult, const FileMgr_WChar *pStrURL, const u8 *pMode, IBase *pOwner);

/** SrvFileMgrCloseFile
@brief  Close a file

@param[out]     pIFStream           close file stream

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. do not open the file
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret FileMgrCloseFile(FileMgr_Stream_t *pStream);

/**
 *  FileMgrStreamRead
 *  \brief  Read from file
 *
 *  \param  pStream           Pointer to the pIAStream interface
 *  \param  pBuffer           Pointer to the buffer into which the data is being read.
 *  \param  nWordCnt          Number of bytes to read.
 *	\param  pByteRead         Pointer to an integer returning the cumber of bytes read if data is available for reading.
 *                            if *pByteRead = 0, it means all available data is read
 *  \retval MAE_RET_SUCCESS   SUCCESS.
 *  \retval MAE_STREAM_BLOCK if no data is currently available.
 */
MAE_Ret FileMgrStreamRead(FileMgr_Stream_t *pStream, void *pBuffer, u32 nWordCnt, u32 *pByteRead);

/**
 *  FileMgrStreamRead
 *  \brief  Read from file
 *
 *  \param  pStream           Pointer to the pIAStream interface
 *  \param  pBuffer           Pointer to the buffer into which the data is being read.
 *  \param  nWordCnt          Number of bytes to read.
 *	\param  pByteRead         Pointer to an integer returning the cumber of bytes read if data is available for reading.
 *                            if *pByteRead = 0, it means all available data is read
 *  \retval MAE_RET_SUCCESS   SUCCESS.
 *  \retval MAE_STREAM_BLOCK if no data is currently available.
 */
__SLDPM_FREE__ MAE_Ret FileMgrStreamSyncRead(FileMgr_Stream_t *pStream, void *pBuffer, u32 nWordCnt, u32 *pByteRead);

/**
 *  FileMgrStreamWrite
 *  @brief  Write data to a stream from current file pointer. It is a non-blocking interface if we don't specify pfnCB.
 *
 *  @param  pStream            Pointer to the FStream interface
 *  @param  pBuffer            Data buffer
 *  @param  nCount             number of bytes to be stored to the file stream
 *  @param  pfnCallBackFuncPtr Callback function which will be executed while the operation is done. User can free pBuffer in this callback. If pfnCB is NULL,
 *                             this API is blocking.
 *  @param  pCallBackData      Place holder to MAEFSWriteCallBack_s structure, including the pointer of the caller instance, userdata and an U32 space to write return code
                               during callback. FStream objects won't free this memory. It is recommended to free this memory inside callback function.
 *  @retval MAE_RET_FS_ERROR   1.Error on file system. 2. Previous request has not been proceed and a new request comes in asychronus mode.
                               3. Invalid caller object within pCallBackData structure.
 *  @retval Others		       Number of bytes written
 */
MAE_Ret FileMgrStreamWrite(FileMgr_Stream_t *pStream, const void *pBuffer, u32 nCount, FileMgrCallback_Fxp pfnCallBackFuncPtr, FileMgrFileCallback_t *pCallBackData);

/**
 *  FileMgrStreamSyncWrite
 *  @brief  Write data to a stream from current file pointer. It is a non-blocking interface if we don't specify pfnCB.
 *
 *  @param  pStream            Pointer to the FStream interface
 *  @param  pBuffer            Data buffer
 *  @param  nCount             number of bytes to be stored to the file stream
 *  @retval MAE_RET_FS_ERROR   1.Error on file system. 2. Previous request has not been proceed and a new request comes in asychronus mode.
                               3. Invalid caller object within pCallBackData structure.
 *  @retval Others		       Number of bytes written
 */
MAE_Ret FileMgrStreamSyncWrite(FileMgr_Stream_t *pStream, const void *pBuffer, u32 nCount);

/**
 *  FileMgrStreamSetCallBack
 *  \brief Set a callback function. After the data is available, it would execute this function.
 *
 *  \param  pStream          Pointer to the pIAStream interface
 *  \param  pfnStreamCB      Pointer to the callback function
 *  \param  pUser            Pointer to user-specified data that is passed as a parameter to the callback function.
 *  \retval None
 *
 */
void FileMgrStreamSetCallBack(FileMgr_Stream_t *pStream, PfnFileMgr_StreamCallback pfnStreamCB, void *pUser);

/** FileMgrStreamCancelCallBack
 *  \brief  Cancel the callback function
 *  \param  pStream         Pointer to the pIAStream interface
 *  \retval None
 */
void FileMgrStreamCancelCallBack(FileMgr_Stream_t *pStream);

/**
 *  @brief  Get the size of this stream, used for allocating buffers
 *  @param  pStream         Pointer to the IFStream interface
 *  @return The size of this stream, type u32
 */
MAE_Ret FileMgrStreamCheckStreamSize(FileMgr_Stream_t *pStream);

/**
 *  FileMgrStreamSeek
 *  @brief  Move currect file pointer
 *
 *  @param  pStream          Pointer to the FStream interface
 *  @param  nOffset          Move dinstance. Both positive or negetive value are avaiable.
 *	@param  eSeekType        Seek from current pointer, beginning or end of file. Types are MAE_SEEK_CUR, MAE_SEEK_END, MAE_SEEK_SET

 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Failed
 *  @retval MAE_RET_BUSY		There's already a nonblocking command which has not finished.
 */
__SLDPM_FREE__ MAE_Ret FileMgrStreamSeek(FileMgr_Stream_t *pStream, s32 nOffset, FileMgrSeekType_e eSeekType);

/**
 *  FileMgrStreamGetCurrentPos
 *  @brief  Return the current file position
 *
 *  @param  pStream       Pointer to the FStream interface

 *  @retval MAE_RET_FS_ERROR	1.Error on file system.
 *  @retval Others			    Offset from the beginning of the stream
 */
s32 FileMgrStreamGetCurrentPos(FileMgr_Stream_t *pStream);

/**
 *  FileMgrStreamEOF
 *  @brief  Check if the stream is at the end of file.
 *
 *  @param  pStream     Pointer to the FStream interface
 *  @retval TRUE		The stream reaches to EOF
 *  @retval FALSE		Not end of file.
 */
MAE_Ret FileMgrIsStreamEOF(FileMgr_Stream_t *pStream);

#endif// __SRV_FILEMGR_FSTREAM_H__
