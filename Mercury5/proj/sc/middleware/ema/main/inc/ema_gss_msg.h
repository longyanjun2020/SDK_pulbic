/**
 *
 * @file    ema_gss_msg.h
 *
 * @brief   This module defines the EMA camera message struct type for GSS service
 *
 * @author  Pauli Leong
 * @version $Id: ema_gss_msg.h 12577 2008-07-17 06:29:49Z jack.hsieh $
 *
 */
#ifndef __EMA_GSS_MSG_H__
#define __EMA_GSS_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_gss_itf.h"
#include "ema.h"




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
typedef struct {
    u16     x;
    u16     y;
    u16     width;
    u16     height;
} ema_GssWinParam_t;

typedef struct {
  ema_GssWinParam_t  WinArea;
} ema_GssWinGeometry_t;

typedef struct {
  u16  SCK;
} ema_GssSetSCK_t;

typedef struct {
  u16  SCK;
} ema_GssEraseColor_t;

typedef struct {
  u8  transLevel;
} ema_GssSetTransLev_t;

typedef struct {
  ema_GssWinParam_t WinArea;
  u8                RotateAngle;
} ema_GssSelectICPWin_t;

typedef struct {
  isl_GssDrawBmpParam_t bmpParam;
} ema_GssDrawBmp_t;

typedef struct {
  isl_GssJpegParam_t jpegParam;
} ema_GssJpegDecode_t;

typedef struct {
  isl_GssJpegPngParam_t jpngParam;
} ema_GssJpegPngDecode_t;

typedef struct {
  esl_GssGESetting_t    geParam;
} ema_GssGe_t;

typedef struct {
  isl_GssJpegParam_t decodeParam;
  isl_GssRegion_t    region;
} ema_GssPartialDecode_t;

typedef struct {
  isl_GssGetPicInfoParam_t getPicInfoParam;
} ema_GssGetPicInfo_t;

typedef struct {
	esl_GssRenderConfig_t gssRenderConfig;
} ema_GssRenderCong_t;

typedef struct {
  esl_GssRenderStopConfig_t  gssRenderStopConfig;
} ema_GssRendStopConfig_t;

typedef struct {
  esl_GssFileInfo_t  fileParam;
  esl_GssEXIF_Info_t exifInfo;
} ema_GssSetEXIF_Cmd_t;

typedef struct {
  isl_GssRenderParam_t  renderParam;
} ema_GssRendDraw_t;

typedef struct {
  esl_GssEncodeSetting_t  encodeParam;
} ema_GssEncode_t;

typedef struct {
  esl_GssGetInfoParam_t  getInfoParam;
} ema_GssGetInfo_t;

typedef struct {
  esl_GssRenderInput_t inputParam;
} ema_GssRenderInput_t;

typedef struct {
  esl_GssDisplayQuality_t setting;
} ema_GssDQSet_t;

typedef struct {
  esl_GssLayer_e layer;
  esl_GssLayerProperty_t property;
} ema_GssLayerProerty_t;

typedef struct {
  esl_GssDQType_e type;
} ema_GssGetDQType_t;

typedef struct {
  ema_TransType_t TransType;
  esl_GssCb_t     *pESLGssCb; /*for ESL*/
  isl_GssCb_t     *pGssCb;    /*for ISL*/
  isl_GssLayer_e   LayerID;
  union {
    ema_GssWinGeometry_t     gssWinGeoCmd;
    ema_GssSetSCK_t          gssSetSCKCmd;
    ema_GssSetTransLev_t     gssSetTransCmd;
    ema_GssSelectICPWin_t    gssSelectICPWinCmd;
    ema_GssDrawBmp_t         gssDrawBmpCmd;
    ema_GssJpegDecode_t      gssJpegDecodeCmd;
    ema_GssGetPicInfo_t      gssGetPicInfoCmd;
    ema_GssSetEXIF_Cmd_t     gssSetEXIFCmd;
    ema_GssPartialDecode_t   gssPartialDecodeCmd;
    ema_GssRenderCong_t      gssRenderCmd;
    ema_GssRendDraw_t        gssRenderDrawCmd;
    ema_GssRendStopConfig_t  gssRenderStopCmd;

    ema_GssEncode_t          gssEncodeCmd;
    ema_GssGetInfo_t         gssGetInfoCmd;
    ema_GssRenderInput_t     gssRenderInputCmd;
    ema_GssDQSet_t           gssDQSetCmd;
    ema_GssLayerProerty_t    gssSetLayerPropertyCmd;
    ema_GssGetDQType_t       gssDQGetCmd;
		ema_GssJpegPngDecode_t   gssJpegPngDecodeCmd;
    ema_GssGe_t              gssGeCmd;
  } cmdType;
} ema_GssCmd_t;


typedef struct {
  u16             sender;
  ema_TransType_t TransType;
  ema_ErrCode_e   errorStatus;
} ema_GssRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_GSS_MSG_H__ */




