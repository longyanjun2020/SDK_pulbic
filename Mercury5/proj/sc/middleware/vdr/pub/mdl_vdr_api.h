////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_api.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_API_H__
#define __MDL_VDR_API_H__

#include "srv_resmgr_mmlvideo_types.h"

typedef struct{
    MmlVideoRotationAngle_e EncodeRotation;
}vdr_extra_info_t;

typedef struct{
    MmlVideoUCParam_t mml;
    vdr_extra_info_t extra;
} vdr_usecase_param_t;

void MdlVdrMainTaskInit(void *);
void MdlVdrVideoTaskInit(void *);
void MdlVdrAudioTaskInit(void *);
void MdlVdrWriteTaskInit(void *);
void MdlVdrMainTask(vm_msg_t * arg);
void MdlVdrVideoTask(vm_msg_t * arg);
void MdlVdrAudioTask(vm_msg_t * arg);
void MdlVdrWriteTask(vm_msg_t * arg);
void MdlVdrParseUseCase(void *pUseCaseParam, u32 nUseCaseParamSize, u32 nUserData);
void MdlVdrNotifyCallback(u16 nSenderID, u32 nUserValue, MmlVideoNotify_t *pVideoNotify);
int MdlVdrRegAudRawDataCb(void (*fn)(void*, int));
void MdlVdrUnRegAudRawDataCb(void);

// forward declaration
typedef struct av_info_s _av_info_s;
typedef struct avmux_s _avmux_s;
S32 _MdlVdrMuxerInit(void * precInst, _av_info_s *pav_info, _avmux_s *pmuxer); //temp
S32 _MdlVdrMuxerDeInit(_avmux_s *pmuxerm, U8 bDel3gp); // temp

#if defined(__VT_3G324M__)
S32 Vdr_GetMediaData(U8 *buf, U32 *size, U32 *type);    // temp
#endif

#if defined(__I_SW__)
void MdlVdrVideoTask_isw(void);
#endif
#endif //__MDL_VDR_API_H__

