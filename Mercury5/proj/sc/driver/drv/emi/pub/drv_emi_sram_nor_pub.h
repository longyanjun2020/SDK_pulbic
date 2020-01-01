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

#ifndef __DRV_EMI_SRAM_NOR_PUB_H__
#define __DRV_EMI_SRAM_NOR_PUB_H__

/**
 * @defgroup Emi External Memory Interface Driver
 * @ingroup Driver
 * @brief External memory interface driver (EMI)
 * @details 
 * @note
 **/

/** \addtogroup Emi
 *  @{
 * \file
 */


/*=============================================================*/
// Include files
/*=============================================================*/
#include "drv_emi_pub.h"
#include "drv_clkgen_cmu.h"
#include "drv_emi_sram_nor_pub_types.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define NOUSE               0xFFFFFFFF			///<No use define value
#define CRVALUE             0xFFFFFFFE			///<CR Value
#define MAXPARAMETERSNO     90					///<The IMI array size
#ifdef MCP_CONFIG_TABLE
#define MAXSWCMDNO          16					///<software commands array size
#else
#define MAXSWCMDNO          20					///<software commands array size
#endif

/*=============================================================*/
// Type definition
/*=============================================================*/

/*!
 *      \brief The emi port.
 */
typedef enum
{
    EMI_MEM0 = 0,
    EMI_MEM1,
    EMI_MEM2,
    EMI_MEM3
} emi_Port_e;

/*!
 *      \brief The nor/psram running mode.
 */
typedef enum
{
    EMI_SINGLE = 0,
    EMI_PAGE,
    EMI_BURST_WRITE,
    EMI_BURST_READ = 4,
    EMI_BURST_RW = 6
} emi_mode_e;


/*!
 *      \brief The nor/psram page size.
 */
typedef enum
{
    EMI_PAGE_1WORD = 0,
    EMI_PAGE_2WORDS,
    EMI_PAGE_4WORDS,
    EMI_PAGE_8WORDS,
    EMI_PAGE_16WORDS
} emi_pagesize_e;


/*!
 *      \brief The nor/psram type.
 */
typedef enum
{
    EMI_NOR = 0,
    EMI_CELLULARRAM,
    EMI_COSMORAM,
    EMI_UtRAM,
    EMI_SRAM
} emi_type_e;

/*!
 *      \brief The nor/psram bust size.
 */
typedef enum
{
    EMI_NO_BOUNDARY = 0,
    EMI_BURST_4WORDS,
    EMI_BURST_8WORDS,
    EMI_BURST_16WORDS,
    EMI_BURST_32WORDS,
    EMI_BURST_64WORDS,
    EMI_BURST_128WORDS,
    EMI_BURST_256WORDS,
} emi_Burstsize_e;

/*!
 *      \brief The flash type.
 */
typedef enum
{
    FLASH_NAND = 0,
    FLASH_NOR,
    FLASH_SPI
} emi_flash_type_e;


typedef struct
{
/**
 * @struct emi_SramNorCfg_t
 * @brief emi sram nor config
 * The structure is for emi sram nor config.
 */
    u32 nMode;			///<mode
    u32 nPageSize;		///<00 = 4 words, 1 = 8 words, 2=   16 words, 3 = 32 words
    u32 nWaitAcct;		///<number of BCLK cycles before wait valid
    u32 nBHold;			///<0 : 1 data /bclk                           1 : 1 data / 2bclk
    u32 nWaitPol;		///<Wait signal input polarity 0 : wait active low                     1 : wait active high
    u32 nWaitShift;		///<0 : wait is active during data not valid cycle 1 : wait is active one cycle before data not valid
    u32 nBpAcct;		///<burst or page access time (0 = 1, 1 = 2,...)
    u32 nStrechRdWr;	///<stretch mode enable 0: no stretch double access   1: stretch double access
    u32 nWaitRd;		///<Read wait state time
    u32 nHalf0Rd;		///<Read half HCLK start edge delay
    u32 nHalf1Rd;		///<Read half HCLK stop edge delay
    u32 nSetupRd;		///<Read setup time
    u32 nHoldRd;		///<Read hold time
    u32 nWaitWr;		///<Write wait state time
    u32 nHalf0Wr;		///<Write half HCLK start edge delay
    u32 nHalf1Wr;		///<Write half HCLK stop edge delay
    u32 nSetupWr;		///<Write setup time
    u32 nHoldWr;		///<Write hold time
    u32 nBta;			///<Bus Turn Around : number of hclk cycles between a read and write access on MEM0.
    u32 nRtor;			///<number of HCLK cycles between 2 consecutive read.
    u32 nWtow;			///<number of HCLK cycles between 2 consecutive write.
} emi_SramNorCfg_t;

