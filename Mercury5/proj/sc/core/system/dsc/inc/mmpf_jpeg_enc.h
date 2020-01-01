//==============================================================================
//
//  File        : mmpf_jpeg_enc.h
//  Description : INCLUDE File for the JPEG encode Function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_JPEG_ENC_H_
#define _MMPF_JPEG_ENC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "aitu_calendar.h"
#include "mmp_dsc_inc.h"
#include "drv_jpe_io_st_kernel.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define JPGENC_MAX_STREAM_NUM           (8)

#define JPGENC_OBUF_ALIGN_BASE          (32)

#define JPGENC_MAX_QUEUE_SIZE           (40)
#define JPGENC_MAX_QUEUE_WRAP_CNT       (0xFFFFFFFF)
#define JPGENC_INVALID_QUEUE_SIZE       (0xFFFFFFFF)

#define JPGENC_MAX_CAM_SEL_NUM          (MMP_JPEG_ENC_CAM_SEL_NUM)

#define JPGENC_YUV422_W_ALIGNMENT       (16)
#define JPGENC_YUV422_H_ALIGNMENT       (8)

#define JPGENC_YUV420_W_ALIGNMENT       (16)
#define JPGENC_YUV420_H_ALIGNMENT       (16)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    MMP_JPEG_ENC_CAM_SEL_PRM = 0,
    MMP_JPEG_ENC_CAM_SEL_SCD,
    MMP_JPEG_ENC_CAM_SEL_TRD,
    MMP_JPEG_ENC_CAM_SEL_NUM
} MMP_JPEG_ENC_CAM_SEL;

typedef enum
{
    MMP_JPEG_ENC_TYPE_PRM_MJPEG = 0,
    MMP_JPEG_ENC_TYPE_SCD_MJPEG,
    MMP_JPEG_ENC_TYPE_TRD_MJPEG,
    MMP_JPEG_ENC_TYPE_PRM_PRIMARY,
    MMP_JPEG_ENC_TYPE_SCD_PRIMARY,
    MMP_JPEG_ENC_TYPE_TRD_PRIMARY,
    MMP_JPEG_ENC_TYPE_PRM_THUMB,
    MMP_JPEG_ENC_TYPE_SCD_THUMB,
    MMP_JPEG_ENC_TYPE_TRD_THUMB,
    MMP_JPEG_ENC_TYPE_PRM_VR_THUMB,
    MMP_JPEG_ENC_TYPE_SCD_VR_THUMB,
    MMP_JPEG_ENC_TYPE_TRD_VR_THUMB,
    MMP_JPEG_ENC_TYPE_NUM
} MMP_JPEG_ENC_TYPE;

typedef enum
{
    MMP_JPEG_ENC_OP_NONE    = 0x00,
    MMP_JPEG_ENC_OP_START   = 0x01,
    MMP_JPEG_ENC_OP_PAUSE   = 0x02,
    MMP_JPEG_ENC_OP_RESUME  = 0x04,
    MMP_JPEG_ENC_OP_STOP    = 0x08
} MMP_JPEG_ENC_OP;

typedef enum
{
    MMP_JPEG_ENC_ATTR_ENC_W = 0,
    MMP_JPEG_ENC_ATTR_ENC_H,
    MMP_JPEG_ENC_ATTR_ENC_BUF_W,
    MMP_JPEG_ENC_ATTR_ENC_BUF_H,
    MMP_JPEG_ENC_ATTR_INPUT_FMT,
    MMP_JPEG_ENC_ATTR_MAX_SHOT_NUM,
    MMP_JPEG_ENC_ATTR_CAM_SEL,
    MMP_JPEG_ENC_ATTR_ENC_DONE_FLOW,
    MMP_JPEG_ENC_ATTR_ENC_COMP_TYPE,
    MMP_JPEG_ENC_ATTR_NUM
} MMP_JPEG_ENC_ATTR;

