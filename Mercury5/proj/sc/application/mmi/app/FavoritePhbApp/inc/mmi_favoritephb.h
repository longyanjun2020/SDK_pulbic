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
* @file    mmi_favoritephp.h
* @version $Id: mmi_favoritephp.h  $
* @brief   favorite Phonebook applet header file
*/

#ifndef __MMI_FAVORITEPHB_H__
#define __MMI_FAVORITEPHB_H__

/*Include*/
#include "mmi_phbsrv.h"
#include "mmi_filemgrapp.h"
#include "mmi_launcher_phb.h"

/*-------------------------------------------------------------------------*/
#include "mmi_srv_header.h"

/*Definitions*/
#define FAVORITE_PHB_ITEM_MAX_NUM                       (12)

/*Structure*/
typedef struct
{
	MmiPhbNumber_t	atNumber[FAVORITE_PHB_ITEM_MAX_NUM];
} MmiFavoritePhbData_t;

MAE_Ret FavoritePhb_New(MAE_ClsId id, void **ppObj);

#endif /* __MMI_FAVORITEPHB_H__ */
