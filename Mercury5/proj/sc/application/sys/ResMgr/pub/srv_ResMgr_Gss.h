/**
* @file srv_ResMgr_Gss.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of GSS.
*
*/

#ifndef __SRV_RESMGR_GSS_H__
#define __SRV_RESMGR_GSS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_gss_itf.h"
#include "mdl_imgcodec_main.h"
#include "isl_gss_itf.h"
#include "srv_resmgr_mmlimage_types.h"
#include "srv_resmgr_mmlgame_types.h"
#include "srv_resmgr_mmlvideosdk_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define ABL_AVP_CODEC_4CC(a, b, c, d) \
            (((u32) (a) << 24) | ((u32) (b) << 16) | \
             ((u32) (c) <<  8) | ((u32) (d)))

enum ABL_AVP_CODEC_TYPE
{
    ABL_VIDEO_CODEC_I420    = ABL_AVP_CODEC_4CC('i','4','2','0'),
    ABL_VIDEO_CODEC_RGB565  = ABL_AVP_CODEC_4CC('r','g','b', 16),
};

typedef MmlVideoSdkOpenColorConverter_t   ABL_GssCmdOpenColorConvert_t;
typedef MmlVideoSdkConvertColor_t         ABL_GssCmdConvertColor_t;

typedef struct ABL_AvpRect_s
{
    u16                x;
    u16                y;
    u16                w;
    u16                h;
} ABL_AvpRect_s;

typedef struct ABL_VideoFrame_s
{
    u8      version;
    u8      *data[4];
    s32     stride[4];
    s32     pts;        /* unit: ms */
    ABL_AvpRect_s   dispArea;
    void    *opaque;     /* callback data */
} ABL_VideoFrame_st;

typedef struct ABL_GssConvertColor_t_
{
    u32                 uHandle;
    ABL_VideoFrame_st *FrameInput;
    ABL_VideoFrame_st *FrameOutput;
} ABL_GssConvertColor_t;

typedef struct ABL_AvpVideoConfig_s
{
    u8      version;
    u32     codecType;  /* only I420 is available for now */
    u16     width;
    u16     height;
    u32     frameRateNum;
    u32     frameRateDen;
    u8      tsType;
    u8      *configData; /* codec specific config data*/
    s32     configLen;
}ABL_AvpVideoConfig_st;

typedef struct ABL_VdoStartConvert_t_
{
    u32                     uHandle;
    ABL_AvpVideoConfig_st   *ConfigInput;
    ABL_AvpVideoConfig_st   *ConfigOutput;
} ABL_GssOpenConvert_t;

/**
 *  @brief The sturcture defines the return information of video media file
 */
typedef struct {
  union {
    u32                 uHandle;
  } param;
} ABL_GssConvertInfo_t;


/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef esl_GssFileInfo_t ABL_GssFileInfo_t;
typedef esl_GssEXIF_Info_t ABL_GssEXIF_Info_t;

typedef struct ABL_GssSetEXIF_Cmd_t_
{
    esl_GssFileInfo_t  fileParam;
    esl_GssEXIF_Info_t exifInfo;
} ABL_GssSetEXIF_Cmd_t;

typedef enum ABL_GssStoragePath_e_
{
    ABL_GSS_PATH_DIR,     /**< MMI decide folder only */
    ABL_GSS_PATH_PREFIX,  /**< MMI decide pre-fix of file name   */
    ABL_GSS_PATH_ABSOLUTE /**< MMI give full folder path and file name   */
} ABL_GssStoragePath_e;

typedef MmlImageInfo_t                  ABL_GssImageInfo_t;
typedef MmlImageDecodeCompleteInfo_t    ABL_GssImageDecodeCompleteInfo_t;
typedef MmlImageDecodingCapability_t    ABL_GssImageDecodingCapability_t;
typedef MmlImageGetDecodingCapability_t ABL_GssImageGetDecodingCapability_t;
typedef MmlGameEmuGameInfo_t            ABL_GameInfo_t;
typedef MmlGameCapability_t             ABL_GameCapability_t;

