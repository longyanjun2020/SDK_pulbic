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

/**
 * @file drv_unfd_types.h
 * @brief
 */

#ifndef __DRV_UNFD_TYPES_H__
#define __DRV_UNFD_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_unfd_forward.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define  UNFD_ST_SUCCESS                   0

/*=============================================================*/
// Data type definition
/*=============================================================*/
struct _NAND_INFO
{
	U8	au8_Tag[16];
	U8	u8_IDByteCnt;
	U8	au8_ID[15];
	U32	u32_ChkSum;
	U16	u16_SpareByteCnt;
	U16	u16_PageByteCnt;
	U16	u16_BlkPageCnt;
	U16	u16_BlkCnt;
	U32	u32_Config;
	U16	u16_ECCType;
	U16	u16_SeqAccessTime;
	U8	padding[12];
	U8	au8_Vendor[16];
	U8	au8_PartNumber[16];
};

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype & definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __DRV_UNFD_TYPES_H__ */

