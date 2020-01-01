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
* @file    hal_bus_i2c.h
* @version
* @brief   This file contains the bus I2C hardware layer headers.
*
*/

#ifndef __HAL_BUS_I2C_H__
#define __HAL_BUS_I2C_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_bus_i2c.h"
#include "vm_types.ht"
#include "sys_sys.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define BUS_I2C_ERROR_LEVEL				(_DEV)
#define BUS_I2C_TRACE_LEVEL				(BUS_I2C_ERROR_LEVEL | LEVEL_6)

////////////////////////////////////////////////////////////////////////////////
// Define & data type
////////////////////////////////////////////////////////////////////////////////

#ifdef _HAL_IIC_C_
#define _extern_HAL_IIC_
#else
#define _extern_HAL_IIC_ extern
#endif

#define BOOL bool

//v: value n: shift n bits
//v: value n: shift n bits
#define _LShift(v, n)       ((v) << (n))
#define _RShift(v, n)       ((v) >> (n))
#define udelay(x)	SYS_UDELAY(x)
#define HIGH_BYTE(val)      (U8)_RShift((val), 8)
#define LOW_BYTE(val)       ((U8)((val) & 0xFF))

#define __BIT(x)    ((U16)_LShift(1, x))
#define __BIT0       __BIT(0)
#define __BIT1       __BIT(1)
#define __BIT2       __BIT(2)
#define __BIT3       __BIT(3)
#define __BIT4       __BIT(4)
#define __BIT5       __BIT(5)
#define __BIT6       __BIT(6)
#define __BIT7       __BIT(7)
#define __BIT8       __BIT(8)
#define __BIT9       __BIT(9)
#define __BIT10      __BIT(10)
#define __BIT11      __BIT(11)
#define __BIT12      __BIT(12)
#define __BIT13      __BIT(13)
#define __BIT14      __BIT(14)
#define __BIT15      __BIT(15)

#if 0
//////////////////////////////////////////////////////////////////////////////////////
typedef unsigned int               BOOL;                            // 1 byte
/// data type unsigned char, data length 1 byte
typedef unsigned char               U8;                              // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short              U16;                             // 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned int               U32;                             // 4 bytes
/// data type unsigned int64, data length 8 byte
typedef unsigned long         MS_U64;                             // 8 bytes
/// data type signed char, data length 1 byte
typedef signed char                 MS_S8;                              // 1 byte
/// data type signed short, data length 2 byte
typedef signed short                MS_S16;                             // 2 bytes
/// data type signed int, data length 4 byte
typedef signed int                 MS_S32;                             // 4 bytes
/// data type signed int64, data length 8 byte
typedef signed long            MS_S64;                             // 8 bytes
/////////////////////////////////////////////////////////////////////////////////
#endif

#define HWI2C_SET_RW_BIT(bRead, val) ((bRead) ? ((val) | __BIT0) : ((val) & ~__BIT0))

#define HAL_HWI2C_PORTS         4

#define HAL_HWI2C_PORT0         0
#define HAL_HWI2C_PORT1         1
#define HAL_HWI2C_PORT2         2
#define HAL_HWI2C_PORT3         3

typedef enum _HAL_HWI2C_STATE
{
    E_HAL_HWI2C_STATE_IDEL = 0,
    E_HAL_HWI2C_STATE_START,
    E_HAL_HWI2C_STATE_WRITE,
    E_HAL_HWI2C_STATE_READ,
    E_HAL_HWI2C_STATE_INT,
    E_HAL_HWI2C_STATE_WAIT,
    E_HAL_HWI2C_STATE_STOP
} HAL_HWI2C_STATE;


typedef enum _HAL_HWI2C_PORT
{
    E_HAL_HWI2C_PORT0_0 = 0, //00:disable port 0
    E_HAL_HWI2C_PORT0_1,
    E_HAL_HWI2C_PORT0_2,
    E_HAL_HWI2C_PORT0_3,

    E_HAL_HWI2C_PORT1_0,     //04:disable port 1
    E_HAL_HWI2C_PORT1_1,
    E_HAL_HWI2C_PORT1_2,
    E_HAL_HWI2C_PORT1_3,

    E_HAL_HWI2C_PORT2_0,     //08:disable port 2
    E_HAL_HWI2C_PORT2_1,
    E_HAL_HWI2C_PORT2_2,
    E_HAL_HWI2C_PORT2_3,

    E_HAL_HWI2C_PORT3_0,     //12:disable port 3
    E_HAL_HWI2C_PORT3_1,
    E_HAL_HWI2C_PORT3_2,
    E_HAL_HWI2C_PORT3_3,

    E_HAL_HWI2C_PORT_NOSUP   //16:(4 port * 4 pad)
} HAL_HWI2C_PORT;

