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
* @file    _drv_bdma.h
* @version
* @brief   Bdma driver interface
*
*/

#ifndef __DRV_BDMA_INC_H__
#define __DRV_BDMA_INC_H__

/*=============================================================*/
// Include files
/*=============================================================*/



/*=============================================================*/
// System Data Type
/*=============================================================*/
/// data type hardware physical address
#ifndef MS_PHYADDR
typedef unsigned long               MS_PHYADDR;// 32bit physical address
#endif
/// data type unsigned char, data length 1 byte
#ifndef MS_U8
typedef unsigned char               MS_U8;// 1 byte
#endif
/// data type unsigned short, data length 2 byte
#ifndef MS_U16
typedef unsigned short              MS_U16;// 2 bytes
#endif
/// data type unsigned int, data length 4 byte
#ifndef MS_U32
typedef unsigned long               MS_U32;// 4 bytes
#endif
/// data type signed int, data length 4 byte
#ifndef MS_S32
typedef signed long                 MS_S32;// 4 bytes
#endif
/// definition for MS_BOOL
#ifndef MS_BOOL
typedef unsigned char               MS_BOOL;
#endif

#define DISABLE                     0
/// Operation cfg
#define BDMA_OPCFG_DEF          	(0)
#define BDMA_OPCFG_INV_COPY     	(0x01)
#define BDMA_OPCFG_CRC_REFLECT  	(0x02)      //bit reflection of each input byte
#define BDMA_OPCFG_CRC_COPY     	(0x04)      //copy then crc check
#define BDMA_OPCFG_NOWAIT_COPY  	(0x08)      //copy then quit
#define BDMA_OPCFG_MOBF_PS  		(0x10)      //copy then quit

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum _BDMA_DbgLv
{
    E_BDMA_DBGLV_NONE           //no debug message
    ,E_BDMA_DBGLV_PERFORMANCE   //show performance only
    ,E_BDMA_DBGLV_ERR_ONLY      //show error only
    ,E_BDMA_DBGLV_REG_DUMP      //show error & reg dump
    ,E_BDMA_DBGLV_INFO          //show error & informaiton
    ,E_BDMA_DBGLV_ALL           //show error, information & funciton name
}BDMA_DbgLv;

typedef enum _BDMA_Dev
{
    E_BDMA_DEV_MIU0
    ,E_BDMA_DEV_MIU1
    ,E_BDMA_DEV_SEARCH
    ,E_BDMA_DEV_CRC32
    ,E_BDMA_DEV_MEM_FILL
    ,E_BDMA_DEV_FLASH
    ,E_BDMA_DEV_DMDMCU
    ,E_BDMA_DEV_VDMCU
    ,E_BDMA_DEV_DSP
    ,E_BDMA_DEV_TSP
    ,E_BDMA_DEV_1KSRAM_HK51
    ,E_BDMA_DEV_NOT_SUPPORT
}BDMA_Dev;

typedef enum _BDMA_SrcDev
{
    E_BDMA_SRCDEV_MIU0          = E_BDMA_DEV_MIU0
    ,E_BDMA_SRCDEV_MIU1         = E_BDMA_DEV_MIU1
    ,E_BDMA_SRCDEV_MEM_FILL     = E_BDMA_DEV_MEM_FILL
    ,E_BDMA_SRCDEV_FLASH        = E_BDMA_DEV_FLASH
    ,E_BDMA_SRCDEV_NOT_SUPPORT  = E_BDMA_DEV_NOT_SUPPORT
}BDMA_SrcDev;

typedef enum _BDMA_DstDev
{
    E_BDMA_DSTDEV_MIU0          = E_BDMA_DEV_MIU0
    ,E_BDMA_DSTDEV_MIU1         = E_BDMA_DEV_MIU1
    ,E_BDMA_DSTDEV_SEARCH       = E_BDMA_DEV_SEARCH
    ,E_BDMA_DSTDEV_CRC32        = E_BDMA_DEV_CRC32
    ,E_BDMA_DSTDEV_DMDMCU       = E_BDMA_DEV_DMDMCU         //Demod
    ,E_BDMA_DSTDEV_VDMCU        = E_BDMA_DEV_VDMCU          //VD
    ,E_BDMA_DSTDEV_DSP          = E_BDMA_DEV_DSP
    ,E_BDMA_DSTDEV_TSP          = E_BDMA_DEV_TSP
    ,E_BDMA_DSTDEV_HK51_1KSRAM  = E_BDMA_DEV_1KSRAM_HK51
    ,E_BDMA_DSTDEV_NOT_SUPPORT  = E_BDMA_DEV_NOT_SUPPORT
}BDMA_DstDev;


typedef enum _BDMA_Result
{
    E_BDMA_NOT_SUPPORT = -1
    ,E_BDMA_OK = 0   
    ,E_BDMA_FAIL = 1
    ,E_BDMA_TIMEOUT
    ,E_BDMA_QUEUE_FULL
    ,E_BDMA_BUSY
}BDMA_Result;

typedef struct _BDMA_HwInfo
{
    MS_BOOL bEnMIU1;        //MIU1
    MS_BOOL bEnHost;        //bdma host
    MS_BOOL bEnMemFill;     //memory fill
    MS_BOOL bEnFlsCpy;      //flash copy
    MS_BOOL bEnDevDw;       //bdma device data width
    MS_BOOL bEnDmyWrCnt;    //bdma dummy wr count
    MS_BOOL bEnDMDMCU;      //bdma to DeMod MCU
    MS_BOOL bEnTSP;         //bdma to TSP
    MS_BOOL bEnDSP;         //bdma to DSP
    MS_BOOL bEnHK51_1KSRAM; //bdma to HK51_1KSRAM
}BDMA_HwInfo;

typedef struct _BDMA_Info
{
    MS_U8       u8ChNum;
    MS_U16      u16ChipVer;
    MS_U32      u32IOMap;
    MS_U32      u32MIU1Base;
    MS_S32      s32Mutex;
    MS_BOOL     bInit;
    BDMA_DbgLv  eDbgLv;
    BDMA_HwInfo sHwCap;
}BDMA_Info;


typedef void (*BDMA_ISR_CBF)(BDMA_Result eRet);

/* Below API is from ROM BDMA driver */
//static MS_BOOL _BDMA_Is_Init(void);
//static MS_BOOL _BDMA_Get_FreeCh(MS_U8 *pu8Ch);
//static void _BDMA_MemFlush(BDMA_Dev eDev, MS_U32 u32Base, MS_U32 u32Size);
//static BDMA_Result _BDMA_CmnHnd(BDMA_OP_CB sOpCB, MS_U8 *pu8Ch);
//static BDMA_Result _BDMA_Check_Device(BDMA_SrcDev eSrc, BDMA_DstDev eDst);
//static MS_U8 _BDMA_GetDevCfg(BDMA_Dev eDev);
//BDMA_Result MDrv_BDMA_Init(MS_U32 u32Miu1Base);
//BDMA_Result MDrv_BDMA_PatternFill(MS_PHYADDR u32Addr, MS_U32 u32Len, MS_U32 u32Pattern, BDMA_DstDev eDev);
//void MDrv_BDMA_DumpCB(void *pvOpCB);

#endif /* __DRV_BDMA_INC_H__ */

