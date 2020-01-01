/**
 * @file ven_codec.h
 *
 * This file defines the MMI image and media related request vendor API and
 * MMI response API
 *
 * @version $Id: ven_codec.h 45468 2009-11-13 05:13:00Z Mobile_CM $
 *
 */
#ifndef __VEN_CODEC_H_
#define __VEN_CODEC_H_


#include "ven_sdk.h"
#include "ven_graphics.h"


#define VEN_CODEC_NEXT_FRAME     -1
#define VEN_CODEC_CURRENT_FRAME  -2

#define KMV_MOVIE_IMAGE_SIZE (16*1024)
#define KMV_MOVIE_NAME_LENGTH (120)
#define KMV_MOVIE_STARRING_LENGTH (200)
#define KMV_MOVIE_SYNOPSIS_LENGTH (800)

typedef enum ven_codec_KmvCategoryType_e_
{
    KmvCategoryType_Action = 0,
    KmvCategoryType_Adventure,
    KmvCategoryType_Animation,
    KmvCategoryType_Comedy,
    KmvCategoryType_Documentary,
    KmvCategoryType_Drama,
    KmvCategoryType_FamilyKids,
    KmvCategoryType_Fantasy,
    KmvCategoryType_Horror,
    KmvCategoryType_Music,
    KmvCategoryType_Mystery,
    KmvCategoryType_PerformingArts,
    KmvCategoryType_Romance,
    KmvCategoryType_SciFi,
    KmvCategoryType_Sports,
    KmvCategoryType_Suspense,
    KmvCategoryType_War,
    KmvCategoryType_Western,
    KmvCategoryType_Others,
    KmvCategoryType_NumOfCategory,
    KmvCategoryType_Invalid = 0xFFFF
} ven_codec_KmvCategoryType_e;

typedef struct                              /// four bytes alignment
{
    u8 strMovieName[KMV_MOVIE_NAME_LENGTH];	/// utf8 encoding
    u16 nMovieTime;
    u16 nMovieYear;
    u8 strMovieStarring[KMV_MOVIE_STARRING_LENGTH];
    u8 strMovieSynopsis[KMV_MOVIE_SYNOPSIS_LENGTH];
    ven_codec_KmvCategoryType_e eCategory;
    u32 nImageSize;                         /// in bytes
    u8 aryImageData[KMV_MOVIE_IMAGE_SIZE];
} ven_codec_kmvExtInfo_t;

enum
{
    VEN_CODEC_SUCCESS = 0,
    VEN_CODEC_SUCCESS_WAITING,
    VEN_CODEC_SUCCESS_MORE_FRAMES,
    VEN_CODEC_PLAY_FINISHED,
    VEN_CODEC_RECORD_FINISHED,
    VEN_CODEC_STREAMING_ADD_BUFFER_DONE,  ///< Streaming data is duplicated into queue. Vendor could free its own stream data
    VEN_CODEC_STREAMING_BUFFER_UNDER_RUN, ///< The streaming buffer is almost empty. Vendor needs to send more streaming data immediately
    VEN_CODEC_STREAMING_BUFFER_FULL,      ///< The streaming buffer is full. Vendor needs to send streaming data latter
     VEN_CODEC_NOT_SUPPORTED = (s32) -17,
    VEN_CODEC_REC_RES_SUSPEND,
    VEN_CODEC_DRM_NO_RIGHTS,    
    VEN_CODEC_RE_ENTRY_ABORT,
    VEN_CODEC_BAD_PARAMETERS,
    VEN_CODEC_WRONG_HANDLE,
    VEN_CODEC_NOT_ENOUGH_MEMORY,
    VEN_CODEC_TOO_MUCH_EXECUTING_INSTANCE,
    VEN_CODEC_DEC_ERR,
    VEN_CODEC_FORMAT_UNSUPPORT,
    VEN_CODEC_SEND_MSG_FAILED,
    VEN_CODEC_NOT_PLAYING,
	VEN_CODEC_NOT_PAUSE,
    VEN_CODEC_ERROR,
    VEN_CODEC_DENY,
    VEN_CODEC_PLAY_SUSPEND,
    VEN_CODEC_SPACE_FULL
};

typedef s32 ven_codec_ret_t;

///////////////////////////////////////////////////////////////////////////////////////////////
//Image
enum
{
    VEN_IMAGE_FORMAT_ERR = 0,
    VEN_IMAGE_FORMAT_BMP,
    VEN_IMAGE_FORMAT_PNG,
    VEN_IMAGE_FORMAT_GIF,
    VEN_IMAGE_FORMAT_JPG,
    VEN_IMAGE_FORMAT_GIFA,
    VEN_IMAGE_FORMAT_MMP,
    VEN_IMAGE_FORMAT_WAVBMP,
    VEN_IMAGE_FORMAT_WAPBMP,
    VEN_IMAGE_FORMAT_TOTAL
};

typedef u8 ven_codec_imgFormat_t;

enum
{
    VEN_ROTATION_ANGLE_0 = 0,   //no rotation (captured image stored "as is")
    VEN_ROTATION_ANGLE_90,      //input image is rotated by +90?while stored in RAM
    VEN_ROTATION_ANGLE_270,     //input image is rotated by -90?(= +270? while stored in RAM
    VEN_ROTATION_ANGLE_180      // input image is rotated by +180?while stored in RAM
};

typedef u8 ven_codec_rotAngle_t;

typedef struct
{
    ven_codec_imgFormat_t   format;     // file format
    u16                     width_p;    // image width
    u16                     height_p;   // image height
    u32                     TotalFrames;
    u32                     size_p;     // bytes of entire file.
    bool                    bIsFile;

} ven_codec_imgInfo_t;

typedef struct
{
    u32         caps;
    u16         width;
    u16         height;
    u32         bpp;
    u32         stride;
    u32         size;
    u32         format;
    u32         addr;

} ven_codec_imgData_t;

typedef struct
{
    ven_codec_rotAngle_t  angle;    ///< Decode angle
    ven_GraphicsRect_t    region;   ///< partial decode parameters, for visible region of decode width and height
} ven_codec_decode_param_t;


enum {
  VEN_CODEC_ENC_QUALITY_LOW,     /* Low quality */
  VEN_CODEC_ENC_QUALITY_NORMAL,  /* Nomal quality */
  VEN_CODEC_ENC_QUALITY_HIGH     /* High quality */
};
typedef u16 ven_codec_EncQuality_e;

enum {
  VEN_CODEC_ENC_COLOR_RGB_565,              /**< RGB 565 format */
  VEN_CODEC_ENC_COLOR_YUV_420,              /**< YUV 420 format */
  VEN_CODEC_ENC_COLOR_UNKNOW_FORMAT         /**< Unknown pixel format */
};

typedef u16 ven_codec_EncColorFormat_e;

typedef struct {
  u16                         posX;           /**< Image x-axis coordination*/
  u16                         posY;           /**< Image y-axis coordination*/
  u16                         width;          /**< Image width*/
  u16                         height;         /**< Image height*/
  u32                         stride;         /**< Image stride (= pitch)*/
  u32                         size;           /**< Image data size (bytes)*/
  u32                         addr;           /**< data address*/
  ven_codec_EncColorFormat_e  format;         /**< Image format*/
}ven_codec_EncSurface_t;

typedef struct  {
 u8   *pBuffer;                /**< Gss decode buffer point*/
 u32   bufferLen;              /**< Gss decode buffer length*/
} ven_codec_encOutMemInfo_t;

typedef struct  {
 u16   *pWStrFileName;                /**< Gss decode buffer point*/
} ven_codec_encOutFileInfo_t;


typedef struct {
  ven_codec_EncQuality_e             encQuality;        /**< JPEG quality: Low, Normal and High */
  ven_codec_EncSurface_t             inputData;         /**< Encoded image data */
  union
  {
    ven_codec_encOutMemInfo_t         outMemInfo;
    ven_codec_encOutFileInfo_t        outFileInfo;
  }outInfo;  
} ven_codec_jpg_enc_info_t;

enum
{
    VEN_CODEC_ENC_JPG_TO_MEM = 0,
    VEN_CODEC_ENC_JPG_TO_FILE,
};
typedef struct {
    u32 **ppOutMemAddr;
    u32 *pOutMemSize;
}ven_codec_jpg_enc_mem_result_t;

typedef u16 ven_codec_enc_type;
typedef struct {
    ven_codec_enc_type u16EncType;
    union{
        ven_codec_jpg_enc_info_t   jpg_enc;
    }encoder;
    
    union{
    ven_codec_jpg_enc_mem_result_t jpg_enc_mem_result;   
    }encoder_result;
} ven_codec_enc_param_t;


///////////////////////////////////////////////////////////////////////////////////////////////
//Media

///////////////////////////////////////////////////////////////////////////////////////////////
//KMV download interface

typedef enum ven_codec_downloadStatus_e_
{
    VEN_CODEC_DOWNLOAD_STATUS_START,          /// Download module receive START request
    VEN_CODEC_DOWNLOAD_STATUS_START_DOWNLOAD, /// Connect to server success and start to download
    VEN_CODEC_DOWNLOAD_STATUS_STOPPED,
    VEN_CODEC_DOWNLOAD_STATUS_COMPLETE,
    VEN_CODEC_DOWNLOAD_STATUS_ERROR,
    VEN_CODEC_DOWNLOAD_STATUS_INCOMING_DATA,
} ven_codec_downloadStatus_e;

typedef struct ven_codec_downloadData_t_
{
    void *pData;
    u32 nDataSize;
    u32 nDataPos;
} ven_codec_downloadData_t;

typedef struct ven_codec_downloadStatusInfo_t_
{
    ven_codec_downloadStatus_e eStatus;
    union
    {
        u32 nFileSize;                          /// Used when eStatus == VEN_CODEC_DOWNLOAD_STATUS_START_DOWNLOAD
        ven_codec_downloadData_t tdownloadData; /// Used when eStatus == VEN_CODEC_DOWNLOAD_STATUS_INCOMING_DATA
    } uInfo;
} ven_codec_downloadStatusInfo_t;

typedef void *ven_codec_downloadHdl_t;

typedef void (*ven_codec_DLItf_OnStatusChangedCb)(ven_codec_downloadHdl_t pDLHdl, u32 nCusData, ven_codec_downloadStatusInfo_t *pStatusInfo);

