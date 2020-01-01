//------------------------------------------------------------------------------
//
//  File        : mmp_clk_inc.h
//  Description : Header file of MMP system clock information
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------

#ifndef _MMP_CLK_INC_H_
#define _MMP_CLK_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================
/*
 * [NOTE]
 * The order of enumeration MMP_CLK_SRC should follow the global register spec.
 * The value is identical to the source selection bits of every group domain.
 * DON'T modify it unless you are implementing driver for a new CHIP.
 */
typedef enum _GRP_CLK_SRC {
    DPLL0       = 0,
    DPLL1       = 1,
    DPLL2       = 2,
    PMCLK       = 3,
    DPLL3       = 4,
    DPLL4       = 5,
    DPLL5       = 6,
    GRP_CLK_SRC_MAX
} GRP_CLK_SRC;

/*
 * - List of clock domains -
 * The list MUST starts from 0, and assign 0 to CLK_GRP_GBL (G0).
 * DON"T try to rearrange the order of enumeration CLK_GRP, otherwise
 * you HAVE TO update @ref gGrpClkCfg in clk_cfg.c for all projects.
 * Suggestion: only modify the enumeration during porting new CHIP driver.
 */
typedef enum _CLK_GRP {
    CLK_GRP_GBL = 0,    ///< Global  clock group
    CLK_GRP_CPUA,       ///< CPU A   clock group
    CLK_GRP_CPUB,       ///< CPU B   clock group
    CLK_GRP_DRAM,       ///< DRAM    clock group
    CLK_GRP_AUD,        ///< Audio   clock group
    CLK_GRP_SNR,        ///< Sensor  clock group
    CLK_GRP_BAYER,      ///< Bayer   clock group
    CLK_GRP_COLOR,      ///< Color   clock group
    CLK_GRP_USB,        ///< USB PHY clock group
    CLK_GRP_TV,         ///< TV      clock group
    CLK_GRP_HDMI,       ///< HDMI    clock group
    CLK_GRP_MIPITX,     ///< MIPI Tx clock group
    CLK_GRP_RXBIST,     ///< Rx BIST clock group
    CLK_GRP_NUM
} CLK_GRP;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

#endif // _MMP_CLK_INC_H_

