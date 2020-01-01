/**
 * @file    mmi_req_bt.h
 * @brief   The file handles all the BT request function to BT Task
 * @author  christine.tai@mstarsemi.com
 *
 * $Id: $
 */
#ifndef __MMI_REQ_BT_H__
#define __MMI_REQ_BT_H__

#ifdef __BLUETOOTH_MMI__

#include "mmi_btsrv_def.h"
#include "mmi_btsrv_atcmd.h"
#include "drv_bt_api.h"


#ifdef __RES_MGR_DEBUG__
#define BTSRV_DEBUG_HISTORY
#endif


#ifdef BTSRV_DEBUG_HISTORY
//========================================//
//Debug History Info:
//Record messages between BTSRV & BT Task
//=========================================//
#define BTSRV_HISTORY_NUM               100
#define BTSRV_HISTORY_STR_MAX_LEN       8
#endif


#ifdef BTSRV_DEBUG_HISTORY
void _mmi_bt_add_msg_history_for_service(u16 u16ClsId, IBase* pRecipient, u16 msgType, u8 isReq, u32 param1, u32 param2);
void _mmi_bt_add_msg_history_for_service_ex(u16 u16ClsId, IBase* pRecipient, u16 msgType, u8 isReq, u32 param1, u8 *pStr, u32 uStrLen);
void _mmi_bt_add_msg_history(u16 msgType, u8 isReq, u32 param1, u32 param2);
void _mmi_bt_add_msg_history_ex(u16 msgType, u8 isReq, u32 param1, u8 *pStr, u32 uStrLen);
#endif


#ifdef BTSRV_DEBUG_HISTORY
typedef struct msgInfo
{
    u16         msgType;                            //The type of the message
    u8          isReq;                              //1: Req, 0: Cnf/Ind
    u32         param1;                             //Msg param1
    u32         param2;                             //Msg param2
    u8          pStr[BTSRV_HISTORY_STR_MAX_LEN];
} tMsgInfo;//19 bytes
#endif


#ifdef BTSRV_DEBUG_HISTORY
typedef struct BTMessageHistory_t_
{
    u8          u8NextIdx;
    tMsgInfo    tBTMessageHistory[BTSRV_HISTORY_NUM];
} BTMessageHistory_t;
#endif


#define MMI_LEVEL_BT MMI_LEVEL_27


#ifdef _MSIM_
void mmi_sim_set_BTSRVPTR(void * ptr);
void mmi_sim_set_BTOBEXSRVPTR(void * ptr);
void mmi_sim_set_BTFILESIZEREMAIN(u32 *pFileSizeRemain);
void mmi_sim_set_BTINQUIRY(u32 nInquiryTimer, bool bNoDevice);
#endif


void mmi_bt_power_onoff_req(BTSRV_PowerAction_e action);
void mmi_bt_inquiry_req(BTSRV_InquiryAction_e action);
void mmi_bt_acl_link_req(BTSRV_ACLLinkAction_e action, u8 *Addr);
void mmi_bt_auth_link_req(u8 *Addr);
void mmi_bt_name_query_req(u8 *Addr);
void mmi_bt_pin_code_rsp(u8 accept, u16 *PinCode, u8 *Addr);
void mmi_bt_delete_device_req(u8 *Addr);
void mmi_bt_set_local_name_req(MAE_WChar *localName);
void mmi_bt_set_discoverable_req(BTSRV_Discoverable_e action);
void mmi_bt_audio_link_req(BTSRV_AudioLink_e action, u8 *Addr, BTSRV_PROFILE_e profile);
//__BLUETOOTH_DRV_MSTAR__
void mmi_bt_audio_link_conn_rsp(boolean bIsAccept, u8 *Addr);
void mmi_bt_audio_call_req(BTSRV_AudioCallType_e action, BTSRV_PROFILE_e profile);
void mmi_bt_audio_mute_req(BTSRV_AudioMuteType_e mute);
void mmi_bt_audio_call_status_req(BTSRV_AudioCallStatus_e status,  u8* CallerID, u8 Type);
void mmi_bt_audio_atcmd_rsp(u8 *cmd, u8 *rsp);
void mmi_bt_audio_volume_req(s8 volume,BTSRV_PROFILE_e profile);


#ifdef __BLUETOOTH_DRV_MSTAR_ACRUX2__
void mmi_bt_loopback_test_req(u8 *pAddress, u32 hop_mode, u32 tx_channel, u32 rx_channel, u32 packet_type);
#endif


#ifdef __BLUETOOTH_OBEX_MMI__
void mmi_bt_obex_link_req(BTSRV_ObexLinkAction_e action, u8 *Addr);
void mmi_bt_obex_send_req(MAE_WChar *fileName, u32 fileSize, BTSRV_ObexCallback  Callback);
void mmi_bt_obex_send_rsp(BTSRV_ObexStatus_e status);
void mmi_bt_obex_receive_set_cb_req(BTSRV_ObexCallback  Callback);
void mmi_bt_obex_data_buff_rel_req(u8 *pAddr, BTOBEX_StatusWriteFile_e eStatus);
void mmi_bt_obex_receive_rsp(BTSRV_ObexStatus_e status);
void mmi_bt_pause_req(BTSRV_RecvAction_e eAction);
#endif //__BLUETOOTH_OBEX_MMI__


#ifdef __BLUETOOTH_NEW_CONTINUOUS_TX_FEATURE__
void mmi_bt_rf_test_mode_req(BTSRV_RfTestAction_e action, u32 Param, u32 DataMode, u32 Payload);
#else
void mmi_bt_rf_test_mode_req(BTSRV_RfTestAction_e action, u32 Param);
#endif


#ifdef __BLUETOOTH_A2DP_MMI__
void mmi_bt_a2dp_updateui_set_cb_req(BtA2dpUICallback  Callback);
void mmi_bt_a2dp_service_req(BTSRV_A2dpLinkAction_e eAction, u8 *Addr);
void mmi_bt_a2dp_link_req(BTSRV_A2dpLinkAction_e eAction, u8 *Addr);
void mmi_bt_a2dp_action_req(BTSRV_A2dpActionType_e eAction, u8 *Addr);
#endif


#ifdef __BLUETOOTH_A2DP_MMI__
#ifdef __BLUETOOTH_AVRCP_MMI__
void mmi_bt_avrcp_action_req(BTSRV_AvrcpActionType_e eAction, u8 *Addr, u32 u32Value);
void mmi_bt_avrcp_action_rsp(BTSRV_AvrcpActionType_e eAction, BTSRV_A2dpStatus_e eStatus);
#endif
#endif


void mmi_bt_sdp_service_req(u8 *Addr);
void mmi_bt_clip_req(u8 *CallerID, u8 type);


#endif //__BLUETOOTH_MMI__

#endif /* __MMI_REQ_BT_H__ */
