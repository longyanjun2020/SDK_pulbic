/**
 * @file    mmi_sssrv_util.h
 * @brief   xxxx
 * @version $Id: mmi_sssrv_util.h 12124 2008-06-30 07:48:27Z lih.wang $
 */
#ifndef MMI_SSSRV_UTIL_H
#define MMI_SSSRV_UTIL_H

#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"

void SSSRV_UtilFreeMsgDataModel(IBase *pOwner, u32 lParam, u32 dParam);

MAE_WChar *SSSRV_GetErrorCause(u16 errorCode);
#endif /* MMI_SSSRV_UTIL_H */
