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
/**
* @file mmi_offapp.h
*
* Class Id: CLSID_OFFAPP
*/
#ifndef __MMI_OFFAPP_H__
#define __MMI_OFFAPP_H__

/*-----------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_common_off_type.h"

/*
 * When OffApp is built as a sldlm (static load, dynamic link module), 
 * some functions/variables should be set as exception so that
 * the sldlm module can be loaded successfully.
 * The functions/variables associated with loading/unloading the sldlm
 * cannot be put into the sldm.
 * They should be given the __DLM_OFFAPP_FREE__ attribute so that
 * they are free from being compressed by the sldlm mechanism.
 *
 * To reduce the number of veneers, the attribute is set to be the same
 * with dpm.
 *
 * Principle: assign __DLM_OFFAPP_FREE__ to functions/data that are used
 * before the "new" function
 * */
#if defined(__DLM_OFFAPP_MMI__) && defined(__arm) && defined(__TARGET__)
#define __DLM_OFFAPP_FREE__ __attribute__((section(".sldpm_free")))
#else
#define __DLM_OFFAPP_FREE__
#endif


/**
 * Functions
 */
__DLM_OFFAPP_FREE__ MAE_Ret OffAppNew    (MAE_ClsId id, void **ppObj);
__DLM_OFFAPP_FREE__ MAE_Ret SwitchModeNew(MAE_ClsId id, void **ppObj);
__DLM_OFFAPP_FREE__ void    OffAppPreNew(void);
__DLM_OFFAPP_FREE__ void    SwitchModePreNew(void);
/*------------------------------------------------------------------------------*/
#endif /* __MMI_OFFAPP_H__ */
