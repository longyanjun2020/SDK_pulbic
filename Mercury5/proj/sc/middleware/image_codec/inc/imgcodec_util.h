#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_UTIL_H_
#define _IMGCODEC_UTIL_H_
#include "imgcodec_common.h"
#include "mdl_drm_vfs_file.ho"

#define img_file_fopen drm_file_fopen
#define img_file_fread drm_file_fread
#define img_file_ftell drm_file_ftell
#define img_file_fseek drm_file_fseek
#define img_file_ferror drm_file_ferror
#define img_file_fclose drm_file_fclose


#define IMGCODEC_MAX(a,b) ((a) > (b) ? (a) : (b))
#define IMGCODEC_MIN(a,b) ((a) < (b) ? (a) : (b))

#define IMGCODEC_SWAP(a, b) ((a) ^= (b) ^= (a) ^= (b))

#define IMGCODEC_EOF (-1)

#define IMGCODEC_FILE_MODE_CACHE    0
#define IMGCODEC_FILE_MODE_NONCACHE 1
#define IMGCODEC_FILE_MODE_MEMORY   2

typedef struct IMGCODEC_FILE_s IMGCODEC_FILE;

typedef struct ImgFSFunc_s
{
    IMGCODEC_FILE *handle;
    u32 (*fread) (IMGCODEC_FILE *handle, void* buf, u32 size);
    s32 (*fseek) (IMGCODEC_FILE *handle, s32 offset, int origin);
    int (*getc)  (IMGCODEC_FILE *handle);
    u32 (*ftell) (IMGCODEC_FILE *handle);
    int (*ferror) (IMGCODEC_FILE *handle);
} ImgFSFunc_st;

typedef enum
{
    IMAGE_RESOURCE_SCL = 0,
    IMAGE_RESOURCE_JPD,
    IMAGE_RESOURCE_NUM,
}Image_Resource;

int imageCodec_ferror(IMGCODEC_FILE* img_fp);
u32 imageCodec_ftell(IMGCODEC_FILE* img_fp);
int imageCodec_getc(IMGCODEC_FILE* img_fp);
u32 imageCodec_fread(IMGCODEC_FILE* img_fp, void* buf, u32 size);
s32 imageCodec_fseek(IMGCODEC_FILE* img_fp, s32 offset, int origin);
s32 imageCodec_fclose(IMGCODEC_FILE* img_fp);
IMGCODEC_FILE *imageCodec_fopen_file(u16* fileName, u32 cacheSize);  // File mode.
IMGCODEC_FILE *imageCodec_fopen_memory(u8 *data, u32 size);  // Memory mode.

s32 imageCodec_loadFS(ImgFSFunc_st *pFuncFS, u8 bIsFile, u8 *buffer, u32 bufferSize, u32 cacheSize, u32 fpos);

void imageCodec_reqCPUSpeed(int level);

u32  imageCodec_getQb(void);
u32  imageCodec_qb2ms(u32 qb);
u32  imageCodec_ms2qb(u32 ms);

void imageCodec_dbgTrace(u32 level, char *msg, ...);
void imageCodec_dbgError(u32 level, char *msg, ...);

image_Errmsg imageCodec_resourceLock(Image_Resource type);
image_Errmsg imageCodec_resourceUnlock(Image_Resource type);

u16 imageCodec_getLcdWidth(void);
u16 imageCodec_getLcdHeight(void);
#endif
#endif

