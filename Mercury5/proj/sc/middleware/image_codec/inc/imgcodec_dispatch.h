#ifndef _IMGCODEC_DISPATCH_H_
#define _IMGCODEC_DISPATCH_H_

#include "imgcodec_common.h"

typedef enum
{
    IMAGE_SCLCAP_FRAME_MODE,
    IMAGE_SCLCAP_ROW_MODE_YUV422,
    IMAGE_SCLCAP_ROW_MODE_YUV422_YV12,
    IMAGE_SCLCAP_ROW_MODE_YUV420_YV12
} Image_SclCap;

IMGCODEC_FORMAT imageCodec_getFormat(u8* buf);
image_Errmsg imageCodec_getInfoEx(IMGCODEC_FORMAT format, ImgFSFunc_st *pFuncFS, Image_Info_t *pInfo);
image_Errmsg imageCodec_getDecoder(PIMGCODEC_CONTEXT pDecoder);
u8  imageCodec_checkSclCapability(Image_SclCap caps);
u32 imageCodec_checkRamBoundary(void *buff, u32 buffSize);
#endif
