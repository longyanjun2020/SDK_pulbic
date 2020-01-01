/**
 *
 * @file    esl_efs_itf.h
 *
 * @brief   This module defines Enchaced Service Layer interface of File System service
 *
 * @author  Xavier Fan
 * @version $Id: esl_efs_itf.h 12017 2008-06-26 03:33:14Z jack.hsieh $
 *
 */
#ifndef __ESL_EFS_ITF_H__
#define __ESL_EFS_ITF_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_EFS_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif


#define ESL_EFS_FAT_SPEC_NAME_LEN     (255)  /**< Define the max length of file name without path in Unicode (without '\0')   */
#define ESL_EFS_FAT_SPEC_FULLPATH_LEN (261)  /**< Define the max length of file path with full path in Unicode (without '\0') */

#define ESL_EFS_FILE_ID_LEN           (8)    /**< Define the length of file id in bytes */




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the ESL external file system error code
 */
typedef enum
{
  FAT_NO_ERROR,                   /**< Function complete successfully                             */
  (-1),                 /**< Function fail by unknown cause                             */
  ESL_EFS_PARAM_ERROR,          /**< The input parameter is wrong                               */
  ESL_EFS_MEM_ALLOC_ERROR,      /**< Can not allocate available memory from OS                  */
  ESL_EFS_REJECT,               /**< Request reject because of other function's confliction     */
  ESL_EFS_ABORT,                /**< Request abort because of incorrect sequence                */ 
  ESL_EFS_TIMEOUT,              /**< Request is timeout caused by MMP does not response in time */
  ESL_EFS_NOT_DIR,              /**< Input path is not a folder                                 */
  ESL_EFS_NOT_FILE,             /**< Input path is not a file                                   */
  ESL_EFS_FILE_NOT_EXIST,       /**< Input path is not exist                                    */
  ESL_EFS_PATH_ERROR,           /**< Input path is not in correct format                        */
  ESL_EFS_PATH_LEN_ERROR,       /**< Input path length is not incorrect                         */
  FAT_ASYNC_COMPLETED,      /**< Async request is completed                                 */
} esl_EfsErrCode_e;


/**
 *  @brief The enumeration defines type of the EFS notification.
 */
typedef enum
{
	ESL_EFS_ENTRY_NUM_UPDATE,     /**< Notify MMI that the total number of entry in the folder has been update by MMP */
	ESL_EFS_NOTIFY_NUM            /**< Notify numbers                                                                 */
} esl_EfsNotifyType_e;


/**
 *  @brief The data structure defines file ID structure
 */
typedef struct
{
  u32   content[ESL_EFS_FILE_ID_LEN / sizeof(u32)]; /**< file id  */
} VFS_FileID_t;


/**
 *  @brief The data structure defines file date
 */
typedef struct
{
  u32   second    : 5;    /**< Unit is 2 seconds, range=0~29, ex: 2009/09/28 11:32:21, the field will be 10 */
  u32   minute    : 6;    /**< range=0~59, ex: 2009/09/28 11:32:21, the field will be 32                    */
  u32   hour      : 5;    /**< range=0~23, ex: 2009/09/28 11:32:21, the field will be 11                    */
  u32   day       : 5;    /**< range=1~31, ex: 2009/09/28 11:32:21, the field will be 28                    */
  u32   month     : 4;    /**< range=1~12, ex: 2009/09/28 11:32:21, the field will be 09                    */
  u32   year      : 7;    /**< start from 1980, ex: 2009/09/28 11:32:21, the field will be 29 (2009-1980)   */
} esl_EfsDate_t;


/**
 *  @brief The data structure defines file attribute
 */
typedef struct
{
  u8    isRdOnly  : 1;    /**< The bit will be set if the entry is Read-Only, bit mask = 0x01     */
  u8    isHidden  : 1;    /**< The bit will be set if the entry is Hidden, bit mask = 0x02        */
  u8    isSystem  : 1;    /**< The bit will be set if the entry is System File, bit mask = 0x04   */
  u8    reserve0  : 1;    /**< Reserved Bit                                                       */
  u8    isFolder  : 1;    /**< The bit will be set if the entry is a Folder, bit mask = 0x10      */
  u8    isArchive : 1;    /**< The bit will be set if the entry is an Archive, bit mask = 0x20    */
  u8    reserve1  : 1;    /**< Reserved Bit                                                       */
  u8    reserve2  : 1;    /**< Reserved Bit                                                       */
} esl_EfsAttr_t;


