#ifndef MVC_DECODER_H
#define MVC_DECODER_H

#include <stdint.h>

#ifdef _MSC_VER
#define MVC_API __cdecl
#else
#define MVC_API
#endif

#define PIC_PRESERVE_REF(    y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y)    ] =  1)
#define PIC_PRESERVE_DISPLAY(y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y) + 1] =  1)
#define PIC_RELEASE_REF(     y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y)    ] =  0)
#define PIC_RELEASE_DISPLAY( y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y) + 1] =  0)
#define PIC_IS_REFFERED(     y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y)    ] != 0)
#define PIC_IS_WAITDISP(     y_ptr, flag_y) (((uint8_t *)(y_ptr))[(flag_y) + 1] != 0)

// enable one-to-one byte mapping using MBS
//#define MBS_MC_INT

/*
when UV_LINE_INTERLEAVE is not defined, the following frame format is used as default

+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                       |
|                                       |
|                                       |
|                   Y                   |
|                                       |
|                                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                   |
|         U         |
|                   |
+-+-+-+-+-+-+-+-+-+-+
|                   |
|         V         |
|                   |
+-+-+-+-+-+-+-+-+-+-+

If UV_LINE_INTERLEAVE is defined, each pair of U/V line is interleaved as shown below.
(padded and blanking areas are included if any).

+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                       |
|                                       |
|                                       |
|                   Y                   |
|                                       |
|                                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                   |                   |
|         U         |         V         |
|                   |                   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
#define UV_LINE_INTERLEAVE

#if !defined(SUPPORT_H263) && (defined(SUPPORT_M4V) || defined(SUPPORT_H263PP))
#define SUPPORT_H263
#endif

#ifdef _SUPPORT_2KX2K_
#define M4VDEC_MAX_WIDTH   2048
#define M4VDEC_MAX_HEIGHT  2048
#define M4VDEC_MAX_MB_WIDTH     128
#define M4VDEC_MAX_MB_HEIGHT    128
#define AVCDEC_MAX_DPB_SIZE 13056
#elif defined(_SUPPORT_1080I_)
#define M4VDEC_MAX_WIDTH   1920
#define M4VDEC_MAX_HEIGHT  1088
#define M4VDEC_MAX_MB_WIDTH     120
#define M4VDEC_MAX_MB_HEIGHT    68
#define AVCDEC_MAX_DPB_SIZE 12288
#elif defined(_SUPPORT_720P_)
#define M4VDEC_MAX_WIDTH   1280
#define M4VDEC_MAX_HEIGHT  720
#define M4VDEC_MAX_MB_WIDTH     80
#define M4VDEC_MAX_MB_HEIGHT    45
#define AVCDEC_MAX_DPB_SIZE 6750
#elif defined(_SUPPORT_D1_)
#define M4VDEC_MAX_WIDTH   720
#define M4VDEC_MAX_HEIGHT  576
#define M4VDEC_MAX_MB_WIDTH     45
#define M4VDEC_MAX_MB_HEIGHT    36
#define AVCDEC_MAX_DPB_SIZE 3038
#elif defined(_SUPPORT_CIF_)
#define M4VDEC_MAX_WIDTH   352
#define M4VDEC_MAX_HEIGHT  288
#define M4VDEC_MAX_MB_WIDTH     22
#define M4VDEC_MAX_MB_HEIGHT    18
#define AVCDEC_MAX_DPB_SIZE 892
#elif defined(_SUPPORT_QCIF_)
#define M4VDEC_MAX_WIDTH   176
#define M4VDEC_MAX_HEIGHT  144
#define M4VDEC_MAX_MB_WIDTH     11
#define M4VDEC_MAX_MB_HEIGHT    9
#define AVCDEC_MAX_DPB_SIZE 150
#else
#error "at lease one of resolution definition should be defined"
//#define M4VDEC_MAX_WIDTH   720
//#define M4VDEC_MAX_HEIGHT  576
//#define M4VDEC_MAX_MB_WIDTH     45
//#define M4VDEC_MAX_MB_HEIGHT    36
//#define AVCDEC_MAX_DPB_SIZE 3038
#endif

/* 1080I: 3427200 Byte, 720P: 1814400 Byte, SD: 816480 Byte */
#define AVCDEC_MAX_BUF_SIZE (1024*AVCDEC_MAX_DPB_SIZE/(384*M4VDEC_MAX_MB_WIDTH*M4VDEC_MAX_MB_HEIGHT)+1)*(84*M4VDEC_MAX_MB_WIDTH*M4VDEC_MAX_MB_HEIGHT)

//#define _UV_PLANAR_

