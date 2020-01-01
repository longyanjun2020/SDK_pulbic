#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _MW_IMGBASICFUN_H
#define _MW_IMGBASICFUN_H

#include <string.h>


#ifdef JPDCModel
#define IMGDEC_MALLOC(Type_t, nSize)               ((Type_t *)malloc(nSize))
#define IMGDEC_MFREE(pMem)                         free(pMem)
#define IMGDEC_FLUSH(pMem, nSize)
#define IMGDEC_INVALIDATE(pMem, nSize)
#define IMGDEC_MEMSET(pMem, nVal, nSize)           memset(pMem, nVal, nSize)
#define IMGDEC_MEMCPY(pDst, pSrc, nSize)           memcpy(pDst, pSrc, nSize)
#define IMGDEC_MEMMOVE(pDst, pSrc, nSize)          memmove(pDst, pSrc, nSize)
#define IMGDEC_MEMCMP(pMem1, pMem2, nSize)         memcmp(pMem1, pMem2, nSize)
#define IMGDEC_ISRAM_MALLOC(Type_t, nSize)        ((Type_t *)malloc(nSize))
#define IMGDEC_ISRAM_MFREE(pMem)                  free(pMem)
#else
#include "cus_os.hc"
#include "imgcodec_common.h"
#define JASON_ENBALE_UNIFYIO

#ifdef JASON_ENBALE_UNIFYIO
#define ImageFSFunc_t ImgFSFunc_st
#define ImageFSSeek fseek
#define ImageFSRead fread
#define pHdl handle
#endif //JASON_ENBALE_UNIFYIO

#define IMGDEC_MALLOC(Type_t, nSize)               ((Type_t *)MsPMalloc(nSize))
#define IMGDEC_MFREE(pMem)                         MsReleaseMemory(pMem)
#define IMGDEC_FLUSH(pMem, nSize)
#define IMGDEC_INVALIDATE(pMem, nSize)
#define IMGDEC_MEMSET(pMem, nVal, nSize)           memset(pMem, nVal, nSize)
#define IMGDEC_MEMCPY(pDst, pSrc, nSize)           memcpy(pDst, pSrc, nSize)
#define IMGDEC_MEMMOVE(pDst, pSrc, nSize)          memmove(pDst, pSrc, nSize)
#define IMGDEC_MEMCMP(pMem1, pMem2, nSize)         memcmp(pMem1, pMem2, nSize)
#define IMGDEC_SLEEP(nTick)                        MsSleep(nTick)
#define IMGDEC_DELAY(nMicroSec)
#define IMGDEC_GET_TICK
#if defined(__IRAM_ALLOC__)
#define IMGDEC_ISRAM_MALLOC(Type_t, nSize)        ((Type_t *)MsGetIramMemory(nSize))
#define IMGDEC_ISRAM_MFREE(pMem)                  MsReleaseIramMemory(pMem)
#else
#define IMGDEC_ISRAM_MALLOC(Type_t, nSize)        ((Type_t *)MsPMalloc(nSize))
#define IMGDEC_ISRAM_MFREE(pMem)                  MsReleaseMemory(pMem)
#endif

#define IMGDEC_SENDMSG(eMailbox, pMsg)             MsSend(eMailbox, pMsg)

#endif //JPDCModel

#define DRV_MEM_ALIGNMENT_SIZE (32-1)

#define jpd_trace1 img_trace1
#define jpd_trace2 img_trace2
#define jpd_error1 img_error1
#define jpd_error2 img_error2

typedef enum
{
    IMAGE_INPUT_TYPE_FILE = 1,      ///< Decode form filename based source
    IMAGE_INPUT_TYPE_MEMORY,        ///< Decode form in-memory source
    /* */
    IMAGE_INPUT_TYPE_NUM
} ImageInputType_e;

typedef enum
{
    JpgMemISram = 0,
    JpgMemDram,
} JpgMemType_e;

typedef enum
{
    IMAGE_TYPE_JPG = 1,
    IMAGE_TYPE_BMP,
    IMAGE_TYPE_GIF,
    IMAGE_TYPE_PNG,
    IMAGE_TYPE_MAX = IMAGE_TYPE_PNG,
    IMAGE_TYPE_UNKNOWN,
} IMAGE_TYPE;

