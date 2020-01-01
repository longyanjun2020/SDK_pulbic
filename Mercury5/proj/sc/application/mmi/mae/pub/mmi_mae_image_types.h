/**
 * @file mmi_mae_image_types.h
 *
 * @version $Id: mmi_mae_image_types.h $
 */
#ifndef __MMI_MAE_IMAGE_TYPES_H__
#define __MMI_MAE_IMAGE_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_image_forward.h"

#define IMG_AUTODECODE_DEFAULT   TRUE
#define IMG_NEXT_FRAME     -1
#define IMG_CURRENT_FRAME  -2

enum ImgParam_e_
{
	IMG_PARM_SET_SRC_BUF = 0x10,  	///< Set source buffer to IImage, c1:buffer pointer, c2:buffer size
	IMG_PARM_SET_SRC_URL,         	///< Set source URL to IImage, c1:UCS2 filename pointer, c2:unused

	IMG_PARM_SET_SRC_STREAM,      	///< Set source IStream to IImage, c1:IAStream pointer, c2:unused
	IMG_PARM_SET_PFNBUFFREE,     	///< Set free function pointer used to free source buffer, this function is used only when the source buffer is set. c1:PfnMAE_ImgBuffer, c2:unused
	IMG_PARM_SET_DISPLAY,			///< Set IDisplay to IImage, c1:IDisplay pointer, c2:unused
	IMG_PARM_SET_DECODE_PARM,    ///< Set decode size and rotate angle. xy size set to 0 to reset to original image size. Rotate angle only support 0, 90, 180, and 270 degree in clockwise direction. other values mean no change. c1:ImageDecodeParm_t, c2:unused

	IMG_PARM_SET_DECODE_SIZE,     	///< Set decode size, parameters set to 0 to reset to original image size, c1:width, c2:height
	IMG_PARM_SET_ROTATE_ANGLE,    ///< Set decode rotate angle, only support 0, 90, 180, and 270 degree in clockwise direction, c1:ImgDecAngle_t, c2:unused

	IMG_PARM_REG_NOTIFY,    		///< Register notification function, c1:PfnMAE_ImgNotify, c2:IBase*, caller instance
	IMG_PARM_DEREG_NOTIFY,   		///< Deregister notification function, c1:PfnMAE_ImgNotify, c2:IBase*, caller instance

	IMG_PARM_AUTODECODE,          	///< IImage will start decode after source buffer is ready if this IMG_PARM_AUTODECODE is set to TRUE, c1:boolean, c2:unused

	IMG_PARM_DECODEONDRAW,		///< IImage will decode before draw frame and release bitmap after draw if this IMG_PARM_DECODEONDRAW is set to TRUE, c1:boolean, c2:unused
	IMG_PARM_FREE_DECODE_BUFFER,
	IMG_PARM_CLEAR_SRC_BUFFER,
	IMG_PARM_FORCE_ASYNC, ///< Force use asynchronous decoder
	IMG_PARM_SET_DELAY_TIME, ///< Set the delay time that a frame is displayed in an animation to IImage object
	IMG_PARM_SET_CAN_USE_PALETTE_OUTPUT, ///< Set if the image can use palette output, this is 8 bit color format
        IMG_PARM_STEREO_TYPE,
        IMG_PARM_DEC_PARM_STEREO,
	IMG_PARM_LAST
};

enum ImgCodecProperty_e_
{
	IMG_PROP_IMG_INFO = 0,    ///< image info
	IMG_PROP_IMG_FORMAT,       ///< image format
	IMG_PROP_IMG_SIZE,        ///< image size (width and height)
	IMG_PROP_DEC_PARAM,       ///< current decode parameters
	IMG_PROP_DEF_DEC_SIZE,    ///< default decode size
	IMG_PROP_STATUS,
	IMG_PROP_ERROR_CODE,
	IMG_PROP_ANIM_STATUS,
	IMG_PROP_IS_ANIMATION,
	IMG_PROP_TOTAL
};

enum ImgDecAngle_e_
{
	IMG_DEC_ANGLE_0 = 0,
	IMG_DEC_ANGLE_90,
	IMG_DEC_ANGLE_180,
	IMG_DEC_ANGLE_270,
	IMG_DEC_ANGLE_TOTAL
};

