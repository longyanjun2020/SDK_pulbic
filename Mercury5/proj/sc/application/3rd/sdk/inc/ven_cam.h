/**
 * @file ven_cam.h
 *
 * This file defines the camera/camcorder related request vendor API and
 * MMI response API
 *
 * @version $Id: ven_cam.h 44566 2009-10-30 14:47:24Z code.lin $
 *
 */

#ifndef __VEN_CAM_H_
#define __VEN_CAM_H_

#include "ven_types.h"
#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

///< Macro to calculate buffer size from image width/height
#define CALCULATE_RGB565_BUFFER_SIZE(width, height) (width * height * 2)
#define CALCULATE_YUV420_BUFFER_SIZE(width, height) (width * height * 1.5)

///< Return code
enum
{
    VEN_CAM_OK,
    VEN_CAM_ERROR,
    VEN_CAM_BAD_PARAM,
    VEN_CAM_NO_MEMORY,
    VEN_CAM_SEND_MSG_FAILED,
    VEN_CAM_NOT_SUPPROTED,
};
typedef u32 ven_cam_ret_t;

///< Camera id
enum
{
    VEN_CAM_MAIN, ///< Main camera sensor
    VEN_CAM_SUB,  ///< Sub camera sensor
};
typedef u8 ven_cam_id_t;

///< Camera mode
enum
{
    VEN_CAM_CAMERA,
    VEN_CAM_CAMCORDER,  ///< Not supported now
};
typedef u8 ven_cam_mode_t;

///< Camera capture resolution
enum
{
    VEN_CAM_3264_2448 = 0,  ///< 3264x2448(8M pixel)
    VEN_CAM_3072_2304,      ///< 3072x2304(7M pixel)
    VEN_CAM_3032_2008,      ///< 3032x2008(6M pixel)
    VEN_CAM_2560_1920,      ///< 2560x1920(5M pixel)
    VEN_CAM_2240_1680,      ///< 2240x1680(4M pixel)
    VEN_CAM_2048_1536,      ///< 2048x1536(3M pixel)
    VEN_CAM_1600_1200,      ///< 1600x1200(UXGA)
    VEN_CAM_1280_1024,      ///< 1280x1024(1.3M pixel)
    VEN_CAM_1024_768,       ///< 1024x768
    VEN_CAM_800_600,        ///< 800x600
    VEN_CAM_640_480,        ///< 640x480(VGA)
    VEN_CAM_320_240,        ///< 320x240(QVGA)
    VEN_CAM_240_320,        ///< 240x320
    VEN_CAM_176_220,        ///< 176x220
    VEN_CAM_160_120,        ///< 160x120(QQVGA)
    VEN_CAM_160_112,        ///< 160x112
    VEN_CAM_128_128,        ///< 128x128
    VEN_CAM_96_96,          ///< 96x96
    VEN_CAM_80_64,          ///< 80x64

    VEN_CAM_RES_NUM,
};
typedef u8 ven_cam_capture_res_t;

///< Camera capture quality
enum
{
    VEN_CAM_QUALITY_LOW,
    VEN_CAM_QUALITY_NORMAL,
    VEN_CAM_QUALITY_HIGH,
};
typedef u8 ven_cam_quality_t; ///< Not support now

///< Mode of camera snapshot
enum
{
    VEN_CAM_SINGLE,     ///< Single shot mode
    VEN_CAM_CONSSINGLE, ///< Continuous shot mode, not supported now
};
typedef u8 ven_cam_shot_mode_t;

///< The format of camera capture output
enum
{
    VEN_CAM_YUV420,
    VEN_CAM_RGB565,
};
typedef u8 ven_cam_color_format_t;

///< The storage of camera capture output
enum
{
    VEN_CAM_STORAGE_MEMORY, ///< Capture to memory
    VEN_CAM_STORAGE_FILE,   ///< Capture to file
};
typedef u8 ven_cam_storage_t;

///< Camera config parameter
typedef struct
{
    ven_cam_id_t camId;
    ven_cam_mode_t mode;
} ven_cam_open_param_t;

///< Camera capture parameter
typedef struct
{
    ven_cam_color_format_t format;
    ven_cam_capture_res_t resolution;
    ven_cam_quality_t quality;   ///< Not support now
    ven_cam_storage_t storage;   ///< Support VEN_CAM_STORAGE_MEMORY only now
    union
    {
        struct
        {
            u16 *pPath;     ///< File path in UCS2 format
            u16 pathLen;    ///< Length of file path in character
        } file;             ///< File is not supported

        struct
        {
            u8 *pBuffer;    ///< Pointer to the output buffer
            u32 bufferSize; ///< Buffer size in bytes
        } memory;
    } storageInfo;

} ven_cam_capture_param_t;

