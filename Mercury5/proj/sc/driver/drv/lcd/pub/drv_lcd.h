/****************************************************************************\
  @file     lcd_drv.h
  @brief    header file of LCD driver
  @date     2007/10/31
  @version  1.00
  @author
  @warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __LCD_DRV_H__
#define __LCD_DRV_H__


#include <string.h>
#include "vm_types.ht"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_traces.ho"


#define BRIDGE_TO_BYPASS_MODE     0x00
#define BYPASS_TO_BRIDGE_MODE     0x01

#define LCD_BPP              2
#define LCD_ESD_CHECK_TIME    (RTK_S_TO_TICK(2))
#define LCD_CHECK_TIME    (RTK_S_TO_TICK(2))
#define __LCD_CHECK_INIT_RECOVER__
#define LCD_CHECK_INIT_TIMES 5

#define LCD_DEFAULT_INIT_PANEL_COLOR 0x7777

#define __LCD_LOGO_BGCOLOR_PIXEL_0__
#define LCD_DEFAULT_START_PANEL_COLOR 0x0000
#define LCD_DEFAULT_BL_LEVEL 8 /*RANGE = 1-10*/

#define U16ColorToRGB888(u16Color,R8,G8,B8)  (  R8 = (U8)((u16Color>>8)&0xf8) + ((u16Color>>13)&0x7), \
                                                G8 = (U8)((u16Color>>3)&0xfc) + ((u16Color>>9)&0x3), \
                                                B8 = (U8)((u16Color<<3)&0xf8) + ((u16Color>>2)&0x7)  )

#define DISP_HW_BOUNDARY_LIMIT(addr,size) ((((u32)(addr)%0x800000)+ (size))>0x800000)

#define LCD_TRACE                  (_CUS1|LEVEL_11)


extern void sys_UartPrintf(const char *fmt, ...);


#if 0 // for rtpp

//#define LCD_DEBUG_SEND_TRACE

#ifdef LCD_DEBUG_SEND_TRACE

