//==============================================================================
//
//  File        : mmpf_mp4venc.h
//  Description : Header function of video codec
//  Author      : Will Tseng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_MP4VENC_H_
#define _MMPF_MP4VENC_H_

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "mmpf_h264enc.h"
#include "mmp_vidrec_inc.h"

/** @addtogroup MMPF_VIDEO
@{
*/

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_VIDENC_QUEUE_TYPE {
    MMPF_VIDENC_QUEUE_INPUT_Q = 0,
    MMPF_VIDENC_QUEUE_DONE_Q,
	MMPF_VIDENC_QUEUE_DMAGEN_Q,
    MMPF_VIDENC_QUEUE_TYPE_NUM
} MMPF_VIDENC_QUEUE_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef void MMPF_VIDENC_Callback(void);

typedef struct _MMPF_VIDENC_MODULE {
    MMP_BOOL                bInitMod;
    MMPF_H264ENC_MODULE     H264EMod;
} MMPF_VIDENC_MODULE;

typedef struct _MMPF_VIDNEC_INSTANCE {
    MMP_BOOL                bInitInst;
    MMPF_VIDENC_MODULE      *Module;
    MMPF_H264ENC_ENC_INFO   h264e;
} MMPF_VIDENC_INSTANCE;

typedef struct _VIDENC_QUEUE_PTR {
    MMP_ULONG               ulWrWrap;
    MMP_ULONG               ulRdWrap;
    MMP_ULONG               ulWrIdx;
    MMP_ULONG               ulRdIdx;
} VIDENC_QUEUE_PTR;

typedef struct _VIDENC_INPUT_QUEUE {
    VIDENC_INPUT_ATTR       attr[VIDENC_MAX_QUEUE_SIZE];
    VIDENC_QUEUE_PTR        stQptr;
} VIDENC_INPUT_QUEUE;

typedef struct _VIDENC_DONE_QUEUE {
    VIDENC_DONE_ATTR        attr[VIDENC_MAX_QUEUE_SIZE];
    VIDENC_QUEUE_PTR        stQptr;
} VIDENC_DONE_QUEUE;

typedef struct _VIDENC_DMAGEN_QUEUE {
	VIDENC_INPUT_ATTR       attr[VIDENC_MAX_QUEUE_SIZE];
    VIDENC_QUEUE_PTR        stQptr;
} VIDENC_DMAGEN_QUEUE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#define get_vidinst_id(_p)          ((MMPF_VIDENC_INSTANCE*)(_p) - MMPF_VIDENC_GetInstance(0))

MMPF_VIDENC_MODULE* MMPF_VIDENC_GetModule(void);
MMPF_VIDENC_INSTANCE* MMPF_VIDENC_GetInstance(MMP_ULONG ulInstId);

// Initialize Functions
MMP_BOOL    MMPF_VIDENC_IsModuleInit(void);
MMP_ERR     MMPF_VIDENC_InitModule(void);
MMP_ERR     MMPF_VIDENC_DeinitModule(void);
MMP_ERR     MMPF_VIDENC_InitInstance(MMP_ULONG *pulInstId, MMP_USHORT usStreamType, MMP_USHORT usRcMode, void* pCompHandle);
MMP_ERR     MMPF_VIDENC_DeInitInstance(MMP_ULONG ulInstId);
MMP_ULONG   MMPF_VIDENC_GetActiveInstCnt(void);

// Timer Function
MMP_ERR     MMPF_VIDENC_EnableTimer(MMP_BOOL bEnable);
MMP_BOOL    MMPF_VIDENC_IsTimerEnabled(void);

// Video Encode Function
MMP_ERR     MMPF_VIDENC_StopAllRecord(void);
MMP_ERR     MMPF_VIDENC_PreEncode(MMPF_H264ENC_ENC_INFO *pEnc);
MMP_ERR     MMPF_VIDENC_Start(MMPF_H264ENC_ENC_INFO *pEnc);
MMP_ERR     MMPF_VIDENC_Pause(MMPF_H264ENC_ENC_INFO *pEnc);
MMP_ERR     MMPF_VIDENC_Resume(MMPF_H264ENC_ENC_INFO *pEnc);
MMP_ERR     MMPF_VIDENC_Stop(MMPF_H264ENC_ENC_INFO *pEnc);
MMP_ERR     MMPF_VIDENC_InputFrameReady(MMP_UBYTE ubEncID, VIDENC_INPUT_ATTR stEncAttr);
MMP_BOOL    MMPF_VIDENC_CheckCapability(MMP_ULONG ulTotalMB, MMP_ULONG ulFps);

