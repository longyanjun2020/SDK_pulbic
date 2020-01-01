//==============================================================================
//
//  File        : mmpf_dsc.h
//  Description : INCLUDE File for the DSC Driver Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_DSC_H_
#define _MMPF_DSC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_dsc_inc.h"

/** @addtogroup MMPF_DSC
@{
*/

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPF_CONTI_SHOT_INFO {
    MMP_ULONG           ulExifBufAddr;
    MMP_ULONG           ulShotCnt;
    MMP_ULONG           ulStoreFrmCnt;
    MMP_ULONG           ulMaxShotNum;
    MMP_UBYTE           ubCamSel;
    MMP_BOOL            bEnable;
} MMPF_CONTI_SHOT_INFO;

typedef struct _MMPF_MJPEG_ENC_FPS_INFO {
    MMP_ULONG           ulInputInc;
    MMP_ULONG           ulInputRes;
    MMP_ULONG           ulInputAcc;
    MMP_ULONG           ulOutputInc;
    MMP_ULONG           ulOutputRes;
    MMP_ULONG           ulOutputAcc;
} MMPF_MJPEG_ENC_FPS_INFO;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* Conti-Shot Function */
MMP_BOOL MMPF_ContiShot_IsWriteFileBusy(MMP_UBYTE ubCamSel);
MMP_BOOL MMPF_ContiShot_IsWriteFileDone(MMP_UBYTE ubCamSel);
MMP_ERR  MMPF_ContiShot_InitParam(MMP_UBYTE ubCamSel, MMP_ULONG ulExifBufAddr, MMP_ULONG ulMaxShotNum);

/* MJPEG Function */
MMP_ERR  MMPF_MJPEG_SetFpsInfo(MMP_ULONG ulInc, MMP_ULONG ulInRes, MMP_ULONG ulOutRes);
MMP_BOOL MMPF_MJPEG_FpsControl(void);

/* Store Function */
MMP_ERR  MMPF_DSC_SetFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR  MMPF_DSC_SetThumbFileName(MMP_ULONG ulFileNameAddr);
MMP_ERR  MMPF_DSC_JpegDram2Card(MMP_ULONG ulStartAddr, MMP_ULONG ulWritesize, MMP_BOOL bFirstwrite, MMP_BOOL bLastwrite);
MMP_ERR  MMPF_DSC_ThumbDram2Card(MMP_ULONG ulStartAddr, MMP_ULONG ulWriteSize);

#endif // _MMPF_DSC_H_
