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

#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

#include "drvMassStor.h"

/*=========Sub Classes=========*/
#define MS_RBC_SC       0x01    /* Typically, flash devices */
#define MS_ATAPI_SC     0x02    /* CD-ROM */
#define MS_QIC_SC       0x03    /* QIC-157 Tapes */
#define MS_UFI_SC       0x04    /* Floppy */
#define MS_SFF_SC       0x05    /* Removable media */
#define MS_SCSI_SC      0x06    /* Transparent */
#define MS_LSD_SC       0x07    /* LSD FS */
#define MS_DEVICE_SC    0xff    /* Use device's value */
/*=============================*/
/*==========Protocols==========*/
#define MS_CBI_PR       0x00    /* CBI */
#define MS_CB_PR        0x01    /* CB */
#define MS_BULK_PR      0x50    /* BOT */
#define MS_DEVICE_PR    0xff
/*=============================*/

struct stBulk_cb
{
	U32 Inscription;
	U32 Label;
	U32 DataLength;
	unsigned char   Flag;
	unsigned char   Lun;
	unsigned char   Len;
	unsigned char   CDB[16];
};

struct stBulk_cs
{
	U32 Inscription;
	U32 Label;
	U32 Remains;
	unsigned char   Class;
};

#define BULK_CB_WRAP_LEN    31
#define BULK_CB_SIGN        0x43425355
#define BULK_CS_WRAP_LEN    13
#define BULK_CS_SIGN        0x53425355

#define BULK_CS_OLYMPUS_SIGN    0x55425355
#define BULK_STAT_OK            0
#define BULK_STAT_FAIL          1
#define BULK_STAT_PHASE         2

#define BULK_RESET_REQUEST  0xff
#define BULK_GET_MAX_LUN    0xfe

#define XFER_GOOD		0
#define XFER_SHORT		1
#define XFER_STALLED		2
#define XFER_LONG		3
#define XFER_ERROR		4
#define XFER_NO_DEV		5

#define TRANSPORT_GOOD		0
#define TRANSPORT_FAILED	1
#define TRANSPORT_NO_SENSE	2
#define TRANSPORT_ERROR		3
#define TRANSPORT_NO_DEVICE	4

#define MS_CBI_ADSC     0

#if SupportOtherDevice
extern void ms_usb_qic157_command(stCmd_scsi*, struct ms_usdata*);
extern void ms_usb_ufi_command(stCmd_scsi*, struct ms_usdata*);
#endif
extern void ms_usb_transparent_scsi_command(stCmd_scsi*, struct ms_usdata*);
extern int ms_usb_CB_transport(stCmd_scsi*, struct ms_usdata*);
extern int ms_usb_CB_reset(struct ms_usdata*);
extern int ms_usb_bulk_transport(stCmd_scsi*, struct ms_usdata*);
extern int ms_usb_bulk_reset(struct ms_usdata*);
extern void ms_usb_invoke_transport(stCmd_scsi*, struct ms_usdata*);
extern int ms_usb_control_msg(struct ms_usdata *ptr, U32 pipe,
        unsigned char req, unsigned char rt, U16 val, U16 idx, void *data, U16 len, int time_out);
extern int ms_usb_msc_clear_halt(struct ms_usdata *ptr, U32 pipe);
extern int ms_usb_bulk_transfer_buf(struct ms_usdata *ptr, U32 pipe, void *buf, U32 len, U32 *act_len);
#endif
