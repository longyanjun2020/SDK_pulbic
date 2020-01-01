/**
 * @file    mmi_req_cdwap.h
 * @brief   The file handles the cdwap event with wap task
 * @author  
 *
 * $Id:$
 */
#ifndef __MMI_REQ_CDWAP_H__
#define __MMI_REQ_CDWAP_H__

#ifdef __WAP_MMI_CDWAP__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

//-----------
#include "wap_define.hi"

//-----------
//For simulator testing
#include "mmi_if_cdwap.h"



MAE_Ret mmi_cdwap_send_cmd_req(WapEvent_t *WapEvt);
MAE_Ret mmi_cdwap_change_useragent_req(u8* pUserAgent);



#endif//__WAP_MMI_CDWAP__

#endif /* __MMI_REQ_CDWAP_H__ */