/**
 *  @brief The data structure for extension filter
 */
typedef struct
{
  u32   count;     /**< Number of extension should be compared                                      */
  u16 * pExtList;  /**< Extension list in Unicode, please separate with '|' in wide character, too  */
} esl_EfsExtFilter_t;


/**
 *  @brief The data structure for file size filter
 */
typedef struct
{
  u32   minSize;  /**< Define the min-size of filter  */
  u32   maxSize;  /**< Define the max-size of filter  */
} esl_EfsSizeFilter_t;


/**
 *  @brief The enum for attr filter
 */
typedef enum
{
  VFS_ATTR_FILTER_IGNORE, /**< Even what the value of the entry attribute, keep this entry    */
  VFS_ATTR_FILTER_KEEP,   /**< If the attribute is equal the condition, keep this entry       */
  VFS_ATTR_FILTER_OUT     /**< If the attribute is equal the condition, skip this entry       */
} esl_EfsAttrFilter_e;


/**
 *  @brief The data structure defines file attribute filter
 */
typedef struct
{
  esl_EfsAttrFilter_e   rdOnlySwitch;   /**< Used to switch if need to filter RD-Only attribute */
  esl_EfsAttrFilter_e   hiddenSwitch;   /**< Used to switch if need to filter Hidden attribute  */
  esl_EfsAttrFilter_e   systemSwitch;   /**< Used to switch if need to filter System attribute  */
  esl_EfsAttrFilter_e   folderSwitch;   /**< Used to switch if need to filter Folder attribute  */
  esl_EfsAttrFilter_e   archiveSwitch;  /**< Used to switch if need to filter Archive attribute */
} esl_EfsAttrFilter_t;


/**
 *  @brief The data structure for List-Filter
 */
typedef struct
{
  esl_EfsExtFilter_t    extFilter;  /**< Filter with extension name, if the count=0, this filter would be ignored                             */
  esl_EfsSizeFilter_t   sizeFilter; /**< Filter with file size, if min=0 & max=0xFFFFFFFF, this filter would be ignored                       */
  esl_EfsAttrFilter_t   attrFilter; /**< Filter with attribute, if all switches are VFS_ATTR_FILTER_IGNORE, this filter would be ignored  */
} esl_EfsListFilter_t;


/**
 *  @brief The data structure defines file info structure for ESL-EFS interfaces
 */
typedef struct
{
  #if 1
  u16               longName[ESL_EFS_FAT_SPEC_FULLPATH_LEN + 1];  /**< Filename in Unicode with terminal character                              */
  VFS_FileID_t   uniqueId;                                     /**< The entry ID generated by MMP                                            */
  u32               createdDate;                                  /**< Date-time to create the entry, the detail can be reference esl_EfsDate_t */
  u32               modifiedDate;                                 /**< Date-time to modify the entry, the detail can be reference esl_EfsDate_t */
  u32               size;                                         /**< Item size in bytes, if the entry is a folder, the value will be 0        */
  u8                attr;                                         /**< Entry attributes, the detail can be reference esl_EfsAttr_t              */
  u8                padding[3];                                   /**< Padding space for memory alignment                                       */
  u8                padding1[28];                                   /**< Padding space for memory alignment                                       */
  #else
  u16               longName[ESL_EFS_FAT_SPEC_FULLPATH_LEN + 1];  /**< Filename in Unicode with terminal character                              */
  VFS_FileID_t   uniqueId;                                     /**< The entry ID generated by MMP                                            */
  esl_EfsDate_t     createdDate;                                  /**< Date-time to create the entry                                            */
  esl_EfsDate_t     modifiedDate;                                 /**< Date-time to modify the entry                                            */
  u32               size;                                         /**< Item size in bytes, if the entry is a folder, the value will be 0        */
  esl_EfsAttr_t     attr;                                         /**< Entry attributes                                                         */
  u8                padding[3];                                   /**< Padding space for memory alignment                                       */
  u8                padding1[28];                                   /**< Padding space for memory alignment                                       */
  #endif
} VFS_PartialListFileInfo_t;