/**
ven_codec_DLItf_InitDownload
@brief  Init download module

@param[out]     ppDLHdl			Download module handle
@param[in]      nInitData       Data for init download module

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_InitDownload)(ven_codec_downloadHdl_t *ppDLHdl, u32 nInitData);

/**
ven_codec_DLItf_UninitDownload
@brief  Uninit download module

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_UninitDownload)(ven_codec_downloadHdl_t pDLHdl);

/**
ven_codec_DLItf_SetDownloadUrl
@brief  Set the URL of download file

@param[in]     pDLHdl			Download module handle
@param[in]     pDownloadUrl		File URL

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SetDownloadUrl)(ven_codec_downloadHdl_t pDLHdl, u16 *pDownloadUrl);

/**
ven_codec_DLItf_SetBufferSize
@brief  Set maximum buffer size, if download module allocate a buffer for storing data,
        the buffer size must not exceed this limit

@param[in]     pDLHdl			Download module handle
@param[in]     nSize		    Maximim buffer size

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SetBufferSize)(ven_codec_downloadHdl_t pDLHdl, u32 nSize);

/**
ven_codec_DLItf_SetNotifyThreshold
@brief  Set the threshold of notifying incoming data, the size of notified data must exceed this
        lower bound (except the last incoming data)

@param[in]     pDLHdl			Download module handle
@param[in]     nThreshold		Notify threshold

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SetNotifyThreshold)(ven_codec_downloadHdl_t pDLHdl, u32 nThreshold);

/**
ven_codec_DLItf_SetNotifyCallback
@brief  Set the callback for listening the status of download module

@param[in]     pDLHdl			Download module handle
@param[in]     pfnStatusCb		Notify callback
@param[in]     nCusData         User data, download module will return it while invoking pfnStatusCb

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SetNotifyCallback)(ven_codec_downloadHdl_t pDLHdl, ven_codec_DLItf_OnStatusChangedCb pfnStatusCb, u32 nCusData);

/**
ven_codec_DLItf_SetDownloadPosition
@brief  Set the beginning position of download, the position of incoming data will based on it

@param[in]     pDLHdl			Download module handle
@param[in]     nPosition		Download position

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SetDownloadPosition)(ven_codec_downloadHdl_t pDLHdl, u32 nPosition);

/**
ven_codec_DLItf_StartDownload
@brief  Start download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_StartDownload)(ven_codec_downloadHdl_t pDLHdl);

/**
ven_codec_DLItf_StopDownload
@brief  Stop download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_StopDownload)(ven_codec_downloadHdl_t pDLHdl);

/**
ven_codec_DLItf_SuspendDownload
@brief  Suspend download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_SuspendDownload)(ven_codec_downloadHdl_t pDLHdl);

/**
ven_codec_DLItf_ResumeDownload
@brief  Resume download

@param[in]     pDLHdl			Download module handle

@return MAE_RET_SUCCESS         If successful
@return MAE_RET_FAILED          If failed
@return MAE_RET_BAD_PARAM       Incorrect parameter
 */
typedef ven_codec_ret_t (*ven_codec_DLItf_ResumeDownload)(ven_codec_downloadHdl_t pDLHdl);

enum
{
    //cmd: MDL streaming control -> download module
    VEN_CODEC_AVP_STREAMING_CMD_NONE = 0x1000,                                                    //0x1000
    VEN_CODEC_AVP_STREAMING_CMD_OPEN,    //open data link                                         //0x1001
    VEN_CODEC_AVP_STREAMING_CMD_CLOSE,   //close data link                                        //0x1002
    VEN_CODEC_AVP_STREAMING_CMD_INIT,    //init download module handle                            //0x1003
    VEN_CODEC_AVP_STREAMING_CMD_UNINIT,  //uninit download module handle                          //0x1004
    VEN_CODEC_AVP_STREAMING_CMD_PLAY,    //play one url                                           //0x1005
    VEN_CODEC_AVP_STREAMING_CMD_STOP,    //stop play one url                                      //0x1006
    VEN_CODEC_AVP_STREAMING_CMD_PAUSE,                                                            //0x1007
    VEN_CODEC_AVP_STREAMING_CMD_RESUME,                                                           //0x1008
    VEN_CODEC_AVP_STREAMING_CMD_SEEK,                                                             //0x1009
    VEN_CODEC_AVP_STREAMING_CMD_DATA_CONSUMED,                                                    //0x100a
    VEN_CODEC_AVP_STREAMING_CMD_GET_DATA,                                                         //0x100b
    VEN_CODEC_AVP_STREAMING_CMD_SEND_RTCP,                                                        //0x100c

    //internal DM cmd: MDL streaming control -> MDL streaming control
    VEN_CODEC_AVP_STREAMING_INT_CMD_PLAY = 0X2000,                                                //0x2000
    VEN_CODEC_AVP_STREAMING_INT_CMD_PAUSE,                                                        //0x2001
    VEN_CODEC_AVP_STREAMING_INT_CMD_RESUME,                                                       //0x2002
    VEN_CODEC_AVP_STREAMING_INT_CMD_UNINIT,                                                       //0x2003
    VEN_CODEC_AVP_STREAMING_INT_CMD_UPDATE_DWN_POS,                                               //0x2004

    //cmd: avp_handle-> MDL streaming control
    VEN_CODEC_AVP_STREAMING_AVP_CMD_PLAY = 0x3000,                                                //0x3000
    VEN_CODEC_AVP_STREAMING_AVP_CMD_PAUSE,                                                        //0x3001
    VEN_CODEC_AVP_STREAMING_AVP_CMD_RESUME,                                                       //0x3002
    VEN_CODEC_AVP_STREAMING_AVP_CMD_SEEK,                                                         //0x3003
    VEN_CODEC_AVP_STREAMING_AVP_CMD_STOP,                                                         //0x3004

    //response: download module -> MDL streaming control
    VEN_CODEC_AVP_STREAMING_RSP_OPEN = 0x4000,                                                    //0x4000
    VEN_CODEC_AVP_STREAMING_RSP_CLOSE,                                                            //0x4001
    VEN_CODEC_AVP_STREAMING_RSP_INIT,                                                             //0x4002
    VEN_CODEC_AVP_STREAMING_RSP_UNINIT,                                                           //0x4003
    VEN_CODEC_AVP_STREAMING_RSP_PLAY,                                                             //0x4004
    VEN_CODEC_AVP_STREAMING_RSP_STOP,                                                             //0x4005
    VEN_CODEC_AVP_STREAMING_RSP_PAUSE,                                                            //0x4006
    VEN_CODEC_AVP_STREAMING_RSP_RESUME,                                                           //0x4007
    VEN_CODEC_AVP_STREAMING_RSP_SEEK,                                                             //0x4008
    VEN_CODEC_AVP_STREAMING_RSP_GET_DATA,                                                         //0x4009

    //event: download module -> MDL streaming control
    //       MDL streaming control -> avp_handle
    //       MDL streaming control -> MDL streaming control
    VEN_CODEC_AVP_STREAMING_EVENT_OPEN_FAIL = 0x5000,                                             //0x5000
    VEN_CODEC_AVP_STREAMING_EVENT_OPEN_COMPLETE,                                                  //0x5001
    VEN_CODEC_AVP_STREAMING_EVENT_CLOSE_FAIL,                                                     //0x5002
    VEN_CODEC_AVP_STREAMING_EVENT_CLOSE_COMPLETE,                                                 //0x5003
    VEN_CODEC_AVP_STREAMING_EVENT_INIT_FAIL,                                                      //0x5004
    VEN_CODEC_AVP_STREAMING_EVENT_INIT_COMPLETE,                                                  //0x5005
    VEN_CODEC_AVP_STREAMING_EVENT_UNINIT_FAIL,                                                    //0x5006
    VEN_CODEC_AVP_STREAMING_EVENT_UNINIT_COMPLETE,                                                //0x5007
    VEN_CODEC_AVP_STREAMING_EVENT_PLAY_FAIL,                                                      //0x5008
    VEN_CODEC_AVP_STREAMING_EVENT_PLAY_COMPLETE,                                                  //0x5009
    VEN_CODEC_AVP_STREAMING_EVENT_STOP_FAIL,                                                      //0x500a
    VEN_CODEC_AVP_STREAMING_EVENT_STOP_COMPLETE,                                                  //0x500b
    VEN_CODEC_AVP_STREAMING_EVENT_PAUSE_FAIL,                                                     //0x500c
    VEN_CODEC_AVP_STREAMING_EVENT_PAUSE_COMPLETE,                                                 //0x500d
    VEN_CODEC_AVP_STREAMING_EVENT_RESUME_FAIL,                                                    //0x500e
    VEN_CODEC_AVP_STREAMING_EVENT_RESUME_COMPLETE,                                                //0x500f
    VEN_CODEC_AVP_STREAMING_EVENT_SEEK_FAIL,                                                      //0x5010
    VEN_CODEC_AVP_STREAMING_EVENT_SEEK_COMPLETE,                                                  //0x5011
    VEN_CODEC_AVP_STREAMING_EVENT_GET_DATA_FAIL,                                                  //0x5012
    VEN_CODEC_AVP_STREAMING_EVENT_GET_DATA_COMPLETE,                                              //0x5013
    VEN_CODEC_AVP_STREAMING_EVENT_DATA_IN,                                                        //0x5014
    VEN_CODEC_AVP_STREAMING_EVENT_DATA_EOS,                                                       //0x5015
    VEN_CODEC_AVP_STREAMING_EVENT_STORAGE_FULL,                                                   //0x5016
    VEN_CODEC_AVP_STREAMING_EVENT_NETWORK_DISCONNECTED,                                           //0x5017
    VEN_CODEC_AVP_STREAMING_EVENT_NETWORK_CONNECTION_FAIL,                                        //0x5018
    VEN_CODEC_AVP_STREAMING_EVENT_NETWORK_OPERATION_FAIL,                                         //0x5019
    VEN_CODEC_AVP_STREAMING_EVENT_UPDATE_DOWNLOAD_POS,                                            //0x501a
};


typedef ven_codec_ret_t (*ven_codec_VideoStreaming_DLItf)(s32 mediaHandle, s32 message_type, s32 data_size, void *data);


typedef enum Streaming_DLItf_Ret_
{
	VDO_STREAMING_DLITF_RET_OK = 0,
	VDO_STREAMING_DLITF_RET_INIT_FAILED,
	VDO_STREAMING_DLITF_RET_OPEN_FAILED,
	VDO_STREAMING_DLITF_RET_OPEN_PENDING,
	VDO_STREAMING_DLITF_RET_RECV_FAILED,
	VDO_STREAMING_DLITF_RET_RECV_PENDING,
	VDO_STREAMING_DLITF_RET_CONNECT_FAILED,
	VDO_STREAMING_DLITF_RET_INVALID_PARM,
	VDO_STREAMING_DLITF_RET_ERROR_NOMEMORY,
	VDO_STREAMING_DLITF_RET_ERROR_SETTING,
	VDO_STREAMING_DLITF_RET_ERROR_NETWORK,
	VDO_STREAMING_DLITF_RET_ERROR_TIMEOUT,
	VDO_STREAMING_DLITF_RET_ERROR_UNKOWN,
	VDO_STREAMING_DLITF_RET_NOT_HANDLE_REQ
}Vdo_Streaming_DLItf_Ret;

