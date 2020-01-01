/**
 *
 * @file    isl_gss_itf.h
 *
 * @brief   This module defines the GSS Interfal Serivce Layer for platform usage
 *
 * @author  Jack Hsieh
 * @version $Id: isl_gss_itf.h 12573 2008-07-17 06:26:10Z jack.hsieh $
 *
 */
#ifndef __ISL_GSS_ITF_H__
#define __ISL_GSS_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ISL_GSS_ITF__
#define	DefExtern
#else
#define	DefExtern	extern
#endif

#define ISL_GSS_OSD_RGB565_TRANS_COLOR    0x0821     /**< Default transparancy OSD magenta in RGB565 format */
#define ISL_GSS_OSD_RGB8888_TRANS_COLOR   0xFF080408 /**< Default transparancy OSD magenta in RGB8888 format */

#if 0
/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define isl_GSS_ClearBurst() {*(volatile u16*)(EBI_CS1_BASE_ADD) = 0x0000;}


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief Isl GSS return error code, mapping to 'image_codec' definition
 */
typedef enum {
  ISL_GSS_PARAMETER_ERROR  = (s32)-6,   /**< Bad parameters*/
  ISL_GSS_WRONG_HANDLE,                 /**< Gss image decode wrong decode handle */
  ISL_GSS_NOT_ENOUGH_MEMORY,            /**< Gss image decode memory (output buffer ?) not enough*/
  ISL_GSS_TOO_MUCH_EXECUTING_INSTANCE,  /**< Gss image decode too much executing instance*/
  ISL_GSS_DEC_ERR,                      /**< Gss image decode error*/
  ISL_GSS_FORMAT_UNSUPPORT,             /**< Gss image decode format not support*/
  ISL_GSS_FAIL,                         /**< Gss image decode error ( keep this be 0)*/
  ISL_GSS_OK,                           /**< Gss image decode success = 1*/
  ISL_GSS_SUCCESS_WAITING,              /**< By Montage, caller wait for IMGCODEC_MSG_DECODE_DONE or IMGCODEC_MSG_ERROR or callback function*/
  ISL_GSS_SUCCESS_MORE_FRAMES,          /**< GIFA, Caller wait for IMGCODEC_MSG_UPDATE_GIFA message*/
  ISL_GSS_REJECT,                       /**< Request reject because of other function's confliction */
  ISL_GSS_ABORT                         /**< Request abort because of incorrect sequence */
} isl_GssErrCode_e;

/**
 *  @brief Gss isl layer define
 */
typedef enum {
    ISL_GSS_LAYER_G0 = 0,			/**< Gss G0 Layer */
    ISL_GSS_LAYER_G1,					/**< Gss G1 Layer */
    ISL_GSS_LAYER_V0,					/**< Gss V0 Layer */
    ISL_GSS_LAYER_ICP,				/**< Gss ICP Layer */
    ISL_GSS_LAYER_MAX
} isl_GssLayer_e;

/**
 *  @brief Gss isl rotate value define
 */
typedef enum {
    ISL_GSS_ROTATE_0 = 0,				/**< Rotate angle 0 degree */
    ISL_GSS_ROTATE_90,			    /**< Rotate angle 90 degree */
    ISL_GSS_ROTATE_180,		      /**< Rotate angle 180 degree */
    ISL_GSS_ROTATE_270,		      /**< Rotate angle 270 degree */
    ISL_GSS_ROTATE_MAX
} isl_GssRotateAngle_e;

/**
 *  @brief Gss isl jpeg decode back define
 */
typedef enum {
    ISL_GSS_JPEG_DECODE_BACK = 0,								/**< Jpeg decode back to BB */
    ISL_GSS_JPEG_DECODE_NOBACK,									/**< Jpeg decode not back to BB (direct display) */
    ISL_GSS_IMAGE_DECODE_BACK                   /**< Other decode file*/
} isl_GssGetBackChk_e;

/**
 *  @brief Gss isl write read command define
 */