typedef struct
{
/**
 * @struct emi_AdvancedConfig_t
 * @brief emi advanced config
 * The structure is for emi advanced config.
 */
    /*EMI Parameters*/
    u32 FineInBound;        ///<0~7, unit: 0.4 ns
    u32 FineOutBound;       ///<0~7, unit: 0.4 ns
    u32 smcCLK;             ///<0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
    u32 CoarseInBound;      ///<0~3, unit: 3.2 ns
    u32 CoarseOutBound;     ///<0~3, unit: 3.2 ns
    u32 dmcCLK;             ///<0: 26M, 1:52M, 2:78M, 3:104M, 4:130M, 5:156M
    /*Psram BCR*/
    u32 OM;                 ///<A15
    u32 IL;                 ///<A14
    u32 LC;                 ///<A13-A11
    u32 WaitPol;            ///<A10
    u32 WaitConfig;         ///<A8
    u32 DrivStrength;       ///<A5-A4
    u32 BurstWrap;          ///<A3
    u32 BLength;            ///<A2-A0
    /*Psram RCR*/
    u32 PageMode;           ///<A7
    u32 DeepPWD;            ///<A4
    u32 PartialRefresh;     ///<A2-A0
} emi_AdvancedConfig_t;

typedef struct
{
/**
 * @struct emi_BasicConfig_t
 * @brief emi basic config
 * The structure is for emi basic config.
 */
	u32 nOenToEnd;				///<OEN to End
	u32 nSetupWr;				///<WEN after CEN
	u32 nTurnAround;			///<Turn arround cycle
	u32 nPageAddAcct;			///<Page address access
	u32 nWenCycle;				///<WEN cycle
	u32 nSetupRd;				///<OEN after CEN
	u32 nWrCs;					///<CEN cycle for write
	u32 nRdCs;					///<CEN cycle for read
	emi_mode_e nOpMode;			///<operation mode, 0x0:single mode,  0x01:page mode, 0x02:burst write, 0x04:burst read
	emi_type_e nType;			///<0x00:Nor, 0x01:Cellular RAM, 0x02:COSMORAM, 0x03:UtRAM, 0x04: SRAM
	u32 BurstReadWait;			///<0 = variable latency, =n: fix length latency
	u32 BurstWriteWait;			///<0 = variable latency, =n: fix length latency
	emi_pagesize_e nPageSize;	///<2^n words, 0:1word, 1,:2words, 2:4words, 3:8words, 4: 16words
	emi_Burstsize_e BurstSize;	///<0: no boundary, 1:4 words, 2:8words, 3:16words,  4:32words, 5:64words, 6:128words
} emi_BasicConfig_t;

