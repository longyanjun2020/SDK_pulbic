#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

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

#ifndef MDL_IMGDEC_HANDLE_H
#define MDL_IMGDEC_HANDLE_H

#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"

#include "srv_ResMgr_MmlManager.h"
#include "srv_resmgr_mmlimage_types.h"
#include "vm_types.ht"

#include "imgcodec_common.h"
#include "vm_msgof.hc"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define NULL 0
#define MdlImg_msg     vm_msg
#define true TRUE
#define false FALSE

#define MDLIMG_STATECTRL_MBX        VM_MBX_CUS31
#define MDLIMG_MAIN_MBX             VM_MBX_CUS32
#define MDLIMG_INFO_MBX             VM_MBX_CUS35

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif

#ifdef __SDK_SIMULATION__
#include <assert.h>
#define ASSERT(_e_)  assert(_e_)
#else
#define ASSERT(_e_)	{\
						if(!(_e_))\
						{\
							extern void ker_assert_func(u8 * str, u8 * file, u32 line);\
							ker_assert_func( (u8*)#_e_, (u8*)__FILE__, __LINE__);\
						}\
					}
#endif /* __PC_SIMULATOR__ */

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
  MDL_IMG_STATE_IDLE,
  MDL_IMG_STATE_DECODING,
  MDL_IMG_STATE_STOPPING,
}Mdl_ImgDecode_State_e;



typedef enum
{
  MDL_IMG_TIMER_START,
  MDL_IMG_TIMER_STOP,
}Mdl_ImgDecode_TimerAction_e;



#define MDL_GET_IMGDEC_UCID(pMsg)           (MML_GET_IMAGE_UCID(&pMsg->Body.tImageUCParam))
#define MDL_GET_IMGDEC_CTL_MSGID(pMsg)      ((Mdl_ImgDecode_CtlMsgId_e)(pMsg->Body.tImageResponse.eMsgId))


typedef struct
{
  MmlUseCaseImageId_e       eUseCase;
  Mdl_ImgDecode_CtlMsgId_e  eMsgId;
  image_Errmsg              eErrCode;
  MmlImageDecodeCompleteInfo_t tDecodeCompleteInfo;
  union{
    MmlImageInfo_t          tImageInfo;
    void                    *pParam;
    s32                     nHandle;
  }uPayload;
} Mdl_ImgDecode_Response_t;

typedef struct
{
  u32                       pHandle;
  u32                       userValue;
} Mdl_ImgDecode_Handle_t;


/*=============================================================*/
// Global function definition                                  *
/*=============================================================*/


void MdlImgDecodeStateCtrlStateTask(void *pMessage);

void MdlImgDecodeStateCtrlTaskInit(void);

void MdlImgDecodeMainTask(void *pMessage);

void MdlImgDecodeMainTaskInit(void);

void GetImageInfo_Test(u16 *pInBuffer);

//PQ tool for display tuning
void DisplayTuningToImageDecoderReq(Mdl_ImgDecode_CtlMsgId_e eMsgId, image_Errmsg eErrCode, void *pPayload);

void GetImageInfo_Test(u16 *pInBuffer);
u32 Open_Test(void);
void Close_Test(void);
void Decode_Test(void);
void Abort_Test(u32 nHandle);

u32 MdlImgGetDecodingHandle(void);

#endif //MDL_IMGDEC_HANDLE_H
#endif