// Set/Get Parameter Function
MMP_ERR     MMPF_VIDENC_SetMfeResrc(MMPF_H264ENC_ENC_INFO *pEncInfo, MMP_ULONG ulPixFmt, MMP_LONG lOutlen, MMP_ULONG lInLen);
MMP_ERR     MMPF_VIDENC_SetMfeMotion(MMPF_H264ENC_ENC_INFO *pEnc,
                                     MMP_ULONG ulDmvX, MMP_ULONG ulDmvY,
                                     MMP_ULONG ulSubPel, MMP_ULONG ulMvBlks0, MMP_ULONG ulMvBlks1);
MMP_ERR     MMPF_VIDENC_SetMfeSplit(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG ulRows, MMP_ULONG ulBits);
MMP_ERR     MMPF_VIDENC_SetVideoRes(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG ulEncW, MMP_ULONG ulEncH, MMP_ULONG ulEncBufW, MMP_ULONG ulEncBufH);
MMP_ERR     MMPF_VIDENC_SetVideoProfile(MMPF_H264ENC_ENC_INFO *pEnc, VIDENC_PROFILE eProfile);
MMP_ERR     MMPF_VIDENC_SetVideoLevel(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG ulLevel);
MMP_ERR     MMPF_VIDENC_SetVideoEntropy(MMPF_H264ENC_ENC_INFO   *pEnc,
                                        VIDENC_ENTROPY          entropy);
MMP_ERR     MMPF_VIDENC_SetVideoGOP(MMPF_H264ENC_ENC_INFO   *pEnc,
                                    MMP_USHORT              usPFrame,
                                    MMP_USHORT              usBFrame);
MMP_ERR     MMPF_VIDENC_SetRcMode( MMPF_H264ENC_ENC_INFO   *pEnc,
                                   VIDENC_RC_MODE          mode);
MMP_ERR     MMPF_VIDENC_SetRcSkippable(MMPF_H264ENC_ENC_INFO *pEnc, MMP_BOOL skip);
MMP_ERR     MMPF_VIDENC_SetRcSkipType( MMPF_H264ENC_ENC_INFO   *pEnc,
                                       VIDENC_RC_SKIPTYPE      type);
MMP_ERR     MMPF_VIDENC_SetRcLbSize(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG lbs);
MMP_ERR     MMPF_VIDENC_SetInitQP(MMPF_H264ENC_ENC_INFO   *pEnc,
                                  MMP_UBYTE               ubIQP,
                                  MMP_UBYTE               ubPQP);
MMP_ERR     MMPF_VIDENC_SetBitRate(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG updatebr);
MMP_ERR     MMPF_VIDENC_SetEncFrameRate(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG incr, MMP_ULONG resol);
MMP_ERR     MMPF_VIDENC_UpdateEncFrameRate(MMPF_H264ENC_ENC_INFO *pEnc, MMP_ULONG incr, MMP_ULONG resol);
MMP_ERR     MMPF_VIDENC_SetSnrFrameRate( MMPF_H264ENC_ENC_INFO *pEnc,
                                         MMP_USHORT            usStreamType,
                                         MMP_ULONG             incr,
                                         MMP_ULONG             resol);
MMP_ERR     MMPF_VIDENC_SetH264ForceICount(MMP_ULONG ulForceICount);
MMP_ERR     MMPF_VIDENC_GetParameter(MMPF_H264ENC_ENC_INFO  *pEnc,
                                     VIDENC_ATTRIBUTE       attrib,
                                     void                   *arg);

void        MMPF_VIDENC_SetStatus(MMP_ULONG ulEncId, MMP_USHORT status);
MMP_USHORT  MMPF_VIDENC_GetStatus(MMP_ULONG ulEncId);

/// @}

#endif	// _MMPF_MP4VENC_H_