/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct
{
  esl_EfsNotifyType_e	  notifyType;   /**< Type of EFS notification                                                                   */
  union
  {
    struct
    {
      u32                 numEntry;   /**< MMP return the total number of entries in the folder, which will be update in the runtime  */
      esl_EfsErrCode_e    status;     /**< MMP return the status of this notification: ABORT, OK (continue), or COMPLETED             */
    } getNum;
  } notify;	
} VFS_NotifyInfo_t;


/**
 *  @brief Notification Call back function, MMI need to provide the function entity 
 *
 * @param senderID		  : Sender task id. 
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pCamGetInfo   : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_EfsNotifyCb)(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pEfsGetInfo);


/**
 *  @brief Callback informatoin structure supported for application layer (MMI)
 */
typedef struct {
	u16               senderID;	  /**< Sender ID                                                                            */
	u32               userValue;  /**< Reference value for indicating different sender in same task or check msg response.  */
	esl_EfsNotifyCb   pfnCb;      /**< Call back function that called by Media task after process finished.                 */
} esl_EfsNotifyCb_t;


/**
 *  @brief The sturcture defines the request to EMA to get file number in the folder with filter
 *         (for EMA internal using)
 */
typedef struct  
{
  struct
  {
    u16                 * pPath;          /**< Folder Path                                            */
    esl_EfsListFilter_t * pFilter;        /**< Filter                                                 */
    u32                   fileInfoNum;    /**< Indicate the first time buffer num to store file info  */
  } request;
  struct
  {
    VFS_PartialListFileInfo_t   * pFileInfoArray; /**< Indicate the buffer to store file info at first time   */
    u32                 * pFileInfoNum;   /**< Indicate the result of the file info got at first time */
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result                     */  
  } out;
} esl_EfsGetFileNumReq_t;


/**
 *  @brief The sturcture defines the request to EMA to register the notification
 *         (for EMA internal using)
 */
typedef struct 
{
	struct
	{
	  esl_EfsNotifyType_e   notifyType;     /**< Type of EFS notification                       */
		esl_EfsNotifyCb_t			notifyCb;       /**< MMI registered information for future using    */
	} request;

  struct
  {
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result             */  
  } out;
} esl_EfsRegNotify_t;


/**
 *  @brief The sturcture defines the request to EMA to abort get file number request
 *         (for EMA internal using)
 */
typedef struct 
{
  struct
  {
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result             */  
  } out;
} esl_EfsAbortGetFileNum_t;


/**
 *  @brief The sturcture defines the request to EMA to do partial list to get file info
 *         (for EMA internal using)
 */
typedef struct  
{
  struct
  {
    u16                 * pPath;          /**< Folder Path                                    */
    esl_EfsListFilter_t * pFilter;        /**< Filter                                         */
    u32                   offset;         /**< Indicate where start to list                   */
    u32                   fileInfoNum;    /**< Indicate the buffer num to store file info     */
  } request;
  struct
  {
    VFS_PartialListFileInfo_t   * pFileInfoArray; /**< Indicate the buffer to store file info         */
    u32                 * pFileInfoNum;   /**< Indicate the result of the file info got       */
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result             */  
  } out;
} esl_EfsPartialListWithInfo_t;


/**
 *  @brief The sturcture defines the request to EMA to do partial list to get file ID
 *         (for EMA internal using)
 */
typedef struct  
{
  struct
  {
    u16                 * pPath;          /**< Folder Path                                    */
    esl_EfsListFilter_t * pFilter;        /**< Filter                                         */
    u32                   offset;         /**< Indicate where start to list                   */
    u32                   fileIdNum;    /**< Indicate buffer num to store file info         */
  } request;
  struct
  {
    VFS_FileID_t     * pFileIdArray;   /**< Indicate the buffer to store file ID           */
    u32                 * pFileIdNum;     /**< Indicate the result of the file ID got         */
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result             */
  } out;
} esl_EfsPartialListWithId_t;


/**
 *  @brief The sturcture defines the request to EMA to convert ID to File Info
 *         (for EMA internal using)
 */