#define lcd_printf	sys_UartPrintf
#define lcd_debug(dbg_lv, str, ...)				\
	do {												\
													\
			lcd_printf(str, ##__VA_ARGS__);			\
    	} while(0)

#define lcd_send_trace(X) lcd_debug X

#else

#define lcd_send_trace(X) _TRACE(X)

#endif

#endif  // for rtpp




#if 0//def __LCD_PANEL_DETECT_BY_ADC_DRV__
/**
 *  @brief The structure defines the device information
 */
typedef enum {
  LCD_PANEL_TYPE_0 = 0, /* BYD - all view        (0v) */
  LCD_PANEL_TYPE_1,     /* TRULY                 (1.4v) */
  LCD_PANEL_TYPE_2,     /* BYD - single view     (1.1v)*/
  LCD_PANEL_TYPE_3,     /* Wistron - all view    (0.8v)*/
  LCD_PANEL_TYPE_4      /* Wistron - single view (1.4v)*/
}dev_LcdPanelType_e;
#endif

        /* ------------------------ Structures  ------------------------------ */


typedef enum
{
    LCD_16bit_CMD_16bit_BUS,
    LCD_8bit_CMD_8bit_BUS,
    LCD_18bit_CMD_18bit_BUS,
    LCD_16bit_CMD_8bit_BUS_HL,
    LCD_16bit_CMD_8bit_BUS_LH,
    LCD_18bit_CMD_8bit_BUS_HL,
    LCD_18bit_CMD_8bit_BUS_LH,
    LCD_18bit_CMD_9bit_BUS_HL,
    LCD_18bit_CMD_9bit_BUS_LH,
    LCD_9bit_CMD_9bit_BUS,
    LCD_8bit_CMD_DATA,
} dev_LcdCmdType_t;

typedef enum
{
    LCD_16bit_COLOR_DEPTH = 0x0,
    LCD_18bit_COLOR_DEPTH,
    LCD_8bit_COLOR_DEPTH,
    LCD_24bit_COLOR_DEPTH,
    LCD_24bit_COLOR_DEPTH_MSB6BIT,
    LCD_18bit_COLOR_DEPTH_24BITS,
} dev_LcdColorDepth_t;

typedef enum
{
    LCD_16BIT_IN16BIT = 0,
    LCD_LOW16BIT_IN18BIT,
    LCD_HIGH16BIT_IN18BIT,
    LCD_SHIFT16BIT_IN18BIT,
    LCD_LOW8BIT_IN9BIT,
    LCD_HIGH8BIT_IN9BIT,
} dev_LcdBusExpand_e;

typedef enum
{
    LCD_EnterSleep = 0,
    LCD_ExitSleep,
}LCD_SLEEPCTRL;

typedef enum
{
    LCD_NORMAL_PANEL = 0,
    LCD_FMARK_PANEL,
    LCD_VSYNC_PANEL,
    LCD_RGB_PANEL,
	LCD_SPI_PANEL,
} LCDPanelType_e;

typedef enum
{
    LCD_SEL_MAIN = 0,
    LCD_SEL_SUB,
    LCD_SEL_MAX
}  LCDPanelSel_e;


typedef enum
{
    LcdPixelClk_3M = 0,
    LcdPixelClk_5M,
    LcdPixelClk_6P5M,
    LcdPixelClk_9P75M,
    LcdPixelClk_13M,

    LcdPixelClk_15M,
    LcdPixelClk_19P9M,
    LcdPixelClk_26M,
    LcdPixelClk_30M,

    LcdPixelClk_31P2M,
    LcdPixelClk_39M,
    LcdPixelClk_44P5M,
    LcdPixelClk_52M,
    LcdPixelClk_60M,
} LcdPixelClk_e;


/// for SPI Panel
/*
0 : SCL_TYPE
1 : DATA_PACK_NON_8_BITES
2 : SKIP_START_BYTE
3 : START_BYTE_RW_BIT_R1_W0

4 : START_BYTE_RS_BIT_C1_D0
5 : THREE_WIRE_SPI_INTERFACE
6, 7 : RD_DATA_BYTE_CNT

8, 9 : CMD_BYTE_CNT
10, 11 : WR_DATA_BYTE_CNT

12 : READ_ID_WITH_START_BYTE
13 : USE_DUMMY_CYCLE
14, 15, 16 : DUMMY_RD_CNT
*/

enum
{
    SCL_TYPE_HL = 0x00000000,
    SCL_TYPE_LH = 0x00000001,
};

enum
{
    DATA_PACK_WITH_8_BITES = 0x00000000,
    DATA_PACK_NON_8_BITES = 0x00000002,
};

enum
{
    USE_START_BYTE = 0x00000000,
    SKIP_START_BYTE = 0x00000004,
};

enum
{
    START_BYTE_RW_BIT_R0_W1 = 0x00000000,
    START_BYTE_RW_BIT_R1_W0 = 0x00000008,
};

enum
{
    START_BYTE_RS_BIT_C0_D1 = 0x00000000,
    START_BYTE_RS_BIT_C1_D0 = 0x00000010,
};

enum
{
    FOUR_WIRE_SPI_INTERFACE = 0x00000000,
    THREE_WIRE_SPI_INTERFACE = 0x00000020,
};

enum
{
    ONE_BYTE_RD_DATA = 0x00000040,
    TWO_BYTE_RD_DATA = 0x00000080,
    THREE_BYTE_RD_DATA = 0x000000C0,
};

enum
{
    ONE_BYTE_CMD = 0x00000100,
    TWO_BYTE_CMD = 0x00000200,
};

enum
{
    ONE_BYTE_WR_DATA = 0x00000400,
    TWO_BYTE_WR_DATA = 0x00000800,
    THREE_BYTE_WR_DATA = 0x00000C00,
};

enum
{
    READ_ID_NOT_BY_START_BYTE = 0x00000000,
    READ_ID_WITH_START_BYTE = 0x00001000,
};

enum
{
    READ_ID_USE_DUMMY_BYTE_CNT = 0x00000000,
    READ_ID_USE_DUMMY_CYCLE = 0x00002000,
};

enum
{
    ZERO_DUMMY_RD_CNT = 0x00000000,
    ONE_DUMMY_RD_CNT = 0x00004000,
    TWO_DUMMY_RD_CNT = 0x00008000,
    THREE_DUMMY_RD_CNT = 0x0000C000,
    FOUR_DUMMY_RD_CNT = 0x00010000,
    FIVE_DUMMY_RD_CNT = 0x00014000,
    SIX_DUMMY_RD_CNT = 0x00018000,
    SEVEN_DUMMY_RD_CNT = 0x0001C000,
};

///




typedef struct
{
    void (* LCD_Init)               (u8 reInit);
    void (* LCD_SleepModeOn)        (void);
    void (* LCD_SleepModeCancel)    (void);
    void (* LCD_PowerOff)           (void);
    u16  (* LCD_GetDevice)          (u16 index);
    void (* LCD_SetDisplayRange)    (u16 x, u16 y, u16 width, u16 height);
    void (* LCD_WriteLogo)          (void);
	u16  (* LCD_GetStrInfo)         (u8 id, char *pStr, u16 maxLen);
} dev_LcdFunc_t;


typedef struct
{
    u16 device_code;
    u16 device_code_addr;
    dev_LcdCmdType_t  cmd_bit;
    dev_LcdColorDepth_t  color_depth;
    u16 x_size;
    u16 y_size;
    u16 stride;
    LcdPixelClk_e       PixelClk;   // config display engine clock
    dev_LcdBusExpand_e  busExpand;
    LCDPanelType_e      panel_type;
    u32                 panel_parameter;
    dev_LcdFunc_t lcdFun;
} dev_LcdConfig_t;

typedef struct
{
    bool x_Invert; /*TRUE is invert X axis*/
    bool y_Invert; /*TRUE is invert Y axis*/
} dev_LcdTSInfo_t;

typedef struct
{
    s16 id;
    dev_LcdCmdType_t  cmd_bit;
    u16 x_size;
    u16 y_size;
    u16 stride;
    u16 color_depth;
    LcdPixelClk_e       PixelClk;
    u8  sleep_on;
    u8  test;
    LCDPanelType_e      panel_type;
    u32                 panel_parameter;
} dev_LcdSetting_t;


typedef struct
{
    u8  index;
    u16 data;
} dev_LcdReg_t;


        /* ---------------------- Function Prototypes ------------------------ */

#ifndef __SDK_SIMULATION__
void DrvLcdPartialUpdateScreen(u16 x, u16 y, u16 w, u16 h, u16 *pixel, u32 len);
u16 LCD_GetDeviceID(void);
u16 DrvLcdGetLcdWidth(u8 nLcdSelect);
u16 DrvLcdGetLcdHeight(u8 nLcdSelect);
u16 DrvLcdGetDPM(u8 nLcdSelect);
void DrvLcdSleepModeOn(void);
void DrvLcdSleepModeCancel(void);
void DrvLcdPowerOff(void);
void DrvLcdInitHW(void);
void DrvLcdInitSW(void);
//void DrvLcdWriteLcd(PMSBLT_SRCCOPY pParam);
void DrvLcdSetDisplayRange(u16 x, u16 y, u16 width, u16 height);
u16 DrvLCDGetStrInfo(u8 id, char *pStr, u16 maxLen);

#ifdef __LCD_CHECK__
void LCD_CheckTimerCtrl(u8 Enable);
#endif//#ifdef __LCD_CHECK__


/**
 * @brief Lcd get tounch screen info
 *
 * @param       refresh_mmi  : refresh the screen using SurfMain
 *              color        : 16 bit 565 color to fill lcd
 *
 * @return                   : None
 */
void DrvLcdTest(u8 refresh_mmi, u16 color);

void DrvLcdLowLevelPowerOn(void);

/**
 *  @brief  Re-init LCD, the implementation should be the same with the implementation of
 *          DrvLcdLowLevelPowerOn between LCD_DRIVER_SEM consume and produce
 *
 *  @param  NONE
 *  @return void
 */
bool DrvLcdReinit(void);


/**
 * @brief Lcd on/off function for system power management count the total device ready to on
 *
 * @param    OnOff  : TRUE for ON, FALSE for OFF
 *
 * @return          : NONE
 */
void DrvLcdOnOff(bool OnOff);


/**
 * @brief To check current LCM power status (on/off)
 *
 * @param    NONE
 *
 * @return   :  FALSE: All power is off, otherwise is TRUE (parts of devices is on or all device is on)
 */
//bool LCD_CheckPowerStatus(void);
bool DrvLcdCheckPowerStatus(void);


/**
 * @brief Get current LCM flush time(write date to lcd screen updated)
 *
 * @param    NONE
 *
 * @return   : delay time (number of os tick)
 */
u32 DrvLcdGetFlushTime(void);


/*=================================================================*\
 * @brief Update the given buffer (Multi-Layer) to screen according to the given location.
 *
 * @param
    PMSSURFACE    pUpdateSurf[MSGDI_MAX_DISPLAY_LAYER];
    MSLAYERCONFIG LayerConfig[MSGDI_MAX_DISPLAY_LAYER];
    MSREGION      UpdateRegion[MSGDI_MAX_DISPLAY_LAYER];
 * @return   : delay time (number of os tick)
 \*=================================================================*/
//void DrvLcdWriteLcdEx(PMSUPDATE pParam);

/**
 * @brief Dump lcd registers
 *
 * @param    NONE
 *
 * @return   : NONE
 */
void DrvLcdDumpRegisters(void);


/**
 * @brief Dump lcd registers to backtrace
 *
 * @param    : NONE
 *
 * @return   : NONE
 */
void DrvLcdBackTrace(void);


#if defined (__G3D_DRV__)
/**
 * @brief Flip display engine function
 *
 * @pParam   : Flip buffer parameter[MSGDI_MAX_DISPLAY_LAYER];
 *
 * @return   : TRUE   : Flip success
 * @return   : FALSE  : Flip fail
 */
u8 DrvLcdFlipBuffer(PMSFLIP pParam);
#endif




#ifndef __I_SW__
#include "boot_logo_default_dimension.txt"
#if defined(__DUAL_LCD__)
#include "sub_boot_logo_default_dimension.txt"
#endif
#endif


void DrvLcdWriteLogoEx(u16 *pLogo, s16 xStart, s16 yStart, u16 w, u16 h);


bool DrvLcdSkipSplashImage(void);


u16 DrvGetMainDeviceID(void);
void DrvSetMainDeviceID(u16);

#if defined(__DUAL_LCD__)
u16 DrvGetSubDeviceID(void);
void DrvSetSubDeviceID(u16);
#endif


void DrvLcdSetLcmBus(dev_LcdCmdType_t cmd_bit);
void DrvLcdReset(void);

void DrvLcdReadCmdIndex(u16 RegIndex);
u16 DrvLcdReadCmdTimes(u16 Times);
void DrvLcdReadCmdArray(u16 RegIdx, u16 times, u32 *pData);


//external functions....

void DrvLcdWriteOneCmd(u32 RegAddr);
void DrvLcdWriteOneData(u32 RegData);

void DrvLcdBitFormatExp(dev_LcdBusExpand_e ExpandType);
u16  DrvLcdReadCmd(u16 RegIdx);
u16  DrvLcdReadCmdEx(u16 RegIdx, u16 times);

void DrvLcdWriteCmd(u32 RegAddr, u32 RegData);
void DrvLcdWriteSingleCmd(u16 RegAddr);
void DrvLcdWriteData(u16 data);

void DrvLcdWriteCmdSeq(u16 *pCmdSeq, u32 CmdLen);

#if defined(__DUAL_LCD__)
void DrvLcdSetRunLcdID(LCDPanelSel_e LCDSel);
#endif

u8 DrvLcdGetFMarkConfig(u32 PanelID);

void DrvLcdUpdate(u32 PanelID,u16 x, u16 y, u16 width, u16 height,void *pLayerFormat);

void DrvLcdUDelay(u32 uDelay);
void DrvLcdMDelay(u32 mDelay);

bool DrvLcdEmCmd(void *pStream);
bool DrvLcdEmReadCmd(void *pStream,u32 *num,u32 *pArray);

#define LCD_CONFIG_CONST __attribute__((section("cust_lcd_functable")))

extern dev_LcdConfig_t *pLcdFuncT;
extern dev_LcdSetting_t *pRunningLcd;

extern dev_LcdSetting_t MainLcd;

#if defined(__DUAL_LCD__)
extern dev_LcdSetting_t SubLcd;
#endif


#endif//ifndef __SDK_SIMULATION__


#endif//ndef __LCD_DRV_H__
