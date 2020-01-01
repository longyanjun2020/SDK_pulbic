/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : API of H.264 Decoder
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: h264decapi.h,v $
--  $Date: 2007/11/22 10:35:17 $
--  $Revision: 1.7 $
--
------------------------------------------------------------------------------*/

#ifndef __H264DECAPI_H__
#define __H264DECAPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_mfd_basetype.h"
#include "drv_mfd_decapicommon.h"
#ifdef _M4VD_GBUF_
#include "drv_mfd_mvc_decoder.h"
#endif
/*------------------------------------------------------------------------------
    API type definitions
------------------------------------------------------------------------------*/

    /* Return values */
    typedef enum H264DecRet_
    {
        H264DEC_OK = 0,
        H264DEC_STRM_PROCESSED = 1,
        H264DEC_PIC_RDY = 2,
        H264DEC_PIC_DECODED = 3,
        H264DEC_HDRS_RDY = 4,
        H264DEC_ADVANCED_TOOLS = 5,

        H264DEC_PARAM_ERROR = -1,
        H264DEC_STRM_ERROR = -2,
        H264DEC_NOT_INITIALIZED = -3,
        H264DEC_MEMFAIL = -4,
        H264DEC_INITFAIL = -5,
        H264DEC_HDRS_NOT_RDY = -6,
        H264DEC_STREAM_NOT_SUPPORTED = -8,

        H264DEC_HW_RESERVED = -254,
        H264DEC_HW_TIMEOUT = -255,
        H264DEC_HW_BUS_ERROR = -256,
        H264DEC_SYSTEM_ERROR = -257,
        H264DEC_DWL_ERROR = -258,

        H264DEC_EVALUATION_LIMIT_EXCEEDED = -999,
        H264DEC_FORMAT_NOT_SUPPORTED = -1000
    } H264DecRet;

    /* decoder  output picture format */
    typedef enum H264DecOutFormat_
    {
        H264DEC_SEMIPLANAR_YUV420 = 0x020001,
        H264DEC_TILED_YUV420 = 0x020002
    } H264DecOutFormat;

    /* Decoder instance */
    typedef const void *H264DecInst;

    /* Input structure */
    typedef struct H264DecInput_
    {
        const u8 *pStream;   /* Pointer to the input */
        u32 streamBusAddress;   /* DMA bus address of the input stream */
        u32 dataLen;         /* Number of bytes to be decoded         */
        u32 picId;           /* Identifier for the picture to be decoded */
    } H264DecInput;

    /* Output structure */
    typedef struct H264DecOutput_
    {
        const u8 *pStrmCurrPos;    /* Pointer to stream position where decoding ended */
        u32 strmCurrBusAddress; /* DMA bus address location where the decoding ended */
        u32 dataLeft;        /* how many bytes left undecoded */
    } H264DecOutput;

    /* cropping info */
    typedef struct H264CropParams_
    {
        u32 cropLeftOffset;
        u32 cropOutWidth;
        u32 cropTopOffset;
        u32 cropOutHeight;
    } H264CropParams;

    /* Output structure for H264DecNextPicture */
    typedef struct H264DecPicture_
    {
        u32 picWidth;        /* pixels width of the picture as stored in memory */
        u32 picHeight;       /* pixel height of the picture as stored in memory */
        H264CropParams cropParams;  /* cropping parameters */
        const u32 *pOutputPicture;  /* Pointer to the picture */
        u32 outputPictureBusAddress;    /* DMA bus address of the output picture buffer */
        u32 picId;           /* Identifier of the picture to be displayed */
        u32 isIdrPicture;    /* Indicates if picture is an IDR picture */
        u32 nbrOfErrMBs;     /* Number of concealed MB's in the picture  */
#ifdef _M4VD_GBUF_
        VID_PICTURE *decPic_ptr;
#endif
    } H264DecPicture;

    /* stream info filled by H264DecGetInfo */
    typedef struct H264DecInfo_
    {
        u32 picWidth;
        u32 picHeight;
        u32 videoRange;      /* samples' video range */
        u32 matrixCoefficients;
        H264CropParams cropParams;  /* cropping information */
        H264DecOutFormat outputFormat;  /* format of the output picture */
        u32 sarWidth;        /* sample aspect ratio */
        u32 sarHeight;       /* sample aspect ratio */
        int frameMinNum;
    } H264DecInfo;

    /* Version information */
    typedef struct H264DecApiVersion_
    {
        u32 major;           /* API major version */
        u32 minor;           /* API minor version */
    } H264DecApiVersion;

    typedef struct H264DecBuild_
    {
        u32 swBuild;         /* Software build ID */
        u32 hwBuild;         /* Hardware build ID */
        DecHwConfig hwConfig;   /* hardware supported configuration */
    } H264DecBuild;

/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/

    H264DecApiVersion H264DecGetAPIVersion(void);

    H264DecBuild H264DecGetBuild(void);

    H264DecRet H264DecInit(H264DecInst * pDecInst, u32 noOutputReordering);

    void H264DecRelease(H264DecInst decInst);

    H264DecRet H264DecDecode(H264DecInst decInst,
                             const H264DecInput * pInput,
                             H264DecOutput * pOutput);

    H264DecRet H264DecNextPicture(H264DecInst decInst,
                                  H264DecPicture * pOutput, u32 endOfStream);

    H264DecRet H264DecGetInfo(H264DecInst decInst, H264DecInfo * pDecInfo);

/*------------------------------------------------------------------------------
    Prototype of the API trace funtion. Traces all API entries and returns.
    This must be implemented by the application using the decoder API!
    Argument:
        string - trace message, a null terminated string
------------------------------------------------------------------------------*/
    void H264DecTrace(const char *string);

#ifdef __cplusplus
}
#endif

#endif                       /* __H264DECAPI_H__ */
