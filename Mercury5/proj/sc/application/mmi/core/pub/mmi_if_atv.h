/**
 * @file    mmi_if_atv.c
 *
 * @brief   This file implements the functions which are used parse the confirmations from atv driver and send events to atv AP.
 * @author	sho.ding@mstarsemi.com
 *
 * @version $Id: mmi_if_atv.h 11319 2008-06-04 03:32:12Z allan.hsu $
 */

#ifndef __MMI_IF_ATV_H__
#define __MMI_IF_ATV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"



void mmi_atv_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_atv_common_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_open_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_close_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_config_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_awb_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_ae_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_af_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_zoom_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_ev_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_antiflicker_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_effect_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_attr_env_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_start_preview_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_stop_preview_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_start_capture_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_start_record_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_stop_record_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_atv_get_filename_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_atv_scan_channel_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_atv_get_info_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_atv_get_em_info_if(IBase *pRecipient, struct vm_msg *pData);
void mmi_atv_reg_notify_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_play_shutter_sound_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_capture_stop_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_vdo_position_update_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_vdo_rec_stop_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_vdo_rec_space_full_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_vdo_rec_error_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_atv_set_shutter_sound_if(IBase* pRecipient, struct vm_msg *pData);

void mmi_atv_resmgr_notify_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_ATV_H__ */