enum ImgStatus_e_
{
	IMG_STAT_CDC_START = 0,
	IMG_STAT_CDC_INIT = IMG_STAT_CDC_START,
	IMG_STAT_CDC_READY_TO_DEC,
	IMG_STAT_CDC_DECODING,
	IMG_STAT_CDC_DONE,
	IMG_STAT_CDC_FRAME_TIMEOUT,
	IMG_STAT_CDC_ERROR,
	IMG_STAT_CDC_TOTAL,
	IMG_STAT_ANIM_START,
	IMG_STAT_ANIM_STOP
};

enum ImgDecStereo_tag
{
    IMG_STEREOTYPE_NONE = 0,
    IMG_STEREOTYPE_RED_CYAN,
    /* */
    IMG_STEREOTYPE_NUM
};
typedef u32 ImgDecStereo_e;

enum ImgAnimState_e_
{
	IMG_ANIM_STOP = 0,
	IMG_ANIM_START,
	IMG_ANIM_PLAYING
};

enum ImgInfoType_e_
{
	IMG_IMAGE_INFO = 0,
	IMG_DECODE_INFO
};

// Image decode error code
enum ImgCDCMsg_e_
{
	IMG_CDC_MSG_JPD_RES_NOT_SUPPORT              = -8,
	IMG_CDC_MSG_RE_ENTRY_ABORT                   = -7,
	IMG_CDC_MSG_BAD_PARAMETERS                   = -6,    /**< Bad parameters*/
	IMG_CDC_MSG_WRONG_HANDLE                     = -5,    /**< Image decode wrong decode handle */
	IMG_CDC_MSG_NOT_ENOUGH_MEMORY                = -4,    /**< Image decode memory not enough*/
	IMG_CDC_MSG_TOO_MUCH_EXECUTING_INSTANCE      = -3,    /**< Image decode too much executing instance*/
	IMG_CDC_MSG_DEC_ERR                          = -2,    /**< Image decode error*/
	IMG_CDC_MSG_FORMAT_UNSUPPORT                 = -1,    /**< Image decode format not support*/
	IMG_CDC_MSG_ERROR                            =  0,     /**< Image decode error ( keep this be 0)*/
	IMG_CDC_MSG_SUCCESS,                                  /**< Image decode success = 1*/
	IMG_CDC_MSG_SUCCESS_WAITING,                          /**< By Montage, caller wait for IMGCODEC_MSG_DECODE_DONE or IMGCODEC_MSG_CDC_MSG or callback function*/
	IMG_CDC_MSG_SUCCESS_MORE_FRAMES,                      /**< GIFA, Caller wait for IMGCODEC_MSG_UPDATE_GIFA message.*/
	IMG_CDC_MSG_SUCCESS_ABORTED,                          /**< Image Decoding is Done (aborted)*/
	IMG_CDC_MSG_READ_FILE_FAIL					 = 0X20,
	IMG_CDC_MSG_IMAGE_FINALIZE_DECODE_FAIL,

};

struct ImageSize_t_
{
	u32         nWidth;          ///< Image width
	u32         nHeight;         ///< Image height
};

enum ImgFormat_e_
{
	IMG_FORMAT_UNKNOWN = 0,
	IMG_FORMAT_BMP,
	IMG_FORMAT_PNG,
	IMG_FORMAT_GIF,
	IMG_FORMAT_JPG,
	IMG_FORMAT_PROGRESSIVE_JPG,
	IMG_FORMAT_WAPBMP,
	IMG_FORMAT_TOTAL,
};

struct ImageInfo_t_
{
	u32         nWidth;          ///< Image width
	u32         nHeight;         ///< Image height
	u32         nFrames;         ///< Frames in the image
	ImgFormat_e   nFormat;         ///< image format
};

struct ImageRegion_t_
{
	u16                x;
	u16                y;
	u16                nWidth;
	u16                nHeight;
};

struct ImageDecodeParm_t_
{
	u32         nWidth;          ///< Output width
	u32         nHeight;         ///< Output height
	ImgDecAngle_e  nAngle;       ///< Decode angle
	//partial decode parameters
	//for visible region of decode width and height
	ImageRegion_t tRegion;
};

struct ImageDefaultDecParm_t_
{
	ImgDecAngle_t nDecAngle;      ///< decode angle
	ImageSize_t   tDefSize;      ///< default decode size according to DecAngle
};

struct ImageStatus_t_
{
	ImgStatus_e  nStatus;        ///< Image status
	u32          nCurFrame;     ///< current frame decoded/decoding in the buffer
	u32          nFrames;        ///< total frames
	u32          nDelayTime;    ///< delay time of current frame, valid when frames>1
};

#endif /* __MMI_MAE_IMAGE_TYPES_H__ */