typedef struct {
  union {
    esl_GssBufferInfo_t                 decodeBuffInfo;             /**< Gss decode 1st frame buffer information response */
    esl_GssBufferInfo_t                 encodeBuffInfo;             /**< Gss encode Dst buffer information response */
    esl_GssBufferInfo_t                 gameStatusInfo;             /**< EMU game status buffer information response */
    u32                                 nEmuHashData;               /**< EMU game hash data */
    u32                                 nEmuVersion;                /**< EMU version b31~b16 is major version number, b16~b0 is minor version number */
    u32                                 nEmuStatusSize;             /**< EMU Game Status Buffer Size */
    u32                                 nHandle;                    /**< Gss decoder handle from MML middle ware */
    ABL_GameCapability_t                tEmuGameCapability;
    ABL_GssImageInfo_t                  tImageInfo;                 /**< Gss decoder image info from MML middle ware */
    ABL_GssImageDecodeCompleteInfo_t    tDecodeCompleteInfo;        /**< Gss decode complete info */
    ABL_GssImageDecodingCapability_t    tImageDecodingCapability;   /**< GSS image decoding capability info */
    ABL_GameInfo_t                      tEmuInfo;
  } param;
} ABL_GssInfo_t;

typedef struct  {
    u8     *pBuffer;         /**< Jpeg respone buffer pointer */
    u32    bufferLen;        /**< Jpeg respone buffer length */
    u8     *pData;           /**< Jpeg respone data pointer (decode data) */
    u32    dataLen;          /**< Jpeg respone data length */
} ABL_GssImgInfo_t;

typedef struct {
  union {
    ABL_GssImgInfo_t   gssImgInfo;       /**< Imgae decode response */
  } param;
} ABL_GssInfoExt_t;

typedef PMSSURFACE ABL_GSSPMSSurface_t;
typedef MSSURFACE  ABL_GssMSSurface_t;
typedef esl_GssRenderConfig_t ABL_GssRenderConfig_t;
typedef esl_GssRenderStopConfig_t ABL_GssRenderStopConfig_t;
typedef esl_GssRenderInput_t ABL_GssRenderInput_t;
typedef esl_GssGetInfoParam_t ABL_GssGetInfoParam_t;
typedef esl_GssEncodeSetting_t ABL_GssEncodeSetting_t;
typedef Image_RotationAngle ABL_GssRotateAngle_e;
typedef esl_GssBufferInfo_t ABL_GssBufferInfo_t;
typedef esl_GssRegion_t ABL_GssRegion_t;
typedef esl_Gss_PaletteConfig_t ABL_Gss_PaletteConfig_t;
typedef esl_Gss_EmuConfig_t ABL_Gss_EmuConfig_t;

typedef Image_decodeParm_t ABL_GssDecodeParam_t;

