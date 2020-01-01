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


#ifndef  __MDL_UT_BAT_PUB_H__
#define  __MDL_UT_BAT_PUB_H__

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

#define ut_BatVirtualChargerPlugin()     do{} while(0)
#define ut_BatVirtualChargerPlugout()    do{} while(0)
#define ut_BatDisableVirtualCharger()    do{} while(0)
#define ut_BatVirtualBatteryLow()        do{} while(0)
#define ut_BatVirtualBatteryFull()       do{} while(0)
#define ut_BatVirtualBatteryNormal()     do{} while(0)
#define ut_BatDisableVirtualBattery()    do{} while(0)

#else //#if !defined(__SDK_SIMULATION__)

s32 ut_BatVirtualChargerPlugin(void);
s32 ut_BatVirtualChargerPlugout(void);
s32 ut_BatDisableVirtualCharger(void);
s32 ut_BatVirtualBatteryLow(void);
s32 ut_BatVirtualBatteryFull(void);
s32 ut_BatVirtualBatteryNormal(void);
s32 ut_BatDisableVirtualBattery(void);

#endif //#if !defined(__SDK_SIMULATION__)

#endif //__MDL_UT_BAT_PUB_H__

