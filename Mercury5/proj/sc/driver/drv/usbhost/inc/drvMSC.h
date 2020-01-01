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

#ifndef _DRV_SCSI_H
#define _DRV_SCSI_H

#include "include/drvTypes.h"

#define MAX_COMMAND_SIZE	16
#define SCSI_SENSE_BUFFERSIZE    64

#define MAX_USTOR  8 // maximux mass storage device per root hub port
#define TEST_UNIT_READY         0x00
#define REQUEST_SENSE           0x03
#define INQUIRY                 0x12
#define MODE_SENSE              0x5a
#define MODE_SENSE6             0x1a
#define READ_CAPACITY           0x25
#define READ_10                 0x28
#define WRITE_10                0x2a
#define ATA_PASS_THROUGH_COMMAND        0xa1

#define TYPE_ROM                0x05
#define TYPE_SES                0x0d

#define SUCCESS         0x2002
#define FAILED          0x2003

#define IDENTIFY_BASE       0x80
#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |\
                ((can_disconnect) ?  0x40 : 0) |\
                ((lun) & 0x07))

#define DID_NO_CONNECT  0x01
#define DID_BAD_TARGET  0x04
#define DID_ABORT       0x05
#define DID_ERROR       0x07

#define SCSI_DATA_UNKNOWN       0
#define SCSI_DATA_WRITE         1
#define SCSI_DATA_READ          2
#define SCSI_DATA_NONE          3

#define MS_STAT_GOOD            0x00
#define MS_STAT_CHECK_CONDITION 0x02

#define CB_LENGTH_TEST_UNIT_READY   0x06
#define CB_LENGTH_REQUEST_SENSE     0x06
#define CB_LENGTH_INQUIRY           0x06
#define CB_LENGTH_MODE_SENSE        0x06
#define CB_LENGTH_READ_CAPACITY     0x0A
#define CB_LENGTH_READ_10           0x0A
#define CB_LENGTH_WRITE_10          0x0A
#define CB_LENGTH_ATA_PASS_THROUGH_COMMAND  0x0C

#define DATA_LENGTH_INQUIRY         36
#define DATA_LENGTH_MODE_SENSE      192
#define DATA_LENGTH_REQUEST_SENSE   18
#define DATA_LENGTH_READ_CAPACITY   8

typedef struct ScsiDevice
{
	/* Get by INQUIRY command */
	unsigned char u8DeviceType;
	unsigned char u8VendorID[8];
	unsigned char u8ProductID[16];
	unsigned char u8ProductVer[4];
} Scsi_Device;

struct scMsc_cmd
{
	U32 serial_number;
	unsigned char lun;
	unsigned char cmd_len;
	unsigned char sc_data_direction;
	unsigned char cmnd[MAX_COMMAND_SIZE];
	U32 req_buf_len;
	void *req_buf;
	int resid;
	unsigned char sense_buffer[SCSI_SENSE_BUFFERSIZE];
	//U32 flags; // NUSED
	void (*scsi_done) (struct scMsc_cmd *);
	int result;
	//unsigned char tag; // NUSED
};

typedef struct scMsc_cmd stCmd_scsi;

#define MS_MSC_WAIT_MUTEX_TIMEOUT  3000  //3sec

/* drvMSC.c */
//extern BOOL ms_bInit_USB_Disk(U8 uPort);
extern BOOL ms_bSCSI_Read_10(U8 uPort, unsigned char uLunNum, U32 u32BlockAddr, U32 u32BlockNum, unsigned char *u8Buffer);
extern BOOL ms_bSCSI_Write_10(U8 uPort, unsigned char uLunNum, U32 u32BlockAddr, U32 u32BlockNum, unsigned char *u8Buffer);
extern void ms_MSC_fast_device_disconnect(MS_U8 uDevS, MS_U8 uDevE);
extern void ms_MSC_device_inquiry(MS_U8 uDevS, MS_U8 uDevE);
extern BOOL ms_bSCSI_ATA_THRU_STANDBY(U8, U8, U8);

/* drvUSBDisk.c */
extern void RemoveUSBDiskPort(U8 uPort, U8 uLunNum);
extern BOOL ConnectUSBDisk(U8 uPort, U8 uLunNum);

#endif
