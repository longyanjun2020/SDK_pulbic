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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_supplicant.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#ifndef __MDL_SUPPLICANT_H__
#define __MDL_SUPPLICANT_H__

#if defined(__cplusplus)
extern "C" {
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define WPA_CMD_OPEN                    0x00043001
#define WPA_CMD_STOP                    0x00043002
#define WPA_CMD_SET_RESET               0x00043003
#define WPA_CMD_SET_SCAN                0x00043004
#define WPA_CMD_SET_CONNECT             0x00043005
#define WPA_CMD_SET_DISCONNECT		0x00043006
#define WPA_CMD_SET_CONFIGURATION	0x00043007
#define WPA_CMD_SET_POWER_SAVING	0x00043008
#define WPA_CMD_GET_SCAN_RESULTS	0x00043009
#define WPA_CMD_GET_CONFIGURATION	0x0004300A
#define WPA_CMD_GET_BSS	                0x0004300B
#define WPA_CMD_STOP_SCAN               0x0004300C
#define WPA_CMD_SET_BT_STATUS           0x0004300D
#define WPA_CMD_SET_FW_TEST             0x0004300E
#define WPA_CMD_GET_FW_TEST_RESULT      0x0004300F
#define WPA_CMD_SET_HW_REG              0x00043010
#define WPA_CMD_GET_HW_REG              0x00043011
#define WPA_CMD_SET_RXFILTER		0x00043012
#define WPA_CMD_GET_RXFILTER_RESULT	0x00043013
#define WPA_CMD_GET_AQU_FW_VER		0x00043014
#define WPA_CMD_SET_GSM_STATUS		0x00043015
#define WPA_CMD_SET_RF_REGISTER		0x00043016
#define WPA_CMD_GET_RF_REGISTER		0x00043017
#define WPA_CMD_SET_TX_SINTONE		0x00043018
#define WPA_CMD_SET_CONT_TX_STOP	0x00043019
#define WPA_CMD_SET_AQUA_MEM		0x0004301a
#define WPA_CMD_GET_AQUA_MEM		0x0004301b


#define WPA_EVENT_CONNECT_FAIL		0x00044001
#define WPA_EVENT_CONNECT_OK		0x00044002
#define WPA_EVENT_DISCONECTED		0x00044003
#define WPA_EVENT_ROMMING               0x00044004
#define WPA_EVENT_SCAN_DONE             0x00044005
#define WPA_EVENT_PASSWORD_FAIL		0x00044006
#define WPA_EVENT_FW_TEST_DONE		0x00044007

#define WPA_CMD_OK                      1
#define WPA_CMD_FAIL                    2
#define WPA_CMD_DATA_INVALID            3
#define WPA_CMD_NON_SUPPORT             4

/*=============================================================*/
// Data type definition
/*=============================================================*/
struct SupCmdSet {
	u32 cmd_id;				// Command ID
    u8* in_buf;             // Message buffer to wpa_supplicant
    u32 in_len;             // Message Length to wpa_supplicant
    u8 *out_buf;            // Message buffer from wpa_supplicant
    u32 out_len;            // Message Reserve Length from wpa_supplicant
    u32 ret_len;           	// Message Length from wpa_supplicant
    u32 status;				// Message status
};

#if defined(__cplusplus)
}
#endif

#endif // __MDL_SUPPLICANT_H__
