/**
 * @file    mmi_download_def.h
 * @brief   The definitions of download interface
  *
  */
#ifndef __MMI_DOWNLOAD_DEF_H__
#define __MMI_DOWNLOAD_DEF_H__
/*=============================================================*/
// Include Files
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum mmi_DownloadStatus_e_
{
    MMI_DOWNLOAD_STATUS__START, //Download module receive START request
    MMI_DOWNLOAD_STATUS__START_DOWNLOAD, //Connect to server success and start to download
    MMI_DOWNLOAD_STATUS__STOPPED,
    MMI_DOWNLOAD_STATUS__COMPLETE,
    MMI_DOWNLOAD_STATUS__ERROR,    
    MMI_DOWNLOAD_STATUS__INCOMING_DATA,
} mmi_DownloadStatus_e;

typedef struct mmi_DownloadData_t_
{
    void *pData;
    u32 nDataSize;
    u32 nDataPos;
} mmi_DownloadData_t;

typedef struct mmi_DownloadStatusInfo_t_
{
    mmi_DownloadStatus_e eStatus;
    union
    {
        u32 nFileSize; // Used with MMI_DOWNLOAD_STATUS__START_DOWNLOAD
        mmi_DownloadData_t tDownloadData; // Used with MMI_DOWNLOAD_STATUS__INCOMING_DATA
    } uInfo;
} mmi_DownloadStatusInfo_t;

typedef void *DownloadHdl_t;

typedef void (*DLItf_OnStatusChangedCb)(DownloadHdl_t pDLHdl, u32 nCusData, mmi_DownloadStatusInfo_t *pStatusInfo);

/**
DLItf_InitDownload
@brief  Init download module

@param[out]     ppDLHdl			Download module handle
@param[in]      nInitData       Data for init download module

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_InitDownload)(DownloadHdl_t *ppDLHdl, u32 nInitData);

/**
DLItf_UninitDownload
@brief  Uninit download module

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_UninitDownload)(DownloadHdl_t pDLHdl);

/**
DLItf_SetDownloadUrl
@brief  Set the URL of download file

@param[in]     pDLHdl			Download module handle
@param[in]     pDownloadUrl		File URL

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetDownloadUrl)(DownloadHdl_t pDLHdl, MAE_WChar *pDownloadUrl);

/**
DLItf_SetBufferSize
@brief  Set maximum buffer size, if download module allocate a buffer for storing data, 
        the buffer size must not exceed this limit

@param[in]     pDLHdl			Download module handle
@param[in]     nSize		    Maximim buffer size in bytes

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetBufferSize)(DownloadHdl_t pDLHdl, u32 nSize);

/**
DLItf_SetNotifyThreshold
@brief  Set the threshold of notifying incoming data, the size of notified data must exceed this
        lower bound (except the last incoming data)

@param[in]     pDLHdl			Download module handle
@param[in]     nThreshold		Notify threshold in bytes

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetNotifyThreshold)(DownloadHdl_t pDLHdl, u32 nThreshold);

/**
DLItf_SetNotifyCallback
@brief  Set the callback for listening the status of download module

@param[in]     pDLHdl			Download module handle
@param[in]     pfnStatusCb		Notify callback
@param[in]     nCusData         User data, download module will return it while invoking pfnStatusCb

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetNotifyCallback)(DownloadHdl_t pDLHdl, DLItf_OnStatusChangedCb pfnStatusCb, u32 nCusData);

/**
DLItf_SetDownloadPosition
@brief  Set the beginning position of download, the position of incoming data will based on it

@param[in]     pDLHdl			Download module handle
@param[in]     nPosition		Download position in bytes

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetDownloadPosition)(DownloadHdl_t pDLHdl, u32 nPosition);

/**
DLItf_StartDownload
@brief  Start download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_StartDownload)(DownloadHdl_t pDLHdl);

/**
DLItf_StopDownload
@brief  Stop download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_StopDownload)(DownloadHdl_t pDLHdl);

/**
DLItf_SuspendDownload
@brief  Suspend download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SuspendDownload)(DownloadHdl_t pDLHdl);

/**
DLItf_ResumeDownload
@brief  Resume download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_ResumeDownload)(DownloadHdl_t pDLHdl);

/**
DLItf_SetDownloadTimestamp
@brief  Set the beginning timestamp of download, the timestamp of incoming data will based on it

@param[in]     pDLHdl			Download module handle
@param[in]     nPosition		Download timestamp in msec

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef MAE_Ret (*DLItf_SetDownloadTimestamp)(DownloadHdl_t pDLHdl, u32 nTimeStamp);

typedef struct mmi_DownloadInterface_t_
{
    DLItf_InitDownload pfnInit;
    DLItf_UninitDownload pfnUninit;
    DLItf_SetDownloadUrl pfnSetUrl;
    DLItf_SetBufferSize pfnSetBufferSize;
    DLItf_SetNotifyThreshold pfnSetNotifyThreshold;
    DLItf_SetNotifyCallback pfnSetNotifyCb;
    DLItf_SetDownloadPosition pfnSetPosition;
    DLItf_StartDownload pfnStart;
    DLItf_StopDownload pfnStop;
    DLItf_SuspendDownload pfnSuspend;
    DLItf_ResumeDownload pfnResume;
    DLItf_SetDownloadTimestamp pfnSetTimestamp;
} mmi_DownloadInterface_t;

#endif /* __MMI_DOWNLOAD_DEF_H__ */
