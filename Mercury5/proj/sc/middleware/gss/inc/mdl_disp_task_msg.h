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

#ifndef __MDL_DISP_TASK_MSG_H__
#define __MDL_DISP_TASK_MSG_H__

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    u32 nUseCaseID;      //UpdateScreenApp,UpdateScreenMdl,UpdateScreenAppEx
    u32 nPanelID;
    union
    {
   	    MSUPDATELAYER tSrcCpy;
        MSUPDATE tUpdate;
    } uParam;
} MdlDispTaskParam_t;

typedef union
{
  MdlDispTaskParam_t    tMdlDispTaskParam;
} vm_msgBody_t;


#include "vm_msgt.ht"

/*=============================================================*/
// Variable definition
/*=============================================================*/




/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __MDL_DISP_TASK_MSG_H__
