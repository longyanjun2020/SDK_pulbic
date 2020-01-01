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

/**
* @file    mmi_ebookapp.h
* @version
* @brief   Ebook header file
*
*/
#ifndef __MMI_EBOOKAPP_H__
#define __MMI_EBOOKAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret EbookAppNew(MAE_ClsId id, void **ppObj);
void EbookPreNew(void);

#endif /* __MMI_EBOOKAPP_H__ */
