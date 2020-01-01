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
* @file    mmi_phbapp_urlhandler.h
* @version $Id: mmi_phbapp_urlhandler.h 2010-01-13 11:30:23Z shin.lin $
* @brief   Phonebook AP decoupling header file,handle other ap launch phbapp URL request
*
*/

#ifndef __MMI_PHBAP_HANDLER_H__
#define __MMI_PHBAP_HANDLER_H__

#include "mmi_phbapp.h"
#include "mmi_phbapp_priv.h"
#include "mmi_log.h"

#include "mmi_UrlSrvClientHelper.h"
#include "mmi_UrlSrvUtil.h"
#include "mmi_UrlSrvCommonSchemeTbl.h"

__SLDPM_FREE__ boolean PhbAppLaunch(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

#endif /* __MMI_PHBAP_HANDLER_H__ */
