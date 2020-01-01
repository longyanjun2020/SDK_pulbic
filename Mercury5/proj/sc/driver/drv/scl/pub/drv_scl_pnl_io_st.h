////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 *  @file drv_scl_pnl_io_st.h
 *  @brief pnl Driver IOCTL parameter interface
 */

/**
* \ingroup sclpnl_group
* @{
*/

#ifndef __DRV_SCL_PNL_IO_ST_H__
#define __DRV_SCL_PNL_IO_ST_H__

//=============================================================================
// Defines
//=============================================================================
// library information
#define DRV_SCLPNL_VERSION                        0x0100



//=============================================================================
// enum
//=============================================================================
/// @cond
typedef enum
{
    E_DRV_SCLPNL_IO_ID_1,
    E_DRV_SCLPNL_IO_ID_NUM,
} DrvSclPnlIoIdType_e;

/**
* The error type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLPNL_IO_ERR_OK    =  0, ///< No Error
    E_DRV_SCLPNL_IO_ERR_FAULT = -1, ///< Fault
    E_DRV_SCLPNL_IO_ERR_INVAL = -2, ///< Invalid value
    E_DRV_SCLPNL_IO_ERR_MULTI = -3, ///< MultiInstance Fault
}DrvSclPnlIoErrType_e;
/// @endcond

//=============================================================================
// struct
//=============================================================================
/**
* Setup timing or lpll configuration for SCLPNL
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    u16 u16Vsync_St; ///< vertical sync start point
    u16 u16Vsync_End;///< vertical sync end point
    u16 u16Vde_St;   ///< vertical data enable start point
    u16 u16Vde_End;  ///< vertical data enable end point
    u16 u16Vfde_St;  ///< vertical framecolor data enable start point
    u16 u16Vfde_End; ///< vertical framecolor data enable end point
    u16 u16Vtt;      ///< vertical  total
    u16 u16Hsync_St; ///< horizontal sync start point
    u16 u16Hsync_End;///< horizontal sync end point
    u16 u16Hde_St;   ///< horizontal data enable start point
    u16 u16Hde_End;  ///< horizontal data enable end point
    u16 u16Hfde_St;  ///< horizontal framecolor data enable start point
    u16 u16Hfde_End; ///< horizontal framecolor data enable end point
    u16 u16Htt;      ///< horizontal total
    u16 u16VFreqx10; ///< vertical frequecny x10

    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclPnlIoTimingConfig_t;


/**
* The version of SCLPNL
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    u32   u32Version;      ///< version
    u32   VerChk_Size;     ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclPnlIoVersionConfig_t;

///@cond
/**
* The configuration of rotate for SCLPNL
*/
typedef struct
{
    DrvSclPnlIoErrType_e (*DrvSclPnlIoSetTimingConfig)(s32 s32Handler, DrvSclPnlIoTimingConfig_t *pstIOPnlTimingCfg);
    DrvSclPnlIoErrType_e (*DrvSclPnlIoSetLpllConfig)(s32 s32Handler, DrvSclPnlIoTimingConfig_t *pstIOPnlTimingCfg);
    DrvSclPnlIoErrType_e (*DrvSclPnlIoGetVersionConfig)(s32 s32Handler, DrvSclPnlIoVersionConfig_t *psIOVersionCfg);
}DrvSclPnlIoFunctionConfig_t;
///@endcond

//=============================================================================

//=============================================================================
#endif //

/** @} */ // end of sclpnl_group
