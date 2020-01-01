/**
 *
 * @file    ema_efs_msg.h
 *
 * @brief   This module defines the EMA file system message struct type for file system interface using.
 *
 * @author  Xavier Fan
 * @version $Id: ema_efs_msg.h 11013 2008-05-27 05:32:20Z xavier.fan $
 *
 */
#ifndef __EMA_EFS_MSG_H__
#define __EMA_EFS_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define DefExtern
#else
#define DefExtern extern
#endif




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


typedef struct
{
  ema_TransType_t   TransType;
  isl_EfsCb_t     * pEfsDoneCB;
  isl_EfsDrive_e    storage;

  union
  {
    isl_EfsList_t             efsListCmd;
    isl_EfsRename_t           efsRenameCmd;
    isl_EfsOpen_t             efsOpenCmd;
    isl_EfsClose_t            efsCloseCmd;
    isl_EfsRemoveFile_t       efsRemoveFileCmd;
    isl_EfsRemoveDir_t        efsRemoveDirCmd;
    isl_EfsMakeDir_t          efsMakeDirCmd;
    isl_EfsFormat_t           efsFormatCmd;
    isl_EfsRead_t             efsReadCmd;
    isl_EfsWrite_t            efsWriteCmd;
    isl_EfsSeek_t             efsSeekCmd;
    isl_EfsTell_t             efsTellCmd;
    isl_EfsGetFileSize_t      efsGetFileSizeCmd;
    isl_EfsGetFileDate_t      efsGetFileDateCmd;
    isl_EfsGetVolumeSpace_t   efsGetVolumeSpaceCmd;
    isl_EfsCopyReq_t          efsCopyReqCmd;
    isl_EfsAbortCopy_t        efsAbortCopyCmd;
    isl_EfsRegNotify_t        efsRegNotifyCmd;
    isl_EfsMemoryCardNotify_t efsMemoryCardNotifyCmd;
    isl_EfsAttr_t             efsAttrCmd;
    isl_EfsGetRenameLen_t     efsGetRenameLenCmd;
    isl_EfsTruncFile_t        efsTruncFileCmd;
    isl_EfsTruncOpenedFile_t  efsTruncOpenedFileCmd;
    isl_EfsGetDirSize_t       efsGetDirSizeCmd;
    isl_EfsGetFileInfo_t      efsGetFileInfoCmd;
    isl_EfsGetOpenFileInfo_t  efsGetOpenFileInfoCmd;
    isl_EfsSdCardChange_t     efsSdCardChangeCmd;
    isl_EfsGetDirChecksum_t   efsGetDirChecksumCmd;
    isl_EfsGetChksum_t        efsGetChksumCmd;
    isl_EfsAbortGetChksum_t   efsAbortGetChksumCmd;
    isl_EfsQueryMountResult_t efsQueryMountResultCmd;
    isl_EfsFlush_t            efsFlushCmd;

    /* Partial List */
    isl_EfsGetFileNumReq_t    efsGetFileNumCmd;
    isl_EfsAbortGetFileNum_t  efsAbortGetFileNumCmd;
    isl_EfsPartialList_t      efsPartialListCmd;
    isl_EfsConvertIdToInfo_t  efsConvertIdToInfoCmd;

    isl_EfsAsyncDelete_t      efsAsyncDeleteCmd;
    isl_EfsAbortAsyncDelete_t efsAbortAsyncDeleteCmd;
    isl_EfsChkdsk_t           efsChkdskCmd;
    isl_EfsAbortChkdsk_t      efsAbortChkdskCmd;

    isl_EfsGetSerial_t        efsGetSerialCmd;
  } cmdType;
} ema_EfsCmd_t;


typedef struct
{
  u16               prim;
  u16               sender;
  ema_TransType_t   TransType;
  ema_ErrCode_e     errorStatus;
} ema_EfsRsp_t;


typedef struct
{
  u32   bufferLen;
  u8  * pBuffer;
} ema_EfsDoneRsp_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_EFS_MSG_H__ */