typedef enum ABL_GssErrCode_e_
{
    ABL_GSS_NOT_SUPPORT = (s32)-9,
    ABL_GSS_JPD_RES_NOT_SUPPORT = (s32)-8,    //IMAGE_JPD_RES_NOT_SUPPORT(-8)
    ABL_GSS_RE_ENTRY_ABORT,                   //IMAGE_RE_ENTRY_ABORT(-7)
    ABL_GSS_BAD_PARAMS,                       //IMAGE_BAD_PARAMETERS(-6)                  ESL_GSS_PARAMETER_ERROR(-6)               ISL_GSS_PARAMETER_ERROR(-6)
    ABL_GSS_WRONG_HANDLE,                     //IMAGE_WRONG_HANDLE(-5)                    ESL_GSS_WRONG_HANDLE(-5)                  ISL_GSS_WRONG_HANDLE
    ABL_GSS_NOT_ENOUGH_MEMORY,                //IMAGE_NOT_ENOUGH_MEMORY(-4)               ESL_GSS_NOT_ENOUGH_MEMORY(-4)             ISL_GSS_NOT_ENOUGH_MEMORY
    ABL_GSS_TOO_MUCH_EXECUTING_INSTANCE,      //IMAGE_TOO_MUCH_EXECUTING_INSTANCE(-3)     ESL_GSS_TOO_MUCH_EXECUTING_INSTANCE(-3)   ISL_GSS_TOO_MUCH_EXECUTING_INSTANCE
    ABL_GSS_DEC_ERR,                          //IMAGE_DEC_ERR(-2)                         ESL_GSS_DEC_ERR(-2)                       ISL_GSS_DEC_ERR
    ABL_GSS_FORMAT_UNSUPPORT,                 //IMAGE_FORMAT_UNSUPPORT(-1)                ESL_GSS_FORMAT_UNSUPPORT(-1)              ISL_GSS_FORMAT_UNSUPPORT
    ABL_GSS_FAIL,                             //IMAGE_ERROR(0)                            ESL_GSS_FAIL(0)                           ISL_GSS_FAIL
    ABL_GSS_OK,                               //IMAGE_SUCCESS(1)                          ESL_GSS_OK(1)                             ISL_GSS_OK
    ABL_GSS_SUCCESS_WAITING,                  //IMAGE_SUCCESS_WAITING(2)                  ESL_GSS_SUCCESS_WAITING(2)                ISL_GSS_SUCCESS_WAITING
    ABL_GSS_SUCCESS_MORE_FRAMES,              //IMAGE_SUCCESS_MORE_FRAMES(3)              ESL_GSS_SUCCESS_MORE_FRAMES(3)            ISL_GSS_SUCCESS_MORE_FRAMES
    ABL_GSS_REJECT,                           //                                          ESL_GSS_REJECT(4)                         ISL_GSS_REJECT
    ABL_GSS_ABORT,                            //                                          ESL_GSS_ABORT(5)                          ISL_GSS_ABORT
    ABL_GSS_FILE_CORRUPT,                     //                                          ESL_GSS_FILE_CORRUPT(6)
    ABL_GSS_FILE_NOT_EXIST,                   //                                          ESL_GSS_FILE_NOT_EXIT(7)
    ABL_GSS_FILE_SIZE_OVERFLOW,               //                                          ESL_GSS_FILE_SIZE_OVERFLOW(8)
    ABL_GSS_DENY,
    ABL_GSS_MERGE,
    ABL_GSS_OUT_OF_MEMORY,
    ABL_GSS_INCORRECT_EMU_ENGINE_VERSION,
    ABL_GSS_NO_EMU_ENGINE
} ABL_GssErrCode_e;

typedef struct
{
    ABL_GssErrCode_e eErrCode;
    ABL_GameCapability_t tEmuCapability;
} ABL_GssGetEmuCapInfo_t;

typedef Image_Info_t ABL_ImageInfo_t;

typedef Image_RapidInfo_t ABL_RapidImageInfo_t;

typedef struct ABL_GssRspInfoExt_t_
{
    ABL_GssErrCode_e eErrCode;
    ABL_GssInfoExt_t tGssInfo;
} ABL_GssRspInfoExt_t;

typedef struct ABL_GssRspInfo_t_
{
    ABL_GssErrCode_e eErrCode;
    ABL_GssInfo_t tGssInfo;
    u32 uExtInfo;
} ABL_GssRspInfo_t;