typedef enum _HAL_HWI2C_CLKSEL
{
    E_HAL_HWI2C_CLKSEL_HIGH = 0,
    E_HAL_HWI2C_CLKSEL_NORMAL,
    E_HAL_HWI2C_CLKSEL_SLOW,
    E_HAL_HWI2C_CLKSEL_VSLOW,
    E_HAL_HWI2C_CLKSEL_USLOW,
    E_HAL_HWI2C_CLKSEL_UVSLOW,
    E_HAL_HWI2C_CLKSEL_NOSUP
} HAL_HWI2C_CLKSEL;


typedef enum
{
    E_HAL_HWI2C_READ_MODE_DIRECT,                       ///< first transmit slave address + reg address and then start receive the data */
    E_HAL_HWI2C_READ_MODE_DIRECTION_CHANGE,             ///< slave address + reg address in write mode, direction change to read mode, repeat start slave address in read mode, data from device
    E_HAL_HWI2C_READ_MODE_DIRECTION_CHANGE_STOP_START,  ///< slave address + reg address in write mode + stop, direction change to read mode, repeat start slave address in read mode, data from device
    E_HAL_HWI2C_READ_MODE_MAX
} HAL_HWI2C_ReadMode;

typedef enum _HAL_HWI2C_DMA_ADDRMODE
{
    E_HAL_HWI2C_DMA_ADDR_NORMAL = 0,
    E_HAL_HWI2C_DMA_ADDR_10BIT,
    E_HAL_HWI2C_DMA_ADDR_MAX,
} HAL_HWI2C_DMA_ADDRMODE;

typedef enum _HAL_HWI2C_DMA_MIUPRI
{
    E_HAL_HWI2C_DMA_PRI_LOW = 0,
    E_HAL_HWI2C_DMA_PRI_HIGH,
    E_HAL_HWI2C_DMA_PRI_MAX,
} HAL_HWI2C_DMA_MIUPRI;

typedef enum _HAL_HWI2C_DMA_MIUCH
{
    E_HAL_HWI2C_DMA_MIU_CH0 = 0,
    E_HAL_HWI2C_DMA_MIU_CH1,
    E_HAL_HWI2C_DMA_MIU_MAX,
} HAL_HWI2C_DMA_MIUCH;

typedef struct _HAL_HWI2C_PinCfg
{
    U32  u32Reg;    /// register
    U8   u8BitPos;  /// bit position
    BOOL bEnable;   /// enable or disable
} HAL_HWI2C_PinCfg;

typedef struct _HAL_HWI2C_PortCfg //Synchronize with drvHWI2C.h
{
    U32                  	u32DmaPhyAddr;  /// DMA physical address
    HAL_HWI2C_DMA_ADDRMODE  eDmaAddrMode;   /// DMA address mode
    HAL_HWI2C_DMA_MIUPRI    eDmaMiuPri;     /// DMA miu priroity
    HAL_HWI2C_DMA_MIUCH     eDmaMiuCh;      /// DMA miu channel
    BOOL                 	bDmaEnable;     /// DMA enable

    HAL_HWI2C_PORT          ePort;          /// number
    HAL_HWI2C_CLKSEL        eSpeed;         /// clock speed
    HAL_HWI2C_ReadMode      eReadMode;      /// read mode

} HAL_HWI2C_PortCfg;

/// I2C Configuration for initialization
typedef struct _HAL_HWI2C_CfgInit //Synchronize with drvHWI2C.h
{
    HAL_HWI2C_PortCfg   sCfgPort[4];    /// port cfg info
    HAL_HWI2C_PinCfg    sI2CPin;        /// pin info
    HAL_HWI2C_CLKSEL    eSpeed;         /// speed
    HAL_HWI2C_PORT      ePort;          /// port
    HAL_HWI2C_ReadMode  eReadMode;      /// read mode

} HAL_HWI2C_CfgInit;

typedef struct _I2C_DMA
{
    void  *i2c_dma_addr;
    u8  *i2c_virt_addr;
} I2C_DMA;