typedef u32 mmi_vdo_streaming_evt_type_e;

typedef struct _ven_codec_vdo_streaming_dm_to_stm_init_complete_t
{
    void *download_module_handle;
}ven_codec_vdo_streaming_dm_to_stm_init_complete_t;


typedef struct _ven_codec_vdo_streaming_dm_to_stm_data_in_t
{
    int data_size;
    void *data;
    int start_pos;
}  ven_codec_vdo_streaming_dm_to_stm_data_in_t;

typedef struct _ven_codec_vdo_streaming_http_pos_info_s
{
    int start_pos;
} ven_codec_vdo_streaming_http_pos_info_st;

typedef struct _ven_codec_vdo_streaming_rtsp_pos_info_s
{
    int start_pos;
    int audio_start_seq_num;
    int video_start_seq_num;
} ven_codec_vdo_streaming_rtsp_pos_info_st;

typedef struct _ven_codec_vdo_streaming_dm_to_stm_play_complete_s
{
    int file_size;
    union
    {
        ven_codec_vdo_streaming_http_pos_info_st http_pos_info;
        ven_codec_vdo_streaming_rtsp_pos_info_st rtsp_pos_info;
    } pos_info;
}ven_codec_vdo_streaming_dm_to_stm_play_complete_st;


typedef int vdo_streaming_avp_send_msg_to_avp_cb(int message_type, int data_size, void *data);
typedef int vdo_streaming_avp_send_msg_to_dm_cb(int message_type, int data_size, void *data);
typedef int vdo_streaming_avp_send_msg_to_stm_cb(void *stm_ctx, int message_type, int data_size, void *data);

typedef struct vdo_streaming_avp_to_dm_open_s
{
    vdo_streaming_avp_send_msg_to_avp_cb  *send_msg_to_avp;
} vdo_streaming_avp_to_dm_open_t;

typedef struct vdo_streaming_stm_to_dm_init_s
{
    void *streaming_handle;
    int min_queue_size;
    vdo_streaming_avp_send_msg_to_stm_cb *send_msg_to_stm;
} vdo_streaming_stm_to_dm_init_t;

typedef struct vdo_streaming_stm_to_dm_uninit_s
{
    void *download_module_handle;
} vdo_streaming_stm_to_dm_uninit_t;

#define VDO_STREAM_MAX_PATH 250
typedef struct vdo_streaming_stm_to_dm_play_s
{
    void *download_module_handle;
    u16 play_url[VDO_STREAM_MAX_PATH];
    int seek_type;
    int start_pos;
    int end_pos;
    int enable_audio;
    int enable_video;
} vdo_streaming_stm_to_dm_play_t;

typedef struct vdo_streaming_stm_to_dm_stop_s
{
    void *download_module_handle;
} vdo_streaming_stm_to_dm_stop_t;

typedef struct vdo_streaming_stm_to_dm_pause_s
{
    void *download_module_handle;
} vdo_streaming_stm_to_dm_pause_t;

typedef struct vdo_streaming_stm_to_dm_resume_s
{
    void *download_module_handle;
} vdo_streaming_stm_to_dm_resume_t;

typedef struct vdo_streaming_stm_to_dm_seek_s
{
    void *download_module_handle;
    int seek_type;
    int seek_pos;
} vdo_streaming_stm_to_dm_seek_t;

typedef struct vdo_streaming_stm_to_dm_data_consumed_s
{
    void *download_module_handle;
    void *data_ptr;
    int  data_size;
} vdo_streaming_stm_to_dm_data_consumed_t;

typedef struct _ven_codec_Vdo_Straming_DLItfHandle_t
{
    /* MDL info */
    struct ven_codec_downloadInterface_t_ *pDLItfFuncTbl;
    vdo_streaming_avp_send_msg_to_avp_cb *pDatalinkCtlCb;
    vdo_streaming_avp_send_msg_to_stm_cb *pStreamCtlCb;
    void *pStreamCtlHandle;
    /* user setting parameter*/
    u8 *pUrlPath;
    u16 nPathLen;
    void *pUserData;

}ven_codec_Vdo_Straming_DLItfHandle_t;

typedef int (*vdo_streaming_send_msg_to_dm_cb)(int message_type, int data_size, void *data);
typedef int (*vdo_streaming_send_msg_to_stm_cb)(void *stm_ctx, int message_type, int data_size, void *data);



typedef ven_codec_ret_t (*ven_codec_DLItf_Func)(ven_codec_Vdo_Straming_DLItfHandle_t *pVdoStreamingHandle, void *pMsg);


typedef struct ven_codec_downloadInterface_t_
{
    ven_codec_DLItf_Func           pfnMdlOpen;   
    ven_codec_DLItf_Func          pfnMdlClose;
    ven_codec_DLItf_Func           pfnMdlInit;
    ven_codec_DLItf_Func         pfnMdlUnInit;
    ven_codec_DLItf_Func           pfnMdlPlay;
    ven_codec_DLItf_Func           pfnMdlStop;
    ven_codec_DLItf_Func         pfnMdlResume;
    ven_codec_DLItf_Func          pfnMdlPause;
    ven_codec_DLItf_Func           pfnMdlSeek;
    ven_codec_DLItf_Func   pfnMdlDataComsumed;
   
} ven_codec_vdo_streaming_DLItfTbl_t;


////////////////////////////////////////////////////////////////////////////////////////////////
//Enumerations
////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
    VEN_MEDIA_FORMAT_WAVE,
    VEN_MEDIA_FORMAT_MP3,
    VEN_MEDIA_FORMAT_AAC,
    VEN_MEDIA_FORMAT_AMR,
    VEN_MEDIA_FORMAT_AWB,
    VEN_MEDIA_FORMAT_MID,   //midi
    VEN_MEDIA_FORMAT_MP4,
    VEN_MEDIA_FORMAT_WMA,
    VEN_MEDIA_FORMAT_WMV,
    VEN_MEDIA_FORMAT_3GP,
    VEN_MEDIA_FORMAT_RM,
    VEN_MEDIA_FORMAT_IMEL,  //melody
    VEN_MEDIA_FORMAT_KMV,
    VEN_MEDIA_FORMAT_PCM,
    VEN_MEDIA_FORMAT_M4A,    
    VEN_MEDIA_FORMAT_UNKNOWN,
    VEN_MEDIA_FORMAT_NUM

};

typedef u8 ven_codec_mediaFormat_t;

enum
{
    VEN_MEDIA_TYPE_AUDIO,
    VEN_MEDIA_TYPE_VIDEO,
    VEN_MEDIA_TYPE_UNKNOWN,
};

typedef u8 ven_codec_mediaType_t;

enum
{
    VEN_MEDIA_VOLUME_DEFAULT = 4,
    VEN_MEDIA_VOLUME_MIN = 0,
    VEN_MEDIA_VOLUME_0 = VEN_MEDIA_VOLUME_MIN,
    VEN_MEDIA_VOLUME_1,
    VEN_MEDIA_VOLUME_2,
    VEN_MEDIA_VOLUME_3,
    VEN_MEDIA_VOLUME_4,
    VEN_MEDIA_VOLUME_5,
    VEN_MEDIA_VOLUME_6,
    VEN_MEDIA_VOLUME_7,
    VEN_MEDIA_VOLUME_8,
    VEN_MEDIA_VOLUME_MAX = VEN_MEDIA_VOLUME_8

};

typedef u8 ven_codec_mediaVolume_t;

enum
{
    VEN_MEDIA_VDO_PLAY_SPEED_0_5X,
    VEN_MEDIA_VDO_PLAY_SPEED_1X,
    VEN_MEDIA_VDO_PLAY_SPEED_2X,
    VEN_MEDIA_VDO_PLAY_SPEED_4X
};

typedef u8 ven_codec_mediaVdoPlaySpeed_t;

enum
{
    VEN_MEDIA_TONE_ID_0 = 0, //< Index '0' DTMF Tone
    VEN_MEDIA_TONE_ID_1,     //< Index '1' DTMF Tone
    VEN_MEDIA_TONE_ID_2,     //< Index '2' DTMF Tone
    VEN_MEDIA_TONE_ID_3,     //< Index '3' DTMF Tone
    VEN_MEDIA_TONE_ID_4,     //< Index '4' DTMF Tone
    VEN_MEDIA_TONE_ID_5,     //< Index '5' DTMF Tone
    VEN_MEDIA_TONE_ID_6,     //< Index '6' DTMF Tone
    VEN_MEDIA_TONE_ID_7,     //< Index '7' DTMF Tone
    VEN_MEDIA_TONE_ID_8,     //< Index '8' DTMF Tone
    VEN_MEDIA_TONE_ID_9,     //< Index '9' DTMF Tone
    VEN_MEDIA_TONE_ID_A,     //< Index 'A' DTMF Tone
    VEN_MEDIA_TONE_ID_B,     //< Index 'B' DTMF Tone
    VEN_MEDIA_TONE_ID_C,     //< Index 'C' DTMF Tone
    VEN_MEDIA_TONE_ID_D,     //< Index 'D' DTMF Tone
    VEN_MEDIA_TONE_ID_STAR,  //< Index '*' DTMF Tone
    VEN_MEDIA_TONE_ID_HASH,  //< Index '#' DTMF Tone
    VEN_MEDIA_TONE_ID_BEEP1, //< System pre-defined beep
    VEN_MEDIA_TONE_ID_BEEP2, //< System pre-defined beep
};
typedef u8 ven_codec_mediaTone_t;

enum
{
    VEN_MEDIA_STORAGE_MEMORY = 0,///< Not support now
    VEN_MEDIA_STORAGE_MEMCARD,
    VEN_MEDIA_STORAGE_NOR,       ///< Not support now
    VEN_MEDIA_STORAGE_NAND,      ///< Not support now
};
typedef u8 ven_codec_mediaStorage_t;

enum
{
    VEN_MEDIA_PATH_DIRECTORY = 0,   ///< Directory
    VEN_MEDIA_PATH_PREFIX,          ///< Prefix, not support now 
    VEN_MEDIA_PATH_ABSOLUTE,        ///< Absolute filename
};
typedef u8 ven_codec_mediaPath_t;

enum
{
    VEN_MEDIA_LIMIT_SIZE = 0,   ///< Limit by file/memory size
    VEN_MEDIA_LIMIT_TIME,       ///< Limit by time in seconds
};
typedef u8 ven_codec_mediaLimit_t;

