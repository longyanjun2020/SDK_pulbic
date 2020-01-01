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
 * \file sys_mem.c
 * \brief Intel PSRAM/NOR specific commands
 */

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "string.h"
#include "vm_types.ht"
#include "drv_clkgen_cmu.h"
#include "drv_emi_misc_pub.h"
#include "kernel.h"
#include "sys_traces.ho"
#include "drv_emi_sram_nor_pub.h"
#include "drv_imi_bw.h"
#include "sys_mem.h"
#include "sys.ho"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_sys_bootinit.h"
#include "drv_flash_lowl_ht_pub.h"

// #include "fms_atcmd.h" // <-@@@ ???
#include "drv_clkgen_cmu_api.h"

#ifdef __SUPPORT_BUS_FSP_SPI__
#include "drv_serial_flash.h"
#endif
#include "sys_sys_isw_uart.h" // UartSendTrace
#include "sys_chip.h"

#include "hal_drv_util.h"

#ifndef __NAND__
#include "mcp_drv_pub_types.h" 	// for const sys_EmiParams_t sys_EmiParams[];
								// for fms_GroupFlashIdentifierEX_t  fms_cas_Identifiers_Group[] ;

#ifdef MCP_CONFIG_TABLE

#include "mdl_fms_cus.h"

#ifdef __SUPPORT_BUS_FSP_SPI__
#ifdef __DUAL_SPI_FLASH__
#include "fms_defs.hm"
#endif //__DUAL_SPI_FLASH__
#endif //__SUPPORT_BUS_FSP_SPI__

void sys_ReadDIDR(u32 *device_id);

#define FLAT_ID_MEM_TABLE 0x4D52504DUL  // "MPRM"

s32 MemPrmCusCallback(u32 offset, u32 size, void *pParam)
{
    u32 *pParameter = pParam;

    *pParameter = offset;
	*(pParameter + 1) = size;

    return 0;
}

s32 sys_MemGetParameterFromCUS(u32 *nSize)
{
    u32 aParam[2] = {0};

    fms_AdIterateLow(FLAT_ID_MEM_TABLE, MemPrmCusCallback, aParam);

    *nSize = aParam[1];

    return aParam[0];
}

extern void sys_UartPrintf(const char *fmt, ...);

extern const FMS_S_CMDSETSMAPPING fms_s_CmdSets_Array[];

extern FlashDeviceGeometry_t_new fms_cas_tGeometry[];
extern FlashBanksDescriptor_t_new fms_cas_tBanks[];
extern FlashActionsDescriptor_t fms_cas_tActions[];

extern const emi_EmbeddedPsramConfig* sys_EmbeddedPsramConfig[];

static emi_mcpConfig_new *gMcpConfigFinal = NULL;
#ifdef __SUPPORT_BUS_FSP_SPI__
const emi_EmbeddedPsramConfig *gPsramConfigEmbedded = NULL;
#endif

u8 *gFlashName = NULL;