typedef enum {
    ISL_GSS_BYPASS_WRITE = 0,										/**< Main display bypass write */
    ISL_GSS_BYPASS_READ,												/**< Main display bypass read */
    ISL_GSS_BYPASS_WRITE_COLOR_EXPAND
} isl_GssMainByPass_e;

/**
 *  @brief Gss isl bypass bridge
 */
typedef enum {
    ISL_GSS_BYPASS_MODE = 0,					/**< Set mode to bypass mode */
    ISL_GSS_BRIDGE_MODE,							/**< Set mode to bridge mode */
} isl_GssSwithMode_e;

/**
 *  @brief Gss isl decode type
 */
typedef enum {
    ISL_GSS_DECODE_FILE = 0,					/**< Decode file  */
    ISL_GSS_DECODE_DATA,							/**< Deacode data (streaming) */
} isl_GssDecodeType_e;

/**
 *  @brief Gss LCD update defination
 */
typedef enum {
    ISL_GSS_LCD_UPDATE_OSD = 0,					    /**< Set update mode to OSD */
    ISL_GSS_LCD_UPDATE_RENDER,              /**< Set update mode to MMP Render mode */
    ISL_GSS_LCD_UPDATE_BRIDGE,              /**< Set update mode to bridge, directly write buffer to base layer */
    ISL_GSS_LCD_UPDATE_BYPASS,							/**< Set update mode to bypass */
    ISL_GSS_LCD_UPDATE_DISP,
    ISL_GSS_LCD_UPDATE_NONE                 /**< Set reject update mode */
} isl_GssLcdUpdateMode_e;

/**
 *  @brief The enumeration defines the Gss render type
 */
typedef enum {
  ISL_GSS_RENDER_PALETTE,        /**< PALETTE render type */
  ISL_GSS_RENDER_MAX             /**< maximum render type */
} isl_GssRenderType_e;

/**
 *  @brief The structure defines the window area property
 */
typedef struct
{
    u16     x;          /**< Horizontal position of top-left */
    u16     y;          /**< Vertical position of top-left */
    u16     width;      /**< Horizontal width */
    u16     height;     /**< Vertical height */
} isl_GssRegion_t;

/**
 *  @brief Jpeg gss parameter structure definition
 */
typedef struct {
    isl_GssDecodeType_e   decodeTyp;        /**< Jpeg decode type*/
    isl_GssRegion_t       scaleRegion;       /**< Jpeg scale size region (current only use width and height */
    isl_GssRotateAngle_e  rotateAngle;      /**< Jpeg decode define rotate angle */
    isl_GssGetBackChk_e   getBackChk;       /**< Jpeg decode get back or no get back flag */
    u8                    *bmpDataPtr;      /**< Jpeg decode get back bitmap decode buffer */
    u32                   outPutLen;        /**< Decode get back bitmap buffer length */
    u32                   scaleStride;      /**< Decode scale stride (width bytes)*/
    u16                   *fileNamePtr;     /**< Jpeg decode file name pointer (UCS2) */
    u16                   fileNameLength;   /**< Jpeg decode file name length (UCS2) */
    u8                    orientation;      /**< Jpeg decode orientation */
    u8                    *pData;           /**< Image decode data pointer (only support in Big2?) */
    u32                   dataLength;       /**< Image decode data length */
} isl_GssJpegParam_t;


typedef struct {
	u8											*pBuffer;
	u32											bufferLen;
}isl_GssJpegPngMem_t;


typedef struct {
    isl_GssRegion_t       scaleRegion;       /**< Jpeg scale size region (current only use width and height */
    isl_GssRotateAngle_e  rotateAngle;      /**< Jpeg decode define rotate angle */
		isl_GssJpegPngMem_t		input;
		isl_GssJpegPngMem_t		output;
		isl_GssJpegPngMem_t		pngInput;
		isl_GssJpegPngMem_t		pngOutput;
    u32                   scaleStride;      /**< Decode scale stride (width bytes)*/
} isl_GssJpegPngParam_t;



