#ifndef DRV_MFD_MVC_DECODER_H
#define DRV_MFD_MVC_DECODER_H

#include <stdint.h>

#ifdef _MSC_VER
#define MVC_API __cdecl
#else
#define MVC_API
#endif

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
    int frameSize; // [NOTE] frameSize includes AuxBufferSize
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
    uint8_t nal_unit_size;
    uint8_t min_frame_count;
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

#endif /* DRV_MFD_MVC_DECODER_H */