#ifdef SUPPORT_AVC
#define FRAME_BUF_NUM   6
#elif defined(SUPPORT_WMV)
#define FRAME_BUF_NUM   6
#else
#define FRAME_BUF_NUM   4
#endif

#define M4V_HANDLE_SIZE 1000000

#define FRAME_Y_STRIDE_ALIGN_A 16
#define FRAME_C_STRIDE_ALIGN_A 16

#ifdef SUPPORT_AVC
#define M4VDEC_MEMORY_REQS  \
    ((((M4VDEC_MAX_WIDTH+32)+(FRAME_Y_STRIDE_ALIGN_A-1)) & ~(FRAME_Y_STRIDE_ALIGN_A-1))*16 /* Fake Y frame buffer for B-VOP decoding */ \
    +(((M4VDEC_MAX_WIDTH/2+16)+(FRAME_C_STRIDE_ALIGN_A-1)) & ~(FRAME_C_STRIDE_ALIGN_A-1))*8*2 /* Fake U,V frame buffer for B-VOP decoding */ \
    +(M4VDEC_MAX_MB_WIDTH)*(M4VDEC_MAX_MB_HEIGHT)*4 /* mbmd_buf[][]. 45, 36 should be the same as DEC_MBC and DEC_MBR. */ \
    +(M4VDEC_MAX_MB_HEIGHT)*(M4VDEC_MAX_MB_WIDTH)*4*2*2 /* CoMVx[][] and CoMVy[][] */ \
    +(M4VDEC_MAX_MB_WIDTH+1)*4*4*2 /* additional memory for backward mv's. */ \
    +M4V_HANDLE_SIZE \
    + 1500000 \
    + AVCDEC_MAX_BUF_SIZE + (M4VDEC_MAX_MB_HEIGHT)*(M4VDEC_MAX_MB_WIDTH)*16*4*2)
#else
#define M4VDEC_MEMORY_REQS  \
    ((((M4VDEC_MAX_WIDTH+32)+(FRAME_Y_STRIDE_ALIGN_A-1)) & ~(FRAME_Y_STRIDE_ALIGN_A-1))*16 /* Fake Y frame buffer for B-VOP decoding */ \
    +(((M4VDEC_MAX_WIDTH/2+16)+(FRAME_C_STRIDE_ALIGN_A-1)) & ~(FRAME_C_STRIDE_ALIGN_A-1))*8*2 /* Fake U,V frame buffer for B-VOP decoding */ \
    +(M4VDEC_MAX_MB_WIDTH)*(M4VDEC_MAX_MB_HEIGHT)*4 /* mbmd_buf[][]. 45, 36 should be the same as DEC_MBC and DEC_MBR. */ \
    +(M4VDEC_MAX_MB_HEIGHT)*(M4VDEC_MAX_MB_WIDTH)*4*2*2 /* CoMVx[][] and CoMVy[][] */ \
    +(M4VDEC_MAX_MB_WIDTH+1)*4*4*2 /* additional memory for backward mv's. */ \
    +M4V_HANDLE_SIZE)
#endif

#define MAX_BUF_STRIDE ((((((M4VDEC_MAX_WIDTH+40)+(FRAME_Y_STRIDE_ALIGN_A-1)) & ~(FRAME_Y_STRIDE_ALIGN_A-1))+(FRAME_Y_STRIDE_ALIGN_A*2-1))&~(FRAME_Y_STRIDE_ALIGN_A*2-1)))
#define M4VDEC_BUFFER_MEMORY_REQS \
    ((FRAME_BUF_NUM*(MAX_BUF_STRIDE*(M4VDEC_MAX_HEIGHT+40) + MAX_BUF_STRIDE*(M4VDEC_MAX_HEIGHT/2+16))) \
    +(63+16+16)*(FRAME_BUF_NUM-1)) /*64-byte alignment of ref(Y,U,V), for(Y,U,V)*/

#ifdef SUPPORT_M2V
#define M2VDEC_MEMORY_REQS  1000000
#define VID_MEMORY_REQS  (M2VDEC_MEMORY_REQS>M4VDEC_MEMORY_REQS) ? M2VDEC_MEMORY_REQS : M4VDEC_MEMORY_REQS
#else
#define VID_MEMORY_REQS  M4VDEC_MEMORY_REQS
#endif

#ifdef SUPPORT_WMV
#define WMV_SIM_VOP
#endif

#ifndef _PROCESSOR_NUMBER_
#define _PROCESSOR_NUMBER_ 1
#define _PROCESSOR_ID_ 0
#endif

