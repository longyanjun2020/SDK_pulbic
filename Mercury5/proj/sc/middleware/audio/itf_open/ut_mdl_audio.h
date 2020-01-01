////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef  __UT_MDL_AUDIOH__
#define  __UT_MDL_AUDIOH__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

#if defined(__SDK_SIMULATION__)

#define ut_AudVirtualHeadsetPlugin()     do{} while(0)
#define ut_AudVirtualHeadsetPlugout()    do{} while(0)
#define ut_AudDisableVirtualHeadset()    do{} while(0)

#else //#if defined(__SDK_SIMULATION__)

s32 ut_AudVirtualHeadsetPlugin(void);
s32 ut_AudVirtualHeadsetPlugout(void);
s32 ut_AudDisableVirtualHeadset(void);

#endif //#if defined(__SDK_SIMULATION__)
 /**
  *  @}
  */
#endif //__VM_AUDIO_H__