enum
{
    VEN_MEDIA_AUD_8_KHZ = 0,   ///< 8 kHz
    VEN_MEDIA_AUD_11_025_KHZ,  ///< 11.025 kHz
    VEN_MEDIA_AUD_12_KHZ,      ///< 12 kHz
    VEN_MEDIA_AUD_16_KHZ,      ///< 16 kHz
    VEN_MEDIA_AUD_22_050_KHZ,  ///< 22.050 kHz
    VEN_MEDIA_AUD_24_KHZ,      ///< 24 kHz
    VEN_MEDIA_AUD_32_KHZ,      ///< 32 kHz
    VEN_MEDIA_AUD_44_1_KHZ,    ///< 44.1 kHz
    VEN_MEDIA_AUD_48_KHZ,      ///< 48 kHz
    VEN_MEDIA_AUD_64_KHZ,      ///< 64 kHz
    VEN_MEDIA_AUD_96_KHZ       ///< 96 kHz
};
typedef u8 ven_codec_mediaAudFreq_t;

enum
{
    VEN_MEDIA_VDO_UNSEEKABLE        = 0,   /**< specified video file is unseekable */
    VEN_MEDIA_VDO_SEEKABLE          = 1,   /**< specified video file is seekable */
    VEN_MEDIA_VDO_SEEK_TAKES_TIME   = 2,   /**< specified video file is seekable, but takes time */
};
typedef u8 ven_codec_mediaVdoSeekable_t;

enum
{
    VEN_MEDIA_STREAM_ACT_FILL_DATA  = 0,   /**< Fill streaming data */
    VEN_MEDIA_STREAM_ACT_PLAY       = 1,   /**< Start streaming playback */
    VEN_MEDIA_STREAM_ACT_DATA_END   = 2,   /**< Fill last streaming data */
};
typedef u32 ven_codec_streamAction_t;

typedef enum
{   
    VEN_CODEC_AUD_MONO = 0,
    VEN_CODEC_AUD_STEREO,
}ven_codec_aud_mode_e;

typedef enum
{
    VEN_CODEC_CHANNEL_ONE = 0,
    VEN_CODEC_CHANNEL_TWO,
}ven_codec_aud_channel_num_e;

enum
{
	VEN_CODEC_RESOURCE_STATE_SUSPEND = 0,
	VEN_CODEC_RESOURCE_STATE_RESUME = 1,
	VNE_CODEC_RESOURCE_STATE_MAX
};
typedef s32 ven_codec_resource_state_t;

enum
{
    VEN_MEDIA_STREAM_PROG__NOT_STARTED = 0,
    VEN_MEDIA_STREAM_PROG__PARTIAL,
    VEN_MEDIA_STREAM_PROG__COMPLETE,
};
typedef u32 ven_codec_VideoStreamingProgress_e;


////////////////////////////////////////////////////////////////////////////////////////////////
//Structures
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    u32               totalTime;      //total playing time (milliseconds)
    u32               sampleRate;     //audio sample rate (Hz)
    u32               bitRate;        //audio bit rate (Hz)
    bool              stereo;         //stereo(true) or mono(false)
    ven_codec_mediaFormat_t format;   //audio format
} ven_codec_mediaAudInfo_t;

typedef struct
{
    u32                totalTime;     //total playing time (milliseconds)
    u32                sampleRate;    //audio sample rate (Hz)
    u32                bitRate;       //audio bit rate
    u32                vdoBitRate;    //video bit rate

    ven_codec_mediaVdoPlaySpeed_t maxSpeed;    //video playback support max speed

    bool               stereo;        //stereo(true) or mono(false)
    ven_codec_mediaVdoSeekable_t      seekable;      //video seek availability

    u16                height;        //video resolution height
    u16                width;         //video resolution width
} ven_codec_mediaVdoInfo_t;

typedef struct
{
    union
    {
        ven_codec_mediaAudInfo_t audInfo;
        ven_codec_mediaVdoInfo_t vdoInfo;
    } param;

    ven_codec_mediaType_t   type;   //audio/video/unknown

} ven_codec_mediaFileInfo_t;

typedef struct
{
    u32 status;         ///< image status
    u32 currentFrame;   ///< current frame decoded/decoding in the buffer
    u32 totalFrame;     ///< total frames
    u32 delayTime;      ///< delay to next frame (if total frames > 0)
} ven_codec_imageDecodeStatus_t;

typedef struct
{
    ven_codec_mediaTone_t   tone;   ///< Tone type
    ven_codec_mediaVolume_t volume; ///< Tone volume
} ven_codec_toneParam;

typedef struct
{
    ven_codec_mediaStorage_t storageType; ///< Storage device
    union
    {
        struct
        {
            u8  *pMemory;           ///< Storage memory pointer
            u32 memorySize;         ///< Storage memory size in bytes
        } memory;
        struct
        {
            u16 *pPath;             /* File path in UCS2 format, Ex. File: L"/Card/Record/Voice.amr"
                                                                     Folder: L"/Card/Record" */
            u16 pathLen;            ///< Path length in character
            ven_codec_mediaPath_t pathType; ///< File path type
        } file;
    } output;
} ven_codec_mediaRecStorage_t;

typedef struct
{
    ven_codec_mediaLimit_t limitType;   ///< Limit by file/memory size or time in seconds
    u32 limitValue;                     ///< The value of size(byets) or time(seconds)
} ven_codec_mediaRecLimit_t;

typedef struct
{
    ven_codec_aud_mode_e eMode;
    ven_codec_aud_channel_num_e eChanNum;
}ven_codec_mediaAudChanelParam_t;

typedef struct
{
    ven_codec_mediaFormat_t recFormat;      ///< Only AMR supported currently
    ven_codec_mediaAudFreq_t audFreq;       ///< Set audio record sample rate, not support now
    u32 bitRate;                            ///< Audio record bit rate, not support now
    ven_codec_mediaRecStorage_t storage;    ///< Record storage
    ven_codec_mediaRecLimit_t limit;        ///< Record limitation
} ven_codec_mediaAudRecParam_t;

typedef struct
{
    ven_codec_mediaAudRecParam_t sMediaAudRecParam;
    ven_codec_mediaAudChanelParam_t sMediaAudChannelParam;
}ven_codec_mediaAudRecParam_ex_t;

typedef struct
{
    u8 *pData;
    u32 dataSize;
} ven_codec_mediaAudioStreamRecord_RecInfo_t;

typedef void (*ven_codec_mediaAudioStreamRecord_RecCb)(ven_codec_mediaAudioStreamRecord_RecInfo_t *pRecInfo);

typedef struct
{
    ven_codec_mediaFormat_t recFormat;      ///< Only AMR supported currently
    ven_codec_mediaAudFreq_t audFreq;       ///< Set audio record sample rate, not support now
    u32 bitRate;                            ///< Audio record bit rate, not support now
    ven_codec_mediaAudioStreamRecord_RecCb pfnCb; ///< Callback function for recorded data indication
} ven_codec_mediaAudStreamingRecParam_t;

typedef struct
{
    ven_codec_mediaAudStreamingRecParam_t sMediaAudStreamingRecParam;
    ven_codec_mediaAudChanelParam_t sMediaAudChannelParam;
}ven_codec_mediaAudStreamingRecParam_ex_t;

typedef struct
{
    ven_codec_mediaFormat_t format; ///< Media format for streaming, support VEN_MEDIA_FORMAT_WAVE / VEN_MEDIA_FORMAT_AMR
    u8 *pData;                     ///< Pointer to the streaming data
    u32 dataLen;                    ///< The data length in byte
    ven_codec_streamAction_t action; ///< 0: fill 1:play 2:end
} ven_codec_streaming_param_t;

typedef struct
{
    ven_codec_mediaAudFreq_t audFreq;
    u32 bitRate;
    ven_codec_mediaAudChanelParam_t sMediaAudChannelParam;
}ven_codec_mediaAud_info_t;

typedef enum
{
    VEN_MEDIA_SEEK_MODE__OFF,             /// disable the functionality to seek
    VEN_MEDIA_SEEK_MODE__DOWNLOADED_ONLY, /// it can only seek downloaded data
    VEN_MEDIA_SEEK_MODE__ALL,             /// it can seek all data
} ven_codec_SeekMode_e;

typedef enum
{
    VEN_MEDIA_VDO_STREAM_FILE_MODE  = 0,   /// file mode
    VEN_MEDIA_VDO_STREAM_MEM_MODE   = 1, /// memory mode
}ven_codec_videoStreamingMode_e;

enum
{
    VEN_MEDIA_VDO_STATUS_PLAY_RESULT  = 0, /**< Update the play result */
    VEN_MEDIA_VDO_STATUS_PLAYTICK   = 1,   /**< Update the playback timetick */
    VEN_MEDIA_VDO_STATUS_TERMINATED = 2,   /**< Playback is terminated */
};
typedef u8 ven_codec_video_status_e;


typedef struct
{
    ven_codec_videoStreamingMode_e eStreamingMode;
    u16 *pURL;
    u16 nUrlLen;
    void *pUsrData;
    ven_codec_mediaFormat_t nFormat; ///< Media format for streaming, only support VEN_MEDIA_FORMAT_KMV for now
} ven_codec_videostreaming_req_t;

typedef struct Ven_Codec_VideoStreamingInfo
{
    u16 *pURL;                                    ///< URL for streaming video. 
    u16 nUrlLen;                                  ///< Length of URL
    ven_codec_VideoStreamingProgress_e eProgress; ///< progress of given URL
} Ven_Codec_VideoStreamingInfo_t;

typedef enum
{
    VEN_CODEC_VDOSTREAM_FILECHANGE_MOVE= 0,
    VEN_CODEC_VDOSTREAM_FILECHANGE_COPY,
}ven_codec_videostreaming_filechg_mode_t;
typedef struct Ven_Codec_VideoStreamingFileChange
{
    u16 *pSrcURL;
    u16 nSrcUrlLen;
    u16 *pDestURL;
    u16 nDestUrlLen;
    ven_codec_videostreaming_filechg_mode_t eVdoStreamFileChgMode;
} Ven_Codec_VideoStreamingFileChange_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_codec_openMedia
 *  @brief    Caller must call this opening function and keep the returned handle for further usage.
 *            Caller must call the ven_codec_closeMedia(s32) to release all allocated system resources.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  pMediaHandle     [out]Pointer to store the opened media handle
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        s32 mediaHandle;           [out]Handle of media session.
 *        ven_codec_ret_t retCode;   [out]The result of opening media session.
 *                                        If the retCode is not VEN_CODEC_SUCCESS, the value of mediaHandle is meaningless
 *    } ven_codec_open_media_rsp_t;
 *
 */

ven_codec_ret_t ven_codec_openMedia(s32* pMediaHandle, ven_req_data_t* ptVenReq);