// single process: do not define _READ_VLD_OUTPUT_ and _WRITE_VLD_OUTPUT_
// dual process-1st process: define _SYN_DEC_ and _WRITE_VLD_OUTPUT_
// dual process-2nd process: define _SEM_DEC_ and _READ_VLD_OUTPUT_

#if _PROCESSOR_NUMBER_ == 1
    #define _SYN_DEC_
    #define _SEM_DEC_
#elif _PROCESSOR_NUMBER_ == 2
  #if _PROCESSOR_ID_ == 0
    #define _SYN_DEC_
    #define _WRITE_VLD_OUTPUT_
  #elif _PROCESSOR_ID_ == 1
    #define _SEM_DEC_
    #define _READ_VLD_OUTPUT_
  #else
    #error "_PROCESSOR_ID_ not set correctly"
  #endif
#else
    #error "_PROCESSOR_NUMBER_ not set correctly"
#endif

//#define _SYN_DEC_
//#define _SEM_DEC_
//#define _READ_VLD_OUTPUT_
//#define _WRITE_VLD_OUTPUT_


typedef signed char    int1;
typedef signed char    int2;
typedef signed char    int3;
typedef signed char    int4;
typedef signed char    int5;
typedef signed char    int6;
typedef signed char    int7;

typedef unsigned char    uint1;
typedef unsigned char    uint2;
typedef unsigned char    uint3;
typedef unsigned char    uint4;
typedef unsigned char    uint5;
typedef unsigned char    uint6;
typedef unsigned char    uint7;

enum VID_FILTER_LEVEL
{
    VID_FILTER_ON,
    VID_FILTER_NON_REF_FILTER_OFF,
    VID_FILTER_FILTER_OFF,
};

#define VID_TICKS_PER_SECOND   1000000 //it is usec

// return values
#define VID_OK           0
#define VID_NO_MORE_FRAME   0x004   // for vidGetLastFrame
#define VID_NOT_CODED    -1
#define VID_SKIPPED      -2
#define VID_NO_MEMORY    -3
#define VID_EXIT         -4
#define VID_UNSUPPORTED  -5
#define VID_INVALID_ARG  -6
#define VID_ERR_VOL_INVALID_PROFILE       -10
#define VID_ERR_VOL_INVALID_PARA          -11
#define VID_ERR_VOL_UNSUPPORTED_BITSTREAM -12
#define VID_UNKNOWN      -15

// flags : used in m4vDecFrame()
#define VID_FLAGS          0x00F
#define VID_SKIP_FLAGS     0x003
#define VID_DECODE_FRAME   0x001
#define VID_SKIP_FRAME     0x002
#define VID_SKIP_GOP       0x003

#define VID_DECODE_FLAGS    0x00c
#define VID_DECODE_IPB_ONLY 0x000
#define VID_DECODE_IP_ONLY  0x004
#define VID_DECODE_I_ONLY   0x008

//flags:modifier : used in m4vInitDecoder()
#define VID_MODIFIERS      0xFF0
#define VID_MOD_NONE       0x100   //ISO, DIVX (4.xx), DX50 (5.xx)
#define VID_MOD_MP4V       0x110
#define VID_MOD_MP2V       0x120
#define VID_MOD_DIV3       0x130
#define VID_MOD_H263       0x190   // H.263, H.263+, H.263++
#define VID_MOD_FLV1       0X1A0
#define VID_MOD_VP30       0x1C0
#define VID_MOD_VP60       0x1D0
#define VID_MOD_VP70       0x1E0
#define VID_MOD_VP80       0x1F0
#define VID_MOD_MP41       0x210
#define VID_MOD_MP42       0x220
#define VID_MOD_MP43       0x230
#define VID_MOD_WMV1       0x240
#define VID_MOD_WMV2       0x250
#define VID_MOD_WMV3       0x260
#define VID_MOD_WMV7       0x270
#define VID_MOD_WMV8       0x280
#define VID_MOD_WMV9       0x290
#define VID_MOD_WMVA       0x2A0
#define VID_MOD_AVC1       0x2C0
#define VID_MOD_MP2        0x310
#define VID_MOD_RV10       0x380  // RV 1.0, not supported yet.
#define VID_MOD_RV20       0x390  // RV G2, not supported yet.
#define VID_MOD_RV30       0x3A0  // RV 8
#define VID_MOD_RV40       0x3B0  // RV 9 or RV 10
#define VID_MOD_RVCH       0x3C0  // RV file with header
#define VID_MOD_CAVS       0x3D0  // Chinese AVS


