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
* @file    mmi_privateprotectpwapp.h
* @version
* @brief   Privateprotectpw header file
*
*/

#ifndef __MMI_PRIVATEPROTECTPWAPP_H__
#define __MMI_PRIVATEPROTECTPWAPP_H__ 

#ifdef __APP_MMI_PRIVATEPROTECT__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** BmiNew
* @brief        New function for create Privateprotectpw Applet
*
* @param[in]    nClsId                 Privateprotect class id
* @param[in]    ppObj               The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail
*
*/

MAE_Ret PrivateprotectpwAppNew
(
	MAE_ClsId nClsId,
	void **ppObj
);

#endif// __APP_MMI_PRIVATEPROTECT__
#endif /* __MMI_PRIVATEPROTECTPWAPP_H__ */
