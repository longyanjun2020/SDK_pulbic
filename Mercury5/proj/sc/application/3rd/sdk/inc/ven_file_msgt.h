#ifndef __VEN_FILE_MSGT_H__
#define __VEN_FILE_MSGT_H__

#include "ven_file.h"
#include "ven_comdef_priv.h"

typedef struct
{
    u32 progress;
    u32 readLength;
    u8  *pBuffer;
} iVen_file_read_info_t;

typedef struct
{
    u32 progress;
    u32 writeLength;
    u8  *pBuffer;
} iVen_file_write_info_t;


/****************************************************************************/
/*  Message :       I_VEN_FILE_BROWSE_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to launch a   */
/*              file browser for user to select file(s)                     */
/*                                                                          */
/*  Structure : iVen_file_browse_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* ptTitle;
    u8 titleLen;
    ven_file_browser_type_t type;
    u8 maxMarkSize;
    u16 **pptOutData;
    u16 *ptOutDataLen;
    u8 *ptOutMarkedSize;
} iVen_file_browse_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* ptTitle;
    u8 titleLen;
    ven_file_browser_type_t type;
    u8 maxMarkSize;
    u16 **pptOutData;
    u16 *ptOutDataLen;
    u8 *ptOutMarkedSize;
    ven_file_ExtensionFilter_t tExtList;
    u16 *pwszBrowsingFolder;
    u16 nFolderStrLen;
}iVen_file_browse_ex_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* ptTitle;
    u8 titleLen;
    u16 **pptOutData;
    u16 *ptOutDataLen;
} iVen_file_select_folder_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_file_avail_path_t type;
    ven_file_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u16 **ppOutPath;    //output: only useful if the ReqBase.bSync is TRUE
    u16 *pOutPathLen;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_file_get_avail_path_req_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_BROWSE_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              user select file(s)                                         */
/*                                                                          */
/*  Structure : iVen_file_browse_rsp_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u16* ptData;
    u16  dataLen;
    u8   nMarkedSize;
} iVen_file_browse_rsp_t;

typedef iVen_file_browse_rsp_t  iVen_file_browse_ex_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u16* ptData;
    u16  dataLen;
} iVen_file_select_folder_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_SYNC_FOLDER_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to sync a     */
/*              given folder path to MMI's DB.                              */
/*                                                                          */
/*  Structure : iVen_file_browse_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* pFolderPath;
} iVen_file_sync_folder_req_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_SYNC_FOLDER_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_time_set_time_rsp_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    bool bRet;
} iVen_file_sync_folder_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_SYNC_CONTENT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to sync a     */
/*              given content path to MMI's DB.                             */
/*                                                                          */
/*  Structure : iVen_file_browse_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16 *pContentUrl; // Content URL with NULL terminate
    u16 *pNewContentUrl; // New content URL
    u8 op;  // Add/Del/Update Content
} iVen_file_sync_content_req_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_FILE_ACCESS_IND                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure is used to send File Access indication to     */
/*              MMI task                                                    */
/*                                                                          */
/*  Structure : iVen_file_file_access_ind_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

// --> This enum will be defined in mae_filemgr.h
typedef enum
{
    E_FMG_OPEN_WITH_READ, // pPath is meaningful
    E_FMG_OPEN_WITH_WRITE, // pPath is meaningful
    E_FMG_LIST,  // pPath is meaningful
    E_FMG_ADD,  // pPath is meaningful
    E_FMG_DELETE,   // pPath is meaningful
    E_FMG_COPY,  // Will not be used by ven_file now
    E_FMG_MOVE,  // Will not be used by ven_file now
    E_FMG_RENAME,   // pPath and pNewPath is meaningful
    E_FMG_CLOSE  // pHandle is meaningful

} FolderContentOperation_e;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    bool bAccess_SD;    //File Access on SD Card

    FolderContentOperation_e eOperation;
    u16* pPath;
    u16* pNewPath;
    void* pHandle;
} iVen_file_file_access_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_ASYNC_READ_RSP                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_file_async_read_rsp_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_file_async_operation_t op;
    s32 ret;
    union
    {
        iVen_file_read_info_t readInfo;
        iVen_file_write_info_t writeInfo;
    } info;
} iVen_file_async_operation_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_FILE_ASYNC_WRITE_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_file_async_write_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 ret;
    u32 progress; ///< write progress, 0~100
} iVen_file_async_write_rsp_t;

#endif //__VEN_FILE_MSGT_H__