typedef struct  
{
  struct
  {
    u16                 * pPath;          /**< Folder Path                                    */
    VFS_FileID_t     * pFileIdArray;   /**< File ID Array                                  */
    u32                   numFileId;      /**< Indicate num of File ID                        */
  } request;
  struct
  {
    VFS_PartialListFileInfo_t   * pFileInfoArray; /**< Indicate the buffer to store file Info         */
    u32                 * pFileInfoNum;   /**< Indicate the result of the file Info got       */
		esl_EfsErrCode_e    * pStatus;        /**< point to the storage of the result             */
  } out;
} esl_EfsConvertIdToInfo_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/

/** 
 *  @brief This function is called to get the file number in the folder in asynchronous way 
 *    
 *  @param pPath                   : (I)The folder we want to list, need in Unicode format and with terminal 
 *                                   character
 *  @param pFilter                 : (I)Describe the filter condition of the result, the detail can be reference 
 *                                   esl_EfsListFilter_t structure.
 *  @param startFileNumber         : (I)The first result number, used to check buffer checking for MMP.
 *  @param pStartFileNumber        : (O)Used to store the first result of the file number.
 *  @param pStartFileInfoArray     : (O)Used to store the file information
 *                                   *Note*  The buffer address and size should be 32-byte alignment. 
 *                                           If not, API will reject the request with ESL_EFS_PARAM_ERROR.
 *  @param pEfsCb                  : Call back structure, include sender ID, userValue and call back function. 
 *                                   It uses to send response message that provide by application layer(MMI) 
 *                                   to inform application layer(MMI) the process in EMA is success or fail.
 *
 *  @return FAT_NO_ERROR             : Operation success
 *  @return (-1)           : Operation fail caused by unknown issue.
 *  @return ESL_EFS_PARAM_ERROR    : Operation parameter error, ex: buffer alignment is not aligned
 *  @return ESL_EFS_REJECT         : Operation has been rejected by EMA state conflict
 *  @return ESL_EFS_NOT_DIR        : Input path is not a directory
 *  @return ESL_EFS_PATH_LEN_ERROR : Input path length is not correct
 */
esl_EfsErrCode_e esl_EfsGetEntryNumReq(
                                    u16                 * pPath, 
                                    esl_EfsListFilter_t * pFilter, 
                                    u32                   startFileNumer,
                                    u32                 * pStartFileNumber, 
                                    VFS_PartialListFileInfo_t   * pStartFileInfoArray,
                                    esl_EfsNotifyCb_t   * pEfsCb);


/** 
 *  @brief This function is called to abort the previous esl_EfsGetEntryNumReq(). This function is needed to
 *         be called due to M3 only provide one session to process esl_EfsGetEntryNumReq() command. If previous 
 *         one is not aborted, the following esl_EfsGetEntryNumReq() will return ESL_EFS_REJECT error code.
 *   
 *  @param None
 *
 *  @return FAT_NO_ERROR             : Operation success
 *  @return (-1)           : Operation fail caused by unknown issue.
 *  @return ESL_EFS_PARAM_ERROR    : Operation parameter error, ex: buffer alignment is not aligned
 *  @return ESL_EFS_REJECT         : Operation has been rejected by EMA state conflict
 */
esl_EfsErrCode_e esl_EfsAbortGetEntryNumReq(void);


/** 
 *  @brief This function is called to query the information of a set entries from entry ID. 
 *         *Note* Due to ID cannot query the full path, you should prevent to input the entry IDs from different
 *         folders
 *   
 *  @param numIdArray              : (I)Indicate the ID array size, to prevent MMP destroyed memory
 *  @param pIdArrayBffer           : (I)Indicate where is the ID array, and MMP will try to find the information 
 *                                   of each ID in the array in order.
 *                                   *Note*  The buffer address and size should be 32-byte alignment. 
 *                                           If not, API will reject the request with ESL_EFS_PARAM_ERROR.
 *  @param pFileInfoArray          : (O)Used to store the file information.
 *                                   *Note*  The buffer address and size should be 32-byte alignment. 
 *                                           If not, API will reject the request with ESL_EFS_PARAM_ERROR.
 *
 *  @return FAT_NO_ERROR             : Operation success
 *  @return (-1)           : Operation fail caused by unknown issue.
 *  @return ESL_EFS_PARAM_ERROR    : Operation parameter error, ex: buffer alignment is not aligned
 *  @return ESL_EFS_REJECT         : Operation has been rejected by EMA state conflict
 */
