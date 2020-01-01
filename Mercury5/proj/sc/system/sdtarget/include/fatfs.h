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

/**
 * @file    fatfs.h
 * @brief   This module defines the FAT API layer 
 */
#ifndef __FATFS_H__
#define __FATFS_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "stdcomp.h"

/*--------------------------------------------------------------------------*/
/* CONSTANT DEFINITIONS */
/*--------------------------------------------------------------------------*/
#define FS_ERR_NOERR 0     /* No error */
#define FS_ERR_IO -1     /* I/O error */
#define FS_ERR_INVAL -2    /* Invalid argument */
#define FS_ERR_NOENT -3    /* No such entity */
#define FS_ERR_EOF -4  /* End of file reached */
#define FS_ERR_NOMEM -5    /* Out of memory */
#define FS_ERR_MIUADDR -6    /* Invalid MIU addr */
#define FS_ERR_NOTDIR -7   /* Not Directory */
#define FS_ERR_NOT512ALIGN -8
#define FS_ERR_INCONSIS -9

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
extern s32 FatfsReadFile(u32 nDmaAddr, u32 nOffset, u32 nDataCluster, u32 nRdSz);
extern s32 FatfsInit( void );


#endif //#ifndef __FATFS_H__
