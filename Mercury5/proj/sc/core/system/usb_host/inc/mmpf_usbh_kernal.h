//==============================================================================
//
//  File        : mmpf_usbh_kernal.h
//  Description : Header file for the USB HOST kernal function
//  Author      : Bruce_Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_KERNAL_H_
#define _MMPF_USBH_KERNAL_H_

#include "lib_retina.h"

//==============================================================================
//
//                              MACRO FUNC
//
//==============================================================================

#define USBH_TEMP_DBG_LOG_EN        (0)

#define SEPARATE_HEADER_RX          (0) // Separate 64B-448B-LEFT_B, USB_MCI least 32B 
#define EN_CALI_USE_SW_TMR          (1)
#define EN_DBGLOG_PFMC              (0)
#define EN_DBGLOG_RX_PFMC           (0)
#define EN_CHECK_AIT_TEST_PATTERN   (0)
#define EN_DUMP_H264_BS             (0)
#define EN_DUMP_YUV_FRM             (0) // Change gusUVCRxEpBufCnt to dump whole frame, e.g. (58)
#define EN_DUMP_MJPEG_FRM           (0)
#define EN_BENCH_LOG                (0)

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

#define USBH_H264_NALU_SIZE         (80)
#if (EN_DBGLOG_PFMC)
#define MAX_USBH_PFMC_PHASE         (51)
#define MAX_USBH_PFMC_ROUND         (10)
#endif
#if (EN_DBGLOG_RX_PFMC)
#define MAX_USBH_RX_PFMC_ROUND      (1890)
#endif
#if (EN_BENCH_LOG)
#define USBH_BCH_TIME_QUEUE_SIZE    (8)
#define USBH_BCH_DATA_QUEUE_SIZE    (8)
#endif

/* Error case of USB Rx */
#define USBH_ERR_RX_WRG_HDR_DAT     (0x00000001)    //wrong header data(uvc header and AIT header)
#define USBH_ERR_RX_WRG_WR_PTR      (0x00000002)    //wrong WR pointer, not frame size alignment
#define USBH_ERR_RX_WRG_2ND_WR_PTR  (0x00000004)    //wrong 2nd WR pointer
#define USBH_ERR_RX_WRG_FRM_SZ      (0x00000008)    //wrong frame size
#define USBH_ERR_RX_WRG_PL_HDR_SZ   (0x00000010)    //wrong payload + header size(physical transfer size)
#define USBH_ERR_RX_WRG_PL_TRANS_SZ (0x00000020)    //wrong payload transaction size
#define USBH_ERR_RX_WRG_SCHED_CNT   (0x00000040)    //wrong rx schedule count
#define USBH_ERR_RX_FRM_NOT_CPLT    (0x00000080)    //next frame comes before current frame rx complete

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/* Mgr/USBH handshake config */
typedef struct __attribute__((packed)) _MMPF_USBH_MGR_HS_CFG 
{
    /* Mgr notify USBH to close file by seamless record close file */
    MMP_UBYTE   ubVidMgrNotifyUVCForceI;        /* HS OP1: set flag */
    MMP_UBYTE   ubReqUVCForceIDone;             /* HS OP2: req force I done */
    MMP_UBYTE   ubGetUVCIDRFrm;                 /* HS OP3: get IDR frame */
    MMP_ULONG   ulFrmCntBeforeCloseCurFile;     /* # of frame RX after OP2 till OP3  */

    /* USBH notify Mgr to close file by UVC buffer overflow */
    MMP_UBYTE   ubNotifyVidMgr2StopRecordDone;  /* HS OP: notify Mgr done */
    MMP_UBYTE   ubSlowCardWaitReStartRecd;      /* HS OP: USBH wait restart video recd */

    /* Mgr notify USBH to stop UVC record by Mgr slow card */
    MMP_UBYTE   ubVidMgrNotifySlowCard;         /* HS OP: set flag */

    /* USBH maintain parameters of UVC record only */
    MMP_BOOL    bVidMgrUVCRecdSt;               /* UVC record start: MMP_TRUE/MMP_FALSE, trigger by frist I */
    MMP_BOOL    bGetRecdHdrDone;                /* get H264 SpsPpsHdr info from first I */
    MMP_UBYTE   ubH264Nalu[USBH_H264_NALU_SIZE];
    MMP_UBYTE   ubProfileIDC;
    MMP_UBYTE   ubLevelIDC;
} MMPF_USBH_MGR_HS_CFG ;

#if (EN_BENCH_LOG)
typedef struct _MMPF_USBH_BENCH_CFG 
{
    MMP_UBYTE ubEnShowLog;
    MMP_ULONG ulTimeIdx;
    MMP_ULONG ulDataIdx;
    MMP_ULONG ulSizeIdx;
    MMP_ULONG ulTime[USBH_BCH_TIME_QUEUE_SIZE];
    MMP_ULONG ulAddr[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulSAddr[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulDAddr[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulData[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulSize[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulSize2[USBH_BCH_DATA_QUEUE_SIZE];
    MMP_ULONG ulCntIdx;
    MMP_UBYTE ubStr[32];
} MMPF_USBH_BENCH_CFG ;
#endif

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if (EN_DBGLOG_PFMC)
extern MMP_ULONG    glUSBHPtx[MAX_USBH_PFMC_ROUND][MAX_USBH_PFMC_PHASE];
extern MMP_USHORT   gsUSBHPPIdx;
extern MMP_USHORT   gsUSBHPRIdx;
extern MMP_UBYTE    gbEnPFMC;
#endif
#if (EN_DBGLOG_RX_PFMC)
extern MMP_ULONG    gltmpStTime;
extern MMP_ULONG    gltmpEndTime;
extern MMP_ULONG    gltmpSeqNo;
extern MMP_ULONG    glDmaRxSt[MAX_USBH_RX_PFMC_ROUND];
extern MMP_ULONG    glDmaRxEnd[MAX_USBH_RX_PFMC_ROUND];
extern MMP_BYTE     gbDmaSType[MAX_USBH_RX_PFMC_ROUND];
extern MMP_ULONG    glDmaSeqNo[MAX_USBH_RX_PFMC_ROUND];
extern MMP_USHORT   gsDmaRxStIdx;
extern MMP_USHORT   gsDmaRxEndIdx;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (SUPPORT_SYNC_UVC_TIME)
MMP_ERR MMPF_USBH_StopCalibrationTimer(void);
MMP_ERR MMPF_USBH_StopSyncUVCTimer(void);
MMP_ERR MMPF_USBH_StartSyncUVCTimer(void);
#endif

MMP_UBYTE MMPF_USBH_IsSlowCardWaitReStartRecdSts(void);
MMP_ERR MMPF_USBH_SendErrMsg(MMP_UBYTE ubErrCase, MMP_ULONG ulParm0, MMP_ULONG ulParm1, MMP_ULONG ulParm2, MMP_ULONG ulParm3);
MMP_ERR MMPF_USBH_RstMgrHsState(void);
MMP_ERR MMPF_USBH_RstUVCRecdState(void);
#if (EN_BENCH_LOG)
MMPF_USBH_BENCH_CFG* MMPF_USBH_GetBchCFG(void);
MMP_ERR MMPF_USBH_SwitchShowLog(void);
#endif
void MMPF_USBH_ProcPacketHandler(MMP_UBYTE ubRxState);

#endif // _MMPF_USBH_KERNAL_H_
