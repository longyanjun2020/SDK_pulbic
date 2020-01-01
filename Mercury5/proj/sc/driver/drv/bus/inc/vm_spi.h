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
 * @page SPI_API SPI Interface
 *
 *
 * @section intro_sec Introduction
 *
 * This document describes the SPI bus Interface
 *
 *  <hr>
 * @section SectionMMI2SPI 1. MMI to SPI Interface
 *
 * @li @ref vm_spiOpen
 * @li @ref vm_spiClose
 * @li @ref vm_spiWrite
 * @li @ref vm_spiRead
 *
 *
 *  <hr>
 * @section Usage 2. Usage
 *
 *  The client first calls @ref vm_spiOpen to open a session on the SPI bus. This allocates the IOs used for this bus.
 *
 *  Then it can call @ref vm_spiWrite or/and @ref vm_spiRead to read and write data from/to the SPI bus.
 *
 *  A call to @ref vm_spiClose will close the session and free all resources (IOs) and powers off the SPI block.
 *
 *
 *
 *
 *
 *  <hr>
 *  @section Notes 3. NOTES
 *
 *  Current limitations :
 *
 *  \li 1. The clock speed cannot be changed during an opened session.
 *
 *
 */

/**
 * @file vm_spi.h
 * @brief API prototypes for SPI bus
 */

#ifndef __VM_SPI_H__
#define __VM_SPI_H__

#include "drv_vm_spi.h"

#endif /* __VM_SPI_H__*/

