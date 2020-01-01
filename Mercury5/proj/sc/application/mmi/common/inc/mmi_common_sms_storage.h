/**
 * @file    mmi_common_sms_storage.h
 *
 * @brief   This file defines the interface of sms file handling functions.
 * @version $Id: mmi_common_sms_storage.h 41287 2009-09-24 06:22:46Z joe.hsu $
 * @author	miya.chien
 *
 */
#ifndef __MMI_COMMON_SMS_STORAGE_H__
#define __MMI_COMMON_SMS_STORAGE_H__

#include "mmi_mae_filemgr.h"
#include "mmi_mae_common_def.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_sms.h"
#include "mmi_util_fs.h"

#define MAXSize MMI_RAI_SIZE_MAX
#define reservedIDSize 5

typedef struct
{
	const MAE_WChar *pFileName;
	u32 RId;

}Msg_FileNameTabel_t;

enum
{
    MSG_MASTER_E_NOT_TEMP=0x00,
    MSG_MASTER_E_TEMP_INBOX=0x01,
    MSG_MASTER_E_TEMP_OUTBOX=0x02,
    MSG_MASTER_E_TEMP_SENTBOX=0x04,
    MSG_MASTER_E_TEMP_DRAFTBOX=0x08,
    MSG_MASTER_E_TEMP_MSGID=0x10,
    MSG_MASTER_E_TEMP_NO_INIT=0x20,
	MSG_MASTER_E_TEMP_PMBOX=0x40,
	MSG_MASTER_E_TEMP_TNBOX=0x80
};
typedef u16 Msg_FileMapInfo_e;

typedef struct
{
    u32 FileID;
    u32 TempFileID;
    Msg_FileMapInfo_e MapInfoMask;
}Msg_TempFileID_MapInfo_t;

#define MsgFile_Prefix L"fs:/PHON/SMS/m"

/**----------------------------Message Storage--------------------------------**/
/**
  * \fn		IFStream* MsgFLEMGR_OpenFile(const MAE_WChar* pStrDir, const u8 *mode, IBase *pOwner);
  * \brief	1. Get the file stream pointer with the file name if it's NAND
  			2. Get the mapping RAI id with the file name if it's NOR RAI
  * \param	[in] Pointer to the IFileMgr interface
  * \param	[in] File path
  * \param	[in] The open mode of file
  * \param	[in] The owner instance
  * \return	Pointer to FStream object

  */
__SLDPM_FREE__ FileMgr_Stream_t* MsgFLEMGR_OpenFile(const MAE_WChar* pStrDir, const u8 *mode, IBase *pOwner);

/**
  * \fn		MAE_Ret MsgFLEMGR_Exist(const MAE_WChar* pStrDir);
  * \brief	Check the object exist or not with the file name
  * \param	[in] Pointer to the IFileMgr interface
  * \param	[in] File path
  * \return	MAE_Ret
  */
MAE_Ret MsgFLEMGR_Exist(const MAE_WChar* pStrDir);

/**
  * \fn		MAE_Ret MsgFLEMGR_Delete(const MAE_WChar* pStrDir);
  * \brief	Delete the object with the file name
  * \param	[in] Pointer to the IFileMgr interface
  * \param	[in] File path
  * \return	MAE_Ret
  */
MAE_Ret MsgFLEMGR_Delete(const MAE_WChar* pStrDir);

/**
  * \fn		MAE_Ret MsgFLEMGR_Rename(const MAE_WChar* pStrPathSrc, const MAE_WChar* pStrNameDest);
  * \brief	Rename the file name of the object
  * \param	[in] Pointer to the IFileMgr interface
  * \param	[in] Source file to be renamed
  * \param	[in] Destination file name "abc.123", cannot be a path.
  * \return	MAE_Ret
  */
MAE_Ret MsgFLEMGR_Rename(const MAE_WChar* pStrPathSrc, const MAE_WChar* pStrNameDest);

/**
  * \fn		MAE_Ret MsgFLEMGR_GetInfo(const MAE_WChar *pStrDir, void *pInfo);
  * \brief	Get the object information with the file name
  * \param	[in] Pointer to the IFileMgr interface
  * \param	[in] File path
  * \param	[out] Place holder to file information
                 1. Typecast to MAEFileInfo_s if it's NAND
				 2. Typecast to mmi_raiInfo_t if it's NOR RAI
  * \return	MAE_Ret
  */
MAE_Ret MsgFLEMGR_GetInfo(const MAE_WChar *pStrDir, VFS_PartialListFileInfo_t *pInfo);

/**
  * \fn		MAE_Ret MsgFLEMGR_Read(IFStream* pIFStream, void *bufferPtr, u32 wordCnt, u32 *byteRead);
  * \brief	Read the data
  * \param	[in] file stream pointer
				 1. Pointer to the pIAStream interface if  it's NAND
				 2. Typecast to u32 RAI id if it's NOR RAI
 * \param	[in] start offset
  * \param	[in] Pointer to the buffer into which the data is being read
  * \param	[in] Number of bytes to read
  * \param	[out]Pointer to an integer returning the cumber of bytes read if data is available for reading
  * \return	MAE_Ret
  */
MAE_Ret MsgFLEMGR_Read(FileMgr_Stream_t* pIFStream,void *bufferPtr, u16 nStart, u32 wordCnt, u32 *byteRead);

/**
  * \fn		s32 MsgFLEMGR_Write(IFStream *pIFStream, const void *pBuffer, u32 count, MAE_PFNCALLBACK callBackFuncPtr, MAEFileCallback_s* pCallBackData);
  * \brief	Write the data
  * \param	[in] RAI id
  * \param	[in] Data buffer
  * \param	[in] number of bytes to be stored to the file stream
  * \param	[in] Callback function which will be executed while the operation is done. User can free pBuffer in this callback. If callBackFuncPtr is NULL,this API is blocking.
  * \param	[in] Place holder to MAEFSWriteCallBack_s structure, including the pointer of the caller instance, userdata and an U32 space to write return code
				 during callback. FStream objects won't free this memory. It is recommended to free this memory inside callback function.
  * \return	s32
  */
s32 MsgFLEMGR_Write(FileMgr_Stream_t *pIFStream, const void *pBuffer, u32 count, PfnMAE_Callback callBackFuncPtr, FileMgrFileCallback_t* pCallBackData);

MAE_Ret MsgFLEMGR_Release_IFStream(FileMgr_Stream_t* pIFStream,IBase *pOwner);
/**
  * \fn		MAE_Ret MsgFLEMGR_CheckFreeSpace(const MAE_WChar *pStrDir, u32 *totalSize, u32 *remainSize);
  * \brief	Check Free Space
  * \param	[in] Destination dir
  * \param	[out] total memory size
  * \param	[out] free memory size
  * \return	MAE_Ret   MAE_RET_SUCCESS
  *					  MAE_RET_FAIL
  */
MAE_Ret MsgFLEMGR_CheckFreeSpace(const MAE_WChar *pStrDir, u32 *totalSize, u32 *remainSize);

MAE_Ret MsgFLEMGR_DeleteByMsgIdArray(u32 *paMsgId, u32 nNum );

#endif /* __MMI_COMMON_SMS_STORAGE_H__*/