/**
 *  @brief Gss get picture info parameter structure definition
 */
typedef struct {
    u8                  *bufferPtr;        /**< Return information buffer point (>12 bytes) */
    u32                 bufferLens;       /**< Information buffer length */
    u16                 *fileNamePtr;     /**< File name pointer (UCS2)currently support jpg, bmp ,png and gif*/
    u16                 fileNameLength;   /**< File name length (UCS2)*/
    isl_GssErrCode_e    *resultPtr;       /**< Point to the storage of the result of get picture info operation */
} isl_GssGetPicInfoParam_t;

/**
 *  @brief Bmp gss parameter structure definition
 */
typedef struct {
isl_GssRegion_t       bmpRegion;        /**< Bmp draw region */
u8 			  					 *writeBmpPtr;			/**< Bmp drawing data buffer point */
u32 							  	writeBmpLen;			/**< Bmp drawing data length */
isl_GssRotateAngle_e	rotateAngle;			/**< Bmp drawing rotate angle (0~3) */
u16									  transColor;				/**< Bmp drawing transparent 16 bit color*/
bool                  isSetTrans;				/**< Bmp drawing transparent set flag*/
bool                  isDirectMode;     /**< Bmp drawing using direct drawing mode or command mode flag*/
} isl_GssDrawBmpParam_t;


/**
 *  @brief Bmp gss parameter structure definition
 */
typedef struct {
u8 			  					 *pNesBuffer;			/**< Direct drawing data buffer point */
u32 							  	bufferLens;			/**< Direct drawing data length */
} isl_GssNesDirectDrawParam_t;

/**
 *  @brief The structure defines the render configuration
 */
typedef struct {
  isl_GssRenderType_e   type;       /**< Render type */
  isl_GssRegion_t       region;     /**< Render region */
  union {
  isl_GssNesDirectDrawParam_t nesDrawParam;
  }param;
} isl_GssRenderParam_t;


/**
 *  @brief Jpeg response structure definition
 */
typedef struct  {
 u8     *pBuffer;         /**< Jpeg respone buffer pointer */
 u32    bufferLen;        /**< Jpeg respone buffer length */
 u8     *pData;           /**< Jpeg respone data pointer (decode data) */
 u32    dataLen;          /**< Jpeg respone data length */
} isl_GssImgInfo_t;

/**
 *  @brief Esl get reponse structure definition
 */
typedef struct {
  union {
    isl_GssImgInfo_t   gssImgInfo;       /**< Imgae decode response */
  } param;
} isl_GssInfo_t;

/**
 *  @brief Esl call back function definition
 */
typedef void (*islGssCb)(u16 senderID, u32 userValue, isl_GssErrCode_e status, isl_GssInfo_t *pGssInfo);

/**
 *  @brief Esl call back function structure definition
 */
typedef struct {
  u16           senderID;       /**< Task id of sender */
  u32           userValue;      /**< userValue of sender for checking msg response */
  islGssCb      pfnCb;          /**< Done call back function that called by EMA */
} isl_GssCb_t;

#endif
/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