typedef struct DBLRemapGssErrCode_t_
{
    ABL_GssErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLRemapGssErrCode_t;

typedef enum ABL_GssFormat_e_
{
    ABL_GSS_JPG,                    //ESL_GSS_JPG
    ABL_GSS_BMP,                    //ESL_GSS_BMP
    ABL_GSS_PNG,                    //ESL_GSS_PNG
    ABL_GSS_GIF,                    //ESL_GSS_GIF
    ABL_GSS_UNKNOW_FORMAT           //ESL_GSS_UNKNOW_FORMAT
} ABL_GssFormat_e;

typedef enum ABL_GssRenderType_e_
{
    ABL_GSS_RENDER_PALETTE,         //ESL_GSS_RENDER_PALETTE
    ABL_GSS_RENDER_EM_TEST_LCD,     //ESL_GSS_RENDER_EM_TEST_LCD
    ABL_GSS_RENDER_EMU,         //ESL_GSS_RENDER_EMU
    ABL_GSS_RENDER_MAX              //ESL_GSS_RENDER_MAX
} ABL_GssRenderType_e;

typedef enum ABL_GssColorFormat_e_
{
    ABL_GSS_COLOR_RGB_565,          //ESL_GSS_COLOR_RGB_565
    ABL_GSS_COLOR_YUV_420,          //ESL_GSS_COLOR_YUV_420
    ABL_GSS_COLOR_UNKNOW_FORMAT     //ESL_GSS_COLOR_UNKNOW_FORMAT
} ABL_GssColorFormat_e;

typedef enum ABL_GssEmuBinType_e_
{
    ABL_GSS_EMU_BIN_DEFAULT,        //ESL_GSS_EMU_BIN_DEFAULT
    ABL_GSS_EMU_BIN_FILE,           //ESL_GSS_EMU_BIN_FILE
    ABL_GSS_EMU_BIN_DATA            //ESL_GSS_EMU_BIN_DATA
} ABL_GssEmuBinType_e;


typedef void (*ABL_GssCb)(u16 uSenderId, u32 uUserValue, ABL_GssErrCode_e errCode, ABL_GssInfo_t *pGssInfo);
typedef void (*ABL_GssCbExt)(u16 uSenderId, u32 uUserValue, ABL_GssErrCode_e errCode, ABL_GssInfoExt_t *pGssInfo);
typedef void (*ABL_AllocDecBuf)(void *pUsrData, PMSSURFACE *ppSurf);
typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_GssCb pfnCb;
} ABL_GssCb_t;

typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_GssCbExt pfnCb;
} ABL_GssCbExt_t;

typedef struct ABL_GssDecodeRegion_Cmd_t_
{
    s32 sDecoder;
    u8 *pInBuffer;
    u32 uBufferSize;
    ABL_GSSPMSSurface_t pOutSurface;
    ABL_GssDecodeParam_t DecodeParm;

} ABL_GssDecodeRegion_Cmd_t;

typedef struct ABL_GssDecodeExt_Cmd_t_
{
    s32 sDecoder;
    u8 *pInBuffer;
    u32 uBufferSize;
    ABL_GSSPMSSurface_t pOutSurface;
    ABL_GssRotateAngle_e eRotateAngle;

} ABL_GssDecodeExt_Cmd_t;

typedef struct ABL_GssOpen_Cmd_t_
{
    s32 sDecoder;
} ABL_GssOpen_Cmd_t;

typedef struct ABL_GssRenderStart_Cmd_t_
{
    ABL_GssRenderConfig_t pConfig;
} ABL_GssRenderStart_Cmd_t;

typedef struct ABL_GssRenderStop_Cmd_t_
{
    ABL_GssRenderStopConfig_t pConfig;
} ABL_GssRenderStop_Cmd_t;

typedef struct ABL_GssRenderInput_Cmd_t_
{
    ABL_GssRenderInput_t pInput;
} ABL_GssRenderInput_Cmd_t;


typedef struct ABL_GssRenderGetInfo_Cmd_t_
{
    ABL_GssGetInfoParam_t pInfo;
} ABL_GssRenderGetInfo_Cmd_t;

typedef struct ABL_CamImgDecCapInfo_t_
{
    ABL_GssErrCode_e eErrCode;
    ABL_GssImageDecodingCapability_t tImgDecCap;
} ABL_ImgGetDecCapInfo_t;