///< Camera open response
typedef struct
{
    s32 cameraHandle;
    ven_cam_ret_t retCode;
} ven_cam_open_camera_rsp_t;

///< Camera capture response
typedef struct
{
    ven_cam_ret_t retCode;
    u8 imageIdx; ///< Used for continuous shot mode to indicate the index of current image. Not supported now
} ven_cam_capture_rsp_t;

typedef struct
{
    u16 width;
    u16 height;
    ven_cam_color_format_t format;
    u8 *pBuffer;           ///< Pointer to buffer
    u32 bufferSize;        ///< Buffer size
} ven_cam_source_buffer_param_t;

typedef struct
{
    u16 width;
    u16 height;
    ven_cam_color_format_t format;
    u8 *pBuffer;           ///< Pointer to buffer
    u32 bufferSize;        ///< Buffer size
    u16 x0;                ///< X position in the given buffer
    u16 y0;                ///< Y position in the given buffer
    u16 pitch;             ///< width * 2
} ven_cam_destination_buffer_param_t;

typedef enum
{
    VEN_CAM_PLAYBACK_FALSE = 0,
	VEN_CAM_PLAYBACK_TRUE,
} ven_cam_playback_t;

typedef enum
{
    VEN_CAM_RETURNPATH_FALSE = 0,
	VEN_CAM_RETURNPATH_TRUE,
} ven_cam_returnpath_t;

typedef enum
{
    VEN_CAM_MULTISHOT_FALSE = 0,
	VEN_CAM_MULTISHOT_TRUE,
} ven_cam_multishot_t;

typedef struct
{
    u32                   ThisStructureSize; // in bytes, please set this element to sizeof(ven_cam_launch_app_req_t)
    ven_cam_playback_t    bIsEnterPlaybackMode; // if auto enter MMI picture viewer AP after camera AP
    ven_cam_returnpath_t  bIsReturnFilePath; // if return file path from camera, if yes, Camera/PictureViewer AP will return file path then be closed automatically
    ven_cam_multishot_t   bIsMultiShotSupport; // if support multishot, if yes && bIsReturnFilePath ==TRUE, rsp structure will return total file num and file path will be packed.
} ven_cam_launch_app_req_t;

typedef struct
{
    u8        nNumOfPhotoOrVideo;
    u16       *pFileName;
} ven_cam_launch_app_rsp_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_cam_openCamera
 *
 *  @brief  Get a handle of camera
 *          Note: This function supports both synchronous and asynchronous
 *
 *  @param  pCamHandle      [out]Handle of camera.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_openCamera(s32 *pCamHandle, ven_cam_open_param_t *pOpenParam, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_closeCamera
 *
 *  @brief  Close a handle of camera
 *          Note: This function supports both synchronous and asynchronous
 *
 *  @param  camHandle       [in]Handle of camera.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_closeCamera(s32 camHandle, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_startPreview
 *
 *  @brief  Start to preview with the given camera handle
 *          Note: This function supports both synchronous and asynchronous
 *
 *  @param  camHandle       [in]Handle of camera.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_startPreview(s32 camHandle, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_startPreview
 *
 *  @brief  Stop current preview with the given camera handle
 *          Note: This function supports both synchronous and asynchronous
 *
 *  @param  camHandle       [in]Handle of camera.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_stopPreview(s32 camHandle, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_captureImage
 *
 *  @brief  Camture image via a opened camera handle
 *          Note: This function supports asynchronous only
 *                This function must be used after ven_cam_startPreview() is called
 *
 *  @param  camHandle       [in]Handle of camera.
 *  @param  pCaptureParam   [in]Capture parameter
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_captureImage(s32 camHandle, ven_cam_capture_param_t *pCaptureParam, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_convertImage
 *
 *  @brief  Camture image via a opened camera handle
 *          Note: This function supports asynchronous only
 *                This function must be used after ven_cam_openCamera() is called
 *
 *  @param  camHandle       [in]Handle of camera.
 *  @param  pSouceBufParam  [in]Pointer of source buffer parameter
 *  @param  pDestBufParam   [in]Pointer of destination buffer parameter
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_convertImage(s32 camHandle, ven_cam_source_buffer_param_t *pSouceBufParam, ven_cam_destination_buffer_param_t *pDestBufParam, ven_req_data_t *ptVenReq);

/**
 *  ven_cam_launchApplet
 *
 *  @brief  Launch MMI camera applet
 *          Note: This function supports asynchronous only
 *
 *  @param  pLaunchReqData  [in]Pointer of request data
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_CODEC_SUCCESS if success
 *          VEN_CODEC_ERROR if failed
 *          VEN_CODEC_BAD_PARAMETERS if input parameter is invalid
 */
ven_cam_ret_t ven_cam_launchApplet(ven_cam_launch_app_req_t *pLaunchReqData, ven_req_data_t *ptVenReq);
#endif //__VEN_CAM_H_

