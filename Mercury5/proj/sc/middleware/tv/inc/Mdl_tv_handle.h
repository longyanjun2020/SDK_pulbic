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

#ifndef __MDL_TV_HANDLE_H__
#define __MDL_TV_HANDLE_H__
#include "srv_ResMgr_MmlManager.h"
#include "srv_resmgr_mmltv_types.h"
#include "srv_resmgr_mml_api.h"
#include "vm_msgof.hc"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MdlTvMsg     vm_msg
#define true TRUE
#define false FALSE
#define TV_LEVEL                   _CUS2 | LEVEL_12

#define TV_TRACE(...)                 _TRACE((TV_LEVEL,__VA_ARGS__))
#define TV_ERROR(...)                 _ERROR((TV_LEVEL,__VA_ARGS__))

//#define MDL_TV_GET_MSG_BASE(msgID)   (u16)(msgID & 0xFFC0)

#ifdef __SDK_SIMULATION__
#define TV_ASSERT(_e_)  
#else
#define TV_ASSERT(_e_)	{\
						if(!(_e_))\
						{\
							extern void ker_assert_func(u8 * str, u8 * file, u32 line);\
							ker_assert_func( #_e_, __FILE__, __LINE__);\
						}\
					}
#endif /* __PC_SIMULATOR__ */

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
  MDL_TV_ATV,
  MDL_TV_DTV,
}Mdl_Tv_Type_e;

typedef enum
{
  MDL_TV_POWER_OFF,
  MDL_TV_POWER_ON,
  MDL_TV_PREVIEW_OFF,
  MDL_TV_PREVIEWING,
  MDL_TV_RETRIEVING,
}Mdl_Tv_State_e;



typedef enum
{
  MDL_TV_TIMER_START,
  MDL_TV_TIMER_STOP,
}Mdl_Tv_TimerAction_e;


typedef struct
{
  MmlUseCaseTvId_e          nUseCaseID;
  MmlTvResult_e             eResult;
  union{
    MmlTvRetrievalCompleteInfo_t          tEsgInfo;
    MmlTvScanResult_t                     tScanInfo;
    MmlTvTvInfo_t                         tTvInfo;
  }uPayload;
} Mdl_Tv_Response_t;


/*=============================================================*/
// Global Variable / Local function decalaration               *
/*=============================================================*/


/*=============================================================*/
// Global function definition                                  *
/*=============================================================*/






#endif //__MDL_TV_HANDLE_H__