typedef MmlGameStartGame_t      ABL_GameStartGame_t;
typedef MmlGameStopGame_t       ABL_GameStopGame_t;
typedef MmlGameGetGameInfo_t    ABL_GameGetGameInfo_t;
typedef MmlGameSendKeyEvent_t   ABL_GameSendKeyEvent_t;
typedef MmlImageSetJpegExifInfo_t   ABL_ImageSetJpegExifInfo_t;
typedef MmlImageDecodeImage_t       ABL_ImageDecodeImage_t;
typedef MmlImageGetImageInfo_t      ABL_ImageGetImageInfo_t;
typedef MmlGameGetGameCapability_t  ABL_GameGetGameCapability_t;
typedef Image_FrameInfo_t           ABL_ImageFrameInfo_t;
typedef MmlImageStereoType_e        ABL_ImageStereoType_e;

typedef struct GssCmd_t_
{
    union
    {
        ABL_GssCb_t *pCbParams;
        ABL_GssCbExt_t *pCbExtParams;
    } tCallBack;
    u32 nHandle;
    union
    {
		ABL_GameStartGame_t tGameStartGame;
        ABL_GameStopGame_t  tGameStopGame;
        ABL_GameGetGameInfo_t tGameGetGameInfo;
        ABL_GameSendKeyEvent_t tGameSendKeyEvent;
        ABL_ImageSetJpegExifInfo_t  tImageSetJpegExifInfo;
        ABL_ImageDecodeImage_t      tImageDecodeImage;    //Used with ABL_GssDecodeRegion
        ABL_ImageGetImageInfo_t     tImageGetImageInfo;     //Used with ABL_GssGetImageInfo
        MmlImageEncodeImage_t       tEncodeImage;           ///< Encode image (jpeg)
        ABL_GssImageGetDecodingCapability_t tImageGetDecodingCapability;
        ABL_GameGetGameCapability_t tGameGetGameCapability;
        ABL_GssSetEXIF_Cmd_t tGssSetEXIFParams;
        ABL_GssDecodeRegion_Cmd_t tGssDecodeRegionParams;
        ABL_GssDecodeExt_Cmd_t tGssDecodeExtParams;
        ABL_GssEncodeSetting_t tEncodeParams;
        ABL_GssRenderStart_Cmd_t tGssRenderStartParams;
        ABL_GssRenderStop_Cmd_t tGssRenderStopParams;
        ABL_GssRenderInput_Cmd_t tGssRenderInputParams;
        ABL_GssRenderGetInfo_Cmd_t tGssRenderGetInfoParams;
    } tParams;
} GssCmd_t;

typedef struct ABL_GssConvertRspInfo_t_
{
    ABL_GssErrCode_e eErrCode;
    ABL_GssConvertInfo_t tGssConvertInfo;
    u32 uExtInfo;
} ABL_GssConvertRspInfo_t;

typedef void (*ABL_GssConvertCb)(u16 uSenderId, u32 uUserValue, ABL_GssErrCode_e eErrCode, ABL_GssConvertInfo_t *pVdoInfo);
typedef struct {
    u16 uSenderId;     /**< Task id of sender */
    u32 uUserValue;    /**< userValue of sender for checking msg response to related applicatoin */
    ABL_GssConvertCb pfnCb;        /**< Done call back function that called by EMA */
} ABL_GssConvertCb_t;

typedef struct GssConvertCmd_t_
{
    ABL_GssConvertCb_t *pCbParams;
    u32 uHandle;
    union
    {
        ABL_GssCmdOpenColorConvert_t      tGssOpenColorConvert;
        ABL_GssCmdConvertColor_t          tGssConvertColor;
    } tParams;
} GssConvertCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
/*
    Following functions are Asynchronous and they need M2's support.
    Therefore, Resource Manager need to take care these operations.
*/
ABL_GssErrCode_e ABL_GssSetEXIF
(
    ResMgr_AppId_e eAppId,
    ABL_GssFileInfo_t *pFileParam,
    ABL_GssEXIF_Info_t *pInfo,
    ABL_GssCb_t *pGssCb
);