/// debug level
typedef enum _HWI2C_DbgLv
{
    E_HWI2C_DBGLV_NONE,          /// no debug message
    E_HWI2C_DBGLV_ERR_ONLY,      /// show error only
    E_HWI2C_DBGLV_INFO,          /// show error & informaiton
    E_HWI2C_DBGLV_ALL            /// show error, information & funciton name
} HWI2C_DbgLv;

/// I2C select master port
typedef enum _HWI2C_PORT
{
    E_HWI2C_PORT_0 = 0, /// port 0_0 //disable port 0
    E_HWI2C_PORT0_1,    /// port 0_1
    E_HWI2C_PORT0_2,    /// port 0_2
    E_HWI2C_PORT0_3,    /// port 0_3
    E_HWI2C_PORT0_4,    /// port 0_4
    E_HWI2C_PORT0_5,    /// port 0_5
    E_HWI2C_PORT0_6,    /// port 0_6
    E_HWI2C_PORT0_7,    /// port 0_7

    E_HWI2C_PORT_1 = 8, /// port 1_0 //disable port 1
    E_HWI2C_PORT1_1,    /// port 1_1
    E_HWI2C_PORT1_2,    /// port 1_2
    E_HWI2C_PORT1_3,    /// port 1_3
    E_HWI2C_PORT1_4,    /// port 1_4
    E_HWI2C_PORT1_5,    /// port 1_5
    E_HWI2C_PORT1_6,    /// port 1_6
    E_HWI2C_PORT1_7,    /// port 1_7

    E_HWI2C_PORT_2 = 16,/// port 2_0 //disable port 2
    E_HWI2C_PORT2_1,    /// port 2_1
    E_HWI2C_PORT2_2,    /// port 2_2
    E_HWI2C_PORT2_3,    /// port 2_3
    E_HWI2C_PORT2_4,    /// port 2_4
    E_HWI2C_PORT2_5,    /// port 2_5
    E_HWI2C_PORT2_6,    /// port 2_6
    E_HWI2C_PORT2_7,    /// port 2_7

    E_HWI2C_PORT_3 = 24,/// port 3_0 //disable port 3
    E_HWI2C_PORT3_1,    /// port 3_1
    E_HWI2C_PORT3_2,    /// port 3_2
    E_HWI2C_PORT3_3,    /// port 3_3
    E_HWI2C_PORT3_4,    /// port 3_4
    E_HWI2C_PORT3_5,    /// port 3_5
    E_HWI2C_PORT3_6,    /// port 3_6
    E_HWI2C_PORT3_7,    /// port 3_7

    E_HWI2C_PORT_NOSUP  /// non-support port
} HWI2C_PORT;

/// I2C clock speed select
typedef enum _HWI2C_CLKSEL
{
    E_HWI2C_HIGH = 0,  /// high speed
    E_HWI2C_NORMAL,    /// normal speed
    E_HWI2C_SLOW,      /// slow speed
    E_HWI2C_VSLOW,     /// very slow
    E_HWI2C_USLOW,     /// ultra slow
    E_HWI2C_UVSLOW,    /// ultra-very slow
    E_HWI2C_NOSUP      /// non-support speed
} HWI2C_CLKSEL;

/// I2C state
typedef enum _HWI2C_State
{
    E_HWI2C_IDLE,      /// idle state
    E_HWI2C_READ_DATA, /// read data state
    E_HWI2C_WRITE_DATA, /// write data state
    E_HWI2C_DMA_READ_DATA, /// DMA read data state
    E_HWI2C_DMA_WRITE_DATA /// DMA write data state
} HWI2C_State;

typedef enum
{
    E_HWI2C_READ_MODE_DIRECT,                 ///< first transmit slave address + reg address and then start receive the data */
    E_HWI2C_READ_MODE_DIRECTION_CHANGE,       ///< slave address + reg address in write mode, direction change to read mode, repeat start slave address in read mode, data from device
    E_HWI2C_READ_MODE_DIRECTION_CHANGE_STOP_START,  ///< slave address + reg address in write mode + stop, direction change to read mode, repeat start slave address in read mode, data from device
    E_HWI2C_READ_MODE_MAX
} HWI2C_ReadMode;

