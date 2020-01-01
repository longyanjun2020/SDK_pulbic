/**
* @file    mmi_srv_filemgr.h
* @brief
*
*/

#ifndef __MMI_SRV_FSTREAM_H__
#define __MMI_SRV_FSTREAM_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "filemgr_fstream.h"

typedef void *hFstream;

//hFstream is get form File manager service file open operation and close by file close

/** SrvFstreamSyncRead
@brief  The interface is use to Read stream data from file.

@param[in]  hFstream            Fstream handler
@param[in]  pReadBuffer         Pointer to the buffer into which the data is being read.
@param[in]  nReadSize           Number of bytes to read.
@param[out] pByteRead           Pointer to an integer returning the cumber of bytes read if data is available for reading
                                if *byteRead = 0, it means all available data is read

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FS_ERROR            If FStream busy. 
@retval MAE_RET_BAD_PARAM       If invalid object during setting FStream callback. 
@retval MAE_RET_FAILED          If file read len < 0
*/
__SLDPM_FREE__ MAE_Ret SrvFstreamSyncRead(hFstream pFstream, void *pReadBuffer, u32 nReadSize, u32 *pByteRead);

/** SrvFstreamSeek
@brief  The interface is use to Move current file pointer

@param[in]  hFstream            Fstream handler
@param[in]  nPost               Move distance. Both positive or negative value are available.
@param[in]  eSeekType           Seek from current pointer, beginning or end of file. 
                                Types are MAE_SEEK_CUR, MAE_SEEK_END, MAE_SEEK_SET

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BUSY            If an error happen. 
*/
__SLDPM_FREE__ MAE_Ret SrvFstreamSeek(hFstream pFstream, s32 nPost, FileMgrSeekType_e eSeekType);

/** SrvFstreamGetCurrentPos
@brief  The interface is use to get current file pointer

@param[in]  hFstream                Fstream handler

@retval  Current file position
*/
s32 SrvFstreamGetCurrentPos(hFstream pFstream);

/** SrvFstreamWrite
@brief  The interface is use to get current file pointer

@param[in]  hFstream                Fstream handler
@param[out] pBuffer                 Current file position
@param[in]  nSize                   number of bytes to be stored to the file stream
@param[in]  pnfFstreamWriteCB       Fstream write end callback (can be NULL, if not available)
@param[in]  pUserDat                User data for Write CB used (can be NULL if not used callback)

@retval MAE_RET_FS_ERROR	1.Error on file system. 2. Previous request has not been proceed and a new request comes in asychronus mode.
                        3. Invalid caller object within pCallBackData structure.
@retval Others			Number of bytes written
*/
MAE_Ret SrvFstreamWrite(hFstream pFstream,
                    const void *pBuffer,
                    u32 nSize,
                    FileMgrCallback_Fxp pnfFstreamWriteCB,
                    FileMgrFileCallback_t *pUserDat);

/** SrvFstreamSyncWrite
@brief  The interface is use to get current file pointer

@param[in]  hFstream                Fstream handler
@param[out] pBuffer                 Current file position
@param[in]  nSize                   number of bytes to be stored to the file stream

@retval MAE_RET_FS_ERROR	1.Error on file system. 2. Previous request has not been proceed and a new request comes in asychronus mode.
                        3. Invalid caller object within pCallBackData structure.
@retval Others			Number of bytes written
*/
MAE_Ret SrvFstreamSyncWrite(hFstream pFstream,
                    const void *pBuffer,
                    u32 nSize);

/** SrvFstreamIsEndOfFile
@brief  The interface is use to gCheck if the stream is at the end of file.

@param[in]  hFstream                Fstream handler

@retval MAE_RET_EOF		    The stream reaches to EOF
@retval MAE_RET_NOT_EOF		Not end of file.
*/
MAE_Ret SrvFstreamIsEndOfFile(hFstream pFstream);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_FSTREAM_H__
