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
* @file    drv_lcd_table.h
* @version
* @brief   LCD table driver private header file
*
*/

#if defined(__DRV_LCD_TABLE_C__)
#ifndef __DRV_LCD_TABLE_H__
#define __DRV_LCD_TABLE_H__

#include "stdcomp.h" /// for u8, u16, etc.


typedef enum
{
    I80_INTFAC = 0,
    M68_INTFAC,
    RGB_INTFAC,
    SPI_INTFAC,
    FMARK_INTFAC,
    MAX_INTFAC,
} lcd_interface_e;

typedef enum
{
    E_16BIT_CMD_8BIT_BUS_HL  = 0,
    E_16BIT_CMD_8BIT_BUS_LH  = 1,
    E_16BIT_CMD_16BIT_BUS    = 2,
    E_8BIT_CMD_8BIT_BUS      = 3,
    E_18BIT_CMD_18BIT_BUS    = 4,
    E_18BIT_CMD_8BIT_BUS_HL  = 5,
    E_18BIT_CMD_8BIT_BUS_LH  = 6,
    E_18BIT_CMD_9BIT_BUS_HL  = 7,
    E_18BIT_CMD_9BIT_BUS_LH  = 8,
    E_9BIT_CMD_9BIT_BUS_LH   = 9,
} lcd_cmd_bus_type_e;

typedef enum
{
    ADDRESS_FUNC = 0x01,             // Address -- Set LCD Register Address
    WRITE_FUNC = 0x02,               // Write Data -- Write LCD Register.
    READ_CMP_FUNC = 0x03,            // Read and compare data -- Read LCD Register and compare with the data
    DELAY_FUNC = 0x04,               // Delay -- Delay x ms
    X_FUNC = 0x05,                   // X -- Set Display Range Start X coordinate(16 bits)
    X_L_FUNC = 0x06,                 // X(L) -- Set Display Range Start X coordinate(Low byte)
    X_H_FUNC = 0x07,                 // X(H) -- Set Display Range Start X coordinate(High byte)
    Y_FUNC = 0x08,                   // Y -- Set Display Range Start Y coordinate(16 bits)
    Y_L_FUNC = 0x09,                 // Y(L)-- Set Display Range Start Y coordinate(Low byte)
    Y_H_FUNC = 0x0A,                 // Y(H)-- Set Display Range Start Y coordinate(High byte)
    X_A_W_FUNC = 0x0B,               // X+W-1 -- Set Display Range X+W-1 coordinate(16 bits)
    Y_A_H_FUNC = 0x0C,               // Y+H-1 -- Set Display Range Y+H-1 coordinate(16 bits)
    X_A_W_L_FUNC = 0x0D,             // X+W-1(L) -- Set Display Range X+W-1(L) coordinate(Low byte)
    X_A_W_H_FUNC = 0x0E,             // X+W-1(H) -- Set Display Range X+W-1(H) coordinate(High byte)
    Y_A_H_L_FUNC = 0x0F,             // Y+H-1(L) -- Set Display Range Y+H-1(L) coordinate(Low byte)
    Y_A_H_H_FUNC = 0x10,             // Y+H-1(H) -- Set Display Range Y+H-1(H) coordinate(High byte)
    CONFIG_API_FUNC = 0x11,          // Config the API for function 01, and function 02
    CONFIG_READ_TIMES_FUNC = 0x12,   // Config the parameter of DrvLcdReadCmdTimes()
    CONFIG_ID_MASK_FUNC = 0x13,      // Config the mask of read result of function 03
    PW_X_W_FUNC = 0x14,              // PW-X-W -- Set Display Range PanelWidth - X - width
    PW_X_1_FUNC = 0x15,              // PW-X-1 -- Set Display Range PanelWidth - X - 1
    PH_Y_H_FUNC = 0x16,              // PH-Y-H -- Set Display Range PanelHeight - Y - height
    PH_Y_1_FUNC = 0x17,              // Set Display Range PanelHeight - Y - 1
    MAX_FUNC
} lcd_function_e;


enum
{
    /**
     * Address is saved in a variable.
     * write a data to a register with a single API call
     * This is the default API type
     */
    API_REG_DATA_PAIR = 0,

    /**
     * Write register is an API call. Write data is another API call.
     * They are isolated. We can write to a register once, and write
     * multiple data.
     */
    API_ISOLATED_REG_DATA = 1,
    NR_API_TYPE
};

#ifdef __SDK_SIMULATION__
typedef struct
#elif defined(__GNUC__)
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u16 GI;
    u16 GL;
} lcdtbl_group_hdr_t;