typedef enum _HWI2C_DMA_ADDRMODE
{
    E_HWI2C_DMA_ADDR_NORMAL = 0,
    E_HWI2C_DMA_ADDR_10BIT,
    E_HWI2C_DMA_ADDR_MAX,
} HWI2C_DMA_ADDRMODE;

typedef enum _HWI2C_DMA_READMODE
{
    E_HWI2C_DMA_READ_NOSTOP = 0,
    E_HWI2C_DMA_READ_STOP,
    E_HWI2C_DMA_READ_MAX,
} HWI2C_DMA_READMODE;

typedef enum _HWI2C_DMA_MIUPRI
{
    E_HWI2C_DMA_PRI_LOW = 0,
    E_HWI2C_DMA_PRI_HIGH,
    E_HWI2C_DMA_PRI_MAX,
} HWI2C_DMA_MIUPRI;

typedef enum _HWI2C_DMA_MIUCH
{
    E_HWI2C_DMA_MIU_CH0 = 0,
    E_HWI2C_DMA_MIU_CH1,
    E_HWI2C_DMA_MIU_MAX,
} HWI2C_DMA_MIUCH;

/// I2C master pin config
typedef struct _HWI2C_PinCfg
{
    U32  u32Reg;    /// register
    U8   u8BitPos;  /// bit position
    BOOL bEnable;   /// enable or disable
} HWI2C_PinCfg;

/// I2C port config
typedef struct _HWI2C_PortCfg
{
    U32              	u32DmaPhyAddr;  /// DMA physical address
    HWI2C_DMA_ADDRMODE  eDmaAddrMode;   /// DMA address mode
    HWI2C_DMA_MIUPRI    eDmaMiuPri;     /// DMA miu priroity
    HWI2C_DMA_MIUCH     eDmaMiuCh;      /// DMA miu channel
    BOOL             	bDmaEnable;     /// DMA enable

    HWI2C_PORT          ePort;          /// number
    HWI2C_CLKSEL        eSpeed;         /// clock speed
    HWI2C_ReadMode      eReadMode;      /// read mode

} HWI2C_PortCfg;

/// I2C Configuration for initialization
typedef struct _HWI2C_UnitCfg
{
    HWI2C_PortCfg   sCfgPort;    	/// port cfg info
    HWI2C_PinCfg    sI2CPin;        /// pin info
    HWI2C_CLKSEL    eSpeed;         /// speed
    HWI2C_PORT      ePort;          /// port
    HWI2C_ReadMode  eReadMode;      /// read mode
    int             eGroup;         /// port
} HWI2C_UnitCfg;

/// I2C information
typedef struct _HWI2C_Info
{
    U32          	u32IOMap; /// base address
    HWI2C_UnitCfg   sUnitCfg; /// configuration
} HWI2C_Info;

/// I2C status
typedef struct _HWI2C_Status
{
    U8       u8DbgLevel;   /// debug level
    BOOL     bIsInit;      /// initialized
    BOOL     bIsMaster;    /// master
    HWI2C_State eState;       /// state
} HWI2C_Status;


////////////////////////////////////////////////////////////////////////////////
// Extern function
////////////////////////////////////////////////////////////////////////////////
_extern_HAL_IIC_ U32 MsOS_PA2KSEG1(U32 addr);
_extern_HAL_IIC_ U32 MsOS_VA2PA(U32 addr);

_extern_HAL_IIC_ void HAL_HWI2C_ExtraDelay(U32 u32Us);
_extern_HAL_IIC_ void HAL_HWI2C_SetIOMapBase(U8 u8Port, U32 u32Base, U32 u32ChipBase, U32 u32ClkBase);
_extern_HAL_IIC_ U8 HAL_HWI2C_ReadByte(U32 u32RegAddr);
_extern_HAL_IIC_ U16 HAL_HWI2C_Read2Byte(U32 u32RegAddr);
_extern_HAL_IIC_ U32 HAL_HWI2C_Read4Byte(U32 u32RegAddr);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteByte(U32 u32RegAddr, U8 u8Val);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Write2Byte(U32 u32RegAddr, U16 u16Val);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Write4Byte(U32 u32RegAddr, U32 u32Val);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteRegBit(U32 u32RegAddr, U8 u8Mask, BOOL bEnable);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteByteMask(U32 u32RegAddr, U8 u8Val, U8 u8Mask);