#if 1
ABL_GssErrCode_e ABL_GssDecodeAsync
(
    ResMgr_AppId_e eAppId,
    s32 sDecoder,
    u8 *pInBuffer,
    u32 uBufferSize,
    ABL_GSSPMSSurface_t pOutSurf,
    ABL_GssRotateAngle_e eRotateAngle,
    ABL_ImageStereoType_e eImgStereoType,
    ABL_GssCbExt_t *pGssCb
 );
#endif

#if 1
ABL_GssErrCode_e ABL_GssDecodeRegion
(
    ResMgr_AppId_e eAppId,
    s32 sDecoder,
    u8 *pInBuffer,
    u32 uBufferSize,
    ABL_GssDecodeParam_t *pDecodeParm,
    ABL_GSSPMSSurface_t pOutSurf,
    ABL_ImageStereoType_e eImgStereoType,
    ABL_GssCbExt_t *pGssCb
 );
#endif

/* Async M3*/
void ABL_GssM3DecodeSync
(
 ResMgr_AppId_e eAppId,
 s32 sDecoder,
 u8 *pInBuffer,
 u32 uBufferSize,
 ABL_GSSPMSSurface_t pOutSurf,
 ABL_GssRotateAngle_e eRotateAngle,
 ABL_GssCbExt_t *pGssCb
 );

/*
    Following functions are Synchronous and they don't need M2's support.
    Therefore, Resource Manager don't need to take care these operations.
*/
ABL_GssErrCode_e ABL_GssDecodeSync
(
    s32 sDecoder,
    u8 *pInBuffer,
    u32 uBufferSize,
    ABL_GSSPMSSurface_t pOutSurf,
    ABL_GssRotateAngle_e eRotateAngle,
    ABL_ImageStereoType_e eImgStereoType
);

