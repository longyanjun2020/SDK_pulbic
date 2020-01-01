/*
 * netutility.h
 */
#ifndef __NET_UTILITY_H__
#define __NET_UTILITY_H__

//
// mi Media API
//
typedef struct MI_THUMBNAIL MI_THUMBNAIL;
MI_THUMBNAIL* miOpenThumbnail(char *filename, int *error);
MI_THUMBNAIL* miOpenLargeThumbnail(char *filename);
void miCloseThumbnail(MI_THUMBNAIL *handle);
int miGetThumbnail(MI_THUMBNAIL *handle, unsigned char **jpegbuf);
int miGetThumbnailSize(MI_THUMBNAIL *handle);
int miGetThumbnailDimension(MI_THUMBNAIL *handle, int *pwidth, int *pheight);

typedef struct {
    int     type;
    int     width;
    int     height;
    int     samplecount;
    int     timescale;
    int     duration;
    int     fps;
} MI_INFO;
int miGetMediaInfo(char *filename, MI_INFO *miInfo);

typedef struct {
    unsigned char* buf;
    int len;
} nalu_buf_t;
struct _MI_H264_SPS_INFO;
typedef struct _MI_H264_SPS_INFO MI_H264_SPS_INFO;

MI_H264_SPS_INFO* miH264GetSpsInfo(int idx);
void miH264InitSpsInfo(MI_H264_SPS_INFO* sps);
void miH264ModifySpsInfo(MI_H264_SPS_INFO* sps, MMP_USHORT w, MMP_USHORT h);
int miH264GenerateSps (nalu_buf_t *nalu_buf, MI_H264_SPS_INFO *sps);
int miH264GenerateSpsPpsNalu(nalu_buf_t * const sps_buf, nalu_buf_t *sps_pps_buf);
void start_station_service(void);
void stop_station_service(void);
void ns_convert_fn_fs_to_web(char* from, char* to);

#define USE_THREAD_SAFE_DCF_API (1)

/*
 * There is same declarations in ahc_dcf.h too.
 */
typedef struct _FFINST FFINST, *PFFINST;
typedef struct FF_ARG {//File Finder Arguments
    unsigned int format;
        #define GROUP_FLAG      (0x80)
        #define ALL_TYPE        (0x7f)
        #define DCF_TYPE_ALL    (-1)
        //type is extension file name, the index number synchronizes with m_DcfSupportFileType
        #define DCF_TYPE_ALL (-1)
        #define DCF_TYPE_JPEG (0)
        #define DCF_TYPE_AVI (2)
        #define DCF_TYPE_MOV (3)
        #define DCF_TYPE_MP4 (4)
        #define DCF_TYPE_3GP (5)
    unsigned char db; //which data base
        #define FF_DB_ALL (-1)
    unsigned char cam;
        #define FF_CAM_FRONT (0)
        #define FF_CAM_REAR  (1)
    unsigned char order; //This only works using node traversing
        #define FF_FORWARD (0)
        #define FF_BACKWARD (1)
    signed   char new_file;
        #define FF_ATTR_NEW (1)
        #define FF_ATTR_ANY (-1)
} FF_ARG;
typedef int (*FFN)(PFFINST hinst, char *inout, void* attr, FF_ARG* arg);

typedef struct {
    FFN     ffn;
    FF_ARG  arg;
} FFFILTER_FN;

typedef struct {
    unsigned short  grpid;  // Group ID
    unsigned short  grpno;  // Group File No
    unsigned short  grpto;  // Group File total
    unsigned short  dkey;
    unsigned short  fkey;
    unsigned char   grpmo;  // Group File mode as created
} FILE_GRPINFO;

#define NET_THUMBNAIL_WIDTH     (160)
#define NET_THUMBNAIL_HEIGHT    (96)

PFFINST FindFirstFile(char *inout, int bufsize, int *retsize, FFFILTER_FN* pfilter);
int FindNextFile(PFFINST hinst, char *out, int bufsize, int *retsize, FFFILTER_FN* pfilter);
int FindFileGroup(PFFINST hinst, FILE_GRPINFO *pinf);
#include "fs_api.h"
int FindFileAttr(PFFINST hinst, char *in, unsigned int* size, char** fmt, int *rd, FS_FILETIME *ft, int *new_file);
void *FindFileSetPosition(PFFINST hinst, int pos, FFFILTER_FN* pFilter);
int GetFrontFilename(char* front);
int wildstrcmp(char *s1, const char* ws2, int ws2len);

#endif  // __NET_UTILITY_H__
