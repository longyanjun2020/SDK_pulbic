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

/**
 * @defgroup LCD LCD Panel Drivers
 * @ingroup DisplayDriver
 **/


/*!
 *  \file drv_lcd.h
 *
 *  declaration of lcd driver functions.
 */


/**
 * @defgroup LCDDriver LCD Panel Controller Interface
 * @ingroup LCD
 * @brief LCD panel controller interface
 *        These functions will connect to customer's LCD functions.
 * @details These APIs are used for control different LCDs
 *          The document of how to program customer's LCD functions is "LCD driver porting guide".
 *          That document can describe how to porting one new LCD driver on our platform.
 *          Here, we will focus on functions to our engine and their behavior.
 * @note
 **/

/** \addtogroup LCDDriver
 *  @{
 * \file
 */

#include "stdcomp.h"

#define LCD_DEFAULT_START_X 0
#define LCD_DEFAULT_START_Y 0
#define LCD_DEFAULT_START_WIDTH 0
#define LCD_DEFAULT_START_HEIGHT 0

#define _TRACE(...)
#define sys_UartPrintf(...)

#define U16ColorToRGB888(u16Color,R8,G8,B8)  (  R8 = (u8)((u16Color>>8)&0xf8) + ((u16Color>>13)&0x7), \
                                                G8 = (u8)((u16Color>>3)&0xfc) + ((u16Color>>9)&0x3), \
                                                B8 = (u8)((u16Color<<3)&0xf8) + ((u16Color>>2)&0x7)  )


#define DrvDispUDelay DrvLcdUDelay

/**
 * @brief LCD select panels
 */
typedef enum
{
    LCD_SEL_MAIN = 0,  ///<  Select main panel
    LCD_SEL_SUB,       ///<  Select sub panel
    LCD_SEL_MAX
}  LCDPanelSel_e;


/// @endcond


/**
 * @brief LCD ADC Value define.
 */
typedef enum {
    LCD_ADC_VALUE_0 = 0,    ///<  LCD ADC Value define 0
    LCD_ADC_VALUE_1,        ///<  LCD ADC Value define 1
    LCD_ADC_VALUE_2,        ///<  LCD ADC Value define 2
    LCD_ADC_VALUE_3,        ///<  LCD ADC Value define 3
    LCD_ADC_VALUE_4,        ///<  LCD ADC Value define 4
    LCD_ADC_VALUE_5,        ///<  LCD ADC Value define 5
    LCD_ADC_VALUE_6,        ///<  LCD ADC Value define 6
    LCD_ADC_NONE            ///<  LCD ADC Value define none
}LcdADCValue_e;

/**
 * @brief LCD command bus define.
 */
typedef enum
{
    LCD_16bit_CMD_16bit_BUS,     ///<  LCD 16 bit command in 16 bit bus
    LCD_8bit_CMD_8bit_BUS,       ///<  LCD 8 bit command in 8 bit bus
    LCD_18bit_CMD_18bit_BUS,     ///<  LCD 18 bit command in 18 bit bus
    LCD_16bit_CMD_8bit_BUS_HL,   ///<  LCD 16 bit command in 8 bit bus with high then low command
    LCD_16bit_CMD_8bit_BUS_LH,   ///<  LCD 16 bit command in 8 bit bus with low then high command
    LCD_18bit_CMD_8bit_BUS_HL,   ///<  LCD 18 bit command in 8 bit bus with high then low command
    LCD_18bit_CMD_8bit_BUS_LH,   ///<  LCD 18 bit command in 8 bit bus with low then high command
    LCD_18bit_CMD_9bit_BUS_HL,   ///<  LCD 18 bit command in 9 bit bus with high then low command
    LCD_18bit_CMD_9bit_BUS_LH,   ///<  LCD 18 bit command in 9 bit bus with low then high command
    LCD_9bit_CMD_9bit_BUS,       ///<  LCD 9 bit command in 9 bit bus
    LCD_8bit_CMD_DATA,           ///<  LCD 8 bit command data sequence
} dev_LcdCmdType_t;


/**
 * @brief LCD color depth
 */
typedef enum
{
    LCD_16bit_COLOR_DEPTH = 0x0,    ///<  LCD 16 bit color depth
    LCD_18bit_COLOR_DEPTH,          ///<  LCD 18 bit color depth
    LCD_8bit_COLOR_DEPTH,           ///<  LCD 8 bit color depth
    LCD_24bit_COLOR_DEPTH,          ///<  LCD 24 bit color depth
    LCD_24bit_COLOR_DEPTH_MSB6BIT,  ///<  LCD 24 bit color depth for MSB666 18 bit
    LCD_18bit_COLOR_DEPTH_24BITS,   ///<  LCD 18 bit color depth with MSB666 24 bit
} dev_LcdColorDepth_t;