_extern_HAL_IIC_ BOOL HAL_HWI2C_Init_Chip(void);
_extern_HAL_IIC_ BOOL HAL_HWI2C_IsMaster(void);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Master_Enable(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_SetPortRegOffset(U8 u8Port, U16* pu16Offset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_GetPortIdxByOffset(U16 u16Offset, U8* pu8Port);
_extern_HAL_IIC_ BOOL HAL_HWI2C_GetPortIdxByPort(HAL_HWI2C_PORT ePort, U8* pu8Port);
_extern_HAL_IIC_ BOOL HAL_HWI2C_SelectPort(HAL_HWI2C_PORT ePort);
_extern_HAL_IIC_ BOOL HAL_HWI2C_SetClk(U16 u16PortOffset, HAL_HWI2C_CLKSEL eClkSel);

_extern_HAL_IIC_ BOOL HAL_HWI2C_Start(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Stop(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_ReadRdy(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_SendData(U16 u16PortOffset, U8 u8Data);
_extern_HAL_IIC_ U8 HAL_HWI2C_RecvData(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Get_SendAck(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_NoAck(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Ack(U16 u16PortOffset);
_extern_HAL_IIC_ U8 HAL_HWI2C_GetState(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Is_Idle(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Is_INT(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Clear_INT(U16 u16PortOffset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Reset(U16 u16PortOffset, BOOL bReset);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Send_Byte(U16 u16PortOffset, U8 u8Data);
_extern_HAL_IIC_ BOOL HAL_HWI2C_Recv_Byte(U16 u16PortOffset, U8 *pData);

_extern_HAL_IIC_ BOOL HAL_HWI2C_DMA_Init(U16 u16PortOffset, HAL_HWI2C_PortCfg* pstPortCfg);
_extern_HAL_IIC_ BOOL HAL_HWI2C_DMA_Enable(U16 u16PortOffset, BOOL bEnable);
_extern_HAL_IIC_ BOOL HAL_HWI2C_DMA_ReadBytes(U16 u16PortOffset, U16 u16SlaveCfg, U32 uAddrCnt, U8 *pRegAddr, U32 uSize, U8 *pData);
_extern_HAL_IIC_ BOOL HAL_HWI2C_DMA_WriteBytes(U16 u16PortOffset, U16 u16SlaveCfg, U32 uAddrCnt, U8 *pRegAddr, U32 uSize, U8 *pData);

_extern_HAL_IIC_ void HAL_HWI2C_Init_ExtraProc(void);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteChipByteMask(U32 u32RegAddr, U8 u8Val, U8 u8Mask);
_extern_HAL_IIC_ U8 HAL_HWI2C_ReadChipByte(U32 u32RegAddr);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteChipByte(U32 u32RegAddr, U8 u8Val);
_extern_HAL_IIC_ void Hal_HW_IIC_Init(volatile void *base, volatile void *chipbase, int i2cgroup, volatile void *clkbase);
_extern_HAL_IIC_ BOOL Hal_HWI2C_InitPort(HWI2C_UnitCfg *psCfg);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteClk2Byte(U32 u32RegAddr, U16 u16Val);
_extern_HAL_IIC_ BOOL HAL_HWI2C_WriteClkByteMask(U32 u32RegAddr, U16 u16Val, U16 u16Mask);
_extern_HAL_IIC_ U16 HAL_HWI2C_ReadClk2Byte(U32 u32RegAddr);
_extern_HAL_IIC_ U32 HAL_HWI2C_XferWrite(u8 u8Port, u8 u8slaveAddr, u8 *pbuf, int length);
_extern_HAL_IIC_ U32 HAL_HWI2C_XferRead(u8 u8Port, u8 u8slaveAddr, u8 *pbuf, int length);
_extern_HAL_IIC_ I2CErrorCode_e HalI2cInitStandard(void);
_extern_HAL_IIC_ I2CErrorCode_e HalI2cSendDataStandard(u8 nPortNum, u8 nAddr, u8 nSpeed, bool bReStart, s32 nNbItems, const u8 *pDataToWrite, bool bStopBit);
_extern_HAL_IIC_ I2CErrorCode_e HalI2cReceiveStandard(u8 nPortNum, u8 nAddr, u8 nSpeed, bool bReStart, u32 nNbItemsToWrite, u8 *pDataToWrite, u32 nNbItemsToRead, u8 *pDataToRead);

#endif //__HAL_BUS_I2C_H__