#ifdef __SDK_SIMULATION__
typedef struct
#elif defined(__GNUC__)
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u16 cmd;
    u16 data;
} group_func_t;


#ifdef __SDK_SIMULATION__
typedef struct
#elif defined(__GNUC__)
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u16 GI;
    u16 GL;
    u16 *pData;
    u8  isRecord;
} lcdtbl_group_t;

typedef struct
{
    u32 Magic;
    u16 Vesion;
    u16 CID;
    u32 Size;
    u8 XBIT;
    u8 intfac;
    u16 GN;
    u16 X;
    u16 Y;
    u16 color_depth;
    u8  busExpand;
    u8  PixelClk;
    u32 PanelParameter;
    u16 reserve4;
    u16 reserve5;
} lcdtbl_hdr_t;

typedef enum
{
//#if defined(__CUS_LCM_TABLE_DRV__)
    E_LCM_TABLE,
//#endif

//#if defined(__CUS_DISPLAY_TABLE_DRV__)
//    E_DISP_TABLE,
//#endif

    E_NR_TABLE
} table_type_e;

typedef struct
{
    table_type_e eTableType;
    bool save_table_in_mem;
    u16 saved_CID;

    u8 driver_indx;
    u8 driver_count;
} search_table_param_t;

typedef u16 (*func_t)(u16 data);


#define LCD_TABLE_ID                0x434D434CUL  // "CMCL" -> revert of "LCMC"
#define CHECK_PATTERN               0x4c43        // "L""C"
#define LCM_TABLE_MAGIC             0x434c5444    // DTLC

#define CAST_TO_GI_TYPE(_x_)		 ((u16)(_x_))
#define LCD_GI_GET_DEVICE_ID		 CAST_TO_GI_TYPE(0)
#define LCD_GI_INIT  			     CAST_TO_GI_TYPE(1)
#define LCD_GI_SLEEP_MODE_ON  	     CAST_TO_GI_TYPE(2)
#define LCD_GI_SLEEP_MODE_CANCEL     CAST_TO_GI_TYPE(3)
#define LCD_GI_POWER_OFF  		     CAST_TO_GI_TYPE(4)
#define LCD_GI_PARTIAL_UPDATE  	     CAST_TO_GI_TYPE(5)
#define LCD_GI_SET_DISPLAY_RANGE     CAST_TO_GI_TYPE(6)
#define LCD_GI_CHECK_REG  		     CAST_TO_GI_TYPE(7)
#define LCD_GI_CHECK_INIT  		     CAST_TO_GI_TYPE(8)
#define LCD_GI_MAX					 (9)
#define LCD_GI_DISPLAY_TABLE         CAST_TO_GI_TYPE(0xFF01)
#define LCD_GI_LCM_INFO              CAST_TO_GI_TYPE(0xFF04)

#define CEIL4(_x_)                  ((((_x_) + 3) >> 2) << 2)

/**
 * given a pointer to lcd table header
 * point to the first group in the lcd table
 */
#define FIRST_GROUP_HDR(_pLcdTableHdr_)      ((lcdtbl_group_hdr_t *)((_pLcdTableHdr_) + 1))

/**
 * given a pointer to a lcd group header
 * point to the next group of the lcd table
 */
#define NEXT_GROUP_HDR(_pLcdGroupHdr_)   ((lcdtbl_group_hdr_t *)((u8 *)((_pLcdGroupHdr_) + 1) + (_pLcdGroupHdr_)->GL))

/**
 * given a pointer to a lcd group header
 * return the group ID
 */
#define GROUP_ID(_pLcdGroupHdr_)   ((_pLcdGroupHdr_)->GI)

/**
 * given a pointer to a lcd group header
 * return the group length
 */
#define GROUP_LENGTH(_pLcdGroupHdr_)   ((_pLcdGroupHdr_)->GL)

/**
 * given a pointer to a lcd group header
 * point to the data of the group
 */
#define GROUP_DATA(_pLcdGroupHdr_)   ((u16 *)((_pLcdGroupHdr_) + 1))

/**
 * given a pointer to a lcd group header
 * returns the number of function index in this group
 * (assuming every function has a parameter)
 */
#define GROUP_FUNCTION_NUM(_pLcdGroupHdr_)   (GROUP_LENGTH(_pLcdGroupHdr_) / 4)

/**
 * Check if LCM is detected by LCM table driver
 */
#define IsLCMRecoginzed()   (cur_if != MAX_INTFAC)


#endif // #ifndef __DRV_LCD_TABLE_H__
#else // #if defined(__DRV_LCD_TABLE_C__)

#error "only drv_lcd_table.c is allowed to include this header file"

#endif

