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

#ifndef __MMI_FMSCHAPP_H__
#define __MMI_FMSCHAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_fmsch_cfg.h"
#include "mmi_alarmsrv.h"
#include "mmi_common_util.h"

#include "mmi_UrlSrvClientHelper.h"
#include "mmi_launcher_fmradio.h"
#include "mmi_common_fmsch_type.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/


/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

void FmSchPreNew(void);
MAE_Ret FmSchAppNew(MAE_ClsId id, void **ppObj);

#endif /* __MMI_ALARMAPP_H__ */