/**
 * @brief LCD command shift enum
 */
typedef enum
{
    LCD_16BIT_IN16BIT = 0,    ///<  LCD 16 bit command in 16 bit bus
    LCD_LOW16BIT_IN18BIT,     ///<  LCD low 16 bit command in 18 bit bus
    LCD_HIGH16BIT_IN18BIT,    ///<  LCD high 16 bit command in 18 bit bus
    LCD_SHIFT16BIT_IN18BIT,   ///<  LCD shift 16 bit command in 18 bit bus with two 8bits
    LCD_LOW8BIT_IN9BIT,       ///<  LCD low 8 bit command in 9 bit bus
    LCD_HIGH8BIT_IN9BIT,      ///<  LCD high 8 bit command in 9 bit bus
} dev_LcdBusExpand_e;


/**
 * @brief LCD panel type
 */
typedef enum
{
    LCD_NORMAL_PANEL = 0, ///<  LCD normal panel
    LCD_FMARK_PANEL,      ///<  LCD FMark panel
    LCD_VSYNC_PANEL,      ///<  LCD VSync panel
    LCD_RGB_PANEL,        ///<  LCD RGB panel
	LCD_SPI_PANEL,        ///<  LCD SPI panel
} LCDPanelType_e;

/**
 * @brief LCD pixel clock select
 */
typedef enum
{
    LcdPixelClk_3M = 0,  ///<  LCD pixel clock 3M
    LcdPixelClk_5M,      ///<  LCD pixel clock 5M
    LcdPixelClk_6P5M,    ///<  LCD pixel clock 6.5M
    LcdPixelClk_9P75M,   ///<  LCD pixel clock 9.75M
    LcdPixelClk_13M,     ///<  LCD pixel clock 13M
    LcdPixelClk_15M,     ///<  LCD pixel clock 15M
    LcdPixelClk_19P9M,   ///<  LCD pixel clock 19.9M
    LcdPixelClk_26M,     ///<  LCD pixel clock 26M
    LcdPixelClk_30M,     ///<  LCD pixel clock 30M
    LcdPixelClk_31P2M,   ///<  LCD pixel clock 31.2M
    LcdPixelClk_39M,     ///<  LCD pixel clock 39M
    LcdPixelClk_44P5M,   ///<  LCD pixel clock 44.5M
    LcdPixelClk_52M,     ///<  LCD pixel clock 52M
    LcdPixelClk_60M,     ///<  LCD pixel clock 60M
} LcdPixelClk_e;


// for SPI Panel
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

/**
 * @brief SPI SCL type
 */
typedef enum
{
    SCL_TYPE_HL = 0x00000000,  ///<  SPI SCL type high to low
    SCL_TYPE_LH = 0x00000001,  ///<  SPI SCL type low to high
} LcdSpiLcm_SclType_e;

/**
 * @brief SPI data pack type
 */
typedef enum
{
    DATA_PACK_WITH_8_BITES = 0x00000000,  ///<  SPI data pack with 8 bit
    DATA_PACK_NON_8_BITES = 0x00000002,   ///<  SPI data pack with non 8 bit
} LcdSpiLcm_DataPackType_e;


/**
 * @brief SPI start byte type
 */
typedef enum
{
    USE_START_BYTE = 0x00000000,   ///<  SPI use start byte
    SKIP_START_BYTE = 0x00000004,  ///<  SPI skip start byte
} LcdSpiLcm_StartByteType_e;


/**
 * @brief SPI RW bit type
 */
typedef enum
{
    START_BYTE_RW_BIT_R0_W1 = 0x00000000,  ///<  SPI RW bit type Read(0) Write(1)
    START_BYTE_RW_BIT_R1_W0 = 0x00000008,  ///<  SPI RW bit type Read(1) Write(0)
} LcdSpiLcm_RWBitType_e;


/**
 * @brief SPI RS bit type
 */
typedef enum
{
    START_BYTE_RS_BIT_C0_D1 = 0x00000000,  ///<  SPI RS bit type Code(0) Data(1)
    START_BYTE_RS_BIT_C1_D0 = 0x00000010,  ///<  SPI RS bit type Code(1) Data(0)
} LcdSpiLcm_RSBitType_e;