typedef enum{
   ImageFromFile = 0,
   ImageFromMemory,
} ImageSrc;

typedef enum
{
    JPD_DECODE_IMAGE = 0,
    JPD_DECODE_GET_INFO,
}JPD_DECODE_MODE;

typedef enum
{
    ImgRotate_0 = 0,
    ImgRotate_90,
    ImgRotate_180,
    ImgRotate_270
} ImageRot_e;

typedef enum
{
    ImgRGB565 = 0,
    ImgRGB888,
} ImgFmt_e;



typedef struct
{
	u8  ROIEnable;
    u16 ROI_X0;
    u16 ROI_Y0;
    u16 ROI_XEnd;
    u16 ROI_YEnd;
} ImageROIRegion_t;


typedef struct
{
    ImageRot_e ImgRotate;
    u8  XMirror;
    u8  YMirror;
    u16 OutWidth;
    u16 OutHeight;
    u16 OutPitch;
    void *pOutPtr;
    u32 OutBufSize;
    ImgFmt_e ImgFmt;
} ImageOutCfg_t;


typedef struct
{
    ImageInputType_e    eInputType;
    s32                 FileHandle;
    u32                 RemainingSize; //FileSize;
    u32                 TotalDataSize;
    u8                  *pSrcPtr;
    u8                  *pBackSrcPtr;
} ImageHandle_t, *pImageHdl;

typedef s32 (*ImageFSOpen) ( pImageHdl pHdl, void *ptr );

#if 0
//there should be
// 1. open function.
// 2. close function.
// 3. read function.
// 4. seek function.
#ifndef JASON_ENBALE_UNIFYIO
typedef struct _ImageFSFunc_t_
{
	ImageHandle_t               sImgHdl;
	pImageHdl                   pHdl;

	image_Errmsg (*ImageFSOpen)	( pImageHdl pHdl, void *ptr, u32 Size);
	s32 (*ImageFSClose)         ( pImageHdl pHdl );
	u32 (*ImageFSRead)          ( pImageHdl pHdL, void *pDst, u32 Size);
	s32 (*ImageFSSeek)          ( pImageHdl pHdl, u32 Position, u32 Mode);
    u32 (*ImageGetSize)         ( pImageHdl pHdl );
    u32 (*ImageGetTatolDataSize)         ( pImageHdl pHdl );
} ImageFSFunc_t;
#endif //def JASON_ENBALE_UNIFYIO
#endif

typedef struct
{
    u8 *JpgISramPtr;
    u8 *JpgISramBackPtr;
    u32 JpgISramLeftSize;
    u32 JpgISramSize;

    u8 *JpgDramPtr;
    u8 *JpgDramBackPtr;
    u32 JpgDramLeftSize;
    u32 JpgDramSize;
} JpgMemory_t;

//extern ImageFSFunc_t sImgFSFunc;

image_Errmsg MImage_OpenFile(pImageHdl pHDL, void *pointer, u32 Size);
u32 MImage_ReadData(pImageHdl pHDL, void *pDst,u32 Size);
IMAGE_TYPE MImage_CheckType(pImageHdl pHDL);
s32 MImage_FileSeek(pImageHdl pHDL, u32 Position,u32 Mode);
s32 MImage_CloseFile(pImageHdl pHDL);
u32 MImage_GetFileSize(pImageHdl pHDL);
u32 MImage_GetTotalDataSize(pImageHdl pHDL);

u32 MImage_ReadData_Mem(pImageHdl pHDL, void *pDst, u32 Size);
s32 MImage_CloseFile_Mem(pImageHdl pHDL);
image_Errmsg MImage_OpenFile_Mem(pImageHdl pHDL, void *pointer, u32 Size);
s32 MImage_FileSeek_Mem(pImageHdl pHDL, u32 Position, u32 Mode);
u32 MImage_GetFileSize_Mem(pImageHdl pHDL);

void *MwImgMalloc(JpgMemory_t *pJpgMemory, u32 Size, JpgMemType_e Position);
image_Errmsg MwImgHeapMem(u16 Mode, JpgMemory_t *pJpgMemory, u32 Size, JpgMemType_e Position);
image_Errmsg MwImgFreeMem(u16 Mode, JpgMemory_t *pJpgMemory, JpgMemType_e Position);
#endif //_MW_IMGBASICFUN_H
#endif