esl_EfsErrCode_e esl_EfsGetFileInfoByFileId(
                                    u16                 * pPath, 
                                    u32                   numIdArray,
                                    VFS_FileID_t     * pIdArrayBuffer,
                                    VFS_PartialListFileInfo_t   * pFileInfoArray);


/** 
 *  @brief This function is called to partially list the file information with filter
 *   
 *  @param pPath                   : (I)The folder we want to list, need in Unicode format and with terminal 
 *                                   character
 *  @param pFilter                 : (I)Describe the filter condition of the result, the detail can be reference 
 *                                   esl_EfsListFilter_t structure.
 *  @param offset                  : (I)Indicate the start address after reference ID
 *                                   *Note* The reference ID is get from IndexArray Buffer, but the contain may be 
 *                                          not valid anymore. MMI should take care about any change in the same folder.
 *  @param numEntry                : (I)The number of entries this feature want to get.
 *  @param pResultFileNumber       : (O)Used to store the result of the file number got in this operation.
 *  @param pResultFileInfoArray    : (O)Used to store the file information got in this operation.
 *                                   *Note*  The buffer address and size should be 32-byte alignment. 
 *                                           If not, API will reject the request with ESL_EFS_PARAM_ERROR.
 *
 *  @return FAT_NO_ERROR             : Operation success
 *  @return (-1)           : Operation fail caused by unknown issue.
 *  @return ESL_EFS_PARAM_ERROR    : Operation parameter error, ex: buffer alignment is not aligned
 *  @return ESL_EFS_REJECT         : Operation has been rejected by EMA state conflict
 *  @return ESL_EFS_NOT_DIR        : Input path is not a directory
 *  @return ESL_EFS_PATH_LEN_ERROR : Input path length is not correct
 */
esl_EfsErrCode_e esl_EfsPartialListToGetFileInfo(
                                    u16                 * pPath, 
                                    esl_EfsListFilter_t * pilter, 
                                    u32                   offset,
                                    u32                   numEntry,
                                    u32                 * pResultFileNumber, 
                                    VFS_PartialListFileInfo_t   * pResultFileInfoArray);
                                    

/** 
 *  @brief This function is called to partially list the file ID with filter
 *   
 *  @param pPath                   : (I)The folder we want to list, need in Unicode format and with terminal 
 *                                   character
 *  @param pFilter                 : (I)Describe the filter condition of the result, the detail can be reference 
 *                                   esl_EfsListFilter_t structure.
 *  @param offset                  : (I)Indicate the start address after reference ID
 *                                   *Note* The reference ID is get from IndexArray Buffer, but the contain may be 
 *                                          not valid anymore. MMI should take care about any change in the same folder.
 *  @param numEntry                : (I)The number of entries this feature want to get.
 *  @param pResultFileNumber       : (O)Used to store the result of the file number got in this operation.
 *  @param pResultFileIdArray      : (O)Used to store the file information got in this operation.
 *                                   *Note*  The buffer address and size should be 32-byte alignment. 
 *                                           If not, API will reject the request with ESL_EFS_PARAM_ERROR.
 *  @param pEfsCb                  : Call back structure, include sender ID, userValue and call back function. 
 *                                   It uses to send response message that provide by application layer(MMI) 
 *                                   to inform application layer(MMI) the process in EMA is success or fail.
 *
 *  @return FAT_NO_ERROR             : Operation success
 *  @return (-1)           : Operation fail caused by unknown issue.
 *  @return ESL_EFS_PARAM_ERROR    : Operation parameter error, ex: buffer alignment is not aligned
 *  @return ESL_EFS_REJECT         : Operation has been rejected by EMA state conflict
 *  @return ESL_EFS_NOT_DIR        : Input path is not a directory
 *  @return ESL_EFS_PATH_LEN_ERROR : Input path length is not correct
 */
esl_EfsErrCode_e esl_EfsPartialListToGetFileId(
                                    u16                 * pPath, 
                                    esl_EfsListFilter_t * pFilter, 
                                    u32                   offset,
                                    u32                   numEntry,
                                    u32                 * pResultFileNumber, 
                                    VFS_FileID_t     * pResultFileIdArray);
                                    

#endif  /*  end of __ESL_EFS_ITF_H__  */