/**
 * @brief SPI wire interface
 */
typedef enum
{
    FOUR_WIRE_SPI_INTERFACE = 0x00000000,   ///<  SPI four wire interface
    THREE_WIRE_SPI_INTERFACE = 0x00000020,  ///<  SPI three wire interface
} LcdSpiLcm_WireType_e;


/**
 * @brief SPI read data type
 */
typedef enum
{
    ONE_BYTE_RD_DATA = 0x00000040,   ///<  SPI one byte read data
    TWO_BYTE_RD_DATA = 0x00000080,   ///<  SPI two bytes read data
    THREE_BYTE_RD_DATA = 0x000000C0, ///<  SPI three bytes read data
} LcdSpiLcm_ReadDataType_e;


/**
 * @brief SPI write command type
 */
typedef enum
{
    ONE_BYTE_CMD = 0x00000100,  ///<  SPI one byte write command
    TWO_BYTE_CMD = 0x00000200,  ///<  SPI two bytes write command
} LcdSpiLcm_WriteCmdType_e;


/**
 * @brief SPI write data type
 */
typedef enum
{
    ONE_BYTE_WR_DATA = 0x00000400,    ///<  SPI one byte write data
    TWO_BYTE_WR_DATA = 0x00000800,    ///<  SPI two bytes write data
    THREE_BYTE_WR_DATA = 0x00000C00,  ///<  SPI three bytes write data
} LcdSpiLcm_WriteDataType_e;


/**
 * @brief SPI read id with start byte or not
 */
typedef enum
{
    READ_ID_NOT_BY_START_BYTE = 0x00000000,  ///<  SPI read id not by start byte
    READ_ID_WITH_START_BYTE = 0x00001000,    ///<  SPI read id with start byte
} LcdSpiLcm_ReadId_StartByteType_e;


/**
 * @brief SPI read id with dummy byte or with dummy cycle
 */
typedef enum
{
    READ_ID_USE_DUMMY_BYTE_CNT = 0x00000000,  ///<  SPI read id with dummy byte
    READ_ID_USE_DUMMY_CYCLE = 0x00002000,     ///<  SPI read id with dummy cycle
} LcdSpiLcm_ReadId_DummyUnitType_e;


/**
 * @brief SPI read id dummy unit cnt
 */
typedef enum
{
    ZERO_DUMMY_RD_CNT = 0x00000000,   ///<  SPI read id with zero dummy unit
    ONE_DUMMY_RD_CNT = 0x00004000,    ///<  SPI read id with one dummy unit
    TWO_DUMMY_RD_CNT = 0x00008000,    ///<  SPI read id with two dummy units
    THREE_DUMMY_RD_CNT = 0x0000C000,  ///<  SPI read id with three dummy units
    FOUR_DUMMY_RD_CNT = 0x00010000,   ///<  SPI read id with four dummy units
    FIVE_DUMMY_RD_CNT = 0x00014000,   ///<  SPI read id with five dummy units
    SIX_DUMMY_RD_CNT = 0x00018000,    ///<  SPI read id with six dummy units
    SEVEN_DUMMY_RD_CNT = 0x0001C000,  ///<  SPI read id with seven dummy units
} LcdSpiLcm_ReadId_DummyCntType_e;




/**
 * @brief LCD function type define
 */
typedef struct
{
    void (* LCD_Init)               (u8 reInit);   ///< LCD initial function
    void (* LCD_SleepModeOn)        (void);        ///< LCD sleep mode on
    void (* LCD_SleepModeCancel)    (void);        ///< LCD sleep mode cancel
    void (* LCD_PowerOff)           (void);        ///< LCD power off
    u16  (* LCD_GetDevice)          (u16 index);   ///< LCD get device ID
    void (* LCD_SetDisplayRange)    (u16 x, u16 y, u16 width, u16 height);  ///< LCD set display range
    void (* LCD_WriteLogo)          (void);        ///< LCD write logo
	u16  (* LCD_GetStrInfo)         (u8 id, char *pStr, u16 maxLen);  ///< LCD get ID string information
    //u16  (* LCD_RegCheck)           (void);
} dev_LcdFunc_t;


/**
 * @brief LCD check register
 */
typedef struct
{
    u16 Reg;         ///< LCD register
    u16 Times;       ///< Read times
    u16 Values[16];  ///< Return values
} LCDCheck_t;


/**
 * @brief LCD configs
 */