typedef enum
{
    MMP_JPEG_ENC_DONE_SIZE_CTL = 0,          ///< JPEG encode done then do size control
    MMP_JPEG_ENC_DONE_CONTINUOUS_SHOT,       ///< JPEG encode done then trigger continuous shot
    MMP_JPEG_ENC_DONE_UVC_MJPG,              ///< JPEG encode done then transfer by UVC
    MMP_JPEG_ENC_DONE_WIFI_MJPG,             ///< JPEG encode done then transfer by WIFI
    MMP_JPEG_ENC_DONE_VID_TO_MJPG,           ///< Video frame JPEG encode done then transfer by WIFI
    MMP_JPEG_ENC_DONE_NONE = 0xFF
} MMP_JPEG_ENC_DONE_MODE;

typedef enum
{
    MMP_JPEG_ENC_EVENT_ENC_DONE = 0,
    MMP_JPEG_ENC_EVENT_OBUF_FULL,
    MMP_JPEG_ENC_EVENT_MAX
} MMP_JPEG_ENC_EVENT;

typedef enum
{
    MMP_JPEG_ENC_RAW_YUYV = 0x0,
    MMP_JPEG_ENC_RAW_YVYU = 0x1,
    MMP_JPEG_ENC_RAW_NV12 = 0x3,
    MMP_JPEG_ENC_RAW_NV21 = 0x4,
} MMP_JPEG_ENC_RAW_FMT;

typedef enum
{
    MMP_JPEG_ENC_CALLBACK_CAPTURE_START = 0,
    MMP_JPEG_ENC_CALLBACK_STORECARD_START,
    MMP_JPEG_ENC_CALLBACK_STORECARD_END,
    MMP_JPEG_ENC_CALLBACK_STORECARD_ERROR
} MMP_JPEG_ENC_CALLBACK_TYPE;

typedef enum
{
    MMPF_JPEG_ENC_QUEUE_INPUT_Q = 0,
    MMPF_JPEG_ENC_QUEUE_DONE_Q,
    MMPF_JPEG_ENC_QUEUE_TYPE_NUM
} MMPF_JPEG_ENC_QUEUE_TYPE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef void JpegEncCallBackFunc(int);

typedef struct _MMPF_JPGENC_INSTANCE {
    MMP_BOOL                    bInitInst;      // The instance initialized or not
    MMP_USHORT                  usOperation;    // The operation from host command
    MMP_USHORT                  usStatus;       // The status of JPE engine
    MMP_ULONG                   ulInstId;       // Instance ID
    MMP_UBYTE                   ubRcIdx;        // Rate control ID
    MMP_UBYTE                   ubCamSel;       // The image source
    struct _MMPF_JPGENC_MODULE  *pModule;       // Pointer to connected module
    void                        *pCompHandle;   // Pointer to connected component
    JpeDev_t                    *pJpeDev;       // Pointer to JpeDev_t structure
    JpeCtx_t                    *pJpeCtx;       // Pointer to JpeCtx_t structure

    MMP_USHORT                  usEncW;         // The width of desired encoded frame
    MMP_USHORT                  usEncH;         // The height of desired encoded frame
    MMP_USHORT                  usEncBufW;      // The width of input frame
    MMP_USHORT                  usEncBufH;      // The height of input frame
    MMP_USHORT                  usMarkerW;      // The width of Marker
    MMP_USHORT                  usMarkerH;      // The height of Marker
    MMP_ULONG                   ulEncFmt;       // The color format of input frame
    MMP_USHORT                  usEncType;      // The encode type (Ref:JPE_COMP_USAGE)
    MMP_USHORT                  usEncDoneMode;  // The encode done mode
    MMP_ULONG                   ulCurShotCnt;   // The current shot count
    MMP_ULONG                   ulMaxShotCnt;   // The max shot count

    MMP_ULONG                   ulOutBufStPAddr;// The output buffer address (PA)
    MMP_ULONG                   ulOutBufEdPAddr;// The output buffer address (PA)
    MMP_ULONG                   ulOutBufSize;   // The output buffer size
    MMP_ULONG                   ulMarkerVAddr;  // The marker start address (VA)
    MMP_ULONG                   ulMarkerSize;   // The total marker size
} MMPF_JPGENC_INSTANCE;

typedef struct _MMPF_JPGENC_MODULE {
    MMP_BOOL                    bInitMod;       // The module initialized or not
    MMP_BOOL                    bWorking;       // The module is working or not
    MMPF_JPGENC_INSTANCE        *pJpeInst;      // Pointer to current instance
} MMPF_JPGENC_MODULE;

