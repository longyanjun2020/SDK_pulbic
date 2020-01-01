/**
 * @file    mmi_if_ati.h
 * @brief   The file handles the ATI task event
 * @author  eric.chen@mstarsemi.com
 * 
 * @version $Id: mmi_if_ati.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_ATI_H__
#define __MMI_IF_ATI_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "esl_wifi_itf.h"

void mmi_ati_msg_parser(IBase *pRecipient, struct vm_msg *pData);

// void mmi_ati_ind_plug_if(IBase *pRecipient, struct vm_msg *pData);

void mmi_ati_resp_if(IBase *pRecipient, struct vm_msg *pData);
void mmi_ati_wcus_cmd_ind_if(IBase *pRecipient, struct vm_msg *pData);

typedef struct
{
	u8 *pRespStr;
	u16 u16RespStrLen;
} MAE_ATI_MSG_t;

// Wifi auto test for PC tool
void mmi_em_wifi_test_mode_off(MAE_Ret nRet);
void mmi_em_wifi_test_mode_on(MAE_Ret nRet);
void mmi_em_wifi_tx_test(MAE_Ret nRet);
void mmi_em_wifi_rx_moniter(MAE_Ret nRet, esl_WifiFwTstResult_t *pWifiFwTestResult);

#endif /* __MMI_IF_ATI_H__ */
