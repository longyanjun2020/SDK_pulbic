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
 * @file    fmrx_i2c.h
 * @brief   This file defines the common header for EMA task
 */
#ifndef __FMRX_I2C_H__
#define __FMRX_I2C_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

//#define I2C_MODE_I2C
#define I2C_MODE_GPIO

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

void gpio_StartI2C(void);
void gpio_StopI2C(void);
void gpio_WriteI2C(u8 mode, u8 data);
u8 gpio_ReadI2C(u8 last_byte);
void dev_ConfigI2C(void);
void dev_WriteI2C_Byte(u8 addr, u8 reg, u8 data);
void dev_WriteI2C_Seq(u8 addr, u8* data, u8 size);
u8 dev_ReadI2C_Byte(u8 addr, u8 reg);
void dev_ReadI2C_Seq(u8 addr, u8* read_data, u8 size);
void dev_WriteI2C(u8 addr, u8* data, u8 size);
void dev_ReadI2C(u8 addr, u8* read_data, u8 size);

#endif /*__FMRX_I2C_H__ */
