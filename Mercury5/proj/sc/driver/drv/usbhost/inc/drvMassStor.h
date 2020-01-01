//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef _USB_STOR_H_
#define _USB_STOR_H_

#include "include/drvUSBHost.h"
#include "include/drvBitops.h"

#include "drvUsbHostConfig.h"
#include "drvMSC.h"

struct ms_usdata;
struct stUnusual_dev
{
	const char* vendorName;
	const char* productName;
	unsigned char  useProtocol;
	unsigned char  useTransport;
	int (*initFunction)(struct ms_usdata *);
	U32 flags;
};

/* usb storage flag, bit indicator */
#define MS_SINGLE_LUN      0x00000001
#define MS_SCM_MULT_TARG   0x00000020
#define MS_FIX_INQUIRY     0x00000040
#define MS_FIX_CAPACITY    0x00000080

/* usb storage flag, bit indicator shift */
#define MS_IDX_URB_ACTIVE	    18
#define MS_IDX_ABORTING             20
#define MS_IDX_DISCONNECTING        21
#define MS_IDX_RESETTING            22

#define NO_SUBMIT   ((1UL << MS_IDX_ABORTING) | \
            (1UL << MS_IDX_DISCONNECTING) | (1UL << MS_IDX_RESETTING))

/* usb storage current operating state */
//#define IDLE_STATE          1 // there is the same copy in the drvKernel.h
//#define RUNNING_STATE       2
//#define RESETTING_STATE     3
//#define ABORTING_STATE      4

#define MAX_USB_MSC_LUNS    8

#define MS_IOBUF_SIZE   64 // there is the same copy in the drvKernel.h

typedef int (*trans_cmnd)(stCmd_scsi*, struct ms_usdata*);
typedef int (*trans_reset)(struct ms_usdata*);
typedef void (*proto_cmnd)(stCmd_scsi*, struct ms_usdata*);
typedef void (*extra_data_destructor)(void *);

struct ms_usdata
{
	S32     dev_mutex;
	struct usb_device   *pusb_dev;
	struct usb_interface    *pusb_intf;
	struct stUnusual_dev   *unusual_dev;
	U32     flags;
	U32     bulk_send_pipe;
	U32     bulk_recv_pipe;
	U32     ctrl_send_pipe;
	U32     ctrl_recv_pipe;
	U32     int_recv_pipe;
	char            vendor[MSC_STRING_LEN];
	char            product[MSC_STRING_LEN];
	char            serial[MSC_STRING_LEN];
	unsigned char           subclass;
	unsigned char           protocol;
	unsigned char           max_lun;
	unsigned char           ifnum;  //interface number
	unsigned char           bInterval_ep;
	trans_cmnd      transport;
	trans_reset     transport_reset;
	proto_cmnd      proto_handler;
	stCmd_scsi      srb;
	Scsi_Device     device;
	//int             usb_state; // NUSED
	struct urb      *current_urb;
	struct usb_ctrlrequest  *cr;
	unsigned char   *iobuf;
	dma_addr_t      cr_dma;
	dma_addr_t      iobuf_dma;
	//struct stCompletion   notify; // NUSED
	void            *extra;
	extra_data_destructor	extra_destructor;

	BOOL bDevInit;
	struct LUN_Device* msc_device;

	unsigned char   ustor_id;
	unsigned char   host_id;
};

struct LUN_Device
{
	unsigned char u8LunNum;
	unsigned char u8DevType;
	U32 u32BlockSize;
	U32 u32BlockSize_log2;
	U32 u32BlockTotalNum;
	BOOL bDeviceReady;
	BOOL bWriteProtect;
	BOOL bFSInit;
};

extern struct usb_driver usb_storage_driver;

#define SupportOtherDevice	1

extern int ms_usb_msc_control_thread(void * __us);
extern struct ms_usdata *Mass_stor_us[NUM_OF_ROOT_HUB*MAX_USTOR];

static inline void Clr_Stor_Dev_Info(MS_U8 us_id)
{
	Mass_stor_us[us_id] = NULL;
}

static inline BOOL Is_Stor_Dev_Info_Valid(MS_U8 us_id)
{
	return (Mass_stor_us[us_id] != NULL);
}

static inline BOOL Is_Stor_Dev_Init(MS_U8 us_id)
{
	return (Mass_stor_us[us_id] != NULL ? Mass_stor_us[us_id]->bDevInit : FALSE);
}

static inline void Set_Stor_Dev_Init(MS_U8 us_id, BOOL bInit)
{
	if (Mass_stor_us[us_id])
		Mass_stor_us[us_id]->bDevInit = bInit;
}

static inline unsigned char Get_Stor_Max_Lun(MS_U8 us_id)
{
	return (Mass_stor_us[us_id] != NULL ? Mass_stor_us[us_id]->max_lun : 0);
}

int ms_ioctl_issue_ctrl(struct ms_usdata *ms_us, void *pData);
int ms_ioctl_issue_bulk(struct ms_usdata *ms_us, void *pData);
bool quirk_bypass_stage(struct ms_usdata *ms_us, U32 stage_flag);
void quirk_list_init(void);
int quirk_list_add_3g(U32 vid_pid);

#define QUIRK_IGNORE_TUR        (BIT0)
#define QUIRK_IGNORE_CD_ROM     (BIT1)
#define QUIRK_IGNORE_RD_CAP     (BIT2)
#define QUIRK_IGNORE_MOD_SENSE  (BIT3)

#endif