typedef struct
{
/**
 * @struct emi_SmcConfig_t
 * @brief emi smc config
 * The structure is for emi smc config.
 */
#if 0
	u32 nOpMode; 		// operation mode, 0x00:page mode, 0x01:burst write, 0x02:burst read
	u32 nPageSize; 		// 00 = 4 words, 1 = 8 words, 2=	16 words, 3 = 32 words
	u32 nType;			// 0x00:Nor, 0x01:Cellular RAM, 0x02:COSMORAM, 0x03:UtRAM, 0x04: SRAM
	u32 WrAcct;			// WEN cycle
	u32 nWrCs;			// CEN cycle for write
	u32 nRdCs;			// CEN cycle for read
	u32 nTurnAround;				// Turn arround cycle
	u32 nPageAddAcct; 	// Page address access
	u32 nSetupRd;		// OEN after CEN
	u32 Rtor;
	u32 Wtow;
#elif 1
	u32 nOpMode;		///<operation mode, 0x00:page mode, 0x01:burst write, 0x02:burst read
	u32 nPageSize; 		///<00 = 4 words, 1 = 8 words, 2=	16 words, 3 = 32 words
	u32 nType;			///<0x00:Nor, 0x01:Cellular RAM, 0x02:COSMORAM, 0x03:UtRAM, 0x04: SRAM
	u32 nWenCycle;		///<WEN cycle
	u32 nWrCs;			///<CEN cycle for write
	u32 nRdCs;			///<CEN cycle for read
	u32 nTurnAround;	///<Turn arround cycle
	u32 nPageAddAcct; 	///<Page address access
	u32 nSetupRd;		///<OEN after CEN
	u32 nSetupWr;		///<WEN after CEN
	u32 nOenToEnd;		///<OEN to End
#endif
} emi_SmcConfig_t;

typedef struct
{
/**
 * @struct emi_mcpConfig_t
 * @brief emi mcp config
 * The structure is for emi mcp config.
 */
    emi_AdvancedConfig_t emiAdvanParams;	///<emi common parameters
    emi_BasicConfig_t NorBasicParams;		///<emi nor parameters
    emi_BasicConfig_t PsramBasicParams;		///<emi psram parameters
} emi_mcpConfig_t;

typedef struct
{
/**
 * @struct emi_EMIParam_t
 * @brief emi parameter
 * The structure is for emi register setting.
 */
    volatile u32 * RegAddr;		///<emi register address
    u32 RegData;				///<emi register data
} emi_EMIParam_t;

typedef struct
{
/**
 * @struct sys_EmiParams_t
 * @brief emi parameter
 * The structure is for emi parameter setting.
 */
    u32 flash_id;						///<Jedec ID of the Flash
    emi_mcpConfig_t * mcp_config;		///<emi full structure paramters
    AdvanSWCommand_t * NorSWCmd;		///<emi nor software commands array
    AdvanSWCommand_t * PsramSWCmd;		///<emi psram software commands array
    emi_mcpConfig_t * mcp_config_var;	///<mcp variable latency config
} sys_EmiParams_t;


/*!
 *      \brief The function pointer define
 */
typedef void (*fn_getExtendId)(u32*);

typedef struct
{
/**
 * @struct sys_EmiParams_Ext_t
 * @brief emi external parameter
 * The structure is for emi external parameter setting.
 */
    u32 flash_id;						///<Jedec ID of the Flash
    emi_mcpConfig_t  * mcp_config;		///<emi full structure paramters
    AdvanSWCommand_t * NorSWCmd;		///<emi nor software commands array
    AdvanSWCommand_t * PsramSWCmd;		///<emi psram software commands array
    u16 deviceSecondID ;				///<DIDR
    u16 SecondIDMask ;					///<DIDR mask
} sys_EmiParams_Ext_t;

typedef struct
{
/**
 * @struct fms_GroupFlashIdentifierEX_t
 * @brief flash group flash info
 * The structure is for flash driver info.
 */
    sys_EmiParams_Ext_t  *ps_FlashIdentifierEX;		///<flash parameter pointer
    u32                   u32_NumOfElement;			///<number of array size
    fn_getExtendId        pf_ExtendedID;			///<read DIDR function pointer
}fms_GroupFlashIdentifierEX_t;



typedef struct
{
/**
 * @struct emi_protect_region_t
 * @brief emi protect region
 * The structure is for emi protection.
 */
    u32 nBlockId;						///<id = 0..7
    u32 nStartAddr;						///<phsical address
    u32 nEndAddr;						///<phsical address
    u32 nClusterSize;					///<cluster size
    u32 nResideu;						///<resideu
    u32 nPattern;						///<pattern
    void (*pfnProtectCallback)(void);	///<function pointer
} emi_protect_region_t;