typedef struct
{
    u16 device_code;          ///< LCD device code
    u16 device_code_addr;     ///< LCD device code register address
    dev_LcdCmdType_t  cmd_bit; ///< LCD command bit
    dev_LcdColorDepth_t  color_depth; ///< LCD color depth
    u16 x_size;  ///< LCD width
    u16 y_size;  ///< LCD height
    u16 stride;  ///< LCD stride
    LcdPixelClk_e       PixelClk;   ///< LCD pixel clock
    dev_LcdBusExpand_e  busExpand;  ///< LCD bus expansion
    LCDPanelType_e      panel_type; ///< LCD types
    u32                 panel_parameter; ///< LCD other parameters
    dev_LcdFunc_t lcdFun; ///< LCD function pointers
} dev_LcdConfig_t;

///@cond INTERNAL
/**
 * @brief LCD configs
 */
typedef struct
{
    s16 id;       ///< LCD device code
    dev_LcdCmdType_t  cmd_bit;   ///< LCD command bit
    u16 x_size;  ///< LCD width
    u16 y_size;  ///< LCD height
    u16 stride;  ///< LCD stride
    u16 color_depth;   ///< LCD color depth
    LcdPixelClk_e       PixelClk;  ///< LCD pixel clock
    u8  sleep_on;      ///< LCD sleep flag
    u8  test;          ///< LCD test
    LCDPanelType_e      panel_type;  ///< LCD types
    u32                 panel_parameter;  ///< LCD other parameters
} dev_LcdSetting_t;
///@endcond

#ifndef __SDK_SIMULATION__

void DrvLcdInitHW(void);

/*!
 *  \fn void DrvLcdWriteOneCmd(u32 RegAddr)
 *
 *  \brief Write one LCD command, only write one LCD command no LCD data
 *
 *  \param[in] RegAddr LCD register address
 *
 *  \returns None
 */
void DrvLcdWriteOneCmd(u32 RegAddr);

/*!
 *  \fn void DrvLcdWriteOneData(u32 RegData)
 *
 *  \brief Write one LCD data, only write one LCD data no LCD command
 *
 *  \param[in] RegData LCD data value
 *
 *  \returns None
 */
void DrvLcdWriteOneData(u32 RegData);

/*!
 *  \fn u16  DrvLcdReadCmd(u16 RegIdx)
 *
 *  \brief Read LCD register. This function is used to read LCD register with indicate register index.
 *
 *  \param[in] RegIdx Register index
 *
 *  \returns Read value
 */
u16  DrvLcdReadCmd(u16 RegIdx);

u16  DrvLcdReadCmdEx(u16 RegIdx, u16 times);

u16 DrvLcdReadCmdTimes(u16 Times);

void DrvLcdReadCmdArray(u16 RegIdx, u16 times, u32 *pData);



/*!
 *  \fn void DrvLcdUDelay(u32 uDelay)
 *
 *  \brief Delay function for LCD delay in us
 *
 *  \param[in] uDelay Delay time in us
 *
 *  \returns None
 */
void DrvLcdUDelay(u32 uDelay);

/*!
 *  \fn void DrvLcdWriteLogoEx(u16 *pLogo, s16 xStart, s16 yStart, u16 w, u16 h)
 *
 *  \brief Write lcd logo
 *
 *  \param[in] *pLogo     Start pointer of logo buffer
 *  \param[in] xStart     Start point x coordinate
 *  \param[in] yStart     Start point y coordinate
 *  \param[in] w          Window width
 *  \param[in] h          Window height
 *
 *  \returns None
 */
void DrvLcdWriteLogoEx(u16 *pLogo, s16 xStart, s16 yStart, u16 w, u16 h);

void DrvLcdWriteCmdSeq(u16 *pCmdSeq, u32 CmdLen);

void DrvLcdWriteCmd(u32 RegAddr, u32 RegData);

void DrvLcdWriteSingleCmd(u16 RegAddr);



void DrvLcdReset(void);
void DrvLcdSetLcmBus(dev_LcdCmdType_t  cmd_bit);
void DrvLcdBitFormatExp(dev_LcdBusExpand_e ExpandType);

u16 DrvGetMainDeviceID(void);
void DrvSetMainDeviceID(u16 id);




#define LCD_CONFIG_CONST __attribute__((section("cust_lcd_functable")))

extern dev_LcdConfig_t *pLcdFuncT;

#endif

/** @}*/
#endif//ndef __LCD_DRV_H__

