/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2007 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : API for the 8170 MPEG-2 Decoder
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mpeg2decapi.h,v $
--  $Date: 2007/12/14 10:58:21 $
--  $Revision: 1.10 $
--
------------------------------------------------------------------------------*/

#ifndef __MPEG2DECAPI_H__
#define __MPEG2DECAPI_H__

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
    typedef enum
    {
        MPEG2DEC_OK = 0,
        MPEG2DEC_STRM_PROCESSED = 1,
        MPEG2DEC_PIC_RDY = 2,
        MPEG2DEC_HDRS_RDY = 3,
        MPEG2DEC_HDRS_NOT_RDY = 4,
        MPEG2DEC_PIC_DECODED = 5,

        MPEG2DEC_PARAM_ERROR = -1,
        MPEG2DEC_STRM_ERROR = -2,
        MPEG2DEC_NOT_INITIALIZED = -3,
        MPEG2DEC_MEMFAIL = -4,
        MPEG2DEC_INITFAIL = -5,

        MPEG2DEC_HW_RESERVED = -254,
        MPEG2DEC_HW_TIMEOUT = -255,
        MPEG2DEC_HW_BUS_ERROR = -256,
        MPEG2DEC_SYSTEM_ERROR = -257,
        MPEG2DEC_DWL_ERROR = -258,
        MPEG2DEC_FORMAT_NOT_SUPPORTED = -1000
    } Mpeg2DecRet;

    /* decoder output picture format */
    typedef enum
    {
        MPEG2DEC_SEMIPLANAR_YUV420 = 0x020001,
        MPEG2DEC_TILED_YUV420 = 0x020002
    } Mpeg2DecOutFormat;

    /* DAR (Display aspect ratio) */
    typedef enum
    {
        MPEG2DEC_1_1 = 0x01,
        MPEG2DEC_4_3 = 0x02,
        MPEG2DEC_16_9 = 0x03,
        MPEG2DEC_2_21_1 = 0x04
    } Mpeg2DecDARFormat;

    /* SAR (Sample aspect ratio) */
    /* TODO! */

    typedef struct
    {
        u32 *pVirtualAddress;
        u32 busAddress;
    } Mpeg2DecLinearMem;

    /* Decoder instance */
    typedef void *Mpeg2DecInst;

    /* Input structure */
    typedef struct
    {
        const u8 *pStream;    /* Pointer to stream to be decoded              */
        u32 streamBusAddress;   /* DMA bus address of the input stream */
        u32 dataLen;    /* Number of bytes to be decoded                */
        u32 picId;
    } Mpeg2DecInput;

    /* Time code */
    typedef struct
    {
        u32 hours;
        u32 minutes;
        u32 seconds;
        u32 pictures;
    } Mpeg2DecTime;

    typedef struct
    {
        Mpeg2DecLinearMem outputPicture;    /* Pointer and bus address to the
                                             * recent decoded picture decoder
                                             * output, YCbCr format  */
        const u8 *pStrmCurrPos;
        u32 strmCurrBusAddress; /* DMA bus address location where the decoding
                                 * ended */
        u32 dataLeft;
    } Mpeg2DecOutput;

    /* stream info filled by Mpeg2DecGetInfo */
    typedef struct
    {
        u32 frameWidth;
        u32 frameHeight;
        u32 codedWidth;
        u32 codedHeight;
        u32 profileAndLevelIndication;
        u32 sampleAspectRatio;
        u32 DisplayAspectRatio;
        u32 streamFormat;
        u32 videoFormat;
        u32 videoRange; /* ??? only [0-255] */
        u32 interlacedSequence;
        Mpeg2DecOutFormat outputFormat;
    } Mpeg2DecInfo;

    typedef struct
    {
        u8 *pOutputPicture;
        u32 outputPictureBusAddress;
        u32 frameWidth;
        u32 frameHeight;
        u32 codedWidth;
        u32 codedHeight;
        u32 keyPicture;
        u32 bPicture;
        u32 picId;
        u32 interlaced;
        u32 fieldPicture;
        u32 topField;
        u32 firstField;
        u32 repeatFirstField;
        u32 repeatFrameCount;
        u32 numberOfErrMBs;
        Mpeg2DecTime timeCode;
#ifdef _M4VD_GBUF_
        VID_PICTURE *decPic_ptr;
#endif
    } Mpeg2DecPicture;

    /* Version information */
    typedef struct
    {
        u32 major;  /* API major version */
        u32 minor;  /* API minor version */

    } Mpeg2DecApiVersion;

    typedef struct
    {
        u32 swBuild;    /* Software build ID */
        u32 hwBuild;    /* Hardware build ID */
        DecHwConfig hwConfig;   /* hardware supported configuration */
    } Mpeg2DecBuild;

/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/

    Mpeg2DecApiVersion Mpeg2DecGetAPIVersion(void);

    Mpeg2DecBuild Mpeg2DecGetBuild(void);

    Mpeg2DecRet Mpeg2DecInit(Mpeg2DecInst * pDecInst);

    Mpeg2DecRet Mpeg2DecDecode(Mpeg2DecInst decInst,
                               Mpeg2DecInput * pInput,
                               Mpeg2DecOutput * pOutput);

    Mpeg2DecRet Mpeg2DecGetInfo(Mpeg2DecInst decInst, Mpeg2DecInfo * pDecInfo);

    Mpeg2DecRet Mpeg2DecNextPicture(Mpeg2DecInst decInst,
                                    Mpeg2DecPicture * pPicture,
                                    u32 endOfStream);

    void Mpeg2DecRelease(Mpeg2DecInst decInst);

/*------------------------------------------------------------------------------
    Prototype of the API trace funtion. Traces all API entries and returns.
    This must be implemented by the application using the decoder API!
    Argument:
        string - trace message, a null terminated string
------------------------------------------------------------------------------*/
    void Mpeg2DecTrace(const char *string);

#ifdef __cplusplus
}
#endif

#endif /* __MPEG2DECAPI_H__ */