typedef struct
{
/**
 * @struct emi_mem_protect_setting_t
 * @brief emi protect setting
 * The structure is for emi protection setting.
 */
    u32     nBlockId;					///<id = 0..7

    u8      nClientId0;					///<client id0
    u8      nClientId1;					///<client id1
    bool    bInverseMach;				///<inversemach
    bool    bAddrRuleOutsideTheRange;	///<the range

    u32     nStartAddr;					///<physical address
    u32     nEndAddr;					///<physical address

    bool    bEnable;					///<enable flag
} emi_mem_protect_setting_t;


typedef struct
{
/**
 * @struct sys_IntelBusCtrlReg_t
 * @brief system bus control
 * The structure is for system bus control.
 */
	u32 BL:3;			///<BL 3bits
	u32 BW:1;			///<BW 1bit
	u32 DS:2;			///<DS 2bits
	u32 WC:1;			///<WC 1bit
	u32 WP:1;			///<WP 1bit
	u32 LAT:3;			///<LAT 3bits
	u32 OP:1;			///<OP 1bit
} sys_IntelBusCtrlReg_t;



//#define MCP_CONFIG_TABLE

#ifdef MCP_CONFIG_TABLE

#include "drv_flash_lowl_ht_pub.h"
#include "drv_flash_lowl_ho_pub.h"
#include "drv_emi_sram_nor_pub_types.h"

typedef enum
{
    FMS_S_CMDS_Numonyx             = 0x20,
    FMS_S_CMDS_Numonyx_Buf         = 0x21,
    FMS_S_CMDS_NumonyxM18_Buf      = 0x25,
    FMS_S_CMDS_Spansion            = 0x50,
    FMS_S_CMDS_Spansion_Buf        = 0x51,
    FMS_S_CMDS_SpansionVS_Buf      = 0x55,
    FMS_S_CMDS_SamsungA            = 0x60,
    FMS_S_CMDS_SamsungA_Buf        = 0x61,
    FMS_S_CMDS_SamsungB            = 0x64,
    FMS_S_CMDS_SamsungB_Buf        = 0x65,
    FMS_S_CMDS_Toshiba             = 0x70,
    FMS_S_CMDS_Toshiba_Buf         = 0x71,

    FMS_S_CMDS_SPI_Winbond_Buf     = 0xC0,
    FMS_S_CMDS_SPI_Macronix_Buf    = 0xC4,
    FMS_S_CMDS_SPI_Micron_Buf      = 0xD0,
    FMS_S_CMDS_SPI_Gigadevice_Buf  = 0xD4,
    FMS_S_CMDS_SPI_EONSI_Buf       = 0xD8,
    FMS_S_CMDS_SPI_ESMT_Buf        = 0xDC,

    FMS_S_CMDS_MAXINDEX,
} FMS_S_COMMANDSETS_E;

typedef struct
{				
    FMS_S_COMMANDSETS_E             fms_enum;
    const FlashActionsDescriptor_t *pDescriptors;
} FMS_S_CMDSETSMAPPING;

#endif

/*=============================================================*/
// External function prototype
/*=============================================================*/