typedef struct _JPGENC_INPUT_ATTR {
    void*                       pComp;          // Linked Component Handle
    MMP_USHORT                  usEncId;        // Encode Instance ID
    MMP_ULONG                   ulInBufAddr;    // Input Buffer Address (VA)
    MMP_ULONG                   ulInBufSize;    // Input Buffer Size
    MMP_USHORT                  usInitQFactor;  // Encode Quality (Scale) Factor
    JpegEncCallBackFunc         *pfEncCBFunc;   // Encode Callback Function
    void*                       pEncCBFuncArg;  // Encode Callback Function Argument
    AUTL_DATETIME               stDateTime;     // Encode Time Stamp
    MMP_ULONG                   ulBufBias;      // Encode Buffer Bias.
} JPGENC_INPUT_ATTR;

typedef struct _JPGENC_DONE_ATTR {
    MMP_ULONG                   ulBSSize;       // Encoded Bitstream Size
    MMP_ULONG                   ulTotalSize;    // Encoded Total Size (Marker + Bitstream)
    MMP_USHORT                  usEncId;        // Encode Instance ID
    MMP_USHORT                  usEncType;      // Encode Type
    MMP_USHORT                  usEncDoneMode;  // Encode Done Mode
    MMP_ULONG                   ulEncBufAddr;   // Encode Buffer Address
} JPGENC_DONE_ATTR;

typedef struct _JPGENC_INPUT_QUEUE
{
    JPGENC_INPUT_ATTR           attr[JPGENC_MAX_QUEUE_SIZE];
    JPG_QUEUE_PTR               stQptr;
} JPGENC_INPUT_QUEUE;

typedef struct _JPGENC_DONE_QUEUE
{
    JPGENC_DONE_ATTR            attr[JPGENC_MAX_QUEUE_SIZE];
    JPG_QUEUE_PTR               stQptr;
} JPGENC_DONE_QUEUE;

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_DSC_CALLBACK *MMP_JPEG_ENC_ErrorStoreCardCallback;

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_BOOL MMPF_JPGENC_IsModuleInit(void);
MMP_ERR MMPF_JPGENC_InitModule(void);
MMP_ERR MMPF_JPGENC_DeinitModule(void);
MMPF_JPGENC_MODULE* MMPF_JPGENC_GetModule(void);
MMP_ERR MMPF_JPGENC_InitInstance(MMP_ULONG* InstId, void* pCompHandle);
MMP_ERR MMPF_JPGENC_DeInitInstance(MMP_ULONG ulInstId);
MMPF_JPGENC_INSTANCE* MMPF_JPGENC_GetInstance(MMP_ULONG ulInstId);
MMP_ERR MMPF_JPGENC_GetActiveInstNum(MMP_ULONG *pulOpenNum);

MMP_ERR MMPF_JPGENC_SetParameter(MMPF_JPGENC_INSTANCE   *pInst,
                                 MMP_JPEG_ENC_ATTR      eAttrib,
                                 MMP_ULONG              ulValue);
MMP_ERR MMPF_JPGENC_RegisterIntrCBFunc(MMP_JPEG_ENC_EVENT event, JpegEncCallBackFunc *pCallBack, void *pArgument);
MMP_USHORT MMPF_JPGENC_GetStatus(MMP_ULONG ulEncId);
MMP_BOOL MMPF_JPGENC_CheckMaxShotExceed(MMP_ULONG ulEncId);
MMP_USHORT MMPF_JPGENC_GetEncodeDoneMode(MMP_ULONG ulEncId);
MMP_ERR MMPF_JPGENC_GetJpegSize(MMP_UBYTE ubRcIdx, MMP_ULONG *ulJpegSize);
MMP_ERR MMPF_JPGENC_GetJpegBitBufAttr(MMP_UBYTE ubRcIdx, MMP_ULONG *ulJpegbufAddr, MMP_ULONG *ulJpegbufSize);

MMP_ERR MMPF_JPGENC_InputFrameReady(MMP_ULONG ulEncId, JPGENC_INPUT_ATTR stJpgEncAttr);
MMP_ERR MMPF_JPGENC_EncDonePostProcessing(void);

#endif // _MMPF_JPEG_ENC_H_