emi_mcpConfig_new* sys_GetEmiConfiguration(u32 Flash_ID)
{
    emi_mcpConfig_new *mcp_cus_fromBin = NULL;
    u32 nCusSize = 0, ii = 0, jj = 0;
    u32 extendID = 0, extendIDMask = 0;
    u8 nFlashNo;
    #ifdef __DUAL_SPI_FLASH__
    u32 FlashTypeExt = DrvFlashGetFlashTypeExt();
    #endif //__DUAL_SPI_FLASH__

    for (nFlashNo = 0; nFlashNo < 1; nFlashNo++)
    {
        fms_cas_Descriptors[nFlashNo].ptGeometry = &fms_cas_tGeometry[nFlashNo];
        fms_cas_Descriptors[nFlashNo].ptBanks = &fms_cas_tBanks[nFlashNo];
        fms_cas_Descriptors[nFlashNo].ptActions = &fms_cas_tActions[nFlashNo];
    }

#ifdef __DUAL_SPI_FLASH__
    if (NULL != FlashTypeExt)
    {
        fms_cas_Descriptors[1].ptGeometry = &fms_cas_tGeometry[0];
        fms_cas_Descriptors[1].ptBanks = &fms_cas_tBanks[0];
        fms_cas_Descriptors[1].ptActions = &fms_cas_tActions[1];
    }
#endif //__DUAL_SPI_FLASH__

    mcp_cus_fromBin = (emi_mcpConfig_new*)sys_MemGetParameterFromCUS(&nCusSize);

    //read DIDR
    sys_ReadDIDR(&extendID);

#ifdef __SUPPORT_BUS_FSP_SPI__
#ifndef __FPGA__
    {
        s32 ct = 0;

        while(sys_EmbeddedPsramConfig[ct] != NULL)
        {
            if (sys_EmbeddedPsramConfig[ct]->nID == (extendID & sys_EmbeddedPsramConfig[ct]->nIDMask))
            {
                gPsramConfigEmbedded = sys_EmbeddedPsramConfig[ct];
                break;
            }
            ct++;
        }
        if (gPsramConfigEmbedded == NULL)
            return NULL;
    }
#endif
#endif

#ifdef __SUPPORT_BUS_FSP_SPI__
    for (ii = 0; ii < (nCusSize / (sizeof(emi_mcpConfig_new) - sizeof(emi_BasicConfig_new))); ii ++)
#else
    for (ii = 0; ii < (nCusSize / sizeof(emi_mcpConfig_new)); ii ++)
#endif
    {
        if (mcp_cus_fromBin->nDeviceFullId == Flash_ID)
        {
            extendIDMask = mcp_cus_fromBin->nSecondIDMask;
            if (mcp_cus_fromBin->nDeviceSecondID  == (extendID&extendIDMask))
            {
                gMcpConfigFinal = mcp_cus_fromBin;

                #if 1
                fms_cas_Descriptors[0].nDeviceFullId = mcp_cus_fromBin->nDeviceFullId;
                fms_cas_Descriptors[0].nFeatures = mcp_cus_fromBin->nFeatures;
                fms_cas_Descriptors[0].ptGeometry->nDeviceSize = mcp_cus_fromBin->nDeviceSize;
                fms_cas_Descriptors[0].ptGeometry->nRegionNumber = mcp_cus_fromBin->nRegionNumber;
                fms_cas_Descriptors[0].ptGeometry->nPad = mcp_cus_fromBin->nPad;
                memcpy(fms_cas_Descriptors[0].ptGeometry->nAsRegions, mcp_cus_fromBin->nAsRegions, 8 * sizeof(FlashDeviceSectorRegion_new));

                fms_cas_Descriptors[0].ptBanks->nBankNumber = mcp_cus_fromBin->nBankNumber;
                memcpy(fms_cas_Descriptors[0].ptBanks->nBankAddresses, mcp_cus_fromBin->nBankAddresses, 32 * sizeof(u16));

                while (fms_s_CmdSets_Array[jj].pDescriptors)
                {
                    if (fms_s_CmdSets_Array[jj].fms_enum == mcp_cus_fromBin->nCommandSetsIndex)
                    {
                        memcpy(fms_cas_Descriptors[0].ptActions, fms_s_CmdSets_Array[jj].pDescriptors, sizeof(FlashActionsDescriptor_t));
                        break;
                    }

                    jj ++;
                }
                #endif

                gFlashName = mcp_cus_fromBin->nFlashName;

#ifdef __SUPPORT_BUS_FSP_SPI__
                #ifdef __DUAL_SPI_FLASH__
                if (NULL != FlashTypeExt)
                {
                    mcp_cus_fromBin = (emi_mcpConfig_new *)((u8*)mcp_cus_fromBin + (sizeof(emi_mcpConfig_new) - sizeof(emi_BasicConfig_new)));

                    fms_cas_Descriptors[1].nDeviceFullId = mcp_cus_fromBin->nDeviceFullId;
                    fms_cas_Descriptors[1].nFeatures = mcp_cus_fromBin->nFeatures;
                    fms_cas_tGeometry[0].nDeviceSize = (mcp_cus_fromBin->nDeviceSize + (FMS_FLASH_EMBED_SPI_FLASH_SIZE / 0x10000));
                    fms_cas_tGeometry[0].nRegionNumber = (mcp_cus_fromBin->nRegionNumber + 1);
                    fms_cas_tGeometry[0].nPad = mcp_cus_fromBin->nPad;
                    fms_cas_tBanks[0].nBankNumber = mcp_cus_fromBin->nBankNumber;
                    fms_cas_tBanks[0].nBankAddresses[0] += (FMS_FLASH_EMBED_SPI_FLASH_SIZE / 0x1000);

                    fms_cas_tGeometry[0].nAsRegions[0].nShiftedSize = mcp_cus_fromBin ->nAsRegions[0].nShiftedSize;
                    fms_cas_tGeometry[0].nAsRegions[0].nNumber = (FMS_FLASH_EMBED_SPI_FLASH_SIZE / (1 << mcp_cus_fromBin ->nAsRegions[0].nShiftedSize));
                    fms_cas_tGeometry[0].nAsRegions[1].nNumber = mcp_cus_fromBin ->nAsRegions[0].nNumber;
                    fms_cas_tGeometry[0].nAsRegions[1].nShiftedSize = mcp_cus_fromBin ->nAsRegions[0].nShiftedSize;
                    fms_cas_tGeometry[0].nAsRegions[2].nNumber = mcp_cus_fromBin ->nAsRegions[1].nNumber;
                    fms_cas_tGeometry[0].nAsRegions[2].nShiftedSize = mcp_cus_fromBin ->nAsRegions[1].nShiftedSize;

                    jj = 0;

                    while (fms_s_CmdSets_Array[jj].pDescriptors)
                    {
                        if (fms_s_CmdSets_Array[jj].fms_enum == mcp_cus_fromBin->nCommandSetsIndex)
                        {
                            memcpy(fms_cas_Descriptors[1].ptActions, fms_s_CmdSets_Array[jj].pDescriptors, sizeof(FlashActionsDescriptor_t));
                            break;
                        }

                        jj ++;
                    }
                }
                #endif //__DUAL_SPI_FLASH__
#endif //__SUPPORT_BUS_FSP_SPI__

                return mcp_cus_fromBin;
            }
        }
        mcp_cus_fromBin = (emi_mcpConfig_new *)((u8*)mcp_cus_fromBin + (sizeof(emi_mcpConfig_new) - sizeof(emi_BasicConfig_new)));
    }
    return NULL;
}