typedef struct
{
    s32 mediaHandle;
    ven_codec_ret_t retCode;

} ven_codec_open_media_rsp_t;

/**
 *  ven_codec_closeMedia
 *  @brief    Users must call this closing function to release all internal allocated resources.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  pMediaHandle     [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;          [out]The result of closing media request.
 *
 */
ven_codec_ret_t ven_codec_closeMedia(s32 mediaHandle, ven_req_data_t* ptVenReq);

/**
*  ven_codec_setAudioResStateLisenter
*  @brief    Users must call this interface to listen the Audio Res state change for your App 
*            Note: This function supports only asynchronous
*
*  @param  pMediaHandle     [in]Handle returned from ven_codec_openMedia()
*  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS if success
*			VEN_CODEC_WRONG_HANDLE  if worng handle
*			VEN_CODEC_BAD_PARAMETERS if wrong param
*
*  @limit: only support aync to registry Res Ind
*  Response structure:
*
*    ven_codec_ret_t retCode;          [out]The result of Set Audio resource lisenter.
*
*/

//wait for remove
ven_codec_ret_t ven_codec_setAudioResStateLisenter(s32 mediaHandle, ven_req_data_t* ptVenReq);
/**
*  ven_codec_GetAudioResState
*  @brief    Users  call this interface to get the Audio Res state by media hadnle for your App 
*            Note: This function supports only synchronous
*
*  @param  pMediaHandle     [in]Handle returned from ven_codec_openMedia()
*  @param  pState         	[out]Pointer to Audio Resource state
*
*  @retval VEN_CODEC_SUCCESS if success
*			VEN_CODEC_WRONG_HANDLE  if worng handle
*			VEN_CODEC_BAD_PARAMETERS if wrong param
*
*  @limit: only support sync
*  Response structure:
*
*    ven_codec_ret_t retCode;          [out]The result of get audio resource state.
*
*/
/*
//wait for remove
ven_codec_ret_t ven_codec_GetAudioResState(s32 mediaHandle,ven_codec_resource_state_t *pState);
*/
/**
 *  ven_codec_getFileInfo
 *  @brief    This function is used to get the information of specified media file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  URL              [in]The file URL to be played. The file URL is in UCS2 format and in absolute path.
 *                               Note: The memory of this field should be allocated by vender task.
 *                                     And the memory should be freed by vender when the response message is received
 *  @param  URLLen           [in]The total char length of file URL.
 *  @param  pInfo            [out]The file information which platform return
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        ven_codec_ret_t retCode;             [out]The result of getting file info request.
 *                                                  If the retCode is not VEN_CODEC_SUCCESS, the pInfo data is meaningless
 *        ven_codec_mediaFileInfo_t *pInfo;    [out]The pointer of the retrieved file info. Third party has to free the data once finished using it
 *                                                  only if the retCode is VEN_CODEC_SUCCESS; otherwise, pInfo is NULL *
 *    } ven_codec_get_file_info_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_getFileInfo(s32 mediaHandle , u16 *URL, u16 URLLen, ven_codec_mediaFileInfo_t *pInfo , ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    ven_codec_mediaFileInfo_t *pInfo;
} ven_codec_get_file_info_rsp_t;

/**
 *  ven_codec_getRawInfo
 *  @brief    This function is used to get the information of specified media raw data (audio/video)
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pData            [in]The raw data of the specified media.  The memory of this field should be allocated by vendor task, and the memory
 *                               should be freed by vendor when the response message is received.
 *  @param  dataLen          [in]The size of the raw data
 *  @param  pInfo            [out]The file information which platform return
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        ven_codec_ret_t retCode;             [out]The result of getting file info request.
 *                                                  If the retCode is not VEN_CODEC_SUCCESS, the pInfo data is meaningless
 *        ven_codec_mediaFileInfo_t *pInfo;    [out]The pointer of the retrieved file info. Third party has to free the data once finished using it
 *                                                  only if the retCode is VEN_CODEC_SUCCESS; otherwise, pInfo is NULL *
 *    } ven_codec_get_raw_info_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_getRawInfo(s32 mediaHandle , void *pData, u32 dataLen, ven_codec_mediaFormat_t mediaFormat, ven_codec_mediaFileInfo_t *pInfo , ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    ven_codec_mediaFileInfo_t *pInfo;
} ven_codec_get_raw_info_rsp_t;

/**
 *  ven_codec_getVdoExtInfo
 *  @brief    This function is used to get the extended information of specified media file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  URL              [in]The file URL to be played. The file URL is in UCS2 format and in absolute path.
 *                               Note: The memory of this field should be allocated by vender task.
 *                                     And the memory should be freed by vender when the response message is received
 *  @param  URLLen           [in]The total char length of file URL.
 *  @param  pExtInfo           [in]The pointer of the extention information data.
 *  @param  nExtInfoLen           [in]The total char length of the extention information data.
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        ven_codec_ret_t retCode;             [out]The result of getting file info request.
 *                                                  If the retCode is not VEN_CODEC_SUCCESS, the pInfo data is meaningless
 *        u32 *pExtInfo;    [out]The pointer of the extended information data.
 *        u32 nExtInfo;      [out]The length of the extended information data.
 *    } ven_codec_get_vdo_ext_info_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_getVdoExtInfo(s32 mediaHandle , u16 *URL, u16 urlLen, u32 *pExtInfo, u32 nExtInfoLen, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    u32 *pExtInfo;
    u32 nExtInfoLen;
} ven_codec_get_vdo_ext_info_rsp_t;

/**
 *  ven_codec_getAudRawInfo
 *  @brief    This function is used to get the information of specified audio raw data
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pData            [in]The raw data of the specified media.  The memory of this field should be allocated by vendor task, and the memory
 *                               should be freed by vendor when the response message is received.
 *  @param  dataLen          [in]The size of the raw data
 *  @param  mediaFormat      [in]The format of the raw data, platform will try to parse format by itself when it is VEN_MEDIA_FORMAT_UNKNOWN. 
 *  @param  pInfo            [out]The file information which platform return
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        ven_codec_ret_t retCode;             [out]The result of getting file info request.
 *                                                  If the retCode is not VEN_CODEC_SUCCESS, the pInfo data is meaningless
 *        ven_codec_mediaAudInfo_t *pInfo;    [out]The pointer of the retrieved file info.
 *    } ven_codec_get_aud_raw_info_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_getAudRawInfo(s32 mediaHandle , void *pData, u32 dataLen, ven_codec_mediaFormat_t mediaFormat, ven_codec_mediaAudInfo_t *pInfo , ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    ven_codec_mediaAudInfo_t *pInfo;
} ven_codec_get_aud_raw_info_rsp_t;

/**
 *  ven_codec_getPlayingTime
 *  @brief    This function is used to get the current playing time.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pPlayingTime     [out]The playing time which platform return
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR   if failed
 *          VEN_CODEC_UNSUPPORT if there is no availavle playing time for the given media handle (ex. midi / raw data / streaming)
 *          VEN_CODEC_NOT_PLAYING if the music is not playing
 *          VEN_CODEC_PLAY_FINISHED if the music is finished
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;   [out]The result of playing time request.
 */
ven_codec_ret_t ven_codec_getPlayingTime(s32 mediaHandle, u32* pPlayingTime, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    u32 playingTime;
} ven_codec_get_playing_time_rsp_t;


/**
 *  ven_codec_playAudio
 *  @brief    This function is used to play the audio file(URL) with specified parameters.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pURL             [in]The URL is in UCS2 format and in absolute path.
 *                               The memory of this field should be allocated by vendor task, and the memory should
 *                               be freed by vendor when the response message is received.
 *  @param  URLLen           [in]The total char length of file URL
 *  @param  position         [in]The starting point. Default is 0, from the beginning
 *  @param  volume           [in]Volumn level
 *  @param  loop             [in]Repeat the playing or not
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;   [out]The result of playing audio request.
 *
 *
 *    Note that when the music is finished, VEN_CODEC_PLAY_FINISHED is returned to the same callback function.
 *
 */
