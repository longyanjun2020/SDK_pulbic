#ifndef __MMI_IF_WLAN_H__
#define __MMI_IF_WLAN_H__

/*=============================================================*/
/* Include Files                                               */
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_wlansrv.h"

/*=============================================================*/
/* Function Declarations                                       */
/*=============================================================*/
void    mmi_wlan_msg_parser (IBase *pRecipient, vm_msg_t *pData);
void    mmi_em_wlan_msg_parser(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_common_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_status_update_ind_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_scan_done_ind_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_get_bss_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_get_aqu_ver_if (IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_emapp_common_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_emapp_regnotify_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_emapp_get_result_if(IBase *pRecipient, vm_msg_t *pData);
void    mmi_wlan_emapp_common_data_if(IBase *pRecipient, vm_msg_t *pData);


#endif /* __MMI_IF_WLAN_H__ */
