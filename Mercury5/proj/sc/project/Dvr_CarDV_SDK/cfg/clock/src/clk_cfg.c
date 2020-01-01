//------------------------------------------------------------------------------
//
//  File        : clk_cfg.c
//  Description : Source file of clock frequency configuration
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "clk_cfg.h"
#include "dram_cfg.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
/*
 * The following table decides the clock frequency of each clock domain.
 * The settings could seriously impact the system reliability & performance,
 * you MUST modifiy it carefully.
 *
 * The clock frequency of each group depends on the frequency of its source
 * (PLL or PMCLK), and its clock divider.
 */

//Notes: MCV_V2 EXT_CLK is 24Mhz
const MMPF_PLL_SETTINGS m_PllSettings[GRP_CLK_SRC_MAX] = 
{
    // M,      			N,      		DIV,        		Frac,	VCO,          		Freq}
    {0,	                0, 	            0,	                0, 		0, 	                600000},
};

const GRP_CLK_CFG gGrpClkCfg[CLK_GRP_NUM] = {
/*    src    div  */
    { DPLL2, 2 }, // CLK_GRP_GBL    264MHz
    { DPLL2, 1 }, // CLK_GRP_CPUA   528MHz
    { DPLL2, 1 }, // CLK_GRP_CPUB   528MHz
#if (DRAM_ID == DRAM_DDR)
    { DPLL0, 3 }, // CLK_GRP_DRAM   200MHz/180MHz
#elif (DRAM_ID == DRAM_DDR2)
    { DPLL5, 2 }, // CLK_GRP_DRAM   200MHz
#else //(DRAM_ID == DRAM_DDR3)
    { DPLL0, 1 }, // CLK_GRP_DRAM   400MHz
#endif
    { DPLL3, 1 }, // CLK_GRP_AUD 24.576MHz (may be changed in driver)
#if (CUSTOMIZED_DPLL1_CLOCK == 1)
    { DPLL1, 2 }, // CLK_GRP_SNR    297MHz (For SONY IMX322 sensor MCLK, it requests 297MHz / 8 = 37.125MHz)
#else
	{ DPLL5, 1 }, // CLK_GRP_SNR    480MHz
#endif
    { DPLL5, 1 }, // CLK_GRP_BAYER  480MHz
    { DPLL5, 1 }, // CLK_GRP_COLOR  480MHz
    { PMCLK, 1 }, // CLK_GRP_USB     24MHz
    { DPLL4, 7 }, // CLK_GRP_TV      54MHz
    { DPLL4, 2 }, // CLK_GRP_HDMI    24MHz (may be changed in driver)
    { PMCLK, 1 }, // CLK_GRP_MIPITX  24MHz
    { PMCLK, 1 }, // CLK_GRP_RXBIST  24MHz
};

