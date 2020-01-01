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
* @file    hal_io_chip.h
* @version
* @brief   HAL header for GPIO of main chip
*
*/

#ifndef __HAL_IO_CHIP_H__
#define __HAL_IO_CHIP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/* register definition */
#define GPIO_CTRL_IN   0x01
#define GPIO_CTRL_OUT  0x02
#define GPIO_CTRL_OEN  0x04
#define GPIO_CTRL_DRV1 0x08
#define GPIO_CTRL_PE   0x10
#define GPIO_CTRL_PS   0x20
#define GPIO_CTRL_DRV  0x40
#define GPIO_CTRL_MODE 0x80

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    ePWM_0 = 0,
    ePWM_1,
    eMAX_PWM,
} PWM_NUM_e; 

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#define HalIoChipFastDwnGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
	(*(volatile u8 *)x) &= ~GPIO_CTRL_OUT; \
    }else{\
        (*(volatile u32 *)0x3400C1D4) &= ~(0x10<<(x&3));\
    }\
}while(0)

#define HalIoChipFastUpGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
	    (*(volatile u8 *)x) |= GPIO_CTRL_OUT; \
    }else{\
        (*(volatile u32 *)0x3400C1D4) |= (0x10<<(x&3));\
    }\
}while(0)

#define HalIoChipFastSetDirInputGpio(x) \
do { \
    if((x & 0x3400C100) != 0x3400C100){\
        (*(volatile u8 *)x) |= (GPIO_CTRL_OEN); \
        (*(volatile u8 *)x) |= GPIO_CTRL_MODE; \
    }else{\
            (*(volatile u32 *)0x3400C184) |= 0x4000;\
        (*(volatile u32 *)0x3400C1E8) |= (1<<4);\
        (*(volatile u32 *)0x3400C1E4) |= (1<<4);\
        (*(volatile u32 *)0x3400C184) |= 1;\
        *(volatile u32*) 0x3400C1B4 = 0x79;\
        if(x&3 == 0)\
            (*(volatile u32 *)0x3400C1D4)  |= (1<<0);\
        else\
            (*(volatile u32 *)0x3400C1E8) &= ~((1<<11)<<(x&3));\
    }\
}while(0)

#define HalIoChipFastAcqGpio(x)  ((x & 0x3400C100) == 0x3400C100)?((*(volatile u32 *)0x3400C1D4) & (0x100 << (x&3))) >> (8 + (x&3)):(*(volatile u8 *)x) & GPIO_CTRL_IN

#define HalIoChipFastSetDirOutputGpio(x, y) \
do { \
    if((x & 0x3400C100) == 0x3400C100){\
        (*(volatile u32 *)0x3400C184) |= 0x4000;\
        (*(volatile u32 *)0x3400C1E8) |= (1<<4);\
        (*(volatile u32 *)0x3400C1E4) |= (1<<4);\
        (*(volatile u32 *)0x3400C184) |= 1;\
        *(volatile u32*) 0x3400C1B4 = 0x79;\
         (*(volatile u32 *)0x3400C1D4) &= ~(0x10<<(x&3));\
         (*(volatile u32 *)0x3400C1D4) |= ((y<<4)<<(x&3));\
        if(x&3 == 0)\
            (*(volatile u32 *)0x3400C1D4)  &= ~(1<<0);\
        else\
            (*(volatile u32 *)0x3400C1E8) |= ((1<<11)<<(x&3));\
    }else{\
        if(y != VM_IO_SKIP){ \
            (*(volatile u8 *)x) &= ~GPIO_CTRL_OUT; \
            (*(volatile u8 *)x) |= y << 1; \
        } \
        (*(volatile u8 *)x) &= ~GPIO_CTRL_OEN; \
        (*(volatile u8 *)x) |= GPIO_CTRL_MODE; \
    }\
}while(0)

#endif //__HAL_IO_CHIP_H__