typedef struct VID_SETUP_S {
    int width;
    int height;
    uint8_t *bitstream; // the decoder buffer
    int length;      // the length of the decoder stream
    int consumed;
    int flags;       //DECODE_FRAME or SKIP_FRAME

#ifdef SUPPORT_WMV
#ifdef WMV_SIM_VOP
    char wmv_simvophdr;
#else
    char skip_frame;
#endif
#else
    char _space;
#endif
    uint8_t  enable_post_filter;

    uint16_t active_x, active_y;
    uint16_t stride_y, stride_uv;

    // for global buffer pool
    int frameSizeY;
    int frameSizeC;
    unsigned frameStartAlignY, frameStartAlignC;
    unsigned frameStrideAlignY, frameStrideAlignC;
    int offsetY, offsetCb, offsetCr;
    uint32_t offsetFlag_Y;      // relative to offsetY, 0:reference, 1:display
    uint8_t  needExtraBuf;

    uint32_t offsetAux;
    uint32_t AuxBufferSize;
    uint8_t  par_width;
    uint8_t  par_height;
    uint8_t  interlaced;
    uint1    ts_type;           // 0: pts  1: dts
    uint1    maxbuffersize;
    uint1    plain_mode;
    uint1    low_delay_mode;
    uint1   force_low_delay;
    void    *cbctx;             // application context for callback functions
    uint8_t nal_wo_startcode;
    uint8_t nal_frame_unit_size;
    uint8_t nal_config_unit_size;
    uint8_t min_frame_count;
    uint1   overlap_framebuf;
    uint1   use_frame_row_buffer;
    int     loopfilter_level;
} VID_SETUP;

typedef struct VID_PICTURE_S {
    void *packet;

#ifdef _WRITE_VLD_OUTPUT_
    uint8_t *vld_buf_ptr;
    int      vld_buf_size;
#else
    void *y;    // in/out
    void *u;    // in/out
    void *v;    // in/out
    void *aux_data;
#endif

    int64_t  pts;
    uint1    valid;
    int16_t  width;
    int16_t  height;
} VID_PICTURE;

typedef struct VID_OUTPUT_S {
    uint8_t *y;
    uint8_t *u;
    uint8_t *v;
    int y_pitch;
    int c_pitch;
    int width;
    int height;
    int row_num;
    int x_offset;
    int y_offset;
} VID_OUTPUT;

/* return non-zero to abort decoding process */
typedef int    (MVC_API * vidCallbackProgress)(void *context, int frame_num, int mb_num, int mb_total);
typedef int    (MVC_API * vidCallbackOutput)(void *ctx, VID_OUTPUT *src);
typedef void * (MVC_API * vidCallbackMalloc)(void *context, int size);
typedef void   (MVC_API * vidCallbackFree)(void *context, void *ptr);

typedef struct VID_CALLBACK_S
{
    /* return non-zero to abort decoding process */
    vidCallbackProgress pfnProgress;
    vidCallbackMalloc   pfnMalloc;
    vidCallbackFree     pfnFree;
    vidCallbackOutput   pfnOutput;
} VID_CALLBACK;

#ifdef __cplusplus
extern "C" {
#endif

void MVC_API vidInitAllPlugins(void);
int MVC_API vidInitDecoder(int *handle, VID_SETUP *setup,
#ifndef _SEM_DEC_
                   VID_PICTURE *pic,
#endif
                   uint8_t *decbuf, int *p_decbuf_size);
int MVC_API vidDecFrame(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidGetLastFrame(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidFiniDecoder(int handle);
void MVC_API vidGetRowBufSize(int handle, uint32_t *row_buffer_y_size, uint32_t *row_buffer_uv_size);
void MVC_API vidSetRowBuf(int handle, uint8_t *row_buffer_y, uint8_t *row_buffer_uv);

#ifdef SUPPORT_WMV
int MVC_API vidGetHeaderMode(int handle);
int MVC_API vidGetNumBFrames(int handle);
int MVC_API vidGetWmvVersion(int handle);
#endif

int MVC_API vidPostFilterFrame(VID_SETUP *setup, VID_PICTURE *pic);

void MVC_API vidSetExtraBuf(int handle, VID_PICTURE *decPicture, int index);
void MVC_API vidReSetExtraBuf(int handle, VID_PICTURE *decPicture, int index);

int MVC_API judge_avc_visual(VID_SETUP *setup);
int MVC_API judge_m4v_visual(VID_SETUP *setup);
int MVC_API judge_m2v_visual(VID_SETUP *setup);
int MVC_API judge_rv9_visual(VID_SETUP *setup);

int MVC_API vidDecIntraFrame(VID_SETUP *setup, VID_PICTURE *pic, void *heap, int heap_size, void *framebuf);
void MVC_API vidSetupCallback(VID_CALLBACK *callback);

#ifdef __cplusplus
}
#endif

#endif /* MVC_DECODER_H */
