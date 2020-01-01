////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
 * @file drv_emi_sram_nor_pub.h
 * @brief SRAM/NOR driver public interface
 */

#ifndef __DRV_EMI_SRAM_NOR_PUB_TYPES_H__
#define __DRV_EMI_SRAM_NOR_PUB_TYPES_H__

/*=============================================================*/
// Type definition
/*=============================================================*/

typedef struct
{
/**
 * @struct AdvanSWCommand_t
 * @brief emi software commmand
 * The structure is for emi software command info.
 */
    u32 Addr_h;		///<address high bit.
    u32 Addr_l;		///<address low bit.
    u32 WrData;		///<data
} AdvanSWCommand_t;

#ifdef MCP_CONFIG_TABLE
typedef struct
{
    u16 nShiftedSize;
    u16 nNumber;
} FlashDeviceSectorRegion_new;

typedef struct
{
    /*EMI Parameters*/
    u32 FineInBound;        //0~7, unit: 0.4 ns
    u32 FineOutBound;       //0~7, unit: 0.4 ns
    u32 smcCLK;             //0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
    u32 CoarseInBound;      //0~3, unit: 3.2 ns
    u32 CoarseOutBound;     //0~3, unit: 3.2 ns
    u32 dmcCLK;             //0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
    /*Psram BCR*/
    u32 OM;                 //A15
    u32 IL;                 //A14
    u32 LC;                 //A13-A11
    u32 WaitPol;            //A10
    u32 WaitConfig;         //A8
    u32 DrivStrength;       //A5-A4
    u32 BurstWrap;          //A3
    u32 BLength;            //A2-A0
    /*Psram RCR*/
    u32 PageMode;           //A7
    u32 DeepPWD;            //A4
    u32 PartialRefresh;     //A2-A0
    u32 ndummy0;
    u32 ndummy1;
} emi_AdvancedConfig_new;

typedef struct
{				
    u32 nOenToEnd;
    u32 nSetupWr;			
    u32 nTurnAround;
    u32 nPageAddAcct;	
    u32 nWenCycle;   
    u32 nSetupRd; 
    u32 nWrCs; 
    u32 nRdCs;  
    u32 nOpMode;  
    u32 nType;     		
    u32 BurstReadWait; 
    u32 BurstWriteWait; 
    u32 nPageSize; 
    u32 BurstSize;	
    u32 nDriving;   //@@ u8->u32
    u32 ndummy0;
    u32 ndummy1;
} emi_BasicConfig_new;

typedef struct
{
    u32 eOpMode;
    u32 eFunc;
    u32 eBusClock;
    u32 pSPIInit;
    u32 pSPICmdByp;
    u32 nCMDStatus2;
    u32 nCMDSuspend;
    u32 nCMDResume;
    u32 nSuspendBit;
    u32 R_CSZ;
    u32 W_CSZ;
    u32 nDriving;   //@@ u8->u32
    u32 nDummyClk;
    u32 ndummy0;
    u32 ndummy1;    
} emi_SpiNorBasicConfig_new;

typedef union
{
    emi_BasicConfig_new			ParallelNorBasicParams; 
    emi_SpiNorBasicConfig_new	SpiNorBasicParams; 
} emi_NorBasicConfig_union;

typedef struct
{
    u32 nMagic; //@@ magic number
    
    //Flash Identifier
    u32 nDeviceFullId;    	//Include Manufacturer ID and Device ID
    u8  nFlashName[36];
    u32 nFlashType;			//0:NUMONYX, 1:MICRON, 2:SPANSION series(Include MICRONIX, EON),....
	
    u32 nFeatures;

    //DIDR
    u16 nDeviceSecondID ;
    u16 nSecondIDMask ;
        
    //Geometry 
    u16 nDeviceSize;
    u8 nPad;					   //<---??
    u8 nRegionNumber;
    FlashDeviceSectorRegion_new nAsRegions[8];
    
    //Bank
    u32 nBankNumber;    //@@ u16->u32
    u16 nBankAddresses[32];
    
    //CommandSets
    u8	nCommandSetsIndex;
    u8	ndummyArray[3];  //@@ u8->u8[3]
    
    u32 ndummy0;
    u32 ndummy1;
    
    //SW Command
    AdvanSWCommand_t Psram_SWCmd[16];
    AdvanSWCommand_t Nor_SWCmd[16];      
    
    //emi config 
    emi_AdvancedConfig_new		emiAdvanParams;
    emi_NorBasicConfig_union 	NorBasicParams;

    emi_BasicConfig_new PsramBasicParams;
} emi_mcpConfig_new;

typedef struct
{
    //DIDR
    u16 nID;
    u16 nIDMask;

    //SW Command
    AdvanSWCommand_t       *pPsramSWCmd;

    //emi config 
    emi_AdvancedConfig_new *pAdvanParams;
    emi_BasicConfig_new    *pPsramParams;
} emi_EmbeddedPsramConfig;

typedef struct
{
	u16 nDeviceSize; /* Device size = u16_DeviceSize * 64 KiB */
	u8	nPad;
	u8	nRegionNumber;
	FlashDeviceSectorRegion_new nAsRegions[8];
} FlashDeviceGeometry_t_new;

typedef struct
{
    u16 nBankNumber;
    u16 nBankAddresses[32];
} FlashBanksDescriptor_t_new;
#endif
#endif
