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
--  Description : API of MPEG-4 Decoder
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: mp4decapi.h,v $
--  $Date: 2007/11/26 11:32:00 $
--  $Revision: 1.17 $
--
------------------------------------------------------------------------------*/

#ifndef __MP4DECAPI_H__
#define __MP4DECAPI_H__

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
    typedef enum MP4DecRet_{
        MP4DEC_OK = 0,
        MP4DEC_STRM_PROCESSED = 1,
        MP4DEC_PIC_RDY = 2,
        MP4DEC_PIC_DECODED = 3,
        MP4DEC_HDRS_RDY = 4,
        MP4DEC_DP_HDRS_RDY = 5,

        MP4DEC_VOS_END = 14,
        MP4DEC_HDRS_NOT_RDY = 15,

        MP4DEC_PARAM_ERROR = -1,
        MP4DEC_STRM_ERROR = -2,
        MP4DEC_NOT_INITIALIZED = -4,
        MP4DEC_MEMFAIL = -5,
        MP4DEC_INITFAIL = -6,
        MP4DEC_FORMAT_NOT_SUPPORTED = -7,
        MP4DEC_STRM_NOT_SUPPORTED = -8,

        MP4DEC_HW_RESERVED = -254,
        MP4DEC_HW_TIMEOUT = -255,
        MP4DEC_HW_BUS_ERROR = -256,
        MP4DEC_SYSTEM_ERROR = -257,
        MP4DEC_DWL_ERROR = -258
    } MP4DecRet;

    /* decoder output picture format */
    typedef enum MP4DecOutFormat_
    {
        MP4DEC_SEMIPLANAR_YUV420 = 0x020001,
        MP4DEC_TILED_YUV420 = 0x020002
    } MP4DecOutFormat;

    typedef struct
    {
        u32 *pVirtualAddress;
        u32 busAddress;
    } MP4DecLinearMem;

    /* Decoder instance */
    typedef void *MP4DecInst;

    /* Input structure */
    typedef struct MP4DecInput_{
        const u8 *pStream;       /* Pointer to stream to be decoded  */
        u32 streamBusAddress; /* DMA bus address of the input stream */
        u32 dataLen;        /* Number of bytes to be decoded                */
        u32 enableDeblock;  /* Enable deblocking of post processed picture  */
                            /* NOTE: This parameter is not valid if the decoder
                             * is not used in pipeline mode with the post
                             * processor i.e. it has no effect on the
                             * decoding process */

        u32 picId;
    } MP4DecInput;

    /* Time code */
    typedef struct TimeCode_{
        u32 hours;
        u32 minutes;
        u32 seconds;
        u32 timeIncr;
        u32 timeRes;
    } MP4DecTime;

    typedef struct MP4DecOutput_{
        const u8  *pStrmCurrPos;
        u32 strmCurrBusAddress; /* DMA bus address location where the decoding
                                   ended */
        u32 dataLeft;
    } MP4DecOutput;

    /* stream info filled by MP4DecGetInfo */
    typedef struct MP4DecInfo_{
        u32 frameWidth;
        u32 frameHeight;
        u32 codedWidth;
        u32 codedHeight;
        u32 streamFormat;
        u32 profileAndLevelIndication;
        u32 videoFormat;
        u32 videoRange;
        u32 parWidth;
        u32 parHeight;
        u32 userDataVOSLen;
        u32 userDataVISOLen;
        u32 userDataVOLLen;
        u32 userDataGOVLen;
        u32 interlacedSequence;
        MP4DecOutFormat outputFormat;
    } MP4DecInfo;

    /* User data type */
    typedef enum {
        MP4DEC_USER_DATA_VOS = 0,
        MP4DEC_USER_DATA_VISO,
        MP4DEC_USER_DATA_VOL,
        MP4DEC_USER_DATA_GOV

    } MP4DecUserDataType;

    /* User data configuration */
    typedef struct {
        MP4DecUserDataType userDataType;
        u8  *pUserDataVOS;
        u32  userDataVOSMaxLen;
        u8  *pUserDataVISO;
        u32  userDataVISOMaxLen;
        u8  *pUserDataVOL;
        u32  userDataVOLMaxLen;
        u8  *pUserDataGOV;
        u32  userDataGOVMaxLen;
    } MP4DecUserConf;

    /* Version information */
    typedef struct MP4DecVersion_{
        u32 major;    /* API major version */
        u32 minor;    /* API minor version */
    } MP4DecApiVersion;

    typedef struct MP4DecBuild_
    {
        u32 swBuild;    /* Software build ID */
        u32 hwBuild;    /* Hardware build ID */
        DecHwConfig hwConfig;   /* hardware supported configuration */
    } MP4DecBuild;

    typedef struct
    {
        const u8 *pOutputPicture;
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
        u32 nbrOfErrMBs;
        MP4DecTime timeCode;
#ifdef _M4VD_GBUF_
        VID_PICTURE *decPic_ptr;
#endif
    } MP4DecPicture;

/*------------------------------------------------------------------------------
    Prototypes of Decoder API functions
------------------------------------------------------------------------------*/

    MP4DecApiVersion MP4DecGetAPIVersion(void);

    MP4DecBuild MP4DecGetBuild(void);

    MP4DecRet MP4DecInit(MP4DecInst * pDecInst, u32 sorensonSpark);

    MP4DecRet MP4DecDecode(MP4DecInst decInst,
                           const MP4DecInput   * pInput,
                           MP4DecOutput        * pOutput);

    MP4DecRet MP4DecGetInfo(MP4DecInst decInst,
                                MP4DecInfo  * pDecInfo);

    MP4DecRet MP4DecGetUserData(MP4DecInst        decInst,
                                const MP4DecInput * pInput,
                                MP4DecUserConf    * pUserDataConfig);

    MP4DecRet MP4DecNextPicture(MP4DecInst        decInst,
                                MP4DecPicture    *pPicture,
                                u32               endOfStream);

    void  MP4DecRelease(MP4DecInst decInst);

/*------------------------------------------------------------------------------
    Prototype of the API trace funtion. Traces all API entries and returns.
    This must be implemented by the application using the decoder API!
    Argument:
        string - trace message, a null terminated string
------------------------------------------------------------------------------*/
    void MP4DecTrace(const char *string);

#ifdef __cplusplus
}
#endif

#endif /* __MP4DECAPI_H__ */