/*!
 *  \fn EmiErrorCode_e DrvEmiInitSram(ClkgenClkSpeed_e speed, emi_SramNorCfg_t *config_array)
 *
 *  \brief Configures the EMI for SRAM (on CS_MEM1) accesses, for the given MIU speed.
 *
 *  \param speed			miu speed
 *  \param config_array		config array
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiInitSram(ClkgenClkSpeed_e speed, emi_SramNorCfg_t *config_array);

/*!
 *  \fn EmiErrorCode_e DrvEmiInitNor(ClkgenClkSpeed_e speed, emi_SramNorCfg_t *config_array)
 *
 *  \brief Configures the EMI for NOR Flash (on CS_MEM0) accesses, for the given MIU speed.
 *
 *  \param speed			miu speed
 *  \param config_array		config array
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiInitNor(ClkgenClkSpeed_e speed, emi_SramNorCfg_t *config_array);

/*!
 *  \fn EmiErrorCode_e DrvEmiSetMiuClk(ClkgenClkSpeed_e eMiuClkSpeed)
 *
 *  \brief Dynamic config miu clock speed functon.
 *
 *  \param eMiuClkSpeed		miu speed
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiSetMiuClk(ClkgenClkSpeed_e eMiuClkSpeed);

/*!
 *  \fn EmiErrorCode_e EmiErrorCode_e DrvEmiGpioPatch(bool bEnable)
 *
 *  \brief The function is Gpio patch for setting mcp by software commands.
 *
 *  \param bEnable	if true means gpio mode starting in emi pad.
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiGpioPatch(bool bEnable);

#ifdef MCP_CONFIG_TABLE

/*!
 *  \fn EmiErrorCode_e DrvEmiComputeAndSetEMIParams(emi_AdvancedConfig_new *pAdvancedConfig, emi_BasicConfig_new *pNorConfig, emi_BasicConfig_new *pPsramConfig, AdvanSWCommand_t *pNorSWCmd, AdvanSWCommand_t *pPsramSWCmd) 
 *
 *  \brief This is the main function that programming mcp into burst/page mode.
 *
 *  \param pMcpConfig			MCP setting parameters.
 *  \param pAdvancedConfig		advanced emi setting parameters.
 *  \param pNorConfig			parallel NOR setting parameters.
 *  \param pPsramConfig		PSRAM setting parameters.
 *  \param pNorSWCmd			parallel NOR software commands array.
 *  \param pPsramSWCmd		PSRAM software commands array.
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiComputeAndSetEMIParams(emi_mcpConfig_new *pMcpConfig, emi_AdvancedConfig_new *pAdvancedConfig, emi_BasicConfig_new *pNorConfig, emi_BasicConfig_new *pPsramConfig, AdvanSWCommand_t *pNorSWCmd, AdvanSWCommand_t *pPsramSWCmd);
#else

/*!
 *  \fn EmiErrorCode_e DrvEmiComputeAndSetEMIParams(emi_mcpConfig_t * config, AdvanSWCommand_t * NorSWCmd, AdvanSWCommand_t * PsramSWCmd)
 *
 *  \brief This is the main function that programming mcp into burst/page mode.
 *
 *  \param config		the emi config parameters.
 *  \param NorSWCmd		the emi setting parameters, nor software commands array.
 *  \param PsramSWCmd	the emi setting parameters, psram software commands array.
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiComputeAndSetEMIParams(emi_mcpConfig_t * config, AdvanSWCommand_t * NorSWCmd, AdvanSWCommand_t * PsramSWCmd);
#endif

#if __MCP_VALIDATION_TEST__

/*!
 *  \fn EmiErrorCode_e DrvEmiDumpEMIParams(void)
 *
 *  \brief This function is for parmaters dump.
 *
 *  \return -   RET_EMI_SUCCESS, if success
 *  \return -   Others, if fail
 */
EmiErrorCode_e DrvEmiDumpEMIParams(void);
#endif // __MCP_VALIDATION_TEST__

// EmiErrorCode_e DrvEmiSmcSetClock (ClkgenClkSpeed_e speed); // TODO: not used <-@@@
// EmiErrorCode_e DrvEmiSmcSetConfig(emi_Port_e portNo, const emi_SmcConfig_t *config); // TODO: not used <-@@@
// EmiErrorCode_e DrvEmiSetProtectRegion(emi_protect_region_t *protect_region); // TODO: not used <-@@@
// EmiErrorCode_e DrvEmiSetMemoryProtect(emi_mem_protect_setting_t *protect_setting); // TODO: not used <-@@@


/** @}*/
#endif // __DRV_EMI_SRAM_NOR_PUB_H__