ven_codec_ret_t ven_codec_playAudio(s32 mediaHandle, u16 *URL, u16 URLLen, u32 position, ven_codec_mediaVolume_t volume, bool loop, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_playAudioRaw
 *  @brief    This function is used to play the audio raw data with specified parameters.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  mediaFormat      [in]The media format of the raw data.  Currently, only wav and midi formats are supported.
 *  @param  pData            [in]The raw data of the audio.  The memory of this field should be allocated by vendor task, and the memory
 *                               should be freed by vendor when the response message is received.
 *  @param  dataLen          [in]The size of the raw data
 *  @param  volume           [in]Volumn level
 *  @param  loop             [in]Repeat the playing or not
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR   if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;   [out]The result of playing audio raw data request.
 *
 *
 *    Note that when the music is finished, VEN_CODEC_PLAY_FINISHED is returned to the same callback function.
 *
 */
ven_codec_ret_t ven_codec_playAudioRaw(s32 mediaHandle, ven_codec_mediaFormat_t mediaFormat, u8 *pData, u32 dataLen, ven_codec_mediaVolume_t volume, bool loop, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_pauseAudio
 *  @brief    This function is used to pause the playing audio file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *          VEN_CODEC_UNSUPPORT if the given media handle can not be paused (ex. midi / raw data / streaming)
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;   [out]The result of pausing audio request.
 *
 */
ven_codec_ret_t ven_codec_pauseAudio(s32 mediaHandle, ven_req_data_t* ptVenReq);


/**
 *  ven_codec_resumeAudio
 *  @brief    This function is used to resume the playing audio file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *          VEN_CODEC_UNSUPPORT if the given media handle can not be resumed (ex. midi / raw data / streaming)
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;    [out]The result of resuming audio request.
 *
 */
ven_codec_ret_t ven_codec_resumeAudio(s32 mediaHandle, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_stopAudio
 *  @brief    This function is used to stop the playing audio file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;     [out]The result of stopping audio request.
 *
 */
ven_codec_ret_t ven_codec_stopAudio(s32 mediaHandle, ven_req_data_t* ptVenReq);


/**
 *  ven_codec_setAudioPosition
 *  @brief    This function is used to stop the playing audio file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  position         [in]The position to be set. Always count from the start
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;    [out]The result of setting audio position request.
 *
 */
ven_codec_ret_t ven_codec_setAudioPosition(s32 mediaHandle, u32 position, ven_req_data_t* ptVenReq);


/**
 *  ven_codec_setAudioVolume
 *  @brief    This function is used to stop the playing audio file
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  volume           [in]The volume level to be set.
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;   [out]The result of setting audio volume request.
 *
 */
ven_codec_ret_t ven_codec_setAudioVolume(s32 mediaHandle, ven_codec_mediaVolume_t volume , ven_req_data_t* ptVenReq);



/**
 *  ven_codec_getAudioVolume
 *  @brief    This function is used to get the current volume level.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pVolume          [out]The pointer to the retrieved volume.
 *                                Note: asynchronous api so the parameter should be NULL
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                           It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    typedef struct {
 *        ven_codec_ret_t retCode;                 [out]The result of getting audio volume request.
 *                                                      If the retCode is not VEN_CODEC_SUCCESS, the volume is meaningless
 *        ven_codec_mediaVolume_t volume;          [out]The retrieved audio volume
 *    } ven_codec_get_audio_volume_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_getAudioVolume(s32 mediaHandle, ven_codec_mediaVolume_t* pVolume, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    ven_codec_mediaVolume_t volume;
} ven_codec_get_audio_volume_rsp_t;

/**
 * ven_codec_playTone
 * @brief     This function is used to play pre-defined tone
 *            Note: This function supports both synchronous and asynchronous
 *
 * @param  mediaHandle    [in]Handle returned from ven_codec_openMedia()
 * @param  tone           [in]Pre-defined tone
 * @param  volume         [in]Volumn level
 * @param  ptVenReq       [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_CODEC_SUCCESS  if success
 *         VEN_CODEC_ERROR    if failed
 *
 * Response structure:
 *
 *   ven_codec_ret_t retCode;   [out]The result of playing midi request
 *
 */
ven_codec_ret_t ven_codec_playTone(s32 mediaHandle, ven_codec_mediaTone_t tone, ven_codec_mediaVolume_t volume, ven_req_data_t* ptVenReq);



/*********************************************************
Use case of StartRec and StopRec
Sync:
1.
Sync Start request with StartCB(), return success ==> When play End, will trigger StarCB(return code, ven_codec_audio_record_rsp_t *pRecordData)
2.
Sync Start request with StartCB(), return success ==> Sync StopEx Request, return success and get (ven_codec_audio_record_rsp_t *pRecordData) by Param

Async
1.
Async Start request with StartCB(), return success and then will trigger StartCB(return code, ven_codec_audio_record_rsp_t *pRecordData) to make sure Rec is success
==> When play End, will trigger StarCB(return code, ven_codec_audio_record_rsp_t *pRecordData)
2.
Async Start request with StartCB(), return success and then will trigger StartCB(return code, ven_codec_audio_record_rsp_t *pRecordData) to make sure Rec is success
==> Async Stop Request, return success,will trigger StarCB(return code, ven_codec_audio_record_rsp_t *pRecordData) to get return code and RecData
**********************************************************/
/**
 *  ven_codec_StartAudioRecord
 *  @brief    This function is used to start audio recording.
 *            Note: This function both supports sync and asynchronous 
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pRecParam        [in]The pointer to the recording parameter.
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                           It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *          VEN_CODEC_BAD_PARAMETERS   if the input parameters are not legal
 *          VEN_CODEC_FORMAT_UNSUPPORT if the input format doesn't support now
 *
 *  @deprecated
 *      the API only support SD card storage for old user
 **                         VEN_MEDIA_FORMAT_AMR with frequency = 8  KHZ, bitrate = 12200      and mode = mono
 *                           VEN_MEDIA_FORMAT_AWB with frequency = 16 KHZ, bitrate = 23850      and mode = mono
 *                           VEN_MEDIA_FORMAT_PCM with frequency = 8  KHZ, bit     = 16         and mode = mono
 *                           VEN_MEDIA_FORMAT_WAV with frequency = 8  KHZ, bits    = 4          and mode = mono
 *                           VEN_MEDIA_FORMAT_MP3 with frequency = 32 KHZ, bitrate = 160000 bps and mode = mono
 *
 *      once you specifies the format, the frequency, bitrate and mode is hard code as above.
 *      if you want to change the frequency, bitrate ...etc, you can use ven_codec_StartAudioRecordEx instead.
 *
 *
 *  Response structure:
 *
 *  typedef struct
 *  {
 *      ven_codec_ret_t retCode;               [out]The result of recording audio request.
 *      ven_codec_mediaStorage_t storageType;  [out]The storage type user select while starting record.
 *      union
 *      {
 *          struct
 *          {
 *              u8  *pMemory;           ///< Storage memory pointer
 *              u16 memorySize;         ///< Storage memory size in bytes
 *          } memory;// Not support now 
 *          struct
 *          {
 *              u16 *pPath;             ///< File path in UCS2 format
 *              u16 pathLen;            ///< Path length in character
 *          } file;
 *      } output;                              [out]The output file, only available when stop record or other event(space full, record error) 
 *                                                  occurs during recording, if save file failed, it will be NULL, too.
 *  } ven_codec_audio_record_rsp_t;
 *
 *  Note: Vendor has to make a copy of the output file/memory from ven_codec_audio_record_rsp_t
 */
ven_codec_ret_t ven_codec_StartAudioRecord(s32 mediaHandle, ven_codec_mediaAudRecParam_t *pRecParam, ven_req_data_t* ptVenReq);

/**
*  ven_codec_StartAudioRecordEx
*  @brief    This function is used to start audio recording.
*            Note: This function supports asynchronous only
*
*  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
*  @param  pRecParamEx      [in]The pointer to the recording parameter.
*  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS          if success
*          VEN_CODEC_ERROR            if failed
*          VEN_CODEC_BAD_PARAMETERS   if the input parameters are not legal
*          VEN_CODEC_FORMAT_UNSUPPORT if the input format doesn't support now
*
*  Response structure:
*
*  typedef struct
*  {
*      ven_codec_ret_t retCode;               [out]The result of recording audio request.
*      ven_codec_mediaStorage_t storageType;  [out]The storage type user select while starting record.
*      union
*      {
*          struct
*          {
*              u8  *pMemory;           ///< Storage memory pointer
*              u16 memorySize;         ///< Storage memory size in bytes
*          } memory;// Not support now 
*          struct
*          {
*              u16 *pPath;             ///< File path in UCS2 format
*              u16 pathLen;            ///< Path length in character
*          } file;
*      } output;                              [out]The output file, only available when stop record or other event(space full, record error) 
*                                                  occurs during recording, if save file failed, it will be NULL, too.
*  } ven_codec_audio_record_rsp_t;
*
*  Note: Vendor has to make a copy of the output file/memory from ven_codec_audio_record_rsp_t
*
*        The extention API support SD/MEMORY/NAND/NOR stroage 
*                             VEN_MEDIA_FORMAT_AMR with frequency = 8  KHZ, bitrate = 12200      and mode = mono
*                             VEN_MEDIA_FORMAT_AWB with frequency = 16 KHZ, bitrate = 23850      and mode = mono
*                             VEN_MEDIA_FORMAT_PCM with frequency = 8  KHZ, bits    = 16         and mode = mono
*                                                       frequency = 16 KHZ, bits    = 16         and mode = mono
*                                                       frequency = 32 KHZ, bits    = 16         and mode = mono
*                             VEN_MEDIA_FORMAT_WAV with frequency = 8  KHZ, bits    = 4          and mode = mono
*                                                       frequency = 16 KHZ, bits    = 4          and mode = mono
*                                                       frequency = 32 KHZ, bits    = 4          and mode = mono
*                             VEN_MEDIA_FORMAT_MP3 with frequency = 32 KHZ, bitrate = 160000 bps and mode = mono
*
*/
ven_codec_ret_t ven_codec_StartAudioRecordEx(s32 mediaHandle, ven_codec_mediaAudRecParam_ex_t *pRecParamEx, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    ven_codec_mediaStorage_t storageType; ///< Storage device
    union
    {
        struct
        {
            u8  *pMemory;           ///< Storage memory pointer
            u32 memorySize;         ///< Storage memory size in bytes
        } memory;
        struct
        {
            u16 *pPath;             ///< File path in UCS2 format
            u16 pathLen;            ///< Path length in character
        } file;
    } output;
} ven_codec_audio_record_rsp_t;

/**
 *  ven_codec_StopAudioRecord
 *  @brief    This function is used to stop audio recording.
 *            Note: This function supports asynchronous only
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                           It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *  typedef struct
 *  {
 *      ven_codec_ret_t retCode;               [out]The result of stop recording audio request.
 *      ven_codec_mediaStorage_t storageType;  [out]The storage type user select while starting record.
 *      union
 *      {
 *          struct
 *          {
 *              u8  *pMemory;           ///< Storage memory pointer
 *              u16 memorySize;         ///< Storage memory size in bytes
 *          } memory;// Not support now 
 *          struct
 *          {
 *              u16 *pPath;             ///< File path in UCS2 format
 *              u16 pathLen;            ///< Path length in character
 *          } file;
 *      } output;                              [out]The output file, only available when stop record or other event(space full, record error) 
 *                                                  occurs during recording, if save file failed, it will be NULL, too.
 *  } ven_codec_audio_record_rsp_t;
 *
 *  Note: Vendor has to make a copy of the output file/memory from ven_codec_audio_record_rsp_t
 */
ven_codec_ret_t ven_codec_StopAudioRecord(s32 mediaHandle, ven_req_data_t* ptVenReq);

/**
*  ven_codec_StopAudioRecordEx
*  @brief    This function is used to stop audio recording.
*            Note: This function supports both sync and asynchronous
*
*  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
*  @Param  pRecResultData  [out] to get the result of RecData when Request is Sync (if Rec by File, after return success should Free output.file.pPath(content is URL) by Self)
*  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                                    It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS if success
*          VEN_CODEC_ERROR  if failed
*
*
*  Response structure:
*
*  typedef struct
*  {
*      ven_codec_ret_t retCode;               [out]The result of stop recording audio request.
*      ven_codec_mediaStorage_t storageType;  [out]The storage type user select while starting record.
*      union
*      {
*          struct
*          {
*              u8  *pMemory;           ///< Storage memory pointer
*              u16 memorySize;         ///< Storage memory size in bytes
*          } memory;// Not support now 
*          struct
*          {
*              u16 *pPath;             ///< File path in UCS2 format
*              u16 pathLen;            ///< Path length in character
*          } file;
*      } output;                              [out]The output file, only available when stop record or other event(space full, record error) 
*                                                  occurs during recording, if save file failed, it will be NULL, too.
*  } ven_codec_audio_record_rsp_t;
*
*  Note: Vendor has to make a copy of the output file/memory from ven_codec_audio_record_rsp_t
*/

ven_codec_ret_t ven_codec_StopAudioRecordEx(s32 mediaHandle, ven_codec_mediaRecStorage_t *pRecResultData, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_StartAudioStreamingRecord
 *  @brief    This function is used to start audio streaming recording.
 *            Note: This function supports asynchronous only
 *
 *  @param  mediaHandle         [in]Handle returned from ven_codec_openMedia()
 *  @param  pStreamingRecParam  [in]The pointer to the recording parameter.
 *  @param  ptVenReq            [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                              It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *          VEN_CODEC_BAD_PARAMETERS   if the input parameters are not legal
 *          VEN_CODEC_FORMAT_UNSUPPORT if the input format doesn't support now
 *
 *  @deprecated
 *      the API only support VEN_MEDIA_FORMAT_AMR with frequency = 8  KHZ, bitrate = 12200      and mode = mono
 *                           VEN_MEDIA_FORMAT_AWB with frequency = 16 KHZ, bitrate = 23850      and mode = mono
 *                           VEN_MEDIA_FORMAT_PCM with frequency = 8  KHZ, bit     = 16         and mode = mono
 *                           VEN_MEDIA_FORMAT_WAV with frequency = 8  KHZ, bits    = 4          and mode = mono
 *                           VEN_MEDIA_FORMAT_MP3 with frequency = 32 KHZ, bitrate = 160000 bps and mode = mono
 *
 *  Response structure:
 *
 *   ven_codec_ret_t retCode;   [out]The result of starting audio streaming record
 *
 *    typedef struct {
 *        u8 *pData;      [out]Pointer to the recorded data
 *        u32 dataSize;   [out]Data size in bytes
 *    } ven_codec_mediaAudioStreamRecord_RecInfo_t;
 *
 *    Note: Vendor has to make a copy of the pData from ven_codec_mediaAudioStreamRecord_RecInfo_t
 *
 */
ven_codec_ret_t ven_codec_StartAudioStreamingRecord(s32 mediaHandle, ven_codec_mediaAudStreamingRecParam_t *pStreamingRecParam, ven_req_data_t* ptVenReq);

/**
*  ven_codec_StartAudioStreamingRecordEx
*  @brief    This function is used to start audio streaming recording.
*            Note: This function supports asynchronous only
*
*  @param  mediaHandle         [in]Handle returned from ven_codec_openMedia()
*  @param  pStreamingRecParamEx[in]The pointer to the recording parameter.
*  @param  ptVenReq            [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                              It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS          if success
*          VEN_CODEC_ERROR            if failed
*          VEN_CODEC_BAD_PARAMETERS   if the input parameters are not legal
*          VEN_CODEC_FORMAT_UNSUPPORT if the input format doesn't support now
*
*
*  Response structure:
*
*   ven_codec_ret_t retCode;   [out]The result of starting audio streaming record
*
*    typedef struct {
*        u8 *pData;      [out]Pointer to the recorded data
*        u32 dataSize;   [out]Data size in bytes
*    } ven_codec_mediaAudioStreamRecord_RecInfo_t;
*
*    Note: Vendor has to make a copy of the pData from ven_codec_mediaAudioStreamRecord_RecInfo_t
*
*          The API only support VEN_MEDIA_FORMAT_AMR with frequency = 8  KHZ, bitrate = 12200       and mode = mono
*                               VEN_MEDIA_FORMAT_AWB with frequency = 16 KHZ, bitrate = 23850       and mode = mono
*                               VEN_MEDIA_FORMAT_PCM with frequency = 8  KHZ, bits    = 16          and mode = mono
*                                                         frequency = 16 KHZ, bits    = 16          and mode = mono
*                                                         frequency = 32 KHZ, bits    = 16          and mode = mono
*                               VEN_MEDIA_FORMAT_WAV with frequency = 8  KHZ, bits    = 4           and mode = mono
*                                                         frequency = 16 KHZ, bits    = 4           and mode = mono
*                                                         frequency = 32 KHZ, bits    = 4           and mode = mono
*                               VEN_MEDIA_FORMAT_MP3 with frequency = 32 KHZ, bitrate = 160000  bps and mode = mono
*/
ven_codec_ret_t ven_codec_StartAudioStreamingRecordEx(s32 mediaHandle, ven_codec_mediaAudStreamingRecParam_ex_t *pStreamingRecParamEx, ven_req_data_t* ptVenReq);

typedef struct
{
    u8 *pData;      ///< Pointer to the recorded data
    u32 dataSize;   ///< Data size in bytes
} ven_codec_audio_streaming_record_ind_t;

/**
 *  ven_codec_StopAudioStreamingRecord
 *  @brief    This function is used to stop audio streaming recording.
 *            Note: This function supports asynchronous only
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                           It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *   ven_codec_ret_t retCode;   [out]The result of stopping audio streaming record
 *
 */
ven_codec_ret_t ven_codec_StopAudioStreamingRecord(s32 mediaHandle, ven_req_data_t* ptVenReq);

/**
*  ven_codec_setAudioInfo
*
* @brief     This function is used to set header information for those no header audio data
*            Ex: Pcm
*
**/
ven_codec_ret_t ven_codec_setAudioInfo(s32 mediaHandle, ven_codec_mediaAud_info_t *psMediaAudInfo);


/**
 *  ven_codec_playAudioStreaming
 *
 * @brief     This function is used to play audio streaming
 *            Note: This function supports asynchronous only
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  mediaFormat      [in]The media format of the raw data.  Currently, only wav and AMR formats are supported.
 *  @param  pData            [in]The raw data of the audio.  The memory of this field should be allocated by vendor task, and the memory
 *                               should be freed by vendor when the response message is received.
 *  @param  dataLen          [in]The size of the raw data
 *  @param  volume           [in]Volumn level
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 *          VEN_CODEC_STREAMING_ADD_BUFFER_DONE if the streaming data is duplicated into system streaming buffer
 *          VEN_CODEC_STREAMING_BUFFER_FULL if system streaming buffer is full
 *
 * Response structure:
 * typedef struct {
 *     u8 *pData;
 *     u32 requestDataSize;
 *     ven_codec_ret_t retCode;
 * } ven_codec_play_audio_streaming_rsp_t;
 *
 */
ven_codec_ret_t ven_codec_playAudioStreaming(s32 mediaHandle, ven_codec_streaming_param_t *pStreamParam, ven_req_data_t* ptVenReq);

typedef struct
{
    u8 *pData;                  /// The pointer of the played streaming data.
    u32 requestDataSize;        /// System streaming buffer is almost empty, vendor needs to send more data immediately. The max data size is requestDataSize
    ven_codec_ret_t retCode;    /// VEN_CODEC_STREAMING_ADD_BUFFER_DONE if the streaming data is duplicated to system streaming buffer
                                /// VEN_CODEC_STREAMING_BUFFER_FULL if system stream buffer is full.
                                /// VEN_CODEC_STREAMING_BUFFER_UNDER_RUN if system streaming buffer is almost empty
} ven_codec_play_audio_streaming_rsp_t;

ven_codec_ret_t ven_codec_getAvailableAudioStreamingBufferSize(s32 mediaHandle, u32 *pAvailableSize, ven_req_data_t* ptVenReq);

typedef struct
{
    u32 nSize;
    ven_codec_ret_t retCode;
} ven_codec_get_available_audio_streaming_buffer_size_rsp_t;

ven_codec_ret_t ven_codec_getFilledAudioStreamingBufferSize(s32 mediaHandle, u32 *pFilledSize, ven_req_data_t* ptVenReq);

typedef struct
{
    u32 nSize;
    ven_codec_ret_t retCode;
} ven_codec_get_filled_audio_streaming_buffer_size_rsp_t;

ven_codec_ret_t ven_codec_getStreamingRingBufferSize(s32 mediaHandle, u32 *pRingBufferSize, ven_req_data_t* ptVenReq);

typedef struct
{
    u32 nSize;
    ven_codec_ret_t retCode;
} ven_codec_get_audio_streaming_buffer_size_rsp_t;

typedef struct
{
    u32 nStatus;
    ven_codec_ret_t retCode;
} ven_codec_is_audio_streaming_rsp_t;

ven_codec_ret_t ven_codec_isAudioStreaming(s32 mediaHandle, u32 *pStatus, ven_req_data_t* ptVenReq);

/**
*  ven_codec_pauseAudioStreaming
*  @brief    This function is used to pause the playing audio file
*            Note: This function supports both synchronous and asynchronous
*
*  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
*  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS if success
*          VEN_CODEC_ERROR  if failed
*          VEN_CODEC_UNSUPPORT if the given media handle can not be paused (ex. midi / raw data / streaming)
*		    VEN_CODEC_NOT_PLAYING if do not have streaming play now
*			VEN_CODEC_BAD_PARAMETERS if Parameter have wrong param
*
*
*  Response structure:
*
*    ven_codec_ret_t retCode;   [out]The result of pausing audio request.
*
*/
ven_codec_ret_t ven_codec_pauseAudioStreaming(s32 mediaHandle, ven_req_data_t* ptVenReq);


/**
*  ven_codec_resumeAudioStreaming
*  @brief    This function is used to resume the playing audio file
*            Note: This function supports both synchronous and asynchronous
*
*  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
*  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval VEN_CODEC_SUCCESS if success
*          VEN_CODEC_ERROR  if failed
*          VEN_CODEC_UNSUPPORT if the given media handle can not be resumed (ex. midi / raw data / streaming)
*			VEN_CODEC_NOT_PAUSE if it does not have streaming play in Pause status
*			VEN_CODEC_BAD_PARAMETERS if Parameter have wrong param
*
*
*  Response structure:
*
*    ven_codec_ret_t retCode;    [out]The result of resuming audio request.
*
*/
ven_codec_ret_t ven_codec_resumeAudioStreaming(s32 mediaHandle, ven_req_data_t* ptVenReq);

/**
 * ven_codec_playMidiTone
 * @brief     This function is used to play audio midi
 *            Note: This function supports both synchronous and asynchronous
 *
 * @param  mediaHandle    [in]Handle returned from ven_codec_openMedia()
 * @param  note           [in]Note number (0 to 127)
 * @param  duration       [in]The duration (in milliseconds) of this note
 * @param  volume         [in]Tone volume value from 0(silent) to 100(maximum)
 * @param  ptVenReq       [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 * @retval VEN_CODEC_SUCCESS  if success
 *         VEN_CODEC_ERROR    if failed
 *
 * Response structure:
 *
 *   ven_codec_ret_t retCode;   [out]The result of playing midi request
 *
 */
ven_codec_ret_t ven_codec_playMidiTone(s32 mediaHandle, u32 note, u32 duration, u32 volume, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_setMidiChannelVolume
 *  @brief    This function is used to set midi channel volume.
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  channel          [in]MIDI channel (0 to 15)
 *  @param  volume           [in]The volume value. (0 to 127)
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of setting channel volume
 *
 */
ven_codec_ret_t ven_codec_setMidiChannelVolume(s32 mediaHandle, u32 channel, u32 volume, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_setMidiProgram
 *  @brief    This function is used to set a program number.

 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  channel          [in]MIDI channel (0 to 15)
 *  @param  bank             [in]The identifier of the sound bank to which the program is set
 *                               (A 14 bit integer that consists of higher 7 bit of the bank select MSB and lower 7 bit of the bank select LSB.)
 *  @param  program          [in]The program number (0 to 127)
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of setting program number
 *
 */
ven_codec_ret_t ven_codec_setMidiProgram(s32 mediaHandle, u32 channel, u32 bank, u32 program, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_sendMidiShortEvent
 *  @brief    This function is used to send a short MIDI message.

 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  type             [in]The status byte of the message
 *  @param  param1           [in]When no parameter is required for the message, 0 is designated
 *  @param  param2           [in]When the message has 1 byte parameter only, 0 is designated
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of sending short event
 *
 */
ven_codec_ret_t ven_codec_sendMidiShortEvent(s32 mediaHandle, u32 type, u32 param1, u32 param2, ven_req_data_t* ptVenReq);


/**
 *  ven_codec_sendMidiLongEvent
 *  @brief    This function is used to send a long MIDI message.

 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pLongEvent       [in]A pointer to the data containing a long event.
 *  @param  length           [in]The size in bytes of the long event data
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of sending long event
 *
 */
ven_codec_ret_t ven_codec_sendMidiLongEvent(s32 mediaHandle, u8* pLongEvent, u32 length, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_playVideo
 *  @brief    This function is used to play the video file with specified parameters.
 *            And the user interface will provided by platform. If vendor needs to take control of
 *            user interface of video player, please contact MStar.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  pURL             [in]The URL is in UCS2 format and in absolute path.
 *                               Note: The memory of this field should be allocated by vender task.
 *                                     And the memory should be freed by vender when the response message is received
 *  @param  URLLen          [in]It is the char length of file URL.
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of playing video request.
 *
 */
ven_codec_ret_t ven_codec_playVideo(s32 mediaHandle, u16 *pURL, u16 URLLen, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_playVideoStreaming
 *  @brief    This function is used to play the video file with specified parameters.
 *            And the user interface will provided by platform. If vendor needs to take control of
 *            user interface of video player, please contact MStar.
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  mediaHandle      [in]Handle returned from ven_codec_openMedia()
 *  @param  URLLen          [in]It is the char length of file URL.
 *  @param  ptVenReq         [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR  if failed
 *
 *
 *  Response structure:
 *
 *    ven_codec_ret_t retCode;      [out]The result of playing video request.
 *
 */
ven_codec_ret_t ven_codec_playVideoStreaming(s32 mediaHandle, ven_codec_videostreaming_req_t * pStreamingVideoReq, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_getVideoStreamingInfo
 *  @brief    This function is used to get streaming progress of temp file.
 *  @param  mediaHandle    [in]Handle returned from ven_codec_openMedia()
    @param  pVideoStreamingInfo  [in] setup the url and url length of query video
 *  @param  ptVenReq       [in]The pointer of vendor request data. This API
                               will not keep the pointer and will not free the memory. It is up to the user to
                               free the memory allocated for the vendor request data.
 *  @retval VEN_CODEC_SUCCESS if success
 *         VEN_CODEC_ERROR  if failed
 *
 *  Response structure:
 *    [sync]
 *    pVideoStreamingInfo->eProgress      [out]The result of given streaming url.
 *    [Async]                           
 *    parameter 2 of async callback is the eProgress of given url.   
 */

ven_codec_ret_t ven_codec_getVideoStreamingInfo(s32 mediaHandle, Ven_Codec_VideoStreamingInfo_t * pVideoStreamingInfo, ven_req_data_t* ptVenReq);
/**
 *  ven_codec_VideoStreamingFileChange
 *  @brief    This function is used to copy/move streaming tmp file.
 *  @param  mediaHandle                [in]Handle returned from ven_codec_openMedia()
    @param  pVideoStreamingFileChange  [in] url and path setting of streaming temp files
 *  @param  ptVenReq       [in]The pointer of vendor request data. This API
                               will not keep the pointer and will not free the memory. It is up to the user to
                               free the memory allocated for the vendor request data.
 *  @retval VEN_CODEC_SUCCESS if success
 *         VEN_CODEC_ERROR  if failed
 *
 *  Support Async only                           
 */
ven_codec_ret_t ven_codec_VideoStreamingFileChange(s32 mediaHandle, Ven_Codec_VideoStreamingFileChange_t * pVideoStreamingFileChange, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_codec_video_status_e eStatus;
    union
    {
        ven_codec_ret_t nResult; //// VEN_MEDIA_VDO_STATUS_PLAY_RESULT
        u32 nPlayTick;           //// VEN_MEDIA_VDO_STATUS_PLAYTICK
    } uInfo;
} ven_codec_play_video_status_t;

ven_codec_ret_t ven_codec_stopVideoStreaming(s32 mediaHandle, ven_req_data_t* ptVenReq);
ven_codec_ret_t ven_codec_setSeekMode(s32 mediaHandle, ven_codec_SeekMode_e eSeekMode, ven_req_data_t* ptVenReq);
ven_codec_ret_t ven_codec_setDownloadInterface(s32 mediaHandle, ven_codec_vdo_streaming_DLItfTbl_t *pDownloadItf, u32 nInitData, ven_req_data_t* ptVenReq);

/**
 *  ven_codec_openImgCodec
 *
 *  @brief  Get a handle of image codec
 *
 *  @param  pImgCodecHandle [out]Handle of image codec.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_openImgCodec(s32 *pImgCodecHandle, ven_req_data_t *ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    s32 imageCodecHandle;
} ven_codec_open_image_codec_rsp_t;

/**
 *  ven_codec_closeImgCodec
 *
 *  @brief  Close a handle of image codec
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_closeImgCodec(s32 imgCodecHandle, ven_req_data_t *ptVenReq);

//close codec rsp, no need for a struct
//ven_codec_ret_t retCode

typedef struct
{
    ven_codec_ret_t retCode;
    s32 imageCodecHandle;
    ven_codec_imageDecodeStatus_t decodeStatus;
} ven_codec_decode_image_rsp_t;

/**
 *  ven_codec_decodeImage
 *
 *  @brief  Decode a given image buffer/file url
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  pBitmap         [in]Pointer to the bitmap to store the decoded image.
 *  @param  pSrcBuf         [in]Pointer to the buffer to decode. Use NULL if you want to decode a file with a given URL
 *  @param  bufSize         [in]Buffer size. Use zero if you want to decode a file with a given URL
 *  @param  pSrcFileURL     [in]Pointer to the URL of the source file to decode. Use NULL if you want to decode a given image buffer
 *  @param  frame           [in]Frame to decode.
 *  @param  pDecodeParam    [in]Pointer to the decode parameter.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_decodeImage(s32 imgCodecHandle,
                                      ven_GraphicsBitmap *pBitmap,
                                      const u8 *pSrcBuf,
                                      u32 bufSize,
                                      u16 *pSrcFileURL,
                                      s32 frame,
                                      ven_codec_decode_param_t *pDecodeParam,
                                      ven_req_data_t *ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;           ///< return code of async callback
    s32 imageCodecHandle;              ///< imageHandle of current action
    u8 *pMem;                          ///< the encoded bitstream buffer. shold be the same addr feeded.
    u32 nMemLen;                       ///< size of encoded bitstream.
} ven_codec_encode_rsp_t;


/**
 *  ven_codec_encodeImage
 *
 *  @brief  Encode a image to a specified image type given in EncParam
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  pEncParam       [in]input parameters of given image.(support for BMP565 only, now)
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_encodeImage(s32 imgCodecHandle,
                                      ven_codec_enc_param_t  *pEncParam,
                                      ven_req_data_t *ptVenReq);

/**
 *  ven_codec_getNextImageFrame
 *
 *  @brief  Get next frame of a decoded image
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_getNextImageFrame(s32 imgCodecHandle, ven_req_data_t *ptVenReq);

typedef struct
{
    ven_codec_ret_t retCode;
    s32 imageCodecHandle;
    ven_codec_imageDecodeStatus_t decodeStatus;
} ven_codec_get_image_next_frame_rsp_t;

/**
 *  ven_codec_getImageInfo
 *
 *  @brief  Get image info a given image buffer/file URL
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  pImgBuf         [in]Pointer to image buffer or file URL
 *  @param  pImgInfo        [out]Pointer to image information
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_getImageInfo(s32 imgCodecHandle, const u8 *pImgBuf, ven_codec_imgInfo_t *pImgInfo);

/**
 *  ven_codec_getImageInfoEx
 *  
 *  @brief  Get image info a given image buffer/file URL. uBufSize is only valid when imge source is not a file.
 *
 *  @param  imgCodecHandle  [in]Handle of image codec.
 *  @param  pImgBuf         [in]Pointer to image buffer or file URL
 *  @param  uBufSize        [in]Image buffer size
 *  @param  pImgInfo        [out]Pointer to image information
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_getImageInfoEx(s32 imgCodecHandle, const u8 *pImgBuf,u32 uBufSize, ven_codec_imgInfo_t *pImgInfo);

/**
 *  ven_codec_setAudioRingBufSize
 *  
 *  @brief  Set the ring buffer size of audio ring buffer.
 *
 *  @param  mediaHandle     [in]Handle of audio codec.
 *  @param  Size            [in]Audio Ring buffer size. the buffer size can not exceed 64K bytes.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_codec_ret_t ven_codec_setAudioRingBufSize(s32 mediaHandle, u32 Size);

/**
*  ven_codec_setAudioRingBufAvailableTimeThreshold
*  
*  @brief  Set the ring buffer available time threshold to trigger play streaming callback. Set before play
*
*  @param  mediaHandle     [in]Handle of audio codec.
*  @param  nTime             [in]Audio Ring buffer available time threshold(ms). 
*
*  @retval VEN_CODEC_SUCCESS if success
*          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
*/
ven_codec_ret_t ven_codec_setAudioRingBufAvailableTimeThreshold(s32 mediaHandle, u32 nTime);

/**
*  ven_codec_macEnable
*  
*  @brief  Enable/Disable Mac, can revive sound by mac and send to play path channel to hear (only support earpieces now)
*          , Enable only operate with earpieces mac phone is available. Disable can use any time 
*
*  @param  imgCodecHandle  [in]Handle of Media handle.
*  @param  bEnable             [in]On/Off the mac phone
*
*  @retval VEN_CODEC_SUCCESS if success
*             VEN_CODEC_ERROR if failed
*             VEN_CODEC_DENY when request is not excusable
*             VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
*/
ven_codec_ret_t ven_codec_macEnable(s32 mediaHandle, bool bEnable);



#endif //__VEN_CODEC_H_

