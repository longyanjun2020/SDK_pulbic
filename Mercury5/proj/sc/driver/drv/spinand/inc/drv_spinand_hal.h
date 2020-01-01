/*
 *#############################################################################
 *
 * Copyright (c) 2006-2011 MStar Semiconductor, Inc.
 * All rights reserved.
 *
 * Unless otherwise stipulated in writing, any and all information contained
 * herein regardless in any format shall remain the sole proprietary of
 * MStar Semiconductor Inc. and be kept in strict confidence
 * (!¡±MStar Confidential Information!¡L) by the recipient.
 * Any unauthorized act including without limitation unauthorized disclosure,
 * copying, use, reproduction, sale, distribution, modification, disassembling,
 * reverse engineering and compiling of the contents of MStar Confidential
 * Information is unlawful and strictly prohibited. MStar hereby reserves the
 * rights to any and all damages, losses, costs and expenses resulting therefrom.
 *
 *#############################################################################
 */
BOOL DrvSpinandIsActive(void);
BOOL DrvSpinandInit(SpinandInfo_t *gtSpinandInfo);
BOOL MDrv_SPINAND_ForceInit(SpinandInfo_t *gtSpinandInfo);
U8 MDrv_SPINAND_ReadID(U16 u16Size, U8 *u8Data);
U32 MDrv_SPINAND_Read(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
U32 MDrv_SPINAND_Write(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
U32 MDrv_SPINAND_BLOCK_ERASE(U32 u32_BlkIdx);
U32 MDrv_SPINAND_SetMode(SPINAND_MODE eMode);
U32 DrvSpinandWriteProtect(BOOL bEnable);
U32 MDrv_SPINAND_Read_RandomIn(U32 u32_PageIdx, U32 u32_Column, U32 u32_Byte, U8 *u8Data);
U32 DrvSpinandReadStatusRegister(U8 *u8Status, U8 u8Addr);
void MDrv_SPINAND_Device(struct device *dev);
void _spiNandMain(unsigned int dwSramAddress, unsigned int dwSramSize);

inline U32  MsSpinandCreateMutex (MsOSAttribute eAttribute, char *pMutexName, U32 u32Flag);
inline BOOL DrvSpinandInInterrupt (void);
inline BOOL DrvSpinandDeleteMutex(S32 s32MutexId);
inline BOOL MS_SPINAND_OBTAIN_MUTEX (S32 s32MutexId, U32 u32WaitMs);
inline BOOL DrvSpinandReleaseMutex (S32 s32MutexId);