void ABL_GssEncodeReq(ResMgr_AppId_e eAppId, ABL_GssEncodeSetting_t *pEncodeSetting, ABL_GssCb_t *pGssCb);
void ABL_GssEncodeSyncReq(ResMgr_AppId_e eAppId, ABL_GssEncodeSetting_t *pEncodeSetting, ABL_GssCb_t *pGssCb);
ABL_GssErrCode_e ABL_GssGetImageInfo(s32 sDecoder, u8* pInBuffer, u32 uBufSize, ABL_ImageInfo_t* pImageInfo);
ABL_GssErrCode_e ABL_GssGetRapidImageInfo(s32 sDecoder, u8* pInBuffer, u32 uBufSize, ABL_RapidImageInfo_t* pImageInfo);
s32 ABL_GssOpen(void);
u32 ABL_GssGetNextFrameDelayTime(s32 sDecoder);
ABL_GssErrCode_e ABL_GssDecodeNextFrame(s32 sDecoder, u32 *pDelayTime);
ABL_GssErrCode_e ABL_GssDecodeGetFrameInfo(s32 sDecoder, ABL_ImageFrameInfo_t *pFrameInfo);
u8 ABL_GssDecodeHasNextFrame(s32 sDecoder);
ABL_GssErrCode_e ABL_GssClose(s32 sDecoder);
ABL_CmnErrCode_e ABL_GssRenderStartReq(ResMgr_AppId_e eAppId, ABL_GssRenderConfig_t *pConfig, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssRenderStopReq(ResMgr_AppId_e eAppId, ABL_GssRenderStopConfig_t *pConfig, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssRenderInputReq(ResMgr_AppId_e eAppId, ABL_GssRenderInput_t *pInput, ABL_GssCb_t *pGssCb);
void ABL_GssImageGetDecodingCapabilityReq(ResMgr_AppId_e eAppId, ABL_GssImageGetDecodingCapability_t *pGetDecodingCapability, ABL_GssCb_t *pGssCb);
void ABL_GssRenderGetCapabilityReq(ResMgr_AppId_e eAppId, ABL_GameGetGameCapability_t *pGetGameCapability, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssRenderGetInfoReq(ResMgr_AppId_e eAppId, ABL_GssGetInfoParam_t *pInfo, ABL_GssCb_t *pGssCb);
void *ABL_GssCusFunc(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CusCmdType_e eCusCmdType);
ABL_CmnErrCode_e ABL_GssOpenSessionReq(ResMgr_AppId_e eAppId, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssCloseSessionReq(ResMgr_AppId_e eAppId, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssRenderCleanUpReq(ResMgr_AppId_e eAppId, ABL_GssCb_t *pGssCb);
ABL_CmnErrCode_e ABL_GssOpenConvertPlayerReq(ResMgr_AppId_e eAppId, ABL_GssConvertCb_t *pGssConvertCb);
void ABL_GssOpenConvertPlayerSyncReq(ResMgr_AppId_e eAppId, ABL_GssConvertCb_t *pGssConvertCb);
ABL_CmnErrCode_e ABL_GssOpenConvertPlayer(ResMgr_AppId_e eAppId, ABL_GssConvertCb_t *pGssConvertCb, bool bSync);
ABL_CmnErrCode_e ABL_GssCloseConvertPlayerReq(ResMgr_AppId_e eAppId, u32 nHandle, ABL_GssConvertCb_t *pGssConvertCb);
void ABL_GssCloseConvertPlayerSyncReq(ResMgr_AppId_e eAppId, u32 nHandle, ABL_GssConvertCb_t *pGssConvertCb);
ABL_CmnErrCode_e ABL_GssCloseConvertPlayer(ResMgr_AppId_e eAppId, u32 nHandle, ABL_GssConvertCb_t *pGssConvertCb, bool bSync);
ABL_CmnErrCode_e ABL_GssOpenColorConvertReq(ResMgr_AppId_e eAppId,ABL_GssOpenConvert_t *pOpenConvert,ABL_GssConvertCb_t *pGssConvertCb);
void ABL_GssOpenColorConvertSyncReq(ResMgr_AppId_e eAppId,ABL_GssOpenConvert_t *pOpenConvert,ABL_GssConvertCb_t *pGssConvertCb);
ABL_CmnErrCode_e ABL_GssOpenColorConvert(ResMgr_AppId_e eAppId,ABL_GssOpenConvert_t *pOpenConvert,ABL_GssConvertCb_t *pGssConvertCb,bool bSync);
ABL_CmnErrCode_e ABL_GssCloseColorConvertReq(ResMgr_AppId_e eAppId,u32 uHandle,ABL_GssConvertCb_t *pGssConvertCb);
void ABL_GssCloseColorConvertSyncReq(ResMgr_AppId_e eAppId,u32 uHandle,ABL_GssConvertCb_t *pGssConvertCb);
ABL_CmnErrCode_e ABL_GssCloseColorConvert(ResMgr_AppId_e eAppId,u32 uHandle,ABL_GssConvertCb_t *pGssConvertCb,bool bSync);
ABL_CmnErrCode_e ABL_GssConvertColorReq(ResMgr_AppId_e eAppId, ABL_GssConvertColor_t *pConvertColor, ABL_GssConvertCb_t *pGssConvertCb);
void ABL_GssConvertColorSyncReq(ResMgr_AppId_e eAppId,ABL_GssConvertColor_t *pConvertColor,ABL_GssConvertCb_t *pGssConvertCb);
ABL_CmnErrCode_e ABL_GssConvertColor(ResMgr_AppId_e eAppId,ABL_GssConvertColor_t *pConvertColor,ABL_GssConvertCb_t *pGssConvertCb,bool bSync);
#endif //__ABL_GSS_H__