//isl_GssErrCode_e isl_GSS_JpegPngDecodeReq(isl_GssJpegPngParam_t gssJpngParam, isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss jpeg decode
 *
 * @param  gssJpegParam				   			  : [in] Gss jpeg parameter
 * @param  pGssDoneCB									  : [in] Gss done call back structure point
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_JpegDecodeReq(isl_GssJpegParam_t gssJpegParam, isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss select ICP windows region with rotate angle
 *
 * @param  RWSelect				   			      : [in] Gss main diplay bypass set
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_SelectMainDispBypass(isl_GssMainByPass_e RWSelect);


/**
 * @brief EMA gss bridge and bypass mode switch
 *
 * @param  ModeSelect			   			      : [in] Gss mode select
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_BridgeBypassSwitch(isl_GssSwithMode_e modeSelect);


/**
 * @brief EMA gss draw bmp function
 *
 * @param  LayerID				   					  : [in] Gss set layer id
 * @param  gssDrawBmpParam 			        : [in] Gss draw bmp parameter
 * @param  pGssDoneCB							  		: [in] Gss done call back structure point
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_DrawBmpReq(isl_GssLayer_e LayerID, isl_GssDrawBmpParam_t  gssDrawBmpParam, isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss render lcd function
 *
 * @param  pRenderParam				   				: [in] Gss render parameter
 * @param  pGssDoneCB							  		: [in] Gss done call back structure point
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_RenderReq(isl_GssRenderParam_t *pRenderParam, isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss diable layer
 *
 * @param  LayerID				   					  : [in] Gss set layer
 * @param  pGssDoneCB									  : [in] Gss done call back structure point
 *
 * @return ISL_GSS_OK       				    : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_DisableLayerReq(isl_GssLayer_e LayerID,  isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss get picture info
 *
 * @param  pGetPicInfoParam             : [in] Gss get pic info parameter pointer
 * @param  pGssDoneCB                   : [in] Gss done call back structure point
 *
 * @return ISL_GSS_OK                   : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_GetPicInfoReq(isl_GssGetPicInfoParam_t *pGetPicInfoParam, isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss check update device
 *
 * @return ISL_GSS_LCD_UPDATE_OSD       			: Gss need to load osd
 * @return ISL_GSS_LCD_UPDATE_BYPASS          : Gss only need local updat screen
 * @return ISL_GSS_LCD_UPDATE_NONE            : LCD no need update screen
 */
//isl_GssLcdUpdateMode_e isl_GSS_CheckUpdateDev(void);


/**
 * @brief This function is used to decode partial image (jpeg, bmp and png format)
 *
 * @param   gssJpegParam                            : [in] Gss jpeg parameter
 * @param   pGssDoneCB                              : [in] Gss done call back structure point
 *
 * @return  ISL_GSS_PARAMETER_ERROR               : Bad parameters
 * @return  ISL_GSS_WRONG_HANDLE,                 : Gss image decode wrong decode handle
 * @return  ISL_GSS_NOT_ENOUGH_MEMORY,            : Gss image decode memory (output buffer ?) not enough
 * @return  ISL_GSS_TOO_MUCH_EXECUTING_INSTANCE,  : Gss image decode too much executing instance
 * @return  ISL_GSS_DEC_ERR,                      : Gss image decode error
 * @return  ISL_GSS_FORMAT_UNSUPPORT,             : Gss image decode format not support
 * @return  ISL_GSS_FAIL,                         : Gss image decode error ( keep this be 0)
 * @return  ISL_GSS_OK,                           : Gss image decode success = 1
 * @return  ISL_GSS_SUCCESS_WAITING,              : By Montage, caller wait for IMGCODEC_MSG_DECODE_DONE or IMGCODEC_MSG_ERROR or callback function
 * @return  ISL_GSS_SUCCESS_MORE_FRAMES,          : GIFA, Caller wait for IMGCODEC_MSG_UPDATE_GIFA message
 * @return  ISL_GSS_REJECT,                       : Request reject because of other function's confliction
 * @return  ISL_GSS_ABORT                         : Request abort because of incorrect sequence
 */
//isl_GssErrCode_e isl_GSS_PartialDecodeReq(isl_GssJpegParam_t *pDecodeParam,isl_GssRegion_t *pRegion , isl_GssCb_t *pGssDoneCB);


/**
 * @brief EMA gss decode abort interface
 *
 * @param  NONE
 *
 * @return ISL_GSS_OK                   : Gss set success
 * @return ISL_GSS_FAIL                 : Gss set fail
 * @return ISL_GSS_PARAMETER_ERROR      : Gss set parameter error
 */
//isl_GssErrCode_e isl_GSS_DecodeAbort(void);

#endif /* __ISL_GSS_ITF_H__ */