#else
extern sys_EmiParams_t * sys_GetEmiConfiguration(u32 Flash_ID);
void sys_ReadDIDR(u32 *device_id);

static sys_EmiParams_t *cur_memEmiParams = NULL;

sys_EmiParams_t * sys_GetEmiConfiguration(u32 Flash_ID)
{
    u32 i = 0 , j = 0;
    u32 extendID = 0, extendIDMask = 0;
    sys_EmiParams_Ext_t *pFlashIdentifierEX = NULL;
    u32 elementCount = 0;

    //look up didr and others group
    for (i = 0; fms_cas_Identifiers_Group[i].u32_NumOfElement != 0 ; i++)
    {
        if (fms_cas_Identifiers_Group[i].pf_ExtendedID != NULL)
        {
            fms_cas_Identifiers_Group[i].pf_ExtendedID(&extendID);
            pFlashIdentifierEX = fms_cas_Identifiers_Group[i].ps_FlashIdentifierEX;
            elementCount =  fms_cas_Identifiers_Group[i].u32_NumOfElement;
            for (j = 0; j < elementCount; j++)
            {
                if (pFlashIdentifierEX[j].flash_id == Flash_ID)
                {
                    extendIDMask = pFlashIdentifierEX[j].SecondIDMask;
                    if (pFlashIdentifierEX[j].deviceSecondID  == (extendID&extendIDMask))
                    {
                        cur_memEmiParams = (sys_EmiParams_t *) & pFlashIdentifierEX[j];
                        return cur_memEmiParams;
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    //look up normal group
    i = 0;
    do
    {
        if (sys_EmiParams[i].flash_id == Flash_ID)
        {
            cur_memEmiParams = (sys_EmiParams_t *) & (sys_EmiParams[i]);
            return cur_memEmiParams;
        }
        i++;
    }
    while ((void *)sys_EmiParams[i].flash_id != NULL);

    return NULL;
}
#endif

#endif // __NAND__

/*
 * \fn   : void sys_MemInit(void)
 * \brief: This function get corresponding EMI/MCP parameters from our table and call ComputeAndSetEMIParams to configure
 * \param: void
 */
void sys_MemInit(void)
{
#ifdef __FIXME__
    sys_ChipType_e eChiptype = sys_GetChipType();
#endif

#ifndef __NAND__

#ifdef MCP_CONFIG_TABLE
	u32 				Current_Flash_ID;
	emi_mcpConfig_new	*pEmiConfig_New = NULL;
#ifndef __FPGA__
	ClkgenClkSpeed_e 	eClkSpeed;
#endif

#ifdef __DUAL_SPI_FLASH__
    u32 FlashTypeExt = NULL;
#endif //__DUAL_SPI_FLASH__

	if(CHIP_TYPE_BRAVO == eChiptype)
		DrvEmiSetMiuClk(CLKGEN_26MHZ);

#if defined(__SUPPORT_BUS_FSP_SPI__)

#ifndef __DUAL_SPI_FLASH__
    if (TRUE == DrvSPIBootSrcIsSPI())
        DrvSetSPIChipSelect(SPINOR_CS1);
    Current_Flash_ID = DrvFSPReadID();
#else
    DrvSetSPIChipSelect(SPINOR_CS1);

    if (TRUE == DrvSPIBootSrcIsSPI())
    {
        Current_Flash_ID = DrvFSPReadID();
    }
    else
    {
        FlashTypeExt = DrvFSPReadID();
        DrvFlashSetFlashTypeExt(FlashTypeExt);
        DrvSetSPIChipSelect(SPINOR_CS0);
        Current_Flash_ID = DrvFSPReadID();
    }
#endif //__DUAL_SPI_FLASH__
    DrvSetSPIParameters(Current_Flash_ID);
#else
    Current_Flash_ID = DrvFlashProbe(MEM0_BASE_ADD);
#endif

    pEmiConfig_New = sys_GetEmiConfiguration(Current_Flash_ID);
    if (pEmiConfig_New != NULL)
        sys_UartPrintf("Flash ID = 0x%08X\n", pEmiConfig_New->nDeviceFullId);
    else
    {
#ifdef __SUPPORT_BUS_FSP_SPI__
        if (gPsramConfigEmbedded == NULL)
            sys_UartPrintf("Invalid Chip\n");
        else
#endif
            sys_UartPrintf("Invalid Flash Config\n");
#ifndef __FPGA__
        while(TRUE);
#endif
    }

#ifdef __SUPPORT_BUS_FSP_SPI__
    if (gPsramConfigEmbedded != NULL)
    {
#ifndef __FPGA__
        if (gPsramConfigEmbedded->pAdvanParams->smcCLK == EMI_CLK_66MHZ &&
            gPsramConfigEmbedded->pAdvanParams->dmcCLK == EMI_CLK_66MHZ)
            eClkSpeed = CLKGEN_124P8MHZ;
        else
            eClkSpeed = CLKGEN_156MHZ;

        DrvClkgenDrvSetMaxMiuSpeed(eClkSpeed);
        DrvEmiComputeAndSetEMIParams(pEmiConfig_New, gPsramConfigEmbedded->pAdvanParams, NULL, gPsramConfigEmbedded->pPsramParams, NULL, gPsramConfigEmbedded->pPsramSWCmd);
#endif
    }
#else
    if (pEmiConfig_New != NULL)
    {
#ifndef __FPGA__
        if (pEmiConfig_New->emiAdvanParams.smcCLK == EMI_CLK_66MHZ &&
            pEmiConfig_New->emiAdvanParams.dmcCLK == EMI_CLK_66MHZ)
            eClkSpeed = CLKGEN_124P8MHZ;
        else
            eClkSpeed = CLKGEN_156MHZ;

        DrvClkgenDrvSetMaxMiuSpeed(eClkSpeed);
        DrvEmiComputeAndSetEMIParams(pEmiConfig_New, &(pEmiConfig_New->emiAdvanParams), &(pEmiConfig_New->NorBasicParams), &(pEmiConfig_New->PsramBasicParams), &(pEmiConfig_New->Nor_SWCmd), &(pEmiConfig_New->Psram_SWCmd));
#endif
    }
#endif

	if(CHIP_TYPE_BRAVO == eChiptype)
		DrvEmiSetMiuClk(CLKGEN_156MHZ);

#else
    u32 Current_Flash_ID;
//	    sys_EmiParams_t  * EmiMcpParams = NULL;
//	    ClkgenClkSpeed_e eClkSpeed;

#ifdef __FIXME__
		if(CHIP_TYPE_BRAVO == eChiptype)
			DrvEmiSetMiuClk(CLKGEN_26MHZ);
#endif

#if defined(__SUPPORT_BUS_FSP_SPI__)

    UartSendTrace("g_ptKeQspi->reg_mode_sel = %d\n", g_ptKeQspi->reg_mode_sel);

    Current_Flash_ID = DrvSerflashReadID();

    DrvSetSPIParameters(Current_Flash_ID);

    UartSendTrace("Current_Flash_ID = 0x%x\n", Current_Flash_ID);

    UartSendTrace("g_ptKeQspi->reg_mode_sel = %d\n", g_ptKeQspi->reg_mode_sel);

#else
    Current_Flash_ID = DrvFlashProbe(MEM0_BASE_ADD);
#endif

#ifdef __FIXME__
    EmiMcpParams = sys_GetEmiConfiguration(Current_Flash_ID);

    if (EmiMcpParams != NULL)
    {
        if (EmiMcpParams->mcp_config->emiAdvanParams.smcCLK == EMI_CLK_66MHZ &&
            EmiMcpParams->mcp_config->emiAdvanParams.dmcCLK == EMI_CLK_66MHZ)
            eClkSpeed = CLKGEN_124P8MHZ;
        else
            eClkSpeed = CLKGEN_156MHZ;

        DrvClkgenDrvSetMaxMiuSpeed(eClkSpeed);
#if defined(__SUPPORT_BUS_FSP_SPI__)
        if ( HalIsGFType() )
            DrvEmiComputeAndSetEMIParams(EmiMcpParams->mcp_config_var, EmiMcpParams->NorSWCmd, EmiMcpParams->PsramSWCmd);
        else // Not GF Type
#endif
        DrvEmiComputeAndSetEMIParams(EmiMcpParams->mcp_config,
                    EmiMcpParams->NorSWCmd, EmiMcpParams->PsramSWCmd);
    }

		if(CHIP_TYPE_BRAVO == eChiptype)
			DrvEmiSetMiuClk(CLKGEN_156MHZ);
#endif	//MCP_CONFIG_TABLE
#endif	//__NAND__
#endif  // __FIXME__

#ifndef __FPGA__
#ifdef __FIXME__
    /* raise MIU and XIU to highest speed until CMU CLGKEN manages these two clocks */
    if (CHIP_TYPE_G1 != eChiptype)
    {
        //DrvClkgenDrvClockUpdate(CLKGEN_DRV_CORE, CLKGEN_CLK_MIU, CLKGEN_MIU_MAX);
        //DrvClkgenDrvClockUpdate(CLKGEN_DRV_CORE, CLKGEN_CLK_XIU, CLKGEN_78MHZ);

        sys_MemClockInit_first();
    }
#endif
#endif
}

#ifdef MCP_CONFIG_TABLE
void sys_GetMcpInformation(sys_McpOpMode* mcp_OpMode)
{

#if defined (__NAND__)
	mcp_OpMode->isNor = FALSE ;
	mcp_OpMode->flash_type = FLASH_NAND ;
#else
	mcp_OpMode->isNor = TRUE ;

#ifdef __SUPPORT_BUS_FSP_SPI__
	mcp_OpMode->flash_type = FLASH_SPI ;
#else
	mcp_OpMode->flash_type = FLASH_NOR ;
#endif		//__SUPPORT_BUS_FSP_SPI__

	if (gMcpConfigFinal)
	{
		mcp_OpMode->nor_OpMode = (emi_mode_e)gMcpConfigFinal->NorBasicParams.ParallelNorBasicParams.nOpMode ;
		mcp_OpMode->psram_OpMode = (emi_mode_e)gMcpConfigFinal->PsramBasicParams.nOpMode ;
	}
	else
	{
		mcp_OpMode->psram_OpMode =  EMI_SINGLE;
		mcp_OpMode->nor_OpMode   =  EMI_SINGLE ;
	}
#endif
	return ;
}
#else
void sys_GetMcpInformation(sys_McpOpMode* mcp_OpMode)
{

#if defined (__NAND__)
	mcp_OpMode->isNor = FALSE ;
	mcp_OpMode->flash_type = FLASH_NAND ;
#else
	sys_EmiParams_t *pMcpParams = cur_memEmiParams ;
	mcp_OpMode->isNor = TRUE ;

#ifdef __SUPPORT_BUS_FSP_SPI__
	mcp_OpMode->flash_type = FLASH_SPI ;
#else
	mcp_OpMode->flash_type = FLASH_NOR ;
#endif		//__SUPPORT_BUS_FSP_SPI__

	if(pMcpParams != NULL)
	{
		mcp_OpMode->nor_OpMode = pMcpParams->mcp_config->NorBasicParams.nOpMode ;
		mcp_OpMode->psram_OpMode = pMcpParams->mcp_config->PsramBasicParams.nOpMode ;
	}
	else
	{
		mcp_OpMode->psram_OpMode =  EMI_SINGLE;
		mcp_OpMode->nor_OpMode   =  EMI_SINGLE ;
	}
#endif
	return ;
}
#endif

#if defined(__arm) && !defined(__GNUC__)
#pragma arm section code = "ram_config"
#endif

#ifndef __NAND__
void sys_ReadDIDR(u32 *device_id)
{
    register volatile u32 value;
    MsIntMask_e ItMask;

    #define DIDR_INVALID 0xFFFF
    static u32 didr_kept = DIDR_INVALID;

    // XXX: this function is special, and it should be issued before
    // XXX: sys_Enable_cache() at first time (now is @ sys_MemInit())
    if (DIDR_INVALID == didr_kept)
    {
        ItMask = MsDisableInterrupt();

        DrvEmiGpioPatch(TRUE);

        /*Read DIDR*/
        value = *(volatile u16*)0x10FFFFFF;
        value = *(volatile u16*)0x10FFFFFF;
        *(volatile u16*)0x10FFFFFF = 0x0002; //read DIDR
        value = *(volatile u16*)0x10FFFFFF;

        /*device id*/
        *device_id = (value & 0xffff);
        didr_kept  = (value & 0xffff);

		DrvEmiGpioPatch(FALSE);

        MsEnableInterrupt(ItMask);
    }
    else
    {
        *device_id = didr_kept;
    }
}
#endif

void sys_PsramReset(void)
{
//	    register volatile u32 value;
    register volatile u32 BCR;
//	    register volatile u32 opmode;

    *(volatile u32*)0x74002888 = 0x0;
    *(volatile u32*)0x7400281c = *(volatile u32*)0x7400281c | 0x4;
    *(volatile u32*)0x74002818 = *(volatile u32*)0x74002818 | 0x1;

    /*Read BCR*/
//	    value = *(volatile u16*)0x10FFFFFF;
//	    value = *(volatile u16*)0x10FFFFFF;
    *(volatile u16*)0x10FFFFFF = 0x0001; //read BCR
    BCR = *(volatile u16*)0x10FFFFFF;

    /*Write BCR*/
    BCR |= 0x8000 ;
//	    value = *(volatile u16*)0x10FFFFFF;
//	    value = *(volatile u16*)0x10FFFFFF;
    *(volatile u16*)0x10FFFFFF = 0x0001; //Write BCR
    *(volatile u16*)0x10FFFFFF = BCR;
    /*lint -e550 */
    /*lint -e529 */
}
    /*lint +e550 */
    /*lint +e529 */
#if defined(__arm) && !defined(__GNUC__)
#pragma arm section code
#endif

#if defined(__EMI_POOL_PROTECT__)
#include "sys_rtk_hm.h"
#include "hal_emi_sram_nor.h"

__ONCE_CALL_ON_BOOT__ void sys_EmiPoolProtectInit(void)
{
	extern void sys_Invalidate_data_cache(void);
	extern pMemHandle_t ms_mhCtxt;
	int i;
	u32 cluster_size;

	for (i = 0; i < ms_mhCtxt->rtkCtxt.Rtk_NbOfPool; i++)
	{
		if (ms_mhCtxt->rtkCtxt.Rtk_PtrPoolDesc[i].NeedProtect)
		{
			cluster_size = ALIGN_MEM(ms_mhCtxt->rtkCtxt.Rtk_PtrPoolDesc[i].ClusterLength) + LEN_rtk_MemOverhead_t + EMI_POOL_GUARD_LEN;

			sys_EmiSetBW(
				1,
				i+1,
				(u32)ms_mhCtxt->rtkCtxt.Rtk_PtrPoolDesc[i].ClusterStart,
				(u32)ms_mhCtxt->rtkCtxt.Rtk_PtrPoolDesc[i].ClusterStart+cluster_size*ms_mhCtxt->rtkCtxt.Rtk_PtrPoolDesc[i].NbCluster,
				cluster_size,
				cluster_size-EMI_POOL_GUARD_LEN,
				(u32)((u32)EMI_POO_GUARD << 24) + ((u32)EMI_POO_GUARD << 16) + ((u32)EMI_POO_GUARD << 8) + EMI_POO_GUARD
			);
		}
	}
}

void sys_EmiSetBW(u32 en, u32 blockid, u32 start, u32 end, u32 cluster_size, u32 resideu, u32 pattern)
{
	extern void sys_Invalidate_data_cache(void);
	emi_protect_pat_t epr;

	//Flush initialized pool data
	sys_Invalidate_data_cache();

	epr.nEn = en;
	epr.nBlockId = blockid;
	epr.nStartAddr = start;
	epr.nClusterSize = cluster_size;
	epr.nEndAddr = end;
	epr.nResideu = resideu;
	epr.nPattern = pattern;

	_TRACE((_RTK | LEVEL_26, "en=%d, id=%d, start=0x%0.8x, end=0x%0.8x, c=%d, r=%d",
	epr.nEn, epr.nBlockId, epr.nStartAddr, epr.nEndAddr, epr.nClusterSize, epr.nResideu));

	DrvEmiSetMemProtectByPatternSnoop(&epr);
}

#endif // __EMI_POOL_PROTECT__

void sys_EmiStopBW(void)
{
	DrvEmiStopMemProtectByPatternSnoop(0);
}

void sys_MemProtectAt(u32 en, u32 blockid, u32 addr, u32 pattern)
{
#if defined(__EMI_POOL_PROTECT__)
	u32 align16, diff16;

	align16 = 0xFFFFFFF0 & addr;
	diff16 = addr - align16;
	sys_EmiSetBW(en, blockid, align16, align16+15, 16, diff16, pattern);
#else
	return;
#endif
}

void sys_ImiSetBW(u32 en, u32 blockid, u32 start, u32 end, u32 cluster_size, u32 resideu, u32 pattern)
{
	extern void sys_Invalidate_data_cache(void);

    //Flush initialized pool data
    sys_Invalidate_data_cache();

    DrvImiBw_Enable(FALSE);

    if (en)
    {
        DrvImiBw_SetConfiguration(blockid, start, end, pattern, IMIBW_RANGE_16_BYTES, resideu);
        DrvImiBw_Enable(TRUE);
    }
}

void sys_IMIProtectAt(u32 en, u32 blockid, u32 addr, u32 pattern)
{
	u32 align16, diff16;

	align16 = 0xFFFFFFF0 & addr;
	diff16 = addr - align16;
	sys_ImiSetBW(en, blockid, align16, align16+15, 16, diff16, pattern);
}

//#include "msmglobal.h"

u32 sys_GetM3RamAddress(void)
{
	return (u32)0;
}

__ONCE_CALL_ON_BOOT__ void sys_ActivateBurstRam(bool enable)
{
    // TODO:
}

__ONCE_CALL_ON_BOOT__ void sys_ActivateBurstNor(bool enable)
{
    // TODO:
}

/**
 * \fn void sys_MemClockInit_first(void)
 * \brief Set Memory Clock needed in sys_premain_second(). It set clock without using DrvClkgenDrvClockUpdate() due to
 *         malloc() cannot be used before RtkInitHeap()
 * \return None
 */
void sys_MemClockInit_first(void)
{
#ifdef __FIXME__
    DrvClkgenModuleSetMemClock();
#endif
}

/**
 * \fn void sys_MemClockInit_Second(void)
 * \brief After RtkInitHeap() is called, re-set memory clock and fill the clock table.
 * \return None
 */
void sys_MemClockInit_Second(void)
{
   // DrvClkgenDrvClockUpdate(CLKGEN_DRV_CORE, CLKGEN_CLK_MIU, CLKGEN_MIU_MAX);
   // DrvClkgenDrvClockUpdate(CLKGEN_DRV_CORE, CLKGEN_CLK_XIU, CLKGEN_78MHZ);
}

